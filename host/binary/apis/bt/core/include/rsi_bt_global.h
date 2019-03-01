/**
 * @file     rsi_bt_global.h
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

#ifndef _RSIBTGLOBAL_H_
#define _RSIBTGLOBAL_H_

#include "rsi_bt_generic.h"


/*
Set Profile Mode
----------------

Command Index: 0x0008
*/

typedef union {
  
  struct {
    UINT08  ProfileMode;
  }SetprofileModeFrameSnd;

  UINT08 uSetProfileModeBuf;

} RSI_BT_CMD_SET_PROFILE_MODE;

/*
Set Discovery Mode
------------------

Command Index: 0x0009

Arguments:
1. Mode (1B)
2. Timeout (4B)
*/
typedef union {
  
  struct {
    UINT08  Mode;
    UINT08 Reserved[3];
    INT32  Timeout;
  }SetDiscvModeFrameSnd;

  UINT08 uSetDiscvModeBuf[8];

} RSI_BT_CMD_SET_DISCV_MODE;


/*
Query Discovery Mode (Resp)
-------------------------

Command Index: 0x000A

Arguments:
1. Mode (1B)
*/
typedef struct rsi_bt_resp_query_discovery_mode {
    UINT08  DiscoveryMode;
} RSI_BT_RESP_QUERY_DISCOVERY_MODE;


/*
Set Connectability Mode
-----------------------

Command Index: 0x000B

Arguments:
1. Mode (1B)
*/
typedef union {
  
  struct {
    UINT08  ConnectabilityMode;
  }SetConnectabilityModeFrameSnd;

  UINT08 uSetConnectabilityModeBuf;

}RSI_BT_CMD_SET_CONNECTABILITY_MODE;


/*
Query Connectability Mode (Resp)
------------------------------

Command Index: 0x000C

Arguments:
1. Mode (1B)
*/

typedef struct rsi_bt_resp_query_connectability_mode {
    UINT08  ConnectabilityMode;
} RSI_BT_RESP_QUERY_CONNECTABILITY_MODE;

/*
Set Pair Mode
-------------

Command Index: 0x000D

Arguments:
1. Mode (1B)
*/
typedef union {

  struct {
    UINT08  PairMode;
  }SetPairModeFrameSnd;

  UINT08 uSetPairModeBuf;

}RSI_BT_CMD_SET_PAIR_MODE;


/*
Query Pair Mode (Resp)
--------------------

Command Index: 0x000E

Arguments:
1. Mode (1B)
*/
typedef struct rsi_bt_resp_query_pair_mode {
    UINT08  PairMode;
} RSI_BT_RESP_QUERY_PAIR_MODE;


/*
Remote Name Request
-------------------

Command Index: 0x000F

Arguments:
1. BD Address (6B)
*/
typedef union {

  struct {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
  }RemNameReqFrameSnd;

  UINT08 uRemNameReqBuf[RSI_BT_BD_ADDR_LEN];

}RSI_BT_CMD_REMOTE_NAME_REQUEST;


/*
Remote Name Request Cancel
--------------------------

Command Index: 0x0010

Arguments:
1. BD Address (6B)
*/
typedef union {
  
  struct {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
  }RemNameReqCancelFrameSnd;

  UINT08 uRemNameReqCancelBuf[RSI_BT_BD_ADDR_LEN];

}RSI_BT_CMD_REMOTE_NAME_REQUEST_CANCEL;


/*
Inquiry
-------

Command Index: 0x0011

Arguments:
1. Inquiry Type (1B)
2. Inquiry Duration (4B)
3. Maximum device to find (1B)
*/
typedef union {
  
  struct {
    UINT08  InquiryType;
    UINT08  Reserved[3];
    UINT32  Duration;
    UINT08  MaximumDevicesToFind;
    UINT08  Reserved1[3];
  }InqFrameSnd;

  UINT08 uInqBuf[12];

} RSI_BT_CMD_INQUIRY;


/*
Inquiry Cancel
--------------

Command Index: 0x0012

Arguments:
No Arguments.
*/


/*
Bond
----

Command Index: 0x0013

Arguments:
1. BD Address (6B)
*/
typedef union {
  
  struct {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
  }BondFrameSnd;

  UINT08 uBondBuf[RSI_BT_BD_ADDR_LEN];

}RSI_BT_CMD_BOND;


