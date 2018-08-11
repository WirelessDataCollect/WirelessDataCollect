/**
 * @file        rsi_json_create.c
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
 * @brief Create JSON Object: This function is used to create a JSON object
 *
 * @section Description
 * This file contains the function to create a JSON Object that is associated
 * with a webpage.
 *
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"
#include "sensor_data.h"

#if (!RSI_TCP_IP_BYPASS & JSON_LOAD)
/**
 * Global Variables
 */

/*==============================================*/
/**
 * @fn             int16 rsi_json_create(rsi_jsonCreateObject_t* obj)
 * @brief          Erases all files in the webpage file system
 * @param[in]      obj -> the structure representing the json filename & string
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
 * This API creates a JSON Object that will be associated with a webpage.
 */
int16 rsi_json_create(rsi_jsonCreateObject_t* obj, uint8* json_string_buffer, uint8* json_load_done)
{
    int16           retval     =  0;
    uint16          total_len  =  0;
    uint16          curr_len   =  0;
    static uint16   offset;


#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL3,"\r\nJSON Create Start");
#endif

    total_len = strlen((const char *)json_string_buffer);
    curr_len  = (total_len > JSON_CHUNK_LEN) ? JSON_CHUNK_LEN : total_len;

    //!Initialize both length parameters 
    *(uint16*) (obj->total_length)   = total_len;
    *(uint16*) (obj->current_length) = curr_len;

    //! Filename is already initialized, so copy content now 
    memcpy((uint8*)(obj->json_data), json_string_buffer + offset, curr_len);

#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL3,"\r\nTotal, Current, Offset: %d, %d, %d\n", total_len, curr_len, offset);
#endif

    //! Send the Command 
    retval = rsi_execute_cmd((uint8 *)rsi_frameCmdJSONCreate, 
                             (uint8*)obj, sizeof(rsi_jsonCreateObject_t));

    //!Update the offset
    offset += curr_len;

    if (offset == total_len) {
        offset = 0;
        *json_load_done = 1;
    }

    return retval;
}
#endif
