/**
 * @file       rsi_snmp_get_next_rsp.c
 * @version    1.0
 * @date       2014-Mar-03
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief SNMP GET NEXT RSP: sends response for SNMP get next request
 *
 * @section Description
 * This file contains the Snmp get next response function.
 *
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"


/*==============================================*/
/**
 * @fn          int16 rsi_snmp_get_next_rsp(rsi_uSnmp  *uSnmpGetNextRsp)
 * @brief       Sends the SNMP get next response command to the Wi-Fi module
 * @param[in]   rsi_uSnmp *uSnmpGetNextRsp
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
 * This API is used to send SNMP get next response.
 * This API has to be called only after the rsi_snmp_enable API.
 */
int16 rsi_snmp_get_next_rsp(rsi_uSnmp  *uSnmpGetNextRsp)
{
  int16    retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nSNMP get next response Start");
#endif
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdSnmpGetNextRsp,(uint8 *)uSnmpGetNextRsp, sizeof(rsi_uSnmp));
  return retval;
}


