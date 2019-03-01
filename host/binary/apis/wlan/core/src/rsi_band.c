/**
 * @file     rsi_band.c
 * @version  2.7
 * @date     2012-Sep-26
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief BAND: Sets the BAND value 
 *
 * @section Description
 * This file contains the Band function.
 *
 *
 */

/**
 * Includes
 */
#include "rsi_global.h"

/*==============================================*/
/**
 * @fn          int16 rsi_band(uint8 band)
 * @brief       Sends the Band command to the Wi-Fi module
 * @param[in]   uint8 band, band value to configure,0 for 2.4GHz and 1 for 5GHz.
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
 * This API is used to select the 2.4 GHz mode or 5GHz mode. 
 * which have an option of operating in either the 2.4GHz or 5GHz modes. 
 * in the 2.4GHz mode. This API has to be called only after the rsi_opermode API.
 */
int16 rsi_band(uint8 band)
{
  int16               retval;
  rsi_uBand           uBandFrame;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL13,"\r\n\nBand Start");
  RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %s %1.1fGHz\n","WLAN","Tx","Set Band Req","Set Band ",(band==0?2.4:5.0));
#endif
  uBandFrame.bandFrameSnd.bandVal = band;
  retval =rsi_execute_cmd((uint8 *)rsi_frameCmdBand,(uint8 *)&uBandFrame, sizeof(rsi_uBand));
  return retval;
}


