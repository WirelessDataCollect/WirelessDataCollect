#include "crc.h"
//********************************
//函数作用：计算Crc16数值
//
//hex：多项式码 0x8005  为 X^15+X^5+1
//********************************

CRC_TYPE CalCrc(u16 CRCIn, c8 * buf, u16 len,u16 polyHex)
{
    u16 byte;
    u8 k;
    u32 ACC,TOPBIT;
    u16 remainder = CRCIn;//1、初始值
    TOPBIT = 0x8000;  //用于取最高位
    for (byte = 0; byte < len; ++byte)
    {
        ACC = buf[byte];
        remainder ^= (ACC <<8); // 2、将数据第一个字节和CRCIn高8位异或
        for (k = 8; k > 0; --k)
        {
            if (remainder & TOPBIT)//3、取最高位，为1则与多项式Hex码异或
            {
                remainder = (remainder << 1) ^polyHex;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
    }
    remainder=remainder^0x0000;//就是原来那个数
	
    return remainder;
}

