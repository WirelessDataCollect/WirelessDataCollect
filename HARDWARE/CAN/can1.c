/**
  ******************************************************************************
  * @file    can1.c
  * @author  zju.nesc.iotlab    浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    13-March-2019
  * @brief   CAN1 function   CAN1方法
  ******************************************************************************
  */

//-------------include---------------//
#include "can1.h"
#include "gpio.h"
#include "userwifi.h"

//!CAN1发送使能
u8 CAN1_Send_EN = 1;
/**
  * @brief  CAN1初始化
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
  * @param  filter_list：存储过滤器ID的数组，8个字节为一组
  * @param  list_len：过滤器个数，1~14
  * @note   BaudRate = Tpclk / (tq * ( (tbs1+1) + (tbs2 +2) + 1))
  * @note   Tpclk一般为42MHz
  * @exam   CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS1_6tq,CAN_BS2_7tq,6,CAN_Mode_Normal);//can1初始化500k波特率
  * @retval None
  */
void CAN1_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode,u8 * filter_list,u8 list_len){
	GPIO_InitTypeDef GPIO_InitStructure; 
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	#if CAN1_RX0_INT_ENABLE 
		NVIC_InitTypeDef  NVIC_InitStructure;
	#endif
	/* 使能相关时钟*/
	RCC_AHB1PeriphClockCmd(RCC_PERIPH_CAN1_PORT_TX|RCC_PERIPH_CAN1_PORT_RX, ENABLE);                  											 
	RCC_APB1PeriphClockCmd(RCC_PERIPH_CAN1, ENABLE);	

	/* 初始化GPIO*/
	GPIO_InitStructure.GPIO_Pin = CAN1_PIN_TX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;       //复用功能
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       //上拉
	GPIO_Init(CAN1_PORT_TX, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = CAN1_PIN_RX;
	GPIO_Init(CAN1_PORT_RX, &GPIO_InitStructure);

	/* 引脚复用映射配置*/
	GPIO_PinAFConfig(CAN1_PORT_TX,CAN1_PIN_SOURCE_TX,CAN1_PORT_AF);
	GPIO_PinAFConfig(CAN1_PORT_RX,CAN1_PIN_SOURCE_RX,CAN1_PORT_AF);

	/* CAN单元设置*/
	CAN_InitStructure.CAN_TTCM      = DISABLE;	  //非时间触发通信模式   
	CAN_InitStructure.CAN_ABOM      = DISABLE;	  //软件自动离线管理	  
	CAN_InitStructure.CAN_AWUM      = DISABLE;    //睡眠模式通过软件唤醒(清除CAN->MCR的SLEEP位)
	CAN_InitStructure.CAN_NART      = ENABLE;	  //使能报文自动重发 
	CAN_InitStructure.CAN_RFLM      = DISABLE;	  //报文不锁定,新的覆盖旧的  
	CAN_InitStructure.CAN_TXFP      = DISABLE;	  //优先级由报文标识符决定 
	CAN_InitStructure.CAN_Mode      = mode;	      //模式设置 
	CAN_InitStructure.CAN_SJW       = tsjw;	      //重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位 CAN_SJW_1tq~CAN_SJW_4tq
	CAN_InitStructure.CAN_BS1       = tbs1;       //Tbs1范围CAN_BS1_1tq ~CAN_BS1_16tq
	CAN_InitStructure.CAN_BS2       = tbs2;       //Tbs2范围CAN_BS2_1tq ~	CAN_BS2_8tq
	CAN_InitStructure.CAN_Prescaler = brp;        //分频系数(Fdiv)为brp+1
	CAN_Init(CAN1, &CAN_InitStructure);           // 初始化CAN1 

	/* 配置过滤器*/
	for(u8 filter_num = 0;filter_num < list_len;filter_num++){
		CAN_FilterInitStructure.CAN_FilterNumber         = filter_num;	          //过滤器
//		CAN_FilterInitStructure.CAN_FilterMode           = CAN_FilterMode_IdMask;
		CAN_FilterInitStructure.CAN_FilterMode           = CAN_FilterMode_IdList; //List模式	
		CAN_FilterInitStructure.CAN_FilterScale          = CAN_FilterScale_32bit; //32位滤波
		CAN_FilterInitStructure.CAN_FilterIdHigh         = *(filter_list + 0 + filter_num * 8) + 256 * (*(filter_list + 1 + filter_num * 8));
		CAN_FilterInitStructure.CAN_FilterIdLow          = *(filter_list + 2 + filter_num * 8) + 256 * (*(filter_list + 3 + filter_num * 8));
		CAN_FilterInitStructure.CAN_FilterMaskIdHigh     = *(filter_list + 4 + filter_num * 8) + 256 * (*(filter_list + 5 + filter_num * 8));
		CAN_FilterInitStructure.CAN_FilterMaskIdLow      = *(filter_list + 6 + filter_num * 8) + 256 * (*(filter_list + 7 + filter_num * 8));;
		CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;      //过滤器0关联到FIFO0
		CAN_FilterInitStructure.CAN_FilterActivation     = ENABLE;                //激活过滤器
		CAN_FilterInit(&CAN_FilterInitStructure);                                 //滤波器初始化	
	}


	/* 接收中断*/
	#if CAN1_RX0_INT_ENABLE
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);	    
	NVIC_InitStructure.NVIC_IRQChannel                   = CAN1_RX0_IRQn;
	/* !! 中断优先级CAN1和CAN2必须相同*/
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	#endif
}   

