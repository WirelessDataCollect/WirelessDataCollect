/**
 * @file       rsi_snmp_enable.c
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
 * @brief SNMP ENABLE: Enables SNMP 
 *
 * @section Description
 * This file contains the Snmp enable function.
 *
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"


/*==============================================*/
/**
 * @fn          int16 rsi_snmp_enable(uint8 snmpEnable)
 * @brief       Sends the SNMP enable command to the Wi-Fi module
 * @param[in]   uint8 snmpEnable,value to enable snmp
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
 * This API is used to enable SNMP.
 * This API has to be called only after the rsi_ipparm_set or rsi_ipconf6 API.
 */
int16 rsi_snmp_enable(uint8 snmpEnable)
{
  int16    retval;
  rsi_uSnmpEnable  usnmpEnableFrame;
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nSNMP enable Start");
#endif
  usnmpEnableFrame.snmpEnableFrameSnd.snmpEnable = snmpEnable;
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdSnmpEnable,(uint8 *)&usnmpEnableFrame, sizeof(rsi_uSnmpEnable));
  return retval;
}


