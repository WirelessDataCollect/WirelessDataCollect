/**
 * @file       rsi_query_rssi.c
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
 * @brief QUERY RSSI: Get the RSSI
 *
 * @section Description
 * This file contains the QUERY RSSI function.
 *
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"
#include <stdio.h>
#include <string.h>
 

/**
 * Global Variables
 */


/*===========================================================================*/
/**
 * @fn          int16 rsi_query_rssi(void)
 * @brief       SPI, QUERY RSSI Command
 * @param[in]   none
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
 * This API is used to query the rssi of the Wi-Fi module.
 */
int16 rsi_query_rssi(void)
{
  int16            retval;
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery Rssi Start");
#endif
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdRssi,NULL,0);
  return retval;
}




