/**
 * @file       rsi_send_ludp_data.c
 * @version    1.2
 * @date       2013-Feb-18
 *
 * Copyright(C) Redpine Signals 2013
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief SEND LUDP DATA: Function to send ludp data to an existing connection
 *
 * @section Description
 * This file contains the SEND function.
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"
#include <stdio.h>
#include <string.h>
#include "rsi_app.h"

/*
 * Global Variables
 */


/*=============================================================*/
/**
 * @fn          int16 rsi_send_ludp_data(uint16 socketDescriptor,
 *              uint8 *payload, uint32 payloadLen,uint8 protocol,
 *              uint8 *destIp, uint16 destPort)
 * @brief       SEND Packet command
 * @param[in]   uint16 socketDescriptor, socket descriptor for the socket to send data to
 * @param[in]   uint8 *payload, pointer to the data to send payload buffer
 * @param[in]   uint32 payloadLen, length of the data to send payload
 * @param[in]   uint8  protocol, 0 - LUDP
 * @param[in]   uint8 *destIp, Remote target IP address
 * @param[in]   uint8 *destPort, Remote target port
 * @param[out]  uint32 bytes_sent, number of bytes sent
 * @return      errCode
 *              SPI:
 *              -1 = SPI busy / Timeout
 *              -2 = SPI Failure
 *              -3 = BUFFER FULL
 *              0  = SUCCESS
 *              UART/USB/USB-CDC:
 *              -2 = Command issue failed
 *              0  = SUCCESS
 *
 * @section description
 * This API used to send LUDP data using an already opened socket. This function
 * should be called after successfully opening a socket using the rsi_socket API.
 * If this API return error codes like -1, Application need to retry this function until
 * successfully send the packet over WiFi module.
 */
#if !RSI_TCP_IP_BYPASS
int16 rsi_send_ludp_data(uint16 socketDescriptor, uint8 *payload,
    uint32 payloadLen,uint8 protocol, uint8 *destIp, uint16 destPort,uint32 *bytes_sent)
{
  int16         retval = 0;
  //!payload length sent in each packet
  uint32        send_payload_len = 0;
  //!payload offset
  uint32        payload_offset = 0;
  uint32        headerLen = 0;
  //! length of frame without padding bytes
  uint32        frameLen = 0;
  //! length to pad the transfer so it lines up on a 4 byte boundary
  uint8  rsi_local_frameCmdSend[RSI_BYTES_3];

  memcpy(rsi_local_frameCmdSend, rsi_frameCmdSend, RSI_BYTES_3);

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\nSend LUDP Data Start\n");
#endif

  if(protocol == RSI_PROTOCOL_UDP_V4)
  {
    headerLen = RSI_UDP_FRAME_HEADER_LEN;
  }
  else
  {
    headerLen = RSI_UDP_V6_FRAME_HEADER_LEN;
  }

  rsi_uint16_to_2bytes(rsi_app_cb.uSendFrame.sendFrameLudpSnd.sendDataOffsetSize, headerLen);

  rsi_uint16_to_2bytes(rsi_app_cb.uSendFrame.sendFrameLudpSnd.ip_version, RSI_IP_VERSION);
  rsi_uint16_to_2bytes(rsi_app_cb.uSendFrame.sendFrameLudpSnd.socketDescriptor, socketDescriptor);
  rsi_uint16_to_2bytes(rsi_app_cb.uSendFrame.sendFrameLudpSnd.destPort, destPort);


  if(RSI_IP_VERSION == IP_VERSION_4)
  {
    memcpy(&rsi_app_cb.uSendFrame.sendFrameLudpSnd.destIPaddr.ipv4_address,destIp,RSI_IP_ADD_LEN);
  }
  else
  {
    memcpy(&rsi_app_cb.uSendFrame.sendFrameLudpSnd.destIPaddr.ipv6_address,destIp ,16);
  }
  while(payloadLen)
  {
    if(payloadLen >= RSI_UDP_MAX_SEND_SIZE)
    {
      send_payload_len =RSI_UDP_MAX_SEND_SIZE;
    }
    else
    {
      send_payload_len = payloadLen;
    }
    frameLen = send_payload_len + headerLen;
    rsi_uint16_to_2bytes(rsi_local_frameCmdSend, ((frameLen & 0x0FFF) | 0x5000));
    

    rsi_uint16_to_2bytes(rsi_app_cb.uSendFrame.sendFrameLudpSnd.sendBufLen,send_payload_len);
    
    memcpy((uint8 *)&rsi_app_cb.uSendFrame.uSendBuf[headerLen],(uint8 *)(payload + payload_offset),send_payload_len);
    retval = rsi_execute_cmd((uint8 *)rsi_local_frameCmdSend,(uint8 *)&rsi_app_cb.uSendFrame, (uint16)frameLen);
    if (retval != 0x00)
    {
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL4,"SendCmd Err=%02x", (uint16)retval);  
#endif
      return retval;
    }
    payloadLen     -= send_payload_len;
    *bytes_sent    += send_payload_len;
    payload_offset += send_payload_len;
  }
  return retval;
}
#endif
