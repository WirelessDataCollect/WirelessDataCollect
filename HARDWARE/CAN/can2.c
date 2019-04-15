/**
  ******************************************************************************
  * @file    can2.c
  * @author  zju.nesc.iotlab    浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    13-March-2019
  * @brief   CAN2 function   CAN2方法
  ******************************************************************************
  */

//-------------include---------------//
#include "can1.h"
#include "can2.h"
#include "gpio.h"
#include "delay.h"
#include "string.h"
#include "userwifi.h" 


CanRxMsg RxMessage;//定义全局变量存储CAN收到的数据，并在main.c中使用
u8 CAN2_Send_EN = 0;


/**
  * @brief  CAN2初始化
  * @param  tsjw：重新同步跳跃时间单元
			@arg CAN_SJW_1tq ~ CAN_SJW_4tq
  * @param  tbs2：时间段2的时间单元
			@arg CAN_BS2_1tq ~ CAN_BS2_8tq;
  * @param  tbs1：时间段1的时间单元
			@arg CAN_BS1_1tq ~ CAN_BS1_16tq
  * @param  brp：波特率分频器.范围:1~1024; tq=(brp)*tpclk1
  * @param  mode：CAN_Mode_Normal,普通模式;CAN_Mode_LoopBack,回环模式;
			@arg CAN_Mode_Normal：普通模式
			@arg CAN_Mode_LoopBack：回环模式
  * @param  filter_list：存储过滤器拓展ID的数组
  * @param  list_len：滤波ID个数
  * @note   BaudRate = Tpclk / (tq * ( (tbs1+1) + (tbs2 +2) + 1))
  * @note   Tpclk一般为42MHz
  * @exam   CAN2_Mode_Init(CAN_SJW_1tq,CAN_BS1_6tq,CAN_BS2_7tq,6,CAN_Mode_Normal);//can2初始化500k波特率
  * @retval None
  */