/*
Bond Cancel
-----------
Command Index: 0x0014

Arguments:
1. BD Address (6B)
*/
typedef union {
  
  struct {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
  }BondCancelFrameSnd;

  UINT08 uBondCancelBuf[RSI_BT_BD_ADDR_LEN];

}RSI_BT_CMD_BOND_CANCEL;


/*
Un-Bond
-------

Command Index: 0x0015

Arguments:
1. BD Address (6B)
*/
typedef union {
  
  struct {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
  }UnbondFrameSnd;

  UINT08 uUnbondBuf[RSI_BT_BD_ADDR_LEN];

}RSI_BT_CMD_UNBOND;


/*
Set PIN Type
------------

Command Index: 0x0016

Arguments:
1. Pin Type (1B)
*/
typedef union {
  
  struct {
    UINT08  PINType;
  }SetPinTypeFrameSnd;

  UINT08 uSetPinTypeBuf;

}RSI_BT_CMD_SET_PIN_TYPE;


/*
Query PIN Type (Resp)
-------------------

Command Index: 0x0017

Arguments:
1. Pin Type (1B)
*/
typedef struct rsi_bt_resp_query_pin_type {
    UINT08  PinType;
} RSI_BT_RESP_QUERY_PIN_TYPE;


/*
User Confirmation
-----------------

Command Index: 0x0018

Arguments:
1. BD Address (6B)
2. Confirmation (1B)
*/
typedef union {
  
  struct {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT08  Confirmation;
  }UserConfFrameSnd;

  UINT08 uUserConfBuf[RSI_BT_BD_ADDR_LEN + 1];

} RSI_BT_CMD_USER_CONFIRMATION;


/*
Passkey Request Reply
---------------------

Command Index: 0x0019

Arguments:
1. BD Address (6B)
2. Reply type (1B)
3. Passkey (4B)
*/
typedef union {

  struct {
    UINT08   BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT08   ReplyType;
  	UINT08   Reserved;
    UINT32   Passkey;
  }PasskeyReplyFrameSnd;

  UINT08 uPasskeyReplyBuf[RSI_BT_BD_ADDR_LEN +1 +1 +4];

} RSI_BT_CMD_PASSKEY_REPLY;


#define MAX_PINCODE_REPLY_SIZE  17
/*
Pincode Request Reply
---------------------

Command Index: 0x001A

Arguments:
1. BD Address (6B)
2. Reply type (1B)
3. Pin code (16B)
*/
typedef union {
  
  struct {
    UINT08   BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT08   ReplyType;
    UINT08   Reserved;
    UINT08   Pincode[MAX_PINCODE_REPLY_SIZE];
  }PincodeReplyFrameSnd;

  UINT08 uPincodeReplyBuf[RSI_BT_BD_ADDR_LEN + 1+ 1+ MAX_PINCODE_REPLY_SIZE];

} RSI_BT_CMD_PINCODE_REPLY;


/*
Query Master Slave Role (Cmd, Resp)
---------------------------------

Command Index: 0x001B

Arguments:
1. BD Address (6B)

1. Role (1B)
*/
typedef union {
  
  struct {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
  }QueryRoleFrameSnd;

  UINT08 uQueryRoleBuf[RSI_BT_BD_ADDR_LEN];

} RSI_BT_CMD_QUERY_ROLE;

typedef struct rsi_bt_resp_query_role {
    UINT08  Role;
} RSI_BT_RESP_QUERY_ROLE;


/*
Set Master-Slave Role
---------------------

Command Index: 0x001C

Arguments:
1. BD Address (6B)
2. Role (1B)
*/
typedef union {
  
  struct {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT08  Role;
  }SetRoleFrameSnd;

  UINT08 uSetRoleBuf[RSI_BT_BD_ADDR_LEN + 1];

} RSI_BT_CMD_SET_ROLE;


/*
Query Services (Cmd, Resp)
------------------------

Command Index: 0x001D

Arguments:
1. BDAddress (6B)

1.
2. 
*/
typedef union {
  
  struct {
    UINT08 BDAddress[RSI_BT_BD_ADDR_LEN];
  }QueryServFrameSnd;

  UINT08 uQueryServBuf[RSI_BT_BD_ADDR_LEN];

} RSI_BT_CMD_QUERY_SERVICES;

