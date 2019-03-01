
#include "rsi_bt_app.h"
#include "rsi_ble_api.h"
#include "rsi_ble_config.h"
#include "rsi_app_util.h"
#include "rsi_lib_util.h"
#ifdef RSI_HAL
#include "rsi_hal.h"
#endif
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#ifdef LINUX_PLATFORM
#include "unistd.h"
#endif
#ifdef COEX_APP_CHANGES
#include "rsi_scheduler.h"
#include "rsi_config.h"
void rsi_set_wlan_sleep_mode(UINT32 mode);
void rsi_set_bt_or_zb_sleep_mode(UINT32 mode);
#endif
//#pragma pack(1)
#include "rsi_ble_global.h"

RSI_BLE_RESP_ADD_GATT_SERVICE   dbg_add_serv_resp;
RSI_BLE_RESP_ADD_GATT_SERVICE   dbg_add_serv_resp1;

char *ble_commands_str[] =
{
				"ADVERTISE            ",     
				"SCAN                 ",     
				"CONNECT              ",     
				"DISCONNECT           ",     
				"QUERY_DEVICE_STATE   ",     

				"START_ENCRYPTION ",
				"SMP_PAIR_REQUEST ",      
				"SMP_RESPONSE     ",          
				"SMP_PASSKEY      " ,

				"QUERY_PROFILES_LIST          ",
				"QUERY_PROFILE                ",
				"QUERY_CHARACTERISTIC_SERVICES",
				"QUERY_INCLUDE_SERVICES       ",
				"READ_CHAR_VALUE_BY_UUID      ",
				"QUERY_ATT_DESC               ",
				"QUERY_ATT_VALUE              ",
				"QUERY_MULTIPLE_ATT_VALUES    ",
				"QUERY_LONG_ATT_VALUE         ",
				"SET_ATT_VALUE                ",
				"SET_ATT_VALUE_NO_ACK         ",
				"SET_LONG_ATT_VALUE           ",
				"SET_PREPARE_LONG_ATT_VALUE   ",
				"EXECUTE_LONG_ATT_VALUE_WRITE ",
				"INIT_BLE                     ",
				"DE_INIT                      ",
     		"ANTENNA_SELECT               ",
        //"CONFIG_ENABLE                ",
     		//"LINKKEY_REPLY                ",
        
        "ADD_LINKLOSS_SERVICE         ",
        "ADD_LINKLOSS_ATTRIBUTE_1     ",
        "ADD_LINKLOSS_ATTRIBUTE_2     ",
        "ADD_NOTIFY_ATTRIBUTE_3       ",
        "ADD_IMMEDIATE_SERVICE        ",
        "ADD_IMMEDIATE_ATTRIBUTE_1    ",
        "ADD_IMMEDIATE_ATTRIBUTE_2    ",
        "SET_LOCAL_ATT_VALUE          ",
        "GET_LOCAL_ATT_VALUE          ",
        "SET_ADVERTISE_DATA           ",  //37
        "SET_PING_TIMEOUT             ",
        "GET_PING_TIMEOUT             ",
        "SET_RANDOM_ADDRESS           ",
        "ANTENNA_TX_POWER_LEVEL       ",
    	"LE_ADD_WHITELIST             ",   //42
        "LE_REMOVE_WHITELIST          ",    //43
		"LE_CLEAR_ALL_WHITELIST"
};

char *ble_events_str[] = 
{
				"ADVERTISE_REPORT           ",
				"CONNECTION_STATUS          ",
				"SMP_REQUEST                ",
				"SMP_RESPONSE               ",
				"SMP_PASSKEY                ",
				"SMP_FAILED                 ",
				"GATT_NOTIFICATION          ",
				"GATT_INDICATION            "
        "ENCRYPT_ENABLED            ",
				"",//17
				"",//18
				"",//19
				"",//1A
				"",//1B
				"",//1C
				"",//1D
				"",//1E
				"",//1F
        /*"PXPR_LINK_LOSS_ALERT",
        "PXPR_IMMEDIATE_ALERT",
        "PXPR_LINK_IS_LOST"*/
};


