/**
 * @file      rsi_bt_core.c
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
 * @brief Contains BT Classic Core API's.
 *
 * @section Description
 * This file contains a) Set Discovery Mode function.
 *          		      b) Query Discovery Mode function.
 *   		              c) Set Connectability Mode function.
 *    		            d) Set Pair Mode function.
 *    		            e) Query Pair Mode function.
 *    		            f) Remote Name Request function.
 *    		            g) Remote Name Requst Cancel functon.
 *    		            h) Inquiry function.
 *    		            i) Inquity Cancel function.
 *    		            j) Bond function.
 *    		            k) Bond Cancel function.
 *    		            l) Unbond function.
 *    		            m) Set Pin Type function.
 *    		            n) Query Pin Type function.
 *    		            o) User Confirmation funcion.
 *    		            p) Passkey Request Reply function.
 *    		            q) PinCode Reply function.
 *    		            r) Query Role function.
 *    		            s) Query Services function.
 *    		            t) Search Services function.
 *   		              u) Set Profile Mode function.
 *   		              v) Query Connectability mode function.
 *   		              w) set Role function.
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
 * @fn          INT16 rsi_bt_set_discovery_mode(RSI_BT_CMD_SET_DISCV_MODE *uSetDiscoveryMode)
 * @brief       Sends the Set Discovery Mode command to the BT module
 * @param[in]   RSI_BT_CMD_SET_DISCV_MODE *uSetDiscoveryMode, Pointer to Set Discovery Mode structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *               0  = SUCCESS
 * @section description 
 * This API is used to set the BT Module in any of the 3 discovery modes.
 *
 * @section prerequisite 
 */

INT16 rsi_bt_set_discovery_mode(RSI_BT_CMD_SET_DISCV_MODE *uSetDiscoveryMode)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nSet Discovery Mode Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetDiscvMode, (UINT08 *)uSetDiscoveryMode, sizeof(RSI_BT_CMD_SET_DISCV_MODE));
  return retval;
}



/*===========================================================================
 *
 * @fn          INT16 rsi_bt_query_discovery_mode(void)
 * @brief       Sends the Query Discovery mode command to the BT module
 * @param[in]   none
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to get Discovery Mode of the BT module.
 *
 * @section prerequisite 
 */

INT16 rsi_bt_query_discovery_mode(void)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery Discovery Mode start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryDiscvMode, NULL, 0);
  return retval;
}




/*===========================================================================
 *
 * @fn         INT16 rsi_bt_set_connectability_mode(RSI_BT_CMD_SET_CONNECTABILITY_MODE *uSetConnectabilityMode)
 * @brief       Sends the  Set Connectability Mode command to the BT module
 * @param[in]   RSI_BT_CMD_SET_CONNECTABILITY_MODE *uSetConnectabilityMode, Pointer to Set Connectability Mode structure  			
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to set the BT module in one of the two Connectability modes. 
 *
 * @section prerequisite 
 */
INT16 rsi_bt_set_connectability_mode(RSI_BT_CMD_SET_CONNECTABILITY_MODE *uSetConnectabilityMode)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nSet Connectability Mode starts ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetConnMode,  (UINT08 *)uSetConnectabilityMode, sizeof(RSI_BT_CMD_SET_CONNECTABILITY_MODE));
  return retval;
}



/*===========================================================================
 *
 * @fn          INT16 rsi_bt_query_connectability_mode(void)
 * @brief       Sends the Query Connectability mode command to the BT module
 * @param[in]   none
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to query the connectability mode of the BT module.
 *
 * @section prerequisite 
 */

INT16 rsi_bt_query_connectability_mode(void)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery Connectability Mode start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryConnMode, NULL, 0);
  return retval;
}



