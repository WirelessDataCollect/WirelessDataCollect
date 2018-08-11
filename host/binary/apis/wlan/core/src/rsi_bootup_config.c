/**
 * @file     rsi_bootup_config.c
 * @version  1.0
 * @date     2014-Apr-13
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief BOOTUP: Bootup configuration file 
 *
 * @section Description
 * This file contains the Bootup functionality.
 * @functions Defined: 
 * rsi_waitfor_boardready
 * rsi_select_option
 * rsi_upgrade_fw
 */

/**
 * Includes
 */
#include "rsi_global.h"
#include "rsi_api.h"


/*==============================================*/
/**
 * @fn          int16 rsi_waitfor_boardready(void)
 * @brief       Waits to receive board ready from WiFi module
 * @param[in]   none
 * @param[out]  none
 * @return      errCode
 *              0  = SUCCESS
 *              < 0 = Failure 
 *              -3 = Board ready not received
 *              -4 = Bootup options last configuration not saved
 *              -5 = Bootup options checksum failed
 *              -6 = Bootloader version mismatch 
 * @section description 
 * This API is used to check board ready from WiFi module.
 */
#if (defined(USB_INTERFACE) || defined(SPI_INTERFACE))
int16 rsi_waitfor_boardready(void)
{
  int16 retval = 0;
  uint16 read_value = 0;
//读取mem，如果是[15:8]=HOST_INTERACT_REG_VALID;[7:0]!=BOOTUP_OPTIONS_LAST_CONFIG_NOT_SAVED....等则正常启动
  retval = rsi_boot_insn(REG_READ, &read_value);

  if(retval < 0)
  {
    return retval;
  }
  if ((read_value & 0xFF00) == (HOST_INTERACT_REG_VALID & 0xFF00))
  {
    if((read_value & 0xFF) == BOOTUP_OPTIONS_LAST_CONFIG_NOT_SAVED)
    {
#ifdef RSI_DEBUG_PRINT      
      RSI_DPRINT(RSI_PL3,"BOOTUP OPTIOINS LAST CONFIGURATION NOT SAVED\n");
#endif
      return -4;
    }
    else if((read_value & 0xFF) == BOOTUP_OPTIONS_CHECKSUM_FAIL)
    {
#ifdef RSI_DEBUG_PRINT      
      RSI_DPRINT(RSI_PL3,"BOOTUP OPTIONS CHECKSUM FAIL\n");
#endif
      return -5;
    }
#if BOOTLOADER_VERSION_CHECK
		else if((read_value & 0xFF) == BOOTLOADER_VERSION)
    {
#ifdef RSI_DEBUG_PRINT      
      RSI_DPRINT(RSI_PL3,"BOOTLOADER VERSION CORRECT\n");
#endif
    }
    else
    {
#ifdef RSI_DEBUG_PRINT      
      RSI_DPRINT(RSI_PL3,"BOOTLOADER VERSION NOT MATCHING\n");
#endif

      return -6;
    }
#endif

#ifdef RSI_DEBUG_PRINT      
    RSI_DPRINT(RSI_PL3,"RECIEVED BOARD READY\n");
#endif
		return 0;
  }

#ifdef RSI_DEBUG_PRINT      
      RSI_DPRINT(RSI_PL3,"WAITING FOR BOARD READY\n");
#endif
  return -3;
}

/*==============================================*/
/**
 * @fn          int16 rsi_select_option(uint8 cmd)
 * @brief       Sends cmd to select option to load or update configuration 
 * @param[in]   uint8 cmd, type of configuration to be saved
 * @param[out]  none
 * @return      errCode
                < 0 = Command issue failed
 *              0  = SUCCESS
 * @section description 
 * This API is used to send firmware load request to WiFi module or update default configurations.
 */
int16 rsi_select_option(uint8 cmd)
{
  uint16   boot_cmd = 0;
  int16    retval = 0;
  uint16   read_value = 0;
  uint8    image_number  = 0;
  volatile int32  loop_counter = 0;

  boot_cmd = HOST_INTERACT_REG_VALID | cmd;
  if(cmd == RSI_CHECK_CRC)
  {
    boot_cmd &= 0xF0FF;
    boot_cmd |= (image_number << 8);
  }
  retval   = rsi_boot_insn(REG_WRITE, &boot_cmd);
  if(retval < 0)
  {
    return retval;
  }

  if((cmd != RSI_LOAD_IMAGE_I_FW) && (cmd != RSI_LOAD_IMAGE_I_ACTIVE_LOW_FW))
  {
    RSI_RESET_LOOP_COUNTER(loop_counter);
    RSI_WHILE_LOOP(loop_counter, RSI_LOOP_COUNT_SELECT_OPTION)
    {
      retval = rsi_boot_insn(REG_READ, &read_value);
      if(retval < 0)
      {
        return retval;
      }
      if(cmd == RSI_CHECK_CRC)
      {
        if((read_value & 0xFF) == CHECKSUM_SUCCESS)
        {
#ifdef RSI_DEBUG_PRINT      
          RSI_DPRINT(RSI_PL3,"CHECKSUM SUCCESS\n");
#endif
        }
        else if(read_value == CHECKSUM_FAILURE)
        {
#ifdef RSI_DEBUG_PRINT      
          RSI_DPRINT(RSI_PL3,"CHECKSUM FAIL\n");
#endif
        }
        else if(read_value == CHECKSUM_INVALID_ADDRESS)
        {
#ifdef RSI_DEBUG_PRINT      
          RSI_DPRINT(RSI_PL3,"Invalid Address \n");
#endif
        }
      }
      if (read_value == (HOST_INTERACT_REG_VALID | cmd))
      {
        break;
      }
    }
    RSI_CHECK_LOOP_COUNTER(loop_counter, RSI_LOOP_COUNT_SELECT_OPTION);
  }
  return retval;
}
/*==============================================*/
/**
 * @fn          int16 rsi_upgrade_fw(uint8 image_type, uint8 *fw_image, uint32 fw_image_size)
 * @brief       Upgrades firmware to WiFi module
 * @param[in]   uint8 image_type, type of firmware image to upgrade
 * @param[in]   uint8* fw_image, pointer to firmware
 * @param[in]   uint32 fw_image_size, size of firmware image
 * @param[out]  none
 * @return      errCode
 *              <0 = Command issue failed
 *              0  = SUCCESS
 * @section description 
 * This API is used to upgrade firmware to WiFi module.
 */
