/**
 * @file      rsi_bt_spp.c
 * @version   1.0
 * @date      2014-Aug-22
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief Contains BT Classic SPP API's
 *
 * @section Description
 * This file contains a) SPP Connect function.
 * 		      b) SPP Disconnect function.		
 *		      c) SPP Transfer function.
 *
 */


/**
 * Includes
 */
#include "rsi_bt_global.h"
#include "rsi_bt_generic.h"
#include "rsi_bt_api.h"
#include "rsi_global.h"


/**
 * Global Variables
 */


/*===========================================================================
 *
 * @fn          INT16 rsi_bt_spp_connect(RSI_BT_CMD_SPP_CONNECT *SPPConnect)
 * @brief       Sends the SPP Connect command to the BT module
 * @param[in]   RSI_BT_CMD_SPP_CONNECT *SPPConnect, Pointer to SPP Connect structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to establish SPP connection with the remote BT device.
 *
 * @section prerequisite 
 */


INT16 rsi_bt_spp_connect(RSI_BT_CMD_SPP_CONNECT *uSPPConnect)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nSPP Connect Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSPPConn, (UINT08 *)uSPPConnect, sizeof(RSI_BT_CMD_SPP_CONNECT));
  return retval;
}







/*===========================================================================
 *
 * @fn          INT16 rsi_bt_spp_disconnect(RSI_BT_CMD_SPP_DISCONNECT *SPPDisConnect)
 * @brief       Sends the SPP disconnect command to the BT module
 * @param[in]   RSI_BT_CMD_SPP_DISCONNECT *SPPDisConnect, Pointer to SPP Disconnect structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to disconnect the SPP connection with the remote BT device.
 *
 * @section prerequisite 
 */

INT16 rsi_bt_spp_disconnect(RSI_BT_CMD_SPP_DISCONNECT *uSPPDisConnect)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nSPP Disconnect Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSPPDisConn, (UINT08 *)uSPPDisConnect, sizeof(RSI_BT_CMD_SPP_DISCONNECT));
  return retval;
}





/*===========================================================================
 *
 * @fn          INT16 rsi_bt_spp_transfer(RSI_BT_CMD_SPP_TRANSFER *SPPTransfer)
 * @brief       Sends the SPP transfer command to the BT module
 * @param[in]   RSI_BT_CMD_SPP_TRANSFER *SPPTransfer, Pointer to SPP Transfer structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to send data to the remote BT device using SPP profile. 
 *
 * @section prerequisite
 * none
 */


INT16 rsi_bt_spp_transfer(RSI_BT_CMD_SPP_TRANSFER *uSPPTransfer)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nSPP Transfer Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSPPTransfer, (UINT08 *)uSPPTransfer, sizeof(RSI_BT_CMD_SPP_TRANSFER));
  return retval;
}












































































