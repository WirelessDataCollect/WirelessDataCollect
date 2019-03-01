/**
 * @file       rsi_rf_power_mode.c
 * @version    2.7
 * @date       2015-Feb-04
 *
 * Copyright(C) Redpine Signals 2015
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief RF POWER: Function which sets the modules RF power levels
 *
 * @section Description
 * This file contains the function to set the module RF power levels
 * This command must be preceeded by the BAND command
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

/*==============================================*/
/**
 * @fn             int16 rsi_rf_current_config(rsi_rf_current_config_t *rf_config)
 * @brief          Set RF TX/RX Power/current Levels
 * @param[in]      rsi_rf_current_config_t *rf_config, Pointer to rf current mode configuration structure
 * @param[out]     none
 * @return         errCode
 *                 -2 = Command execution failed
 *                 -1 = Buffer Full
 *                 0  = SUCCESS
 * @section description   
 * This API is used set RF current/Power levels. 
 * It has to be called only before rsi_init APIs.
 */
int16 rsi_rf_current_config(rsi_rf_current_config_t *rf_config)
{
	int16  retval;
	
#ifdef RSI_DEBUG_PRINT
	RSI_DPRINT(RSI_PL3,"\r\n\nRF Power/Current Command Start");
#endif

	retval = rsi_execute_cmd((uint8 *)rsi_frameCmdRFCurConfig, (uint8 *)rf_config, sizeof(rsi_rf_current_config_t));
	return retval;
		
}
