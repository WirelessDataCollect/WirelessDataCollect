/**
 * @file           rsi_bt_config.h
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
 * @brief BT CONFIG INIT Contains the default configurations used in the BT API's.
 *
 * @section Description
 * USER is supposed to configure the module/API's  by using the following defines.
 *
 *
 */


#ifndef _BT_INITSTRUCT_H_
#define _BT_INITSTRUCT_H_


#include "rsi_bt_api.h"

/*==============================================*/
/**
 * Global Defines
 */
#define RSI_BT_REMOTE_BD_ADDRESS             "00:15:83:6A:64:17"  //"E4:92:FB:F7:28:BA"//"90:68:C3:3C:E7:EA" //"D0:C1:B1:AF:68:CA"//  0 //"11:22:33:44:55:66"

#define RSI_BT_SET_LOCAL_NAME                "REDPINE-BT"
#define RSI_BT_SET_LOCAL_COD                 1000 
#define RSI_BT_QUERY_RSSI_ADDR               RSI_BT_REMOTE_BD_ADDRESS
#define RSI_BT_QUERY_LINK_QUALITY_ADDR       RSI_BT_REMOTE_BD_ADDRESS 
#define RSI_BT_SET_DISC_MODE                 1 
#define RSI_BT_SET_DISC_MODE_TIMEOUT         1000 
#define RSI_BT_SET_CONN_MODE                 1
#define RSI_BT_SET_PAIR_MODE                 1
#define RSI_BT_REM_NAME_REQ_ADDR             RSI_BT_REMOTE_BD_ADDRESS   
#define RSI_BT_REM_NAME_REQ_CANCEL_ADDR      RSI_BT_REMOTE_BD_ADDRESS
#define RSI_BT_INQ_TYPE                      1
#define RSI_BT_INQ_DURATION                  10000       
#define RSI_BT_INQ_MAX_DEVICES               10
#define RSI_BT_BOND_ADDR                     RSI_BT_REMOTE_BD_ADDRESS
#define RSI_BT_BOND_CANCEL_ADDR              RSI_BT_REMOTE_BD_ADDRESS
#define RSI_BT_UNBOND_ADDR                   RSI_BT_REMOTE_BD_ADDRESS
#define RSI_BT_SET_PIN_TYPE                  1
#define RSI_BT_USER_CONF_ADDR                RSI_BT_REMOTE_BD_ADDRESS
#define RSI_BT_USER_CONF                     1
#define RSI_BT_PASSKEY_ADDR                  RSI_BT_REMOTE_BD_ADDRESS
#define RSI_BT_PASSKEY_REPLY_TYPE            1
#define RSI_BT_PASSKEY                       1234
#define RSI_BT_PINCODE_REPLY_ADDR            RSI_BT_REMOTE_BD_ADDRESS
#define RSI_BT_PINCODE_REPLY_TYPE            1
#define RSI_BT_LINKKEY_REPLY_ADDR            RSI_BT_REMOTE_BD_ADDRESS
#define RSI_BT_LINKKEY_REPLY_TYPE            0
#define RSI_BT_PINCODE                       "1234"
#define RSI_BT_QUERY_ROLE_ADDR               RSI_BT_REMOTE_BD_ADDRESS
#define RSI_BT_SET_ROLE_ADDR                 RSI_BT_REMOTE_BD_ADDRESS
#define RSI_BT_SET_ROLE                      1

#define RSI_BT_SPP_CONN_ADDR                 RSI_BT_REMOTE_BD_ADDRESS
#define RSI_BT_SPP_DISCONN_ADDR              RSI_BT_REMOTE_BD_ADDRESS


#define RSI_BT_QUERY_SERV_ADDR               RSI_BT_REMOTE_BD_ADDRESS
#define RSI_BT_SEARCH_SERV_ADDR              RSI_BT_REMOTE_BD_ADDRESS
#define RSI_BT_SEARCH_SERV_SIZE              2
#define RSI_BT_SEARCH_SERV_UUID              0x1105

extern UINT08  rsi_bt_TransferBuffer[RSI_BT_MAX_PAYLOAD_SIZE]; //{"0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"};
#define RSI_BT_SPP_TX_LEN                    (UINT16)(sizeof(rsi_bt_TransferBuffer))
#define RSI_BT_SPP_TX_DATA                   rsi_bt_TransferBuffer 


//PER commands
#define  BT_PER_TRANSMIT_MODE               1
#define  BT_PER_RECEIVE_MODE                2
#define  BT_PER_CW_MODE                     3
#define  BT_PER_MODE                        BT_PER_CW_MODE              


/*PER TRANSMIT PACKET PARAMETERS*/
#define RSI_BT_PER_TX_ENABLE                 1
#define RSI_BT_PER_TX_MAC_ADD                "00:23:A7:11:22:33"
#define RSI_BT_PER_TX_PKT_TYPE               15                       

