/*HEADER**********************************************************************
Copyright (c)
All rights reserved
This software embodies materials and concepts that are confidential to Redpine
Signals and is made available solely pursuant to the terms of a written license
agreement with Redpine Signals

Project name : RSI
Module name  : LINUX SPI driver
File Name    : rsi_nic.h

File Description:

List of functions:

Author :

Rev History:

*END**************************************************************************/
#ifndef __RSI_NIC_H_
#define __RSI_NIC_H_

#include "linux/netdevice.h"
#include <linux/version.h>
#if LINUX_VERSION_CODE == KERNEL_VERSION(2,6,18)
#include <asm/semaphore.h>
#else
#include "linux/semaphore.h"
#endif
#include "rsi_common.h"
#include "rsi_global.h"
#ifdef ENABLE_WMM_FEATURE
#include "rsi_core_wmm.h"
#endif

/* rsi ioctl */
#define RSI_WSC_PRIV_IOCTLS      SIOCDEVPRIVATE
#define OID_WSC_GET_STATUS       RSI_WSC_PRIV_IOCTLS + 0x1
#define OID_WSC_BOOT_READ        RSI_WSC_PRIV_IOCTLS + 0x2
#define OID_WSC_BOOT_WRITE       RSI_WSC_PRIV_IOCTLS + 0x3
#define OID_WSC_BOOT_PING_WRITE  RSI_WSC_PRIV_IOCTLS + 0x4
#define OID_WSC_BOOT_PONG_WRITE  RSI_WSC_PRIV_IOCTLS + 0x5
#define OID_WSC_POWER_SAVE_ENABLE  RSI_WSC_PRIV_IOCTLS + 0x6
#define OID_WSC_WAKEUP  RSI_WSC_PRIV_IOCTLS + 0x7

#define USB_MAX_PACKET_SIZE													2048

#define BIT(n)                                  (1 << (n))
#define MAX_SPI_PKT_SIZE                        1600

#define RSI_LITTLE_ENDIAN                       1 //! Comment this for Big Endian

#define RSI_DESC_LEN                            16
#define RSI_LENGTH_OF_ADDRESS                   6
#define MAX_BUFF_SIZE                           1600
#define RSI_HEADER_SIZE                         14

#define MGMT_QUEUE                              0
#define DATA_QUEUE                              1

#define SND_DATA_Q                              0x5

#define WLAN_PORT_ID 0x1111
#define ZB_PORT_ID   0x2222
#define BT_PORT_ID   0x3333




#define FSM_OPEN                                1

/* Status indications */
#define BUFFER_FULL                             0x01
#define BUFFER_EMPTY                            0x02
#define RX_PKT_PENDING                          0x04 
#define POWER_SAVE                              0x08

/* Kernel version between and including a & b */
#define KERNEL_VERSION_BTWN_2_6_(a,b) \
 ((LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,a)) && \
  (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,b)))

#define KERNEL_VERSION_EQUALS_2_6_(a) \
 (LINUX_VERSION_CODE == KERNEL_VERSION(2,6,a))

/* Kernel version greater than equals */
#define KERNEL_VERSION_GREATER_THAN_EQUALS_2_6_(a)  \
 (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,a))

/* Kernel version Less than equals */
#define KERNEL_VERSION_LESS_THAN_EQUALS_2_6_(a)  \
 (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,a))

/* Update types from user to kernel */
enum {
  MODULE_POWER_CYCLE = 0x01,
  UPDATE_JOIN_DONE   = 0x02,
  PS_CONTINUE        = 0x03,
  WKP_FROM_HOST      = 0x04,
};

typedef struct _RSI_EVENT {
    atomic_t   eventCondition;
    wait_queue_head_t  eventQueue;
}RSI_EVENT, *PRSI_EVENT;

#ifdef USB_INTERFACE
#define USB_VENDOR_REGISTER_READ                    0x15
#define USB_VENDOR_REGISTER_WRITE                   0x16
#define USB_TX_HEAD_ROOM_WLAN                       236
#define USB_TX_HEAD_ROOM_ZB                         0
#define USB_TX_HEAD_ROOM_BT                         0
#define USB_RPINE_VENDER_ID                         0x1618
#define USB_RPINE_VENDER_ID_2                       0x41B
#define USB_RPINE_PRODUCT_ID                        0x9113

