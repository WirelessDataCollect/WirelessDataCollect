/**
  ******************************************************************************
  * @file    can2.h
  * @author  zju.nesc.iotlab    浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    13-March-2019
  * @brief   CAN2 function   CAN2方法
  ******************************************************************************
  */

#ifndef __CAN2_H
#define __CAN2_H	

//-------------include---------------//
#include "sys.h"	    

/** 
  * @brief  中断
  * @{
  */
//CAN2通用定义
#define RCC_PERIPH_CAN2           RCC_APB1Periph_CAN2   
#define CAN2_PORT_AF              GPIO_AF_CAN2

//CAN2的TX
#define RCC_PERIPH_CAN2_PORT_TX   RCC_AHB1Periph_GPIOB 
#define CAN2_PORT_TX              GPIOB
#define CAN2_PIN_SOURCE_TX        GPIO_PinSource13
#define CAN2_PIN_TX               GPIO_Pin_13
//CAN2的RX
#define RCC_PERIPH_CAN2_PORT_RX   RCC_AHB1Periph_GPIOB 
#define CAN2_PORT_RX              GPIOB
#define CAN2_PIN_SOURCE_RX        GPIO_PinSource12
#define CAN2_PIN_RX               GPIO_Pin_12
/**
  * @}
  */
  
/** 
  * @brief  CAN2数据发送情况
  * @{
  */
typedef enum{
	CAN2_SEND_ERROR = 0,
	CAN2_SEND_OK
}CAN2_Send_Sta;
/**
  * @}
  */
  
//! CAN2接收RX0中断使能
#define CAN2_RX1_INT_ENABLE       1		//0：不使能；1：使能.
  
//! CAN2发使能
extern u8 CAN2_Send_EN;		


void CAN2_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode,u32 * filter_list,u8 list_len);//CAN初始化
u8 CAN2_Send_Msg(u8* msg,u8 len);						//发送数据
u8 CAN2_Receive_Msg(u8 *buf);							//接收数据


#endif

















