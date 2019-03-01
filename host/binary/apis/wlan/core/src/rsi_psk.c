/**
 * @file       rsi_psk.c
 * @version    1.0
 * @date       2014-Jan-07
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief PSK: sends PSK command to WiFi module
 *
 * @section Description
 * This file contains PSK command
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

/*===========================================================================
 *
 * @fn          int16 rsi_psk(rsi_uPsk *uPskReqFrame)
 * @brief       Sends the PSK command to the Wi-Fi module
 * @param[in]   rsi_uPsk *uPskReqFrame,Pointer to Psk structure
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
 * This API is used to set the desired PSK value 
 *
 */

int16 rsi_psk(rsi_uPsk *uPskReqFrame)
{
  int16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nPSK Start ");
#endif

  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdPsk, (uint8 *)uPskReqFrame, sizeof(rsi_uPsk));
  return retval;
}
