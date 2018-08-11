/**
 * @file           rsi_ble_config.h
 * @version        1.0
 * @date           2014-Aug-23
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief BLE CONFIG INIT Contains the default configurations used in the BLE API's.
 *
 * @section Description
 * USER is supposed to configure the module/API's  by using the following defines.
 *
 *
 */


#ifndef _BLEINITSTRUCT_H_
#define _BLEINITSTRUCT_H_


#include "rsi_bt_api.h"

/*==============================================*/
/**
 * Global Defines
 */
#ifndef RSI_BT_REMOTE_BD_ADDRESS
#define RSI_BT_REMOTE_BD_ADDRESS             0 //"11:22:33:44:55:66"
#endif

/**
 * Bluetooth Low Energy Global Defines
 **/

/* device modes */
#define  RSI_BLE_CENTRAL_MODE   1
#define  RSI_BLE_PERIPHERAL_MODE   2
#define  RSI_BT_DEVICE_MODE   RSI_BLE_CENTRAL_MODE

/* advertise status */
#define ADV_DISENABLE                                  0
#define ADV_ENABLE                                     1

/* advertise types */
#define UNDIR_CONN                                     0x80
#define DIR_CONN                                       0x81
#define UNDIR_SCAN                                     0x82
#define UNDIR_NON_CONN                                 0x83
#define DIR_CONN_LOW_DUTY_CYCLE                        0x84

#define ALLOW_SCAN_REQ_ANY_CONN_REQ_ANY                0
#define ALLOW_SCAN_REQ_WHITE_LIST_CONN_REQ_ANY         1
#define ALLOW_SCAN_REQ_ANY_CONN_REQ_WHITE_LIST         1
#define ALLOW_SCAN_REQ_WHITE_LIST_CONN_REQ_WHITE_LIST  2

/* advertiseing flags */
#define LE_LIMITED_DISCOVERABLE                       0x01
#define LE_GENERAL_DISCOVERABLE                       0x02
#define LE_BR_EDR_NOT_SUPPORTED                       0x04

#define RSI_BLE_ADV_STATUS             ADV_ENABLE      
#define RSI_BLE_ADV_TYPE               UNDIR_CONN
#define RSI_BLE_ADV_FILTER_TYPE        ALLOW_SCAN_REQ_ANY_CONN_REQ_ANY

/* scan paramters */
#define SCAN_DISENABLE                                  0
#define SCAN_ENABLE                                     1

#define SCAN_TYPE_PASSIVE                               0
#define SCAN_TYPE_ACTIVE                                1

#define SCAN_FILTER_TYPE_ALL                            0
#define SCAN_FILTER_TYPE_ONLY_WHITE_LIST                1

#define RSI_BLE_SCAN_STATUS                             SCAN_ENABLE
#define RSI_BLE_SCAN_TYPE                               SCAN_TYPE_ACTIVE
#define RSI_BLE_SCAN_FILTER_TYPE                        SCAN_FILTER_TYPE_ALL

/* address types */
#define LE_PUBLIC_ADDRESS       0
#define LE_RANDOM_ADDRESS       1

#define RSI_BLE_ADV_DIR_ADDR_TYPE   LE_PUBLIC_ADDRESS
#define RSI_BLE_ADV_DIR_ADDR        "00:15:83:6A:64:17"


#define RSI_BLE_CONN_ADDR_TYPE   LE_PUBLIC_ADDRESS
//#define RSI_BLE_CONN_ADDR        "C0:FF:EE:C0:FF:EE"
#define RSI_BLE_CONN_ADDR        0

/*  Antenna Tx Power Level For BLE mode */
#define RSI_BLE_TX_POWER                             8  

#define RSI_BLE_RAND_ADDR        "00:23:A7:11:22:33"
#define LE_SCAN_INTERVAL                             0x0100
#define LE_SCAN_WINDOW                               0x0050
#define CONNECTION_INTERVAL_MIN                      0x00A0
#define CONNECTION_INTERVAL_MAX                      0x00A0
#define CONNECTION_LATENCY                           0x0000
#define SUPERVISION_TIMEOUT                          0x07D0 


#define LE_PING_TIMEOUT                              0x1E

/* Add/delete device to/from white list */
#define RSI_BLE_WHITE_LIST_BDADDRESS                 "00:23:a7:80:50:22" 
#define RSI_BLE_WHITE_LIST_BDADDRESS_TYPE             0          // 0 - Public address, 1 - Random address

#define RSI_BLE_SMP_PAIR_REQ_IO_CAP  
#define RSI_BLE_SMP_PAIR_RESP_IO_CAP
#define RSI_BLE_SMP_PASS_KEY

#define RSI_BLE_SMP_IOCAPABILITY                   DISPLAY_ONLY   /* 0 - Display only, 1 - Keyboard and Display */

#define RSI_BLE_PROFILE_LIST_START_HANDLE                  0x0001
#define RSI_BLE_PROFILE_LIST_END_HANDLE                    0xFFFF

#define RSI_BLE_UUID_SIZE                               2
#define RSI_BLE_PROFILE_UUID                            0x1800

#define RSI_BLE_CHAR_SERV_START_HANDLE                  0x0001
#define RSI_BLE_CHAR_SERV_END_HANDLE                    0xFFFF