typedef struct rsi_bt_resp_query_services {
      UINT08  NbrServices;
      UINT08  Reserved[3];
      UINT32  uuid[32];

} RSI_BT_RESP_QUERY_SERVICES;


/*
Search Service(Cmd, Resp)
--------------

Command Index: 0x001E

Arguments:
1. BDAddress (6B)
2. Service UUID

1. Service Status (1B)
*/

typedef union {
  
  struct {
    UINT08 BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT08 Reserved[2];
    UINT32   ServiceUUID;
  }SearchServFrameSnd;

  UINT08 uSearchServBuf[RSI_BT_BD_ADDR_LEN + 2 + 4 ];

} RSI_BT_CMD_SEARCH_SERVICE;

typedef struct rsi_bt_resp_search_service {
   
  UINT08 ServiceStatus; 

} RSI_BT_RESP_SEARCH_SERVICE;

/*
SPP Connect
-----------

Command Index: 0x001F

Arguments:
1. BDAddress (6B)
*/
typedef union {
  
  struct {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
  }SppConnFrameSnd;

  UINT08 uSppConnBuf[RSI_BT_BD_ADDR_LEN];

} RSI_BT_CMD_SPP_CONNECT;


/*
SPP DisConnect
--------------

Command Index: 0x0020

Arguments:
1. BDAddress (6B)
*/
typedef union {
  
  struct {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
  }SppDisconnFrameSnd;

  UINT08 uSppDisconnBuf[RSI_BT_BD_ADDR_LEN];

} RSI_BT_CMD_SPP_DISCONNECT;


/*
SPP Transfer
------------

Command Index: 0x0021

Arguments:
1. Data Length (2B)
2. Data (1024B)
*/
typedef union {
  
  struct {
    UINT08  DataLength[2];
    UINT08  Data[RSI_BT_MAX_PAYLOAD_SIZE];
  }SppTransferFrameSnd;

  UINT08 uSppTransferBuf[RSI_BT_MAX_PAYLOAD_SIZE + 2];

} RSI_BT_CMD_SPP_TRANSFER;

/*
PER Transfer
------------

Command Index: 0x0098

Arguments:
1. 
2. 
*/
typedef union {
  
  struct {
    UINT08 type;
    UINT08 enable;
    UINT08 bt_addr[6];
    UINT08 pkt_type;       
    UINT08 pkt_length[2];     
    UINT08 link_type;
    UINT08 edr_ind;        
    UINT08 rx_channel;     
    UINT08 tx_channel;     
    UINT08 scrambled_seed ;
    UINT32 num_pkts;       
    UINT08 payload_type;   
    UINT08 protocol_mode;
    UINT08 le_channel;     
    UINT08 tx_power_index ;
    UINT08 tx_mode;        
    UINT08 frequency_hop;  
    UINT08 ant_sel;
  }PerTransmitFrameSnd;

  UINT08 uPerTransmitBuf[27];

} RSI_BT_CMD_PER_TRANSMIT;

/*
PER Receive
------------

Command Index: 0x0099

Arguments:
1. 
2. 
*/
typedef union {
  
  struct {
    UINT08 type;
    UINT08 enable;
    UINT08 bt_addr[6];
    UINT16 pkt_length;     
    UINT08 pkt_type;       
    UINT08 link_type;
    UINT08 edr_ind;        
    UINT08 rx_channel;     
    UINT08 tx_channel;     
    UINT08 scrambled_seed ;
    UINT08 payload_type;
    UINT08 protocol_mode;
    UINT08 le_channel;     
    UINT08 frequency_hop;  
    UINT08 ant_sel;
  }PerReceiveFrameSnd;

  UINT08 uPerReceiveBuf[21];

} RSI_BT_CMD_PER_RECEIVE;

/*
PER Status
------------

Command Index: 0x009A

Arguments:
1. 
2. 
*/
typedef union {
  
  struct {
    UINT08 type;
    UINT08 enable;
  }PerStatsFrameSnd;

  UINT08 uPerStatsBuf[2];

} RSI_BT_CMD_PER_STATS;


