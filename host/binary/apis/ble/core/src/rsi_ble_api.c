/**
 * @file     rsi_ble_api.c
 * @version  1.0
 * @date     2014-08-23
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief API: Definitions of various data structures and variables
 * 
 * @section Description
 * This file contains definition of different commands variables.
 * These definitions are used to construct frames. 
 *
 * @section Improvements
 * None
 */


/**
 * Includes
 */
#include "rsi_ble_global.h"
#include "rsi_ble_api.h"

#include "rsi_bt_global.h"

/**
 * Global Variables
 */

/* In the 4 bytes,  
 * BYTE0[0:7],BYTE1[0:3] together represent length of the payload for the frame command
 * BYTE1[4:7], indicates queue number 0000 - Management,0001 - Data
 * BYTE2[0:8], BYTE3[0:7] together represent the Frame command type. 
 */
#ifdef BLE_ENABLE

const UINT08  rsi_frameCmdSetLocalName[RSI_BYTES_4]         = {sizeof(RSI_BT_CMD_SET_LOCAL_NAME), 0x00, 0x01, 0x00};
const UINT08  rsi_frameCmdQryLocalName[RSI_BYTES_4]         = {0x00, 0x00, 0x02, 0x00};      
const UINT08  rsi_frameCmdSetLocalCOD[RSI_BYTES_4]          = {0x04, 0x00, 0x03, 0x00}; 
const UINT08  rsi_frameCmdQryLocalCOD[RSI_BYTES_4]          = {0x00, 0x00, 0x04, 0x00}; 
const UINT08  rsi_frameCmdQryRSSI[RSI_BYTES_4]              = {0x06, 0x00, 0x05, 0x00};    
const UINT08  rsi_frameCmdQryLinkQuality[RSI_BYTES_4]       = {0x06, 0x00, 0x06, 0x00};        
const UINT08  rsi_frameCmdQryLocalBDAddr[RSI_BYTES_4]       = {0x00, 0x00, 0x07, 0x00};       

const UINT08  rsi_frameCmdLEAdv[RSI_BYTES_4]                = {sizeof(RSI_BLE_CMD_ADVERTISE), 0x00, 0x75, 0x00}; 
const UINT08  rsi_frameCmdLEScan[RSI_BYTES_4]               = {sizeof(RSI_BLE_CMD_SCAN), 0x00, 0x76, 0x00}; 
const UINT08  rsi_frameCmdLEConn[RSI_BYTES_4]               = {sizeof (RSI_BLE_CMD_CONNECT), 0x00, 0x77, 0x00}; 
const UINT08  rsi_frameCmdLEDisconn[RSI_BYTES_4]            = {0x06, 0x00, 0x78, 0x00};  
const UINT08  rsi_frameCmdQryDevstate[RSI_BYTES_4]          = {0x00, 0x00, 0x79, 0x00};        
const UINT08  rsi_frameCmdHciParams[RSI_BYTES_4]            = {0x00, 0x00, 0x7A, 0x00};     
const UINT08  rsi_frameCmdStartEnc[RSI_BYTES_4]             = {0x06, 0x00, 0x7B, 0x00};    
const UINT08  rsi_frameCmdSMPPairReq[RSI_BYTES_4]           = {0x07, 0x00, 0x7C, 0x00};      
const UINT08  rsi_frameCmdSMPResp[RSI_BYTES_4]              = {0x07, 0x00, 0x7D, 0x00}; 
const UINT08  rsi_frameCmdSMPPasskey[RSI_BYTES_4]           = {sizeof(RSI_BLE_CMD_SMP_PASSKEY), 0x00, 0x7E, 0x00};     
      
