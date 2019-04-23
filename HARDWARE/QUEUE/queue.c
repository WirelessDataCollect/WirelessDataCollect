/**
  ******************************************************************************
  * @file    queue.c
  * @author  zju.nesc.iotlab 浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    13-March-2019
  * @brief   adc data queue configuration functions   ADC数据队列方法
  ******************************************************************************
  */

//-------------include---------------//
#include "queue.h"
#include "usart.h"
#include <string.h>

//! 本次实验名称
volatile u8 test_name[MAX_TEST_NAME_LENGTH] = DEFAULT_TEST_NAME;  
/**
  * @brief  队列清零
  * @param  pQueue：队列
  * @retval None
  */
void queue_init(volatile Queue * pQueue)
{
    memset((void *)pQueue, 0, sizeof(Queue));
}

/**
  * @brief  获取队列头部数据
  * @param  pQueue：队列
  * @retval 队头字节数据
  */
u8 queue_get(volatile Queue * pQueue)
{
    u8 data = pQueue->arr[pQueue->head];
    pQueue->head = (pQueue->head + 1) % QUEUE_SIZE;
    return data;
}

/**
  * @brief  u8数据加入队列
  * @param  pQueue：队列
  * @param  ch：要加入的u8数据
  * @retval None
  */
 void queue_put(volatile Queue * pQueue, u8 ch)
{
    pQueue->arr[pQueue->tail] = ch;
	pQueue->tail = (pQueue->tail + 1) % QUEUE_SIZE;
}

/**
  * @brief  u8数据拷贝至queue.arr尾部
  * @param  pQueue：队列
  * @param  buf：要加入的u8数组
  * @param  len：u8数组长度
  * @retval None
  */
void queue_arr_memcpy(Queue * pQueue, u8 * buf , u8 len){
	if((len + pQueue->tail) <= QUEUE_SIZE){
		memcpy((u8 *)&(pQueue->arr[pQueue->tail]),buf,len);
		
	}else{
		memcpy((u8 *)&(pQueue->arr[pQueue->tail]),buf,QUEUE_SIZE - pQueue->tail);
		memcpy((u8 *)&(pQueue->arr[0]),buf+QUEUE_SIZE - pQueue->tail,len - QUEUE_SIZE + pQueue->tail);
	}
	pQueue->tail = (pQueue->tail + len)  % QUEUE_SIZE;
	
}

/**
  * @brief  队列清空，tail=head
  * @param  pQueue：队列
  * @retval None
  */
void queue_clear(volatile Queue * pQueue)
{
	pQueue->head = pQueue->tail;
}

/**
  * @brief  队列添加帧头，包括年月日、计时器、ADC字节数据、节点数据长度、开关信号、测试名称
  * @param  pQueue：队列
  * @param  count：ADC字节格式
  * @param  id：节点ID号
  * @param  IO_input1：开关信号1
  * @param  IO_input2：开关信号2
  * @param  dataType：
           @arg CAN_DATA_PACKAGE
		       @arg ADC_DATA_PACKAGE
  * @retval None
  */
void queue_addtime_addIO(volatile Queue * pQueue, u32 count, u8 id, u8 IO_input1, u8 IO_input2,u8 dataType)
{
	pQueue->head = (pQueue->head  + QUEUE_SIZE -PACKAGE_HEAD_FRAME_LENGTH)% QUEUE_SIZE;  //往前距离为包的帧头长度，包括测试名称、时间、IO高低电平等
//	printf("Head: %d \r\nTail: %d \r\n\r\n",pQueue->head,pQueue->tail);
	pQueue->arr[(pQueue->head+0)% QUEUE_SIZE] = (u8)(pQueue->YYYY_MM_DD);
	pQueue->arr[(pQueue->head+1)% QUEUE_SIZE] = (u8)(pQueue->YYYY_MM_DD>>8);
	pQueue->arr[(pQueue->head+2)% QUEUE_SIZE] = (u8)(pQueue->YYYY_MM_DD>>16);
	pQueue->arr[(pQueue->head+3)% QUEUE_SIZE] = (u8)(pQueue->YYYY_MM_DD>>24);
	
	pQueue->arr[(pQueue->head+4)% QUEUE_SIZE] = (u8)(pQueue->HeadTime);
	pQueue->arr[(pQueue->head+5)% QUEUE_SIZE] = (u8)(pQueue->HeadTime>>8);
	pQueue->arr[(pQueue->head+6)% QUEUE_SIZE] = (u8)(pQueue->HeadTime>>16);
	pQueue->arr[(pQueue->head+7)% QUEUE_SIZE] = (u8)(pQueue->HeadTime>>24);
	
	pQueue->arr[(pQueue->head+8)% QUEUE_SIZE] = (u8)count;
	pQueue->arr[(pQueue->head+9)% QUEUE_SIZE] = (u8)(count>>8);
	pQueue->arr[(pQueue->head+10)% QUEUE_SIZE] = (u8)(count>>16);
	pQueue->arr[(pQueue->head+11)% QUEUE_SIZE] = (u8)(count>>24);
	
	
	pQueue->arr[(pQueue->head+12)% QUEUE_SIZE] = id;
	pQueue->arr[(pQueue->head+13)% QUEUE_SIZE] = IO_input1 | (IO_input2 << 1);
	pQueue->arr[(pQueue->head+14)% QUEUE_SIZE] = dataType;
	pQueue->arr[(pQueue->head+15)% QUEUE_SIZE] = pQueue->arr[(pQueue->head + 4)% QUEUE_SIZE];//校验位
	
	queue_add_name(pQueue,test_name);//添加本次实验的名称，长度为MAX_TEST_NAME_LENGTH

}

/**
  * @brief  给某一个包添加本次实验的名称
  * @param  pQueue：队列
  * @param  testname：测试名称
  * @note   只能在本文件中使用
  * @retval None
  */
static void queue_add_name(volatile Queue * pQueue, volatile u8 testname[MAX_TEST_NAME_LENGTH])
{
	for(int i = MAX_TEST_NAME_LENGTH;i>0;i--)
	{
		//从时间、IO等帧头后面开始加入测试名称
		//如时间、IO的长度为16，则从第16个开始给队列赋值testname
		pQueue->arr[(pQueue->head+PACKAGE_TIME_IO_LENGTH+i-1)% QUEUE_SIZE] = testname[i-1];
	}
}

/**
  * @brief  给队列直接写入数据，队头数据搬移到队尾
  * @param  pQueue：队列
  * @param  length：数据长度
  * @retval None
  */
void queue_oversize(volatile Queue * pQueue,u32 length)
{
	memcpy((u8 *)&pQueue->arr[QUEUE_SIZE],(u8 *)&pQueue->arr[0],length);
	
}

/**
  * @brief  查看是否是空队列
  * @param  queue：队列
  * @retval 是否空队列（1：空队列；0：非空队列）
  */
u8 queue_empty(volatile Queue queue)
{
    if(queue.head == queue.tail)
        return 1;
    return 0;
}

/**
  * @brief  查看队列长度
  * @param  queue：队列
  * @retval 队列长度
  */
u32 queue_length(volatile Queue queue)
{
	return (queue.tail-queue.head+QUEUE_SIZE)%QUEUE_SIZE;
}

/**
  * @brief  查看队列是否满
  * @param  queue：队列
  * @retval 是否满队列（1：满队列；0：非满队列）
  */
u8 queue_full(volatile Queue queue)
{
    if((queue.tail + 20) % QUEUE_SIZE >= queue.head)
        return 1;
    return 0;
}


