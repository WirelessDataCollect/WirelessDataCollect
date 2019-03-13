#ifndef _USERWIFI_H_
#define _USERWIFI_H_
#include "sys.h"
#include "queue.h"
#include "config.h"

//!UDP数据包最大大小   546 = 8 * 67 + PACKAGE_HEAD_FRAME_LENGTH
#define  UDP_SEND_SIZE          (8*67+PACKAGE_HEAD_FRAME_LENGTH)
//!是不是主时钟设备
#define  IAM_MASTER_CLOCK       0  


/** 
  * @brief  上位机命令接收后是否需要返回
  */  
typedef enum{
	NOT_NEED_RETURN_INFO = 0,
	NEED_RETURN_INFO
}CMD_GetState;

/** @defgroup 采用TCP还是UDP发送给私有云服务器
  * @hint 两者定义一个且仅仅一个，TCP未验证，不建议使用
  * @{
  */
//#define  SEND_WITH_TCP  1  //用tcp传输数据
#define SEND_WITH_UDP     1   //用udp传输数据
/**
  * @}
  */

/** @defgroup 默认的远程服务器IPV4地址
  * @{
  */
#define DESTIP_TXRX_GROUP1 115
#define DESTIP_TXRX_GROUP2 159
#define DESTIP_TXRX_GROUP3 154
#define DESTIP_TXRX_GROUP4 160
/**
  * @}
  */

/** @defgroup AP模式参数
  * @{
  */
#define AP_MODE_SOCKET_DEST_IP       "192.168.100.2"
#define AP_MODE_SOCKET_DEST_PORT     5002
#define AP_MODE_SOCKET_MODULE_PORT   5001
/**
  * @}
  */

/** @defgroup 上位机命令 
  * @{
  */
#define  GET_TIME_SYNC_PC           0xa1   //来自上位机的同步信号
#define  RETURN_INFO			    0xa2   //
#define  GET_TEST_NAME              0xa3//获取测试名称
#define  GET_TIME_SYNC_MAIN_CLOCK   0xa4  //来自主机的同步信号
#define  GET_WIFI_SEND_EN           0xa5
#define  GET_WIFI_SEND_DISABLE      0xa6
#define  GET_CHANNEL_MODEL          0xa7
#define  GET_CAN_SEND_EN            0xa8
#define  GET_REMOTE_IP_PORT         0xa9
#define  PAGING                     0xaa  //寻呼信号
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

//!系统时钟
extern u32   SYSTEMTIME;
//!年月日
extern u32   YYMMDD;

//!是否已经同步
extern u8    Time_Sync_Flag;

//!数据采集和发送使能
extern u8    Wifi_Send_EN;
//!CAN采集和发送使能
extern u8    CAN_Send_EN;

//!adc接收缓存
extern Queue adc_queue;	

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

void receive_udp_package(void);
void wifi_send_package_test(void);
u8 OpenLudpSocket(u8* destIp,unsigned short destSocket,unsigned short moduleSocket,unsigned short * socketDescriptor);
u8 OpenTcpSocket(u8 *destIp,unsigned short destSocket,unsigned short moduleSocket,unsigned short * socketDescriptor);
u8 wifi_send_package(void);
u8 order_anay(u8 arr[]);
void Send_Sync_Time(void);
#endif


