/**
 * @file        rsi_json_erase_file.c
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
 * @brief Erase Webpage File: This function erases one json file in the file system
 *
 * @section Description
 * This file contains the function to erase one json file present in the
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
 * @fn             int16 rsi_json_erase_file(void)
 * @brief          Erases all files in the json file system
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
 * This API erases one json file present in the file system.
 */
int16 rsi_json_erase_file(rsi_tfs_erase_file_t* file)
{
    int16                   retval;

#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL3,"\r\nJSON erase file Start");
#endif
    retval = rsi_execute_cmd((uint8 *)rsi_frameCmdJSONEraseFile,
                             (uint8 *)file, sizeof(rsi_tfs_erase_file_t));
    return retval;
}
