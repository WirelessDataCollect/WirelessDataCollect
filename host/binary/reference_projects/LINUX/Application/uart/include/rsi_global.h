/**
 * @file     rsi_global.h
 * @version  3.6
 * @date     2013-May-16
 *
 * Copyright(C) Redpine Signals 2013
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief HEADER, GLOBAL, Global Header file, the things that must be almost everywhere 
 *
 * @section Description
 * This is the top level global.h file for data/functions that need to be in every module
 * This file contains all the structures and defines used in the entire application 
 *
 * @section Improvements
 * New structures are added. 
 * The definition for MACRO "RSI_TXDATA_OFFSET_LUDP" from 28 to 26.
 * LTCP Conn Establishment Rcv structure is changed. 
 * rsi_uSleepTimer is changed
 *
 */


#ifndef _RSIGLOBAL_H_
#define _RSIGLOBAL_H_


/**
 * Global defines
 */
#define RSI_TRUE            1    
#define RSI_FALSE           0
#ifndef NULL
#define NULL                0
#endif
//#define PACKED            1 


//!Comment This in case the host MCU is of BIG ENDIAN 
#define RSI_LITTLE_ENDIAN                       0


//! Interrupt Mode Selection 
#define RSI_INTERRUPTS

//! Polled Mode selection
//#define RSI_POLLED

/*
 * @ Type Definitions
 */
typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned long       uint32;
typedef char                int8;
typedef short               int16;
typedef long                int32;


#define ENABLE                      1
#define DISABLE                     0


#ifndef RSI_HWTIMER 
//! need to define this macro if h/w timer is available and it should increment spiTimer2, spiTimer1 
#define RSI_TICKS_PER_SECOND        50000 
#else
#define RSI_TICKS_PER_SECOND        10
#endif

/**
 * Debugging Parameters
 */
#define RSI_DEBUG_DEVICE                    "UART_1"
#define RSI_MAX_PAYLOAD_SIZE                 1600  //@ Maximum data payload size
#define RSI_WEBSOCKET_MAX_SEND_SIZE          1450
#define RSI_TCP_MAX_SEND_SIZE                1460
#define RSI_UDP_MAX_SEND_SIZE                1472
/**
 * Things that are needed in this .h file
 */
#define RSI_FRAME_DESC_LEN                  16     //@ Length of the frame descriptor, for both read and write
#define RSI_FRAME_CMD_RSP_LEN               56     //@ Length of the command response buffer/frame

/**
 * Const declaration
 *
 */
#define RSI_BYTES_3                         3
#define RSI_BYTES_2                         2


//! Debug Print Levels
#define RSI_DEBUG_LVL         0x00ff
//! These bit values may be ored to all different combinations of debug printing
#define RSI_PL0                0xffff
#define RSI_PL1                0x0001
#define RSI_PL2                0x0002
#define RSI_PL3                0x0004
#define RSI_PL4                0x0008
#define RSI_PL5                0x0010
#define RSI_PL6                0x0020
#define RSI_PL7                0x0040
#define RSI_PL8                0x0080
#define RSI_PL9                0x0100
#define RSI_PL10               0x0200
#define RSI_PL11               0x0400
#define RSI_PL12               0x0800
#define RSI_PL13               0x1000
#define RSI_PL14               0x2000
#define RSI_PL15               0x4000
#define RSI_PL16               0x8000

//#define RSI_DPRINT(lvl, fmt, args)              if (lvl & DEBUG_LVL) printf(fmt, ##args)



#include "platform_specific.h"
#ifdef LINUX_PLATFORM
#include "string.h"
#endif
#endif
