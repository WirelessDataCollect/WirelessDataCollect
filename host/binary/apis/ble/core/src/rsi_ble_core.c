/**
 * @file      rsi_ble_core.c
 *
 * @version   1.0
 * @date      2014-Aug-22
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief Contains BLE Core API's.
 *
 * @section Description
 * This file contains a) Advertise function.
 *  		      b) Scan function.
 *   		      c) Connect function.
 *    		      d) Disconnect function.
 *    		      e) Query Device State function.
 *    		      f) Start encryption functon.
 *    		      g) SMP Pair Request function.
 *    		      h) SMP Response function.
 *    		      i) SMP passkey function.
 *    		      j) Set advertise data.
 *    		      k) LE ping timeout.
 *                l) Set Random Address.
 *    		     	     
 */		      	


/**
 * Includes
 */
#include "rsi_global.h"
#include "rsi_ble_global.h"
#include "rsi_ble_api.h"
#include "rsi_bt_api.h"


/**
 * Global Variables
 */


/*===========================================================================
 *	
 * @fn          INT16 rsi_ble_advertise(RSI_BLE_CMD_ADVERTISE *LEAdvertise)
 * @brief       Sends the Advertise command to the BLE module
 * @param[in]   RSI_BLE_CMD_ADVERTISE *LEAdvertise, Pointer to Set Advertise structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *               0  = SUCCESS
 * @section description 
 * This API is used to expose (or) advertise about local device to remote LE devices. 
 *
 * @section prerequisite 
 */

INT16 rsi_ble_advertise(RSI_BLE_CMD_ADVERTISE *uLEAdvertise)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL13,"\r\n\nSet Advertise Mode Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdLEAdv, (UINT08 *)uLEAdvertise, sizeof(RSI_BLE_CMD_ADVERTISE));
  return retval;
}





/*===========================================================================
 *
 * @fn          INT16 rsi_ble_scan(RSI_BLE_CMD_SCAN *LEScan)
 * @brief       Sends the  Scan command to the BLE module
 * @param[in]   RSI_BLE_CMD_SCAN *LEScan, Pointer to Scan structure  			
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to scan for remote LE advertise devices. 
 *
 * @section prerequisite 
 */

INT16 rsi_ble_scan(RSI_BLE_CMD_SCAN *uLEScan)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nScan starts ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdLEScan, (UINT08 *)uLEScan, sizeof(RSI_BLE_CMD_SCAN));
  return retval;
}




/*===========================================================================
 *
 * @fn          INT16 rsi_ble_connect(RSI_BLE_CMD_CONNECT *LEConnect)	
 * @brief       Sends the connect command to the BLE module
 * @param[in]   RSI_BLE_CMD_CONNECT *LEConnect,Pointer to connect structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to create connection with remote LE device. .
 *
 * @section prerequisite 
 */

INT16 rsi_ble_connect(RSI_BLE_CMD_CONNECT *uLEConnect)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n Connection start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdLEConn, (UINT08 *)uLEConnect, sizeof(RSI_BLE_CMD_CONNECT));
  return retval;
}




/*===========================================================================
 *
 * @fn          INT16 rsi_ble_disconnect(void)
 * @brief       Sends the disconnect command to the BLE module
 * @param[in]   none
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to cancel create connection command or disconnect HCI connection of already connected device.
 *
 * @section prerequisite 
 */

INT16 rsi_ble_disconnect(RSI_BLE_CMD_DISCONNECT  *uLEDisconnect)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nDisconnect start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdLEDisconn, (UINT08 *)uLEDisconnect, sizeof (RSI_BLE_CMD_DISCONNECT));
  return retval;
}




/*===========================================================================
 *
 * @fn          INT16 rsi_ble_query_device_state(void)
 * @brief       Sends the Query Device State command to the BLE module
 * @param[in]   none
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to get local LE device state.
 *
 * @section prerequisite 
 */
INT16 rsi_ble_query_device_state(void)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery Device State start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryDevstate, NULL, 0);
  return retval;
}




/*===========================================================================
 *
 * @fn          INT16 rsi_ble_start_encryption(void)
 * @brief       Sends the start Encryption command to the BLE module
 * @param[in]   none
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to .
 *
 * @section prerequisite 
 */

INT16 rsi_ble_start_encryption(RSI_BLE_CMD_ENCRYPTTION  *uLEEncrypt)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nStart Encryption start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdStartEnc, (UINT08 *)uLEEncrypt, sizeof (RSI_BLE_CMD_ENCRYPTTION));
  return retval;
}



