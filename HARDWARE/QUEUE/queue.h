#ifndef   QUEUE_H_
#define   QUEUE_H_
#include <sys.h>

 
#define QUEUE_SIZE 10000
#define ARR_SIZE  10000+ 600

typedef struct{
    u8 arr[ARR_SIZE];
	u32 YYYY_MM_DD;
	u32 HeadTime;
    int head,tail;
}Queue;

void queue_init(volatile Queue * pQueue);
u8 queue_get(volatile Queue * pQueue);
void queue_put(volatile Queue * pQueue, u8 ch);
void queue_addtime_addIO(volatile Queue * pQueue, u8 IO_input1, u8 IO_input2);
void queue_oversize(volatile Queue * pQueue,u32 length);
void queue_clear(volatile Queue * pQueue);
int queue_empty(volatile Queue queue);
int queue_full(volatile Queue queue);
u32 queue_length(volatile Queue queue);

#endif
