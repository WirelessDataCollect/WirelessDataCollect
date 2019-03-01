/**
 * @file       rsi_ping_request.c
 * @version    3.6
 * @date       2013-Mar-8
 *
 * Copyright(C) Redpine Signals 2013
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief, PING REQUEST, implements the ping request  command
 *
 * @section Description
 * This file contains the ping request function.
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
 * @fn          int16 rsi_ping_request(rsi_ping_request_t *pingReq)
 * @brief       Sends the ping request command to the Wi-Fi module
 * @param[in]   rsi_ping_request_t *pingReq, Pointer to ping request data structure
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
 * This API is used to send ping request from Wi-Fi module. 
 * This API should be called only after successful connection 
 * establishment and IP configuration..
 *
 * @section prerequisite 
 * The rsi_ipparam_set of the Wi-Fi module should be done successfully.
 */
int16 rsi_ping_request(rsi_ping_request_t *pingReq)
{
  int16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n Ping Request Start");
#endif

  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdPingRequest ,(uint8 *)pingReq, 
                                                      sizeof(rsi_ping_request_t));
  return retval;
}
