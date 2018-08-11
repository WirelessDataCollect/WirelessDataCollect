/**
 * @file     rsi_build_smtp_header.c
 * @version  2.7
 * @date     2015-Oct-2
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief SMTP header: Adds SMTP header
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
 * @fn          void rsi_build_smtp_header(uint8 *smtp_header)
 * @brief       User configurable smtp header 
 * @param[in]   uint8 uint8 *smtp_header
 * @param[out]  none
  *
 * @section description
  * To build the user configurable smtp header.user can add smtp header fields.
 */

void rsi_build_smtp_header(uint8 *smtp_header)
{
  strcpy((char *)smtp_header ,"MIME-Version: 1.0\\r\n");
  strcat((char *)smtp_header ,"Content-Type: text/plain\r\n");
  strcat((char *)smtp_header ,"  charset=\"utf-8\"\r\n");
  strcat((char *)smtp_header ,"Content-Transfer-Encoding: 8bit\r\n");
  strcat((char *)smtp_header ,"\r\n");
}