#define RSI_BLE_INC_SERV_START_HANDLE                   0x0001
#define RSI_BLE_INC_SERV_END_HANDLE                     0xFFFF

#define RSI_BLE_READ_CHAR_START_HANDLE                  0x0001
#define RSI_BLE_READ_CHAR_END_HANDLE                    0xFFFF
#define RSI_BLE_READ_CHAR_UUID                          0x2A00   // name of the device

#define RSI_BLE_ATT_START_HANDLE                        0x0001
#define RSI_BLE_ATT_END_HANDLE                          0x0005

#define RSI_BLE_ATT_VAL_HANDLE                          3

#define RSI_BLE_MUL_NBR_OF_ATT                          2
#define RSI_BLE_MUL_ATT_HANDLE1                         0x0002
#define RSI_BLE_MUL_ATT_HANDLE2                         0x0003

#define RSI_BLE_LONG_ATT_HANDLE                         0x0003
#define RSI_BLE_LONG_ATT_OFFSET                         0x0002

#define RSI_BLE_SET_ATT_HANDLE                          0x000C
#define RSI_BLE_SET_ATT_LEN                             0x01
#define RSI_BLE_SET_ATT_VAL                             0x01

#define RSI_BLE_SET_ATT_NO_ACK_HANDLE                   0x0034
#define RSI_BLE_SET_ATT_NO_ACK_LEN                      0x02
#define RSI_BLE_SET_ATT_NO_ACK_VAL                      0x0000

#define RSI_BLE_SET_LONG_ATT_HANDLE                     0x0034
#define RSI_BLE_SET_LONG_ATT_OFFSET                     0x00
#define RSI_BLE_SET_LONG_ATT_LEN                        0x02
#define RSI_BLE_SET_LONG_ATT_VAL                        0x0001

#define RSI_BLE_PREP_LONG_ATT_HANDLE                    0x0034
#define RSI_BLE_PREP_LONG_ATT_OFFSET                    0x00
#define RSI_BLE_PREP_LONG_ATT_LEN                       0x02
#define RSI_BLE_PREP_LONG_ATT_VAL                       0x0000

#define RSI_BLE_EXE_LONG_ATT_FLAG                       0x01


#define RSI_BT_ANTENNA_VALUE                            0x0       //0-Intenal, 1-External

#define  BT_LE_READ                                    0x02
#define  BT_LE_WRITE                                   0x08
#define  BT_LE_NOTIFY                                  0x10

#define  RSI_BLE_GATT_CHAR_SERVICE_UUID                 0x2803
#define  RSI_BLE_LINKLOSS_SERVICE_UUID                  0x1803
#define  RSI_BLE_IMMEDIATE_ALERT_SERVICE_UUID           0x1802
#define  RSI_BLE_GATT_ALERT_ATT_UUID                    0x2A06
#define  RSI_BLE_GATT_CLIENT_CHAR                       0x2902


#define  RSI_BLE_GATT_CHAR_SERVICE_UUID                 0x2803
#define  RSI_BLE_RSI_SERVICE_UUID                       0xAABB
#define  RSI_BLE_GATT_RSI1_ATT_UUID                     0x1AA1
#define  RSI_BLE_GATT_RSI2_ATT_UUID                     0x1BB1
#define  RSI_BLE_GATT_CLIENT_CHAR                       0x2902

#define  RSI_BLE_GATT_CHANGE_RSI_ATT_HANDLE             0x0E
#define  RSI_BLE_GATT_CHANGE_RSI_ATT_DATA_LEN           0x0F
#define  RSI_BLE_GATT_CHANGE_RSI_ATT_DATA              "Redpine_signals"


#define  RSI_BLE_GATT_CHANGE_ATT_HANDLE                 0x0C
#define  RSI_BLE_GATT_CHANGE_ATT_DATA_LEN               0x01
#define  RSI_BLE_GATT_CHANGE_ATT_DATA                   0x02


#define  RSI_BLE_GATT_GET_LOCAL_ATT_HANDLE              0x0C


#define RSI_BT_DEVICE_IS_MASTER                 1
#define RSI_BT_DEVICE_IS_SLAVE                  (~RSI_BT_DEVICE_IS_MASTER)

#define RSI_BT_CHECK_REMOTE_SERVICES            0
#define RSI_BT_SEARCH_FOR_SERVICE               0

#define RSI_BT_DEV_IS_SCAN_ENABLE               0

#define  RSI_BLE_ADVERTISE_INTERVAL_MIN                           0x800
#define  RSI_BLE_ADVERTISE_INTERVAL_MAX                           0x800
#define  RSI_BLE_ADVERTISE_CHANNEL_MAP                             0x07   //USING 37,38,39 CHANNELS.
#define  BT_LE_SCAN_FROM_ANY_CONN_FROM_ANY                          0
#define  BT_LE_SCAN_FROM_WHITE_LIST_CONN_FROM_ANY                   1
#define  BT_LE_SCAN_FROM_ANY_CONN_FROM_WHITE_LIST                   2
#define  BT_LE_SCAN_FROM_WHITE_LIST_CONN_FROM_WHITE_LIST            3
#define  RSI_BLE_OWN_ADDRESS_TYPE                            LE_PUBLIC_ADDRESS
INT16 rsi_ble_init_struct(UINT16  CommandType);


#endif
