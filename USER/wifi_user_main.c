/**
 * @file     main.c
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
 #include "wificonf.h"
 #include "userwifi.h"
 #include "typetrans.h"
#include "rsi_global.h"
#include "rsi_config.h"
#include "rsi_app_util.h"
#include "rsi_hal.h"
#ifdef RSI_HAL
#include "rsi_spi_cmd.h"
#endif
#include "rsi_app.h"
#include <string.h>
#if JSON_LOAD
#include "sensor_data.h"
#endif

#ifdef LINUX_PLATFORM
#include "rsi_nl_app.h"
#include "rsi_wireless_copy.h"
#include <sys/ioctl.h>
#endif
#if FIPS_MODE_ENABLE
#include "rsi_fips.h"
#endif
#if RSI_PUF_ENABLE
#include "rsi_puf.h"
#endif
/** Global Variables
 */

/* Application control block */
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

#if ENTERPRISE_MODE
#include "../../../../apis/wlan/ref_apps/include/wifiuser.pem"
#include "../../../../apis/wlan/ref_apps/include/testuser.pac"
#endif
#if (CLIENT_MODE && SSL_SUPPORT)
#include "../../../../apis/wlan/ref_apps/include/cacert.pem"
#include "../../../../apis/wlan/ref_apps/include/clientcert.pem"
#include "../../../../apis/wlan/ref_apps/include/clientkey.pem"
#include "../../../../apis/wlan/ref_apps/include/servercert.pem"
#include "../../../../apis/wlan/ref_apps/include/serverkey.pem"
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

#if RSI_HTTP_POST_DATA_SUPPORT
uint8 http_file[] = {
#include "../../../../apis/wlan/ref_apps/include/http_post_data.txt"
};

#define RSI_HTTP_POST_DATA_CHUNK_LEN  900
#endif

#if RSI_HTTP_CLIENT_PUT
#define RSI_HTTP_PUT_DATA_CHUNK_LEN  900
uint8 http_put_file[] = {
#include "../../../../apis/wlan/ref_apps/include/http_post_data.txt"
};
#endif
#ifdef RSI_FTP_CLIENT
uint8 ftp_file[] = {
#include "../../../../apis/wlan/ref_apps/include/ftp_file_write.txt"
};
#endif

#if RSI_POP3_CLIENT
uint16 pop3_mail_index;
#endif

/* Defines number of OIDs currently supported */
#define MAX_OIDS_SUPPORT        69

/* Contains list of OIDs currently supported */
volatile static const uint8 oid_list[MAX_OIDS_SUPPORT][MAX_OID_LENGTH] = {"1.3.6.1.2.1.4.10",
	"",
	"",
	"1.3.6.1.2.1.4.3",
	"1.3.6.1.2.1.4.9",
	"",
	"1.3.6.1.2.1.4.6",
	"1.3.6.1.2.1.4.15",
	"1.3.6.1.2.1.4.16",
	"1.3.6.1.2.1.4.4",
	"",
	"1.3.6.1.2.1.4.5",
	"1.3.6.1.2.1.4.7",
	"1.3.6.1.2.1.4.11",
	"1.3.6.1.2.1.4.12",
	"",
	"",
	"",
	"",
	"1.3.6.1.2.1.4.17",
	"1.3.6.1.2.1.4.18",
	"1.3.6.1.2.1.4.19",
	"1.3.6.1.2.1.4.14",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"1.3.6.1.2.1.7.4",
	"",
	"1.3.6.1.2.1.7.1",
	"",
	"1.3.6.1.2.1.7.3",
	"1.3.6.1.2.1.7.2",
	"",
	"",
	"1.3.6.1.2.1.6.11",
	"",
	"1.3.6.1.2.1.6.10",
	"",
	"1.3.6.1.2.1.6.14",
	"",
	"",
	"",
	"1.3.6.1.2.1.6.6",
	"1.3.6.1.2.1.6.5",
	"",
	"1.3.6.1.2.1.6.7",
	"1.3.6.1.2.1.6.12",
	"1.3.6.1.2.1.6.8",
	"1.3.6.1.2.1.6.15",
	"1.3.6.1.2.1.5.1",
	"",
	"1.3.6.1.2.1.5.2",
	"1.3.6.1.2.1.5.15",
	"1.3.6.1.2.1.5.21",
	"",
	"",
	"1.3.6.1.2.1.5.9",
	"1.3.6.1.2.1.5.8",
	"1.3.6.1.2.1.5.22",
	"",
	"",
	"",
	"",
	"",
	"1.3.6.1.2.1.5.14"
};



