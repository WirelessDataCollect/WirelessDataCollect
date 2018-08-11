/**
 * @file       rsi_set_eap.c
 * @version    2.7
 * @date       2012-Sep-26
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief EAP: Function which implements the version of the EAP command
 *
 * @section Description
 * This file contains the EAP function.
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
 * @fn          int16 rsi_set_eap(rsi_uSetEap *uSetEapFrame)
 * @param[in]   rsi_uSetEap *uSetEapFrame, Pointer to EAP structure
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
 * This API is used to set EAP parameters to the Wi-Fi module.
 *
 * @section prerequisite 
 * The rsi_init should be done sussessfully.
 */

int16 rsi_set_eap(rsi_uSetEap *uSetEap)
{
  int16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL13,"\r\n\n Set Eap Start");
  RSI_DPRINT(RSI_PL3,"%-10.7s%-7.5s %-15.15s %-30.25s\n","WLAN","Tx","Set EAP","Loading EAP parametrs");
#endif

  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdSetEap,(uint8 *)uSetEap, sizeof(rsi_uSetEap));
  return retval;
}

