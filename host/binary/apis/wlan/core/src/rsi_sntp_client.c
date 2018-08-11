/**
 * @file       rsi_sntp_client.c
 * @version    1.0
 * @date       2015-Jun-11
 *
 * Copyright(C) Redpine Signals 2015
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief SNTPP CLIENT: Function which implements SNTP client
 *
 * @section Description
 * This file contains the SNTP client functionality.
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
 * @fn          int16 rsi_sntp_client(uint8 type, rsi_sntp_client_t *sntp_client)
 * @brief       Sends the SNTP commands to the Wi-Fi module
 * @param[in]   rsi_sntp_client_t *sntp_client, Pointer to SNTP structure
 * @param[in]   uint8 type, type of SNTP command
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
 * This API is used to send SNTP commands to the Wi-Fi module.
 * This API should be called only after rsi_ip_param_set API.
 *
 * @section prerequisite 
 * The IP configuration should be done sussessfully.
 */

int16 rsi_sntp_client(uint8 type, rsi_sntp_client_t *sntp_client)
{
  int16          retval;
  uint8          rsi_frameCmdSNTP[RSI_BYTES_3] = {0x00, 0x40, 0xE4};    

  //! Fill command type
  sntp_client->command_type = type;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n SNTP client");
#endif

  rsi_uint16_to_2bytes(rsi_frameCmdSNTP, ((sizeof(rsi_sntp_client_t) & 0x0FFF) | 0x4000));    
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdSNTP, (uint8 *)sntp_client, sizeof(rsi_sntp_client_t));

  return retval;
}


