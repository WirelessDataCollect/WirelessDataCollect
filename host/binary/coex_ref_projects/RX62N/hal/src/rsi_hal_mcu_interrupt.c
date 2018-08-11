/**
 * @file     rsi_hal_mcu_interrupt.c
 * @version  2.7
 * @date     2012-Sep-26
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @section Description
 * This file contains the list of functions for configuring the microcontroller interrupts. 
 * Following are list of API's which need to be defined in this file.
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"


/*===================================================*/
/**
 * @fn      void rsi_irq_start(void)
 * @brief    Starts and enables the SPI interrupt
 * @param[in]  none
 * @param[out]  none
 * @return    none
 * @description This HAL API should contain the code to initialize the register related to interrupts.
 */
void rsi_irq_start(void)
{

   ICU.IER[9].BIT.IEN5 = 1;
}


/*===================================================*/
/**
 * @fn      void rsi_irq_disable(void)
 * @brief    Disables the SPI Interrupt
 * @param[in]  none
 * @param[out]  none
 * @return    none
 * @description This HAL API should contain the code to disable interrupts.
 */
void rsi_irq_disable(void)
{
  ICU.IER[9].BIT.IEN5 = 0;
}


/*===================================================*/
/**
 * @fn      void rsi_irq_enale(void)
 * n
 * @brief    Enables the SPI interrupt
 * @param[in]   none  
 * @param[out]  none
 * @return    none
 * @description This HAL API should contain the code to enable interrupts.
 */
void rsi_irq_enable(void)
{
  ICU.IER[9].BIT.IEN5 = 1;
}

/*====================================================*/
/**
 * @fn		void rsi_wakeup_pin_init(void)
 * @brief	Configuring wakeup pin as output. 
 * @param[in] none
 * @return	none
 * @description This HAL API is used to configure wakeup pin as output.
 */
void rsi_wakeup_pin_init(void)
{
	/* Configure Wakeup pin as output */

	/* PE4 used as wake up source */

	/* Configure PE4 as output */
	PORTE.DDR.BIT.B4 = 1 ;

	/* set to 0 */
	PORTE.DR.BIT.B4 = 0 ;
	/* PE5 is used to detect the device active status*/
	/* Configure PE5 as input */
	PORTE.DDR.BIT.B5 = 0 ;
}


/*===================================================*/
/**
 * @fn      void rsi_irq_clear_pending(void)
 * @brief    Clears the pending SPI interrupt
 * @param[in]  none
 * @param[out]  none
 * @return    none
 * @description This HAL API should contain the code to clear the handled interrupts.
 */
void rsi_irq_clear_pending(void)
{
  
}

/*===================================================*/
/**
 * @fn          void rsi_irq_status(void)
 * n
 * @brief        Checks the SPI interrupt
 * @param[in]   none  
 * @param[out]  uint8, interrupt status
 * @return      none
 * @description This API is used to check pending interrupts.
 */
uint8 rsi_irq_status(void)
{
  //Return interrupt status
  return ICU.IR[77].BIT.IR;
}

/*===================================================*/
/**
 * @fn			    void rsi_assert_status(void)
 * n
 * @brief		    Checks the SPI interrupt
 * @param[in]   none	
 * @param[out]	uint8, assert status
 * @return		  none
 * @description This API is used to check pending interrupts.
 */
uint8 rsi_assert_status(void)
{
  //Return assert status
  return PORTE.DR.BIT.B4;
}


/*====================================================*/
/**
 * @fn		void rsi_assert_wakeup_source(void)
 * @brief	Configuring wakeup pin as output. 
 * @param[in] none
 * @return	none
 * @description This HAL API is used to configure wakeup pin as output.
 */
void rsi_assert_wakeup_source()
{
  PORTE.DR.BIT.B4 = 1;
}


/*====================================================*/
/**
 * @fn		void rsi_deassert_wakeup_source(void)
 * @brief	Configuring wakeup pin as output. 
 * @param[in] none
 * @return	none
 * @description This HAL API is used to configure wakeup pin as output.
 */
void rsi_deassert_wakeup_source()
{
  PORTE.DR.BIT.B4 = 0;
}
