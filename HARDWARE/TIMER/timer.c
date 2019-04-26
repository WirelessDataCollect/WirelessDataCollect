/**
  ******************************************************************************
  * @file    timer.c
  * @author  zju.nesc.iotlab 浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    13-March-2019
  * @brief   timer configuration and running functions   定时器配置和运行方法
  ******************************************************************************
  */

//-------------include---------------//
#include "timer.h"
#include "gpio.h"
#include "queue.h"
#include "string.h"
#include "userwifi.h"
#include "adc.h"
#include "can1.h"
#include "can2.h"
#include "config.h"

/**
  * @brief  定时器4初始化
  * @param  arr：自动重装值
  * @param  psc：预分频值
  * @note   freq = Fclk / (arr + 1) / (psc + 1) ，其中TIM4 Fclk = 84MHz
  * @retval None
  */
void TIM4_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	/* 使能TIM4时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  

	/* 设置自动重装载值*/
	TIM_TimeBaseInitStructure.TIM_Period = arr;
	/* 设置预分频值 */
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
	/* 向上计数模式 */
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	/* 定时器时钟 (CK_INT) 频率与数字滤波器所使用的采样时钟（ETR、TIx）之间的分频比*/
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	/* TIM4参数配置*/
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);

	/* 允许TIM4更新中断*/
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); 
	/* 使能TIM4*/
	TIM_Cmd(TIM4,ENABLE); 

	/* TIM4中断*/
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; 
	/* 抢占优先级*/
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00;
	/* 子优先级3*/
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

/**
  * @brief  定时器4中断处理函数，用于系统时钟计时
  * @param  None
  * @retval None
  */
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //溢出中断
	{
		/* 系统时钟，计时单位由TIM4设置的中断周期值*/
		SYSTEMTIME++;
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);	//清除中断标志位
}

/**
  * @brief  定时器3初始化
  * @param  arr：自动重装值
  * @param  psc：预分频值
  * @note   freq = Fclk / (arr + 1) / (psc + 1) ，其中TIM4 Fclk = 84MHz
  * @retval None
  */
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 

	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//!同步时钟模块距离上次同步的时间间隔
volatile u32 sync_interval_time = 0;

//!ms时间
u32 MS_TIME = 0;
//!指示nodeId闪烁周期
#define NODE_ID_LED_SHINE_1PERIOD      400      /*!< 一次闪烁的周期>*/
#define NODE_ID_LED_SLEEP_PERIOD       2000     /*!< nodeId次闪烁后等待的时间>*/
#define NODE_ID_TIMER_ARR              ((u32)nodeId * NODE_ID_LED_SHINE_1PERIOD + NODE_ID_LED_SLEEP_PERIOD)  /*!< 指示nodeId闪烁周期,包括闪烁和等待的时间>*/
#define NODE_ID_LED_SHINE_PERIOD       ((u32)nodeId * NODE_ID_LED_SHINE_1PERIOD)                             /*!< 指示nodeId闪烁周期,只有闪烁时间>*/
//!ms时间，计算一个nodeId展示周期
u32 dispNodeIdTimer = 0;
/**
  * @brief  定时器3中断处理函数，用于处理各个周期性的活动
  * @note   中断周期以TIM3初始化时决定，暂时采用1ms周期
  * @param  None
  * @retval None
  */
void TIM3_IRQHandler(void)
{
	//!adc数值缓存
	u8 * adcTamp;
	MS_TIME ++ ;
	//!溢出中断
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) 
	{
		/**
		* 在系统初始化后才能运行的程序
		*/
		if(BOARD_STA == BOARD_RUNNING){
			if(IAM_MASTER_CLOCK == 'Y'){
				sync_interval_time++;
			}else{
				/* 如果队列空了，时间戳更新*/
				if(queue_empty(&adc_queue)){
					adc_queue.HeadTime = SYSTEMTIME;
					adc_queue.YYYY_MM_DD = YYMMDD;
				}
				/* 开始发数据了再开始采集*/
				if((Wifi_Send_EN == 1) && (ADC_Get_EN == 1)){
					/*! @note 
						//       转换时间 = N * Tconv + (N-1) * 1us,Tconv = 2us for AD7606-4,Tconv = 3us for AD7606-6
						//       AD7606-4,64 Sample ratio,T = 193
						//       CONV  :  H(25ns,转换中)  ->  L(25ns)   ->   H(25ns,转换中)
					*/
					ADC_CONV_L();//最短时间25ns
					/**采集数据，顺便当做延时用*/
					adcTamp = ADC_Read(ADC_MAX_BYTES);
					/* 读八个字节数据*/
					for(int i=0;i<ADC_MAX_BYTES;i++){
						queue_put((Queue *)&adc_queue, *(adcTamp+i));
							
					}
					/* 拉高开始下一次转换*/
					ADC_CONV_H();//最短时间25ns
				}				
			}
				
			/* LED闪烁*/
			#if WORKING_LED_SHINE_IN_TIMER					
				/* 工作灯*/
				if(RSI_WIFI_OPER_MODE == RSI_WIFI_CLIENT_MODE_VAL){/*!< CLIENT模式下低速闪烁>*/
					if(MS_TIME%1000==0){
						WORKING_LED_CONV();//工作灯
						BEEP_ON(0);//关蜂鸣器
					}
				}else if(RSI_WIFI_OPER_MODE == RSI_WIFI_AP_MODE_VAL){/*!< AP模式下快速闪烁>*/
					if(MS_TIME%150==0){   //工作灯快闪
						WORKING_LED_CONV();
					}
					if((MS_TIME%900) < 150){   //蜂鸣器900ms周期鸣叫
						BEEP_ON(1);
					}else{
						BEEP_ON(0);
					}
				}
			#endif			
		}else if((BOARD_STA == BOARD_INITING) || (BOARD_STA == BOARD_INITING)){
			/* 工作灯亮*/
			WORKING_LED_OFF(0);
		}
		
		/**
		* 在系统启动后就能运行的程序
		*/
		/* LED等闪烁或者亮*/
		#if NODE_ID_LED_SHINE_IN_TIMER	
					
			/* nodeId展示*/
			dispNodeIdTimer++;
			if(dispNodeIdTimer >= NODE_ID_TIMER_ARR){              //计时器大于重装载值，则清零
				dispNodeIdTimer = 0;
				ID_LED_OFF(1);
			}else if(dispNodeIdTimer >= NODE_ID_LED_SHINE_PERIOD){ //计时器大于闪烁周期，则关灯等待
				ID_LED_OFF(1);
			}else if((dispNodeIdTimer % (NODE_ID_LED_SHINE_1PERIOD/2)) == 0){
				ID_LED_CONV();
			}
		#endif
		/* 处理串口或者AP模式下的指令*/
		if(MS_TIME%2000 == 0){
			dealCmdMsg(&CMD_RX_BUF);
		}
		
		/* 输出50ms脉冲，用于测量同步时钟精度*/
		/*! @note 测试时，需要关闭串口打印功能 @ref PRINT_UART_LOG*/
		#if IO_SHINE_IN_TIMER
			if(MS_TIME%20==0){//50ms输出一个脉冲
				PAout(9) = ~PAout(9);
				PAout(10) = ~PAout(10);
			}
		#endif
	 }

	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}



