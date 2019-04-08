/**
  ******************************************************************************
  * @file    delay.c
  * @author  zju.nesc.iotlab    浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    8-April-2019
  * @brief   delay function   延时函数
  ******************************************************************************
  */

//-------------include---------------//
#include "delay.h"
#include "sys.h"

static u8  fac_us=0;							//us延时倍乘数			   
static u16 fac_ms=0;							//ms延时倍乘数,在os下,代表每个节拍的ms数
	
/**
  * @brief  初始化延迟函数
  * @param  SYSCLK：系统时钟频率
  * @retval None
  */
void delay_init(u8 SYSCLK)
{
 	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	fac_us=SYSCLK/8;						//不论是否使用OS,fac_us都需要使用
	fac_ms=(u16)fac_us*1000;				//非OS下,代表每个ms需要的systick时钟数   
}								    

/**
  * @brief  延时nus
  * @param  nus：要延时的us数.
  * @retval None
  */
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 				//时间加载	  		 
	SysTick->VAL=0x00;        				//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ; //开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; //关闭计数器
	SysTick->VAL =0X00;       				//清空计数器 
}

/**
  * @brief  延时nms
  * @param  nms：要延时的ms数
  * @note   SysTick->LOAD为24位寄存器,所以,最大延时为:
						nms<=0xffffff*8*1000/SYSCLK
						SYSCLK单位为Hz,nms单位为ms
						对168M条件下,nms<=798ms 
  * @retval None
  */
void delay_xms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;			//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           			//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL =0X00;     		  		//清空计数器	  	    
} 
//延时nms 
//nms:0~65535
/**
  * @brief  延时nms
  * @param  nms：要延时的ms数
  * @note   nms取值范围0~65535
  * @retval None
  */
void delay_ms(u16 nms)
{	 	 
	u8 repeat=nms/540;
	u16 remain=nms%540;
	while(repeat)
	{
		delay_xms(540);
		repeat--;
	}
	if(remain)delay_xms(remain);
} 
		

