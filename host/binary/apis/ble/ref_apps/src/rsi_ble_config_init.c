/**
 * @file       rsi_ble_config_init.c
 * @version    1.0
 * @date       2014-Sep-03
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief INIT STRUCT: Initializes the global parameter structure to the values in the #define statements in main.h
 *
 * @section Description
 * This file contains function to initialize the main structure which defines
 * system operation
 *
 *
 */

/**
 * Includes
 */
#include "rsi_ble_global.h"
#include "rsi_ble_api.h"
#include "rsi_ble_config.h"
#include "rsi_app_util.h"
#include "rsi_lib_util.h"
#include "rsi_bt_app.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
 * Proto types
 */
extern void rsi_asciiMacAddressTo6Bytesrev(UINT08 *hexAddr, INT08 *asciiMacAddress);

/**
 * Global Variables
 */
extern RSI_BT_APP_CB                   rsi_bt_AppControlBlock;
extern RSI_BLE_RESP_ADD_GATT_SERVICE   dbg_add_serv_resp;
extern RSI_BLE_RESP_ADD_GATT_SERVICE   dbg_add_serv_resp1;
UINT08  remote_dev_list[MAX_NBR_OF_REMOET_DEVS][SIZE_OF_BDADDR];
UINT08  remote_dev_count;

UINT08  connected_dev_list[MAX_NBR_OF_REMOET_DEVS][SIZE_OF_BDADDR];
UINT08  connected_dev_count;

UINT08 dbg_ix;

/*====================================================*/
/**
 * @fn             int16 rsi_ble_init_struct(rsi_api *ptrStrApi)
 * @brief          Initialize the global parameter structure
 * @param[in]      CommandType, type of the command
 * @param[out]     none
 * @return         status
 *                 0  = SUCCESS
 * @description	
	* This function is used to initialize the global parameter structure with parameters
 * used to configure the BLE module.
 * 
 * @prerequisite 
	* rsi_sys_init should be done successfully. 		
 */
