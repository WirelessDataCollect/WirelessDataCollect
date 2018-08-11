/**
 * @file     rsi_debug_prints.c
 * @version  1.0
 * @date     2014-Jun-6
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief DEBUG: Enables debug prints
 *
 * @section Description
 * This file contains the Debug enable function.
 *
 *
 */

/**
 * Includes
 */
#include "rsi_global.h"

/*==============================================*/
/**
 * @fn          int16 rsi_debug_prints(rsi_udebug *uDebugFrame)
 * @brief       Sends the Debug command to the Wi-Fi module,
 *              used to get debug prints on uart2
 * @param[in]   rsi_udebug, pointer to debug structure.
 * @param[out]  none
 * @return      errCode
 *              SPI:
 *              -1 = SPI busy / Timeout
 *              -2 = SPI Failure
 *              -3 = BUFFER FULL
 *              0  = SUCCESS
 *              UART/USB/USB-CDC:
 *              -2 = Command issue failed
 *              0  = SUCCESS
 * @section description 
 * This API is used to enable debug prints.
 * This API has to be called before oper mode command.
 * Based on the level enabled,debug prints will be coming on UART2 interface
 */
int16 rsi_debug_prints(rsi_uDebug *uDebugFrame)
{
  int16               retval;  
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nDebug Start");
#endif
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdDebug, (uint8 *)uDebugFrame, sizeof(rsi_uDebug));
  return retval;
}


