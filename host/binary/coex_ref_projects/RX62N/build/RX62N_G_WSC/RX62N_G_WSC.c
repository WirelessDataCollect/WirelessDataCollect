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

#include <stdbool.h>
#include "rsi_config.h"
#include "rsi_app_util.h"
#include "platform_specific.h"
#include "rsi_app.h"
/* Defines debug LCD functions used in this file */
#include "lcd.h"
/* RSPI API library support */
#include "YRDKRX62N_RSPI_API.h"
/* Board specific definitions */
#include "YRDKRX62N.h"
#include "iodefine_RPDL.h"
#include "rsi_scheduler.h"

#include "rsi_global.h"
#include "rsi_config.h"
#include "rsi_app_util.h"
#include "rsi_spi_cmd.h"
#include "rsi_app.h"
#if JSON_LOAD
#include "sensor_data.h"
#endif



/* SCI RPDL function definitions */
#include "RPDL/r_pdl_sci.h"
/* CMT RPDL function definitions */
#include "RPDL/r_pdl_cmt.h"
/* General RPDL function definitions */
#include "RPDL/r_pdl_definitions.h"

/**
 * Include files
 */ 
#include "iodefine.h"
#include "rsi_global.h"


/** Global Variables
 */
extern volatile int rsi_schdulr_init_done;

int16 rsi_hal_mcu_sysinit(void); 
void rsi_wakeup_pin_init(void);

//#if RSI_USE_HOST_WAKEUP_AS_INTERRUPT
#pragma interrupt (Excep_IRQ13(vect=77))
void Excep_IRQ13(void)
{ 
rsi_set_event(RSI_RX_EVENT);
rsi_irq_disable();
}
//#endif

void Init_Async(void)
{
    /* Declare error flag */
    bool err = true;

    /* Display instructions onto the LCD */
    DisplayLCD(LCD_LINE1, "Async   ");
    DisplayLCD(LCD_LINE2, "Serial  ");

    /* Configure the pin selection of SCI channel */
    err &=    R_SCI_Set
              (
              PDL_SCI_PIN_SCI2_B
              );

    /* Configure the RS232 port */
    err &=    R_SCI_Create
              (
              2,
              PDL_SCI_ASYNC |
              PDL_SCI_TX_CONNECTED | PDL_SCI_RX_CONNECTED | PDL_SCI_CLK_INT_IO |
              PDL_SCI_8_BIT_LENGTH | PDL_SCI_PARITY_NONE  | PDL_SCI_STOP_2,
              115200,// Baudrate
              5
              );    //3686400
			  
	while (!err);
}

/*====================================================*/
/**
 * @fn		void rsi_wsc_wakeup_pin_init(void)
 * @brief	Configuring wakeup pin as output. 
 * @param[in] none
 * @return	none
 * @description This HAL API is used to configure wakeup pin as output.
 */
void rsi_wsc_wakeup_pin_init(void)
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

/*===================================================*/
/**
 * @fn		void rsi_wakeup_from_host(void)
 * @brief	raising wakeup interrupt for the module in sleep 
 * @param[in] none
 * @return	none
 * @description This HAL API is used to raise wakeup interrupt.
 */
void rsi_wakeup_from_host(void)
{
	/* raise Wakeup interrupt - raising edge */
	/* PE4 used as wake up source */
#if 1
	/* set to 0 */
	PORTE.DR.BIT.B4 = 0 ;

	/* set to 1 */
	PORTE.DR.BIT.B4 = 1 ;
	/* set to 0 */
	PORTE.DR.BIT.B4 = 0 ;
#endif
}

void delay(void)
{
	unsigned long delay_cnt=0,loop_cnt=0;
	while(delay_cnt<5000000){
		while(loop_cnt<1000000){
		loop_cnt++;
		}
		delay_cnt++;
	}
}


int main(void);

int main(void)
{
  int retval=0;
  /* Initialise the LCD on the RSPI bus */
  YRDKRX62N_RSPI_Init(RSPI_CHANNEL_0);
  InitialiseLCD();

  /* Initialise the SCI unit for asynchronous operation */
  Init_Async();
  delay();

  /*========================================================*/
  /**
   * System Initialization
   *
   * Initialize the platform specific HAL init - here 
   */
  /*========================================================*/
      rsi_hal_mcu_sysinit();
#ifdef UART_INTERFACE  
     rsi_wakeup_pin_init();
#endif	 
#ifndef UART_INTERFACE	 
#if (RSI_POWER_MODE == RSI_POWER_MODE_3)
  rsi_app_cb.ps_ok_to_send = 1;
#endif
#ifndef UART_INTERFACE 
#ifndef LINUX_PLATFORM 
  retval = rsi_sys_init();
  if(retval != 0)
  {
    return -1;
  }
#endif
#endif
#if HOST_INTERACTION_MODE
#if USB_DUAL_ENUMERATION
  if(app_mode == 1)
  {
#endif
    //! wait for board ready
    do
    {
      retval = rsi_waitfor_boardready();

      if((retval < 0) && (retval != -3))
      {
#ifdef RSI_DEBUG_PRINT
        RSI_DPRINT(RSI_PL0,"BOARD READY FAILED !!\n\n");
#endif
        return -1;
      }
    }while(retval == -3);
	
#if FW_UPGRADE
    retval = rsi_upgrade_fw(RSI_UPGRADE_IMAGE_TYPE, (uint8 *)fw_image, sizeof(fw_image));
    if(retval < 0)
    {
#ifdef RSI_DEBUG_PRINT
        RSI_DPRINT(RSI_PL0,"UPGRADATION FAILED !!\n\n");
#endif
        return -1;
    }
    /* Once firmware is upgraded re-initialize module again */
#ifndef LINUX_PLATFORM 
    retval = rsi_sys_init();
    if(retval != 0)
    {
      return -1;
    }
#else
    return 0;
#endif
#endif
    /* Load the firmware */
#if FIPS_MODE_ENABLE
    rsi_select_option(RSI_ENABLE_FIPS_MODE);
#endif
    rsi_select_option(RSI_HOST_BOOTUP_OPTION);
    if(RSI_HOST_BOOTUP_OPTION != RSI_LOAD_IMAGE_TYPE)
    {
#ifndef LINUX_PLATFORM 
      retval = rsi_sys_init();
      if(retval != 0)
      {
        return -1;
      }
#else
      return 0;
#endif
    }
#if USB_DUAL_ENUMERATION
    return 0;
  }
#endif
#endif


  //! Mem set certificate structure
  memset(&rsi_app_cb.set_chunks, 0, sizeof(struct SET_CHUNK_S));
#endif
  //wifi_main();
  
  rsi_main();

}

/* Interrupt handler function */



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


