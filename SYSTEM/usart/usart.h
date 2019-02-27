#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "string.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define USART_BUFF_LEN  		250  	//定义最大buff容量
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
#define PRINT_UART_LOG          1       //输出日志到串口	
typedef struct{
	//接收缓冲,最大USART_REC_LEN个字节.
	u8 buff[USART_BUFF_LEN];
	u8 CmdCompleteFlag;
	//接收状态
	//bit15，	接收完成标志
	//bit14，	接收到0x0d
	//bit13~0，	接收到的有效字节数目
    int head,tail;
}CMD_QUEUE;

extern CMD_QUEUE CMD_RX_BUF;
//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);


//uart队列处理
void uart_queue_put(volatile CMD_QUEUE * pQueue, u8 ch);
void uart_queue_put_many(volatile CMD_QUEUE * pQueue, u8 * ch,u16 len);//put多个
u8 uart_queue_pop(volatile CMD_QUEUE * pQueue);
u16 uart_queue_length(volatile CMD_QUEUE * pQueue);
void uart_queue_clear(volatile CMD_QUEUE * pQueue);


#endif


