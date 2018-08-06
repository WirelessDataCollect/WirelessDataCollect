#ifndef __IIC_H
#define __IIC_H
#include "led.h"
#define IIC_SCL_H		GPIO_SetBits(GPIOB, GPIO_Pin_15)//WB_Gpio_Put(33,GPIO_HIGH)
#define IIC_SCL_L		GPIO_ResetBits(GPIOB, GPIO_Pin_15)//WB_Gpio_Put(33,0)

#define IIC_SDA_H		GPIO_SetBits(GPIOB, GPIO_Pin_14)//WB_Gpio_Put(32,GPIO_HIGH)
#define IIC_SDA_L		GPIO_ResetBits(GPIOB, GPIO_Pin_14)//WB_Gpio_Put(32,0)

#define READ_SDA    	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)//WB_Gpio_Get(32)//输入SDA 

//#define SDA_IN()		WB_Gpio_Init(32,GPIO_INPUT,GPIO_HIGH); 
//#define SDA_OUT()		WB_Gpio_Init(32,GPIO_OUTPUT,GPIO_HIGH); 

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);			//IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
uint8_t IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	  
#endif
















