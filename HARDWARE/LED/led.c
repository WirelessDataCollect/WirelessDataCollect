#include "led.h" 

s8 channel[4];
   
//LED IO初始化
//LED1 PB4
//LED2 PD2
// Vin Iin modle choose  高电平为电压输入模式
//EN1 PA15
//EN2 PC10
//EN3 PC11
//EN4 PC12
void LED_GPIO_Init(void)
{    	 
	GPIO_InitTypeDef  GPIO_InitStructure;
	//时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOB时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOC时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOD时钟
	
	//开关信号输入
	GPIO_InitStructure.GPIO_Pin = DIG1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(DIG1_PORT, &GPIO_InitStructure);//初始化
	GPIO_InitStructure.GPIO_Pin = DIG2_PIN;
	GPIO_Init(DIG2_PORT, &GPIO_InitStructure);//初始化	
	//ADG711的开关通道
	GPIO_InitStructure.GPIO_Pin = CH1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(CH1_PORT, &GPIO_InitStructure);//初始化
	GPIO_InitStructure.GPIO_Pin = CH2_PIN;
	GPIO_Init(CH2_PORT, &GPIO_InitStructure);//初始化
	GPIO_InitStructure.GPIO_Pin = CH3_PIN;
	GPIO_Init(CH3_PORT, &GPIO_InitStructure);//初始化	
	GPIO_InitStructure.GPIO_Pin = CH4_PIN;
	GPIO_Init(CH4_PORT, &GPIO_InitStructure);//初始化
	//默认通道拉低
	Channel1=0;Channel2=0;Channel3=0;Channel4=0;
	//LED
	GPIO_InitStructure.GPIO_Pin = LED1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(LED1_PORT, &GPIO_InitStructure);//初始化
	GPIO_InitStructure.GPIO_Pin = LED2_PIN;
	GPIO_Init(LED2_PORT, &GPIO_InitStructure);//初始化
	LED1_OFF(1);LED2_OFF(1);//关灯
}



void Channel_model(u8 modle[])
{		
	Channel1 = modle[0];
	channel[0] = modle[0];
	Channel2 = modle[1];
	channel[1] = modle[1];
	Channel3 = modle[2];
	channel[2] = modle[2];
	Channel4 = modle[3];
	channel[3] = modle[3];
}




