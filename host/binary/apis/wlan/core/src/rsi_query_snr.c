/**
 * @file       rsi_query_snr.c
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
 * @brief QUERY SNR: Get the SNR with respect to connected AP
 *
 * @section Description
 * This file contains the QUERY SNR function.
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
 * @fn          int16 rsi_query_snr(void)
 * @brief       SPI, QUERY SNR Command
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
 *      
 * @section description 
 * This API is used to query the SNR for the Wi-Fi module with respect to connected AP.
 */
int16 rsi_query_snr(void)
{
  int16            retval;
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery Snr Start");
#endif
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdSnr,NULL,0);
  return retval;
}




