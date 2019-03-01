/**
 * @file       rsi_coex_execute_cmd.c
 * @version    2.7
 * @date       2012-Sep-26
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief Implements common functionality for all the commands
 *
 * @section Description
 * This file contains common api needed for all the commands
 *
 *
 */

/**
 * Includes
 */
#ifdef WLAN_ENABLE
#include "rsi_global.h"
#include "rsi_spi_cmd.h"
#include "rsi_app.h"

#ifdef COEX_APP_CHANGES
#include "rsi_scheduler.h"
void rsi_enq_pkt_to_wlan_q(rsi_uFrameDsc *uFrameDscFrame,UINT8 *payloadparam,UINT16 size_param);
UINT8 rsi_WlanTxPktStatus = 0;
#endif

/*====================================================*/
/**
 * @fn          int16 rsi_execute_cmd(uint8 *descparam,uint8 *payloadparam,uint16 size_param)
 * @brief       Common function for all the commands.
 * @param[in]   uint8 *descparam, pointer to the frame descriptor parameter structure
 * @param[in]   uint8 *payloadparam, pointer to the command payload parameter structure
 * @param[in]   uint16 size_param, size of the payload for the command
 * @return      errCode
 *              -1 = SPI busy / Timeout
 *              -2 = SPI Failure
 *              -3 = BUFFER FULL
 *              0  = SUCCESS
 * @section description 
 * This is a common function used to process a command to the Wi-Fi module.
 */
int16 rsi_execute_cmd(uint8 *descparam,uint8 *payloadparam,uint16 size_param)
{
  int16            retval = 0;
  rsi_uFrameDsc    uFrameDscFrame;
  //! 16 bytes, send/receive command descriptor frame
  //! Create the Command Frame Descriptor  
  rsi_build_frame_descriptor(&uFrameDscFrame,descparam);
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL13,"Descriptor write");
#endif
  //! Write descriptor and payload
#ifdef RSI_USE_HOST_WAKEUP_AS_INTERRUPT 
 // rsi_deassert_wakeup_source();
 // rsi_irq_enable(); 
#endif
  rsi_enq_pkt_to_wlan_q(&uFrameDscFrame, payloadparam, size_param);

  return retval;
}

void rsi_enq_pkt_to_wlan_q(rsi_uFrameDsc *uFrameDscFrame,UINT8 *payloadparam,UINT16 size_param)
{
  UINT8 *cmd_buff;
  PKT_STRUCT_T *pkt = (PKT_STRUCT_T *)&rsi_app_cb.write_packet_buffer;
  if(pkt == NULL)
  {
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"NULL POINTER ACCESS");
#endif
  return;
  }
  pkt->next = (PKT_STRUCT_T *)(((UINT8 *)pkt));
  pkt->data = (UINT8 *)(((UINT8 *)pkt) + (sizeof(UINT8 *) * 2) );
  cmd_buff = (UINT8 *)pkt->data;
  rsi_memcpy(cmd_buff, uFrameDscFrame, RSI_FRAME_DESC_LEN);
  rsi_memcpy((cmd_buff + RSI_FRAME_DESC_LEN), payloadparam, size_param);

  rsi_enqueue_to_rcv_q(&rsi_common_app_cb.rsi_wlan_tx_q, pkt);
  rsi_WlanTxPktStatus = 1; 
  rsi_set_event(RSI_TX_EVENT);
}

void rsi_wlan_free_pkt(PKT_STRUCT_T *pkt)
{
  rsi_WlanTxPktStatus = 0;
}
#endif