/*
PER Status
------------

Command response Index: 0x009A

Arguments:
1. 
2. 
*/
typedef struct {
  
    UINT16 crc_fail;
    UINT16 crc_pass;
    UINT16 RSSI;
    UINT16 Id_pkts;

} RSI_BT_RESP_PER_STATS;


/*
PER CW mode
------------

Command Index: 0x009B

Arguments:
1. 
2. 
*/
typedef union {
  
  struct {
    UINT08 type;
    UINT08 channel;
    UINT08 cw_mode;
    UINT08 cw_type;
    UINT08 ant_sel;
  }PerCwFrameSnd;

  UINT08 uPerCwBuf[5];

} RSI_BT_CMD_PER_CW_MODE;

/*
 * Antenna Tx Power Level
------------

Command Index: 0x00A7

Arguments:
1.  Protocol mode BT/LE
2.  Tx Power value
*/
typedef union {
  struct {
    UINT08 ProtocolMode;
    UINT08 TxPower;
  } AntennaTxPowerLevelsnd;
  
  UINT08 uAntennaTxPowerLevelBuf[2];

} RSI_BT_CMD_SET_ANTENNA_TX_POWER_LEVEL;

/*
 * Set EIR Data 
------------
Command Index: 0x00A9

Arguments:
1.  
2.  Tx Power value
*/
typedef union {
  struct {
    UINT08 FECRequired;
    UINT08 DataLength;
    UINT08 EIRData[200];
  } EIRDatasnd;
  
  UINT08 uEIRDataBuf[2];

} RSI_BT_CMD_SET_EIR_DATA;

/*
linkkey Request Reply
---------------------

Command Index: 0x009C

Arguments:
1. BD Address (6B)
2. Reply type (1B)
3. Reserved (1B)
4. linkkey (16B)
*/
typedef union {
  
  struct {
    UINT08   BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT08   ReplyType;
    UINT08   Reserved;
    UINT08   LinkKey[RSI_BT_LINK_KEY_LEN];
  }LinkKeyReplyFrameSnd;

  UINT08 uLinkKeyReplyBuf[RSI_BT_BD_ADDR_LEN + 2 + RSI_BT_LINK_KEY_LEN];

} RSI_BT_CMD_LINKKEY_REPLY;

/*
Start Sniff mode
---------------------

Command Index: 0x009D

Arguments:
1. BD Address (6B)
2. sniff max interval (2B)
3. sniff min interval (2B)
4. sniff attempts     (2B)
5. sniff timeout      (2B)
*/
typedef union
{
  struct {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT16  SniffMaxIntr;
    UINT16  SniffMinIntr;
    UINT16  SniffAttempt;
    UINT16  SniffTimeout;
  } SniffModeFrameSend;

  UINT08 uSniffModeBuf[RSI_BT_BD_ADDR_LEN + 8];

} RSI_BT_CMD_SNIFF_MODE;

/*
Sniff Exit Mode
---------------------

Command Index: 0x009E

Arguments:
1. BD Address (6B)
*/
typedef union
{
  struct {
    UINT08   BDAddress[RSI_BT_BD_ADDR_LEN];
  } SniffExitFrameSend;

  UINT08 uSniffExitBuf[RSI_BT_BD_ADDR_LEN];
} RSI_BT_CMD_SNIFF_EXIT;


/*
!Sniff Subrating Mode
---------------------

Command Index: 0x009F

Arguments:
1. BD Address (6B)
2. sniff max latency  (2B)
3. sniff min remote timeout (2B)
4. sniff min local timeout  (2B)
*/
typedef union
{
  struct {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT16  MaxLatency;
    UINT16  MinRemoteTimeout;
    UINT16  MinLocalTimeout;
  } SniffSubratingFrameSend;

  UINT08 uSniffSubratingBuf[RSI_BT_BD_ADDR_LEN + 6];
} RSI_BT_CMD_SNIFF_SUBRATING;

/*
!Set SSP Mode
---------------------

Command Index: 0x00A0

Arguments:
1. Pair mode (enable/disable) (1B)
2. IO capability  (1B)
*/
typedef union
{
  struct {
    UINT08   Enable;
    UINT08   IO_Capability;
  } SSPModeFrameSend;
  UINT08 uSspModeBuf[2];
} RSI_BT_CMD_SSP_MODE;

