
#include "rsi_bt_generic.h"
#include "rsi_bt_app.h"
#include "rsi_bt_api.h"
#include "rsi_bt_config.h"
#include "rsi_app_util.h"
#include "rsi_lib_util.h"
#include "rsi_hal.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

//#pragma pack(1)
#include "rsi_bt_global.h"
char *bt_commands_str[] =
{
  "SET_LOCAL_NAME",
  "GET_LOCAL_NAME",
  "SET_LOCAL_COD",
  "GET_LOCAL_COD",
  "GET_RSSI",     
  "GET_LINK_QUALITY",                         
  "GET_LOCAL_BDADDR",

  "SET_PROFILE_MODE",

  "SET_DISCOVERY_MODE",
  "GET_DISCOVERY_MODE",      
  "SET_CONN_MODE",          
  "GET_CONN_MODE",
  "SET_PAIR_MODE",          
  "GET_PAIR_MODE",
  "REMOTE_NAME_REQ",
  "REMOTE_NAME_REQ_CANCEL",
  "INQUIRY",
  "INQUIRY_CANCEL",
  "BOND",
  "BOND_CANCEL",
  "UNBOND",
  "SET_PIN_TYPE",
  "GET_PIN_TYPE",
  "USER_CONFIRMATION",
  "PASSKEY_REPLY",
  "USER_PINCODE",
  "GET_DEV_ROLE",
  "SET_DEV_ROLE",

  "GET_SERVICES",
  "SEARCH_SERVICES",

  "SPP_CONNECT",
  "SPP_DISCONNECT",
  "SPP_TX",

  "INIT",
  "DEINIT",
  "LINKKEY_REPLY",
  "ANTENNA_TX_POWER_LEVEL",
  "SET_EIR_DATA",
  "SET_SNIFF_MODE",
  "EXIT_SNIFF_MODE"

};

char *bt_events_str[] = 
{
  "ROLE_CHANGE_STATUS",
  "RSI_BT_EVT_UNBOND_STATUS",
  "RSI_BT_EVT_BOND_RESPONSE",
  "RSI_BT_EVT_INQUIRY_RESPONSE",
  "RSI_BT_EVT_REMOTE_DEVICE_NAME",
  "RSI_BT_EVT_REMOTE_NAME_REQUEST_CANCEL",
  "RSI_BT_EVT_DISCONNECTED",
  "RSI_BT_EVT_USER_CONFIRMATION_REQUEST",
  "RSI_BT_EVT_USER_PASKEY_DISPLAY",
  "RSI_BT_EVT_USER_PINCODE_REQUEST",
  "RSI_BT_EVT_USER_PASSKEY_REQUEST",
  "RSI_BT_EVT_INQUIRY_COMPLETE",
  "RSI_BT_EVT_AUTH_COMPLETE",
  "RSI_BT_EVT_USER_LINKKEY_REQUEST",
  "RSI_BT_EVT_USER_LINKKEY_SAVE",


  "RSI_BT_EVT_SPP_RECEIVE ",
  "RSI_BT_EVT_SPP_CONNECTED",
  "RSI_BT_EVT_SPP_DISCONNECTED"
};


