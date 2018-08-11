/**
 * @file     rsi_spi_framerdwr.c
 * @version  3.6
 * @date     2013-June-12
 *
 * Copyright(C) Redpine Signals 2013
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief SPI Control: Functions used to control SPI frame read/write functions
 *
 * @section Description
 * SPI function to read/write management descriptors frames to/from the Wi-Fi module
 *
 * @section Improvements
 * Function header is modified for frameDscRd() function
 */



/*
 * Includes
 */
#include "rsi_global.h"
#include "rsi_spi_cmd.h"
#include "rsi_config.h"

#if (RSI_INTERFACE == RSI_SPI)
/**
 * Global Variables
 */

/*====================================================*/
/**
 * @fn          int16 rsi_frame_read(uint8 *pkt_buffer)
 * @brief This  function is used to read the response from module.
 * @param[in]   uint8 *pkt_buffer, pointer to the buffer to which packet has to read
 *              which is used to store the response from the module
 * @param[out]  none
 * @return      errCode
 *              -1 = SPI busy / Timeout
 *              -2 = SPI Failure
 *              0  = SUCCESS
 * @section description 
 * This is a common function to read response for all the command and data from Wi-Fi module.
 */
int16 rsi_frame_read(uint8 *pkt_buffer)
{
  int16     retval; 
  uint8     local_buffer[8];


  retval = rsi_pre_dsc_rd(&local_buffer[0]);
  if (retval != 0x00) 
  {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL4,"DscRd Error=%02x ", (uint16)retval);
#endif
    return retval;
  }
  retval = rsi_pkt_rd(pkt_buffer, ((*(uint16 *)&local_buffer[2])-4),((*(uint16 *)&local_buffer[0])-4));
  if (retval != 0x00) 
  {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL4,"DscRdError=%02x ", (uint16)retval);
#endif
    return retval;
  }

  return retval;
}

/*====================================================*/
/**
 * @fn          int16 rsi_frame_write(rsi_uFrameDsc *uFrameDscFrame,uint8 *payloadparam,uint16 size_param)
 * @brief       Common function for all the commands.
 * @param[in]   uFrameDsc uFrameDscFrame, frame descriptor
 * @param[in]   uint8 *payloadparam, pointer to the command payload parameter structure
 * @param[in]   uint16 size_param, size of the payload for the command
 * @return      errCode
 *              -1 = SPI busy / Timeout
 *              -2 = SPI Failure
 *              0  = SUCCESS
 * @section description 
 * This is a common function used to process a command to the Wi-Fi module.
 */
int16 rsi_frame_write(rsi_uFrameDsc *uFrameDscFrame,uint8 *payloadparam,uint16 size_param)
{
  int16      retval;

  //! Write out the Command Frame Descriptor
  retval = rsi_spi_frame_dsc_wr(uFrameDscFrame);  

  if (retval != 0x00) 
  {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL4,"Descriptor write failErr=%02x", (uint16)retval);
#endif
    return retval;
  }

  //! Write the Command Frame Data
  if(size_param)
  {
    size_param= (size_param+3)&~3;  
    retval = rsi_spi_frame_data_wr(size_param, payloadparam, 0, NULL);
    if (retval != 0x00)
    {
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL4,"FramePayload writeErr=%02x", (uint16)retval);
#endif
      return retval;
    }
  }

  return retval;
}

/*===========================================================================*/
/**
 * @fn          int16 rsi_pre_dsc_rd(uint8 *dbuf)
 * @brief       Reads a pre frame descriptor
 * @param[in]   uint8 *dbuf, pointer to the buffer into which pre decriptor has to be read
 * @param[out]  none
 * @return      errCode
 *              -1 = SPI busy / Timeout
 *              -2 = SPI Failure
 *              0  = SUCCESS
 * @section description 
 * This function performs pre frame decriptor read. 
 */
int16 rsi_pre_dsc_rd(uint8 *dbuf)
{
  int16     retval;
  uint8     c1;
  uint8     c2;
  uint8     c3;
  uint8     c4;


  c1 = RSI_C1FRMRD16BIT4BYTE;         //! 0x5c
#ifdef RSI_BIT_32_SUPPORT
  c2 = RSI_C2SPIADDR4BYTE;            //! 0x40
#else
  c2 = RSI_C2MEMRDWRNOCARE;           //! 0x00
#endif
  c3 = 0x04;                          //! command frame response descriptor
  c4 = 0x00;                          //! upper bye of transfer length
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL5," CFrameDscRd=");
#endif
  // Send C1/C2
  retval = rsi_send_c1c2(c1, c2);
  if (retval != 0) {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL6," pre desc read - C1C2 Failed");
