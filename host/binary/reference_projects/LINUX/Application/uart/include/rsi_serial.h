/**
 * @file     rsi_serial.h
 * @version  1.0
 * @date     2014-Sep-6
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief HEADER  
 *
 * @section Description
 * 
 *
 */


#ifndef __RSI_SERIAL_H_
#define __RSI_SERIAL_H_

#include "rsi_defines.h"

#define RSI_UART_DEVICE             "/dev/ttyUSB0"

int16 rsi_serial_frame_write(uint8 *packet_buffer, int16 length);
int16 rsi_serial_init(int port);
void * RecvSerialThreadBody(void * arg );

#endif //__RSI_SERIAL_H_
