/**
 * @file     rsi_usb_framerdwr.c
 * @version  1.0
 * @date     2015-Mar-24
 *
 * Copyright(C) Redpine Signals 2013
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief USB Control: Functions used to control USB frame read/write functions
 *
 * @section Description
 * USB function to read/write management descriptors frames to/from the Wi-Fi module
 *
 * @section Improvements
 * Function header is modified for frameDscRd() function
 */


/*
 * Includes
 */
#include "rsi_global.h"
#include "rsi_usb_cmd.h"
#include "rsi_config.h"

#if (RSI_INTERFACE == RSI_USB)
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
  return 0;
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
  return 0;
}

#endif