INT16 bt_print_options(void)
{
#ifndef BT_MENU_SKIP
    UINT16 ii = 0;
    UINT16 max_cmds = RSI_BT_RSP_SPP_TRANSFER  - RSI_BT_RSP_SET_LOCAL_NAME + 8;  
    int in_cmd;

    for  (ii = 0; ii < max_cmds; ii++)
    {
        if((strcmp (bt_commands_str[ii], "GET_LINK_QUALITY")) && \
            (strcmp (bt_commands_str[ii], "SET_PAIR_MODE")) && \
            (strcmp (bt_commands_str[ii], "GET_PAIR_MODE")) && \
            (strcmp (bt_commands_str[ii], "USER_CONFIRMATION")) && \
            (strcmp (bt_commands_str[ii], "PASSKEY_REPLY")) && \
            (strcmp (bt_commands_str[ii], "SET_DEV_ROLE")) )

        RSI_DPRINT(RSI_PL0," %d. %s\n",ii+1, bt_commands_str[ii]);
    }
    RSI_DPRINT(RSI_PL0,"\n");
    RSI_DPRINT(RSI_PL0,"Read the packet from recv queue... \n=========================\n");
    RSI_DPRINT(RSI_PL0," %d. READ RESPONSE....\n", (ii+1));
    RSI_DPRINT(RSI_PL0,"Enter your choice:\n");
    scanf("%d",&in_cmd);
    if (in_cmd > max_cmds)
    {
        in_cmd = -1;
    }

    return (INT16)in_cmd;
#else
	return 1;
#endif	
}

INT16 rsi_bt_app(void)
{
				INT16 cmd;
				INT16 RetVal = 0;

				cmd = bt_print_options();

				if ((cmd > 0) && (cmd < 34))
				{
								RSI_DPRINT(RSI_PL0,"Executing the command %s\n",bt_commands_str[cmd -1]);
								RetVal = rsi_bt_init_struct(cmd);
				}
				else if (cmd == 34)
				{
								RSI_DPRINT(RSI_PL0,"Executing the command %s\n",bt_commands_str[33]);
								RetVal = rsi_bt_init_struct(RSI_BT_REQ_INIT);
				}
				else if (cmd == 35)
				{
								RSI_DPRINT(RSI_PL0,"Executing the command %s\n",bt_commands_str[34]);
								RetVal = rsi_bt_init_struct(RSI_BT_REQ_DEINIT);
				}
				else if (cmd == 36)
				{
								RSI_DPRINT(RSI_PL0,"Executing the command %s\n",bt_commands_str[35]);
								RetVal = rsi_bt_init_struct(RSI_BT_REQ_LINKEKY_REPLY);
				}
				else if (cmd == 37)
				{
								RSI_DPRINT(RSI_PL0,"Executing the command %s\n",bt_commands_str[36]);
								RetVal = rsi_bt_init_struct(RSI_BT_SET_ANTENNA_TX_POWER_LEVEL);
				}
				else if (cmd == 38)
				{
								RSI_DPRINT(RSI_PL0,"Executing the command %s\n",bt_commands_str[37]);
								RetVal = rsi_bt_init_struct(RSI_BT_SET_EIR_DATA);
				}
				else if (cmd == 39)
				{
								RSI_DPRINT(RSI_PL0,"Executing the command %s\n",bt_commands_str[38]);
								RetVal = rsi_bt_init_struct(RSI_BT_REQ_START_SNIFF_MODE);
				}
				else if (cmd == 40)
				{
								RSI_DPRINT(RSI_PL0,"Executing the command %s\n",bt_commands_str[39]);
								RetVal = rsi_bt_init_struct(RSI_BT_REQ_STOP_SNIFF_MODE);
				}
				else
								RSI_DPRINT(RSI_PL0,"Waiting for events ...\n");
 
        return RetVal;
}