INT16 print_options(void)
{
    UINT16 ii = 0;

    /* There is an unsupported command in between 0 and 5 */
    UINT16 max_cmds = RSI_BLE_REQ_ANTENNA_SELECT - RSI_BLE_REQ_ADVERTISE;
    int in_cmd;

    max_cmds += ( RSI_BLE_SET_ANTENNA_TX_POWER_LEVEL - RSI_BLE_REQ_ADD_LINKLOSS_SERVICE + 1 ); 
    max_cmds += ( RSI_BLE_CLEARALL_WHITELIST - RSI_BLE_ADD_WHITELIST + 1);
	for  (ii = 0; ii < max_cmds; ii++)
	{
		if (ii == 0)
		{
#ifdef RSI_DEBUG_PRINT			
             RSI_DPRINT(RSI_PL3,"\nBLE core commands \n=========================\n");
#endif		 
		}
		else if (ii == 5)
		{
#ifdef RSI_DEBUG_PRINT
             RSI_DPRINT(RSI_PL3,"\nBLE SMP commands \n=========================\n");
#endif
		}
		else if (ii == 9)
		{
#ifdef RSI_DEBUG_PRINT
             RSI_DPRINT(RSI_PL3,"\nBLE GATT commands \n=========================\n");
#endif
		}
		else if (ii == 26)
		{
#ifdef RSI_DEBUG_PRINT
             RSI_DPRINT(RSI_PL3,"\nBLE GATT service \n=========================\n");
#endif
        }
#ifdef RSI_DEBUG_PRINT
		 RSI_DPRINT(RSI_PL3," %d. %s\n",ii+1, ble_commands_str[ii]);
#endif
	}
#ifdef RSI_DEBUG_PRINT
	 RSI_DPRINT(RSI_PL3,"\n");
     RSI_DPRINT(RSI_PL3,"Read the packet from recv queue... \n=========================\n");
     RSI_DPRINT(RSI_PL3," %d. READ RESPONSE....\n",(max_cmds+1));
     RSI_DPRINT(RSI_PL3,"Enter your choice:\n");
    scanf("%d",&in_cmd);
#endif
    
    if (in_cmd > max_cmds)
    {
      in_cmd = -1;
    }
    
    return (INT16)in_cmd;
}

#ifndef FSM_BASED_BLE_APP
INT16 rsi_ble_app(void)
{
    INT16 cmd;
    INT16 RetVal = 0;

    
    cmd = print_options();
    if (cmd >= 41)
    {
#ifdef RSI_DEBUG_PRINT
        RSI_DPRINT(RSI_PL3,"Executing the command %s\n",ble_commands_str[cmd -1]);
#endif
        RetVal = rsi_ble_init_struct(cmd  + RSI_BLE_ADD_WHITELIST - 41);
    }
    else if (cmd >= 27)
    {
#ifdef RSI_DEBUG_PRINT
         RSI_DPRINT(RSI_PL3,"Executing the command %s\n",ble_commands_str[cmd -1]);
#endif
        RetVal = rsi_ble_init_struct(cmd  + RSI_BLE_REQ_ADD_LINKLOSS_SERVICE - 27);
    }
    else if (cmd > 5)
    {
#ifdef RSI_DEBUG_PRINT
         RSI_DPRINT(RSI_PL3,"Executing the command %s\n",ble_commands_str[cmd -1]);
#endif
        RetVal = rsi_ble_init_struct(cmd  + RSI_BLE_REQ_ADVERTISE);
    }
    else if (cmd > 0)
    {
#ifdef RSI_DEBUG_PRINT
         RSI_DPRINT(RSI_PL3,"Executing the command %s\n",ble_commands_str[cmd -1]);
#endif
        RetVal = rsi_ble_init_struct((cmd - 1) + RSI_BLE_REQ_ADVERTISE);
    }
    else
	{
#ifdef RSI_DEBUG_PRINT
         RSI_DPRINT(RSI_PL3,"Waiting for events ...\n");
#endif
	}
    
    return RetVal;
}
#endif

/* Process responses */
void print_uuid(UUID_T *t_uuid)
{
#ifdef RSI_DEBUG_PRINT
    UINT16 jj;
    UINT08 *tmp_uuid;
    RSI_DPRINT(RSI_PL3,"UUID:\n");
    tmp_uuid = (UINT08*)&t_uuid->Val;
	
    for (jj = 0; jj < t_uuid->size; jj++)
    {
				     RSI_DPRINT(RSI_PL3,"%02x",tmp_uuid[jj]); 
		 }
	 RSI_DPRINT(RSI_PL3,"\n");
#endif
}

