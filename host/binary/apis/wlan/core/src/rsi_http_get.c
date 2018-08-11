/**
 * @file     rsi_http_get.c
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
 * @brief HTTP GET: Function which implements HTTP GET command
 *
 * @section Description
 * This file contains the Join function.
 *
 *
 */

/**
 * Includes
 */
#include "rsi_global.h"
#include <string.h>

/**
 * Global Variables
 */

/*=================================================*/
/**
 * @fn          int16 rsi_http_get(rsi_uHttpReq *uHttpGetReqFrame)
 * @brief       Sends the Http Get command to the Wi-Fi module via SPI
 * @param[in]   rsi_uHttpReq *uHttpGetReqFrame, Pointer to Http Get structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failed
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to give the HTTP GET Request for HTTP server. 
 * @section prerequisite 
 * The rsi_ipparam_set  should be done sussessfully.
 */
 
int16 rsi_http_get(rsi_uHttpReq *uHttpGetReqFrame)
{
  int16  retval;
  uint16 buf_len;
  uint16 ii =0;
  uint8 count =0;

  /*Http GET Request Frame */
  uint8   rsi_frameCmdHttpGetReq[RSI_BYTES_3] = {0x00, 0x40, 0x51};

  buf_len = sizeof(rsi_uHttpReq) - HTTP_BUFFER_LEN;

  if(rsi_bytes2R_to_uint16(uHttpGetReqFrame->HttpReqFrameSnd.https_enable) & 2)
  {
    while(count != 6)
    {
      if(uHttpGetReqFrame->HttpReqFrameSnd.buffer[ii++] == '\0')
      {
        count++;
        
      }
      buf_len++;
    }
    buf_len--; // Not considering NULL at the end of the buffer
  }
  else
  {
    buf_len += strlen((char *)uHttpGetReqFrame->HttpReqFrameSnd.buffer);

  }

  rsi_uint16_to_2bytes(rsi_frameCmdHttpGetReq, (buf_len & 0xFFF));

  rsi_frameCmdHttpGetReq[1] |= 0x40;


#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n HTTP GET Start");
#endif
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdHttpGetReq,(uint8 *)uHttpGetReqFrame, buf_len);
  return retval;
}
