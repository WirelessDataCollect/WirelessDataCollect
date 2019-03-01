/**
 * @file       rsi_send_url_rsp.c
 * @version    1.1
 * @date       2013-Feb-6
 *
 * Copyright(C) Redpine Signals 2013
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief SPI URL RESPONSE: Function which sends host web page.
 *
 * @section Description
 * This file contains the functionality to send host web page.
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"


/**
 * Global Variables
 */


/*=================================================*/
/**
 * @fn          int16 rsi_send_url_rsp(HostWebpageSnd_t *uUrlRsp, uint8 *webpage_morechunks, uint8 *webpage_file , uint32 file_size, uint8 first_chunk)
 * @brief       Sends the Webserver command to the Wi-Fi module via SPI
 * @param[in]   HostWebpageSnd_t *uUrlRsp, Pointer to WebpageSnd_t structure
 * @param[in]   uint8 *webpage_morechunks, Pointer to webpage_morechunks
 * @param[in]   uint8 *webpage_file, pointer to webpage
 * @param[in]   uint32 file_size, web page total size
 * @param[in]   uint8 first_chunk, to identify whether it is first chunk or not
 * @param[out]  none
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
 * This API is used to send url response to the Wi-Fi module. 
 * This API should be called only after rsi_init API.
 *
 * @section prerequisite 
 * The rsi_init for the Wi-Fi Module initialization should be done successfully.
 */
#if WEBPAGE_BYPASS_SUPPORT
int16 rsi_send_url_rsp(HostWebpageSnd_t *uUrlRsp, uint8 *webpage_morechunks, uint8 *webpage_file , uint32 file_size, uint8 first_chunk)
{
  int16  retval     =  0;
  uint16 curr_len   =  0;
  uint16 send_length = 0;
  uint8 rsi_framelocalCmdUrlRsp[3] = {0};

  static uint32 offset;
#ifdef RSI_DEBUG_PRINT
  static uint16 count=0;
#endif

  if(first_chunk)
  {
    //! If it is the first chunk then reset offset to zero
    offset = 0;
  }
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\nLoad Host Webpage Start\n");
#endif

  //! Get the current length that you want to send
  curr_len = ((file_size - offset) > MAX_HOST_WEBPAGE_SEND_SIZE) 
    ? MAX_HOST_WEBPAGE_SEND_SIZE : (file_size - offset);

  //! Fill total host web page size
  rsi_uint32_to_4bytes(uUrlRsp->total_len, file_size);

  //! Fill more chunks
  if((file_size - offset) <= MAX_HOST_WEBPAGE_SEND_SIZE)
  {
    *webpage_morechunks = 0;
    uUrlRsp->more_chunks = 0;
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL3, "sending Last chunk\n");
#endif
  }
  else
  {
    *webpage_morechunks = 1;
    uUrlRsp->more_chunks = 1;
  }

  //! Fill web page content
  memcpy((uint8*)(uUrlRsp->webpage), (uint8*)(webpage_file + offset), curr_len);

  //! calculate length of frame to send
  send_length = curr_len + (sizeof(HostWebpageSnd_t) - sizeof(uUrlRsp->webpage));

  //! Fill frame length & packet type
  rsi_uint16_to_2bytes(rsi_framelocalCmdUrlRsp, ((send_length & 0xFFF) | (0x4 << 12)));

  //! Fill frame type
  rsi_framelocalCmdUrlRsp[2] = RSI_RSP_HOST_WEBPAGE; 

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3, "total, current, send_length, offset, count: %d, %d, %d, %d %d\n", file_size, curr_len, send_length, offset, ++count);
#endif

  //! Send the current chunk 
  retval = rsi_execute_cmd((uint8 *)rsi_framelocalCmdUrlRsp ,(uint8 *)uUrlRsp, send_length);

  //! Adjust the offset
  offset += curr_len;

  //! Reset offset for next file if required
  if (offset >= file_size) 
  {
    offset = 0;
#ifdef RSI_DEBUG_PRINT
    count = 0;
#endif
  }

  return retval;
}
#endif

