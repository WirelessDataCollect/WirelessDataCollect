/**
 * @file       rsi_host_rtc_time.c
 * @version    8.4
 * @date       2016-April-5
 *
 * Copyright(C) Redpine Signals 2016
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief implements the set rtc time command used to initialize the module rtc time.
 *
 * @section Description
 * This file contains the rsi_host_rtc_time function.
 *
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"



/*=================================================*/
/**
 *@fn            int16 rsi_host_rtc_time(module_rtc_time_t *rtc_time)
 * @brief        Sends the host rtc time command to the Wi-Fi module via SPI
 * @param[in]    
 *               
 * @param[out]   none
 * @return       errCode
 *               SPI:
 *                -1 = SPI busy / Timeout
 *                -2 = SPI Failure
 *                -3 = BUFFER FULL
 *                0  = SUCCESS
 *               UART/USB/USB-CDC:
 *                -2 = Command issue failed
 *                0  = SUCCESS
 * @section description 
 * This API is used to send the host rtc time.
 */
int16 rsi_host_rtc_time(module_rtc_time_t *rtc_time)
{
  int16    retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nRTC time from host");
#endif
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdRtcTime,(uint8 *)rtc_time, sizeof(module_rtc_time_t));
  return retval;
}

