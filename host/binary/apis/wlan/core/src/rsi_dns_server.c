/**
 * @file     rsi_dns_server.c
 * @version  2.7
 * @date     2012-Sep-26
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief DNS SERVER: Function to set the DNS SERVER IP Addresses
 *
 * @section Description
 * This file contains the DNS SERVER function.
 */

/**
 * Includes
 */
#include "rsi_global.h"

/*=================================================*/
/**
 *@fn           int16 rsi_dns_server(rsi_uDnsServer *uDnsServer)
 * @brief       Sends the DNS Server command to the Wi-Fi module via SPI
 * @param[in]   rsi_uDnsServer *uDnsServer ,pointer to DNS server configuration stucture.
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
 * This API is used to set the DNS Server primary and secondary IPs.
 * @section prerequisite 
 * The rsi_ipparam_set  should be done sussessfully.
 */

int16 rsi_dns_server(rsi_uDnsServer *uDnsServer)
{
    int16    retval;
      
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL3,"\r\n\nDns Server");
#endif
       
    retval = rsi_execute_cmd((uint8 *)rsi_frameCmdDnsServer,(uint8 *)uDnsServer,sizeof(rsi_uDnsServer));  
  
    return retval;
}




