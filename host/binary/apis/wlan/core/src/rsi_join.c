/**
 * @file       rsi_join.c
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
 * @brief JOIN: Function which implements the join command
 *
 * @section Description
 * This file contains the Join function.
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
/*=================================================*/
/**
 * @fn          int16 rsi_join(rsi_uJoin *uJoinFrame)
 * @brief       Sends the Join command to the Wi-Fi module via SPI
 * @param[in]   rsi_uJoin *uJoinFrame, Pointer to join structure
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
 * This API is used to connect the Wi-Fi module to an Access Point. 
 * This API should be called only after rsi_scan API.
 *
 * @section prerequisite 
 * The rsi_scan for the access point should be done sussessfully.
 */
int16 rsi_join(rsi_uJoin *uJoinFrame)
{
  int16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL13,"\r\n\n Join Start");
  RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-25.25s-\"%s\"\n","WLAN","Tx","Join Req","Join Initiated with SSID ",&uJoinFrame->uJoinBuf[68]);
#endif
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdJoin,(uint8 *)uJoinFrame,sizeof(rsi_uJoin));
  return retval;
}


