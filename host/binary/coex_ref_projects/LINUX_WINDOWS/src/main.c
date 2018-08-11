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
#include "rsi_global.h"

#ifdef WLAN_ENABLE
#include "rsi_api.h"
#include "rsi_app.h"
#endif
#ifdef ZB_ENABLE
#include "rsi_zigb_types.h"
#include "rsi_zigb_global.h"
#include "rsi_zigb_app.h"
#include "rsi_zigb_api.h"
#endif
#ifdef BLE_ENABLE
#include "rsi_bt_app.h"
#include "rsi_bt_global.h"
#include "rsi_ble_global.h"
#endif
#ifdef BT_ENABLE
#include "rsi_bt_app.h"
#include "rsi_bt_global.h"
#endif
#include "rsi_scheduler.h"
#include "platform_specific.h"
#include "rsi_serial.h"

/*
 * Defines
 */
/*
 * Global Variables
 */
rsi_linux_app_cb_t            rsi_linux_app_cb;

#ifdef WLAN_ENABLE
extern rsi_app_cb_t           rsi_app_cb;
extern int wifi_main(int );
#endif
#ifdef ZB_ENABLE
extern rsi_zigb_app_cb_t      rsi_zigb_app_cb;
/* function declarations */
extern int zigb_main(UINT8 );
#endif
#if defined(BLE_ENABLE) | defined(BT_ENABLE) 
extern RSI_BT_APP_CB rsi_bt_AppControlBlock;
#endif

extern INT16 rsi_frame_read(UINT8 *packet_buffer);
extern INT16 rsi_frame_write(rsi_uFrameDsc *uFrameDscFrame,UINT8 *payloadparam,UINT16 size_param);

//Macro to check for event pending
#define SCHEDULER_CHECK		{	if(rsi_common_app_cb.scheduler_info.event_map & rsi_common_app_cb.scheduler_info.mask_map) \
															{rsi_coex_scheduler(&rsi_common_app_cb.scheduler_info); } }

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
 * module. 
 * */
