#include "adc.h"
#include "rsi_global.h"
#include "rsi_app.h"
//时钟配置


void ADC_RCC_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能时钟
	RCC_APB2PeriphClockCmd(ADC_SPIx_PERIPH, ENABLE);
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
	RNG_Cmd(ENABLE );
}

//ADC的控制引脚配置（包括SPI、复位等）配置
void ADC_CTRL_Conf(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	ADC_RCC_Config();//时钟配置
	//CS
	GPIO_InitStructure.GPIO_Pin = ADC_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(ADC_CS_PORT, &GPIO_InitStructure);
	//CONV
	GPIO_InitStructure.GPIO_Pin = ADC_CONV_PIN;
	GPIO_Init(ADC_CONV_PORT, &GPIO_InitStructure);
	//RAGE:5V or 10V
	GPIO_InitStructure.GPIO_Pin = ADC_RAGE_PIN;
	GPIO_Init(ADC_RAGE_PORT, &GPIO_InitStructure);
	ADC_Set5V();
	//RST
	GPIO_InitStructure.GPIO_Pin = ADC_RST_PIN;
	GPIO_Init(ADC_RST_PORT, &GPIO_InitStructure);
	ADC_RST_L();delay_ms(1);ADC_RST_H();//复位
	//OS1/2/3
	GPIO_InitStructure.GPIO_Pin = ADC_OS1_PIN;
	GPIO_Init(ADC_OS1_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = ADC_OS2_PIN;
	GPIO_Init(ADC_OS2_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = ADC_OS3_PIN;
	GPIO_Init(ADC_OS3_PORT, &GPIO_InitStructure);
	ADC_64Sample_Mean();//64次采样平均
	//BUSY,输入转换的状态
	GPIO_InitStructure.GPIO_Pin = ADC_BUSY_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(ADC_BUSY_PORT, &GPIO_InitStructure); 

	//SPI：CLK;MISO;MOSI
	GPIO_InitStructure.GPIO_Pin = ADC_CLK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(ADC_CLK_PORT, &GPIO_InitStructure);//初始化
	GPIO_InitStructure.GPIO_Pin = ADC_MOSI_PIN;	
	GPIO_Init(ADC_MOSI_PORT, &GPIO_InitStructure);	//初始化
	GPIO_InitStructure.GPIO_Pin = ADC_MISO_PIN;	
	GPIO_Init(ADC_MISO_PORT, &GPIO_InitStructure);	//初始化

	ADC_CS_H();
	//复用
	GPIO_PinAFConfig(ADC_CLK_PORT,ADC_CLK_AF_PINSOURCE,ADC_SPIx_AF);
	GPIO_PinAFConfig(ADC_MISO_PORT,ADC_MISO_AF_PINSOURCE,ADC_SPIx_AF);
	GPIO_PinAFConfig(ADC_MOSI_PORT,ADC_MOSI_AF_PINSOURCE,ADC_SPIx_AF);

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
	SPI_Init(ADC_SPIx, &SPI_InitStructure);  

	SPI_Cmd(ADC_SPIx, ENABLE); 
	ADC_CS_L(); 
}
//ADC的SPIx的中断
void ADC_EXTI_Conf(void)
{
	
}
//ADC的SPIx的NVIC
void ADC_NVIC_Config(void)
{
	
}