/**
 * @file       rsi_bt_zb_event_handler.c
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
extern INT32 rsi_bt_app_event(UINT8 *buffer);

/*====================================================*/
/**
 * @fn          void rsi_bt_or_zb_event_handler()
 * @brief       This is a event handler for BT/ZB event.
 * @param[in]   none
 * @return      void
 * @section description 
 * This function handles the received data from module. 
 */
void rsi_bt_or_zb_event_handler()
{
  PKT_STRUCT_T *pkt = NULL;
#if (defined BLE_ENABLE || defined BT_ENABLE || defined ZB_ENABLE)
  UINT8 *buf_ptr = NULL;
#endif
  /* Check the Is there any packets */
  if (rsi_check_queue_status(&rsi_common_app_cb.rsi_bt_or_zb_rx_q))
  {
    pkt = rsi_dequeue_from_rcv_q(&rsi_common_app_cb.rsi_bt_or_zb_rx_q);
#if (defined BLE_ENABLE || defined BT_ENABLE || defined ZB_ENABLE)
    buf_ptr = (UINT8 *)pkt->data;
#endif
#ifdef BLE_ENABLE
    rsi_ble_app_event(buf_ptr);
#endif      
 
#ifdef ZB_ENABLE
    rsi_zigb_state_machine(buf_ptr);
#endif      

#ifdef BT_ENABLE
    rsi_bt_app_event(buf_ptr); 
#endif
    rsi_unmask_event(RSI_RX_EVENT);

    rsi_irq_enable();
  }
  else
  {
    rsi_clear_event(RSI_BT_OR_ZB_EVENT);
  }
}


/*====================================================*/
/**
 * @fn          void rsi_set_bt_or_zb_sleep_mode(UINT32 mode)
 * @brief       This function sets the power mode. 
 * @param[in]   mode,the power mode to be set
 * @return      none  
 *               
 * @section description 
 * This function will send the power mode command.
 */
void rsi_set_bt_or_zb_sleep_mode(UINT32 mode)
{
  rsi_common_app_cb.slp_params.bt_or_zb_sleep_mode = mode;
  rsi_set_event(RSI_COMMON_EVENT);
}

