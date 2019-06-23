/**
  ******************************************************************************
  * @file    wificonf.c
  * @author  zju.nesc.iotlab 浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    13-March-2019
  * @brief   wifi module configuration functions   wifi模组配置方法
  ******************************************************************************
  */

//-------------include---------------//
#include "wificonf.h"
#include "rsi_global.h"
#include "rsi_app.h"
#include "userwifi.h"
#include "typetrans.h"
#include "config.h"

/**
  * @brief  RCC时钟配置
  * @param  None
  * @retval None
  */
void RCC_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
	RNG_Cmd(ENABLE );
}
 
/**
  * @brief  设置WIFI的中断NVIC
  * @param  None
  * @retval None
  */
void WIFI_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=WIFI_INTR_EXTI_CH;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//设置成最高优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  WIFI模组的引脚配置
  * @param  None
  * @retval None
  */
void WIFI_SPI_Conf(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	RCC_Config();	
	WIFI_EXTI_Conf();	
	WIFI_NVIC_Config();	
	/* CS*/
	GPIO_InitStructure.GPIO_Pin = WIFI_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(WIFI_CS_PORT, &GPIO_InitStructure);
	
	/* RST*/
	GPIO_InitStructure.GPIO_Pin = WIFI_RST_PIN;
	GPIO_Init(WIFI_RST_PORT, &GPIO_InitStructure);
		
	/* INTR中断*/
	GPIO_InitStructure.GPIO_Pin = WIFI_INTR_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(WIFI_INTR_PORT, &GPIO_InitStructure); 
	SYSCFG_EXTILineConfig(WIFI_INTR_EXTI_PORTSOURCE,WIFI_INTR_EXTI_PINSOURCE);  
	
	/* CLK;MISO;MOSI*/
	GPIO_InitStructure.GPIO_Pin = WIFI_CLK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(WIFI_CLK_PORT, &GPIO_InitStructure);//初始化
	GPIO_InitStructure.GPIO_Pin = WIFI_MOSI_PIN;	
	GPIO_Init(WIFI_MOSI_PORT, &GPIO_InitStructure);	//初始化
	GPIO_InitStructure.GPIO_Pin = WIFI_MISO_PIN;	
	GPIO_Init(WIFI_MISO_PORT, &GPIO_InitStructure);	//初始化

	WIFI_CS_H();
	/* 复用*/
	GPIO_PinAFConfig(WIFI_CLK_PORT,WIFI_CLK_AF_PINSOURCE,WIFI_SPIx_AF);
	GPIO_PinAFConfig(WIFI_MISO_PORT,WIFI_MISO_AF_PINSOURCE,WIFI_SPIx_AF);
	GPIO_PinAFConfig(WIFI_MOSI_PORT,WIFI_MOSI_AF_PINSOURCE,WIFI_SPIx_AF);

	/* wifi spi的配置*/
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;	
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;	
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;		
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	
	SPI_InitStructure.SPI_CRCPolynomial = 7;	
	SPI_Init(WIFI_SPIx, &SPI_InitStructure);  

	SPI_Cmd(WIFI_SPIx, ENABLE); 
	WIFI_CS_L(); 
}   
/**
  * @brief  设置MCU接收WiFi信号的外部中断配置
  * @param  None
  * @retval None
  */
void WIFI_EXTI_Conf(void)
{
	EXTI_InitTypeDef   EXTI_Type;
	EXTI_Type.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Type.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Type.EXTI_Line=WIFI_INTR_EXTI_LINE;
	EXTI_Type.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_Type);
}
/**
  * @brief  SPI的收发
  * @param  None
  * @retval None
  */
u8 WIFI_SPIx_TxRx(u8 TxData)
{		 			 
	WIFI_SPIx->DR=TxData;
	while ((WIFI_SPIx->SR&SPI_I2S_FLAG_RXNE) == 0); 
	return WIFI_SPIx->DR;//SPI_I2S_ReceiveData(SPI1);		    
}

/**
  * @brief  处理网络端口接收到的数据的中断函数
  * @param  None
  * @retval None
  */
void EXTI4_IRQHandler(void)
{
	EXTI->PR		|=1<<4;
	rsi_app_cb.pkt_pending ++;//= RSI_TRUE;	
	printf("[%d]  pkt_pending : %d\r\n",SYSTEMTIME,rsi_app_cb.pkt_pending);
	/* 初始化时不能进行自动check*/
	if( BOARD_STA == BOARD_RUNNING){
		if((DATA_AUTO_CHECK_EN)&&(RSI_WIFI_OPER_MODE == RSI_WIFI_CLIENT_MODE_VAL)){//处于Clien模式，而且要使能自动check
			receive_udp_package();
		}		
	}

}

/**
  * @brief  设置为AP模式
  * @param  None
  * @retval None
  */
void setApModePara(void){
	RSI_IP_CFG_MODE    = RSI_STATIC_IP_MODE;//设置为静态地址
	RSI_WIFI_OPER_MODE = RSI_WIFI_AP_MODE_VAL;//设置为AP模式
	RSI_BAND           = RSI_BAND_2P4GHZ;//AP模式只支持2.4G
}


/**
  * @brief  设置为Client模式
  * @param  None
  * @retval None
  */
void setClientModePara(void){
	RSI_IP_CFG_MODE     = RSI_DHCP_IP_MODE;//设置为DHCP地址
	RSI_WIFI_OPER_MODE  = RSI_WIFI_CLIENT_MODE_VAL;//设置为客户端模式
	RSI_BAND            = RSI_DUAL_BAND ;//客户端模式支持双频
}