/* Contains type of OIDs currently suppiorted */
volatile static const uint8 oid_type[MAX_OIDS_SUPPORT] = {SNMP_ANS1_COUNTER,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_COUNTER,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_NO_SUCH_OBJECT,
	SNMP_ANS1_COUNTER,
};



/* function declarations */
int wifi_main(int app_mode);
int16 rsi_wifi_init(void);
rsi_uCmdRsp *rsi_parse_response(uint8 *rsp);
uint8 *rsi_wrapper_to_rsp(uint8 *rsp, uint8 rsp_type);
void  rsi_receive_data_packet(uint8 *payloadPtr);
int16 rsi_per_cont_wave_mode(rsi_uPerMode *uPerModeFrame, int8 per_cw_mode_state);


int RspCode =0,retval,tmp=0;

u8 WIFI_Conf(void)
{
	/*opermode配置指令 */					//this is command
	retval = rsi_oper_mode((rsi_uOperMode *)rsi_fill_parameters(RSI_REQ_OPERMODE,&rsi_app_cb.send_buffer[0]));
	RspCode=Read_PKT();
	if(RspCode!=RSI_REQ_OPERMODE||rsi_app_cb.error_code!=0)
	{
		return 1;//Hard_reset();
	}else{
		
	}

	/*频段选择*/
	retval = rsi_band(RSI_BAND); 			//this is command
	RspCode=Read_PKT();        //读取读取响应

	/*init指令*/
	retval = rsi_init();                 	//init基带和RF组件
	RspCode=Read_PKT();
//	LOGS("MAC:%0.2X.%0.2X.%0.2X.%0.2X.%0.2X.%0.2X\r\n",
//	rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.initResponse.macAddress1[0],
//	rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.initResponse.macAddress1[1],
//	rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.initResponse.macAddress1[2],
//	rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.initResponse.macAddress1[3],
//	rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.initResponse.macAddress1[4],
//	rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.initResponse.macAddress1[5]
//	);//打印mac地址

	/*选择天线 和增益*/
	//0：内部天线；1：外部天线
	retval = rsi_select_antenna(1,8,8);                  //init
	RspCode=Read_PKT();

	/*查询固件版本*/
 	RspCode=rsi_query_fw_version();          //this is command
	RspCode=Read_PKT();
	#if PRINT_UART_LOG
	printf("FWversion:%s\r\n",rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.qryFwversionFrameRcv.fwversion);
	#endif
	if(RSI_WIFI_OPER_MODE == RSI_WIFI_CLIENT_MODE_VAL)	{			
	//STATION
	/*WIFI模块为station 模式
	RSI_WIFI_OPER_MODE 0

	#define RSI_TCP_IP_FEATURE_BIT_MAP (TCP_IP_FEAT_DHCPV4_CLIENT | TCP_IP_FEAT_DHCPV4_SERVER|TCP_IP_FEAT_HTTP_SERVER)

	*/ 	
		/*scan扫描指令*/							//this is command
		RspCode = rsi_scan((rsi_uScan *)rsi_fill_parameters(RSI_REQ_SCAN,&rsi_app_cb.send_buffer[0]));  //??
		RspCode=Read_PKT();	                //Join  0x14 
		if(RspCode!=RSI_REQ_SCAN||rsi_app_cb.error_code!=0)
		{
			return 1;
		}else{
			tmp=0;
			#if PRINT_UART_LOG
			printf("scan num:%d\r\n",rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.scanResponse.scanCount[0]);
			#endif
			while(rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.scanResponse.scanCount[0]--)
			{
//				#if PRINT_UART_LOG
//				LOGS("%d.SSID:%s",tmp,rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.scanResponse.strScanInfo[tmp].ssid);
//				LOGS("  securityMode:%d",rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.scanResponse.strScanInfo[tmp].securityMode);
//				LOGS("  rfChannel:%d",rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.scanResponse.strScanInfo[tmp].rfChannel);
//				LOGS("  rssiVal:%d",rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.scanResponse.strScanInfo[tmp].rssiVal);
//				LOGS("  uNetworkType:%d\r\n",rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.scanResponse.strScanInfo[tmp].uNetworkType);
//				#endif
				tmp++;
			}
			
		}
		/*加入命令*/								//this is command
		RspCode = rsi_join((rsi_uJoin *)rsi_fill_parameters(RSI_REQ_JOIN,&rsi_app_cb.send_buffer[0]));      //??
		RspCode=Read_PKT();	                //Join  0x14 

		/*配置IP DHCP*/								//this is command			
		RspCode = rsi_ip_param_set((rsi_uIpparam *)rsi_fill_parameters(RSI_REQ_IPPARAM_CONFIG,&rsi_app_cb.send_buffer[0]));         //DHCP or ??
		RspCode=Read_PKT();	
	}else if(RSI_WIFI_OPER_MODE == RSI_WIFI_AP_MODE_VAL){
	//AP	0//   AP   AP   AP   AP   AP   AP   AP   AP   AP   AP
	/*WIFI模块AP热点,模式 注意下细节*/
		/*配置AP IP必须静态*/						//this is command	
		//这里面会把所有参数包括ssid都加入到数据包中
		u8 * nodeIdStr = itoa(nodeId);//包括最后一个0
		strcpy((char*)RSI_JOIN_SSID,NODE_AP_NAME_HEAD);strcpy((char*)(RSI_JOIN_SSID+strlen(NODE_AP_NAME_HEAD)),(c8*)nodeIdStr);//AP的名称，后面会有一个0，作为结束
		RspCode = rsi_ip_param_set((rsi_uIpparam *)rsi_fill_parameters(RSI_REQ_IPPARAM_CONFIG,&rsi_app_cb.send_buffer[0]));         //DHCP or ??
		RspCode=Read_PKT();
		if(RspCode!=RSI_REQ_IPPARAM_CONFIG||rsi_app_cb.error_code!=0)
		{
			while(1){//设置参数失败
				#if PRINT_UART_LOG
				printf("Module AP Paras Filled Unsuccessfully!\r\n");
				#endif
				dealCmdMsg(&CMD_RX_BUF);
				delay_ms(1000);
			};
		}else{
			#if PRINT_UART_LOG
			printf("Module AP Para Filled Successfully!\r\n");
			#endif		
		}

		/*配置AP参数*/								//this is command
		RspCode = rsi_set_ap_config((rsi_apconfig *)rsi_fill_parameters(RSI_REQ_APCONFIG,&rsi_app_cb.send_buffer[0]));
		RspCode=Read_PKT();

		if(RspCode!=RSI_REQ_APCONFIG||rsi_app_cb.error_code!=0)
		{
			while(1){//设置参数失败
				#if PRINT_UART_LOG
				printf("Module AP Paras Config Unsuccessfully!\r\n");
				#endif
				dealCmdMsg(&CMD_RX_BUF);
				delay_ms(1000);
			};
		}else{
			#if PRINT_UART_LOG
			printf("Module AP Para Config Successfully!\r\n");
			#endif		
		}
		
		/*加入AP 并启动*/							//this is command
		RspCode = rsi_join((rsi_uJoin *)rsi_fill_parameters(RSI_REQ_JOIN,&rsi_app_cb.send_buffer[0]));      //??
		RspCode=Read_PKT();

		#if PRINT_UART_LOG
		printf("Module AP Created(Func:rsi_join) Successfully!\r\n");
		#endif		
	}

		
	#if RSI_MULTICAST_SUPPORT //如果支持组播
		rsi_multicast((rsi_uMulticast *)rsi_fill_parameters(RSI_REQ_MULTICAST,&rsi_app_cb.send_buffer[0]));
		#if RSI_MULTICAST_FILTER_ENABLE//设置滤波
			rsi_multicast_mac_filter(RSI_MULTICAST_MAC_CMD_TYPE,RSI_MULTICAST_MAC_ADDRESS);
		#endif

	#endif
		
	/*STA模式才使用的指令.才有效*/	
	if(RSI_WIFI_OPER_MODE == RSI_WIFI_CLIENT_MODE_VAL){
		/*查询net参数 [成功链接之后]*/
		RspCode=rsi_query_net_parms();         		//this is command
		RspCode=Read_PKT();
		
		/*查询RSSI [成功链接之后]*/
		RspCode=rsi_query_rssi();          			//this is command
		RspCode=Read_PKT();
	//	LOGS("RSSI:0x%0.2X\r\n",rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.rssiFrameRcv.rssiVal[0]);	
	}
	RspCode=RspCode+1;
		
	return 0;
}

