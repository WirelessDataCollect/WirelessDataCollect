/**
 * @file       rsi_config_init.c
 * @version    3.6
 * @date       2013-May-16
 *
 * Copyright(C) Redpine Signals 2013
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief INIT STRUCT: Initializes the global parameter structure
 *
 * @section Description
 * This file contains function to initialize the main structure which defines
 * system operation
 *
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"
#include "rsi_app_util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rsi_app.h"

#if ENABLE_USER_STORE_CONFIGURATION
#include "rsi_user_store_config_init.h"
#endif

#if RSI_PUF_ENABLE
#include "rsi_puf.h"
#endif

	

/**
 * Global Variables
 */


/*====================================================*/
/**
 * @fn             int16 rsi_fill_paremeters(int type,rsi_api *buffer )
 * @brief          Initialize the global parameter structure
 * @param[in]      rsi_api *buffer, pointer to the global parameter structure
 * @param[out]     none
 * @return         status
 *                 0  = SUCCESS
 * @description	
 * This function is used to initialize the global parameter structure with parameters
 * used to configure the Wi-Fi module.
 * 
 */


#if SNMP_SUPPORT
MIB_ENTRY   mib2_mib[] = {
  {(char *)"1.3.6.1.2.1.1.1.0",SNMP_ANS1_OCTET_STRING,"REDPINE SIGNALS"},

  {(char *)"1.3.6.1.2.1.1.2.0",SNMP_ANS1_OBJECT_ID,"1.3.6.1.4.1.8072.3.2.10"},

  {(char *)"1.3.6.1.2.1.1.3.0",SNMP_ANS1_TIME_TICS,"(1774633) 4:55:46.33"},

  {(char *)"1.3.6.1.2.1.1.4.0",SNMP_ANS1_OCTET_STRING,"Root <root@localhost> (configure /etc/snmp/snmp.local.conf)"},

  {(char *)"1.3.6.1.2.1.1.5.0",SNMP_ANS1_OCTET_STRING,"SNMP Application"},

  {(char *)"1.3.6.1.2.1.1.6.0",SNMP_ANS1_OCTET_STRING,"Unknown (edit /etc/snmp/snmpd.conf)"},

  {(char *)"1.3.6.1.2.1.1.8.0",SNMP_ANS1_TIME_TICS,"(7) 0:00:00.07"},

  {(char *)"1.3.6.1.2.1.1.9.1.2.1",SNMP_ANS1_OBJECT_ID,"1.3.6.1.6.3.11.3.1.1"}, 

  {(char *)"1.3.6.1.2.1.1.9.1.2.2",SNMP_ANS1_OBJECT_ID,"1.3.6.1.6.3.15.2.1.1"},

  {(char *)"1.3.6.1.2.1.1.9.1.2.3",SNMP_ANS1_OBJECT_ID,"1.3.6.1.6.3.10.3.1.1"},

  {(char *)"1.3.6.1.2.1.1.9.1.2.4",SNMP_ANS1_OBJECT_ID,"1.3.6.1.6.3.1"},

  {(char *)"1.3.6.1.2.1.1.9.1.2.5",SNMP_ANS1_OBJECT_ID,"1.3.6.1.2.1.49"},

  {(char *)"1.3.6.1.2.1.1.9.1.2.6",SNMP_ANS1_OBJECT_ID,"1.3.6.1.2.1.4"},

  {(char *)"1.3.6.1.2.1.1.9.1.2.7",SNMP_ANS1_OBJECT_ID,"1.3.6.1.2.1.50"},

  {(char *)"1.3.6.1.2.1.1.9.1.2.8",SNMP_ANS1_OBJECT_ID,"1.3.6.1.6.3.16.2.2.1"},

  {(char *)"1.3.6.1.2.1.1.9.1.2.9",SNMP_ANS1_OBJECT_ID,"1.3.6.1.6.3.13.3.1.3"},

  {(char *)"1.3.6.1.2.1.1.9.1.2.10",SNMP_ANS1_OBJECT_ID,"1.3.6.1.2.1.92"},

  {(char *)"1.3.6.1.2.1.1.9.1.3.1",SNMP_ANS1_OCTET_STRING,"The MIB for Message Processing and Dispatching."},

  {(char *)"1.3.6.1.2.1.1.9.1.3.2",SNMP_ANS1_OCTET_STRING,"The management information definitions for the SNMP User-based Security Model."},

  {(char *)"1.3.6.1.2.1.1.9.1.3.3",SNMP_ANS1_OCTET_STRING,"The SNMP Management Architecture MIB."},

  {(char *)"1.3.6.1.2.1.1.9.1.3.4",SNMP_ANS1_OCTET_STRING,"The MIB module for SNMPv2 entities"},

  {(char *)"1.3.6.1.2.1.1.9.1.3.5",SNMP_ANS1_OCTET_STRING,"The MIB module for managing TCP implementations"},

  {(char *)"1.3.6.1.2.1.1.9.1.3.6",SNMP_ANS1_OCTET_STRING,"The MIB module for managing IP and ICMP implementations"},

  {(char *)"1.3.6.1.2.1.1.9.1.3.7",SNMP_ANS1_OCTET_STRING,"The MIB module for managing UDP implementations"},

  {(char *)"1.3.6.1.2.1.1.9.1.3.8",SNMP_ANS1_OCTET_STRING,"View-based Access Control Model for SNMP."},

  {(char *)"1.3.6.1.2.1.1.9.1.3.9",SNMP_ANS1_OCTET_STRING,"The MIB modules for managing SNMP Notification, plus filtering."},

  {(char *)"1.3.6.1.2.1.1.9.1.3.10",SNMP_ANS1_OCTET_STRING,"The MIB module for logging SNMP Notifications."},

  {(char *)"1.3.6.1.2.1.1.9.1.4.1",SNMP_ANS1_TIME_TICS,"(7) 0:00:00.07"},

  {(char *)"1.3.6.1.2.1.1.9.1.4.2",SNMP_ANS1_TIME_TICS,"(7) 0:00:00.07"},

  {(char *)"1.3.6.1.2.1.1.9.1.4.3",SNMP_ANS1_TIME_TICS,"(7) 0:00:00.07"},

  {(char *)"1.3.6.1.2.1.1.9.1.4.4",SNMP_ANS1_TIME_TICS,"(7) 0:00:00.07"},

  {(char *)"1.3.6.1.2.1.1.9.1.4.5",SNMP_ANS1_TIME_TICS,"(7) 0:00:00.07"},

  {(char *)"1.3.6.1.2.1.1.9.1.4.6",SNMP_ANS1_TIME_TICS,"(7) 0:00:00.07"},

  {(char *)"1.3.6.1.2.1.1.9.1.4.7",SNMP_ANS1_TIME_TICS,"(7) 0:00:00.07"},

  {(char *)"1.3.6.1.2.1.1.9.1.4.8",SNMP_ANS1_TIME_TICS,"(7) 0:00:00.07"},

  {(char *)"1.3.6.1.2.1.1.9.1.4.9",SNMP_ANS1_TIME_TICS,"(7) 0:00:00.07"},

  {(char *)"1.3.6.1.2.1.1.9.1.4.10",SNMP_ANS1_TIME_TICS,"(7) 0:00:00.07"},

  {(char *)"1.3.6.1.2.1.25.1.1.0",SNMP_ANS1_TIME_TICS,"(7) 0:00:00.07"}

};

#endif

