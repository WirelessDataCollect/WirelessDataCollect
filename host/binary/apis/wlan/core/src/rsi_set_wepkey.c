/**
 * @file       rsi_set_wepkey.c
 * @version    2.9
 * @date       2012-Nov-21
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief WEPKEY: Function which implements the wepkey command
 *
 * @section Description
 * This file contains the rsi_set_wepkey function.
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
 * @fn          int16 rsi_set_wepkey(rsi_wepkey *wepkey)
 * @brief       SPI, SET WEP KEY Command
 * @param[in]   rsi_wepkey *wepkey - Pointer to the WEP key structure
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
 * This API is used to set the WEP keys for connection to a WEP Secured AP.
 */
int16 rsi_set_wepkey(rsi_wepkey *wepkey)
 {
    int16 retval;
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nSet Wepkey");
#endif
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdWepkey,(uint8 *)wepkey, sizeof(rsi_wepkey));
  return retval;
 }
