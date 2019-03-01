/**
 * @file       rsi_snmp_get_stats.c
 * @version    1.0
 * @date       2017-Thu-04
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief SNMP GET STATS: sends intermediate response for SNMP get request
 *
 * @section Description
 * This file contains the Snmp get stats function.
 *
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"


/*==============================================*/
/**
 * @fn          void rsi_snmp_get_rsp(void)
 * @brief       Sends the SNMP statistics as an intermediate response
 * @param[in]   none
 * @param[out]  none
 * @return      none
 * @section description 
 * This API is used to send SNMP statistics as response.
 * This API has to be called only after the rsi_snmp_enable API.
 */
int16 rsi_snmp_get_stats(void)
{
  int16 retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nSNMP get stats Start");
#endif
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdSnmpGetStats, NULL, 0);
  return retval;
}


