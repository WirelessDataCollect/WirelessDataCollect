#ifndef   QUEUE_H_
#define   QUEUE_H_
#include <sys.h>

 
#define QUEUE_SIZE 2000
#define ARR_SIZE  2000+ 600

//最长的测试名称名长度，ascii码
#define MAX_TEST_NAME_LENGTH 32
#define PACKAGE_TIME_IO_LENGTH 16
#define PACKAGE_HEAD_FRAME_LENGTH (MAX_TEST_NAME_LENGTH+PACKAGE_TIME_IO_LENGTH)

typedef struct{
    u8 arr[ARR_SIZE];
	u32 YYYY_MM_DD;
	u32 HeadTime;
    int head,tail;
}Queue;

void queue_init(volatile Queue * pQueue);
u8 queue_get(volatile Queue * pQueue);
void queue_put(volatile Queue * pQueue, u8 ch);
void queue_addtime_addIO(volatile Queue * pQueue, u32 count, u8 nodeId, u8 IO_input1, u8 IO_input2);
void queue_oversize(volatile Queue * pQueue,u32 length);
void queue_clear(volatile Queue * pQueue);
int queue_empty(volatile Queue queue);
int queue_full(volatile Queue queue);
u32 queue_length(volatile Queue queue);
static void queue_add_name(volatile Queue * pQueue,volatile u8 testname[MAX_TEST_NAME_LENGTH]);

#endif
