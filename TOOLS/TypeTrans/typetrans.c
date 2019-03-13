/**
  ******************************************************************************
  * @file    typetrans.c
  * @author  zju.nesc.iotlab 浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    13-March-2019
  * @brief   integer-string trans functions   整数-字符串转换方法
  ******************************************************************************
  */

//-------------include---------------//
#include "typetrans.h"
#include "config.h"

/**
  * @brief  反转字符串
  * @param  s：要反转的字符串
  * @retval 转换后的字符串
  */
u8 *reverse(char *s){
    char temp;
	/*p指向s的头部*/
    char *p = s;    
	/*q指向s的尾部*/
    char *q = s;
    while(*q)
    ++q;
    q--;
    
    /* 交换移动指针，直到p和q交叉*/
    while(q > p){
        temp = *p;
        *p++ = *q;
        *q-- = temp;
    }
    return (u8*)s;
}

/**
  * @brief  整数转字符串，如123->"123"
  * @param  n：整数
  * @retval 转换后的字符串
  */
u8 *itoa(u32 n)
{
    int i = 0,isNegative = 0;
	/* 必须为static变量，或者是全局变量*/
    static char s[STR_MAX_LENGTH];      
	/* 如果是负数，先转为正数*/
    if((isNegative = n) < 0) 
    {
        n = -n;
    }
    do      /* 从各位开始变为字符，直到最高位，最后应该反转*/
    {
        s[i++] = n%10 + '0';
        n = n/10;
    }while(n > 0);
    /* 如果是负数，补上负号*/
    if(isNegative < 0)   
    {
        s[i++] = '-';
    }
    s[i] = '\0';    /* 最后加上字符串结束符*/
    return reverse(s);
}