uint8* rsi_fill_parameters(uint32 type, uint8 *buffer)
{
 
  uint8 str[7] = {0};
  #if SNMP_SUPPORT
    uint8 server_objid[MAX_OID_LENGTH]={0};
  #endif

#if RSI_CONCURRENT_MODE
  uint8 vap_id = 0;
  if(type == RSI_REQ_JOIN)
  {

    rsi_uJoin *join = (rsi_uJoin *)buffer;            
    vap_id = join->joinFrameSnd.vap_id;
  }
#endif  

  //! Memset request buffer
  memset(buffer, '\0', RSI_MAX_PAYLOAD_SIZE);
  switch(type)
  {
    case RSI_REQ_OPERMODE:
      {
        //! opermode Parameters 
        rsi_uOperMode *oper=(rsi_uOperMode *)buffer;

        rsi_uint32_to_4bytes(oper->operModeFrameSnd.oper_mode, RSI_OPERMODE);
        rsi_uint32_to_4bytes(oper->operModeFrameSnd.feature_bit_map, RSI_FEATURE_BIT_MAP);
        rsi_uint32_to_4bytes(oper->operModeFrameSnd.tcp_ip_feature_bit_map, RSI_TCP_IP_FEATURE_BIT_MAP);
        rsi_uint32_to_4bytes(oper->operModeFrameSnd.custom_feature_bit_map, RSI_CUSTOM_FEATURE_BIT_MAP);
        rsi_uint32_to_4bytes(oper->operModeFrameSnd.ext_custom_feature_bit_map, RSI_EXT_CUSTOM_FEATURE_BIT_MAP);
        rsi_uint32_to_4bytes(oper->operModeFrameSnd.ble_feature_bit_map, RSI_BLE_CUSTOM_FEATURE_BIT_MAP);
	    rsi_uint32_to_4bytes(oper->operModeFrameSnd.ext_tcpip_feature_bit_map, RSI_EXT_TCP_IP_FEATURE_BIT_MAP);
      }
      break;
    case RSI_REQ_SCAN:
      {
        //! Scan Parameters
        rsi_uScan *scan = (rsi_uScan *)buffer;

        scan->scanFrameSnd.channel[0] = RSI_SCAN_CHANNEL;
        strcpy((char *)scan->scanFrameSnd.ssid, RSI_SCAN_SSID);
        if(RSI_BAND == RSI_DUAL_BAND)
        {
          rsi_uint16_to_2bytes(scan->scanFrameSnd.channel_bit_map_2_4, RSI_SCAN_CHANNEL_BIT_MAP_2_4);
          rsi_uint32_to_4bytes(scan->scanFrameSnd.channel_bit_map_5, RSI_SCAN_CHANNEL_BIT_MAP_5);
        }
        else if (RSI_BAND == RSI_BAND_5GHZ)
        {
          rsi_uint32_to_4bytes(scan->scanFrameSnd.channel_bit_map_5, RSI_SCAN_CHANNEL_BIT_MAP_5);
        }
        else
        {
          rsi_uint16_to_2bytes(scan->scanFrameSnd.channel_bit_map_2_4, RSI_SCAN_CHANNEL_BIT_MAP_2_4);
        }
        if((!RSI_SCAN_CHANNEL) && !(strlen(RSI_SCAN_SSID)))
        {
          scan->scanFrameSnd.scan_feature_bitmap = RSI_SCAN_FEAT_BITMAP;
        }
        else
        {
          scan->scanFrameSnd.scan_feature_bitmap = 0;
        }

      }
      break;
    case RSI_REQ_JOIN:
      {
        //! Join Parameters
        rsi_uJoin *join = (rsi_uJoin *)buffer;  

        join->joinFrameSnd.securityType = RSI_SECURITY_MODE;
        join->joinFrameSnd.dataRate     = RSI_DATA_RATE;   //数据速率
        join->joinFrameSnd.powerLevel   = RSI_POWER_LEVEL;
        join->joinFrameSnd.join_feature_bitmap = RSI_JOIN_FEAT_BIT_MAP;
        join->joinFrameSnd.ssid_len     = strlen((c8 *)RSI_JOIN_SSID);  //要加入的ssid长度
        rsi_uint32_to_4bytes(join->joinFrameSnd.listen_interval, RSI_LISTEN_INTERVAL);

        if(SEND_PSK_IN_JOIN)
        {
          strcpy((char *)join->joinFrameSnd.psk, (c8 *)RSI_PSK);//PSK共享密钥
        }
#if RSI_CONCURRENT_MODE   //concurrent模式
        if(vap_id == 1)
        {
          strcpy((char *)join->joinFrameSnd.ssid, RSI_CONCURRENT_AP_JOIN_SSID);//把创建的AP的SSID存入
          join->joinFrameSnd.ssid_len     = (sizeof(RSI_CONCURRENT_AP_JOIN_SSID) - 1);
          //! Restore vap id
          join->joinFrameSnd.vap_id = vap_id;
        }
        else{
          strcpy((char *)join->joinFrameSnd.ssid, (c8*)RSI_JOIN_SSID);
        }
#else
        strcpy((char *)join->joinFrameSnd.ssid, (c8*)RSI_JOIN_SSID);
#endif
        rsi_ascii_mac_address_to_6bytes((uint8 *)join->joinFrameSnd.join_bssid, (int8 *)RSI_AP_BSSID);
      }
      break;
#if SET_REGION_SUPPORT
    case RSI_REQ_SET_REG_CODE:
      {
        //! Set region parameters
        rsi_usetregion *setregion = (rsi_usetregion *)buffer;

        setregion->setRegionFrameSnd.setregion_code_from_user_cmd = SET_REGION_FROM_USER_OR_BEACON;
        setregion->setRegionFrameSnd.region_code = REGION_CODE;                    
        rsi_uint16_to_2bytes(setregion->setRegionFrameSnd.module_type,MODULE_TYPE);
      }
      break;
#endif
#if SET_REGION_AP_SUPPORT
    case RSI_REQ_SET_REG_AP:
      {
        //! Set region in AP mode
        rsi_usetregion_ap_t *setregion_ap = (rsi_usetregion_ap_t *)buffer;

        setregion_ap->setRegionApFrameSnd.setregion_code_from_user_cmd = SET_REGION_AP_FROM_USER;
        strcpy((char *)setregion_ap->setRegionApFrameSnd.country_code,RSI_COUNTRY_CODE);

#if SET_REGION_AP_FROM_USER
        extract_setregionap_country_info(setregion_ap);
#endif
      }
      break;
#endif
#if RSI_PSK_SUPPORT
    case RSI_REQ_HOST_PSK:
      {
        uint16 i,j;        
        //! PSK and PMK parameters            
        rsi_uPsk *psk_key = (rsi_uPsk *)buffer;

        psk_key->PskFrameSnd.TYPE = RSI_PSK_TYPE;
        if(RSI_PSK_TYPE == RSI_PMK_FROM_HOST)
        {
          for(i=0 ,j=0 ; i < 64 && j < 32; i+=2,j++)
          {
            if(RSI_PMK[i] && RSI_PMK[i + 1])
            {
              psk_key->PskFrameSnd.psk_or_pmk[j]  = ((uint16 )convert_lower_case_to_upper_case(RSI_PMK[i])) * 16;
              psk_key->PskFrameSnd.psk_or_pmk[j] += convert_lower_case_to_upper_case(RSI_PMK[i + 1]); 
            }
            else
            {
              psk_key->PskFrameSnd.psk_or_pmk[j]=0;
            }
          }
        }
        else if(RSI_PSK_TYPE == RSI_GENERATE_PMK)
        {
          strcpy((char *)psk_key->PskFrameSnd.psk_or_pmk, (c8 *)RSI_PSK);
          strcpy((char *)psk_key->PskFrameSnd.ap_ssid, (c8 *)RSI_JOIN_SSID);
        }
        else if(RSI_PSK_TYPE == RSI_PSK_FROM_HOST)
        {
          strcpy((char *)psk_key->PskFrameSnd.psk_or_pmk, (c8 *)RSI_PSK);
        }
        else
        {
          memset(psk_key->PskFrameSnd.psk_or_pmk, '\0', RSI_PSK_LEN);
        }

      }
      break;
#endif
#if RSI_RF_CURRENT_CONFIG
    case RSI_REQ_RF_CURRENT_CONFIG:
      { 
        //! RF Current Configurations
        rsi_rf_current_config_t *rf_config = (rsi_rf_current_config_t *)buffer;

        rf_config->rf_rx_curr_mode = (uint8)RSI_RF_TX_POWER;
        rf_config->rf_tx_curr_mode = (uint8)RSI_RF_RX_POWER;
        rf_config->rf_tx_dbm = (uint16)RSI_TX_POWER_DBM;
      }
      break;
#endif
#if (RSI_POWER_MODE != RSI_POWER_MODE_0)
    case RSI_REQ_PWRMODE:
      {
        //! Power mode setting
        rsi_uPower *powermode = (rsi_uPower *)buffer;

        powermode->powerFrameSnd.powerVal = RSI_POWER_MODE;
        powermode->powerFrameSnd.ulp_mode_enable = RSI_ULP_MODE;
        powermode->powerFrameSnd.listen_interval_dtim = RSI_LISTEN_INTERVAL_DTIM;

      }
      break;
    case RSI_REQ_SLEEP_TIMER:
      {
        //! SleepTimer Parameters
        rsi_uSleepTimer *sleep = (rsi_uSleepTimer *)buffer;

        rsi_uint16_to_2bytes(sleep->SleepTimerFrameSnd.TimeVal,RSI_TIMEVAL);
      }
      break;
#endif

    case RSI_REQ_SET_MAC_ADDR:
      {
        //! Set Mac Address
        rsi_ascii_mac_address_to_6bytes((uint8 *)buffer, (int8 *)RSI_MAC_ADDRESS);
      }
      break;
#if RSI_DEBUG_PRINTS_ENABLE
    case RSI_REQ_DEBUG_PRINTS:
      {
        /*Debug parameters*/
        rsi_uDebug *debug = (rsi_uDebug *)buffer;

        rsi_uint32_to_4bytes(debug->debugFrameSnd.assertion_type, RSI_DEBUG_ASSERTION_TYPE);
        rsi_uint32_to_4bytes(debug->debugFrameSnd.assertion_level, RSI_DEBUG_ASSERTION_LEVEL);

      }
      break;
#endif
#if ENABLE_USER_STORE_CONFIGURATION
    case RSI_REQ_USER_STORE_CFG:
      {
        rsi_user_store_config_init(buffer);                            
      }
      break;
#endif
#if RSI_ENABLE_REJOIN_PARAMS 
    case RSI_REQ_REJOIN_PARAMS:
      {
        //! rejoin parameters
        rsi_rejoin_params_t *rejoin_params = (rsi_rejoin_params_t *)buffer;

        rsi_uint32_to_4bytes(rejoin_params->rsi_max_try, RSI_REJOIN_MAX_RETRY);
        rsi_uint32_to_4bytes(rejoin_params->rsi_scan_interval, RSI_REJOIN_SCAN_INTERVAL);
        rsi_uint32_to_4bytes(rejoin_params->rsi_beacon_missed_count, RSI_REJOIN_BEACON_MISSED_CNT);
        rsi_uint32_to_4bytes(rejoin_params->rsi_first_time_retry_enable, RSI_REJOIN_FIRST_TIME_RETRY);

      }
      break;
#endif
#if RSI_WMM_PS_SUPPORT
    case RSI_REQ_WMM_PS:
      {
        //! wmmps parameters
        rsi_uWmmPs *wmmps = (rsi_uWmmPs *)buffer;

        wmmps->wmmPsFrameSnd.wmm_ps_uapsd_bitmap = RSI_WMM_PS_UAPSD_BITMAP;
        rsi_uint16_to_2bytes(wmmps->wmmPsFrameSnd.wmm_ps_enable, RSI_WMM_PS_SUPPORT);
        rsi_uint16_to_2bytes(wmmps->wmmPsFrameSnd.wmm_ps_type, RSI_WMM_PS_TYPE);
        rsi_uint32_to_4bytes(wmmps->wmmPsFrameSnd.wmm_ps_wakeup_interval, RSI_WMM_PS_WAKEUP_INTERVAL);

      }
      break;
#endif
#if RSI_WPS_SUPPORT
    case RSI_REQ_WPS_METHOD:
      {
        //! WPS METHOD
        rsi_uWpsMethod *wps = (rsi_uWpsMethod *)buffer;
        rsi_uint16_to_2bytes(wps->wpsMethodFrameSnd.wps_method, RSI_WPS_METHOD);
        rsi_uint16_to_2bytes(wps->wpsMethodFrameSnd.generate_pin, RSI_GENERATE_PIN);
        memcpy((char *)wps->wpsMethodFrameSnd.wps_pin , RSI_WPS_PIN, sizeof(RSI_WPS_PIN));

      }
      break;
#endif
#if RSI_BG_SCAN_ENABLE    
    case RSI_REQ_BG_SCAN:
      {
        //! BG Scan Parameters  
        rsi_ubgScan *bgScan = (rsi_ubgScan *)buffer;

        rsi_uint16_to_2bytes(bgScan->bgscanFrameSnd.bgscan_enable, RSI_BG_SCAN_ENABLE);
        rsi_uint16_to_2bytes(bgScan->bgscanFrameSnd.enable_instant_bgscan, RSI_INSTANT_BG);
        rsi_uint16_to_2bytes(bgScan->bgscanFrameSnd.bgscan_threshold,RSI_BG_SCAN_THRESHOLD );
        rsi_uint16_to_2bytes(bgScan->bgscanFrameSnd.rssi_tolerance_threshold, RSI_RSSI_TOLERANCE_THRESHOLD);
        rsi_uint16_to_2bytes(bgScan->bgscanFrameSnd.bgscan_periodicity,RSI_BG_SCAN_PERIODICITY );
        rsi_uint16_to_2bytes(bgScan->bgscanFrameSnd.active_scan_duration, RSI_ACTIVE_SCAN_DURATION );
        rsi_uint16_to_2bytes(bgScan->bgscanFrameSnd.passive_scan_duration,RSI_PASSIVE_SCAN_DURATION );
        bgScan->bgscanFrameSnd.multi_probe = RSI_MULTIPROBE;

      }
      break;
#endif
#if RSI_ROAMING_SUPPORT
    case RSI_REQ_ROAM_PARAMS:
      {
        //! Roaming parameters
        rsi_uRoamParams *roamparams = (rsi_uRoamParams *)buffer;

        rsi_uint32_to_4bytes(roamparams->roamParamsFrameSnd.roam_enable, RSI_ROAMING_SUPPORT);
        rsi_uint32_to_4bytes(roamparams->roamParamsFrameSnd.roam_threshold,  RSI_ROAMING_THRESHOLD);
        rsi_uint32_to_4bytes(roamparams->roamParamsFrameSnd.roam_hysteresis, RSI_ROAMING_HYSTERISIS); 

      }
      break;
#endif
    case RSI_REQ_SET_WEP_KEY:
      {
        //! Wepkey data initialisation
        rsi_wepkey *wepkey = (rsi_wepkey *)buffer;

        rsi_uint16_to_2bytes(wepkey->index,RSI_WEP_INDEX);
        strcpy((char *)wepkey->key[0], (char *)RSI_WEPKEY0);
        strcpy((char *)wepkey->key[1], (char *)RSI_WEPKEY1);
        strcpy((char *)wepkey->key[2], (char *)RSI_WEPKEY2);
        strcpy((char *)wepkey->key[3], (char *)RSI_WEPKEY3);

      }
      break;
    case RSI_REQ_DISCONNECT:
      {
        //! disconnect parameters
        rsi_disassoc_t *disassoc = (rsi_disassoc_t *)buffer;

        rsi_uint16_to_2bytes(disassoc->mode_flag,MODE_FLAG);
        rsi_ascii_mac_address_to_6bytes((uint8 *)&disassoc->client_mac_addr, (int8 *)CLIENT_MAC_ADDRESS);

      }
      break;
#if P2P_MODE
    case RSI_REQ_CFG_P2P:
      {
        //! WiFi direct parameters
        rsi_uConfigP2p *p2p = (rsi_uConfigP2p *)buffer;

        rsi_uint16_to_2bytes(p2p->configP2pFrameSnd.GOIntent, GO_INTENT_VALUE);
        rsi_uint16_to_2bytes(p2p->configP2pFrameSnd.operChannel, P2P_OPER_CHANNEL);
        strcpy((char *)p2p->configP2pFrameSnd.deviceName, P2P_DEVICE_NAME);
        strcpy((char *)p2p->configP2pFrameSnd.ssidPostFix, POST_FIX_SSID);
        strcpy((char *)p2p->configP2pFrameSnd.psk, (c8 *)RSI_PSK);

      }
      break;
#endif
#if (AP_MODE) || (RSI_CONCURRENT_MODE)
    case RSI_REQ_APCONFIG:
      {
        //! AP Configuration data Initialisation
        rsi_apconfig *ap = (rsi_apconfig *)buffer;

        rsi_uint16_to_2bytes(ap->dtim_period,RSI_DTIM_PERIOD);
        rsi_uint16_to_2bytes(ap->beacon_interval,RSI_BEACON_INTERVAL);
        rsi_uint16_to_2bytes(ap->channel_no,RSI_AP_CHANNEL_NUM);
        rsi_uint16_to_2bytes(ap->max_sta_support,MAX_NO_OF_CLIENTS);
#if RSI_CONCURRENT_MODE
        strcpy((char *)ap->ssid,RSI_CONCURRENT_AP_JOIN_SSID);		
        strcpy((char *)ap->psk,RSI_CONCURRENT_AP_PSK);		
#else
        strcpy((char *)ap->ssid,(c8 *)RSI_JOIN_SSID);
        strcpy((char *)ap->psk,(c8 *)RSI_PSK);
#endif
        ap->security_type = RSI_SECURITY_TYPE;
        ap->ap_keepalive_type = AP_KEEPALIVE_TYPE;
        ap->ap_keepalive_period = AP_KEEPALIVE_PERIOD;
        ap->encryp_mode = RSI_ENCRYPTION_MODE;

      }
      break;
    case RSI_REQ_AP_HT_CAPS:
      {
        //! HT CAPS parameters
        rsi_uHtCaps *ht_caps = (rsi_uHtCaps *)buffer;

        rsi_uint16_to_2bytes(ht_caps->htCapsFrameSnd.mode_11n_enable, RSI_MODE_11N_ENABLE);
        rsi_uint16_to_2bytes(ht_caps->htCapsFrameSnd.ht_caps_bitmap, RSI_HT_CAPS_BIT_MAP);
      }
      break;
#endif
#if ENTERPRISE_MODE
    case RSI_REQ_SET_EAP_CFG:
      {
        //! EAP parameters
        rsi_uSetEap *eap = (rsi_uSetEap *)buffer;

        strcpy((char *)eap->setEapFrameSnd.eapMethod, EAP_METHOD);
        strcpy((char *)eap->setEapFrameSnd.innerMethod, INNER_METHOD);
        strcpy((char *)eap->setEapFrameSnd.userIdentity, USER_IDENTITY);
        strcpy((char *)eap->setEapFrameSnd.password, PASSWORD);
        rsi_uint32_to_4bytes((uint8 *)eap->setEapFrameSnd.okc_enable, EAP_OKC_ENABLE);
        strcpy((char *)eap->setEapFrameSnd.private_key_passwd, PRIVATE_KEY_PASSWORD);
      }
      break;
#endif
#if RSI_PER_MODE_SUPPORT
    case RSI_REQ_PER_PARAMS:
      {
        //! per mode parameters
        rsi_uPerMode *permode = (rsi_uPerMode *)buffer;

        rsi_uint16_to_2bytes(permode->perModeFrameSnd.per_mode_enable,RSI_PER_MODE_SUPPORT);
        rsi_uint16_to_2bytes(permode->perModeFrameSnd.power, RSI_PER_MODE_POWER);
        rsi_uint32_to_4bytes(permode->perModeFrameSnd.rate, RSI_PER_MODE_RATE);
        rsi_uint16_to_2bytes(permode->perModeFrameSnd.length, RSI_PER_MODE_LENGTH);
        rsi_uint16_to_2bytes(permode->perModeFrameSnd.mode, RSI_PER_MODE_MODE);
        rsi_uint16_to_2bytes(permode->perModeFrameSnd.channel, RSI_PER_MODE_CHANNEL);
        rsi_uint16_to_2bytes(permode->perModeFrameSnd.rate_flags, RSI_PER_MODE_RATE_FLAGS);
        rsi_uint16_to_2bytes(permode->perModeFrameSnd.reserved1, RSI_PER_MODE_PER_CH_BW);
        rsi_uint16_to_2bytes(permode->perModeFrameSnd.aggr_enable, RSI_PER_MODE_AGGR_ENABLE);
        rsi_uint16_to_2bytes(permode->perModeFrameSnd.reserved2, RSI_PER_MODE_AGGR_COUNT);
        rsi_uint16_to_2bytes(permode->perModeFrameSnd.no_of_pkts, RSI_PER_MODE_NO_OF_PKTS);
        rsi_uint32_to_4bytes(permode->perModeFrameSnd.delay, RSI_PER_MODE_DELAY);
      }
      break;
#endif
    case RSI_REQ_PER_STATS:
      {
        //! PER stats 
        rsi_uPerStats *perstats = (rsi_uPerStats *)buffer;

        rsi_uint16_to_2bytes(perstats->perStatsFrameSnd.per_stats_enable, RSI_PER_STATS);
        rsi_uint16_to_2bytes(perstats->perStatsFrameSnd.per_stats_channel, RSI_PER_STATS_CHANNEL);
      }
      break;
#if !RSI_TCP_IP_BYPASS
    case RSI_REQ_IPCONF6:
      {
        //! ip version_6 parameters
        rsi_uIPconf6 *ipconf6 = (rsi_uIPconf6 *)buffer;

        rsi_uint16_to_2bytes(ipconf6->ipconf6FrameSnd.mode, RSI_IPV6_CFG_MODE);
        rsi_uint16_to_2bytes(ipconf6->ipconf6FrameSnd.prefixLength, RSI_IPV6_PREFIX_LENGTH);
        parse_ipv6_address(ipconf6->ipconf6FrameSnd.ipaddr6, (uint8 *)RSI_MODULE_IPV6_ADDRESS);
        parse_ipv6_address(ipconf6->ipconf6FrameSnd.gateway6, (uint8 *)RSI_DEFAULT_ROUTER_IPV6_ADDRESS);

      }
      break;
    case RSI_REQ_IPPARAM_CONFIG:
      {
        //! ip params
        rsi_uIpparam *ipparam = (rsi_uIpparam *)buffer;

        rsi_ascii_dot_address_to_4bytes(ipparam->ipparamFrameSnd.ipaddr, (int8 *)RSI_MODULE_IP_ADDRESS);
        rsi_ascii_dot_address_to_4bytes(ipparam->ipparamFrameSnd.netmask, (int8 *)RSI_NETMASK);
        rsi_ascii_dot_address_to_4bytes(ipparam->ipparamFrameSnd.gateway, (int8 *)RSI_GATEWAY);
        ipparam->ipparamFrameSnd.dhcpMode = RSI_IP_CFG_MODE;
        strcpy((char *)ipparam->ipparamFrameSnd.hostname, RSI_DHCP_HOST_NAME);
        ipparam->ipparamFrameSnd.vap_id = 0; 
        rsi_uint32_to_4bytes(ipparam->ipparamFrameSnd.fqdn_flag, RSI_DHCP_FQDN_FLAG);

      }
      break;
#if RSI_ICMP_FROM_MODULE
    case RSI_REQ_PING_PACKET:
      {
        //! ping parameters
        rsi_ping_request_t *ping_request = (rsi_ping_request_t *)buffer;

        rsi_uint16_to_2bytes(ping_request->ip_version, RSI_PING_VERSION);
        if(RSI_IP_VERSION == IP_VERSION_4)
        {
          rsi_ascii_dot_address_to_4bytes(((uint8 *)&(ping_request->ping_address.ipv4_address)),(uint8 *)RSI_PING_TARGET_IP);
        }
        else
        {
          parse_ipv6_address(ping_request->ping_address.ipv6_address, (uint8 *)RSI_PING_TARGET_IPV6);
        }
        rsi_uint16_to_2bytes(ping_request->ping_size, RSI_PING_DATA_SIZE);                     
        
        rsi_uint16_to_2bytes(ping_request->timeout, RSI_PING_REPLY_TIMEOUT);                     
      }
      break;
#endif
    case RSI_REQ_SOCKET_CREATE:
      {
        //! Socket Parameters
        rsi_uSocket *socket_create = (rsi_uSocket *)buffer;

        rsi_uint16_to_2bytes(socket_create->socketFrameSnd.ip_version,RSI_IP_VERSION);
        rsi_uint16_to_2bytes(socket_create->socketFrameSnd.moduleSocket,RSI_MODULE_SOCKET_ONE);
        rsi_uint16_to_2bytes(socket_create->socketFrameSnd.destSocket,RSI_TARGET_SOCKET_ONE); 
        rsi_uint16_to_2bytes(socket_create->socketFrameSnd.socketType,RSI_SOCKET_TYPE); 
        rsi_uint16_to_2bytes(socket_create->socketFrameSnd.max_count, RSI_MAX_LTCP_CONNECTIONS); 
        rsi_uint32_to_4bytes(socket_create->socketFrameSnd.tos, RSI_TOS);

        socket_create->socketFrameSnd.ssl_bitmap   = SOCKET_FEATURE;
        socket_create->socketFrameSnd.ssl_ciphers  = SSL_CIPHERS;
        strcpy((char *)socket_create->socketFrameSnd.webs_resource_name, WEBS_RESOURCE_NAME);
        strcpy((char *)socket_create->socketFrameSnd.webs_host_name, WEBS_HOST_NAME);
        socket_create->socketFrameSnd.tcp_retry_count = TCP_RETRANMISSIONS_COUNT; 
        socket_create->socketFrameSnd.socket_bitmap   = SOCKET_BITMAP; 
        socket_create->socketFrameSnd.rx_window_size  = TCP_RX_WINDOW_SIZE; 

        if(RSI_IP_VERSION == IP_VERSION_4)
        { 
          rsi_ascii_dot_address_to_4bytes((uint8 *)socket_create->socketFrameSnd.destIpaddr.ipv4_address, (int8 *)RSI_TARGET_IP_ADDRESS);
        }
        else
        {
          parse_ipv6_address(socket_create->socketFrameSnd.destIpaddr.ipv6_address, (uint8 *)RSI_TARGET_IPV6_ADDRESS);
        }

      }
      break;
    case RSI_REQ_READ:
      {
        //! Read Parameters
		  //没什么作用
//        rsi_uSocketRead *socket_read = (rsi_uSocketRead *)buffer;
      }
      break;
#if SNMP_SUPPORT

    case RSI_REQ_SNMP_GET:
      {
        //! SNMP GET parameters
        rsi_uSnmp *snmpget = (rsi_uSnmp *)buffer;

        snmpget->snmpFrameSnd.type  = RSI_SNMP_OBJ_TYPE;
        if(RSI_SNMP_OBJ_TYPE == SNMP_ANS1_OCTET_STRING)
        {
          strcpy((char *)snmpget->snmpFrameSnd.value, (char *)RSI_SNMP_OBJ_VALUE);
        }
        else
        {
          rsi_uint32_to_4bytes(snmpget->snmpFrameSnd.value, (uint32)RSI_SNMP_OBJ_VALUE);
        }
	
      }
      break;
  case RSI_REQ_SNMP_GETNEXT:
       {
        //! SNMP GETNEXT parameters
        rsi_uSnmp *snmpget = (rsi_uSnmp *)buffer;

        int status =0,i=0, SNMP_MIB_TABLE_SIZE;

        memset(server_objid,0,sizeof(server_objid));

        //! copying server_objid from the received bufer 
        strncpy(server_objid,&rsi_app_cb.read_packet_buffer[16],rsi_app_cb.read_packet_buffer[0]);

        SNMP_MIB_TABLE_SIZE = sizeof(mib2_mib)/sizeof(mib2_mib[0]); 

        //! comparing server_objid with obj_id list in the MIB
        for(i = 0; i < SNMP_MIB_TABLE_SIZE; i++)
        {  
          status =  strncmp(server_objid, mib2_mib[i].obj_id,strlen(server_objid));
          //! server_objid found in the MIB list 
          if (status == 0)
          { //! if both server_objid and obj_id in the MIB are equal then give next obj_id from MIB 
            if(strlen(server_objid) == strlen(mib2_mib[i].obj_id))
            {
              i=i+1;
              break;
            }
            //! If server_objid is less than obj_id in the MIB then give same obj_id from MIB  
            else if(strlen(server_objid) < strlen(mib2_mib[i].obj_id))
            {
              break;
            }
          }
        } 

        //! Giving snmp respone to SNMP server from host 
        if(status == 0)
        {
          //! if server_objid is found in the MIB list then give that response to server   
          if(i <= (SNMP_MIB_TABLE_SIZE - 1)) 
          {
            snmpget->snmpFrameSnd.type  = mib2_mib[i].obj_type;

            strcpy((char *)snmpget->snmpFrameSnd.value, (char *)mib2_mib[i].obj_value);

            strcpy((char *)snmpget->snmpFrameSnd.objid, (char *)mib2_mib[i].obj_id);

          }
          else if(i == SNMP_MIB_TABLE_SIZE)
          {
            //! if server_objid is last in the MIB list then give the "END_OF_MIB" to server
            snmpget->snmpFrameSnd.type  = SNMP_ANS1_END_OF_MIB_VIEW ;

            strcpy((char *)snmpget->snmpFrameSnd.objid, (char *)server_objid);
          } 
        }
        else
        {
          //! if server_objid is not found in MIB list then give the "NO_SUCH_OBJECT" to server
          snmpget->snmpFrameSnd.type  = SNMP_ANS1_NO_SUCH_OBJECT ;

          strcpy((char *)snmpget->snmpFrameSnd.objid, (char *)server_objid);
        }
      }
      break;
#endif
    case RSI_REQ_SOCKET_CONFIG:
      {
        //! socket config parameters
        rsi_socket_config_t *socket_config = (rsi_socket_config_t *)buffer;

        socket_config->total_sockets       = RSI_TOTAL_SOCKETS;
        socket_config->total_tcp_sockets   = RSI_TOTAL_TCP_SOCKETS;
        socket_config->total_udp_sockets   = RSI_TOTAL_UDP_SOCKETS;
        socket_config->tcp_tx_only_sockets = RSI_TCP_TX_ONLY_SOCKETS;
        socket_config->tcp_rx_only_sockets = RSI_TCP_RX_ONLY_SOCKETS;
        socket_config->udp_tx_only_sockets = RSI_UDP_TX_ONLY_SOCKETS;
        socket_config->udp_rx_only_sockets = RSI_UDP_RX_ONLY_SOCKETS;
        socket_config->tcp_rx_high_performance_sockets = RSI_TCP_RX_HIGH_PERFORMANCE_SOCKETS;

      }
      break;
    case RSI_REQ_HTTP_GET:
      {
        //! HTTP get
        uint32 http_len = 0;
        uint8 http_feature = 0;
        rsi_uHttpReq *httpreq = (rsi_uHttpReq *)buffer;

        rsi_uint16_to_2bytes(httpreq->HttpReqFrameSnd.ip_version,RSI_IP_VERSION);
        rsi_uint16_to_2bytes(httpreq->HttpReqFrameSnd.https_enable, RSI_HTTPS_SUPPORT);
        rsi_uint16_to_2bytes(httpreq->HttpReqFrameSnd.http_port, RSI_HTTP_SERVER_PORT);
        http_feature = RSI_HTTPS_SUPPORT;
        if(!(http_feature & RSI_HTTP_NULL_DELIMITER))
        {
          strcpy((char *)&httpreq->HttpReqFrameSnd.buffer, RSI_HTTP_USERNAME);
          strcat((char *)&httpreq->HttpReqFrameSnd.buffer, ",");
          strcat((char *)&httpreq->HttpReqFrameSnd.buffer, RSI_HTTP_PASSWORD);
          strcat((char *)&httpreq->HttpReqFrameSnd.buffer, ",");
          strcat((char *)&httpreq->HttpReqFrameSnd.buffer, RSI_HTTP_HOSTNAME);
          strcat((char *)&httpreq->HttpReqFrameSnd.buffer, ",");
          if(RSI_IP_VERSION == IP_VERSION_4)
          {
            strcat((char *)&httpreq->HttpReqFrameSnd.buffer, RSI_HTTP_IP);
          }
          else
          {
            strcat((char *)&httpreq->HttpReqFrameSnd.buffer, RSI_HTTP_IPV6);
          }
          strcat((char *)&httpreq->HttpReqFrameSnd.buffer, ",");
          strcat((char *)&httpreq->HttpReqFrameSnd.buffer, RSI_HTTP_URL);
          strcat((char *)&httpreq->HttpReqFrameSnd.buffer, ",");
          rsi_buildHttpExtendedHeader((uint8 *)httpreq->HttpReqFrameSnd.buffer, 0);
        }
        else
        {
          strcpy((char *)&httpreq->HttpReqFrameSnd.buffer, RSI_HTTP_USERNAME);
          http_len = sizeof(RSI_HTTP_USERNAME);

          strcpy(((char *)&httpreq->HttpReqFrameSnd.buffer) + http_len, RSI_HTTP_PASSWORD);
          http_len += sizeof(RSI_HTTP_PASSWORD);

          strcpy(((char *)&httpreq->HttpReqFrameSnd.buffer) + http_len, RSI_HTTP_HOSTNAME);
          http_len += sizeof(RSI_HTTP_HOSTNAME);

          if(RSI_IP_VERSION == IP_VERSION_4)
          {
            strcpy(((char *)&httpreq->HttpReqFrameSnd.buffer) + http_len, RSI_HTTP_IP);
            http_len += sizeof(RSI_HTTP_IP);
          }
          else
          {
            strcpy(((char *)&httpreq->HttpReqFrameSnd.buffer) + http_len, RSI_HTTP_IPV6);
            http_len += sizeof(RSI_HTTP_IPV6);
          }
          strcpy(((char *)&httpreq->HttpReqFrameSnd.buffer) + http_len, RSI_HTTP_URL);
          http_len += sizeof(RSI_HTTP_URL);

          rsi_buildHttpExtendedHeader((uint8 *)&(httpreq->HttpReqFrameSnd.buffer) + http_len, 1);

        }
      }
      break;
    case RSI_REQ_HTTP_POST:
      {
        rsi_uHttpReq *httpreq = (rsi_uHttpReq *)buffer;
        uint32 http_len = 0;
        uint8 http_feature = 0;

        /*HTTP post*/
        rsi_uint16_to_2bytes(httpreq->HttpReqFrameSnd.ip_version,RSI_IP_VERSION);
        rsi_uint16_to_2bytes(httpreq->HttpReqFrameSnd.https_enable, RSI_HTTPS_SUPPORT);
        rsi_uint16_to_2bytes(httpreq->HttpReqFrameSnd.http_port, RSI_HTTP_SERVER_PORT);


        if(!(http_feature & RSI_HTTP_NULL_DELIMITER))
        {
          strcpy((char *)&httpreq->HttpReqFrameSnd.buffer, RSI_HTTP_USERNAME);
          strcat((char *)&httpreq->HttpReqFrameSnd.buffer, ",");
          strcat((char *)&httpreq->HttpReqFrameSnd.buffer, RSI_HTTP_PASSWORD);
          strcat((char *)&httpreq->HttpReqFrameSnd.buffer, ",");
          strcat((char *)&httpreq->HttpReqFrameSnd.buffer, RSI_HTTP_HOSTNAME);
          strcat((char *)&httpreq->HttpReqFrameSnd.buffer, ",");
          if(RSI_IP_VERSION == IP_VERSION_4)
          {
            strcat((char *)&httpreq->HttpReqFrameSnd.buffer, RSI_HTTP_IP);
          }
          else
          {
            strcat((char *)&httpreq->HttpReqFrameSnd.buffer, RSI_HTTP_IPV6);
          }
          strcat((char *)&httpreq->HttpReqFrameSnd.buffer, ",");
          strcat((char *)&httpreq->HttpReqFrameSnd.buffer, RSI_HTTP_URL);
          strcat((char *)&httpreq->HttpReqFrameSnd.buffer, ",");
          rsi_buildHttpExtendedHeader((uint8 *)httpreq->HttpReqFrameSnd.buffer, 0);
          strcat((char *)&httpreq->HttpReqFrameSnd.buffer, ",");

          //! Check for HTTP post data feature bit
          if(RSI_HTTPS_SUPPORT & RSI_FEAT_HTTP_POST_DATA)
          {
            //! Append HTTP content length
            strcat((char *)&httpreq->HttpReqFrameSnd.buffer, (const char *)rsi_itoa(RSI_HTTP_DATA_LENGTH, str));
          }
          else
          {
            strcat((char *)&httpreq->HttpReqFrameSnd.buffer, RSI_HTTP_DATA);
          }
        }
        else
        {
          strcpy((char *)&httpreq->HttpReqFrameSnd.buffer, RSI_HTTP_USERNAME);
            http_len = sizeof(RSI_HTTP_USERNAME);

          strcpy(((char *)&httpreq->HttpReqFrameSnd.buffer) + http_len, RSI_HTTP_PASSWORD);
          http_len += sizeof(RSI_HTTP_PASSWORD);

          strcpy(((char *)&httpreq->HttpReqFrameSnd.buffer) + http_len, RSI_HTTP_HOSTNAME);
          http_len += sizeof(RSI_HTTP_HOSTNAME);

          if(RSI_IP_VERSION == IP_VERSION_4)
          {
            strcpy(((char *)&httpreq->HttpReqFrameSnd.buffer) + http_len, RSI_HTTP_IP);
            http_len += sizeof(RSI_HTTP_IP);
          }
          else
          {
            strcpy(((char *)&httpreq->HttpReqFrameSnd.buffer) + http_len, RSI_HTTP_IPV6);
            http_len += sizeof(RSI_HTTP_IPV6);
          }
          strcpy(((char *)&httpreq->HttpReqFrameSnd.buffer) + http_len, RSI_HTTP_URL);
          http_len += sizeof(RSI_HTTP_URL);

          rsi_buildHttpExtendedHeader((uint8 *)httpreq->HttpReqFrameSnd.buffer + http_len, 1);

          //! Check for HTTP post data feature bit
          if(RSI_HTTPS_SUPPORT & RSI_FEAT_HTTP_POST_DATA)
          {
            //! Append HTTP content length
            http_len += strlen((const char *)rsi_itoa(RSI_HTTP_DATA_LENGTH, str));
            strcpy(((char *)&httpreq->HttpReqFrameSnd.buffer) + http_len, (const char *)rsi_itoa(RSI_HTTP_DATA_LENGTH, str));
          }
          else
          {

            http_len += strlen((char *)&(httpreq->HttpReqFrameSnd.buffer) + http_len) + 1;
            strcpy(((char *)&httpreq->HttpReqFrameSnd.buffer) + http_len, RSI_HTTP_DATA);
          }

        }

      }
      break;
    case RSI_REQ_HTTP_POST_DATA:
      {
        //! HTTP post data 
//        rsi_uHttpPostDataReq *httppost_data_req = (rsi_uHttpPostDataReq *)buffer;
      }
      break;
	  
	  case RSI_REQ_DNS_UPDATE:
      {
        //! DNS Update
        rsi_uDnsUpdate *dns_update = (rsi_uDnsUpdate *)buffer;

        //rsi_uint16_to_2bytes(dns_update->dnsUpdateFrameSnd.ip_version, RSI_IP_VERSION);
        dns_update->dnsUpdateFrameSnd.ip_version = RSI_IP_VERSION;
        strcpy((char *)dns_update->dnsUpdateFrameSnd.aZoneName,DNS_ZONE_NAME);
        strcpy((char *)dns_update->dnsUpdateFrameSnd.aHostName,DNS_HOST_NAME);
        rsi_uint16_to_2bytes(dns_update->dnsUpdateFrameSnd.uDNSServerNumber,DNS_SERVER_NUM);
        rsi_uint16_to_2bytes(dns_update->dnsUpdateFrameSnd.ttl, DNS_UPDATE_TTL);
      }
      break;
    case RSI_REQ_DNS_QRY:
      {
        //! DNS Get get
        rsi_uDnsQry *dns_qry = (rsi_uDnsQry *)buffer;

        rsi_uint16_to_2bytes(dns_qry->dnsQryFrameSnd.ip_version, RSI_IP_VERSION);
        strcpy((char *)dns_qry->dnsQryFrameSnd.aDomainName,DNS_QRY_URL);
        rsi_uint16_to_2bytes(dns_qry->dnsQryFrameSnd.uDNSServerNumber,DNS_SERVER_NUM);
      }
      break;
    case RSI_REQ_DNS_SERVER:
      {
        //! Dns server Params
        rsi_uDnsServer *dns_Server = (rsi_uDnsServer *)buffer;

        rsi_uint16_to_2bytes(dns_Server->dnsServerFrameSnd.ip_version, RSI_IP_VERSION);
        rsi_uint16_to_2bytes(dns_Server->dnsServerFrameSnd.DNSMode, RSI_DNS_CFG_MODE);
        if (RSI_IP_VERSION == IP_VERSION_4)
        {
          rsi_ascii_dot_address_to_4bytes((uint8 *)dns_Server->dnsServerFrameSnd.primary_dns_ip.ipv4_address, (int8 *)RSI_PRIMARY_DNS_IP_ADDRESS);
          rsi_ascii_dot_address_to_4bytes((uint8 *)dns_Server->dnsServerFrameSnd.secondary_dns_ip.ipv4_address, (int8 *)RSI_SECONDARY_DNS_IP_ADDRESS);
        }
        else
        {

          parse_ipv6_address(dns_Server->dnsServerFrameSnd.primary_dns_ip.ipv6_address, (uint8 *)RSI_TARGET_IPV6_ADDRESS);
          parse_ipv6_address(dns_Server->dnsServerFrameSnd.secondary_dns_ip.ipv6_address, (uint8 *)RSI_TARGET_IPV6_ADDRESS);
        }
      }
      break;
#if DHCP_USER_CLASS_SUPPORT
    case RSI_REQ_DHCP_USER_CLASS:
      {
        uint8 i;
        uint8 *usr_cls_data_arr[RSI_DHCP_USER_CLASS_MAX_COUNT] = {DHCP_USER_CLASS_DATA_1, DHCP_USER_CLASS_DATA_2};
        uint8 usr_cls_data_length_arr[RSI_DHCP_USER_CLASS_MAX_COUNT] = {DHCP_USER_CLASS_DATA_LENGTH_1, DHCP_USER_CLASS_DATA_LENGTH_2};

        //! DHCP USer Class Params
        rsi_dhcp_user_class_t *usr_cls = (rsi_dhcp_user_class_t *)buffer;

        usr_cls->mode = DHCP_USER_CLASS_MODE;
        //! Fill user class count
        usr_cls->count = DHCP_USER_CLASS_COUNT;

        //! Fill user class data
        for(i=0; i < DHCP_USER_CLASS_COUNT; i++)
        {
          if(i >= RSI_DHCP_USER_CLASS_MAX_COUNT)
          {
            break;
          }

          usr_cls->user_class_data[i].length = usr_cls_data_length_arr[i];
          memcpy(&(usr_cls->user_class_data[i].data), usr_cls_data_arr[i], usr_cls_data_length_arr[i]);
        }    
      }
      break;
#endif

    case RSI_RSP_HTTP_CREDENTIALS:
      {
        //! HTTP Credentials
        rsi_uhttpCredentials *http_credential = (rsi_uhttpCredentials *)buffer;

        strcpy((char *)(http_credential->httpCredentialsFrameSnd.username),RSI_HTTP_SERVER_USERNAME);
        strcpy((char *)(http_credential->httpCredentialsFrameSnd.password),RSI_HTTP_SERVER_PASSWORD);
      }
      break;
#if RSI_SNTP_CLIENT
    case RSI_REQ_SNTP:
      {
        //! SNTP parameters
        rsi_sntp_client_t *sntp = (rsi_sntp_client_t *)buffer;

        sntp->command_type = SNTP_COMMAND_CREATE;
        sntp->ip_version   = RSI_SNTP_IP_VERSION;

        if(sntp->ip_version == IP_VERSION_4)
        {
          rsi_ascii_dot_address_to_4bytes((uint8 *)&sntp->server_ip_address.ipv4_address,(int8 *)RSI_SNTP_SERVER_IP_ADDRESS);
        }
        else
        {
          parse_ipv6_address(sntp->server_ip_address.ipv6_address, (uint8 *)RSI_SNTP_SERVER_IPV6_ADDRESS);
        }
        sntp->sntp_method = RSI_SNTP_METHOD;
        
        rsi_uint16_to_2bytes(sntp->sntp_timeout, RSI_SNTP_TIMEOUT);

      }
      break;
#endif
#if RSI_MDNS_SD
    case RSI_REQ_MDNS:
      {
        //! mdns parameters
        rsi_mdns_t *mdns = (rsi_mdns_t *)buffer;

        mdns->command_type = MDNS_INIT;
        mdns->mdns_struct.mdns_init.ip_version = MDNS_IP_VERSION;
        *(uint16 *)mdns->mdns_struct.mdns_init.ttl = MDNS_INIT_TTL;
        strcpy((char *)&mdns->buffer[0], MDNS_HOST_NAME);           
      }
      break;
#endif   
#if RSI_SMTP_CLIENT
    case RSI_REQ_SMTP:
      {
        //! smtp client
        rsi_smtp_client_t *smtp_client = (rsi_smtp_client_t *)buffer;

        smtp_client->command_type = SMTP_CLIENT_CREATE;
      }
      break;
#endif

#if RSI_HTTP_CLIENT_PUT
    case RSI_REQ_HTTP_CLIENT_PUT:
      {
       //!http client put 
       rsi_http_client_put_req_t *http_client_put = (rsi_http_client_put_req_t *)buffer;
      
       http_client_put->command_type = HTTP_CLIENT_PUT_CREATE;
      }
      break;
#endif 
#if RSI_POP3_CLIENT
    case RSI_REQ_POP3:
      {
        //! pop3 client
        rsi_pop3_client_t *pop3_client = (rsi_pop3_client_t *)buffer;

        //! Fill POP3 command type
        pop3_client->command_type  = POP3_CLIENT_SESSION_CREATE;

        //! Fill POP3 ip version
        pop3_client->pop3_struct.pop3_client_session_create.ip_version = RSI_POP3_IP_VERSION;

        //! Check ip version
        if(RSI_POP3_IP_VERSION == IP_VERSION_4)
        {
          //! Fill IPv4 address
          rsi_ascii_dot_address_to_4bytes(((uint8 *)&(pop3_client->pop3_struct.pop3_client_session_create.server_ip_address.ipv4_address)),(uint8 *)RSI_POP3_SERVER_IPV4_ADDRESS);
        }
        else
        {
          //! Fill IPv6 address
          parse_ipv6_address(pop3_client->pop3_struct.pop3_client_session_create.server_ip_address.ipv6_address, (uint8 *)RSI_POP3_SERVER_IPV6_ADDRESS);
        }

        //! Fill POP3 server port number
        rsi_uint16_to_2bytes(pop3_client->pop3_struct.pop3_client_session_create.server_port_number, RSI_POP3_SERVER_PORT);

        //! Fill POP3 authentication type
        pop3_client->pop3_struct.pop3_client_session_create.auth_type = RSI_POP3_AUTH_TYPE;
        
        //! Fill POP3 username
        strcpy((uint8 *)pop3_client->pop3_struct.pop3_client_session_create.username, RSI_POP3_CLIENT_USERNAME);
        
        //! Fill POP3 password
        strcpy((uint8 *)pop3_client->pop3_struct.pop3_client_session_create.password, RSI_POP3_CLIENT_PASSWORD);
      }
      break;
#endif
#if RSI_FTP_CLIENT
    case RSI_REQ_FTP:
      {
        //! ftp client
        rsi_ftp_client_t *ftp_client = (rsi_ftp_client_t *)buffer;

        ftp_client->command_type = FTP_COMMAND_CREATE;
      }
      break;
#endif
    case RSI_REQ_CREATE_JSON: 
      {
        //! json
        rsi_jsonCreateObject_t *json = (rsi_jsonCreateObject_t *)buffer;

        strcpy(json->filename, JSON_FILENAME);

      }
      break;
    case RSI_REQ_GET_WEBPAGE:
      {
        //! Web Server Parameters
        rsi_uWebServer *webserver = (rsi_uWebServer *)buffer;

        rsi_uint16_to_2bytes(webserver->webServFrameSnd.Webpage_info.total_len,WEB_PAGE_LENGTH);
        strcpy((char*)&webserver->webServFrameSnd.Webpage_info.filename, WEB_PAGE_FILENAME);
        webserver->webServFrameSnd.Webpage_info.has_json_data = WEB_PAGE_HAS_JSON;         
      }
      break;
    case RSI_REQ_CLEAR_FILES:
      {
        //! Clear files
        rsi_tfs_clear_files_t *clear_file = (rsi_tfs_clear_files_t *)buffer;

        clear_file->clear = WEB_PAGE_CLEAR_ALL_FILES;    
      }
      break;
    case RSI_REQ_HOST_WEBPAGE:
      {
          /*URL response Parameters*/
           HostWebpageSnd_t *webpage_snd = (HostWebpageSnd_t *)buffer;
           memset((char *)&webpage_snd, '\0', sizeof(HostWebpageSnd_t));
      }
      break;

    case RSI_REQ_OTA_FW_UP:
      {

        rsi_uOtafReq *otaf_fw_up = (rsi_uOtafReq *)buffer;

        //! Fill ip version
        otaf_fw_up->OtafReqFrameSnd.ip_version = RSI_OTAF_IP_VERSION;

        //! Check ip version
        if(RSI_OTAF_IP_VERSION == IP_VERSION_4)
        {
          //! Fill IPv4 address
          rsi_ascii_dot_address_to_4bytes(((uint8 *)&(otaf_fw_up->OtafReqFrameSnd.server_address.ipv4_address)),(int8 *)RSI_OTAF_SERVER_IPV4_ADDRESS);
        }
        else
        {
          //! Fill IPv6 address
          parse_ipv6_address(otaf_fw_up->OtafReqFrameSnd.server_address.ipv6_address, (uint8 *)RSI_OTAF_SERVER_IPV6_ADDRESS);
        }

        //! Fill OTAF server port number
        rsi_uint32_to_4bytes(otaf_fw_up->OtafReqFrameSnd.server_port, RSI_OTAF_SERVER_PORT);

        //! Fill OTAF chunk number
        rsi_uint16_to_2bytes(otaf_fw_up->OtafReqFrameSnd.chunk_number, RSI_OTAF_CHUNK_NUMBER);
        
        //! Fill OTAF Receive timeout
        rsi_uint16_to_2bytes(otaf_fw_up->OtafReqFrameSnd.time_out, RSI_OTAF_RX_TIMEOUT);
        
        //! Fill OTAF tcp retry count
        rsi_uint16_to_2bytes(otaf_fw_up->OtafReqFrameSnd.retry_count, RSI_OTAF_TCP_RETRY_COUNT);

      }
      break;
#if RSI_MULTICAST_SUPPORT
    case RSI_REQ_MULTICAST:
      {
        //! Multicast patameters
        rsi_uMulticast *multicast = (rsi_uMulticast *)buffer;

        rsi_uint16_to_2bytes(multicast->multicastFrameSnd.ip_version, RSI_IP_VERSION);
        rsi_uint16_to_2bytes(multicast->multicastFrameSnd.req_Type, RSI_MULTICAST_MESSAGE_TYPE);
        if(RSI_IP_VERSION == IP_VERSION_4)
        {
          rsi_ascii_dot_address_to_4bytes((uint8 *)multicast->multicastFrameSnd.group_address.ipv4_address, (int8 *)RSI_MULTICAST_GROUP_IPV4_ADDRESS);
        }
        else
        {
          parse_ipv6_address(multicast->multicastFrameSnd.group_address.ipv6_address, (uint8 *)RSI_MULTICAST_GROUP_IPV6_ADDRESS);
        }
      }
      break;
#endif
#endif
    default:
      break;
  }

  //! Return filled buffer
  return buffer;
}


