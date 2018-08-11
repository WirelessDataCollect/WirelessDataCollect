/**
 * @file       rsi_common_event_handlers.c
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
extern UINT8 rsi_sleep_ack[RSI_FRAME_DESC_LEN];

#ifdef PWR_SAVE
volatile UINT8 PwrModeEnable=0;
#endif
volatile UINT8 oper_mode_rcvd=0;
#ifdef WLAN_ENABLE
UINT8 wlan_joined;
extern uint8 rsi_raw_data_pkt[500];
#endif

/*====================================================*/
/**
 * @fn          void rsi_common_event_handler()
 * @brief       Common function for all the commands.
 * @param[in]   none
 * @return      none
 * @section description 
 * This is a common function used to process a pkt command from the module.
 */
void rsi_common_event_handler(void)
{
  PKT_STRUCT_T *pkt = NULL;
  UINT8 *buf_ptr = NULL;
  UINT8 frame_type;

  if (rsi_check_queue_status(&rsi_common_app_cb.rsi_cmn_rx_q)) {
    pkt = rsi_dequeue_from_rcv_q(&rsi_common_app_cb.rsi_cmn_rx_q);

    buf_ptr = (UINT8 *)pkt->data;

    /* Extract the frame type from the received frame*/
    frame_type = *(UINT8*)(buf_ptr + RSI_RESP_OFFSET);

    rsi_cmn_pkt_parser(buf_ptr, frame_type);

    rsi_unmask_event(RSI_RX_EVENT);

    rsi_irq_enable();

  }

  rsi_sleep_mode_decision(&rsi_common_app_cb);
  rsi_clear_event(RSI_COMMON_EVENT);
}

/*====================================================*/
/**
 * @fn          void rsi_rx_pkt_pending_event()
 * @brief       Common function for all the commands.
 * @param[in]   none
 * @return      none
 * @section description 
 * This is a common function used to process a pkt command from the module.
 */
void rsi_rx_pkt_pending_event(void)
{
  UINT8 queue_no;
  UINT16 length;
  UINT8 frame_type;
  UINT8 *buf_ptr = NULL;
  PKT_STRUCT_T *rcvPktPtr = NULL;
  //Have a chk for actual pkt pending,if pkt_pending=0 just skip the event handling
  /* Allocate Memory */
  rcvPktPtr = (PKT_STRUCT_T *)rsi_common_app_cb.device_rx_pkt;
  if(rcvPktPtr == NULL)
  {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL13,"NULL POINTER ACCESS!\n");
#endif
    //Masking RX event if BUffer Pool is fully used
    rsi_mask_event(RSI_RX_EVENT);
    return;
  }
  rcvPktPtr->next = (PKT_STRUCT_T *)(((UINT8 *)rcvPktPtr));
  rcvPktPtr->data = (UINT8 *)(((UINT8 *)rcvPktPtr) + (sizeof(UINT8 *) * 2) );

  buf_ptr = (UINT8 *)rcvPktPtr->data;
  /* 
   * Read the Packet from the Module in case of micro controller
   * otherwise read it from queue
   */

  if(rsi_frame_read(buf_ptr))
  {
    rsi_clear_event(RSI_RX_EVENT);
    return;
  }
  /* Extract the queue number from the receivec frame */
  queue_no = ((buf_ptr[1] & 0xF0) >> 4);
  length = rsi_bytes2R_to_uint16(buf_ptr);
  length = length & 0x0fff;
  length += RSI_FRAME_DESC_LEN;
  /* Extract the frame type from the received frame*/
  frame_type = *(UINT8*)(buf_ptr + RSI_RESP_OFFSET);

#ifdef PWR_SAVE  
  if(PwrModeEnable)
  {
    /* If the response frame is one of the followong frames:
     * 1:RSI_SLP
     * 2:RSI_WKP
     *  Then handle them here based on state machine
     * */  
    if ((frame_type == RSI_RSP_SLP) || (frame_type == RSI_RSP_WKP))
    {
      rsi_handle_slp_wkp(frame_type); 
#ifndef LINUX_PLATFORM
      rsi_irq_enable();
#endif
      return;
    }
  }
#endif  

#ifdef WLAN_ENABLE 
#ifdef RSI_TEST_DBG
  if((queue_no == WLAN_DATA_Q) && (wlan_joined))
  {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL3,"\n####### SENDING RAW DATA of Len %d ######\n",sizeof(rsi_raw_data_pkt));
#endif
    rsi_set_event(RSI_RAW_DATA_TEST_EVENT);
  }
