/**
 * @file     rsi_disconnect.c
 * @version  2.9
 * @date     2012-Nov-23
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief DISCONNECT: Function to disconnect
 *
 * @section Description
 * This file contains the DISCONNECT function.
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


/*===================================================*/
/**
 * @fn         int16 rsi_disconnect(rsi_disassoc_t *disassoc_Frame)
 * @brief      Sends the DISCONNECT command to the Wi-Fi module
 * @param[in]  rsi_disassoc_t *disassoc_Frame, Pointer to disassoc frame structure  
 * @param[out] none  
 * @return     errCode
 *              SPI:
 *              -1 = SPI busy / Timeout
 *              -2 = SPI Failure
 *              -3 = BUFFER FULL
 *              0  = SUCCESS
 *              UART/USB/USB-CDC:
 *              -2 = Command issue failed
 *              0  = SUCCESS
 *
 * @section description 
 * This function is used to disconnect the module's Wi-Fi connection.
 * @section prerequisite 
 * Wi-Fi connection should be successful
 */

int16 rsi_disconnect(rsi_disassoc_t *disassoc_Frame)
{
  int16            retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nDisconnect Start");
#endif

  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdDisconnect,(uint8 *)disassoc_Frame,sizeof(rsi_disassoc_t));
  return retval;
}


