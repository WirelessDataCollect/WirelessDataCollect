/**
  ******************************************************************************
  * @file    main.c
  * @author  zju.nesc.iotlab    浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    13-March-2019
  * @brief   main function   主函数
  ******************************************************************************
  */

//-------------include---------------//
#include "sys.h"
#include "userwifi.h"
#include "delay.h"  
#include "usart.h"   
#include "gpio.h"
#include "wificonf.h"
#include "queue.h"
#include "can1.h"
#include "can2.h"
#include "timer.h"
#include "adc.h"
#include "stmflash.h" 
#include "config.h"
#include "rsi_global.h"
#include "rsi_app.h"
#include "crc.h"

u8 IO_input[3];
extern u32 bytes_sent;

void testAdc(void);
u8 can_send_package(void);
void Initialization (void);

/**
  * @brief  系统初始化
  * @param  None
  * @retval None
  */
void Initialization (void)
{
	/*设置优先级分组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	/*初始化GPIO*/
	GP_IO_Init();
	/*初始化UART*/
	uart_init(115200);
	/*初始化延时功能*/
	delay_init(168); 
	
	/* 出厂设置，一般运行不需要*/
	/*setFactory();*/
	
	#if PRINT_UART_LOG
	printf("System Initing...!\r\n");
	#endif
	
	/*下载参数*/
	loadParafromMainOrBackupFlash();//getPara();
	/*设置wifi为客户端模式*/
	setClientModePara();InitWiFi();
	/*检查模组连接情况，如果连接失败，则设置为AP模式*/
	checkModuleSta(); 
	/*开启所有需要的套接字*/
	if(RSI_WIFI_OPER_MODE == RSI_WIFI_CLIENT_MODE_VAL){
		openAllSocket();
	}else if(RSI_WIFI_OPER_MODE == RSI_WIFI_AP_MODE_VAL){
		OpenSocket((u8*)AP_MODE_SOCKET_DEST_IP,AP_MODE_SOCKET_DEST_PORT,AP_MODE_SOCKET_MODULE_PORT,RSI_SOCKET_TCP_SERVER);
		Read_PKT();
		printf("Open TCP Socket!\r\n");
	}
	
	/*队列配置*/
	queue_init(&adc_queue);
	
	/*ADC相关引脚初始化*/
	ADC_CTRL_Conf();
	
	/*ms时间*/
	TIM3_Int_Init(TIM3_ARR,TIM3_PSC); //1000us
	/*系统时间100us中断*/
	TIM4_Int_Init(TIM4_ARR,TIM4_PSC);
	#if PRINT_UART_LOG
	printf("System Inited Successfully!\r\n");
	/*帮助文档*/
	getHelp();
	/*参数打印*/
	getPara();
	#endif
}

/**
  * @brief  CAN数据发送
  * @param  None
  * @retval None
  */
u8 can_send_package()
{ 
	if(CAN_Send_EN && CAN1_Send_EN){
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



/**
  * @brief  测试ADC，打印到串口
  * @param  None
  * @retval None
  */
void testAdc(void){
	u8 * AdcTemp;
	ADC_CONV_H();
	delay_us(5);
	ADC_CONV_L();
	delay_us(5);
	ADC_CONV_H();
	delay_us(100);
	AdcTemp = ADC_Read(ADC_MAX_BYTES);
	#if PRINT_UART_LOG
//	printf("%d ",(AdcTemp[0]*256+AdcTemp[1]));
//	printf("%d ",(AdcTemp[2]*256+AdcTemp[3]));
//	printf("%d ",(AdcTemp[4]*256+AdcTemp[5]));
//	printf("%d \r\n",(AdcTemp[6]*256+AdcTemp[7]));
	printf("%.3f   ",(double)(AdcTemp[0]*256+AdcTemp[1])*5.0/32768.0);	
	printf("%.3f   ",(double)(AdcTemp[2]*256+AdcTemp[3])*5.0/32768.0);	
	printf("%.3f   ",(double)(AdcTemp[4]*256+AdcTemp[5])*5.0/32768.0);	
	printf("%.3f   ",(double)(AdcTemp[6]*256+AdcTemp[7])*5.0/32768.0);	
	printf("\r\n");
	delay_ms(1000);
	#endif
}

int main(void)
{     
	setBoardSta(BOARD_INITING);Initialization();setBoardSta(BOARD_INITED);//初始化系统
	setBoardSta(BOARD_RUNNING);//运行中
	u8 RspCode;u16 tcpRecvBuffLen;u8 * pRecvData;
	while(1)
	{
		if(RSI_WIFI_OPER_MODE == RSI_WIFI_CLIENT_MODE_VAL){
//			CAN1_Send_Msg((u8 *)&SYSTEMTIME,4);
//			delay_ms(1000);
//			CAN2_Send_Msg((u8 *)&SYSTEMTIME,4);
//			CAN1_Receive_Msg(CanBuf);
//			delay_ms(1000);
		wifi_send_package();//发送数据，每次时钟更新后或者数据到达一定数量UDP_SEND_SIZE  8bytes时间+2bytes数字IO+8*N bytes ADC信号
//			testAdc();
//			receive_udp_package();\\stm32_wifi_ap_1_x\../HARDWARE/WIFI/userwifi.c\adc_queue.tail
//			wifi_send_package_test();
			#if IAM_MASTER_CLOCK
				if(sync_interval_time >= SYNC_INTERVAL_TIME&&Wifi_Send_EN)
				{
					LED2_CONV();//DS2翻转
					LED4_CONV();
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
							tcpRecvBuffLen,
							RSI_PROTOCOL_TCP_V4,&bytes_sent);		//参数
						#if PRINT_UART_LOG
						printf("WARNING : Cannot Deal With More Than 2 CMDs!\r\n");
						#endif						
					}
					break;
				default:
					break;
			}
		}			
	}
}









