/**
 * @file       rsi_commmon_apis.c
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
#include "rsi_global.h"
#include "bget.h"

/* set Operating mode frame */ 
const UINT8   rsi_frameCmdOperModeCmn[3] = {0x10,  0x40, 0x10};
/* Power mode frame */
const UINT8   rsi_frameCmdPowerCmn[RSI_FRAME_DESC_LEN] = {0x02, 0x40, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};    
/* Sleep Ack frame */
const UINT8 rsi_sleep_ack[RSI_FRAME_DESC_LEN]      =    {0x00, 0x40, 0xDE, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 
/* Card Ready frame */
UINT8 card_ready_frame[16] = { 0x00, 0x40, 0x89, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
extern RSI_COMMON_APP_CB_T rsi_common_app_cb;

#ifdef PWR_SAVE
extern volatile UINT8 PwrModeEnable;
#endif

void rsi_unblock_protocol_queues();
void rsi_block_protocol_queues();
void rsi_set_module_sleep_state(uint32 state);
/*====================================================*/
/**
 * @fn          INT16 rsi_sleep_mode_decision()
 * @brief       This is a handler which decides the power
 *              mode to program and change 
 * @param[in]   none
 * @return       0 = not to program
 *               1 = program non-connected sleep
 *               2 = program connected sleep
 * @section description 
 * This function will send the power mode command.
 */
void rsi_sleep_mode_decision(RSI_COMMON_APP_CB_T *rsi_common_app_cb)
{
  UINT8 power_mode = 0;
  UINT8 mode_decision=((rsi_common_app_cb->slp_params.wlan_sleep_mode << 4) | (rsi_common_app_cb->slp_params.bt_or_zb_sleep_mode));
  if(rsi_common_app_cb->slp_params.ps_sent == RSI_PWR_SAVE_RESP )
  {
    rsi_common_app_cb->slp_params.ps_sent= RSI_PWR_SAVE_IDLE;
#ifdef PWR_SAVE 
    if(  rsi_common_app_cb->slp_params.power_mode != RSI_POWER_MODE_0)
    { 
      rsi_send_pwr_mode(rsi_common_app_cb->slp_params.power_mode,RSI_ULP_MODE);
    }
    else
    {
      rsi_unblock_protocol_queues();
      rsi_set_module_sleep_state(RSI_IDLE);
      rsi_set_event(RSI_TX_EVENT);
      rsi_unmask_protocol_events();
      rsi_unmask_tx_events();
    }
#endif
    return;
  }

  if (RSI_COEX_MODE == 0)
  {
    mode_decision=((rsi_common_app_cb->slp_params.wlan_sleep_mode << 4) | (rsi_common_app_cb->slp_params.wlan_sleep_mode));
  }
  else
  {
#if RSI_NO_WLAN_MODE      
    mode_decision=((rsi_common_app_cb->slp_params.bt_or_zb_sleep_mode << 4) | (rsi_common_app_cb->slp_params.bt_or_zb_sleep_mode));
#else
    mode_decision=((rsi_common_app_cb->slp_params.wlan_sleep_mode << 4) | (rsi_common_app_cb->slp_params.bt_or_zb_sleep_mode));
#endif    
  }

  switch(mode_decision)
  {
    case 0x00:
    case 0x10:
    case 0x01:
    case 0x20:
    case 0x02:
      {
        power_mode = RSI_POWER_MODE_0;
      }
      break;
    case 0x11:
      {
#if (RSI_POWER_MODE == RSI_POWER_MODE_8)    
        power_mode = RSI_POWER_MODE_8;
#elif (RSI_POWER_MODE == RSI_POWER_MODE_9)
        power_mode = RSI_POWER_MODE_9;
#endif 
      }
      break;
    case 0x21:
    case 0x12: 
    case 0x22:
      {
#if (RSI_POWER_MODE == RSI_POWER_MODE_2)    
        power_mode = RSI_POWER_MODE_2;
#elif (RSI_POWER_MODE == RSI_POWER_MODE_3)
        power_mode = RSI_POWER_MODE_3;
#elif (RSI_POWER_MODE == RSI_POWER_MODE_1)
          power_mode = RSI_POWER_MODE_1;
#endif    
      }
      break;

  }

  if (rsi_common_app_cb->slp_params.power_mode != power_mode)
  {
    rsi_common_app_cb->slp_params.power_mode = power_mode;
#ifdef PWR_SAVE    
    //First Send Power mode zero
    rsi_send_pwr_mode(RSI_POWER_MODE_0,RSI_ULP_MODE);
#endif
    //Block protocol events
    rsi_mask_protocol_events(); 
    rsi_common_app_cb->slp_params.ps_sent =RSI_PWR_SAVE_INTER;
  }

}


/*====================================================*/
/**
 * @fn          void rsi_send_pwr_mode(UINT8 power_mode,UINT8 ulp_mode)
 * @brief       This is a handler which decides the power
 *              mode to program and change 
 * @param[in]   power mode,the power mode to be programmed
 * @param[in]   ulp_mode,the ulp mode to be programmed
 * @return      none
 * @section description 
 * This function will send the power mode command.
 */
void rsi_send_pwr_mode(UINT8 power_mode,UINT8 ulp_mode)
{
  UINT8 pwr_mode[2];
  pwr_mode[0]=power_mode;
  pwr_mode[1]=ulp_mode;
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3, "\n Sending Power Mode:%d \n",power_mode);
#endif  
  rsi_common_execute_cmd((UINT8 *)rsi_frameCmdPowerCmn ,&pwr_mode[0], sizeof(pwr_mode));
}

/*====================================================*/
/**
 * @fn          void rsi_send_oper_mode()
 * @brief       This is used to send oper mode.
 * @return      void
 * @section description 
 * This function sends the oper mode. 
 */
void rsi_send_oper_mode()
{
  UINT8 cmd_buff[16],opermode[15],coex[20];
  rsi_uOperMode oper;
  rsi_uint32_to_4bytes(oper.operModeFrameSnd.oper_mode, RSI_OPERMODE);
  rsi_uint32_to_4bytes(oper.operModeFrameSnd.feature_bit_map, RSI_FEATURE_BIT_MAP);
  rsi_uint32_to_4bytes(oper.operModeFrameSnd.tcp_ip_feature_bit_map, RSI_TCP_IP_FEATURE_BIT_MAP);
  rsi_uint32_to_4bytes(oper.operModeFrameSnd.custom_feature_bit_map, RSI_CUSTOM_FEATURE_BIT_MAP);


  rsi_memset(cmd_buff, 0, RSI_FRAME_DESC_LEN);
  rsi_memcpy(cmd_buff, rsi_frameCmdOperModeCmn, sizeof(rsi_frameCmdOperModeCmn));
  
	if(RSI_WIFI_OPER_MODE== 0)
		rsi_memcpy(opermode,"WLAN Client",13);
	else if(RSI_WIFI_OPER_MODE== 1)
  		rsi_memcpy(opermode,"WLAN P2P Mode",14);
	else if(RSI_WIFI_OPER_MODE== 2)
  		rsi_memcpy(opermode,"WLAN EAP Sec",14);
	else if(RSI_WIFI_OPER_MODE== 6)
  		rsi_memcpy(opermode,"WLAN AP Mode",14);
	else if(RSI_WIFI_OPER_MODE== 8)
  		rsi_memcpy(opermode,"PER Mode",14);
  		
	if(RSI_COEX_MODE== 0)
		rsi_memcpy(coex,"Only",13);
	else if(RSI_COEX_MODE== 3)
  		rsi_memcpy(coex,"ZigBee Coex Mode",20);
	else if(RSI_COEX_MODE== 5)
  		rsi_memcpy(coex,"BT Coex Mode",20);
	else if(RSI_COEX_MODE== 13)
  		rsi_memcpy(coex,"BTLE Coex Mode",20);		
  
  RSI_DPRINT(RSI_PL3,"\n%-10.7s%-4.2s %-20.15s %s %s + %s\n","WLAN","Tx","Operating Mode Req","Mode:",opermode,coex);
  rsi_common_execute_cmd(cmd_buff, (UINT8 *)&oper,sizeof(rsi_uOperMode));
}

/*====================================================*/
/**
 * @fn          void rsi_common_execute_cmd(UINT8 *desc, UINT8 *payload, UINT16 payload_len)
 * @brief       This is used to send common mgmt pkts.
 * @param[in]   uint8 *descparam, pointer to the frame descriptor parameter structure
 * @param[in]   uint8 *payloadparam, pointer to the command payload parameter structure
 * @param[in]   uint16 size_param, size of the payload for the command
 * @return      void
 * @section description 
 * This function sends the oper mode. 
 */

void rsi_common_execute_cmd(UINT8 *desc, UINT8 *payload, UINT16 payload_len)
{
  UINT8 *cmd_buff = NULL;
  PKT_STRUCT_T *pkt = (PKT_STRUCT_T *)&rsi_common_app_cb.rsi_device_tx_pkt[0];
  if(pkt == NULL)
  {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL13,"Allocation failed to recv packet\n");
#endif
    return;
  }
  pkt->next = (PKT_STRUCT_T *)(((UINT8 *)pkt));
  pkt->data = (UINT8 *)(((UINT8 *)pkt) + (sizeof(UINT8 *) * 2) );

  cmd_buff = (UINT8 *)pkt->data;

  rsi_memcpy(cmd_buff, desc, RSI_FRAME_DESC_LEN);

  if (payload_len)
    rsi_memcpy((cmd_buff + RSI_FRAME_DESC_LEN), payload, payload_len);

  rsi_enqueue_to_rcv_q(&rsi_common_app_cb.rsi_cmn_tx_q, pkt);
  rsi_set_event(RSI_TX_EVENT);
}


