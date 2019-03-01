/**
 * @file       rsi_read_data.c
 * @version    1.2
 * @date       2015-Dec-16
 *
 * Copyright(C) Redpine Signals 2013
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief READ: Function to read tcp/udp data 
 *
 * @section Description
 * This file contains the READ function.
 *
 * @Improvements
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"
#include "rsi_app.h"
#include <string.h>

/*
 * Global Variables 
 */


/*=============================================================*/
/**
 * @fn          int16 rsi_read_data(rsi_uSocketRead  *uSocketReadFrame)
 * @brief       READ Data Packet command
 * @param[in]   uint16 socketDescriptor, socket descriptor for the socket to send data to
 * @param[out]  uint32 bytes_sent, number of bytes sent succesfuly
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
 * This API used to read TCP/UDP data using an already opened socket. This function
 * should be called after successfully opening a socket using the rsi_socket API.
 * If this API return error code-1.
 */
#if !RSI_TCP_IP_BYPASS
int16 rsi_read_data(rsi_uSocketRead  *uSocketReadFrame, uint16 socketDescriptor, uint32 dataLength, uint16 time_out)
{
  int16   retval = 0;
  uint8   rsi_frameCmdReadData[RSI_BYTES_3] = {0x07, 0x50, 0x6B};

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nRead Data");
#endif

  uSocketReadFrame->socketReadFrameSnd.socketDescriptor   = socketDescriptor;
  rsi_uint32_to_4bytes(uSocketReadFrame->socketReadFrameSnd.data_length,dataLength);
  rsi_uint16_to_2bytes(uSocketReadFrame->socketReadFrameSnd.timeout_in_ms, time_out);

  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdReadData,(uint8 *)uSocketReadFrame,sizeof(rsi_uSocketRead));  
  return retval;
}
#endif