/*
!Set Feature BitMap
---------------------

Command Index: 0x00A6

Arguments:
1. Feature_Bitmap (enable/disable) (4B)
*/
typedef union
{
  struct {
    UINT32   Feature_BitMap;
  } BitMapFrameSend;
  UINT08 uFeatureBitMapBuf[2];
} RSI_BT_CMD_FEATURE_BIT_MAP;

/*****************************************************************************************/
/*                               Bluetooth Events                                        */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                 BR/EDR Events                                         */
/*****************************************************************************************/

/*
Role Change Status
-------------------

Event Index: 0x1000

Arguments:
1. BD Address (6B)
2. Status (1B)
*/
typedef struct rsi_bt_event_role_change_status {
    UINT08 BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT08 RoleChangeStatus;
} RSI_BT_EVENT_ROLE_CHANGE_STATUS;


/*
Unbond Status
-------------

Event Index: 0x1001

Arguments:
1. BD Address (6B)
2. Status (1B)
*/
typedef struct rsi_bt_event_unbond_status {
    UINT08 BDAddress[RSI_BT_BD_ADDR_LEN];
} RSI_BT_EVENT_UNBOND_STATUS;


/*
Bond Response
-------------

Event Index: 0x1002

Arguments:
1. BD Address (6B)
2. Bond Status (1B)
3. Error Status (4B)
*/
typedef struct rsi_bt_event_bond_response {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
} RSI_BT_EVENT_BOND_RESPONSE;


/*
Inquiry Response
----------------

Event Index: 0x1003

Arguments:
1. Inquiry Type (1B)
2. BD Address (6B)
3. Remote Device Name Length (1B)
4. Remote Device Name (50B)
5. COD (4B)
6. RSSI (1B) (Present only if Inquiry with RSSI)
*/
typedef struct rsi_bt_event_inquiry_response {
    UINT08  InquiryType;
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT08  NameLength;
    INT08   RemoteDeviceName[RSI_BT_DEVICE_NAME_LEN];
    UINT08  COD[3];
    UINT08  RSSI;
} RSI_BT_EVENT_INQUIRY_RESPONSE;


/*
Remote Device Name
------------------

Event Index: 0x1004

Arguments:
1. BD Address (6B)
2. Remote Name Length (1B)
3. Remote Device Name (50B)
*/
typedef struct rsi_bt_event_remote_device_name {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT08  NameLength;
    INT08   RemoteDeviceName[RSI_BT_DEVICE_NAME_LEN];
} RSI_BT_EVENT_REMOTE_DEVICE_NAME;


/*
Remote Name Request Cancelled
-----------------------------

Event Index: 0x1005

Arguments:
1. BD Address (6B)
*/
typedef struct rsi_bt_event_remote_name_request_cancel {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
} RSI_BT_EVENT_REMOTE_NAME_REQUEST_CANCEL;


/*
Disconnected
------------

Event Index: 0x1006

Arguments:
1. Connection Handle (4B)
2. Disconnection Reason (1B)
*/
typedef struct rsi_bt_event_disconnected {
    UINT08  ConnectionHandle[4];
    UINT08  DisconnectionReason;
} RSI_BT_EVENT_DISCONNECTED;


/*
User Confirmation Request
-------------------------

Event Index: 0x1007

Arguments:
1. BD Address (6B)
2. ConfirmationValue (4B)
*/
typedef struct rsi_bt_event_user_confirmation_request {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT08  Reserved[2];
    UINT08  ConfirmationValue[4];
} RSI_BT_EVENT_USER_CONFIRMATION_REQUEST;


/*
User Passkey Display
--------------------

Event Index: 0x1008

Arguments:
1. BD Address (6B)
2. Passkey (4B)
*/
typedef struct rsi_bt_event_user_passkey_display {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT08  Reserved[2];
    UINT08  Passkey[4];
} RSI_BT_EVENT_USER_PASKEY_DISPLAY;


/*
User Pincode Request
--------------------

Event Index: 0x1009

Arguments:
1. BD Address (6B)
*/
typedef struct rsi_bt_event_user_pincode_request {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
} RSI_BT_EVENT_USER_PINCODE_REQUEST;


