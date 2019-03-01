/**
 * @file     rsi_dns_update.c
 * @version  2.7
 * @date     2016-Aug-30
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief DNS Update: Function which updates the hostname (TYPE_A record)in the DNS server.
 *
 * @section Description
 * This file contains the DNS Update function.
 *
 *
 */



/**
 * Includes
 */
#include "rsi_global.h"

/*=================================================*/
/**
 *@fn           int16 rsi_dns_update(rsi_uDnsUpdate  *uDnsUpdateFrame)
 * @brief       Sends the DNS Update command to the Wi-Fi module
 * @param[in]   rsi_uDnsUpdate  *uDnsUpdateFrame,pointer to DNS client update configuration stucture.
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
 * This API is used to update the hostname(TYPE_A record) of the module.
 * @section prerequisite 
 * The rsi_ipparam_set  should be done sussessfully.
 */

int16 rsi_dns_update(rsi_uDnsUpdate  *uDnsUpdateFrame)
{
   int16 retval;
   
   /* DNS update  */
   uint8   rsi_frameCmdDnsUpdate[RSI_BYTES_3] = {0x43 , 0x40 , 0xED };
      
#ifdef RSI_DEBUG_PRINT
   RSI_DPRINT(RSI_PL3,"\r\n\nDns Update");
#endif
       
   retval = rsi_execute_cmd((uint8 *)rsi_frameCmdDnsUpdate,(uint8 *)uDnsUpdateFrame,sizeof(rsi_uDnsUpdate));  
   
   return retval;
}