#endif
#endif

  if((queue_no == WLAN_MGMT_Q) && ((frame_type == RSI_RSP_PWRMODE)
        || (frame_type == RSI_RSP_CARD_READY 
          || (frame_type == RSI_RSP_DATA_PACKET_ACK))))
  {
    //Handle DATA ACK for UART here
    if(frame_type == RSI_RSP_DATA_PACKET_ACK)
    {
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL13,"\n Change the state to  RSI_IDLE\n");
      RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %s\n","WLAN","Rx","Send data Rsp","Send Data Ack");
      
#endif
      rsi_common_app_cb.tx_pkt_state = RSI_IDLE_STATE;
      rsi_unmask_queue(&rsi_common_app_cb.rsi_wlan_tx_q);
      rsi_set_event(RSI_TX_EVENT);
      //FIXME: set tx event
    }
    rsi_enqueue_to_rcv_q(&rsi_common_app_cb.rsi_cmn_rx_q,rsi_common_app_cb.device_rx_pkt);
    rsi_set_event(RSI_COMMON_EVENT);
  }
  else
  {
    /* Queue to them to the protocol queue */
    if ((queue_no == BT_Q) || (queue_no == ZB_Q))
    {
      rsi_enqueue_to_rcv_q(&rsi_common_app_cb.rsi_bt_or_zb_rx_q, rsi_common_app_cb.device_rx_pkt);
      rsi_set_event(RSI_BT_OR_ZB_EVENT);
    }
    else if((queue_no == WLAN_MGMT_Q) || (queue_no == WLAN_DATA_Q))
    {
#ifdef RSI_TEST_DBG
#ifndef LINUX_PLATFORM
#ifdef UART_INTERFACE
      //Work around to receive OPERMODE RESP FIXME
      if (frame_type == RSI_RSP_OPERMODE) {
        oper_mode_rcvd=1;
      }
#endif	
#endif	
#endif	
      rsi_enqueue_to_rcv_q(&rsi_common_app_cb.rsi_wlan_rx_q, rsi_common_app_cb.device_rx_pkt);
      rsi_set_event(RSI_WLAN_EVENT);
    } 
  }
#ifdef RSI_TEST_DBG
#ifndef LINUX_PLATFORM 
#ifdef UART_INTERFACE
  if(!oper_mode_rcvd)
  {
    //Work around to receive OPERMODE RESP FIXME
    //Just return ,without clearing RX event.
    return;
  }else
#endif
#endif
#endif
  {
#if !(defined LINUX_PLATFORM || defined WINDOWS)
    rsi_mask_event(RSI_RX_EVENT);
#endif
 
    return;
  }
}



/*====================================================*/
/**
 * @fn          void rsi_tx_event_handler()
 * @brief       This is a event handler for ble tx event.
 * @param[in]   UINT32 event_num
 * @return      void
 * @section description 
 * This function handles the sends data to module. 
 */
volatile UINT8 once_flag=1;
void rsi_tx_event_handler()
{
  PKT_STRUCT_T *pkt = NULL;
  UINT8 *buf_ptr;
  UINT16 length = 0;
#ifdef SPI_INTERFACE
  UINT16 retval =0 ,int_status = 0;
#endif
  UINT8 pkt_pending = 0;
  UINT8 wlan_pkt_pending = 0;
  UINT8 rsi_BtZbPktPending = 0;
  uint8 queueno = 0xff;

  /* First Check for Common Queue */
  if ((pkt_pending = rsi_check_queue_status(&rsi_common_app_cb.rsi_cmn_tx_q)))
  {
    pkt = (PKT_STRUCT_T *)rsi_dequeue_from_rcv_q(&rsi_common_app_cb.rsi_cmn_tx_q);
  }
  else if (( rsi_BtZbPktPending = rsi_check_queue_status(&rsi_common_app_cb.rsi_bt_or_zb_tx_q)))
  {
    pkt = (PKT_STRUCT_T *)rsi_dequeue_from_rcv_q(&rsi_common_app_cb.rsi_bt_or_zb_tx_q);
  }
  else if ((wlan_pkt_pending = rsi_check_queue_status(&rsi_common_app_cb.rsi_wlan_tx_q)))
  {
#ifdef SPI_INTERFACE
    //! Buffer full has to be checked before calling send data
    retval = rsi_device_interrupt_status(&int_status);

    if(retval != 0x0) 
    {
      //FIXME:Have Mask to wlan TX Queue
      rsi_mask_queue(&rsi_common_app_cb.rsi_wlan_tx_q);
      return;
    }

    if(int_status & RSI_IRQ_BUFFERFULL)
    {
      //FIXME:Have Mask to wlan TX Queue
      rsi_mask_queue(&rsi_common_app_cb.rsi_wlan_tx_q);
      return;
    }
#endif
#ifdef UART_INTERFACE
    if(rsi_common_app_cb.tx_pkt_state == RSI_WAITING_FOR_OK)
    {

#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL3,"\nWAITING FOR DATA ACK\n");
#endif
      /* 
       * If ACK for previous packet is not received then don't dequeue 
       * the packet instead return
       * */
      //FIXME:Have Mask to wlan TX Queue
      rsi_mask_queue(&rsi_common_app_cb.rsi_wlan_tx_q);
      //FIXME:clear event
      return; 
    }
#endif

    {
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL13,"\n## Deque Pkt\n");
#endif
      pkt = (PKT_STRUCT_T *)rsi_dequeue_from_rcv_q(&rsi_common_app_cb.rsi_wlan_tx_q);
    }
  }

  if (pkt_pending || wlan_pkt_pending || rsi_BtZbPktPending) 
  {
    buf_ptr = (UINT8 *)pkt->data;
    queueno =  (buf_ptr[1] & 0xf0) >> 4;
    length = (*(UINT16 *)buf_ptr & 0x0FFF);

#ifdef PWR_SAVE
    if (buf_ptr[2] == RSI_REQ_PWRMODE)
    {
      /* Mask Tx events while sending pwr mode req*/
      rsi_mask_tx_events();
    }
#endif
#ifdef WLAN_ENABLE
    if (queueno == WLAN_DATA_Q)
    {
#ifdef UART_INTERFACE
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL13,"\n WAITING FOR DATA ACK\n");
#endif
      rsi_common_app_cb.tx_pkt_state = RSI_WAITING_FOR_OK;
#endif
    }
