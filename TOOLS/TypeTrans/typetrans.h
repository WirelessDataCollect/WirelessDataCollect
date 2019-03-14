/**
  ******************************************************************************
  * @file    typetrans.h
  * @author  zju.nesc.iotlab 浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    13-March-2019
  * @brief   integer-string trans functions   整数-字符串转换方法
  ******************************************************************************
  */


#ifndef __TYPETRANS_H
#define __TYPETRANS_H

//-------------include---------------//
#include "sys.h"

//!支持的整数转字符串最长长度
#define STR_MAX_LENGTH  20


u8 * itoa(u32 n);

#endif

