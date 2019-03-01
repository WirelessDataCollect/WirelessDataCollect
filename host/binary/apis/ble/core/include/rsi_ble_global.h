/**
 * @file     rsi_ble_global.h
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

#ifndef _RSIBLEGLOBAL_H_
#define _RSIBLEGLOBAL_H_

#include "rsi_bt_generic.h"

/*****************************************************************************************/
/*                               Bluetooth Low energy                                    */
/*****************************************************************************************/


/*
Advertise Local Device
----------------------

Command Index: 0x75

Arguments:
1. Status (1B)
2. Advertise Type (1B)
3. Filter Type (1B)
4. DirectAddrType (1B)
5. DirectAddr (6B)
6. adv_int_min (2B)
7. adv_int_max (2B)
8. own_add_type (1B)
9. adv_channel_map (1B)
*/
typedef union {
  
  struct {
    UINT08  Status;
    UINT08  AdvertiseType;
    UINT08  FilterType;
    UINT08  DirectAddrType;
    UINT08  DirectAddr[RSI_BT_BD_ADDR_LEN];
    UINT16  adv_int_min;
    UINT16  adv_int_max;
    UINT08  own_add_type;
    UINT08  adv_channel_map;
  }AdvFrameSnd  ;

  UINT08 uAdvBuf[RSI_BT_BD_ADDR_LEN + 10];

} RSI_BLE_CMD_ADVERTISE  ;


/*
Scan Devices
------------

Command Index: 0x76

Arguments:
1. Status (1B)
2. Scan type (1B)
3. Filter Type (1B)
4. own_add_type (1B)
5. scan_int (2B)
6. scan_win (2B)
*/
typedef union {
  
  struct {
    UINT08  Status;
    UINT08  Scantype;
    UINT08  FilterType;
   // UINT08  Reserved;
    UINT08  own_add_type;
    UINT16  scan_int;
    UINT16  scan_win;
  }ScanFrameSnd  ;

  UINT08 uScanBuf[8];

} RSI_BLE_CMD_SCAN  ;


/*
LE Connection
-------------

Command Index: 0x77

Arguments:
1. Address Type (1B)
2. BD Address (6B)
*/
typedef union {
  
  struct {
    UINT08  AddressType;
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT08  Reserved;
    UINT16  LeScanInterval;
    UINT16  LeScanWindow;
    UINT16  ConnIntervalMin;
    UINT16  ConnIntervalMax;
    UINT16  ConnLatency;
    UINT16  SupervisionTimeout;
  }ConnectFrameSnd  ;

  UINT08 uConnectBuf[RSI_BT_BD_ADDR_LEN + 14];

} RSI_BLE_CMD_CONNECT  ;


/*
LE Disconnect
-------------

Command INdex: 0x78

Arguments:
1. BDAddress (6B)
*/

typedef union {
  
  struct {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
  }DisconnectFrameSnd;

  UINT08 uDisconnectReqbuf[RSI_BT_BD_ADDR_LEN];

} RSI_BLE_CMD_DISCONNECT;


/*
Set LE Random Address
-------------

Command INdex: 0xA3

Arguments:
1. BDAddress (6B)
*/

typedef union {
  
  struct {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
  }SetRandAddFrameSnd;

  UINT08 uSetRandAddbuf[RSI_BT_BD_ADDR_LEN];

} RSI_BLE_CMD_SET_RANDOM_ADDRESS;

/*
Set Tx power value
-------------

Command INdex: 0xA7

Arguments:
1. Tx power value
*/

typedef union {
  
  struct {
    UINT08  ProtocolMode;
    UINT08  AntennaTxPower;
  }SetAntennaTxPower;

  UINT08 uSetAntennaTxPowerbuf[2];

} RSI_BLE_CMD_SET_ANTENNA_TX_POWER_VLAUE;

/*
Set Tx power value
-------------

Command INdex: 0xAA

Arguments:
Arguments:
1. BDAddress (6B)
2. Address type (1B)
3. Clear/Add device to white list (1B)  //  0 - Clear white list
                                        //  1 - Add to white list
                                        //  2 - Delete from white list *
*/
typedef union {
  
  struct {

    UINT08  AddOrDelete;
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT08  BDAddresstype;
  }BleWhiteList;

  UINT08 uBLEWhiteList[RSI_BT_BD_ADDR_LEN + 2];

} RSI_BLE_CMD_WHITE_LIST;

/*
Query Device State (Resp)
-----------------------

Command Index: 0x79 

Arguments:
1. State (1B)
*/
typedef struct rsi_ble_resp_query_device_state {
    UINT08  DeviceState;    
} RSI_BLE_RESP_QUERY_DEVICE_STATE  ;


