/**
 * @file         rsi_scheduler.h
 * @version      1.0
 * @date         2015-Feb-17
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
#ifndef RSI_SCHEDULER_H
#define RSI_SCHEDULER_H

#include "rsi_common_types.h"
#ifndef LINUX_PLATFORM
#include "bget.h"
#endif

#define RSI_MAX_NUM_EVENTS                 6

#define RSI_RESP_OFFSET                2
#define RSI_BYTE_4                     4

#define RSI_RX_EVENT                   0
#define RSI_COMMON_EVENT               1
#define RSI_BT_OR_ZB_EVENT             2
#define RSI_WLAN_EVENT                 3
#define RSI_TX_EVENT                   4
#define RSI_RAW_DATA_TEST_EVENT        5

#define ZB_Q                           1
#define BT_Q                           2
#define WLAN_MGMT_Q                    4
#define WLAN_DATA_Q                    5

#define RSI_PWR_SAVE_IDLE              0
#define RSI_PWR_SAVE_INTER             1
#define RSI_PWR_SAVE_RESP              2


#define RSI_FRAME_DESC_LEN            16
#define RSI_MAX_PAYLOAD_SIZE          1600

#define RSI_SECONDARY_PROTO           0xE 

/* Module State Machine */
#define RSI_IDLE               0
#define RSI_SLP_RECEIVED       1
#define RSI_SLP_ACK_SENT       2
#define RSI_WKUP_RECEIVED      3



#ifdef LINUX_PLATFORM
#define rsi_malloc(ptr) malloc(ptr)
#define rsi_free(ptr)	  free(ptr)
#endif
/*==============================================*/


#define RSI_MAX_BUFFER_SIZE 1600
#define RSI_MAX_NO_OF_BUFF  10


/* This structure contains the information
 * on which the scheduler core operates and
 * controls the execution of events */
typedef struct scheduler_info_s
{
	/* This bitmap is used to set and
	 * clear events */
	volatile UINT32 event_map;
	/* This bitmap is used to mask and
	 * unmask events */
	volatile UINT32 mask_map;
}RSI_SCHEDULER_INFO_T;

/* EVENT control block */
typedef struct event_cb_s
{
  void   (*event_handler)(void);
}RSI_EVENT_CB_T;

/* Power Save Structure */
typedef struct rsi_sleep_params_s
{
  /* module state */
  UINT32 module_state;
#define RSI_ACTIVE           0
#define RSI_DEEP_SLEEP       1
#define RSI_CONNECTED_SLEEP  2  
  /* WLAN Sleep Mode */
  UINT32 wlan_sleep_mode;
  /* Secondary Protocol Sleep Mode */
  UINT32  bt_or_zb_sleep_mode;
  /* Power Mode */
  UINT8 power_mode;
  /* power save sent flag */
  UINT8 ps_sent;

} RSI_SLEEP_PARAMS_T;

typedef struct pkt_struct_s
{
  struct pkt_struct_s *next;
  UINT8  *data;
}PKT_STRUCT_T;

/* Receive queue */
typedef struct
{
  PKT_STRUCT_T *head;               /* queue head */
  PKT_STRUCT_T *tail;               /* queue tail*/
  UINT16 pending_pkt_count;         /* pending packets in the queue*/
  UINT16 queue_mask;                /* pending packets in the queue*/
}PKT_QUEUE_T;