void CAN2_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode,u32 * filter_list,u8 list_len){
	#if PRINT_UART_LOG
	printf("\r\nCAN2 Initing...\r\n");
	#endif
	GPIO_InitTypeDef GPIO_InitStructure; 
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	#if CAN2_RX1_INT_ENABLE 
		NVIC_InitTypeDef  NVIC_InitStructure;
	#endif
	/* 使能相关时钟*/
	RCC_AHB1PeriphClockCmd(RCC_PERIPH_CAN2_PORT_TX|RCC_PERIPH_CAN2_PORT_RX, ENABLE);	
	RCC_APB1PeriphClockCmd(RCC_PERIPH_CAN1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_PERIPH_CAN2, ENABLE);

	/* 初始化GPIO*/
	GPIO_InitStructure.GPIO_Pin    =  CAN2_PIN_TX;
	GPIO_InitStructure.GPIO_Mode   =  GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType  =  GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed  =  GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd   =  GPIO_PuPd_UP;
	GPIO_Init(CAN2_PORT_TX, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin    =  CAN2_PIN_RX;
	GPIO_Init(CAN2_PORT_RX, &GPIO_InitStructure);

	/* 复用*/
	GPIO_PinAFConfig(CAN2_PORT_TX,CAN2_PIN_SOURCE_TX,GPIO_AF_CAN2);
	GPIO_PinAFConfig(CAN2_PORT_RX,CAN2_PIN_SOURCE_RX,GPIO_AF_CAN2);

	//CAN单元设置
	CAN_InitStructure.CAN_TTCM      = DISABLE;	   //非时间触发通信模式   
	CAN_InitStructure.CAN_ABOM      = DISABLE;	   //软件自动离线管理	  
	CAN_InitStructure.CAN_AWUM      = DISABLE;     //睡眠模式通过软件唤醒(清除CAN->MCR的SLEEP位)
	CAN_InitStructure.CAN_NART      = ENABLE;	   //禁止报文自动传送 
	CAN_InitStructure.CAN_RFLM      = DISABLE;	   //报文不锁定,新的覆盖旧的  
	CAN_InitStructure.CAN_TXFP      = DISABLE;	   //优先级由报文标识符决定 
	CAN_InitStructure.CAN_Mode      = mode;	       //模式设置 
	CAN_InitStructure.CAN_SJW       = tsjw;	       //重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位 CAN_SJW_1tq~CAN_SJW_4tq
	CAN_InitStructure.CAN_BS1       = tbs1;        //Tbs1范围CAN_BS1_1tq ~CAN_BS1_16tq
	CAN_InitStructure.CAN_BS2       = tbs2;        //Tbs2范围CAN_BS2_1tq ~	CAN_BS2_8tq
	CAN_InitStructure.CAN_Prescaler = brp;         //分频系数(Fdiv)为brp+1	
	CAN_Init(CAN2, &CAN_InitStructure);            // 初始化CAN2 
	
	#if PRINT_UART_LOG
	printf("CAN2 Filter List:\r\n");
	printf("--------------------------------\r\n");
	#endif	
	/* 配置过滤器*/
//	/* Example. 过滤出标准帧ID：0x7e9和拓展帧ID：0x1800f001*/
//	CAN_FilterInitStructure.CAN_FilterNumber         = 14;	          //过滤器
//	CAN_FilterInitStructure.CAN_FilterMode           = CAN_FilterMode_IdList;
//	CAN_FilterInitStructure.CAN_FilterScale          = CAN_FilterScale_32bit; //32位滤波
////	u16 std_id = 0x7e9;
////	CAN_FilterInitStructure.CAN_FilterIdHigh         = (u16)(std_id<<5);
////	CAN_FilterInitStructure.CAN_FilterIdLow          = 0|CAN_ID_STD;
//	u32 ext_id1 = 0x1800f001;
//	CAN_FilterInitStructure.CAN_FilterIdHigh         = (u16)((ext_id1<<3)>>16) & 0xffff;
//	CAN_FilterInitStructure.CAN_FilterIdLow          = (u16)((ext_id1<<3) & 0xffff) | CAN_ID_EXT;
//	u32 ext_id2 = 0x1800f002;
//	CAN_FilterInitStructure.CAN_FilterMaskIdHigh     = (u16)(((ext_id2<<3)>>16) & 0xffff);
//	CAN_FilterInitStructure.CAN_FilterMaskIdLow      = (u16)(((ext_id2<<3) & 0xffff) | CAN_ID_EXT);
//	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO1;      //过滤器0关联到FIFO1
//	CAN_FilterInitStructure.CAN_FilterActivation     = ENABLE;                //激活过滤器
//	CAN_FilterInit(&CAN_FilterInitStructure);                                 //滤波器初始化	
	u32 ext_id1,ext_id2;
	for(u8 filter_num = 0;filter_num < list_len;filter_num+=2){
		CAN_FilterInitStructure.CAN_FilterNumber         = filter_num/2 + 14;	      //过滤器，can2支持从14开始
		CAN_FilterInitStructure.CAN_FilterMode           = CAN_FilterMode_IdList; //List模式	
		CAN_FilterInitStructure.CAN_FilterScale          = CAN_FilterScale_32bit; //32位滤波
		ext_id1 = filter_list[filter_num];
		/* 根据list长度奇数或者偶数来决定第二个滤波器寄存器的数值*/
		if(list_len - filter_num == 1){ //发现只剩下一个ID没有过滤，则将第二个寄存器也配置成该ID
			ext_id2 = filter_list[filter_num];
		}else{                          //还有大于等于2个ID没有过滤
			ext_id2 = filter_list[filter_num+1];
		}
		printf("  0x%X , 0x%X \r\n",ext_id1,ext_id2);
		CAN_FilterInitStructure.CAN_FilterIdHigh         = (u16)((ext_id1<<3)>>16) & 0xffff;
		CAN_FilterInitStructure.CAN_FilterIdLow          = (u16)((ext_id1<<3) & 0xffff) | CAN_ID_EXT;
		CAN_FilterInitStructure.CAN_FilterMaskIdHigh     = (u16)((ext_id2<<3)>>16) & 0xffff;
		CAN_FilterInitStructure.CAN_FilterMaskIdLow      = (u16)((ext_id2<<3) & 0xffff) | CAN_ID_EXT;		
		CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO1;      //过滤器0关联到FIFO0
		CAN_FilterInitStructure.CAN_FilterActivation     = ENABLE;                //激活过滤器
		CAN_FilterInit(&CAN_FilterInitStructure);                                 //滤波器初始化	
	}
	#if PRINT_UART_LOG
	printf("--------------------------------\r\n");
	#endif
	
	#if CAN2_RX1_INT_ENABLE
	CAN_ITConfig(CAN2,CAN_IT_FMP1,ENABLE);		    
	NVIC_InitStructure.NVIC_IRQChannel                   = CAN2_RX1_IRQn;
	/* !! 中断优先级CAN1和CAN2必须相同*/
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	#endif
	#if PRINT_UART_LOG
	printf("CAN2 Inited Successfully...!\r\n\r\n");
	#endif	
}   
 
//!使能RX0中断
#if CAN2_RX1_INT_ENABLE
/**
  * @brief  CAN2中断服务函数
  * @param  None
  * @retval None
  */
void CAN2_RX1_IRQHandler(void)
{
  	CanRxMsg RxMessage;

	if (CAN_GetITStatus(CAN2,CAN_IT_FMP1)!= RESET){
		/* 如果队列空了，时间戳更新*/
		if(queue_empty(can_queue)){
			can_queue.HeadTime = SYSTEMTIME;
			can_queue.YYYY_MM_DD = YYMMDD;
		}
		/* 接收CAN数据*/
		CAN_Receive(CAN2, CAN_FIFO1 ,&RxMessage);
		/* 加入CAN的ID*/
		queue_put(&can_queue,CAN2_ID);
		/* 加入CAN的接收时间偏移*/
		u32 deltaTime = SYSTEMTIME - can_queue.HeadTime;
		queue_arr_memcpy(&can_queue, (u8 *)&deltaTime , sizeof(deltaTime));
		/* CAN2数据拷贝至queue.arr尾部，并更新tail*/
		queue_arr_memcpy(&can_queue, (u8 *)&RxMessage , sizeof(RxMessage));
	#if PRINT_UART_LOG
		printf("CAN2 Data : ");
		for(int i = 0; i < RxMessage.DLC;i++){
			printf("%d ",RxMessage.Data[i]);
		}
		printf("\r\n");
	#endif
	 }
	 CAN_ClearITPendingBit(CAN2, CAN_IT_FMP1);
	 CAN_FIFORelease(CAN2,CAN_FIFO1); //清中断标志
}

#endif

/**
  * @brief  can2发送一组数据
  * @param  msg：数据指针,最大为8个字节
  * @param  len：数据长度(最大为8)	
  * @retval 发送成功与否
           @arg CAN2_SEND_ERROR 失败
           @arg CAN2_SEND_OK  成功
  */
u8 CAN2_Send_Msg(u8* msg,u8 len){	
	u8 mbox;
	u16 i=0;
	CanTxMsg TxMessage;
	//! 标准标识符为0,该帧的优先级
	TxMessage.StdId = 0x32;
	//! 设置扩展标示符（29位）
	TxMessage.ExtId = 0x32;
	//! 使用扩展标识符
	TxMessage.IDE   = CAN_Id_Extended;
	//! 消息类型为数据帧，一帧8位
	TxMessage.RTR   = 0;
	//! 发送信息长度
	TxMessage.DLC   = len;
	for(i=0;i<len;i++)
	TxMessage.Data[i]=msg[i];				 // 第一帧信息
	mbox = CAN_Transmit(CAN2, &TxMessage);   
	i=0;
	while((CAN_TransmitStatus(CAN2, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF)){
		i++;
		mbox= CAN_Transmit(CAN2, &TxMessage); 
	}
	if(i>=0XFFF){
	  return CAN2_SEND_ERROR;
	}
	return CAN2_SEND_OK;		

}

/**
  * @brief  can1口接收数据查询
  * @param  buf：保存数据的buffer指针
  * @retval 数据字节长度
  */
u8 CAN2_Receive_Msg(u8 *buf){
 	u32 i;
	CanRxMsg RxMessage;
	//! 没有接收到数据,直接退出 
    if( CAN_MessagePending(CAN2,CAN_FIFO1)==0){
		return 0;		
	}
	//! 读取数据	
    CAN_Receive(CAN2, CAN_FIFO1, &RxMessage);
    for(i=0;i<RxMessage.DLC;i++){
		buf[i]=RxMessage.Data[i]; 
	}
	return RxMessage.DLC;	
}
