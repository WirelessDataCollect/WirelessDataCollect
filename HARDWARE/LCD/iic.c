#include "iic.h"


void delay_5ms(void)
{
	uint32_t i=0x8;
	while(i--);
}

void SDA_IN(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
}
void SDA_OUT(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
	
}

//初始化IIC
void IIC_Init(void)
{					     
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOF时钟

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
	GPIO_SetBits(GPIOB, GPIO_Pin_14);//GPIOF9,F10设置高，灯灭
	GPIO_SetBits(GPIOB, GPIO_Pin_15);//GPIOF9,F10设置高，灯灭
	
//	IIC_SCL_H;//高电平
//	IIC_SDA_H;

}
//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA_H;	  	  
	IIC_SCL_H;
	delay_5ms();//(4);
 	IIC_SDA_L;//START:when CLK is high,DATA change form high to low 
	delay_5ms();//(4);
	IIC_SCL_L;//钳住I2C总线，准备发送或接收数据 
	delay_5ms();//(4);
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL_L;
	IIC_SDA_L;//STOP:when CLK is high DATA change form low to high
 	delay_5ms();//(4);
	IIC_SCL_H; 
	delay_5ms();//(4);
	IIC_SDA_H;//发送I2C总线结束信号
	delay_5ms();//(4);									   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	
	delay_5ms();//(4);	   
	IIC_SCL_H;
	delay_5ms();//(4);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
		delay_5ms();//(1);
	}
	IIC_SCL_L;//时钟输出0 
  delay_5ms();//(50);	
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL_L;
	SDA_OUT();
	IIC_SDA_L;
	delay_5ms();//(5);
	IIC_SCL_H;
	delay_5ms();//(5);
	IIC_SCL_L;
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	IIC_SCL_L;
	SDA_OUT();
	IIC_SDA_H;
	delay_5ms();//(5);
	IIC_SCL_H;
	delay_5ms();//(5);
	IIC_SCL_L;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	SDA_OUT(); 	    
    IIC_SCL_L;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
		{
			IIC_SDA_H;
		}
		else
		{
			IIC_SDA_L;
		}
        txd<<=1; 	  
		delay_5ms();//(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL_H;
		delay_5ms();//(2); 
		IIC_SCL_L;	
		delay_5ms();//(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	 {
        IIC_SCL_L; 
        delay_5ms();//(50);
				IIC_SCL_H;
		    delay_5ms();//(50);
        receive<<=1;
        if(READ_SDA)
				receive++;	
				
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}

void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data)
{
	uint8_t i;		  	    																 
	IIC_Start();  
	IIC_Send_Byte(daddr);	   //发送写命令//发送器件地址0xB8,写数据 
	IIC_Wait_Ack();

	IIC_Send_Byte(addr);//发送地址
	IIC_Wait_Ack();
	
	IIC_Send_Byte(data); //进入接收模式			   
	IIC_Wait_Ack();	 
	
	IIC_Stop();//产生一个停止条件
}
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr)  
{
	uint8_t i;		  	    																 
	IIC_Start();  
	IIC_Send_Byte(daddr);	   //发送写命令//发送器件地址0xB8,写数据 
	IIC_Wait_Ack();

	IIC_Send_Byte(addr);//发送地址
	IIC_Wait_Ack();

	IIC_Start();  	 	   
	IIC_Send_Byte(daddr+1); //进入接收模式			   
	IIC_Wait_Ack();	 

//	for(i=0;i<4;i++)
//	{
//	dat[i]=IIC_Read_Byte(1);//读前四个，发送ACK
//	}
	i=IIC_Read_Byte(0);//读第5个发送NACK

	IIC_Stop();//产生一个停止条件

	return i;

}