/*
Start Encryption
----------------

Command Index: 0x7b

Arguments:
1. BDAddress    (6B)
*/
typedef union {
  
  struct {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
  }SmpEncriptionFrameSnd  ;

  UINT08 uSmpEncryptReqbuf[RSI_BT_BD_ADDR_LEN];

} RSI_BLE_CMD_ENCRYPTTION;


/*
Start SMP Pair Request
----------------------

Command Index: 0x7c

Arguments:
1. BDAddress (6B)
2. IOCapability (1B)
*/
typedef union {
  
  struct {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT08  IOCapability;   
  }SmpPairReqFrameSnd  ;

  UINT08 uSmpPairReqbuf[RSI_BT_BD_ADDR_LEN + 1];

} RSI_BLE_CMD_SMP_PAIR_REQUEST  ;


/*
SMP Response
------------

Command Index: 0x7d

Arguments:
1. BDAddress (6B)
2. IOCapability (1B)
*/

typedef union {
  
  struct {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT08  IOCapability;    
  }SmpRespFrameSnd  ;

  UINT08 uSmpRespBuf[RSI_BT_BD_ADDR_LEN + 1];

} RSI_BLE_CMD_SMP_RESPONSE  ;


/*
SMP Passkey 
-----------

Command Index:  0x7e

Arguments:
1. BDAddress (6B)
2. Passkey (4B)
*/
typedef union {
  
  struct {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT08  Reserved[2];
    UINT08  Passkey[4];
  }SmpPasskeyFrameSnd  ;

  UINT08 uSmpPasskeyBuf[RSI_BT_BD_ADDR_LEN + 6];

} RSI_BLE_CMD_SMP_PASSKEY  ;

/*
Set advertise data 
-----------

Command Index:  0x7e

Arguments:
1. Data (31B)
2. Data Length (1B)
*/
typedef union {
  
  struct {
    UINT08  DataLen;
    UINT08  Data[31];
  }SetAdvertiseDataFrameSnd  ;

  UINT08 uSetAdvertiseDataBuf[32];

} RSI_BLE_CMD_SET_ADVERTISE_DATA  ;


/*
Set le ping timeout 
-----------

Command Index:  0x7e

Arguments:
1. BDAddress (6B)
2. timeout (2B)
*/
typedef union {
  
  struct {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT16  Timeout;
  }SetLePingTimeoutFrameSnd  ;

  UINT08 uSetLePingTimeoutBuf[RSI_BT_BD_ADDR_LEN + 2];

} RSI_BLE_CMD_SET_PING_TIMEOUT  ;

/*
Get le ping timeout 
-----------

Command Index:  0x7e

Arguments:
1. timeout (2B)
*/
  
typedef struct  rsi_ble_resp_get_ping_timeout{
    UINT16  Timeout;
} RSI_BLE_RESP_GET_PING_TIMEOUT  ;



/*****************************************************************************************/
/*                               Bluetooth Low energy (GATT)                             */
/*****************************************************************************************/


/*
Query All Profile List (Resp)
---------------------------

Command Index: 0x7f

Arguments:
1. BD Address
2. start handle
3. end handle


Arguments:
1. Number of Profiles (1B)
2. Profile Descriptors List (6B)
2.1. Start Handle (2B)
2.2. End Handle (2B)
2.3. Profile UUID (2B)
*/
#define  BLE_MAX_RESP_LIST   5
typedef union {
  
  struct {
    UINT08     BDAddress[6];
    UINT16     StartHandle;
    UINT16     EndHandle;
  }ProfileReqFrameSnd;

  UINT08 uProfileReqBuf[10];

} RSI_BLE_CMD_PROFILE_LIST;

typedef struct profile_descriptor{
    UINT08  StartHandle[2];
    UINT08  EndHandle[2];
    UUID_T    ProfileUUID;
}PROFILE_DESCRIPTOR  ;

typedef struct rsi_ble_resp_query_profiles_list {
    UINT08  NumberOfProfiles;
    UINT08  Reserved[3];
    PROFILE_DESCRIPTOR ProfileDescriptor[BLE_MAX_RESP_LIST];
} RSI_BLE_RESP_QUERY_PROFILES_LIST  ;


/*
Query Single Profile Descriptor (Cmd, Resp)
-----------------------------------------

Command Index: 0x80

Arguments:
1. UUID Size (1B)
2. Profile UUID (16B Max)

1. BDAddress (6B)
2. ProfileDescriptor
*/
typedef union {
  
  struct {
    UINT08  BDAddress[6];
	  UINT08  Reserved[2];
    UUID_T    ProfileUUID;
  }QueryProfileDescFrameSnd  ;

  UINT08 uQueryProfileDescBuf[28];

} RSI_BLE_CMD_QUERY_PROFILE  ;

typedef struct rsi_ble_resp_query_profile_descriptor {
    PROFILE_DESCRIPTOR  ProfileDescriptor;
} RSI_BLE_RESP_QUERY_PROFILE_DESCRIPTOR  ;

