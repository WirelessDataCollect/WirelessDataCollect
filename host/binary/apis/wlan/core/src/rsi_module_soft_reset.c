/**
 * @file       rsi_module_soft_reset.c
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
 * @brief RESET: Function which resets the WiSeConnect module
 *
 * @section Description
 * This file contains the function to reset the module.
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
 * @fn             int16 rsi_module_soft_reset(void)
 * @brief          Resets the WiSeConnect module
 * @param[in]      none
 * @param[out]     none
 * @return         errCode
 *                 SPI:
 *                  -1 = SPI busy / Timeout
 *                  -2 = SPI Failure
 *                  -3 = BUFFER FULL
 *                  0  = SUCCESS
 *                 UART/USB/USB-CDC:
 *                  -2 = Command issue failed
 *                  0  = SUCCESS
 * @section description   
 * This API Resets the WiSeConnect module. User need to 
 * reissue the commands from start.
 */
int16 rsi_module_soft_reset(void)
{
  int16   retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nRESET Start");
#endif
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdReset,NULL, 0);
  return retval;
}
