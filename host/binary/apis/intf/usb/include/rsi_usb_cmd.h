/**
 * @file     rsi_usb_cmd.h
 * @version  3.6
 * @date     2015-Mar-24
 *
 * Copyright(C) Redpine Signals 2013
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief USB HEADER: USB specific function declarations
 *
 * @section Description
 * This file contains the function prototypes of the api's defined in usb library. 
 *
 */



/**
 * Include Files
 */
#include "rsi_global.h"

/**
 * Global Defines
 */

/*=========================================================*/
int16 rsi_mem_wr(uint32 addr, uint16 len, uint8 *dBuf);
int16 rsi_mem_rd(uint32 addr, uint16 len, uint8 *dBuf);
int16 rsi_pkt_rd(uint8 *pkt, uint16 dummy_len, uint16 total_len);

