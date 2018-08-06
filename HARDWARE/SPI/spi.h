#ifndef __SPI_H
#define __SPI_H
#include "sys.h"
#include "delay.h"
#include "stm32f4xx.h"
#define SPI_CS_H	GPIO_SetBits(GPIOC,GPIO_Pin_5)
#define SPI_CS_L	GPIO_ResetBits(GPIOC,GPIO_Pin_5)
#define WIFI_RST_H	GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define WIFI_RST_L	GPIO_ResetBits(GPIOB,GPIO_Pin_0)
u8 SPI1_TxRx(u8 TxData);
void EXTI_Conf(void) ;
void SPI_Conf(void);

void NVIC_Config(void);
void RCC_Config(void);


char WIFI_Conf(void);
char WIFI_BOOT(void);
void OpenSocket(char *destIP,unsigned short destSocket,unsigned short moduleSocket,unsigned short polo );
int Read_PKT(void);
int Check_PKT(void);


#endif

