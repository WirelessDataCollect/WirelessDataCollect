/**
 * @file      rsi_web_fields.c
 * @version   2.7
 * @date      2012-Sep-26
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief WEB FIELDS: Function which implements the web fields command
 *
 * @section Description
 * This file contains the web fields function.
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
 * @fn          int16 rsi_web_fields(rsi_uWebFields *uWebFields)
 * @brief       Sends the WebFields command to the Wi-Fi module via SPI
 * @param[in]   rsi_uWebFields *uWebFields, Pointer to Webfields structure
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
 * This API is used to load the webpage to the Wi-Fi module. 
 * This API should be called only after rsi_init API.
 *
 * @section prerequisite 
 * The rsi_init for the Wi-Fi Module initialization should be done successfully.
 */
int16 rsi_web_fields(rsi_uWebFields *uWebFields)
{
	int16	retval;

#ifdef RSI_DEBUG_PRINT
	RSI_DPRINT(RSI_PL3,"\r\n\n Web Fields Start");
#endif

	retval = rsi_execute_cmd((uint8 *)rsi_frameCmdWebFields ,(uint8 *)uWebFields, sizeof(rsi_uWebFields));
	return retval;
}