/*
Query all Characteristic Services (Cmd, Resp)
-------------------------------------------

Command Index: 0x81

Arguents:
1. BDAddress
2. Start Handle (2B)
3. End Handle (2B)

1. Handle (2B)
2. Character Property (1B)
3. Character Handle (2B)
4. Character UUID (16B)
*/
typedef union {
  
  struct {
    UINT08  BDAddress[6];
    UINT08  StartHandle[2];
    UINT08  EndHandle[2];
  }QueryCharSerFrameSnd  ;
  
  UINT08 uQueryCharSerBuf[10];

} RSI_BLE_CMD_QUERY_CHARACTERISTIC_SERVICES  ;

typedef struct bt_le_char_serv {
		UINT08  CharacterProperty;
		UINT08  Reserved;
		UINT16  CharacterHandle;
		UUID_T    CharacterUUID;
} BT_LE_CHAR_SERV;

typedef struct characteristic_service {
    UINT16   Handle;
    UINT08   Reserved[2];
    BT_LE_CHAR_SERV  CharServ;
}CHARACTERISTIC_SERVICE  ;

typedef struct rsi_ble_resp_query_characteristic_services {
    UINT08                  NumberOfCharServices;
    UINT08                  Reserved[3];
    CHARACTERISTIC_SERVICE  CharacteristicService[BLE_MAX_RESP_LIST];
} RSI_BLE_RESP_QUERY_CHARACTERISTIC_SERVICES  ; 


/*
Query Include Services (Cmd, Resp)
--------------------------------

Command Index: 0x82

Arguments:
1. BDAddress    (6B)
2. Start Handle (2B)
3. End Handle   (2B)

1. Handle (2B)
2. Include Start Handle (2B)
3. Include End Handle (2B)
4. Include UUID (16B)
*/
typedef union {
  
  struct {
    UINT08  BDAddress[6];
    UINT08  StartHandle[2];
    UINT08  EndHandle[2];
  }QueryIncludeServFrameSnd  ;

  UINT08 uQueryIncludeServBuf[10];

} RSI_BLE_CMD_QUERY_INCLUDE_SERVICES  ;


typedef struct bt_le_inc_serv {
	UINT16  IncludeStartHandle;
	UINT16  IncludeEndHandle;
    UUID_T    IncludeUUID;
} BT_LE_INC_SERV;
typedef struct include_service {
    UINT16          Handle;
	UINT08          Reserved[2];
    BT_LE_INC_SERV  IncServ;
}INCLUDE_SERVICE  ;

typedef struct rsi_ble_resp_query_include_service {
    UINT08           NumberOfIncludeServices;
	UINT08           Reserved[3];
    INCLUDE_SERVICE  IncludeServices[BLE_MAX_RESP_LIST];    
} RSI_BLE_RESP_QUERY_INCLUDE_SERVICE  ;


/*
Read Characteristic Value By UUID (Cmd, Resp)
---------------------------------------------

Command Index: 0x83 

Arguments:
1. BDAddress (6B)
2. Start Handle (2B)
3. End Handle (2B)
4. UUID Size (1B)
5. UUID (16B)

1. Number of values (1B)
2. Character values[30] (30B)

*/
typedef union {

  struct {
    UINT08  BDAddress[6];
    UINT08  StartHandle[2];
    UINT08  EndHandle[2];
	  UINT08  Reserved[2];
    UUID_T    CharacterUUID;   
  }ReadCharValByUuidFrameSnd  ;

  UINT08 uReadCharValByUuidBuf[12 + sizeof(UUID_T)];

} RSI_BLE_CMD_READ_CHAR_VALUE_BY_UUID  ;

typedef struct rsi_ble_resp_read_char_value_by_uuid {
    UINT16  NumberOfValues;
    UINT08  CharacterValue[30];
} RSI_BLE_RESP_READ_CHAR_VALUE_BY_UUID  ;


/*
Query Attributes (Cmd, Resp)
----------------------------

Command Index: 0x84

Arguments:
1. BDAddress
2. Start Handle (2B)
3. End Handle (2B)

1. Handle (2B)
2, Attribute Type(2B)
*/
typedef union {

  struct {
    UINT08  BDAddress[6];
    UINT08  StartHandle[2];
    UINT08  EndHandle[2];
  }QueryAttFrameSnd  ;

  UINT08 uQueryAttBuf[10];

} RSI_BLE_CMD_QUERY_ATT_DESC  ;

typedef struct attribute_descriptor {
    UINT08  Handle[2];
	UINT08  Reserved[2];
    UUID_T    AttributeTypeUUID;
} ATTRIBUTE_DESCRIPTOR  ;

