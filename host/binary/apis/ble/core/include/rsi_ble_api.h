/**
 * @file     rsi_ble_api.h
 * @version  1.0
 * @date     2014-Aug-21
 *
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief HEADER: API specific Defines
 *
 * @section Description
 * This file contains the function prototypes of the APIs defined in library. 
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 */

#ifndef _BLEAPI_H_
#define _BLEPI_H_

/**
 * Include Files
 */
#include "rsi_ble_global.h"
#include "rsi_bt_generic.h"


#define  BLEPI_H_EXTERN  extern


#ifdef __cplusplus
extern "C"{
#endif


#define  MAX_NBR_OF_REMOET_DEVS    5
#define  SIZE_OF_BDADDR            6
BLEPI_H_EXTERN  UINT08  remote_dev_list[MAX_NBR_OF_REMOET_DEVS][SIZE_OF_BDADDR];
BLEPI_H_EXTERN  UINT08  remote_dev_count;

BLEPI_H_EXTERN  UINT08  connected_dev_list[MAX_NBR_OF_REMOET_DEVS][SIZE_OF_BDADDR];
BLEPI_H_EXTERN  UINT08  connected_dev_count;


/* Core commands */
#define  RSI_BLE_REQ_ADVERTISE                            0x0075
#define  RSI_BLE_REQ_SCAN                                 0x0076                               
#define  RSI_BLE_REQ_CONNECT                              0x0077                       
#define  RSI_BLE_REQ_DISCONNECT                           0x0078                 
#define  RSI_BLE_REQ_QUERY_DEVICE_STATE                   0x0079               

/* SMP commands */
#define  RSI_BLE_REQ_START_ENCRYPTION                     0x007B             
#define  RSI_BLE_REQ_SMP_PAIR_REQUEST                     0x007C       
#define  RSI_BLE_REQ_SMP_RESPONSE                         0x007D                         
#define  RSI_BLE_REQ_SMP_PASSKEY                          0x007E                                   

/* GATT commands */
#define  RSI_BLE_REQ_QUERY_PROFILES_LIST                  0x007F                 
#define  RSI_BLE_REQ_QUERY_PROFILE                        0x0080                       
#define  RSI_BLE_REQ_QUERY_CHARACTERISTIC_SERVICES        0x0081                          
#define  RSI_BLE_REQ_QUERY_INCLUDE_SERVICES               0x0082                   
#define  RSI_BLE_REQ_READ_CHAR_VALUE_BY_UUID              0x0083                   
#define  RSI_BLE_REQ_QUERY_ATT_DESC                       0x0084                     
#define  RSI_BLE_REQ_QUERY_ATT_VALUE                      0x0085                     
#define  RSI_BLE_REQ_QUERY_MULTIPLE_ATT_VALUES            0x0086                 
#define  RSI_BLE_REQ_QUERY_LONG_ATT_VALUE                 0x0087                       
#define  RSI_BLE_REQ_SET_ATT_VALUE                        0x0088                   
#define  RSI_BLE_REQ_SET_ATT_VALUE_NO_ACK                 0x0089                               
#define  RSI_BLE_REQ_SET_LONG_ATT_VALUE                   0x008A                                   
#define  RSI_BLE_REQ_SET_PREPARE_LONG_ATT_VALUE           0x008B                     
#define  RSI_BLE_REQ_EXECUTE_LONG_ATT_VALUE_WRITE         0x008C              
#define  RSI_BLE_REQ_ANTENNA_SELECT                       0x008F
#define  RSI_BLE_REQ_CONFIG_ENABLE                        0x0090
//#define  RSI_BLE_REQ_LINKKEY_REPLY                        0x0091
#define  RSI_BLE_REQ_ADD_SERVICE                          0x0092
#define  RSI_BLE_REQ_ADD_ATTRIBUTE                        0x0093
#define  RSI_BLE_REQ_SET_LOCAL_ATT_VALUE                  0x0094
#define  RSI_BLE_REQ_GET_LOCAL_ATT_VALUE                  0x0095

#define  RSI_BLE_REQ_ADD_LINKLOSS_SERVICE                 0x0150
#define  RSI_BLE_REQ_ADD_LINKLOSS_ATT1                    0x0151
#define  RSI_BLE_REQ_ADD_LINKLOSS_ATT2                    0x0152
#define  RSI_BLE_REQ_ADD_LINKLOSS_ATT3                    0x0153

#define  RSI_BLE_REQ_ADD_IMMEDIATE_SERVICE		 	          0x0154
#define  RSI_BLE_REQ_ADD_IMMEDIATE_ATT1                   0x0155
#define  RSI_BLE_REQ_ADD_IMMEDIATE_ATT2                   0x0156

#define  RSI_BLE_REQ_SET_LOCAL_ATT_VALUE_ID               0x0157
#define  RSI_BLE_REQ_GET_LOCAL_ATT_VALUE_ID               0x0158

#define  RSI_BLE_REQ_SET_ADVERTISE_DATA                   0x0159
#define  RSI_BLE_REQ_SET_LE_PING_TIMEOUT                  0x015A
#define  RSI_BLE_REQ_GET_LE_PING_TIMEOUT                  0x015B
#define  RSI_BLE_REQ_SET_RANDOM_ADDRESS                   0x015C
#define  RSI_BLE_SET_ANTENNA_TX_POWER_LEVEL               0x015D

#define  RSI_BLE_REQ_ADD_RSI_SERVICE                      0x0160
#define  RSI_BLE_REQ_ADD_RSI_ATT1                         0x0161
#define  RSI_BLE_REQ_ADD_RSI_ATT2                         0x0162
#define  RSI_BLE_REQ_ADD_RSI_ATT3                         0x0163
#define  RSI_BLE_REQ_ADD_RSI_ATT4                         0x0164
#define  RSI_BLE_REQ_ADD_RSI_ATT5                         0x0165

#define  RSI_BLE_REQ_GET_RSI_ATT4                         0x0166
#define  RSI_BLE_REQ_SET_RSI_ATT4                         0x0167

#define  RSI_BLE_ADD_WHITELIST                            0x0168 
#define  RSI_BLE_DELETE_WHITELIST                         0x0169
#define  RSI_BLE_CLEARALL_WHITELIST                       0x016A
//! BLE Response Frame Codes
#define  RSI_BLE_RSP_ADVERTISE                            0x0075 
#define  RSI_BLE_RSP_SCAN                                 0x0076                               
#define  RSI_BLE_RSP_CONNECT                              0x0077                       
#define  RSI_BLE_RSP_DISCONNECT                           0x0078                 
#define  RSI_BLE_RSP_QUERY_DEVICE_STATE                   0x0079               
#define  RSI_BLE_RSP_START_ENCRYPTION                     0x007B             
#define  RSI_BLE_RSP_SMP_PAIR_REQUEST                     0x007C       
#define  RSI_BLE_RSP_SMP_RESPONSE                         0x007D                         
#define  RSI_BLE_RSP_SMP_PASSKEY                          0x007E                                   
#define  RSI_BLE_RSP_QUERY_PROFILES_LIST                  0x007F                 
#define  RSI_BLE_RSP_QUERY_PROFILE                        0x0080                       
#define  RSI_BLE_RSP_QUERY_CHARACTERISTIC_SERVICES        0x0081                          
#define  RSI_BLE_RSP_QUERY_INCLUDE_SERVICES               0x0082                   
#define  RSI_BLE_RSP_READ_CHAR_VALUE_BY_UUID              0x0083                   
#define  RSI_BLE_RSP_QUERY_ATT_DESC                       0x0084                     
#define  RSI_BLE_RSP_QUERY_ATT_VALUE                      0x0085                     
#define  RSI_BLE_RSP_QUERY_MULTIPLE_ATT_VALUES            0x0086                 
#define  RSI_BLE_RSP_QUERY_LONG_ATT_VALUE                 0x0087                       
#define  RSI_BLE_RSP_SET_ATT_VALUE                        0x0088                   
#define  RSI_BLE_RSP_SET_ATT_VALUE_NO_ACK                 0x0089                               
#define  RSI_BLE_RSP_SET_LONG_ATT_VALUE                   0x008A                                   
#define  RSI_BLE_RSP_SET_PREPARE_LONG_ATT_VALUE           0x008B                     
#define  RSI_BLE_RSP_EXECUTE_LONG_ATT_VALUE_WRITE         0x008C     
#define  RSI_BLE_RSP_ANTENNA_SELECT                       0x008F
#define  RSI_BLE_RSP_CONFIG_ENABLE                        0x0090
#define  RSI_BLE_RSP_LINKKEY_REPLY                        0x0091
#define  RSI_BLE_RSP_ADD_SERVICE                          0x0092
#define  RSI_BLE_RSP_ADD_ATTRIBUTE                        0x0093
#define  RSI_BLE_RSP_SET_LOCAL_ATT_VALUE                  0x0094
#define  RSI_BLE_RSP_GET_LOCAL_ATT_VALUE                  0x0095

#define  RSI_BLE_RSP_SET_ADVERTISE_DATA                   0x009C
#define  RSI_BLE_RSP_GET_LE_PING_TIMEOUT                  0x00A1
#define  RSI_BLE_RSP_SET_LE_PING_TIMEOUT                  0x00A2
#define  RSI_BLE_RSP_ANTENNA_TX_POWER_LEVEL               0x00A7
#define  RSI_BLE_RSP_WHITE_LIST                           0x00AA

//! BLE Event Frames
#define  RSI_BLE_EVENT_ADVERTISE_REPORT                   0x150E
#define  RSI_BLE_EVENT_CONNECTION_STATUS                  0x150F

#define  RSI_BLE_EVENT_SMP_REQUEST                        0x1510
#define  RSI_BLE_EVENT_SMP_RESPONSE                       0x1511
#define  RSI_BLE_EVENT_SMP_PASSKEY                        0x1512
#define  RSI_BLE_EVENT_SMP_FAILED                         0x1513

//! BLE GATT Profile Event Frames
#define  RSI_BLE_EVENT_GATT_NOTIFICATION                  0x1514
#define  RSI_BLE_EVENT_GATT_INDICATION                    0x1515

#define  RSI_BLE_EVENT_ENCRYPT_ENABLED                    0x1516
#define  RSI_BLE_EVENT_GATT_WRITE_VALUE                   0x1517
#define  RSI_BLE_EVENT_MTU_SIZE_VALUE                     0x151C
#define  RSI_BLE_EVENT_SMP_PASSKEY_DISPLAY                0x151D

//! BLE Proximity Profile Event Frames
#define  RSI_BLE_EVENT_PXPR_LINK_LOSS_ALERT               0x1520
#define  RSI_BLE_EVENT_PXPR_IMMEDIATE_ALERT               0x1521
#define  RSI_BLE_EVENT_PXPR_LINK_IS_LOST                  0x1522
#define BLE_CLEARALL_ENTRYS_FROM_WHITELIST         0x00 
#define BLE_ADD_ENTRY_TO_WHITE_LIST                0x01
#define BLE_DELETE_ENTRY_FROM_WHITE_LIST           0x02
/* IOCapability for SMP*/
#define DISPLAY_ONLY                     0
#define KEYBOARD_AND_DISPLAY             1


/*
 * BLE Core Function Prototype Definitions
 */

INT16 rsi_ble_advertise(RSI_BLE_CMD_ADVERTISE *LEAdv);
INT16 rsi_ble_scan(RSI_BLE_CMD_SCAN *LEScan);
INT16 rsi_ble_connect(RSI_BLE_CMD_CONNECT *LEConn);
INT16 rsi_ble_disconnect(RSI_BLE_CMD_DISCONNECT  *uLEDisconnect);
INT16 rsi_ble_query_device_state(void);
INT16 rsi_ble_start_encryption(RSI_BLE_CMD_ENCRYPTTION  *uLEEncrypt);
INT16 rsi_ble_smp_pair_request(RSI_BLE_CMD_SMP_PAIR_REQUEST *SMPPairReq);
INT16 rsi_ble_smp_response(RSI_BLE_CMD_SMP_RESPONSE *SMPResp);
INT16 rsi_ble_smp_passkey(RSI_BLE_CMD_SMP_PASSKEY *SMPPasskey);

INT16 rsi_ble_set_advertise_data(RSI_BLE_CMD_SET_ADVERTISE_DATA *uSetadvertisedata);
INT16 rsi_ble_set_ping_timeout(RSI_BLE_CMD_SET_PING_TIMEOUT *uSetLePingTimeout);
INT16 rsi_ble_get_ping_timeout(void);

INT16 rsi_ble_set_random_address(RSI_BLE_CMD_SET_RANDOM_ADDRESS *uSetRandAdd);                            

/*
 * BLE GATT Profile Function Prototype Definitions
 */

INT16 rsi_ble_query_profiles_list(RSI_BLE_CMD_PROFILE_LIST  *uGetProfileList);
INT16 rsi_ble_query_profile(RSI_BLE_CMD_QUERY_PROFILE *GetProf);
INT16 rsi_ble_query_characteristic_services(RSI_BLE_CMD_QUERY_CHARACTERISTIC_SERVICES *GetCharServ);
INT16 rsi_ble_query_include_service(RSI_BLE_CMD_QUERY_INCLUDE_SERVICES *GetIncludeServ);
INT16 rsi_ble_read_char_value_by_UUID(RSI_BLE_CMD_READ_CHAR_VALUE_BY_UUID *ReadCharValByUUID);
INT16 rsi_ble_query_att(RSI_BLE_CMD_QUERY_ATT_DESC *GetAtt);
INT16 rsi_ble_query_att_value(RSI_BLE_CMD_QUERY_ATT_VALUE *GetAttVal);
INT16 rsi_ble_query_multi_att_values(RSI_BLE_CMD_QUERY_MULTIPLE_ATT_VALUES *GetMulAttVal);
INT16 rsi_ble_query_long_att_value(RSI_BLE_CMD_QUERY_LONG_ATT_VALUE *GetLongAttVal);
INT16 rsi_ble_set_att_value(RSI_BLE_CMD_SET_ATT_VALUE *SetAttVal);
INT16 rsi_ble_set_att_value_no_ack(RSI_BLE_CMD_SET_ATT_VALUE_NO_ACK *SetAttValNoAck);
INT16 rsi_ble_set_long_att_value(RSI_BLE_CMD_SET_LONG_ATT_VALUE *SetLongAttVal);
INT16 rsi_ble_set_prep_long_att_value(RSI_BLE_CMD_SET_PREPARE_LONG_ATT_VALUE *SetPrepLongAttVal);
INT16 rsi_ble_execute_long_att_value(RSI_BLE_CMD_EXECUTE_LONG_ATT_VALUE_WRITE *ExeLongAttVal);

/*
 * BT Generic commands
 */
INT16 rsi_bt_device_init(void);
INT16 rsi_bt_device_deinit(void);
INT16 rsi_bt_antenna_select(RSI_BT_CMD_ANTENNA_SELECT *uAntennaSelect);
INT16 rsi_ble_device_AddService(RSI_BLE_CMD_ADD_GATT_SERVICE *uLEAddService);
INT16 rsi_ble_device_AddServiceAttribute(RSI_BLE_CMD_ADD_GATT_ATTRIBUTE *uLEAddAttribute);
INT16 rsi_ble_device_ChangeLocalAttValue(RSI_BLE_CMD_SET_LOCAL_ATT_VALUE *uLEChangeAttVal);
INT16 rsi_ble_device_GetLocalAttValue(RSI_BLE_CMD_GET_LOCAL_ATT_VALUE *uLEGetAttVal);


void  clear_scan_resp (void);
void  update_scan_resp (UINT08  *p_resp_buf, UINT16   resp_len);
void  update_connected_devices (UINT08  *p_resp_buf, UINT16   resp_len);
void  remove_connected_devices (UINT08  *p_resp_buf, UINT16   resp_len);
INT08 GetScanDevIndex (void);
INT08 GetConnectedDevIndex (void);

INT16 ble_main(void);

#ifdef __cplusplus
}
#endif

#endif
