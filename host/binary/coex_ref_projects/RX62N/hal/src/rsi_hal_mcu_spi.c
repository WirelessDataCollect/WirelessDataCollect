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
 */


/**
 * Includes
 */
#include "rsi_global.h"

void rsi_change_transfer_length_32bit( void );
void rsi_change_transfer_length_8bit( void );

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
  PORTC.DR.BIT.B1 = 0;
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
  PORTC.DR.BIT.B1 = 1;
}

/*==================================================================*/
/**
 * @fn       int16 rsi_spi_send(uint8 *ptrBuf,uint16 bufLen,uint8 *valBuf,uint8 mode)
 * @param[in]   uint8 *ptrBuf, pointer to the buffer with the data to be sent/received
 * @param[in]   uint16 bufLen, number of bytes to send
 * @param[in]   uint8 *valBuf, pointer to the buffer where the response is stored
 * @param[in]   uint8 mode, To indicate mode 8 BIT/32 BIT.
 * @param[out]   None
 * @return   0, 0=success
 * @section description   
 * This API is used to send data to the Wi-Fi module through the SPI interface.
 */
int16 rsi_spi_send(uint8 *ptrBuf, uint16 bufLen,uint8 *valBuf,uint8 mode)
{
   uint16            i,j, dummy_ret;
#ifdef RSI_DEBUG_PRINT
   RSI_DPRINT(RSI_PL11,"Send:");
#endif
    
   rsi_spi_cs_assert();

#ifdef RSI_BIT_32_SUPPORT
    if(mode == RSI_MODE_32BIT)
     rsi_change_transfer_length_32bit();
#endif   
   for (i=0,j=0; i < bufLen; j++) {
      //! send the byte, blocks until ready
      //SPIM_1_WriteTxData(ptrBuf[i]);
#ifdef RSI_BIT_32_SUPPORT
      if(mode == RSI_MODE_8BIT)
#endif
      {
         while (RSPI0.SPSR.BIT.IDLNF) ;
         /* short 16 bits */
         RSPI0.SPDR.WORD.H = *(uint8 *)&ptrBuf[i];
         i+=1;
      }
#ifdef RSI_BIT_32_SUPPORT
      else
      {
         while (RSPI0.SPSR.BIT.IDLNF) ;
         RSPI0.SPDR.LONG =(*(uint32 *)&ptrBuf[i]);
         i+=4;
      }
#endif
      /* Wait for transfer to complete */
      while (RSPI0.SPSR.BIT.IDLNF) ;
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL9,"%02x", (uint16)ptrBuf[i]);
#endif
      if(RSPI0.SPCR.BIT.TXMD == 0)
      {         
         if((j<2)&&(RSPI0.SPSR.BIT.OVRF == 0))
         {
#ifdef RSI_BIT_32_SUPPORT
         if(mode == RSI_MODE_8BIT)
#endif
         {
            valBuf[j] = RSPI0.SPDR.WORD.H;
         }
#ifdef RSI_BIT_32_SUPPORT
         else
         {
            valBuf[j] = (uint8)RSPI0.SPDR.LONG;
         }
#endif
         }
         else
         {
#ifdef RSI_BIT_32_SUPPORT
         if(mode == RSI_MODE_8BIT)
#endif
            dummy_ret = (uint8)RSPI0.SPDR.WORD.H;
#ifdef RSI_BIT_32_SUPPORT
            dummy_ret = (uint8)RSPI0.SPDR.LONG;
#endif
            RSPI0.SPSR.BIT.OVRF = 0;
            //break;
         }
      }
   }
#ifdef RSI_BIT_32_SUPPORT
   if(mode == RSI_MODE_32BIT)
   rsi_change_transfer_length_8bit();
#endif   

   rsi_spi_cs_deassert();
   return 0;
}


