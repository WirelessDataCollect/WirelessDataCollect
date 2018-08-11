/**
 * @file       rsi_uart_flow_control.c
 * @version    2.7
 * @date       2015-Feb-6
 *
 * Copyright(C) Redpine Signals 2015
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief ENABLE/DISABLE UART HARDWARE FLOW CONTROL:Enable/disable UART hw flow control
 *
 * @section Description
 * This file contains API to enable/disable hardware flow control
 *
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"
#include <stdio.h>
#include <string.h>
 

/**
 * Global Variables
 */


/*===========================================================================*/
/**
 * @fn          int16 rsi_uart_flow_control(uint8 enable)
 * @brief       Enable/disable UART hw flow control 
 * @param[in]   enable = 1/disable =0
 * @param[out]  none
 * @return      errCode
 *                SPI:
 *                  -1 = SPI busy / Timeout
 *                  -2 = SPI Failure
 *                  -3 = BUFFER FULL
 *                  0  = SUCCESS
 *                 UART/USB/USB-CDC:
 *                  -2 = Command issue failed
 *                  0  = SUCCESS
 *      
 * @section description 
 * This API is used to enable/disable hardware flow control 
 * */
int16 rsi_uart_flow_control(uint8 enable)
{

  int16            retval;
  rsi_uHwFlowControl UartHwFlowcontrol;
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nUART flow control Enable");
#endif
  UartHwFlowcontrol.HwFlowControlEnableFrameSnd.uart_hw_flowcontrol_enable = enable;
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdUartFlowControl,(uint8 *)&UartHwFlowcontrol,1);
  return retval;
}




