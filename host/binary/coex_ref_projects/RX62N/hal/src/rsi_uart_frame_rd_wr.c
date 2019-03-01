/**
 * @file     rsi_uart_framerdwr.c
 * @version  1.0
 * @date     2014-Sept-14
 *
 * Copyright(C) Redpine Signals 2013
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief UART Control: Functions used to control UART frame read/write functions
 *
 * @section Description
 * UART function to read/write management descriptors frames to/from the Wi-Fi module
 *
 * @section Improvements
 * Function header is modified for frameDscRd() function
 */


/*
 * Includes
 */

#include "rsi_global.h"
#include "rsi_app.h"
#include "rsi_config.h"
#include "platform_specific.h"
#include "RPDL/r_pdl_sci.h"
/* CMT RPDL function definitions */
#include "RPDL/r_pdl_cmt.h"
/* General RPDL function definitions */
#include "RPDL/r_pdl_definitions.h"
#include <stdio.h>
#include <stdlib.h>


#if (RSI_INTERFACE == RSI_UART)
/**
 * Global Variables
 */

/*====================================================*/
/**
 * @fn          int16 rsi_frame_read(uint8 *pkt_buffer)
 * @brief This  function is used to read the response from module.
 * @param[in]   uint8 *pkt_buffer, pointer to the buffer to which packet has to read
 *              which is used to store the response from the module
 * @param[out]  none
 * @return      errCode
 *              0  = SUCCESS
 * @section description 
 * This is a common function to read response for all the command and data from Wi-Fi module.
 */
int16 rsi_frame_read(uint8 *pkt_buffer)
{  
  uint8 rxbuf[4];
  int16 retval = 0;

#ifdef RSI_USE_HOST_WAKEUP_AS_INTERRUPT
  rsi_assert_wakeup_source();
   while(!rsi_assert_status())
      {
        rsi_assert_wakeup_source();
      }
#endif


   R_SCI_Receive(2, PDL_NO_DATA, (&rxbuf),4, PDL_NO_FUNC, PDL_NO_FUNC);
   R_SCI_Receive(2, PDL_NO_DATA,pkt_buffer,((*(uint16*)&rxbuf[0])-4), PDL_NO_FUNC, PDL_NO_FUNC);

#ifdef RSI_USE_HOST_WAKEUP_AS_INTERRUPT
   rsi_app_cb.pkt_pending = RSI_FALSE;
   rsi_irq_disable();
   rsi_deassert_wakeup_source();
   while(rsi_assert_status())
      {
        rsi_deassert_wakeup_source();
      }
	  rsi_irq_enable();//Handled in pkt_pending handler
#endif
  /* Return success */
  return retval;
}

/*====================================================*/
/**
 * @fn          int16 rsi_frame_write(rsi_uFrameDsc *uFrameDscFrame,uint8 *payloadparam,uint16 size_param)
 * @brief       Common function for all the commands.
 * @param[in]   uFrameDsc uFrameDscFrame, frame descriptor
 * @param[in]   uint8 *payloadparam, pointer to the command payload parameter structure
 * @param[in]   uint16 size_param, size of the payload for the command
 * @return      errCode
 *              0  = SUCCESS
 * @section description 
 * This is a common function used to process a command to the Wi-Fi module.
 */
int16 rsi_frame_write(rsi_uFrameDsc *uFrameDscFrame,uint8 *payloadparam,uint16 size_param)
{
   int16 retval = 0	;
   R_SCI_Send(2, PDL_NO_DATA, (uint8 const*)uFrameDscFrame,16, PDL_NO_FUNC);
   if(size_param)
   {
    R_SCI_Send(2, PDL_NO_DATA, payloadparam,size_param, PDL_NO_FUNC);
   }
   return retval;
}
#endif

