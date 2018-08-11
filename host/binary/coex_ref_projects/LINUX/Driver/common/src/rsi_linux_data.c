/**
 * @file          rsi_linux_data.c
 * @version       1.6
 * @date          2013-June-12
 *
 * Copyright(C) Redpine Signals 2013
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief This contains all the functions related to data tranfer
 * over net device.
 *
 * @section Description
 * This file contains the following functions.
 *    rsi_xmit
 *    rsi_transmit_thread
 *    rsi_indicate_packet
 *
 */

#include "rsi_linux.h"
#include "rsi_nic.h"
#include "rsi_api.h"
#ifdef ENABLE_WMM_FEATURE
#include "rsi_core_wmm.h"
#endif
#include <linux/sched.h>

/*==============================================*/
/**
 * @fn          INT32 rsi_xmit (struct sk_buff *skb,
 *                           struct net_device *dev)
 * @brief       To transmit data
 * @param[in]   struct sk_buff *skb,
 *              Pointer to the socket buffer structure
 * @param[in]   struct net_device *dev,
 *              Pointer to our network device structure
 * @param[out]  none
 * @return      errCode
 *              -ve = FAIL
 *              0  = SUCCESS
 * @section description
 * When a packet is sent by the upper layers, the transmit entry
 * point registered at the time of initialization will be called.
 * This function will que the skb and set the event.
 */

#ifdef ENABLE_WMM_FEATURE
void onebox_set_contention_vals(struct chanAccParams wme_wmeChanParams, PRSI_ADAPTER adapter);
uint8 core_determine_hal_queue(PRSI_ADAPTER adapter);
#endif

INT32 rsi_xmit (struct sk_buff *skb, struct net_device *dev)
{
  PRSI_ADAPTER Adapter = rsi_getpriv (dev);
#ifdef ENABLE_WMM_FEATURE
 	UINT16 pkt_priority = BE_Q_STA;
	UINT8  tos;
#endif
  UINT32 qId;

#ifdef RSI_DEBUG_PRINT
  RSI_DEBUG(RSI_ZONE_SPI_DBG,"\nrsi_xmit:\n");
#endif
  RSI_DEBUG (RSI_ZONE_DATA_SEND, "+rsi_xmit\n");

  /*Checking if data pkt is rcvd in open state or not */
  if (Adapter->FSM_STATE != FSM_OPEN)
  {
    RSI_DEBUG (RSI_ZONE_ERROR, "rsi_xmit: Not in open state ");
    goto fail;
  }

  /* Checking the size of the packet */
  if (skb->len > 1528)
  {
    RSI_DEBUG (RSI_ZONE_ERROR, "rsi_xmit: Big packet ");
    goto fail;
  }

#ifdef ENABLE_WMM_FEATURE

  if(!Adapter->dbg_test_values_loaded)
  {
    Adapter->dbg_test_values_loaded = 1;
    onebox_set_contention_vals(Adapter->wme_wmeChanParams,Adapter);
  }

  if (Adapter->total_pkts_qd > RSI_MAX_PKTS_QUEUED){
    RSI_DEBUG (RSI_ZONE_DATA_SEND, "rsi_xmit: failed due to total pkt qd crossed RSI_MAX_PKTS_QUEUED\n");
    //goto fail;
  }

#ifdef RSI_WMM_PS_SUPPORT
  /* Incase of device encap pick the tos from the IP hdr */
  tos = skb->data[15] >> 5;
  Adapter->tid = tos; 
  Adapter->priority = TID_TO_WME_AC(tos);
#else
  Adapter->priority = 1;
#endif
  switch (Adapter->priority) 
  {
    case WME_AC_VO:
      pkt_priority = VO_Q_STA;
      break;
    case WME_AC_VI:
      pkt_priority = VI_Q_STA;
      break;
    case WME_AC_BE:
      pkt_priority = BE_Q_STA;
      break;
    case WME_AC_BK:
      pkt_priority = BK_Q_STA;
      break;
    default:
      /* Should not come here */
      pkt_priority = BE_Q_STA;
  }
  qId = pkt_priority;
  RSI_DEBUG (RSI_ZONE_DATA_SEND, "rsi_xmit: qId of packet %d and tid %d\n", qId,Adapter->tid);

  rsi_lock_bh(&Adapter->lockqueue);
  Adapter->total_pkts_qd++;
  rsi_unlock_bh(&Adapter->lockqueue);

  /*Acquiring the lock on the skb queues */
  rsi_queue_tail (&Adapter->list[qId], skb);
  //rsi_queue_tail (&Adapter->list[0], skb);

  rsi_Set_Event(&Adapter->Event);

  RSI_DEBUG (RSI_ZONE_DATA_SEND, "rsi_xmit: Signalled\n");
  return NETDEV_TX_OK;
#else
  qId = DATA_QUEUE;

  if (Adapter->total_pkts_qd > RSI_MAX_PKTS_QUEUED)
  {

    {

      rsi_Set_Event(&Adapter->Event);
    }

    goto fail;
#if 0    
    if (!rsi_netif_queue_stopped (Adapter->net_device))
    {
      rsi_netif_stop_queue (Adapter->net_device);
    }
#endif    
  }

  rsi_lock_bh(&Adapter->lockqueue);
  Adapter->total_pkts_qd++;
  rsi_unlock_bh(&Adapter->lockqueue);

  /*Acquiring the lock on the skb queues */
  rsi_queue_tail (&Adapter->list[qId - 1], skb);
  rsi_Set_Event(&Adapter->Event);
  RSI_DEBUG (RSI_ZONE_DATA_SEND, "rsi_xmit: Signalled\n");
  return NETDEV_TX_OK;
#endif
fail:
  RSI_DEBUG (RSI_ZONE_DATA_SEND, "-Dropped\n");
  Adapter->stats.tx_dropped++;
  rsi_kfree_skb (skb);
  return 0;
}


