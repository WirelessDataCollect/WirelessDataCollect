/**
 * @file     rsi_cfg_save.c
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
 * @brief CFG SAVE: Saves the configuration to flash
 *
 * @section Description
 * This file contains the function to save the current configuration.
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
 * @fn             int16 rsi_cfg_save(void)
 * @brief          Config save
 * @param[in]      none
 * @param[out]     none
 * @return         errCode
 *               SPI:
 *                 -1 = SPI busy / Timeout
 *                 -2 = SPI Failure
 *                 -3 = BUFFER FULL
 *                 0  = SUCCESS
 *               UART/USB/USB-CDC:
 *                 -2 = Command issue failed
 *                 0  = SUCCESS
 *
 * @section description   
 * This file contains the function to save the current configuration.
 */
int16 rsi_cfg_save(void)
{
  int16            retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nCFG Save Start");
#endif
  
  retval =rsi_execute_cmd((uint8 *)rsi_frameCmdCfgSave,NULL, 0);
  
  return retval;
}
