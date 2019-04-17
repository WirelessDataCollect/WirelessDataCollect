/**
  ******************************************************************************
  * @file    userwifi.h
  * @author  zju.nesc.iotlab    浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    13-March-2019
  * @brief   wifi application functions   WiFi模组应用方法
  ******************************************************************************
  */

#ifndef _USERWIFI_H_
#define _USERWIFI_H_

//-------------include---------------//
#include "sys.h"
#include "queue.h"
#include "config.h"

//!是不是主时钟设备
#define  IAM_MASTER_CLOCK       0  


/** 
  * @brief  上位机命令接收后是否需要返回
  * @{
  */ 
typedef enum{
	NOT_NEED_RETURN_INFO = 0,/*!< 需要返回信息>*/
	NEED_RETURN_INFO         /*!< 不需要返回信息>*/
}CMD_GetState;
/**
  * @}
  */


/** @defgroup 默认的远程服务器IPV4地址
  * @{
  */
#define DESTIP_TXRX_GROUP1 115    /*!< IP 第1组>*/
#define DESTIP_TXRX_GROUP2 159    /*!< IP 第2组>*/
#define DESTIP_TXRX_GROUP3 154    /*!< IP 第3组>*/
#define DESTIP_TXRX_GROUP4 160    /*!< IP 第4组>*/
/**
  * @}
  */

/** @defgroup AP模式参数
  * @{
  */
#define AP_MODE_SOCKET_DEST_IP       "192.168.100.2"    /*!< AP模式下连接者的IP>*/
#define AP_MODE_SOCKET_DEST_PORT     5002               /*!< AP模式下连接者的端口>*/
#define AP_MODE_SOCKET_MODULE_PORT   5001               /*!< AP模式下本设备的端口>*/
/**
  * @}
  */
  
/** @defgroup 超时发送
  * @{
  */
#define CAN_OVERTIME_SEND_TIME       600000    /*!< 8000ms>*/
/**
  * @}
  */  

/** @defgroup 上位机命令，UDP数据包第1个字节
  * @{
  */
#define  GET_TIME_SYNC_PC           0xa1   /*!< 来自上位机的同步信号>*/
#define  RETURN_INFO			    0xa2   /*!< 返回信息>*/
#define  GET_TEST_NAME              0xa3   /*!< 获取测试名称>*/
#define  GET_TIME_SYNC_MAIN_CLOCK   0xa4   /*!< 来自主机的同步信号>*/
#define  GET_WIFI_SEND_EN           0xa5   /*!< 数据采集和发送使能>*/
#define  GET_WIFI_SEND_DISABLE      0xa6   /*!< 数据采集和发送失能>*/
#define  GET_CHANNEL_MODEL          0xa7   /*!< 设置通道的电流/电压模式>*/
#define  GET_CAN_FILTER_ID          0xa8   /*!< CAN数据采集的ID列表设置>*/
#define  GET_REMOTE_IP_PORT         0xa9   /*!< 设置发送数据对象（私有云服务器）IP>*/
#define  PAGING                     0xaa   /*!< 寻呼信号>*/
/**
  * @}
  */
  
/** @defgroup 给上位机的返回指令长度
  * @{
  */
#define ANAL_RSP_LENGTH            3
/**
  * @}
  */
  
/** @defgroup CAN使能位
  * @{
  */
#define CAN1_ENABLE_BIT_SLC         0x01  /*!< CAN1使能位，即第0位>*/
#define CAN2_ENABLE_BIT_SLC         0x02  /*!< CAN2使能位，即第1位>*/
/**
  * @}
  */

//!系统时钟
extern u32   SYSTEMTIME;
//!年月日
extern u32   YYMMDD;

//!是否已经同步
extern u8    Time_Sync_Flag;

//!数据采集和发送使能
extern volatile u8    Wifi_Send_EN;
//!CAN采集使能
extern u8    CAN_Get_EN;
//!ADC采集使能
extern u8    ADC_Get_EN;

//!adc接收缓存
extern Queue adc_queue;	
//!can接收缓存
extern Queue can_queue;

//!私有云服务器IP地址
extern u8 destIp_txrx[IPV4_LENGTH];
//!ADC数据指向的私有云服务器端口
extern unsigned short destSocket_txrx;
//!节点模组-私有云服务器UDP网络接口的描述
extern unsigned short socketDescriptor_txrx;
//!节点模组数据接收（私有云服务器）端口，无用
extern unsigned short moduleSocket_txrx;

//!同步时钟对象的IP地址，255.255.255.255广播
extern u8 destIp_sync[IPV4_LENGTH];
//!同步时钟对象的端口
extern unsigned short destSocket_sync;
//!同步时钟模块的端口
extern unsigned short moduleSocket_sync;
//!节点模组-同步模块UDP网络接口的描述
extern unsigned short socketDescriptor_sync;

//!局域网上位机IP地址，255.255.255.255广播
extern u8 localDestIp_txrx[IPV4_LENGTH];    //数据收发 IP
//!局域网上位机端口
extern unsigned short localDestSocket_txrx;
//!节点模组数据接收（上位机）端口，无用
extern unsigned short localModuleSocket_txrx;	
//!节点模组-局域网上位机UDP网络接口的描述
extern unsigned short localSocketDescriptor_txrx;

//!是否在中断中自动check数据
extern u8 DATA_AUTO_CHECK_EN;

void receive_udp_package(void);
void wifi_send_package_test(void);
u8 OpenLudpSocket(u8* destIp,unsigned short destSocket,unsigned short moduleSocket,unsigned short * socketDescriptor);
u8 OpenTcpSocket(u8 *destIp,unsigned short destSocket,unsigned short moduleSocket,unsigned short * socketDescriptor);
u8 wifi_send_package(void);
u8 order_anay(u8 arr[]);
void Send_Sync_Time(void);
#endif