void rsi_bt_decode_rsp(UINT16 rsp_type, UINT16 status, void *rsp)
{

  RSI_DPRINT(RSI_PL0,"Received response type: 0x%04X, status:%02x\n", rsp_type, status);
  /*if ( (rsp_type >= RSI_BT_RSP_SET_LOCAL_NAME) && (rsp_type <= RSI_BT_RSP_SPP_TRANSFER))
  {
    RSI_DPRINT(RSI_PL0,"Received response type: %s, status:%02x\n", bt_commands_str[rsp_type - 1], status);
  }
  else if ( (rsp_type >= RSI_BT_EVT_ROLE_CHANGE_STATUS) && (rsp_type <= RSI_BT_EVT_SPP_DISCONNECTED) )
  {
    RSI_DPRINT(RSI_PL0,"Received event type: %s, status:%02x\n", bt_events_str[rsp_type - RSI_BT_EVT_ROLE_CHANGE_STATUS], status);
  }*/

  switch (rsp_type)
  {
    case RSI_BT_RSP_CARD_READY:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_CARD_READY");
      break;

    case RSI_BT_RSP_SET_LOCAL_NAME:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_SET_LOCAL_NAME");
      break;

    case RSI_BT_RSP_QUERY_LOCAL_NAME:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_QUERY_LOCAL_NAME: %s", ((UINT08 *)rsp + 1));

      break;

    case RSI_BT_RSP_SET_LOCAL_COD:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_SET_LOCAL_COD:");
      break;

    case RSI_BT_RSP_QUERY_LOCAL_COD:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_SET_LOCAL_COD: 0x%x", *((UINT32 *) rsp));
      break;

    case RSI_BT_RSP_QUERY_RSSI:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_QUERY_RSSI: 0x%02x", *((UINT08 *) rsp));
      break;

    case RSI_BT_RSP_QUERY_LINK_QUALITY:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_QUERY_LINK_QUALITY: %d", *((UINT08 *) rsp));
      break;

    case RSI_BT_RSP_QUERY_LOCAL_BD_ADDRESS:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_QUERY_LOCAL_BD_ADDRESS: ");
      {  
        INT08  ix;

        for (ix = 5; ix >= 0; ix--) {
          printf ("%02x", ((UINT08 *)rsp)[ix]);
          if(ix > 0)
            RSI_DPRINT(RSI_PL0,"-");
        }
        printf ("\n");
      }
      break;

    case RSI_BT_RSP_SET_PROFILE_MODE:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_SET_PROFILE_MODE: ");
      break;

    case RSI_BT_RSP_SET_DISCV_MODE:
      RSI_DPRINT(RSI_PL0,"RSI_BT_RSP_SET_DISCV_MODE: ");
      break;

    case RSI_BT_RSP_QUERY_DISCOVERY_MODE:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_QUERY_DISCOVERY_MODE: %d\r\n", ((UINT08 *)rsp)[0]);
      break;

    case RSI_BT_RSP_SET_CONNECTABILITY_MODE:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_SET_CONNECTABILITY_MODE: ");
      break;

    case RSI_BT_RSP_QUERY_CONNECTABILITY_MODE:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_QUERY_CONNECTABILITY_MODE: %d\r\n", ((UINT08 *)rsp)[0]);
      break;

    case RSI_BT_RSP_SET_PAIR_MODE:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_QUERY_CONNECTABILITY_MODE: ");
      break;

    case RSI_BT_RSP_QUERY_PAIR_MODE:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_QUERY_PAIR_MODE: %d\r\n", ((UINT08 *)rsp)[0]);
      break;

    case RSI_BT_RSP_REMOTE_NAME_REQUEST:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_REMOTE_NAME_REQUEST:\r\n");
      break;

    case RSI_BT_RSP_REMOTE_NAME_REQUEST_CANCEL:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_REMOTE_NAME_REQUEST_CANCEL: \r\n");
      break;

    case RSI_BT_RSP_INQUIRY:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_INQUIRY: \r\n");
      break;

    case RSI_BT_RSP_INQUIRY_CANCEL:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_INQUIRY_CANCEL: \r\n");
      break;

    case RSI_BT_RSP_BOND:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_BOND: \r\n");
      break;

    case RSI_BT_RSP_BOND_CANCEL:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_BOND_CANCEL: \r\n");
      break;

    case RSI_BT_RSP_UNBOND:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_UNBOND: \r\n");
      {
        INT08  ix;

        for (ix = 5; ix >= 0; ix--) {
          printf ("%02x", ((UINT08 *)rsp)[ix]);
          if(ix > 0)
            RSI_DPRINT(RSI_PL0,"-");
        }
        printf ("\n");
      }
      break;

    case RSI_BT_RSP_SET_PIN_TYPE:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_SET_PIN_TYPE: \r\n");
      break;

    case RSI_BT_RSP_QUERY_PIN_TYPE:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_QUERY_PIN_TYPE: %d\r\n", ((UINT08 *)rsp)[0]);
      break;

    case RSI_BT_RSP_USER_CONFIRMATION:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_USER_CONFIRMATION: \r\n");
      break;

    case RSI_BT_RSP_PASSKEY_REPLY:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_PASSKEY_REPLY: \r\n");
      break;

    case RSI_BT_RSP_PINCODE_REPLY:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_PINCODE_REPLY: \r\n");
      break;

    case RSI_BT_RSP_QUERY_ROLE:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_QUERY_ROLE:%d \r\n",((UINT08 *)rsp)[0]);
      break;

    case RSI_BT_RSP_SET_ROLE:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_SET_ROLE: \r\n");
      break;

    case RSI_BT_RSP_QUERY_SERVICES:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_QUERY_SERVICES: \r\n");
      {
        UINT08                       ix;
        RSI_BT_RESP_QUERY_SERVICES  *p_ser;

        p_ser = (RSI_BT_RESP_QUERY_SERVICES *)rsp;
        printf ("NbrServices: %d, uuids: ",p_ser->NbrServices);
        for (ix = 0; ix < p_ser->NbrServices; ix++) {
          printf ("0x%04x, ", (int32)p_ser->uuid[ix]);
        }
      }
      break;

    case RSI_BT_RSP_SEARCH_SERVICE:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_SEARCH_SERVICE: \r\n");
      break;

    case RSI_BT_RSP_SPP_CONNECT:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_SPP_CONNECT: \r\n");
      {
        INT08  ix;

       for (ix = 5; ix >= 0; ix--) {
          printf ("%02x", ((UINT08 *)rsp)[ix]);
          if(ix > 0)
            RSI_DPRINT(RSI_PL0,"-");
        }
        printf ("\n");
      }
      break;

    case RSI_BT_RSP_SPP_DISCONNECT:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_SPP_DISCONNECT: \r\n");
      {
        INT08  ix;
        for (ix = 5; ix >= 0; ix--) {
          printf ("%02x", ((UINT08 *)rsp)[ix]);
          if(ix > 0)
            RSI_DPRINT(RSI_PL0,"-");
        }
        printf ("\n");
      }
      break;

    case RSI_BT_RSP_SPP_TRANSFER:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_RSP_SPP_TRANSFER \r\n");
      break;

      /* events list */
    case RSI_BT_EVT_ROLE_CHANGE_STATUS:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_EVT_ROLE_CHANGE_STATUS: \r\n");
      {
        INT08  ix;
        for (ix = 5; ix >= 0; ix--) {
          printf ("%02x", ((UINT08 *)rsp)[ix]);
          if(ix > 0)
            RSI_DPRINT(RSI_PL0,"-");
        }
        printf ("\n");   
      }
      break;

    case RSI_BT_EVT_UNBOND_STATUS:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_EVT_UNBOND_STATUS: \r\n");
      {
        INT08  ix;
        for (ix = 5; ix >= 0; ix--) {
          printf ("%02x", ((UINT08 *)rsp)[ix]);
          if(ix > 0)
            RSI_DPRINT(RSI_PL0,"-");
        }
        printf ("\n");
      }
      break;

    case RSI_BT_EVT_BOND_RESPONSE:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_EVT_BOND_RESPONSE: \r\n");
      {
        INT08  ix;
        for (ix = 5; ix >= 0; ix--) {
          printf ("%02x", ((UINT08 *)rsp)[ix]);
          if(ix > 0)
            RSI_DPRINT(RSI_PL0,"-");
        }
        printf ("\n");
      }
      break;

    case RSI_BT_EVT_INQUIRY_RESPONSE:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_EVT_INQUIRY_RESPONSE: \r\n");
      {
        RSI_BT_EVENT_INQUIRY_RESPONSE *p_inq_resp;
        INT08  ix;

        p_inq_resp = (RSI_BT_EVENT_INQUIRY_RESPONSE *)rsp;
       
       for (ix = 5; ix >= 0; ix--) {
          printf ("%02x", ((UINT08 *)p_inq_resp->BDAddress)[ix]);
          if(ix > 0)
            RSI_DPRINT(RSI_PL0,"-");
        }
        printf ("\n"); 
        printf ("\r\nName: %s", p_inq_resp->RemoteDeviceName);
      }
      break;

//    case RSI_BT_EVT_INQUIRY_COMPLETE:
//      RSI_DPRINT(RSI_PL0,"RSI_BT_EVT_INQUIRY_COMPLETE: \r\n");
//      break;

    case RSI_BT_EVT_REMOTE_DEVICE_NAME:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_EVT_REMOTE_DEVICE_NAME: \r\n");
      {
        RSI_BT_EVENT_REMOTE_DEVICE_NAME *p_rmt_name;
        INT08  ix;

        p_rmt_name = (RSI_BT_EVENT_REMOTE_DEVICE_NAME *)rsp;
        
        for (ix = 5; ix >= 0; ix--) {
          printf ("%02x", ((UINT08 *)p_rmt_name->BDAddress)[ix]);
          if(ix > 0)
            RSI_DPRINT(RSI_PL0,"-");
        }
        
        printf ("\n");

        printf ("\r\nlen: %d, Name: %s", p_rmt_name->NameLength, p_rmt_name->RemoteDeviceName);
      }
      break;

    case RSI_BT_EVT_REMOTE_NAME_REQUEST_CANCEL:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_EVT_REMOTE_NAME_REQUEST_CANCEL: \r\n");
      break;

    case RSI_BT_EVT_DISCONNECTED:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_EVT_DISCONNECTED: \r\n");
      break;

    case RSI_BT_EVT_USER_CONFIRMATION_REQUEST:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_EVT_USER_CONFIRMATION_REQUEST: \r\n");
      break;

    case RSI_BT_EVT_USER_PASKEY_DISPLAY:
    case RSI_BT_EVT_USER_PASKEY_NOTIFY:
      {
        RSI_BT_EVENT_USER_PASKEY_DISPLAY  *p_passkey;
        p_passkey = (RSI_BT_EVENT_USER_PASKEY_DISPLAY *)rsp;
        RSI_DPRINT(RSI_PL0,"\nRSI_BT_EVT_USER_PASKEY_DISPLAY: passkey: %d \r\n", *((UINT32 *)p_passkey->Passkey));
      }
      break;

    case RSI_BT_EVT_USER_PINCODE_REQUEST:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_EVT_USER_PINCODE_REQUEST: \r\n");
      {
        RSI_BT_EVENT_USER_PINCODE_REQUEST *p_pincode;
        INT08  ix;

        p_pincode = (RSI_BT_EVENT_USER_PINCODE_REQUEST *)rsp;
       
        for (ix = 5; ix >= 0; ix--) {
          printf ("%02x", ((UINT08 *)p_pincode->BDAddress)[ix]);
          if(ix > 0)
            RSI_DPRINT(RSI_PL0,"-");
        }
        printf ("\n");
        
        memcpy(rsi_bt_AppControlBlock.RemoteBDAddress, p_pincode->BDAddress, RSI_BT_BD_ADDR_LEN);
      }
      break;

    case RSI_BT_EVT_USER_LINKKEY_REQUEST:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_EVT_USER_LINKKEY_REQUEST: \r\n");
      {
        RSI_BT_EVENT_USER_LINKKEY_REQUEST *p_linkkey;
        INT08  ix;

        p_linkkey = (RSI_BT_EVENT_USER_LINKKEY_REQUEST *)rsp;

        for (ix = 5; ix >= 0; ix--) {
          printf ("%02x", ((UINT08 *)p_linkkey->BDAddress)[ix]);
          if(ix > 0)
            RSI_DPRINT(RSI_PL0,"-");
        }
        printf ("\n");

        memcpy(rsi_bt_AppControlBlock.RemoteBDAddress, p_linkkey->BDAddress, RSI_BT_BD_ADDR_LEN);
      }
      break;

    case RSI_BT_EVT_USER_LINKKEY_SAVE:
      RSI_DPRINT(RSI_PL0,"RSI_BT_EVT_USER_LINKKEY_SAVE: \r\n");
      {
        RSI_BT_EVENT_USER_LINKKEY_SAVE *p_linkkey_save;
        INT08  ix;

        p_linkkey_save = (RSI_BT_EVENT_USER_LINKKEY_SAVE *)rsp;

        for (ix = 5; ix >= 0; ix--) {
          printf ("%02x", ((UINT08 *)p_linkkey_save->BDAddress)[ix]);
          if(ix > 0)
            RSI_DPRINT(RSI_PL0,"-");
        }
        printf ("\n");

        for (ix = 0; ix < 16; ix++) {
          printf ("%02x", ((UINT08 *)p_linkkey_save->LinkKey)[ix]);
          if(ix > 0)
            RSI_DPRINT(RSI_PL0," ");
        }
        printf ("\n");
        /* Only one entry is saved here, to let the user understand the usage. 
		 * User can write his own algorithm to save as many entries as per his requirement. 
		 */
        memcpy(rsi_bt_AppControlBlock.RemoteBDAddress, p_linkkey_save->BDAddress, RSI_BT_BD_ADDR_LEN);
        memcpy(rsi_bt_AppControlBlock.RemoteLinkKey, p_linkkey_save->LinkKey, RSI_BT_LINK_KEY_LEN);
      }
      break;

    case RSI_BT_EVT_USER_PASSKEY_REQUEST:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_EVT_USER_PASSKEY_REQUEST: \r\n");
      break;

    case RSI_BT_EVT_INQ_COMPLETE:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_EVT_USER_INQ_COMPLETE: \r\n");
      break;

    case RSI_BT_EVT_AUTH_COMPLETE:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_EVT_USER_AUTH_COMPLETE: \r\n");
      break;

    case RSI_BT_EVT_SPP_RECEIVE:
      RSI_DPRINT(RSI_PL0,"\nRSI_BT_EVT_SPP_RECEIVE: \r\n");
      {
        RSI_BT_EVENT_SPP_RECEIVE  *p_spp_rx = rsp;
       /* UINT16  len; */

        /*len = *((UINT16 *)rsp);
        ((UINT08 *)rsp)[len + 2] = 0;
        printf ("len: %d, data: %s", len, &((UINT08 *)rsp)[2]);*/

        p_spp_rx->Data[(p_spp_rx->DataLen)] = 0;
    //   printf ("len: %d, data: %s", *(p_spp_rx->DataLen), p_spp_rx->Data);
      printf ("len: %d, data: %s", (p_spp_rx->DataLen), p_spp_rx->Data);
      }
      break;

    case RSI_BT_EVT_SPP_CONNECTED:
      RSI_DPRINT(RSI_PL0,"RSI_BT_EVT_SPP_CONNECTED: \r\n");
      {
        RSI_BT_EVENT_SPP_CONNECTED *p_conn;
        INT08  ix;

        p_conn = (RSI_BT_EVENT_SPP_CONNECTED *)rsp;
        for (ix = 5; ix >= 0; ix--) {
          printf ("%02x", ((UINT08 *)p_conn->BDAddress)[ix]);
          if(ix > 0)
            RSI_DPRINT(RSI_PL0,"-");
        }
        printf ("\n");
      }
      break;

    case RSI_BT_EVT_SPP_DISCONNECTED:
      RSI_DPRINT(RSI_PL0,"RSI_BT_EVT_SPP_DISCONNECTED: \r\n");
      {
        RSI_BT_EVENT_SPP_DISCONNECTED *p_disconn;
        INT08  ix;

        p_disconn = (RSI_BT_EVENT_SPP_DISCONNECTED *)rsp;
        for (ix = 5; ix >= 0; ix--) {
          printf ("%02x", ((UINT08 *)p_disconn->BDAddress)[ix]);
          if(ix > 0)
            RSI_DPRINT(RSI_PL0,"-");
        }
        printf ("\n");
      }
      break;

    case RSI_BT_RSP_INIT:
      RSI_DPRINT(RSI_PL0,"RSI_BT_RSP_INIT: \r\n");
      break;
     
    case RSI_BT_RSP_DEINIT:
      RSI_DPRINT(RSI_PL0,"RSI_BT_RSP_DEINIT: \r\n");
      break;

    case RSI_BT_RSP_PER_STATS:
      //RSI_DPRINT(RSI_PL0,"RSI_BT_PER_RSP: \r\n");
      {
        RSI_BT_RESP_PER_STATS *p_per_stats;
        INT08  ix;

        p_per_stats =  (RSI_BT_RESP_PER_STATS *)rsp;

	//printf("%10d %10d %10d    %10d\n",p_per_stats->crc_fail,p_per_stats->crc_pass,p_per_stats->Tx_dones,p_per_stats->RSSI);
	//printf("%8d %8d %8d    %8d\n",*(uint16*)&rsp[0],*(uint16*)&rsp[2],*(uint16*)&rsp[18],*(int16*)&rsp[16]);
      }
      break;
      
    case RSI_BT_RSP_START_SNIFF_MODE:
      RSI_DPRINT(RSI_PL0,"RSI_BT_RSP_START_SNIFF_MODE: \r\n");
      break;
      
    case RSI_BT_RSP_STOP_SNIFF_MODE:
      RSI_DPRINT(RSI_PL0,"RSI_BT_RSP_STOP_SNIFF_MODE: \r\n");
      break;
    
    case RSI_BT_RSP_SNIFF_SUBRATING_MODE:
      RSI_DPRINT(RSI_PL0,"RSI_BT_RSP_SNIFF_SUBRATING_MODE: \r\n");
      break;
      
    case RSI_BT_RSP_SSP_ENABLE:
      RSI_DPRINT(RSI_PL0,"RSI_BT_RSP_SSP_ENABLE: \r\n");
      break;
    
    case RSI_BT_EVT_SSP_COMPLETE:
      //RSI_BT_EVENT_SSP_COMPLETE
      RSI_DPRINT(RSI_PL0,"RSI_BT_EVT_SSP_COMPLETE: \r\n");
      break;
    
    case RSI_BT_EVT_MODE_CHANGE:
      //RSI_BT_EVENT_MODE_CHANGE
      RSI_DPRINT(RSI_PL0,"RSI_BT_EVT_MODE_CHANGE: \r\n");
      break;
    
    case RSI_BT_EVT_SNIFF_SUBRATING_CHANGED:
      //RSI_BT_EVENT_SNIFF_SUBRATING
      RSI_DPRINT(RSI_PL0,"RSI_BT_EVT_SNIFF_SUBRATING_CHANGED: \r\n");
      break;
    
    case RSI_BT_RSP_ANTENNA_TX_POWER_LEVEL:
      RSI_DPRINT(RSI_PL0,"RSI_BT_RSP_ANTENNA_TX_POWER_LEVEL: \r\n");
      break;

    case RSI_BT_RSP_EIR_DATA:
      RSI_DPRINT(RSI_PL0,"RSI_BT_RSP_EIR_DATA: \r\n");
      break;
    default:
      printf ("undefined event\r\n");
  }
}

