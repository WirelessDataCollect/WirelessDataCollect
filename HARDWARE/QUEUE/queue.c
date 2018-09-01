#include "queue.h"
#include <string.h>
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
void queue_addtime_addIO(volatile Queue * pQueue, u32 count, u8 wifi_client_id, u8 IO_input1, u8 IO_input2)
{
	pQueue->head = (pQueue->head-16 + QUEUE_SIZE)% QUEUE_SIZE;
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
	
	
	pQueue->arr[(pQueue->head+12)% QUEUE_SIZE] = wifi_client_id;
	pQueue->arr[(pQueue->head+13)% QUEUE_SIZE] = IO_input1;
	pQueue->arr[(pQueue->head+14)% QUEUE_SIZE] = IO_input2;
	pQueue->arr[(pQueue->head+15)% QUEUE_SIZE] = pQueue->arr[(pQueue->head+4)% QUEUE_SIZE];//Ð£ÑéÎ»

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


