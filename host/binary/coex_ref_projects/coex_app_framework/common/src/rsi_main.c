/**
 * @file       rsi_main.c
 * @version    2.7
 * @date       2015-Feb-17
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief Implements common functionality for all the commands
 *
 * @section Description
 * This file contains common api needed for all the commands
 *
 *
 */

/**
 * Includes
 */
#include "platform_specific.h"
#include "rsi_api.h"
#include "rsi_ble_api.h"
#include "rsi_app.h"
#include "rsi_scheduler.h"
#ifdef LINUX_PLATFORM
#include "rsi_serial.h"
#endif

RSI_COMMON_APP_CB_T rsi_common_app_cb;
//volatile UINT8 skip_card_ready = 0;

extern void rsi_buff_pool_init();
extern void rsi_bt_struct_init();


extern rsi_app_cb_t rsi_app_cb; 
void rsi_rx_pkt_pending_event(void);
void rsi_common_event_handler(void);
void rsi_raw_data_event_handler(void);



/*====================================================*/
/**
 * @fn          void rsi_main()
 * @brief       Common function for all the commands.
 * @return      void
 * @section description 
 * This is a common function used to do intialization of scheduler.
 */
INT16 rsi_main()
{
	
  /* Scheduler Initialization */
  rsi_coex_scheduler_init(&rsi_common_app_cb.scheduler_info);  
  
#ifdef BLE_ENABLE
  /* Ble Struct Initialization */
  rsi_ble_struct_init();
#endif

#ifdef BT_ENABLE
  /* BT Struct Initialization */
  rsi_bt_struct_init();
#endif


#ifdef ZB_ENABLE
  /* ZB Struct Initialization */
 rsi_zigb_init_struct();
#endif
 
  /* Queues Initialization */
  rsi_queues_init();

  /* Registering the Receive Event */
  if (rsi_register_event(RSI_RX_EVENT, rsi_rx_pkt_pending_event))
  {
    return -1;
  }
  /* Registering the Common Event */
  if (rsi_register_event(RSI_COMMON_EVENT, rsi_common_event_handler))
  {
    return -1;
  }
  /* Register the BT/ZigBee Events */
  if (rsi_register_event(RSI_BT_OR_ZB_EVENT, rsi_bt_or_zb_event_handler))
  {
    return -1;
  }
  /* Register the WLAN Events */
  if (rsi_register_event(RSI_WLAN_EVENT, rsi_wlan_event_handler))
  {
    return -1;
  }
  /* Common TX Event */
  if (rsi_register_event(RSI_TX_EVENT, rsi_tx_event_handler))
  {
    return -1;
  }
#ifdef WLAN_ENABLE
  /* WLAN RAW DATA TX TEST Event */
  if (rsi_register_event(RSI_RAW_DATA_TEST_EVENT, rsi_raw_data_event_handler))
  {
    return -1;
  }
#endif
/*Enable the wi-fi module interrupt*/
  //

#ifndef UART_INTERFACE  
 /*INTERRUPT has to enabled for SPI interface,
 For uart it is enabled after sending oper_mode
 */
  rsi_irq_start();
#endif
#if !(defined LINUX_PLATFORM || defined WINDOWS)
#ifdef UART_INTERFACE
	rsi_skip_card_ready();
#endif
#endif
  return 0;
}