/*
User Passkey Request
--------------------

Event Index: 0x100A

Arguments:
1. BD Address (6B)
*/
typedef struct rsi_bt_event_user_passkey_request {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
} RSI_BT_EVENT_USER_PASSKEY_REQUEST;

/*
Inquiry Complete
--------------------

Event Index: 0x100B

Arguments:
1. BD Address (6B)
*/

/*
Auth Complete
--------------------

Event Index: 0x100C

Arguments:
1. BD Address (6B)
*/
typedef struct rsi_bt_event_auth_complete {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
} RSI_BT_EVENT_AUTH_COMPLETE;

/*
User linkkey Request
--------------------

Event Index: 0x100D

Arguments:
1. BD Address (6B)
*/
typedef struct rsi_bt_event_user_linkkey_request {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
} RSI_BT_EVENT_USER_LINKKEY_REQUEST;

/*
User linkkey save
--------------------

Event Index: 0x100E

Arguments:
1. BD Address (6B)
2. linkkey  (16B)
*/
typedef struct rsi_bt_event_user_linkkey_save {
    UINT08  BDAddress[6];
    UINT08  LinkKey[16];
} RSI_BT_EVENT_USER_LINKKEY_SAVE;

/*
BT Mode event
--------------------

Event Index: 0x1010

Arguments:
1. BD Address   (6B)
2. CurrentMode  (1B)
3. Reserved     (1B)
4. ModeInterval (2B)
*/
typedef struct rsi_bt_event_mode_change
{
  UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
	UINT08  CurrentMode;
  UINT08  Reserved;
	UINT16  ModeInterval;
} RSI_BT_EVENT_MODE_CHANGE;

/*
BT sniff subrating event
--------------------

Event Index: 0x1011

Arguments:
1. BD Address       (6B)
2. MaxTxLatency     (2B)
3. MinRemoteTimeout (2B)
4. MinLocalTimeout  (2B)
*/
typedef struct rsi_bt_event_sniff_subrating
{
  UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
	UINT16  MaxTxLatency;
	UINT16  MinRemoteTimeout;
	UINT16  MinLocalTimeout;
} RSI_BT_EVENT_SNIFF_SUBRATING;

/*
BT SPP pair complete
--------------------

Event Index: 0x100F

Arguments:
1. BD Address (6B)
2. Status     (1B)
*/
typedef struct rsi_bt_event_ssp_complete
{
  UINT08   BDAddress[RSI_BT_BD_ADDR_LEN];
	UINT08   Status;
} RSI_BT_EVENT_SSP_COMPLETE;

/*
SPP Receive
-----------
Command Index: 0x1100

Arguments:
1. Data Length (2B)
2. Data (200B)
*/
typedef struct rsi_bt_event_spp_receive {
    UINT16  DataLen;
    UINT08  Data[200];
} RSI_BT_EVENT_SPP_RECEIVE;



/*
SPP Connected
-------------

Event Index: 0x1101

Arguments:
1. BD Address (6B)
*/
typedef struct rsi_bt_event_spp_connected {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
} RSI_BT_EVENT_SPP_CONNECTED;


/*
SPP DisConnected
-------------

Event Index: 0x1102

Arguments:
1. BD Address (6B)
*/
typedef struct rsi_bt_event_spp_disconnected {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
} RSI_BT_EVENT_SPP_DISCONNECTED;