/*===========================================================================
 *
 * @fn          INT16 rsi_ble_smp_pair_request(RSI_BLE_CMD_SMP_PAIR_REQUEST *SMPPairRequest)	
 * @brief       Sends the smp pair request command to the BLE module
 * @param[in]   RSI_BLE_CMD_SMP_PAIR_REQUEST *SMPPairRequest, Pointer to SMP Pair Request structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to send the SMP pair request command to connected remote device.
 *
 * @section prerequisite 
 */
INT16 rsi_ble_smp_pair_request(RSI_BLE_CMD_SMP_PAIR_REQUEST *uSMPPairRequest)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n SMP Pair Request start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSMPPairReq, (UINT08 *)uSMPPairRequest, sizeof(RSI_BLE_CMD_SMP_PAIR_REQUEST));
  return retval;
}



/*===========================================================================
 *
 * @fn          INT16 rsi_ble_smp_response(RSI_BLE_CMD_SMP_RESPONSE *SMPResponse)
 * @brief       Sends the smp response command to the BLE module
 * @param[in]   RSI_BLE_CMD_SMP_RESPONSE *SMPResponse, Pointer to SMP Response structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to send SMP response command to the BLE module.
 *
 * @section prerequisite 
 */
INT16 rsi_ble_smp_response(RSI_BLE_CMD_SMP_RESPONSE *uSMPResponse)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n SMP Response start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSMPResp, (UINT08 *)uSMPResponse, sizeof(RSI_BLE_CMD_SMP_RESPONSE));
  return retval;
}



/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_ble_smp_passkey(RSI_BLE_CMD_SMP_PASSKEY *SMPPasskey)                                                                                                                                             													      
 * @brief       Sends the smp passkey command to the BLE module                                                  													      
 * @param[in]   RSI_BLE_CMD_SMP_PASSKEY *SMPPasskey, Pointer to SMP Passkey structure                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to send SMP Pass key command to the module.                                                                                     													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */                                                                                                          													      
 INT16 rsi_ble_smp_passkey(RSI_BLE_CMD_SMP_PASSKEY *uSMPPasskey)                                                                                                            													                                                              													      
{                                                                                                            													      
  INT16          retval;                                                                                     													      
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n SMP passkey start ");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSMPPasskey, (UINT08 *)uSMPPasskey, sizeof(RSI_BLE_CMD_SMP_PASSKEY));													      
  return retval;                                                                                             													      
}                                                                                                            													      
/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_ble_set_advertise_data(RSI_BLE_CMD_SET_ADVERTISE_DATA *uSetadvertisedata)                                                                                                                                             													      
 * @brief       Sends the advertise data command to the BLE module                                                  													      
 * @param[in]   RSI_BLE_CMD_SET_ADVERTISE_DATA *uSetAdvertiseData, Pointer to Set advertise data  structure                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to prepare and send the advertise data command to the module.                                                                                     													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */                                                                                                          													      
 INT16 rsi_ble_set_advertise_data(RSI_BLE_CMD_SET_ADVERTISE_DATA *uSetAdvertiseData)                              
{                                                                                                            													      
  INT16          retval;                                                                                     													      
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n Set advertise data ");                                                            													      
#endif                                                                                                       													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetAdvertiseData, (UINT08 *)uSetAdvertiseData, sizeof(RSI_BLE_CMD_SET_ADVERTISE_DATA));													      
  return retval;                                                                                             													      
}                           
/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_ble_set_random_address(RSI_BLE_CMD_SET_RANDOM_ADDRESS *uSetRandAdd)                                                                                                                                             													      
 * @brief       Sends the set random address command to the BLE module                                                  													      
 * @param[in]   RSI_BLE_CMD_SET_RANDOM_ADDRESS *uSetRandAdd, Pointer to Set advertise data  structure                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to set and send the random address command to the module.                                                                                     													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */                                                                                                          													      
 INT16 rsi_ble_set_random_address(RSI_BLE_CMD_SET_RANDOM_ADDRESS *uSetRandAdd)                              
{                                                                                                            													      
  INT16          retval;                                                                                     													      
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n Set Random Adsress ");                                                            													      
#endif                                                                                                       													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetRandAdd, (UINT08 *)uSetRandAdd, sizeof(RSI_BLE_CMD_SET_RANDOM_ADDRESS));													      
  return retval;                                                                                             													      
}           

