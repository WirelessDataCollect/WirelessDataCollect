/**
 * @file       rsi_pop3_client.c
 * @version    1.0
 * @date       2015-Dec-23
 *
 * Copyright(C) Redpine Signals 2015
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief POP3 CLIENT: Function which implements POP3 client
 *
 * @section Description
 * This file contains the POP3 client functionality.
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
 * @fn          int16 rsi_pop3_client(uint8 type, rsi_pop3_client_t *pop3_client)
 * @brief       Sends the POP3 commands to the Wi-Fi module
 * @param[in]   rsi_pop3_client_t *pop3_client, Pointer to POP3 structure
 * @param[in]   uint8 type, type of POP3 command
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
 * This API is used to send POP3 commands to the Wi-Fi module.
 * This API should be called only after rsi_ip_param_set API.
 *
 * @section prerequisite 
 * The IP configuration should be done sussessfully.
 */

int16 rsi_pop3_client(uint8 type, rsi_pop3_client_t *pop3_client)
{
  int16          retval = 0;
  uint8          rsi_frameCmdPOP3[RSI_BYTES_3] = {0xE2, 0x40, 0xE7};    

  //! Fill command type
  pop3_client->command_type = type;


#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n POP3 client");
#endif

  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdPOP3, (uint8 *)pop3_client, sizeof(rsi_pop3_client_t));

  return retval;
}