INT16 rsi_ble_init_struct(UINT16  CommandType)
{
    RSI_BLE_API  *uApiParams;
    INT16         ret_val = 0;
    INT08        dev_ix=0;
    
    
    uApiParams = rsi_bt_AppControlBlock.uBLEApiInitParams;
#ifdef RSI_DEBUG_PRINT
		RSI_DPRINT(RSI_PL13,"CMD TYPE %d\n",CommandType);
#endif
    switch (CommandType) {
      case RSI_BLE_ADD_WHITELIST:
        {
          memset(&uApiParams->uLeWhiteList, 0, sizeof (RSI_BLE_CMD_WHITE_LIST));

          uApiParams->uLeWhiteList.BleWhiteList.AddOrDelete = BLE_ADD_ENTRY_TO_WHITE_LIST;
          
          rsi_asciiMacAddressTo6Bytesrev(uApiParams->uLeWhiteList.BleWhiteList.BDAddress, (INT08*)RSI_BLE_WHITE_LIST_BDADDRESS);  
          uApiParams->uLeWhiteList.BleWhiteList.BDAddresstype = RSI_BLE_WHITE_LIST_BDADDRESS_TYPE;

          ret_val = rsi_ble_white_list(&uApiParams->uLeWhiteList);
        }
        break;
      
      case RSI_BLE_DELETE_WHITELIST:
        {
          memset(&uApiParams->uLeWhiteList, 0, sizeof (RSI_BLE_CMD_WHITE_LIST));

          uApiParams->uLeWhiteList.BleWhiteList.AddOrDelete = BLE_DELETE_ENTRY_FROM_WHITE_LIST;
          
          rsi_asciiMacAddressTo6Bytesrev(uApiParams->uLeWhiteList.BleWhiteList.BDAddress, (INT08*)RSI_BLE_WHITE_LIST_BDADDRESS);  
          uApiParams->uLeWhiteList.BleWhiteList.BDAddresstype = RSI_BLE_WHITE_LIST_BDADDRESS_TYPE;

          ret_val = rsi_ble_white_list(&uApiParams->uLeWhiteList);
        }
        break;

      case RSI_BLE_CLEARALL_WHITELIST:
        {
          memset(&uApiParams->uLeWhiteList, 0, sizeof (RSI_BLE_CMD_WHITE_LIST));

          uApiParams->uLeWhiteList.BleWhiteList.AddOrDelete = BLE_CLEARALL_ENTRYS_FROM_WHITELIST;
          
          rsi_asciiMacAddressTo6Bytesrev(uApiParams->uLeWhiteList.BleWhiteList.BDAddress, (INT08*)RSI_BLE_WHITE_LIST_BDADDRESS);  
          uApiParams->uLeWhiteList.BleWhiteList.BDAddresstype = RSI_BLE_WHITE_LIST_BDADDRESS_TYPE;

          ret_val = rsi_ble_white_list(&uApiParams->uLeWhiteList);
        }
        break;
      case RSI_BLE_SET_ANTENNA_TX_POWER_LEVEL:
        {
          memset(&uApiParams->uLeAntennaTxPower, 0, sizeof (RSI_BLE_CMD_SET_ANTENNA_TX_POWER_VLAUE));

          uApiParams->uLeAntennaTxPower.SetAntennaTxPower.ProtocolMode       = 2;
          uApiParams->uLeAntennaTxPower.SetAntennaTxPower.AntennaTxPower     = RSI_BLE_TX_POWER;

          ret_val = rsi_ble_set_antenna_tx_power_value(&uApiParams->uLeAntennaTxPower);
        }
        break;

      case RSI_BLE_REQ_SET_RANDOM_ADDRESS:
           {
           memset  (&uApiParams->uLeRandAdd, 0, sizeof (RSI_BLE_CMD_SET_RANDOM_ADDRESS));
           rsi_asciiMacAddressTo6Bytesrev(uApiParams->uLeRandAdd.SetRandAddFrameSnd.BDAddress, (INT08*)RSI_BLE_RAND_ADDR); //random address
           ret_val = rsi_ble_set_random_address(&uApiParams->uLeRandAdd);
           }
             break;

        case RSI_BLE_REQ_SET_ADVERTISE_DATA:
             {
                 UINT08  data[3] = {2,1,6};  //filling the flags parameter in advertise data(general discv and le only suppport)
                 memset  (&uApiParams->uLeSetAdvertiseData, 0, sizeof (RSI_BLE_CMD_SET_ADVERTISE_DATA));
                 uApiParams->uLeSetAdvertiseData.SetAdvertiseDataFrameSnd.DataLen = sizeof (data);
                 memcpy (uApiParams->uLeSetAdvertiseData.SetAdvertiseDataFrameSnd.Data, data, uApiParams->uLeSetAdvertiseData.SetAdvertiseDataFrameSnd.DataLen);
                 ret_val = rsi_ble_set_advertise_data(&uApiParams->uLeSetAdvertiseData);
             }
             break;

        case RSI_BLE_REQ_SET_LE_PING_TIMEOUT:
             memset  (&uApiParams->uLeSetPingTimeout, 0 ,sizeof (RSI_BLE_CMD_SET_PING_TIMEOUT));
#ifndef FSM_BASED_BLE_APP             
             dev_ix = GetConnectedDevIndex ();
             if ((dev_ix < 0)  && (dev_ix >= connected_dev_count)) {
                 return 0;
             }
             memcpy (uApiParams->uLeSetPingTimeout.SetLePingTimeoutFrameSnd.BDAddress,connected_dev_list[dev_ix],6); //remote device address
#else   
             if (RSI_BLE_CONN_ADDR != 0) {
               rsi_asciiMacAddressTo6Bytesrev(uApiParams->uLeSetPingTimeout.SetLePingTimeoutFrameSnd.BDAddress, (INT08*)RSI_BLE_CONN_ADDR); //remote device address
             }
#endif
             uApiParams->uLeSetPingTimeout.SetLePingTimeoutFrameSnd.Timeout =  LE_PING_TIMEOUT;
             ret_val = rsi_ble_set_ping_timeout(&uApiParams->uLeSetPingTimeout);
             break;
             
        case RSI_BLE_REQ_GET_LE_PING_TIMEOUT:
             ret_val = rsi_ble_get_ping_timeout();
             break;
      
        case RSI_BLE_REQ_ADVERTISE:
#ifdef RSI_DEBUG_PRINT
			RSI_DPRINT(RSI_PL13,"ADVERTISE CMD \n");
			RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","BLE","Tx","BLE Advrt Req","Advertisment Requested");
#endif
			
             memset (&uApiParams->uLeAdvertise, 0, sizeof (RSI_BLE_CMD_ADVERTISE));
             uApiParams->uLeAdvertise.AdvFrameSnd.Status                = RSI_BLE_ADV_STATUS;
             uApiParams->uLeAdvertise.AdvFrameSnd.AdvertiseType         = RSI_BLE_ADV_TYPE;
             uApiParams->uLeAdvertise.AdvFrameSnd.FilterType            = RSI_BLE_ADV_FILTER_TYPE;
             uApiParams->uLeAdvertise.AdvFrameSnd.DirectAddrType        = RSI_BLE_ADV_DIR_ADDR_TYPE;
             rsi_asciiMacAddressTo6Bytesrev(uApiParams->uLeAdvertise.AdvFrameSnd.DirectAddr, (INT08*)RSI_BLE_ADV_DIR_ADDR); //remote device address
             uApiParams->uLeAdvertise.AdvFrameSnd.adv_int_min           = RSI_BLE_ADVERTISE_INTERVAL_MIN;                   // minimum advertise interval
             uApiParams->uLeAdvertise.AdvFrameSnd.adv_int_max           = RSI_BLE_ADVERTISE_INTERVAL_MAX;                   // maximum advertise interval
             uApiParams->uLeAdvertise.AdvFrameSnd.own_add_type          = RSI_BLE_OWN_ADDRESS_TYPE;                         // module address type
             uApiParams->uLeAdvertise.AdvFrameSnd.adv_channel_map       = RSI_BLE_ADVERTISE_CHANNEL_MAP;                    // advertise channel map

             ret_val = rsi_ble_advertise(&uApiParams->uLeAdvertise);
             break;

        case RSI_BLE_REQ_SCAN:
             memset (&uApiParams->uLeScan, 0, sizeof (RSI_BLE_CMD_SCAN));
             uApiParams->uLeScan.ScanFrameSnd.Status       = RSI_BLE_SCAN_STATUS;           //1-scan enable, 0-scan disable
             uApiParams->uLeScan.ScanFrameSnd.Scantype     = RSI_BLE_SCAN_TYPE;             //scan type (active /passive)
             uApiParams->uLeScan.ScanFrameSnd.FilterType   = RSI_BLE_SCAN_FILTER_TYPE;      //filter type
             uApiParams->uLeScan.ScanFrameSnd.own_add_type = RSI_BLE_OWN_ADDRESS_TYPE;      // module address type
             uApiParams->uLeScan.ScanFrameSnd.scan_int     = LE_SCAN_INTERVAL;              // LE scan interval
             uApiParams->uLeScan.ScanFrameSnd.scan_win     = LE_SCAN_WINDOW;                // LE scan window

             ret_val = rsi_ble_scan(&uApiParams->uLeScan);
             break;

        case RSI_BLE_REQ_CONNECT:
             memset (&uApiParams->uLeConnect, 0, sizeof (RSI_BLE_CMD_CONNECT));
#ifndef FSM_BASED_BLE_APP             
             dev_ix = GetScanDevIndex ();
             uApiParams->uLeConnect.ConnectFrameSnd.AddressType          = RSI_BLE_CONN_ADDR_TYPE;        //remote device type
             //rsi_asciiMacAddressTo6Bytesrev(uApiParams->uLeConnect.ConnectFrameSnd.BDAddress, (INT08*)RSI_BLE_CONN_ADDR); //remote device address
             uApiParams->uLeConnect.ConnectFrameSnd.LeScanInterval       = LE_SCAN_INTERVAL;
             uApiParams->uLeConnect.ConnectFrameSnd.LeScanWindow         = LE_SCAN_WINDOW;
             uApiParams->uLeConnect.ConnectFrameSnd.ConnIntervalMin      = CONNECTION_INTERVAL_MIN;
             uApiParams->uLeConnect.ConnectFrameSnd.ConnIntervalMax      = CONNECTION_INTERVAL_MAX;
             uApiParams->uLeConnect.ConnectFrameSnd.ConnLatency          = CONNECTION_LATENCY;
             uApiParams->uLeConnect.ConnectFrameSnd.SupervisionTimeout   = SUPERVISION_TIMEOUT;

             if ((dev_ix < 0) && (dev_ix >=  remote_dev_count)) {
               break;
             }
             memcpy (uApiParams->uLeConnect.ConnectFrameSnd.BDAddress,remote_dev_list[dev_ix],6); //remote device address
#else         
             if (RSI_BLE_CONN_ADDR != 0) {
               rsi_asciiMacAddressTo6Bytesrev(uApiParams->uLeConnect.ConnectFrameSnd.BDAddress,(INT08 *) RSI_BLE_CONN_ADDR);   // Convert from BD address string to BD address.
             } else {
               memcpy (uApiParams->uLeConnect.ConnectFrameSnd.BDAddress,remote_dev_list[dev_ix],6); //remote device address
             }
#endif             
             uApiParams->uLeConnect.ConnectFrameSnd.AddressType = RSI_BLE_CONN_ADDR_TYPE;        //remote device type
             ret_val = rsi_ble_connect(&uApiParams->uLeConnect);
             break;

        case RSI_BLE_REQ_DISCONNECT:
             memset (&uApiParams->uLeDisConnect, 0, sizeof (RSI_BLE_CMD_DISCONNECT));
             dev_ix = GetConnectedDevIndex ();
             if ((dev_ix < 0)  && (dev_ix >= connected_dev_count)) {
                 return 0;
             }
             //memcpy (uApiParams->uLeCharVal.ReadCharValByUuidFrameSnd.BDAddress,connected_dev_list[dev_ix],6); //remote device address
             memcpy (uApiParams->uLeDisConnect.DisconnectFrameSnd.BDAddress,connected_dev_list[dev_ix],6); //remote device address
             ret_val = rsi_ble_disconnect(&uApiParams->uLeDisConnect);
             break;

        case RSI_BLE_REQ_QUERY_DEVICE_STATE:
             ret_val = rsi_ble_query_device_state();
             break;
        
        case RSI_BLE_REQ_START_ENCRYPTION:
             memset (&uApiParams->uLeSmpEncrypt, 0, sizeof (RSI_BLE_CMD_ENCRYPTTION));
             dev_ix = GetConnectedDevIndex ();
             if ((dev_ix < 0)  && (dev_ix >= connected_dev_count)) {
                 return 0;
             }
             memcpy (uApiParams->uLeCharVal.ReadCharValByUuidFrameSnd.BDAddress,connected_dev_list[dev_ix],6); //remote device address
             ret_val = rsi_ble_start_encryption(&uApiParams->uLeSmpEncrypt);
             break;

        case RSI_BLE_REQ_SMP_PAIR_REQUEST:
             memset (&uApiParams->uLeSmpReq, 0, sizeof (RSI_BLE_CMD_SMP_PAIR_REQUEST));
             dev_ix = GetConnectedDevIndex ();
             if ((dev_ix < 0)  && (dev_ix >= connected_dev_count)) {
                 return 0;
             }
             memcpy (uApiParams->uLeCharVal.ReadCharValByUuidFrameSnd.BDAddress,connected_dev_list[dev_ix],6); //remote device address
             uApiParams->uLeSmpReq.SmpPairReqFrameSnd.IOCapability = RSI_BLE_SMP_IOCAPABILITY;
             ret_val = rsi_ble_smp_pair_request(&uApiParams->uLeSmpReq);
             break;

        case RSI_BLE_REQ_SMP_RESPONSE:
             memset (&uApiParams->uLeSmpResp, 0, sizeof (RSI_BLE_CMD_SMP_RESPONSE));
             dev_ix = GetConnectedDevIndex ();
             if ((dev_ix < 0)  && (dev_ix >= connected_dev_count)) {
                 return 0;
             }
             memcpy (uApiParams->uLeCharVal.ReadCharValByUuidFrameSnd.BDAddress,connected_dev_list[dev_ix],6); //remote device address
             uApiParams->uLeSmpResp.SmpRespFrameSnd.IOCapability = RSI_BLE_SMP_IOCAPABILITY;            
             ret_val = rsi_ble_smp_response(&uApiParams->uLeSmpResp);
             break;

        case RSI_BLE_REQ_SMP_PASSKEY:
             memset (&uApiParams->uLeSmppasskey, 0, sizeof (RSI_BLE_CMD_SMP_PASSKEY));
             dev_ix = GetConnectedDevIndex ();
             if ((dev_ix < 0)  && (dev_ix >= connected_dev_count)) {
                 return 0;
             }
             memcpy (uApiParams->uLeCharVal.ReadCharValByUuidFrameSnd.BDAddress,connected_dev_list[dev_ix],6); //remote device address
             uApiParams->uLeSmppasskey.SmpPasskeyFrameSnd.Passkey[0] = 0;  //passkey value
             uApiParams->uLeSmppasskey.SmpPasskeyFrameSnd.Passkey[1] = 0;  //passkey value
             uApiParams->uLeSmppasskey.SmpPasskeyFrameSnd.Passkey[2] = 0;  //passkey value
             uApiParams->uLeSmppasskey.SmpPasskeyFrameSnd.Passkey[3] = 0;  //passkey value
             ret_val = rsi_ble_smp_passkey(&uApiParams->uLeSmppasskey);
             break;

        case RSI_BLE_REQ_QUERY_PROFILES_LIST:         
             memset (&uApiParams->uLeAllServ, 0, sizeof (RSI_BLE_CMD_PROFILE_LIST));
#ifndef FSM_BASED_BLE_APP             
             dev_ix = GetConnectedDevIndex ();
             if ((dev_ix < 0)  && (dev_ix >= connected_dev_count)) {
                 return 0;
             }
             memcpy (uApiParams->uLeAllServ.ProfileReqFrameSnd.BDAddress,connected_dev_list[dev_ix],6); //remote device address
#else             
             if (RSI_BLE_CONN_ADDR != 0) {
              rsi_asciiMacAddressTo6Bytesrev(uApiParams->uLeAllServ.ProfileReqFrameSnd.BDAddress,(INT08 *) RSI_BLE_CONN_ADDR);   // Convert from BD address string to BD address.
             } else {
             memcpy (uApiParams->uLeAllServ.ProfileReqFrameSnd.BDAddress,connected_dev_list[0],6); //remote device address
             }
#endif			 
             uApiParams->uLeAllServ.ProfileReqFrameSnd.StartHandle = RSI_BLE_PROFILE_LIST_START_HANDLE;
             uApiParams->uLeAllServ.ProfileReqFrameSnd.EndHandle   = RSI_BLE_PROFILE_LIST_END_HANDLE;
             ret_val = rsi_ble_query_profiles_list(&uApiParams->uLeAllServ);
             break;

        case RSI_BLE_REQ_QUERY_PROFILE:
             memset (&uApiParams->uLeSev, 0, sizeof (RSI_BLE_CMD_QUERY_PROFILE));
             dev_ix = GetConnectedDevIndex ();
             if ((dev_ix < 0)  && (dev_ix >= connected_dev_count)) {
                 return 0;
             }
             memcpy (uApiParams->uLeSev.QueryProfileDescFrameSnd.BDAddress,connected_dev_list[dev_ix],6); //remote device address
             uApiParams->uLeSev.QueryProfileDescFrameSnd.ProfileUUID.size = RSI_BLE_UUID_SIZE;
             rsi_uint16_to_2bytes ((UINT08 *)&uApiParams->uLeSev.QueryProfileDescFrameSnd.ProfileUUID.Val.val16, RSI_BLE_PROFILE_UUID);
             ret_val = rsi_ble_query_profile(&uApiParams->uLeSev);
             break;

        case RSI_BLE_REQ_QUERY_CHARACTERISTIC_SERVICES:
             memset (&uApiParams->uLeCharServ, 0, sizeof (RSI_BLE_CMD_QUERY_CHARACTERISTIC_SERVICES));
             dev_ix = GetConnectedDevIndex ();
             if ((dev_ix < 0)  && (dev_ix >= connected_dev_count)) {
                 return 0;
             }
             memcpy (uApiParams->uLeCharServ.QueryCharSerFrameSnd.BDAddress,connected_dev_list[dev_ix],6); //remote device address
             rsi_uint16_to_2bytes (uApiParams->uLeCharServ.QueryCharSerFrameSnd.StartHandle, RSI_BLE_CHAR_SERV_START_HANDLE);
             rsi_uint16_to_2bytes (uApiParams->uLeCharServ.QueryCharSerFrameSnd.EndHandle, RSI_BLE_CHAR_SERV_END_HANDLE);
             ret_val = rsi_ble_query_characteristic_services(&uApiParams->uLeCharServ);
             break;

        case RSI_BLE_REQ_QUERY_INCLUDE_SERVICES:
             memset (&uApiParams->uLeIncServ, 0, sizeof (RSI_BLE_CMD_QUERY_INCLUDE_SERVICES));
             dev_ix = GetConnectedDevIndex ();
             if ((dev_ix < 0)  && (dev_ix >= connected_dev_count)) {
                 return 0;
             }
             memcpy (uApiParams->uLeIncServ.QueryIncludeServFrameSnd.BDAddress,connected_dev_list[dev_ix],6); //remote device address
             rsi_uint16_to_2bytes (uApiParams->uLeIncServ.QueryIncludeServFrameSnd.StartHandle, RSI_BLE_INC_SERV_START_HANDLE);
             rsi_uint16_to_2bytes (uApiParams->uLeIncServ.QueryIncludeServFrameSnd.EndHandle, RSI_BLE_INC_SERV_END_HANDLE);
             ret_val = rsi_ble_query_include_service(&uApiParams->uLeIncServ);
             break;

        case RSI_BLE_REQ_READ_CHAR_VALUE_BY_UUID:
             memset (&uApiParams->uLeCharVal, 0, sizeof (RSI_BLE_CMD_READ_CHAR_VALUE_BY_UUID));
             dev_ix = GetConnectedDevIndex ();
             if ((dev_ix < 0)  && (dev_ix >= connected_dev_count)) {
                 return 0;
             }
             memcpy (uApiParams->uLeCharVal.ReadCharValByUuidFrameSnd.BDAddress,connected_dev_list[dev_ix],6); //remote device address
             rsi_uint16_to_2bytes (uApiParams->uLeCharVal.ReadCharValByUuidFrameSnd.StartHandle, RSI_BLE_READ_CHAR_START_HANDLE);
             rsi_uint16_to_2bytes (uApiParams->uLeCharVal.ReadCharValByUuidFrameSnd.EndHandle, RSI_BLE_READ_CHAR_END_HANDLE);
             uApiParams->uLeCharVal.ReadCharValByUuidFrameSnd.CharacterUUID.size = 2;
             rsi_uint16_to_2bytes ((UINT08 *)&uApiParams->uLeCharVal.ReadCharValByUuidFrameSnd.CharacterUUID.Val.val16, RSI_BLE_READ_CHAR_UUID);

             ret_val = rsi_ble_read_char_value_by_UUID(&uApiParams->uLeCharVal);
             break;

        case RSI_BLE_REQ_QUERY_ATT_DESC:
             memset (&uApiParams->uLeAttDesc, 0, sizeof (RSI_BLE_CMD_QUERY_ATT_DESC));
             dev_ix = GetConnectedDevIndex ();
             if ((dev_ix < 0)  && (dev_ix >= connected_dev_count)) {
                 return 0;
             }
             memcpy (uApiParams->uLeAttDesc.QueryAttFrameSnd.BDAddress,connected_dev_list[dev_ix],6); //remote device address
             rsi_uint16_to_2bytes(uApiParams->uLeAttDesc.QueryAttFrameSnd.StartHandle, RSI_BLE_ATT_START_HANDLE);
             rsi_uint16_to_2bytes(uApiParams->uLeAttDesc.QueryAttFrameSnd.EndHandle, RSI_BLE_ATT_END_HANDLE);
             ret_val = rsi_ble_query_att(&uApiParams->uLeAttDesc);
             break;

        case RSI_BLE_REQ_QUERY_ATT_VALUE:
             memset (&uApiParams->uLeAttVal, 0, sizeof (RSI_BLE_CMD_QUERY_ATT_VALUE));
             dev_ix = GetConnectedDevIndex ();
             if ((dev_ix < 0)  && (dev_ix >= connected_dev_count)) {
                 return 0;
             }
             memcpy (uApiParams->uLeAttVal.QueryAttValFrameSnd.BDAddress,connected_dev_list[dev_ix],6); //remote device address
             rsi_uint16_to_2bytes (uApiParams->uLeAttVal.QueryAttValFrameSnd.Handle, RSI_BLE_ATT_VAL_HANDLE);
             ret_val = rsi_ble_query_att_value(&uApiParams->uLeAttVal);
             break;

        case RSI_BLE_REQ_QUERY_MULTIPLE_ATT_VALUES:
             memset (&uApiParams->uLeMulAttVals, 0, sizeof (RSI_BLE_CMD_QUERY_MULTIPLE_ATT_VALUES));
             dev_ix = GetConnectedDevIndex ();
             if ((dev_ix < 0)  && (dev_ix >= connected_dev_count)) {
                 return 0;
             }
             memcpy (uApiParams->uLeMulAttVals.QueryMulAttValFrameSnd.BDAddress,connected_dev_list[dev_ix],6); //remote device address
             uApiParams->uLeMulAttVals.QueryMulAttValFrameSnd.NumberOfHandles = RSI_BLE_MUL_NBR_OF_ATT;
             rsi_uint16_to_2bytes ((UINT08 *)&uApiParams->uLeMulAttVals.QueryMulAttValFrameSnd.Handles[0], RSI_BLE_MUL_ATT_HANDLE1);
             rsi_uint16_to_2bytes ((UINT08 *)&uApiParams->uLeMulAttVals.QueryMulAttValFrameSnd.Handles[1], RSI_BLE_MUL_ATT_HANDLE2);

             ret_val = rsi_ble_query_multi_att_values(&uApiParams->uLeMulAttVals);
             break;

        case RSI_BLE_REQ_QUERY_LONG_ATT_VALUE:
             memset (&uApiParams->uLeLongAttVal, 0, sizeof (RSI_BLE_CMD_QUERY_LONG_ATT_VALUE));
             dev_ix = GetConnectedDevIndex ();
             if ((dev_ix < 0)  && (dev_ix >= connected_dev_count)) {
                 return 0;
             }
             memcpy (uApiParams->uLeLongAttVal.QueryLongAttValFrameSnd.BDAddress,connected_dev_list[dev_ix],6); //remote device address
             rsi_uint16_to_2bytes ((UINT08 *)&uApiParams->uLeLongAttVal.QueryLongAttValFrameSnd.Handle, RSI_BLE_LONG_ATT_HANDLE);
             rsi_uint16_to_2bytes ((UINT08 *)&uApiParams->uLeLongAttVal.QueryLongAttValFrameSnd.Offset, RSI_BLE_LONG_ATT_OFFSET);

             ret_val = rsi_ble_query_long_att_value(&uApiParams->uLeLongAttVal);
             break;

        case RSI_BLE_REQ_SET_ATT_VALUE:
             memset (&uApiParams->uLeSetAttVal, 0, sizeof (RSI_BLE_CMD_SET_ATT_VALUE));
             dev_ix = GetConnectedDevIndex ();
             if ((dev_ix < 0)  && (dev_ix >= connected_dev_count)) {
                 return 0;
             }
             memcpy (uApiParams->uLeSetAttVal.SetAttValFrameSnd.BDAddress,connected_dev_list[dev_ix],6); //remote device address
             rsi_uint16_to_2bytes (uApiParams->uLeSetAttVal.SetAttValFrameSnd.Handle, RSI_BLE_SET_ATT_HANDLE);
             uApiParams->uLeSetAttVal.SetAttValFrameSnd.Length = RSI_BLE_SET_ATT_LEN;
             rsi_uint16_to_2bytes(uApiParams->uLeSetAttVal.SetAttValFrameSnd.Value, RSI_BLE_SET_ATT_VAL);

             ret_val = rsi_ble_set_att_value(&uApiParams->uLeSetAttVal);
             break;

        case RSI_BLE_REQ_SET_ATT_VALUE_NO_ACK:
             memset (&uApiParams->uLeSetCmdAttVal, 0, sizeof (RSI_BLE_CMD_SET_ATT_VALUE_NO_ACK));
             dev_ix = GetConnectedDevIndex ();
             if ((dev_ix < 0)  && (dev_ix >= connected_dev_count)) {
                 return 0;
             }
             memcpy (uApiParams->uLeSetCmdAttVal.SetAttValNoAckFrameSnd.BDAddress,connected_dev_list[dev_ix],6); //remote device address
             rsi_uint16_to_2bytes (uApiParams->uLeSetCmdAttVal.SetAttValNoAckFrameSnd.Handle, RSI_BLE_SET_ATT_NO_ACK_HANDLE);
             uApiParams->uLeSetCmdAttVal.SetAttValNoAckFrameSnd.Length = RSI_BLE_SET_ATT_NO_ACK_LEN;
             rsi_uint16_to_2bytes(uApiParams->uLeSetCmdAttVal.SetAttValNoAckFrameSnd.Value, RSI_BLE_SET_ATT_NO_ACK_VAL);

             ret_val = rsi_ble_set_att_value_no_ack(&uApiParams->uLeSetCmdAttVal);
             break;

        case RSI_BLE_REQ_SET_LONG_ATT_VALUE:
             memset (&uApiParams->uLeSetLongAttVal, 0, sizeof (RSI_BLE_CMD_SET_LONG_ATT_VALUE));
             dev_ix = GetConnectedDevIndex ();
             if ((dev_ix < 0)  && (dev_ix >= connected_dev_count)) {
                 return 0;
             }
             memcpy (uApiParams->uLeSetLongAttVal.SetLongAttValFrameSnd.BDAddress,connected_dev_list[dev_ix],6); //remote device address
             rsi_uint16_to_2bytes (uApiParams->uLeSetLongAttVal.SetLongAttValFrameSnd.Handle, RSI_BLE_SET_LONG_ATT_HANDLE);
             rsi_uint16_to_2bytes (uApiParams->uLeSetLongAttVal.SetLongAttValFrameSnd.Offset, RSI_BLE_SET_LONG_ATT_OFFSET);
             uApiParams->uLeSetLongAttVal.SetLongAttValFrameSnd.Length = RSI_BLE_SET_LONG_ATT_LEN;
             rsi_uint16_to_2bytes (uApiParams->uLeSetLongAttVal.SetLongAttValFrameSnd.Value, RSI_BLE_SET_LONG_ATT_VAL);

             ret_val = rsi_ble_set_long_att_value(&uApiParams->uLeSetLongAttVal);
             break;

        case RSI_BLE_REQ_SET_PREPARE_LONG_ATT_VALUE:
             memset (&uApiParams->uLePrepareAttVal, 0, sizeof (RSI_BLE_CMD_SET_PREPARE_LONG_ATT_VALUE));
             dev_ix = GetConnectedDevIndex ();
             if ((dev_ix < 0)  && (dev_ix >= connected_dev_count)) {
                 return 0;
             }
             memcpy (uApiParams->uLePrepareAttVal.SetPreLongAttValFrameSnd.BDAddress,connected_dev_list[dev_ix],6); //remote device address
             rsi_uint16_to_2bytes (uApiParams->uLePrepareAttVal.SetPreLongAttValFrameSnd.Handle, RSI_BLE_PREP_LONG_ATT_HANDLE);
             rsi_uint16_to_2bytes (uApiParams->uLePrepareAttVal.SetPreLongAttValFrameSnd.Offset, RSI_BLE_PREP_LONG_ATT_OFFSET);
             uApiParams->uLePrepareAttVal.SetPreLongAttValFrameSnd.Length = RSI_BLE_PREP_LONG_ATT_LEN;
             rsi_uint16_to_2bytes (uApiParams->uLePrepareAttVal.SetPreLongAttValFrameSnd.Value, RSI_BLE_PREP_LONG_ATT_VAL);

             ret_val = rsi_ble_set_prep_long_att_value(&uApiParams->uLePrepareAttVal);
             break;

        case RSI_BLE_REQ_EXECUTE_LONG_ATT_VALUE_WRITE:
             memset (&uApiParams->uLeExecuteWrite, 0, sizeof (RSI_BLE_CMD_EXECUTE_LONG_ATT_VALUE_WRITE));
             dev_ix = GetConnectedDevIndex ();
             if ((dev_ix < 0)  && (dev_ix >= connected_dev_count)) {
                 return 0;
             }
             memcpy (uApiParams->uLeExecuteWrite.ExeLongAttValWrFrameSnd.BDAddress,connected_dev_list[dev_ix],6); //remote device address
             uApiParams->uLeExecuteWrite.ExeLongAttValWrFrameSnd.Flag = RSI_BLE_EXE_LONG_ATT_FLAG;

             ret_val = rsi_ble_execute_long_att_value(&uApiParams->uLeExecuteWrite);
             break;
        case RSI_BT_REQ_INIT:
             ret_val = rsi_bt_device_init();
             break;
        case RSI_BT_REQ_DEINIT:
             ret_val = rsi_bt_device_deinit();
             break;
        case RSI_BT_REQ_ANTENNA_SELECT:
             memset(&uApiParams->uAntennaSelect, 0, sizeof(RSI_BT_CMD_ANTENNA_SELECT));
             uApiParams->uAntennaSelect.AntennaSelectFrameSnd.AntennaVal = RSI_BT_ANTENNA_VALUE;
             ret_val = rsi_bt_antenna_select(&uApiParams->uAntennaSelect);
             break;

        case RSI_BLE_REQ_SET_LOCAL_ATT_VALUE_ID:
             //RSI_DPRINT(RSI_PL3,"RSI_BLE_REQ_SET_LOCAL_ATT_VALUE, handle: 0x%04x\r\n", RSI_BLE_GATT_CHANGE_ATT_HANDLE);
             memset(&uApiParams->uLeSetLocalAttValue, 0, sizeof(RSI_BLE_CMD_SET_LOCAL_ATT_VALUE));
             uApiParams->uLeSetLocalAttValue.Hndl    = RSI_BLE_GATT_CHANGE_ATT_HANDLE;
             uApiParams->uLeSetLocalAttValue.DataLen = RSI_BLE_GATT_CHANGE_ATT_DATA_LEN;
             uApiParams->uLeSetLocalAttValue.Data[0] = RSI_BLE_GATT_CHANGE_ATT_DATA;
             ret_val = rsi_ble_device_ChangeLocalAttValue(&uApiParams->uLeSetLocalAttValue);
             break;

        case RSI_BLE_REQ_GET_LOCAL_ATT_VALUE_ID:
             //RSI_DPRINT(RSI_PL3,RSI_BLE_REQ_GET_LOCAL_ATT_VALUE, handle: 0x%04x\r\n", RSI_BLE_GATT_GET_LOCAL_ATT_HANDLE);
             memset(&uApiParams->uLeGetLocalAttValue, 0, sizeof(RSI_BLE_CMD_GET_LOCAL_ATT_VALUE));
             uApiParams->uLeGetLocalAttValue.Hndl = RSI_BLE_GATT_GET_LOCAL_ATT_HANDLE;
             ret_val = rsi_ble_device_GetLocalAttValue(&uApiParams->uLeGetLocalAttValue);
             break;

        case RSI_BLE_REQ_ADD_LINKLOSS_SERVICE:// RSI_BLE_REQ_ADD_SERVICE:
             //RSI_DPRINT(RSI_PL3,"add link loss service\r\n");
             memset (&uApiParams->uLeAddService, 0, sizeof (RSI_BLE_CMD_ADD_GATT_SERVICE));
             uApiParams->uLeAddService.AddServiceRecord.ServiceUUID.size = 2;
             uApiParams->uLeAddService.AddServiceRecord.ServiceUUID.Val.val16 = RSI_BLE_LINKLOSS_SERVICE_UUID;
             ret_val = rsi_ble_device_AddService(&uApiParams->uLeAddService);
             break;

        case RSI_BLE_REQ_ADD_LINKLOSS_ATT1:                    //RSI_BLE_REQ_ADD_ATTRIBUTE:
             
             //RSI_DPRINT(RSI_PL3,"add link loss service, att1\r\n");
             //RSI_DPRINT(RSI_PL3,"service handler: 0x%08x\r\n", dbg_add_serv_resp.ServiceHndlerPtr);
             //RSI_DPRINT(RSI_PL3,"start handle   : 0x%04x\r\n", dbg_add_serv_resp.StartHndl);

             memset (&uApiParams->uLeAddAttribute, 0, sizeof (RSI_BLE_CMD_ADD_GATT_ATTRIBUTE));
             uApiParams->uLeAddAttribute.AddAttRecord.ServiceHndlerPtr  = dbg_add_serv_resp.ServiceHndlerPtr;   // service handler from device response
             uApiParams->uLeAddAttribute.AddAttRecord.AttUUID.size      = 2;
             uApiParams->uLeAddAttribute.AddAttRecord.AttUUID.Val.val16 = RSI_BLE_GATT_CHAR_SERVICE_UUID;
             uApiParams->uLeAddAttribute.AddAttRecord.Hndl              = dbg_add_serv_resp.StartHndl + 1;
             uApiParams->uLeAddAttribute.AddAttRecord.Prop              = BT_LE_READ;
             uApiParams->uLeAddAttribute.AddAttRecord.DataLen           = 6;
             uApiParams->uLeAddAttribute.AddAttRecord.Data[0] = BT_LE_READ | BT_LE_WRITE | BT_LE_NOTIFY;
             rsi_uint16_to_2bytes (uApiParams->uLeAddAttribute.AddAttRecord.Data + 2, dbg_add_serv_resp.StartHndl + 2);
             rsi_uint32_to_4bytes (uApiParams->uLeAddAttribute.AddAttRecord.Data + 4, RSI_BLE_GATT_ALERT_ATT_UUID);
             
             ret_val = rsi_ble_device_AddServiceAttribute(&uApiParams->uLeAddAttribute);
             break;
        
        case RSI_BLE_REQ_ADD_LINKLOSS_ATT2: 
             //RSI_DPRINT(RSI_PL3,"add link loss service, att2\r\n");
             //RSI_DPRINT(RSI_PL3,"service handler: 0x%08x\r\n", dbg_add_serv_resp.ServiceHndlerPtr);
             //RSI_DPRINT(RSI_PL3,"start handle   : 0x%08x\r\n", dbg_add_serv_resp.StartHndl);
             memset (&uApiParams->uLeAddAttribute, 0, sizeof (RSI_BLE_CMD_ADD_GATT_ATTRIBUTE));
             uApiParams->uLeAddAttribute.AddAttRecord.ServiceHndlerPtr  = dbg_add_serv_resp.ServiceHndlerPtr;   // service handler from dd ervice response
             uApiParams->uLeAddAttribute.AddAttRecord.AttUUID.size      = 2;
             uApiParams->uLeAddAttribute.AddAttRecord.AttUUID.Val.val16 = RSI_BLE_GATT_ALERT_ATT_UUID;
             uApiParams->uLeAddAttribute.AddAttRecord.Hndl              = dbg_add_serv_resp.StartHndl + 2;
             uApiParams->uLeAddAttribute.AddAttRecord.Prop              = BT_LE_READ | BT_LE_WRITE | BT_LE_NOTIFY;
             uApiParams->uLeAddAttribute.AddAttRecord.DataLen           = 1;
             uApiParams->uLeAddAttribute.AddAttRecord.Data[0]           = 0;

             ret_val = rsi_ble_device_AddServiceAttribute(&uApiParams->uLeAddAttribute);
             break;
        
        case RSI_BLE_REQ_ADD_LINKLOSS_ATT3: 
             //RSI_DPRINT(RSI_PL3,"add link loss service, att2\r\n");
             //RSI_DPRINT(RSI_PL3,"service handler: 0x%08x\r\n", dbg_add_serv_resp.ServiceHndlerPtr);
             //RSI_DPRINT(RSI_PL3,"start handle   : 0x%08x\r\n", dbg_add_serv_resp.StartHndl);
             memset (&uApiParams->uLeAddAttribute, 0, sizeof (RSI_BLE_CMD_ADD_GATT_ATTRIBUTE));
             uApiParams->uLeAddAttribute.AddAttRecord.ServiceHndlerPtr  = dbg_add_serv_resp.ServiceHndlerPtr;   // service handler from dd ervice response
             uApiParams->uLeAddAttribute.AddAttRecord.AttUUID.size      = 2;
             uApiParams->uLeAddAttribute.AddAttRecord.AttUUID.Val.val16 = RSI_BLE_GATT_CLIENT_CHAR;
             uApiParams->uLeAddAttribute.AddAttRecord.Hndl              = dbg_add_serv_resp.StartHndl + 3;
             uApiParams->uLeAddAttribute.AddAttRecord.Prop              = BT_LE_READ | BT_LE_WRITE;
             uApiParams->uLeAddAttribute.AddAttRecord.DataLen           = 2;
             uApiParams->uLeAddAttribute.AddAttRecord.Data[0]           = 0;
             uApiParams->uLeAddAttribute.AddAttRecord.Data[1]           = 0;

             ret_val = rsi_ble_device_AddServiceAttribute(&uApiParams->uLeAddAttribute);
             break;
             
        case RSI_BLE_REQ_ADD_IMMEDIATE_SERVICE:// RSI_BLE_REQ_ADD_SERVICE:            
             //RSI_DPRINT(RSI_PL3,"add Immediate alert service\r\n");
             memset (&uApiParams->uLeAddService, 0, sizeof (RSI_BLE_CMD_ADD_GATT_SERVICE));
             uApiParams->uLeAddService.AddServiceRecord.ServiceUUID.size = 2;
             uApiParams->uLeAddService.AddServiceRecord.ServiceUUID.Val.val16 = RSI_BLE_IMMEDIATE_ALERT_SERVICE_UUID;
             ret_val = rsi_ble_device_AddService(&uApiParams->uLeAddService);
             break;


        case RSI_BLE_REQ_ADD_IMMEDIATE_ATT1:                    //RSI_BLE_REQ_ADD_ATTRIBUTE:
             
             //RSI_DPRINT(RSI_PL3,"add Immediate alert service, att1\r\n");
             //RSI_DPRINT(RSI_PL3,"service handler: 0x%08x\r\n", dbg_add_serv_resp1.ServiceHndlerPtr);
             //RSI_DPRINT(RSI_PL3,"start handle   : 0x%08x\r\n", dbg_add_serv_resp1.StartHndl);

             memset (&uApiParams->uLeAddAttribute, 0, sizeof (RSI_BLE_CMD_ADD_GATT_ATTRIBUTE));
             uApiParams->uLeAddAttribute.AddAttRecord.ServiceHndlerPtr  = dbg_add_serv_resp1.ServiceHndlerPtr;   // service handler from dd ervice response
             uApiParams->uLeAddAttribute.AddAttRecord.AttUUID.size      = 2;
             uApiParams->uLeAddAttribute.AddAttRecord.AttUUID.Val.val16 = RSI_BLE_GATT_CHAR_SERVICE_UUID;
             uApiParams->uLeAddAttribute.AddAttRecord.Hndl              = dbg_add_serv_resp1.StartHndl + 1;
             uApiParams->uLeAddAttribute.AddAttRecord.Prop              = BT_LE_READ;
             uApiParams->uLeAddAttribute.AddAttRecord.DataLen           = 6;
             uApiParams->uLeAddAttribute.AddAttRecord.Data[0] = BT_LE_READ | BT_LE_WRITE;
             rsi_uint16_to_2bytes (uApiParams->uLeAddAttribute.AddAttRecord.Data + 2, dbg_add_serv_resp1.StartHndl + 2);
             rsi_uint32_to_4bytes (uApiParams->uLeAddAttribute.AddAttRecord.Data + 4, RSI_BLE_GATT_ALERT_ATT_UUID);
             
             ret_val = rsi_ble_device_AddServiceAttribute(&uApiParams->uLeAddAttribute);
             break;
        
        case RSI_BLE_REQ_ADD_IMMEDIATE_ATT2: 
             //RSI_DPRINT(RSI_PL3,"add Immediate alert service, att2\r\n");
             //RSI_DPRINT(RSI_PL3,"service handler: 0x%08x\r\n", dbg_add_serv_resp1.ServiceHndlerPtr);
             //RSI_DPRINT(RSI_PL3,"start handle   : 0x%08x\r\n", dbg_add_serv_resp1.StartHndl);
             memset (&uApiParams->uLeAddAttribute, 0, sizeof (RSI_BLE_CMD_ADD_GATT_ATTRIBUTE));
             uApiParams->uLeAddAttribute.AddAttRecord.ServiceHndlerPtr  = dbg_add_serv_resp1.ServiceHndlerPtr;   // service handler from dd ervice response
             uApiParams->uLeAddAttribute.AddAttRecord.AttUUID.size      = 2;
             uApiParams->uLeAddAttribute.AddAttRecord.AttUUID.Val.val16 = RSI_BLE_GATT_ALERT_ATT_UUID;
             uApiParams->uLeAddAttribute.AddAttRecord.Hndl              = dbg_add_serv_resp1.StartHndl + 2;
             uApiParams->uLeAddAttribute.AddAttRecord.Prop              = BT_LE_READ | BT_LE_WRITE;
             uApiParams->uLeAddAttribute.AddAttRecord.DataLen           = 1;
             uApiParams->uLeAddAttribute.AddAttRecord.Data[0]           = 0;

             ret_val = rsi_ble_device_AddServiceAttribute(&uApiParams->uLeAddAttribute);
             break;


        case RSI_BLE_REQ_ADD_RSI_SERVICE:// RSI_BLE_REQ_ADD_SERVICE:
             RSI_DPRINT(RSI_PL13,"add RSI new service\r\n");
             RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","BLE","Tx","Add Srvc Req","Adding New BLE Service");
             memset (&uApiParams->uLeAddService, 0, sizeof (RSI_BLE_CMD_ADD_GATT_SERVICE));
             uApiParams->uLeAddService.AddServiceRecord.ServiceUUID.size = 2;
             uApiParams->uLeAddService.AddServiceRecord.ServiceUUID.Val.val16 = RSI_BLE_RSI_SERVICE_UUID;
             ret_val = rsi_ble_device_AddService(&uApiParams->uLeAddService);
             break;

        case RSI_BLE_REQ_ADD_RSI_ATT1:                    //RSI_BLE_REQ_ADD_ATTRIBUTE:
             RSI_DPRINT(RSI_PL13,"add Attribute 1\r\n");
             RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","BLE","Tx","Add Attr Req","Adding Attr 1");
             memset (&uApiParams->uLeAddAttribute, 0, sizeof (RSI_BLE_CMD_ADD_GATT_ATTRIBUTE));
             uApiParams->uLeAddAttribute.AddAttRecord.ServiceHndlerPtr  = dbg_add_serv_resp.ServiceHndlerPtr;   // service handler from device response
             uApiParams->uLeAddAttribute.AddAttRecord.AttUUID.size      = 2;
             uApiParams->uLeAddAttribute.AddAttRecord.AttUUID.Val.val16 = RSI_BLE_GATT_CHAR_SERVICE_UUID;
             uApiParams->uLeAddAttribute.AddAttRecord.Hndl              = dbg_add_serv_resp.StartHndl + 1;
             uApiParams->uLeAddAttribute.AddAttRecord.Prop              = BT_LE_READ;
             uApiParams->uLeAddAttribute.AddAttRecord.DataLen           = 6;
             uApiParams->uLeAddAttribute.AddAttRecord.Data[0] = BT_LE_READ | BT_LE_WRITE;
             rsi_uint16_to_2bytes (uApiParams->uLeAddAttribute.AddAttRecord.Data + 2, dbg_add_serv_resp.StartHndl + 2);
             rsi_uint32_to_4bytes (uApiParams->uLeAddAttribute.AddAttRecord.Data + 4, RSI_BLE_GATT_RSI1_ATT_UUID);
             
             ret_val = rsi_ble_device_AddServiceAttribute(&uApiParams->uLeAddAttribute);
             break;
        
        case RSI_BLE_REQ_ADD_RSI_ATT2: 
             RSI_DPRINT(RSI_PL13,"add Attribute 2\r\n");
            RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","BLE","Tx","Add Attr Req","Adding Attr 2");
             memset (&uApiParams->uLeAddAttribute, 0, sizeof (RSI_BLE_CMD_ADD_GATT_ATTRIBUTE));
             uApiParams->uLeAddAttribute.AddAttRecord.ServiceHndlerPtr  = dbg_add_serv_resp.ServiceHndlerPtr;   // service handler from dd ervice response
             uApiParams->uLeAddAttribute.AddAttRecord.AttUUID.size      = 2;
             uApiParams->uLeAddAttribute.AddAttRecord.AttUUID.Val.val16 = RSI_BLE_GATT_RSI1_ATT_UUID;
             uApiParams->uLeAddAttribute.AddAttRecord.Hndl              = dbg_add_serv_resp.StartHndl + 2;
             uApiParams->uLeAddAttribute.AddAttRecord.Prop              = BT_LE_READ | BT_LE_WRITE;
             uApiParams->uLeAddAttribute.AddAttRecord.DataLen           = 20;
             uApiParams->uLeAddAttribute.AddAttRecord.Data[0]           = 0;

             ret_val = rsi_ble_device_AddServiceAttribute(&uApiParams->uLeAddAttribute);
             break;
        
        case RSI_BLE_REQ_ADD_RSI_ATT3:                    //RSI_BLE_REQ_ADD_ATTRIBUTE:
             
             RSI_DPRINT(RSI_PL13,"add Attribute 3\r\n");
             RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","BLE","Tx","Add Attr Req","Adding Attr 3");
             memset (&uApiParams->uLeAddAttribute, 0, sizeof (RSI_BLE_CMD_ADD_GATT_ATTRIBUTE));
             uApiParams->uLeAddAttribute.AddAttRecord.ServiceHndlerPtr  = dbg_add_serv_resp.ServiceHndlerPtr;   // service handler from device response
             uApiParams->uLeAddAttribute.AddAttRecord.AttUUID.size      = 2;
             uApiParams->uLeAddAttribute.AddAttRecord.AttUUID.Val.val16 = RSI_BLE_GATT_CHAR_SERVICE_UUID;
             uApiParams->uLeAddAttribute.AddAttRecord.Hndl              = dbg_add_serv_resp.StartHndl + 3;
             uApiParams->uLeAddAttribute.AddAttRecord.Prop              = BT_LE_READ;
             uApiParams->uLeAddAttribute.AddAttRecord.DataLen           = 6;
             uApiParams->uLeAddAttribute.AddAttRecord.Data[0] = BT_LE_READ | BT_LE_WRITE | BT_LE_NOTIFY;
             rsi_uint16_to_2bytes (uApiParams->uLeAddAttribute.AddAttRecord.Data + 2, dbg_add_serv_resp.StartHndl + 4);
             rsi_uint32_to_4bytes (uApiParams->uLeAddAttribute.AddAttRecord.Data + 4, RSI_BLE_GATT_RSI2_ATT_UUID);
             
             ret_val = rsi_ble_device_AddServiceAttribute(&uApiParams->uLeAddAttribute);
             break;
        
        case RSI_BLE_REQ_ADD_RSI_ATT4: 
             RSI_DPRINT(RSI_PL13,"add Attribute 4\r\n");
            RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","BLE","Tx","Add Attr Req","Adding Attr 4");
             memset (&uApiParams->uLeAddAttribute, 0, sizeof (RSI_BLE_CMD_ADD_GATT_ATTRIBUTE));
             uApiParams->uLeAddAttribute.AddAttRecord.ServiceHndlerPtr  = dbg_add_serv_resp.ServiceHndlerPtr;   // service handler from dd ervice response
             uApiParams->uLeAddAttribute.AddAttRecord.AttUUID.size      = 2;
             uApiParams->uLeAddAttribute.AddAttRecord.AttUUID.Val.val16 = RSI_BLE_GATT_RSI2_ATT_UUID;
             uApiParams->uLeAddAttribute.AddAttRecord.Hndl              = dbg_add_serv_resp.StartHndl + 4;
             uApiParams->uLeAddAttribute.AddAttRecord.Prop              = BT_LE_READ | BT_LE_WRITE | BT_LE_NOTIFY;
             uApiParams->uLeAddAttribute.AddAttRecord.DataLen           = 20;
             uApiParams->uLeAddAttribute.AddAttRecord.Data[0]           = 0;

             ret_val = rsi_ble_device_AddServiceAttribute(&uApiParams->uLeAddAttribute);
             break;
        case RSI_BLE_REQ_ADD_RSI_ATT5: 
             RSI_DPRINT(RSI_PL13,"add Attribute 5\r\n");
            RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","BLE","Tx","Add Attr Req","Adding Attr 5");
             memset (&uApiParams->uLeAddAttribute, 0, sizeof (RSI_BLE_CMD_ADD_GATT_ATTRIBUTE));
             uApiParams->uLeAddAttribute.AddAttRecord.ServiceHndlerPtr  = dbg_add_serv_resp.ServiceHndlerPtr;   // service handler from dd ervice response
             uApiParams->uLeAddAttribute.AddAttRecord.AttUUID.size      = 2;
             uApiParams->uLeAddAttribute.AddAttRecord.AttUUID.Val.val16 = RSI_BLE_GATT_CLIENT_CHAR;
             uApiParams->uLeAddAttribute.AddAttRecord.Hndl              = dbg_add_serv_resp.StartHndl + 5;
             uApiParams->uLeAddAttribute.AddAttRecord.Prop              = BT_LE_READ | BT_LE_WRITE;
             uApiParams->uLeAddAttribute.AddAttRecord.DataLen           = 2;
             uApiParams->uLeAddAttribute.AddAttRecord.Data[0]           = 0;
             uApiParams->uLeAddAttribute.AddAttRecord.Data[1]           = 0;

             ret_val = rsi_ble_device_AddServiceAttribute(&uApiParams->uLeAddAttribute);
             break;

        case RSI_BLE_REQ_SET_RSI_ATT4:
             {
                 static UINT08  tx_count = 0;

                 memset(&uApiParams->uLeSetLocalAttValue, 0, sizeof(RSI_BLE_CMD_SET_LOCAL_ATT_VALUE));
                 uApiParams->uLeSetLocalAttValue.Hndl    = RSI_BLE_GATT_CHANGE_RSI_ATT_HANDLE;
                 uApiParams->uLeSetLocalAttValue.DataLen = RSI_BLE_GATT_CHANGE_RSI_ATT_DATA_LEN + 1;
                 memcpy (uApiParams->uLeSetLocalAttValue.Data, RSI_BLE_GATT_CHANGE_RSI_ATT_DATA, RSI_BLE_GATT_CHANGE_RSI_ATT_DATA_LEN);
                 uApiParams->uLeSetLocalAttValue.Data[RSI_BLE_GATT_CHANGE_RSI_ATT_DATA_LEN] = ((tx_count++) % 10) + 0x30;
                 ret_val = rsi_ble_device_ChangeLocalAttValue(&uApiParams->uLeSetLocalAttValue);
             }
             break;

        default:
#ifdef RSI_DEBUG_PRINT
	         RSI_DPRINT(RSI_PL3,"WRONG/UNSUPPORTED CMD \n");
#endif
			 break;
    }
    
    return ret_val;    
}

