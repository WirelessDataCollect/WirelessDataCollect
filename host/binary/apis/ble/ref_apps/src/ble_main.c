/**
 * @file     main.c
 * Copyright(C) 2013 Redpine Signals Inc.
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief MAIN: Top level file, execution begins here
 *
 * @section Description
 * This file contains the entry point for the application. It also has the 
 * initialization of parameters of the global structure and the operations to 
 * control & configure the module, like scanning networks, joining to an Access Point etc.
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
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "rsi_global.h"
#include "rsi_api.h"

#include "rsi_config.h"
#include "rsi_bt_generic.h"

#define RSI_BLE_OPERMODE (0xd << 16)
//#define RSI_POWER_MODE RSI_POWER_MODE_3


typedef struct scanned_device {
    INT08  DeviceName[RSI_BT_DEVICE_NAME_LEN];
    UINT08 BDAddress[RSI_BT_BD_ADDR_LEN];
}RSI_BT_SCANNED_DEVICES;



RSI_BT_APP_CB rsi_bt_AppControlBlock;
RSI_BT_SCANNED_DEVICES  rsi_bt_ScannedDevices[10];
//static UINT08  rsi_bt_ScannedDevsCount;
#ifdef BLE_ENABLE
volatile UINT16 first_cmd_pkt_rcvd = 0;
#endif
//UINT08  rsi_bt_TransferBuffer[] = "Data";

volatile UINT16 glbl_dbg_resp_count = 0;

RSI_BT_RESPONSE *rsi_bt_parse_response(UINT08 *rsp);
void rsi_ble_decode_rsp(UINT16 rsp_type, UINT16 status, void *rsp);
void rsi_common_pkt_parser(UINT08 *rsp, UINT08 rsp_type);
INT16 rsi_bt_oper_mode(rsi_uOperMode *uOperMode);
INT16 rsi_bt_pwr_mode(UINT08 pwr_mode);
INT16 rsi_ble_init (void);
INT16 rsi_ble_app(void);

#ifndef FSM_BASED_BLE_APP
INT16 ble_main (void )
{
  INT16   RetVal;
  UINT16  ResponseType;

  rsi_bt_AppControlBlock.uBLEApiInitParams = &rsi_bt_AppControlBlock.uBLEApiInitParams_actual;
  
  /* Initialize the BLE functionality */
  if(rsi_ble_init()){
	
	RSI_DPRINT(RSI_PL3,"Error BLE init\n");
    return 0;
   }

#ifdef LINUX_PLATFORM 
  rsi_bt_AppControlBlock.PacketPending = (rsi_linux_app_cb.rcv_queue.pending_pkt_count > 0);
#endif  
  
  while(1)
  {     

    /* MCU receives an external interrupt from the module */
    if( rsi_bt_AppControlBlock.PacketPending == RSI_TRUE )
    {
	
        RSI_DPRINT(RSI_PL3,"Dequeue packet \n");
        RetVal = rsi_frame_read(rsi_bt_AppControlBlock.ReadPacketBuffer);
        rsi_bt_AppControlBlock.ResponseFrame = rsi_bt_parse_response(rsi_bt_AppControlBlock.ReadPacketBuffer);

        if(RetVal == 0)
        {
            /* Retrieve response code from the received packet */
            ResponseType           = rsi_bytes2R_to_uint16(rsi_bt_AppControlBlock.ResponseFrame->ResponseCode);
            rsi_bt_AppControlBlock.ErrorCode = rsi_bytes2R_to_uint16(rsi_bt_AppControlBlock.ResponseFrame->Status);

            /* Switch between type of packet received */
            switch (ResponseType)
            {
              case RSI_BLE_REQ_CONNECT:
                   if(!rsi_bt_AppControlBlock.ErrorCode) {
                       RetVal = rsi_ble_init_struct(RSI_BLE_REQ_QUERY_PROFILES_LIST);
                       RetVal = rsi_ble_query_profiles_list(&rsi_bt_AppControlBlock.uBLEApiInitParams->uLeAllServ);
                   } else {
                       return -1;
                   }
                   break;

              case RSI_BLE_REQ_QUERY_PROFILES_LIST:
                   if(!rsi_bt_AppControlBlock.ErrorCode) {
                       RetVal = rsi_ble_init_struct(RSI_BLE_REQ_QUERY_CHARACTERISTIC_SERVICES);
                       RetVal = rsi_ble_query_characteristic_services(&rsi_bt_AppControlBlock.uBLEApiInitParams->uLeCharServ);
                   } else {
                       return -1;
                   }
                   break;

              case RSI_BLE_REQ_QUERY_CHARACTERISTIC_SERVICES:
                   if(!rsi_bt_AppControlBlock.ErrorCode) {
                       RetVal = rsi_ble_init_struct(RSI_BLE_REQ_READ_CHAR_VALUE_BY_UUID);
                       RetVal = rsi_ble_read_char_value_by_UUID(&rsi_bt_AppControlBlock.uBLEApiInitParams->uLeCharVal);
                   } else {
                       return -1;
                   }
                   break;

              case RSI_BLE_REQ_READ_CHAR_VALUE_BY_UUID:
                   if(!rsi_bt_AppControlBlock.ErrorCode) {
                       /* bluetooth le initilization ended */
                   } else {
                       return -1;
                   }
                   break;
            }
        }
    }
#ifdef LINUX_PLATFORM 
    rsi_bt_AppControlBlock.PacketPending = (rsi_linux_app_cb.rcv_queue.pending_pkt_count > 0);
#endif
  }  // while

  return 0;
}

