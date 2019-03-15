/**
  ******************************************************************************
  * @file    userwifi.c
  * @author  zju.nesc.iotlab   浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    13-March-2019
  * @brief   wifi application functions    WiFi模组应用方法
  ******************************************************************************
  */

//-------------include---------------//
#include "userwifi.h"
#include  "wificonf.h"
#include "rsi_global.h"
#include "gpio.h"
#include "rsi_app.h"
#include "config.h"

u8     DATA_AUTO_CHECK_EN = 1;	//是否在中断中自动check数据
u32    SYSTEMTIME = 0;//系统时间
u32    YYMMDD =0;//年月日
u8     Time_Sync_Flag = 0;//最近时钟是否同步
volatile u8 Wifi_Send_EN = 0;//数据发送和接受使能
u8     CAN_Send_EN = 0;//CAN数据发送和接受使能
Queue  adc_queue;//ADC数据存储
u8     localDestIp_txrx[4] = {255,255,255,255};
u8     destIp_txrx[4] = {DESTIP_TXRX_GROUP1,DESTIP_TXRX_GROUP2,DESTIP_TXRX_GROUP3,DESTIP_TXRX_GROUP4};
u8     destIp_sync[4] = {255,255,255,255};  //同步
u16    destSocket_txrx = 5001;
u16    moduleSocket_txrx =5002;
u16    destSocket_sync = 5003;
u16    moduleSocket_sync = 5003;
u16    localDestSocket_txrx = 5014;
u16    localModuleSocket_txrx = 5005;
u16    socketDescriptor_txrx = 0;
u16    socketDescriptor_sync = 1;
u16    localSocketDescriptor_txrx = 2;
u32    bytes_sent = 0;//字节数据发送个数
u8     AnalRsp[ANAL_RSP_LENGTH];//anal处理完后，需要返回状态信息
/**
  * @brief  接受UDP包并处理
  * @param  None
  * @retval None
  */
void receive_udp_package()
{
	rsi_recvFrameUdp *data_recv=NULL;

	u8 RspCode;
	unsigned short  recvSocket;
	RspCode = Check_PKT();
	
	switch (RspCode)
	{
		case RSI_RSP_DATA_RECEIVE:  //接收到数据
			data_recv = (rsi_recvFrameUdp *)&(rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad);
		    recvSocket = rsi_bytes2R_to_uint16(data_recv->recvSocket);
		    if(recvSocket ==socketDescriptor_sync)//命令或者时钟同步信息
			{ 
				if(order_anay(data_recv->recvDataBuf) == NEED_RETURN_INFO)//如果返回了1说明，需要回复信息
				{
					AnalRsp[0] = RETURN_INFO;//表示这是返回信息
					AnalRsp[1] = data_recv->recvDataBuf[0];//返回传过来的命令
					AnalRsp[2] = nodeId;
					u8 temp = DATA_AUTO_CHECK_EN;DATA_AUTO_CHECK_EN = 0;
					rsi_send_ludp_data(socketDescriptor_sync,AnalRsp ,ANAL_RSP_LENGTH, RSI_PROTOCOL_UDP_V4, (uint8 *)destIp_sync, destSocket_sync ,&bytes_sent);
					DATA_AUTO_CHECK_EN = temp;
				}
			}
			
			break;
		case RSI_FWUP_RSP://无线更新固件（RS9113的）
			rsi_wireless_fwupgrade();
			break;
		default:
			break;
	
	}
}

/**
  * @brief  WiFi发送测试
  * @param  None
  * @retval None
  */
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
	queue_addtime_addIO(&adc_queue,Length, nodeId, DIGITAL_INPUT1,DIGITAL_INPUT2);
	if(adc_queue.head + UDP_SEND_SIZE > QUEUE_SIZE ) queue_oversize(&adc_queue,adc_queue.head + UDP_SEND_SIZE - QUEUE_SIZE);
	Head = adc_queue.head;
	adc_queue.head = adc_queue.tail; 

	DATA_AUTO_CHECK_EN = 0;
	//局域网
	rsi_send_ludp_data(localSocketDescriptor_txrx, &adc_queue.arr[Head],Length+PACKAGE_HEAD_FRAME_LENGTH, RSI_PROTOCOL_UDP_V4, (uint8 *)localDestIp_txrx, localDestSocket_txrx, &bytes_sent);
	receive_udp_package();
	delay_ms(1000);
	//远程服务器
	rsi_send_ludp_data(socketDescriptor_txrx, &adc_queue.arr[Head],Length+PACKAGE_HEAD_FRAME_LENGTH, RSI_PROTOCOL_UDP_V4, (uint8 *)destIp_txrx, destSocket_txrx, &bytes_sent);
	DATA_AUTO_CHECK_EN = temp;
	
}

