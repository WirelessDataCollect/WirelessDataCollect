/**
 * @file     rsi_socket.c
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
 * @brief SOCKET: Function which creates the socket connection 
 *
 * @section Description
 * This file contains the SOCKET function.
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
 * @fn          int16 rsi_socket(rsi_uSocket *uSocketFrame)
 * @brief       Sends the SOCKET open command to the Wi-Fi module
 * @param[in]   rsi_uSocket *uSocketFrame, pointer to socket create structure
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
 * This API is used to open a TCP/UDP Server/Client socket in the Wi-Fi module. 
 * It has to be called only after the module has been assigned an IP address using the 
 * rsi_ipparam_set API.
 * @section prerequisite 
 * WiFi Connection should be established before opening the sockets
 */
int16 rsi_socket(rsi_uSocket *uSocketFrame)
{
  int16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL13,"\r\n\nSocket Open Start");
  RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %s\n","WLAN","Tx","Socket Open Req","Request for opening a socket");
#endif
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdSocket,(uint8 *)uSocketFrame,sizeof(rsi_uSocket));
  return retval;
}

