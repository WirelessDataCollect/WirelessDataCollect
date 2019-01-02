#include "timer.h"
#include "led.h"
#include "myiic.h"
#include "queue.h"
#include "string.h"
#include "userwifi.h"
//////////////////////////////////////////////////////////////////////////////////	 
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz  84M
//这里使用的是定时器3!

void TIM4_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///使能TIM4时钟

	TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 

	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//初始化TIM4

	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //允许定时器4更新中断
	TIM_Cmd(TIM4,ENABLE); //使能定时器4

	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //定时器4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //溢出中断
	{
		SYSTEMTIME++;
#if IO_SHINE_IN_TIMER
			if(SYSTEMTIME%10000==0)//50ms输出一个脉冲
			{
				PAout(9) = ~PAout(9);
				PAout(10) = ~PAout(10);
			}
#endif
#if LED_SHINE_IN_TIMER	
		if(SYSTEMTIME%200000==0)
		{
			LED1=!LED1;//DS1翻转
		}
#endif
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);	//清除中断标志位
}

void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟

	TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 

	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM3,ENABLE); //使能定时器3

	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

#if IAM_MASTER_CLOCK
volatile u16 sync_interval_time = 0;
#endif
//short int time_inter=0;
//volatile u32 time1 = 0;
//volatile u32 time2 = 0;
//volatile u32 status = 0;
//定时器3中断服务函数
//100us INC
//volatile u32 AckFlag = 0;//用于测试是否出现没有接收到Ack的情况，次数
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
#if IAM_MASTER_CLOCK
			sync_interval_time++;
#else

			if(queue_empty(adc_queue)) //如果队列空了
			{
				adc_queue.HeadTime = SYSTEMTIME;
			}
			if(Wifi_Send_EN)//开始发数据了再开始采集
			{
				ADS8266_read();

			}
#endif		
	 }

	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);	//清除中断标志位
}



