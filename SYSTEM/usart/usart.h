/**
  ******************************************************************************
  * @file    usart.h
  * @author  zju.nesc.iotlab    浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    8-April-2019
  * @brief   usart function   串口函数
  ******************************************************************************
  */

#ifndef __USART_H
#define __USART_H

//-------------include---------------//
#include "stdio.h"	
#include "string.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 

/** 
  * @brief  串口性质
  * @{
  */
#define USART_REC_LEN  			200  	/*!< 定义最大接收字节数>*/
#define USART_BUFF_LEN  		250  	/*!< 定义最大buff容量>*/
#define EN_USART1_RX 			  1		  /*!< 使能（1）/禁止（0）串口1接收>*/
#define PRINT_UART_LOG      1     /*!< 输出日志到串口	>*/
/**
  * @}
  */
	
/** 
  * @brief  串口命令结构体
  * @{
  */
typedef struct{
	//接收缓冲,最大USART_REC_LEN个字节.
	u8 buff[USART_BUFF_LEN];
	u8 CmdCompleteFlag;
  int head,tail;
}CMD_QUEUE;
/**
  * @}
  */

//! 接收命令的缓存器
extern CMD_QUEUE CMD_RX_BUF;



void uart_init(u32 bound);
void uart_queue_put(volatile CMD_QUEUE * pQueue, u8 ch);
void uart_queue_put_many(volatile CMD_QUEUE * pQueue, u8 * ch,u16 len);//put多个
u8 uart_queue_pop(volatile CMD_QUEUE * pQueue);
u16 uart_queue_length(volatile CMD_QUEUE * pQueue);
void uart_queue_clear(volatile CMD_QUEUE * pQueue);


#endif


