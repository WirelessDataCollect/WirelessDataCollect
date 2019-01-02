#include "userwifi.h"
#include  "spi.h"
#include "rsi_global.h"
#include "led.h"
#include "rsi_app.h"

extern rsi_app_cb_t rsi_app_cb;
/* Gloab  data*/

u8 DATA_AUTO_CHECK_EN = 0;	

//timer 
u32 SYSTEMTIME=0;
u32  YYMMDD =0;
u8 Time_Sync_Flag = 0;//时钟同步信号
u8 Wifi_Send_EN = 1;//发送数据的命令
u8 CAN_Send_EN = 0;

//IIC
Queue adc_queue;	 //adc接收缓存

//wifi_main 
u8 localDestIp_txrx[4]={255,255,255,255};    //局域网
//u8 destIp_txrx[4]={255,255,255,255};    //服务器远程数据收发
u8 destIp_txrx[4]={115,159,154,160};    //服务器远程数据收发
u8 destIp_sync[4]={255,255,255,255};  //同步
unsigned short destSocket_txrx= 5001;
unsigned short moduleSocket_txrx=5002;
unsigned short destSocket_sync= 5003;//这里要一样
unsigned short moduleSocket_sync=5003;
unsigned short localDestSocket_txrx= 5004;//局域网的远程IP
unsigned short localModuleSocket_txrx=5005;

unsigned short socketDescriptor_txrx=0;
unsigned short socketDescriptor_sync=1;
unsigned short localSocketDescriptor_txrx=2;

u32 bytes_sent=0;





void receive_udp_package()
{
	rsi_recvFrameUdp *data_recv=NULL;
	u8 ANAL_RSP_LENGTH = 3;
	u8 RspCode;
	u8 AnalRsp[ANAL_RSP_LENGTH];//anal处理完后，需要返回wifi信息
	unsigned short  recvSocket;
	RspCode = Check_PKT();
	
	switch (RspCode)
	{
		case 0x00:
			data_recv = (rsi_recvFrameUdp *)&(rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad);
		    recvSocket = rsi_bytes2R_to_uint16(data_recv->recvSocket);
		    if(recvSocket ==socketDescriptor_sync)//命令或者时钟同步信息
			{ 
				if(order_anay(data_recv->recvDataBuf))//如果返回了1说明，需要回复信息
				{
					AnalRsp[0] = RETURN_INFO;//表示这是返回信息
					AnalRsp[1] = data_recv->recvDataBuf[0];//返回传过来的命令
					AnalRsp[2] = WIFI_CLIENT_ID;
					rsi_send_ludp_data(socketDescriptor_sync,AnalRsp ,ANAL_RSP_LENGTH, RSI_PROTOCOL_UDP_V4, (uint8 *)destIp_sync, destSocket_sync ,&bytes_sent);
				}
			}
			
			break;
		case 0x59:
			rsi_wireless_fwupgrade();
			break;
		default:
			break;
	
	}
}


void wifi_send_package_test()
{
	int Head;
	uint32 Length;
	u8 temp= DATA_AUTO_CHECK_EN;
	for(int i =0;i<UDP_SEND_SIZE;i++)
	{
		queue_put(&adc_queue,i);
	}
	
	Length = queue_length(adc_queue);
	queue_addtime_addIO(&adc_queue,Length, WIFI_CLIENT_ID, DIGITAL_INPUT1,DIGITAL_INPUT2);
	if(adc_queue.head + UDP_SEND_SIZE > QUEUE_SIZE ) queue_oversize(&adc_queue,adc_queue.head + UDP_SEND_SIZE - QUEUE_SIZE);
	Head = adc_queue.head;
	adc_queue.head = adc_queue.tail; 
	
  DATA_AUTO_CHECK_EN = 0;
	rsi_send_ludp_data(localSocketDescriptor_txrx, &adc_queue.arr[Head],Length+16, RSI_PROTOCOL_UDP_V4, (uint8 *)localDestIp_txrx, localDestSocket_txrx, &bytes_sent);
  receive_udp_package();
	DATA_AUTO_CHECK_EN = temp;
	
}

