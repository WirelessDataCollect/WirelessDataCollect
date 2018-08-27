#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 								  
////////////////////////////////////////////////////////////////////////////////// 	
extern u32 SYSTEMTIME;

#define SYNC_INTERVAL_TIME    2000  //基本是2s更新一下
#define LED_SHINE_IN_TIMER   1//是否让灯在定时器中闪烁
extern u16 sync_interval_time;
void TIM3_Int_Init(u16 arr,u16 psc);

#endif