const UINT08  rsi_frameCmdQryProfList[RSI_BYTES_4]          = {0x0A, 0x00, 0x7F, 0x00};          
const UINT08  rsi_frameCmdQryProfDesc[RSI_BYTES_4]          = {0x1C, 0x00, 0x80, 0x00};    
const UINT08  rsi_frameCmdQryCharServ[RSI_BYTES_4]          = {0x0A, 0x00, 0x81, 0x00};     
const UINT08  rsi_frameCmdQryIncludeServ[RSI_BYTES_4]       = {0x0A, 0x00, 0x82, 0x00};        
const UINT08  rsi_frameCmdReadCharValByUUID[RSI_BYTES_4]    = {0x20, 0x00, 0x83, 0x00};          
const UINT08  rsi_frameCmdQryAtt[RSI_BYTES_4]               = {0x0A, 0x00, 0x84, 0x00};  
const UINT08  rsi_frameCmdQryAttVal[RSI_BYTES_4]            = {0x08, 0x00, 0x85, 0x00};  
const UINT08  rsi_frameCmdQryMulAttVal[RSI_BYTES_4]         = {0x12, 0x00, 0x86, 0x00};        
const UINT08  rsi_frameCmdQryLongAttVal[RSI_BYTES_4]        = {0x0A, 0x00, 0x87, 0x00};        
const UINT08  rsi_frameCmdSetAttVal[RSI_BYTES_4]            = {0x22, 0x00, 0x88, 0x00};     
const UINT08  rsi_frameCmdSetAttValNoAck[RSI_BYTES_4]       = {0x22, 0x00, 0x89, 0x00};          
const UINT08  rsi_frameCmdSetLongAttVal[RSI_BYTES_4]        = {0x33, 0x00, 0x8A, 0x00};
const UINT08  rsi_frameCmdSetPrepLongAttVal[RSI_BYTES_4]    = {0x33, 0x00, 0x8B, 0x00};
const UINT08  rsi_frameCmdExeLongAttVal[RSI_BYTES_4]        = {0x07, 0x00, 0x8C, 0x00};

const UINT08  rsi_frameCmdBTInit[RSI_BYTES_4]        		    = {0x00, 0x00, 0x8D, 0x00};       
const UINT08  rsi_frameCmdBTDeinit[RSI_BYTES_4]        	    = {0x00, 0x00, 0x8E, 0x00};       

const UINT08  rsi_frameCmdBTAntennaSelect[RSI_BYTES_4]      = {0x01, 0x00, 0x8F, 0x00};       
const UINT08  rsi_frameCmdBTConfigEnable[RSI_BYTES_4]       = {0x01, 0x00, 0x90, 0x00};
const UINT08  rsi_frameCmdBTLinkkeyReply[RSI_BYTES_4]       = {0x17, 0x00, 0x91, 0x00};  //need to fill proper valus
const UINT08  rsi_frameCmdBleAddService[RSI_BYTES_4]       	= {0x18, 0x00, 0x92, 0x00};
const UINT08  rsi_frameCmdBleAddAttribute[RSI_BYTES_4]     	= {0x3E, 0x00, 0x93, 0x00};
const UINT08  rsi_frameCmdBleSetLocalAttValue[RSI_BYTES_4]  = {0x23, 0x00, 0x94, 0x00};
const UINT08  rsi_frameCmdBleGetLocalAttValue[RSI_BYTES_4]  = {0x02, 0x00, 0x95, 0x00};

const UINT08  rsi_frameCmdPerTransmit[RSI_BYTES_4]          = {sizeof (RSI_BT_CMD_PER_TRANSMIT ), 0x00, 0x98, 0x00};
const UINT08  rsi_frameCmdPerReceive[RSI_BYTES_4]           = {sizeof (RSI_BT_CMD_PER_RECEIVE  ), 0x00, 0x99, 0x00};
const UINT08  rsi_frameCmdPerBTStats[RSI_BYTES_4]           = {sizeof (RSI_BT_CMD_PER_STATS    ), 0x00, 0x9a, 0x00};
const UINT08  rsi_frameCmdPerCwMode[RSI_BYTES_4]            = {sizeof (RSI_BT_CMD_PER_CW_MODE   ), 0x00, 0x9b, 0x00};

const UINT08  rsi_frameCmdSetAdvertiseData[RSI_BYTES_4]     = {sizeof (RSI_BLE_CMD_SET_ADVERTISE_DATA), 0x00, 0x9C, 0x00};
const UINT08  rsi_frameCmdGetPingTimeout[RSI_BYTES_4]       = {0x00, 0x00, 0xA1, 0x00}; 
const UINT08  rsi_frameCmdSetPingTimeout[RSI_BYTES_4]        = {sizeof (RSI_BLE_CMD_SET_PING_TIMEOUT), 0x00, 0xA2, 0x00};

const UINT08  rsi_frameCmdSetRandAdd[RSI_BYTES_4]           = {sizeof (RSI_BLE_CMD_SET_RANDOM_ADDRESS), 0x00, 0xA3, 0x00 };
const UINT08  rsi_frameCmdSetTxPowerValue[RSI_BYTES_4]      = {sizeof (RSI_BLE_CMD_SET_ANTENNA_TX_POWER_VLAUE), 0x00, 0xA7, 0x00 };
const UINT08  rsi_frameCmdBleWhiteList[RSI_BYTES_4]         = {sizeof (RSI_BLE_CMD_WHITE_LIST), 0x00, 0xAA, 0x00 };

#endif
