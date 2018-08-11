/**
 * @file       rsi_hal.h
 * @version    2.2.0.0
 * @date       2011-May-30
 *
 * Copyright(C) Redpine Signals 2011
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 *
 * @section Description
 * This file contains the function definition prototypes for HAL
 *
 *
 */


#ifndef _RSIHAL_H_
#define _RSIHAL_H_


/**
 * INCLUDES
 */
#include "rsi_global.h"

#ifdef SAM9_G20
#define SPI_INTR_GPIO_PIN AT91_PIN_PB8
#endif
#ifdef SAM9_G35
#define SPI_INTR_GPIO_PIN AT91_PIN_PA7
#endif
#ifdef SAM9_G45
#define SPI_INTR_GPIO_PIN AT91_PIN_PD0
#define SPI_WAKEUP_REQ_GPIO  AT91_PIN_PB10
#define SPI_WAKEUP_STAT_GPIO AT91_PIN_PB11

#endif
#ifdef X86
#define SPI_INTR_GPIO_PIN 0
#endif

/**
 * DEFINES
 */
#define RSI_SPI_SEND_BYTE(A)   // to send 1 byte over SPI interface
#define RSI_SPI_SEND_4BYTE(A)  // to send 4 bytes over SPI interface
#define RSI_SPI_READ_BYTE(B)   // to receive 1 byte over SPI interface
#define RSI_SPI_READ_4BYTE(B)  // to receive 4 byte over SPI interface
/**
 * Function Prototypes
 */
void  rsi_irq_start(void);
void  rsi_irq_enable(void);
void  rsi_irq_disable(void);
void  rsi_irq_clear_pending(void);
uint8 rsi_irq_status(void);
void  rsi_module_power(uint8 tf);
int16 rsi_spi_send(uint8 *ptrBuf, uint16 bufLen,uint8 *valBuf,uint8 mode);
int16 rsi_spi_recv(uint8 *ptrBuf, uint16 bufLen,uint8 mode);
void  rsi_delay_ms(uint16 delay);
void  rsi_delay_us(uint16 delay);
#endif
