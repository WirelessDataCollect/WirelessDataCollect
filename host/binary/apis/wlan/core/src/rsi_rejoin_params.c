/**
 * @file       rsi_rejoin_params.c
 * @version    2.7
 * @date       2014-June-23
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief REJOIN PARAMS: Function which implements the rejoin_params command
 *
 * @section Description
 * This file contains the rejoin params function.
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
 * @fn          int16 rsi_rejoin_params(rsi_rejoin_params_t *uRejoinFrame)
 * @brief       Sends the Rejoin Params command to the Wi-Fi module via SPI
 * @param[in]   rsi_rejoin_params_t *uRejoinFrame, Pointer to Rejoin Params structure
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
 * This API is used to give rejoin params to WiFi module. 
 *
 * @section prerequisite 
 * None
 */
int16 rsi_rejoin_params(rsi_rejoin_params_t *uRejoinFrame)
{
  int16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n Rejoin Params Start");
#endif
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdRejoinParams,(uint8 *)uRejoinFrame,sizeof(rsi_rejoin_params_t));
  return retval;
}


