/**
 * @file       rsi_http_abort.c
 * @version    2.7
 * @date       2015-Feb-4
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief HTTP ABORT: Function to abort the current execution of the http request.
 *
 * @section Description
 * This file contains the HTTP ABORT function.
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


/*===========================================================================*/
/**
 * @fn          int16 rsi_http_abort(void)
 * @brief       Sends the HTTP ABORT command to the Wi-Fi module

 * @param[in]   none
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 *      
 * @section description 
 * This API is used to abort the http request of the Wi-Fi module.
 */
int16 rsi_http_abort(void)
{
  int16            retval;
  uint8   rsi_frameCmdHttpAbort[RSI_BYTES_3] = {0x00, 0x40, 0xB3};

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nSTART HTTP ABORT\n");
#endif

  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdHttpAbort, NULL,0);
  return retval;
}




