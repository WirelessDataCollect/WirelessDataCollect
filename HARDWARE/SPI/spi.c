#include "spi.h"
#include "rsi_global.h"
#include "rsi_app.h"
//时钟配置


void RCC_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);
	RNG_Cmd(ENABLE );
}
 


void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//设置成最高优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//
//	NVIC_InitStructure.NVIC_IRQChannel=EXTI15_10_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
//	NVIC_Init(&NVIC_InitStructure);
	//
}

void SPI_Conf(void)
{	 
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	//CS:PC5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//RST:PB0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	//INTR中断：PC4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,GPIO_PinSource4);  
  
	
//	// TX INTR中断：PA10
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//	GPIO_Init(GPIOA, &GPIO_InitStructure); 
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,GPIO_PinSource10); 
//	//
//	
//	//PA9 
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	//
	
	//CLK:PA5;MISO:PA6;MOSI:PA7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	SPI_CS_H;

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_SPI1);


	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;	
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;	
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;		
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	
	SPI_InitStructure.SPI_CRCPolynomial = 7;	
	SPI_Init(SPI1, &SPI_InitStructure);  

	SPI_Cmd(SPI1, ENABLE); 
	SPI_CS_L;

	//	SPI1_TxRx(0xff);	 
}   
void EXTI_Conf(void)
{
	EXTI_InitTypeDef   EXTI_Type;
	EXTI_Type.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Type.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Type.EXTI_Line=EXTI_Line4;
	EXTI_Type.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_Type);
	
	
}

void EXTI_TX_Conf(void)
{
	EXTI_InitTypeDef   EXTI_Type;
	EXTI_Type.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Type.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Type.EXTI_Line=EXTI_Line10;
	EXTI_Type.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_Type);
}

u8 SPI1_TxRx(u8 TxData)
{		 			 
	
//  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}//??????  
	SPI1->DR=TxData;
	//SPI_I2S_SendData(SPI1, TxData); //????SPIx????byte  ??
  while ((SPI1->SR&SPI_I2S_FLAG_RXNE) == 0); //???????byte  
		
//  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET){} //???????byte  
 
	return SPI1->DR;//SPI_I2S_ReceiveData(SPI1); //????SPIx???????	
 		    
}


//uint32 rsi_send_fast_ludp_data(uint16 socketDescriptor, uint8 *payload,
//    uint32 payloadLen,uint8 protocol, uint8 *destIp, uint16 destPort,uint32 *bytes_sent)
//{
//  int16         retval = 0;
//  //!payload length sent in each packet
//  uint32        send_payload_len = 0;
//  //!payload offset
//  uint32        payload_offset = 0;
//  uint32        headerLen = 0;
//  //! length of frame without padding bytes
//  uint32        frameLen = 0;
//  //! length to pad the transfer so it lines up on a 4 byte boundary
//  uint8  rsi_local_frameCmdSend[RSI_BYTES_3];

//  memcpy(rsi_local_frameCmdSend, rsi_frameCmdSend, RSI_BYTES_3);

//  if(protocol == RSI_PROTOCOL_UDP_V4)
//  {
//    headerLen = RSI_UDP_FRAME_HEADER_LEN;
//  }
//  else
//  {
//    headerLen = RSI_UDP_V6_FRAME_HEADER_LEN;
//  }

//  rsi_uint16_to_2bytes(rsi_app_cb.uSendFrame.sendFrameLudpSnd.sendDataOffsetSize, headerLen);

//  rsi_uint16_to_2bytes(rsi_app_cb.uSendFrame.sendFrameLudpSnd.ip_version, RSI_IP_VERSION);
//  rsi_uint16_to_2bytes(rsi_app_cb.uSendFrame.sendFrameLudpSnd.socketDescriptor, socketDescriptor);
//  rsi_uint16_to_2bytes(rsi_app_cb.uSendFrame.sendFrameLudpSnd.destPort, destPort);


//  if(RSI_IP_VERSION == IP_VERSION_4)
//  {
//    memcpy(&rsi_app_cb.uSendFrame.sendFrameLudpSnd.destIPaddr.ipv4_address,destIp,RSI_IP_ADD_LEN);
//  }
//  else
//  {
//    memcpy(&rsi_app_cb.uSendFrame.sendFrameLudpSnd.destIPaddr.ipv6_address,destIp ,16);
//  }
//  while(payloadLen)
//  {
//    if(payloadLen >= RSI_UDP_MAX_SEND_SIZE)
//    {
//      send_payload_len =RSI_UDP_MAX_SEND_SIZE;
//    }
//    else
//    {
//      send_payload_len = payloadLen;
//    }
//    frameLen = send_payload_len + headerLen;
//    rsi_uint16_to_2bytes(rsi_local_frameCmdSend, ((frameLen & 0x0FFF) | 0x5000));
//    

//    rsi_uint16_to_2bytes(rsi_app_cb.uSendFrame.sendFrameLudpSnd.sendBufLen,send_payload_len);
//    
//    memcpy((uint8 *)&rsi_app_cb.uSendFrame.uSendBuf[headerLen],(uint8 *)(payload + payload_offset),send_payload_len);
//    retval = rsi_execute_cmd((uint8 *)rsi_local_frameCmdSend,(uint8 *)&rsi_app_cb.uSendFrame, (uint16)frameLen);
//    if (retval != 0x00)
//    {
//      return retval;
//    }
//    payloadLen     -= send_payload_len;
//    *bytes_sent    += send_payload_len;
//    payload_offset += send_payload_len;
//  }
//  return retval;
//}




