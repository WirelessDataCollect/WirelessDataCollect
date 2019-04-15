/**
  ******************************************************************************
  * @file    can1.h
  * @author  zju.nesc.iotlab    浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    13-March-2019
  * @brief   CAN1 function   CAN1方法
  ******************************************************************************
  */


#ifndef __CAN1_H
#define __CAN1_H	

//-------------include---------------//
#include "sys.h"	    

/** 
  * @brief  中断
  * @{
  */
//CAN1通用定义
#define RCC_PERIPH_CAN1           RCC_APB1Periph_CAN1   
#define CAN1_PORT_AF              GPIO_AF_CAN1

//CAN1的TX
#define RCC_PERIPH_CAN1_PORT_TX   RCC_AHB1Periph_GPIOA 
#define CAN1_PORT_TX              GPIOA
#define CAN1_PIN_SOURCE_TX        GPIO_PinSource12
#define CAN1_PIN_TX               GPIO_Pin_12
//CAN1的RX
#define RCC_PERIPH_CAN1_PORT_RX   RCC_AHB1Periph_GPIOA 
#define CAN1_PORT_RX              GPIOA
#define CAN1_PIN_SOURCE_RX        GPIO_PinSource11
#define CAN1_PIN_RX               GPIO_Pin_11
/**
  * @}
  */
  
/** 
  * @brief  CAN1数据发送情况
  * @{
  */
typedef enum{
	CAN1_SEND_ERROR = 0,
	CAN1_SEND_OK
}CAN1_Send_Sta;
/**
  * @}
  */

//!CAN1接收RX0中断使能
#define CAN1_RX0_INT_ENABLE	      1		//0,不使能;1,使能.

//! CAN2发使能
extern u8 CAN1_Send_EN;	
										 							 				    
void CAN1_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode,u32 * filter_list,u8 list_len);
u8 CAN1_Send_Msg(u8* msg,u8 len);						//发送数据
u8 CAN1_Receive_Msg(u8 *buf);							//接收数据
#endif

