s16 TcpStatus = -1;
s32 TcpCount = 0;
/**
  * @brief  发送ADC数据
  * @param  None
  * @retval 数据发送状态（发送完成：1；未开启发送：0）
  */
u8 wifi_send_package()
{
	int Head;
	u32 Length;

	
	if(!Wifi_Send_EN){
		return 0;
	}
	

	if(Time_Sync_Flag==1)
	{
		Length = queue_length(adc_queue);
		
		queue_addtime_addIO(&adc_queue,Length, nodeId, DIGITAL_INPUT1,DIGITAL_INPUT2);    //  head <- head-10; //
		
		if(adc_queue.head + UDP_SEND_SIZE > QUEUE_SIZE ) {
			queue_oversize(&adc_queue,adc_queue.head + UDP_SEND_SIZE - QUEUE_SIZE);
		}
		Head = adc_queue.head;
		adc_queue.head = adc_queue.tail; 
		//  why not use   rsi_send_data()	
		u8 temp = DATA_AUTO_CHECK_EN;
		DATA_AUTO_CHECK_EN = 0;
		//发送到远程服务器
	#ifdef SEND_WITH_UDP
			rsi_send_ludp_data(socketDescriptor_txrx, &adc_queue.arr[Head],Length+PACKAGE_HEAD_FRAME_LENGTH, RSI_PROTOCOL_UDP_V4, (uint8 *)destIp_txrx, destSocket_txrx, &bytes_sent);
	    
		#else
			rsi_send_data(socketDescriptor_txrx,  &adc_queue.arr[Head], Length+PACKAGE_HEAD_FRAME_LENGTH,RSI_PROTOCOL_TCP_V4,&bytes_sent);
	#endif
		DATA_AUTO_CHECK_EN = temp;
		//延时防止阻塞崩溃
		delay_ms(5);
		temp = DATA_AUTO_CHECK_EN;
		DATA_AUTO_CHECK_EN = 0;
		//发送到局域网
		rsi_send_ludp_data(localSocketDescriptor_txrx, &adc_queue.arr[Head],Length+PACKAGE_HEAD_FRAME_LENGTH, RSI_PROTOCOL_UDP_V4, (uint8 *)localDestIp_txrx, localDestSocket_txrx, &bytes_sent);
		DATA_AUTO_CHECK_EN = temp;
		Time_Sync_Flag = 0;//时钟同步位清零
	}
	
	if(queue_length(adc_queue) >= (UDP_SEND_SIZE - PACKAGE_HEAD_FRAME_LENGTH )){
		
		Length = queue_length(adc_queue);
		
		queue_addtime_addIO(&adc_queue,Length,nodeId, DIGITAL_INPUT1,DIGITAL_INPUT2);   //  head <- head-10;
		if(adc_queue.head + UDP_SEND_SIZE > QUEUE_SIZE ){
			queue_oversize(&adc_queue,adc_queue.head + UDP_SEND_SIZE - QUEUE_SIZE);
		}
		Head = adc_queue.head;
		adc_queue.head = adc_queue.tail; 
		//发送到远程服务器
		u8 temp = DATA_AUTO_CHECK_EN;
		DATA_AUTO_CHECK_EN = 0;
#ifdef SEND_WITH_UDP
		rsi_send_ludp_data(socketDescriptor_txrx, &adc_queue.arr[Head],Length+PACKAGE_HEAD_FRAME_LENGTH, RSI_PROTOCOL_UDP_V4, (uint8 *)destIp_txrx, destSocket_txrx, &bytes_sent);
#else
		while(TcpStatus!=0&&TcpCount <100)
		{
			TcpCount++;
			TcpStatus = rsi_send_data(socketDescriptor_txrx,  &adc_queue.arr[Head],(uint32)(Length + PACKAGE_HEAD_FRAME_LENGTH),RSI_PROTOCOL_TCP_V4,&bytes_sent);
		}
		TcpCount=0;
		TcpStatus=-1;
#endif
		DATA_AUTO_CHECK_EN = temp;
		delay_ms(5);
		//发送到局域网
		temp = DATA_AUTO_CHECK_EN;
		DATA_AUTO_CHECK_EN = 0;
		rsi_send_ludp_data(localSocketDescriptor_txrx, &adc_queue.arr[Head],Length+PACKAGE_HEAD_FRAME_LENGTH, RSI_PROTOCOL_UDP_V4, (uint8 *)localDestIp_txrx, localDestSocket_txrx, &bytes_sent);
		DATA_AUTO_CHECK_EN = temp;
	}
	return 1;
}