int16 TcpStatus =-1;
int TcpCount = 0;
u8 wifi_send_package()
{
	int Head;
	uint32 Length;

	
	if(!Wifi_Send_EN) return 0;

	if(Time_Sync_Flag==1)
	{
		Length = queue_length(adc_queue);
		
		queue_addtime_addIO(&adc_queue,Length, WIFI_CLIENT_ID, DIGITAL_INPUT1,DIGITAL_INPUT2);    //  head <- head-10; //
		
		if(adc_queue.head + UDP_SEND_SIZE > QUEUE_SIZE ) queue_oversize(&adc_queue,adc_queue.head + UDP_SEND_SIZE - QUEUE_SIZE);
		Head = adc_queue.head;
		adc_queue.head = adc_queue.tail; 
		//  why not use   rsi_send_data()		
		
		//发送到远程服务器
	#ifdef SEND_WITH_UDP
			rsi_send_ludp_data(socketDescriptor_txrx, &adc_queue.arr[Head],Length+16, RSI_PROTOCOL_UDP_V4, (uint8 *)destIp_txrx, destSocket_txrx, &bytes_sent);
	    
		#else
			rsi_send_data(socketDescriptor_txrx,  &adc_queue.arr[Head], Length+16,RSI_PROTOCOL_TCP_V4,&bytes_sent);
	#endif
		
		
		//延时保证两个udp发送正常
		delay_us(100);
		for(int n=0;n<20;n++){
			receive_udp_package();
			delay_us(100);
		}
		
		//发送到局域网
		rsi_send_ludp_data(localSocketDescriptor_txrx, &adc_queue.arr[Head],Length+16, RSI_PROTOCOL_UDP_V4, (uint8 *)localDestIp_txrx, localDestSocket_txrx, &bytes_sent);
		Time_Sync_Flag = 0;//时钟同步位清零
	}
	
	if(queue_length(adc_queue) >= UDP_SEND_SIZE - 16 )//我觉得>=比较好，万一没来得及发现==UDP_SEND_SIZE - 10的情况呢
	{
		
		Length = queue_length(adc_queue);
		
		queue_addtime_addIO(&adc_queue,Length,WIFI_CLIENT_ID, DIGITAL_INPUT1,DIGITAL_INPUT2);   //  head <- head-10;
		if(adc_queue.head + UDP_SEND_SIZE > QUEUE_SIZE ) queue_oversize(&adc_queue,adc_queue.head + UDP_SEND_SIZE - QUEUE_SIZE);
		Head = adc_queue.head;
		adc_queue.head = adc_queue.tail; 
		//发送到远程服务器
#ifdef SEND_WITH_UDP
		rsi_send_ludp_data(socketDescriptor_txrx, &adc_queue.arr[Head],Length+16, RSI_PROTOCOL_UDP_V4, (uint8 *)destIp_txrx, destSocket_txrx, &bytes_sent);
#else
		while(TcpStatus!=0&&TcpCount <100)
		{
			TcpCount++;
			TcpStatus = rsi_send_data(socketDescriptor_txrx,  &adc_queue.arr[Head],(uint32)(Length + 16),RSI_PROTOCOL_TCP_V4,&bytes_sent);
		}
		TcpCount=0;
		TcpStatus=-1;
#endif
		//延时保证两个udp发送正常
		delay_us(100);
		for(int n=0;n<20;n++){
			receive_udp_package();
			delay_us(100);
		}
		//发送到局域网
		rsi_send_ludp_data(localSocketDescriptor_txrx, &adc_queue.arr[Head],Length+16, RSI_PROTOCOL_UDP_V4, (uint8 *)localDestIp_txrx, localDestSocket_txrx, &bytes_sent);
	}
	return 1;
}

//如果返回了1说明，需要回复信息
//或者本次接收到的信息无用也返回0
extern u8 txrx_refreshed;
u8 order_anay(u8 arr[])
{
	switch(arr[0])
	{
		case GET_TIME_SYNC_PC://时钟同步信号
			if(DATA_AUTO_CHECK_EN)
			{
			memcpy(&YYMMDD,&arr[1],4);
			memcpy(&SYSTEMTIME,&arr[5],4);
			Time_Sync_Flag = 1;
			LED2 = ~LED2;
		  }
			break;
		case 	GET_TIME_SYNC_MAIN_CLOCK:
			memcpy(&YYMMDD,&arr[1],4);
			memcpy(&SYSTEMTIME,&arr[5],4);
			Time_Sync_Flag = 1;
		 // GPIO_SetBits(GPIOA, GPIO_Pin_9);
//		  PAout(9) = ~PAout(9);
//		   PAout(10) = ~PAout(10);
			LED2 = ~LED2;
			return 0;				
		case RETURN_INFO://返回了回复信号
			return 0;//表示不需要返回信息
		case GET_TEST:
			break;
		case GET_WIFI_SEND_EN:
			Wifi_Send_EN =1;  //wifi开始发送
//			//如果启动了本设备
//			if(arr[1]==WIFI_CLIENT_ID){
//				Wifi_Send_EN =1;  //wifi开始发送
//			}
//			else{
//				return 0;
//			}
			break;
		case GET_WIFI_SEND_DISABLE:        
			Wifi_Send_EN =0;//wifi停止发送			
//			if(arr[1]==WIFI_CLIENT_ID){
//				Wifi_Send_EN =0;//wifi停止发送
//			}
//			else{
//				return 0;
//			}
			break;
		case GET_CHANNEL_MODEL:         // 通道模式选择
			if(arr[1]==WIFI_CLIENT_ID)//如果命令指定了本ID
				Channel_model(&arr[2]);
			else  //如果命令不是给本设备的，则返回0，表示不需要返回ack
				return 0;
			break;
		case GET_CAN_SEND_EN:
			CAN_Send_EN = 1; // CAN转发数据，时间+2路IO+4路AD
			break;
		case GET_REMOTE_IP_PORT:            //主机地址
			memcpy(destIp_txrx,&arr[1],4);
		  memcpy(&destSocket_txrx,&arr[5],2);
		  
			rsi_socket_close(socketDescriptor_txrx, moduleSocket_txrx);//关闭掉原来的远程服务器的socket
#ifdef SEND_WITH_UDP
			OpenLudpSocket(destIp_txrx,destSocket_txrx,moduleSocket_txrx,&socketDescriptor_txrx);
#else
			OpenTcpSocket(destIp_txrx,destSocket_txrx,moduleSocket_txrx,&socketDescriptor_txrx);//创建一个数据收发socket
#endif
			break;
		case PAGING://寻呼信号
			break;
		default:
			return 0;
	}
	return 1;
	
}

