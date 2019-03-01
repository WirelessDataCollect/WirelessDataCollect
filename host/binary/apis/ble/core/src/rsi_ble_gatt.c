/**
 * @file      rsi_ble_gatt.c
 *
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
 * @brief Contains BLE GATT API's.
 *
 * @section Description
 * This file contains a) Query profiles list function.
 *  		         b) Query profile descriptor function.
 *   		        c) Query characterstic services function.
 *    		      d) Query include service function.
 *    		      e) Read cahr value by UUID function.
 *    		      f) Query descriptor function.
 *    		      g) Query att value functon.
 *    		      h) Query multi att value function.
 *    		      i) Query long att value function.
 *    		      j) Set att value function.
 *    		      k) Set att value no ack function.
 *    		      l) Set long att value function.
 *    		      m) Set Prep long att value function.
 *    		      n) Execute long att value function.
 *
 *    		     
 *    		     
 *    		     	     
 */		      	


/**
 * Includes
 */
#include "rsi_global.h"
#include "rsi_ble_global.h"
#include "rsi_bt_api.h"
#include "platform_specific.h"


/**
 * Global Variables
 */


/*===========================================================================
 *	
 * @fn          INT16 rsi_ble_query_profiles_list(void)
 * @brief       Sends the Query Profiles list command to the BLE module.
 * @param[in]   None
 * @param[out]  None
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *               0  = SUCCESS
 * @section description 
 * This API is used to get all supported profiles list from remote device.
 *
 * @section prerequisite
 * This API must be used after connecting with the remote device.
 */

INT16 rsi_ble_query_profiles_list(RSI_BLE_CMD_PROFILE_LIST  *uGetProfileList)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery profile list Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryProfList, (UINT08 *)uGetProfileList, sizeof (RSI_BLE_CMD_PROFILE_LIST));
  return retval;
}





/*===========================================================================
 *
 * @fn          INT16 rsi_ble_query_profile(RSI_BLE_CMD_QUERY_PROFILE *uGetProfile)
 * @brief       Sends the Query profile command to the BLE module
 * @param[in]   RSI_BLE_CMD_QUERY_PROFILE *uGetProfile, Pointer to Get Profile structure  			
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to get information about the given profile in the remote device. 
 *
 * @section prerequisite 
 * This API must be used after connecting with the remote device.
 */

INT16 rsi_ble_query_profile(RSI_BLE_CMD_QUERY_PROFILE *uGetProfile)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery profile descriptor starts ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryProfDesc, (UINT08 *)uGetProfile, sizeof(RSI_BLE_CMD_QUERY_PROFILE));
  return retval;
}



/*===========================================================================
 *
 * @fn          INT16 rsi_ble_query_characteristic_services(RSI_BLE_CMD_QUERY_CHARACTERISTIC_SERVICES *GetCharacteristicServices);	
 * @brief       Sends the query characterstic services command to the BLE module.
 * @param[in]   RSI_BLE_CMD_QUERY_CHARACTERISTIC_SERVICES *GetCharacteristicServices, Pointer to Query characterstic services structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to get all characteristic services list from remote device.
 *
 * @section prerequisite 
 */

INT16 rsi_ble_query_characteristic_services(RSI_BLE_CMD_QUERY_CHARACTERISTIC_SERVICES *uGetCharacteristicServices)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n Query Characterstic services start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryCharServ, (UINT08 *)uGetCharacteristicServices, sizeof(RSI_BLE_CMD_QUERY_CHARACTERISTIC_SERVICES));
  return retval;
}

/*===========================================================================
 *
 * @fn          INT16 rsi_ble_query_include_service(RSI_BLE_CMD_QUERY_INCLUDE_SERVICES *GetIncludeService);
 * @brief       Sends the query include service command to the BLE module
 * @param[in]   RSI_BLE_CMD_QUERY_INCLUDE_SERVICES *GetIncludeService,Pointer to Query include services structure.
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to get include services list from remote device.
 *
 * @section prerequisite 
 */

INT16 rsi_ble_query_include_service(RSI_BLE_CMD_QUERY_INCLUDE_SERVICES *uGetIncludeService)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery Include Service start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryIncludeServ, (UINT08 *)uGetIncludeService, sizeof(RSI_BLE_CMD_QUERY_INCLUDE_SERVICES));
  return retval;
}