#define USB_WLAN                                    0x0
#define USB_BT_ZB                                   0x1
#endif

typedef struct _RSI_ADAPTER
{
#ifdef SPI_INTERFACE
  struct spi_device                               *spi;
#endif
#ifdef USB_INTERFACE
  struct usb_device                               *usbdev;
  struct usb_interface                            *interface;
#define MAX_BULK_END_POINTS     2
  UINT8                                           *rx_buf[MAX_BULK_END_POINTS];
  UINT32                                          rx_len[MAX_BULK_END_POINTS];
  UINT32                                          tx_len[MAX_BULK_END_POINTS];
  UINT32                                          max_rx_len[MAX_BULK_END_POINTS];
  UINT8                                           rx_endpoint_address[MAX_BULK_END_POINTS];
  UINT8                                           tx_endpoint_address[MAX_BULK_END_POINTS];
  
#define MAX_RX_URBS 2 
  struct urb                                      *rx_usb_urb[MAX_RX_URBS];
#define MAX_TX_URBS 2
  struct urb                                      *tx_usb_urb[MAX_TX_URBS];

#endif
  struct workqueue_struct                         *workqueue;
  struct net_device                                *net_device;
  UINT8                                            rx_buffer[MAX_BUFF_SIZE];
  volatile UINT8                                   rsi_status;
  UINT32                                           FSM_STATE;
  struct _RSI_EVENT                                Event;
  struct _RSI_EVENT                                PwrSaveEvent;
  INT32                                            txPkt_count;
  //struct cli_callBk_s       c_callBk ;
  volatile UINT8                                   BufferFull;
  UINT8                                            bufferfull_indicated;
  rsi_powerstate                                   rsi_pwstate;
  struct net_device_stats                         stats;
  struct sk_buff_head                             list[4];
  struct work_struct                              handler;
  spinlock_t                                      lockqueue;
  spinlock_t                                      locks[4];
  UINT8                                           PermanentAddress[RSI_LENGTH_OF_ADDRESS];
  UINT32                                          PktLen; /*Transmit pkt length*/
  UINT8                                           DataRcvPacket[MAX_BUFF_SIZE*4];
  UINT8                                           DataSndPacket[MAX_BUFF_SIZE];
  struct semaphore                                int_check_sem;
  struct semaphore                                sleep_ack_sem;
  struct semaphore                                tx_data_sem;
  UINT32                                          RcvPktLen;
  UINT32                                          InterruptStatus;
  UINT32                                          handler_intr_cnt;
  UINT32                                          int_ctr;
  UINT32                                          isr_intr_cnt;
  UINT32                                          once_full;
  UINT32                                          once_empty;
  UINT32                                          pdca_int_cnt;
  UINT8                                           qos_enable;
  UINT8                                           about_to_send;
  UINT8                                           halt_flag;
  volatile INT32                                  total_pkts_qd;
  UINT16                                          save_flsh_status;
  UINT32                                          wlan_seq_num;
  UINT32                                          zb_seq_num;
  UINT32                                          bt_seq_num;
  INT32                                           txThreadId;
  int                                             transmit_thread_exit;//txThreadDone;
  struct completion                               txThreadComplete;
  uint8                                           irq_registered;
  uint8                                           power_save_enable;

#ifdef ENABLE_WMM_FEATURE
  /* WMM specific variables */
	int32                                             per_q_wt[NUM_EDCA_QUEUES];
	int32                                             wme_org_q[NUM_EDCA_QUEUES];
	int32                                             pkt_contended[NUM_EDCA_QUEUES];
 	//global varibles from onebox_wmm.c
	uint8                                           selected_qnum;
	uint8                                           pkt_cnt;
	uint8                                           tid;
	uint8                                           priority;
  struct chanAccParams                            wme_wmeChanParams;
  uint8                                           dbg_test_values_loaded;
#endif
} RSI_ADAPTER, *PRSI_ADAPTER;

#define RSI_MAX_PKTS_QUEUED  6400
#if 0
typedef struct {
  UINT8  sleep_received;
  UINT8  ack_sent;
}rsi_powerstate;
#endif



#endif  //__RSI_NIC_H_
