/**
 * @file       rsi_bt_config_init.c
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
#include "rsi_bt_global.h"
#include "rsi_bt_generic.h"
#include "rsi_bt_api.h"
#include "rsi_bt_config.h"
#include "rsi_app_util.h"
#include "rsi_lib_util.h"
#include "rsi_bt_app.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
 * Global Variables
 */

extern RSI_BT_APP_CB rsi_bt_AppControlBlock;

UINT08  rsi_bt_TransferBuffer[RSI_BT_MAX_PAYLOAD_SIZE]={"01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567"};
UINT08  rsi_bt_EIRDataBuffer[RSI_BT_MAX_PAYLOAD_SIZE] = {2,1,0,8,9,0x52,0x45,0x44,0x50,0x49,0x4E,0x45};  //Format is {length, type, Value} here length = type + value(in hex) bytes

static void rsi_bt_fill_bd_address(UINT08  *BDAddressBuf, UINT08  *UsrInitBDAddress);
extern void rsi_ascii_mac_address_to_6bytes_rev(UINT08 *hexAddr, INT08 *asciiMacAddress);

/*====================================================*/
/**
 * @fn             int16 rsi_init_struct(rsi_api *ptrStrApi)
 * @brief          Initialize the global parameter structure
 * @param[in]      rsi_api *ptrStrApi, pointer to the global parameter structure
 * @param[out]     none
 * @return         status
 *                 0  = SUCCESS
 * @description	
	* This function is used to initialize the global parameter structure with parameters
 * used to configure the Wi-Fi module.
 * 
 * @prerequisite 
	* rsi_sys_init should be done successfully. 		
 */
