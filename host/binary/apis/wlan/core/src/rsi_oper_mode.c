/**
 * @file       rsi_oper_mode.c
 * @version    2.7
 * @date       2012-Sep-26
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief OPERATING MODE: implements the OPERATING MODE command
 *
 * @section Description
 * This file contains the rsi_opermode function.
 *
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"


/**
 * Global Variables
 */


/*=================================================*/
/**
 *@fn            int16 rsi_oper_mode(rsi_uOperMode *uOperMode)
 * @brief        Sends the OPERATING MODE command to the Wi-Fi module via SPI
 * @param[in]    uint8 mode value to configure 0 for legacy client mode , 
 *               1 for wifi-direct mode , 2 for enterprise security mode.
 * @param[out]   none
 * @return       errCode
 *               SPI:
 *                -1 = SPI busy / Timeout
 *                -2 = SPI Failure
 *                -3 = BUFFER FULL
 *                0  = SUCCESS
 *               UART/USB/USB-CDC:
 *                -2 = Command issue failed
 *                0  = SUCCESS
 * @section description 
 * This API is used to select the Legacy client mode or P2P mode or Enterprise Security Mode.
 */
int16 rsi_oper_mode(rsi_uOperMode *uOperMode)
{
  int16    retval;

#ifdef RSI_DEBUG_PRINT
  uint32 opermode = 0, coex = 0,i;
  UINT8 opermode_str[15],coex_str[20];

  opermode = *(uint16 *)&uOperMode[0];
  coex =     *(uint32 *)&uOperMode[0]>>16;

	if(opermode == 0)
		memcpy(opermode_str,"WLAN Client",13);
	else if(opermode == 1)
		memcpy(opermode_str,"WLAN P2P",14);
	else if(opermode == 2)
		memcpy(opermode_str,"WLAN EAP Sec",14);
	else if(opermode == 6)
		memcpy(opermode_str,"WLAN AP",14);
	else if(opermode == 8)
		memcpy(opermode_str,"PER",14);

	if(coex == 0)
		memcpy(coex_str,"Only",13);
	else if(coex== 3)
		memcpy(coex_str,"+ ZigBee Coex ",20);
	else if(coex== 5)
		memcpy(coex_str,"+ BT Coex ",20);
	else if(coex== 13)
		memcpy(coex_str,"+ BTLE Coex ",20);		

	RSI_DPRINT(RSI_PL3,"\n%-10.7s%-4.2s %-20.15s %s %s  %s\n","WLAN","Tx","Operating Mode Req","Mode:",opermode_str,coex_str);
	RSI_DPRINT(RSI_PL13,"\r\n\nOperating Mode");
#endif
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdOperMode,(uint8 *)uOperMode, sizeof(rsi_uOperMode));
  return retval;
}