typedef struct rsi_ble_resp_query_att_desc {
    UINT08                NumberOfAttributes;
	UINT08                Reserved[3];
    ATTRIBUTE_DESCRIPTOR  AttributeDescriptor[BLE_MAX_RESP_LIST];
} RSI_BLE_RESP_QUERY_ATT_DESC  ;


/*
Query Attribute Value (Cmd, Resp)
--------------------------------

Command Index: 0x85

Arguments:
1. BDAddress (6B)
2. Handle (2B)

1. Number of Values (1B)
2. Attribute Values[30] (30B Max)
*/
typedef union {
  
  struct {
    UINT08  BDAddress[6];
    UINT08  Handle[2];
  }QueryAttValFrameSnd  ;

  UINT08 uQueryAttValBuf[8];

} RSI_BLE_CMD_QUERY_ATT_VALUE  ;

typedef struct rsi_ble_resp_query_att_value {
    UINT08  NumberOfValues;
    UINT08  AttributeValues[30];
} RSI_BLE_RESP_QUERY_ATT_VALUE  ;



/*
Query Multiple Attribute Values (Cmd, Resp)
------------------------------------

Command Index: 0x0087

Arguments:
1. BD Address        (6B)
1. Number Of Handles (2B)
2. Handles[5] (2B each)

1. Number of Values (1B)
2. Attribute values[30] (30B)
*/
typedef union {

  struct {
    UINT08  BDAddress[6];
    UINT08  NumberOfHandles;
	  UINT08  Reserved;
    UINT16  Handles[5];    
  }QueryMulAttValFrameSnd  ;

  UINT08 uQueryMulAttValBUF[18];

} RSI_BLE_CMD_QUERY_MULTIPLE_ATT_VALUES  ;

typedef struct rsi_ble_resp_query_multiple_att_values {
    UINT16  NumberOfValues;
    UINT08  AttributeValues[30];
} RSI_BLE_RESP_QUERY_MULTIPLE_ATT_VALUES  ;


/*
Query Long Attribute Values (Cmd, Resp)
--------------------------------------

Command Index:0x0088

Arguments:
1. BDAddress(6B);
2. Handle (2B)
3. Offset (2B)

1. Number of Values (1B)
2. Long Attribute Values[50] (50B) 
*/
typedef union {
  struct {
    UINT08  BDAddress[6];
    UINT16  Handle;
    UINT16  Offset;   
  }QueryLongAttValFrameSnd  ;

  UINT08 QueryLongAttValBuf[10];

} RSI_BLE_CMD_QUERY_LONG_ATT_VALUE  ;

typedef struct rsi_ble_resp_query_long_att_value {
    UINT08  NumberOfValues;
    UINT08  LongAttValue[50];    
} RSI_BLE_RESP_QUERY_LONG_ATT_VALUE  ;


/*
Set Attribute Value 
--------------------

Command Index:  0x88

Arguments:
1. BDAddress(6B);
2. Handle (2B)
3. Length (1B)
4. Value[25] (1B each)
*/
typedef union {
  
  struct {
    UINT08  BDAddress[6];
    UINT08  Handle[2];
    UINT08  Length;
    UINT08  Value[25];
  }SetAttValFrameSnd  ;

  UINT08 uSetAttValBuf[34];

} RSI_BLE_CMD_SET_ATT_VALUE  ;


/*
Set Attribute Value with no response from remote device
-------------------------------------------------------

Command Index: 0x89

Arguments:
1. BDAddress(6B);
2. Handle (2B)
3. Length (1B)
4. Value[25] (1B each) 
*/
typedef union {
  
  struct {
    UINT08  BDAddress[6];
    UINT08  Handle[2];
    UINT08  Length;
    UINT08  Value[25];
  }SetAttValNoAckFrameSnd  ;

  UINT08 uSetAttValNoAckbuf[34];

} RSI_BLE_CMD_SET_ATT_VALUE_NO_ACK  ;


/*
Set Long Attribute Value 
-------------------------

Command Index:  0x8a

Arguments:
1. BDAddress(6B);
2. Handle (2B)
3. Offset (2B)
4. Length (1B)
5. Value[40] (1B)
*/
typedef union {
  
  struct {
    UINT08  BDAddress[6];
    UINT08  Handle[2];
    UINT08  Offset[2];
    UINT08  Length;
    UINT08  Value[40];
  }SetLongAttValFrameSnd;

  UINT08 uSetLongAttValBuf[51];

}RSI_BLE_CMD_SET_LONG_ATT_VALUE;


/*
Set Prepare Long Attribute Value(Prepare write)
------------------------------------------------

Command Index:  0x8b

Arguments:
1. BDAddress(6B);
2. Handle (2B)
3. Offset (2B)
4. Length (1B)
5. Value[40] (1B each)
*/
typedef union {
  
  struct {
    UINT08  BDAddress[6];
    UINT08  Handle[2];
    UINT08  Offset[2];
    UINT08  Length;
    UINT08  Value[40];
  }SetPreLongAttValFrameSnd;

  UINT08 uSetPreLongAttValBuf[51];

}RSI_BLE_CMD_SET_PREPARE_LONG_ATT_VALUE;


