#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h" 
#include "queue.h"
// ADC_INT PB5 
// SCL PB6
// SDA PB7 	
 	   		   
//IO方向设置
#define SDA_IN()  {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=0<<7*2;}	//PB7输入模式
#define SDA_OUT() {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=1<<7*2;} //PB7输出模式
//IO操作函数	 
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	 
#define READ_SDA   PBin(7)  //输入SDA 
#define ADC_DISANBLE  PBin(5)  // INIT
//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

// 
extern Queue adc_queue;

//ADS7924 寄存器操作
// AO = GND
#define ADS7924W_Adress 0x90  //写地址
#define ADS7924R_Adress 0x91  //读地址


#define MODECNTRL_Adress 0x00
#define MODECNTRL_Reg    0xFC//0xFC

#define SLPCONFIG_Adress 0x13
#define SLPCONFIG_Reg    0x20

#define ACQCONFIG_Adress 0x14
#define ACQCONFIG_Reg 0x1f

// Tacq= 0x1f*2+6 = 68us
// Tconv = 4 us
//SLPTime = 2.5ms/4
// Tup = 0
// t=4*(Tacq+Tconv+Tup)+SLPTime


#define DATA0_U_Adress 0x02
u8 ADS8266_config(void);
u8 ADS8266_read(void);
#endif
















