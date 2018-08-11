/**
 * @file     rsi_buildHttpExtendedHeader.c
 * @version  2.7
 * @date     2012-Sep-12
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief Extended HTTP header: Adds Extended HTTP header
 *
 * @section Description
 * This file contains the Store Configuration Enable/Disable function.
 *
 *
 */

/**
 * Includes
 */
#include <string.h>
#include "rsi_global.h"

/*==============================================*/
/**
 * @fn          void rsi_buildHttpExtendedHeader(uint8 *http_header, uint8 delimiter_mode)
 * @brief       User configurable Extended http header 
 * @param[in]   uint8 uint8 *http_header
 * @param[in]   uint8 delimiter_mode mode of delimiter
 * @param[out]  none
  *
 * @section description
  * To build the user configurable http header.user can add http header fields.
 */

void rsi_buildHttpExtendedHeader(uint8 *http_header, uint8 delimiter_mode)
{

  if(delimiter_mode)
  {
    strcpy((char *)http_header ,"User-Agent: curl/7.30.0\r\n");
  }
  else
  {
    strcat((char *)http_header ,"User-Agent: curl/7.30.0\r\n");
  }
  strcat((char *)http_header ,"Accept: */*\r\n");
  strcat((char *)http_header ,"Content-Type: application/x-www-form-urlencoded\r\n");

}