/*==============================================*/
/**
 * @fn          VOID rsi_transmit_thread (PVOID pContext)
 * @brief       Tranmit thread to write data onto card
 * @param[in]   PVOID pContext
 * @param[out]  none
 * @return      none
 * @section description
 * This thread dequeues the skb from the list and adds the
 * descriptor. Finally, it writes onto the card.
 */
INT32 rsi_transmit_thread (PVOID pContext)
{
  PRSI_ADAPTER Adapter = (PRSI_ADAPTER) pContext;
  UINT32 Len = 0, i;
  UINT32 q_num, que_end;
  UINT32 que_start = 0;
  INT32 status;
  UINT8 cmd_qnum = SND_DATA_Q;
  UINT8 desc[RSI_DESC_LEN];
  UINT8           int_status = 0;
  UINT32 num_pkts = 0;

#ifdef RSI_DEBUG_PRINT
  RSI_DEBUG(RSI_ZONE_SPI_DBG,"\nrsi_transmit_thread:\n");
#endif
  RSI_DEBUG (RSI_ZONE_DATA_SEND,
             "rsi_transmit_thread: XMIT thread started\n");

  set_user_nice(current,-5);
  
  #if LINUX_VERSION_CODE <= KERNEL_VERSION(3, 6, 11)
  daemonize("XMIT-Thread");
  #endif

#ifdef ENABLE_WMM_FEATURE 
  do
  {
    UINT8 InterruptStatus = 0;
    UINT8 tid = 0;
    struct sk_buff *rcvskb;
    struct sk_buff *rcvskb_free;


    if (Adapter->BufferFull)
    {
      status = rsi_Wait_Event (&Adapter->Event, 10);
    }
    else
    {
      status = rsi_Wait_Event (&Adapter->Event, EVENT_WAIT_FOREVER);
    }

    rsi_Reset_Event (&Adapter->Event); 
    while(1)
    {
      q_num = core_determine_hal_queue(Adapter);
      if (Adapter->FSM_STATE != FSM_OPEN)
      {
        RSI_DEBUG(RSI_ZONE_DATA_SEND,(TEXT("transmit_thread: FSM is not in OPEN State\n")));
        break;
      }

      if (q_num == INVALID_QUEUE) 
      {
        RSI_DEBUG(RSI_ZONE_DATA_SEND,TEXT("\nqos_pro: No More Pkt Due to invalid queueno\n"));
        break;
      }
      rsi_lock_bh(&Adapter->lockqueue);
      Adapter->total_pkts_qd--;
      rsi_unlock_bh(&Adapter->lockqueue);

      rcvskb = rsi_dequeue (&Adapter->list[q_num]);

      RSI_DEBUG (RSI_ZONE_DATA_SEND, "Deque frm %d\n", q_num);
      if (rcvskb == NULL)
      {
        RSI_DEBUG (RSI_ZONE_ERROR,
            "rsi_transmit_thread: ERROR!!!! skb NULL %d\n",
            q_num);
        RSI_DEBUG(RSI_ZONE_DATA_SEND,(TEXT("No packet queued and trying to deque packet\n")));
        break;
      }
      
      tid = WME_AC_TO_TID(q_num);
      rsi_memset (desc, 0, 16);
#ifdef RSI_LITTLE_ENDIAN
      *(UINT16 *)&desc[0] = (((rcvskb->len) | (SND_DATA_Q << 12)) & 0x7fff);
#else
      desc[0] = (UINT8)((UINT16)((rcvskb->len ) & 0x00ff));
      desc[1] = (UINT8)((UINT16)((((rcvskb->len )| (SND_DATA_Q << 4)) >> 8) & 0x00ff));
#endif
      /*Keep Tid at 14th byte upper nibble*/
      desc[14] |= (((tid & 0xf) << 4) | (q_num & 0xf));
      Len = rcvskb->len;

      RSI_DEBUG (RSI_ZONE_DATA_SEND, "Queue %d and Tid of the queue %d\n", q_num,tid);
      //need to send the data from application
      Adapter->txPkt_count++;
      do
      {
        //need to send the data from application
        rsi_down_interruptible(&Adapter->int_check_sem);
        status = rsi_execute_cmd(desc, rcvskb->data, Len);

        rsi_up_sem(&Adapter->int_check_sem);
        if (status == -2)
        {
          RSI_DEBUG (RSI_ZONE_ERROR, "\nstatus : %d\n",status);
          RSI_DEBUG (RSI_ZONE_ERROR,
              "trying data %d bytes, Pkt_Count:%d\n",
              Len, Adapter->txPkt_count);

        }
#ifdef SPI_INTERFACE
        if (status == -1)
        {
          rsi_queue_head(&Adapter->list[q_num], rcvskb);
          rsi_lock_bh(&Adapter->lockqueue);
          Adapter->total_pkts_qd++;
          rsi_unlock_bh(&Adapter->lockqueue);
          break;
        }
#endif
        if (status == 0)
        {
          break;
        }
      }while(1);

      if(status == -1)
        break;
      if (status != RSI_STATUS_SUCCESS)
      {
#ifdef RSI_DEBUG_PRINT
        RSI_DEBUG (RSI_ZONE_ERROR,
            //"rsi_transmit_thread: Dropped Pkt of %d bytes\n",Len);
                  "desc Pkt Count: %d\n",
                  Adapter->txPkt_count);
#endif
        rsi_kfree_skb (rcvskb);
        Adapter->stats.tx_dropped++;
        break;
      }


      RSI_DEBUG (RSI_ZONE_DATA_SEND,
          "rsi_transmit_thread: Pkt of %d bytes written on card\n",
          Len);
      rsi_kfree_skb (rcvskb);
      Adapter->stats.tx_packets++;
      Adapter->stats.tx_bytes += Len;

      if(Adapter->transmit_thread_exit)
      {
        rsi_lock_bh(&Adapter->lockqueue);
        while(Adapter->total_pkts_qd > 0)
        {
          rcvskb_free= rsi_dequeue (&Adapter->list[q_num]);
          Adapter->total_pkts_qd--;
          rsi_kfree_skb (rcvskb_free);
        }
        rsi_unlock_bh(&Adapter->lockqueue);
        break;
      }
    }
  } while (Adapter->transmit_thread_exit == 0);
#else

  do
  {
    UINT8 InterruptStatus = 0;
    struct sk_buff *rcvskb;
    struct sk_buff *rcvskb_free;
    if (Adapter->BufferFull)
    {
      status = rsi_Wait_Event (&Adapter->Event, 10);
    }
    else
    {
      status = rsi_Wait_Event (&Adapter->Event, EVENT_WAIT_FOREVER);
    }
    rsi_Reset_Event (&Adapter->Event); 

    RSI_DEBUG (RSI_ZONE_DATA_SEND, "rsi_transmit_thread:event released\n");
	que_end = 1;
      if (Adapter->transmit_thread_exit )
    {
      RSI_DEBUG (RSI_ZONE_DATA_SEND,
                 "rsi_transmit_thread: Halt flag set\n");
      break;
    }
  que_loop:
    for (q_num = que_start; q_num < que_end; ++q_num)
    {
      UINT32 pkts_given = 0;
      RSI_DEBUG (RSI_ZONE_DATA_SEND, "rsi_transmit_thread: Q_NUM:%d\n",
                 q_num);

      if (Adapter->FSM_STATE != FSM_OPEN)
      {
        RSI_DEBUG(RSI_ZONE_DATA_SEND,(TEXT("ganges_transmit_thread: FSM is not in OPEN State\n")));
        break;
      }

      do
      {

        ++pkts_given;

        rsi_lock_bh(&Adapter->lockqueue);

        if (Adapter->total_pkts_qd > 0)
        {
          Adapter->total_pkts_qd--;
        }
        else 
        {
          rsi_unlock_bh(&Adapter->lockqueue);
          break;
        }
        rsi_unlock_bh(&Adapter->lockqueue);
        rcvskb = rsi_dequeue (&Adapter->list[q_num]);

        RSI_DEBUG (RSI_ZONE_DATA_SEND, "Deque frm%d\n", q_num);
        if (rcvskb == NULL)
        {
          RSI_DEBUG (RSI_ZONE_ERROR,
                     "rsi_transmit_thread: ERROR!!!! skb NULL %d\n",
                     q_num);
          break;
        }

        rsi_memset (desc, 0, 16);
        rsi_uint16_to_2bytes(desc, (((rcvskb->len) & 0xFFF) | (SND_DATA_Q << 12)));
        Len = rcvskb->len;

        //need to send the data from application
        Adapter->txPkt_count++;
        do
        {
          //need to send the data from application
          rsi_down_interruptible(&Adapter->int_check_sem);
          status = rsi_execute_cmd(desc, rcvskb->data, Len);
          rsi_up_sem(&Adapter->int_check_sem);

          if (status == -2)
          {
            RSI_DEBUG (RSI_ZONE_ERROR, "\nstatus : %d\n",status);
            RSI_DEBUG (RSI_ZONE_ERROR,
                "trying data %d bytes, Pkt_Count:%d\n",
                Len, Adapter->txPkt_count);

          }
#ifdef SPI_INTERFACE
          if (status == -1)
          {
            rsi_queue_head(&Adapter->list[q_num], rcvskb);
            rsi_lock_bh(&Adapter->lockqueue);
            Adapter->total_pkts_qd++;
            rsi_unlock_bh(&Adapter->lockqueue);
            break;
          }
#endif
          if (status == 0)
          {
            break;
          }
        } while (1); 
        if(status == -1)
          break;
        if (status != RSI_STATUS_SUCCESS)
        {
#ifdef RSI_DEBUG_PRINT
          RSI_DEBUG (RSI_ZONE_ERROR,
              //"rsi_transmit_thread: Dropped Pkt of %d bytes\n",Len);
                    "desc Pkt Count: %d\n",
                    Adapter->txPkt_count);
#endif
          rsi_kfree_skb (rcvskb);
          Adapter->stats.tx_dropped++;
          break;
        }


        RSI_DEBUG (RSI_ZONE_DATA_SEND,
            "rsi_transmit_thread: Pkt of %d bytes written on card\n",
            Len);
        rsi_kfree_skb (rcvskb);
        Adapter->stats.tx_packets++;
        Adapter->stats.tx_bytes += Len;

        if(Adapter->transmit_thread_exit)
        {
          rsi_lock_bh(&Adapter->lockqueue);
          while(Adapter->total_pkts_qd > 0)
          {
            rcvskb_free= rsi_dequeue (&Adapter->list[q_num]);
            Adapter->total_pkts_qd--;
            rsi_kfree_skb (rcvskb_free);
          }
          rsi_unlock_bh(&Adapter->lockqueue);
          break;
        }
#if 0        
        if (Adapter->total_pkts_qd < RSI_MAX_PKTS_QUEUED)
        {
          if (rsi_netif_queue_stopped (Adapter->net_device) )
          {
            rsi_netif_start_queue(Adapter->net_device);
          }
        }
#endif        
      } while (Adapter->total_pkts_qd > 0);
    }

#if 0
    for (i = que_start; i < que_end; i++)
    {
      if (rsi_queue_len (&Adapter->list[i]) /* && (!Adapter->sleep_indcn) */ )
      {
        RSI_DEBUG (RSI_ZONE_DATA_SEND,
            "BFl: %d\nQue0:%d\nQue1:%d\nQue2:%d\nQue3:%d\n",
            Adapter->BufferFull,
            rsi_queue_len (&Adapter->list[0]),
            rsi_queue_len (&Adapter->list[1]),
            rsi_queue_len (&Adapter->list[2]),
            rsi_queue_len (&Adapter->list[3]));
        q_num = i;
        goto que_loop;
      }
    }
#endif
  } while (Adapter->transmit_thread_exit == 0);

#endif

  complete_and_exit(&Adapter->txThreadComplete, 0);

}