int16 rsi_upgrade_fw(uint8 image_type, uint8 *fw_image , uint32 fw_image_size)
{
  uint16 boot_cmd = HOST_INTERACT_REG_VALID | image_type;
  uint16 read_value = 0;
  uint32 offset = 0;
  int16  retval = 0;
  uint32 boot_insn = 0,poll_resp = 0;
  volatile int32  loop_counter = 0;
  retval = rsi_boot_insn(REG_WRITE, &boot_cmd);
  if(retval < 0)
  {
    return retval;
  }
  RSI_RESET_LOOP_COUNTER(loop_counter);
  RSI_WHILE_LOOP(loop_counter, RSI_LOOP_COUNT_UPGRADE_REQ)
  {
    retval = rsi_boot_insn(REG_READ, &read_value);
    if(retval < 0)
    {
      return retval;
    }
    if (read_value == (HOST_INTERACT_REG_VALID | SEND_RPS_FILE))
    {
      break;
    }
  }
  RSI_CHECK_LOOP_COUNTER(loop_counter, RSI_LOOP_COUNT_UPGRADE_REQ);
 
  boot_cmd = HOST_INTERACT_REG_VALID | PONG_VALID;
  while(offset <= fw_image_size){
    switch (boot_cmd){
      case (HOST_INTERACT_REG_VALID | PING_VALID):
        boot_insn = PONG_WRITE;
        poll_resp = PING_AVAIL;
        boot_cmd = HOST_INTERACT_REG_VALID |PONG_VALID;
        break;
      case (HOST_INTERACT_REG_VALID | PONG_VALID):
        boot_insn = PING_WRITE;
        poll_resp = PONG_AVAIL;
        boot_cmd = HOST_INTERACT_REG_VALID |PING_VALID;
        break;
    }

#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL3,"Burning from %x to %x of %x\n", offset, (offset + 4096), fw_image_size);
#endif
    retval = rsi_boot_insn(boot_insn, (uint16 *)((uint8 *)fw_image + offset));
    if(retval < 0)
    {
      return retval;
    }

    RSI_RESET_LOOP_COUNTER(loop_counter);
    RSI_WHILE_LOOP(loop_counter, RSI_LOOP_COUNT_UPGRADE_CHUNK)
    {
      retval = rsi_boot_insn(REG_READ, &read_value);
      if(retval < 0)
      {
        return retval;
      }
      if (read_value == (HOST_INTERACT_REG_VALID | poll_resp))
      {
        break;
      }
    }
    RSI_CHECK_LOOP_COUNTER(loop_counter, RSI_LOOP_COUNT_UPGRADE_CHUNK);
    offset += 1024*4;
  }
  boot_cmd = HOST_INTERACT_REG_VALID | EOF_REACHED;
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"EOF REACHED\n");
#endif
  retval = rsi_boot_insn(REG_WRITE, &boot_cmd);
  if(retval < 0)
  {
    return retval;
  }
  RSI_RESET_LOOP_COUNTER(loop_counter);
  while(loop_counter, RSI_LOOP_COUNT_UPGRADE_STATUS)
  {
    retval = rsi_boot_insn(REG_READ, &read_value);
    if(retval < 0)
    {
      return retval;
    }
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL3,"WAITING TO RECEIVE FIRMWARE UPGRADATION STATUS\n");
#endif
    if (read_value == (HOST_INTERACT_REG_VALID | FWUP_SUCCESSFUL))
    {
#ifdef RSI_DEBUG_PRINT

      RSI_DPRINT(RSI_PL3,"FIRMWARE UPGRADATION SUCCESSFUL\n");
#endif

      break;
    }
  }
  RSI_CHECK_LOOP_COUNTER(loop_counter, RSI_LOOP_COUNT_UPGRADE_STATUS);
  return retval;
}

#endif