/*===========================================================================
 *
 * @fn          INT16 rsi_ble_read_char_value_by_UUID(RSI_BLE_CMD_READ_CHAR_VALUE_BY_UUID *ReadCharValueByUUID)
 * @brief       Sends the Read Characteristic value by UUID command to the BLE module.
 * @param[in]   RSI_BLE_CMD_READ_CHAR_VALUE_BY_UUID *ReadCharValueByUUID ,Pointer to Read Char Value By UUID structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to read the services of given UUID in the given range from the remote device.
 *
 * @section prerequisite 
 */

INT16 rsi_ble_read_char_value_by_UUID(RSI_BLE_CMD_READ_CHAR_VALUE_BY_UUID *uReadCharValueByUUID)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n Read Char Val By UUID start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdReadCharValByUUID, (UINT08 *)uReadCharValueByUUID, sizeof(RSI_BLE_CMD_READ_CHAR_VALUE_BY_UUID));
  return retval;
}


/*===========================================================================
 *
 * @fn          INT16 rsi_ble_query_att(RSI_BLE_CMD_QUERY_ATT_DESC *uGetDescriptor)
 * @brief       Sends the Query descriptor command to the BLE module
 * @param[in]   RSI_BLE_CMD_QUERY_DESCRIPTOR *GetDescriptor, Pointer to Query Descriptor structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to get descriptors with in the given range from the remote device..
 *
 * @section prerequisite 
 */

INT16 rsi_ble_query_att(RSI_BLE_CMD_QUERY_ATT_DESC *uGetDescriptor)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n Query Descriptor start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryAtt, (UINT08 *)uGetDescriptor, sizeof(RSI_BLE_CMD_QUERY_ATT_DESC));
  return retval;
}



/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_ble_query_att_value(RSI_BLE_CMD_QUERY_ATT_VALUE *uGetAttributeValue)                                                                                                                                            													      
 * @brief       Sends the query Attribute Value command to the BLE module                                                  													      
 * @param[in]  	RSI_BLE_CMD_QUERY_ATT_VALUE *GetAttributeValue, Pointer to Query Attribute value structure                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to get the attribute value of the given handle from the remote device.                                                                                     													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT16 rsi_ble_query_att_value(RSI_BLE_CMD_QUERY_ATT_VALUE *uGetAttributeValue)                                                                                                            													                                                              													      
{                                                                                                            													      
  INT16          retval;                                                                                     													      
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n Query Attribute Value start ");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryAttVal, (UINT08 *)uGetAttributeValue, sizeof(RSI_BLE_CMD_QUERY_ATT_VALUE));													      
  return retval;                                                                                             													      
}                                                                                                            													      
                                                                                                             													      

                                                                                                                                                                                                                                                                                                                                                                                                                                                                      												
/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_ble_query_multi_att_values(RSI_BLE_CMD_QUERY_MULTIPLE_ATT_VALUES *GetMultipleAttValues)                                                                                                                                             													      
 * @brief       Sends the query multi att values command to the BLE module                                                  													      
 * @param[in]  	RSI_BLE_CMD_QUERY_MULTIPLE_ATT_VALUES *GetMultipleAttValues, Pointer to Query Multi Att Values structure                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to get the attribute values of the given handle from the remote device.                                                                                     													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT16 rsi_ble_query_multi_att_values(RSI_BLE_CMD_QUERY_MULTIPLE_ATT_VALUES *uGetMultipleAttValues)                                                                                   													                                                              													      
{                                                                                                            													      
  INT16          retval;                                                                                     													      
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n Query Multi Att Values start ");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryMulAttVal, (UINT08 *)uGetMultipleAttValues, sizeof(RSI_BLE_CMD_QUERY_MULTIPLE_ATT_VALUES));													      
  return retval;                                                                                             													      
}                                                                                                            													      
                                                                                                             													      
                                                                                                             													      

/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_ble_query_long_att_value(RSI_BLE_CMD_QUERY_LONG_ATT_VALUE *GetLongAttValue)                                                                                                                                           													      
 * @brief       Sends the query long att value command to the BLE module                                                  													      
 * @param[in]  	RSI_BLE_CMD_QUERY_LONG_ATT_VALUE *uGetLongAttValue, Pointer to Query long att value structure                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to read attribute value of the given handle from the given offset from the remote device.                                                                                     													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT16 rsi_ble_query_long_att_value(RSI_BLE_CMD_QUERY_LONG_ATT_VALUE *uGetLongAttValue)                                                                                      													                                                              													      
{                                                                                                            													      
  INT16          retval;                                                                                     													      
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n Query long att value start ");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryLongAttVal, (UINT08 *)uGetLongAttValue, sizeof(RSI_BLE_CMD_QUERY_LONG_ATT_VALUE));													      
  return retval;                                                                                             													      
}                                                                                                            													      
                                                                                                             													      
                                                                                                             													      


