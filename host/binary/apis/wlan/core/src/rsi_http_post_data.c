/**
 * @file     rsi_http_post_data.c
 * @version  1.0
 * @date     2016-Sep-17
 *
 * Copyright(C) Redpine Signals 2016
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief HTTP client post data to HTTP server
 *
 * @section Description
 * This file contains the functionality of HTTP client post data.
 */

/**
 * Includes
 */
#include "rsi_global.h"


/**
 * Global Variables
 */

/*==============================================*/
/**
 * @fn          int16 rsi_http_post_data(rsi_uHttpPostDataReq *uHttpPostDataReqFrame, uint8 *data, uint16 length, uint32 offset);
 * @brief       send the HTTP post data command to firmare
 * @param[in]   uHttpPostDataReqFrame 
 * @param[in]   data
 * @param[in]   length of the http data
 * @param[in]   offset of the data file from where to fill the payload
 * @return      errCode
 *              0  = SUCCESS
 * @section description 
 * This API is used to send the HTTP post data command to module.
 */
int16 rsi_http_post_data(rsi_uHttpPostDataReq *uHttpPostDataReqFrame, uint8 *data, uint16 length, uint32 offset)
{
  int16               retval;
  uint8   rsi_frameCmdHttpPostData[RSI_BYTES_3] = {0x00, 0x40, 0xEB};
  

  /* Fill HTTP chunk length */
  rsi_uint16_to_2bytes(uHttpPostDataReqFrame->HttpPostDataReqFrameSnd.current_chunk_length, length);

  /* Copy HTTP content */
  memcpy(uHttpPostDataReqFrame->HttpPostDataReqFrameSnd.buffer,((uint8 *)data + offset), length);

  /* Fill length of the command payload */
  length = (sizeof(rsi_uHttpPostDataReq) - HTTP_POST_BUFFER_LEN + length);
  
  *(uint16 *)&rsi_frameCmdHttpPostData[0] = (((length) & 0xFFF) | (0x4 << 12));

  rsi_uint16_to_2bytes(rsi_frameCmdHttpPostData, (length & 0xFFF));

  rsi_frameCmdHttpPostData[1] |= 0x40;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nHTTP POST DATA PACKET LENGTH IS===>>>%d\r\n",length);
#endif
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdHttpPostData, (uint8 *)uHttpPostDataReqFrame, length);
  return retval;
}
