#include "wificonf.h"
#include "rsi_global.h"
#include "rsi_app.h"
//时钟配置


void RCC_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
	RNG_Cmd(ENABLE );
}
 

//设置WIFI的中断NVIC
void WIFI_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=WIFI_INTR_EXTI_CH;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//设置成最高优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void WIFI_SPI_Conf(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	RCC_Config();	
	WIFI_EXTI_Conf();	
	WIFI_NVIC_Config();	
	//CS:PC5
	GPIO_InitStructure.GPIO_Pin = WIFI_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(WIFI_CS_PORT, &GPIO_InitStructure);
	
	//RST
	GPIO_InitStructure.GPIO_Pin = WIFI_RST_PIN;
	GPIO_Init(WIFI_RST_PORT, &GPIO_InitStructure);
		
	//INTR中断
	GPIO_InitStructure.GPIO_Pin = WIFI_INTR_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(WIFI_INTR_PORT, &GPIO_InitStructure); 
	SYSCFG_EXTILineConfig(WIFI_INTR_EXTI_PORTSOURCE,WIFI_INTR_EXTI_PINSOURCE);  
	
	//CLK;MISO;MOSI
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
	//复用
	GPIO_PinAFConfig(WIFI_CLK_PORT,WIFI_CLK_AF_PINSOURCE,WIFI_SPIx_AF);
	GPIO_PinAFConfig(WIFI_MISO_PORT,WIFI_MISO_AF_PINSOURCE,WIFI_SPIx_AF);
	GPIO_PinAFConfig(WIFI_MOSI_PORT,WIFI_MOSI_AF_PINSOURCE,WIFI_SPIx_AF);

	//wifi spi的配置
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
//设置WIFI中断
void WIFI_EXTI_Conf(void)
{
	EXTI_InitTypeDef   EXTI_Type;
	EXTI_Type.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Type.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Type.EXTI_Line=WIFI_INTR_EXTI_LINE;
	EXTI_Type.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_Type);
}
//WiFi SPI的收发
u8 WIFI_SPIx_TxRx(u8 TxData)
{		 			 
	WIFI_SPIx->DR=TxData;
	while ((WIFI_SPIx->SR&SPI_I2S_FLAG_RXNE) == 0); 
	return WIFI_SPIx->DR;//SPI_I2S_ReceiveData(SPI1);		    
}




