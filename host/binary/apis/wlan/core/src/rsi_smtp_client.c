/**
 * @file       rsi_smtp_client.c
 * @version    1.0
 * @date       2015-Sep-23
 *
 * Copyright(C) Redpine Signals 2015
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief SMTP CLIENT: Function which implements SMTP client
 *
 * @section Description
 * This file contains the SMTP client functionality.
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
 * @fn          int16 rsi_smtp_client(uint8 type, rsi_smtp_client_t *smtp_client)
 * @brief       Sends the SMTP commands to the Wi-Fi module
 * @param[in]   rsi_smtp_client_t *smtp_client, Pointer to SMTP structure
 * @param[in]   uint8 type, type of SMTP command
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
 * This API is used to send SMTP commands to the Wi-Fi module.
 * This API should be called only after rsi_ip_param_set API.
 *
 * @section prerequisite 
 * The IP configuration should be done sussessfully.
 */

int16 rsi_smtp_client(uint8 type, rsi_smtp_client_t *smtp_client)
{
  int16          retval, str_len =0, buf_len = 0;
  uint16         pkt_len = 0;
  uint8          no_of_fields=0, i=0;
  uint8          rsi_frameCmdSMTP[RSI_BYTES_3] = {0x00, 0x40, 0xE6};    

  //! Fill command type
  smtp_client->command_type = type;

  if((type == SMTP_CLIENT_CREATE) || (type == SMTP_CLIENT_DEINIT))
  {
    pkt_len = sizeof(rsi_smtp_client_t) - RSI_SMTP_BUFFER_LENGTH;
  }

  if(smtp_client->command_type == SMTP_CLIENT_INIT)
  {
    no_of_fields = 4;

    while( i < no_of_fields)
    {
      str_len = strlen((const char *)&smtp_client->smtp_buffer[buf_len]);
      buf_len += (str_len + 1);
      i++;
    }
    pkt_len = sizeof(rsi_smtp_client_t) - RSI_SMTP_BUFFER_LENGTH + buf_len;
  }

  if(smtp_client->command_type == SMTP_CLIENT_MAIL_SEND)
  {
    no_of_fields = 2;


    while( i < no_of_fields)
    {
      str_len = strlen((const char *)&smtp_client->smtp_buffer[buf_len]);
      buf_len += (str_len + 1);
      i++;
    }

    buf_len += rsi_bytes2R_to_uint16(smtp_client->smtp_struct.smtp_mail_send.smtp_client_mail_body_length); 

    if(smtp_client->smtp_struct.smtp_mail_send.smtp_feature & RSI_FEAT_SMTP_EXTENDED_HEADER)
    {
      str_len = strlen((const char *)&smtp_client->smtp_buffer[buf_len]);
      buf_len += (str_len + 1);
    }
    pkt_len = sizeof(rsi_smtp_client_t) - RSI_SMTP_BUFFER_LENGTH + buf_len;
  }


  rsi_uint16_to_2bytes(rsi_frameCmdSMTP, ((pkt_len & 0x0FFF) | 0x4000));

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n SMTP client");
#endif

  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdSMTP, (uint8 *)smtp_client, pkt_len);

  return retval;
}


