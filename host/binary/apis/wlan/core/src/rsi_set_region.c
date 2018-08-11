/**
 * @file       rsi_set_region.c
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
 * @brief SET REGION: Function to set the Region Code.
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
 *@fn           int16 rsi_set_region(rsi_uSetRegion *uSetRegionReqFrame)
 * @brief       Sends the SET Region Code command to the Wi-Fi module via SPI
 * @param[in]   rsi_uSetRegionReq *uSetRegionReqFrame,Pointer to Set Region structure
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
 * This API is used to select the region code.
 * This API is called only if opermode is 0 or 2 and is given only after init command
 */
#if SET_REGION_SUPPORT
int16 rsi_set_region(rsi_usetregion *uSetRegionReqFrame)
{
  int16 retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n Set region");
#endif

  retval =rsi_execute_cmd((uint8 *)rsi_frameSetRegion,(uint8 *)uSetRegionReqFrame, sizeof(rsi_usetregion));
  return retval;

  }
#endif
