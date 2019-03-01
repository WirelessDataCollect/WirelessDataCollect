/**
 * @file       rsi_roam_params.c
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
 * @brief Roam Params: Function which sets the roaming parameters 
 *
 * @section Description
 * This file contains the Roaming Parameter set function.
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
 * @fn          int16 rsi_roam_params(rsi_uRoamParams *uRoamParamsFrame)
 * @brief       Sets the Roaming parameters in the Wi-Fi module 
 * @param[in]   rsi_uRoamParams *uRoamParamsFrame, Pointer to Roam Params structure
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
 * This API is used to give the Roaming Parameter set Request . 
 * @section prerequisite 
 * The BGscan  should be done sussessfully.
 */
 
int16 rsi_roam_params(rsi_uRoamParams *uRoamParamsFrame)
{
    int16  retval;

 #ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n ROAM PARAMS start");
 #endif

  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdRoamParams,(uint8 *)uRoamParamsFrame,sizeof(rsi_uRoamParams));
  
  return retval;
}
