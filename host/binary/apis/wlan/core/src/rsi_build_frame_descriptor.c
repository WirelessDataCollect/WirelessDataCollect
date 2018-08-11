/**
 * @file     rsi_build_frame_descriptor.c
 * @version  2.7
 * @date     2012-Sep-26
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief Function which builds the frame descriptor
 *
 * @section Description
 * This file contains a function to build the frame descriptor.
 *
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"


/**
 * Global Variables
 */


/*==================================================*/
/**
 * @fn          void rsi_build_frame_descriptor(rsi_uFrameDsc *uFrameDscFrame, uint8 *cmd)
 * @brief       Creates a Frame Descriptor
 * @param[in]   rsi_uFrameDsc *uFrameDscFrame,Frame Descriptor
 * @param[in]   uint8 *cmd,Indicates type of the packet(data or management)
 * @param[out]  none
 * @return      none
 * 
 * @section description 
 * This API is used to build the frame descriptor for the packet which is supposed to be 
 * given to the firmware/module 
 *
 */
void rsi_build_frame_descriptor(rsi_uFrameDsc *uFrameDscFrame, uint8 *cmd)
{
  uint8        i; 
  uint8        queue_no;
  for (i = 0; i < RSI_FRAME_DESC_LEN; i++) 
  { 
    uFrameDscFrame->uFrmDscBuf[i] = 0x00; 
  } 
  queue_no = (cmd[1] & 0xf0) >> 4;
  //!zero the frame descriptor buffer
  //!data or management frame type
  if ((queue_no == WLAN_MGMT_TYPE )||(queue_no == WLAN_DATA_TYPE)) 
  {
    //!The first two bytes have different functions for management frames and
    //!control frames, but these are set in the pre-defined
    uFrameDscFrame->uFrmDscBuf[0] = cmd[0];      
    //!arrays which are the argument passed to this function, so we just set the two values
    uFrameDscFrame->uFrmDscBuf[1] = cmd[1];
    uFrameDscFrame->uFrmDscBuf[2] = cmd[2];      
  }
  else if ((queue_no == BT_MGMT_TYPE )||(queue_no == BT_DATA_TYPE)) 
  {
    //!The first two bytes have different functions for management frames and
    //!control frames, but these are set in the pre-defined
    uFrameDscFrame->uFrmDscBuf[0] = cmd[0];      
    //!arrays which are the argument passed to this function, so we just set the two values
    uFrameDscFrame->uFrmDscBuf[1] = cmd[1];
    uFrameDscFrame->uFrmDscBuf[2] = cmd[2];      
    uFrameDscFrame->uFrmDscBuf[3] = cmd[3];      
  }
  else if(queue_no == ZB_MGMT_TYPE)
  {
    for (i = 0; i < RSI_FRAME_DESC_LEN; i++) 
    { 
      uFrameDscFrame->uFrmDscBuf[i] = cmd[i]; 
    }  
  }
  else
  {
#ifdef RSI_DEBUG_PRINT  
     RSI_DPRINT(RSI_PL4,"\n INVALID QUEUE : ERROR !!!!!\n "); 
#endif 

  }


  return;
}



