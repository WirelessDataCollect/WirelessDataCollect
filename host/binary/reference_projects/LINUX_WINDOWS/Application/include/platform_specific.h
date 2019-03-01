/**
 * @file         platform_specific.h
 * @version      3.1
 * @date         2012-Dec-21
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief HEADER UTIL: Util Header file, the things that are useful for application 
 *
 * @section Description
 * This file is linux platform specific. packet and socket specific
 * structutures are defined here
 *
 *
 */

#ifndef __PLATFORM_SPECIFIC_H_
#define __PLATFORM_SPECIFIC_H_
#ifdef WINDOWS
#include <windows.h>
#include <conio.h>
#else
#include "rsi_zigb_types.h"
#include <pthread.h>
#endif
#include "rsi_serial.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

//@ Some things are boolean values
#define RSI_TRUE        1
#define RSI_FALSE       0
#define RSI_RXPKT_HEAD_ROOM     16
#ifndef ZB_ENABLE
#ifdef WINDOWS
#define RSI_DPRINT(lvl, fmt, ...)                  if (lvl & RSI_DEBUG_LVL) printf(fmt, __VA_ARGS__)
#else
#define RSI_DPRINT(lvl, fmt, args...)              if (lvl & RSI_DEBUG_LVL) printf(fmt, ##args)
#endif
#endif
#define rsi_malloc(a)           malloc(a)
#define rsi_free(a)             free(a)
#define rsi_memcpy(a, b, c)     memcpy(a, b, c)
#define rsi_memset(a, b, c)     memset(a, b, c)

typedef struct pkt_struct_s
{
  struct pkt_struct_s *next;
  uint8_t  *data;
}pkt_struct_t;

/* Receive queue */
typedef struct
{
  pkt_struct_t *head;               /* queue head */
  pkt_struct_t *tail;               /* queue tail*/
  uint16_t pending_pkt_count;         /* pending packets in the queue*/
}pkt_queue_t;
#ifdef WINDOWS
CRITICAL_SECTION	crit_sec;
#endif
/* Application control block */
typedef struct {
  int32_t                nl_sd;       /* netlink socket descriptor */
  int32_t                ioctl_sd;    /* socket descriptor of ioctl */
  int32_t                ttyfd;
  int32_t                family_id;   /* family id */
  uint8_t                rsi_glbl_genl_nl_hdr[20];
  uint8_t                mac_addr[6];
  uint32_t               num_rcvd_packets;
#ifndef WINDOWS
  pthread_mutex_t      mutex1;
#endif
  volatile uint8_t       wfd_dev_found;
  uint8_t                pending_cmd_type;
  volatile int16_t       rsi_status;
  uint32_t               interrupt_rcvd;
  pkt_queue_t          rcv_queue;
  uint8_t                udp_sock_flag;
  /* for set certificate */
  uint8_t                cert_morechunks;
  /* for webpage write */
  uint8_t                webpage_morechunks;
  uint8_t                rx_is_in_progress;
  uint8_t                pre_desc_buf[RSI_PRE_DESC_LEN];
  uint16_t               byte_count;
  uint16_t               payload_size;
  pkt_struct_t          *rcvPktPtr;

}rsi_linux_app_cb_t;

extern rsi_linux_app_cb_t rsi_linux_app_cb;
int16_t rsi_register_interrupt_irq(void);
void measure_throughput(uint32 pkt_length, uint32 tx_rx);
pkt_struct_t *rsi_dequeue_from_rcv_q(void);
void rsi_enqueue_to_rcv_q(pkt_struct_t *Pkt);
uint8_t *rsi_alloc_and_init_cmdbuff(uint8_t *Desc, uint8_t *payload, uint16_t payload_size);
#endif
