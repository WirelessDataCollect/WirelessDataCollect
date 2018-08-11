/**
 * @file       rsi_p2pcmd.c
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
 * @brief , P2P, implements the P2P command
 *
 * @section Description
 * This file contains the rsi_p2pconfig function.
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
 * @fn          int16 rsi_p2p_config(rsi_uConfigP2p *uConfigP2pFrame)
 * @brief       Sends the P2P command to the Wi-Fi module via SPI
 * @param[in]   rsi_uConfigP2p *uConfigP2pFrame, Pointer to configP2p structure
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
 * This API is used to set the WiFi-direct settings to the WiFi Module
 * This API should be called only after rsi_spi_init.
 *
 * @section prerequisite 
 * The rsi_init should be done sussessfully.
 */
int16 rsi_p2p_config(rsi_uConfigP2p *uConfigP2p)
{
  int16          retval;
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n Config p2p Start");
#endif

  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdP2pConfig,(uint8 *)uConfigP2p, 
                                                          sizeof(rsi_uConfigP2p));
  return retval;
}