//打开udp
u8 OpenLudpSocket(u8 *destIp,unsigned short destSocket,unsigned short moduleSocket,unsigned short * socketDescriptor)
{
	int RspCode;
	u8 temp= DATA_AUTO_CHECK_EN ;
	DATA_AUTO_CHECK_EN= 0;
	OpenSocket(destIp,destSocket,moduleSocket,RSI_SOCKET_LUDP);
	RspCode=Read_PKT();
	if(RspCode!=RSI_RSP_SOCKET_CREATE)
	{
		DATA_AUTO_CHECK_EN = temp;
		return 1;
	}
	
	*socketDescriptor = rsi_bytes2R_to_uint16(rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.socketFrameRcv.socketDescriptor);
	DATA_AUTO_CHECK_EN = temp;
	return 0;
}

//打开tcp
u8 OpenTcpSocket(u8 *destIp,unsigned short destSocket,unsigned short moduleSocket,unsigned short * socketDescriptor)
{
	u8 temp= DATA_AUTO_CHECK_EN ;
	DATA_AUTO_CHECK_EN= 0;
	
	int RspCode;
	OpenSocket(destIp,destSocket,moduleSocket,RSI_SOCKET_TCP_CLIENT);
	RspCode=Read_PKT();
	if(RspCode!=RSI_RSP_SOCKET_CREATE)
	{
		DATA_AUTO_CHECK_EN = temp;
		return 1;
	}
	DATA_AUTO_CHECK_EN = temp;
	*socketDescriptor = rsi_bytes2R_to_uint16(rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.socketFrameRcv.socketDescriptor);
	
	return 0;
}
#if IAM_MASTER_CLOCK
#define SYNC_TIME_BYTES   9   //同步时钟命令长度
void Send_Sync_Time(void)
{
	uint8 time[SYNC_TIME_BYTES] = {0};//时间信息
	time[0] = GET_TIME_SYNC_MAIN_CLOCK;//时间同步命令
	time[1] = (uint8) YYMMDD;
	time[2] = (uint8) (YYMMDD>>8);
	time[3] = (uint8) (YYMMDD>>16);
	time[4] = (uint8) (YYMMDD>>24);
	time[5] = (uint8) SYSTEMTIME;
	time[6] = (uint8) (SYSTEMTIME>>8);
	time[7] = (uint8) (SYSTEMTIME>>16);
	time[8] = (uint8) (SYSTEMTIME>>24);
	u8 temp= DATA_AUTO_CHECK_EN ;
	DATA_AUTO_CHECK_EN= 0;
	rsi_send_ludp_data(socketDescriptor_sync,time ,SYNC_TIME_BYTES, RSI_PROTOCOL_UDP_V4, (uint8 *)destIp_sync, destSocket_sync ,&bytes_sent);
	receive_udp_package();
	DATA_AUTO_CHECK_EN = temp;
	//rsi_send_data(socketDescriptor_sync, time, SYNC_TIME_BYTES,RSI_PROTOCOL_UDP_V4,&bytes_sent);
}
#endif



void EXTI15_10_IRQHandler(void)
{
	EXTI->PR		|=1<<10;
	wifi_send_package_test();
	GPIO_ResetBits(GPIOA,GPIO_Pin_9);
}
