/**
 * @file     rsi_app.h
 * @version      1.0
 * @date         2014-Jan-31
 *
 * Copyright(C) Redpine Signals 2012
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

#ifndef _RSI_APP_CB_H
#define _RSI_APP_CB_H
/* Application control block */
typedef struct 
{
   /* received paket count */
   uint32        rcvd_data_pkt_count;
   /* flag to enable send data*/
   uint8         glbl_send_data;
   /* Error code */
   uint16        error_code;
   /* Mac address */
   uint8         mac_addr[6];
  /* packet pending flag */
   volatile      uint32 pkt_pending;
   /* Send buffer data */
   uint8         send_buffer[RSI_MAX_PAYLOAD_SIZE+100];
  /* Buffer to hold the received packet */
   uint8 read_packet_buffer[1600];
}rsi_app_cb_t;
extern rsi_app_cb_t rsi_app_cb;

#endif
