/**
 * @file     rsi_set_ap_config.c
 * @version  2.9
 * @date     2012-Nov-21
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief AP CONFIGURATION: Function which implements the apconf command
 *
 * @section Description
 * This file contains the rsi_apconfiguration function.
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
 * @fn          int16 rsi_set_ap_config(rsi_apconfig *apconf)
 * @param[in]   rsi_apconfig *apconf, Pointer to apconfig structure
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
 * This API is used to set AP configuration parameters to the Wi-Fi module.
 *
 * @section prerequisite 
 * The rsi_init should be done sussessfully.
 */
int16 rsi_set_ap_config(rsi_apconfig *apconf)
 {
    int16 retval;
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nAP configuration");
#endif
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdAPconf, (uint8 *)apconf, sizeof(rsi_apconfig));
  return retval;   
 }
