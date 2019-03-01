/*HEADER**********************************************************************
Copyright (c)
All rights reserved
This software embodies materials and concepts that are confidential to Redpine
Signals and is made available solely pursuant to the terms of a written license
agreement with Redpine Signals

Project name : WiSeConnect
Module name  : Linux SPI driver
File Name    : rsi_spi.h

File Description:
      SPI specific header file

List of functions:

Author :

Rev History:
Ver   By               date        Description
---------------------------------------------------------
1.1   Anji &           1 Aug06     Initial version
      Ravi Vaishnav
---------------------------------------------------------
*END**************************************************************************/

#ifndef __RSI_SPI_H_
#define __RSI_SPI_H_

#include "rsi_common.h"
#include "rsi_nic.h"
#include <linux/spi/spi.h>




RSI_STATUS rsi_probe(struct spi_device *spi_device);
VOID  rsi_interrupt_handler(struct work_struct *work);

RSI_STATUS rsi_init_interface(PVOID pContext);
VOID  rsi_deinit_interface(PVOID pContext);

#endif // __RSI_SPI_H_
