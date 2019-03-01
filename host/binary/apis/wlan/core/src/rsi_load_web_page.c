/**
 * @file       rsi_load_web_page.c
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
 * @brief SPI WEB SERVER: Function which implements the spi version of the web server command
 *
 * @section Description
 * This file contains the SPI web server function.
 *
 * @Improvements
 * rsi_webserver function changed to rsi_load_webpage. Now, 3K webpage can
 * be loaded from module to host. 
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"


/**
 * Global Variables
 */
#if WEB_PAGE_LOAD

/*=================================================*/
/**
 * @fn          int16 rsi_load_web_page(rsi_uWebServer *uWebServer), uint8 *webpage_morechunks, uint8 *webpage_load_done)
 * @brief       Sends the Webserver command to the Wi-Fi module via SPI
 * @param[in]   rsi_uWebServer *uWebServer, Pointer to Webserver structure
 * @param[in]   uint8 *webpage_morechunks, Pointer to webpage_morechunks
 * @param[in]   uint8 *webpage_load_done, Pointer to webpage_load_done
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *               0 = SUCCESS
 * @section description 
 * This API is used to load the webpage to the Wi-Fi module. 
 * This API should be called only after rsi_init API.
 *
 * @section prerequisite 
 * The rsi_init for the Wi-Fi Module initialization should be done successfully.
 */
#if !RSI_TCP_IP_BYPASS
int16 rsi_load_web_page(rsi_uWebServer *uWebServer, uint8* webpage_file, uint8* webpage_load_done)
{
  int16  retval     =  0;
  uint16 curr_len   =  MAX_WEBPAGE_SEND_SIZE;
  uint16 file_size  =  *(uint16*)(uWebServer->webServFrameSnd.Webpage_info.total_len);

  static uint16 offset;
  uint32 send_size = 0;

  /* Webserver loading Frame */
  uint8   rsi_frameCmdWebServer[RSI_BYTES_3] = {0x1D, 0x44, 0x50};  

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\nLoad Webpage Start\n");
#endif

  //! Get the current length that you want to send
  curr_len = (file_size - offset > MAX_WEBPAGE_SEND_SIZE) 
              ? MAX_WEBPAGE_SEND_SIZE : (file_size - offset);

  //! Update the current length to be sent
  *(uint16*) (uWebServer->webServFrameSnd.Webpage_info.current_len) = curr_len;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3, "total, current, offset: %d, %d, %d\n", file_size, curr_len, offset);
#endif

  //! Copy the webpage file contents into the buffer
  memcpy((uint8*)(uWebServer->webServFrameSnd.Webpage_info.webpage), 
          (uint8*)(webpage_file + offset), curr_len);
 
  send_size = sizeof(rsi_uWebServer) - MAX_WEBPAGE_SEND_SIZE + curr_len;

  rsi_uint16_to_2bytes(rsi_frameCmdWebServer, ((send_size & 0x0FFF) | 0x4000));
  
  
  //! Send the data 
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdWebServer ,(uint8 *)uWebServer, 
      send_size);

  //! Adjust the offset
  offset += curr_len;

  //! Reset offset for next file if required
  if (offset == file_size) {
      offset = 0;
      *webpage_load_done = 1;
    }

  return retval;
}

#endif
#endif