/*
Execute Long Attribute value Write
-----------------------------------

Command Index: 0x8c

Arguments:
1. BDAddress(6B);
1. Flag (1B)
*/
typedef union {
  
  struct {
    UINT08  BDAddress[6];
    UINT08  Flag;
  }ExeLongAttValWrFrameSnd  ;

  UINT08 uExeLongAttValWrbuf;

} RSI_BLE_CMD_EXECUTE_LONG_ATT_VALUE_WRITE  ;

/*
Add GATT Service
-----------------------------------

Command Index: 0x92

Arguments:
1. ServiceUUID(20B);
2. NbrOfAttributes(2B);
3. MaxDataSize(2B);

1. ServiceHndlerPtr (4B)
2. StartHndl        (2B)
*/
typedef union {
  
  struct  {
      UUID_T        ServiceUUID;
      UINT16      NbrAttributes;
      UINT16      MaxAttDataSize;
  } AddServiceRecord;

  UINT08 uAddServiceRecord[24];

} RSI_BLE_CMD_ADD_GATT_SERVICE;


typedef struct rsi_ble_resp_add_gatt_service {
    void     *ServiceHndlerPtr;
    UINT16    StartHndl;
} RSI_BLE_RESP_ADD_GATT_SERVICE;

/*
Add Attibute to GATT Service
-----------------------------------

Command Index: 0x93

Arguments:
1. ServiceHndlerPtr(4B);
2. attribute handle(2B);
3. Reserved(2B);
4. attribute uuid(20B);
5. property of attribute value (read/write)(1B);
6. data (maximum of 31 bytes).
7. data length(2B).
*/
typedef union {
    
    struct  {
        void       *ServiceHndlerPtr;
        UINT16      Hndl;
        UINT16      Reserved;
        UUID_T        AttUUID;
        UINT08      Prop;
        UINT08      Data[31];
        UINT16      DataLen;
    } AddAttRecord;

  UINT08 uAddAttRecord[62];

} RSI_BLE_CMD_ADD_GATT_ATTRIBUTE;


/*
Set or change the LOCAL Attribute Value
-----------------------------------

Command Index: 0x94

Arguments:
1. Hndl(2B);
2. DataLen handle(2B);
3. Data(31B);
*/
typedef struct  {
    UINT16             Hndl;
    UINT16             DataLen;
    UINT08             Data[31];
} RSI_BLE_CMD_SET_LOCAL_ATT_VALUE;

/*
Get the Local Attribute Value
-----------------------------------
Command Index: 0x95

Arguments:
1. Hndl(2B);

1. Hndl(2B);
2. DataLen handle(2B);
3. Data(31B);
*/
typedef struct  {
    UINT16             Hndl;
} RSI_BLE_CMD_GET_LOCAL_ATT_VALUE;

//Get the attribute value from GATT service(RESP), cmd_ix = 0x95;
typedef struct  {
    UINT16             Hndl;
    UINT16             DataLen;
    UINT08             Data[31];
} RSI_BLE_RESP_GET_LOCAL_ATT_VALUE;



/*****************************************************************************************/
/*                                     LE Events                                         */
/*****************************************************************************************/

/*
LE Advertise Report
-------------------

Event Index: RSI_BLE_EVENT_GAP_SCAN_RESP

Arguments:
1. BD Address Type (1B)
2. BD Address (6B)
3. Remote Device Name (50B)
*/
typedef struct rsi_ble_event_advertise_report {
  UINT08  BDAddresstype;
  UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
  UINT08  Adv_data_len;
  UINT08  Adv_data[31];
  UINT08  RSSI;
} RSI_BLE_EVENT_RESP_ADVERTISE_REPORT  ;


/*
Connection Status Event
-----------------------

Event Index: RSI_BLE_EVENT_GAP_CONN_STATUS

Arguments:
1. BD Address Type (1B)
2. BD Address (6B)
3. Status (1B) 
*/
typedef struct rsi_ble_event_connection_status {
    UINT08  BDAddresstype;
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT08  Status;
} RSI_BLE_EVENT_RESP_CONNECTION_STATUS  ;

/*
Disconnection Status Event
-----------------------

Event Index: RSI_BLE_EVENT_GAP_CONN_STATUS

Arguments:
1. BD Address (6B)
*/
typedef struct rsi_ble_event_disconnection_status {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT08  Type;
} RSI_BLE_EVENT_DISCONNECTION_STATUS  ;

