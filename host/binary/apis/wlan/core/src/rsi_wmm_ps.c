/**
 * @file       rsi_wmm_ps.c
 * @version    1.0
 * @date       2014-Apr-16
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief WMM PS : Function which sets the WMM PS parameters 
 *
 * @section Description
 * This file contains the WMM PS Parameter set function.
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
 * @fn          int16 rsi_wmm_ps(rsi_uWmmPs *uWmmPsFrame)
 * @brief       Sets the Wmm Ps parameters in the Wi-Fi module 
 * @param[in]   rsi_uWmmPs *uWmmPsFrame, Pointer to WMM Ps structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failed
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to give the WMM PS Request . 
 * @section prerequisite 
 * The join should be done sussessfully.
 */
 
int16 rsi_wmm_ps(rsi_uWmmPs *uWmmPsFrame)
{
    int16  retval;

 #ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n WMM PS Start");
 #endif

  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdWmmPs,(uint8 *)uWmmPsFrame,sizeof(rsi_uWmmPs));
  
  return retval;
}
