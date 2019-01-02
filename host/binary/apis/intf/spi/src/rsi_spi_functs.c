/**
 * @file     rsi_spi_functs.c
 * @version  2.7
 * @date     2012-Sep-26
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief Common SPI Functions
 *
 * @section Description
 * SPI bus Layer function used to transfer spi protocol level commands to module.
 * For more detail refer PRM for spi commands
 *
 */


/*
 * Includes
 */
 #include "spi.h"
#include "rsi_global.h"
#include "rsi_spi_cmd.h"
#include "rsi_config.h"

#if (RSI_INTERFACE == RSI_SPI)

/**
 * Global Variables
 */


/*==================================================*/
/**
 * @fn          int16 rsi_send_c1c2(uint8 c1, uint8 c2)
 * @brief       Sends the C1 & C2 commands bytes, should check response for C1 command.Incase of busy should retry.
 * @param[in]   uint8 c1 SPI c1 command.
 * @param[in]   uint8 c2 SPI c2 command
 * @param[out]  none
 * @return      errCode
 *              -1 = SPI busy / Timeout
 *              -2 = SPI Failure
 *              0  = SUCCESS
 */
int16 rsi_send_c1c2(uint8 c1, uint8 c2)
{
 int16                   retval;
 uint32                  timeout;            
 uint8                   txCmd[2];             
 uint8                   localBuf[8];
 timeout = 1 * RSI_TICKS_PER_SECOND;     
 //! reset the timeout timer to 0
 RSI_RESET_TIMER1;      
 while (1) {
   txCmd[0] = c1;    
   txCmd[1] = c2;               
   if (RSI_INC_TIMER_1 > timeout) 
   {           
     retval = RSI_BUSY;              
#ifdef RSI_DEBUG_PRINT
     RSI_DPRINT(RSI_PL8,"\r\n C1C2 command Timeout");
#endif
     break;
   }
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL7," C1C2=");
#endif
  //! Send C1 & C2 
  retval = rsi_spi_send(&txCmd[0], 2,localBuf,RSI_MODE_8BIT);
   
//    uint16        i; 
//	uint8 	temp1;
	/*这里用移植好的代码*/
	/*SPI_CS    SPI1_TxRx 这两个*/
//	SPI_CS_L;
//	for(i =0;i <2;i ++) 
//	{	  
//		SPI1->DR=txCmd[i];
//		while ((SPI1->SR&SPI_I2S_FLAG_RXNE) == 0); //???????byte  


//		temp1 = SPI1->DR;//SPI_I2S_ReceiveData(SPI1); //????SPIx???????	

//		localBuf[i] =temp1;

//	}
//	SPI_CS_H;
  if((localBuf[1] == RSI_SPI_SUCCESS) ||(localBuf[1] == 0x00))  {            
   //! success, so return now 
   retval = RSI_SUCCESS;
   break;
  }
  else if (localBuf[1] == RSI_SPI_FAIL) {
#ifdef RSI_DEBUG_PRINT
   RSI_DPRINT(RSI_PL8,"\r\n C1C2 command Failed");
#endif
   retval = RSI_FAIL;
   break;
  }
  else if (localBuf[1] == RSI_SPI_BUSY) {
   //! Busy, retry once again 
   retval = RSI_BUSY;
  }
 }

 return retval;
}



/*==================================================*/
/**
 * @fn          int16 rsi_send_c3c4(uint8 c3, uint8 c4)
 * @brief       Sends the C3/C4 bytes
 * @param[in]   uint8 c3 SPI c3 command bytes to be sent
 * @param[in]   uint8 c4 SPI c4 command bytes to be sent
 * @param[out]  none
 * @return      errCode
 *              -1 = SPI busy / Timeout
 *              -2 = SPI Failure
 *              0  = SUCCESS
 * @prerequisite rsi_send_c1c2 should successful before this function.
 */
int16 rsi_send_c3c4(uint8 c3, uint8 c4)
{
 int16                   retval;
 uint8                   txCmd[2];  //@ command buffer
 uint8                   localBuf[8];

 txCmd[0] = c3;
 txCmd[1] = c4;
#ifdef RSI_DEBUG_PRINT
 RSI_DPRINT(RSI_PL15," C3C4=");
#endif
 //!command should send only 8 bit mode 
 retval = rsi_spi_send(txCmd, (uint16)sizeof(txCmd),localBuf,RSI_MODE_8BIT);
//    uint16        i; 
//	uint8 	temp1;
//	/*这里用移植好的代码*/
//	/*SPI_CS    SPI1_TxRx 这两个*/
//	SPI_CS_L;
//	for(i =0;i <2;i ++) 
//	{	  
//		//  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}//??????  
//	SPI1->DR=txCmd[i];
//	//SPI_I2S_SendData(SPI1, TxData); //????SPIx????byte  ??
//  while ((SPI1->SR&SPI_I2S_FLAG_RXNE) == 0); //???????byte  
//		
//  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET){} //???????byte  
// 
//	temp1 = SPI1->DR;//SPI_I2S_ReceiveData(SPI1); //????SPIx???????	

//	localBuf[i] =temp1;

//	}
//	SPI_CS_H;
	
 return retval;
}



/*==================================================*/
/**
 * @fn            int16 rsi_spi_wait_start_token(uint32 timeout,uint8 mode)
 * @brief         Loops reading the SPI until a start token, 0x55, is received
 * @param[in]     uint32  timeout   Timeout for start token.
 * @param[in]     uint8   mode      To indicate 8bit/32bit mode.
 * @param[out]    none
 * @return        errCode
 *                 0 = success
 *                -1 = busy/timeout failure
 *                -2 = spi failure
 * @section prerequisite 
 * should issue read commands before this function.
 */
