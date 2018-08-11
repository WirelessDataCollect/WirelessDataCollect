/**
 * @file     rsi_socket_config.c
 * @version  1.0
 * @date     2015-Feb-23
 *
 * Copyright(C) Redpine Signals 2015
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief SOCKET CONFIG: Function sets the sockets configuration 
 *
 * @section Description
 * This file contains the SOCKET CONFIGURATION function.
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


/**===========================================================================
 * @fn          int16 rsi_socket_config(rsi_socket_config_t *socket_config)
 * @brief       API is used to set the sockets configuration
 * @param[in]   socket_config, pointer to socket configration sructure
 * @param[out]  none
 * @return      errCode
 *                 SPI:
 *                  -1 = SPI busy / Timeout
 *                  -2 = SPI Failure
 *                  -3 = BUFFER FULL
 *                  0  = SUCCESS
 *                 UART/USB/USB-CDC:
 *                  -2 = Command issue failed
 *                  0  = SUCCESS
 *       
 * @section description  
 * This API is used to set the sockets configuration.
 * @section prerequisite 
 * It has to be called only after the module has been assigned an IP address using the 
 * rsi_ipparam_set API.
 */
int16 rsi_socket_config(rsi_socket_config_t *socket_config)
{
  int16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\nSocket Config\n");
#endif
  retval = rsi_execute_cmd((uint8 *)rsi_frameSocketConfig,(uint8 *)socket_config,sizeof(rsi_socket_config_t));
  return retval;
}

