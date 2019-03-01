/**
 * @file     	rsi_user_store_config.c
 * @version		1.0
 * @date 		2014-August-01
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief USER STORE CONFIG : sends User store configuration command
 *
 * @section Description
 * This file contains the user store configuration command
 *
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"

#if ENABLE_USER_STORE_CONFIGURATION
/*==============================================*/
/**
 * @fn          rsi_user_storecfg(rsi_uUserStoreCfg_t *ptr_userstrcfg)
 * @brief       Sends the user store configuration parameters command to the Wi-Fi module
 * @param[in]   rsi_user_storecfg(rsi_uUserStoreCfg_t *ptr_userstrcfg)
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
 * This API is used for send user stpre configuration parameters
 *  * This API has to be called only after the rsi_snmp_enable API.
 */
 
int16 rsi_user_store_config(rsi_user_store_config_t  *ptr_userstrcfg)
{
  int16               retval;
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nUSER STORE CONFIGURATION");
#endif

   retval = rsi_execute_cmd((uint8 *)rsi_frameCmdUserStoreCfg, (uint8 *)ptr_userstrcfg, sizeof(struct sc_params_s));
  return retval;
}
#endif