//#include <WyzBee_Ext.h>
u8 WIFI_BOOT(void)
{
	/*清除Buff数据*/
	rsi_app_cb.pkt_pending=0;
	memset(&rsi_app_cb, 0, sizeof(rsi_app_cb));	
	/*检查SPi是否和模块正常通讯*/
	/*检查SPI  IO 硬件是否正常*/
	RspCode = rsi_sys_init();
	if(RspCode != 0)
	{
		printf("Module Sys Inited Unsuccessfully!\r\n");
		return 1;
	}
	/*加载BOOT*/
	do{																					//GPIO_Bypass
		RspCode = rsi_waitfor_boardready();
		if((RspCode < 0) && (RspCode != -3))
			return 1;
	}while(RspCode == -3);
	/*选择固件*/
	RspCode = rsi_select_option(RSI_HOST_BOOTUP_OPTION);
	if(RspCode < 0){
		printf("Module Selected FW Unsuccessfully!\r\n");
		return 1;
	}
	/*等待card read  Rsp=0x89*/
	RspCode=Read_PKT();
	if(RspCode!=0x89||rsi_app_cb.error_code!=0)
	{		
		//TODO
		return 1;//Hard_reset();
	}
	
	return 0;
}

//void wifi_set(void)
//{
//	goto WIFI_SET;
//}

