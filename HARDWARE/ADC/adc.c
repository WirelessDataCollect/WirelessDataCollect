/**
  ******************************************************************************
  * @file    adc.c
  * @author  zju.nesc.iotlab 浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    13-March-2019
  * @brief   ad7606 configuration/read functions   ad7606相关配置和读写方法
  ******************************************************************************
  */

//-------------include---------------//
#include "adc.h"
#include "rsi_global.h"
#include "rsi_app.h"
#include "queue.h"
#include "userwifi.h"

/**
  * @brief  MCU上和ADC通信的时钟配置
  * @note  MCU时钟
  * @param  None
  * @retval None
  */
void ADC_RCC_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能时钟
	RCC_APB1PeriphClockCmd(ADC_SPIx_PERIPH, ENABLE);

}

/**
  * @brief  ADC的控制引脚配置（包括SPI、复位等）配置
  * @param  None
  * @retval None
  */
void ADC_CTRL_Conf(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	ADC_RCC_Config();//时钟配置
	/* CS*/
	GPIO_InitStructure.GPIO_Pin = ADC_CS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(ADC_CS_PORT, &GPIO_InitStructure);
	ADC_CS_L();
	/* CONV*/
	GPIO_InitStructure.GPIO_Pin = ADC_CONV_PIN;
	GPIO_Init(ADC_CONV_PORT, &GPIO_InitStructure);
	ADC_CONV_H();//默认从拉高开始
	/* RAGE:5V or 10V*/
	GPIO_InitStructure.GPIO_Pin = ADC_RAGE_PIN;
	GPIO_Init(ADC_RAGE_PORT, &GPIO_InitStructure);
	ADC_Set5V();
	/* RST*/
	GPIO_InitStructure.GPIO_Pin = ADC_RST_PIN;
	GPIO_Init(ADC_RST_PORT, &GPIO_InitStructure);
	ADC_RST_L();delay_ms(1);ADC_RST_H();delay_ms(1);ADC_RST_L();//复位
	/* OverSample 1/2/3*/
	GPIO_InitStructure.GPIO_Pin = ADC_OS1_PIN;
	GPIO_Init(ADC_OS1_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = ADC_OS2_PIN;
	GPIO_Init(ADC_OS2_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = ADC_OS3_PIN;
	GPIO_Init(ADC_OS3_PORT, &GPIO_InitStructure);
	//!8 OS带宽较高，平均效果好
	ADC_8Sample_Mean();
	/* BUSY,输入转换的状态*/
	GPIO_InitStructure.GPIO_Pin = ADC_BUSY_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(ADC_BUSY_PORT, &GPIO_InitStructure); 

	/* SPI：CLK;MISO;MOSI*/
	GPIO_InitStructure.GPIO_Pin = ADC_CLK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(ADC_CLK_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = ADC_MOSI_PIN;	
	GPIO_Init(ADC_MOSI_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = ADC_MISO_PIN;	
	GPIO_Init(ADC_MISO_PORT, &GPIO_InitStructure);

	ADC_CS_H();
	/* 复用*/
	GPIO_PinAFConfig(ADC_CLK_PORT,ADC_CLK_AF_PINSOURCE,ADC_SPIx_AF);
	GPIO_PinAFConfig(ADC_MISO_PORT,ADC_MISO_AF_PINSOURCE,ADC_SPIx_AF);
	GPIO_PinAFConfig(ADC_MOSI_PORT,ADC_MOSI_AF_PINSOURCE,ADC_SPIx_AF);

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
	SPI_Init(ADC_SPIx, &SPI_InitStructure);  

	SPI_Cmd(ADC_SPIx, ENABLE); 
	ADC_CS_L();
}

//读取ADC数据，最多8个通道，16bytes数据
//如果使用AD7606-4则只有4个通道，8bytes数据
u8 AD7606_Data_Temp[ADC_MAX_BYTES]={0,0};
/**
  * @brief  ADC数据读取，返回一个u8指针，存储采集一次的数据
  * @note   存储空间一定，后一次覆盖前一次空间
  * @param  NumByteToRead：要读取的数据字节长度
  * @retval AD7606_Data_Temp：ADC数据存储地址
  */
u8 * ADC_Read(u16 NumByteToRead)
{
 	u16 i;											    
	ADC_CS_L();   //片选  
	//4四个通道的数据全部保存
    for(i=0;(i<NumByteToRead) && (i < ADC_MAX_BYTES);i++)
	{ 
		AD7606_Data_Temp[i] = ADC_SPIx_ReadWriteByte(0XFF);//循环读数   
    }
	ADC_CS_H();   //取消片选 
	return AD7606_Data_Temp;
}

/**
  * @brief  读取ADC一个字节
  * @param  TxData：要写入的字节
  * @retval 读取的数据
  */
u8 ADC_SPIx_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(ADC_SPIx, SPI_I2S_FLAG_TXE) == RESET){		
		retry++;
		if(retry>200){
			return 0;
		}
	}			  
	/* 通过外设SPIx发送一个数据*/
	SPI_I2S_SendData(ADC_SPIx, TxData); 
	retry=0;

	while (SPI_I2S_GetFlagStatus(ADC_SPIx, SPI_I2S_FLAG_RXNE) == RESET){
		retry++;
		if(retry>200){
			return 0;
		}
	}	  						    
	return SPI_I2S_ReceiveData(ADC_SPIx); //返回通过SPIx最近接收的数据					    
}