/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_ble_set_antenna_tx_power_value(RSI_BLE_CMD_SET_ANTENNA_TX_POWER_VLAUE *uSetAntennaTxPower)                                                                                                                                             													      
 * @brief       Sends the set Tx power value in BLE                                                  													      
 * @param[in]   RSI_BLE_CMD_SET_ANTENNA_TX_POWER_VLAUE *uSetAntennaTxPower, Pointer to Set antenna tx power structure                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to set BLE Tx power to the Antenna.                                                                                     													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */                                                                                                          													      
 INT16 rsi_ble_set_antenna_tx_power_value(RSI_BLE_CMD_SET_ANTENNA_TX_POWER_VLAUE * uSetAntennaTxPower)
{                                                                                                            													      
  INT16          retval;                                                                                     													      
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n Set  BLE Tx power value ");                                                            													      
#endif                                                                                                       													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetTxPowerValue, (UINT08 *)uSetAntennaTxPower, sizeof(RSI_BLE_CMD_SET_ANTENNA_TX_POWER_VLAUE));													      
  return retval;                                                                                             													      
}           
											      
/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_ble_white_list(RSI_BLE_CMD_WHITE_LIST *uBleWhiteList)                                                                                                                                             													      
 * @brief       Add,Delete and clear all white list                                                  													      
 * @param[in]   RSI_BLE_CMD_WHITE_LIST *uBleWhiteList, Pointer to Add,Delete and clear all white list structure                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to Add,Delete and clear all white list      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */                                                                                                          													      
INT16 rsi_ble_white_list(RSI_BLE_CMD_WHITE_LIST *uBleWhiteList)                                                                                                                                             													      
{                                                                                                            													      
  INT16          retval;                                                                                     													      
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n BLE White List cmd \n");                                                            													      
#endif                                                                                                       													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdBleWhiteList, (UINT08 *)uBleWhiteList, sizeof(RSI_BLE_CMD_WHITE_LIST));													      
  return retval;                                                                                             													      
}           

/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_ble_set_ping_timeout(RSI_BLE_CMD_SET_PING_TIMEOUT *uSetLePingTimeout)                                                                                                                                             													      
 * @brief       Sets the BLE ping (Authenticated Payload Timeout) timeout to the BLE module
 * @param[in]   RSI_BLE_CMD_SET_PING_TIMEOUT *uSetLePingTimeout, Pointer to Set le ping timeout  structure                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to send the set le ping timeout command to the module.                                                                                     													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */                                                                                                          													      
 INT16 rsi_ble_set_ping_timeout(RSI_BLE_CMD_SET_PING_TIMEOUT *uSetLePingTimeout)                              
{                                                                                                            													      
  INT16          retval;                                                                                     													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n Set le ping timeout");                                                            													      
#endif                                                                                                       				
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetPingTimeout, (UINT08 *)uSetLePingTimeout, sizeof(RSI_BLE_CMD_SET_PING_TIMEOUT));													      
  return retval;                                                                                             													      
}           


/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn         INT16 rsi_ble_get_ping_timeout(void)                                                                                                                                             													      
 * @brief      Gets the BLE ping (Authenticated Payload Timeout) timeout from the BLE module
 * @param[in]  none 	      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to send the get ping timeout command to the module.                                                                                     													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */                                                                                                          													      
 INT16 rsi_ble_get_ping_timeout(void)                              

{                                                                                                            													      
  INT16          retval;                                                                                     													      
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n Get le ping timeout");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdGetPingTimeout,NULL, 0);													      
  return retval;                                                                                             													      
}               



    
/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT08 clear_scan_resp(void)
 * @brief       clear the scaned device list
 * @param[in]  	none                                  													      
 * @param[out]  none                                                                                         													      
 * @return      none
 *
 * @section description                                                                                      													      
 * This API is used to cleat the scaned device list.
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

void  clear_scan_resp ()
{
    remote_dev_count = 0;
    memset (remote_dev_list, 0, sizeof (remote_dev_list));
}

/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT08 update_scan_resp(UINT08  *p_resp_buf, UINT16   resp_len)
 * @brief       update the scaned device list
 * @param[in]  	none                                  													      
 * @param[out]  none                                                                                         													      
 * @return      none
 *
 * @section description                                                                                      													      
 * This API is used to update the scaned device list.
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

void  update_scan_resp (UINT08  *p_resp_buf,
                        UINT16   resp_len)
{
    RSI_BLE_EVENT_RESP_ADVERTISE_REPORT  *p_scan_resp;
    UINT08                                ix;
    UINT08                                dev_found;


    p_scan_resp = (RSI_BLE_EVENT_RESP_ADVERTISE_REPORT *)p_resp_buf;

    dev_found = 0;
    if (remote_dev_count != 0) {
        for (ix = 0; ix < remote_dev_count; ix++) {
            if (!memcmp (remote_dev_list[ix], p_scan_resp->BDAddress, 6)) {
                dev_found = 1;
                break;
            }
        }
    }

    if ((dev_found        ==                            0) &&
        (remote_dev_count  < (MAX_NBR_OF_REMOET_DEVS - 1))) {

        memcpy (remote_dev_list[remote_dev_count], p_scan_resp->BDAddress, 6);
        remote_dev_count++;
    }

    return;
}

