/**
 * @file       rsi_event.c
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
 * @fn          void rsi_set_event(UINT32 event_num)
 * @brief       Common function for all the commands.
 * @param[in]   UINT32 event_num
 * @return      void
 * @section description 
 * This is a common function used to set an event.
 */
void rsi_set_event(UINT32 event_num)
{
	rsi_common_app_cb.scheduler_info.event_map |= BIT(event_num);
	return;
}

/*====================================================*/
/**
 * @fn          void rsi_clear_event(UINT32 event_num)
 * @brief       Common function for all the commands.
 * @param[in]   UINT32 event_num
 * @return      void
 * @section description 
 * This is a common function used to set an event.
 */
void rsi_clear_event(UINT32 event_num)
{
	rsi_common_app_cb.scheduler_info.event_map &= ~BIT(event_num);
	return;
}

/*====================================================*/
/**
 * @fn          void rsi_mask_event(UINT32 event_num)
 * @brief       Common function for all the commands.
 * @param[in]   UINT32 event_num
 * @return      void
 * @section description 
 * This is a common function used to mask an event.
 */
void rsi_mask_event(UINT32 event_num)
{
	rsi_common_app_cb.scheduler_info.mask_map &= ~BIT(event_num);
	return;
}

/*====================================================*/
/**
 * @fn          void rsi_unmask_event(UINT32 event_num)
 * @brief       Common function for all the commands.
 * @param[in]   UINT32 event_num
 * @return      void
 * @section description 
 * This is a common function used to unmask an event.
 */
void rsi_unmask_event(UINT32 event_num)
{
	rsi_common_app_cb.scheduler_info.mask_map |= BIT(event_num);
	return;
}

/*====================================================*/
/**
 * @fn          void rsi_find_event(UINT32 event_num)
 * @brief       Common function for all the commands.
 * @param[in]   UINT32 event_num
 * @return      void
 * @section description 
 * This is a common function find the active event.
 */
UINT32 rsi_find_event(UINT32 event_map)
{
  UINT8 i;

  for(i=0 ; i<RSI_MAX_NUM_EVENTS ; i++)
  {
    if(event_map & BIT(i))
    {
      break;
    }
  }
  return i;
}

/*====================================================*/
/**
 * @fn          UINT16 rsi_register_event(UINT32 event_id, void (*event_handler_ptr)(void))
 * @brief       Common function for all the commands.
 * @param[in]   UINT32 event_num
 * @param[in]   void (*event_handler_ptr)(void)
 * @return      
 *                1= error
 *                0= Success
 * @section description 
 * This is a common function used to register an event.
 */
UINT16 rsi_register_event(UINT32 event_id, void (*event_handler_ptr)(void))
{
  if((event_id > RSI_MAX_NUM_EVENTS) || (rsi_common_app_cb.event_list[event_id].event_handler != NULL))
  {
    /*
     *Return , if the event number exceeds the RSI_MAX_NUM_EVENTS ,or
     * the event is already registered
     */
#ifdef RSI_DEBUG_PRINT
    RSI_DPRINT(RSI_PL14,"\nInvalid Event Registration:\n");
#endif
    return 1;
  }

  rsi_common_app_cb.event_list[event_id].event_handler = event_handler_ptr;
	return 0;
}

/*====================================================*/
/**
 * @fn          void rsi_mask_tx_events()
 * @brief       This is used to mask tx event.
 * @return      void
 * @section description 
 * This function masks the tx event. 
 */
void rsi_mask_tx_events()
{
  rsi_mask_event(RSI_TX_EVENT);
}

/*====================================================*/
/**
 * @fn          void rsi_unmask_tx_events()
 * @brief       This is used to unmask tx event.
 * @return      void
 * @section description 
 * This function unmasks the tx event. 
 */
void rsi_unmask_tx_events()
{
  rsi_unmask_event(RSI_TX_EVENT);
}


/*====================================================*/
/**
 * @fn          void rsi_chk_tx_event(void)
 * @brief       Common function for all the commands.
 * @param[in]   uint32_t event_num
 * @return      uint8_t  
 *              1:Event set
 *              0:Event not set
 * @section description 
 * This is a common function used to check the TX event.
 */
UINT8 rsi_chk_tx_event(void)
{
	return (rsi_common_app_cb.scheduler_info.event_map & BIT(RSI_TX_EVENT));
}


/*====================================================*/
/**
 * @fn          void rsi_mask_queue(PKT_QUEUE_T *rcv_queue)
 * @brief       Common function maks wlan queue.
 * @param[in]   PKT_QUEUE_T *rcv_queue
 * @return      none  
 * @section description 
 * This is a common function used to wlan queue.
 */
void rsi_mask_queue(PKT_QUEUE_T *rcv_queue)
{

  rcv_queue->queue_mask =1;
}

/*====================================================*/
/**
 * @fn          void rsi_unmask_queue(PKT_QUEUE_T *rcv_queue)
 * @brief       Common function maks wlan queue.
 * @param[in]   none
 * @return      none  
 * @section description 
 * This is a common function used to wlan queue.
 */
void rsi_unmask_queue(PKT_QUEUE_T *rcv_queue)
{

  rcv_queue->queue_mask =0;
}

/*====================================================*/
/**
 * @fn          void rsi_mask_protocol_events()
 * @brief       This is used to mask tx event.
 * @return      void
 * @section description 
 * This function masks the tx event. 
 */
void rsi_mask_protocol_events()
{
  rsi_mask_event(RSI_WLAN_EVENT);
  rsi_mask_event(RSI_BT_OR_ZB_EVENT);
}

/*====================================================*/
/**
 * @fn          void rsi_umask_protocol_events()
 * @brief       This is used to mask tx event.
 * @return      void
 * @section description 
 * This function masks the tx event. 
 */
void rsi_unmask_protocol_events()
{
  rsi_unmask_event(RSI_WLAN_EVENT);
  rsi_unmask_event(RSI_BT_OR_ZB_EVENT);
}

