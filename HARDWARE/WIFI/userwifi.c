#include "userwifi.h"
#include  "spi.h"
#include "rsi_global.h"

#include "rsi_app.h"

extern rsi_app_cb_t rsi_app_cb;
/* Gloab  data*/

//timer 
u32 SYSTEMTIME=0;
u32  YYMMDD =0;
u8 Time_Sync_Flag=0;
u8 Wifi_Send_EN =0;

//IIC
Queue adc_queue;	 //adc接收缓存

//wifi_main
char* destIp_txrx="";    //数据收发
char* destIp_sync="255,255,255,255";  //同步
unsigned short destSocket_txrx= 5001;
unsigned short moduleSocket_txrx=5002;
unsigned short destSocket_sync= 5003;
unsigned short moduleSocket_sync=5004;
unsigned short socketDescriptor_txrx=0;
unsigned short socketDescriptor_sync=1;
u32 bytes_sent=0;


rsi_recvFrameUdp *data_recv=NULL;

void receive_udp_package()
{
	u8 RspCode;
	unsigned short  recvSocket;
	RspCode = Check_PKT();
	
	switch (RspCode)     //???
	{
		case 0x00:
			data_recv = (rsi_recvFrameUdp *)&(rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad);
		    recvSocket = rsi_bytes2R_to_uint16(data_recv->recvSocket);
		    if(recvSocket ==socketDescriptor_sync)
			{ 
				time_sync(data_recv->recvDataBuf);
			}
			else
			{
				order_anay(data_recv->recvDataBuf);
				
			}
			break;
		case 0x59:
			rsi_wireless_fwupgrade();
			break;
		default:
			break;
	
	}
}

u8 wifi_send_package()
{
	int Head;
	int Length;
	
	if(!Wifi_Send_EN) return 0;
	
	if(Time_Sync_Flag==1)
	{
		queue_addtime(&adc_queue);
		Head = adc_queue.head;
		Length = queue_length(adc_queue);
		adc_queue.head = adc_queue.tail;  // why not use   rsi_send_data()
		
		rsi_send_ludp_data(socketDescriptor_txrx, &adc_queue.arr[Head],Length, RSI_PROTOCOL_UDP_V4, (uint8 *)destIp_txrx, moduleSocket_sync, &bytes_sent);
	}
	if(queue_length(adc_queue)>500)
	{
		queue_addtime(&adc_queue); 
		Head = adc_queue.head;
		Length = queue_length(adc_queue);
		adc_queue.head = (adc_queue.tail+500)%QUEUE_SIZE; 
		rsi_send_ludp_data(socketDescriptor_txrx, &adc_queue.arr[Head],508, RSI_PROTOCOL_UDP_V4, (uint8 *)destIp_txrx, 5002 ,&bytes_sent);
	}
	return 1;
}

u8 time_sync(u8 time[])
{
	Time_Sync_Flag = 1; 
	memcpy(&YYMMDD,time,4);
	memcpy(&SYSTEMTIME,time+4,4);
	return 1;
}
u8 order_anay(u8 arr[])
{
	if(arr[0] == 0xa5 )
	{
		Wifi_Send_EN =1;
	}
	else
	{
		Wifi_Send_EN =0;
	}
	return 1;
	
}




