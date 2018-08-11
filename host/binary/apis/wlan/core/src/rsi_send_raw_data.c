/**
 * @file       rsi_send_raw_data.c
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
 * @brief SEND RAW DATA: Function to send raw data.
 *
 * @section Description
 * This file contains the SEND Raw data function.
 *
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"


/*
 * Global Variables 
 */


/*=============================================================*/
/**
 * @fn          int16 rsi_send_raw_data(uint8 *payload, uint32 payloadLen,uint32 *bytes_sent)
 * @brief       SEND Packet command
 * @param[in]   uint8 *payload, pointer to the data to payload buffer
 * @param[in]   uint32 payloadLen, length of the payload
 * @param[out]  uint32 bytes_sent, number of bytes sent
 * @return      errCode
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
 * This API used to send raw data over Wi-Fi module. This API is used to send data 
 * packets in TCP/IP bypass mode.If this API return error code like -1, 
 * Application need to retry this function until successfully send the packet 
 * over WiFi module.
 */

int16 rsi_send_raw_data(uint8 *payload, uint32 payloadLen,uint32 *bytes_sent)
{
  int16         retval = 0;
  rsi_uFrameDsc uFrameDscFrame;
  
  if(payloadLen > RSI_RAW_DATA_MAX_SEND_SIZE)
  {
    return -2;
  }
  rsi_uint16_to_2bytes(uFrameDscFrame.frameDscDataSnd.dataFrmLenAndQueue, ((payloadLen & 0x0FFF) | 0x5000));
  

  retval = rsi_execute_cmd((uint8 *)&uFrameDscFrame,(uint8 *)payload, payloadLen);

  if (retval != 0x00) 
  {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL4,"SndFrmDescErr=%02x", (uint16)retval);  
#endif
    return retval;
  }

  *bytes_sent    = payloadLen;
  return retval;
}
