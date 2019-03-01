/**
 * @file     main.c
 * Copyright(C) 2013 Redpine Signals Inc.
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief MAIN, Top level file, it all starts here
 *
 * @section Description
 * This file contains the entry point for the application. It also has the 
 * initialization of parameters of the global structure and the operations to 
 * control & configure the module, like scanning networks, joining to an Access Point etc.
 */  


/**
 * Include files
 */ 
#include "iodefine.h"
#include "rsi_global.h"


/** Global Variables
 */
int16 rsi_hal_mcu_sysinit(void); 
void rsi_wakeup_pin_init(void);


int main(void);

int main(void)
{
  
  /*========================================================*/
  /**
   * System Initialization
   *
   * Initialize the platform specific HAL init - here 
   */
  /*========================================================*/
  rsi_hal_mcu_sysinit();
  
  rsi_wakeup_pin_init();
#if (RSI_POWER_MODE == RSI_POWER_MODE_3)
  rsi_app_cb.ps_ok_to_send = 1;
#endif

  wifi_main();

}

/* Interrupt handler function */
#pragma interrupt (Excep_IRQ13(vect=77))
void Excep_IRQ13(void)
{ 
	rsi_interrupt_handler();
}



/*===========================================================*/
/**
 * @fn			int hal_mcu_sysinit(void)
 * @brief		HAL, RX62N, Initializes the RX62N specific hardware
 * @param[in]	none
 * @param[out]	none
 * @return		errCode
 *				-1 = Error
 *				0  = OK
 */
int16 rsi_hal_mcu_sysinit(void)
{

  MSTP(RSPI0) = 0 ;  
  SYSTEM.SCKCR.BIT.ICK=0; //x8
  SYSTEM.SCKCR.BIT.PCK=1; //x4
  SYSTEM.SCKCR.BIT.BCK=0; //x2
	
  /* Select proper bank of pins for SPI0 */
  /* SCK (PC.1) is active */
  IOPORT.PFGSPI.BIT.RSPIS = 0 ;
  /* SCK (PC.5) is active */
  IOPORT.PFGSPI.BIT.RSPCKE = 1 ;
  /* SSL3 (PC.2) is inactive (toggled as GPIO instead) */
  IOPORT.PFGSPI.BIT.SSL2E = 0 ;
  /* MOSI (PC.6) is active */
  IOPORT.PFGSPI.BIT.MOSIE = 1 ;
  /* MISO (PC.7) is active */	
  IOPORT.PFGSPI.BIT.MISOE = 1 ;
  
  /* Set up chip select pin */
  PORTC.DDR.BIT.B1 = 1 ;
  /* Set level to active */
  PORTC.DR.BIT.B1 = 1 ;
   
  /* MISO as an input */
  PORTC.DDR.BIT.B7 = 0 ;
  /* Enable input buffer for peripheral */
  PORTC.DR.BIT.B7 = 0 ;
  PORTC.ICR.BIT.B7 = 1;
		
  /* MOSI as an output */
  PORTC.DDR.BIT.B6 = 1 ;
  /* Enable input buffer for peripheral */
  PORTC.DR.BIT.B6 = 1 ;

  /* SCK as an output */
  PORTC.DDR.BIT.B5 = 1 ;
  /* Set level to inactive */
  PORTC.DR.BIT.B5 = 1 ;
    
  /* Initialize SPI (per flowchart in hardware manual) */
  /* No loopback, CMos Output */
  RSPI0.SPPCR.BYTE = 0x00 ;
  /* Full Speed is 0x00  255 works */
  //RSPI0.SPBR.BYTE = 0x00 ; 
  RSPI0.SPBR.BYTE = 0x01; //0x05 - // 2.67 MBPS
  /* 16-bit data 1 frame 1 chip select */
  RSPI0.SPDCR.BYTE = 0x00;   //0x00 ;   /* if 5th bit is 1 long word is used */
										/*  if 5th bit is 0  word is used */
  /* 2 clock delay before next access to SPI device */
  RSPI0.SPCKD.BYTE = 0x00 ;
  /* 2 clock delay after de-asserting SSL */
  RSPI0.SSLND.BYTE = 0x00 ;
  /* 2 clock delay before next access to SPI device */
  RSPI0.SPND.BYTE = 0x00 ;
  /* No parity no idle interrupts */
  RSPI0.SPCR2.BYTE = 0x00 ;
  /* MSB first 8-bit data, keep SSL low */
  RSPI0.SPCMD0.WORD = 0x0700 ;  /* 0000 0111 0000 0000  for 8bit transfer length */ 
								  /* 0000 0011 0000 0000  for 32bit transfer length */ 
         
  /* Enable RSPI 3wire in master mode with RSPI Enable Transmit Receive and Interupt */  
  RSPI0.SPCR.BYTE = 0xE8 ;
  
  /* SSL3A Polarity */
  RSPI0.SSLP.BYTE = 0x04 ;
  /* One frame. */
  RSPI0.SPSCR.BYTE = 0x00 ;	
	
  /* Configure External interrupt */
  IOPORT.PF8IRQ.BIT.ITS13 = 0;
	
  //ICU.IER[9].BIT.IEN5 = 0 ;
	
  /* Interrupt as an input */
  //PORT5.DDR.BIT.B5 = 0 ;
  PORT0.DDR.BIT.B5 = 0 ;
  /* Enable input buffer for interrupt */
  PORT0.DR.BIT.B5 = 1 ;
  PORT0.ICR.BIT.B5 = 1;
  
  ICU.IRQCR[13].BIT.IRQMD = 0x00 ; //0x0 - low level
  ICU.IR[77].BIT.IR = 0 ;

  ICU.IPR[0x2D].BIT.IPR = 0xe; //1111 is highest
  ICU.IER[9].BIT.IEN5 = 0;

  return 0;											

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
	//PORTE.DR.BIT.B5 = 0 ;
}

