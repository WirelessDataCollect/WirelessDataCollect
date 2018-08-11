/**
 * @file       rsi_http_post.c
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
 * @brief HTTP POST: Function which implements the HTTP POST command
 *
 * @section Description
 * This file contains the HTTP post function.
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
 * @fn          int16 rsi_http_post(rsi_uHttpReq *uHttpPostReqFrame)
 * @brief       Sends the Http Post command to the Wi-Fi module 
 * @param[in]   rsi_uHttpReq *uHttpPostReqFrame, Pointer to HTTP POST structure
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
 * This API is used to Post the HTTP data from module to HTTP server. 
 * @section prerequisite 
 * The rsi_ipparam_set  should be done sussessfully.
 */

int16 rsi_http_post(rsi_uHttpReq *uHttpPostReqFrame)
{
  int16  retval;
  uint16 buf_len = 0;
  uint16 count = 0,ii=0;
  /*Http Post Request Frame */
  uint8   rsi_frameCmdHttpPostReq[RSI_BYTES_3] = {0x00, 0x40, 0x52};

  buf_len = sizeof(rsi_uHttpReq) - HTTP_BUFFER_LEN;

  if(rsi_bytes2R_to_uint16(uHttpPostReqFrame->HttpReqFrameSnd.https_enable) & 2)
  {
    while(count != 7)
    {
      if(uHttpPostReqFrame->HttpReqFrameSnd.buffer[ii++] == '\0')
      {
        count++;
        
      }
      buf_len++;
    }
    buf_len--; // Not considering NULL at the end of the buffer
  }
  else
  {
    buf_len += strlen((char *)uHttpPostReqFrame->HttpReqFrameSnd.buffer);

  }

  rsi_uint16_to_2bytes(rsi_frameCmdHttpPostReq, (buf_len & 0xFFF));

  rsi_frameCmdHttpPostReq[1] |= 0x40;


#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n Http Post Start");
#endif
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdHttpPostReq,(uint8 *)uHttpPostReqFrame, buf_len);
  return retval;
}
