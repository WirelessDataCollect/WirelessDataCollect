/**
 * @file     rsi_fwup_frm_host.c
 * @version  1.0
 * @date     2014-Sep-13
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief Firmware upgration form host 
 *
 * @section Description
 * This file contains the functionality of upgrading the firmware from host.
 * @functions Defined: 
 * rsi_fwup_frm_host()
 * rsi_parse_rps_file()
 */

/**
 * Includes
 */
#include "rsi_global.h"


/**
 * Global Variables
 */

/*==============================================*/
/**
 * @fn          int16 rsi_fwup_frm_host()
 * @brief       send the rps file to firmare for upgradation
 * @param[in]   fw_up_params 
 * @param[in]   rps_file
 * @param[in]   offset of the file from where to fill the payload
 * @param[in]   length to be filled in buffer
 * @param[in]   type 1-> request ,0->payload
 * @return      errCode
 *              0  = SUCCESS
 * @section description 
 * This API is used to send the rps file to firmare for upgradation of new image.
 */
int16 rsi_fwup_frm_host(rsi_fw_up_t *ptr_fw_up, uint8 *rps_file,uint32 rps_offset,uint16 length,uint16 type)
{
  int16               retval;
  uint8   rsi_frameCmdFwUpFrmHost[RSI_BYTES_3] ;
  *(uint16 *)&rsi_frameCmdFwUpFrmHost[0] = (((length+4) & 0xFFF) | (0x4 << 12));
  rsi_frameCmdFwUpFrmHost[2]= 0x99;
  /*fill Type*/
  *(uint16 *)&ptr_fw_up->packet_info[0] = type;
  /*filling length in the packet info*/
  *(uint16 *)&ptr_fw_up->packet_info[2] = length;
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nFIRMWARE UPGRADTION FROM HOST PACKET OFFSET IS===>>>%d\r\n",rps_offset);
#endif
  /*copying the actual payload from the rps file to the buffer*/
  memcpy(ptr_fw_up->payload,((uint8 *)rps_file + rps_offset),length);
  /*add 4 in length to include the packet info size*/
  length += 4;
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nFIRMWARE UPGRADTION FROM HOST PACKET LENGTH IS===>>>%d\r\n",length);
#endif
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdFwUpFrmHost, (uint8 *)ptr_fw_up, length);
  return retval;
}
