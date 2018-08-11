/**
 * @file       rsi_per_stats.c
 * @version    1.0
 * @date       2014-Sep-02
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief PER STATS: Function which sends the PER statistics command
 *
 * @section Description
 * This file contains the PER stats function.
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
 * @fn          int16 rsi_per_stats(rsi_uPerStats *uPerStatsFrame)
 * @brief       Sends the Per Stats command to the Wi-Fi module
 * @param[in]   rsi_uPerStats *uPerStatsFrame, Pointer to Per Stats structure
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
 * This API is used to give the PER STATS parameter set Request . 
 * @section prerequisite 
 * The rsi_init  should be done sussessfully.
 */
 
int16 rsi_per_stats(rsi_uPerStats *uPerStatsFrame)
{
  int16  retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n PER STATS Start");
#endif

  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdPerStats,(uint8 *)uPerStatsFrame,sizeof(rsi_uPerStats));

  return retval;
}
