/**
 * @file     rsi_bytes_sent_count.c
 * @version  1.0
 * @date     2014-Oct-31
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief BYTES SENT COUNT: Function to send bytes sent count on socket
 *
 * @section Description
 * This file contains the socket sent bytes count query function.
 *
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"


/**
 * Global defines
 */


/**===========================================================================
 * @fn          int16 rsi_bytes_sent_count(uint16 socketDescriptor)
 * @brief       Queries the total bytes sent count with the given socket descriptor
 * @param[in]   uint16 socketDescriptor, socket to query
 * @param[out]  none
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
 * This API is used to query the total bytes sent count with the given descriptor.
 * @section prerequisite 
 * Socket with the given descriptor should already be created.
 */
int16 rsi_bytes_sent_count(uint16 socketDescriptor)

{
  int16                                   retval;
  rsi_uQuerySentBytesCount                uQuerySentBytesCountFrame;
  
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\nSent bytes query\n");
#endif


  rsi_uint16_to_2bytes(uQuerySentBytesCountFrame.querySentBytesCountFrameSnd.socketDescriptor, socketDescriptor);
  
  retval =rsi_execute_cmd((uint8 *)rsi_frameCmdSentBytesCount,(uint8 *)&uQuerySentBytesCountFrame,sizeof(rsi_uQuerySentBytesCount));
  return retval;

}
