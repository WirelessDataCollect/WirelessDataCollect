#ifndef __SPI_H
#define __SPI_H
#include "sys.h"
#include "delay.h"
#include "stm32f4xx.h"



#define LOGS(...)	printf(__VA_ARGS__)


//====定义wifi相关的引脚
#define WIFI_SPIx SPI1
#define WIFI_SPIx_AF GPIO_AF_SPI1
//中断
#define WIFI_INTR_PORT GPIOA
#define WIFI_INTR_PIN GPIO_Pin_4
#define WIFI_INTR_EXTI_PORTSOURCE EXTI_PortSourceGPIOA
#define WIFI_INTR_EXTI_PINSOURCE GPIO_PinSource4
//时钟
#define WIFI_CLK_PORT GPIOA
#define WIFI_CLK_PIN GPIO_Pin_5
#define WIFI_CLK_AF_PINSOURCE GPIO_PinSource5
//MISO
#define WIFI_MISO_PORT GPIOA
#define WIFI_MISO_PIN GPIO_Pin_6
#define WIFI_MISO_AF_PINSOURCE GPIO_PinSource6
//MOSI
#define WIFI_MOSI_PORT GPIOA
#define WIFI_MOSI_PIN GPIO_Pin_7
#define WIFI_MOSI_AF_PINSOURCE GPIO_PinSource7
//CS
#define WIFI_CS_PORT GPIOC
#define WIFI_CS_PIN GPIO_Pin_14
#define WIFI_CS_H GPIO_SetBits(WIFI_CS_PORT,WIFI_CS_PIN)
#define WIFI_CS_L GPIO_ResetBits(WIFI_CS_PORT,WIFI_CS_PIN)
//RESET
#define WIFI_RST_PORT GPIOC
#define WIFI_RST_PIN GPIO_Pin_5
#define WIFI_RST_H	GPIO_SetBits(WIFI_RST_PORT,WIFI_RST_PIN)
#define WIFI_RST_L	GPIO_ResetBits(WIFI_RST_PORT,WIFI_RST_PIN)



u8 WIFI_SPIx_TxRx(u8 TxData);
void EXTI_Conf(void) ;
void EXTI_TX_Conf(void);
void SPI_Conf(void);

void NVIC_Config(void);
void RCC_Config(void);


char WIFI_Conf(void);
char WIFI_BOOT(void);
void OpenSocket(u8 *destIP,unsigned short destSocket,unsigned short moduleSocket,unsigned short polo );
int Read_PKT(void);
int Check_PKT(void);


#endif