/*===========================================================================
 *
 * @fn          INT16 rsi_bt_set_pair_mode(RSI_BT_CMD_SET_PAIR_MODE *uSetPairMode)
 * @brief       Sends the Set Pair Mode command to the BT module
 * @param[in]   RSI_BT_CMD_SET_PAIR_MODE *uSetPairMode , Pointer to Set Pair Mode structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to enable or disable the Pairing mode of the BT module. 
 *
 * @section prerequisite 
 */

INT16 rsi_bt_set_pair_mode(RSI_BT_CMD_SET_PAIR_MODE *uSetPairMode)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nSet Pair Mode Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetPairMode, (UINT08 *)uSetPairMode, sizeof(RSI_BT_CMD_SET_PAIR_MODE));
  return retval;
}



/*===========================================================================
 *
 * @fn          INT16 rsi_bt_query_pair_mode(void)
 * @brief       Sends the query pair mode command to the BT module
 * @param[in]   none
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to query current pairing mode of the BT module.
 *
 * @section prerequisite 
 */

INT16 rsi_bt_query_pair_mode(void)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery Pair Mode start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryPairMode, NULL, 0);
  return retval;
}



/*===========================================================================
 *
 * @fn          INT16 rsi_bt_remote_name_request(RSI_BT_CMD_REMOTE_NAME_REQUEST *uRemoteNameRequest)	
 * @brief       Sends the Remote Name Request command to the BT module
 * @param[in]   RSI_BT_CMD_REMOTE_NAME_REQUEST *uRemoteNameRequest , Pointer to Remote Name Request structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to know the name of the remote BT device.
 *
 * @section prerequisite 
 */

INT16 rsi_bt_remote_name_request(RSI_BT_CMD_REMOTE_NAME_REQUEST *uRemoteNameRequest)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n  Remote Name Request Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdRemNameReq , (UINT08 *)uRemoteNameRequest , sizeof(RSI_BT_CMD_REMOTE_NAME_REQUEST));
  return retval;
}




/*===========================================================================
 *
 * @fn          INT16 rsi_bt_remote_name_request_cancel(RSI_BT_CMD_REMOTE_NAME_REQUEST_CANCEL *uRemoteNameRequestCancel)	
 * @brief       Sends the Remote Name Request Cancel command to the BT module
 * @param[in]   RSI_BT_CMD_REMOTE_NAME_REQUEST_CANCEL *uRemoteNameRequestCancel, Pointer to Remote Name Request Cancel structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to cancel the request made by “Remote Name Request” command
 *
 * @section prerequisite 
 */

INT16 rsi_bt_remote_name_request_cancel(RSI_BT_CMD_REMOTE_NAME_REQUEST_CANCEL *uRemoteNameRequestCancel)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n  Remote Name Request Cancel Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdRemNameReqCancel , (UINT08 *)uRemoteNameRequestCancel , sizeof(RSI_BT_CMD_REMOTE_NAME_REQUEST_CANCEL));
  return retval;
}



/*===========================================================================
 *
 * @fn          INT16 rsi_bt_inquiry(RSI_BT_CMD_INQUIRY *uInquiry)	
 * @brief       Sends the Inquiry command to the BT module.
 * @param[in]   RSI_BT_CMD_INQUIRY *uInquiry, Pointer to Inquiry structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to perform an inquiry to find BT devices in the vicinity.
 *
 * @section prerequisite 
 */
INT16 rsi_bt_inquiry(RSI_BT_CMD_INQUIRY *uInquiry)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n  Inquiry Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdInq , (UINT08 *)uInquiry , sizeof(RSI_BT_CMD_INQUIRY));
  return retval;
}



/*===========================================================================
 *
 * @fn          INT16 rsi_bt_inquiry_cancel(void); 	
 * @brief       Sends the Inquiry Cancel command to the BT module
 * @param[in]   none
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to cancel the inquiry which was in progress.
 *
 * @section prerequisite 
 */
INT16 rsi_bt_inquiry_cancel(void)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n  Inquiry Cancel Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdInqCancel , NULL, 0);
  return retval;
}



