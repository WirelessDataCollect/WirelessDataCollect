/**
 * @file     rsi_wifi_init.c
 * Copyright(C) 2013 Redpine Signals Inc.
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief MAIN: Top level file, execution begins here
 *
 * @section Description
 * This file contains the entry point for the application. It also has the 
 * initialization of parameters of the global structure and the operations to 
 * control & configure the module, like scanning networks, joining to an Access Point etc.
 */  

/**
 * Include files
 */ 
#include "rsi_global.h"
#include "rsi_config.h"
#include "rsi_app_util.h"
#include "rsi_spi_cmd.h"
#include "rsi_app.h"
#include "rsi_api.h"
#if JSON_LOAD
#include "sensor_data.h"
#endif
#ifndef LINUX_PLATFORM
rsi_app_cb_t            rsi_app_cb;
#else
rsi_app_cb_t            rsi_app_cb = 
{
#if (RSI_POWER_MODE == RSI_POWER_MODE_3)
  .ps_ok_to_send = 1
#endif
};
#endif

#if    (ENTERPRISE_MODE || (CLIENT_MODE && SSL_SUPPORT))
#include "../../../../apis/wlan/ref_apps/include/wifiuser.pem"
#include "../../../../apis/wlan/ref_apps/include/testuser.pac"
#include "../../../../apis/wlan/ref_apps/include/cacert.pem"
#include "../../../../apis/wlan/ref_apps/include/clientcert.pem"
#include "../../../../apis/wlan/ref_apps/include/clientkey.pem"
#include "../../../../apis/wlan/ref_apps/include/servercert.pem"
#include "../../../../apis/wlan/ref_apps/include/serverkey.pem"
#endif

#if FIPS_MODE_ENABLE
#include "rsi_fips.h"
#endif
#ifdef COEX_APP_CHANGES
#include "rsi_scheduler.h"
void rsi_set_wlan_sleep_mode(UINT32 mode);
void rsi_set_bt_or_zb_sleep_mode(UINT32 mode);
  

uint8 rsi_raw_data_pkt[500] = {0xec,0x1a,0x59,0xb2,0x80,0x5d,
								0x00,0x23,0xa7,0x91,0x91,0x91,
								0x08,0x00,0x12,0xea,
                       0x7f,0x66,0xc0,0x00,0x00,0x00,0x01,0x00,
                       0x00,0x00};
uint32 data_txed[1];
extern UINT8 wlan_joined;
#endif

#if !RSI_TCP_IP_BYPASS
#if WEB_PAGE_LOAD 
/* Webpage to be loaded */
uint8 index_htm[] = 
#include "sample_webpage.txt"
;
#endif

#if WEBPAGE_BYPASS_SUPPORT
uint8 host_webpage[] = 
#include "host_webpage.txt"
;
#endif
#endif



#if (FW_UPGRADE || RSI_ENABLE_UPGRADATION_FROM_HOST)
#if (RSI_UPGRADE_IMAGE_TYPE == RSI_UPGRADE_IMAGE_I_FW )
uint32 fw_image[] = {
#include "../../../../apis/wlan/ref_apps/src/wlan_rps_file"
};
#else
uint32 fw_image[] = {
#include "../../../../apis/wlan/ref_apps/src/bl_rps_file"
};
#endif
#endif

#if RSI_ENABLE_UPGRADATION_FROM_HOST
uint32 fw_image_size = sizeof(fw_image);
uint32 rps_offset = 0;
#endif



rsi_uCmdRsp *rsi_parse_response(uint8 *rsp);
uint8 *rsi_wrapper_to_rsp(uint8 *rsp, uint8 rsp_type);
void  rsi_receive_data_packet(uint8 *payloadPtr, uint16 pkt_lenth);
rsi_uConnected_station_t stations_connected[RSI_NO_OF_CLIENTS_SUPPORTED];



/*=================================================*/
/**
 * @fn          rsi_uCmdRsp *rsi_parse_response(uint8 *rsp)
 * @brief       To parse the resposne received from Kernel
 * @param[in]   uint8 *rsp, response buffer pointer
 * @param[out]  none
 * @return      rsi_uCmdRsp *ptr, response pointer
 * @section description 
 * This API is used to parse the recieved response. This returns the 
 * pointer which points to rsptype, status, response payload in order.
 */
rsi_uCmdRsp *rsi_parse_response(uint8 *rsp)
{
  rsi_uCmdRsp             *temp_uCmdRspPtr = NULL;
  uint16                  temp_rspCode;
  uint16                  temp_status;
  uint8                   *descPtr = rsp ;
  uint8                   *payloadPtr = rsp + RSI_FRAME_DESC_LEN;
#ifdef RSI_DEBUG_PRINT
  uint8 i;
#endif

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL13,"Recieved Packet PRINT3 \n");
#endif
  /* Check whether it is any rxpkt or just a status indication */
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL13,"Recieved Packet PRINT4 \n");
#endif

  /* In Response received First 24 bytes are header.
   * And then Desc and Payload of the response is present.
   * 2nd byte of the Desc is status and 14th byte of the Desc is RspType.
   */

  /* Retrieve response code from the received packet */
  temp_status  = rsi_bytes2R_to_uint16(descPtr + RSI_STATUS_OFFSET);
  temp_rspCode = rsi_bytes2R_to_uint16(descPtr + RSI_RSP_TYPE_OFFSET);

#ifdef RSI_DEBUG_PRINT
  for(i=0;i<16;i++)
  {
    RSI_DPRINT(RSI_PL13,"received rspcode: 0x%x \n",descPtr[i]);

  }
#endif    

  if(temp_rspCode)
  {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL13,"received status : 0x%x \n",temp_status);
    RSI_DPRINT(RSI_PL13,"received rspcode: 0x%x \n",temp_rspCode);
#endif    
  }
  else
  {
    /* call data receive function */
    rsi_receive_data_packet(payloadPtr, (*(uint16 *)rsp & 0xfff));

  }
  /* this function does re arrange of the reponse 
     for the responses where the response structures are padded in between */
  if(!temp_status)
  {
    rsp = rsi_wrapper_to_rsp(rsp, temp_rspCode);  
  }

  /* Copy the response type and status to payloadPtr-4, payloadPtr-2
   * locations respectively.
   */
  rsi_uint16_to_2bytes((payloadPtr - 2), temp_status);
  rsi_uint16_to_2bytes((payloadPtr - 4), temp_rspCode);

  temp_uCmdRspPtr = (rsi_uCmdRsp *)(payloadPtr - 4);

  return temp_uCmdRspPtr;
}


/*=================================================*/
/**
 * @fn          uint8 *rsi_wrapper_to_rsp(uint8 *rsp, uint8 rsp_type)
 * @brief       To rearrange the response in response structure
 * @param[in]   uint8 *rsp, response buffer pointer
 * @param[in]   uint8 rsp_type, response type
 * @param[out]  none
 * @return      uint8 *ptr, response pointer
 * @section description 
 * This API is used to rearrange the response in the response structures when 
 * response bytes are shifted because of padding bytes added between the members
 * of the response structure.
 */
