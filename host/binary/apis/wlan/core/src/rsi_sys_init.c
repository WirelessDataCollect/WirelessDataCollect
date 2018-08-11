/** 
 * @file       rsi_sys_init.c
 * @version    2.0.0.0
 * @date       2011-Feb-25
 *
 * Copyright(C) Redpine Signals 2011
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief SYS INIT: Top level system initializations
 * 
 * @section Description
 * Any initializations which are not module or platform specific are done here
 * Any plaform or module specific initializations are called from here
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"
#include "rsi_spi_cmd.h"
#include <stdio.h>

/**
 * Global Variables
 */


/*===========================================================*/
/**
 * @fn            int16 rsi_sys_init()
 * @brief         SYSTEM INIT, Initializes the system specific hardware
 * @param[in]     none
 * @param[out]    none
 * @return        errCode
 *              
 *              -1 = SPI busy / Timeout
 *              -2 = SPI Failure
 *              -3 = BUFFER FULL
 *              0  = SUCCESS
 * @description This API is used to initialize the module and its SPI interface.
 */
int16 rsi_sys_init()
{
  int16    retval;              

  //! cycle the power to the module
  retval = rsi_module_power_cycle();//¸´Î»Ò»ÏÂ
  if(retval != 0)
  {
    return retval;
  }
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT( RSI_PL3,"\r\n\nSPI Interface Init ");
#endif  
  //!Init the module SPI interface, can only be done once after power on
  retval = rsi_spi_iface_init();
  if(retval != 0)
  {
    return retval;
  }
  return retval;
}