#endif
#ifdef PWR_SAVE
    if(PwrModeEnable)
    {

#ifndef LINUX_PLATFORM
#if ((RSI_POWER_MODE == RSI_POWER_MODE_2) || (RSI_POWER_MODE == RSI_POWER_MODE_8))
      rsi_req_wakeup();
#endif
#endif


#ifdef RSI_TEST_DBG
#ifndef LINUX_PLATFORM
#ifdef UART_INTERFACE
#ifdef RSI_USE_HOST_WAKEUP_AS_INTERRUPT 
      rsi_deassert_wakeup_source();
      rsi_irq_enable();//UART_COEX_CHANGES 
#endif
#endif
#endif
#endif

    }
#endif
    // Writing to Module
    rsi_frame_write((rsi_uFrameDsc *)buf_ptr,&buf_ptr[16],length);
#ifndef LINUX_PLATFORM
#ifdef UART_INTERFACE
    //FIXME
    if(once_flag){
      rsi_set_event(RSI_RX_EVENT);//Set RX event to receive opermode response
      once_flag=0;
    }
#endif
#endif
    if(wlan_pkt_pending)
    {
#ifdef WLAN_ENABLE
      rsi_wlan_free_pkt(pkt);
#endif
    }
    else if(rsi_BtZbPktPending)
    {
#ifdef BT_ENABLE
      rsi_bt_free_pkt(pkt);
#endif
    }
    else
    {
      rsi_common_free_pkt(pkt);
    }

  } 
  else
  {

#ifdef PWR_SAVE
    if(PwrModeEnable)
    {	
#if ((RSI_POWER_MODE == RSI_POWER_MODE_2) || (RSI_POWER_MODE == RSI_POWER_MODE_8))
      rsi_allow_sleep();
#endif
    }

#if ((RSI_POWER_MODE == RSI_POWER_MODE_3) || (RSI_POWER_MODE == RSI_POWER_MODE_9))
    if(PwrModeEnable)
    {
      if (rsi_common_app_cb.slp_params.module_state == RSI_SLP_RECEIVED)
      {
#ifdef RSI_DEBUG_PRINT
          RSI_DPRINT(RSI_PL3,"\n#ACK\n");
#endif
          //Send ACK if POWERMODE 3 and 9,incase of powermode 2 and 8 make GPIO low
          if (rsi_frame_write(rsi_sleep_ack,NULL,NULL))
          {
#ifdef RSI_DEBUG_PRINT
          RSI_DPRINT(RSI_PL3,"\n#ACK Writing Failed\n");
#endif
          }
          rsi_mask_tx_events();
      }
  }
#endif

#endif

/*FIXEME: Not supposed to be here but enable because it working on RX62N platform only if it is present*/
#ifndef LINUX_PLATFORM
#if (RSI_INTERFACE == RSI_UART)
   rsi_irq_enable();
#endif
#endif
    rsi_clear_event(RSI_TX_EVENT);
  } 

}

#ifndef LINUX_PLATFORM
/*====================================================*/
/**
 * @fn          void bfree(void *buf)
 * @brief       This function release buffer and unmask RX_EVENT.
 * @param[in]   void *buf
 * @return      void
 * @section description 
 * This function release the buffer and unmask RX_EVENT. 
 */
void bfree(void *buff)
{
  brel(buff);
  rsi_unmask_event(RSI_RX_EVENT);
}
#endif
