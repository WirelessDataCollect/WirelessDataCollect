/**
 * @file      rsi_set_certificate.c
 * @version    1.2
 * @date       2013-Feb-16
 *
 * Copyright(C) Redpine Signals 2013
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief SET CERTIFICATE: Function which loads the Certificate 
 *
 * @section Description
 * This file contains the SET CERTIFICATE function.
 *
 * @Improvements
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"
#include <string.h>


/**
 * Global Variables
 */


/*===============================================================*/
/**
 * @fn        int16 rsi_set_certificate(uint8 certificate_type,uint8 *buffer,uint32 certifictae_length, struct SET_CHUNK_S *SetChunkPtr)
 * @brief      loads the certificate to the module 
 * @param[in]  uint8 certificate_type, type of the certificate to load
 * @param[in]  uint8 *buffer, pointer to the certificate buffer
 * @param[in]  uint32 certificate_length, length of the certificate 
 * @param[in]  SET_CHUNK_S *SetChunkPtr, pointer to the certificate structure
 * @param[out] none
 * @return     int16 retval
 *              SPI:
 *              -1 = SPI busy / Timeout
 *              -2 = SPI Failure
 *              -3 = BUFFER FULL
 *              0  = SUCCESS
 *              UART/USB/USB-CDC:
 *              -2 = Command issue failed
 *              0  = SUCCESS
 * @description This API is used to load the certificate to the module.
 */

int16 rsi_set_certificate(uint8 certificate_type,uint8 *buffer, uint32 certificate_length, struct SET_CHUNK_S *SetChunkPtr)
{ 
  int16 retval = 0;
  static uint16 rem_len ;
  uint16 chunk_size = 0;
  static uint16 offset;
  uint8  rsi_local_frameCmdCert[RSI_BYTES_3];

  //!Get the certificate chunk size  
  chunk_size = (MAX_CERT_SEND_SIZE - sizeof(struct cert_info_s)); 
  memcpy(rsi_local_frameCmdCert, rsi_frameCmdCert, RSI_BYTES_3);

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\nSet Certificate Start\n");
#endif
 //! This means it is the first chunk
  if(SetChunkPtr->cert_info.more_chunks == 0)
  {
	  rem_len = certificate_length;
  }
  
  if(rem_len >= chunk_size)
  {
    rsi_uint16_to_2bytes(rsi_local_frameCmdCert, ((MAX_CERT_SEND_SIZE & 0x0FFF) | 0x4000));
    
    //! Copy the certificate chunk 
    memcpy(SetChunkPtr->Certificate, buffer + offset, chunk_size);
    //! Move the offset by chunk size 
    offset += chunk_size;
    //! Subtract the rem_len by the chunk size  
    rem_len -= chunk_size;
    //!Set the total length of certificate
    rsi_uint16_to_2bytes(SetChunkPtr->cert_info.total_len, certificate_length);
    //! Set the certificate type 
    SetChunkPtr->cert_info.CertType = certificate_type;
    //! more chunks to send 
    SetChunkPtr->cert_info.more_chunks = 1;
    //! Set the length of the certificate chunk 
    rsi_uint16_to_2bytes(SetChunkPtr->cert_info.CertLen, chunk_size);
    //! set the Key_password of the certificate
    strcpy((char *)&SetChunkPtr->cert_info.KeyPwd,KEY_PASSWORD);
    retval = rsi_execute_cmd((uint8 *)rsi_local_frameCmdCert,(uint8 *)SetChunkPtr,MAX_CERT_SEND_SIZE);
  }
  else
  {
    rsi_uint16_to_2bytes(rsi_local_frameCmdCert, (((rem_len + sizeof(struct cert_info_s)) & 0x0FFF) | 0x4000));

    //! Copy the certificate chunk 
    memcpy(SetChunkPtr->Certificate, buffer + offset, rem_len);
    //! Move the offset by chunk size 
    offset += rem_len;
    //!Set the total length of certificate 
    rsi_uint16_to_2bytes(SetChunkPtr->cert_info.total_len, certificate_length);
    //! Set the certificate type 
    SetChunkPtr->cert_info.CertType = certificate_type;
    //!This is the last chunks to send
    SetChunkPtr->cert_info.more_chunks = 0;
    //! Set the length of the certificate chunk
    rsi_uint16_to_2bytes(SetChunkPtr->cert_info.CertLen,rem_len);
    //!set the Key_password of the certificate
    strcpy((char *)&SetChunkPtr->cert_info.KeyPwd,KEY_PASSWORD); 
    retval = rsi_execute_cmd((uint8 *)rsi_local_frameCmdCert,(uint8 *)SetChunkPtr,(rem_len + sizeof(struct cert_info_s)));

    //! Reset rem_len and offset 
    rem_len = 0;
    offset = 0;
  }

  return retval;
}
