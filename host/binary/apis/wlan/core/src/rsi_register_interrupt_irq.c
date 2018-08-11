/**
 * @file       rsi_register_interrupt_irq.c
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
 * @brief IRQ: Function to register interrupt irq
 *
 * @section Description
 * This file contains the function used to register the interrupt IRQ
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
 *@fn           int16 rsi_register_interrupt_irq(uint8 mask)
 * @brief       Sends the register interrupt irq to the Wi-Fi module via SPI
 * @param[in]   none
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
 * This API is used to register the interrupt irq.
 */
int16 rsi_register_interrupt_irq(void)
{
  int16     retval;
  /* set unblock interrupt frame */  
  uint8      rsi_frameRegisterInterruptIrq[RSI_BYTES_3] = {0x01,  0x40, 0xEE};


#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nunblocking interrupt");
#endif
  retval = rsi_execute_cmd((uint8 *)rsi_frameRegisterInterruptIrq, NULL, 0);
  return retval;
}