/*===========================================================================
 *
 * @fn          INT16 rsi_bt_bond(RSI_BT_CMD_BOND *uBond)	
 * @brief       Sends the Bond command to the BT module
 * @param[in]   RSI_BT_CMD_BOND *uBond, Pointer to Bond structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to establish Bond between BT module and remote BT device.
 *
 * @section prerequisite 
 */

INT16 rsi_bt_bond(RSI_BT_CMD_BOND *uBond)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n  Bond Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdBond , (UINT08 *)uBond , sizeof(RSI_BT_CMD_BOND));
  return retval;
}



/*===========================================================================
 *
 * @fn          INT16 rsi_bt_bond_cancel(RSI_BT_CMD_BOND_CANCEL *uBondCancel)	
 * @brief       Sends the Bond Cancel command to the BT module
 * @param[in]   RSI_BT_CMD_BOND_CANCEL *uBondCancel,pointer to Bond Cancel structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to cancel Bond between BT module and remote BT device.
 *
 * @section prerequisite 
 */

INT16 rsi_bt_bond_cancel(RSI_BT_CMD_BOND_CANCEL *uBondCancel)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n Bond Cancel Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdBondCancel , (UINT08 *)uBondCancel, sizeof(RSI_BT_CMD_BOND_CANCEL));
  return retval;
}




/*===========================================================================
 *
 * @fn          INT16 rsi_bt_unbond(RSI_BT_CMD_UNBOND *uUnbond)
 * @brief       Sends the UnBond command to the BT module
 * @param[in]   RSI_BT_CMD_UNBOND *uUnbond, Pointer to UnBond structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to un-bond the device, which was already bonded.
 *
 * @section prerequisite 
 */
INT16 rsi_bt_unbond(RSI_BT_CMD_UNBOND *uUnbond)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\n  UnBond Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdUnbond , (UINT08 *)uUnbond , sizeof(RSI_BT_CMD_UNBOND));
  return retval;
}




/*===========================================================================
 *
 * @fn          INT16 rsi_bt_set_pin_type(RSI_BT_CMD_SET_PIN_TYPE *uSetPinType)
 * @brief       Sends the Set Pin Type command to the BT module
 * @param[in]   RSI_BT_CMD_SET_PIN_TYPE *uSetPinType, Pointer to Set Pin Type structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to Set Pin Type of the BT module.
 *
 * @section prerequisite 
 */

INT16 rsi_bt_set_pin_type(RSI_BT_CMD_SET_PIN_TYPE *uSetPinType)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nSet Pin Type Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetPinType, (UINT08 *)uSetPinType, sizeof(RSI_BT_CMD_SET_PIN_TYPE));
  return retval;
}



/*===========================================================================
 *
 * @fn          INT16 rsi_bt_query_pin_type(void)
 * @brief       Sends the Query Pin Type command to the BT module
 * @param[in]   none
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to Get Pin Type of the BT module.
 *
 * @section prerequisite 
 */
INT16 rsi_bt_query_pin_type(void)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery Pin Type start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryPinType, NULL, 0);
  return retval;
}



/*===========================================================================
 *
 * @fn          INT16 rsi_bt_user_confirmation(RSI_BT_CMD_USER_CONFIRMATION *uUserConfirmation)
 * @brief       Sends the User Confirmation command to the BT module
 * @param[in]   RSI_BT_CMD_USER_CONFIRMATION *uUserConfirmation, Pointer to  User Confirmation structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to give the confirmation for the values sent by remote BT devices at the time of bonding. 
 *
 * @section prerequisite 
 */
INT16 rsi_bt_user_confirmation(RSI_BT_CMD_USER_CONFIRMATION *uUserConfirmation)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nUser Confirmation Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdUserConf, (UINT08 *)uUserConfirmation, sizeof(RSI_BT_CMD_USER_CONFIRMATION));
  return retval;
}



