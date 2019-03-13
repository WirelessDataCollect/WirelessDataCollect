/**
  ******************************************************************************
  * @file    wificonf.h
  * @author  zju.nesc.iotlab 浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    13-March-2019
  * @brief   wifi module configuration cfunctions   wifi模组配置方法
  ******************************************************************************
  */

#ifndef __WIFICONF_H
#define __WIFICONF_H

//-------------include---------------//
#include "sys.h"
#include "delay.h"
#include "stm32f4xx.h"


//!日志函数
#define LOGS(...)	printf(__VA_ARGS__)

/** 
  * @brief  SPI设置
  * @{
  */ 
#define WIFI_SPIx SPI1
#define WIFI_SPIx_AF GPIO_AF_SPI1
/**
  * @}
  */
  
  
/** 
  * @brief  中断
  * @{
  */
/* GPIO新版本*/
#define WIFI_INTR_PORT              GPIOA
#define WIFI_INTR_PIN               GPIO_Pin_4
/* GPIO旧版本*/
//#define WIFI_INTR_PORT              GPIOC
//#define WIFI_INTR_PIN               GPIO_Pin_4

/* 中断源新版本*/
#define WIFI_INTR_EXTI_PORTSOURCE   EXTI_PortSourceGPIOA
#define WIFI_INTR_EXTI_PINSOURCE    GPIO_PinSource4
/* 中断源旧版本*/
//#define WIFI_INTR_EXTI_PORTSOURCE   EXTI_PortSourceGPIOC
//#define WIFI_INTR_EXTI_PINSOURCE    GPIO_PinSource4

/* 中断线，新旧相同*/
#define WIFI_INTR_EXTI_LINE         EXTI_Line4//中断线
#define WIFI_INTR_EXTI_CH           EXTI4_IRQn//中断入口
/**
  * @}
  */

/** 
  * @brief  SPI时钟
  * @{
  */
/* SPI时钟新旧版本相同*/
#define WIFI_CLK_PORT               GPIOA
#define WIFI_CLK_PIN                GPIO_Pin_5
#define WIFI_CLK_AF_PINSOURCE       GPIO_PinSource5
/**
  * @}
  */


/** 
  * @brief  SPI的MISO
  * @{
  */
/* SPI MISO新旧版本相同*/
#define WIFI_MISO_PORT              GPIOA
#define WIFI_MISO_PIN               GPIO_Pin_6
#define WIFI_MISO_AF_PINSOURCE      GPIO_PinSource6
/**
  * @}
  */

/** 
  * @brief  SPI的MISO
  * @{
  */
/* SPI MOSI新旧版本相同*/
#define WIFI_MOSI_PORT              GPIOA
#define WIFI_MOSI_PIN               GPIO_Pin_7
#define WIFI_MOSI_AF_PINSOURCE      GPIO_PinSource7
/**
  * @}
  */

/** 
  * @brief  SPI的片选
  * @{
  */
//CS
#define WIFI_CS_PORT                GPIOC
/* 新版本*/
#define WIFI_CS_PIN                 GPIO_Pin_4
/* 旧版本*/
//#define WIFI_CS_PIN               GPIO_Pin_5
/* 片选信号，低：选中*/
#define WIFI_CS_H()                 GPIO_SetBits(WIFI_CS_PORT,WIFI_CS_PIN)
#define WIFI_CS_L()                 GPIO_ResetBits(WIFI_CS_PORT,WIFI_CS_PIN)
/**
  * @}
  */

/** 
  * @brief  WiFi模组的Reset
  * @{
  */
/* RESET新版本*/
#define WIFI_RST_PORT               GPIOC
#define WIFI_RST_PIN                GPIO_Pin_5
/* RESET旧版本*/
//#define WIFI_RST_PORT               GPIOB
//#define WIFI_RST_PIN                GPIO_Pin_0

#define WIFI_RST_H()	            GPIO_SetBits(WIFI_RST_PORT,WIFI_RST_PIN)
#define WIFI_RST_L()	            GPIO_ResetBits(WIFI_RST_PORT,WIFI_RST_PIN)
/**
  * @}
  */
  


u8 WIFI_SPIx_TxRx(u8 TxData);
void WIFI_EXTI_Conf(void) ;
void WIFI_SPI_Conf(void);
void WIFI_NVIC_Config(void);
u8 WIFI_Conf(void);
u8 WIFI_BOOT(void);

void OpenSocket(u8 *destIP,unsigned short destSocket,unsigned short moduleSocket,unsigned short polo );
int Read_PKT(void);
int Check_PKT(void);
void InitWiFi(void);
void checkModuleSta(void);
void openAllSocket(void);
void setClientModePara(void);
void setApModePara(void);

#endif