/**
  * @brief  检查模组连接状态,如何没有成功连接多次，则设置为AP模式
  * @param  None
  * @retval None
  */
void checkModuleSta(void){
	u8 RspCode;
	u8 resetNum=6;//最多重启的次数
	/*STA模式才使用的指令.才有效*/	
	if(RSI_WIFI_OPER_MODE == RSI_WIFI_CLIENT_MODE_VAL){
		delay_ms(1000);delay_ms(1000);//等待一段时间
		//获取当前的连接状态
		rsi_query_conn_status();
		RspCode=Read_PKT();		
		//如果没有连接则多次启动
		while(resetNum-- > 0 ){
			if(rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.conStatusFrameRcv.state[0] != 0){//如果连接
				#if PRINT_UART_LOG
				printf("Module Connected Ap Successfully!\r\n");//1:连接
				#endif
			
				/*查询net参数 [成功链接之后]*/
				RspCode=rsi_query_net_parms();         		//this is command
				RspCode=Read_PKT();
				if(RSI_RSP_NETWORK_PARAMS == RspCode){
					memcpy(localhost,rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.qryNetParmsFrameRcv.ipaddr,IPV4_LENGTH);
					#if PRINT_UART_LOG
					printf("Module Ip : %d:%d:%d:%d\r\n",localhost[0],localhost[1],localhost[2],localhost[3]);//0:未连接	
					#endif
				}
				
				/*查询RSSI [成功链接之后]*/
				RspCode=rsi_query_rssi();          			//this is command
				RspCode=Read_PKT();
				#if PRINT_UART_LOG
				printf("RSSI:0x%0.2X\r\n",rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.rssiFrameRcv.rssiVal[0]);	
				#endif	
				return;	//如果连接了则直接返回			
			}else{//如果没有连接
				#if PRINT_UART_LOG
				printf("Module Connected Ap Unsuccessfully!\r\n");//1:连接
				printf("Soft Resetting Module ...\r\n");//重启
				#endif
				rsi_module_soft_reset();//软件重启
				delay_ms(1000);
				#if PRINT_UART_LOG
				printf("Soft Reset Module Successfully!\r\n");//重启
				printf("\r\n");//设置为Client
				#endif
				setClientModePara();//设置为client模式参数
				WIFI_BOOT();//boot
				WIFI_Conf();//conf	
				delay_ms(500);
				rsi_query_conn_status();//查看当前的连接状态
				RspCode=Read_PKT();					
			}
		
		};
		//说明重启多次失败了，设置为AP模式
		if(rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.conStatusFrameRcv.state[0] == 0){//没有连接
			#if PRINT_UART_LOG
			printf("Module Connected Ap Unsuccessfully!\r\n");//0:未连接
			#endif
			
			//reset模组
			do{
				#if PRINT_UART_LOG
				printf("Soft Resetting Module ...\r\n");
				#endif
				rsi_module_soft_reset();
				delay_ms(1500);
//				#if PRINT_UART_LOG
//				printf("Module Return %d\r\n",RspCode);
//				#endif
				RspCode = Read_PKT();
			}while(RspCode != RSI_RSP_CONNECTION_STATUS);//这里是为什么，只能返回0x48
			#if PRINT_UART_LOG
			printf("Soft Reset Module Successfully!\r\n");
			#endif
			
			
			#if PRINT_UART_LOG
			printf("Setting Module As Ap...\r\n");//0:未连接
			#endif
			//设置为AP模式
			setApModePara();
			
			WIFI_BOOT();
			WIFI_Conf();
			#if PRINT_UART_LOG
			printf("Setted Module As Ap Successfully!\r\n");//0:未连接
			#endif
		}

	}
}

/**
  * @brief  初始化WiFi模组，包括IO初始化、BOOT、CONFIG
  * @param  None
  * @retval None
  */
void InitWiFi(void){
	WIFI_SPI_Conf();
	u8 status;
	status = WIFI_BOOT();
	if(status!=0){//说明有问题
		#if PRINT_UART_LOG
		printf("WiFi Boot Unsuccessfully!\r\n");
		return;//boot有问题，直接返回
		#endif
	}else if(status == 0){
		#if PRINT_UART_LOG
		printf("WiFi Boot Successfully!\r\n");
		#endif	
	}
	status = WIFI_Conf();
	if(status!=0){//说明有问题
		#if PRINT_UART_LOG
		printf("WiFi Config Unsuccessfully!\r\n");
		#endif
	}else if(status == 0){
		#if PRINT_UART_LOG
		printf("WiFi Config Successfully!\r\n");
		#endif	
	}
	delay_ms(1000);
}

/**
  * @brief  打开所有需要的套接字
  * @param  None
  * @retval None
  */
void openAllSocket(void){
	u8 status;
	DATA_AUTO_CHECK_EN= 0;
	status = OpenLudpSocket(destIp_txrx,destSocket_txrx,moduleSocket_txrx,&socketDescriptor_txrx);//服务器的数据
	if(status != 0){//有问题
		printf("WiFi Data-UDP Connect Unsuccessfully!\r\n");
	}else if(status == 0){
		printf("WiFi Data-UDP Connect Successfully!\r\n");
	}
	OpenLudpSocket(localDestIp_txrx,localDestSocket_txrx,localModuleSocket_txrx,&localSocketDescriptor_txrx);//局域网内数据传输
	OpenLudpSocket(destIp_sync,destSocket_sync,moduleSocket_sync,&socketDescriptor_sync);//时钟同步socket	
	DATA_AUTO_CHECK_EN= 1;
}
