/**
 * @file     rsi_bt_generic.h
 * @version  1.0
 * @date     2014-Aug-23
 *
 * Copyright(C) Redpine Signals 2014
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
 *
 * @section Improvements
 * None
 */

#ifdef __cplusplus
extern "C" {
#endif
#ifndef _RSIBTGENERIC_H_
#define _RSIBTGENERIC_H_

#define RSI_BT_DEVICE_NAME_LEN 50
#define RSI_BT_BD_ADDR_LEN  6
#define RSI_BT_LINK_KEY_LEN 16
#define RSI_TRUE 1
#define RSI_FALSE 0

#ifndef NULL
#define NULL 0
#endif  

#define RSI_BT_FRAME_CMD_RSP_LEN               56     //@ Length of the command response buffer/frame
#define RSI_BT_MAX_PAYLOAD_SIZE                200 
#define RSI_BYTES_4                            4 

#define RSI_BT_STATUS_OFFSET         12
#define RSI_BT_RSP_TYPE_OFFSET       2
#define RSI_BT_FRAME_DESC_LEN        16     //@ Length of the frame descriptor, for both read and write

/**
 * @ Type Definitions
 */
#if 0 /*FIXME:warnings*/
typedef unsigned short    UINT16;
typedef unsigned long	  UINT32;
typedef short	          INT16;
typedef long	          INT32;
 
typedef unsigned char	  UINT08;
typedef signed char       INT08;
#else
#include "rsi_common_types.h"
#endif

typedef struct bt_uuid128 {
    UINT08      data1[4];
    UINT08      data2[2];
    UINT08      data3[2];
    UINT08      data4[8];
} UUID128;
typedef  UINT16      UUID16;
typedef  UINT32      UUID32;

typedef struct bt_uuid {
    UINT08      size;
    UINT08      reserved[3];
    union bt_uuid_t {
        UUID128  val128;        
        UUID32   val32;
        UUID16   val16;
    } Val;
} UUID_T;

/*===================================================*/
/**
 * Frame Descriptor
 */

typedef union {
    struct {
        UINT08   FrmLenAndQueue[2];            
        //@ Bits 15:12=queue, 0000 and 0001 for BT, Bits 11:0 are the length
        UINT08   RespType[2];                
        UINT08   Padding[8];                       
        //@ Unused , set to 0x0
        UINT08   RespStatus[2];
        //@ Frame descriptor response status, 0x0000=success, else error
        UINT08   Padding1[2];
        //@ Unused , set to 0x0
    } FrameDesc;
    UINT08   uFrmDscBuf[RSI_BT_FRAME_DESC_LEN];
    //@ byte format for spi interface, 16 bytes
} RSI_BT_FRAME_DESC;

/*===============================================*/
/**
 *  Set Local Name
 *  --------------
 *  
 *  Command Index: 0x0001
 *  
 *  Arguments:
 *  1. Name Length (1B)
 *  2. Name (50B)
 */
typedef union {

  struct {
    UINT08  NameLength;
    INT08  Name[RSI_BT_DEVICE_NAME_LEN];
  }SetLocalNameFrameSnd;

  UINT08 uSetLocalNameBuf[RSI_BT_DEVICE_NAME_LEN + 1];

} RSI_BT_CMD_SET_LOCAL_NAME;

/*===============================================*/
/*
Query Local Name (Resp)
---------------------

Command Index: 0x0002

Arguments:
1. Name Length (1B)
2. Name (50B)
*/
typedef struct rsi_bt_resp_query_local_name {
    UINT08   NameLength;
    INT08   Name[RSI_BT_DEVICE_NAME_LEN];
} RSI_BT_RESP_QUERY_LOCAL_NAME;

/*===============================================*/

/*
Set Local COD
-------------

Command Index: 0x0003

Arguments:
1. Local COD (4B)
*/
typedef union {

  struct {
    UINT32  LocalCOD;
  }SetLocalCodFrameSnd;

  UINT08 uSetLocalCodBuf[4];

} RSI_BT_CMD_SET_LOCAL_COD;

/*
Antenna select
------------------

Command Index: 0x008F

Arguments:
1. Antenna select (1B)
*/
typedef union {

  struct {
    UINT08 AntennaVal;
  }AntennaSelectFrameSnd;

  UINT08 uAntennaVal;

} RSI_BT_CMD_ANTENNA_SELECT;

/*
Configuration enable/disable
-----------------------------

Command Index: 0x0090

Arguments:
1. config enable (1B)
*/
/*typedef union {

  struct {
    UINT08 ConfigEnable;
  }ConfigEnableFrameSnd;

  UINT08 uConfigEnable;

} RSI_BT_CMD_CONFIG_ENABLE;
*/
/*
Query Local COD (Resp)
--------------------

Command Index: 0x0004

Arguments:
1. Local COD (4B)
*/
typedef struct rsi_bt_resp_query_local_cod {
    UINT32 LocalCOD;
} RSI_BT_RESP_QUERY_LOCAL_COD;


/*
Query RSSI (Cmd, Resp)
--------------------

Command Index: 0x0005

Arguments:
1. BD Address (6B)

1. RSSI value (1B)
*/
typedef union {                                    

  struct {
    UINT08 BDAddress[RSI_BT_BD_ADDR_LEN];
  }QueryRssiFrameSnd;

  UINT08 uQueryRSSIBuf[RSI_BT_BD_ADDR_LEN];

} RSI_BT_CMD_QUERY_RSSI;

typedef struct rsi_bt_resp_query_rssi {
    UINT08 RSSI;
} RSI_BT_RESP_QUERY_RSSI;


/*
Query Link Quality (Cmd, Resp)
----------------------------

Command Index: 0x0006

Arguments:
1. BD Address (6B)

1. Link Quality (1B)
*/
typedef union {
  
  struct {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
  }QueryLinkQualityFrameSnd;

  UINT08 uQueryLinkQualityBuf[RSI_BT_BD_ADDR_LEN];

} RSI_BT_CMD_QUERY_LINK_QUALITY;

typedef struct rsi_bt_resp_query_link_quality {
    UINT08 LinkQuality;
} RSI_BT_RESP_QUERY_LINK_QUALITY;


/*
Query Local BD Address (Resp)
---------------------------

Command Index: 0x0007

Arguments:
1. BD Address (6B)
*/
typedef struct rsi_bt_resp_query_local_bd_address {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
} RSI_BT_RESP_QUERY_LOCAL_BD_ADDRESS;

extern const UINT08  rsi_frameCmdSetLocalName[RSI_BYTES_4];         
extern const UINT08  rsi_frameCmdQryLocalName[RSI_BYTES_4];        
extern const UINT08  rsi_frameCmdSetLocalCOD[RSI_BYTES_4];          
extern const UINT08  rsi_frameCmdQryLocalCOD[RSI_BYTES_4];          
extern const UINT08  rsi_frameCmdQryRSSI[RSI_BYTES_4];              
extern const UINT08  rsi_frameCmdQryLinkQuality[RSI_BYTES_4];       
extern const UINT08  rsi_frameCmdQryLocalBDAddr[RSI_BYTES_4];      

extern const UINT08  rsi_frameCmdBTInit[RSI_BYTES_4];     
extern const UINT08  rsi_frameCmdBTDeinit[RSI_BYTES_4];       
extern const UINT08  rsi_frameCmdBTAntennaSelect[RSI_BYTES_4];       

// Set Tx power for BT
extern const UINT08  rsi_frameCmdAntennaTxPowerLevel[RSI_BYTES_4];       
extern const UINT08  rsi_frameCmdEIRData[RSI_BYTES_4];


//! PER commands
extern const UINT08  rsi_frameCmdPerTransmit[RSI_BYTES_4];
extern const UINT08  rsi_frameCmdPerReceive[RSI_BYTES_4];
extern const UINT08  rsi_frameCmdPerBTStats[RSI_BYTES_4];
extern const UINT08  rsi_frameCmdPerCwMode[RSI_BYTES_4];
extern const UINT08  rsi_frameCmdFeatureBitMap[RSI_BYTES_4];

#ifndef RSI_HWTIMER 
//! need to define this macro if h/w timer is available and it should increment spiTimer2, spiTimer1 
#define RSI_TICKS_PER_SECOND        50000 
#else
#define RSI_TICKS_PER_SECOND        10
#endif 
/*@ Start token timeout */
#define RSI_START_TOKEN_TIMEOUT        10 * RSI_TICKS_PER_SECOND

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
































#ifdef __cplusplus
}
#endif
#endif
