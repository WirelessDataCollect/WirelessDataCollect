/**
 * @file     rsi_bt_api.c
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
#include "rsi_bt_global.h"
#include "rsi_bt_generic.h"
#include "rsi_bt_api.h"


/**
 * Global Variables
 */

/* In the 4 bytes,  
 * BYTE0[0:7],BYTE1[0:3] together represent length of the payload for the frame command
 * BYTE1[4:7], indicates queue number 0000 - Management,0001 - Data
 * BYTE2[0:8], BYTE3[0:7] together represent the Frame command type. 
 */

#ifdef BT_ENABLE

const UINT08  rsi_frameCmdSetLocalName[RSI_BYTES_4]         = {0x33, 0x00, 0x01, 0x00};
const UINT08  rsi_frameCmdQryLocalName[RSI_BYTES_4]         = {0x00, 0x00, 0x02, 0x00};      
const UINT08  rsi_frameCmdSetLocalCOD[RSI_BYTES_4]          = {0x04, 0x00, 0x03, 0x00}; 
const UINT08  rsi_frameCmdQryLocalCOD[RSI_BYTES_4]          = {0x00, 0x00, 0x04, 0x00}; 
const UINT08  rsi_frameCmdQryRSSI[RSI_BYTES_4]              = {0x06, 0x00, 0x05, 0x00};    
const UINT08  rsi_frameCmdQryLinkQuality[RSI_BYTES_4]       = {0x06, 0x00, 0x06, 0x00};        
const UINT08  rsi_frameCmdQryLocalBDAddr[RSI_BYTES_4]       = {0x00, 0x00, 0x07, 0x00};       

const UINT08  rsi_frameCmdSetProfMode[RSI_BYTES_4]          = {0x01, 0x00, 0x08, 0x00};    
const UINT08  rsi_frameCmdSetDiscvMode[RSI_BYTES_4]         = {0x08, 0x00, 0x09, 0x00};   
const UINT08  rsi_frameCmdQryDiscvMode[RSI_BYTES_4]         = {0x00, 0x00, 0x0A, 0x00};    
const UINT08  rsi_frameCmdSetConnMode[RSI_BYTES_4]          = {0x01, 0x00, 0x0B, 0x00};              
const UINT08  rsi_frameCmdQryConnMode[RSI_BYTES_4]          = {0x00, 0x00, 0x0C, 0x00};     
const UINT08  rsi_frameCmdSetPairMode[RSI_BYTES_4]          = {0x01, 0x00, 0x0D, 0x00};                
const UINT08  rsi_frameCmdQryPairMode[RSI_BYTES_4]          = {0x00, 0x00, 0x0E, 0x00};                    
const UINT08  rsi_frameCmdRemNameReq[RSI_BYTES_4]           = {0x06, 0x00, 0x0F, 0x00};          
const UINT08  rsi_frameCmdRemNameReqCancel[RSI_BYTES_4]     = {0x06, 0x00, 0x10, 0x00};                       
const UINT08  rsi_frameCmdInq[RSI_BYTES_4]                  = {0x0C, 0x00, 0x11, 0x00};       
const UINT08  rsi_frameCmdInqCancel[RSI_BYTES_4]            = {0x00, 0x00, 0x12, 0x00};         
const UINT08  rsi_frameCmdBond[RSI_BYTES_4]                 = {0x06, 0x00, 0x13, 0x00};        
const UINT08  rsi_frameCmdBondCancel[RSI_BYTES_4]           = {0x06, 0x00, 0x14, 0x00};           
const UINT08  rsi_frameCmdUnbond[RSI_BYTES_4]               = {0x06, 0x00, 0x15, 0x00};        
const UINT08  rsi_frameCmdSetPinType[RSI_BYTES_4]           = {0x01, 0x00, 0x16, 0x00};            
const UINT08  rsi_frameCmdQryPinType[RSI_BYTES_4]           = {0x00, 0x00, 0x17, 0x00};             
const UINT08  rsi_frameCmdUserConf[RSI_BYTES_4]             = {0x07, 0x00, 0x18, 0x00};              
const UINT08  rsi_frameCmdPasskeyReply[RSI_BYTES_4]         = {0x0C, 0x00, 0x19, 0x00};                  
const UINT08  rsi_frameCmdPincodeReply[RSI_BYTES_4]         = {sizeof(RSI_BT_CMD_PINCODE_REPLY), 0x00, 0x1A, 0x00};         
const UINT08  rsi_frameCmdQryRole[RSI_BYTES_4]              = {0x06, 0x00, 0x1B, 0x00};      
const UINT08  rsi_frameCmdSetRole[RSI_BYTES_4]              = {0x07, 0x00, 0x1C, 0x00};     
const UINT08  rsi_frameCmdQryServ[RSI_BYTES_4]              = {0x06, 0x00, 0x1D, 0x00};         
const UINT08  rsi_frameCmdSearchServ[RSI_BYTES_4]           = {sizeof (RSI_BT_CMD_SEARCH_SERVICE), 0x00, 0x1E, 0x00};                 
               
