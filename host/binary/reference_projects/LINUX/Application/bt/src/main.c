/**
 * @file        bt_main.c
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
#include "rsi_bt_global.h"
#include "platform_specific.h"
#include "rsi_bt_api.h" 
#include "rsi_nl_app.h" 
#include "rsi_lib_util.h"
#include "platform_specific.h"

/*
 * Defines
 */

/*
 * Global Variables
 */
rsi_linux_app_cb_t   rsi_linux_app_cb;



/* function declarations */
int main(int argc, char *argv[]);
extern int bt_main(int app_mode);

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

#ifdef LINUX_PLATFORM
  rsi_linux_app_cb_t *linux_app_cbPtr = &rsi_linux_app_cb;
  /* Open a socket for issueing ioctls */
  if ((linux_app_cbPtr->ioctl_sd = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
  {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT (RSI_PL3,"socket creation error\n");
#endif
    return 2;
  }
#endif
  retval = rsi_nl_socket_init();
  if (retval == -1) {
    /* Error occurred! */
    return 2;
  }

  rsi_fill_genl_nl_hdrs_for_cmd();

#if 0//SPI_INTERFACE
  retval = rsi_update_info(MODULE_POWER_CYCLE);
#endif

#if 1
  if( (rc1 = pthread_create( &thread1, NULL, RecvThreadBody, (void*) message1)) )
  {
    RSI_DPRINT(RSI_PL13,"Thread creation failed: %d\n", rc1);
  }
#endif
  //! send interrupt irq register frame to driver to register the interrupt irq
  //rsi_bt_register_interrupt_irq();
  
  //! calling bt_main
   bt_main(!(argc > 1));

#if 0
  retval = rsi_update_info(UPDATE_JOIN_DONE);
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

#ifdef RSI_DEBUG_PRINT
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
    length += RSI_BT_FRAME_DESC_LEN;

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

    /* Copy the packet into the buffer */
    memcpy(packet_buffer, descPtr, length);

    rsi_free(rspPtr);
    /* Return success */
    return 0;
}