typedef struct rsi_common_app_cb_s
{
  /* Scheduler */
  RSI_SCHEDULER_INFO_T scheduler_info;
  RSI_EVENT_CB_T event_list[RSI_MAX_NUM_EVENTS];
  /* RX Queues */
  PKT_QUEUE_T rsi_cmn_rx_q;
  PKT_QUEUE_T rsi_wlan_rx_q;
  PKT_QUEUE_T rsi_bt_or_zb_rx_q;
  /* TX Queues */
  PKT_QUEUE_T rsi_cmn_tx_q;
  PKT_QUEUE_T rsi_wlan_tx_q;
  PKT_QUEUE_T rsi_bt_or_zb_tx_q;
  /* Power Save params */
  RSI_SLEEP_PARAMS_T slp_params;
  /* UART interface pkt txfers*/
#define RSI_IDLE_STATE         0
#define RSI_WAITING_FOR_OK     1
  UINT8 tx_pkt_state;
  UINT8 rsi_device_rx_pkt[1600];
  UINT8 rsi_device_tx_pkt[1600];
  PKT_STRUCT_T *device_rx_pkt;
} RSI_COMMON_APP_CB_T;

extern RSI_COMMON_APP_CB_T rsi_common_app_cb;




extern void bfree(void *buff);
INT16 rsi_main(void);
UINT16 rsi_cmn_pkt_parser(UINT8 *buffer, UINT16 resp_frame);
void rsi_send_pwr_mode(UINT8 power_mode,UINT8 ulp_mode);

void rsi_coex_scheduler_init(RSI_SCHEDULER_INFO_T *scheduler_info);
void rsi_coex_scheduler(RSI_SCHEDULER_INFO_T *scheduler_info);
UINT16 rsi_register_event(UINT32 event_id, void (*event_handler_ptr)(void));
INT16 rsi_pkt_pending_event_raiser(UINT8* buffer);
void rsi_set_event(UINT32 event_num);
void rsi_clear_event(UINT32 event_num);
void rsi_mask_event(UINT32 event_num);
void rsi_unmask_event(UINT32 event_num);
void rsi_mask_tx_events();
void rsi_unmask_tx_events();

UINT32 rsi_find_event(UINT32 event_map);
void rsi_tx_event_handler(void);
void rsi_bt_or_zb_event_handler(void);
void rsi_wlan_event_handler(void);
void rsi_ble_app_event(UINT8 *buffer);
int rsi_zigb_state_machine(UINT8 *pkt_buffer);
void rsi_zigb_init_struct();
INT16 rsi_send_to_module(UINT8 *data, UINT16 length);

void rsi_set_bt_or_zb_sleep_mode(UINT32 mode);
void rsi_set_wlan_sleep_mode(UINT32 mode);
UINT8 rsi_chk_tx_event(void);


void rsi_send_oper_mode();
void rsi_common_execute_cmd(UINT8 *desc, UINT8 *payload, UINT16 payload_len);
void rsi_common_free_pkt(PKT_STRUCT_T *pkt);
UINT16 rsi_check_queue_status(PKT_QUEUE_T *rcv_queue);
void rsi_sleep_mode_decision(RSI_COMMON_APP_CB_T *rsi_common_app_cb);
void rsi_wlan_free_pkt(PKT_STRUCT_T *pkt);

INT16 rsi_wlan_app_event(UINT8 *buffer);
void rsi_ble_struct_init();
void rsi_skip_card_ready(void);
void rsi_set_wlan_sleep_mode(UINT32 mode);
void rsi_set_bt_or_zb_sleep_mode(UINT32 mode);
void rsi_mask_queue(PKT_QUEUE_T *rcv_queue);
void rsi_unmask_queue(PKT_QUEUE_T *rcv_queue);
void rsi_queues_init(void);
void rsi_handle_slp_wkp(UINT8 frame_type);
void rsi_enqueue_to_rcv_q(PKT_QUEUE_T *rcv_q, PKT_STRUCT_T *Pkt);
PKT_STRUCT_T* rsi_dequeue_from_rcv_q(PKT_QUEUE_T *rcv_q);
void rsi_queues_init(void);
UINT16 rsi_check_queue_status(PKT_QUEUE_T *rcv_queue);
UINT8 *rsi_alloc_and_init_cmdbuff(UINT8 *Desc, UINT8 *payload, UINT16 payload_size);
void rsi_mask_protocol_events();
void rsi_unmask_protocol_events();
#endif
