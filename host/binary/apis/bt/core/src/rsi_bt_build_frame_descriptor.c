/**
 * @file     rsi_bt_build_frame_descriptor.c
 * @version  1.0
 * @date     2014-Aug-23
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief Function which builds the frame descriptor of BT Packet.
 *
 * @section Description
 * This file contains a function to build the frame descriptor of BT Packet.
 *
 *
 */


/**
 * Includes
 */
#include "rsi_bt_global.h"


/**
 * Global Variables
 */


/*==================================================*/
/**
 * @fn          void rsi_bt_build_frame_descriptor(RSI_BT_FRAME_DESC *uFrameDescFrame, UINT08 *Cmd)
 * @brief       Creates a Frame Descriptor
 * @param[in]   RSI_BT_FRAME_DESC *uFrameDescFrame,Frame Descriptor
 * @param[in]   UINT08 *Cmd,Indicates type and length of the packet
 * @param[out]  none
 * @return      none
 * 
 * @section description 
 * This API is used to build the frame descriptor for the BT packet which is supposed to be 
 * given to the firmware/module. 
 *
 */
void rsi_bt_build_frame_descriptor(RSI_BT_FRAME_DESC *uFrameDescFrame, UINT08 *Cmd)
{
  UINT08        i;  
  for (i = 0; i < RSI_BT_FRAME_DESC_LEN; i++) 
  { 
    uFrameDescFrame->uFrmDscBuf[i] = 0x00; 
  }  
  //!zero the frame descriptor buffer
  
  /* Cmd0[0:7],Cmd1[0:3] together represent length of the payload for the frame command
   * Cmd1[4:7], indicates queue number 0000 - Management, 0001 - Data
   * Cmd2[0:8], Cmd3[0:7] together represent the Frame command type. 
   */
  uFrameDescFrame->uFrmDscBuf[0] = Cmd[0];      
  uFrameDescFrame->uFrmDscBuf[1] = (Cmd[1] | (2 << 4));
  uFrameDescFrame->uFrmDscBuf[2] = Cmd[2];      
  uFrameDescFrame->uFrmDscBuf[3] = Cmd[3];      

  return;
}