int16 rsi_spi_wait_start_token(uint32 timeout,uint8 mode)
{
 int16                   retval;
#ifdef RSI_BIT_32_SUPPORT
 uint32                  txChar;       //! char to send/receive data in
#else
 uint8                   txChar;
#endif
 //! Look for start token
 //! Send a character, could be any character, and check the response for a start token
 //! If we don't find it within the timeout time, error out
 //! Timeout value needs to be passed since context is important
#ifdef RSI_DEBUG_PRINT
 RSI_DPRINT(RSI_PL8,"\r\nWaitStartToken=");
#endif
 RSI_RESET_TIMER1;       //! reset the timeout timer to 0;
 while(1) 
 {
  if (RSI_INC_TIMER_1 > timeout) 
  {  
   retval = RSI_BUSY;             
   //! timeout 
   break;                   
  }

  txChar = 0x00;
#ifdef RSI_BIT_32_SUPPORT
  if( mode == RSI_MODE_8BIT)
#endif
   retval = rsi_spi_recv((uint8 *)&txChar, 1, mode);
#ifdef RSI_BIT_32_SUPPORT 
  else
   retval = rsi_spi_recv((uint8 *)&txChar, 4, mode);
#endif    
  if (txChar == RSI_SPI_START_TOKEN) {      
   //! found the start token 
   retval = RSI_SUCCESS;            
   break;
  }
 }
 return retval;
}


/*==================================================*/
/**
 * @fn          int16 rsi_set_intr_mask(uint8 interruptMask)
 * @brief       Sets the INTERRUPT MASK REGISTER of the Wi-Fi module
 * @param[in]   uint8 interruptMask, the value to set the mask register to
 * @param[out]  none
 * @return      errorcode 
 *               0 = Success
 *              -1 = busy/timeout failure
 *              -2 = spi failure 
 
 */
int16 rsi_set_intr_mask(uint8 interruptMask)
{
 int16                     retval;
 int16                     i;
#ifdef RSI_BIT_32_SUPPORT
    uint8                   dBuf[4]= {0,0,0,0};
#else
    uint8                   dBuf[2]= {0,0};
#endif


 //! Create the data to write to the interrupt mask register
 for (i = 0; i < sizeof(dBuf); i++) { dBuf[i] = 0; }  // zero out dBuf
 dBuf[0] = interruptMask;

 //!memory write the mask value
 retval = rsi_mem_wr(RSI_INT_MASK_REG_ADDR, sizeof(dBuf), dBuf); // 0x74, 0x00, 0x22000008, 0x04, interruptMask

 return retval;
}




/*==================================================*/
/**
 * @fn          int16 rsi_clear_interrupt(uint8 interruptClear)
 * @brief       Clears the interrupt register
 * @param[in]   uint8 interrutClear, the value to set the interrupt clear register to
 * @param[out]  none
 * @return      errorcode 
 *              -1 = busy/timeout failure
 *              -2 = spi failure 
 *               0 = Success
 */
int16 rsi_clear_interrupt(uint8 interruptClear)
{
 int16                     retval;
#ifdef RSI_BIT_32_SUPPORT
    uint8                   dBuf[4]= {0,0,0,0};
#else
    uint8                   dBuf[2]= {0,0};
#endif
 //! read in the register so we can set bit 5 and write back out
 //!retval = rsi_memRd(RSI_INT_CLR_REG_ADDR, sizeof(dBuf), dBuf); 
 //! 0x74, 0x00, 0x22000010
 //! set bit 5, interrupt clear
 dBuf[0] |= interruptClear;
 //! memory write the mask value
 retval = rsi_mem_wr(RSI_INT_CLR_REG_ADDR, sizeof(dBuf), dBuf);     
 //! 0x74, 0x00, 0x22000010

 return retval;
}




/*==================================================*/
/**
 * @fn          int16 rsi_device_interrupt_status(uint8 *int_status)
 * @brief       Returns the value of the Interrupt register
 * @param[in]   none
 * @param[out]  none
 * @return      errorcode
 *               0 = Success
 *              -1 = busy/timeout failure
 *              -2 = spi failure  
 */
int16 rsi_device_interrupt_status(uint8 *int_status)
{
 int16                   retval;
 uint32                  timeout; 
	
 //卡死
 // timeout = 1 * RSI_TICKS_PER_SECOND;
	timeout = 10;
 
 RSI_RESET_TIMER2;
 while(1) 
 {
  if (RSI_INC_TIMER_2 > timeout) {   
   retval = RSI_BUSY;       //! timeout
#ifdef RSI_DEBUG_PRINT
   RSI_DPRINT(RSI_PL3,"\r\nError Readng Interrupt Status Register = Timeout");
#endif
   break;                   //!retry some more
  }

  //! read the interrupt register
  retval = rsi_reg_rd(RSI_SPI_INT_REG_ADDR, int_status);    

  if(retval != RSI_BUSY) 
    {
   break;
  }
 }

 return retval;
}
/*==================================================================*/
/**
 * @fn         int16 rsi_spi_high_speed_enable(void)
 * @param[in]  None
 * @param[out] None
 * @return     0, 0=success
 * @description
 * This API is program Redpine module SPI in high speed mode
 */

int16 rsi_spi_high_speed_enable()
{
    uint8 data=1;
    uint8 return_val;
    return_val = rsi_reg_wr(0x08,&data);
    return return_val;
}

#endif
