/**
 * @file      rsi_bt_generic.c
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
 * @brief Contains BT Common API's
 *
 * @section Description
 * This file contains a) Set Local Name function.
 * 		                b) Query Local Name function.		
 *		                c) Set Local COD function.
 *		                d) Query Local COD function.
 *		                e) Query RSSI function.
 *		                f) Query Link Quality function.
 *		                g) Query Local BD Address function.
 *
 */


/**
 * Includes
 */
#include "rsi_bt_global.h"
#include "rsi_bt_generic.h"
#include "rsi_bt_api.h"
#include "platform_specific.h"


/**
 * Global Variables
 */


/*===========================================================================
 *
 * @fn          INT16 rsi_bt_set_local_name(RSI_BT_CMD_SET_LOCAL_NAME *uSetLocalName)
 * @brief       Sends the Set Local name command to the BT module
 * @param[in]   RSI_BT_CMD_SET_LOCAL_NAME *uSetLocalName, Pointer to Set Local Name structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to  Set Name to the BT module.
 *
 * @section prerequisite 
 */

INT16 rsi_bt_set_local_name(RSI_BT_CMD_SET_LOCAL_NAME *uSetLocalName)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nSet Local Name Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetLocalName, (UINT08 *)uSetLocalName, sizeof(RSI_BT_CMD_SET_LOCAL_NAME));
  return retval;
}




/*===========================================================================
 *
 * @fn          INT16 rsi_bt_query_local_name(void)
 * @brief       Sends the Query Local Name command to the BT module
 * @param[in]   none
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to Get Name of the BT module.
 *
 * @section prerequisite 
 * none
 */

INT16 rsi_bt_query_local_name(void)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery Local Name Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryLocalName, NULL, 0);
  return retval;
}




/*===========================================================================
 *
 * @fn          INT16 rsi_bt_set_local_cod(RSI_BT_CMD_SET_LOCAL_COD *SetLocalCOD)
 * @brief       Sends the Set Local code command to the BT module
 * @param[in]   RSI_BT_CMD_SET_LOCAL_COD *uSetLocalCOD, Pointer to Set Local COD structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to set the Class of the BT module.
 *
 * @section prerequisite 
 */
INT16 rsi_bt_set_local_cod(RSI_BT_CMD_SET_LOCAL_COD *uSetLocalCOD)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nSet Local COD Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetLocalCOD, (UINT08 *)uSetLocalCOD, sizeof(RSI_BT_CMD_SET_LOCAL_COD));
  return retval;
}







/*===========================================================================
 *
 * @fn          INT16 rsi_bt_query_local_cod(void);
 * @brief       Sends the Query Local code command to the BT module
 * @param[in]   none
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to query the class of the BT module.
 *
 * @section prerequisite 
 * none
 */


INT16 rsi_bt_query_local_cod(void)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery Local Name Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryLocalCOD, NULL, 0);
  return retval;
}




/*===========================================================================
 *
 * @fn          INT16 rsi_bt_query_rssi(RSI_BT_CMD_QUERY_RSSI *QueryRSSI)
 * @brief       Sends the Query rssi command to the BT module
 * @param[in]   RSI_BT_CMD_QUERY_RSSI *QueryRssi, Pointer to Query RSSI structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to get RSSI of remote BT device.
 *
 * @section prerequisite
 * none
 */

INT16 rsi_bt_query_rssi(RSI_BT_CMD_QUERY_RSSI *uQueryRSSI)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery RSSI Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryRSSI, (UINT08 *)uQueryRSSI, sizeof(RSI_BT_CMD_QUERY_RSSI));
  return retval;
}




/*===========================================================================
 *
 * @fn          INT16 rsi_bt_query_link_quality(RSI_BT_CMD_QUERY_LINK_QUALITY *uQueryLinkQuality)
 * @brief       Sends the Query Link Quality command to the BT module
 * @param[in]   RSI_BT_CMD_QUERY_LINK_QUALITY *uQueryLinkQuality, Pointer to Query Link Quality structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to Get link quality between BT module and remote BT device.
 *
 * @section prerequisite 
 *
 */

