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
#include "timer.h"
#include "can1.h"
#include "can2.h"

u8     DATA_AUTO_CHECK_EN = 1;	    									 //是否在中断中自动check数据
u32    SYSTEMTIME = 0;                                                   //系统时间
u32    YYMMDD =0;                                                        //年月日
u8     Time_Sync_Flag = 0;                                               //最近时钟是否同步
volatile u8 Wifi_Send_EN = 1;                                            //数据采集和发送使能，是CAN和ADC采集的总开关
u8     CAN_Get_EN = CAN1_ENABLE_BIT_SLC|CAN2_ENABLE_BIT_SLC;             //CAN数据发送使能（第0位使能can1，第1位使能can2），默认开启（必须满足Wifi_Send_EN=1，才能采集）
u8     ADC_Get_EN = 1;                                                   //ADC数据采集使能，默认开启（必须满足Wifi_Send_EN=1，才能采集）
Queue  adc_queue;                                                        //ADC数据存储
Queue  can_queue;                                                        //can数据存储
u8     localDestIp_txrx[4] = {255,255,255,255};
u8     destIp_txrx[4] = {DESTIP_TXRX_GROUP1,DESTIP_TXRX_GROUP2,DESTIP_TXRX_GROUP3,DESTIP_TXRX_GROUP4};
u8     destIp_sync[4] = {255,255,255,255};                              //同步
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
void receive_udp_package(void)
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
	for(int i =0;i<ADC_SEND_SIZE;i++)
	{
		queue_put(&adc_queue,i);
	}

	Length = queue_length(&adc_queue);
	queue_addtime_addIO(&adc_queue,Length, nodeId, DIGITAL_INPUT1,DIGITAL_INPUT2,ADC_DATA_PACKAGE);
	if(adc_queue.head + ADC_SEND_SIZE > QUEUE_SIZE ) queue_oversize(&adc_queue,adc_queue.head + ADC_SEND_SIZE - QUEUE_SIZE);
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
  * @brief  发送ADC和CAN数据
  * @param  None
  * @retval 数据发送状态（发送完成：1；未开启发送：0）
  */