#define RSI_BT_PER_TX_PKT_LENGTH             339                     
#define RSI_BT_PER_TX_LINK_TYPE              1      /* 0 - SCO, 1 - ACL, 2 - ESCO */                       
#define RSI_BT_PER_TX_EDR_INDICATION         1      /* 1 - Basic Rate, 2 or 3 - Enhanced Data Rate */                
#define RSI_BT_PER_TX_RX_CHANNEL             0 
#define RSI_BT_PER_TX_TX_CHANNEL             0      
#define RSI_BT_PER_TX_SCRAMBLED_SEED         0               
#define RSI_BT_PER_TX_NUM_PKTS               1
#define RSI_BT_PER_TX_PAYLOAD_TYPE           4
#define RSI_BT_PER_TX_PROTOCOL_MODE          1
#define RSI_BT_PER_TX_LE_CHANNEL             11
#define RSI_BT_PER_TX_POWER_INDEX            16
#define RSI_BT_PER_TX_MODE                   1                        //0-Burst,1-Continous

#define RSI_BT_PER_TX_FREQUENCY_HOP          0
#define RSI_BT_PER_TX_ANT_SEL                3


/*PER RECEIVE PACKET PARAMETERS*/

#define RSI_BT_PER_RX_ENABLE                 1
#define RSI_BT_PER_RX_MAC_ADD                "00:00:12:34:56:78"
#define RSI_BT_PER_RX_PKT_TYPE               14
#define RSI_BT_PER_RX_PKT_LENGTH             679
#define RSI_BT_PER_RX_LINK_TYPE              1
#define RSI_BT_PER_RX_EDR_INDICATION         2
#define RSI_BT_PER_RX_RX_CHANNEL             78
#define RSI_BT_PER_RX_TX_CHANNEL             11
#define RSI_BT_PER_RX_SCRAMBLED_SEED         0
#define RSI_BT_PER_RX_PROTOCOL_MODE          1
#define RSI_BT_PER_RX_PAYLOAD_TYPE           1
#define RSI_BT_PER_RX_LE_CHANNEL             11
#define RSI_BT_PER_RX_FREQUENCY_HOP          0
#define RSI_BT_PER_RX_ANT_SEL                3

/* sniff parameters */
//! Sniff Parameters
#define RSI_BT_SNIFF_BD_ADDR                 RSI_BT_REMOTE_BD_ADDRESS
#define RSI_BT_SNIFF_MAX_INTERVAL            0xC0 
#define RSI_BT_SNIFF_MIN_INTERVAL            0XC0
#define RSI_BT_SNIFF_ATTEMPT                 0X04
#define RSI_BT_SNIFF_TIME_OUT                0X02

//SSP defines
#define RSI_BT_SPP_MODE                      1 //1 -Enable, 0-disable
#define RSI_BT_IO_CAPABILITY                 1 //0 - display only,
                                               //1 - display yes/no
                                               //2 - keyboard only
                                               //3 - no input, no output
                                               
//Feature Bitmap defines
#define RSI_BT_SECURITY_BIT                  0
#define RSI_BT_FEATURE_BITMAP                (1 << RSI_BT_SECURITY_BIT)


/* CW MODE configuration */
#define RSI_CW_MODE_CHANNEL                  78
#define RSI_CW_MODE                          0    //0-Start 2-Stop
#define RSI_CW_ANT_SEL                       2

/*  Antenna Tx Power Level */
#define RSI_BT_TX_POWER                      10 

extern UINT08  rsi_bt_EIRDataBuffer[RSI_BT_MAX_PAYLOAD_SIZE];// = {"21659RAVI"}; 
#define RSI_BT_EIR_DATA_LENGTH               (UINT16)(sizeof(rsi_bt_EIRDataBuffer))      
#define RSI_BT_EIR_DATA                      rsi_bt_EIRDataBuffer

#define RSI_BT_MENU_SKIP


#define RSI_BT_DEVICE_IS_MASTER                 1
#define RSI_BT_DEVICE_IS_SLAVE                  (~RSI_BT_DEVICE_IS_MASTER)

#define RSI_BT_CHECK_REMOTE_SERVICES            0
#define RSI_BT_SEARCH_FOR_SERVICE               0

#define RSI_BT_DEV_IS_SCAN_ENABLE               0


/*! Serial Port Profile (SPP) */
#define RSI_BT_DEVICE_SPP_IS_ENABLE             1

#if RSI_BT_DEVICE_SPP_IS_ENABLE
#define RSI_BT_DEVICE_SPP_PROFILE_NUMBER        1    
#else
#define RSI_BT_DEVICE_SPP_PROFILE_NUMBER        0
#endif

#define RSI_BT_DEVICE_SPP_DATA_TRANSFER         (1 && RSI_BT_DEVICE_SPP_IS_ENABLE)
#define RSI_BT_DEVICE_SPP_DATA_RECEIVE          (1 && RSI_BT_DEVICE_SPP_IS_ENABLE)
#define RSI_BT_DEVICE_SPP_UUID        

#define RSI_BT_DO_SPP_TRANSFER					1 //set to 1 to continously transfer SPP data from module
#define RSI_BT_DO_SPP_TRANSFER_ON_RX			0 //send spp data on recepetion of spp data


#define RSI_BT_SET_PROFILE_MODE                 RSI_BT_DEVICE_SPP_PROFILE_NUMBER



INT16 rsi_bt_init_struct(UINT16  CommandType);






























#endif
