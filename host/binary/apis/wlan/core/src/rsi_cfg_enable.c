/**
 * @file     rsi_cfg_enable.c
 * @version  2.7
 * @date     2012-Sep-12
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief CFG ENABLE: Function to Enable/Disable Store Configuration
 *
 * @section Description
 * This file contains the Store Configuration Enable/Disable function.
 *
 *
 */

/**
 * Includes
 */
#include "rsi_global.h"

/*==============================================*/
/**
 * @fn          int16 rsi_cfg_enable(uint8 cfg_enable_val)
 * @brief       Sends the cfg enable command to the Wi-Fi module
 * @param[in]   uint8 cfg_enable_val,if 1-enables store configuration,
 *              and if 0 disables store configuration
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
  * To enable(1)/disable(0) store configuration.
 */
int16 rsi_cfg_enable(uint8 cfg_enable_val)
{
  int16               retval;
  rsi_uCfgEnable       uCfgEnableFrame;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nCfg enable Start");
#endif

  uCfgEnableFrame.cfgEnableFrameSnd.cfg_enable = cfg_enable_val;
  retval =rsi_execute_cmd((uint8 *)rsi_frameCmdCfgEnable ,(uint8 *)&uCfgEnableFrame, sizeof(rsi_uCfgEnable));
  return retval;
}