unsigned int dumm=0;

void OpenSocket(uint8 *destIP,unsigned short destSocket,unsigned short moduleSocket,unsigned short polo )
{
	rsi_uSocket rsi_Socket;
   memset(&rsi_Socket,0,sizeof(rsi_Socket));
	rsi_uint16_to_2bytes(rsi_Socket.socketFrameSnd.ip_version,IP_VERSION_4);
	rsi_uint16_to_2bytes(rsi_Socket.socketFrameSnd.moduleSocket,moduleSocket);
	rsi_uint16_to_2bytes(rsi_Socket.socketFrameSnd.destSocket,destSocket); 
	rsi_uint16_to_2bytes(rsi_Socket.socketFrameSnd.socketType,polo); 
	rsi_uint16_to_2bytes(rsi_Socket.socketFrameSnd.max_count, RSI_MAX_LTCP_CONNECTIONS); 
	rsi_uint32_to_4bytes(rsi_Socket.socketFrameSnd.tos, RSI_TOS);

	rsi_Socket.socketFrameSnd.ssl_bitmap   = SOCKET_FEATURE;
	rsi_Socket.socketFrameSnd.ssl_ciphers  = SSL_CIPHERS;
	strcpy((char *)rsi_Socket.socketFrameSnd.webs_resource_name, WEBS_RESOURCE_NAME);
	strcpy((char *)rsi_Socket.socketFrameSnd.webs_host_name, WEBS_HOST_NAME);
	rsi_Socket.socketFrameSnd.tcp_retry_count = TCP_RETRANMISSIONS_COUNT; 
	rsi_Socket.socketFrameSnd.socket_bitmap   = SOCKET_BITMAP;//BIT(2); 
	rsi_Socket.socketFrameSnd.rx_window_size  = TCP_RX_WINDOW_SIZE; 

	if(RSI_IP_VERSION == IP_VERSION_4) 
		memcpy(rsi_Socket.socketFrameSnd.destIpaddr.ipv4_address,destIP,4);
		//rsi_ascii_dot_address_to_4bytes((uint8 *)rsi_Socket.socketFrameSnd.destIpaddr.ipv4_address,(int8 *) destIP);	
	else
		parse_ipv6_address(rsi_Socket.socketFrameSnd.destIpaddr.ipv6_address, (uint8 *)RSI_TARGET_IPV6_ADDRESS);	
	
	rsi_socket(&rsi_Socket);
}



