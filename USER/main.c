#include "sys.h"
#include "userwifi.h"
#include "delay.h"  
#include "usart.h"   
#include "led.h"
#include "wificonf.h"
#include "myiic.h"
#include "queue.h"
#include "can.h"
#include "can2.h"
#include "timer.h"
#include "adc.h"

#include "stmflash.h" 
#include "config.h"

#include "rsi_global.h"
#include "rsi_app.h"
#include "crc.h"

/*
优先级
	
	//外部中断
	NVIC_InitStructure.NVIC_IRQChannel=EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	
    //TIM 4
   	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //子优先级0
	
    //TIM 3
   	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //子优先级0
	
	//CAN1
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;     // 主优先级为2
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // 次优先级为0
	
	//CAN2
	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX1_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;     // 主优先级为2
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            // 次优先级为1
	
*/
extern u8 CAN_Send_EN;
extern u8 CAN1_Send_EN;
extern u8 CAN2_Send_EN;
extern u8 DATA_AUTO_CHECK_EN;
u8 IO_input[3];
u8 can_send_package(void);
void Initialization (void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	GP_IO_Init();
	uart_init(115200);		
	delay_init(168); 
//	//出厂设置，一般运行不需要。
//	setFactory();
	#if PRINT_UART_LOG
	printf("System Initing...!\r\n");
	#endif
	loadParafromMainOrBackupFlash();
	InitWiFi();//初始化wifi,默认client模式

	checkModelSta();//如果没有连接AP，则自己的模式将变为AP模式
	//客户端模式时，开启所有需要的UDP端口
	if(RSI_WIFI_OPER_MODE == RSI_WIFI_CLIENT_MODE_VAL){
		openAllSocket();
	}else if(RSI_WIFI_OPER_MODE == RSI_WIFI_AP_MODE_VAL){
		OpenSocket((u8*)AP_MODE_SOCKET_DEST_IP,AP_MODE_SOCKET_DEST_PORT,AP_MODE_SOCKET_MODULE_PORT,RSI_SOCKET_TCP_SERVER);
		Read_PKT();
		printf("Open TCP Socket!\r\n");
	}
	queue_init(&adc_queue);
	delay_ms(1000);
//	ADC_CTRL_Conf();//ADC相关引脚初始化
//	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS1_6tq,CAN_BS2_7tq,6,CAN_Mode_Normal);   //500K
//	CAN2_Mode_Init(CAN_SJW_1tq,CAN_BS1_6tq,CAN_BS2_7tq,12,CAN_Mode_Normal);   //250k
//	TIM3_Int_Init(999,83); //1000us
	TIM4_Int_Init(4,83); //5us
	#if PRINT_UART_LOG
	printf("System Inited Successfully!\r\n");
	#endif
	getHelp();
}

