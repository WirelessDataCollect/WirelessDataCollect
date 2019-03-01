#include "led.h"
#include "OLED_I2C.h"
#include "codetab.h"
#include "iic.h"





void I2C_Configuration(void)
{
//	SetPinFunc_SCK3_1(0);  //Pins initialization 
//	SetPinFunc_SOT3_1(0); 
	//WB_I2c_Init(I2C3,400000);

//	WB_I2c_GetAck(I2C3);
}

void I2C_WriteByte(uint8_t addr,uint8_t data)
{
#if 1
	IIC_Write_One_Byte( 0x78,  addr, data);
#else
DS3231_MulitWrite( 0x78,  addr, &data,  1);

	WB_I2c_Write_DevAddr(I2C3, 0x78);
	WB_I2c_GetAck(I2C3);
	WB_I2c_Start(I2C3);

//	WB_I2c_Write_Data(I2C3, 0x78);Delay(1);	
//	WB_I2c_GetAck(I2C3);Delay(1);
	WB_I2c_Write_DevAddr(I2C3, addr);
	WB_I2c_ClrStatus(I2C3, I2cRxTxInt); 
	while(1) { 

		if(TRUE == WB_I2c_GetStatus(I2C3, I2cTxEmpty)) { 
		break; 
		} 
   }	
	WB_I2c_GetAck(I2C3);
	WB_I2c_Write_DevAddr(I2C3, data);
	WB_I2c_ClrStatus(I2C3, I2cRxTxInt); 
	while(1) { 

	if(TRUE == WB_I2c_GetStatus(I2C3, I2cTxEmpty)) { 
	break; 
		} 
	}
	WB_I2c_GetAck(I2C3);
	WB_I2c_Stop(I2C3);
#endif	

	

	
	
	
}

//void WriteCmd(unsigned char I2C_Command)//写命令
//{
//	I2C_WriteByte(0x00, I2C_Command);
//}

//void WriteDat(unsigned char I2C_Data)//写数据
//{
//	I2C_WriteByte(0x40, I2C_Data);
//}
#define WriteDat(a)	IIC_Write_One_Byte( 0x78,  0x40, a)
#define WriteCmd(a)	IIC_Write_One_Byte( 0x78,  0x00, a)
void OLED_Init(char cls)
{
	IIC_Init();
	delay_ms(1000);
	WriteCmd(0xAE); //display off
	WriteCmd(0x20);	//Set Memory Addressing Mode	
	WriteCmd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	WriteCmd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	WriteCmd(0xc8);	//Set COM Output Scan Direction
	WriteCmd(0x00); //---set low column address
	WriteCmd(0x10); //---set high column address
	WriteCmd(0x40); //--set start line address
	WriteCmd(0x81); //--set contrast control register
	WriteCmd(0xff); //亮度调节 0x00~0xff
	WriteCmd(0xa1); //--set segment re-map 0 to 127
	WriteCmd(0xa6); //--set normal display
	WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
	WriteCmd(0x3F); //
	WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	WriteCmd(0xd3); //-set display offset
	WriteCmd(0x00); //-not offset
	WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
	WriteCmd(0xf0); //--set divide ratio
	WriteCmd(0xd9); //--set pre-charge period
	WriteCmd(0x22); //
	WriteCmd(0xda); //--set com pins hardware configuration
	WriteCmd(0x12);
	WriteCmd(0xdb); //--set vcomh
	WriteCmd(0x20); //0x20,0.77xVcc
	WriteCmd(0x8d); //--set DC-DC enable
	WriteCmd(0x14); //
	WriteCmd(0xaf); //--turn on oled panel
	OLED_Fill(cls);//全屏灭

}

void OLED_SetPos(unsigned char x, unsigned char y) //设置起始点坐标
{ 
	WriteCmd(0xb0+y);
	WriteCmd(((x&0xf0)>>4)|0x10);
	WriteCmd((x&0x0f)|0x01);
}

void OLED_Fill(unsigned char fill_Data)//全屏填充
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		WriteCmd(0xb0+m);		//page0-page1
		WriteCmd(0x00);		//low column start address
		WriteCmd(0x10);		//high column start address
		for(n=0;n<128;n++)
			{
				WriteDat(fill_Data);
			}
	}
}

void OLED_CLS(void)//清屏
{
	OLED_Fill(0x00);
}

void OLED_ON(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X14);  //开启电荷泵
	WriteCmd(0XAF);  //OLED唤醒
}

void OLED_OFF(void)
{
	WriteCmd(0X8D);  //设置电荷泵
	WriteCmd(0X10);  //关闭电荷泵
	WriteCmd(0XAE);  //OLED休眠
}

//--------------------------------------------------------------
// Prototype      : void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
// Calls          : 
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); ch[] -- 要显示的字符串; TextSize -- 字符大小(1:6*8 ; 2:8*16)
// Description    : 显示codetab.h中的ASCII字符,有6*8和8*16可选择
//--------------------------------------------------------------
void OLED_ShowStr(unsigned char x, unsigned char y, char ch[], unsigned char TextSize)
{
	unsigned char c = 0,i = 0,j = 0;
//	switch(TextSize)
//	{
//		case 1:
//		{
//			while(ch[j] != '\0')
//			{
//				c = ch[j] - 32;
//				if(x > 126)
//				{
//					x = 0;
//					y++;
//				}
//				OLED_SetPos(x,y);
//				for(i=0;i<6;i++)
//					WriteDat(F6x8[c][i]);
//				x += 6;
//				j++;
//			}
//		}break;
//		case 2:
//		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i]);
				OLED_SetPos(x,y+1);
				for(i=0;i<8;i++)
					WriteDat(F8X16[c*16+i+8]);
				x += 8;
				j++;
			}
//		}//
//		break;
//	}
}


void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int  adder=32*N;
	OLED_SetPos(x , y);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder]);
		adder += 1;
	}
	OLED_SetPos(x,y + 1);
	for(wm = 0;wm < 16;wm++)
	{
		WriteDat(F16x16[adder]);
		adder += 1;
	}
}

void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;

  if(y1%8==0)
		y = y1/8;
  else
		y = y1/8 + 1;
	for(y=y0;y<y1;y++)
	{
		OLED_SetPos(x0,y);
    for(x=x0;x<x1;x++)
		{
			WriteDat(BMP[j++]);
		}
	}
}
