/**
 * @file       rsi_sleep_timer.c
 * @version    3.4
 * @date       2013-Feb-16
 *
 * Copyright(C) Redpine Signals 2013
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief SLEEP TIMER: Function which sets the SLEEP TIMER value 
 *
 * @section Description
 * This file contains the Sleep timer function.
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
 * @fn          int16 rsi_sleep_timer(rsi_uSleepTimer *uSleepTimer)
 * @brief       Sends the sleep timer command to the Wi-Fi module
 * @param[in]   uSleepTimer, Pointer to rsi_uSleepTimer.
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
 * This API is used to configure sleep timer in seconds.
 * This API has to be called only after the intialisation
 * is done for Wi-Fi module.
 */
int16 rsi_sleep_timer(rsi_uSleepTimer *uSleepTimer)
{
  int16     retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nBand Start");
#endif
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdSleepTimer,(uint8 *)uSleepTimer, sizeof(rsi_uSleepTimer));
  return retval;
}


