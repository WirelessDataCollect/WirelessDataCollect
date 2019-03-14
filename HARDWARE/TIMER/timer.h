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


//! 基本是10s(10000ms)更新一下
#define SYNC_INTERVAL_TIME    10000
//! 是否让灯在定时器中闪烁
#define LED_SHINE_IN_TIMER    1
//! 是否让IO每隔一段时间取反
#define IO_SHINE_IN_TIMER     0     

//!系统时钟，计时单位根据TIM4设置情况而定
//! @note 计时单位T = Tclk / (arr + 1) / (psc + 1)
extern u32 SYSTEMTIME;

//!同步时钟模块距离上次同步的时间间隔
#if IAM_MASTER_CLOCK
extern u16 sync_interval_time;
#endif


void TIM3_Int_Init(u16 arr,u16 psc);
void TIM4_Int_Init(u16 arr,u16 psc);

#endif
