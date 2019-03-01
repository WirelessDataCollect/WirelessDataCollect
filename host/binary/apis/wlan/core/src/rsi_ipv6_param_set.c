/**
 * @file       rsi_ipv6_param_set.c
 * @version    1.0
 * @date       2014-Mar-03
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief IP PARAMETERS: Function to set IPV6 Address to WiFi module.
 *
 * @section Description
 * This file contains the TCPIP function.
 *
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"


/*==============================================*/
/**
 * @fn          int16 rsi_ipv6_param_set(rsi_uIPconf6  *uIpconf6Frame)
 * @brief       Sends the ipv6 address to the Wi-Fi module
 * @param[in]   rsi_uIPconf6  *uIpconf6Frame
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
 * This API is used to set ipv6 address.
 * This API has to be called only after the rsi_join API.
 */

int16 rsi_ipv6_param_set(rsi_uIPconf6  *uIpconf6Frame)
{
  int16               retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nIPV6 ipconfig6 Start");
#endif
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdIPconf6,(uint8 *)uIpconf6Frame, sizeof(rsi_uIPconf6));
  return retval;
}


