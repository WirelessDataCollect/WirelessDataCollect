/**
 * @file       rsi_ble_init.c
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
 * @brief INIT STRUCT: Initializes the global parameter structure to the values in the #define statements in main.h
 *
 * @section Description
 * This file contains function to initialize the main structure which defines
 * system operation
 *
 *
 */
#include "rsi_bt_app.h"
#include "rsi_ble_global.h"
#include "rsi_ble_api.h"
#include "rsi_ble_config.h"
#include "rsi_app_util.h"
#include "rsi_lib_util.h"
#ifdef RSI_HAL
#include "rsi_hal.h"
#endif
#include "rsi_global.h"
#include "rsi_api.h"

#include "rsi_config.h"
#include "rsi_bt_generic.h"

#include "rsi_scheduler.h"
#include "rsi_config.h"

RSI_BT_RESPONSE *rsi_bt_parse_response(UINT08 *rsp);
void rsi_ble_decode_rsp(UINT16 rsp_type, UINT16 status, void *rsp);


extern volatile UINT16 first_cmd_pkt_rcvd ;
void rsi_ble_struct_init()
{
  rsi_bt_AppControlBlock.uBLEApiInitParams = &rsi_bt_AppControlBlock.uBLEApiInitParams_actual;
}

void rsi_ble_app_event(UINT8 *buffer)
{
  INT16 ResponseType = 0;
  static  UINT08  att_count = 0;

  rsi_bt_AppControlBlock.ResponseFrame = rsi_bt_parse_response(buffer);
  /* Retrieve response code from the received packet */
  ResponseType           = rsi_bytes2R_to_uint16(rsi_bt_AppControlBlock.ResponseFrame->ResponseCode);
  rsi_bt_AppControlBlock.ErrorCode = rsi_bytes2R_to_uint16(rsi_bt_AppControlBlock.ResponseFrame->Status);
  if(first_cmd_pkt_rcvd == 1){
    /* Replace 4 with Common Queue Macro */
    rsi_ble_decode_rsp(ResponseType, rsi_bt_AppControlBlock.ErrorCode, (void*)&rsi_bt_AppControlBlock. ResponseFrame->uCmdRspPayLoad);
  }
  /* Switch between type of packet received */
  switch (ResponseType) 
  {
    case RSI_BT_RSP_CARD_READY:
      {
        if(!rsi_bt_AppControlBlock.ErrorCode) {
          if (RSI_BT_DEVICE_MODE == RSI_BLE_PERIPHERAL_MODE) {
#ifdef RSI_DEBUG_PRINT
            RSI_DPRINT(RSI_PL13,"Card ready received RSI_BLE_PERIPHERAL_MODE\n");
			RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","BLE","Rx","BLE card ready","BLE module intiated");
#endif
          } else if (RSI_BT_DEVICE_MODE == RSI_BLE_CENTRAL_MODE) {
#ifdef RSI_DEBUG_PRINT
            RSI_DPRINT(RSI_PL13,"Card ready received  RSI_BLE_CENTRAL_MODE\n");
            RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","BLE","Rx","BLE card ready","BLE module intiated");
#endif
          }
          first_cmd_pkt_rcvd = 1;
          rsi_set_bt_or_zb_sleep_mode(RSI_ACTIVE);
#if (RSI_POWER_MODE == (RSI_POWER_MODE_8 | RSI_POWER_MODE_9))
#ifdef PWR_SAVE 
#ifdef RSI_DEBUG_PRINT
          RSI_DPRINT(RSI_PL3,"$$$ RSI_DEEP_SLEEP SET AT BLE $$$\n");
#endif
               /* Enable the Power Save */
          rsi_set_bt_or_zb_sleep_mode(RSI_DEEP_SLEEP);
          return;
#endif
#endif
          rsi_ble_init_struct(RSI_BLE_REQ_ADD_RSI_SERVICE);

        } else {
          return ;
        }
      }
      break;

    case RSI_BLE_RSP_ADD_SERVICE:
      rsi_ble_init_struct(RSI_BLE_REQ_ADD_RSI_ATT1);
      break;

    case RSI_BLE_RSP_ADD_ATTRIBUTE:
      switch (att_count) {
        case 0:
        	RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","BLE","Rx","Add attr Rsp","Adding Attr 1 Success");
          rsi_ble_init_struct(RSI_BLE_REQ_ADD_RSI_ATT2);
          break;
        case 1:
        	RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","BLE","Rx","Add attr Rsp","Adding Attr 2 Success");
          rsi_ble_init_struct(RSI_BLE_REQ_ADD_RSI_ATT3);
          break;
        case 2:
        	RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","BLE","Rx","Add attr Rsp","Adding Attr 3 Success");
          rsi_ble_init_struct(RSI_BLE_REQ_ADD_RSI_ATT4);
          break;
        case 3:
        	RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","BLE","Rx","Add attr Rsp","Adding Attr 4 Success");
          rsi_ble_init_struct(RSI_BLE_REQ_ADD_RSI_ATT5);
          break;
        case 4:
        	RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","BLE","Rx","Add attr Rsp","Adding Attr 5 Success");
#ifndef   RSI_BLE_MASTER
          rsi_ble_init_struct(RSI_BLE_REQ_ADVERTISE);
#else
          rsi_ble_init_struct(RSI_BLE_REQ_SCAN);
#endif
          break;
      }
      att_count++; 
      break;

    case RSI_BLE_RSP_ADVERTISE:
      if (rsi_bt_AppControlBlock.ErrorCode != 0) {
      	RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %s\n","BLE","Rx","BLE Advt rsp","Advertisment successfull");
#ifndef   RSI_BLE_MASTER      
           rsi_ble_init_struct(RSI_BLE_REQ_ADVERTISE);
#else
          rsi_ble_init_struct(RSI_BLE_REQ_SCAN);
#endif
      }
      break;


    case RSI_BT_EVT_DISCONNECTED:
    	RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","BLE","Rx","BLE event","Disconnected");
#ifndef   RSI_BLE_MASTER
          rsi_ble_init_struct(RSI_BLE_REQ_ADVERTISE);
#else
          rsi_ble_init_struct(RSI_BLE_REQ_SCAN);
#endif
      break;

    case RSI_BLE_EVENT_GATT_WRITE_VALUE:
      rsi_ble_init_struct(RSI_BLE_REQ_SET_RSI_ATT4);
      break;

    default:
      {
        break;
      }  
  }
}