uint8 *rsi_wrapper_to_rsp(uint8 *rsp, uint8 rsp_type)
{
  uint8 *descPtr, *payloadPtr, *temp_payloadPtr;
  uint8 sec[10];
  uint8 ii,i, scanInfo_size;
  rsi_wfdDevResponse wfdDevResp;
  rsi_scanResponse scanRsp;
#if (RSI_POWER_MODE == RSI_POWER_MODE_3)
  int16 retval = 0;
#endif

#if RSI_POWER_MODE
#ifdef RSI_DEBUG_PRINT
  static uint8 sleep_count = 0;
#endif
#endif
  descPtr = rsp;

  switch(rsp_type)
  {

#if (RSI_POWER_MODE == RSI_POWER_MODE_3)
    case RSI_RSP_SLP:
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL13,"SLP%d\n",sleep_count++);
#endif
      do
      {
        retval = rsi_execute_cmd((uint8 *)rsi_sleepack,0,0);
      }while(retval == BUFFER_FULL_FAILURE);
      rsi_app_cb.ps_ok_to_send = 0;
      break;

    case RSI_RSP_WKP:
      rsi_app_cb.ps_ok_to_send = 1;
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL13,"WKP\n");
#endif
      if (rsi_app_cb.ps_pkt_pending)
      {
        do
        {
          retval = rsi_execute_cmd(rsi_app_cb.ps_descparam, 
              rsi_app_cb.ps_pkt_pending, rsi_app_cb.ps_size_param);
        }while(retval == BUFFER_FULL_FAILURE);
        rsi_app_cb.ps_pkt_pending = 0;
      }
      break;
#endif

    case RSI_RESP_WFD_DEV:
      memset(&wfdDevResp,0,sizeof(rsi_wfdDevResponse));
      descPtr = rsp ;
      temp_payloadPtr = payloadPtr = descPtr + RSI_FRAME_DESC_LEN;
      wfdDevResp.devCount = (descPtr[0] | ((descPtr[1] & 0x0f) << 8))/41;
      /* 1 byte(devState) + 32 byte(devName) + 6 byte(macAddress) + 2 byte (devtype)*/

      for(ii=0; ii< wfdDevResp.devCount; ii++)
      {
        wfdDevResp.strWfdDevInfo[ii].devState = *(payloadPtr);
        payloadPtr += 1;
        memcpy(wfdDevResp.strWfdDevInfo[ii].devName, payloadPtr, 32);
        payloadPtr += 32;
        memcpy(wfdDevResp.strWfdDevInfo[ii].macAddress, payloadPtr, 6);
        payloadPtr += 6;
        memcpy(wfdDevResp.strWfdDevInfo[ii].devtype, payloadPtr, 2);
        payloadPtr += 2;
      }

      memcpy(temp_payloadPtr, (uint8 *)&wfdDevResp, sizeof(rsi_wfdDevResponse));
      break;

#if RSI_INSTANT_BG
    case RSI_RSP_BG_SCAN:
#endif
    case RSI_RSP_SCAN:
      scanInfo_size = 46;
      /* 1 + 1 + 1 + 1 + 34 + 6 + 1 + 1 = 46 (sizeof scaninfo structure without padding bytes */
      memset(&scanRsp,0,sizeof(rsi_scanResponse));
      descPtr = rsp;
      temp_payloadPtr = payloadPtr = descPtr + RSI_FRAME_DESC_LEN;
      scanRsp.scanCount[0] = *(payloadPtr);
      if(scanRsp.scanCount[0] != 0)
      {
        payloadPtr += 8; /* move to  (scan count + reserved bytes) */

        for(ii=0; ii< scanRsp.scanCount[0]; ii++)
        {
          memcpy(&scanRsp.strScanInfo[ii], payloadPtr, scanInfo_size);
          payloadPtr += scanInfo_size;
        }
        memcpy(temp_payloadPtr, (uint8 *)&scanRsp, sizeof(rsi_scanResponse));
      }
      //scan results print
      RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","WLAN","Rx","Scan Rsp","Scan Done");
      RSI_DPRINT(RSI_PL3,"\t  --------------------------------------------------- \n");
	  RSI_DPRINT(RSI_PL3,"\t  %-22.20s%-9.8s %-10.10s  %-7.7s \n","   SSID  ","Chnl No.","Security","RSSI");
      RSI_DPRINT(RSI_PL3,"\t  --------------------------------------------------- \n");
      for(i=0; i< scanRsp.scanCount[0]; i++)
      {
      	rsi_memcpy(sec,"\0\0\0\0\0\0\0\0\0\0",10);
    	  if(scanRsp.strScanInfo[i].securityMode==0)
    		  rsi_memcpy(sec,"OPEN",4);
    	  else if(scanRsp.strScanInfo[i].securityMode==1)
			  rsi_memcpy(sec,"WPA",3);
    	  else if(scanRsp.strScanInfo[i].securityMode==2)
    	  	  rsi_memcpy(sec,"WPA2",4);
    	  else if(scanRsp.strScanInfo[i].securityMode==3)
    	  	  rsi_memcpy(sec,"WEP",3);
    	  else if(scanRsp.strScanInfo[i].securityMode==4)
    	  	  rsi_memcpy(sec,"EAP-WPA",7);
    	  else if(scanRsp.strScanInfo[i].securityMode==5)
    	  	  rsi_memcpy(sec,"EAP-WPA2",8);
    	 else
    	  	  rsi_memcpy(sec,"UNKNOWN",9);

    	  if(strlen((const char *)scanRsp.strScanInfo[i].ssid)!= 0)
    	  RSI_DPRINT(RSI_PL3,"\t  %-25.20s%-7.2d %-10.8s %-7.2d \n",scanRsp.strScanInfo[i].ssid,scanRsp.strScanInfo[i].rfChannel,sec,scanRsp.strScanInfo[i].rssiVal);
      }
      RSI_DPRINT(RSI_PL3,"\t  --------------------------------------------------- \n");
      break;
    default:
      break;
  }

  return rsp;
}

/*=================================================*/
/**
 * @fn          void rsi_receive_data_packet(uint8 *rx_pkt_payload, uint16 pkt_length)
 * @brief       To receive data packet
 * @param[in]   uint8 *rx_pkt_payload, received packet payload
 * @param[in]   uint16 pkt_length,length of the received packet
 * @param[out]  none
 * @return      none
 * @section description 
 * This API is used to receive data packet from WIFI module
 */
void rsi_receive_data_packet(uint8 *rx_pkt_payload, uint16 pkt_length)
{
  rsi_app_cb.rcvd_data_pkt_count++;
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL13,"pkt %d received \n",rsi_app_cb.rcvd_data_pkt_count);
#endif    
#ifdef LINUX_PLATFORM
  //measure_throughput(pkt_length, 1);
#endif

}


/*====================================================*/
/**
 * @fn          int16 rsi_wlan_app_event(uint8 *buffer)
 * @brief       Common function for all the commands.
 * @param[in]   uint8 *buffer,buffer points to the wlan pkt received from the module.
 * @return      none
 * @section description 
 * This function is used to process a pkt command from the module in coex mode.
 */

