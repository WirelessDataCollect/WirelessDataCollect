#ifndef __LED_H
#define __LED_H
#include "sys.h"



//LED端口定义
#define LED1 PCout(10)	// DS0
#define LED2 PDout(2)	// DS1	 

void LED_Init(void);//初始化		 				    
#endif