typedef union rsi_bt_api {
    
    RSI_BT_CMD_SET_LOCAL_NAME                uSetLocalName;
    RSI_BT_CMD_SET_LOCAL_COD                 uSetLocalCOD; 
    RSI_BT_CMD_QUERY_RSSI                    uQryRssi;
    RSI_BT_CMD_QUERY_LINK_QUALITY            uQryLinkQuality;              
    RSI_BT_CMD_ANTENNA_SELECT                uAntennaSelect;
//    RSI_BT_CMD_CONFIG_ENABLE                 uConfigEnable; 
    
    RSI_BT_CMD_SET_PROFILE_MODE              uSetProfMode;               
    RSI_BT_CMD_SET_DISCV_MODE                uSetDiscvMode;        
    RSI_BT_CMD_SET_CONNECTABILITY_MODE       uSetConnMode;                   
    RSI_BT_CMD_SET_PAIR_MODE                 uSetPairMode;                     
    RSI_BT_CMD_REMOTE_NAME_REQUEST           uRemNameReq;                     
    RSI_BT_CMD_REMOTE_NAME_REQUEST_CANCEL    uRemNameReqCancel;                     
    RSI_BT_CMD_INQUIRY                       uInq;               
    RSI_BT_CMD_BOND                          uBond;        
    RSI_BT_CMD_BOND_CANCEL                   uBondCancel;                   
    RSI_BT_CMD_UNBOND                        uUnbond;                     
    RSI_BT_CMD_SET_PIN_TYPE                  uSetPinType;                    
    RSI_BT_CMD_USER_CONFIRMATION             uUserConf;          
    RSI_BT_CMD_PASSKEY_REPLY                 uPasskeyReply;                  
    RSI_BT_CMD_PINCODE_REPLY                 uPincodeReply;            
    RSI_BT_CMD_QUERY_ROLE                    uQryRole;               
    RSI_BT_CMD_SET_ROLE                      uSetRole;             
    RSI_BT_CMD_QUERY_SERVICES                uQryServ;                       
    RSI_BT_CMD_SEARCH_SERVICE                uSearchServ;                 
    RSI_BT_CMD_SPP_CONNECT                   uSPPConn;               
    RSI_BT_CMD_SPP_DISCONNECT                uSPPDisConn;                
    RSI_BT_CMD_SPP_TRANSFER                  uSPPTransfer;
    RSI_BT_CMD_LINKKEY_REPLY                 uLinkKeyReply;
    RSI_BT_CMD_SNIFF_MODE                    uSniffEnable;
    RSI_BT_CMD_SNIFF_EXIT                    uSniffDisable;
    RSI_BT_CMD_SNIFF_SUBRATING               uSniffSubrating;
    RSI_BT_CMD_SSP_MODE                      uSSPEnable;
    RSI_BT_CMD_FEATURE_BIT_MAP               uFeatureBitMap;
    RSI_BT_CMD_PER_TRANSMIT                  uPerTransmit;
    RSI_BT_CMD_PER_RECEIVE                   uPerReceive;
    RSI_BT_CMD_PER_STATS                     uPerStats;
    RSI_BT_CMD_PER_CW_MODE                   uPerCw;
    RSI_BT_CMD_SET_ANTENNA_TX_POWER_LEVEL    uAntennaTxPowerLevel;
    RSI_BT_CMD_SET_EIR_DATA                  uSetEIRData;
}RSI_BT_API;