INT16 rsi_ble_init (void)
{
    INT16 RetVal;
    UINT16 ResponseType = 0;
    
    //rsi_bt_ScannedDevsCount = 0;

    /*Enable the H/W module interrupt*/
#ifndef LINUX_PLATFORM
   rsi_irq_start();//UART_COEX_CHANGES
#endif

    while(1) {
        
       /* MCU receives an external interrupt from the module */
        if(rsi_bt_AppControlBlock.PacketPending == RSI_TRUE ) {
            RetVal = rsi_frame_read(rsi_bt_AppControlBlock.ReadPacketBuffer);
            rsi_bt_AppControlBlock.ResponseFrame = rsi_bt_parse_response(rsi_bt_AppControlBlock.ReadPacketBuffer);
            
            if(RetVal == 0) {

                /* Retrieve response code from the received packet */
                ResponseType           = rsi_bytes2R_to_uint16(rsi_bt_AppControlBlock.ResponseFrame->ResponseCode);
                rsi_bt_AppControlBlock.ErrorCode = rsi_bytes2R_to_uint16(rsi_bt_AppControlBlock.ResponseFrame->Status);
#ifndef FSM_BASED_BLE_APP                
         
			    RSI_DPRINT(RSI_PL3,"Response Rcvd %02x\n",ResponseType);
		#endif                
                if(first_cmd_pkt_rcvd == 1){
                  //TODO Added this as temperoary fix
                  if (((rsi_bt_AppControlBlock.ReadPacketBuffer[1] & 0xF0) >> 4) != 4) {
                    rsi_ble_decode_rsp(ResponseType, rsi_bt_AppControlBlock.ErrorCode, (void*)&rsi_bt_AppControlBlock.ResponseFrame->uCmdRspPayLoad);
#ifndef FSM_BASED_BLE_APP                    
#ifdef LINUX_PLATFORM
                    RSI_DPRINT(RSI_PL3,"packets in rcv q: %d\n", rsi_linux_app_cb.rcv_queue.pending_pkt_count);
#endif
	
                    RSI_DPRINT(RSI_PL3,"Enter to continue...\n");
					
                    getchar();
                    getchar();
                    rsi_ble_app();
#endif                    
                  }
                }
                /* Switch between type of packet received */
                switch (ResponseType) {

                    case RSI_BT_RSP_CARD_READY:
                         if(!rsi_bt_AppControlBlock.ErrorCode) {
                             if (RSI_BT_DEVICE_MODE == RSI_BLE_PERIPHERAL_MODE) {
								 RSI_DPRINT(RSI_PL3,"Card ready received RSI_BLE_PERIPHERAL_MODE\n");
                             } else if (RSI_BT_DEVICE_MODE == RSI_BLE_CENTRAL_MODE) {

	                             RSI_DPRINT(RSI_PL13,"Card ready received  RSI_BLE_CENTRAL_MODE\n");
	                             RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","BLE","Rx","BLE card ready","BLE module intiated");
                             }
			                       first_cmd_pkt_rcvd = 1;
  			                     rsi_ble_app();
                         } else {
                             return -1;
                         }
                         break;
                    default:;
                } //switch
            }
					  else {

										RSI_DPRINT(RSI_PL3,"Error reading response ....\n");	//if frame read ret_val
						}
        } 

#ifdef LINUX_PLATFORM 
        rsi_bt_AppControlBlock.PacketPending = (rsi_linux_app_cb.rcv_queue.pending_pkt_count > 0);
#endif        
    }   //while

    return 0;
}
#else
INT16 ble_main (void )
{
  rsi_bt_AppControlBlock.uBLEApiInitParams = &rsi_bt_AppControlBlock.uBTApiInitParams_actual;
  
  /* Initialize the BLE functionality */
  if(rsi_ble_init()){
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL3,"Error BLE init\n");
#endif
    return 0;
   }

  return 0;
}

