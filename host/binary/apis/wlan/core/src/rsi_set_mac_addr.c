/**
 * @file       rsi_set_mac_addr.c
 * @version    2.7
 * @date       2012-Sep-26
 *
 * Copyright(C) Redpine Signals 2011
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief SET MAC ADDRESS: Function to set the mac address
 *
 * @section Description
 * This file contains function to set mac address.
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"
#include <stdio.h>
#include <string.h>


/**
 * Global Variables
 */


/*=================================================*/
/**
 * @fn           int16 rsi_set_mac_addr(uint8 *macAddress)
 * @brief        Sends the set MAC Address command to the Wi-Fi module via SPI
 * @param[in]    uint8 *macAddress
 * @param[out]   none
 * @return       errCode
 *              SPI:
 *              -1 = SPI busy / Timeout
 *              -2 = SPI Failure
 *              -3 = BUFFER FULL
 *              0  = SUCCESS
 *              UART/USB/USB-CDC:
 *              -2 = Command issue failed
 *              0  = SUCCESS
 * @section description  
 * This API is used to overwrite the MAC address provided by the module. It should be 
 * called before the rsi_init API.
 * @section prerequisite  
 * This API should be called before rsi_init API.
 */
int16 rsi_set_mac_addr(uint8 *macAddress)
{
  int16                    retval;
  rsi_uSetMacAddr          uSetMacAddrFrame;  

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\nSetMacAddr Start ");
#endif

  //!send the MAC Address
  memcpy(uSetMacAddrFrame.setMacAddrFrameSnd.macAddr,macAddress, RSI_MACADDRLEN);
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdSetMacAddr,(uint8 *)&uSetMacAddrFrame,sizeof(rsi_uSetMacAddr));
  return retval;
}