/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_ble_set_att_value(RSI_BLE_CMD_SET_ATT_VALUE *SetAttValue)                                                                                                                                           													      
 * @brief       Sends the Set Att Value command to the BLE module                                                  													      
 * @param[in]  	RSI_BLE_CMD_SET_ATT_VALUE *SetAttValue, Pointer to Set Att Value structure                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to .                                                                                     													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT16 rsi_ble_set_att_value(RSI_BLE_CMD_SET_ATT_VALUE *uSetAttValue)                                                                                                        													                                                              													      
{                                                                                                            													      
  INT16          retval;                                                                                     													      
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n Set Att Value start ");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetAttVal, (UINT08 *)uSetAttValue, sizeof(RSI_BLE_CMD_SET_ATT_VALUE));													      
  return retval;                                                                                             													      
}                                                                                                            													      
                                                                                                             													      


/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_ble_set_att_value_no_ack(RSI_BLE_CMD_SET_ATT_VALUE_NO_ACK *SetAttValueNoAck)                                                                                                                                             													      
 * @brief       Sends the Set att value no ack command to the BLE module                                                  													      
 * @param[in]  	RSI_BLE_CMD_SET_ATT_VALUE_NO_ACK *uSetAttValueNoAck, Pointer to Set Att Val No Ack structure                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to .                                                                                     													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT16 rsi_ble_set_att_value_no_ack(RSI_BLE_CMD_SET_ATT_VALUE_NO_ACK *uSetAttValueNoAck)                                                                                                            													                                                              													      
{                                                                                                            													      
  INT16          retval;                                                                                     													      
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n Set att value no ack start ");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetAttValNoAck, (UINT08 *)uSetAttValueNoAck, sizeof(RSI_BLE_CMD_SET_ATT_VALUE_NO_ACK));													      
  return retval;                                                                                             													      
}                                                                                                            													      
                                                                                                             													      
                                                                                                             													      
/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_ble_set_long_att_value(RSI_BLE_CMD_SET_LONG_ATT_VALUE *SetLongAttValue)                                                                                                                                            													      
 * @brief       Sends the Set long att value command to the BLE module                                                  													      
 * @param[in]  	RSI_BLE_CMD_SET_LONG_ATT_VALUE *uSetLongAttValue, Pointer to Set Long Att Value structure                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to .                                                                                     													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT16 rsi_ble_set_long_att_value(RSI_BLE_CMD_SET_LONG_ATT_VALUE *uSetLongAttValue)                                                                                                           													                                                              													      
{                                                                                                            													      
  INT16          retval;                                                                                     													      
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n Set long att value start ");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetLongAttVal, (UINT08 *)uSetLongAttValue, sizeof(RSI_BLE_CMD_SET_LONG_ATT_VALUE));													      
  return retval;                                                                                             													      
}                                                                                                            													      
                                                                                                             													      
                                                                                                             													      
                                                                                                             													      
/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_ble_set_prep_long_att_value(RSI_BLE_CMD_SET_PREPARE_LONG_ATT_VALUE *SetPrepLongAttValue)                                                                                                                                            													      
 * @brief       Sends the Set prep long att value command to the BLE module                                                  													      
 * @param[in]  	RSI_BLE_CMD_SET_PREPARE_LONG_ATT_VALUE *uSetPrepLongAttValue, Pointer to Set Prepare Long Att Value structure                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to .                                                                                     													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */


INT16 rsi_ble_set_prep_long_att_value(RSI_BLE_CMD_SET_PREPARE_LONG_ATT_VALUE *uSetPrepLongAttValue)                                                                                                         													                                                              													      
{                                                                                                            													      
  INT16          retval;                                                                                     													      
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n Set prep Long Att Value start ");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetPrepLongAttVal, (UINT08 *)uSetPrepLongAttValue, sizeof(RSI_BLE_CMD_SET_PREPARE_LONG_ATT_VALUE));													      
  return retval;                                                                                             													      
}                                                                                                            													      
                                                                                                             													      