const UINT08  rsi_frameCmdSPPConn[RSI_BYTES_4]              = {0x06, 0x00, 0x1F, 0x00};  
const UINT08  rsi_frameCmdSPPDisConn[RSI_BYTES_4]           = {0x06, 0x00, 0x20, 0x00};    
const UINT08  rsi_frameCmdSPPTransfer[RSI_BYTES_4]          = {sizeof(RSI_BT_CMD_SPP_TRANSFER), 0x00, 0x21, 0x00};     

const UINT08  rsi_frameCmdBTInit[RSI_BYTES_4]        		    = {0x00, 0x00, 0x8D, 0x00};       
const UINT08  rsi_frameCmdBTDeinit[RSI_BYTES_4]        	    = {0x00, 0x00, 0x8E, 0x00};       
const UINT08  rsi_frameCmdBTAntennaSelect[RSI_BYTES_4]      = {0x01, 0x00, 0x8F, 0x00};       
const UINT08  rsi_frameCmdBTConfigEnable[RSI_BYTES_4]       = {0x01, 0x00, 0x90, 0x00};       

const UINT08  rsi_frameCmdLinkKeyReply[RSI_BYTES_4]         = {0x18, 0x00, 0x91, 0x00};         

const UINT08  rsi_frameCmdPerTransmit[RSI_BYTES_4]          = {sizeof (RSI_BT_CMD_PER_TRANSMIT ), 0x00, 0x98, 0x00};
const UINT08  rsi_frameCmdPerReceive[RSI_BYTES_4]           = {sizeof (RSI_BT_CMD_PER_RECEIVE  ), 0x00, 0x99, 0x00};
const UINT08  rsi_frameCmdPerBTStats[RSI_BYTES_4]           = {sizeof (RSI_BT_CMD_PER_STATS    ), 0x00, 0x9a, 0x00};
const UINT08  rsi_frameCmdPerCwMode[RSI_BYTES_4]            = {sizeof (RSI_BT_CMD_PER_CW_MODE   ), 0x00, 0x9b, 0x00};

const UINT08  rsi_frameCmdSniffMode[RSI_BYTES_4]            = {sizeof (RSI_BT_CMD_SNIFF_MODE), 0x00, 0x9D, 0x00};
const UINT08  rsi_frameCmdSniffExit[RSI_BYTES_4]            = {sizeof (RSI_BT_CMD_SNIFF_EXIT), 0x00, 0x9E, 0x00};
const UINT08  rsi_frameCmdSniffSubrating[RSI_BYTES_4]       = {sizeof (RSI_BT_CMD_SNIFF_SUBRATING), 0x00, 0x9F, 0x00};
const UINT08  rsi_frameCmdSSPEnable[RSI_BYTES_4]            = {sizeof (RSI_BT_CMD_SSP_MODE), 0x00, 0xA0, 0x00};
const UINT08  rsi_frameCmdFeatureBitMap[RSI_BYTES_4]        = {sizeof (RSI_BT_CMD_FEATURE_BIT_MAP), 0x00, 0xA6, 0x00};
const UINT08  rsi_frameCmdAntennaTxPowerLevel[RSI_BYTES_4]  = {sizeof (RSI_BT_CMD_SET_ANTENNA_TX_POWER_LEVEL), 0x00, 0xA7, 0x00};
const UINT08  rsi_frameCmdEIRData[RSI_BYTES_4]              = {sizeof (RSI_BT_CMD_SET_EIR_DATA), 0x00, 0xA9, 0x00};
#endif