/*====================================================*/
/**
 * @fn          UINT16 rsi_cmn_pkt_parser(UINT8 *buffer, UINT16 resp_frame)
 * @brief       Common function for all the commands.
 * @param[in]   UINT8 *buffer, pointer to the rcvd pkt
 * @param[in]   UINT8 resp_frame, the resp cmd from module
 * @return      void
 * @section description 
 * This is a common function used to parse the pkt from the module.
 */

UINT16 rsi_cmn_pkt_parser(UINT8 *buffer, UINT16 resp_frame)
{
  UINT16 status=0xFF;
  switch(resp_frame)
  {
    case RSI_RSP_CARD_READY:
      {
#ifdef RSI_DEBUG_PRINT
        RSI_DPRINT(RSI_PL3,"CARD READY RECEIVED\n");
#endif
        rsi_send_oper_mode();

        break;
      }
    case RSI_RSP_PWRMODE:
      {
        status = (*(uint16 *)(buffer + RSI_STATUS_OFFSET));
        if(!status)
        {
#ifdef RSI_DEBUG_PRINT
          RSI_DPRINT(RSI_PL3,"Power Mode Response:Success\n");
#endif
#ifdef PWR_SAVE
            if(rsi_common_app_cb.slp_params.ps_sent == RSI_PWR_SAVE_INTER)
            {
              rsi_common_app_cb.slp_params.ps_sent =RSI_PWR_SAVE_RESP;
              rsi_set_event(RSI_COMMON_EVENT);
              PwrModeEnable=0;
              rsi_block_protocol_queues();  
            }
            else
            {
              rsi_common_app_cb.slp_params.ps_sent =RSI_PWR_SAVE_IDLE;
              PwrModeEnable=1;

              rsi_unmask_protocol_events();
              rsi_unblock_protocol_queues();
              if(rsi_common_app_cb.slp_params.power_mode == RSI_POWER_MODE_9)
              {
                return 0;
              }
              rsi_set_module_sleep_state(RSI_WKUP_RECEIVED);
              rsi_set_event(RSI_TX_EVENT);
            }
#endif
        }
        else
        {
          rsi_unblock_protocol_queues();
          rsi_unmask_protocol_events();
          rsi_set_module_sleep_state(RSI_IDLE);
          rsi_set_event(RSI_TX_EVENT);
#ifdef RSI_DEBUG_PRINT
          RSI_DPRINT(RSI_PL3,"Power Mode Response Failed\n");
#endif
        }
        rsi_unmask_tx_events();    
        break;
      }
    default:
      {
        break;
      }
  }
  return 0;
}

