/**
 * @file       rsi_multicast.c
 * @version    1.0
 * @date       2014-May-12
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief MULTICAST: Function which sends multicast command to module.
 *
 * @section Description
 * This file contains the Multicast function.
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
 * @fn          int16 rsi_multicast(rsi_uMulticast *uMulticastFrame)
 * @brief       Sends the Multicast command to the Wi-Fi module
 * @param[in]   rsi_uMulticast *uMulticastFrame,Pointer to multicast structure
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
 * This API is used to join or leave multicast group. This API should be called only 
 * after the rsi_ipparam_set API.
 *
 * @section prerequisite 
 * rsi_ipparam_set should be done successfully  
 */

#if RSI_MULTICAST_SUPPORT
int16 rsi_multicast(rsi_uMulticast *uMulticastFrame)
{
  int16   retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nMulticast Start ");
#endif

  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdMulticast, (uint8 *)uMulticastFrame, sizeof(rsi_uMulticast));
  return retval;
}
#endif
