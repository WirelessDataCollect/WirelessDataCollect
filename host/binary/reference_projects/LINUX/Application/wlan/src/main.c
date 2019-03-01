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
#include "rsi_global.h"
#include "rsi_config.h"
#include "rsi_app_util.h"
#include "rsi_nl_app.h"
#include "platform_specific.h"
#include "rsi_app.h"


/*
 * Defines
 */
#define SET_WLAN0_IP system("ifconfig rsi_wlan0 "RSI_MODULE_IP_ADDRESS)
#if RSI_CONCURRENT_MODE
#define SET_WLAN1_IP system("ifconfig rsi_wlan1 "RSI_CONCURRENT_AP_IP_ADDRESS)
#endif

/*
 * Global Variables
 */
rsi_linux_app_cb_t   rsi_linux_app_cb;
extern rsi_app_cb_t  rsi_app_cb;
uint16               rsi_cmd_status;

/* Total Size of data */
uint8  sendBuf[RSI_MAX_PAYLOAD_SIZE+100]= {1};

/* function declarations */
int main(int argc, char *argv[]);
extern int wifi_main(int app_mode);

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
  int           rc1;
  char *message1 = "Recv Thread";
  rsi_linux_app_cb_t *linux_app_cbPtr = &rsi_linux_app_cb;

  /* Open a socket for issueing ioctls */
  if ((linux_app_cbPtr->ioctl_sd = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
  {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT (RSI_PL3,"socket creation error\n");
#endif
    return 2;
  }

  retval = rsi_nl_socket_init();
  if (retval == -1) {
    /* Error occurred! */
    return 2;
  }

  rsi_fill_genl_nl_hdrs_for_cmd();

#ifdef SPI_INTERFACE
  retval = rsi_update_info(MODULE_POWER_CYCLE);
#endif

  if( (rc1 = pthread_create( &thread1, NULL, RecvThreadBody, (void*) message1)) )
  {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL13,"Thread creation failed: %d\n", rc1);
#endif
  }

  //! send interrupt irq register frame to driver to register the interrupt irq
  retval = rsi_register_interrupt_irq();
  if (retval != 0)
  {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL13,"Interrupt irq fail \n");
#endif
    return -1;
  }
  
  //! calling wifi_main
  if( wifi_main(!(argc > 1)))
     return 1;

#if (RSI_TCP_IP_BYPASS & (RSI_HOST_BOOTUP_OPTION == RSI_LOAD_IMAGE_TYPE))
  retval = rsi_update_info(UPDATE_JOIN_DONE);
  SET_WLAN0_IP;
#if RSI_CONCURRENT_MODE
  retval = rsi_update_info(UPDATE_CONCURRENT_AP_JOIN_DONE);
  SET_WLAN1_IP;
#endif
#endif

  /**
   * Exit application
   */
  exit(0);
}


int16 rsi_frame_read(uint8 *packet_buffer)
{
    /* Variables */
    rsi_linux_app_cb_t *linux_app_cbPtr = &rsi_linux_app_cb;
    pkt_struct_t *rspPtr = NULL;

    /* Length of the data to copy */
    int16 length = 0;

    /* Pointer to the Packet file descriptor */
    uint8 *descPtr    = NULL;

#ifdef ENABLE_DEBUG_PRINTS
    int i;
#endif

    /* Do actual deque from the RX queue */
    pthread_mutex_lock(&linux_app_cbPtr->mutex1);
    rspPtr = rsi_dequeue_from_rcv_q();
    pthread_mutex_unlock(&linux_app_cbPtr->mutex1);

    /* Assign pointers to appropriate addresses */
    descPtr    = rspPtr->data + RSI_NL_HEAD_SIZE;

    /* Calculate length of the packet from the first two bytes of the frame descriptor */
    length = rsi_bytes2R_to_uint16(descPtr);
    length &= 0x0FFF;
    length += RSI_FRAME_DESC_LEN;

    /* Debug: Print the length & contents of the packet */
#ifdef ENABLE_DEBUG_PRINTS
    RSI_DPRINT(RSI_PL0,"Response (Length of the Response packet: %d)\n", length);
    for (i=0; i<length; i++) {
        RSI_DPRINT (RSI_PL0, "0x%02x ", descPtr[i]);
        if ((i+1)%16 == 0) {
            RSI_DPRINT(RSI_PL0, "\n");
        }
    }
    RSI_DPRINT(RSI_PL0, "\n");
#endif

    /* Copy the packet into the buffer */
    memcpy(packet_buffer, descPtr, length);
    free(rspPtr);
    /* Return success */
    return 0;
}
