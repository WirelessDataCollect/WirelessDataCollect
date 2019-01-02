#ifndef __ADC_H
#define __ADC_H
#include "sys.h"
#include "delay.h"
#include "stm32f4xx.h"

//====定义ADC相关的引脚
#define ADC_MAX_BYTES 8//ADC一次最多读取的bytes数，2*通道数
#define ADC_SPIx SPI2
#define ADC_SPIx_AF GPIO_AF_SPI2
#define ADC_SPIx_PERIPH RCC_APB1Periph_SPI2
//BUSY
#define ADC_BUSY_PORT GPIOA
#define ADC_BUSY_PIN GPIO_Pin_2
#define getAdcBusyState() GPIO_ReadBits(ADC_BUSY_PORT,ADC_BUSY_PIN)
//CONV
#define ADC_CONV_PORT GPIOB
#define ADC_CONV_PIN GPIO_Pin_11
#define ADC_CONV_H GPIO_SetBits(ADC_CONV_PORT,ADC_CONV_PIN)
#define ADC_CONV_L GPIO_ResetBits(ADC_CONV_PORT,ADC_CONV_PIN)
//RAGE:10V or 5V
#define ADC_RAGE_PORT GPIOC
#define ADC_RAGE_PIN GPIO_Pin_6
#define ADC_Set5V() GPIO_ResetBits(ADC_RAGE_PORT,ADC_RAGE_PIN);
#define ADC_Set10V() GPIO_SetBits(ADC_RAGE_PORT,ADC_RAGE_PIN);
//Sample OS1/2/3
#define ADC_OS1_PORT GPIOA
#define ADC_OS1_PIN GPIO_Pin_8
#define ADC_OS2_PORT GPIOC
#define ADC_OS2_PIN GPIO_Pin_9
#define ADC_OS3_PORT GPIOC
#define ADC_OS3_PIN GPIO_Pin_8
//OS1/2/3=110 64采样
#define ADC_64Sample_Mean() {GPIO_SetBits(ADC_OS1_PORT,ADC_OS1_PIN);GPIO_SetBits(ADC_OS2_PORT,ADC_OS2_PIN);GPIO_ResetBits(ADC_OS3_PORT,ADC_OS3_PIN);}  
//时钟
#define ADC_CLK_PORT GPIOB
#define ADC_CLK_PIN GPIO_Pin_10
#define ADC_CLK_AF_PINSOURCE GPIO_PinSource10
//MISO
#define ADC_MISO_PORT GPIOC
#define ADC_MISO_PIN GPIO_Pin_2
#define ADC_MISO_AF_PINSOURCE GPIO_PinSource2
//MOSI
#define ADC_MOSI_PORT GPIOC
#define ADC_MOSI_PIN GPIO_Pin_3
#define ADC_MOSI_AF_PINSOURCE GPIO_PinSource3
//CS
#define ADC_CS_PORT GPIOA
#define ADC_CS_PIN GPIO_Pin_3
#define ADC_CS_H() GPIO_SetBits(ADC_CS_PORT,ADC_CS_PIN)
#define ADC_CS_L() GPIO_ResetBits(ADC_CS_PORT,ADC_CS_PIN)
//RESET
#define ADC_RST_PORT GPIOC
#define ADC_RST_PIN GPIO_Pin_7
#define ADC_RST_H()	GPIO_SetBits(ADC_RST_PORT,ADC_RST_PIN)
#define ADC_RST_L()	GPIO_ResetBits(ADC_RST_PORT,ADC_RST_PIN)

//和ADC交互的引脚配置
void ADC_CTRL_Conf(void);
u8 ADC_SPIx_ReadWriteByte(u8 TxData);
u8 * ADC_Read(u16 NumByteToRead);

#endif