/**
 * @file       rsi_snmp_trap.c
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
 * @brief SNMP TRAP: sends SNMP trap
 *
 * @section Description
 * This file contains the Snmp trap function.
 *
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"


/*==============================================*/
/**
 * @fn          int16 rsi_snmp_trap(rsi_uSnmptrap *uSnmpTrapFrame)
 * @brief       Sends the SNMP trap command to the Wi-Fi module
 * @param[in]   rsi_uSnmptrap *uSnmpTrapFrame
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
 * This API is used for SNMP trap command.
 * This API has to be called only after the rsi_snmp_enable API.
 */


int16 rsi_snmp_trap(rsi_uSnmptrap  *uSnmpTrapFrame, int snmp_len)
{
  int16               retval;


  /*SNMP trap Response frame*/
  uint8   rsi_frameCmdSnmpTrap[RSI_BYTES_3] = {0x6E, 0x44, 0x86};
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nSNMP trap Start");
#endif

  rsi_uint16_to_2bytes(rsi_frameCmdSnmpTrap, (snmp_len & 0xFFF));

  rsi_frameCmdSnmpTrap[1] |= 0x40;

  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdSnmpTrap,(uint8 *)uSnmpTrapFrame, snmp_len);
  return retval;
}