int Read_PKT(void)
{
	/*防止超时的一个计数器*/
	dumm=0x8FFFFFFF;
	while((rsi_app_cb.pkt_pending ==0)&&dumm--);
	if(dumm<=0)return -1;

	rsi_app_cb.pkt_pending -=1;  
	rsi_frame_read(rsi_app_cb.read_packet_buffer);                     //读取数据帧
	rsi_app_cb.uCmdRspFrame = rsi_parse_response(rsi_app_cb.read_packet_buffer);    //转换uCmdRspFrame

	rsi_app_cb.error_code = rsi_bytes2R_to_uint16(rsi_app_cb.uCmdRspFrame->status);
	return  rsi_bytes2R_to_uint16(rsi_app_cb.uCmdRspFrame->rspCode);                 //返回响应类型
}


int Check_PKT(void)
{
   //rsi_clear_interrupt(0x80);
//   if(rsi_app_cb.pkt_pending == RSI_TRUE)
   if(rsi_app_cb.pkt_pending >0)
	
	{
		rsi_app_cb.pkt_pending -=1;// RSI_FALSE;  
//		rsi_app_cb.pkt_pending = RSI_FALSE;  

		rsi_frame_read(rsi_app_cb.read_packet_buffer);                     //读取数据帧
		rsi_app_cb.uCmdRspFrame = rsi_parse_response(rsi_app_cb.read_packet_buffer);    //转换uCmdRspFrame

		rsi_app_cb.error_code = rsi_bytes2R_to_uint16(rsi_app_cb.uCmdRspFrame->status);
		return  rsi_bytes2R_to_uint16(rsi_app_cb.uCmdRspFrame->rspCode);                 //返回响应类型	
	}
	return -1;
}


int wifi_main(int app_mode)
{
	return 0;
}


int16 rsi_wifi_init(void)
{
	return 0;
}
	





























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
  uint8                   temp_rspCode;
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
  uint8 ii, scanInfo_size;
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
#if (defined(UART_INTERFACE) && !defined(TCP_IP_BYPASS))
      rsi_app_cb.ps_ok_to_send = 2;

      if(rsi_app_cb.ack_flag == 1)
      {
        break;
      }
#endif
      do
      {
		
        retval = rsi_execute_cmd((uint8 *)rsi_sleepack,0,0);
      }while(retval == BUFFER_FULL_FAILURE);
      rsi_app_cb.ps_ok_to_send = 0;
      break;

    case RSI_RSP_WKP:
      rsi_app_cb.ps_ok_to_send = 3;
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL13,"WKP\n");
#endif
      if (rsi_app_cb.ps_pkt_pending){
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
      break;
    default:
      break;
  }

  return rsp;
}

