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
#include "rsi_nl_app.h"
#include "rsi_app.h"
#include "rsi_serial.h"
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include "rsi_app_util.h"



/*
 * Defines
 */

/*
 * Global Variables
 */
rsi_linux_app_cb_t   rsi_linux_app_cb;
rsi_app_cb_t         rsi_app_cb;

/* Total Size of data */
uint8  sendBuf[RSI_MAX_PAYLOAD_SIZE+100]= {1};

/* function declarations */
int main(int argc, char *argv[]);
extern int wifi_main(int app_mode);
void open_serial(int port);

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
  int16 retval = 0;
  pthread_t     thread1;
  pthread_t     thread2;
  int           rc1, rc2;
  char *message1 = "Recv Thread";
  char *message2 = "Recv Thread for serial dev";
  rsi_linux_app_cb.serial_type = UART;

  retval = rsi_nl_socket_init();
  if (retval == -1) {
    /* Error occurred! */
    return 2;
  }
  rsi_fill_genl_nl_hdrs_for_cmd();
  if (argc > 1) {
    rsi_linux_app_cb.serial_type = USB_CDC;
  }
  rsi_serial_init(rsi_linux_app_cb.serial_type);
  

  if( (rc1 = pthread_create( &thread1, NULL, RecvThreadBody, (void*) message1)) )
  {
    RSI_DPRINT(RSI_PL13,"Thread creation failed: %d\n", rc1);
  }

  if( (rc2 = pthread_create( &thread2, NULL, RecvSerialThreadBody, (void*) message2)) )
  {
    RSI_DPRINT(RSI_PL13,"Thread creation failed: %d\n", rc1);
  }
  
  retval = rsi_send_driver_pkt_to_dev();

  if (retval < 0)
  {
    return -1;
  }

  /**
   * Exit application
   */
  exit(0);
}


/*==============================================*/
/**
 * @fn          void rsi_send_driver_pkt_to_dev(void)
 * @brief       Send data from driver to device
 * @param[out]  int
 * @return      errCode
 *              0  = SUCCESS
 *              else failure
 * @section description
 * This is to send rcvd driver data over nl socket to 
 * UART/USB-serial device.
 */

int16 rsi_send_driver_pkt_to_dev(void)
{
    /* Variables */
    rsi_linux_app_cb_t *linux_app_cbPtr = &rsi_linux_app_cb;
    pkt_struct_t *rspPtr = NULL;

    /* Length of the data to copy */
    int16 length = 0;

    /* Pointer to the Packet file descriptor */
    uint8 *descPtr    = NULL;

#ifdef RSI_DEBUG_PRINT
    int i;
#endif

    while (1)
    {
      if (rsi_app_cb.pkt_pending == RSI_TRUE)
      {
        /* Do actual deque from the RX queue */
        pthread_mutex_lock(&linux_app_cbPtr->mutex1);
        rspPtr = rsi_dequeue_from_rcv_q();
        if (rspPtr == NULL)
        {
          rsi_app_cb.pkt_pending = RSI_FALSE;
          pthread_mutex_unlock(&linux_app_cbPtr->mutex1);
          continue;
        }
        pthread_mutex_unlock(&linux_app_cbPtr->mutex1);

        /* Assign pointers to appropriate addresses */
        descPtr    = rspPtr->data + RSI_NL_HEAD_SIZE;

        /* Calculate length of the packet from the first two bytes of the frame descriptor */
        length = rsi_bytes2R_to_uint16(descPtr);
        length &= 0x0FFF;
        
        length += RSI_FRAME_DESC_LEN;

        /* Debug: Print the length & contents of the packet */
#ifdef RSI_DEBUG_PRINT
        RSI_DPRINT(RSI_PL0,"Length of the packet: %d\n", length);
        for (i=0; i<length; i++) {
          RSI_DPRINT (RSI_PL0, "0x%x ", descPtr[i]);
          if (i == 15) {
            RSI_DPRINT(RSI_PL0, "\n");
          }
        }
        RSI_DPRINT(RSI_PL0, "\n");
#endif


        if ((rsi_serial_frame_write(descPtr, length) < 0))
        {
          printf("Error in writing to serial device \n");
          rsi_free(rspPtr);
          break;
        }
        rsi_free(rspPtr);
      }
    }
    printf("return from here\n");
    /* Return failure */
    return -1;
}
