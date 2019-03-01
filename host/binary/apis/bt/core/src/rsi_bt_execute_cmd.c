/**
 * @file       rsi_bt_execute_cmd.c
 * @version    1.0
 * @date       2014-Aug-23
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
#include "rsi_bt_global.h"
#include "rsi_bt_generic.h"


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
  INT16            retval;
  RSI_BT_FRAME_DESC  uFrameDscFrame;
  
  //! 16 bytes, send/receive command descriptor frame
  //! Create the Command Frame Descriptor  
  rsi_bt_build_frame_descriptor(&uFrameDscFrame, descparam);
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"Descriptor write");
#endif

  //! Write descriptor and payload
  retval = rsi_frame_write(&uFrameDscFrame, payloadparam, size_param);

  if (retval != 0x00) 
  {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL4,"Frame write failErr=%02x", (UINT16)retval);
#endif
    return retval;
  }
  
  return retval;
}

