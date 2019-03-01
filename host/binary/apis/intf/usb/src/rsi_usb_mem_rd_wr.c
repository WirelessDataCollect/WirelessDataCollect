/**
 * @file       rsi_usb_mem_rd_wr.c 
 * @version    2.0.0.0
 * @date       2014-Mar-24
 *
 * Copyright(C) Redpine Signals 2011
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief USB MEMRDWR: USB Memory Read/Write functions, r/w memory on the module via the USB interface
 *
 * @section Description
 * This file contains the USB Memory Read/Write functions to the module
 *
 *
 */



/**
 * Includes
 */
#include "rsi_global.h"
#include "rsi_usb_cmd.h"
#include "rsi_config.h" 

#if (RSI_INTERFACE == RSI_USB)
/**
 * Global Variables
 */


/*===========================================================================*/
/** 
 * @fn          int16 rsi_mem_wr(uint32 addr, uint16 len, uint8 *dBuf)
 * @brief       Performs a memory write to the Wi-Fi module
 * @param[in]   uint32 addr, address to write to
 * @param[in]   uint16, len, number of bytes to write
 * @param[in]   uint8 *dBuf, pointer to the buffer of data to write
 * @param[out]  none
 * @return      errCode
 *              -1 = SPI busy / Timeout
 *              -2 = SPI Failure
 *              0  = SUCCESS
 *
 * ABH Master Write (Internal Legacy Name)
 */
int16 rsi_mem_wr(uint32 addr, uint16 len, uint8 *dBuf)
{
   return 0;
}


/*===========================================================================*/
/**
 * @fn          int16 rsi_mem_rd(uint32 addr, uint16 len, uint8 *dBuf)
 * @brief       Performs a memory read from the Wi-Fi module
 * @param[in]   uint32, address to read from
 * @param[in]   uint16, len, number of bytes to read
 * @param[in]   uint8 *dBuf, pointer to the buffer to receive the data into
 * @param[out]  none
 * @return      errCode
 *              -1 = SPI busy / Timeout
 *              -2 = SPI Failure
 *              0  = SUCCESS
 *
 * ABH Master Read (Internal Legacy Name)
 */
int16 rsi_mem_rd(uint32 addr, uint16 len, uint8 *dBuf)
{
   return 0;
}

#endif