#if 0
UINT08 rsi_ble_set_pwr_save_enable(void)
{
  rsi_bt_AppControlBlock.ps_enable = 1;
}

UINT08 rsi_ble_reset_pwr_save_enable(void)
{
  rsi_bt_AppControlBlock.ps_enable = 0;
}

UINT08 rsi_ble_get_pwr_save_enable(void)
{
  return rsi_bt_AppControlBlock.ps_enable;
}

void rsi_ble_app_event(uint8_t *buffer)
{
  INT16 ResponseType = 0;

  rsi_bt_AppControlBlock.uBLEApiInitParams = (RSI_BLE_API *)malloc(sizeof (RSI_BLE_API));
  
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
        
			RSI_DPRINT(RSI_PL3,"Card ready received RSI_BLE_PERIPHERAL_MODE\n");

          } else if (RSI_BT_DEVICE_MODE == RSI_BLE_CENTRAL_MODE) {
            RSI_DPRINT(RSI_PL3,"Card ready received  RSI_BLE_CENTRAL_MODE\n");
          }
		  first_cmd_pkt_rcvd = 1;
          /* Enable the Power Save */
          rsi_ble_set_pwr_save_enable();
          rsi_ble_init_struct(RSI_BLE_REQ_SCAN);
        } else {
          return -1;
        }
      }
      break;
    default:
    {
      break;
    }  
  }
}
#endif

