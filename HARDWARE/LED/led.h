#ifndef __LED_H
#define __LED_H
#include "sys.h"



//LED端口定义
#define LED1 PCout(10)	// DS0
#define LED2 PDout(2)	// DS1	

//模拟信号输入模式选择
#define Channel1 PCout(6)
#define Channel2 PCout(7)
#define Channel3 PCout(8)
#define Channel4 PCout(9)


//数字信号电平检测
#define DIGITAL_INPUT1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)
#define DIGITAL_INPUT2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)


void LED_GPIO_Init(void);//初始化	
void Channel_model(u8 modle[]);
#endif