/**
  * @brief  命令处理
  * @param  接收到的命令首地址
  * @retval 是否需要返回信息给上位机（NOT_NEED_RETURN_INFO 或 NEED_RETURN_INFO）
  */
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
			LED2_CONV();
			LED4_CONV();
		  }
			break;
		case 	GET_TIME_SYNC_MAIN_CLOCK:
			memcpy(&YYMMDD,&arr[1],4);
			memcpy(&SYSTEMTIME,&arr[5],4);
			Time_Sync_Flag = 1;
			LED2_CONV();
			LED4_CONV();
			return NOT_NEED_RETURN_INFO;				
		case RETURN_INFO://返回了回复信号
			return NOT_NEED_RETURN_INFO;//表示不需要返回信息
		case GET_WIFI_SEND_EN:
			//如果启动了本设备
			if(arr[1]==nodeId){
				Wifi_Send_EN =1;  //wifi开始发送
			}
			else{
				return NOT_NEED_RETURN_INFO;
			}
			break;
		case GET_WIFI_SEND_DISABLE:        		
			if(arr[1]==nodeId){
				Wifi_Send_EN =0;//wifi停止发送
			}
			else{
				return NOT_NEED_RETURN_INFO;
			}
			break;
		case GET_CHANNEL_MODEL:         // 通道模式选择
			if(arr[1]==nodeId)//如果命令指定了本ID
				setAdcModel(&arr[2]);
			else  //如果命令不是给本设备的，则返回0，表示不需要返回ack
				return NOT_NEED_RETURN_INFO;
			break;
		case GET_CAN_SEND_EN:
			if(arr[1]==nodeId){
				CAN_Send_EN =1;//CAN开启
			}
			else{
				return NOT_NEED_RETURN_INFO;
			}
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
		case GET_TEST_NAME://获取测试名称	
			if(strlen((c8*)(arr+1)) < MAX_TEST_NAME_LENGTH){
				memset((u8 *)adc_queue.test_name,0,MAX_TEST_NAME_LENGTH);//全部reset为0
				strcpy((char *)adc_queue.test_name,(c8*)(arr+1));
				printf("\r\nGet Test Name : \"%s\"(UTF-8)\r\n",(arr+1));//输出UTF-8中文
			}
			break;	
		case PAGING://寻呼信号
			break;		
		default:
			return NOT_NEED_RETURN_INFO;
	}
	return NEED_RETURN_INFO;
	
}


/**
  * @brief  打开UDP套接字
  * @param  destIp：远程IP
  * @param  destSocket：远程端口
  * @param  moduleSocket：本设备模组端口
  * @param  socketDescriptor：套接字描述
  * @retval 打开UDP成功与否（1：不成功；0：成功）
  */
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

/**
  * @brief  打开TCP套接字
  * @param  destIp：远程IP
  * @param  destSocket：远程端口
  * @param  moduleSocket：本设备模组端口
  * @param  socketDescriptor：套接字描述
  * @retval 打开UDP成功与否（1：不成功；0：成功）
  */
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
/**
  * @brief  同步时钟模块发送同步时钟信号
  * @param  None
  * @retval None
  */
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
}
#endif
