#ifndef _USERWIFI_H_
#define _USERWIFI_H_
#include "sys.h"
#include "queue.h"

#define  UDP_SEND_SIZE 546  // 最好不要超过548    546 = 8 * 67 + 2
extern u32 SYSTEMTIME;
extern u32  YYMMDD;
extern u8 Time_Sync_Flag;
extern u8 Wifi_Send_EN;
extern u8 CAN_Send_EN;

extern Queue adc_queue;	 //adc接收缓存

extern char* destIp_txrx;    //数据收发 IP
extern char* destIp_sync;  //同步    IP

extern unsigned short destSocket_txrx;
extern unsigned short moduleSocket_txrx;

extern unsigned short destSocket_sync;
extern unsigned short moduleSocket_sync;

extern unsigned short socketDescriptor_txrx;
extern unsigned short socketDescriptor_sync;




void receive_udp_package(void);
u8 wifi_send_package(void);
u8 time_sync(u8 time[]);
u8 order_anay(u8 arr[]);

#endif









