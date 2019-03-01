/**
 * @file       rsi_utils.c
 * @version    2.7
 * @date       2015-Mar-2
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief Implements common functionality for all the commands
 *
 * @section Description
 * This file contains common api needed for all the commands
 *
 *
 */

/**
 * Includes
 */
#include "platform_specific.h"
#include "rsi_api.h"
#include "rsi_ble_api.h"
#include "rsi_app.h"
#include "rsi_scheduler.h"



#ifndef LINUX_PLATFORM
/*===========================================================================
 *
 * @fn          void rsi_memcpy(uint8_t *dst, uint8_t *src, uint8_t size)
 * @brief       Copy memory from src to dst 
 * @param[in]   source buffer
 * @param[out]  destination buffer
 * @param[in]   Size of buffer
 * @return      none
 * @section description
 * This API is used to copy given size memory from src to dst 
 *
 * ===========================================================================*/

void rsi_memcpy(UINT8 *dst, UINT8 *src, UINT32 size)
{
  UINT32  i = 0;
  for(i =0 ;i < size; i++) {
    dst[i] = src[i];
  }
}

/*===========================================================================
 *
 * @fn          void rsi_memset(uint8_t *src, uint8_t data, uint8_t size)
 * @brief       Memset the buffer with given data
 * @param[out]  source buffer
 * @param[in]   data
 * @param[in]   size of buffer
 * @return      none
 * @section description
 * This API is used to reset the given buffer with the provided data 
 *
 * ===========================================================================*/

void rsi_memset(UINT8 *src, UINT8 data, UINT32 size)
{
  UINT32  i = 0;
  for(i =0 ;i < size; i++) {
    src[i] = data;
  }
}

/*===========================================================================
 *
 * @fn          uint8_t rsi_memcmp(uint8_t *buf1,uint8_t *buf2,uint8_t len)
 * @brief       Compares two buffers of certain length
 * @param[in]   pointer to buffer 1
 * @param[in]   pointer to buffer 2
 * @param[in]   Length of bufres to be compared
 * @return      1: FAIL,0 : SUCCESS
 * @section description
 * This API is used to compare two buffers of length 'len'
 *
 * ===========================================================================*/

UINT8 rsi_memcmp(UINT8 *buf1,UINT8 *buf2,UINT32 len)
{
  UINT32 i;
  for ( i =0 ; i< len ; i++)
  {
    if(*(buf1 + i)!= *(buf2 + i))
      return 1;
  }
  return 0;
}
#endif


/*===========================================================================
 *
 * @fn          void rsi_exit_critical_sec(void)
 * @brief       Critical Section exit
 * @param[in]   None
 * @return      None
 * @section description
 * This API is used to do critical section exit. 
 *
 * ===========================================================================*/
void rsi_exit_critical_sec(void)
{
#ifdef WINDOWS
	  	LeaveCriticalSection(&crit_sec);
#else
#ifdef LINUX_PLATFORM
      pthread_mutex_unlock(&rsi_linux_app_cb.mutex1);
#endif
#endif
}


/*===========================================================================
 *
 * @fn          void rsi_enter_critical_sec(void)
 * @brief       Critical Section INit
 * @param[in]   None
 * @return      None
 * @section description
 * This API is used to do critical section Init. 
 *
 * ===========================================================================*/
void rsi_enter_critical_sec(void)
{
#ifdef WINDOWS
	  	EnterCriticalSection(&crit_sec);
#else
#ifdef LINUX_PLATFORM
      pthread_mutex_lock(&rsi_linux_app_cb.mutex1);
#endif
#endif
}

