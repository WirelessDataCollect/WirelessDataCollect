/**
 * @file        main.c
 * Copyright(C) 2013 Redpine Signals Inc.
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * T:vshis program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief MAIN, Top level file, it all starts here
 *
 * @section Description
 * This file contains the entry point for the application. It also has the
 * initialization of parameters of the global structure and the operations to
 * control & configure the module, like scanning networks, joining to an Access Point etc.
 */

/**
 * Include files
 */
#include "platform_specific.h"
#include "rsi_serial.h"

#ifdef WLAN_ENABLE
#include "rsi_global.h"
#include "rsi_api.h"
#include "rsi_app.h"
#elif ZB_ENABLE
#include "rsi_zigb_types.h"
#include "rsi_zigb_global.h"
#include "rsi_zigb_app.h"
#include "rsi_zigb_api.h"
#endif
#include "platform_specific.h"
#include "rsi_serial.h"

/*
 * Defines
 */
/*
 * Global Variables
 */
rsi_linux_app_cb_t   rsi_linux_app_cb;

#ifdef WLAN_ENABLE
extern rsi_app_cb_t            rsi_app_cb;
extern int wifi_main(int );
#elif ZB_ENABLE
extern rsi_zigb_app_cb_t rsi_zigb_app_cb;


/* function declarations */
extern int zigb_main(uint8_t );
#endif

/* function declarations */
extern int16_t rsi_frame_read(uint8_t *packet_buffer);
#ifdef WLAN_ENABLE
extern int16_t rsi_frame_write(rsi_uFrameDsc *uFrameDscFrame,uint8_t *payloadparam,uint16_t size_param);
#elif ZB_ENABLE
extern int16_t rsi_frame_write(rsi_zigb_uFrameDsc *uFrameDscFrame,
              uint8_t *payloadparam,uint16_t size_param);
#endif

uint8_t card_ready_frame[16] = { 0x0, 0x40, 0x89, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};


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
#ifdef ZB_ENABLE
      pkt_struct_t *rcvPktPtr = (pkt_struct_t *) rsi_malloc( RSI_ZIGB_MAX_PAYLOAD_SIZE + sizeof(pkt_struct_t));
#elif WLAN_ENABLE
      pkt_struct_t *rcvPktPtr = (pkt_struct_t *) rsi_malloc(RSI_MAX_PAYLOAD_SIZE + sizeof(pkt_struct_t));
#endif

      if(rcvPktPtr == NULL)
      {
#ifdef RSI_DEBUG_PRINT
        RSI_DPRINT(RSI_PL13,"Allocation failed to recv packet\n");
#endif
        return ;
      }

      rcvPktPtr->next = (pkt_struct_t *)(((uint8_t *)rcvPktPtr));
      rcvPktPtr->data = (uint8_t *)(((uint8_t *)rcvPktPtr) + (sizeof(uint8_t *) * 2) );
#ifdef ZB_ENABLE
      rsi_memcpy(rcvPktPtr->data, card_ready_frame, RSI_ZIGB_FRAME_DESC_LEN);
#elif WLAN_ENABLE
      rsi_memcpy(rcvPktPtr->data, card_ready_frame, RSI_FRAME_DESC_LEN);
#endif
#ifdef WINDOWS
		EnterCriticalSection(&crit_sec);
#else
      pthread_mutex_lock(&rsi_linux_app_cb.mutex1);
#endif
      rsi_enqueue_to_rcv_q(rcvPktPtr);
#ifdef ZB_ENABLE
      /* Set Packet Pending Event to Application */
      rsi_zigb_app_cb.pkt_pending = RSI_TRUE;
#elif WLAN_ENABLE
	rsi_app_cb.pkt_pending = RSI_TRUE;
#endif
#ifdef WINDOWS
		LeaveCriticalSection(&crit_sec);
#else
      pthread_mutex_unlock(&rsi_linux_app_cb.mutex1);
#endif
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL13,"Sending Card Ready\n");
#endif      
}

/* This function is for serial interfaces like UART USB_CDC */
/*==============================================*/
/**
 * @fn          void rsi_recv_pkt_serial(void)
 * @brief       Recieve the packet from MCU
 * @param[in]   none
 * @param[out]  none
 * @return      none
 * @section description
 * This function will read the number of bytes return by the
 * module. Call this function in MCU interrupt handler
 */