/*===========================================================================
 *
 * @fn          INT16 rsi_bt_passkey_request_reply(RSI_BT_CMD_PASSKEY_REPLY *uPasskeyReply)
 * @brief       Sends the Passkey Request reply command to the BT module.
 * @param[in]   RSI_BT_CMD_PASSKEY_REPLY *uPasskeyReply, Pointer to Passkey Request Reply structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to respond on a passkey entry request.
 *
 * @section prerequisite 
 */
INT16 rsi_bt_passkey_request_reply(RSI_BT_CMD_PASSKEY_REPLY *uPasskeyReply)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nPasskey Request Reply start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdPasskeyReply, (UINT08 *)uPasskeyReply, sizeof(RSI_BT_CMD_PASSKEY_REPLY));
  return retval;
}



/*===========================================================================
 *
 * @fn          INT16 rsi_bt_pincode_reply(RSI_BT_CMD_PINCODE_REPLY *uPincodeReply)
 * @brief       Sends the Pincodereply command to the BT module
 * @param[in]   RSI_BT_CMD_PINCODE_REPLY *uPincodeReply, Pointer to Pin Code Reply structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to respond on a pincode request.
 *
 * @section prerequisite 
 */

INT16 rsi_bt_pincode_reply(RSI_BT_CMD_PINCODE_REPLY *uPincodeReply)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nPinCode Reply start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdPincodeReply, (UINT08 *)uPincodeReply, sizeof(RSI_BT_CMD_PINCODE_REPLY));
  return retval;
}



/*===========================================================================
 *
 * @fn          INT16 rsi_bt_query_role(RSI_BT_CMD_QUERY_ROLE *uQryRole)
 * @brief       Sends the query role command to the BT module
 * @param[in]   RSI_BT_CMD_QUERY_ROLE *uQryRole, Pointer to Query Role structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *               0  = SUCCESS
 * @section description 
 * This API is used to Get Role of the BT module when connected with a particular remote BT device.
 *
 * @section prerequisite 
 */

INT16 rsi_bt_query_role(RSI_BT_CMD_QUERY_ROLE *uQryRole)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery Role Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryRole, (UINT08 *)uQryRole, sizeof(RSI_BT_CMD_QUERY_ROLE));
  return retval;
}



/*===========================================================================
 *
 * @fn          INT16 rsi_bt_set_role(RSI_BT_CMD_SET_ROLE *uSetRole)
 * @brief       Sends the Set role command to the BT module
 * @param[in]   RSI_BT_CMD_SET_ROLE *uSetRole, Pointer to Set Role structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to Set Master/Slave Role to the BT module.
 *
 * @section prerequisite 
 */

INT16 rsi_bt_set_role(RSI_BT_CMD_SET_ROLE *uSetRole)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nSet Role Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetRole, (UINT08 *)uSetRole, sizeof(RSI_BT_CMD_SET_ROLE));
  return retval;
}



/*===========================================================================
 *
 * @fn          INT16 rsi_bt_query_services(RSI_BT_CMD_QUERY_SERVICES *uGetServ)
 * @brief       Sends the Query services command to the BT module
 * @param[in]   RSI_BT_CMD_QUERY_SERVICES *uGetServ, Pointer to query services structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to search for the services supported by the remote BT Device. 
 *
 * @section prerequisite 
 */
INT16 rsi_bt_query_services(RSI_BT_CMD_QUERY_SERVICES *uGetServ)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nQuery Services Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdQryServ, (UINT08 *)uGetServ, sizeof(RSI_BT_CMD_QUERY_SERVICES));
  return retval;
}




/*===========================================================================
 *
 * @fn          INT16 rsi_bt_search_service(RSI_BT_CMD_SEARCH_SERVICE *uSearchService)
 * @brief       Sends the Search service command to the BT module
 * @param[in]   RSI_BT_CMD_SEARCH_SERVICE *uSearchService, Pointer to Search Service Structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to to find whether a particular service is supported by the remote BT device.
 *
 * @section prerequisite 
 */