INT16 rsi_bt_query_link_quality(RSI_BT_CMD_QUERY_LINK_QUALITY *uQueryLinkQuality)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery Link Quality Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryLinkQuality, (UINT08 *)uQueryLinkQuality, sizeof(RSI_BT_CMD_QUERY_LINK_QUALITY));
  return retval;
}




/*===========================================================================
 *
 * @fn          INT16 rsi_bt_query_local_bd_address(void)
 * @brief       Sends the Query Local BD Address command to the BT module
 * @param[in]   none
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to Get Local BD Address of the BT module.
 *
 * @section prerequisite 
 * none
 */

INT16 rsi_bt_query_local_bd_address(void)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n Query Local BD Address Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryLocalBDAddr, NULL, 0);
  return retval;
}




/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_bt_device_init(void)                                                                                                                                             													      
 * @brief       Sends the BT Device Init command to the BT classic/LE module                                                  													      
 * @param[in]  	none                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to initialise the BT module.                                                                                      													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT16 rsi_bt_device_init(void)                                                                                                           													                                                              													      
{                                                                                                            													      
  INT16          retval;                                                                                     													      
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n BT INIT start");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdBTInit, NULL, 0);													      
  return retval;                                                                                             													      
}                                                                                                            													      




/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_bt_device_deinit(void)                                                                                                                                             													      
 * @brief       Sends the BT Device deinit command to the BT Classic/LE module                                                  													      
 * @param[in]  	none                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to deregister/deinit the BT module. To again initialise the module, rsi_bt_device_init()
 * API has to be called                                                                                     													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT16 rsi_bt_device_deinit(void)                                                                                                           													                                                              													      
{                                                                                                            													      
  INT16          retval;                                                                                     													      
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n BT DEINIT start ");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdBTDeinit, NULL, 0);													      
  return retval;                                                                                             													      
}                                                                                                            													      
                                                                                                             													      



/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_bt_antenna_select(RSI_BT_CMD_ANTENNA_SELECT *uAntennaSelect)                                                                                                                                             													      
 * @brief       Sends the BT antenna select command to the BT Classic/LE module                                                  													      
 * @param[in]  	RSI_BT_CMD_ANTENNA_SELECT *uAntennaSelect                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to select internal/external antenna of the BT module. 
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT16 rsi_bt_antenna_select(RSI_BT_CMD_ANTENNA_SELECT *uAntennaSelect)                                                                                                           													                                                              													      
{                                                                                                            													      
  INT16          retval;                                                                                     													      
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n BT Antenna Select start ");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdBTAntennaSelect, (UINT08 *)uAntennaSelect, sizeof(RSI_BT_CMD_ANTENNA_SELECT));													      
  return retval;                                                                                             													      
}                                                                                                            													      
                                                                                                             													      



/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_bt_config_enable(RSI_BT_CMD_CONFIG_ENABLE *uConfigEnable)                                                                                                                                             													      
 * @brief       Sends the BT config enable command to the BT Classic/LE module                                                  													      
 * @param[in]  	RSI_BT_CMD_CONFIG_ENABLE *uConfigEnable                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to enable/disable stored configuration in the BT module.                                                                                     													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

/*INT16 rsi_bt_config_enable(RSI_BT_CMD_CONFIG_ENABLE *uConfigEnable)                                                                                                           													                                                              													      
{                                                                                                            													      
  INT16          retval;                                                                                     													      
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n BT Config Enable/Disable start ");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdBTConfigEnable, (UINT08 *)uConfigEnable, sizeof(RSI_BT_CMD_CONFIG_ENABLE));													      
  return retval;
}
*/
                                                                                                             													      

/*=================================================*/
/**
 * @fn          rsi_uCmdRsp *rsi_parse_response(UINT08 *rsp)
 * @brief       To parse the resposne received from Kernel
 * @param[in]   UINT08 *rsp, response buffer pointer
 * @param[out]  none
 * @return      rsi_uCmdRsp *ptr, response pointer
 * @section description 
 * This API is used to parse the recieved response. This returns the 
 * pointer which points to rsptype, status, response payload in order.
 */