void recv_pkt_serial()
{
  while (rsi_serial_fifo_status()) {
    if (rsi_linux_app_cb.rx_is_in_progress ==  IDLE_STATE) {
#ifdef ZB_ENABLE
      rsi_linux_app_cb.rcvPktPtr = (pkt_struct_t *) rsi_malloc( RSI_ZIGB_MAX_PAYLOAD_SIZE + sizeof(pkt_struct_t));
#elif WLAN_ENABLE
     rsi_linux_app_cb.rcvPktPtr = (pkt_struct_t *) rsi_malloc( RSI_MAX_PAYLOAD_SIZE + sizeof(pkt_struct_t));
#endif
      if(rsi_linux_app_cb.rcvPktPtr == NULL)
      {
#ifdef RSI_DEBUG_PRINT
        RSI_DPRINT(RSI_PL13,"Allocation failed to recv packet\n");
#endif
        return;
      }

      rsi_linux_app_cb.rcvPktPtr->next = (pkt_struct_t *)(((uint8_t *)rsi_linux_app_cb.rcvPktPtr));
      rsi_linux_app_cb.rcvPktPtr->data = (uint8_t *)(((uint8_t *)rsi_linux_app_cb.rcvPktPtr) + (sizeof(uint8_t *) * 2) );

      rsi_linux_app_cb.rx_is_in_progress = LEN_DESC_RECV_STATE;
      rsi_linux_app_cb.byte_count = 0;
    }

    if (rsi_linux_app_cb.rx_is_in_progress == LEN_DESC_RECV_STATE) {
      rsi_linux_app_cb.pre_desc_buf[rsi_linux_app_cb.byte_count++] = rsi_uart_byte_read();
      if (rsi_linux_app_cb.byte_count == RSI_PRE_DESC_LEN) {
        rsi_linux_app_cb.rx_is_in_progress = WAIT_FOR_DESC_STATE;
        rsi_linux_app_cb.payload_size = *(uint16_t *)&rsi_linux_app_cb.pre_desc_buf[2] - RSI_PRE_DESC_LEN;
      }
      continue;
    }

    if (rsi_linux_app_cb.rx_is_in_progress == WAIT_FOR_DESC_STATE) {
      if (rsi_linux_app_cb.payload_size) {
        rsi_uart_byte_read();
        rsi_linux_app_cb.payload_size--;
        continue;
      }
      if (!rsi_linux_app_cb.payload_size) {
        rsi_linux_app_cb.rx_is_in_progress = PAYLOAD_RECV_STATE;
        rsi_linux_app_cb.payload_size = *(uint16_t *)&rsi_linux_app_cb.pre_desc_buf[0] - *(uint16_t *)&rsi_linux_app_cb.pre_desc_buf[2];
        rsi_linux_app_cb.byte_count = 0;
        if (!rsi_linux_app_cb.payload_size) {
          /* If payload length received  is zero then don't collect the packet
           * and free the buffer and revert the state machine to IDLE */
#ifdef RSI_DEBUG_PRINT
        RSI_DPRINT(RSI_PL13,"Zero Payload Packet Received\n");
#endif
          rsi_linux_app_cb.rx_is_in_progress = IDLE_STATE;
          rsi_free(rsi_linux_app_cb.rcvPktPtr);
          rsi_linux_app_cb.rcvPktPtr = NULL;
          continue;
        }
      }
    }

    if (rsi_linux_app_cb.rx_is_in_progress == PAYLOAD_RECV_STATE) {
      if (rsi_linux_app_cb.payload_size) {
        rsi_linux_app_cb.rcvPktPtr->data[rsi_linux_app_cb.byte_count++] = rsi_uart_byte_read();
        rsi_linux_app_cb.payload_size--;
      }
      if (!rsi_linux_app_cb.payload_size) {
        rsi_linux_app_cb.rx_is_in_progress = IDLE_STATE;
        /* EnQ it! */
#ifdef WINDOWS
				EnterCriticalSection(&crit_sec);
#else
        pthread_mutex_lock(&rsi_linux_app_cb.mutex1);
#endif
        rsi_enqueue_to_rcv_q(rsi_linux_app_cb.rcvPktPtr);
#ifdef ZB_ENABLE
        /* Set Packet Pending Event to Application */
        rsi_zigb_app_cb.pkt_pending = RSI_TRUE;
#elif WLAN_ENABLE
	rsi_app_cb.pkt_pending = RSI_TRUE;
#endif
#ifdef WINDOWS
				LeaveCriticalSection(&crit_sec);
#else
        pthread_mutex_unlock(&rsi_linux_app_cb.mutex1);
#endif
        rsi_linux_app_cb.rcvPktPtr = NULL;
      }
    }
  }
}

/*==============================================*/
/**
 * @fn          void *recvThread(void *args)
 * @brief       
 * @param[out] 
 * @return      none
 * @section description
 * Thread to read the application 
 */

#ifdef WINDOWS
DWORD WINAPI recvThread(void* args)
#else
void *recvThread(void* args)
#endif
{
  uint8_t only_once = 0;
  while (1) {
    if (!only_once) {
      /* On OS based platform, card ready packet is generated at
       * power up and that will not processed.
       * But in case of MCU, interrupt is not configured So, card 
       * ready packet will be received once interrupt is configured
       */
      rsi_skip_card_ready();
      only_once = 1;
      continue;
    } 
   recv_pkt_serial();
  }
}

/*==============================================*/
/**
 * @fn          int main(void)
 * @brief       Start of application
 * @param[out]  int
 * @return      errCode
 *              0  = SUCCESS
 *              else failure
 * @section description
 * This is start of application.
 */

