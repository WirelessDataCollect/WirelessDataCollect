/**
 * @file     rsi_dns_query.c
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
 * @brief DNS Query: Function which gets the DNS IP address.
 *
 * @section Description
 * This file contains the DNS Query function.
 *
 *
 */



/**
 * Includes
 */
#include "rsi_global.h"

/*=================================================*/
/**
 *@fn           int16 rsi_dns_query(rsi_uDnsQry  *uDnsQryFrame)
 * @brief       Sends the DNS Get command to the Wi-Fi module
 * @param[in]   rsi_uDnsQry  *uDnsQryFrame,pointer to DNS server configuration stucture.
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
 * This API is used to resolve the IP Address for the given Domain name.
 * @section prerequisite 
 * The rsi_ipparam_set  should be done sussessfully.
 */

int16 rsi_dns_query(rsi_uDnsQry  *uDnsQryFrame)
{
   int16 retval;
      
#ifdef RSI_DEBUG_PRINT
   RSI_DPRINT(RSI_PL3,"\r\n\nDns Get");
#endif
       
   retval = rsi_execute_cmd((uint8 *)rsi_frameCmdDnsQuery,(uint8 *)uDnsQryFrame,sizeof(rsi_uDnsQry));  
   
   return retval;
}



