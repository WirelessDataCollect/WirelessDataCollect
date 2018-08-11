/**
 * @file       rsi_bt_register_interrupt_irq.c
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
#include "rsi_bt_global.h"
#include "rsi_bt_generic.h"
#include "rsi_bt_api.h"
#include "platform_specific.h"
 

/**
 * Global Variables
 */


/*=================================================*/
/**
 *@fn           INT16 rsi_bt_register_interrupt_irq(UINT08 mask)
 * @brief       Sends the register interrupt irq to the Wi-Fi module via SPI
 * @param[in]   none
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to register the interrupt irq.
 */
INT16 rsi_bt_register_interrupt_irq(void)
{
  INT16     retval;
  /* set unblock interrupt frame */  
  UINT08      rsi_frameRegisterInterruptIrq[RSI_BYTES_4] = {0x01, 0x00, 0xEE, 0x00};


#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nunblocking interrupt");
#endif
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameRegisterInterruptIrq, NULL, 0);
  return retval;
}