typedef struct rsi_bt_response{
  UINT08   ResponseCode[2];
  UINT08   Status[2];                  
  //@ 0- For Success ,Non-Zero Value is the Error Code return
  union {
    //@ response payload    
    RSI_BT_RESP_QUERY_LOCAL_NAME             uQryLocalName;
    RSI_BT_RESP_QUERY_LOCAL_COD              uQryLocalCOD;
    RSI_BT_RESP_QUERY_RSSI                   uQryRssi;
    RSI_BT_RESP_QUERY_LINK_QUALITY           uQryLinkQuality;
    RSI_BT_RESP_QUERY_LOCAL_BD_ADDRESS       uQryLocalBDAddr;
    
    RSI_BT_RESP_QUERY_DISCOVERY_MODE         uQryDiscvMode;
    RSI_BT_RESP_QUERY_CONNECTABILITY_MODE    uQryConnMode;
    RSI_BT_RESP_QUERY_PAIR_MODE              uQryPairMode;
    RSI_BT_RESP_QUERY_PIN_TYPE               uQryPinType;
    RSI_BT_RESP_QUERY_ROLE                   uQryRole;
    RSI_BT_RESP_QUERY_SERVICES               uQryServ;

    RSI_BT_EVENT_ROLE_CHANGE_STATUS          uRoleChangeStatus;  
    RSI_BT_EVENT_UNBOND_STATUS               uUnbondStatus;
    RSI_BT_EVENT_BOND_RESPONSE               uBondResp;
    RSI_BT_EVENT_INQUIRY_RESPONSE            uInqResp;
    RSI_BT_EVENT_REMOTE_DEVICE_NAME          uRemDevName;
    RSI_BT_EVENT_REMOTE_NAME_REQUEST_CANCEL  uRemNameReqCancel; 
    RSI_BT_EVENT_DISCONNECTED                uDisconn;
    RSI_BT_EVENT_USER_CONFIRMATION_REQUEST   uUserConfReq;
    RSI_BT_EVENT_USER_PASKEY_DISPLAY         uUserPaskeyDisp;
    RSI_BT_EVENT_USER_PINCODE_REQUEST        uUserPincodeReq;
    RSI_BT_EVENT_USER_PASSKEY_REQUEST        uUserPasskeyReq;
    RSI_BT_EVENT_SPP_CONNECTED               uSppConn;
    RSI_BT_EVENT_SPP_DISCONNECTED            uSppDisConn;
    RSI_BT_RESP_PER_STATS                    uPerStats;
    UINT08                                   uCmdRspBuf[RSI_BT_FRAME_CMD_RSP_LEN + RSI_BT_MAX_PAYLOAD_SIZE + 100];
    RSI_BT_EVENT_MODE_CHANGE                 uModeChange;  
  }uCmdRspPayLoad;
} RSI_BT_RESPONSE;

 
extern const UINT08  rsi_frameCmdSetProfMode[RSI_BYTES_4];          
extern const UINT08  rsi_frameCmdSetDiscvMode[RSI_BYTES_4];         
extern const UINT08  rsi_frameCmdQryDiscvMode[RSI_BYTES_4];         
extern const UINT08  rsi_frameCmdSetConnMode[RSI_BYTES_4];          
extern const UINT08  rsi_frameCmdQryConnMode[RSI_BYTES_4];          
extern const UINT08  rsi_frameCmdSetPairMode[RSI_BYTES_4];          
extern const UINT08  rsi_frameCmdQryPairMode[RSI_BYTES_4];          
extern const UINT08  rsi_frameCmdRemNameReq[RSI_BYTES_4];           
extern const UINT08  rsi_frameCmdRemNameReqCancel[RSI_BYTES_4];     
extern const UINT08  rsi_frameCmdInq[RSI_BYTES_4];                  
extern const UINT08  rsi_frameCmdInqCancel[RSI_BYTES_4];            
extern const UINT08  rsi_frameCmdBond[RSI_BYTES_4];                 
extern const UINT08  rsi_frameCmdBondCancel[RSI_BYTES_4];           
extern const UINT08  rsi_frameCmdUnbond[RSI_BYTES_4];               
extern const UINT08  rsi_frameCmdSetPinType[RSI_BYTES_4];           
extern const UINT08  rsi_frameCmdQryPinType[RSI_BYTES_4];           
extern const UINT08  rsi_frameCmdUserConf[RSI_BYTES_4];             
extern const UINT08  rsi_frameCmdPasskeyReply[RSI_BYTES_4];         
extern const UINT08  rsi_frameCmdPincodeReply[RSI_BYTES_4];         
extern const UINT08  rsi_frameCmdQryRole[RSI_BYTES_4];              
extern const UINT08  rsi_frameCmdSetRole[RSI_BYTES_4];              
extern const UINT08  rsi_frameCmdQryServ[RSI_BYTES_4];              
extern const UINT08  rsi_frameCmdSearchServ[RSI_BYTES_4];           
                
extern const UINT08  rsi_frameCmdSPPConn[RSI_BYTES_4];              
extern const UINT08  rsi_frameCmdSPPDisConn[RSI_BYTES_4];           
extern const UINT08  rsi_frameCmdSPPTransfer[RSI_BYTES_4];          

extern const UINT08  rsi_frameCmdLinkKeyReply[RSI_BYTES_4];         
extern const UINT08  rsi_frameCmdSniffMode[RSI_BYTES_4];
extern const UINT08  rsi_frameCmdSniffExit[RSI_BYTES_4];
extern const UINT08  rsi_frameCmdSniffSubrating[RSI_BYTES_4];
extern const UINT08  rsi_frameCmdSSPEnable[RSI_BYTES_4];
#endif


#ifdef __cplusplus
}
#endif




