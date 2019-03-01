/**
 * @file     rsi_uart_framerdwr.c
 * @version  1.0
 * @date     2014-Sept-14
 *
 * Copyright(C) Redpine Signals 2013
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief UART Control: Functions used to control UART frame read/write functions
 *
 * @section Description
 * UART function to read/write management descriptors frames to/from the Wi-Fi module
 *
 * @section Improvements
 * Function header is modified for frameDscRd() function
 */


/*
 * Includes
 */
#include "platform_specific.h"
#include "rsi_serial.h"
#include "rsi_app_util.h"
#ifdef ZB_ENABLE
#include "rsi_zigb_types.h"
#include "rsi_zigb_global.h"
#include "rsi_zigb_api.h"
#include "rsi_zigb_app.h"
#elif WLAN_ENABLE
#include "rsi_global.h"
#include "rsi_app.h"
#endif

#ifdef WLAN_ENABLE
extern rsi_app_cb_t    rsi_app_cb;
#elif ZB_ENABLE
extern rsi_zigb_app_cb_t    rsi_zigb_app_cb;
#endif
extern rsi_linux_app_cb_t   rsi_linux_app_cb;
extern uint16_t rsi_check_queue_status(void);
/**
 * Global Variables
 */

/*====================================================*/
/**
 * @fn          int16 rsi_frame_read(uint8 *pkt_buffer)
 * @brief This  function is used to read the response from module.
 * @param[in]   uint8 *pkt_buffer, pointer to the buffer to which packet has to read
 *              which is used to store the response from the module
 * @param[out]  none
 * @return      errCode
 *              0  = SUCCESS
 * @section description 
 * This is a common function to read response for all the command and data from Wi-Fi module.
 */
int16_t rsi_frame_read(uint8_t *packet_buffer)
{
  /* Variables */
  rsi_linux_app_cb_t *linux_app_cbPtr = &rsi_linux_app_cb;
  pkt_struct_t *rspPtr = NULL;

  /* Length of the data to copy */
  int16_t length = 0;

  /* Pointer to the Packet file descriptor */
  uint8_t *descPtr    = NULL;

#ifdef RSI_DEBUG_PRINT
  int i;
#endif

  /* Do actual deque from the RX queue */
#ifdef WINDOWS
		EnterCriticalSection(&crit_sec);
#else
  pthread_mutex_lock(&linux_app_cbPtr->mutex1);
#endif
  rspPtr = rsi_dequeue_from_rcv_q();
  if (!rsi_check_queue_status()) {
    /* Set Packet Pending Event to Application */
#ifdef WLAN_ENABLE
    rsi_app_cb.pkt_pending = RSI_FALSE;
#elif ZB_ENABLE
	rsi_zigb_app_cb.pkt_pending = RSI_FALSE;
#endif
  }
#ifdef WINDOWS
		LeaveCriticalSection(&crit_sec);
#else
  pthread_mutex_unlock(&linux_app_cbPtr->mutex1);
#endif

  /* Assign pointers to appropriate addresses */
  descPtr    = (uint8_t *)rspPtr->data;

  /* Calculate length of the packet from the first two bytes of the frame descriptor */
  length = rsi_bytes2R_to_uint16(descPtr);
  length &= 0x0FFF;
#ifdef WLAN_ENABLE
  length += RSI_FRAME_DESC_LEN;
#elif ZB_ENABLE
  length += RSI_ZIGB_FRAME_DESC_LEN;
#endif


#ifdef RSI_DEBUG_PRINT
  /* Debug: Print the length & contents of the packet */
  RSI_DPRINT(RSI_PL0,"RX Len of the packet: %d\n", length);
  for (i=0; i<length; i++) {
      RSI_DPRINT (RSI_PL0, "0x%x ", descPtr[i]);
      if ((i % 16 == 0) && (i != 0)) {
          RSI_DPRINT(RSI_PL0, "\n");
      }
  }
  RSI_DPRINT(RSI_PL0, "\n");
#endif

  rsi_memset(packet_buffer, 0, length);
  rsi_memcpy(packet_buffer, descPtr, length);

  rsi_free(rspPtr);

  /* Return success */
  return 0 ;
}

/*====================================================*/
/**
 * @fn          int16 rsi_frame_write(rsi_uFrameDsc *uFrameDscFrame,uint8 *payloadparam,uint16 size_param)
 * @brief       Common function for all the commands.
 * @param[in]   uFrameDsc uFrameDscFrame, frame descriptor
 * @param[in]   uint8 *payloadparam, pointer to the command payload parameter structure
 * @param[in]   uint16 size_param, size of the payload for the command
 * @return      errCode
 *              0  = SUCCESS
 * @section description 
 * This is a common function used to process a command to the Wi-Fi module.
 */
#ifdef WLAN_ENABLE
int16_t rsi_frame_write(rsi_uFrameDsc *uFrameDscFrame,uint8_t *payloadparam,uint16_t size_param)
#elif ZB_ENABLE
int16_t rsi_frame_write(rsi_zigb_uFrameDsc *uFrameDscFrame,uint8_t *payloadparam,uint16_t size_param)
#endif
{
  int16_t retval = 0;
  uint8_t *cmd_buff;

  cmd_buff = rsi_alloc_and_init_cmdbuff((uint8_t *)uFrameDscFrame, payloadparam, size_param);
#ifdef WLAN_ENABLE
  retval = rsi_uart_send(cmd_buff, (size_param + RSI_FRAME_DESC_LEN));
#elif ZB_ENABLE
  retval = rsi_uart_send(cmd_buff, (size_param + RSI_ZIGB_FRAME_DESC_LEN));
#endif

  //! Free the command buffer
  free(cmd_buff);

  return retval;
}

