/**
 *  @file     rsi_zigb_execute_cmd.c
 *  @version  1.0
 *  @date     2014-Aug-23
 *
 *  Copyright(C) Redpine Signals 2014
 *  All rights reserved by Redpine Signals.
 *
 *  @section License
 *  This program should be used on your own responsibility.
 *  Redpine Signals assumes no responsibility for any losses
 *  incurred by customers or third parties arising from the use of this file.
 *
 *  @brief 
 *
 *  @section Description
 *  This file contains definition to initiate zigbee write command
 *
 *  @section Improvements
 *
 */


/**
 * Includes
 * */

#ifdef ZB_ENABLE
#include "rsi_zigb_global.h"
#ifdef COEX_APP_CHANGES
#include "rsi_scheduler.h"
#include "platform_specific.h"
#include "rsi_zigb_app.h"
void rsi_enq_pkt_to_zb_q(rsi_zigb_uFrameDsc *uFrameDscFrame,UINT8 *payloadparam,UINT16 size_param);
UINT8 rsi_ZBTxPktStatus = 0;
#endif

/*===========================================================================
 *
 * @fn          int16_t rsi_zigb_execute_cmd(uint8_t *desc, uint8_t *payload, 
 *                                           uint16_t length)
 * @brief       ZigBee Execute command 
 * @param[in]   desc    - descriptor pointer
 * @param[in]   payload - payload pointer
 * @param[in]   length
 * @param[out]  none
 * @return      Status
 * @section description
 * This API is used to execute ZigBee pkt and this should be written to device 
 *
 * ===========================================================================*/
  
int16_t rsi_zigb_execute_cmd(uint8_t *desc, uint8_t *payload, uint16_t length)
{
  int16_t ret_val=0;

  rsi_zigb_uFrameDsc uFrameDscFrame;

#ifdef ZB_DEBUG
  RSI_DPRINT(RSI_PL13,"Descriptor Write\n");
  RSI_DPRINT(RSI_PL13,"TX Pkt: Len of the packet: %d\n", length);
#endif

  //! 16 bytes, send/receive command descriptor frame
  //! Create the Command Frame Descriptor  
  rsi_zigb_build_frame_descriptor(&uFrameDscFrame, desc, length);

  rsi_enq_pkt_to_zb_q(&uFrameDscFrame, payload, length);
  return ret_val;
}

#ifdef COEX_APP_CHANGES

extern rsi_zigb_app_cb_t   rsi_zigb_app_cb;
void rsi_enq_pkt_to_zb_q(rsi_zigb_uFrameDsc *uFrameDscFrame,UINT8 *payloadparam,UINT16 size_param)
{
  UINT8 *cmd_buff;
  PKT_STRUCT_T *pkt = (PKT_STRUCT_T *)&rsi_zigb_app_cb.send_buffer;
    
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
  rsi_memcpy(cmd_buff,(UINT8*)uFrameDscFrame, RSI_FRAME_DESC_LEN);
  rsi_memcpy((cmd_buff + RSI_FRAME_DESC_LEN), payloadparam, size_param);

  rsi_enqueue_to_rcv_q(&rsi_common_app_cb.rsi_bt_or_zb_tx_q, pkt);
  rsi_set_event(RSI_TX_EVENT);
  rsi_ZBTxPktStatus = 1;
}

void rsi_zb_free_pkt(PKT_STRUCT_T *pkt)
{
  rsi_ZBTxPktStatus = 0;

}
#endif
#endif
