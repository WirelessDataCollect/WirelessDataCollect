/**
 * @file       rsi_ht_caps.c
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
 * @brief HT CAPS: Function which sets the high throughput capabilities parameters 
 *
 * @section Description
 * This file contains the HT CAPS Parameter set function.
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
 * @fn          int16 rsi_ht_caps(rsi_uHtCaps *uHtCapsFrame)
 * @brief       Sets the HT CAPS parameters in the Wi-Fi module 
 * @param[in]   rsi_uHtCaps *uHtCapsFrame, Pointer to HT Caps structure
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
 * This API is used to give the HT CAPS Request . 
 * @section prerequisite 
 * The init should be done sussessfully.
 */
 
int16 rsi_ht_caps(rsi_uHtCaps *uHtCapsFrame)
{
  int16  retval;

 #ifdef RSI_DEBUG_PRINT
   RSI_DPRINT(RSI_PL3,"\r\n\n HT CAPS starts");
 #endif

  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdHtCaps,(uint8 *)uHtCapsFrame,sizeof(rsi_uHtCaps));
  
  return retval;
}
