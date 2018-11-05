#ifndef _USERWIFI_H_
#define _USERWIFI_H_
#include "sys.h"
#include "queue.h"
 
#define  UDP_SEND_SIZE          552  // 最好不要超过548    546 = 8 * 67 + 10

#define  IAM_MASTER_CLOCK       0  //是不是主时钟设备
#define  WIFI_CLIENT_ID         1//1,2,3,4，不要超过255
//#define  SEND_WITH_TCP    //用tcp传
#define SEND_WITH_UDP

//请修改				RSI_DHCP_HOST_NAME

#define  GET_TIME_SYNC_PC          0xa1
#define  RETURN_INFO			0xa2
#define  GET_TEST         0xa3
#define  GET_TIME_SYNC_MAIN_CLOCK   0xa4  //来自主机的同步信号
#define  GET_WIFI_SEND_EN       0xa5
#define  GET_WIFI_SEND_DISABLE  0xa6
#define  GET_CHANNEL_MODEL      0xa7
#define  GET_CAN_SEND_EN        0xa8
#define  GET_REMOTE_IP_PORT     0xa9
#define  PAGING     0xaa  //寻呼信号

extern u32 SYSTEMTIME;
extern u32  YYMMDD;
extern u8 Time_Sync_Flag;
extern u8 Wifi_Send_EN;
extern u8 CAN_Send_EN;

extern Queue adc_queue;	 //adc接收缓存

extern u8 destIp_txrx[4];    //数据收发 IP
extern u8 destIp_sync[4];  //同步    IP
extern u8 localDestIp_txrx[4];    //数据收发 IP

extern unsigned short destSocket_txrx;
extern unsigned short moduleSocket_txrx;
extern unsigned short localDestSocket_txrx;
extern unsigned short localModuleSocket_txrx;	

extern unsigned short destSocket_sync;
extern unsigned short moduleSocket_sync;

extern unsigned short socketDescriptor_txrx;
extern unsigned short socketDescriptor_sync;
extern unsigned short localSocketDescriptor_txrx;

void receive_udp_package(void);

u8 OpenLudpSocket(u8* destIp,unsigned short destSocket,unsigned short moduleSocket,unsigned short * socketDescriptor);
u8 OpenTcpSocket(u8 *destIp,unsigned short destSocket,unsigned short moduleSocket,unsigned short * socketDescriptor);
u8 wifi_send_package(void);
u8 order_anay(u8 arr[]);
void Send_Sync_Time(void);

#endif


