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
#include "rsi_bt_global.h"
#include "rsi_bt_generic.h"
#include "rsi_bt_config.h"
#include "rsi_app_util.h"
#include "rsi_lib_util.h"
#include "rsi_hal.h"
#include "string.h"
#include "stdlib.h"


extern RSI_BT_RESPONSE *rsi_bt_parse_response(UINT08 *rsp);


typedef struct scanned_device {
    INT08  DeviceName[RSI_BT_DEVICE_NAME_LEN];
    UINT08 BDAddress[RSI_BT_BD_ADDR_LEN];
}RSI_BT_SCANNED_DEVICES;



RSI_BT_APP_CB rsi_bt_AppControlBlock;
RSI_BT_SCANNED_DEVICES  rsi_bt_ScannedDevices[10];
static UINT08  rsi_bt_ScannedDevsCount;


INT16 bt_main (void)
{
  INT16   RetVal = 0;
  UINT16  ResponseType;

  rsi_bt_AppControlBlock.uBTApiInitParams = &rsi_bt_AppControlBlock.uBTApiInitParams_actual; 
  /* To use the rsi_config.h settings */
  //rsi_bt_init_struct(&rsi_bt_AppControlBlock.APIInitParams);

  /* Initialize the BT functionality */
  if(rsi_bt_init())
    return 0;

  while(1)
  {     

    /* MCU receives an external interrupt from the module */
    if( rsi_bt_AppControlBlock.PacketPending == RSI_TRUE )
    {
      {
        RetVal = rsi_frame_read(rsi_bt_AppControlBlock.ReadPacketBuffer);
        rsi_bt_AppControlBlock.ResponseFrame = rsi_bt_parse_response(rsi_bt_AppControlBlock.ReadPacketBuffer);

        if(RetVal == 0)
        {
          /* Retrieve response code from the received packet */
          ResponseType           = rsi_bytes2R_to_uint16(rsi_bt_AppControlBlock.ResponseFrame->ResponseCode);
          rsi_bt_AppControlBlock.ErrorCode = rsi_bytes2R_to_uint16(rsi_bt_AppControlBlock.ResponseFrame->Status);

          printf("GOT 0x%x packet\n", ResponseType);

          /* Switch between type of packet received */
          switch (ResponseType)
          {
            case RSI_BT_RSP_SPP_TRANSFER:
              if(!rsi_bt_AppControlBlock.ErrorCode)
              {

#if RSI_BT_DEVICE_SPP_DATA_TRANSFER
                RetVal = rsi_bt_init_struct(RSI_BT_REQ_SPP_TRANSFER);                
                RetVal = rsi_bt_spp_transfer(&rsi_bt_AppControlBlock.uBTApiInitParams->uSPPTransfer);
#endif

              }
              else
              {
                return -1;
              }
              break;
            
            case RSI_BT_EVT_SPP_RECEIVE:
              if(!rsi_bt_AppControlBlock.ErrorCode)
              {
                printf("----------------SPP RECEIVED PACKET--------------\n");
                // Send data to user.
              }
              else
              {
                return -1;
              }
              break;
            
            case RSI_BT_EVT_SPP_DISCONNECTED:
              if(!rsi_bt_AppControlBlock.ErrorCode)
              {
                printf("--------------SPP DISCONNECTED-------------------\n");
                // Close the Application.
              }
              else
              {
                return -1;
              }
              break;
            
            default:
              break;
          }
        }
      }
      if(rsi_irq_status() == RSI_FALSE)
      {
        rsi_bt_AppControlBlock.PacketPending = RSI_FALSE;
        rsi_irq_enable();
      }
    }    
  }
  return RetVal;
}

#ifdef BT_ENABLE
volatile UINT16 first_cmd_pkt_rcvd = 0;
#endif
INT16 rsi_bt_init (void)
{
    INT16 RetVal;
    UINT16 ResponseType = 0;
    
    rsi_bt_ScannedDevsCount = 0;

    /*Enable the H/W module interrupt*/
    rsi_irq_start();
    
    while(1) {
        
       /* MCU receives an external interrupt from the module */
        if(rsi_bt_AppControlBlock.PacketPending == RSI_TRUE ) {
            RetVal = rsi_frame_read(rsi_bt_AppControlBlock.ReadPacketBuffer);
            rsi_bt_AppControlBlock.ResponseFrame = rsi_bt_parse_response(rsi_bt_AppControlBlock.ReadPacketBuffer);
            
            if(RetVal == 0) {

                /* Retrieve response code from the received packet */
                ResponseType           = rsi_bytes2R_to_uint16(rsi_bt_AppControlBlock.ResponseFrame->ResponseCode);
                rsi_bt_AppControlBlock.ErrorCode = rsi_bytes2R_to_uint16(rsi_bt_AppControlBlock.ResponseFrame->Status);
                
                printf("Response Rcvd %02x\n",ResponseType);
                if(first_cmd_pkt_rcvd == 1){
                    rsi_bt_decode_rsp(ResponseType, rsi_bt_AppControlBlock.ErrorCode, (void*)&rsi_bt_AppControlBlock.ResponseFrame->uCmdRspPayLoad);
                    printf("\r\nEnter to continue...\n");
                    getchar();
                    rsi_bt_app();
                }
                /* Switch between type of packet received */
                switch (ResponseType) {

                    case RSI_BT_RSP_CARD_READY:
                         if(!rsi_bt_AppControlBlock.ErrorCode) {
                             first_cmd_pkt_rcvd = 1;
                             rsi_bt_app();
                         } else {
                             return -1;
                         }
                         break;
                    default:;
                } //switch
            }
            else {
                printf("Error reading response ....\n");	//if frame read ret_val
            }
        } 
#ifdef LINUX_PLATFORM
        rsi_bt_AppControlBlock.PacketPending = (rsi_linux_app_cb.rcv_queue.pending_pkt_count > 0);
#endif        
    }   //while

    return 0;
}

