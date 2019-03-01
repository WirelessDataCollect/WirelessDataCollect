/**
 * @file        rsi_webpage_clear_files.c
 * @version     2.7
 * @date        2012-Sep-26
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief Clear Webpage Files: This function deletes all webpages in the file system
 *
 * @section Description
 * This file contains the function to erase all webpage files present in the
 * module's file system
 *
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"

/**
 * Global Variables
 */

/*==============================================*/
/**
 * @fn             int16 rsi_webpage_clear_files(void)
 * @brief          Erases all files in the webpage file system
 * @param[in]      none
 * @param[out]     none
 * @return         errCode
 *                 SPI:
 *                  -1 = SPI busy / Timeout
 *                  -2 = SPI Failure
 *                  -3 = BUFFER FULL
 *                  0  = SUCCESS
 *                 UART/USB/USB-CDC:
 *                  -2 = Command issue failed
 *                  0  = SUCCESS
 * @section description   
 * This API erases all webpage files present in the file system.
 */
int16 rsi_webpage_clear_files(rsi_tfs_clear_files_t* clear)
{
    int16                   retval;

#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL3,"\r\nWebpage Clear Files Start");
#endif
    retval = rsi_execute_cmd((uint8 *)rsi_frameCmdWebpageClearFiles, 
                            (uint8*)clear, sizeof(rsi_tfs_clear_files_t));
    return retval;
}
