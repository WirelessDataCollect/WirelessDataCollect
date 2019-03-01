/**
 * @file       rsi_bt_state_mc.c
 * @version    1.0
 * @date       2015-Feb-24
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief 
 *
 * @section Description
 * This file contains function which handles responses/bt events
 * system operation
 *
 *
 */


#include "rsi_config.h"
#include "rsi_bt_api.h"
#include "rsi_bt_app.h"
#include "rsi_app_util.h"
#include "rsi_lib_util.h"
#include "rsi_hal.h"
#include "rsi_global.h"
#include "rsi_api.h"
#include "rsi_bt_generic.h"
#include "rsi_scheduler.h"

RSI_BT_RESPONSE *rsi_bt_parse_response(UINT08 *rsp);
void rsi_bt_decode_rsp(UINT16 rsp_type, UINT16 status, void *rsp);

extern volatile UINT16 first_cmd_pkt_rcvd ;
void rsi_bt_struct_init()
{
  rsi_bt_AppControlBlock.uBTApiInitParams = &rsi_bt_AppControlBlock.uBTApiInitParams_actual;
}

INT32 rsi_bt_app_event(UINT8 *buffer)
{
	INT16 ResponseType = 0;

	rsi_bt_AppControlBlock.ResponseFrame = rsi_bt_parse_response(buffer);
	
  /* Retrieve response code from the received packet */
	ResponseType           = rsi_bytes2R_to_uint16(rsi_bt_AppControlBlock.ResponseFrame->ResponseCode);
	rsi_bt_AppControlBlock.ErrorCode = rsi_bytes2R_to_uint16(rsi_bt_AppControlBlock.ResponseFrame->Status);

	if(first_cmd_pkt_rcvd == 1){
		/* Replace 4 with Common Queue Macro */
		rsi_bt_decode_rsp(ResponseType, rsi_bt_AppControlBlock.ErrorCode, (void*)&rsi_bt_AppControlBlock. ResponseFrame->uCmdRspPayLoad);
	}
	/* Switch between type of packet received */
	switch (ResponseType) 
	{
		case RSI_BT_RSP_CARD_READY:
			if(!rsi_bt_AppControlBlock.ErrorCode) {
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL3,"Card ready received BT\n");
#endif
				first_cmd_pkt_rcvd = 1;

        if ((RSI_WIFI_OPER_MODE == 8) && (RSI_COEX_MODE == 5)) {

            if (BT_PER_MODE == BT_PER_TRANSMIT_MODE ) {
              rsi_bt_init_struct(RSI_BT_REQ_PER_TX);
            }else if(BT_PER_MODE == BT_PER_RECEIVE_MODE) {
              rsi_bt_init_struct(RSI_BT_REQ_PER_RX);
            } else if(BT_PER_MODE == BT_PER_CW_MODE) {
              rsi_bt_init_struct(RSI_BT_REQ_CW_MODE);
            }
        } else {
#if (RSI_POWER_MODE == (RSI_POWER_MODE_8 | RSI_POWER_MODE_9))
#ifdef PWR_SAVE 
          rsi_set_bt_or_zb_sleep_mode(RSI_DEEP_SLEEP);
          return;
#endif
#endif
            rsi_bt_init_struct(RSI_BT_RSP_SET_LOCAL_NAME);
        }
			} else {
				return -1;
			}
			break;
	
		case RSI_BT_RSP_SET_LOCAL_NAME:
			if(!rsi_bt_AppControlBlock.ErrorCode) {
				rsi_bt_init_struct(RSI_BT_REQ_SET_PROFILE_MODE);
			} else {
				return -1;
			}
			break;	 

		case RSI_BT_RSP_SET_PROFILE_MODE :
			if(!rsi_bt_AppControlBlock.ErrorCode) {
				rsi_bt_init_struct(RSI_BT_REQ_SET_DISCV_MODE);
			} else {
				return -1;
			}	
			break;	 

		case RSI_BT_RSP_SET_DISCV_MODE:
			if(!rsi_bt_AppControlBlock.ErrorCode) {
				rsi_bt_init_struct(RSI_BT_REQ_SET_CONNECTABILITY_MODE);
			} else {
				return -1;
			}	
			break;

		case RSI_BT_EVT_USER_PINCODE_REQUEST:
			if(!rsi_bt_AppControlBlock.ErrorCode) {
				rsi_bt_init_struct(RSI_BT_REQ_PINCODE_REPLY);
			} else {
				return -1;
			}	
			break;
		
		case RSI_BT_EVT_BOND_RESPONSE:
		case RSI_BT_EVT_AUTH_COMPLETE:
		
			break;

		case RSI_BT_EVT_USER_LINKKEY_REQUEST:
			if(!rsi_bt_AppControlBlock.ErrorCode) {
				rsi_bt_init_struct(RSI_BT_REQ_LINKEKY_REPLY);
			} else {
				return -1;
			}
			break;
		case RSI_BT_EVT_SPP_CONNECTED:
			if(!rsi_bt_AppControlBlock.ErrorCode)
			{
#ifndef PWR_SAVE 
#if RSI_BT_DO_SPP_TRANSFER
				rsi_bt_init_struct(RSI_BT_REQ_SPP_TRANSFER);                
#endif
#else
				rsi_bt_init_struct(RSI_BT_REQ_START_SNIFF_MODE);                
#endif
			}
			else
			{
				return -1;
			}
			break;
		case RSI_BT_RSP_SPP_TRANSFER:
			if(!rsi_bt_AppControlBlock.ErrorCode)
			{
#if RSI_BT_DO_SPP_TRANSFER
				rsi_bt_init_struct(RSI_BT_REQ_SPP_TRANSFER);                
#endif
			}
			else
			{
				return -1;
			}
			break;

		case RSI_BT_EVT_SPP_RECEIVE:
			if(!rsi_bt_AppControlBlock.ErrorCode) {
#if RSI_BT_DO_SPP_TRANSFER_ON_RX
				rsi_bt_init_struct(RSI_BT_REQ_SPP_TRANSFER);
#endif
			} else{
				return -1;
			}
			break;

		case RSI_BT_RSP_PER_TX:
      //printf("\nReceived Response for Per Tx\n");
			break;

		case RSI_BT_RSP_PER_RX:
    	//printf("\n%10s%10s%10s%10s\n","CRC_FAIL","CRC_PASS","ID_PKTS","RSSI");
      rsi_bt_init_struct(RSI_BT_REQ_PER_STATS);
			break;

		case RSI_BT_RSP_PER_STATS:
			rsi_bt_init_struct(RSI_BT_REQ_PER_STATS);
			break;
    case RSI_BT_RSP_START_SNIFF_MODE:
      if(!rsi_bt_AppControlBlock.ErrorCode) {
      }
      else {
        return -1;
      }
			break;
    case RSI_BT_EVT_MODE_CHANGE:
      if(!rsi_bt_AppControlBlock.ErrorCode) {
#ifdef PWR_SAVE 
        if((rsi_bt_AppControlBlock.ResponseFrame->uCmdRspPayLoad.uModeChange.CurrentMode) == 2)
        {
#ifdef RSI_DEBUG_PRINT
          RSI_DPRINT(RSI_PL3,"Sending Connected sleep command\n");
#endif
          rsi_set_bt_or_zb_sleep_mode(RSI_CONNECTED_SLEEP);
        }
#endif
      }
      else {
        return -1;
      }
			break;
		default:;
	} //end of switch
  return 0;
}
