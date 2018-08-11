/**
 * @file       rsi_bt_coex_execute_cmd.c
 * @version    1.0
 * @date       2015-Mar-4
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief Implements common functionality for all the BT commands
 *
 * @section Description
 * This file contains common API needed for all the BT commands
 *
 *
 */

/**
 * Includes
 */
#if defined(BLE_ENABLE) || defined(BT_ENABLE)  
#include "rsi_global.h"
#include "rsi_bt_global.h"
#include "rsi_bt_generic.h"
#include "rsi_bt_app.h"
#ifdef COEX_APP_CHANGES
#include "rsi_scheduler.h"
void rsi_enq_pkt_to_bt_q(RSI_BT_FRAME_DESC *uFrameDscFrame,UINT8 *payloadparam,UINT16 size_param);
UINT8 rsi_BtTxPktStatus = 0;
#endif
extern void rsi_bt_build_frame_descriptor(RSI_BT_FRAME_DESC *uFrameDescFrame, UINT08 *Cmd);

/*====================================================*/
/**
 * @fn          INT16 rsi_bt_execute_cmd(UINT08 *descparam,UINT08 *payloadparam,UINT16 size_param)
 * @brief       Common function for all the commands.
 * @param[in]   UINT08 *descparam, pointer to the frame descriptor parameter structure
 * @param[in]   UINT08 *payloadparam, pointer to the command payload parameter structure
 * @param[in]   UINT16 size_param, size of the payload for the command
 * @return      errCode
 *              -1 = SPI busy / Timeout
 *              -2 = SPI Failure
 *               0  = SUCCESS
 * @section description 
 * This is a common function used to process a command to the BT module.
 */
INT16 rsi_bt_execute_cmd(UINT08 *descparam, UINT08 *payloadparam, UINT16 size_param)
{
  INT16            retval=0;
  RSI_BT_FRAME_DESC  uFrameDscFrame;
  
  //! 16 bytes, send/receive command descriptor frame
  //! Create the Command Frame Descriptor  
  rsi_bt_build_frame_descriptor(&uFrameDscFrame, descparam);
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL13,"Descriptor write");
#endif

  rsi_enq_pkt_to_bt_q(&uFrameDscFrame, payloadparam, size_param);
  
  return retval;
}

#ifdef COEX_APP_CHANGES
void rsi_enq_pkt_to_bt_q(RSI_BT_FRAME_DESC *uFrameDscFrame,UINT8 *payloadparam,UINT16 size_param)
{
  UINT8 *cmd_buff;
  PKT_STRUCT_T *pkt = (PKT_STRUCT_T *)&rsi_bt_AppControlBlock.SendPacketBuffer;
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
  rsi_BtTxPktStatus = 1;
}

void rsi_bt_free_pkt(PKT_STRUCT_T *pkt)
{
  rsi_BtTxPktStatus = 0;

}
#endif
#endif