/*=================================================*/
/**
 * @fn          void rsi_receive_data_packet(uint8 *rx_pkt_payload)
 * @brief       To receive data packet
 * @param[in]   uint8 *rx_pkt_payload, received packet payload
 * @param[out]  none
 * @return      none
 * @section description 
 * This API is used to receive data packet from WIFI module
 */
void rsi_receive_data_packet(uint8 *rx_pkt_payload)
{
  //uint16 socket_no   = 0;
#ifdef LINUX_PLATFORM
  uint16 data_length = 0; 
  //uint16 data_offset = 0;
  //uint8 *actual_data;

  rsi_recvFrameTcp *data_recv = (rsi_recvFrameTcp *)rx_pkt_payload;

  //! Get socket number
  //socket_no = rsi_bytes2R_to_uint16(data_recv->recvSocket);
  ///////////////////////////////////////////////////////////

  //! Get received data length
  data_length = rsi_bytes2R_to_uint16(data_recv->recvBufLen);

  //! Get actual data offset
  //data_offset = rsi_bytes2R_to_uint16(data_recv->recvDataOffsetSize);
  ////////////////////////////////////////////////////////////////////

  //! Get actual data pointer
  //actual_data = rx_pkt_payload + data_offset;
  ///////////////////////////////////////////////////////////////

  rsi_app_cb.rcvd_data_pkt_count++;

  //! Application has to copy data_length bytes from actual_data pointer

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL13,"pkt %d received \n",rsi_app_cb.rcvd_data_pkt_count);
#endif    
  measure_throughput(data_length, 1);
#endif

}

/*=================================================*/
/**
 * @fn          int16 rsi_per_cont_wave_mode(rsi_uPerMode *uPerModeFrame)
 * @brief       To send per cont wave mode command
 * @param[in]   rsi_uPerMode *uPerModeFrame
 * @param[in]   int8 per_cw_mode_state
 * @section description 
 * This API is used to send per continous wave mode command to module. 
 * For setting power for continous wave mode, burst mode with required 
 * power must be set, burst mode must be disabled and continous wave mode 
 * must be sent.
 */
int16 rsi_per_cont_wave_mode(rsi_uPerMode *uPerModeFrame, int8 per_cw_mode_state)
{
  int16  retval;
  if(per_cw_mode_state == 0)
  {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL13,"per cont state 0, per burst mode start\n");
#endif
    rsi_uint16_to_2bytes(uPerModeFrame->perModeFrameSnd.per_mode_enable, 1);
    rsi_uint16_to_2bytes(uPerModeFrame->perModeFrameSnd.per_mode_enable, 18);
    rsi_uint32_to_4bytes(uPerModeFrame->perModeFrameSnd.rate, RSI_RATE_6); /* Keep any rate */
    rsi_uint16_to_2bytes(uPerModeFrame->perModeFrameSnd.length, 30); /* Keep any length */
    rsi_uint16_to_2bytes(uPerModeFrame->perModeFrameSnd.mode, 0); /* Burst Mode */
    rsi_uint16_to_2bytes(uPerModeFrame->perModeFrameSnd.channel, 1); /* keep required channel */
    retval = rsi_per_mode(uPerModeFrame);
    return retval;
  }

  if(per_cw_mode_state == 1)
  {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL13,"per cont state 1, per burst mode stop\n");
#endif
    rsi_uint16_to_2bytes(uPerModeFrame->perModeFrameSnd.per_mode_enable, 0); /*Disable per mode*/
    retval = rsi_per_mode(uPerModeFrame);
    return retval;
  }

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL13,"per cont state 2, per continous wave mode start\n");
#endif
  rsi_uint16_to_2bytes(uPerModeFrame->perModeFrameSnd.per_mode_enable, 1);
  rsi_uint16_to_2bytes(uPerModeFrame->perModeFrameSnd.mode, RSI_PER_CONT_WAVE_MODE_DC); /*Set mode to continuous wave mode required*/
  retval = rsi_per_mode(uPerModeFrame);
  return retval;
}
