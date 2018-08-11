/**
 * @file       rsi_hal_mcu_spi.c
 * @version    2.3.0.0
 * @date       2011-May-30
 *
 * Copyright(C) Redpine Signals 2011
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief: HAL SPI API
 *
 * @Description:
 * This file Contains all the API's related to HAL 
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"
#include "SPI.h"

/**
 * Global Variables
 */

/*==================================================================*/
/**
 * @fn         int16 rsi_spi_cs_assert(void)
 * @param[in]  None
 * @param[out] None
 * @return     None
 * @description 
 * This API is used to assert the SPI chip select for SPI interface.
 */
void rsi_spi_cs_assert(void)
{
  //! Make SPI CS LOW
}

/*==================================================================*/
/**
 * @fn         int16 rsi_spi_cs_deassert(void)
 * @param[in]  None
 * @param[out] None
 * @return     None
 * @description 
 * This API is used to deassert the SPI chip select for SPI interface.
 */
void rsi_spi_cs_deassert(void)
{
  //! Make SPI CS HIGH
}

/*==================================================================*/
/**
 * @fn         int16 rsi_spi_send(uint8 *ptrBuf,uint16 bufLen,uint8 *valBuf,uint8 mode)
 * @param[in]  uint8 *ptrBuf, pointer to the buffer with the data to be sent/received
 * @param[in]  uint16 bufLen, number of bytes to send
 * @param[in]  uint8 *valBuf, pointer to the buffer where the response is stored
 * @param[in]  uint8 mode, To indicate mode 8 BIT/32 BIT.
 * @param[out] None
 * @return     0, 0=success
 * @section description  
 * This API is used to send data to the Wi-Fi module through the SPI interface.
 */
int16 rsi_spi_send(uint8 *ptrBuf, uint16 bufLen,uint8 *valBuf,uint8 mode)
{
  uint16        i; 
	uint8 	temp1;
	/*这里用移植好的代码*/
	/*SPI_CS    SPI1_TxRx 这两个*/
	SPI_CS_L;
	for(i =0;i <bufLen;i ++) 
	{	  
		temp1 =SPI1_TxRx(ptrBuf[i]);										   // //SPI ????    SPI????  8bit
		if(i <2)
		{
			valBuf[i] =temp1;
		}
	}
	SPI_CS_H;
	
	
  return 0;
}


/*==================================================================*/
/**
 * @fn         int16 rsi_spi_recv(uint8 *ptrBuf,uint16 bufLen,uint8 mode)
 * @param[in]  uint8 *ptrBuf, pointer to the buffer with the data to be sent/received
 * @param[in]  uint16 bufLen, number of bytes to send
 * @param[in]  uint8 mode, To indicate the mode 8 BIT / 32 BIT.
 * @param[out] None
 * @return     0, 0=success
 * @description 
 * This API is used to receive data from Wi-Fi module through the SPI interface.
 */
int16 rsi_spi_recv(uint8 *ptrBuf, uint16 bufLen, uint8 mode)
{
  int16        i;
/*这里用移植好的代码*/
	/*SPI_CS    SPI1_TxRx 这两个*/
	SPI_CS_L;
	for(i =0;i <bufLen;i ++) 
	{  
		ptrBuf[i] =SPI1_TxRx(0x55);
	}
	SPI_CS_H;
  return 0;
}



