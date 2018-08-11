/**
 * @file     rsi_bg_scan.c
 * @version  1.0
 * @date     2014-Jan-07
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief BG SCAN: Back ground Scans for available access points
 *
 * @section Description
 * This file contains the BG Scan function.
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


/*===========================================================================
 *
 * @fn          int16 rsi_bg_scan(rsi_ubgScan *ubgScanFrame)
 * @brief       Sends the BG Scan command to the Wi-Fi module
 * @param[in]   rsi_ubgScan *ubgScanFrame,Pointer to BG scan structure
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
 * This API is used to BG scan for Access Points. This API should be called only 
 * after the rsi_join API.
 *
 * @section prerequisite 
 * rsi_join should be done successfully  
 */

int16 rsi_bg_scan(rsi_ubgScan *ubgScanFrame)
{
  int16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nBG Scan Start ");
#endif

  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdBGScan, (uint8 *)ubgScanFrame, sizeof(rsi_ubgScan));
  return retval;
}
