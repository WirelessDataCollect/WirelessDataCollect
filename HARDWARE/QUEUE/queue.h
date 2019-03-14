/**
  ******************************************************************************
  * @file    queue.h
  * @author  zju.nesc.iotlab 浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    13-March-2019
  * @brief   adc data queue configuration functions   ADC数据队列方法
  ******************************************************************************
  */
#ifndef   QUEUE_H_
#define   QUEUE_H_

//-------------include---------------//
#include <sys.h>

/** 
  * @brief  队列属性
  * @{
  */ 
#define  UDP_SEND_SIZE          (8*60 + PACKAGE_HEAD_FRAME_LENGTH)    /*!< UDP数据包最大大小   616 = 8 * 67 + PACKAGE_HEAD_FRAME_LENGTH>*/
#define  QUEUE_SIZE             700                                 /*!< 队列正常容量>*/
#define  ARR_SIZE               (QUEUE_SIZE + UDP_SEND_SIZE+50)      /*!< 队列最大容量>*/
/**
  * @}
  */
  
/** 
  * @brief  测试名称属性
  * @{
  */   
#define MAX_TEST_NAME_LENGTH         64       /*!< 测试名称最长长度>*/
#define PACKAGE_TIME_IO_LENGTH       16       /*!< 时间、IO、ADC数量等长度>*/
#define PACKAGE_HEAD_FRAME_LENGTH    (MAX_TEST_NAME_LENGTH+PACKAGE_TIME_IO_LENGTH)   /*!< 帧头总长度>*/
#define DEFAULT_TEST_NAME            "DefaultName/2019-03-09\0"       /*!< 默认测试名称>*/
/**
  * @}
  */

/** 
  * @brief  队列
  * @{
  */
typedef struct{
    u8 arr[ARR_SIZE];
	u32 YYYY_MM_DD;
	u32 HeadTime;
	volatile u16 head,tail;
	u8 test_name[MAX_TEST_NAME_LENGTH];   
}Queue;
/**
  * @}
  */




void queue_init(volatile Queue * pQueue);
u8 queue_get(volatile Queue * pQueue);
void queue_put(volatile Queue * pQueue, u8 ch);
void queue_addtime_addIO(volatile Queue * pQueue, u32 count, u8 nodeId, u8 IO_input1, u8 IO_input2);
void queue_oversize(volatile Queue * pQueue,u32 length);
void queue_clear(volatile Queue * pQueue);
u8 queue_empty(volatile Queue queue);
u8 queue_full(volatile Queue queue);
u32 queue_length(volatile Queue queue);
static void queue_add_name(volatile Queue * pQueue,volatile u8 testname[MAX_TEST_NAME_LENGTH]);

#endif
