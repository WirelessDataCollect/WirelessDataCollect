/**
 * @file       rsi_http_credentials.c
 * @version    1.0
 * @date       2015-May-06
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief HTTP Server Credentials: Function which implements HTTP server credentials command
 *
 * @section Description
 * This file contains the Join function.
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
 * @fn          int16 rsi_http_credentials(rsi_uhttpCredentials *uhttpCredentialsFrame)
 * @brief       Sends the Http credentials command to the Wi-Fi module via SPI
 * @param[in]   rsi_uhttpCredentials *uhttpCredentialsFrame, Pointer to Http credentials structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failed
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to set the Credentials to the HTTP server. 
 * @section prerequisite 
 * The rsi_ipparam_set  should be done sussessfully.
 */

int16 rsi_http_credentials(rsi_uhttpCredentials  *uhttpCredentialsFrame)
{
   /* Http Credentials */
   uint8   rsi_frameCmdhttpCredentials[RSI_BYTES_3] = {0x3e , 0x40 , 0xB4 }; 
   int16 retval;
#ifdef RSI_DEBUG_PRINT
   RSI_DPRINT(RSI_PL3,"\r\n\nHTTP Credentials");
#endif
       
   retval = rsi_execute_cmd((uint8 *)rsi_frameCmdhttpCredentials,(uint8 *)uhttpCredentialsFrame,sizeof(rsi_uhttpCredentials));  
   
   return retval;
}
