/**
 * @file       rsi_scheduler.c
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

/**
 * Global Variables
 */
extern RSI_COMMON_APP_CB_T rsi_common_app_cb;
 
/*====================================================*/
/**
 * @fn          UINT16 rsi_coex_scheduler_init(RSI_SCHEDULER_INFO_T scheduler_info)
 * @brief       Common function for all the commands.
 * @param[in]   RSI_SCHEDULER_INFO_T scheduler_info, contains scheduler info(Event Map and Event Mask)
 * @return      void
 * @section description 
 * This is a common function used to to do scheduler init.
 */
void rsi_coex_scheduler_init(RSI_SCHEDULER_INFO_T *scheduler_info)
{
	scheduler_info->event_map = 0x0;
	scheduler_info->mask_map = 0xFFFFFFFF;
  return;
}

/*====================================================*/
/**
 * @fn          void rsi_coex_scheduler(RSI_SCHEDULER_INFO_T *scheduler_info)
 * @brief       Common function for all the commands.
 * @param[in]   RSI_SCHEDULER_INFO_T *scheduler_info,event_map and event mask
 * @return      void
 * @section description 
 * This is a common function used to schedule the events.
 */
 volatile int rsi_schdulr_init_done=1;
void rsi_coex_scheduler(RSI_SCHEDULER_INFO_T *scheduler_info)
{
  UINT32 active_int_event_map;
  UINT32 event_no;
  RSI_EVENT_CB_T *temp_event;
  rsi_schdulr_init_done=0;	
    while((active_int_event_map = (scheduler_info->event_map & 
            scheduler_info->mask_map)))
    {
      event_no = rsi_find_event(active_int_event_map);
      temp_event = &rsi_common_app_cb.event_list[event_no];
      if(temp_event->event_handler)
      {
        temp_event->event_handler();
      }
      else 
      {
        while(1); //If Unregistered Events are raised, event handler is NULL
      }

    }
#ifdef WINDOWS
    Sleep(30);
#endif
}
