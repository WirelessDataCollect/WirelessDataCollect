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
void queue_addtime(volatile Queue * pQueue)
{
	pQueue->head = (pQueue->tail-8+QUEUE_SIZE)% QUEUE_SIZE;
	pQueue->arr[(pQueue->tail+0)% QUEUE_SIZE] = (u8)(pQueue->YYYY_MM_DD);
	pQueue->arr[(pQueue->tail+1)% QUEUE_SIZE] = (u8)(pQueue->YYYY_MM_DD>>8);
	pQueue->arr[(pQueue->tail+2)% QUEUE_SIZE] = (u8)(pQueue->YYYY_MM_DD>>16);
	pQueue->arr[(pQueue->tail+3)% QUEUE_SIZE] = (u8)(pQueue->YYYY_MM_DD>>24);
	pQueue->arr[(pQueue->tail+4)% QUEUE_SIZE] = (u8)(pQueue->HeadTime);
	pQueue->arr[(pQueue->tail+5)% QUEUE_SIZE] = (u8)(pQueue->HeadTime>>8);
	pQueue->arr[(pQueue->tail+6)% QUEUE_SIZE] = (u8)(pQueue->HeadTime>>16);
	pQueue->arr[(pQueue->tail+7)% QUEUE_SIZE] = (u8)(pQueue->HeadTime>>24);
	
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
    if((queue.tail + 16) % QUEUE_SIZE >= queue.head)
        return 1;
    return 0;
}