/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT08 update_connected_devices(UINT08  *p_resp_buf, UINT16   resp_len)
 * @brief       update the connection device list
 * @param[in]  	none                                  													      
 * @param[out]  none                                                                                         													      
 * @return      none
 * @section description                                                                                      													      
 * This API is used to update the connected device list.
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

void  update_connected_devices (UINT08  *p_resp_buf,
                                UINT16   resp_len)
{
    RSI_BLE_EVENT_RESP_CONNECTION_STATUS  *p_conn_evnt;
    UINT08                                 ix;
    UINT08                                 dev_found;


    p_conn_evnt = (RSI_BLE_EVENT_RESP_CONNECTION_STATUS *)p_resp_buf;

    dev_found = 0;
    if (connected_dev_count != 0) {
        for (ix = 0; ix < connected_dev_count; ix++) {
            if (!memcmp (connected_dev_list[ix], p_conn_evnt->BDAddress, 6)) {
                dev_found = 1;
                break;
            }
        }
    }

    if ((dev_found        ==                            0) &&
        (connected_dev_count  < (MAX_NBR_OF_REMOET_DEVS - 1))) {

        memcpy (connected_dev_list[connected_dev_count], p_conn_evnt->BDAddress, 6);
        connected_dev_count++;
    }

    return;
}

/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT08 remove_connected_devices(UINT08  *p_resp_buf, UINT16   resp_len)
 * @brief       removed disconnected device from the list
 * @param[in]  	none                                  													      
 * @param[out]  none                                                                                         													      
 * @return      none
 * @section description                                                                                      													      
 * This API is used to remove from the connected device list
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

void  remove_connected_devices (UINT08  *p_resp_buf,
                                UINT16   resp_len)
{
    RSI_BLE_EVENT_DISCONNECTION_STATUS  *p_disconn_evnt;
    UINT08                      ix, ix1;
    UINT08                      dev_found;


    p_disconn_evnt = (RSI_BLE_EVENT_DISCONNECTION_STATUS *)p_resp_buf;

    dev_found = 0;
    if (connected_dev_count != 0) {
        for (ix = 0; ix < connected_dev_count; ix++) {
            if (!memcmp (connected_dev_list[ix], p_disconn_evnt->BDAddress, 6)) {
                dev_found = 1;
                break;
            }
        }
    }

    if (dev_found == 1) {
        for (ix1 = ix; ix1 < (connected_dev_count - 1); ix1++) {
            memcpy (connected_dev_list[ix1], connected_dev_list[ix1 + 1], 6);
        }
        memset (connected_dev_list[ix1], 0, sizeof (connected_dev_list[ix1]));
        connected_dev_count--;
    }

    return;
}

/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT08 GetScanDevIndex(void)                                                                                                                                             													      
 * @brief       get the scan devices index value.
 * @param[in]  	none                                  													      
 * @param[out]  none                                                                                         													      
 * @return      device index                                                                                      													      
 *              -1 = invalid index
 *              0 to 5 = device index
 * @section description                                                                                      													      
 * 
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT08  GetScanDevIndex ()
{
    int  ix, ix1;


    for (ix = 0; ix < remote_dev_count; ix++) {
        printf ("%d, ", ix);
        for (ix1 = 0; ix1 < 6; ix1++) {
            printf ("%02X", remote_dev_list[ix][5-ix1]);
            if (ix1 < 5) {
                printf ("-");
            }
        }
        printf ("\r\n");
    }

    printf ("enter scan device index: ");
    scanf ("%d", &ix);

    if ((ix >= 0) && (ix < remote_dev_count)){
        return ix;
    }

    return ((UINT08)-1);
}

/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT08 GetRemoteDevIndex(void)                                                                                                                                             													      
 * @brief       connected BLE Device index                                                  													      
 * @param[in]  	none                                  													      
 * @param[out]  none                                                                                         													      
 * @return      device index                                                                                      													      
 *              -1 = invalid index
 *              0 to 5 = device index
 * @section description                                                                                      													      
 * This API is used to initialise the BLE module.                                                                                      													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT08  GetConnectedDevIndex (void)
{
    int  ix, ix1;


    for (ix = 0; ix < connected_dev_count; ix++) {
        printf ("%d, ", ix);
        for (ix1 = 0; ix1 < 6; ix1++) {
            printf ("%02X", connected_dev_list[ix][5-ix1]);
            if (ix1 < 5) {
                printf ("-");
            }
        }
        printf ("\r\n");
    }

    printf ("enter device index: ");
    scanf ("%d", &ix);

    if ((ix >= 0) && (ix < connected_dev_count)){
        return ix;
    }

    return ((UINT08)-1);
}