u8 wifi_send_package(void)
{
	u16 Adc_Head,Can_Head;
	u32 Adc_Length;u32 Can_Length;
	u8 temp;

	
	if(!Wifi_Send_EN){
		return 0;
	}
	
	/* 有同步时钟到来*/
	if(Time_Sync_Flag==1)
	{
		Adc_Length = queue_length(&adc_queue);
		Can_Length = queue_length(&can_queue);
		
		/* ADC Queue加入帧头*/
		//1.加入帧头
		queue_addtime_addIO(&adc_queue,Adc_Length, nodeId, DIGITAL_INPUT1,DIGITAL_INPUT2,ADC_DATA_PACKAGE);
		//2.获取队列头
		Adc_Head = adc_queue.head;
		//3.更新队列
		adc_queue.head = adc_queue.tail;  //队列清空，则会启动下一个包的ADC采集，包括1、在tail后加ADC数据；2、更新时间；3、更新tail		
		/* CAN Queue加入帧头*/
		queue_addtime_addIO(&can_queue,Can_Length, nodeId, DIGITAL_INPUT1,DIGITAL_INPUT2,CAN_DATA_PACKAGE);
		Can_Head = can_queue.head; 
		can_queue.head = can_queue.tail;
		
		/* ADC如果分成两段，将前面一段复制到后面*/
		if(Adc_Head + Adc_Length + PACKAGE_HEAD_FRAME_LENGTH > QUEUE_SIZE ) {
			queue_oversize(&adc_queue,Adc_Head + PACKAGE_HEAD_FRAME_LENGTH + Adc_Length - QUEUE_SIZE);
		}
		/* CAN如果分成两段，将前面一段复制到后面*/
		if(Can_Head + Can_Length + PACKAGE_HEAD_FRAME_LENGTH > QUEUE_SIZE ) {
			queue_oversize(&can_queue,Can_Head + PACKAGE_HEAD_FRAME_LENGTH + Can_Length - QUEUE_SIZE);
		}
		
		temp = DATA_AUTO_CHECK_EN;
		DATA_AUTO_CHECK_EN = 0;
		/* ADC数据发送到远程服务器*/
		rsi_send_ludp_data(socketDescriptor_txrx, &adc_queue.arr[Adc_Head],Adc_Length+PACKAGE_HEAD_FRAME_LENGTH, RSI_PROTOCOL_UDP_V4, (uint8 *)destIp_txrx, destSocket_txrx, &bytes_sent);
		
		DATA_AUTO_CHECK_EN = temp;
		delay_ms(WIFI_MODUEL_WAIT_MSTIME);
		temp = DATA_AUTO_CHECK_EN;
		DATA_AUTO_CHECK_EN = 0;
		/* 发送到远程服务器*/
		rsi_send_ludp_data(socketDescriptor_txrx, &can_queue.arr[Can_Head],Can_Length+PACKAGE_HEAD_FRAME_LENGTH, RSI_PROTOCOL_UDP_V4, (uint8 *)destIp_txrx, destSocket_txrx, &bytes_sent);
		
		DATA_AUTO_CHECK_EN = temp;
		/* 延时防止阻塞崩溃*/
		delay_ms(WIFI_MODUEL_WAIT_MSTIME);
		temp = DATA_AUTO_CHECK_EN;
		DATA_AUTO_CHECK_EN = 0;
		/* ADC数据发送到局域网*/
		rsi_send_ludp_data(localSocketDescriptor_txrx, &adc_queue.arr[Adc_Head],Adc_Length+PACKAGE_HEAD_FRAME_LENGTH, RSI_PROTOCOL_UDP_V4, (uint8 *)localDestIp_txrx, localDestSocket_txrx, &bytes_sent);
		
		DATA_AUTO_CHECK_EN = temp;
		delay_ms(WIFI_MODUEL_WAIT_MSTIME);
		temp = DATA_AUTO_CHECK_EN;
		DATA_AUTO_CHECK_EN = 0;
		/* CAN数据发送到局域网*/
		rsi_send_ludp_data(localSocketDescriptor_txrx, &can_queue.arr[Can_Head],Can_Length+PACKAGE_HEAD_FRAME_LENGTH, RSI_PROTOCOL_UDP_V4, (uint8 *)localDestIp_txrx, localDestSocket_txrx, &bytes_sent);
		DATA_AUTO_CHECK_EN = temp;		
		delay_ms(WIFI_MODUEL_WAIT_MSTIME);
		Time_Sync_Flag = 0;//时钟同步位清零
	}
//	/* ADC队列已满，无包头，用于测试ADC数据精度*/
//	if(queue_length(&adc_queue) >= (ADC_SEND_SIZE)){
//		
//		Adc_Length = queue_length(&adc_queue);
//		Adc_Head = adc_queue.head;
//		adc_queue.head = adc_queue.tail;
//		if(Adc_Head + Adc_Length > QUEUE_SIZE ){
//			queue_oversize(&adc_queue,Adc_Head + Adc_Length - QUEUE_SIZE);
//		}
// 
//		//发送到远程服务器
//		temp = DATA_AUTO_CHECK_EN;
//		DATA_AUTO_CHECK_EN = 0;
//		rsi_send_ludp_data(socketDescriptor_txrx, &adc_queue.arr[Adc_Head],Adc_Length, RSI_PROTOCOL_UDP_V4, (uint8 *)destIp_txrx, destSocket_txrx, &bytes_sent);

//		DATA_AUTO_CHECK_EN = temp;
//		delay_ms(WIFI_MODUEL_WAIT_MSTIME);
//		//发送到局域网
//		temp = DATA_AUTO_CHECK_EN;
//		DATA_AUTO_CHECK_EN = 0;
//		rsi_send_ludp_data(localSocketDescriptor_txrx, &adc_queue.arr[Adc_Head],Adc_Length, RSI_PROTOCOL_UDP_V4, (uint8 *)localDestIp_txrx, localDestSocket_txrx, &bytes_sent);
//		DATA_AUTO_CHECK_EN = temp;
//		delay_ms(WIFI_MODUEL_WAIT_MSTIME);

//	}
	/* ADC队列已满*/
	if(queue_length(&adc_queue) >= (ADC_SEND_SIZE - PACKAGE_HEAD_FRAME_LENGTH )){

		Adc_Length = queue_length(&adc_queue);
		queue_addtime_addIO(&adc_queue,Adc_Length,nodeId, DIGITAL_INPUT1,DIGITAL_INPUT2,ADC_DATA_PACKAGE);   //  head <- head-10;
		Adc_Head = adc_queue.head;
		adc_queue.head = adc_queue.tail;
		if(Adc_Head + Adc_Length + PACKAGE_HEAD_FRAME_LENGTH > QUEUE_SIZE ){
			queue_oversize(&adc_queue,Adc_Head + Adc_Length + PACKAGE_HEAD_FRAME_LENGTH - QUEUE_SIZE);
		}
 
		//发送到远程服务器
		temp = DATA_AUTO_CHECK_EN;
		DATA_AUTO_CHECK_EN = 0;
		rsi_send_ludp_data(socketDescriptor_txrx, &adc_queue.arr[Adc_Head],Adc_Length+PACKAGE_HEAD_FRAME_LENGTH, RSI_PROTOCOL_UDP_V4, (uint8 *)destIp_txrx, destSocket_txrx, &bytes_sent);

		DATA_AUTO_CHECK_EN = temp;
		delay_ms(WIFI_MODUEL_WAIT_MSTIME);
		//发送到局域网
		temp = DATA_AUTO_CHECK_EN;
		DATA_AUTO_CHECK_EN = 0;
		rsi_send_ludp_data(localSocketDescriptor_txrx, &adc_queue.arr[Adc_Head],Adc_Length+PACKAGE_HEAD_FRAME_LENGTH, RSI_PROTOCOL_UDP_V4, (uint8 *)localDestIp_txrx, localDestSocket_txrx, &bytes_sent);
		DATA_AUTO_CHECK_EN = temp;
		delay_ms(WIFI_MODUEL_WAIT_MSTIME);
	}
	/* CAN队列已满*/
	if( queue_length(&can_queue) >= (CAN_SEND_SIZE - PACKAGE_HEAD_FRAME_LENGTH )){
		Can_Length = queue_length(&can_queue);
		queue_addtime_addIO(&can_queue,Can_Length, nodeId, DIGITAL_INPUT1,DIGITAL_INPUT2,CAN_DATA_PACKAGE);
		Can_Head = can_queue.head;
		can_queue.head = can_queue.tail; 
		if(Can_Head + Can_Length + PACKAGE_HEAD_FRAME_LENGTH > QUEUE_SIZE ) {
			queue_oversize(&can_queue,Can_Head + Can_Length + PACKAGE_HEAD_FRAME_LENGTH - QUEUE_SIZE);
		}

		temp = DATA_AUTO_CHECK_EN;
		DATA_AUTO_CHECK_EN = 0;
		/* 发送到远程服务器*/
		//! 是否打印发送数据到模组的时间
		#if PRINTF_WIFI_SEND2MODULE_TIME
		u32 time0 = SYSTEMTIME;
		#endif
		rsi_send_ludp_data(socketDescriptor_txrx, &can_queue.arr[Can_Head],Can_Length+PACKAGE_HEAD_FRAME_LENGTH, RSI_PROTOCOL_UDP_V4, (uint8 *)destIp_txrx, destSocket_txrx, &bytes_sent);
		#if PRINTF_WIFI_SEND2MODULE_TIME
		printf("Time of Send to Module : %d\r\n",SYSTEMTIME - time0);
		#endif
		DATA_AUTO_CHECK_EN = temp;
		delay_ms(WIFI_MODUEL_WAIT_MSTIME);
		temp = DATA_AUTO_CHECK_EN;
		DATA_AUTO_CHECK_EN = 0;
		//! 是否打印出要发出去的CAN数据
		#if CHECK_CAN_STATUS_PRINTF
		//校验时间最低位是否正确
		printf("%x ?= %x\r\n",can_queue.arr[(Can_Head+4)%QUEUE_SIZE],can_queue.arr[(Can_Head+15)%QUEUE_SIZE]);
		if(can_queue.arr[(Can_Head+15)%QUEUE_SIZE] != can_queue.arr[(Can_Head+4)%QUEUE_SIZE]){
			printf("Time Check Error\r\n");
		}
		//校验数据长度
		u32 count = can_queue.arr[(Can_Head+8)%QUEUE_SIZE] + 256 * can_queue.arr[(Can_Head+9)%QUEUE_SIZE] + 256 * 256 * can_queue.arr[(Can_Head+10)%QUEUE_SIZE];
		printf("count : %d ?= Can_Length : %d\r\n",count,Can_Length);
		if(count != Can_Length){
			printf("Len Check Error\r\n");
		}
		#endif
		/* CAN数据发送到局域网*/
		rsi_send_ludp_data(localSocketDescriptor_txrx, &can_queue.arr[Can_Head],Can_Length+PACKAGE_HEAD_FRAME_LENGTH, RSI_PROTOCOL_UDP_V4, (uint8 *)localDestIp_txrx, localDestSocket_txrx, &bytes_sent);
		DATA_AUTO_CHECK_EN = temp;
	}else if(queue_length(&can_queue) > 0){	/* CAN队列中数据存储时间过长，以us为单位，就发出来*/	
		if(((SYSTEMTIME - ((u32)(can_queue.arr[can_queue.head+1]&0xff)|((u32)(can_queue.arr[can_queue.head+2]&0xff)<<8)|((u32)(can_queue.arr[can_queue.head+3]&0xff)<<16)
			      |((u32)(can_queue.arr[can_queue.head+4]&0xff)<<24)))*(TIM4_ARR + 1)*(TIM4_PSC + 1) / TIM3_4_PCLK_MHZ) > CAN_OVERTIME_SEND_TIME){
			Can_Length = queue_length(&can_queue);
			queue_addtime_addIO(&can_queue,Can_Length, nodeId, DIGITAL_INPUT1,DIGITAL_INPUT2,CAN_DATA_PACKAGE);
			Can_Head = can_queue.head;
			can_queue.head = can_queue.tail; 			
			if(Can_Head + Can_Length + PACKAGE_HEAD_FRAME_LENGTH > QUEUE_SIZE ) {
				queue_oversize(&can_queue,Can_Head + Can_Length + PACKAGE_HEAD_FRAME_LENGTH - QUEUE_SIZE);
			};	
			//! 是否打印出要发出去的CAN数据
			#if CHECK_CAN_STATUS_PRINTF
			//校验时间最低位是否正确
			if(can_queue.arr[(Can_Head+15)%QUEUE_SIZE] != can_queue.arr[(Can_Head+4)%QUEUE_SIZE]){
				printf("Time Check Error\r\n");
			}
			//校验数据长度
			u32 count = can_queue.arr[(Can_Head+8)%QUEUE_SIZE] + 255 * can_queue.arr[(Can_Head+9)%QUEUE_SIZE];
			if(count != Can_Length){
				printf("Len Check Error\r\n");
			}
			#endif			
			temp = DATA_AUTO_CHECK_EN;
			DATA_AUTO_CHECK_EN = 0;
			/* 发送到远程服务器*/
			rsi_send_ludp_data(socketDescriptor_txrx, &can_queue.arr[Can_Head],Can_Length+PACKAGE_HEAD_FRAME_LENGTH, RSI_PROTOCOL_UDP_V4, (uint8 *)destIp_txrx, destSocket_txrx, &bytes_sent);
			DATA_AUTO_CHECK_EN = temp;
			delay_ms(WIFI_MODUEL_WAIT_MSTIME);
			temp = DATA_AUTO_CHECK_EN;
			DATA_AUTO_CHECK_EN = 0;
			/* CAN数据发送到局域网*/
			rsi_send_ludp_data(localSocketDescriptor_txrx, &can_queue.arr[Can_Head],Can_Length+PACKAGE_HEAD_FRAME_LENGTH, RSI_PROTOCOL_UDP_V4, (uint8 *)localDestIp_txrx, localDestSocket_txrx, &bytes_sent);
			DATA_AUTO_CHECK_EN = temp;	
			delay_ms(WIFI_MODUEL_WAIT_MSTIME);			
		}
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
				INFO_LED_CONV();
			}
			break;
		case 	GET_TIME_SYNC_MAIN_CLOCK:
			memcpy(&YYMMDD,&arr[1],4);
			memcpy(&SYSTEMTIME,&arr[5],4);
			Time_Sync_Flag = 1;
			INFO_LED_CONV();
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
		//! 通道模式选择
		case GET_CHANNEL_MODEL:         
			if(arr[1]==nodeId)
				setAdcModel(&arr[2]);
			else  //如果命令不是给本设备的，则返回0，表示不需要返回ack
				return NOT_NEED_RETURN_INFO;
			break;
		//! [CMD,nodeId,CANx,FREQ,FilterListNum,[FilterList]]
		//! 即命令，节点ID，CANX，通信频率10KHz，过滤ID数目，过滤ID列表
		case GET_CAN_FILTER_ID:
			if(arr[1] == nodeId){
				if(arr[2] == CAN1_ID){
					
					if(arr[3] == 50){ //500KHz
						CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS1_6tq,CAN_BS2_7tq,6,CAN_Mode_Normal,(u32*)&arr[5],arr[4]);   //500K
					}else if(arr[3] == 25){ //250KHz
						CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS1_6tq,CAN_BS2_7tq,12,CAN_Mode_Normal,(u32*)&arr[5],arr[4]);   //250K
					}
				}else if(arr[2] == CAN2_ID){
					if(arr[3] == 50){ //500KHz
						CAN2_Mode_Init(CAN_SJW_1tq,CAN_BS1_6tq,CAN_BS2_7tq,6,CAN_Mode_Normal,(u32*)&arr[5],arr[4]);   //500K
					}else if(arr[3] == 25){ //250KHz
						CAN2_Mode_Init(CAN_SJW_1tq,CAN_BS1_6tq,CAN_BS2_7tq,12,CAN_Mode_Normal,(u32*)&arr[5],arr[4]);   //250K
					}
				}
			}
			else{
				return NOT_NEED_RETURN_INFO;
			}
			break;
		case GET_REMOTE_IP_PORT:            //主机地址
			memcpy(destIp_txrx,&arr[1],4);
			memcpy(&destSocket_txrx,&arr[5],2);
			rsi_socket_close(socketDescriptor_txrx, moduleSocket_txrx);//关闭掉原来的远程服务器的socket
			OpenLudpSocket(destIp_txrx,destSocket_txrx,moduleSocket_txrx,&socketDescriptor_txrx);
			break;
		case GET_TEST_NAME://获取测试名称	
			if(strlen((c8*)(arr+1)) < MAX_TEST_NAME_LENGTH){
				memset((u8 *)test_name,0,MAX_TEST_NAME_LENGTH);//全部reset为0
				strcpy((char *)test_name,(c8*)(arr+1));
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
