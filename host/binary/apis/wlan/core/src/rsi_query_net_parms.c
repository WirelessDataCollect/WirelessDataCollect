/**
 * @file       rsi_query_net_parms.c
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
 * @brief QUERY NETWORK PARAMETERS: Function to get the status of an existing connection
 *
 * @section Description
 * This file contains the QUERY NETWORK PARAMETERS function.
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
 * @fn          int16 rsi_query_net_parms(void)
 * @brief       SPI, QUERY NETWORK PARAMETERS Command
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
 * This API is used to query the network parameters of the Wi-Fi module.
 */
int16 rsi_query_net_parms(void)
{
  int16            retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery NetworkParms Start");
#endif

  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdQryNetParms, NULL,0);
  return retval;
}