int  rsi_snmp_trap_init(uint8 *buffer)
{
  int snmp_buffer_len =0;
  uint8  *snmp_trap_buf;
  uint8 temp[20];

  rsi_uSnmptrap *snmp_trap = (rsi_uSnmptrap *)buffer;
  /* SNMP TRAP parameters */
  snmp_trap->snmptrapFrameSnd.snmp_version =  RSI_SNMP_VERSION;

  rsi_uint32_to_4bytes(snmp_trap->snmptrapFrameSnd.ip_version, RSI_IP_VERSION);
  if(RSI_IP_VERSION == IP_VERSION_4)
  {
    rsi_ascii_dot_address_to_4bytes(&temp[0],(int8 *)RSI_SNMP_TARGET_IP_ADDRESS);
    snmp_trap->snmptrapFrameSnd.destIPaddr.ipv4_address[3]=temp[0];
    snmp_trap->snmptrapFrameSnd.destIPaddr.ipv4_address[2]=temp[1];
    snmp_trap->snmptrapFrameSnd.destIPaddr.ipv4_address[1]=temp[2];
    snmp_trap->snmptrapFrameSnd.destIPaddr.ipv4_address[0]=temp[3];
  }
  else
  {
    parse_ipv6_address(snmp_trap->snmptrapFrameSnd.destIPaddr.ipv6_address, (uint8 *)RSI_SNMP_TARGET_IPV6_ADDRESS);
  }
  strcpy((char *)snmp_trap->snmptrapFrameSnd.community, RSI_SNMP_COMMUNITY);
  snmp_trap->snmptrapFrameSnd.trap_type = RSI_SNMP_TRAP_TYPE;
  strcpy((char *)snmp_trap->snmptrapFrameSnd.trap_oid, RSI_SNMP_TRAP_OID);
  rsi_uint32_to_4bytes(snmp_trap->snmptrapFrameSnd.elapsed_time, RSI_SNMP_ELAPSED_TIME);
  snmp_trap->snmptrapFrameSnd.obj_list_count =  RSI_SNMP_OBJECT_LIST_COUNT;


  snmp_trap_buf    = snmp_trap->snmptrapFrameSnd.snmp_buf;

  //! To prepare Ip address as a SNMP Object data type 
  snmp_buffer_len  = rsi_build_snmp_buffer((snmp_trap_buf+snmp_buffer_len), "1.2.3.4.3.2.3.2.1", SNMP_ANS1_IP_ADDRESS, 0xc0a8006b, 0, NULL);
 
  //! To prepare Integer as a SNMP Object data type 
  snmp_buffer_len  += rsi_build_snmp_buffer((snmp_trap_buf+snmp_buffer_len),"1.3.2.2.2.1.1.2", SNMP_ANS1_INTEGER, 16, 12, NULL);

  //! To prepare Octect string as a SNMP Object data type 
  snmp_buffer_len  += rsi_build_snmp_buffer((snmp_trap_buf+snmp_buffer_len), "1.4.4.4.4.4.4.3", SNMP_ANS1_OCTET_STRING, 0, 0, "Sample SNMP Trap String!!");

  //! To prepare Counter as a SNMP Object data type 
  snmp_buffer_len  += rsi_build_snmp_buffer((snmp_trap_buf+snmp_buffer_len),"1.3.2.2.2.1.1.2", SNMP_ANS1_COUNTER, 16, 12, NULL);

  //! To prepare Timer Tics as a SNMP Object data type 
  snmp_buffer_len  += rsi_build_snmp_buffer((snmp_trap_buf+snmp_buffer_len),"1.3.2.2.2.1.1.2", SNMP_ANS1_TIME_TICS, 16, 12, NULL);
  
  //! To prepare Counter64 as a SNMP Object data type 
  snmp_buffer_len  += rsi_build_snmp_buffer((snmp_trap_buf+snmp_buffer_len),"1.3.2.2.2.1.1.2", SNMP_ANS1_COUNTER64, 16, 12, NULL);
  
  //! To prepare Guage as a SNMP Object data type 
  snmp_buffer_len  += rsi_build_snmp_buffer((snmp_trap_buf+snmp_buffer_len),"1.3.2.2.2.1.1.2", SNMP_ANS1_GAUGE, 16, 12, NULL);
  
  //! To prepare Np such instance as a SNMP Object data type 
  snmp_buffer_len  += rsi_build_snmp_buffer((snmp_trap_buf+snmp_buffer_len),"1.3.2.2.2.1.1.2", SNMP_ANS1_NO_SUCH_INSTANCE, 16, 12, NULL);

  //! To prepare No such object as a SNMP Object data type 
  snmp_buffer_len  += rsi_build_snmp_buffer((snmp_trap_buf+snmp_buffer_len),"1.3.2.2.2.1.1.2", SNMP_ANS1_NO_SUCH_OBJECT, 16, 12, NULL);
  
  //! To prepare MIB view as a SNMP Object data type 
  snmp_buffer_len  += rsi_build_snmp_buffer((snmp_trap_buf+snmp_buffer_len),"1.3.2.2.2.1.1.2", SNMP_ANS1_END_OF_MIB_VIEW, 16, 12, NULL);
  
  //! Check for maximum allowed buffer length
  if(snmp_buffer_len > (RSI_SNMP_TAP_BUFFER_LENGTH))
  {
    return -1;
  }

  snmp_trap_buf[snmp_buffer_len] = '\0';

  snmp_buffer_len += sizeof(rsi_uSnmptrap) - RSI_SNMP_TAP_BUFFER_LENGTH;

  return snmp_buffer_len;

}