#endif
    return retval;                     //! exit with error if we timed out waiting for the SPI to get ready
  }

  // Send C3/C4
  retval = rsi_send_c3c4(c3, c4);

  // Wait for start token
  retval = rsi_spi_wait_start_token(RSI_START_TOKEN_TIMEOUT,RSI_MODE_32BIT);
  if (retval != 0) {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL6," pre desc read - Start token wait Failed");
#endif
    return retval;                     //! exit with error if we timed out waiting for the SPI to get ready
  }
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL6," CFrameDscRd=");
#endif
  retval = rsi_spi_recv((uint8 *)dbuf, 0x4, RSI_MODE_32BIT); 
  //! read the command frame descriptor
  return retval;                       //! return the control frame length
}


/*===========================================================================*/
/**
 * @fn          int16 rsi_pkt_rd(uint8 *buf, uint16 dummy_len, uint16 total_len)
 * @brief       Reads frame descriptor and payload
 * @param[in]   uint8 *dbuf, pointer to the buffer into which  decriptor and payload has to be read
 * @param[in]   uint16 dummy_len, number of dummy bytes which can be discarded
 * @param[in]   uint16 total_len, number of bytes to be read
 * @param[out]  none
 * @return      errCode
 *              -1 = SPI busy / Timeout
 *              -2 = SPI Failure
 *              0  = SUCCESS
 * @section description 
 * This function performs frame decriptor and payload read. 
 */

int16 rsi_pkt_rd(uint8 *buf, uint16 dummy_len, uint16 total_len)
{
  int16     retval;
  uint8     c1;
  uint8     c2;
  uint8     c3;
  uint8     c4;

  /* Here, the response buffer is allocated only 8 bytes eventhough the payload for many commands is more than this.
   * Since for evey frame  data write module will give dummy response, no need to store these dummy responses. 
   * In 'rsi_spi_recv()' function no need to copy dummy responses, to avoid local dummy_buf array overflow. 
   */

  uint8     dummy_buf[8];
  uint32    aligned_len=0;

  aligned_len = ((total_len) + 3) & ~3;
  c1 = RSI_C1FRMRD16BIT1BYTE;     //! 0x5d
#ifdef RSI_BIT_32_SUPPORT
  c2 = RSI_C2SPIADDR1BYTE;        //! 0x40
#else
  c2 = RSI_C2MEMRDWRNOCARE;       //! 0x00
#endif
  c3 = aligned_len & 0xff;            //! command frame response descriptor
  c4 = (aligned_len & 0xff00) >> 8;   //! upper bye of transfer length

  //! Send C1/C2
  retval = rsi_send_c1c2(c1, c2);
  if (retval != 0) {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL6," packet read - C1C2 Failed");
#endif
    return retval;            //! exit with error if we timed out waiting for the SPI to get ready
  }

  //! Send C3/C4
  retval = rsi_send_c3c4(c3, c4);
  //! Wait for start token
  retval = rsi_spi_wait_start_token(RSI_START_TOKEN_TIMEOUT,RSI_MODE_32BIT);
  if (retval != 0) {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL6," packet read - Start token wait Failed");
#endif
    return retval;               //! exit with error if we timed out waiting for the SPI to get ready
  }
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL6," packet read=");
#endif

  if(dummy_len)
  {
    //! spi recv for dummy bytes
    retval = rsi_spi_recv((uint8 *)&dummy_buf[0],dummy_len,RSI_MODE_8BIT); 
  }

  //! Actual spi read for descriptor and payload
  if(buf)
  {
    retval = rsi_spi_recv(buf, (aligned_len - dummy_len),RSI_MODE_32BIT); //TODO: this support only in 8bit mode need fix it for 32bit mode
  }
  // memcpy((uint8 *)buf, local_buf, (total_len));
  //! read the command frame descriptor
  return retval;       //! return the control frame length
}