void print_profile_descriptor(PROFILE_DESCRIPTOR *pd)
{
#ifdef RSI_DEBUG_PRINT
     RSI_DPRINT(RSI_PL3,"StartHandle : %02x\t", *(UINT16*)pd->StartHandle);
     RSI_DPRINT(RSI_PL3,"EndHandle: %02x\t", *(UINT16*)pd->EndHandle);
     RSI_DPRINT(RSI_PL3,"uuid size: %02x\t\n", pd->ProfileUUID.size);
#endif
    print_uuid(&pd->ProfileUUID);
}
void print_servcie(INCLUDE_SERVICE *is)
{
#ifdef RSI_DEBUG_PRINT
     RSI_DPRINT(RSI_PL3,"Handle : %02x\t", is->Handle);
     RSI_DPRINT(RSI_PL3,"Include Start Handle : %02x\t", is->IncServ.IncludeStartHandle);
     RSI_DPRINT(RSI_PL3,"Include End Handle : %02x\t\n", is->IncServ.IncludeEndHandle);
#endif
    print_uuid(&is->IncServ.IncludeUUID);
}

void rsi_ble_decode_rsp(UINT16 rsp_type, UINT16 status, void *rsp)
{
    UINT16 ii;
#ifdef RSI_DEBUG_PRINT
    UINT16 ix;

    if ( (rsp_type >= RSI_BLE_RSP_ADVERTISE) && (rsp_type <= RSI_BLE_RSP_QUERY_DEVICE_STATE)) {
	
         RSI_DPRINT(RSI_PL13,"Received response type: %s, status:%02x\n", ble_commands_str[rsp_type - RSI_BLE_RSP_ADVERTISE - 1], status);
   } else if ( (rsp_type >= RSI_BLE_RSP_START_ENCRYPTION) && (rsp_type <= RSI_BLE_RSP_WHITE_LIST)) {
	
         RSI_DPRINT(RSI_PL13,"Received response type: %s, status:%02x\n", ble_commands_str[rsp_type - RSI_BLE_RSP_ADVERTISE - 1], status);
    } else if ( (rsp_type >= RSI_BLE_EVENT_ADVERTISE_REPORT) && (rsp_type <= RSI_BLE_EVENT_PXPR_LINK_IS_LOST )) {
	
         RSI_DPRINT(RSI_PL13,"Received event type: %s, status:%02x\n", ble_events_str[rsp_type - RSI_BLE_EVENT_ADVERTISE_REPORT], status);
    }
#endif
    if ((rsp_type < RSI_BT_EVT_ROLE_CHANGE_STATUS) && (status != 0)) {
        return;
    }

	switch (rsp_type)
    {

      case RSI_BLE_RSP_WHITE_LIST:
#ifdef RSI_DEBUG_PRINT				 
             RSI_DPRINT(RSI_PL3,"RSI_BLE_RSP_WHITE_LIST\n");
#endif 
             break;
	    case RSI_BLE_RSP_ANTENNA_TX_POWER_LEVEL:
#ifdef RSI_DEBUG_PRINT				 
             RSI_DPRINT(RSI_PL3,"RSI_BLE_RSP_ANTENNA_TX_POWER_LEVEL\n");
#endif 
             break;

	    case RSI_BLE_RSP_SET_ADVERTISE_DATA:
#ifdef RSI_DEBUG_PRINT				 
             RSI_DPRINT(RSI_PL3,"RSI_BLE_RSP_SET_ADVERTISE_DATA\n");
#endif 
             break;
			 
        case RSI_BLE_RSP_GET_LE_PING_TIMEOUT:
             {
#ifdef RSI_DEBUG_PRINT
                 RSI_DPRINT(RSI_PL3,"RSI_BLE_RSP_GET_LE_PING_TIMEOUT\n");
                 RSI_BLE_RESP_GET_PING_TIMEOUT   *ugetpingtimeout = rsp;
				 RSI_DPRINT(RSI_PL3,"ping timeout :%02x\n",ugetpingtimeout->Timeout);
#endif
             }
             break;
			 
        case RSI_BLE_RSP_SET_LE_PING_TIMEOUT:
#ifdef RSI_DEBUG_PRINT				 
             RSI_DPRINT(RSI_PL3,"RSI_BLE_RSP_SET_LE_PING_TIMEOUT\n");
#endif
             break;

        case RSI_BLE_RSP_ADVERTISE:
             break;
             
        case RSI_BLE_RSP_SCAN:
             if (status == 0) {
                 clear_scan_resp ();
             }
             break;
                    
        case RSI_BLE_RSP_CONNECT:
             break;
        
        case RSI_BLE_RSP_DISCONNECT:
             break;
        
        case RSI_BLE_RSP_QUERY_DEVICE_STATE:
             {
#ifdef RSI_DEBUG_PRINT				 
                 RSI_BLE_RESP_QUERY_DEVICE_STATE   *uQryDevState = rsp;
                 RSI_DPRINT(RSI_PL3,"Device state :%02x\n",uQryDevState->DeviceState);
#endif
			}
             break;

        case RSI_BLE_RSP_START_ENCRYPTION:
             break;

        case RSI_BLE_RSP_SMP_PAIR_REQUEST:
             break;

		case RSI_BLE_RSP_SMP_RESPONSE:
             break;
        
        case RSI_BLE_RSP_SMP_PASSKEY:
             break;
        
        case RSI_BLE_RSP_QUERY_PROFILES_LIST:
             {
                 RSI_BLE_RESP_QUERY_PROFILES_LIST   *uQryProfList = rsp;
#ifdef RSI_DEBUG_PRINT           
                  RSI_DPRINT(RSI_PL3,"Number of profiles: %d\n", uQryProfList->NumberOfProfiles);
#endif
				 for (ii = 0 ; ii < uQryProfList->NumberOfProfiles; ii++) {
                     print_profile_descriptor(&uQryProfList->ProfileDescriptor[ii]);
                 }
#ifdef FSM_BASED_BLE_APP
#ifdef LINUX_PLATFORM
         sleep(1);
#endif
         //rsi_ble_init_struct(RSI_BLE_REQ_QUERY_PROFILES_LIST);
#endif				 
			       }
		         break;
        
        case RSI_BLE_RSP_QUERY_PROFILE:
             {
                 RSI_BLE_RESP_QUERY_PROFILE_DESCRIPTOR   *uQryProf = rsp;
                 
                 print_profile_descriptor(&uQryProf->ProfileDescriptor);
             }
             break;
        
        case RSI_BLE_RSP_QUERY_CHARACTERISTIC_SERVICES:
             {
                 RSI_BLE_RESP_QUERY_CHARACTERISTIC_SERVICES  *uQryCharServ = rsp;
#ifdef RSI_DEBUG_PRINT           
                  RSI_DPRINT(RSI_PL3,"Number of characteristic_services %d\n",uQryCharServ->NumberOfCharServices);
                  RSI_DPRINT(RSI_PL3,"Characteristic services:\n");
#endif
                 
                 for (ii = 0; ii < uQryCharServ->NumberOfCharServices; ii++) {
#ifdef RSI_DEBUG_PRINT
                      RSI_DPRINT(RSI_PL3,"Handle: %02x\n",uQryCharServ->CharacteristicService[ii].Handle);
                      RSI_DPRINT(RSI_PL3,"CharacterProperty: %02x\n",uQryCharServ->CharacteristicService[ii].CharServ.CharacterProperty);
                      RSI_DPRINT(RSI_PL3,"Char Handle: %02x\n", uQryCharServ->CharacteristicService[ii].CharServ.CharacterHandle);
#endif
                     print_uuid(&uQryCharServ->CharacteristicService[ii].CharServ.CharacterUUID);
                 }
             }
             break;
        
        case RSI_BLE_RSP_QUERY_INCLUDE_SERVICES:
             {
                 RSI_BLE_RESP_QUERY_INCLUDE_SERVICE    *uQryIncServ = rsp;
#ifdef RSI_DEBUG_PRINT    
                  RSI_DPRINT(RSI_PL13,"NumberOfIncludeServices:%d\n",uQryIncServ->NumberOfIncludeServices);
#endif
                 for (ii = 0; ii < uQryIncServ->NumberOfIncludeServices; ii++)
                 {
                     print_servcie(&uQryIncServ->IncludeServices[ii]);
                 }
             }
             break;

             case RSI_BLE_RSP_READ_CHAR_VALUE_BY_UUID:
                  {
#ifdef RSI_DEBUG_PRINT
                       RSI_BLE_RESP_READ_CHAR_VALUE_BY_UUID   *uQryCharVal = rsp;
                       RSI_DPRINT(RSI_PL3,"NumberOfValues:%d\n", uQryCharVal->NumberOfValues);
                       RSI_DPRINT(RSI_PL3,"Value:\n");

                      for (ii = 0; ii < uQryCharVal->NumberOfValues; ii++)
                      {
                           RSI_DPRINT(RSI_PL3,"%02x ", uQryCharVal->CharacterValue[ii]);
                      }
                       RSI_DPRINT(RSI_PL3,"\n");
#endif
	              }
                  break;
             
             case RSI_BLE_RSP_QUERY_ATT_DESC:
                  {
#ifdef RSI_DEBUG_PRINT    
                       RSI_BLE_RESP_QUERY_ATT_DESC   *uQryDescList = rsp;
                       RSI_DPRINT(RSI_PL13,"NumberOfAttributes: %d\n",uQryDescList->NumberOfAttributes);
                      for (ii = 0; ii < uQryDescList->NumberOfAttributes; ii++)
                      {
                           RSI_DPRINT(RSI_PL13,"Handle: %02x\n",*(UINT16*)uQryDescList->AttributeDescriptor[ii].Handle);
                          print_uuid(&uQryDescList->AttributeDescriptor[ii].AttributeTypeUUID);
                      }
#endif
	              }
                  break;
             
             case RSI_BLE_RSP_QUERY_ATT_VALUE:
                  {
#ifdef RSI_DEBUG_PRINT
                       RSI_BLE_RESP_QUERY_ATT_VALUE   *uQryAttVal = rsp;
					   RSI_DPRINT(RSI_PL13,"NumberOfValues:%d\n", uQryAttVal->NumberOfValues);
                       RSI_DPRINT(RSI_PL13,"Value:\n");
                      for (ii = 0; ii < uQryAttVal->NumberOfValues; ii++)
                      {
                           RSI_DPRINT(RSI_PL13,"%02x ", uQryAttVal->AttributeValues[ii]);
                      }
                       RSI_DPRINT(RSI_PL13,"\n");
#endif
	              }
                  break;
             
             case RSI_BLE_RSP_QUERY_MULTIPLE_ATT_VALUES:
                  {
#ifdef RSI_DEBUG_PRINT    
                       RSI_BLE_RESP_QUERY_MULTIPLE_ATT_VALUES  *uQryAttVals = rsp;
                       RSI_DPRINT(RSI_PL3,"NumberOfValues:%d\n", uQryAttVals->NumberOfValues);
                       RSI_DPRINT(RSI_PL13,"Value:\n");
                      for (ii = 0; ii < uQryAttVals->NumberOfValues; ii++)
                      {
                           RSI_DPRINT(RSI_PL13,"%02x ", uQryAttVals->AttributeValues[ii]);
                      }
                       RSI_DPRINT(RSI_PL3,"\n");
#endif
	              }
                  break;
             
             case RSI_BLE_RSP_QUERY_LONG_ATT_VALUE:
                  {
#ifdef RSI_DEBUG_PRINT                
                       RSI_BLE_RESP_QUERY_LONG_ATT_VALUE   *uQryLongAttVal = rsp;
                       RSI_DPRINT(RSI_PL13,"NumberOfValues:%d\n", uQryLongAttVal->NumberOfValues);
                       RSI_DPRINT(RSI_PL13,"Long Value:\n");
                      for (ii = 0; ii < uQryLongAttVal->NumberOfValues; ii++)
                      {
                           RSI_DPRINT(RSI_PL13,"%02x ", uQryLongAttVal->LongAttValue[ii]);
                      }
                       RSI_DPRINT(RSI_PL3,"\n");
#endif
	              }
                  break;

             case RSI_BLE_RSP_SET_ATT_VALUE:
                  break;
             
             case RSI_BLE_RSP_SET_ATT_VALUE_NO_ACK:
                  break;

             case RSI_BLE_RSP_SET_LONG_ATT_VALUE:
                  break;
             
             case RSI_BLE_RSP_SET_PREPARE_LONG_ATT_VALUE:
                  break;

             case RSI_BLE_RSP_EXECUTE_LONG_ATT_VALUE_WRITE:
                  break;

								case RSI_BT_RSP_INIT :
#ifdef RSI_DEBUG_PRINT
												 RSI_DPRINT(RSI_PL3,"Received init Response\n");
#endif
												break;
								case RSI_BT_RSP_DEINIT :
#ifdef RSI_DEBUG_PRINT
											 RSI_DPRINT(RSI_PL3,"Received deinit Response\n");
#endif
												break;
             case RSI_BLE_RSP_ADD_SERVICE:
                  {
                     RSI_BLE_RESP_ADD_GATT_SERVICE  *uQryAddservice = rsp;                  

                     if (uQryAddservice->StartHndl == 0x0a) {
                         dbg_add_serv_resp.ServiceHndlerPtr = uQryAddservice->ServiceHndlerPtr;
                         dbg_add_serv_resp.StartHndl        = uQryAddservice->StartHndl;

                        // RSI_DPRINT(RSI_PL3,"service handler: 0x%08x\r\n", (UINT32)dbg_add_serv_resp.ServiceHndlerPtr);
                        // RSI_DPRINT(RSI_PL3,"start handle   : 0x%04x\r\n", dbg_add_serv_resp.StartHndl);

                     } else if (uQryAddservice->StartHndl == 0x0e) {
                         dbg_add_serv_resp1.ServiceHndlerPtr = uQryAddservice->ServiceHndlerPtr;
                         dbg_add_serv_resp1.StartHndl        = uQryAddservice->StartHndl;

                        // RSI_DPRINT(RSI_PL3,"service handler: 0x%08x\r\n", (UINT32)dbg_add_serv_resp1.ServiceHndlerPtr);
                        // RSI_DPRINT(RSI_PL3,"start handle   : 0x%04x\r\n", dbg_add_serv_resp1.StartHndl);
                     }

                  }
                  break;

             case RSI_BLE_RSP_ADD_ATTRIBUTE:
                  break;
             
             case RSI_BLE_RSP_SET_LOCAL_ATT_VALUE:
#ifdef RSI_DEBUG_PRINT
                  RSI_DPRINT (RSI_PL13, "SET_LOCAL_ATT_VALUE resp\r\n");
#endif
                  break;

             case RSI_BLE_RSP_GET_LOCAL_ATT_VALUE:
                  {
                      RSI_BLE_RESP_GET_LOCAL_ATT_VALUE  *uqrylocalattcalue = rsp;
#ifdef RSI_DEBUG_PRINT
                      RSI_DPRINT (RSI_PL3, "GET_LOCAL_ATT_VALUE resp: handle: 0x%x\r\n", uqrylocalattcalue->Hndl);
#endif
                      for (ix = 0; ix < uqrylocalattcalue->DataLen; ix++ ) {
#ifdef RSI_DEBUG_PRINT
                          RSI_DPRINT (RSI_PL3, "0x%02x, ", uqrylocalattcalue->Data[ix] );
#endif
                      }
#ifdef RSI_DEBUG_PRINT
                      RSI_DPRINT (RSI_PL3, "\r\n");
#endif

                  }
                  break;

             case RSI_BT_EVT_DISCONNECTED:
#ifdef RSI_DEBUG_PRINT
                 RSI_DPRINT(RSI_PL13,"\nDisconnect Event\n");
#endif
                  remove_connected_devices (rsp, 6);
                  break;
  
                  
             case RSI_BLE_EVENT_ADVERTISE_REPORT:
    
#ifdef RSI_DEBUG_PRINT
				  for (ix = 0; ix <= 10; ix++) {
                      RSI_DPRINT(RSI_PL3,"%02x, ", ((UINT08 *)rsp)[ix]);
                  }
#endif
                  if (status == 0) {
                      update_scan_resp (rsp, 57);
                  }
#ifdef FSM_BASED_BLE_APP
				          rsi_ble_init_struct(RSI_BLE_REQ_CONNECT);
#endif				  
                  break;
        
             case RSI_BLE_EVENT_CONNECTION_STATUS:
             {
            	 //uint8 *pckt = rsp;
                  if (status == 0) {
                      update_connected_devices (rsp, 8);
                  }
#ifdef FSM_BASED_BLE_APP
#ifdef RSI_DEBUG_PRINT
                  RSI_DPRINT(RSI_PL13,"\n### BT CONN ##\n");
                  //RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %s %02x-%02x-%02x-%02x-%02x-%02x\n","BLE","Rx","BLE conn event","Connected with :",pckt[1],pckt[2],pckt[3],pckt[4],pckt[5],pckt[6]);
				  for (ix = 0; ix <= 10; ix++) {
                      RSI_DPRINT(RSI_PL13,"%02x, ", ((UINT08 *)rsp)[ix]);
                  }

#endif
#ifdef PWR_SAVE
#ifdef RSI_DEBUG_PRINT
                  RSI_DPRINT(RSI_PL0,"\n Enable powerSave\n");
#endif
                  rsi_set_bt_or_zb_sleep_mode(RSI_CONNECTED_SLEEP);
#endif
#ifdef LINUX_PLATFORM
            sleep(2);
#endif
#ifdef  RSI_BLE_MASTER
                    if (status == 0) {
                      rsi_ble_init_struct(RSI_BLE_REQ_QUERY_PROFILES_LIST);
                    }
#endif				  
#endif				  
                  break;
             }
             case RSI_BLE_EVENT_SMP_REQUEST:
                  break;
                
             case RSI_BLE_EVENT_SMP_RESPONSE:
                  break;
                
             case RSI_BLE_EVENT_SMP_PASSKEY:
                  break;

             case RSI_BLE_EVENT_SMP_PASSKEY_DISPLAY:
                  {
#ifdef RSI_DEBUG_PRINT
                    RSI_DPRINT(RSI_PL13,"RSI_BLE_EVENT_SMP_PASSKEY_DISPLAY");

                    RSI_BT_EVENT_SMP_PASSKEY_DISPLAY *uPasskeyDisplay = rsp;

                    RSI_DPRINT(RSI_PL13,"BDAddress:");
                    RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %s %02x-%02x-%02x-%02x-%02x-%02x\n","BLE","Rx","SMP Passkey Display Event","From BD Addr: ", \
                        uPasskeyDisplay->BDAddress[5],uPasskeyDisplay->BDAddress[4],uPasskeyDisplay->BDAddress[3],uPasskeyDisplay->BDAddress[2],uPasskeyDisplay->BDAddress[1],uPasskeyDisplay->BDAddress[0]);
                    RSI_DPRINT(RSI_PL3,"SMP Pass key:%s\n", uPasskeyDisplay->PasskeyStr);
#endif
                  }
                  break;
             case RSI_BLE_EVENT_SMP_FAILED:
                  break;
             case RSI_BLE_EVENT_ENCRYPT_ENABLED:
                  {
#ifdef RSI_DEBUG_PRINT
                    RSI_DPRINT(RSI_PL13,"RSI_BLE_EVENT_ENCRYPT_ENABLED");
#endif
                  }
                  break;

             case RSI_BLE_EVENT_GATT_WRITE_VALUE:
                  {
#ifdef RSI_DEBUG_PRINT
                        RSI_BLE_EVENT_GATT_WRITE *uWriteValue = rsp;
						RSI_DPRINT(RSI_PL13,"BDAddress:");
 RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %s %02x-%02x-%02x-%02x-%02x-%02x\n","BLE","Rx","Write Event","From BD Addr: ", \
 uWriteValue->BDAddress[0],uWriteValue->BDAddress[1],uWriteValue->BDAddress[2],uWriteValue->BDAddress[3],uWriteValue->BDAddress[4],uWriteValue->BDAddress[5]);
                       for (ii = 0; ii < 6; ii++) {
                            RSI_DPRINT(RSI_PL13,"%02x-", uWriteValue->BDAddress[ii]);
                       }
                        RSI_DPRINT(RSI_PL13,"\b\r\n");
RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %s","","","","Data:"); 

                        RSI_DPRINT(RSI_PL13,"Handle:0x%02x\n",*(UINT16 *) uWriteValue->Handle);
                        RSI_DPRINT(RSI_PL13,"NumberOfValues:%d\n", uWriteValue->Length);
                        RSI_DPRINT(RSI_PL13,"Long Value:\n");
                       for (ii = 0; ii < uWriteValue->Length; ii++)
                       {
                            RSI_DPRINT(RSI_PL3,"%02x ", uWriteValue->Value[ii]);
                       }
                        RSI_DPRINT(RSI_PL3,"\n");
#endif
	              }
                  break;

             case RSI_BLE_EVENT_MTU_SIZE_VALUE:
                  {
#ifdef RSI_DEBUG_PRINT
                  RSI_DPRINT(RSI_PL13,"RSI_BLE_EVENT_MTU_SIZE");
                  
                  RSI_BLE_EVENT_MTU_SIZE *uMTUSize = rsp;

                  RSI_DPRINT(RSI_PL13,"BDAddress:");
                  RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %s %02x-%02x-%02x-%02x-%02x-%02x\n","BLE","Rx","MTU size Event","From BD Addr: ", \
                      uMTUSize->BDAddress[0],uMTUSize->BDAddress[1],uMTUSize->BDAddress[2],uMTUSize->BDAddress[3],uMTUSize->BDAddress[4],uMTUSize->BDAddress[5]);
                  RSI_DPRINT(RSI_PL3,"MTUSize:0x%02x\n",*(UINT16 *) uMTUSize->MTU_size);

#endif
	              }
                  break;
                  
             /*case  RSI_BLE_EVENT_PXPR_LINK_LOSS_ALERT:
                    {
                         RSI_BLE_EVENT_PXP_LINKLOSS *uLinkLoss = rsp;
                          RSI_DPRINT(RSI_PL3,"PXP Link loss alert: %d\n", uLinkLoss->LinkLossAlert);
                    }
                    break;

             case  RSI_BLE_EVENT_PXPR_IMMEDIATE_ALERT:
			       {
                       RSI_BLE_EVENT_PXP_IMM_ALERT *uImmAlert = rsp;
                        RSI_DPRINT(RSI_PL3,"PXP immeditate alert: %d\n", uImmAlert->ImmAlert);
                   }
                   break;

             case  RSI_BLE_EVENT_PXPR_LINK_IS_LOST:
                   break;*/
                
             default:
#ifdef RSI_DEBUG_PRINT
			     RSI_DPRINT(RSI_PL3,"undefine case: 0x%04x\r\n", rsp_type);
#endif
				break;
    }
}

