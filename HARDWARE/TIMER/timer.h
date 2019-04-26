/**
  ******************************************************************************
  * @file    timer.ch
  * @author  zju.nesc.iotlab 浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    13-March-2019
  * @brief   timer configuration and running functions   定时器配置和运行方法
  ******************************************************************************
  */

#ifndef _TIMER_H
#define _TIMER_H

//-------------include---------------//
#include "sys.h"
#include "config.h"


//! 基本是10s(10000ms)更新一下
#define SYNC_INTERVAL_TIME    10000
//! 是否让工作灯在定时器中闪烁
#define WORKING_LED_SHINE_IN_TIMER  1
//! 是否让展示nodeId灯在定时器中闪烁
#define NODE_ID_LED_SHINE_IN_TIMER	1
//! 是否让IO每隔一段时间取反
#define IO_SHINE_IN_TIMER     0     
//! TIME3 的ARR和PSC
#define TIM3_ARR              999
#define TIM3_PSC              83
//! TIME4 的ARR和PSC
#define TIM4_ARR              99
#define TIM4_PSC              83
//! TIM3和4的主时钟频率MHz
#define TIM3_4_PCLK_MHZ       84

//!系统时钟，计时单位根据TIM4设置情况而定
//! @note 计时单位T = Tclk / (arr + 1) / (psc + 1)
extern u32 SYSTEMTIME;

//!同步时钟模块距离上次同步的时间间隔
extern volatile u32 sync_interval_time;

void TIM3_Int_Init(u16 arr,u16 psc);
void TIM4_Int_Init(u16 arr,u16 psc);

#endif