INT16 rsi_bt_init_struct(UINT16  CommandType)
{
  RSI_BT_API *uApiParams;
   
  
  uApiParams = rsi_bt_AppControlBlock.uBTApiInitParams;
  memset(uApiParams, 0, sizeof(RSI_BT_API));

    switch (CommandType) {


        case RSI_BT_REQ_SET_LOCAL_NAME:
             strcpy((char *)uApiParams->uSetLocalName.SetLocalNameFrameSnd.Name, RSI_BT_SET_LOCAL_NAME);
             uApiParams->uSetLocalName.SetLocalNameFrameSnd.NameLength = strlen(RSI_BT_SET_LOCAL_NAME);
             rsi_bt_set_local_name (&uApiParams->uSetLocalName);
             break;
        
        case RSI_BT_REQ_QUERY_LOCAL_NAME:
             rsi_bt_query_local_name();
             break;

        case RSI_BT_REQ_SET_LOCAL_COD:
             uApiParams->uSetLocalCOD.SetLocalCodFrameSnd.LocalCOD = RSI_BT_SET_LOCAL_COD;
             rsi_bt_set_local_cod (&uApiParams->uSetLocalCOD);
             break;

        case RSI_BT_REQ_QUERY_LOCAL_COD:
             rsi_bt_query_local_cod();
             break;
        
        case RSI_BT_REQ_QUERY_RSSI:
             rsi_bt_fill_bd_address(uApiParams->uQryRssi.QueryRssiFrameSnd.BDAddress, (UINT08 *)RSI_BT_QUERY_RSSI_ADDR); 
             rsi_bt_query_rssi(&uApiParams->uQryRssi);
             break;

        case RSI_BT_REQ_QUERY_LINK_QUALITY:
             rsi_bt_fill_bd_address(uApiParams->uQryLinkQuality.QueryLinkQualityFrameSnd.BDAddress, (UINT08 *)RSI_BT_QUERY_LINK_QUALITY_ADDR);
             rsi_bt_query_link_quality (&uApiParams->uQryLinkQuality);
             break;

        case RSI_BT_REQ_QUERY_LOCAL_BD_ADDRESS:
             rsi_bt_query_local_bd_address();
             break;

        case RSI_BT_REQ_SET_PROFILE_MODE:
             uApiParams->uSetProfMode.SetprofileModeFrameSnd.ProfileMode = RSI_BT_SET_PROFILE_MODE;
             rsi_bt_set_profile_mode (&uApiParams->uSetProfMode);
             break;

        case RSI_BT_REQ_SET_DISCV_MODE:
             uApiParams->uSetDiscvMode.SetDiscvModeFrameSnd.Mode = RSI_BT_SET_DISC_MODE;
             uApiParams->uSetDiscvMode.SetDiscvModeFrameSnd.Timeout = RSI_BT_SET_DISC_MODE_TIMEOUT;
             rsi_bt_set_discovery_mode (&uApiParams->uSetDiscvMode);
             break;

        case RSI_BT_REQ_QUERY_DISCOVERY_MODE:
             rsi_bt_query_discovery_mode ();
             break;

        case RSI_BT_REQ_SET_CONNECTABILITY_MODE:
             uApiParams->uSetConnMode.SetConnectabilityModeFrameSnd.ConnectabilityMode = RSI_BT_SET_CONN_MODE;
             rsi_bt_set_connectability_mode (&uApiParams->uSetConnMode);
             break;

        case RSI_BT_REQ_QUERY_CONNECTABILITY_MODE:
             rsi_bt_query_connectability_mode ();
             break;

        case RSI_BT_REQ_SET_PAIR_MODE:
             uApiParams->uSetPairMode.SetPairModeFrameSnd.PairMode = RSI_BT_SET_PAIR_MODE;
             rsi_bt_set_pair_mode (&uApiParams->uSetPairMode);
             break;
        
        case RSI_BT_REQ_QUERY_PAIR_MODE:
             rsi_bt_query_pair_mode ();
             break;
        
        case RSI_BT_REQ_REMOTE_NAME_REQUEST:
             rsi_bt_fill_bd_address(uApiParams->uRemNameReq.RemNameReqFrameSnd.BDAddress, (UINT08 *)RSI_BT_REM_NAME_REQ_ADDR);
             rsi_bt_remote_name_request (&uApiParams->uRemNameReq);
             break;

        case RSI_BT_REQ_REMOTE_NAME_REQUEST_CANCEL:
             rsi_bt_fill_bd_address(uApiParams->uRemNameReqCancel.RemNameReqCancelFrameSnd.BDAddress, (UINT08 *)RSI_BT_REM_NAME_REQ_CANCEL_ADDR);
             rsi_bt_remote_name_request_cancel(&uApiParams->uRemNameReqCancel);
             break;

        case RSI_BT_REQ_INQUIRY:
             uApiParams->uInq.InqFrameSnd.InquiryType = RSI_BT_INQ_TYPE;
             uApiParams->uInq.InqFrameSnd.Duration = (UINT32 )RSI_BT_INQ_DURATION;
             uApiParams->uInq.InqFrameSnd.MaximumDevicesToFind = RSI_BT_INQ_MAX_DEVICES;
             rsi_bt_inquiry(&uApiParams->uInq);
             break;

        case RSI_BT_REQ_INQUIRY_CANCEL:
             rsi_bt_inquiry_cancel();
             break;

        case RSI_BT_REQ_BOND:
             rsi_bt_fill_bd_address(uApiParams->uBond.BondFrameSnd.BDAddress, (UINT08 *)RSI_BT_BOND_ADDR);
             rsi_bt_bond (&uApiParams->uBond);
             break;

        case RSI_BT_REQ_BOND_CANCEL:
             rsi_bt_fill_bd_address(uApiParams->uBondCancel.BondCancelFrameSnd.BDAddress, (UINT08 *)RSI_BT_BOND_CANCEL_ADDR);
             rsi_bt_bond_cancel (&uApiParams->uBondCancel);
             break;
        
        case RSI_BT_REQ_UNBOND:
             rsi_bt_fill_bd_address(uApiParams->uUnbond.UnbondFrameSnd.BDAddress, (UINT08 *)RSI_BT_UNBOND_ADDR);
             rsi_bt_unbond(&uApiParams->uUnbond);
             break;

        case RSI_BT_REQ_SET_PIN_TYPE:
             uApiParams->uSetPinType.SetPinTypeFrameSnd.PINType = RSI_BT_SET_PIN_TYPE;
             rsi_bt_set_pin_type (&uApiParams->uSetPinType);
             break;
        
        case RSI_BT_REQ_QUERY_PIN_TYPE:
             rsi_bt_query_pin_type();
             break;
        
        case RSI_BT_REQ_USER_CONFIRMATION:
             rsi_bt_fill_bd_address(uApiParams->uUserConf.UserConfFrameSnd.BDAddress, (UINT08 *)RSI_BT_USER_CONF_ADDR);
             uApiParams->uUserConf.UserConfFrameSnd.Confirmation = RSI_BT_USER_CONF;
             rsi_bt_user_confirmation (&uApiParams->uUserConf);
             break;

        case RSI_BT_REQ_PASSKEY_REPLY:
             rsi_bt_fill_bd_address(uApiParams->uPasskeyReply.PasskeyReplyFrameSnd.BDAddress, (UINT08 *)RSI_BT_PASSKEY_ADDR);
             uApiParams->uPasskeyReply.PasskeyReplyFrameSnd.ReplyType = RSI_BT_PASSKEY_REPLY_TYPE;
             uApiParams->uPasskeyReply.PasskeyReplyFrameSnd.Passkey = (UINT32)RSI_BT_PASSKEY;
             rsi_bt_passkey_request_reply (&uApiParams->uPasskeyReply);
             break;

        case RSI_BT_REQ_PINCODE_REPLY:
             uApiParams->uPincodeReply.PincodeReplyFrameSnd.ReplyType = RSI_BT_PINCODE_REPLY_TYPE;

             if(RSI_BT_PINCODE_REPLY_ADDR != 0) {
               rsi_ascii_mac_address_to_6bytes_rev(uApiParams->uPincodeReply.PincodeReplyFrameSnd.BDAddress,(INT08 *) RSI_BT_PINCODE_REPLY_ADDR);   // Convert from BD address string to BD address.
             } else {
               memcpy ((INT08 *)uApiParams->uPincodeReply.PincodeReplyFrameSnd.BDAddress, (INT08 *)rsi_bt_AppControlBlock.RemoteBDAddress, RSI_BT_BD_ADDR_LEN);
             }
             strcpy((char *)uApiParams->uPincodeReply.PincodeReplyFrameSnd.Pincode, RSI_BT_PINCODE);
             rsi_bt_pincode_reply (&uApiParams->uPincodeReply);
             break;

        case RSI_BT_REQ_LINKEKY_REPLY:
             uApiParams->uLinkKeyReply.LinkKeyReplyFrameSnd.ReplyType = RSI_BT_LINKKEY_REPLY_TYPE;

             if(RSI_BT_LINKKEY_REPLY_ADDR != 0) {
               rsi_ascii_mac_address_to_6bytes_rev(uApiParams->uLinkKeyReply.LinkKeyReplyFrameSnd.BDAddress,(INT08 *) RSI_BT_LINKKEY_REPLY_ADDR);   // Convert from BD address string to BD address.
             } else {
               memcpy (uApiParams->uLinkKeyReply.LinkKeyReplyFrameSnd.BDAddress, rsi_bt_AppControlBlock.RemoteBDAddress, RSI_BT_BD_ADDR_LEN);
             }
             memcpy (uApiParams->uLinkKeyReply.LinkKeyReplyFrameSnd.LinkKey, rsi_bt_AppControlBlock.RemoteLinkKey, RSI_BT_LINK_KEY_LEN);
             rsi_bt_linkkey_reply (&uApiParams->uLinkKeyReply);
             break;

        case RSI_BT_REQ_QUERY_ROLE:
             rsi_bt_fill_bd_address(uApiParams->uQryRole.QueryRoleFrameSnd.BDAddress,(UINT08 *) RSI_BT_QUERY_ROLE_ADDR);
             rsi_bt_query_role (&uApiParams->uQryRole);
             break;

        case RSI_BT_REQ_SET_ROLE:
             rsi_bt_fill_bd_address(uApiParams->uSetRole.SetRoleFrameSnd.BDAddress, (UINT08 *)RSI_BT_SET_ROLE_ADDR);
             uApiParams->uSetRole.SetRoleFrameSnd.Role = RSI_BT_SET_ROLE;
             rsi_bt_set_role (&uApiParams->uSetRole);
             break;

        case RSI_BT_REQ_QUERY_SERVICES:
             rsi_bt_fill_bd_address(uApiParams->uQryServ.QueryServFrameSnd.BDAddress, (UINT08 *)RSI_BT_QUERY_SERV_ADDR);
             rsi_bt_query_services (&uApiParams->uQryServ);
             break;

        case RSI_BT_REQ_SEARCH_SERVICE:
             rsi_bt_fill_bd_address(uApiParams->uSearchServ.SearchServFrameSnd.BDAddress, (UINT08 *)RSI_BT_SEARCH_SERV_ADDR);
             uApiParams->uSearchServ.SearchServFrameSnd.ServiceUUID = (UINT32 )RSI_BT_SEARCH_SERV_UUID;
             /*uApiParams->uSearchServ.SearchServFrameSnd.ServiceUUID.size = RSI_BT_SEARCH_SERV_SIZE;
             uApiParams->uSearchServ.SearchServFrameSnd.ServiceUUID.Val.val16 = (UINT16 )RSI_BT_SEARCH_SERV_UUID;*/
             rsi_bt_search_service(&uApiParams->uSearchServ);
             break;

        case RSI_BT_REQ_SPP_CONNECT: 
             if(RSI_BT_SPP_CONN_ADDR != 0) {
               rsi_ascii_mac_address_to_6bytes_rev(uApiParams->uSPPConn.SppConnFrameSnd.BDAddress,(INT08 *) RSI_BT_SPP_CONN_ADDR);   // Convert from BD address string to BD address.
             } else {
               memcpy (uApiParams->uSPPConn.SppConnFrameSnd.BDAddress, rsi_bt_AppControlBlock.RemoteBDAddress, 6);
             }
             rsi_bt_spp_connect (&uApiParams->uSPPConn);
             break;

        case RSI_BT_REQ_SPP_DISCONNECT:
             if(RSI_BT_SPP_DISCONN_ADDR != 0) {
               rsi_ascii_mac_address_to_6bytes_rev(uApiParams->uSPPDisConn.SppDisconnFrameSnd.BDAddress, (INT08 *)RSI_BT_SPP_DISCONN_ADDR);   // Convert from BD address string to BD address.
             } else {
               uApiParams->uSPPDisConn.SppDisconnFrameSnd.BDAddress[0] = rsi_bt_AppControlBlock.RemoteBDAddress[0];
               uApiParams->uSPPDisConn.SppDisconnFrameSnd.BDAddress[1] = rsi_bt_AppControlBlock.RemoteBDAddress[1];
               uApiParams->uSPPDisConn.SppDisconnFrameSnd.BDAddress[2] = rsi_bt_AppControlBlock.RemoteBDAddress[2];
               uApiParams->uSPPDisConn.SppDisconnFrameSnd.BDAddress[3] = rsi_bt_AppControlBlock.RemoteBDAddress[3];
               uApiParams->uSPPDisConn.SppDisconnFrameSnd.BDAddress[4] = rsi_bt_AppControlBlock.RemoteBDAddress[4];
               uApiParams->uSPPDisConn.SppDisconnFrameSnd.BDAddress[5] = rsi_bt_AppControlBlock.RemoteBDAddress[5];
               //memcpy (uApiParams->uSPPConn.SppConnFrameSnd.BDAddress, rsi_bt_AppControlBlock.RemoteBDAddress, 6);
             }
             rsi_bt_spp_disconnect (&uApiParams->uSPPDisConn);
             break;

        case RSI_BT_REQ_SPP_TRANSFER:
             {
               //UINT16 ii;
               rsi_uint16_to_2bytes(uApiParams->uSPPTransfer.SppTransferFrameSnd.DataLength, RSI_BT_SPP_TX_LEN);
               memset(uApiParams->uSPPTransfer.SppTransferFrameSnd.Data, 0, RSI_BT_SPP_TX_LEN);
               /*   memset(rsi_bt_TransferBuffer, 0, RSI_BT_MAX_PAYLOAD_SIZE);
                    for(ii = 0; ii < 100; ii++)
                    {
                    rsi_bt_TransferBuffer[ii] = ('a'+ii);
                    }*/
               memcpy(uApiParams->uSPPTransfer.SppTransferFrameSnd.Data, RSI_BT_SPP_TX_DATA, RSI_BT_SPP_TX_LEN);
               rsi_bt_spp_transfer (&uApiParams->uSPPTransfer);
             }
             break;
        case RSI_BT_REQ_INIT:
             {
               rsi_bt_device_init();
             }
             break;
        case RSI_BT_REQ_DEINIT:
             {
               rsi_bt_device_deinit();
             }
             break;
        
        case RSI_BT_REQ_PER_TX:
             {
               uApiParams->uPerTransmit.PerTransmitFrameSnd.type            = 4;
               uApiParams->uPerTransmit.PerTransmitFrameSnd.enable          = RSI_BT_PER_TX_ENABLE          ;
               rsi_ascii_mac_address_to_6bytes_rev(uApiParams->uPerTransmit.PerTransmitFrameSnd.bt_addr, (INT08 *)RSI_BT_PER_TX_MAC_ADD);   // Convert from BD address string to BD address.
               uApiParams->uPerTransmit.PerTransmitFrameSnd.pkt_type        = RSI_BT_PER_TX_PKT_TYPE        ;
               uApiParams->uPerTransmit.PerTransmitFrameSnd.pkt_length[0]   = RSI_BT_PER_TX_PKT_LENGTH & 0xFF     ;
               uApiParams->uPerTransmit.PerTransmitFrameSnd.pkt_length[1]   = ((RSI_BT_PER_TX_PKT_LENGTH >> 8) & 0xFF)    ;
               uApiParams->uPerTransmit.PerTransmitFrameSnd.link_type       = RSI_BT_PER_TX_LINK_TYPE       ;
               uApiParams->uPerTransmit.PerTransmitFrameSnd.edr_ind         = RSI_BT_PER_TX_EDR_INDICATION  ;
               uApiParams->uPerTransmit.PerTransmitFrameSnd.rx_channel      = RSI_BT_PER_TX_RX_CHANNEL      ;
               uApiParams->uPerTransmit.PerTransmitFrameSnd.tx_channel      = RSI_BT_PER_TX_TX_CHANNEL      ;
               uApiParams->uPerTransmit.PerTransmitFrameSnd.scrambled_seed  = RSI_BT_PER_TX_SCRAMBLED_SEED  ;
               uApiParams->uPerTransmit.PerTransmitFrameSnd.num_pkts        = RSI_BT_PER_TX_NUM_PKTS        ;
               uApiParams->uPerTransmit.PerTransmitFrameSnd.payload_type    = RSI_BT_PER_TX_PAYLOAD_TYPE    ;
               uApiParams->uPerTransmit.PerTransmitFrameSnd.protocol_mode   = RSI_BT_PER_TX_PROTOCOL_MODE   ;
               uApiParams->uPerTransmit.PerTransmitFrameSnd.le_channel      = RSI_BT_PER_TX_LE_CHANNEL      ;
               uApiParams->uPerTransmit.PerTransmitFrameSnd.tx_power_index  = RSI_BT_PER_TX_POWER_INDEX     ;
               uApiParams->uPerTransmit.PerTransmitFrameSnd.tx_mode         = RSI_BT_PER_TX_MODE            ;
               uApiParams->uPerTransmit.PerTransmitFrameSnd.frequency_hop   = RSI_BT_PER_TX_FREQUENCY_HOP   ;
               uApiParams->uPerTransmit.PerTransmitFrameSnd.ant_sel         = RSI_BT_PER_TX_ANT_SEL         ;

               rsi_bt_per_transmit (&uApiParams->uPerTransmit);
             }
             break;

        case RSI_BT_REQ_PER_RX:
             {
               uApiParams->uPerReceive.PerReceiveFrameSnd.type            = 5;
               uApiParams->uPerReceive.PerReceiveFrameSnd.enable          = RSI_BT_PER_RX_ENABLE          ;

               rsi_ascii_mac_address_to_6bytes_rev(uApiParams->uPerReceive.PerReceiveFrameSnd.bt_addr, (INT08 *)RSI_BT_PER_RX_MAC_ADD);   // Convert from BD address string to BD address.
               //uApiParams->uPerReceive.PerReceiveFrameSnd.bt_addr[6]      = RSI_BT_PER_RX_MAC_ADD         ;
               uApiParams->uPerReceive.PerReceiveFrameSnd.pkt_length      = RSI_BT_PER_RX_PKT_LENGTH      ;
               uApiParams->uPerReceive.PerReceiveFrameSnd.pkt_type        = RSI_BT_PER_RX_PKT_TYPE        ;
               uApiParams->uPerReceive.PerReceiveFrameSnd.link_type       = RSI_BT_PER_RX_LINK_TYPE       ;
               uApiParams->uPerReceive.PerReceiveFrameSnd.edr_ind         = RSI_BT_PER_RX_EDR_INDICATION  ;
               uApiParams->uPerReceive.PerReceiveFrameSnd.rx_channel      = RSI_BT_PER_RX_RX_CHANNEL      ;
               uApiParams->uPerReceive.PerReceiveFrameSnd.tx_channel      = RSI_BT_PER_RX_TX_CHANNEL      ;
               uApiParams->uPerReceive.PerReceiveFrameSnd.scrambled_seed  = RSI_BT_PER_RX_SCRAMBLED_SEED  ;
               uApiParams->uPerReceive.PerReceiveFrameSnd.payload_type    = RSI_BT_PER_RX_PAYLOAD_TYPE    ;
               uApiParams->uPerReceive.PerReceiveFrameSnd.protocol_mode   = RSI_BT_PER_RX_PROTOCOL_MODE   ;
               uApiParams->uPerReceive.PerReceiveFrameSnd.le_channel      = RSI_BT_PER_RX_LE_CHANNEL      ;
               uApiParams->uPerReceive.PerReceiveFrameSnd.frequency_hop   = RSI_BT_PER_RX_FREQUENCY_HOP   ;
               uApiParams->uPerReceive.PerReceiveFrameSnd.ant_sel         = RSI_BT_PER_RX_ANT_SEL         ;

               rsi_bt_per_receive (&uApiParams->uPerReceive);
             }
             break;
        case RSI_BT_REQ_PER_STATS:
             {
               sleep(1);
               uApiParams->uPerStats.PerStatsFrameSnd.type            = 8;
               rsi_bt_per_stats (&uApiParams->uPerStats);
             }
             break;

        case RSI_BT_REQ_CW_MODE:
             {

               uApiParams->uPerCw.PerCwFrameSnd.type            =  13;
               uApiParams->uPerCw.PerCwFrameSnd.channel         = RSI_CW_MODE_CHANNEL;
               uApiParams->uPerCw.PerCwFrameSnd.cw_mode         = RSI_CW_MODE        ;
               uApiParams->uPerCw.PerCwFrameSnd.cw_type         = 1       ;
               uApiParams->uPerCw.PerCwFrameSnd.ant_sel         = RSI_CW_ANT_SEL     ;
               rsi_bt_per_cw_mode (&uApiParams->uPerCw);
               break;                                             
             }

        case RSI_BT_REQ_START_SNIFF_MODE:
             rsi_bt_fill_bd_address(uApiParams->uSniffEnable.SniffModeFrameSend.BDAddress, (UINT08 *)RSI_BT_SNIFF_BD_ADDR); 
             uApiParams->uSniffEnable.SniffModeFrameSend.SniffMaxIntr = RSI_BT_SNIFF_MAX_INTERVAL;
             uApiParams->uSniffEnable.SniffModeFrameSend.SniffMinIntr = RSI_BT_SNIFF_MIN_INTERVAL;
             uApiParams->uSniffEnable.SniffModeFrameSend.SniffAttempt = RSI_BT_SNIFF_ATTEMPT;
             uApiParams->uSniffEnable.SniffModeFrameSend.SniffTimeout = RSI_BT_SNIFF_TIME_OUT;
             rsi_bt_start_sniff_mode (&uApiParams->uSniffEnable);
             break;

        case RSI_BT_REQ_STOP_SNIFF_MODE:
             rsi_bt_fill_bd_address(uApiParams->uSniffDisable.SniffExitFrameSend.BDAddress, (UINT08 *)RSI_BT_SNIFF_BD_ADDR); 
             rsi_bt_exit_sniff_mode (&uApiParams->uSniffDisable);
             break;

        case RSI_BT_REQ_SNIFF_SUBRATING_MODE:
             /*rsi_bt_fill_bd_address(uApiParams->uSniffSubrating.SniffSubratingFrameSend.BDAddress, (UINT08 *)RSI_BT_SNIFF_BD_ADDR); 
             uApiParams->uSniffSubrating.SniffSubratingFrameSend.MaxLatency = ;
             uApiParams->uSniffSubrating.SniffSubratingFrameSend.MinRemoteTimeout = ;
             uApiParams->uSniffSubrating.SniffSubratingFrameSend.MinLocalTimeout = ;
             rsi_bt_sniff_subrating_mode (&uApiParams->uSniffSubrating);*/
             break;

        case RSI_BT_REQ_SSP_ENABLE:
             uApiParams->uSSPEnable.SSPModeFrameSend.Enable = RSI_BT_SPP_MODE;
             uApiParams->uSSPEnable.SSPModeFrameSend.IO_Capability = RSI_BT_IO_CAPABILITY;
             rsi_bt_enable_ssp_mode (&uApiParams->uSSPEnable);
             break;

        case RSI_BT_REQ_FEATURE_BIT_MAP:
             uApiParams->uFeatureBitMap.BitMapFrameSend.Feature_BitMap = RSI_BT_FEATURE_BITMAP;
             rsi_bt_enable_set_feature_bitmap (&uApiParams->uFeatureBitMap);
             break;
        case RSI_BT_SET_ANTENNA_TX_POWER_LEVEL:
             uApiParams->uAntennaTxPowerLevel.AntennaTxPowerLevelsnd.ProtocolMode = 1;               //  1 for BT
             uApiParams->uAntennaTxPowerLevel.AntennaTxPowerLevelsnd.TxPower      = RSI_BT_TX_POWER;
             rsi_bt_set_antenna_tx_power_value(&uApiParams->uAntennaTxPowerLevel);
             break;

        case RSI_BT_SET_EIR_DATA:
             uApiParams->uSetEIRData.EIRDatasnd.FECRequired = 0;               //  Not required
             uApiParams->uSetEIRData.EIRDatasnd.DataLength  = RSI_BT_EIR_DATA_LENGTH;
             memcpy ((UINT08 *)uApiParams->uSetEIRData.EIRDatasnd.EIRData, RSI_BT_EIR_DATA, RSI_BT_EIR_DATA_LENGTH);
             
             rsi_bt_eir_data_value(&uApiParams->uSetEIRData);
             break;
    }

  return 0;    
}


static void rsi_bt_fill_bd_address(UINT08  *BDAddressBuf, UINT08  *UsrInitBDAddress)
{
  if(RSI_BT_SPP_DISCONN_ADDR != 0) 
  {
    rsi_ascii_mac_address_to_6bytes_rev(BDAddressBuf, (INT08 *) UsrInitBDAddress);   // Convert from BD address string to BD address.    
  } 
  else 
  {
    BDAddressBuf[0] = rsi_bt_AppControlBlock.RemoteBDAddress[0];
    BDAddressBuf[1] = rsi_bt_AppControlBlock.RemoteBDAddress[1];
    BDAddressBuf[2] = rsi_bt_AppControlBlock.RemoteBDAddress[2];
    BDAddressBuf[3] = rsi_bt_AppControlBlock.RemoteBDAddress[3];
    BDAddressBuf[4] = rsi_bt_AppControlBlock.RemoteBDAddress[4];
    BDAddressBuf[5] = rsi_bt_AppControlBlock.RemoteBDAddress[5];
  }
}

