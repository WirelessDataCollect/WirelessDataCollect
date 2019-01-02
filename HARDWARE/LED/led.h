#ifndef __LED_H
#define __LED_H
#include "sys.h"



//LED端口定义
#define LED1_PORT GPIOB
#define LED1_PIN GPIO_Pin_3
#define LED2_PORT GPIOD
#define LED2_PIN GPIO_Pin_2
#define LED1 PBout(3)	// LED1
#define LED1_OFF(x) LED1=x //是否关闭LED1
#define LED2 PDout(2)	// LED2	
#define LED2_OFF(x) LED2=x //是否关闭LED2

//模拟信号输入模式选择
#define CH1_PORT GPIOA
#define CH1_PIN GPIO_Pin_15
#define CH2_PORT GPIOC
#define CH2_PIN GPIO_Pin_10
#define CH3_PORT GPIOC
#define CH3_PIN GPIO_Pin_11
#define CH4_PORT GPIOC
#define CH4_PIN GPIO_Pin_12
#define Channel1 PAout(15)
#define Channel2 PCout(10)
#define Channel3 PCout(11)
#define Channel4 PCout(12)


//数字信号电平检测
#define DIG1_PORT GPIOA
#define DIG1_PIN GPIO_Pin_1
#define DIG2_PORT GPIOA
#define DIG2_PIN GPIO_Pin_0
#define DIGITAL_INPUT1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)
#define DIGITAL_INPUT2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)


void LED_GPIO_Init(void);//初始化	
void Channel_model(u8 modle[]);
#endif
