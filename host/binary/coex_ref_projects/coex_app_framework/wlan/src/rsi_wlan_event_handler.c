/**
 * @file       rsi_wlan_event_handler.c
 * @version    2.7
 * @date       2015-Mar-2
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

/**
 * Global Variables
 */
extern RSI_COMMON_APP_CB_T rsi_common_app_cb;

extern uint8 rsi_raw_data_pkt[500];
extern uint32 data_txed[1];


/*====================================================*/
/**
 * @fn          void rsi_wlan_event_handler()
 * @brief       This is a event handler for wlan rx event.
 * @param[in]   UINT32 event_num
 * @return      void
 * @section description 
 * This function handles the received data from module. 
 */
void rsi_wlan_event_handler()
{
  PKT_STRUCT_T *pkt = NULL;
  UINT8 *buf_ptr = NULL;

  /* Check the Is there any packets */
  if (rsi_check_queue_status(&rsi_common_app_cb.rsi_wlan_rx_q))
  {
    pkt = (PKT_STRUCT_T *)rsi_dequeue_from_rcv_q(&rsi_common_app_cb.rsi_wlan_rx_q);
    buf_ptr = (UINT8 *)pkt->data;
#ifdef WLAN_ENABLE    
    rsi_wlan_app_event(buf_ptr);
#endif    
    rsi_unmask_event(RSI_RX_EVENT);

    rsi_irq_enable();
  }
  else
  {
    rsi_clear_event(RSI_WLAN_EVENT);
  }
}

/*====================================================*/
/**
 * @fn          void rsi_raw_data_event_handler()
 * @brief       This is a event handler for ble tx event.
 * @return      void
 * @section description 
 * This function handles the sends data to module. 
 */
#ifdef WLAN_ENABLE
void rsi_raw_data_event_handler()
{
  rsi_clear_event(RSI_RAW_DATA_TEST_EVENT);
  rsi_send_raw_data(rsi_raw_data_pkt,sizeof(rsi_raw_data_pkt),data_txed);
}
#endif


/*====================================================*/
/**
 * @fn          void rsi_set_wlan_sleep_mode(UINT32 mode)
 * @brief       This function sets the power
 *              mode. 
 * @param[in]   mode,the power mode to be set
 * @return      none  
 *               
 * @section description 
 * This function will send the power mode command.
 */
void rsi_set_wlan_sleep_mode(UINT32 mode)
{
  rsi_common_app_cb.slp_params.wlan_sleep_mode = mode;
  rsi_set_event(RSI_COMMON_EVENT);
}

