/**
 * @file       rsi_per_mode.c
 * @version    1.0
 * @date       2014-Apr-17
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief PER MODE: Function which implements PER command
 *
 * @section Description
 * This file contains the PER  function.
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
 * @fn          int16 rsi_per_mode(rsi_uPerMode *uPerModeFrame)
 * @brief       Sends the Per Mode command to the Wi-Fi module via SPI
 * @param[in]   rsi_uPerMode *uPerModeFrame, Pointer to Per Mode structure
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
 * This API is used to give the PER MODE parameter set Request . 
 * @section prerequisite 
 * The rsi_init  should be done sussessfully.
 */
 
int16 rsi_per_mode(rsi_uPerMode *uPerModeFrame)
{
    int16  retval;

 #ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n PER MODE Start");
 #endif

  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdPerMode,(uint8 *)uPerModeFrame,sizeof(rsi_uPerMode));
  
  return retval;
}
