/**
 * @file       rsi_send_boot_insn.c
 * @version    1.0
 * @date       2014-Apr-13
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief SEND BOOT INSN: send boot instructions to WiFi module 
 *
 * @section Description
 * This file contains boot instructions exchanges with WiFi module.
 *
 *
 */

/**
 * Includes
 */
#include "rsi_global.h"

/*==============================================*/
/**
 * @fn          int16 rsi_boot_insn(uint8 type, uint16 *data)
 * @brief       Sends boot instructions to WiFi module
 * @param[in]   uint8 type, type of the insruction to perform
 * @param[in]   uint32 *data, pointer to data which is to be read/write
 * @param[out]  none
 * @return      errCode
 *              < 0  = Command issued failure/Invalid command 
 *                0  = SUCCESS
 *              > 0  = Read value
 * @section description 
 * This API is used to send boot instructions to WiFi module.
 */
#if (defined(USB_INTERFACE) || defined(SPI_INTERFACE))
extern int16 rsi_mem_rd(uint32 reg_address, uint16 len, uint8 *value);
extern int16 rsi_mem_wr(uint32 reg_address, uint16 len, uint8 *value);

int16 rsi_boot_insn(uint8 type, uint16 *data)
{
  int16   retval = 0;
  uint16  local = 0;
  uint32  j = 0;
  uint32  cmd = 0; 
  uint16  read_data = 0;
  volatile int32  loop_counter = 0;
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\nBootInsn\n");
#endif

  switch(type)
  {
    case REG_READ:
      retval = rsi_mem_rd(HOST_INTF_REG_OUT,2,(uint8 *)&read_data);//读取wifi模组中的memory
      *data = read_data;
      break;

    case REG_WRITE:
      retval = rsi_mem_wr(HOST_INTF_REG_IN,2, (uint8 *)data);
      break;

    case PING_WRITE:

      for (j = 0; j<2048; j++){
        retval = rsi_mem_wr(0x19000 + (j*2), 2, (uint8 *)((uint32)data + (j*2)));
        if(retval < 0)
        {
          return retval;
        }
      }

      local = 0xab49;
      retval = rsi_mem_wr(HOST_INTF_REG_IN, 2, (uint8 *)&local);
      break;

    case PONG_WRITE:

      for (j = 0; j<2048; j++){
        retval = rsi_mem_wr(0x1a000 + (j*2), 2 ,(uint8 *)((uint32)data + (j*2)));
        if(retval < 0)
        {
          return retval;
        }
      }
      // Perform the write operation
      local = 0xab4f;
      retval = rsi_mem_wr(HOST_INTF_REG_IN, 2, (uint8 *)&local);
      break;

    case RSI_UPGRADE_IMAGE_I_FW:
      cmd = RSI_UPGRADE_IMAGE_I_FW | HOST_INTERACT_REG_VALID;
      retval = rsi_mem_wr(HOST_INTF_REG_IN, 2, (uint8 *)&cmd);
      if(retval < 0)
      {
        return retval;
      }

      RSI_RESET_LOOP_COUNTER(loop_counter); 
      RSI_WHILE_LOOP(loop_counter, RSI_LOOP_COUNT_UPGRADE_IMAGE)
      {
        retval = rsi_mem_rd(HOST_INTF_REG_OUT, 2, (uint8 *)&read_data);
        if(retval < 0)
        {
          return retval;
        }
        if (read_data == (SEND_RPS_FILE | HOST_INTERACT_REG_VALID)){
          break;
        }
      }
      RSI_CHECK_LOOP_COUNTER(loop_counter, RSI_LOOP_COUNT_UPGRADE_IMAGE);
      break;

    case RSI_LOAD_IMAGE_I_FW:
      cmd = RSI_LOAD_IMAGE_I_FW | HOST_INTERACT_REG_VALID;
      retval = rsi_mem_wr(HOST_INTF_REG_IN, 2, (uint8 *)&cmd);
      break;
    case RSI_LOAD_IMAGE_I_ACTIVE_LOW_FW:
      cmd = RSI_LOAD_IMAGE_I_ACTIVE_LOW_FW | HOST_INTERACT_REG_VALID;
      retval = rsi_mem_wr(HOST_INTF_REG_IN, 2, (uint8 *)&cmd);
      break;
    case RSI_UPGRADE_BL:
      cmd = RSI_UPGRADE_BL | HOST_INTERACT_REG_VALID;
      retval = rsi_mem_wr(HOST_INTF_REG_IN, 2, (uint8 *)&cmd);
      if(retval < 0)
      {
        return retval;
      }
      RSI_RESET_LOOP_COUNTER(loop_counter);
      RSI_WHILE_LOOP(loop_counter, RSI_LOOP_COUNT_UPGRADE_IMAGE)
      {
        retval = rsi_mem_rd(HOST_INTF_REG_OUT,  2, (uint8 *)&read_data);
        if(retval < 0)
        {
          return retval;
        }
        if (read_data == (SEND_RPS_FILE | HOST_INTERACT_REG_VALID)){
          break;
        }
      }
      RSI_CHECK_LOOP_COUNTER(loop_counter, RSI_LOOP_COUNT_UPGRADE_IMAGE);
      break;
    default:
      retval = -2;
      break;
  }
  return retval;
}
#endif
