/**
 * @file     rsi_ota_fw_up.c
 * @version  2.7
 * @date     2016-Oct-7
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief OTAF: Function which upgrades the RS9113 RPS file over the air.
 *
 * @section Description
 * This file contains the OTAF function.
 *
 *
 */



/**
 * Includes
 */
#include "rsi_global.h"

/*=================================================*/
/**
 *@fn           int16 rsi_ota_fw_up(rsi_uOtafReq  *uOtafReqFrame)
 * @brief       Sends the OTAF command to the Wi-Fi module
 * @param[in]   rsi_uOtafReq  *uOtafReqFrame,pointer to OTAF client configuration stucture.
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
 * This API is used for over the air RS9113 firmware upgradation.
 * @section prerequisite 
 * The rsi_ipparam_set  should be done sussessfully.
 */

int16 rsi_ota_fw_up(rsi_uOtafReq  *uOtafReqFrame)
{
   int16 retval;
   
   /* OTAF  */
   uint8   rsi_frameCmdOtafUpgrade[RSI_BYTES_3] = {0x1B , 0x40 , 0xEF };
      
#ifdef RSI_DEBUG_PRINT
   RSI_DPRINT(RSI_PL3,"\r\n\nOTA Firmware Upgradation");
#endif
       
   retval = rsi_execute_cmd((uint8 *)rsi_frameCmdOtafUpgrade,(uint8 *)uOtafReqFrame,sizeof(rsi_uOtafReq));  
   
   return retval;
}



