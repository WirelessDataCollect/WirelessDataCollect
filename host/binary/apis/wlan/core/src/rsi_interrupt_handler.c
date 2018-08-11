/**
 * @file      rsi_interrupt_handler.c
 * @version   2.0.0.0
 * @date      2011-May-30
 *
 * Copyright(C) Redpine Signals 2011
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief HAL: Contains interrupt handler
 *
 * @section Description
 * This file contain interrupt handler 
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"
#include "rsi_app.h"


/**
 * Global Variables
 */

/*===================================================*/
/**
 * @fn             void rsi_interrupt_handler(void)
 * @brief          Sets the standard interrupt flags based on the interrupt received from the module 
 * @param[in]      none
 * @param[out]     none
 * @return         none
 * @section        description 
 * When the MCU is configured for Interrupt mode. this API should be called in the 
 * Interrupt Service Routine service the interrupt from the Wi-Fi module. The interrupt 
 * signal from the Wi-Fi module is an active-high level-sensitive interrupt. 
 * So, it is recommended that the interrupt be disabled first, then this API be called 
 * and then the interrupt be enabled.In polling mode the application should call this 
 * API explicitly to update the events from the module. This API reads the content 
 * of interrupt status register and updates the events accordingly.
 * 
 * @section prerequisite 
 * MCU interrupt should be enabled, also called from polling mode
 */

void rsi_interrupt_handler(void)
{
 // rsi_app_cb.pkt_pending = RSI_TRUE;
 // rsi_irq_disable();
	//²»ÐèÒª
}

#ifdef RSI_HWTIMER 
/*===================================================*/
/**
 * @fn             void rsi_timer_interrupt_handler(void)
 * @brief          This Function Sets the standard interrupt flags based on the interrupt received from the module 
 * @param[in]      none
 * @param[out]     none
 * @return         none
 * @section        description 
 * When the MCU includes hardware timers, this is the Interrupt handler. this API should be called in the timer interrupt 
 * Interrupt Service Routine service the interrupt from the Wi-Fi module. The interrupt 
 * 
 * @section prerequisite 
 * MCU interrupt should be enabled
 */
extern uint32 rsi_spiTimer1, rsi_spiTimer2, rsi_spiTimer3;

void rsi_timer_interrupt_handler(void)
{
	rsi_spiTimer1++;
	rsi_spiTimer2++;
	rsi_spiTimer3++;
}
#endif

