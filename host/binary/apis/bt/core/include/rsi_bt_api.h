/**
 * @file     rsi_bt_api.h
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

#ifndef _BTAPI_H_
#define _BTAPI_H_

/**
 * Include Files
 */
#include "rsi_bt_global.h"


#ifdef __cplusplus
extern "C"{
#endif


#define  RSI_BT_REQ_SET_LOCAL_NAME                        0x0001
#define  RSI_BT_REQ_QUERY_LOCAL_NAME                      0x0002
#define  RSI_BT_REQ_SET_LOCAL_COD                         0x0003
#define  RSI_BT_REQ_QUERY_LOCAL_COD                       0x0004
#define  RSI_BT_REQ_QUERY_RSSI                            0x0005
#define  RSI_BT_REQ_QUERY_LINK_QUALITY                    0x0006
#define  RSI_BT_REQ_QUERY_LOCAL_BD_ADDRESS                0x0007

#define  RSI_BT_REQ_INIT				 				                  0x008D
#define  RSI_BT_REQ_DEINIT				  				              0x008E
#define  RSI_BT_REQ_ANTENNA_SELECT                        0x008F
//#define  RSI_BT_REQ_CONFIG_ENABLE                         0x0090
#define  RSI_BT_REQ_LINKEKY_REPLY                         0x0091

//! Request Frame Codes
#define  RSI_BT_REQ_SET_PROFILE_MODE                      0x0008
#define  RSI_BT_REQ_SET_DISCV_MODE                        0x0009
#define  RSI_BT_REQ_QUERY_DISCOVERY_MODE                  0x000A
#define  RSI_BT_REQ_SET_CONNECTABILITY_MODE               0x000B
#define  RSI_BT_REQ_QUERY_CONNECTABILITY_MODE             0x000C
#define  RSI_BT_REQ_SET_PAIR_MODE                         0x000D
#define  RSI_BT_REQ_QUERY_PAIR_MODE                       0x000E
#define  RSI_BT_REQ_REMOTE_NAME_REQUEST                   0x000F
#define  RSI_BT_REQ_REMOTE_NAME_REQUEST_CANCEL            0x0010
#define  RSI_BT_REQ_INQUIRY                               0x0011
#define  RSI_BT_REQ_INQUIRY_CANCEL                        0x0012
#define  RSI_BT_REQ_BOND                                  0x0013
#define  RSI_BT_REQ_BOND_CANCEL                           0x0014
#define  RSI_BT_REQ_UNBOND                                0x0015
#define  RSI_BT_REQ_SET_PIN_TYPE                          0x0016
#define  RSI_BT_REQ_QUERY_PIN_TYPE                        0x0017
#define  RSI_BT_REQ_USER_CONFIRMATION                     0x0018
#define  RSI_BT_REQ_PASSKEY_REPLY                         0x0019
#define  RSI_BT_REQ_PINCODE_REPLY                         0x001A
#define  RSI_BT_REQ_QUERY_ROLE                            0x001B
#define  RSI_BT_REQ_SET_ROLE                              0x001C
#define  RSI_BT_REQ_QUERY_SERVICES                        0x001D
#define  RSI_BT_REQ_SEARCH_SERVICE                        0x001E
#define  RSI_BT_REQ_SPP_CONNECT                           0x001F
#define  RSI_BT_REQ_SPP_DISCONNECT                        0x0020
#define  RSI_BT_REQ_SPP_TRANSFER                          0x0021
#define  RSI_BT_SET_ANTENNA_TX_POWER_LEVEL                0x00A7
#define  RSI_BT_SET_EIR_DATA                              0x00A9


#define  RSI_BT_REQ_PER_TX                                0x0098
#define  RSI_BT_REQ_PER_RX                                0x0099
#define  RSI_BT_REQ_PER_STATS                             0x009A
#define  RSI_BT_REQ_CW_MODE                               0x009B

#define  RSI_BT_REQ_START_SNIFF_MODE                      0x009D
#define  RSI_BT_REQ_STOP_SNIFF_MODE                       0x009E
#define  RSI_BT_REQ_SNIFF_SUBRATING_MODE                  0x009F
#define  RSI_BT_REQ_SSP_ENABLE                            0x00A0
#define  RSI_BT_REQ_FEATURE_BIT_MAP                       0x00A6

//! Response Frame Codes
#define  RSI_BT_RSP_CARD_READY                            0x0505
#define  RSI_BT_RSP_SET_LOCAL_NAME                        0x0001
#define  RSI_BT_RSP_QUERY_LOCAL_NAME                      0x0002
#define  RSI_BT_RSP_SET_LOCAL_COD                         0x0003
#define  RSI_BT_RSP_QUERY_LOCAL_COD                       0x0004
#define  RSI_BT_RSP_QUERY_RSSI                            0x0005
#define  RSI_BT_RSP_QUERY_LINK_QUALITY                    0x0006
#define  RSI_BT_RSP_QUERY_LOCAL_BD_ADDRESS                0x0007

#define  RSI_BT_RSP_INIT				 				                  0x008D
#define  RSI_BT_RSP_DEINIT				  				              0x008E
#define  RSI_BT_RSP_ANTENNA_SELECT                        0x008F
//#define  RSI_BT_RSP_CONFIG_ENABLE                         0x0090
#define  RSI_BT_RSP_LINKKEY_REPLY                         0x0091

#define  RSI_BT_RSP_SET_PROFILE_MODE                      0x0008
#define  RSI_BT_RSP_SET_DISCV_MODE                        0x0009
#define  RSI_BT_RSP_QUERY_DISCOVERY_MODE                  0x000A
#define  RSI_BT_RSP_SET_CONNECTABILITY_MODE               0x000B
#define  RSI_BT_RSP_QUERY_CONNECTABILITY_MODE             0x000C
#define  RSI_BT_RSP_SET_PAIR_MODE                         0x000D
#define  RSI_BT_RSP_QUERY_PAIR_MODE                       0x000E
#define  RSI_BT_RSP_REMOTE_NAME_REQUEST                   0x000F
#define  RSI_BT_RSP_REMOTE_NAME_REQUEST_CANCEL            0x0010
#define  RSI_BT_RSP_INQUIRY                               0x0011
#define  RSI_BT_RSP_INQUIRY_CANCEL                        0x0012
#define  RSI_BT_RSP_BOND                                  0x0013
#define  RSI_BT_RSP_BOND_CANCEL                           0x0014
#define  RSI_BT_RSP_UNBOND                                0x0015
#define  RSI_BT_RSP_SET_PIN_TYPE                          0x0016
#define  RSI_BT_RSP_QUERY_PIN_TYPE                        0x0017
#define  RSI_BT_RSP_USER_CONFIRMATION                     0x0018
#define  RSI_BT_RSP_PASSKEY_REPLY                         0x0019
#define  RSI_BT_RSP_PINCODE_REPLY                         0x001A
#define  RSI_BT_RSP_QUERY_ROLE                            0x001B
#define  RSI_BT_RSP_SET_ROLE                              0x001C
#define  RSI_BT_RSP_QUERY_SERVICES                        0x001D
#define  RSI_BT_RSP_SEARCH_SERVICE                        0x001E
#define  RSI_BT_RSP_SPP_CONNECT                           0x001F
#define  RSI_BT_RSP_SPP_DISCONNECT                        0x0020
#define  RSI_BT_RSP_SPP_TRANSFER                          0x0021

#define  RSI_BT_RSP_PER_TX                                0x0098
#define  RSI_BT_RSP_PER_RX                                0x0099
#define  RSI_BT_RSP_PER_STATS                             0x009A
#define  RSI_BT_RSP_CW_MODE                               0x009B

#define  RSI_BT_RSP_START_SNIFF_MODE                      0x009D
#define  RSI_BT_RSP_STOP_SNIFF_MODE                       0x009E
#define  RSI_BT_RSP_SNIFF_SUBRATING_MODE                  0x009F
#define  RSI_BT_RSP_SSP_ENABLE                            0x00A0
#define  RSI_BT_RSP_FEATURE_BIT_MAP                       0x00A6
#define  RSI_BT_RSP_ANTENNA_TX_POWER_LEVEL                0x00A7
#define  RSI_BT_RSP_EIR_DATA                              0x00A9
         

//! Event Frame Codes
#define  RSI_BT_EVT_ROLE_CHANGE_STATUS                    0x1000
#define  RSI_BT_EVT_UNBOND_STATUS                         0x1001
#define  RSI_BT_EVT_BOND_RESPONSE                         0x1002
#define  RSI_BT_EVT_INQUIRY_RESPONSE                      0x1003
#define  RSI_BT_EVT_REMOTE_DEVICE_NAME                    0x1004
#define  RSI_BT_EVT_REMOTE_NAME_REQUEST_CANCEL            0x1005
#define  RSI_BT_EVT_DISCONNECTED                          0x1006
#define  RSI_BT_EVT_USER_CONFIRMATION_REQUEST             0x1007
#define  RSI_BT_EVT_USER_PASKEY_DISPLAY                   0x1008
#define  RSI_BT_EVT_USER_PINCODE_REQUEST                  0x1009
#define  RSI_BT_EVT_USER_PASSKEY_REQUEST                  0x100A
#define  RSI_BT_EVT_INQ_COMPLETE                          0x100B
#define  RSI_BT_EVT_AUTH_COMPLETE                         0x100C
#define  RSI_BT_EVT_USER_LINKKEY_REQUEST                  0x100D
#define  RSI_BT_EVT_USER_LINKKEY_SAVE                     0x100E
#define  RSI_BT_EVT_SSP_COMPLETE                          0x100F
#define  RSI_BT_EVT_MODE_CHANGE                           0x1010
#define  RSI_BT_EVT_SNIFF_SUBRATING_CHANGED               0x1011
#define  RSI_BT_EVT_USER_PASKEY_NOTIFY                    0x1012


#define  RSI_BT_EVT_SPP_RECEIVE                           0x1100
#define  RSI_BT_EVT_SPP_CONNECTED                         0x1101
#define  RSI_BT_EVT_SPP_DISCONNECTED                      0x1102



/*
 * Function Prototype Definitions
 */

INT16 rsi_bt_execute_cmd(UINT08 *descparam, UINT08 *payloadparam, UINT16 size_param);

/*
 * Generic Function Prototype Definitions
 */

INT16 rsi_bt_set_local_name(RSI_BT_CMD_SET_LOCAL_NAME *SetLocalName);
INT16 rsi_bt_query_local_name(void);
INT16 rsi_bt_set_local_cod(RSI_BT_CMD_SET_LOCAL_COD *SetLocalCOD);
INT16 rsi_bt_query_local_cod(void);
INT16 rsi_bt_query_rssi(RSI_BT_CMD_QUERY_RSSI *GetRSSI);
INT16 rsi_bt_query_link_quality(RSI_BT_CMD_QUERY_LINK_QUALITY *GetLinkQuality);
INT16 rsi_bt_query_local_bd_address(void);

INT16 rsi_bt_device_init(void);
INT16 rsi_bt_device_deinit(void);
INT16 rsi_bt_antenna_select(RSI_BT_CMD_ANTENNA_SELECT *uAntennaSelect);
//INT16 rsi_bt_config_enable(RSI_BT_CMD_CONFIG_ENABLE *uConfigEnable);


/*
 * BT Classic Core Function Prototype Definitions
 */

INT16 rsi_bt_set_profile_mode(RSI_BT_CMD_SET_PROFILE_MODE *SetProfMode);
INT16 rsi_bt_set_discovery_mode(RSI_BT_CMD_SET_DISCV_MODE *SetDiscvMode);
INT16 rsi_bt_query_discovery_mode(void);
INT16 rsi_bt_set_connectability_mode(RSI_BT_CMD_SET_CONNECTABILITY_MODE *SetConnMode);
INT16 rsi_bt_query_connectability_mode(void);
INT16 rsi_bt_set_pair_mode(RSI_BT_CMD_SET_PAIR_MODE *SetPairMode);
INT16 rsi_bt_query_pair_mode(void);
INT16 rsi_bt_remote_name_request(RSI_BT_CMD_REMOTE_NAME_REQUEST *RemNameReq);
INT16 rsi_bt_remote_name_request_cancel(RSI_BT_CMD_REMOTE_NAME_REQUEST_CANCEL *RemNameReqCancel);
INT16 rsi_bt_inquiry(RSI_BT_CMD_INQUIRY *Inq);
INT16 rsi_bt_inquiry_cancel(void);
INT16 rsi_bt_bond(RSI_BT_CMD_BOND *Bond);
INT16 rsi_bt_bond_cancel(RSI_BT_CMD_BOND_CANCEL *BondCancel);
INT16 rsi_bt_unbond(RSI_BT_CMD_UNBOND *Unbond);
INT16 rsi_bt_set_pin_type(RSI_BT_CMD_SET_PIN_TYPE *SetPinType);
INT16 rsi_bt_query_pin_type(void);
INT16 rsi_bt_user_confirmation(RSI_BT_CMD_USER_CONFIRMATION *UserConf);
INT16 rsi_bt_passkey_request_reply(RSI_BT_CMD_PASSKEY_REPLY *PasskeyReply);
INT16 rsi_bt_pincode_reply(RSI_BT_CMD_PINCODE_REPLY *PincodeReply);
INT16 rsi_bt_query_role(RSI_BT_CMD_QUERY_ROLE *GetRole);
INT16 rsi_bt_set_role(RSI_BT_CMD_SET_ROLE *SetRole);
INT16 rsi_bt_query_services(RSI_BT_CMD_QUERY_SERVICES *GetServ);
INT16 rsi_bt_search_service(RSI_BT_CMD_SEARCH_SERVICE *SearchServ);
INT16 rsi_bt_start_sniff_mode (RSI_BT_CMD_SNIFF_MODE *SniffMode);
INT16 rsi_bt_exit_sniff_mode (RSI_BT_CMD_SNIFF_EXIT *SniffExit);
INT16 rsi_bt_sniff_subrating_mode (RSI_BT_CMD_SNIFF_SUBRATING *SniffSubrating);
INT16 rsi_bt_enable_ssp_mode (RSI_BT_CMD_SSP_MODE *SSPMode);
INT16 rsi_bt_enable_set_feature_bitmap (RSI_BT_CMD_FEATURE_BIT_MAP *FeatureBitMap);

/*
 * BT Classic SPP Function Prototype Definitions
 */

INT16 rsi_bt_spp_connect(RSI_BT_CMD_SPP_CONNECT *SPPConn);
INT16 rsi_bt_spp_disconnect(RSI_BT_CMD_SPP_DISCONNECT *SPPDisConn);
INT16 rsi_bt_spp_transfer(RSI_BT_CMD_SPP_TRANSFER *SPPTransfer);

INT16 rsi_bt_linkkey_reply(RSI_BT_CMD_LINKKEY_REPLY *LinkKeyReply);

//INT16 rsi_spi_frame_dsc_wr(RSI_BT_FRAME_DESC *uFrmDscFrame);
//INT16 rsi_spi_frame_data_wr(UINT16 bufLen, UINT08 *dBuf, UINT16 tbufLen, UINT08 *tBuf);
INT16 rsi_frame_read(UINT08 *PktBuffer);
INT16 rsi_bt_register_interrupt_irq(void);
void rsi_bt_build_frame_descriptor(RSI_BT_FRAME_DESC *uFrameDscFrame, UINT08 *descparam);








#ifdef __cplusplus
}
#endif

#endif