/*
MTU Size Event
-----------------------

Event Index: RSI_BLE_EVENT_MTU_SIZE

Arguments:
1. BD Address (6B)
2. MTU Size   (2B)
*/
typedef struct rsi_ble_event_mtu_size {
    UINT08  BDAddress[RSI_BT_BD_ADDR_LEN];
    UINT08  MTU_size[2];
} RSI_BLE_EVENT_MTU_SIZE  ;

/*
Encryption Enabled
------------------------------------

Event Index: RSI_BLE_EVENT_ENCRYPT_ENABLED

Arguments:
No Arguments.
*/



/*
SMP Request
-----------

Event Index: RSI_BLE_EVENT_SMP_REQUEST

Arguments:
1. BD Address.
*/

typedef struct rsi_bt_event_smp_req {
    UINT08  BDAddress[6];
} RSI_BT_EVENT_SMP_REQ;



/*
SMP Response
------------

Event Index: RSI_BLE_EVENT_SMP_RESPONSE

Arguments:
1. BD Address.
*/

typedef struct rsi_bt_event_smp_resp {
    UINT08  BDAddress[6];
} RSI_BT_EVENT_SMP_RESP;


/*
SMP Passkey
-----------

Event Index: RSI_BLE_EVENT_SMP_PASSKEY

Arguments:
1. BD Address.
*/

typedef struct rsi_bt_event_smp_passkey {
    UINT08  BDAddress[6];
} RSI_BT_EVENT_SMP_PASSKEY;


/*
SMP Passkey
-----------

Event Index: RSI_BT_EVENT_SMP_PASSKEY_DISPLAY

Arguments:
1. BD Address(6B)
2. Reserved(2B)
3. Passkey(4B)
*/
typedef struct rsi_bt_event_smp_passkey_display {
    UINT08  BDAddress[6];                                 /* BD address of the remote device  (6  Bytes) */
    UINT08  PasskeyStr[6];                                /* SMP passkey to be displayed */
} RSI_BT_EVENT_SMP_PASSKEY_DISPLAY;


/*
SMP Failed
----------

Event Index: RSI_BLE_EVENT_SMP_FAILED

Arguments:
1. BD Address.
*/

typedef struct rsi_bt_event_smp_failed {
    UINT08  BDAddress[6];
} RSI_BT_EVENT_SMP_FAILED;



/*
GATT Characteristic Value Notification
--------------------------------------

Event Index: RSI_BLE_EVENT_GATT_NOTIFICATION

Arguments:
1. BD Address
2. Handle (2B)
3. Length (1B)
4. Value[50] (1B)
*/
typedef struct rsi_ble_event_gatt_char_value_notifications {
    UINT08  BDAddress[6];
    UINT08  Handle[2];
    UINT08  Length;
    UINT08  Value[50];
} RSI_BLE_EVENT_GATT_CHAR_VALUE_NOTIFICATIONS  ;


/*
GATT Characteristic Value Indication
------------------------------------

Event Index: RSI_BLE_EVENT_GATT_INDICATION

Arguments:
1. BDAddress (6B)
2. Handle (2B)
3. Length (1B)
4. Value[50] (1B each)
*/
typedef struct rsi_ble_event_gatt_char_value_indication {
    UINT08  BDAddress[6];
    UINT08  Handle[2];
    UINT08  Length;
    UINT08  Value[50];
} RSI_BLE_EVENT_GATT_CHAR_VALUE_INDICATION  ;


/*
GATT Characteristic Value write event
--------------------------------------

Event Index: RSI_BLE_EVENT_GATT_WRITE_VALUE

Arguments:
1. BD Address
2. Handle (2B)
3. Length (1B)
4. Value[50] (1B)
*/
typedef struct rsi_ble_event_gatt_write {
    UINT08  BDAddress[6];
    UINT08  Handle[2];
    UINT08  Length;
    UINT08  Value[50];
} RSI_BLE_EVENT_GATT_WRITE  ;

/*
PXP link loss service alert level
------------------------------------

Event Index: RSI_BLE_EVENT_PXPR_LINK_LOSS_ALERT

Arguments:
1. Link Loss Alert Level(1B)
*/
typedef struct rsi_ble_event_pxp_linkloss {
    UINT08  LinkLossAlert;
} RSI_BLE_EVENT_PXP_LINKLOSS  ;

/*
PXP Immediate alert level
------------------------------------

Event Index: RSI_BLE_EVENT_PXPR_IMMEDIATE_ALERT

Arguments:
1. Immediate Alert Level(1B)
*/
typedef struct rsi_ble_event_pxp_imm_alert {
    UINT08  ImmAlert;
} RSI_BLE_EVENT_PXP_IMM_ALERT  ;

/*
PXP Link loss alert event
------------------------------------

Event Index: RSI_BLE_EVENT_PXPR_LINK_IS_LOST

Arguments:
No Arguments.
*/