int main(int argc, char *argv[])
{
  /* generic return value and counter*/
  int err;
#ifdef WINDOWS
	char card_rdy[]="Loading Done\r\n";
	char recv_card_ready[20];
	DWORD thread1;
#else
  pthread_t     thread1;
#endif
#ifdef ZB_ENABLE
  uint8_t skip_card_ready = 0;
#endif

 int32_t status = 0;

  /* MCU Serial Intializations has to happen */
  if (rsi_serial_init()) {
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL13,"Unable to Open device\n");
#endif      
     return -1;
  }
#ifdef WINDOWS
	while(1)
	{
		rsi_uart_recv(recv_card_ready,sizeof(card_rdy)-1);
		if(!memcmp(recv_card_ready,card_rdy,sizeof(card_rdy)-1))
		{
			break;
		}
	}
	InitializeCriticalSection(&crit_sec);
#endif
  //! Thread Creation
#ifdef WINDOWS
	err = CreateThread(NULL, // default security attributes
	  					0, // use default stack size
						(LPTHREAD_START_ROUTINE)recvThread, // thread function
						NULL, // argument to thread function
						0, // use default creation flags
						&thread1); // returns the thread identifier
	if(err == NULL) {
#else
  if ((err = pthread_create(&thread1, NULL, &recvThread, NULL))) {
#endif
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL13,"Couldn't create thread: [%s]\n", strerror(err));
#endif      
  } else {
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL13,"Thread created successfully!\n");
#endif      
  }
#ifdef ZB_ENABLE
  if (argc != 1) {
    skip_card_ready = 1;
  }
#endif

  //! calling zigb_main
#ifdef ZB_ENABLE
  status = zigb_main(skip_card_ready);
#elif WLAN_ENABLE
  status = wifi_main(argc);
#endif
  if (status != 0) {
#ifdef RSI_DEBUG_PRINT
     RSI_DPRINT(RSI_PL1,"\n Exit from main \n");
#endif     
     return -1;
  }

  /**
   * Exit application
   */
  exit(0);
}


/*=================================================*/
/**
 * @fn          void rsi_enqueue_to_rcv_q(pkt_struct_t *Pkt)
 * @brief       To enqueue the packet to receive queue
 * @param[in]   pkt_struct_t *Pkt
 * @param[out]  none
 * @return      none
 * @section description
 * This API is used to enqueue the received packet from kernel
 * to receive queue.
 */
void rsi_enqueue_to_rcv_q(pkt_struct_t *Pkt)
{
  pkt_queue_t *rcv_q = &rsi_linux_app_cb.rcv_queue;

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
 * @fn          pkt_struct_t *rsi_dequeue_from_rcv_q(void)
 * @brief       To dequeue the packet to receive queue
 * @param[in]   none
 * @param[out]  none
 * @return      pkt_struct_t *Pkt, dequeued packet pointer
 * @section description
 * This API is used to dequeue the packets from receive queue
 * when packets are pending in queue.
 */
pkt_struct_t *rsi_dequeue_from_rcv_q(void)
{
  pkt_struct_t *Pkt = NULL;
  pkt_queue_t *rcv_q = &rsi_linux_app_cb.rcv_queue;

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
 * @fn          uint16_t rsi_check_queue_status(void)
 * @brief       To Check the packet count.
 * @param[in]   none
 * @param[out]  none
 * @return      pending packet count in queue
 * @section description
 * This API is used to get the pending packet count in queue
 */
uint16_t rsi_check_queue_status(void)
{
  return rsi_linux_app_cb.rcv_queue.pending_pkt_count;
}

/*=================================================*/
/**
 * @fn          uint8_t *rsi_alloc_and_init_cmdbuff(uint8_t *Desc,
 *                                       uint8_t *payload,
 *                                       uint16_t payload_size)
 * @brief       To allocate and initialise the command buffer.
 * @param[in]   pkt_struct_t *Pkt
 * @param[out]  none
 * @return      none
 * @section description
 * This API is used to allocate a buffer for the command to send and
 * initializing it with all the header bytes, Desc and payload filled.
 */
uint8_t *rsi_alloc_and_init_cmdbuff(uint8_t *Desc, uint8_t *payload, uint16_t payload_size)
{
  uint8_t *cmd_buff;
  uint16_t desc_len = 0;
#ifdef WLAN_ENABLE
   desc_len = RSI_FRAME_DESC_LEN;
#elif ZB_ENABLE
   desc_len = RSI_ZIGB_FRAME_DESC_LEN;
#endif

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_alloc_and_init_cmdbuff\n");
#endif
  cmd_buff = rsi_malloc(payload_size + desc_len);

  rsi_memcpy(cmd_buff, Desc, desc_len);

  if(payload_size)
    rsi_memcpy((cmd_buff + desc_len), payload, payload_size);

  return cmd_buff;
}

#ifdef ZB_ENABLE
/*===========================================================================
 *
 * @fn          void rsi_zigb_delay(uint32_t time)
 * @brief       Sleep
 * @param[in]   Time to sleep
 * @param[out]  none
 * @return      none
 * @section description
 * This API is used to sleep for a specified 
 * amount of duration
 *
 * ===========================================================================*/
  
void rsi_zigb_delay(uint32_t time)
{
  sleep(time);
}
#endif
