/**
 * @file       rsi_set_region_ap.c
 * @version    2.7
 * @date       2014-Jul-1
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief SET REGION: Function to set the Region Code in AP mode.
 *
 * @section Description
 * This file contains the set region function.
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
 *@fn           int16 rsi_set_region_ap(rsi_usetregion_ap_t *uSetRegionApReqFrame)
 * @brief       Sends the SET Region Code command to the Wi-Fi module via SPI
 * @param[in]   rsi_usetregion_ap_t *uSetRegionApReqFrame,Pointer to Set Region structure
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
 * This API is used to set region of AP and is given immediately after init command
 * This command is valid only if opermode is given as 6.
 */

#if SET_REGION_AP_SUPPORT
int16 rsi_set_region_ap(rsi_usetregion_ap_t *uSetRegionApReqFrame)
{
  int16         retval;
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n Set region AP");
#endif

  retval = rsi_execute_cmd((uint8 *)rsi_frameSetRegionAp,(uint8 *)uSetRegionApReqFrame, sizeof(rsi_usetregion_ap_t));
  return retval;

}
#endif