typedef union{

  RSI_BT_CMD_SET_LOCAL_NAME                uSetLocalName;
  RSI_BT_CMD_SET_LOCAL_COD                 uSetLocalCOD; 
  RSI_BT_CMD_QUERY_RSSI                    uQryRssi;
  RSI_BT_CMD_QUERY_LINK_QUALITY            uQryLinkQuality;             
  RSI_BT_CMD_ANTENNA_SELECT                uAntennaSelect;


  RSI_BLE_CMD_ADVERTISE                    uLeAdvertise;
  RSI_BLE_CMD_SCAN                         uLeScan;
  RSI_BLE_CMD_CONNECT                      uLeConnect;
  RSI_BLE_CMD_DISCONNECT                   uLeDisConnect;

  RSI_BLE_CMD_ENCRYPTTION                  uLeSmpEncrypt;
  RSI_BLE_CMD_SMP_PAIR_REQUEST             uLeSmpReq;
  RSI_BLE_CMD_SMP_RESPONSE                 uLeSmpResp;
  RSI_BLE_CMD_SMP_PASSKEY                  uLeSmppasskey;
  RSI_BLE_CMD_SET_PING_TIMEOUT             uLeSetPingTimeout;
  RSI_BLE_CMD_SET_ADVERTISE_DATA           uLeSetAdvertiseData;
  
  RSI_BLE_CMD_PROFILE_LIST                   uLeAllServ;
  RSI_BLE_CMD_QUERY_PROFILE                  uLeSev;
  RSI_BLE_CMD_QUERY_CHARACTERISTIC_SERVICES  uLeCharServ;
  RSI_BLE_CMD_QUERY_INCLUDE_SERVICES         uLeIncServ;
  RSI_BLE_CMD_READ_CHAR_VALUE_BY_UUID        uLeCharVal;
  RSI_BLE_CMD_QUERY_ATT_DESC                 uLeAttDesc;
  RSI_BLE_CMD_QUERY_ATT_VALUE                uLeAttVal;
  RSI_BLE_CMD_QUERY_MULTIPLE_ATT_VALUES      uLeMulAttVals;
  RSI_BLE_CMD_QUERY_LONG_ATT_VALUE           uLeLongAttVal;
  RSI_BLE_CMD_SET_ATT_VALUE                  uLeSetAttVal;
  RSI_BLE_CMD_SET_ATT_VALUE_NO_ACK           uLeSetCmdAttVal;
  RSI_BLE_CMD_SET_LONG_ATT_VALUE             uLeSetLongAttVal;
  RSI_BLE_CMD_SET_PREPARE_LONG_ATT_VALUE     uLePrepareAttVal;
  RSI_BLE_CMD_EXECUTE_LONG_ATT_VALUE_WRITE   uLeExecuteWrite;
  RSI_BLE_CMD_ADD_GATT_SERVICE               uLeAddService;
  RSI_BLE_CMD_ADD_GATT_ATTRIBUTE             uLeAddAttribute;
  RSI_BLE_CMD_SET_LOCAL_ATT_VALUE            uLeSetLocalAttValue;
  RSI_BLE_CMD_GET_LOCAL_ATT_VALUE            uLeGetLocalAttValue;
  RSI_BLE_CMD_SET_RANDOM_ADDRESS             uLeRandAdd;
  RSI_BLE_CMD_SET_ANTENNA_TX_POWER_VLAUE     uLeAntennaTxPower;
  RSI_BLE_CMD_WHITE_LIST                     uLeWhiteList;

}RSI_BLE_API;

typedef struct rsi_ble_response{
  UINT08   ResponseCode[2];
  UINT08   Status[2];                 
  union {

    RSI_BT_RESP_QUERY_LOCAL_NAME                uQryLocalName;
    RSI_BT_RESP_QUERY_LOCAL_COD                 uQryLocalCOD;       
    RSI_BT_RESP_QUERY_RSSI                      uQryRssi;           
    RSI_BT_RESP_QUERY_LINK_QUALITY              uQryLinkQuality;    
    RSI_BT_RESP_QUERY_LOCAL_BD_ADDRESS          uQryLocalBDAddr;    


    RSI_BLE_RESP_QUERY_DEVICE_STATE             uQryDevState;
    RSI_BLE_RESP_QUERY_PROFILES_LIST            uQryProfList;
    RSI_BLE_RESP_QUERY_PROFILE_DESCRIPTOR       uQryProf;
    RSI_BLE_RESP_QUERY_CHARACTERISTIC_SERVICES  uQryCharServ;
    RSI_BLE_RESP_QUERY_INCLUDE_SERVICE          uQryIncServ;
    RSI_BLE_RESP_READ_CHAR_VALUE_BY_UUID        uQryCharVal;
    RSI_BLE_RESP_QUERY_ATT_DESC                 uQryDescList;
    RSI_BLE_RESP_QUERY_ATT_VALUE                uQryAttVal;
    RSI_BLE_RESP_QUERY_MULTIPLE_ATT_VALUES      uQryAttVals;
    RSI_BLE_RESP_QUERY_LONG_ATT_VALUE           uQryLongAttVal;
    RSI_BLE_RESP_ADD_GATT_SERVICE               uQryAddService;

	RSI_BLE_EVENT_RESP_ADVERTISE_REPORT		    uAdvReport;
	RSI_BLE_EVENT_RESP_CONNECTION_STATUS		uConnStatus;
	RSI_BLE_EVENT_MTU_SIZE	                 	uMTUSize;
	RSI_BLE_EVENT_GATT_CHAR_VALUE_NOTIFICATIONS	uNotifications;
	RSI_BLE_EVENT_GATT_CHAR_VALUE_INDICATION	uIndication;
	//RSI_BLE_EVENT_PXP_LINKLOSS					uLinkLoss;
	//RSI_BLE_EVENT_PXP_IMM_ALERT					uImmAlert;
    RSI_BLE_RESP_GET_PING_TIMEOUT               uGetPingTimeout;
    UINT08                                      uCmdRspBuf[RSI_BT_FRAME_CMD_RSP_LEN + RSI_BT_MAX_PAYLOAD_SIZE + 100];
  }uCmdRspPayLoad;

} RSI_BLE_RESPONSE;

