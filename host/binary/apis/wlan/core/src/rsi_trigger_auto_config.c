/**
 * @file     rsi_trigger_auto_config.c
 * @version  2.7
 * @date     2015-Mar-4
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief Trigger Auto config: To Trigger the auto configuration. 
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
 * @fn          int16 rsi_trigger_auto_config(void)
 * @brief       Sends the Trigger auto config command to the Wi-Fi module
 * @param[in]   none
 * @param[out]  none
 * @return      errCode
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to trigger the auto configuration. 
 * This API has to be called only after the Card Ready response.
 */


int16 rsi_trigger_auto_config()
{
  int16               retval;

  /*Trigger auto config Request Frame */
  uint8   rsi_frameCmdTriggerAutoConfigReq[RSI_BYTES_3] = {0x00, 0x40, 0x91};
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdTriggerAutoConfigReq,NULL, 0);
  return retval;	
}


