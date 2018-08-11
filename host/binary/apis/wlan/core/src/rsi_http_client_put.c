/**
 * @file       rsi_http_client_put.c
 * @version    2.0
 * @date       2016-Sep-23
 *
 * Copyright(C) Redpine Signals 2016
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief HTTP CLIENT: Function which implements HTTP client 
 *
 * @section Description
 * This file contains the HTTP PUT client functionality.
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
 * @fn          int16 rsi_http_client_put(uint8 type, rsi_http_client_put_req_t *http_client_put)
 * @brief       Sends the HTTP PUT commands to the Wi-Fi module
 * @param[in]   rsi_http_client_put_req_t *http_client_put, Pointer to HTTP PUT structure
 * @param[in]   uint8 type, type of HTTP PUT command
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
 * This API is used to send HTTP PUT commands to the Wi-Fi module.
 * This API should be called only after rsi_ip_param_set API.
 *
 * @section prerequisite 
 * The IP configuration should be done sussessfully.
 */

int16 rsi_http_client_put(uint8 type, rsi_http_client_put_req_t *http_client_put)
{

	int16          retval, str_len =0, buf_len = 0;
	uint16         pkt_len = 0;
	uint8          no_of_fields=0, i=0;
	uint8          rsi_frameCmdHTTPPUT[RSI_BYTES_3] = {0x00, 0x40, 0x53};    

	//! Fill command type
    http_client_put->command_type = type;
  
	if((type == HTTP_CLIENT_PUT_DELETE) || (type == HTTP_CLIENT_PUT_CREATE))
	{
		pkt_len = sizeof(rsi_http_client_put_req_t) - RSI_HTTP_CLIENT_PUT_BUFFER_LENGTH;
	}

	if(http_client_put->command_type == HTTP_CLIENT_PUT_START)
	{
		no_of_fields = 6;

		while( i < no_of_fields)
		{		///ÀàÐÍ²»Æ¥Åä
			str_len = strlen((const char *)&http_client_put->http_put_buffer[buf_len]);
			buf_len += (str_len + 1);
			i++;
		}
		
    pkt_len = sizeof(rsi_http_client_put_req_t) - RSI_HTTP_CLIENT_PUT_BUFFER_LENGTH + buf_len;
	}

	if(http_client_put->command_type == HTTP_CLIENT_PUT_PACKET)
  {
    buf_len += rsi_bytes2R_to_uint16(http_client_put->http_client_put_struct.http_client_put_data_req.current_length); 

    pkt_len = sizeof(rsi_http_client_put_req_t) - RSI_HTTP_CLIENT_PUT_BUFFER_LENGTH + buf_len;
  }


  rsi_uint16_to_2bytes(rsi_frameCmdHTTPPUT, ((pkt_len & 0x0FFF) | 0x4000));

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n HTTP client PUT");
#endif

  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdHTTPPUT, (uint8 *)http_client_put, pkt_len);  

  return retval;
}


