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
#include <stdio.h>
#include <stdarg.h>
#endif
#ifdef LINUX_PLATFORM
#include <pthread.h>
#include <malloc.h>
#include "rsi_serial.h"
#endif
#ifndef LINUX_PLATFORM
#ifndef WINDOWS
#include "iodefine.h"
#endif
#include "rsi_app.h"
#endif
#include "rsi_scheduler.h"
#include "rsi_common_types.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//@ Some things are boolean values
#define RSI_TRUE        1
#define RSI_FALSE       0
#define RSI_RXPKT_HEAD_ROOM     16
#ifndef ZB_ENABLE
#endif
#ifdef LINUX_PLATFORM
#define rsi_memcpy(a, b, c)     memcpy(a, b, c)
#define rsi_memset(a, b, c)     memset(a, b, c)
#endif

#ifdef LINUX_PLATFORM
#define RSI_DPRINT(lvl, fmt, args...)              if (lvl & RSI_DEBUG_LVL) printf(fmt, ##args)
#else
#ifdef WINDOWS
#define RSI_DPRINT(lvl, fmt ...)                  if (lvl & RSI_DEBUG_LVL) printf(fmt)
#else
#define RSI_DPRINT(lvl, fmt, args)              if (lvl & RSI_DEBUG_LVL) while(0)
#endif
#endif

#ifndef RSI_PRE_DESC_LEN
#define RSI_PRE_DESC_LEN 4
#endif

#if (defined WINDOWS || defined LINUX_PLATFORM)
#ifdef WINDOWS
CRITICAL_SECTION	crit_sec;
#endif
/* Application control block */
typedef struct {
  int32_t              ttyfd;
  UINT8                mac_addr[6];
  uint32_t             num_rcvd_packets;
#ifndef WINDOWS
  pthread_mutex_t      mutex1;
#endif
  volatile UINT8       wfd_dev_found;
  UINT8                pending_cmd_type;
  volatile INT16       rsi_status;
  uint32_t             interrupt_rcvd;
  PKT_QUEUE_T          rcv_queue;
  UINT8                udp_sock_flag;
  /* for set certificate */
  UINT8                cert_morechunks;
  /* for webpage write */
  UINT8                webpage_morechunks;
  UINT8                rx_is_in_progress;
  UINT8                pre_desc_buf[RSI_PRE_DESC_LEN];
  UINT16               byte_count;
  UINT16               payload_size;
  PKT_STRUCT_T         *rcvPktPtr;

}rsi_linux_app_cb_t;

extern rsi_linux_app_cb_t rsi_linux_app_cb;
INT16  rsi_register_interrupt_irq(void);
void   measure_throughput(uint32  pkt_length, uint32 tx_rx);
PKT_STRUCT_T *rsi_dequeue_from_rcv_q(PKT_QUEUE_T *);
void   rsi_enqueue_to_rcv_q(PKT_QUEUE_T *, PKT_STRUCT_T *);
UINT8  *rsi_alloc_and_init_cmdbuff(UINT8 *Desc, UINT8 *payload, UINT16 payload_size);
#endif
#endif
