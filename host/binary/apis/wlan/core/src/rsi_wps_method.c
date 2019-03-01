/**
 * @file       rsi_wps_method.c
 * @version    1.0
 * @date       2014-Apr-16
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief WPS METHOD: Function which sets the WPS METHOD parameters 
 *
 * @section Description
 * This file contains the WPS METHOD Parameter set function.
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
 * @fn          int16 rsi_wps_method(rsi_uWpsMethod *uWpsMethodFrame)
 * @brief       Sets the WPS PIN METHOD parameters in the Wi-Fi module 
 * @param[in]   rsi_uWpsMethod *uWpsMethodFrame, Pointer to WPS Method structure
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
 * This API is used to give the WPS  method Parameter set Request . 
 * @section prerequisite 
 * The scan should be done sussessfully.
 */
 
int16 rsi_wps_method(rsi_uWpsMethod *uWpsMethodFrame)
{
    int16  retval;

 #ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n WPS METHOD start");
 #endif

  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdWpsMethod,(uint8 *)uWpsMethodFrame,sizeof(rsi_uWpsMethod));
  
  return retval;
}
