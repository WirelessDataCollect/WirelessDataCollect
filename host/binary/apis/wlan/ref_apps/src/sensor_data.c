/**
 * @file     sensor_data.c
 * @version  1.0
 * @date     2014-April-09
 *
 * Copyright(C) Redpine Signals 2014
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief Example usage for Application data to displayed over webpage
 * 
 * @section Description
 * This file contains the implementation of data structures & APIs used to model some
 * sample application data that can be stored in the module & displayed embedded in
 * a webpage. This file also utilizes the JSON parser to convert to & from JSON
 * representation of data.
 *
 *
 */

 /**
 * Includes
 */
#include "rsi_global.h"
#include "rsi_api.h"
#include "sensor_data.h"
#include <stdio.h>
#include <stdlib.h>

/* API Functions */
uint8* sensor_data_stringify(uint8* json, app_data_t* sensor_data)
{
    /* IMPORTANT: Keys are always enclosed in double quotes.
       Use same keys as used in the webpage!
    */
    sprintf((char *)json,
        "{\"temp\":%d,\"accx\":%d,\"accy\":%d,\"accz\":%d,\"cbox1\":%s,\"cbox2\":%s,\"radio1\":%d}",
        sensor_data->temperature,
        sensor_data->accelerometer_x,
        sensor_data->accelerometer_y,
        sensor_data->accelerometer_z,
        (sensor_data->checkbox_1 == 1 ? "true" : "false"),
        (sensor_data->checkbox_2 == 1 ? "true" : "false"),
        sensor_data->radio_selection
        );

    return json;
}

/* This function is used to initialize the structure with default values
   These values can be retrieved from sensors or something similar
 */
void sensor_data_init(app_data_t* sensor_data)
{
    sensor_data->temperature      =  26;
    sensor_data->accelerometer_x  =  3;
    sensor_data->accelerometer_y  =  6;
    sensor_data->accelerometer_z  =  2;
    sensor_data->checkbox_1       =  1;
    sensor_data->checkbox_2       =  0;
    sensor_data->radio_selection  =  1;
}

/* This function is used to update the sensor data structure with the updates
   received from the browser.
 */
uint8 sensor_data_update(app_data_t* sensor_data, uint8* json)
{
    uint8   filename[24] =  "";
    uint8   send_update  =  0;

    /* Extract the filename from the structure */
    json = json_extract_filename(json, filename);

    /* Check if its our object */
    if (strcmp((const char*)filename, JSON_FILENAME) == 0) {

        sensor_data_update_helper(sensor_data, json);
        
        /* If both check boxes are enabled, reset the data structure */
        if (sensor_data->checkbox_1 && sensor_data->checkbox_2) {
            sensor_data_init(sensor_data);
            send_update = 1;
        }
    }

    /* This boolean indicates whether the host needs to push some updated JSON
       data to the module. */
    return send_update;
}


/* Helper functions */

/* Helper function which actually performs the update */
void sensor_data_update_helper(app_data_t* sensor_data, uint8* json)
{
    /* Extract temp value from it & update the struct */
    json_extract_int(json, (uint8 *)"temp", &(sensor_data->temperature));

    /* Extract accelerometer values */
    json_extract_int(json, (uint8 *)"accx", &(sensor_data->accelerometer_x));
    
    /* Extract accelerometer int_vals */
    json_extract_int(json,(uint8 *) "accy", &(sensor_data->accelerometer_y));
    
    /* Extract accelerometer int_vals */
    json_extract_int(json, (uint8 *)"accz", &(sensor_data->accelerometer_z));

    /* Extract checkbox_1 value */
    json_extract_boolean(json, (uint8 *)"cbox1", &(sensor_data->checkbox_1));
    
    /* Extract checkbox_2 value */
    json_extract_boolean(json,(uint8 *) "cbox2", &(sensor_data->checkbox_2));
    
    /* Extract radio button value */
    json_extract_int(json,(uint8 *) "radio1", &(sensor_data->radio_selection));
}

/* This function is used to extract filename out of the received json update data. */
uint8* json_extract_filename(uint8* json, uint8* buffer)
{
    uint8  c;
    uint8  i  =  0;

    while (i < 24) {

        /* Get character */
        c = json[i];

        if (c != ',')
            buffer[i] = c;
        else
            break;

        ++i;
    }

    buffer[i] = '\0';

    return &json[i+1];
}


void json_extract_int(uint8* json, uint8* key, int* val)
{
    uint8*  key_pos     =  NULL;
    uint16  key_len     =  0;
    int     target      =  0;
    char    buffer[20]  =  "";
    uint8   c           =  0;
    uint8   i           =  0;

    /* Get position of key */
    key_pos = (uint8 *)strstr((const char *)json, (const char *)key);

    /* If key matches */
    if (key_pos != NULL) {

        key_len = strlen((const char*)key);
        key_pos += (key_len + 1);

        /* Extract the value */
        if (*key_pos == ':') {

            key_pos++;
            c = *key_pos;

            while (is_int(c)) {
                buffer[i] = c;
                i++; key_pos++;
                c = *key_pos;
            }

            buffer[i] = '\0';

            target = atoi(buffer);
            *val = target;
        }
    }
}

void json_extract_float(uint8* json, uint8* key, float* val)
{
    uint8*  key_pos     =  NULL;
    uint16  key_len     =  0;
    float   target      =  0;
    char    buffer[20]  =  "";
    uint8   c           =  0;
    uint8   i           =  0;

    /* Get position of key */
    key_pos = (uint8 *)strstr((const char *)json, (const char *)key);

    /* If key matches */
    if (key_pos != NULL) {

        key_len = strlen((const char *)key);
        key_pos += (key_len + 1);


        /* Extract the value */
        if (*key_pos == ':') {

            key_pos++;
            c = *key_pos;

            while (is_float(c)) {
                buffer[i] = c;
                i++; key_pos++;
                c = *key_pos;
            }

            buffer[i] = '\0';

            target = atof(buffer);
            *val = target;
        }
    }
}

void json_extract_boolean(uint8* json, uint8* key, int* val)
{
    uint8*  key_pos     =  NULL;
    uint16  key_len     =  0;
    uint8   target      =  0;
    uint8   c           =  0;
    uint8   i           =  0;

    /* Get position of key */
    key_pos = (uint8 *)strstr((const char *)json,(const char *)key);

    /* If key matches */
    if (key_pos != NULL) {

        key_len = strlen((const char *)key);
        key_pos += (key_len + 1);

        /* Extract the value */
        if (*key_pos == ':') {

            key_pos++;
            c = *key_pos;

            while (c != 't' && c != 'f') {
                i++; key_pos++;
                c = *key_pos;
            }


            target = (c == 't');
            *val = target;
        }
    }
}

int is_int(uint8 c)
{
    return (c == '0') || (c == '1') || (c == '2') || (c == '3') ||
           (c == '4') || (c == '5') || (c == '6') || (c == '7') ||
           (c == '8') || (c == '9') || (c == '-');

}

int is_float(uint8 c)
{
    return (c == '0') || (c == '1') || (c == '2') || (c == '3') ||
           (c == '4') || (c == '5') || (c == '6') || (c == '7') ||
           (c == '8') || (c == '9') || (c == '.') || (c == '-');
}