INT16 rsi_bt_search_service(RSI_BT_CMD_SEARCH_SERVICE *uSearchService)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nSearch Services Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSearchServ, (UINT08 *)uSearchService, sizeof(RSI_BT_CMD_SEARCH_SERVICE));
  return retval;
}





/*===========================================================================
 *
 * @fn          INT16 rsi_bt_set_profile_mode(RSI_BT_CMD_SET_PROFILE_MODE *uSetProfileMode)
 * @brief       Sends the Set Profile Mode command to the BT module
 * @param[in]   RSI_BT_CMD_SET_PROFILE_MODE *uSetProfileMode , Pointer to Set Profile Mode structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to set profile mode of the BT module.
 *
 * @section prerequisite 
 */

INT16 rsi_bt_set_profile_mode(RSI_BT_CMD_SET_PROFILE_MODE *uSetProfileMode)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nSet Profile Mode Start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSetProfMode, (UINT08 *)uSetProfileMode, sizeof(RSI_BT_CMD_SET_PROFILE_MODE));
  return retval;
}

/*===========================================================================
 *
 * @fn          INT16 rsi_bt_linkkey_reply(RSI_BT_CMD_LINKKEY_REPLY *uLinkKeyReply)
 * @brief       Sends the LinkKeyreply command to the BT module
 * @param[in]   RSI_BT_CMD_LINKKEY_REPLY *uLinkKeyReply, Pointer to Link Key Reply structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to respond on a linkkey reply request.
 *
 * @section prerequisite 
 */

INT16 rsi_bt_linkkey_reply(RSI_BT_CMD_LINKKEY_REPLY *uLinkKeyReply)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nLinkKey Reply start ");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdLinkKeyReply, (UINT08 *)uLinkKeyReply, sizeof(RSI_BT_CMD_LINKKEY_REPLY));
  return retval;
}

/*===========================================================================
 *
 * @fn          INT16 rsi_bt_start_sniff_mode (RSI_BT_CMD_SNIFF_MODE *SniffMode)
 * @brief       Sends the start sniff mode command to the BT module
 * @param[in]   RSI_BT_CMD_SNIFF_MODE *SniffMode, Pointer to sniff enable structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used after connection completed to keep the device in sniff mode.
 *
 * @section prerequisite 
 */

INT16 rsi_bt_start_sniff_mode (RSI_BT_CMD_SNIFF_MODE *SniffMode)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n start sniff mode \r\n");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSniffMode, (UINT08 *)SniffMode, sizeof(RSI_BT_CMD_SNIFF_MODE));
  return retval;
}

/*===========================================================================
 *
 * @fn          INT16 rsi_bt_exit_sniff_mode (RSI_BT_CMD_SNIFF_EXIT *SniffExit)
 * @brief       Sends the stop/exit sniff mode command to the BT module
 * @param[in]   RSI_BT_CMD_SNIFF_EXIT *SniffExit, Pointer to sniff disable structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to get back the device from sniff mode.
 *
 * @section prerequisite 
 */

INT16 rsi_bt_exit_sniff_mode (RSI_BT_CMD_SNIFF_EXIT *SniffExit)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n sniff exit \r\n");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSniffExit, (UINT08 *)SniffExit, sizeof(RSI_BT_CMD_SNIFF_EXIT));
  return retval;
}

/*===========================================================================
 *
 * @fn          INT16 rsi_bt_sniff_subrating_mode (RSI_BT_CMD_SNIFF_SUBRATING *SniffSubrating)
 * @brief       Sends the sniff subrating mode command to the BT module
 * @param[in]   RSI_BT_CMD_SNIFF_SUBRATING *SniffSubrating, Pointer to sniff subrating structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is used to keep the device in sniff subrating mode.
 *
 * @section prerequisite 
 */

