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
#ifdef LINUX_PLATFORM
#include "rsi_serial.h"
#endif
#include "rsi_global.h"
#include "rsi_app.h"
#include "rsi_scheduler.h"

INT16 rsi_common_frame_write(UINT8 *cmd_buff, UINT16 size_param);
UINT16 rsi_check_queue_status(PKT_QUEUE_T *rcv_queue);

extern rsi_linux_app_cb_t   rsi_linux_app_cb;
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

INT16 rsi_frame_read(UINT8 *packet_buffer)
{
  /* Variables */
  PKT_STRUCT_T *rspPtr = NULL;

  /* Length of the data to copy */
  INT16 length = 0;
  /* Pointer to the Packet file descriptor */
  UINT8 *descPtr    = NULL;

#ifdef RSI_DEBUG_PRINT
  int i;
#endif

  rsi_enter_critical_sec();
  /* Do actual deque from the RX queue */
  if (!rsi_check_queue_status(&rsi_linux_app_cb.rcv_queue)) {
    /*
     * Clear this event if there is nothing pending
     * in queue
     */
    rsi_exit_critical_sec();
    return 1;
  }
  rspPtr = rsi_dequeue_from_rcv_q(&rsi_linux_app_cb.rcv_queue);
  rsi_exit_critical_sec();

  /* Assign pointers to appropriate addresses */
  descPtr    = (UINT8 *)rspPtr->data;
  /* Calculate length of the packet from the first two bytes of the frame descriptor */
  length = rsi_bytes2R_to_uint16(descPtr);
  length = length & 0x0fff;

  length += RSI_FRAME_DESC_LEN;

#ifdef RSI_DEBUG_PRINT
  /* Debug: Print the length & contents of the packet */
  RSI_DPRINT(RSI_PL13,"RX Len of the packet: %d\n", length);
  for (i=0; i<length; i++) {
    if ((i % 16 == 0) && (i != 0)) {
      RSI_DPRINT(RSI_PL13, "\n");
    }
    RSI_DPRINT (RSI_PL13, "0x%02x ", descPtr[i]);
  }
  RSI_DPRINT(RSI_PL13, "\n");

#endif

#if 1
  if (length > RSI_MAX_PAYLOAD_SIZE)
    length = RSI_MAX_PAYLOAD_SIZE;
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
INT16 rsi_frame_write(rsi_uFrameDsc *uFrameDscFrame,UINT8 *payloadparam,UINT16 size_param)
{
  INT16 retval = 0;
  UINT8 *cmd_buff;
  
  cmd_buff = rsi_alloc_and_init_cmdbuff((UINT8 *)uFrameDscFrame, payloadparam, size_param);

  retval = rsi_uart_send(cmd_buff, (size_param + RSI_FRAME_DESC_LEN));

  //! Free the command buffer
  rsi_free(cmd_buff);

  return retval;
}