RSI_BT_RESPONSE *rsi_bt_parse_response(UINT08 *rsp)
{
  RSI_BT_RESPONSE         *temp_uCmdRspPtr = NULL;
  UINT16                  temp_rspCode;
  UINT16                  temp_status;
  UINT08                  *descPtr = rsp ;
  UINT08                  *payloadPtr = rsp + RSI_BT_FRAME_DESC_LEN;

  /* Retrieve response code from the received packet */
  temp_status  = rsi_bytes2R_to_uint16(descPtr + RSI_BT_STATUS_OFFSET);
  temp_rspCode = rsi_bytes2R_to_uint16(descPtr + RSI_BT_RSP_TYPE_OFFSET);
 
  /* Copy the response type and status to payloadPtr-4, payloadPtr-2
   * locations respectively.
   */
  rsi_uint16_to_2bytes((payloadPtr - 2), temp_status);
  rsi_uint16_to_2bytes((payloadPtr - 4), temp_rspCode);

  temp_uCmdRspPtr = (RSI_BT_RESPONSE *)(payloadPtr - 4);

  return temp_uCmdRspPtr;
}


/*===========================================================================
 *
 * @fn          INT16 rsi_bt_per_transmit(RSI_BT_CMD_PER_TRANSMIT *uPerTransmit)
 * @brief       Sends the PER transmit command to the BT module
 * @param[in]   RSI_BT_CMD_PER_TRANSMIT *uPerTransmit, Pointer to PER Transfer structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to send PER transmit command to module. 
 *
 * @section prerequisite
 * none
 */

INT16 rsi_bt_per_transmit(RSI_BT_CMD_PER_TRANSMIT *uPerTransmit)
{
  INT16          retval;
#ifdef BT_ENABLE
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdPerTransmit, (UINT08 *)uPerTransmit, sizeof(RSI_BT_CMD_PER_TRANSMIT ));
#endif  
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\n\nPER Transmit Command Sent...\n");
#endif
  return retval;
}

/*===========================================================================
 *
 * @fn          INT16 rsi_bt_per_receive(RSI_BT_CMD_PER_RECEIVE *uPerReceive)
 * @brief       Sends the PER receive command to the BT module
 * @param[in]   RSI_BT_CMD_PER_RECEIVE *uPerReceive, Pointer to PER Transfer structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to send PER receive command to module. 
 *
 * @section prerequisite
 * none
 */

INT16 rsi_bt_per_receive(RSI_BT_CMD_PER_RECEIVE *uPerReceive)
{
  INT16          retval;

#ifdef BT_ENABLE
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdPerReceive, (UINT08 *)uPerReceive, sizeof(RSI_BT_CMD_PER_RECEIVE));
#endif  
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\n\nPER Receive Command Sent...\n");
#endif
  return retval;
}

/*===========================================================================
 *
 * @fn          INT16 rsi_bt_per_stats(RSI_BT_CMD_PER_STATS *uPerStats)
 * @brief       Sends the PER Stats command to the BT module
 * @param[in]   RSI_BT_CMD_PER_STATS *uPerStats, Pointer to PER Transfer structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to send PER stats command to module. 
 *
 * @section prerequisite
 * none
 */

INT16 rsi_bt_per_stats(RSI_BT_CMD_PER_STATS *uPerStats)
{
  INT16          retval;

#ifdef BT_ENABLE
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdPerBTStats, (UINT08 *)uPerStats, sizeof(RSI_BT_CMD_PER_STATS));
#endif  
  return retval;
}

/*===========================================================================
 *
 * @fn          INT16 rsi_bt_per_cw_mode(RSI_BT_CMD_PER_CW_MODE *uPerCw)
 * @brief       Sends the PER cw mode command to the BT module
 * @param[in]   RSI_BT_CMD_PER_CW_MODE *uPerCw, Pointer to PER Transfer structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to send PER cw mode command to module. 
 *
 * @section prerequisite
 * none
 */

INT16 rsi_bt_per_cw_mode(RSI_BT_CMD_PER_CW_MODE *uPerCw)
{
  INT16          retval;

#ifdef BT_ENABLE
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdPerCwMode, (UINT08 *)uPerCw, sizeof(RSI_BT_CMD_PER_CW_MODE));
#endif  
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\n\nContinous Wave Mode Command Sent...\n");
#endif
  return retval;
}

