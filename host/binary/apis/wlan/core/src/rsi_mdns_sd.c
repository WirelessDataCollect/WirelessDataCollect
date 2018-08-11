/**
 * @file       rsi_mdns_sd.c
 * @version    1.0
 * @date       2015-May-18
 *
 * Copyright(C) Redpine Signals 2015
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief MDNS_SD: Function which frames commands to MDNS
 *
 * @section Description
 * This file contains the MDNS commands formation.
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
 * @fn          int16 rsi_mdns_req(uint8 type, rsi_mdns_t *mdns, uint16 buf_len)
 * @brief       Sends the MDNS commands to the Wi-Fi module
 * @param[in]   uint8 type, type of command in MDNS
 * @param[in]   rsi_mdns_t *mdns, Pointer to MDNS structure
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
 * This API is used to send MDNS related commands to the Wi-Fi module.
 * This API should be called only after rsi_ip_param_set API.
 *
 * @section prerequisite 
 * The IP configuration should be done sussessfully.
 */

#define MDNSD_BUFFER_SIZE 1000

int16 rsi_mdns_req(uint8 type, rsi_mdns_t *mdns)
{
  int16          retval;
  uint8          rsi_frameCmdMDNS[RSI_BYTES_3] = {0x00, 0x40, 0xDB};
  uint8 		 i=0, no_of_txt_fields;
  uint16         pkt_len = 0, str_len = 0, buf_len=0;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n MDNS Command ");
#endif
 
  //! Fill command type
  mdns->command_type = type;

  if(mdns->command_type == MDNS_INIT)
  {
    buf_len = strlen((const char *)mdns->buffer) + 1;
    pkt_len = sizeof(rsi_mdns_t) - MDNSD_BUFFER_SIZE + buf_len;
  }
 
  if(mdns->command_type == MDNS_REGISTER_SERVICE)
  {
	  no_of_txt_fields = 3;

	  while( i < no_of_txt_fields)
	  {
		  str_len = strlen((const char *)&mdns->buffer[buf_len]);
		  buf_len += (str_len + 1);
		  i++;
	  }
	 pkt_len = (sizeof(rsi_mdns_t) - MDNSD_BUFFER_SIZE) + buf_len;
  }

  if(mdns->command_type == MDNS_DEINT)
  {
    pkt_len = sizeof(rsi_mdns_t) - MDNSD_BUFFER_SIZE;
  }

  rsi_uint16_to_2bytes(rsi_frameCmdMDNS, ((pkt_len & 0x0FFF) | 0x4000));    

  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdMDNS, (uint8 *)mdns, pkt_len);
  return retval;
}