int8 ble_asciihex2num(int8 ascii_hex_in)
{
	if((ascii_hex_in >= '0') && (ascii_hex_in <= '9'))
		return (ascii_hex_in - '0');
	if((ascii_hex_in >= 'A') && (ascii_hex_in <= 'F'))
		return (ascii_hex_in - 'A' + 10);
	if((ascii_hex_in >= 'a') && (ascii_hex_in <= 'f'))		
		return (ascii_hex_in - 'a' + 10);
	
	return 0;
}
/*=============================================================================*/
/**
 * @fn		  int8 rsi_ble_charHex2Dec ( uint8 *cBuf)
 * @brief	  Convert given ASCII hex notation to descimal notation (used for mac address)
 * @param[in]	  int8 *cBuf, ASCII hex notation string
 * @return	  value in integer
 */
int8 rsi_ble_charHex2Dec ( int8 *cBuf)
{
	int8 k=0;
	uint8 i;
	for(i=0;i<strlen((char*)cBuf);i++)
	 {
		k = ((k*16) + ble_asciihex2num(cBuf[i])); 
     }
	 return k;
}	 

/*=============================================================================*/
/**
 * @fn			void rsi_asciiMacAddressTo6Bytesrev(uint8 *hexAddr, int8 *asciiMacAddress)
 * @brief		Convert an ASCII : notation MAC address to a 6-byte hex address
 * @param[in		int8 *asciiMacFormatAddress, source address to convert, must be a null terminated string
 * @param[out]		uint8 *hexAddr, converted address is returned here 
 * @return		none
 */
void rsi_asciiMacAddressTo6Bytesrev(UINT08 *hexAddr, INT08 *asciiMacAddress)
{
  UINT08			i;						// loop counter
  UINT08		cBufPos;					// which char in the ASCII representation
  UINT08			byteNum;					// which byte in the 32BitHexAddress
  INT08			cBuf[6];					// temporary buffer

  byteNum = 5;
  cBufPos = 0;
  for (i = 0; i < strlen((char *)asciiMacAddress); i++) {
    // this will take care of the first 5 octets
    if (asciiMacAddress[i] == ':') {					// we are at the end of the address octet
      cBuf[cBufPos] = 0;						// terminate the string
      cBufPos = 0;							// reset for the next char
      hexAddr[byteNum--] = (UINT08)rsi_ble_charHex2Dec((INT08 *)cBuf);	// convert the strint to an integer
    }
    else {
      cBuf[cBufPos++] = asciiMacAddress[i];
    }
  }
  // handle the last octet						// we are at the end of the string with no .
  cBuf[cBufPos] = 0x00;							// terminate the string
  hexAddr[byteNum] = (UINT08)rsi_ble_charHex2Dec((INT08 *)cBuf);		// convert the strint to an integer
}


