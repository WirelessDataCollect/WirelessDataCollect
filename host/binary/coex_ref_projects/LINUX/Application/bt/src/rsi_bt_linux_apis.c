/**
 * @file      rsi_bt_linux_apis.c
 * @version   1.0
 * @date      2014-Aug-26
 *
 * Copyright(C) Redpine Signals 2014
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
#include "rsi_bt_global.h"
#include "rsi_global.h"
#include "rsi_nl_app.h"
#include "rsi_bt_api.h"
#include "rsi_bt_app.h"
#include "rsi_defines.h"
#include <sys/ioctl.h>

/**
 * Function Declarations
 */


/*====================================================*/
/**
 * @fn          int16 rsi_bt_execute_cmd(uint8 *descparam,uint8 *payloadparam,uint16 size_param)
 * @brief       Common function for all the commands.
 * @param[in]   uint8 *descparam, pointer to the frame descriptor parameter structure
 * @param[in]   uint8 *payloadparam, pointer to the command payload parameter structure
 * @param[in]   uint16 size_param, size of the payload for the command
 * @return      errCode
 *              -2 = Command issue failed
 *              0  = SUCCESS
 * @section description
 * This is a common function used to process a command to the Wi-Fi module.
 */

int16 rsi_bt_execute_cmd(uint8 *descparam, uint8 *payloadparam, uint16 size_param)
{
  int16                                         retval = 0;
  RSI_BT_FRAME_DESC         uFrameDscFrame;
  uint8           *cmd_buff;
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_execute_cmd:\n");
#endif

#ifdef SPI_INTERFACE
  while(rsi_buffer_isFull());
#endif

  //! Build 16 bytes, send/receive command descriptor frame
  rsi_bt_build_frame_descriptor(&uFrameDscFrame,descparam);

  cmd_buff = rsi_alloc_and_init_cmdbuff((uint8 *)&uFrameDscFrame,payloadparam,size_param);

  if(rsi_send_usr_cmd(cmd_buff, GET_SEND_LENGTH(cmd_buff)) < 0)
  {
    retval = -2;
  }
  if(retval < 0)
  {
    RSI_DPRINT(RSI_PL13,"Unable to issue command\n");
  }

  //! Free the command buffer
  rsi_free(cmd_buff);

  return retval;
}