/*==================================================================*/
/**
 * @fn       int16 rsi_spi_recv(uint8 *ptrBuf,uint16 bufLen,uint8 mode)
 * @param[in]   uint8 *ptrBuf, pointer to the buffer with the data to be sent/received
 * @param[in]   uint16 bufLen, number of bytes to send
 * @param[in]   uint8 mode, To indicate the mode 8 BIT / 32 BIT.
 * @param[out]   None
 * @return   0, 0=success
 * @description   This API is used to receive data from Wi-Fi module through the SPI interface.
 */


int16 rsi_spi_recv(uint8 *ptrBuf, uint16 bufLen, uint8 mode)
{
   int16            i;
#ifdef RSI_BIT_32_SUPPORT
   uint32              dummy=0;
   uint32              *TEMP_RDR;
#else
   uint8              dummy=0;
   uint8              *TEMP_RDR;
#endif

   rsi_spi_cs_assert();

   //! write data to SPIM tx buffer
#ifdef RSI_DEBUG_PRINT
   RSI_DPRINT(RSI_PL11,"Recv:");
#endif
#ifdef RSI_BIT_32_SUPPORT
    if(mode == RSI_MODE_32BIT)
     rsi_change_transfer_length_32bit();
#endif   
   for (i=0; i < bufLen; ) {
      //! send the byte, blocks until ready
#ifdef RSI_BIT_32_SUPPORT
      if(mode == RSI_MODE_8BIT)
#endif
      {
           while (RSPI0.SPSR.BIT.IDLNF) ;
         /* short 16 bits */
         RSPI0.SPDR.WORD.H = dummy;
      }
#ifdef RSI_BIT_32_SUPPORT
      else
      {
         while (RSPI0.SPSR.BIT.IDLNF) ;
         RSPI0.SPDR.LONG = dummy;
      }   
#endif
      /* Wait for transfer to complete */
      while (RSPI0.SPSR.BIT.IDLNF) ;
      // Read in the byte from the SPI interface
#ifdef RSI_BIT_32_SUPPORT
      if(mode == RSI_MODE_8BIT)
#endif
          {
            if(RSPI0.SPCR.BIT.TXMD == 0)
            {         
               if(RSPI0.SPSR.BIT.OVRF == 0)
               {
                  *(uint8 *)&ptrBuf[i] = RSPI0.SPDR.WORD.H;
               }
               else
               {
                  *TEMP_RDR = (uint8)RSPI0.SPDR.WORD.H;
                  RSPI0.SPSR.BIT.OVRF = 0;
                  //break;
               }
            } 
            i+=1;
         }
#ifdef RSI_BIT_32_SUPPORT
         else
         {         
            if(RSPI0.SPCR.BIT.TXMD == 0)
            {         
               if(RSPI0.SPSR.BIT.OVRF == 0)
               {
                  *(uint32 *)&ptrBuf[i] = RSPI0.SPDR.LONG;
               }
               else
               {
                  *TEMP_RDR = (uint32)RSPI0.SPDR.LONG;
                  RSPI0.SPSR.BIT.OVRF = 0;
                  //break;
               }
            } 
            i+=4;
         }      
#endif
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL10,"%02x", (uint16)ptrBuf[i]);
#endif
   }
#ifdef RSI_BIT_32_SUPPORT
  if(mode == RSI_MODE_32BIT)
  rsi_change_transfer_length_8bit();
#endif

#ifdef RSI_DEBUG_PRINT
   RSI_DPRINT(RSI_PL11," ");
#endif
   
   rsi_spi_cs_deassert();

   return 0;
}

void rsi_change_transfer_length_32bit( void )
{
   RSPI0.SPDCR.BYTE = 0x20;      /* Change SPDR register to long word mode */
   RSPI0.SPCMD0.WORD = 0x0300 ;  /* Change transfer length to 32 bit mode */   
}


void rsi_change_transfer_length_8bit( void )
{
   RSPI0.SPDCR.BYTE = 0x00;     /* Change SPDR register to word mode */
   RSPI0.SPCMD0.WORD = 0x0700 ; /* Change transfer length to 8 bit mode */      
}


