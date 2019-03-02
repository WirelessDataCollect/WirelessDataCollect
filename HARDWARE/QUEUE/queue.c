#include "queue.h"
#include <string.h>

volatile u8 test_name[MAX_TEST_NAME_LENGTH] = "Default Name\0";

void queue_init(volatile Queue * pQueue)
{
    memset((void *)pQueue, 0, sizeof(Queue));
}

u8 queue_get(volatile Queue * pQueue)
{
    u8 data = pQueue->arr[pQueue->head];
    pQueue->head = (pQueue->head + 1) % QUEUE_SIZE;
    return data;
}

void queue_put(volatile Queue * pQueue, u8 ch)
{
    pQueue->arr[pQueue->tail] = ch;
	pQueue->tail = (pQueue->tail + 1) % QUEUE_SIZE;
}
void queue_clear(volatile Queue * pQueue)
{
	
	pQueue->head = pQueue->tail;
}
void queue_addtime_addIO(volatile Queue * pQueue, u32 count, u8 nodeId, u8 IO_input1, u8 IO_input2)
{
	pQueue->head = (pQueue->head-PACKAGE_HEAD_FRAME_LENGTH + QUEUE_SIZE)% QUEUE_SIZE;  //往前距离为包的帧头长度，包括测试名称、时间、IO高低电平等
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
	
	
	pQueue->arr[(pQueue->head+12)% QUEUE_SIZE] = nodeId;
	pQueue->arr[(pQueue->head+13)% QUEUE_SIZE] = IO_input1;
	pQueue->arr[(pQueue->head+14)% QUEUE_SIZE] = IO_input2;
	pQueue->arr[(pQueue->head+15)% QUEUE_SIZE] = pQueue->arr[(pQueue->head+4)% QUEUE_SIZE];//校验位
	
	queue_add_name(pQueue,test_name);//添加本次实验的名称，长度为MAX_TEST_NAME_LENGTH

}
/**
* 函数作用：给某一个包添加本次实验的名称
* 输入参数：pQueue：队列；testname：测试名称：长度为 MAX_TEST_NAME_LENGTH （bytes）
* 备注：只能在本文件内使用
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

void queue_oversize(volatile Queue * pQueue,u32 length)
{
	memcpy((u8 *)&pQueue->arr[QUEUE_SIZE],(u8 *)&pQueue->arr[0],length);
}
int queue_empty(volatile Queue queue)
{
    if(queue.head == queue.tail)
        return 1;
    return 0;
}

u32 queue_length(volatile Queue queue)
{
	return (queue.tail-queue.head+QUEUE_SIZE)%QUEUE_SIZE;
}

int queue_full(volatile Queue queue)
{
    if((queue.tail + 20) % QUEUE_SIZE >= queue.head)
        return 1;
    return 0;
}