uint16 rsi_build_snmp_buffer(uint8 *snmp_buf, char *obj_string, uint32 data_type, uint32 data_msw, uint32 data_lsw, char *data_string)
{
  SNMP_TRAP_OBJECT snmp;

  uint16 str_len = 0;
  uint16 data_str_len = 0;

  strcpy((char *)snmp.snmp_object_string_ptr,obj_string);
  rsi_uint32_to_4bytes(snmp.snmp_object_data.snmp_object_data_type, data_type);
  rsi_uint32_to_4bytes(snmp.snmp_object_data.snmp_object_data_msw, data_msw);
  rsi_uint32_to_4bytes(snmp.snmp_object_data.snmp_object_data_lsw, data_lsw);
  rsi_uint32_to_4bytes(snmp.snmp_object_data.snmp_ip_version, RSI_IP_VERSION);

  
  if(data_type == SNMP_ANS1_IPV6_ADDRESS)
  {
    parse_ipv6_address(snmp.snmp_object_data.snmp_nxd_address.ipv6_address, (uint8 *)RSI_SNMP_TARGET_IPV6_ADDRESS);
  }

  if(data_type != SNMP_ANS1_OCTET_STRING)
  {
    data_string = NULL;
  }

  if(data_string)
  {
    data_str_len = strlen(data_string);
  }

  rsi_uint32_to_4bytes(snmp.snmp_object_data.snmp_object_octet_string_size, data_str_len);

  memcpy(snmp_buf, &snmp, sizeof(SNMP_TRAP_OBJECT));

  str_len += sizeof(SNMP_TRAP_OBJECT);

  if(data_string)
  {
    memcpy(&snmp_buf[str_len], data_string, data_str_len);
    str_len += data_str_len + 1;
  }
  else
  {
    str_len += 1;
    snmp_buf[str_len] = '\0';
  }

  return str_len; 
}

