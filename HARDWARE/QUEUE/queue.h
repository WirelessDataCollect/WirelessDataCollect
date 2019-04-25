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
  * @brief  队列属性
  * @note   队列存储ADC和CAN数据，数据长度以ADC长度设置
  * @{
  */ 
#define  ADC_SEND_SIZE          (8*50 + PACKAGE_HEAD_FRAME_LENGTH)     /*!< ADC数据包最大大小   480 = 8 * 50 + PACKAGE_HEAD_FRAME_LENGTH  UDP包尽量不要超过576－20－8＝548个>*/
#define  CAN_SEND_SIZE          (25 * 16 + PACKAGE_HEAD_FRAME_LENGTH)  /*!< CAN数据包最大大小   480 = 25* 16 + PACKAGE_HEAD_FRAME_LENGTH  UDP包尽量不要超过576－20－8＝548个>*/
#define  QUEUE_SIZE             800                                    /*!< 队列正常容量，必须比ADC_SEND_SIZE大一些，不然会在被后面的信息覆盖>*/
#define  ARR_SIZE               (QUEUE_SIZE + ADC_SEND_SIZE+52)        /*!< 队列最大容量>*/
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
}Queue;
/**
  * @}
  */

/** 
  * @brief  CANx_ID，用于区分不同的CAN编号
  * @{
  */
typedef enum{
	CAN1_ID = 0x01,
	CAN2_ID
}CANx;
/**
  * @}
  */

/** 
  * @brief  wifi数据包存储数据类型，ADC或者CAN
  * @{
  */
typedef enum{
	CAN_DATA_PACKAGE = 0x01,
	ADC_DATA_PACKAGE
}WiFi_DATA_Type;
/**
  * @}
  */

//! 本次实验名称
extern volatile u8 test_name[MAX_TEST_NAME_LENGTH]; 


void queue_init(volatile Queue * pQueue);
u8 queue_get(volatile Queue * pQueue);
void queue_put(volatile Queue * pQueue, u8 ch);
void queue_arr_memcpy(Queue * pQueue, u8 * buf , u8 len);
void queue_addtime_addIO(volatile Queue * pQueue, u32 count, u8 id, u8 IO_input1, u8 IO_input2,u8 dataType);
void queue_oversize(volatile Queue * pQueue,u32 length);
void queue_clear(volatile Queue * pQueue);
u8 queue_empty(volatile Queue * queue);
u8 queue_full(volatile Queue * queue);
u32 queue_length(volatile Queue * queue);
static void queue_add_name(volatile Queue * pQueue,volatile u8 testname[MAX_TEST_NAME_LENGTH]);

#endif