//!使能RX0中断
#if CAN1_RX0_INT_ENABLE	
/**
  * @brief  CAN1中断服务函数
  * @param  None
  * @retval None
  */
void CAN1_RX0_IRQHandler(void){
  	CanRxMsg RxMessage;

	if (CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET)
	{
		/* 如果队列空了，时间戳更新*/
		if(queue_empty(can_queue)){
			can_queue.HeadTime = SYSTEMTIME;
			can_queue.YYYY_MM_DD = YYMMDD;
		}
		/* 接收CAN数据*/
		CAN_Receive(CAN1, CAN_FIFO0 ,&RxMessage);
		/* 加入CAN的ID*/
		queue_put(&can_queue,CAN1_ID);
		/* 拷贝至queue.arr尾部，并更新tail*/
		queue_arr_memcpy(&can_queue, (u8 *)&RxMessage , sizeof(RxMessage));		
		
	#if PRINT_UART_LOG
		printf("CAN1 Data : ");
		for(int i = 0; i < RxMessage.DLC;i++){
			printf("%d ",RxMessage.Data[i]);
		}
		printf("\r\n");
	#endif
	 }
	 CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
	 CAN_FIFORelease(CAN1,CAN_FIFO0);
}
#endif

/**
  * @brief  can1发送一组数据
  * @param  msg：数据指针,最大为8个字节
  * @param  len：数据长度(最大为8)	
  * @retval 发送成功与否
           @arg CAN1_SEND_ERROR 失败
           @arg CAN1_SEND_OK  成功
  */
u8 CAN1_Send_Msg(u8* msg,u8 len){	
	u8 mbox;
	u16 i=0;
	CanTxMsg TxMessage;
	//! 标准标识符为0,该帧的优先级
	TxMessage.StdId   = 0x32;	
	//! 设置扩展标示符（29位），该帧的优先级
	TxMessage.ExtId   = 0x32;
	//! 使用扩展标识符	
	TxMessage.IDE     = 0;		
	//! 消息类型为数据帧，一帧8位	
	TxMessage.RTR     = 0;
	//! 发送信息长度	
	TxMessage.DLC     = len;	
	//! 保存信息
	for(i=0;i<len;i++){
		TxMessage.Data[i] = msg[i];  
	}		
	//! 发送信息
	mbox = CAN_Transmit(CAN1, &TxMessage);   
	i = 0;
	while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF)){
		i++;
		mbox= CAN_Transmit(CAN1, &TxMessage); 
	}
	if(i>=0XFFF){
		return CAN1_SEND_ERROR;
	}
	return CAN1_SEND_OK;		

}

/**
  * @brief  can1口接收数据查询
  * @param  buf：保存数据的buffer指针
  * @retval 数据字节长度
  */
u8 CAN1_Receive_Msg(u8 *buf){
 	u32 i;
	CanRxMsg RxMessage;
	//! 没有接收到数据,直接退出 
    if( CAN_MessagePending(CAN1,CAN_FIFO0)==0){
		return 0;		
	}
	//! 读取数据	
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
    for(i=0;i<RxMessage.DLC;i++){
		buf[i]=RxMessage.Data[i]; 
	}
	return RxMessage.DLC;	
}