int16 rsi_wlan_app_event(uint8 *buffer)
{
  int16 retval=0;
  uint16 response_type = 0;
  uint8 wificonf_done = 0, index = 0 , wfd_dev_found = 0;
  rsi_wfdDevInfo   *ptrStrWfdDevInfo;
  uint8 i;
#if SNMP_SUPPORT
  int snmp_len = 0;
#endif
  uint32      bytes_sent = 0;

  
  
#if(ENTERPRISE_MODE ||(CLIENT_MODE && SSL_SUPPORT))
uint8 certificate_type = 1;
#endif
  
  rsi_app_cb.uCmdRspFrame = rsi_parse_response(buffer);
  
  /* Retrieve response code from the received packet */
  response_type           = rsi_bytes2R_to_uint16(rsi_app_cb.uCmdRspFrame->rspCode);
  rsi_app_cb.error_code = rsi_bytes2R_to_uint16(rsi_app_cb.uCmdRspFrame->status);

  /* Switch between type of packet received */
  switch (response_type)
  {
    case RSI_RSP_CARD_READY:                                    
      if(!rsi_app_cb.error_code)
      {
#ifdef RSI_DEBUG_PRINT
        RSI_DPRINT(RSI_PL13, "Card ready passed !\n");
        RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","WLAN","Rx","Card ready","Card Ready Received");
#endif
        retval = rsi_oper_mode((rsi_uOperMode *)RSI_FILL_PARAMETERS(RSI_REQ_OPERMODE, &rsi_app_cb.send_buffer[0]));        
      }
      else
      {
        return -1;
      }
      break;

#if ENABLE_USER_STORE_CONFIGURATION
    case RSI_RSP_USER_STORE_CFG:
      if(!rsi_app_cb.error_code)
      {
#ifdef RSI_DEBUG_PRINT
        RSI_DPRINT(RSI_PL0, "Opermode Pased!\n");
#endif
#if (WEB_PAGE_LOAD && !RSI_TCP_IP_BYPASS)
#ifdef RSI_DEBUG_PRINT
        RSI_DPRINT(RSI_PL0, "Sending Clear Files Command\n");
#endif
        retval = rsi_webpage_clear_files((rsi_tfs_clear_files_t *)RSI_FILL_PARAMETERS(RSI_REQ_CLEAR_FILES, &rsi_app_cb.send_buffer[0]));        
#else
#ifdef RSI_DEBUG_PRINT
        RSI_DPRINT(RSI_PL13, "Sending FW Version Query\n");
#endif
        retval = rsi_query_fw_version();
#endif /* WEB_PAGE_LOAD */
      }
      else
      {
        return -1;
      }
      break;
#endif

#if RSI_DEBUG_PRINTS_ENABLE
    case RSI_RSP_DEBUG_PRINTS:
      if(!rsi_app_cb.error_code)
      {
#if ENTERPRISE_MODE
        if(EAP_CERTIFICATE_TYPE == RSI_EAP_TLS_CERTIFICATE)
        {
          /* If Enterprise mode , send the Certificate load command */
          retval = rsi_set_certificate(EAP_CERTIFICATE_TYPE, static_cert,sizeof(static_cert) - 1,&rsi_app_cb.set_chunks);
        }
        else
        {
          /* If Enterprise mode , send the Certificate load command */
          retval = rsi_set_certificate(EAP_CERTIFICATE_TYPE, testuser_pac, sizeof(testuser_pac) - 1,&rsi_app_cb.set_chunks);
        }
#else
        retval = rsi_oper_mode((rsi_uOperMode *)RSI_FILL_PARAMETERS(RSI_REQ_OPERMODE, &rsi_app_cb.send_buffer[0]));        
#endif
      }
      else
      {
        return -1;
      }
      break;
#endif

    case RSI_RSP_OPERMODE:
      /*If opermode command response is success */
      if(!rsi_app_cb.error_code)    
      {
#if RSI_NO_WLAN_MODE
        return 1;
#endif
#ifdef RSI_WLAN_DEEPSLP_DBG
        rsi_set_wlan_sleep_mode(RSI_DEEP_SLEEP);
        return 1;
#endif

#ifdef RSI_DEBUG_PRINT
       RSI_DPRINT(RSI_PL13, "Opermode Pased!\n");
       RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","WLAN","Rx","Operating Mode Rsp","Success");
#endif
#if RSI_LOAD_FWUPGRADATION_KEY
        retval = rsi_load_fwupgradation_key((rsi_ufwupgradation_key *)RSI_FILL_PARAMETERS(RSI_REQ_LOAD_FWUPGRADATION_KEY, &rsi_app.cb.send_buffer[0]));
#endif
#if RSI_DEBUG_PRINTS_ENABLE
        retval = rsi_debug_prints((rsi_uDebug *)RSI_FILL_PARAMETERS(RSI_REQ_DEBUG_PRINTS, &rsi_app_cb.send_buffer[0]));        
        break;
#endif
#if ENTERPRISE_MODE
        if(EAP_CERTIFICATE_TYPE == RSI_EAP_TLS_CERTIFICATE)
        {
          /* If Enterprise mode , send the Certificate load command */
          retval = rsi_set_certificate(EAP_CERTIFICATE_TYPE, wifiuser, sizeof(wifiuser) - 1,&rsi_app_cb.set_chunks);
        }
        else
        {
          /* If Enterprise mode , send the Certificate load command */
          retval = rsi_set_certificate(EAP_CERTIFICATE_TYPE, testuser_pac, sizeof(testuser_pac) - 1,&rsi_app_cb.set_chunks);
        }
#elif(CLIENT_MODE && SSL_SUPPORT)
        retval = rsi_set_certificate(RSI_SSL_CLIENT_CERTIFICATE, clientcert, sizeof(clientcert)-1, &rsi_app_cb.set_chunks);

#else
#if ENABLE_USER_STORE_CONFIGURATION
        retval = rsi_user_store_config((rsi_user_store_config_t *)RSI_FILL_PARAMETERS(RSI_REQ_USER_STORE_CFG, &rsi_app_cb.send_buffer[0]));        
        break;
#endif

#if (WEB_PAGE_LOAD && !RSI_TCP_IP_BYPASS)
#ifdef RSI_DEBUG_PRINT
        RSI_DPRINT(RSI_PL0, "Sending Clear Files Command\n");
#endif
        retval = rsi_webpage_clear_files((rsi_tfs_clear_files_t *)RSI_FILL_PARAMETERS(RSI_REQ_CLEAR_FILES, &rsi_app_cb.send_buffer[0]));        
#else
#ifdef RSI_DEBUG_PRINT
        RSI_DPRINT(RSI_PL13, "Sending FW Version Query\n");
#endif
        retval = rsi_band(RSI_BAND);

#endif /* WEB_PAGE_LOAD */
#endif

      }
      /*If opermode command fails */
      else
      {
#ifdef RSI_DEBUG_PRINT
        RSI_DPRINT(RSI_PL13, "Failed!");
        RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","WLAN","Rx","Operating Mode Rsp","Failed");
#endif
        return -1;
      }
      break;
#if RSI_LOAD_FWUPGRADATION_KEY 
    case RSI_RSP_LOAD_FWUPGRADATION_KEY:
      {
        if(!rsi_app_cb.error_code)    
        {
#if RSI_DEBUG_PRINTS_ENABLE
          retval = rsi_debug_prints((rsi_uDebug *)RSI_FILL_PARAMETERS(RSI_REQ_DEBUG_PRINTS, &rsi_app_cb.send_buffer[0]));        
          break;
#endif
#if ENTERPRISE_MODE
          if(EAP_CERTIFICATE_TYPE == RSI_EAP_TLS_CERTIFICATE)
          {
            /* If Enterprise mode , send the Certificate load command */
            retval = rsi_set_certificate(EAP_CERTIFICATE_TYPE, wifiuser, sizeof(wifiuser) - 1,&rsi_app_cb.set_chunks);
          }
          else
          {
            /* If Enterprise mode , send the Certificate load command */
            retval = rsi_set_certificate(EAP_CERTIFICATE_TYPE, testuser_pac, sizeof(testuser_pac) - 1,&rsi_app_cb.set_chunks);
          }
#elif(CLIENT_MODE && SSL_SUPPORT)
          retval = rsi_set_certificate(RSI_SSL_CLIENT_CERTIFICATE, clientcert, sizeof(clientcert)-1, &rsi_app_cb.set_chunks);

#else
#if ENABLE_USER_STORE_CONFIGURATION
          retval = rsi_user_store_config((rsi_user_store_config_t *)RSI_FILL_PARAMETERS(RSI_REQ_USER_STORE_CFG, &rsi_app_cb.send_buffer[0]));        
          break;
#endif

#if (WEB_PAGE_LOAD && !RSI_TCP_IP_BYPASS)
#ifdef RSI_DEBUG_PRINT
          RSI_DPRINT(RSI_PL0, "Sending Clear Files Command\n");
#endif
          retval = rsi_webpage_clear_files((rsi_tfs_clear_files_t *)RSI_FILL_PARAMETERS(RSI_REQ_CLEAR_FILES, &rsi_app_cb.send_buffer[0]));        
#else
#ifdef RSI_DEBUG_PRINT
          RSI_DPRINT(RSI_PL13, "Sending FW Version Query\n");
#endif
          retval = rsi_query_fw_version();
#endif /* WEB_PAGE_LOAD */
#endif


        }
        /*If opermode command fails */
        else
        {
#ifdef RSI_DEBUG_PRINT
          RSI_DPRINT(RSI_PL0, "Failed!");
#endif
          return -1;
        }
      }
      break;
#endif
    case RSI_RSP_FWVERSION_QUERY:
      /*If Firmware Version query command is success */
      if(!rsi_app_cb.error_code)
      {
#if (JSON_LOAD && !RSI_TCP_IP_BYPASS)
        /* Check if the webpage has associated JSON data */
        if (WEB_PAGE_HAS_JSON) 
        {
          /* True: JSON needs to be loaded into the firmware! */
          memset(rsi_app_cb.json_buffer, 0, JSON_BUFFER_SIZE);
          sensor_data_init(&rsi_app_cb.sensor_data);
          sensor_data_stringify(rsi_app_cb.json_buffer, &rsi_app_cb.sensor_data);
          retval = rsi_json_create((rsi_jsonCreateObject_t *)RSI_FILL_PARAMETERS(RSI_REQ_CREATE_JSON, &rsi_app_cb.send_buffer[0]), rsi_app_cb.json_buffer, &rsi_app_cb.json_load_done);
        }
        else 
#endif
        {

          /* False: Proceed with band */
          retval = rsi_band(RSI_BAND);
        }
      }
      /*If Firmware Version query command if fail*/
      else
      {
        return -1;
      }
      break;    

    case RSI_RSP_BAND:
      /*If Band command response is success */
      if(!rsi_app_cb.error_code)
      {
      	RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","WLAN","Rx","Band Rsp","Success");
#if RSI_ENABLE_REJOIN_PARAMS
        /*send the Rejoin Params command*/
        retval = rsi_rejoin_params((rsi_rejoin_params_t *)RSI_FILL_PARAMETERS(RSI_REQ_REJOIN_PARAMS, &rsi_app_cb.send_buffer[0]));        
        break;
#endif
#if RSI_ENABLE_UPGRADATION_FROM_HOST
        retval = rsi_fwup_frm_host(((rsi_fw_up_t *)&rsi_app_cb.send_buffer[0]), (uint8 *)fw_image, rps_offset, RSI_RPS_HEADER,FW_UP_REQ);
        rps_offset = RSI_RPS_HEADER;
        fw_image_size -= RSI_RPS_HEADER;
        break;
#endif
        /*send the Init command*/
        retval = rsi_init();                   

      }
      /*If Band command is failed*/
      else
      {
      	RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %s - %d\n","WLAN","Rx","Band Rsp","Failure",rsi_app_cb.error_code);
        return -1;
      }
      break;
#if RSI_ENABLE_UPGRADATION_FROM_HOST
    case RSI_RSP_FW_UP_REQ:
      {
        if(rsi_app_cb.error_code == RSI_FW_UP_SUCCESS)
        { 
          fw_image_size = 0;
          rps_offset = 0;
#if RSI_ENABLE_REJOIN_PARAMS
          /*send the Rejoin Params command*/
          retval = rsi_rejoin_params((rsi_rejoin_params_t *)RSI_FILL_PARAMETERS(RSI_REQ_REJOIN_PARAMS, &rsi_app_cb.send_buffer[0]));        
          break;
#endif
          /*send the Init command*/
          retval = rsi_init();                   
        }
        else if((!rsi_app_cb.error_code))
        {
          if(fw_image_size < RSI_RPS_PAYLOAD_LEN)
          {
            retval = rsi_fwup_frm_host(((rsi_fw_up_t *)&rsi_app_cb.send_buffer[0]),(uint8 *)fw_image,rps_offset,fw_image_size,FW_UP_PL);
            fw_image_size = 0;
            rps_offset = 0;
          }
          else
          {
            retval = rsi_fwup_frm_host(((rsi_fw_up_t *)&rsi_app_cb.send_buffer[0]), (uint8 *)fw_image, rps_offset, RSI_RPS_PAYLOAD_LEN,FW_UP_REQ);

            fw_image_size -= RSI_RPS_PAYLOAD_LEN;
          }
          rps_offset += RSI_RPS_PAYLOAD_LEN;

        }
        else 
        {
          return -1;
        }
      }
      break;
#endif
    case RSI_RSP_INIT:
      /*If Init command response is success */
      if(!rsi_app_cb.error_code)
      {
        RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","WLAN","Rx","Init Rsp","Init Done");
        memcpy(rsi_app_cb.mac_addr, rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.initResponse.macAddress1, 6);
#if ((RSI_POWER_MODE == RSI_POWER_MODE_8) || (RSI_POWER_MODE == RSI_POWER_MODE_9))
          rsi_set_wlan_sleep_mode(RSI_DEEP_SLEEP);
          break;
#endif


#if SET_REGION_SUPPORT
        retval = rsi_set_region((rsi_usetregion *)RSI_FILL_PARAMETERS(RSI_REQ_SET_REG_CODE, &rsi_app_cb.send_buffer[0]));         
        break;

#elif SET_REGION_AP_SUPPORT
        retval = rsi_set_region_ap((rsi_usetregion_ap_t *)RSI_FILL_PARAMETERS(RSI_REQ_SET_REG_AP, &rsi_app_cb.send_buffer[0]));         
        break;
#endif
#if P2P_MODE
        /*If P2p Mode , send the p2p Configure command*/
        retval = rsi_p2p_config((rsi_uConfigP2p *)RSI_FILL_PARAMETERS(RSI_REQ_CFG_P2P, &rsi_app_cb.send_buffer[0]));        
#elif CLIENT_MODE
#if RSI_PSK_SUPPORT
        retval = rsi_psk((rsi_uPsk *)RSI_FILL_PARAMETERS(RSI_REQ_HOST_PSK, &rsi_app_cb.send_buffer[0]));        
#else
        rsi_set_wlan_sleep_mode(RSI_ACTIVE);
        /*If legacy client mode ,send PSK*/
        retval = rsi_scan((rsi_uScan *)RSI_FILL_PARAMETERS(RSI_REQ_SCAN, &rsi_app_cb.send_buffer[0]));        
#endif
#elif ENTERPRISE_MODE  
        /* If Enterprise mode , send the EAP command */
        retval = rsi_set_eap((rsi_uSetEap *)RSI_FILL_PARAMETERS(RSI_REQ_SET_EAP_CFG, &rsi_app_cb.send_buffer[0]));        
#else
        /* If AP mode , send the AP Config / IP Config command.
           We are not giving IPconfig here. So, AP will be created with Default IP
           of 192.168.100.76 */
        retval = rsi_set_ap_config((rsi_apconfig *)RSI_FILL_PARAMETERS(RSI_REQ_APCONFIG, &rsi_app_cb.send_buffer[0]));        
#endif
      }
      /*If Init command is failed*/
      else
      {
      	RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %s - %d\n","WLAN","Rx","Init Rsp","Failure",rsi_app_cb.error_code);
        return -1;
      }
      break;

#if SET_REGION_SUPPORT
    case RSI_RSP_SET_REG_CODE:
      {
        if(!rsi_app_cb.error_code)
        {
#if P2P_MODE
          /*If P2p Mode , send the p2p Configure command*/
          retval = rsi_p2p_config((rsi_uConfigP2p *)RSI_FILL_PARAMETERS(RSI_REQ_CFG_P2P, &rsi_app_cb.send_buffer[0]));        
#elif CLIENT_MODE
          /*If legacy client mode ,send the scan command*/
          retval = rsi_scan((rsi_uScan *)RSI_FILL_PARAMETERS(RSI_REQ_SCAN, &rsi_app_cb.send_buffer[0]));        

#elif ENTERPRISE_MODE
          /* If Enterprise mode , send the EAP command */
          retval = rsi_set_eap((rsi_uSetEap *)RSI_FILL_PARAMETERS(RSI_REQ_SET_EAP_CFG, &rsi_app_cb.send_buffer[0]));        
#else
#endif
        }
        else
        {
          return -1;
        }

      }
      break;
#endif

#ifdef SET_REGION_AP_SUPPORT
    case RSI_RSP_SET_REG_AP:
      {
        if(!rsi_app_cb.error_code)
        {
#if P2P_MODE
          /*If P2p Mode , send the p2p Configure command*/
          retval = rsi_p2p_config((rsi_uConfigP2p *)RSI_FILL_PARAMETERS(RSI_REQ_CFG_P2P, &rsi_app_cb.send_buffer[0]));        
#else
          /* If AP mode , send the AP Config / IP Config command.
             We are not giving IPconfig here. So, AP will be created with Default IP
             of 192.168.100.76 */
          retval = rsi_set_ap_config((rsi_apconfig *)RSI_FILL_PARAMETERS(RSI_REQ_APCONFIG, &rsi_app_cb.send_buffer[0]));        
#endif
        }
        else
        {
          return -1;
        }
      }
      break;
#endif

#if (ENTERPRISE_MODE ||(CLIENT_MODE && SSL_SUPPORT))
    case RSI_RSP_SET_CERT:
      /* If Certificate chunk loaded  successfully */    

      if(!rsi_app_cb.error_code)
      {
        if(rsi_app_cb.set_chunks.cert_info.more_chunks ==0) /* if last chunk of certificate loaded successfully */ 
        {
#if (CLIENT_MODE && SSL_SUPPORT)
          //!The next certificate can be given
          certificate_type = rsi_app_cb.set_chunks.cert_info.CertType + 1;
#else
          retval = rsi_band(RSI_BAND);
          break;
#endif
        }
        else
        {
          certificate_type = rsi_app_cb.set_chunks.cert_info.CertType ;
        }
        switch(certificate_type)
        {
#if ENTERPRISE_MODE
          case RSI_EAP_TLS_CERTIFICATE:
            {
              retval = rsi_set_certificate(EAP_CERTIFICATE_TYPE, wifiuser, sizeof(wifiuser)-1,&rsi_app_cb.set_chunks);
            }
            break;
          case RSI_EAP_FAST_PAC_CERTIFICATE:
            {
              retval = rsi_set_certificate(EAP_CERTIFICATE_TYPE, testuser_pac, sizeof(testuser_pac) - 1,&rsi_app_cb.set_chunks);
            }
            break;
#endif
#if (CLIENT_MODE && SSL_SUPPORT)
          case RSI_SSL_CLIENT_CERTIFICATE:
            retval = rsi_set_certificate(RSI_SSL_CLIENT_CERTIFICATE,clientcert,sizeof(clientcert)-1, &rsi_app_cb.set_chunks);
            break;
          case RSI_SSL_CLIENT_PRIVATE_KEY:
            retval = rsi_set_certificate(RSI_SSL_CLIENT_PRIVATE_KEY,clientkey,sizeof(clientkey)-1, &rsi_app_cb.set_chunks);
            break;
          case RSI_SSL_CA_CERTIFICATE:
            retval = rsi_set_certificate(RSI_SSL_CA_CERTIFICATE,cacert,sizeof(cacert)-1,&rsi_app_cb.set_chunks);
            break;
          case RSI_SSL_SERVER_CERTIFICATE:
            retval = rsi_set_certificate(RSI_SSL_SERVER_CERTIFICATE,servercert,sizeof(servercert)-1, &rsi_app_cb.set_chunks);
            break;
          case RSI_SSL_SERVER_PRIVATE_KEY:
            retval = rsi_set_certificate(RSI_SSL_SERVER_PRIVATE_KEY,serverkey,sizeof(serverkey)-1, &rsi_app_cb.set_chunks);
            break;
#endif
          default:
            /* send the set band command if all the certificates being loaded*/
            retval = rsi_band(RSI_BAND);
            break;

        }

      }
      /* If certificate load command fail */
      else
      {
        return -1;
      }
      break;
#endif
    case RSI_RSP_SET_EAP_CFG:
      /* If Set eap command success */
      if(!rsi_app_cb.error_code)
      {
        retval = rsi_scan((rsi_uScan *)RSI_FILL_PARAMETERS(RSI_REQ_SCAN, &rsi_app_cb.send_buffer[0]));        
      }
      /* If set eap command fail */
      else
      {
        return -1;
      }
      break;

#if RSI_PSK_SUPPORT
    case RSI_RSP_HOST_PSK:
      /* If Set eap command success */
      if(!rsi_app_cb.error_code)
      {
      	RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","WLAN","Rx","Set PSK Rsp","Success PSK Set");
        retval = rsi_scan((rsi_uScan *)RSI_FILL_PARAMETERS(RSI_REQ_SCAN, &rsi_app_cb.send_buffer[0]));        
      }
      /* If set eap command fail */
      else
      {
      	RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %s-%d\n","WLAN","Rx","Set PSK Rsp","Failure",rsi_app_cb.error_code);
        return -1;
      }
      break;
#endif

    case RSI_RSP_SCAN:  
      /*If Scan command is success*/
      if(!rsi_app_cb.error_code)
      {
#if FIPS_MODE_ENABLE
        retval = rsi_query_config_checksum();
#else
#if RSI_WMM_PS_SUPPORT
        /* send wmm ps command */
        retval = rsi_wmm_ps((rsi_uWmmPs *)RSI_FILL_PARAMETERS(RSI_REQ_WMM_PS, &rsi_app_cb.send_buffer[0]));        
        break;
#endif
        /* send join command */

#if RSI_WPS_SUPPORT
        retval = rsi_wps_method((rsi_uWpsMethod *)RSI_FILL_PARAMETERS(RSI_REQ_WPS_METHOD, &rsi_app_cb.send_buffer[0]));                            
#else
        retval = rsi_join((rsi_uJoin *)RSI_FILL_PARAMETERS(RSI_REQ_JOIN, &rsi_app_cb.send_buffer[0]));                             
#endif
#endif
      }
      else
      {
      	RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %s-%d\n","WLAN","Rx","Scan Rsp","Failure",rsi_app_cb.error_code);
        retval = rsi_scan((rsi_uScan *)RSI_FILL_PARAMETERS(RSI_REQ_SCAN, &rsi_app_cb.send_buffer[0]));        
      }
      break;
#if FIPS_MODE_ENABLE		  
    case RSI_RSP_STORE_CFG_CKHSUM:
      if(!rsi_app_cb.error_code)
      {
        //! Give next command
      }
      else
      {
        return -1;
      }

      break;
    case RSI_RSP_FIPS_FAILURE:
      {
#ifdef ENABLE_DEBUG_PRINTS
        RSI_DPRINT(RSI_PL0,"FIPS FAILURE STATE\n");
#endif
      }
      break;
#endif
#if RSI_BG_SCAN_ENABLE
    case RSI_RSP_BG_SCAN:  
      /*If BG Scan command is success*/
      if(!rsi_app_cb.error_code)
      {
#if RSI_INSTANT_BG
        retval = rsi_bg_scan((rsi_ubgScan *)RSI_FILL_PARAMETERS(RSI_REQ_BG_SCAN,&rsi_app_cb.send_buffer[0])); 
        break;
#endif

#if RSI_ROAMING_SUPPORT 
        retval = rsi_roam_params((rsi_uRoamParams *)RSI_FILL_PARAMETERS(RSI_REQ_ROAM_PARAMS,&rsi_app_cb.send_buffer[0])); 
        break;                        
#endif
#if RSI_TCP_IP_BYPASS
        wificonf_done = 1;
        break;
#endif
      }
      else
      {                    
        return -1;
      }
      break;
#endif

    case RSI_RSP_CFG_P2P:
      /*If Config P2p Command success */
      if(!rsi_app_cb.error_code)
      {
        if(GO_INTENT_VALUE == 16)
        {
          /* send join command in  AUTO GO and Access point mode */
          retval = rsi_join((rsi_uJoin *)RSI_FILL_PARAMETERS(RSI_REQ_JOIN,&rsi_app_cb.send_buffer[0])); 
        }               
         
      }
      /* If config P2p command fail */
      else
      {
        return -1;
      }
      break;

    case RSI_RESP_WFD_DEV:
      /* If RSI module finds any WiFi-Direct Devices */
      if(!rsi_app_cb.error_code)
      {
        ptrStrWfdDevInfo = &rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.wfdDevResponse.strWfdDevInfo[0];

        for(index = 0; index < rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.wfdDevResponse.devCount;  index++,ptrStrWfdDevInfo++)
        {    
          if(!strcmp((void *)ptrStrWfdDevInfo->devName, RSI_JOIN_SSID))
          {
            wfd_dev_found = 1;
            break;
          }
        }    
        if(wfd_dev_found)                  
        {
          /* send the Join command */
          retval = rsi_join((rsi_uJoin *)RSI_FILL_PARAMETERS(RSI_REQ_JOIN,&rsi_app_cb.send_buffer[0]));                      
          wfd_dev_found = 0;
        }
      }
      else
      {
        return -1;
      }

      break;

#if AP_MODE
    case RSI_RSP_APCONFIG:
      {
        if( !rsi_app_cb.error_code) 
        {
          retval = rsi_join((rsi_uJoin *)RSI_FILL_PARAMETERS(RSI_REQ_JOIN,&rsi_app_cb.send_buffer[0]));                      

        }
        else
        {
          return -1;
        }
      }
      break;
#endif

    case RSI_RSP_P2P_CONNREQ:
      if( !rsi_app_cb.error_code) 
      {                      
        /*send the join command*/
        retval = rsi_join((rsi_uJoin *)RSI_FILL_PARAMETERS(RSI_REQ_JOIN,&rsi_app_cb.send_buffer[0]));

      }
      /*If  it is failed*/
      else
      {                    
        return -1;
      }
      break;

    case RSI_RSP_JOIN:
      /*If Join command response is success */
      if( !rsi_app_cb.error_code) 
      { 
      RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","WLAN","Rx","Join Rsp","Joined");
#ifdef COEX_APP_CHANGES
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL13,"\n#### Wifi Joined ####\n");
#endif
#ifdef WLAN_ENABLE
        wlan_joined =1;
#endif


#ifdef PWR_SAVE

#ifdef RSI_DEBUG_PRINT
        RSI_DPRINT(RSI_PL0,"\n#### Pwr Save En ####\n");
#endif
        rsi_set_wlan_sleep_mode(RSI_CONNECTED_SLEEP);
#endif
#endif
#if RSI_MULTICAST_FILTER_ENABLE
        uint8 MAC[6];
        rsi_ascii_mac_address_to_6bytes((uint8 *)MAC, RSI_MULTICAST_MAC_ADDRESS);
        retval = rsi_multicast_mac_filter(RSI_MULTICAST_MAC_CMD_TYPE, MAC);
        break;
#endif

#if RSI_BG_SCAN_ENABLE
        retval = rsi_bg_scan((rsi_ubgScan *)RSI_FILL_PARAMETERS(RSI_REQ_BG_SCAN,&rsi_app_cb.send_buffer[0])); 
        break;
#endif 
        if(rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.joinResponse.operState == 'G' )
        {
          wificonf_done = 1;
          break;
        }
        else
        {
          /*send the IP config command*/
#if !RSI_TCP_IP_BYPASS
#if IPV6_SUPPORT
          retval = rsi_ipv6_param_set((rsi_uIPconf6 *)RSI_FILL_PARAMETERS(RSI_REQ_IPCONF6,&rsi_app_cb.send_buffer[0]));
#else
          retval = rsi_ip_param_set((rsi_uIpparam *)RSI_FILL_PARAMETERS(RSI_REQ_IPPARAM_CONFIG,&rsi_app_cb.send_buffer[0]));
#endif
#else
          wificonf_done = 1;

#endif
        }

      }
      /*If Join command is failed*/
      else
      {     
	  RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %s-%d\n","WLAN","Rx","Join Rsp","Failure",rsi_app_cb.error_code);
        if(wlan_joined)
        {
#ifdef PWR_SAVE
          rsi_set_wlan_sleep_mode(RSI_ACTIVE);
#endif
          wlan_joined = 0;
        }
          retval = rsi_init();    
      }
      break;
    case RSI_RSP_CLIENT_CONNECTED:
      if(!rsi_app_cb.error_code )
      {
        uint8 temp_macaddr[6] = {0};
        for(i = 0;i < RSI_NO_OF_CLIENTS_SUPPORTED;i++)
        {
          if(!memcmp(stations_connected[i].mac_addr,&temp_macaddr,6))
          {
            memcpy(&stations_connected[i].mac_addr,&rsi_app_cb.read_packet_buffer[16],6);
            break;
          }
        }
      }
      break;
    case RSI_RSP_CLIENT_DISCONNECTED:
      if(!rsi_app_cb.error_code )
      {
        for(i = 0;i < RSI_NO_OF_CLIENTS_SUPPORTED;i++)
        {
          if(!memcmp(stations_connected[i].mac_addr,&rsi_app_cb.read_packet_buffer[16],6))
          {
            memset(&stations_connected[i].mac_addr,0,6);
            break;
          }
        }
      }
      break;
#if RSI_MULTICAST_FILTER_ENABLE
    case RSI_RSP_MULTICAST_FILTER:
      if( !rsi_app_cb.error_code) 
      {

#if RSI_BG_SCAN_ENABLE
        retval = rsi_bg_scan((rsi_ubgScan *)RSI_FILL_PARAMETERS(RSI_REQ_BG_SCAN,&rsi_app_cb.send_buffer[0]));    
        break;
#endif 
#if RSI_TCP_IP_BYPASS
        wificonf_done = 1;
        break;
#endif
#if IPV6_SUPPORT
       retval = rsi_ipv6_param_set((rsi_uIPconf6 *)RSI_FILL_PARAMETERS(RSI_REQ_IPCONF6,&rsi_app_cb.send_buffer[0]));
#else
        retval = rsi_ip_param_set((rsi_uIpparam *)RSI_FILL_PARAMETERS(RSI_REQ_IPPARAM_CONFIG,&rsi_app_cb.send_buffer[0]));
#endif
      }else
      {
        return -1;
      }
      break;
#endif

#if RSI_POWER_MODE
    case RSI_RSP_PWRMODE:
      /*If Power mode command response is success */
      if(!rsi_app_cb.error_code )
      {
        /*send the IP config command*/
#if !RSI_TCP_IP_BYPASS
#if IPV6_SUPPORT
        retval = rsi_ipv6_param_set((rsi_uIPconf6 *)RSI_FILL_PARAMETERS(RSI_REQ_IPCONF6,&rsi_app_cb.send_buffer[0]));
#else
        retval = rsi_ip_param_set((rsi_uIpparam *)RSI_FILL_PARAMETERS(RSI_REQ_IPPARAM_CONFIG,&rsi_app_cb.send_buffer[0]));
#endif
#else
        //wificonf_done = 1;
#endif

      }
      /*If Power mode command is failed*/
      else
      {                    
        return -1;
      }
      break;
#endif

#if PER_MODE
    case RSI_RSP_PER_PARAMS:
      if(!rsi_app_cb.error_code )
      {

      }
      else
      {
        return -1;
      }
      break;
#endif

    case RSI_RSP_MAC_QUERY:
      /* If MAC Query Response is success */
      if(!rsi_app_cb.error_code)
      {
        wificonf_done =1;

      }
      /* If MAC Query Response is fail */
      else
      {
        return -1;
      }    
      break;

#if RSI_ROAMING_SUPPORT
    case RSI_RSP_ROAM_PARAMS:
      if(!rsi_app_cb.error_code )
      {
        //TODO
      }
      else
      {
        return -1;
      }    
      break;
#endif

#if AP_MODE
    case RSI_RSP_AP_HT_CAPS:
      if(!rsi_app_cb.error_code )
      {
        retval = rsi_set_ap_config((rsi_apconfig *)RSI_FILL_PARAMETERS(RSI_REQ_APCONFIG, &rsi_app_cb.send_buffer[0]));        
      }
      else
      {
        return -1;
      }    
      break;
#endif

#if RSI_WMM_PS_SUPPORT
    case RSI_RSP_WMM_PS:
      if(!rsi_app_cb.error_code )
      {
#if RSI_WPS_SUPPORT
        retval = rsi_wps_method((rsi_uWpsMethod *)RSI_FILL_PARAMETERS(RSI_REQ_WPS_METHOD,&rsi_app_cb.send_buffer[0]));                      
#else
        retval = rsi_join((rsi_uJoin *)RSI_FILL_PARAMETERS(RSI_REQ_JOIN,&rsi_app_cb.send_buffer[0]));                      
#endif
      }
      else
      {
        return -1;
      }    
      break;
#endif

#if RSI_WPS_SUPPORT
    case RSI_RSP_WPS_METHOD:
      if(!rsi_app_cb.error_code )
      {
        retval = rsi_join((rsi_uJoin *)RSI_FILL_PARAMETERS(RSI_REQ_JOIN,&rsi_app_cb.send_buffer[0]));                      
      }
      else
      {
        return -1;
      }    
      break;
#endif

    case RSI_RSP_MODULE_STATE:
      {
        /*If async message  is enabled through custom bit feature select. Parse response from here*/
#ifdef ENABLE_DEBUG_PRINTS
        RSI_DPRINT(RSI_PL0,"Module status :");
        RSI_DPRINT(RSI_PL0,"Timestamp-> %d \n",*(uint32*)rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.stateFrameRcv.TimeStamp);
        RSI_DPRINT(RSI_PL0,"stateCode-> %x \n",rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.stateFrameRcv.stateCode);
        RSI_DPRINT(RSI_PL0,"ReasonCode-> %x \n",rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.stateFrameRcv.reason_code);
        RSI_DPRINT(RSI_PL0,"Channel-> %x \n",rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.stateFrameRcv.rsi_channel);
        RSI_DPRINT(RSI_PL0,"RSSI-> %x \n",rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.stateFrameRcv.rsi_rssi);
        RSI_DPRINT(RSI_PL0,"MAC-> %x,",rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.stateFrameRcv.rsi_bssid[0]);
        RSI_DPRINT(RSI_PL0," %x,",rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.stateFrameRcv.rsi_bssid[1]);
        RSI_DPRINT(RSI_PL0," %x,",rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.stateFrameRcv.rsi_bssid[2]);
        RSI_DPRINT(RSI_PL0," %x,",rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.stateFrameRcv.rsi_bssid[3]);
        RSI_DPRINT(RSI_PL0," %x,",rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.stateFrameRcv.rsi_bssid[4]);
        RSI_DPRINT(RSI_PL0," %x,",rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.stateFrameRcv.rsi_bssid[5]);
        RSI_DPRINT(RSI_PL0," \n");
#endif
      }
      break;

#if RSI_ENABLE_REJOIN_PARAMS
    case RSI_RSP_REJOIN_PARAMS:
      if(!rsi_app_cb.error_code )
      {
        /*send the Init command*/
        retval = rsi_init();        
      }else
      {
        return -1;
      }
      break;
#endif

#if !RSI_TCP_IP_BYPASS
#if WEB_PAGE_LOAD
    case RSI_RSP_CLEAR_FILES:
      /*If clear files is success */
      if(!rsi_app_cb.error_code)  
      {
#ifdef RSI_DEBUG_PRINT
        RSI_DPRINT(RSI_PL0, "Clear Files Pased!\nSending Webpage command\n");
#endif
        retval = rsi_load_web_page((rsi_uWebServer *)RSI_FILL_PARAMETERS(RSI_REQ_GET_WEBPAGE, &rsi_app_cb.send_buffer[0]),index_htm, &rsi_app_cb.webpage_load_done);                          
      }
      /*If opermode command response is fail */
      else
      {
        return -1;
      }
      break;

    case RSI_RSP_GET_WEBPAGE:
      /**/
      if (!rsi_app_cb.error_code) {
        /* Send next command */
        if (rsi_app_cb.webpage_load_done) {
          /*send the Firmware version command*/
#ifdef RSI_DEBUG_PRINT
          RSI_DPRINT(RSI_PL0, "Webpage Chunk Passed!\nSending FWVersion");
#endif
          retval = rsi_query_fw_version();
        } else {
#ifdef RSI_DEBUG_PRINT
          RSI_DPRINT(RSI_PL0, "Webpage Chunk Passed!\nSending Next Chunk");
#endif
          retval = rsi_load_web_page((rsi_uWebServer *)RSI_FILL_PARAMETERS(RSI_REQ_GET_WEBPAGE, &rsi_app_cb.send_buffer[0]), index_htm, &rsi_app_cb.webpage_load_done);                          
        }
      }
      else {
#ifdef RSI_DEBUG_PRINT
        RSI_DPRINT(RSI_PL0, "Opermode Pased!\nSending Webpage command");
#endif
        return -1;
      }
      break;
#endif

#if JSON_LOAD
    case RSI_RSP_CREATE_JSON:
      if (!rsi_app_cb.error_code) 
      {

        if (rsi_app_cb.json_load_done) 
        {

          /*send the Band command*/
#ifdef RSI_DEBUG_PRINT
          RSI_DPRINT(RSI_PL0, "JSON Chunk Passed!\nSending Band");
#endif
          retval = rsi_band(RSI_BAND);
        } 
        else
        {

#ifdef RSI_DEBUG_PRINT
          RSI_DPRINT(RSI_PL0, "JSON Chunk Passed!\nSending Next Chunk");
#endif
          retval = rsi_json_create((rsi_jsonCreateObject_t *)RSI_FILL_PARAMETERS(RSI_REQ_CREATE_JSON,&rsi_app_cb.send_buffer[0]), rsi_app_cb.json_buffer,&rsi_app_cb.json_load_done);
          
        }

      } else {
        return -1;
      }
      break;
#endif

    case RSI_RSP_IPPARAM_CONFIG:
      /*If IP config command response is success */
      if(!rsi_app_cb.error_code )
      {
      	RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %-30.25s\n","WLAN","Rx","Set IP Rsp","IP set succesfull");
#if SNMP_SUPPORT
        retval = rsi_snmp_enable(RSI_SNMP_ENABLE);
        break;
#endif
#if RSI_ROAMING_SUPPORT
        retval = rsi_roam_params((rsi_uRoamParams *)RSI_FILL_PARAMETERS(RSI_REQ_ROAM_PARAMS,&rsi_app_cb.send_buffer[0]));
        break;                        
#endif
#if RSI_ICMP_FROM_MODULE
       retval = rsi_ping_request((rsi_ping_request_t *)RSI_FILL_PARAMETERS(RSI_REQ_PING_PACKET,&rsi_app_cb.send_buffer[0]));
#endif
#if !WEBPAGE_BYPASS_SUPPORT
        wificonf_done =1;
		
         retval = rsi_socket((rsi_uSocket *)RSI_FILL_PARAMETERS(RSI_REQ_SOCKET_CREATE,&rsi_app_cb.send_buffer[0]));
#endif
      }
      /*If IP config command is failed*/
      else
      {      
	       RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %s-%d\n","WLAN","Rx","Set IP Rsp","Failure",rsi_app_cb.error_code);
         return -1;
      }
      break;



     case RSI_RSP_SOCKET_CREATE:
      if(!rsi_app_cb.error_code )
      {
      	RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %s - %d\n","WLAN","Rx","Sckt create Rsp","Socket Created ",rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.socketFrameRcv.socketDescriptor[0]);
        // send_data = 1;
        unsigned char data_buf[20];
        memcpy(data_buf,"SSL DATA TRANSFER SUCCESS",sizeof("SSL DATA TRANSFER SUCCESS") );
            retval = rsi_send_data(1,data_buf, sizeof("SSL DATA TRANSFER SUCCESS"),0, &bytes_sent);
       }
      else
      {     
	      RSI_DPRINT(RSI_PL3,"%-10.7s%-4.2s %-20.15s %s-%d\n","WLAN","Rx","Sckt create Rsp","Socket Creation Failed",rsi_app_cb.error_code);
        return -1;
      } 
     
     break;

    case RSI_RSP_SENT_BYTES:
      if(!rsi_app_cb.error_code )
      {
        //! Get number of bytes sent
      }
      else
      {                    
        return -1;
      }
      break;

#if RSI_ICMP_FROM_MODULE
    case RSI_RSP_PING_PACKET:
      if(!rsi_app_cb.error_code )
      {
        wificonf_done =1;
      }
      else
      {                    
        return -1;
      }
      break;
#endif

#if IPV6_SUPPORT
    case RSI_RSP_IPCONF6:
      /*If IPV6 config command response is success */
      if(!rsi_app_cb.error_code )
      {
        wificonf_done =1;
      }
      /*If IPV6 config command is failed*/
      else
      {                    
        return -1;
      }
      break;
#endif

#if WEBPAGE_BYPASS_SUPPORT
            case RSI_REQ_HOST_WEBPAGE:
              {
                
                retval = rsi_send_url_rsp(((HostWebpageSnd_t *)RSI_FILL_PARAMETERS(RSI_REQ_HOST_WEBPAGE,&rsi_app_cb.send_buffer[0])),&rsi_app_cb.webpage_morechunks, host_webpage, (sizeof(host_webpage) - 1), 1);
                
              }
              break;
            case RSI_RSP_HOST_WEBPAGE:
              {
                if(!rsi_app_cb.error_code )
                {
                  if(rsi_app_cb.webpage_morechunks == 0)
                  {
                  }
                  else
                  {
                     retval = rsi_send_url_rsp(((HostWebpageSnd_t *)RSI_FILL_PARAMETERS(RSI_REQ_HOST_WEBPAGE,&rsi_app_cb.send_buffer[0])),&rsi_app_cb.webpage_morechunks, host_webpage, (sizeof(host_webpage) - 1), 0);
                  }
                }
                else
                {
                  return -1;
                }
              }
              break;
#endif

#if SNMP_SUPPORT

    case RSI_RSP_SNMP_ENABLE:
      if(!rsi_app_cb.error_code )
      {
        //! Nothing to do
        snmp_len = rsi_snmp_trap_init(&rsi_app_cb.send_buffer[0]);
        if(snmp_len == -1)
        {
             printf("\nTRAP LEN ECEEDED\n");
             //! Maximum supported length got exceeded
             return -1; 
         }

             retval = rsi_snmp_trap(((rsi_uSnmptrap *)&rsi_app_cb.send_buffer[0]), snmp_len);
       }

        //retval = rsi_snmp_trap((rsi_uSnmptrap *)RSI_FILL_PARAMETERS(RSI_REQ_SNMP_TRAP,&rsi_app_cb.send_buffer[0])); 
      
      else
      {
        return -1;
      }
      break;

    case RSI_REQ_SNMP_SET:
      if(!rsi_app_cb.error_code )
      {
        //! Nothing to do


      }
      else
      {
        return -1;
      }
      break;

    case  RSI_RSP_SNMP_TRAP:
      if(!rsi_app_cb.error_code)
      {

      }
      else
      {
        return -1;
      }
      break;

    case RSI_REQ_SNMP_GET:
      if(!rsi_app_cb.error_code )
      { 
        retval = rsi_snmp_get_rsp((rsi_uSnmp *)RSI_FILL_PARAMETERS(RSI_REQ_SNMP_GET,&rsi_app_cb.send_buffer[0])); 
      }
      else
      {
        return -1;
      }    
      break;

    case RSI_RSP_SNMP_GET_RSP:
      if(!rsi_app_cb.error_code )
      {
        retval = rsi_snmp_get_rsp((rsi_uSnmp *)RSI_FILL_PARAMETERS(RSI_REQ_SNMP_GET,&rsi_app_cb.send_buffer[0]));        
      }
      else
      {
        return -1;
      }    
      break;

    case RSI_REQ_SNMP_GETNEXT:
      if(!rsi_app_cb.error_code )
      {
       retval = rsi_snmp_get_next_rsp((rsi_uSnmp *)RSI_FILL_PARAMETERS(RSI_REQ_SNMP_GETNEXT,&rsi_app_cb.send_buffer[0]));
      }
      else
      {
        return -1;
      }    
      break;

    case RSI_RSP_SNMP_GETNEXT_RSP:
      if(!rsi_app_cb.error_code )
      {
        retval = rsi_snmp_get_next_rsp((rsi_uSnmp *)RSI_FILL_PARAMETERS(RSI_REQ_SNMP_GETNEXT,&rsi_app_cb.send_buffer[0]));
      }
      else
      {
        return -1;
      }    
      break;
#endif

    case RSI_RSP_IPCHANGE_NOTIFY:
      if(!rsi_app_cb.error_code )
      {
        //TODO
      }
      else
      {
        return -1;
      }
      break;
#endif

    default:
      break;

  }
  if(wificonf_done == 1)
  {
#ifndef COEX_APP_CHANGES
    break;
#endif
  }
  return retval;
}

#if 0
uint8 data_pkt[34] = {0xec,0x1a,0x59,0xb2,0x80,0x5d,0x00,0x23,
                       0xa7,0x4c,0x06,0xfd,0x08,0x00,0x12,0xea,
                       0x7f,0x66,0xc0,0x00,0x00,0x00,0x01,0x00,
                       0x00,0x00};
#endif