/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_ble_execute_long_att_value(RSI_BLE_CMD_EXECUTE_LONG_ATT_VALUE_WRITE *ExecuteLongAttValue)                                                                                                                                             													      
 * @brief       Sends the Execute long att value command to the BLE module                                                  													      
 * @param[in]  	RSI_BLE_CMD_EXECUTE_LONG_ATT_VALUE_WRITE *uExecuteLongAttValue, Pointer to execute long att value structure                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to .                                                                                     													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT16 rsi_ble_execute_long_att_value(RSI_BLE_CMD_EXECUTE_LONG_ATT_VALUE_WRITE *uExecuteLongAttValue)                                                                                                           													                                                              													      
{                                                                                                            													      
  INT16          retval;                                                                                     													      
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT                                                                                       													      
  RSI_DPRINT(RSI_PL3,"\r\n\n Execute Long Att Value start ");                                                            													      
#endif                                                                                                       													      
                                                                                                             													      
  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdExeLongAttVal, (UINT08 *)uExecuteLongAttValue, sizeof(RSI_BLE_CMD_EXECUTE_LONG_ATT_VALUE_WRITE));													      
  return retval;                                                                                             													      
}                                                                                                            													      


/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_ble_device_AddService(void)                                                                                                                                             													      
 * @brief       Sends the BLE Device add service command to the BLE module                                                  													      
 * @param[in]  	none                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to deregister/deinit the BLE module. To again initialise the module, rsi_ble_device_init()
 * API has to be called                                                                                     													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT16 rsi_ble_device_AddService(RSI_BLE_CMD_ADD_GATT_SERVICE *uLEAddService)
{                                                                                                            													      
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL13,"\r\n BLE Add Service ");
  RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","BLE","Tx","Add srvc req","Adding BLE GAT service");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdBleAddService, (UINT08 *)uLEAddService, sizeof (RSI_BLE_CMD_ADD_GATT_SERVICE));
  return retval;
}
                                                                                                             													      
/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_ble_device_AddServiceAttribute(void)                                                                                                                                             													      
 * @brief       Sends the BLE Device add attribute to service command to the BLE module                                                  													      
 * @param[in]  	none                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to deregister/deinit the BLE module. To again initialise the module, rsi_ble_device_init()
 * API has to be called                                                                                     													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT16 rsi_ble_device_AddServiceAttribute(RSI_BLE_CMD_ADD_GATT_ATTRIBUTE *uLEAddAttribute)
{                                                                                                            													      
  INT16          retval;
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL13,"\r\n BLE Add Attribute ");
  RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","BLE","Tx","Add attr req","BLE Add GATT Attribute");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdBleAddAttribute, (UINT08 *)uLEAddAttribute, sizeof (RSI_BLE_CMD_ADD_GATT_ATTRIBUTE));
  return retval;
}

/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_ble_device_AddServiceAttribute(void)                                                                                                                                             													      
 * @brief       Sends the BLE Device add attribute to service command to the BLE module                                                  													      
 * @param[in]  	none                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to deregister/deinit the BLE module. To again initialise the module, rsi_ble_device_init()
 * API has to be called                                                                                     													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT16 rsi_ble_device_ChangeLocalAttValue(RSI_BLE_CMD_SET_LOCAL_ATT_VALUE *uLEChangeAttVal)
{                                                                                                            													      
  INT16          retval;
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL13,"\r\n BLE Change Local Attribute ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdBleSetLocalAttValue, (UINT08 *)uLEChangeAttVal, sizeof (RSI_BLE_CMD_SET_LOCAL_ATT_VALUE));
  return retval;
}

/*===========================================================================
 *                                                                                                                                                                                                                        													      
 * @fn          INT16 rsi_ble_device_AddServiceAttribute(void)                                                                                                                                             													      
 * @brief       Sends the BLE Device add attribute to service command to the BLE module                                                  													      
 * @param[in]  	none                                  													      
 * @param[out]  none                                                                                         													      
 * @return      errCode                                                                                      													      
 *              -2 = Command execution failure                                                               													      
 *              -1 = Buffer Full                                                                             													      
 *              0  = SUCCESS                                                                                 													      
 * @section description                                                                                      													      
 * This API is used to deregister/deinit the BLE module. To again initialise the module, rsi_ble_device_init()
 * API has to be called                                                                                     													      
 *                                                                                                           													      
 * @section prerequisite                                                                                     													      
 */

INT16 rsi_ble_device_GetLocalAttValue(RSI_BLE_CMD_GET_LOCAL_ATT_VALUE *uLEGetAttVal)
{                                                                                                            													      
  INT16          retval;
                                                                                                             													      
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL13,"\r\n BLE Get Local Attribute ");
  RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","BLE","Tx","Set Local Attr","Set Local Attributes");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdBleGetLocalAttValue, (UINT08 *)uLEGetAttVal, sizeof (RSI_BLE_CMD_SET_LOCAL_ATT_VALUE));
  return retval;
}