extern const UINT08  rsi_frameCmdLEAdv[RSI_BYTES_4];                
extern const UINT08  rsi_frameCmdLEScan[RSI_BYTES_4];               
extern const UINT08  rsi_frameCmdLEConn[RSI_BYTES_4];               
extern const UINT08  rsi_frameCmdLEDisconn[RSI_BYTES_4];             
extern const UINT08  rsi_frameCmdQryDevstate[RSI_BYTES_4];          
extern const UINT08  rsi_frameCmdHciParams[RSI_BYTES_4];            
extern const UINT08  rsi_frameCmdStartEnc[RSI_BYTES_4];             
extern const UINT08  rsi_frameCmdSMPPairReq[RSI_BYTES_4];           
extern const UINT08  rsi_frameCmdSMPResp[RSI_BYTES_4];              
extern const UINT08  rsi_frameCmdSMPPasskey[RSI_BYTES_4];           

extern const UINT08  rsi_frameCmdSetPingTimeout[RSI_BYTES_4];       
extern const UINT08  rsi_frameCmdGetPingTimeout[RSI_BYTES_4];
extern const UINT08  rsi_frameCmdSetAdvertiseData[RSI_BYTES_4];

extern const UINT08  rsi_frameCmdQryProfList[RSI_BYTES_4];          
extern const UINT08  rsi_frameCmdQryProfDesc[RSI_BYTES_4];          
extern const UINT08  rsi_frameCmdQryCharServ[RSI_BYTES_4];          
extern const UINT08  rsi_frameCmdQryIncludeServ[RSI_BYTES_4];       
extern const UINT08  rsi_frameCmdReadCharValByUUID[RSI_BYTES_4];    
extern const UINT08  rsi_frameCmdQryAtt[RSI_BYTES_4];               
extern const UINT08  rsi_frameCmdQryAttVal[RSI_BYTES_4];            
extern const UINT08  rsi_frameCmdQryMulAttVal[RSI_BYTES_4];         
extern const UINT08  rsi_frameCmdQryLongAttVal[RSI_BYTES_4];        
extern const UINT08  rsi_frameCmdSetAttVal[RSI_BYTES_4];            
extern const UINT08  rsi_frameCmdSetAttValNoAck[RSI_BYTES_4];       
extern const UINT08  rsi_frameCmdSetLongAttVal[RSI_BYTES_4];        
extern const UINT08  rsi_frameCmdSetPrepLongAttVal[RSI_BYTES_4];    
extern const UINT08  rsi_frameCmdExeLongAttVal[RSI_BYTES_4];        


extern const UINT08  rsi_frameCmdBTAntennaSelect[RSI_BYTES_4];

//extern const UINT08  rsi_frameCmdBTLinkkeyReply[RSI_BYTES_4];
extern const UINT08  rsi_frameCmdBleAddService[RSI_BYTES_4];
extern const UINT08  rsi_frameCmdBleAddAttribute[RSI_BYTES_4];
extern const UINT08  rsi_frameCmdBleSetLocalAttValue[RSI_BYTES_4];
extern const UINT08  rsi_frameCmdBleGetLocalAttValue[RSI_BYTES_4];


extern const UINT08  rsi_frameCmdSetRandAdd[RSI_BYTES_4];
extern const UINT08  rsi_frameCmdSetTxPowerValue[RSI_BYTES_4];
extern const UINT08  rsi_frameCmdBleWhiteList[RSI_BYTES_4];
#ifdef __cplusplus
}
#endif

#endif