INT16 rsi_bt_sniff_subrating_mode (RSI_BT_CMD_SNIFF_SUBRATING *SniffSubrating)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n sniff subrating mode \r\n");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSniffSubrating, (UINT08 *)SniffSubrating, sizeof(RSI_BT_CMD_SNIFF_SUBRATING));
  return retval;
}

/*===========================================================================
 *
 * @fn          rsi_bt_enable_ssp_mode (RSI_BT_CMD_SSP_MODE *SSPMode)
 * @brief       Sends the enbale ssp pair mode command to the BT module
 * @param[in]   RSI_BT_CMD_SSP_MODE *SSPMode, Pointer to SSP mode enable structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is given before enter the connection state. This is used to enable/disable SSP pair mode.
 * If SSP is disabled, legacy pairing will happen by default
 * @section prerequisite 
 */

INT16 rsi_bt_enable_ssp_mode (RSI_BT_CMD_SSP_MODE *SSPMode)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n SSP mode \r\n");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdSSPEnable, (UINT08 *)SSPMode, sizeof(RSI_BT_CMD_SSP_MODE));
  return retval;
}

/*===========================================================================
 *
 * @fn          INT16 rsi_bt_enable_set_feature_bitmap (RSI_BT_CMD_FEATURE_BIT_MAP *FeatureBitMap)
 * @brief       Sends the set features bit map command to the BT module
 * @param[in]   RSI_BT_CMD_FEATURE_BIT_MAP *FeatureBitMap, Pointer to feature bit map structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is given at initilization time or before connection state.
 * bit fields:
 * bit 0 - security mode (1- enable/ 0-disable).
 * @section prerequisite 
 */

INT16 rsi_bt_enable_set_feature_bitmap (RSI_BT_CMD_FEATURE_BIT_MAP *FeatureBitMap)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n set feature bitmap \r\n");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdFeatureBitMap, (UINT08 *)FeatureBitMap, sizeof(RSI_BT_CMD_FEATURE_BIT_MAP));
  return retval;
}
/*===========================================================================
 *
 * @fn          INT16 rsi_bt_set_antenna_tx_power_value(RSI_BT_CMD_SET_ANTENNA_TX_POWER_LEVEL *AntennaTxPowerLevel)
 * @brief       Sends the BT/BLE Antenna Tx power value based on protocol mode
 * @param[in]   RSI_BT_CMD_SET_ANTENNA_TX_POWER_LEVEL *AntennaTxPowerLevel, pointer to antenna tx power level structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is given at initilization time or before connection state or after connection time.
 * @section prerequisite 
 */

INT16 rsi_bt_set_antenna_tx_power_value (RSI_BT_CMD_SET_ANTENNA_TX_POWER_LEVEL *AntennaTxPowerLevel)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n set BT tx power value \r\n");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdAntennaTxPowerLevel, (UINT08 *)AntennaTxPowerLevel, sizeof(RSI_BT_CMD_SET_ANTENNA_TX_POWER_LEVEL));
  return retval;
}


/*===========================================================================
 *
 * @fn          INT16 rsi_bt_eir_data_value(RSI_BT_CMD_SET_EIR_DATA *EirData)
 * @brief       Sends EIR data 
 * @param[in]   RSI_BT_CMD_SET_EIR_DATA *EirData, pointer to antenna EIR_data structure
 * @param[out]  none
 * @return      errCode
 *              -2 = Command execution failure
 *              -1 = Buffer Full
 *              0  = SUCCESS
 * @section description 
 * This API is given at initilization time or before connection state or after connection time.
 * @section prerequisite 
 */

INT16 rsi_bt_eir_data_value(RSI_BT_CMD_SET_EIR_DATA *EirData)
{
  INT16          retval;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n set BT EIR data value \r\n");
#endif

  retval = rsi_bt_execute_cmd((UINT08 *)rsi_frameCmdEIRData, (UINT08 *)EirData, sizeof(RSI_BT_CMD_SET_EIR_DATA));
  return retval;
}