/*====================================================*/
/**
 * @fn          void rsi_common_free_pkt(PKT_STRUCT_T *pkt)
 * @brief       Common function for all the commands.
 * @param[in]   PKT_STRUCT_T *pkt, pointer to the rcvd pkt
 * @return      void
 * @section description 
 * This is a common function used to parse the pkt from the module.
 */

void rsi_common_free_pkt(PKT_STRUCT_T *pkt)
{
}

/*==============================================*/
/**
 * @fn          void rsi_skip_card_ready(void)
 * @brief       Send alternate card ready 
 * @param[in]   none
 * @param[out]  none
 * @return      none
 * @section description
 * This function will send the card ready
 */
void rsi_skip_card_ready(void)
{
  PKT_STRUCT_T *rcvPktPtr = NULL;
  /* Allocate Memory */
  rcvPktPtr = (PKT_STRUCT_T *)rsi_common_app_cb.device_rx_pkt;
  if(rcvPktPtr == NULL){
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL13,"Allocation failed to recv packet\n");
#endif
    return ;
  }

  rcvPktPtr->next = NULL;
  rcvPktPtr->data = (UINT8 *)(((UINT8 *)rcvPktPtr) + (sizeof(UINT8 *) * 2) );

  rsi_memcpy((UINT8 *)rcvPktPtr->data, card_ready_frame, RSI_FRAME_DESC_LEN);
  rsi_enqueue_to_rcv_q(&rsi_common_app_cb.rsi_cmn_rx_q, rcvPktPtr);
  rsi_set_event(RSI_COMMON_EVENT);

  /*
   * Set the Receive Event here. In case of microcontrolle
   * set this event in ISR
   */

}


