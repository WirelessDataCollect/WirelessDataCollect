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

#define CAN_INIT_REBOOT   0 /*< 是否开机启动can，进行测试>*/

void testAdc(void);
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
	/*ms时间，放在前面，请不要随意移动位置*/
	TIM3_Int_Init(TIM3_ARR,TIM3_PSC); //1000us	
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
	queue_init(&can_queue);
	
	/*ADC相关引脚初始化*/
	ADC_CTRL_Conf();
	
	/* CAN测试*/
	#if CAN_INIT_REBOOT
	u32 filter[7] = {0x1800f001,0x1800f002,0x1800f003,0x1800f004,0x1800f005,0x1800f006,0x1800f007};
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS1_6tq,CAN_BS2_7tq,12,CAN_Mode_Normal,(u32 *)filter,7);
	CAN2_Mode_Init(CAN_SJW_1tq,CAN_BS1_6tq,CAN_BS2_7tq,6,CAN_Mode_Normal,(u32 *)filter,7);
	#endif
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
/**
  * @brief  测试WIFI最快传输速度
  * @param  None
  * @retval None
  */
u8 data[1500];
void testMaxWifiSpeed(){
	
	rsi_send_ludp_data(localSocketDescriptor_txrx, data,1500, RSI_PROTOCOL_UDP_V4, (uint8 *)localDestIp_txrx, localDestSocket_txrx, &bytes_sent);
}
int main(void)
{     
	setBoardSta(BOARD_INITING);Initialization();setBoardSta(BOARD_INITED);//初始化系统
	setBoardSta(BOARD_RUNNING);//运行中
	u8 RspCode;u16 tcpRecvBuffLen;u8 * pRecvData;
	memset(data,32,1500);
	while(1)
	{
//		testMaxWifiSpeed();
		if(RSI_WIFI_OPER_MODE == RSI_WIFI_CLIENT_MODE_VAL){
			if(IAM_MASTER_CLOCK == 'Y'){
				if(sync_interval_time >= SYNC_INTERVAL_TIME&&Wifi_Send_EN){
					INFO_LED_CONV();//翻转
					sync_interval_time = 0;
					Send_Sync_Time();//时钟同步一下
				}
			}else{  //不是主时钟需要发送ADC和CAN数据
				wifi_send_package();
			}
		}else if(RSI_WIFI_OPER_MODE == RSI_WIFI_AP_MODE_VAL){
			delay_ms(10);
			RspCode =Check_PKT();
			switch (RspCode){
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









