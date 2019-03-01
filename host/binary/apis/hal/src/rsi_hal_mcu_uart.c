/**
 * @file       rsi_hal_mcu_uart.c
 * @version    1.0
 * @date       2014-Sept-23
 *
 * Copyright(C) Redpine Signals 2011
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief: HAL UART API
 *
 * @Description:
 * This file Contains all the API's related to HAL 
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"

/**
 * Global Variables
 */

/*==================================================================*/
/**
 * @fn         int16 rsi_uart_send(uint8 *ptrBuf,uint16 bufLen,uint8 *valBuf,uint8 mode)
 * @param[in]  uint8 *ptrBuf, pointer to the buffer with the data to be sent/received
 * @param[in]  uint16 bufLen, number of bytes to send
 * @param[out] None
 * @return     0, 0=success
 * @section description  
 * This API is used to send data to the Wi-Fi module through the UART interface.
 */
int16 rsi_uart_send(uint8 *ptrBuf, uint16 bufLen)
{
  return 0;
}


/*==================================================================*/
/**
 * @fn         int16 rsi_uart_recv(uint8 *ptrBuf,uint16 bufLen,uint8 mode)
 * @param[in]  uint8 *ptrBuf, pointer to the buffer with the data to be sent/received
 * @param[in]  uint16 bufLen, number of bytes to send
 * @param[out] None
 * @return     0, 0=success
 * @description 
 * This API is used to receive data from Wi-Fi module through the UART interface.
 */


int16 rsi_uart_recv(uint8 *ptrBuf, uint16 bufLen)
{
  return 0;
}