/*=================================================*/
/**
 * @fn          void rsi_enqueue_to_rcv_q(PKT_QUEUE_T *rcv_q, PKT_STRUCT_T *Pkt)
 * @brief       To enqueue the packet to receive queue
 * @param[in]   PKT_STRUCT_T *Pkt
 * @param[in]   PKT_QUEUE_T *rcv_q
 * @param[out]  none
 * @return      none
 * @section description
 * This API is used to enqueue the received packet.
 */
void rsi_enqueue_to_rcv_q(PKT_QUEUE_T *rcv_q, PKT_STRUCT_T *Pkt)
{
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_enqueue_to_rcv_q:\n");
#endif
  if(rcv_q->tail == NULL)
  {
    rcv_q->head = Pkt;
  }
  else
  {
    rcv_q->tail->next  = Pkt;
  }
  rcv_q->tail = Pkt;
  rcv_q->tail->next = NULL;
  rcv_q->pending_pkt_count++;
  return;
}


/*=================================================*/
/**
 * @fn          PKT_STRUCT_T *rsi_dequeue_from_rcv_q(PKT_QUEUE_T *rcv_q)
 * @brief       To dequeue the packet to receive queue
 * @param[in]   PKT_QUEUE_T *rcv_q,The queue to be dequeued.
 * @param[out]  none
 * @return      PKT_STRUCT_T *Pkt, dequeued packet pointer
 * @section description
 * This API is used to dequeue the packets from receive queue
 * when packets are pending in queue.
 */
PKT_STRUCT_T* rsi_dequeue_from_rcv_q(PKT_QUEUE_T *rcv_q)
{
  PKT_STRUCT_T *Pkt = NULL;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_dequeue_from_rcv_q:\n");
#endif
  if(rcv_q->pending_pkt_count > 0)
  {
    rcv_q->pending_pkt_count--;
    Pkt = rcv_q->head;
    rcv_q->head = rcv_q->head->next;
    if(rcv_q->head == NULL)
    {
      rcv_q->tail = NULL;
    }
  }
  return Pkt;
}

/*=================================================*/
/**
 * @fn          UINT16 rsi_check_queue_status(void)
 * @brief       To Check the packet count.
 * @param[in]   none
 * @param[out]  none
 * @return      pending packet count in queue
 * @section description
 * This API is used to get the pending packet count in queue
 */
void rsi_queues_init(void)
{
  PKT_STRUCT_T *rcvPktPtr = NULL;
  rsi_common_app_cb.rsi_cmn_rx_q.queue_mask=0;
  rsi_common_app_cb.rsi_wlan_rx_q.queue_mask=0;
  rsi_common_app_cb.rsi_bt_or_zb_rx_q.queue_mask=0;
  rsi_common_app_cb.rsi_cmn_tx_q.queue_mask=0;
  rsi_common_app_cb.rsi_wlan_tx_q.queue_mask=0;
  rsi_common_app_cb.rsi_bt_or_zb_tx_q.queue_mask=0;
   rsi_common_app_cb.device_rx_pkt = rcvPktPtr =(PKT_STRUCT_T *)&rsi_common_app_cb.rsi_device_rx_pkt[0];
  rcvPktPtr->next = (PKT_STRUCT_T *)(((UINT8 *)rcvPktPtr));
  rcvPktPtr->data= (UINT8 *)(((UINT8 *)rcvPktPtr) + (sizeof(UINT8 *) * 2) );



}

/*=================================================*/
/**
 * @fn          UINT16 rsi_check_queue_status(PKT_QUEUE_T *rcv_queue)
 * @brief       To Check the packet count.
 * @param[in]   PKT_QUEUE_T *rcv_queue,the queue whose status is to be checked.
 * @return      pending packet count in queue
 * @section description
 * This API is used to get the pending packet count in queue
 */
