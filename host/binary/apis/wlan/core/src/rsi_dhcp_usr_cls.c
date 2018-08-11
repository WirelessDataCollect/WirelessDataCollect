/**
 * @file       rsi_dhcp_usr_cls.c
 * @version    1.0
 * @date       2017-May-05
 *
 * Copyright(C) Redpine Signals 2015
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief SMTP CLIENT: Function which implements SMTP client
 *
 * @section Description
 * This file contains the SMTP client functionality.
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
 * @fn          int16 rsi_dhcp_client_usr_cls(rsi_dhcp_user_class_t *dhcp_usr_cls)
 * @brief       Sends the DHCP user class commands to the Wi-Fi module
 * @param[in]   rsi_dhcp_user_class_t *dhcp_usr_cls, Pointer to DHCP user class structure
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
 * This API is used to send DHCP user class commands to the Wi-Fi module.
 * This API should be called only after join command API.
 *
 * @section prerequisite 
 * The IP configuration should be done sussessfully.
 */

int16 rsi_dhcp_client_usr_cls(rsi_dhcp_user_class_t *dhcp_usr_cls)
{
	int16    retval;

#ifdef RSI_DEBUG_PRINT
	RSI_DPRINT(RSI_PL3,"\r\n\nDHCP OPTION 77");
#endif

	retval = rsi_execute_cmd((uint8 *)rsi_frameCmdDHCPUsrCls, (uint8 *)dhcp_usr_cls, sizeof(rsi_dhcp_user_class_t));  

	return retval;
}



