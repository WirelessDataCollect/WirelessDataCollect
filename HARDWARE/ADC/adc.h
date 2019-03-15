/**
  ******************************************************************************
  * @file    adc.h
  * @author  zju.nesc.iotlab 浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    13-March-2019
  * @brief   ad7606 configuration/read functions   ad7606相关配置和读写方法
  ******************************************************************************
  */

#ifndef __ADC_H
#define __ADC_H

//-------------include---------------//
#include "sys.h"
#include "delay.h"
#include "stm32f4xx.h"

//! ADC读取长度，共4通道，每个通道2字节
#define ADC_MAX_BYTES                  8

/** 
  * @brief  SPIx说明
  * @{
  */
#define ADC_SPIx                       SPI2
#define ADC_SPIx_AF                    GPIO_AF_SPI2
#define ADC_SPIx_PERIPH                RCC_APB1Periph_SPI2
/**
  * @}
  */
  

/** 
  * @brief  BUSY信号，ADC正在转化
  * @note   AD7606  ->  MCU
  * @{
  */
#define ADC_BUSY_PORT                  GPIOA
#define ADC_BUSY_PIN                   GPIO_Pin_2
#define getAdcBusyState()              GPIO_ReadBits(ADC_BUSY_PORT,ADC_BUSY_PIN)
/**
  * @}
  */
  
/** 
  * @brief  CONV开始转化信号
  * @note   MCU  ->  AD7606
  * @note   转换时间 = N * Tconv + (N-1) * 1us,Tconv = 2us for AD7606-4,Tconv = 3us for AD7606-6
	        AD7606-4,64 Sample ratio,T = 193
	        CONV  :  H(25ns,转换中)  ->  L(25ns)   ->   H(25ns,转换中)
  * @{
  */
#define ADC_CONV_PORT                  GPIOC
#define ADC_CONV_PIN                   GPIO_Pin_7
#define ADC_CONV_H()                   GPIO_SetBits(ADC_CONV_PORT,ADC_CONV_PIN)
#define ADC_CONV_L()                   GPIO_ResetBits(ADC_CONV_PORT,ADC_CONV_PIN)
/**
  * @}
  */

/** 
  * @brief  AD7606量程
  * @note   MCU  ->  AD7606
  * @{
  */
#define ADC_RAGE_PORT                  GPIOC
#define ADC_RAGE_PIN                   GPIO_Pin_6
#define ADC_Set5V()                    GPIO_ResetBits(ADC_RAGE_PORT,ADC_RAGE_PIN);
#define ADC_Set10V()                   GPIO_SetBits(ADC_RAGE_PORT,ADC_RAGE_PIN);
/**
  * @}
  */

/** 
  * @brief  AD7606过采样(滤波)
  * @note   MCU  ->  AD7606
  * @note   
  * @{
  */
#define ADC_OS1_PORT                   GPIOA
#define ADC_OS1_PIN                    GPIO_Pin_8
#define ADC_OS2_PORT                   GPIOC
#define ADC_OS2_PIN                    GPIO_Pin_9
#define ADC_OS3_PORT                   GPIOC
#define ADC_OS3_PIN                    GPIO_Pin_8
/**
  * @}
  */
//!OS_Val = 4*(OS3)+2*(OS2)+1*(OS3)，则过采样 = 2^(OS_Val)
//例如OS_Val = 4(即100)，则过采样 = 16，16次平均
#define ADC_2Sample_Mean()             {GPIO_SetBits(ADC_OS1_PORT,ADC_OS1_PIN);GPIO_ResetBits(ADC_OS2_PORT,ADC_OS2_PIN);GPIO_ResetBits(ADC_OS3_PORT,ADC_OS3_PIN);} 
#define ADC_4Sample_Mean()             {GPIO_ResetBits(ADC_OS1_PORT,ADC_OS1_PIN);GPIO_SetBits(ADC_OS2_PORT,ADC_OS2_PIN);GPIO_ResetBits(ADC_OS3_PORT,ADC_OS3_PIN);}
#define ADC_8Sample_Mean()             {GPIO_SetBits(ADC_OS1_PORT,ADC_OS1_PIN);GPIO_SetBits(ADC_OS2_PORT,ADC_OS2_PIN);GPIO_ResetBits(ADC_OS3_PORT,ADC_OS3_PIN);} 
#define ADC_16Sample_Mean()            {GPIO_ResetBits(ADC_OS1_PORT,ADC_OS1_PIN);GPIO_ResetBits(ADC_OS2_PORT,ADC_OS2_PIN);GPIO_SetBits(ADC_OS3_PORT,ADC_OS3_PIN);}
#define ADC_32Sample_Mean()            {GPIO_SetBits(ADC_OS1_PORT,ADC_OS1_PIN);GPIO_ResetBits(ADC_OS2_PORT,ADC_OS2_PIN);GPIO_SetBits(ADC_OS3_PORT,ADC_OS3_PIN);}
#define ADC_64Sample_Mean()            {GPIO_ResetBits(ADC_OS1_PORT,ADC_OS1_PIN);GPIO_SetBits(ADC_OS2_PORT,ADC_OS2_PIN);GPIO_SetBits(ADC_OS3_PORT,ADC_OS3_PIN);}
//!时钟
#define ADC_CLK_PORT                   GPIOB
#define ADC_CLK_PIN                    GPIO_Pin_10
#define ADC_CLK_AF_PINSOURCE           GPIO_PinSource10
//!MISO
#define ADC_MISO_PORT                  GPIOC
#define ADC_MISO_PIN                   GPIO_Pin_2
#define ADC_MISO_AF_PINSOURCE          GPIO_PinSource2
//!MOSI
#define ADC_MOSI_PORT                  GPIOC
#define ADC_MOSI_PIN                   GPIO_Pin_3
#define ADC_MOSI_AF_PINSOURCE          GPIO_PinSource3
//!CS
#define ADC_CS_PORT                    GPIOA
#define ADC_CS_PIN                     GPIO_Pin_3
#define ADC_CS_H()                     GPIO_SetBits(ADC_CS_PORT,ADC_CS_PIN)
#define ADC_CS_L()                     GPIO_ResetBits(ADC_CS_PORT,ADC_CS_PIN)
//!RESET
#define ADC_RST_PORT                   GPIOB
#define ADC_RST_PIN                    GPIO_Pin_11
#define ADC_RST_H()	                   GPIO_SetBits(ADC_RST_PORT,ADC_RST_PIN)
#define ADC_RST_L()                    GPIO_ResetBits(ADC_RST_PORT,ADC_RST_PIN)

//!和ADC交互的引脚配置
void ADC_CTRL_Conf(void);
u8 ADC_SPIx_ReadWriteByte(u8 TxData);
u8 * ADC_Read(u16 NumByteToRead);

#endif

