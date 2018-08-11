/**
 * @file       rsi_store_config_init.c
 * @version	   3.6
 * @date 	   2013-Aug-2
 *
 * Copyright(C) Redpine Signals 2013
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief INIT STRUCT: Initializes the user store configuration structure
 * @section Description
 * This file contains function to initialize the user store configuration,and supporting API's
 * @Fuunctions defined
 * reverse_translate_channel
 * get_frequency
 * rsi_userstorecfg_init
 */



/**
 * Includes
 */
#include "rsi_global.h"
#include "rsi_app_util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#if ENABLE_USER_STORE_CONFIGURATION
/*====================================================*/
/**
 * @fn			    void rsi_userstorecfg_init(struct sc_params_s *ptr_usercfg)
 * @brief		    Initialize the user store configuration parameters structure
 * @param[in]	    struct sc_params_s *ptr_usercfg, pointer to the sc_params_s structure
 * @param[out]	    none
 * @return		    none
 * @description
 * This function is used to initialize the user store configuration structure
 *  with the configuration provided by the user
 */

void rsi_user_store_config_init(rsi_user_store_config_t *ptr_usercfg)
{

  int i,j;
  uint8 MAC[6];

  //! Memset user store config structure
  memset((uint8 *)ptr_usercfg, '\0', sizeof(rsi_user_store_config_t));

  ptr_usercfg->cfg_enable = USER_CFG_CFG_ENABLE;

  //! Opermode
  rsi_uint32_to_4bytes(ptr_usercfg->opermode, USER_CFG_OPERMODE);
  rsi_uint32_to_4bytes(ptr_usercfg->feature_bit_map, USER_CFG_FEATURE_BIT_MAP);
  rsi_uint32_to_4bytes(ptr_usercfg->tcp_ip_feature_bit_map, USER_CFG_TCP_IP_FEATURE_BIT_MAP);
  rsi_uint32_to_4bytes(ptr_usercfg->custom_feature_bit_map, USER_CFG_CUSTOM_FEATURE_BIT_MAP);
  rsi_uint32_to_4bytes((uint8 *)ptr_usercfg->ext_custom_feature_bit_map, USER_CFG_EXT_CUSTOM_FEATURE_BIT_MAP);

  //! Band
  ptr_usercfg->band =  USER_CFG_BAND;

  //! Join SSID
  strcpy((char *)ptr_usercfg->join_ssid, USER_CFG_JOIN_SSID);

  ptr_usercfg->uRate     =  USER_CFG_URATE;

  ptr_usercfg->uTxPower  = USER_CFG_UTX_POWER;

  ptr_usercfg->csec_mode = USER_CFG_CHANNEL_SECURITY_MODE;
  ptr_usercfg->join_feature_bitmap = USER_CFG_JOIN_FEAT_BIT_MAP;
  rsi_uint32_to_4bytes(ptr_usercfg->listen_interval, USER_CFG_LISTEN_INTERVAL);

#if (USER_CFG_WLAN_OPERMODE == 0 ||USER_CFG_WLAN_OPERMODE == 2)
  ptr_usercfg->scan_ssid_len = strlen(USER_CFG_SCAN_SSID);
  strcpy((char *)ptr_usercfg->psk, USER_CFG_PSK);
  strcpy((char *)ptr_usercfg->scan_ssid, USER_CFG_SCAN_SSID);
  ptr_usercfg->scan_cnum = USER_CFG_SCAN_CHANN_NUM;
#endif

#if(USER_CFG_TCP_STACK_USED == 1 ||USER_CFG_TCP_STACK_USED == 3 )
  ptr_usercfg->dhcp_enable = USER_CFG_DHCP_ENABLE;
  rsi_ascii_dot_address_to_4bytes((uint8 *)ptr_usercfg->ip, (int8 *)USER_CFG_IPV4_ADDRESS);
  rsi_ascii_dot_address_to_4bytes((uint8 *)ptr_usercfg->sn_mask, (int8 *)USER_CFG_SUBNETMASKV4_ADDRESS);
  rsi_ascii_dot_address_to_4bytes((uint8 *)ptr_usercfg->dgw, (int8 *)USER_CFG_GATEWAYV4_ADDRESS);
#endif

#if (USER_CFG_WLAN_OPERMODE == 2)
  strcpy((char *)ptr_usercfg->eap_method, USER_CFG_EAP_METHOD);
  strcpy((char *)ptr_usercfg->inner_method, USER_CFG_INNER_METHOD);
  strcpy((char *)ptr_usercfg->user_identity, USER_CFG_USER_IDENTITY);
  strcpy((char *)ptr_usercfg->passwd, USER_CFG_PASSWORD);
  strcpy((char *)ptr_usercfg->private_key_password, USER_CFG_PRIVATE_KEY_PASSWORD);
#endif

#if (USER_CFG_WLAN_OPERMODE == 1)
  rsi_uint16_to_2bytes(ptr_usercfg->go_intent, USER_CFG_GO_INTENT);
  strcpy((char *)ptr_usercfg->device_name,USER_CFG_DEVICE_NAME);
  rsi_uint16_to_2bytes(ptr_usercfg->operating_channel, USER_CFG_OPERATING_CHANNEL);
  strcpy((char *)ptr_usercfg->ssid_postfix, USER_CFG_SSID_POSTFIX);
  strcpy((char *)ptr_usercfg->psk_key, USER_CFG_PSK_KEY);
#endif
#if (USER_CFG_WLAN_OPERMODE == 0 ||USER_CFG_WLAN_OPERMODE == 2)
#if RSI_STORE_PMK_SUPPORT
  for(i=0 ,j=0 ; i < 64 && j < 32; i+=2,j++)
  {
    if(USER_CFG_PMK[i] && USER_CFG_PMK[i + 1])
    {
      ptr_usercfg->pmk[j]  = ((uint16 )convert_lower_case_to_upper_case(USER_CFG_PMK[i])) * 16;
      ptr_usercfg->pmk[j] += convert_lower_case_to_upper_case(USER_CFG_PMK[i + 1]);
    }
    else
    {
      ptr_usercfg->pmk[j]=0;
    }
  }
#endif
#endif
#if (USER_CFG_WLAN_OPERMODE == 6)
  rsi_uint16_to_2bytes(ptr_usercfg->apconfig.dtim_period, USER_CFG_APCONFIG_DTIM_PERIOD);
  rsi_uint16_to_2bytes(ptr_usercfg->apconfig.beacon_interval, USER_CFG_APCONFIG_BEACON_INTERVAL);
  rsi_uint16_to_2bytes(ptr_usercfg->apconfig.channel_no, USER_CFG_APCONFIG_CHANNEL_NUM);
  rsi_uint16_to_2bytes(ptr_usercfg->apconfig.max_sta_support, USER_CFG_APCONFIG_MAX_STA_SUPPORT);

  strcpy((char *)ptr_usercfg->apconfig.ssid, USER_CFG_APCONFIG_SSID);
  ptr_usercfg->apconfig.ap_keepalive_type = USER_CFG_AP_KEEPALIVE_TYPE;
  ptr_usercfg->apconfig.ap_keepalive_period = USER_CFG_AP_KEEPALIVE_PERIOD;
  ptr_usercfg->apconfig.security_type = USER_CFG_APCONFIG_SECURITY_TYPE;
  ptr_usercfg->apconfig.encryp_mode = USER_CFG_APCONFIG_ENCRYP_MODE;
  strcpy((char *)ptr_usercfg->apconfig.psk, USER_CFG_APCONFIG_PSK);
#endif
  rsi_ascii_mac_address_to_6bytes((uint8 *)&ptr_usercfg->module_mac, (int8 *)USER_CFG_MODULE_MAC);

  rsi_uint16_to_2bytes(ptr_usercfg->antenna_select, USER_CFG_ANTENNA_SELECT);

#if( USER_CFG_WLAN_OPERMODE == 0)
#if	RSI_STORE_WEP_KEY_SUPPORT
  rsi_uint16_to_2bytes(ptr_usercfg->wep_key.index,RSI_WEP_INDEX);
  strcpy((char *)ptr_usercfg->wep_key.key[0], (char *)USER_CFG_WEPKEY_KEY0);
  strcpy((char *)ptr_usercfg->wep_key.key[1], (char *)USER_CFG_WEPKEY_KEY1);
  strcpy((char *)ptr_usercfg->wep_key.key[2], (char *)USER_CFG_WEPKEY_KEY2);
  strcpy((char *)ptr_usercfg->wep_key.key[3], (char *)USER_CFG_WEPKEY_KEY3);
#endif
#endif

#if(USER_CFG_TCP_STACK_USED == 2 ||USER_CFG_TCP_STACK_USED == 3 )
#if RSI_STORE_IPV6_ENABLE
  rsi_uint16_to_2bytes(ptr_usercfg->dhcp6_enable, USER_CFG_DHCPV6_ENABLE);
  rsi_uint16_to_2bytes(ptr_usercfg->prefix_length, USER_CFG_PREFIX_LENGTH);
  parse_ipv6_address((uint32 *)ptr_usercfg->ip6, (uint8 *)USER_CFG_IPV6_ADDRESS);
  parse_ipv6_address((uint32 *)ptr_usercfg->dgw6, (uint8 *)USER_CFG_GATEWAYV6_ADDRESS);
#endif
#endif

  ptr_usercfg->tcp_stack_used = USER_CFG_TCP_STACK_USED;

#if (USER_CFG_WLAN_OPERMODE == 0 ||USER_CFG_WLAN_OPERMODE == 2)
  rsi_uint16_to_2bytes(ptr_usercfg->chan_bitmap_magic_code , RSI_MAGIC_CODE);
  if((!USER_CFG_SCAN_CHANN_NUM) && !(strlen(USER_CFG_SCAN_SSID)))
  { 
    ptr_usercfg->scan_feature_bitmap = USER_CFG_SCAN_FEAT_BITMAP;
  }
  else
  {
    ptr_usercfg->scan_feature_bitmap = 0;
  }
  rsi_uint32_to_4bytes(ptr_usercfg->scan_chan_bitmap_stored_2_4_GHz, (uint32 )USER_CFG_SCAN_CHAN_BITMAP_STORED_2_4_GHZ);
  rsi_uint32_to_4bytes(ptr_usercfg->scan_chan_bitmap_stored_5_GHz, (uint32 )USER_CFG_SCAN_SCAN_CHAN_BITMAP_STORED_5_GHZ);
#endif

#if (USER_CFG_WLAN_OPERMODE == 0 || USER_CFG_WLAN_OPERMODE == 2 )
  ptr_usercfg->multi_probe =  USER_CFG_BGSCAN_MULTI_PROBE;
  rsi_uint16_to_2bytes(ptr_usercfg->bgscan_magic_code, RSI_MAGIC_CODE);
  rsi_uint16_to_2bytes(ptr_usercfg->bgscan_enable, USER_CFG_BGSCAN_ENABLE);
  rsi_uint16_to_2bytes(ptr_usercfg->bgscan_threshold,  USER_CFG_BGSCAN_THRESHOLD);
  rsi_uint16_to_2bytes(ptr_usercfg->rssi_tolerance_threshold,  USER_CFG_BGSCAN_RSSI_TOLERANCE_THRESHOLD);
  rsi_uint16_to_2bytes(ptr_usercfg->bgscan_periodicity,  USER_CFG_BGSCAN_PERIODICITY);
  rsi_uint16_to_2bytes(ptr_usercfg->active_scan_duration, USER_CFG_BGSCAN_ACTIVE_SCAN_DURATION);
  rsi_uint16_to_2bytes(ptr_usercfg->passive_scan_duration,  USER_CFG_BGSCAN_PASSIVE_SCAN_DURATION);
#endif

#if (USER_CFG_WLAN_OPERMODE == 0 || USER_CFG_WLAN_OPERMODE == 2)
  rsi_uint16_to_2bytes(ptr_usercfg->roam_magic_code, RSI_MAGIC_CODE);
  rsi_uint32_to_4bytes(ptr_usercfg->roam_params_stored.roamParamsFrameSnd.roam_enable, USER_CFG_ROAM_ENABLE);
  rsi_uint32_to_4bytes(ptr_usercfg->roam_params_stored.roamParamsFrameSnd.roam_threshold,  USER_CFG_ROAM_THRESHOLD);
  rsi_uint32_to_4bytes(ptr_usercfg->roam_params_stored.roamParamsFrameSnd.roam_hysteresis, USER_CFG_ROAM_HYSTERESIS);
#endif

#if(USER_CFG_WLAN_OPERMODE == 0|| USER_CFG_WLAN_OPERMODE == 2)
  rsi_uint16_to_2bytes(ptr_usercfg->rejoin_magic_code, RSI_MAGIC_CODE);
  rsi_uint32_to_4bytes(ptr_usercfg->rejoin_param_stored.rsi_max_try, USER_CFG_REJOIN_MAX_RETRY_COUNT);
  rsi_uint32_to_4bytes(ptr_usercfg->rejoin_param_stored.rsi_scan_interval, USER_CFG_REJOIN_SCAN_INTERVAL);
  rsi_uint32_to_4bytes(ptr_usercfg->rejoin_param_stored.rsi_beacon_missed_count, USER_CFG_REJOIN_BEACON_MISSED_COUNT);
  rsi_uint32_to_4bytes(ptr_usercfg->rejoin_param_stored.rsi_first_time_retry_enable, USER_CFG_REJOIN_FIRST_TIME_RETRY_ENABLE);
#endif

  ptr_usercfg->region_request_from_host  = USER_CFG_REGION_REQUEST_FROM_HOST;
  ptr_usercfg->rsi_region_code_from_host = USER_CFG_REGION_CODE_FROM_HOST;
  ptr_usercfg->region_code               = USER_CFG_REGION_CODE;

#if FIPS_MODE_ENABLE
  rsi_uint16_to_2bytes(ptr_usercfg->fips_bypass_mode ,USER_CFG_FIPS_BYPASS_MODE);
  ptr_usercfg->keys_restore = USER_CFG_KEYS_RESTORE;
#endif

#if USER_CFG_MULTICAST_SUPPORT
  rsi_uint16_to_2bytes(ptr_usercfg->multicast_magic_code,RSI_MAGIC_CODE);
  rsi_ascii_mac_address_to_6bytes((uint8 *)MAC, (int8 *)USER_CFG_MULTICAST_MAC_ADDRESS);
  if((USER_CFG_MULTICAST_MAC_CMD_TYPE == RSI_MULTICAST_MAC_ADD_BIT) || (USER_CFG_MULTICAST_MAC_CMD_TYPE == RSI_MULTICAST_MAC_CLEAR_BIT))
  {
    rsi_uint16_to_2bytes(ptr_usercfg->multicast_bitmap ,(USER_CFG_MULTICAST_MAC_CMD_TYPE | (multicast_mac_hash(MAC)) << 8));
  }
  else
  {
    rsi_uint16_to_2bytes(ptr_usercfg->multicast_bitmap ,USER_CFG_MULTICAST_MAC_CMD_TYPE);
  }
#endif

#if USER_CFG_POWER_MODE_SUPPORT
  rsi_uint16_to_2bytes(ptr_usercfg->powermode_magic_code,RSI_MAGIC_CODE);
  ptr_usercfg->powermode = USER_CFG_POWER_MODE;
  ptr_usercfg->ulp_mode = USER_CFG_ULP_MODE;
  ptr_usercfg->listen_interval_dtim = USER_CFG_LISTEN_INTERVAL_DTIM;
#endif

#if USER_CFG_WMM_PS_SUPPORT
  rsi_uint16_to_2bytes(ptr_usercfg->wmm_ps_magic_code,RSI_MAGIC_CODE);
  ptr_usercfg->wmm_ps_enable = USER_CFG_WMM_PS_ENABLE ;
  ptr_usercfg->wmm_ps_type = USER_CFG_WMM_PS_TYPE;
  rsi_uint32_to_4bytes(ptr_usercfg->wmm_ps_wakeup_interval,USER_CFG_WMM_PS_WAKEUP_INTERVAL);
  ptr_usercfg->wmm_ps_uapsd_bitmap = USER_CFG_WMM_PS_UAPSD_BITMAP;
#endif
#if USER_CFG_HTTP_SERVER_CREDENTIALS_SUPPORT
  ptr_usercfg->http_credentials_avail = 2;
  strcpy((char *)ptr_usercfg->http_username, USER_CFG_HTTP_SERVER_USERNAME);
  strcpy((char *)ptr_usercfg->http_password, USER_CFG_HTTP_SERVER_PASSWORD);
#endif
#if USER_CFG_JOIN_BSSID_SUPPORT
  rsi_ascii_mac_address_to_6bytes((uint8 *)&ptr_usercfg->join_bssid, (int8 *)USER_CFG_JOIN_BSSID);
#endif
#if USER_FAST_PSP_SUPPORT
  rsi_uint16_to_2bytes(ptr_usercfg->monitor_interval, USER_CFG_FAST_PSP_MONITOR_INTERVAL);
  ptr_usercfg->fast_psp_enable = USER_CFG_FAST_PSP_ENABLE ;
#endif

#if USER_REQ_TIMEOUT_CMD_SUPPORT
  rsi_uint16_to_2bytes(ptr_usercfg->timeout_value, USER_CFG_TIMEOUT_VALUE);
  rsi_uint32_to_4bytes(ptr_usercfg->timeout_bitmap, USER_CFG_TIMEOUT_BITMAP);
#endif

#if USER_HT_CAPS_SUPPORT
  rsi_uint16_to_2bytes(ptr_usercfg->ht_caps_magic_word, USER_CFG_HT_CAPS_MAGIC_WORD);
  rsi_uint16_to_2bytes(ptr_usercfg->htCapsFrameSnd.mode_11n_enable, USER_CFG_HT_CAPS_11N_ENABLE);
  rsi_uint16_to_2bytes(ptr_usercfg->htCapsFrameSnd.ht_caps_bitmap, USER_CFG_HT_CAPS_BITMAP);

#endif

#if USER_CONCURRENT_MODE_AP_PARAMS_SUPPORT

  ptr_usercfg->dhcp_ap_enable = USER_CFG_DHCP_AP_ENABLE;

  rsi_ascii_dot_address_to_4bytes((uint8 *)ptr_usercfg->ap_ip, (int8 *)USER_CFG_AP_IPV4_ADDRESS);
  rsi_ascii_dot_address_to_4bytes((uint8 *)ptr_usercfg->ap_sn_mask, (int8 *)USER_CFG_AP_SUBNETMASKV4_ADDRESS);
  rsi_ascii_dot_address_to_4bytes((uint8 *)ptr_usercfg->ap_dgw, (int8 *)USER_CFG_AP_GATEWAYV4_ADDRESS);

  rsi_uint16_to_2bytes(ptr_usercfg->dhcp6_ap_enable, USER_CFG_DHCPV6_AP_ENABLE);
  rsi_uint16_to_2bytes(ptr_usercfg->ap_prefix_length, USER_CFG_DHCPV6_PREFIX_LENGTH);
  parse_ipv6_address((uint32 *)ptr_usercfg->ap_ip6, (uint8 *)USER_CFG_AP_IPV6_ADDRESS);
  parse_ipv6_address((uint32 *)ptr_usercfg->ap_dgw6, (uint8 *)USER_CFG_AP_GATEWAYV6_ADDRESS);
#endif

return;
}
#endif