UINT16 rsi_check_queue_status(PKT_QUEUE_T *rcv_queue)
{
  if(rcv_queue->queue_mask)
  {
    // If the queue is masked return 0,implies no pkt in queue.
    return 0;
  }
  else
  {
    return rcv_queue->pending_pkt_count;
  }
}

/*=================================================*/
/**
 * @fn          UINT8 *rsi_alloc_and_init_cmdbuff(UINT8 *Desc,
 *                                       UINT8 *payload,
 *                                       UINT16 payload_size)
 * @brief       To allocate and initialise the command buffer.
 * @param[in]   PKT_STRUCT_T *Pkt
 * @param[out]  none
 * @return      none
 * @section description
 * This API is used to allocate a buffer for the command to send and
 * initializing it with all the header bytes, Desc and payload filled.
 */
UINT8 *rsi_alloc_and_init_cmdbuff(UINT8 *Desc, UINT8 *payload, UINT16 payload_size)
{
  UINT8 *cmd_buff;
  UINT16 desc_len = 0;
  desc_len = RSI_FRAME_DESC_LEN;
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_alloc_and_init_cmdbuff\n");
#endif
  cmd_buff = rsi_malloc(payload_size + desc_len);
  if(cmd_buff == NULL){
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL13,"Allocation failed to recv packet\n");
#endif
    return NULL;
  }
  rsi_memcpy(cmd_buff, Desc, desc_len);

  if(payload_size)
    rsi_memcpy((cmd_buff + desc_len), payload, payload_size);

  return cmd_buff;
}



/*=================================================*/
/**
 * @fn          void rsi_handle_slp_wkp(uint8_t frame_type)
 * @brief       To handle slp and wkp.
 * @param[in]   uint8_t frame_type
 * @param[out]  none
 * @return      none
 * @section description
 * This API is used to handle slp and wkp. 
 */

void rsi_handle_slp_wkp(uint8 frame_type)
{
  //! Handle them here based on power save state machine 
  switch (frame_type)
  {
    case RSI_RSP_SLP:
      {
#ifdef RSI_DEBUG_PRINT
        RSI_DPRINT(RSI_PL3,"\n#SLP\n");
#endif
        rsi_common_app_cb.slp_params.module_state = RSI_SLP_RECEIVED;
        rsi_set_event(RSI_TX_EVENT);
      }
      break;
    case RSI_RSP_WKP:
      {
#ifdef RSI_DEBUG_PRINT
        RSI_DPRINT(RSI_PL3,"\n#WKP\n");
#endif
        rsi_common_app_cb.slp_params.module_state = RSI_WKUP_RECEIVED;
#if ((RSI_POWER_MODE == RSI_POWER_MODE_3) || (RSI_POWER_MODE == RSI_POWER_MODE_9))    
        if(rsi_common_app_cb.slp_params.power_mode == RSI_POWER_MODE_9)
        {
          rsi_common_app_cb.slp_params.module_state = RSI_SLP_RECEIVED;
        }
#endif
        rsi_set_event(RSI_TX_EVENT);
        rsi_unmask_tx_events();
      }
      break;
  }

}
/*=================================================*/
/**
 * @fn          void rsi_unblock_protocol_queues()
 * @brief       To unblock protocol queues.
 * @param[in]   none
 * @param[out]  none
 * @return      none
 * @section description
 * This API is used to unblock protocol queues. 
 */
void rsi_unblock_protocol_queues()
{
  rsi_unmask_queue(&rsi_common_app_cb.rsi_wlan_tx_q);
  rsi_unmask_queue(&rsi_common_app_cb.rsi_bt_or_zb_tx_q);
}

/*=================================================*/
/**
 * @fn          void rsi_block_protocol_queues()
 * @brief       To unblock protocol queues.
 * @param[in]   none
 * @param[out]  none
 * @return      none
 * @section description
 * This API is used to handle slp and wkp. 
 */
void rsi_block_protocol_queues()
{
  rsi_mask_queue(&rsi_common_app_cb.rsi_wlan_tx_q);
  rsi_mask_queue(&rsi_common_app_cb.rsi_bt_or_zb_tx_q);
}

/*=================================================*/
/**
 * @fn          void rsi_set_module_sleep_state(uint32_t state)
 * @brief       To handle set module sleep state.
 * @param[in]   uint32 state state to set
 * @param[out]  none
 * @return      none
 * @section description
 * This API is used to set module sleep state. 
 */
void rsi_set_module_sleep_state(uint32 state)
{
  rsi_common_app_cb.slp_params.module_state =  state;
}