/*===========================================================================*/
/**
 * @fn          int16 rsi_spi_frame_dsc_wr(uFrameDsc *uFrameDscFrame)
 * @brief       Writes a Frame descriptor
 * @param[in]   uFrameDsc uFrameDscFrame, frame descriptor
 * @param[in]   uint8 type, To indicate the type whether it is DATA or MGMT
 * @param[out]  none
 * @return      errCode
 *              -1 = SPI busy / Timeout
 *              -2 = SPI Failure
 *              0  = SUCCESS
 * @section description 
 * This function performs Frame Decriptor Write. 
 */
int16 rsi_spi_frame_dsc_wr(rsi_uFrameDsc *uFrameDscFrame)
{
  int16                             retval;
  uint8                             c1;
  uint8                             c2;
  uint8                             c3;
  uint8                             c4;
  uint8                             localBuf[16];


  c1 = RSI_C1FRMWR16BIT4BYTE;    // 0x7c
#ifdef RSI_BIT_32_SUPPORT
  c2 = RSI_C2RDWR4BYTE;         
#else
  c2 = RSI_C2RDWR1BYTE;      
#endif  
  c3 = RSI_FRAME_DESC_LEN;      //! frame descriptor is 16 bytes long
  c4 = 0x00;                    //! upper bye of transfer length
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL5,"\r\nCFrmDscWr");
#endif
  retval = rsi_send_c1c2(c1, c2);  //! send C1/C2

  if (retval != 0) {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL6," desc write - C1C2 Failed");
#endif    
    return retval;                   //! exit with error if we timed out waiting for the SPI to get ready
  }

  retval = rsi_send_c3c4(c3, c4);   //! send C3/C4
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL5," CFrameDscWr=");
#endif
  retval = rsi_spi_send(&uFrameDscFrame->uFrmDscBuf[0], RSI_FRAME_DESC_LEN,localBuf,RSI_MODE_32BIT);   
  //! the Management Type byte is in byte 1 (byte 0 is the length)
  return retval;                
  //! here we can only return ok
}


/*===========================================================================*/
/**
 * @fn          int16 rsi_spi_frame_data_wr(uint16 bufLen, uint8 *dBuf,uint16 tbufLen,uint8 *tBuf)
 * @brief       Writes a Control data frame decriptor.
 * @param[in]   uint16 buflen length of the data buffer to write
 * @param[in]   uint8 *dBuf, pointer to the buffer of data to write
 * @param[in]   uint16 tbuflen length of the data fragment to write
 * @param[in]   uint8 *tBuf, pointer to the buffer of data fragment to write
 * @param[out]  none
 * @return      errCode
 *              -1 = SPI busy / Timeout
 *              -2 = SPI Failure
 *              0  = SUCCESS  
 * @section description 
 * This function performs Frame Data Write. 
 */
int16 rsi_spi_frame_data_wr(uint16 bufLen, uint8 *dBuf,uint16 tbufLen,uint8 *tBuf)
{
  int16                     retval;
  uint8                     c1;
  uint8                     c2;
  uint8                     c3;
  uint8                     c4;
#ifdef LINUX
  uint8                     localBuf[1600];
#else
  uint8                     localBuf[8];
#endif
  uint16                    tempbufLen;
  tempbufLen = bufLen + tbufLen;

  c1 = RSI_C1FRMWR16BIT4BYTE;         
#ifdef RSI_BIT_32_SUPPORT
  c2 = RSI_C2RDWR4BYTE;                
#else
  c2 = RSI_C2RDWR1BYTE;         
#endif  
  c3 = (uint8)(tempbufLen & 0x00ff);       //! lower byte of transfer length
  c4 = (uint8)((tempbufLen >> 8) & 0x00FF);//! upper byte of transfer length
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL5,"\r\nFrmDataWr");
#endif
  retval = rsi_send_c1c2(c1, c2);        //! send C1/C2
  if (retval != 0) {
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL6,"\r\n data write - C1C2 Failed");
#endif 
    return retval; }                       //!exit with error if we timed out waiting for the SPI to get ready

  retval = rsi_send_c3c4(c3, c4);        //! send C3/C4
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL5," FrameData=");
#endif
#if 1
  retval = rsi_spi_send(dBuf, bufLen,localBuf,RSI_MODE_32BIT);
  if(tbufLen)
  {
    retval = rsi_spi_send(tBuf, tbufLen,localBuf,RSI_MODE_32BIT);   
  }
#endif

  return retval;       

}

#endif
