/**
 * @file        measure_throughputs.c
 * @version     1.0
 * @date        24Mar2014
 *
 * Copyright(C) 2013 Redpine Signals Inc.
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * T:vshis program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief MEASURE THROUGHPUTS
 *
 * @section Description
 * This file contains the throughput measurement related api
 */

/**
 * Include files
 */

#include <sys/time.h>
#include <stdio.h>
#include "rsi_global.h"

static uint32 last_tx_print_time;
static uint32 last_rx_print_time;

uint32 total_tx_bytes;
uint32 total_rx_bytes;
uint32 secs;

/*==============================================*/
/**
 * @fn           void measure_throughput(uint32 pkt_length, uint32 tx_rx)
 * @brief        measures throughput.
 * @param[in]    pkt_length of the received packet
 * @param[in]    tx_rx,if tx_rx = 0,indicates the tx pkt
 *                     if tx_rx = 1,indicated the rx pkt
 * @param[out]   none
 * @section description 
 * This API is used to measure throughput of packets recceived/transmitted
 */
void measure_throughput(uint32  pkt_length, uint32 tx_rx)
{
    static uint32 current_time;
    static uint32 last_print_time;
    uint32 total_bytes;
    struct timeval tv1;
    float through_put;

    gettimeofday(&tv1, NULL);
    current_time = tv1.tv_sec * 1000000 + tv1.tv_usec;
    if(tx_rx == 0)
    {
      total_tx_bytes += pkt_length;
      total_bytes = total_tx_bytes;
      last_print_time = last_tx_print_time;
    }
    else
    {
      total_rx_bytes += pkt_length;
      total_bytes = total_rx_bytes;
      last_print_time = last_rx_print_time;
    }
    if((current_time-last_print_time)>=1000000)    //!for 1 sec
    {
      through_put = ((float)(total_bytes)/((current_time-last_print_time))) * 8;
      if(tx_rx == 0)
      {
        printf("\nSecs: %d     Bytes Transmitted %d,Throughput for last %d seconds is = %3.1f Mbps\n",secs++,total_bytes,(current_time-last_print_time)/1000000, through_put);
        last_tx_print_time = current_time;
        total_tx_bytes = 0;
      }
      else
      {
        printf("\nSecs: %d     Bytes Received %d,Throughput for last %d seconds is = %3.1f Mbps\n",secs++,total_bytes,(current_time-last_print_time)/1000000, through_put);
        last_rx_print_time = current_time;
        total_rx_bytes = 0;
      }
    }
    return;
}