/*==============================================*/
/**
 * @fn          INT32 rsi_indicate_packet(PRSI_ADAPTER Adapter,
 *                                     UINT8 * DataRcvPacket,
 *                                     UINT32 pktLen)
 * @brief       Indicated the packet to upper layer
 * @param[in]   PRSI_ADAPTER Adapter,
 *              Pointer to the private data of the device
 * @param[in]   UINT8 *DataRcvPacket, Pointer to a packet
 * @param[in]   UINT32 pktLen, Length of the packet
 * @param[out]  none
 * @return      On success 0, else a negative number
 * @section description
 * This function copies the packet into a skb structure and
 * indicates to the upper layer
 */
INT32
rsi_indicate_packet
(PRSI_ADAPTER Adapter, UINT8 * DataRcvPacket, UINT32 pktLen)
{
  struct sk_buff *rxskb;
  INT32 i = 0;

#ifdef RSI_DEBUG_PRINT
  RSI_DEBUG(RSI_ZONE_SPI_DBG,"\nrsi_indicate_packet:\n");
#endif
  if (Adapter->FSM_STATE != FSM_OPEN)
  {
    RSI_DEBUG (RSI_ZONE_ERROR, "rsi_indicate_packet: Not in open state\n");
    goto fail;
  }

  if (pktLen > 1536)
  {
    RSI_DEBUG (RSI_ZONE_ERROR, "rsi_indicate_packet: Big packet revd\n");
    goto fail;
  }

  if (pktLen < RSI_HEADER_SIZE)
  {
    RSI_DEBUG (RSI_ZONE_ERROR, "rsi_indicate_packet: Runt packet recvd\n");
    goto fail;
  }
  /*Allocate skb and copy the data into it */
  rxskb = rsi_alloc_skb (pktLen);
  if (!rxskb)
  {
    RSI_DEBUG (RSI_ZONE_ERROR,
               "rsi_indicate_packet: Low on memory, packet dropped\n");
    goto fail;
  }

  rsi_memcpy (rsi_skb_put (rxskb, pktLen), DataRcvPacket, pktLen);
  /*Filling the various other fields of skb */
  rxskb->dev = Adapter->net_device;
  rxskb->protocol = rsi_eth_type_trans (rxskb, Adapter->net_device);

  rxskb->ip_summed = CHECKSUM_NONE;

  rsi_netif_rx (rxskb);

  RSI_DEBUG (RSI_ZONE_DATA_RCV,
             "rsi_indicate_packet: Pkt of %d bytes indicated\n", pktLen);

  Adapter->stats.rx_packets++;
  Adapter->stats.rx_bytes += pktLen;
  return 0;

fail:

  Adapter->stats.rx_dropped++;
  return -1;
}

/* $EOF */
/* Log */