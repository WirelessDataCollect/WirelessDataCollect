/**
 * @file       rsi_ftp_client.c
 * @version    1.0
 * @date       2015-May-18
 *
 * Copyright(C) Redpine Signals 2015
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief FTP CLIENT: Function which implements FTP client
 *
 * @section Description
 * This file contains the FTP client functionality.
 *
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"
#include <string.h>

/**
 * Global Variables
 */

/*=================================================*/
/**
 * @fn          int16 rsi_ftp_client(uint8 type, rsi_ftp_client_t*ftp_client)
 * @brief       Sends the FTP commands to the Wi-Fi module
 * @param[in]   rsi_ftp_client_t *ftp_client, Pointer to FTP structure
 * @param[in]   uint8 type, type of FTP command
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
 * This API is used to send FTP commands to the Wi-Fi module.
 * This API should be called only after rsi_ip_param_set API.
 *
 * @section prerequisite 
 * The IP configuration should be done sussessfully.
 */
int16 rsi_ftp_client(uint8 type, rsi_ftp_client_t *ftp_client)
{
  int16          retval;
  uint8          rsi_frameCmdFTP[RSI_BYTES_3] = {0x00, 0x40, 0xE2};    

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n FTP client");
#endif

  
  //! Fill command type
  ftp_client->command_type = type;

  rsi_uint16_to_2bytes(rsi_frameCmdFTP, ((sizeof(rsi_ftp_client_t) & 0x0FFF) | 0x4000));    
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdFTP, (uint8 *)ftp_client, sizeof(rsi_ftp_client_t));

  return retval;
}


/*=================================================*/
/**
 * @fn          int16 rsi_ftp_file_write_content(rsi_ftp_file_write_t * ftp_file_write, uint8 *file_content, uint32 file_size, uint8 ip_version)
 * @brief       Sends the FTP commands to the Wi-Fi module
 * @param[in]   rsi_ftp_file_write_t *ftp_file_write, pointer to file write structure
 * @param[in]   uint8 *file_content, poointer to file
 * @param[in]   uint32 file_size, size of the file
 * @param[in]   uint8 ip_version, ip version used
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
 * This API is used to send FTP commands to the Wi-Fi module.
 * This API should be called only after rsi_ip_param_set API.
 *
 * @section prerequisite 
 * The IP configuration should be done sussessfully.
 */
int16 rsi_ftp_file_write_content(rsi_ftp_file_write_t *ftp_file_write, uint8 *file_content, uint32 file_size, uint8 ip_version)
{
  int16          retval = 0;
  uint8          rsi_frameCmdFTP[RSI_BYTES_3] = {0x00, 0x40, 0xE2};    
  uint32         file_offset = 0;
  uint32         chunk_size = 0;
  uint32         send_size = 0;
  uint8          head_room = 0;

  //! Fill command type
  ftp_file_write->command_type = FTP_COMMAND_FILE_WRITE_CONTENT;

  if(ip_version == 4)
  {
    //! Headroom for IPv4
    head_room = RSI_TCP_FRAME_HEADER_LEN;
  }
  else
  {
    //! Headroom for IPv6
    head_room = RSI_TCP_V6_FRAME_HEADER_LEN;
  }

  while(file_size)
  {
    if(file_size > FTP_MAX_CHUNK_LENGTH)
    {
      //! If size exceeds maximum chunk
      chunk_size = FTP_MAX_CHUNK_LENGTH;

      //! Dont set end of file
      ftp_file_write->end_of_file = 0;
    }
    else
    {
      chunk_size = file_size;

      //! Set end of file
      ftp_file_write->end_of_file = 1;
    }

    //! Copy file content
    memcpy((((uint8 *)ftp_file_write) + head_room), (file_content + file_offset), chunk_size);

    //! Add headroom to send size
    send_size = chunk_size + head_room;

    //! Prepare descriptor 
    rsi_uint16_to_2bytes(rsi_frameCmdFTP, ((send_size & 0x0FFF) | 0x4000));    

    //! Send chunk
    retval = rsi_execute_cmd((uint8 *)rsi_frameCmdFTP, (uint8 *)ftp_file_write, send_size);

    //! Increase file offset
    file_offset  += chunk_size;

    //! Decrese file remaining size
    file_size -= chunk_size;

  }

  return retval;
}

