/**
 * @file         rsi_bt_app.h
 * @version      1.0
 * @date         2014-Aug-25
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief HEADER, APP, APPLICATION Header file which contains application specific structures 
 *
 * @section Description
 * This file contains the Application related information.
 *
 *
 */
#ifdef __cplusplus
extern "C" {
#endif

#include "rsi_bt_config.h"
#include "rsi_bt_global.h"
#include "rsi_ble_global.h"


#ifndef _RSI_BT_APP_CB_H
#define _RSI_BT_APP_CB_H
/* Application control block */

typedef struct rsi_bt_app_cb {

  /* Error code */
  UINT16        ErrorCode;
  
  /* Buffer to receive to response from Wi-Fi module */
  RSI_BT_RESPONSE     *ResponseFrame;
  
  /* Remote BD address */
  UINT08                RemoteBDAddress[6];
  
  /* Remote BD address Link key */
  UINT08                RemoteLinkKey[16];
  
  /* Remote BT Device name  */
  INT08                RemoteName[RSI_BT_DEVICE_NAME_LEN];
  
  RSI_BT_API           uBTApiInitParams_actual;
  /* Buffer to store Bluetooth Initialization parameters */
  RSI_BT_API           *uBTApiInitParams;
  
  RSI_BLE_API          uBLEApiInitParams_actual;

  RSI_BLE_API          *uBLEApiInitParams;

  volatile UINT32               PacketPending;

  UINT08               ReadPacketBuffer[1200];

  UINT08               SendPacketBuffer[1200];

}RSI_BT_APP_CB;


extern RSI_BT_APP_CB rsi_bt_AppControlBlock;
/*
 * Sample application functions
 */

INT16 rsi_bt_init (void);
INT16 rsi_bt_le_init     (void);
INT16 bt_main            (void);
INT16 bt_main            (void);
INT16 rsi_bt_app(void);
void rsi_bt_decode_rsp(UINT16 rsp_type, UINT16 status, void *rsp);

#endif
#ifdef __cplusplus
}
#endif