INT16 rsi_ble_init (void)
{
    INT16 RetVal;
    UINT16 ResponseType = 0;
    //rsi_api ptrStrApi;
    //rsi_bt_ScannedDevsCount = 0;

    /*Enable the H/W module interrupt*/
    //rsi_irq_start();//UART_COEX_CHANGES

  while(1)
    {
        
       /* MCU receives an external interrupt from the module */
        if( rsi_bt_AppControlBlock.PacketPending == RSI_TRUE ) {
            RetVal = rsi_frame_read(rsi_bt_AppControlBlock.ReadPacketBuffer);
            rsi_bt_AppControlBlock.ResponseFrame = rsi_bt_parse_response(rsi_bt_AppControlBlock.ReadPacketBuffer);
            
            if(RetVal == 0) {

                /* Retrieve response code from the received packet */
                ResponseType           = rsi_bytes2R_to_uint16(rsi_bt_AppControlBlock.ResponseFrame->ResponseCode);
                rsi_bt_AppControlBlock.ErrorCode = rsi_bytes2R_to_uint16(rsi_bt_AppControlBlock.ResponseFrame->Status);

                if(first_cmd_pkt_rcvd == 1){
                  /* Replace 4 with Common Queue Macro */
                  if (((rsi_bt_AppControlBlock.ReadPacketBuffer[1] & 0xF0) >> 4) == 4) {
                    rsi_common_pkt_parser((UINT08*)&ResponseType, rsi_bt_AppControlBlock.ErrorCode);
                  } else {
                    rsi_ble_decode_rsp(*(UINT16*)&ResponseType, rsi_bt_AppControlBlock.ErrorCode, (void*)&rsi_bt_AppControlBlock.ResponseFrame->uCmdRspPayLoad);
                  }
                }
                /* Switch between type of packet received */
                switch (ResponseType) 
                {
                    case RSI_BT_RSP_CARD_READY:
                    {
                         if(!rsi_bt_AppControlBlock.ErrorCode) {
                             if (RSI_BT_DEVICE_MODE == RSI_BLE_PERIPHERAL_MODE) {
#ifdef RSI_DEBUG_PRINT								 			
                                 RSI_DPRINT(RSI_PL3,"Card ready received RSI_BLE_PERIPHERAL_MODE\n");
#endif
								 } else if (RSI_BT_DEVICE_MODE == RSI_BLE_CENTRAL_MODE) {
#ifdef RSI_DEBUG_PRINT
                                 RSI_DPRINT(RSI_PL3,"Card ready received  RSI_BLE_CENTRAL_MODE\n");
#endif
								 }
			                       first_cmd_pkt_rcvd = 1;
                             /* Enable the Power Save */
                             rsi_ble_init_struct(RSI_BLE_REQ_SCAN);
                         } else {
                             return -1;
                         }
                    }
                    break;
                   

                   default:
                   {
                     /* 
                      * BLE Packets are handling in BLE decode rsp if any other packets which are not handling
                      * either in rsi_ble_decode_rsp and rsi_common_pkt_parser needs to be handled here
                      */
                   }
                   break;
                } /* End Of Switch Case */
            }
					  else {
#ifdef RSI_DEBUG_PRINT
										RSI_DPRINT(RSI_PL3,"Error reading response ....\n");	//if frame read ret_val
#endif
						}
        } 

#ifdef LINUX_PLATFORM 
        rsi_bt_AppControlBlock.PacketPending = 0;
#endif        
    }   //while

    return 0;
}
#endif

/*=================================================*/
/**
 * @fn          void rsi_common_pkt_parser(UINT08 *rsp)
 * @brief       To parse the resposne received from common module
 * @param[in]   UINT08 *rsp, response buffer pointer
 * @param[out]  none
 * @return      none
 * @section description 
 * This API is used to parse the recieved common response. This 
 * returns the 
 * pointer which points to rsptype, status, response payload in order.
 */
void rsi_common_pkt_parser(UINT08 *rsp, UINT08 rsp_type)
{
#if (RSI_POWER_MODE == RSI_POWER_MODE_3)      
  INT16 retval = 0;
#endif
  switch (rsp_type)
  {
    case RSI_RSP_OPERMODE:
    {
      //UINT08 pwr_mode = 3;
      break;
    }
    case RSI_RSP_PWRMODE:
    {
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL13,"Power Mode Response Received\n");
#endif
#ifdef FSM_BASED_BLE_APP
      rsi_ble_init_struct(RSI_BLE_REQ_SCAN);
#endif      
      break;
    }
    case RSI_RSP_SLP:
    {
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL3,"SLP\n");
#endif
#if 0 //(RSI_POWER_MODE == RSI_POWER_MODE_3)      
      retval = rsi_bt_execute_cmd((uint8 *)rsi_bt_sleepack,0,0);
      if (retval != 0) {
        //exit(0);
		  return;
      }
      rsi_bt_AppControlBlock.ps_ok_to_send = 1;
#endif      
      break;
    }
    case RSI_RSP_WKP:
    {
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL3,"WKP\n");
#endif
#if 0 //(RSI_POWER_MODE == RSI_POWER_MODE_3)      
      rsi_bt_AppControlBlock.ps_ok_to_send = 0;
      if (rsi_bt_AppControlBlock.ps_pkt_pending) {
        retval = rsi_bt_execute_cmd(rsi_bt_AppControlBlock.ps_descparam,
            rsi_bt_AppControlBlock.ps_pkt_pending, rsi_bt_AppControlBlock.ps_size_param);
        if (retval != 0) {
          //exit(0);
		  return;
        }
      }
#endif      
      break;
    }
    default:
    {
      break;
    }
  }
}