u8 Status=1;
extern u32 bytes_sent;
int main(void)
{     

	Initialization();//初始化系统
	u8 RspCode;u16 tcpRecvBuffLen;u8 * pRecvData;
	while(1)
	{
		if(RSI_WIFI_OPER_MODE == RSI_WIFI_CLIENT_MODE_VAL){
			DATA_AUTO_CHECK_EN= 1;
//			wifi_send_package();//发送数据，每次时钟更新后或者数据到达一定数量UDP_SEND_SIZE  8bytes时间+2bytes数字IO+8*N bytes ADC信号
			
//			if(SYSTEMTIME%1000 == 0){
//				rsi_send_ludp_data(localSocketDescriptor_txrx, "GET IN",6, RSI_PROTOCOL_UDP_V4, (uint8 *)localDestIp_txrx, localDestSocket_txrx, &bytes_sent);
//			}
			wifi_send_package_test();
			delay_ms(1000);
			LED1_CONV();
			LED2_CONV();
			#if IAM_MASTER_CLOCK
				if(sync_interval_time>=SYNC_INTERVAL_TIME&&Wifi_Send_EN)
				{
					LED2 = !LED2;//用来表示在更新时钟
					sync_interval_time = 0;
					Send_Sync_Time();//时钟同步一下
				}
			#endif	
		}else if(RSI_WIFI_OPER_MODE == RSI_WIFI_AP_MODE_VAL){
			delay_ms(10);
			RspCode =Check_PKT();
			switch (RspCode)
			{
				case RSI_RSP_DATA_RECEIVE://RSI_RSP_DATA_RECEIVE 接到数据再发出去
					pRecvData =rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.recvFrameTcp.recvDataBuf;
					tcpRecvBuffLen = rsi_bytes4R_to_uint32(rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.recvFrameTcp.recvBufLen);
					#if PRINT_UART_LOG
					printf("Recv %d Byte CMD \"%s\" From TCP Socket!\r\n",tcpRecvBuffLen,pRecvData);
					#endif
					rsi_send_data( rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.recvFrameTcp.recvSocket[0], //id
						pRecvData, 				//接受数据指针
						tcpRecvBuffLen,
						RSI_PROTOCOL_TCP_V4,&bytes_sent);		//参数
					if(CMD_RX_BUF.CmdCompleteFlag == CMD_NOT_COMPLETED){//如果还没没有完整，需要接受命令
						//为了放到USART BUFF中进行相同的处理，需要判断是否长度过长
						if(tcpRecvBuffLen<(USART_BUFF_LEN)){
							//清零且完整，因为一个tcp是整个，不需要考虑usart那种一个一个传输的情况
							uart_queue_clear(&CMD_RX_BUF);
							//加入到BUFF中，会在定时器中自动处理
							uart_queue_put_many(&CMD_RX_BUF,pRecvData,tcpRecvBuffLen);
							uart_queue_put_many(&CMD_RX_BUF,(u8*)"\r\n",2);//后面加上\r\n,就算没有收到\r\n也没有关系
							CMD_RX_BUF.CmdCompleteFlag = CMD_COMPLETED;
						}
					}else if(CMD_RX_BUF.CmdCompleteFlag == CMD_COMPLETED){
						rsi_send_data( rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.recvFrameTcp.recvSocket[0], //id
							(u8*)"Cannot Deal With More Than 2 CMD!\r\nPlese Wait!\r\n", 				//接受数据指针
							tcpRecvBuffLen,//
							RSI_PROTOCOL_TCP_V4,&bytes_sent);		//参数
						#if PRINT_UART_LOG
						printf("WARNING : Cannot Deal With More Than 2 CMDs!\r\n");
						#endif						
					}
					break;
				case 0x59:
					rsi_wireless_fwupgrade();
					while(1);
					break;
				default:
					break;
			}
		}			
	}
}


u8 can_send_package()
{ 
	if(CAN_Send_EN&&CAN1_Send_EN){   
		if(queue_empty(adc_queue)) delay_ms(2);
		IO_input[0] = DIGITAL_INPUT1;
		IO_input[1] = DIGITAL_INPUT2;
		IO_input[2] = nodeId;
		CAN1_Send_Msg((u8 *) &adc_queue.YYYY_MM_DD, 8);
		CAN1_Send_Msg((u8 *) &adc_queue.arr[adc_queue.head],8);
		CAN1_Send_Msg(IO_input,3);
		CAN_Send_EN = 0;
		CAN1_Send_EN = 0;
	}
	if(CAN_Send_EN && CAN2_Send_EN){

		if(queue_empty(adc_queue)) delay_ms(2);
		IO_input[0] = DIGITAL_INPUT1;
		IO_input[1] = DIGITAL_INPUT2;
		IO_input[2] = nodeId;
		CAN2_Send_Msg((u8 *) &adc_queue.YYYY_MM_DD, 8);
		CAN2_Send_Msg((u8 *) &adc_queue.arr[adc_queue.head],8);
		CAN2_Send_Msg(IO_input,3);
		CAN_Send_EN = 0;
		CAN2_Send_EN = 0;
	}
	return 1;
}








