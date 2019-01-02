/**
 * @file       rsi_execute_cmd.c
 * @version    2.7
 * @date       2012-Sep-26
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief Implements common functionality for all the commands
 *
 * @section Description
 * This file contains common api needed for all the commands
 *
 *
 */

/**
 * Includes
 */
#include "rsi_global.h"
#ifdef RSI_HAL
#include "rsi_spi_cmd.h"
#endif
#ifdef LINUX
extern struct net_device *glbl_net_device;
#endif

/*====================================================*/
/**
 * @fn          int16 rsi_execute_cmd(uint8 *descparam,uint8 *payloadparam,uint16 size_param)
 * @brief       Common function for all the commands.
 * @param[in]   uint8 *descparam, pointer to the frame descriptor parameter structure
 * @param[in]   uint8 *payloadparam, pointer to the command payload parameter structure
 * @param[in]   uint16 size_param, size of the payload for the command
 * @return      errCode
 *              SPI:
 *              -1 = SPI busy / Timeout
 *              -2 = SPI Failure
 *              -3 = BUFFER FULL
 *              0  = SUCCESS
 *              UART/USB/USB-CDC:
 *              -2 = Command issue failed
 *              0  = SUCCESS
 * @section description 
 * This is a common function used to process a command to the Wi-Fi module.
 */
int16 rsi_execute_cmd(uint8 *descparam,uint8 *payloadparam,uint16 size_param)
{
  int16            retval = 0;
  rsi_uFrameDsc    uFrameDscFrame;
#ifndef UART_INTERFACE
	uint8 queueno = (descparam[1] & 0xf0) >> 4;  //提取出descparam[1]的[7:4],rsi_frameCmdInit[1]是0x40
  uint8           int_status = 0;
#endif
#ifdef LINUX 
  PRSI_ADAPTER Adapter = rsi_getpriv(glbl_net_device);
#endif
#if ((RSI_POWER_MODE == RSI_POWER_MODE_2)||(RSI_POWER_MODE == RSI_POWER_MODE_8))
  uint8           powersave_enable;

#ifdef LINUX 
  powersave_enable = Adapter->power_save_enable;
#else 
  powersave_enable = rsi_app_cb.power_save_enable;
#endif
#endif

#ifndef LINUX 
#if (RSI_POWER_MODE == RSI_POWER_MODE_3)
  if (!rsi_app_cb.ps_ok_to_send)
  {
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"module in sleep; Enquing\n");
#endif
    memcpy(rsi_app_cb.ps_descparam, descparam, 16);
    rsi_app_cb.ps_pkt_pending = payloadparam;
    rsi_app_cb.ps_size_param  = size_param;
    return 0;
  }
#endif
#endif

#if ((RSI_POWER_MODE == RSI_POWER_MODE_2)||(RSI_POWER_MODE == RSI_POWER_MODE_8))
  if(powersave_enable){
#if (RSI_WMM_PS_SUPPORT && RSI_WMM_PS_TYPE)
    rsi_wait4wakeup();
#else
    rsi_req_wakeup();
#endif
  }
#endif
#ifndef UART_INTERFACE
  if ((queueno == WLAN_MGMT_TYPE) || (queueno == WLAN_DATA_TYPE)) {  //WLAN_MGMT_TYPE=0x04；WLAN_DATA_TYPE=0x05
    //! Buffer full has to be checked before calling send data
    retval = rsi_device_interrupt_status(&int_status);//返回设备的中断状态 //！会卡死
  }
 // printk("intr_status = %x\n", int_status);
  if(retval != 0x0) 
  {
#if ((RSI_POWER_MODE == RSI_POWER_MODE_2)||(RSI_POWER_MODE == RSI_POWER_MODE_8))
  if(powersave_enable){
    rsi_allow_sleep();
  }
#endif
    return retval;
  }
  if(int_status & RSI_IRQ_BUFFERFULL)
  {
#ifdef LINUX    
    Adapter->BufferFull = 1;
#endif    
#if ((RSI_POWER_MODE == RSI_POWER_MODE_2)||(RSI_POWER_MODE == RSI_POWER_MODE_8))
  if(powersave_enable){
    rsi_allow_sleep();
  }
#endif
    return BUFFER_FULL_FAILURE;
  }
  else
  {
#ifdef LINUX    
    Adapter->BufferFull = 0;
#endif    
  }
#endif
  //! 16 bytes, send/receive command descriptor frame
  //! Create the Command Frame Descriptor  
  rsi_build_frame_descriptor(&uFrameDscFrame,descparam);
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"Descriptor write");
#endif
  //! Write descriptor and payload
  retval = rsi_frame_write(&uFrameDscFrame, payloadparam, size_param);

#if ((RSI_POWER_MODE == RSI_POWER_MODE_2)||(RSI_POWER_MODE == RSI_POWER_MODE_8))
  if(powersave_enable){
    rsi_allow_sleep();
  }
#endif
#ifndef UART_INTERFACE
  if (retval != 0x00) 
#else
  if (retval == 0x00) 
#endif
  {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL4,"Frame write failErr=%02x", (uint16)retval);
#endif
    return retval;
  }
  
  return retval;
}