void rsi_recv_pkt_serial()
{
  UINT8 dummy_byte_len=0;
  while (rsi_serial_fifo_status()) {
    if (rsi_linux_app_cb.rx_is_in_progress ==  IDLE_STATE) {
     rsi_linux_app_cb.rcvPktPtr = (PKT_STRUCT_T *) rsi_malloc( RSI_MAX_PAYLOAD_SIZE + sizeof(PKT_STRUCT_T));
      if(rsi_linux_app_cb.rcvPktPtr == NULL)
      {
#ifdef RSI_DEBUG_PRINT
        RSI_DPRINT(RSI_PL13,"Allocation failed to recv packet\n");
#endif
        return;
      }

      rsi_linux_app_cb.rcvPktPtr->next = (PKT_STRUCT_T *)(((UINT8 *)rsi_linux_app_cb.rcvPktPtr));
      rsi_linux_app_cb.rcvPktPtr->data = (UINT8 *)(((UINT8 *)rsi_linux_app_cb.rcvPktPtr) + (sizeof(UINT8 *) * 2) );

      rsi_linux_app_cb.rx_is_in_progress = LEN_DESC_RECV_STATE;
      rsi_linux_app_cb.byte_count = 0;
    }
    /*
     * Reading first four bytes to calculate packet size and offset
     */
    if (rsi_linux_app_cb.rx_is_in_progress == LEN_DESC_RECV_STATE) {
      rsi_linux_app_cb.pre_desc_buf[rsi_linux_app_cb.byte_count++] = rsi_uart_byte_read();
      if (rsi_linux_app_cb.byte_count == RSI_PRE_DESC_LEN) {
        rsi_linux_app_cb.rx_is_in_progress = WAIT_FOR_DESC_STATE;
        dummy_byte_len = *(UINT16 *)&rsi_linux_app_cb.pre_desc_buf[2] - RSI_PRE_DESC_LEN;
     }
      continue;
    }

    /*
     * Reading Dummy Bytes if any
     * */
    if (rsi_linux_app_cb.rx_is_in_progress == WAIT_FOR_DESC_STATE) {
      if (dummy_byte_len) {
        rsi_uart_byte_read();
        dummy_byte_len--;
        continue;
      }
      /*
       * handle zero lenght packets
       */
      if (!dummy_byte_len) {
        rsi_linux_app_cb.rx_is_in_progress = PAYLOAD_RECV_STATE;
        rsi_linux_app_cb.payload_size = *(UINT16 *)&rsi_linux_app_cb.pre_desc_buf[0] - *(UINT16 *)&rsi_linux_app_cb.pre_desc_buf[2];
        rsi_linux_app_cb.byte_count = 0;
        /*
         * handle zero lenght packets
         */
        if (!rsi_linux_app_cb.payload_size) {
          /* If payload length received  is zero then don't collect the packet
           * and free the buffer and revert the state machine to IDLE */
#ifdef RSI_DEBUG_PRINT
          RSI_DPRINT(RSI_PL13,"Zero Payload Packet Received\n");
#endif
          rsi_linux_app_cb.rx_is_in_progress = IDLE_STATE;
          rsi_free(rsi_linux_app_cb.rcvPktPtr);
          rsi_linux_app_cb.rcvPktPtr = NULL;
          return;
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
        rsi_enter_critical_sec();
        rsi_enqueue_to_rcv_q(&rsi_linux_app_cb.rcv_queue, rsi_linux_app_cb.rcvPktPtr);
        /*
         * Set the RECEIVE EVENT here. In case of microcontrolle
         * set this event in ISR
         */
        rsi_set_event(RSI_RX_EVENT);
        rsi_exit_critical_sec();
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
  UINT8 only_once = 0;
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
    rsi_recv_pkt_serial();
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
  int device_status;
 INT32 status = 0;
 /* MCU Serial Intializations has to happen */
 device_status = rsi_device_init();
  if (device_status < 0) {
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL13,"Unable to Open device\n");
#endif      
     return -1;
  }
 /* Platform Based Intializations */
  rsi_platform_based_init();

  status = rsi_main();

  if (status < 0)
  {
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL13,"Returned from rsi_main !\n");
#endif      
  }

	while(1)
	{
		SCHEDULER_CHECK //Check for any event pending
		/*
		 * Application specific code should be added here
		 */
#ifdef 	WINDOWS
		Sleep(1);
#endif
	}


  /**
   * Exit application
   */
  exit(0);
}

/*===========================================================================
 *
 * @fn          UINT8 rsi_device_init(void)
 * @brief       Device Init
 * @param[in]   None
 * @return      Status:
 *              0=SUCCESS
 *              -1=ERROR
 * @section description
 * This API is used to do device inits. 
 *
 * ===========================================================================*/
UINT8 rsi_device_init(void)
{
  /* MCU Serial Intializations has to happen */
  if (rsi_serial_init()) {
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL13,"Unable to Open device\n");
#endif      
     return -1;
  }
  return 0;
}


/*===========================================================================
 *
 * @fn          UINT8 rsi_platform_based_init(void)
 * @brief       Platform Based Init
 * @param[in]   None
 * @return      None
 * @section description
 * This API is used to do platform based inits 
 *
 * ===========================================================================*/
void rsi_platform_based_init(void)
{
  int err;
#ifdef WINDOWS
  char card_rdy[]="Loading Done\r\n";
  char recv_card_ready[20];
#endif
#ifdef WINDOWS
  DWORD thread1;
#else
  pthread_t     thread1;
#endif

#ifdef WINDOWS
    RSI_DPRINT(RSI_PL3,"\n Waiting for Card Ready...\n");
  while(BYPASS_CARD_READY)
  {
    rsi_uart_recv(recv_card_ready,sizeof(card_rdy)-1);
    if(!memcmp(recv_card_ready,card_rdy,sizeof(card_rdy)-1))
    {
      break;
    }
  }
  InitializeCriticalSection(&crit_sec);
#else
	if(pthread_mutex_init(&rsi_linux_app_cb.mutex1, NULL) != 0) { 
    RSI_DPRINT(RSI_PL13,"\n Mutex init failed...");
  }
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
}


