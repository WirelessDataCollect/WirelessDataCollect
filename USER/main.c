#include "sys.h"
#include "userwifi.h"
#include "delay.h"  
#include "usart.h"   
#include "led.h"
#include "spi.h"
#include "myiic.h"
#include "queue.h"
#include "can.h"
#include "can2.h"
#include "timer.h"

/*
优先级
    //TIM 3
   	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //子优先级0
	
	//外部中断
	NVIC_InitStructure.NVIC_IRQChannel=EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	
	//CAN1
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     // 主优先级为2
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // 次优先级为0
	
	//CAN2
	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX1_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     // 主优先级为2
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            // 次优先级为1
	
*/
extern u8 CAN_Send_EN;
extern u8 CAN1_Send_EN;
extern u8 CAN2_Send_EN;
u8 IO_input[2];
u8 can_send_package(void);
void Initialization (void)
{
//	uint32_t client_port=0;	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	RCC_Config();	
	LED_GPIO_Init();
	EXTI_Conf();
	NVIC_Config();
	uart_init(115200);		
	delay_init(168);  
	TIM3_Int_Init(999,83); //1ms
	ADS8266_config();
	CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS1_6tq,CAN_BS2_7tq,6,CAN_Mode_Normal);   //500K
	CAN2_Mode_Init(CAN_SJW_1tq,CAN_BS1_6tq,CAN_BS2_7tq,12,CAN_Mode_Normal);   //250k
	queue_init(&adc_queue);
	//SPI_Conf();	
	//WIFI_BOOT();
	//WIFI_Conf();

	//第一部分移植原文件 到mcu工程 
//	while(!RNG_GetFlagStatus(RNG_FLAG_DRDY));
//	client_port=RNG_GetRandomNumber();
	/*以上代码都是和硬件相关 不做解释
	模块需要的是 SPi的配置 中断 控制模块的IO	*/	
	
	/*
	1.底层完全能用的工程代码.可以在MCU上跑
	RS9113的io配置正确
	2.开始移植
	RS9113.NBZ.WC.GEN.OSI.1.6.6\host只使用binary 其他删掉 复制到mcu工程下
	3.移植.c源文件
		WLAN_APP 不需要 rsi_wifi_state_mc.c
		WLAN_CORE 所有
		WLAN_HAL 只要SPI
	
	4.设置include路劲
	..\host\binary\apis\hal\include;
	..\host\binary\apis\intf\spi\include;
	..\host\binary\apis\wlan\core\include;
	..\host\binary\apis\wlan\ref_apps\include	
	
	5.编译下 
	需要开启WLAN_ENABLE 宏 	#define WLAN_ENABLE 1	
	SPI接口宏				#define RSI_INTERFACE RSI_SPI      
	6.修改编译的警告和error
	7.基本没用错了.开始移植底层 0 error 
	wifi_main.c
	是原厂提供的一个各种模式的实现.全面 但是相对比较繁琐庞大
	看起来很费劲
	直接使用我们移植好的就可以了.原厂的也可以使用 

	8.ENABLE 这个变量 和STM32库冲突 ,需要修改 RSI_CONNFIG.h 修改这里 然后注释掉

	//#define ENABLE                      1
	//#define DISABLE                     0

	第二部分修改硬件底层
	1.首先移植SPI
	spi	需要修改 发送和接受  和片选
	 直接用已经写好的 发送和接受 
		只需要修改
		rsi_spi_recv 
		rsi_spi_send
		其他不用修改
	2.然后是复位 Io
	3.然后是中断 ,
	中断就在中断服务函数里置位
	rsi_app_cb.pkt_pending = 1;//RSI_TRUE;
	好了移植完成 ,底层移植完成 就剩下测试
	
	
	第三部分 
	使我们自己封装的函数 根据习惯使用
	
	不使用官方的实现 删掉,太复杂
	移植写好的代码
	声明下这个函数
	
	1.开始测试
		WIFI_BOOT
	2.连接硬件
	3.rsi_sys_init能正常执行
	 能正常接收card ready(0x89)
	 说明移植成功 ,
	 接下来是应用了


	4. WIFI_Conf()是一个ap模式的代码 需要修改rsi_config.h的配置	
	
	*/
	
}
u8 Status=1;

int main(void)
{        
	Initialization();

	while(1)
	{
		wifi_send_package();
		can_send_package();
	}
}


u8 can_send_package()
{ 
	if(CAN_Send_EN&&CAN1_Send_EN){   
		

		if(queue_empty(adc_queue)) delay_ms(2);
		IO_input[0] = DIGITAL_INPUT1;
	    IO_input[1] = DIGITAL_INPUT2;
		CAN1_Send_Msg((u8 *) &adc_queue.YYYY_MM_DD, 8);
		CAN1_Send_Msg((u8 *) &adc_queue.arr[adc_queue.head],8);
		CAN1_Send_Msg(IO_input,2);
		CAN_Send_EN = 0;
		CAN1_Send_EN = 0;
	}
	if(CAN_Send_EN && CAN2_Send_EN){
	
		if(queue_empty(adc_queue)) delay_ms(2);
		IO_input[0] = DIGITAL_INPUT1;
	    IO_input[1] = DIGITAL_INPUT2;
		CAN2_Send_Msg((u8 *) &adc_queue.YYYY_MM_DD, 8);
		CAN2_Send_Msg((u8 *) &adc_queue.arr[adc_queue.head],8);
		CAN2_Send_Msg(IO_input,2);
	    CAN_Send_EN = 0;
		CAN2_Send_EN = 0;
	}
	return 1;
}








