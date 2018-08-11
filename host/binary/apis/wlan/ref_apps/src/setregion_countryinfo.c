/**
 * @file     setregion_countryinfo.c
 * @version  1.0
 * @date     2014-July-09
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
#include "setregion_countryinfo.h"

#if SET_REGION_AP_SUPPORT

/*====================================================*/
/**
 * @fn             void extract_setregionap_country_info(rsi_usetregion_ap_t *ptr_setreg_ap)
 * @brief          Initializes the parameters used in set region ap command
 * @param[in]      rsi_usetregion_ap_t *ptr_setreg_ap, pointer to the global parameter structure
 * @param[out]     none
 * @return         none
 *                 
 * @description	
	* This function is used to initialize the global parameter structure with parameters
 * used in set region ap command based on the region.
 * 
 */
void extract_setregionap_country_info(rsi_usetregion_ap_t *ptr_setreg_ap)
{
  //! The given domain rules are generic rules for some of the countries
  //! USER can configure the domain regulations for the respective countries
  uint8 region_code;

  if(!strcmp(RSI_COUNTRY_CODE,"US "))
  region_code = REGION_US;
  else if(!strcmp(RSI_COUNTRY_CODE,"EU "))
  region_code = REGION_EU;
  else if(!strcmp(RSI_COUNTRY_CODE,"JP "))
  region_code = REGION_JP;
  else if(!strcmp(RSI_COUNTRY_CODE,"SG "))
  region_code = REGION_SINGAPORE;
  else if(!strcmp(RSI_COUNTRY_CODE,"KR "))
  region_code = REGION_KOREA;


  switch(region_code)
  {
  case REGION_US:
  {

    if(RSI_BAND == RSI_BAND_2P4GHZ)
    {
       rsi_uint32_to_4bytes(ptr_setreg_ap->setRegionApFrameSnd.no_of_rules, 1);
       ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].first_channel= 1;
       ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].no_of_channels= 11;
       ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].max_tx_power= 27;
    }
    else
    {
      rsi_uint32_to_4bytes(ptr_setreg_ap->setRegionApFrameSnd.no_of_rules, 5);
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].first_channel= 36;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].no_of_channels= 4;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].max_tx_power= 16;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[1].first_channel= 52;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[1].no_of_channels= 4;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[1].max_tx_power= 23;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[2].first_channel= 100;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[2].no_of_channels= 5;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[2].max_tx_power= 23;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[3].first_channel= 132;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[3].no_of_channels= 3;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[3].max_tx_power= 23;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[4].first_channel= 149;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[4].no_of_channels= 5;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[4].max_tx_power= 29;

    }
  }
  break;
  case REGION_EU:
  {
    if(RSI_BAND == RSI_BAND_2P4GHZ)
    {
      rsi_uint32_to_4bytes (ptr_setreg_ap->setRegionApFrameSnd.no_of_rules, 1);
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].first_channel= 1;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].no_of_channels= 13;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].max_tx_power= 20;
    }
    else
    {
      rsi_uint32_to_4bytes (ptr_setreg_ap->setRegionApFrameSnd.no_of_rules, 3);
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].first_channel= 36;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].no_of_channels= 4;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].max_tx_power= 23;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[1].first_channel= 52;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[1].no_of_channels= 4;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[1].max_tx_power= 23;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[2].first_channel= 100;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[2].no_of_channels= 11;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[2].max_tx_power= 30;

    }


  }
  break;
  case REGION_JP:
  {
    if(RSI_BAND == RSI_BAND_2P4GHZ)
    {
      rsi_uint32_to_4bytes (ptr_setreg_ap->setRegionApFrameSnd.no_of_rules, 1);
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].first_channel= 1;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].no_of_channels= 14;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].max_tx_power= 20;
    }
    else
    {
      rsi_uint32_to_4bytes (ptr_setreg_ap->setRegionApFrameSnd.no_of_rules, 3);
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].first_channel= 36;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].no_of_channels= 4;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].max_tx_power= 20;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[1].first_channel= 52;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[1].no_of_channels= 4;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[1].max_tx_power= 20;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[2].first_channel= 100;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[2].no_of_channels= 11;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[2].max_tx_power= 30;

    }

  }
  break;

  case REGION_SINGAPORE:

  {
    if(RSI_BAND == RSI_BAND_2P4GHZ)
    {
       rsi_uint32_to_4bytes (ptr_setreg_ap->setRegionApFrameSnd.no_of_rules, 1);
       ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].first_channel= 1;
       ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].no_of_channels= 13;
       ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].max_tx_power= 27;
    }
    else
    {
      rsi_uint32_to_4bytes (ptr_setreg_ap->setRegionApFrameSnd.no_of_rules, 5);
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].first_channel= 36;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].no_of_channels= 4;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].max_tx_power= 16;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[1].first_channel= 52;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[1].no_of_channels= 4;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[1].max_tx_power= 23;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[2].first_channel= 100;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[2].no_of_channels= 5;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[2].max_tx_power= 23;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[3].first_channel= 132;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[3].no_of_channels= 3;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[3].max_tx_power= 23;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[4].first_channel= 149;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[4].no_of_channels= 4;
      ptr_setreg_ap->setRegionApFrameSnd.channel_info[4].max_tx_power= 29;

    }
  }
  break;
  case REGION_KOREA:
      {
        if(RSI_BAND == RSI_BAND_2P4GHZ)
        {
           rsi_uint32_to_4bytes (ptr_setreg_ap->setRegionApFrameSnd.no_of_rules, 1);
           ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].first_channel= 1;
           ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].no_of_channels= 13;
           ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].max_tx_power= 27;
        }
        else
        {
          rsi_uint32_to_4bytes (ptr_setreg_ap->setRegionApFrameSnd.no_of_rules, 1);
          ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].first_channel= 149;
          ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].no_of_channels= 4;
          ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].max_tx_power= 29;

        }
      }

  break;
  default :
    {
      if(RSI_BAND == RSI_BAND_2P4GHZ)
        {
           rsi_uint32_to_4bytes (ptr_setreg_ap->setRegionApFrameSnd.no_of_rules, 1);
           ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].first_channel= 1;
           ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].no_of_channels= 11;
           ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].max_tx_power= 27;
        }
        else
        {
          rsi_uint32_to_4bytes (ptr_setreg_ap->setRegionApFrameSnd.no_of_rules, 5);
          ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].first_channel= 36;
          ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].no_of_channels= 4;
          ptr_setreg_ap->setRegionApFrameSnd.channel_info[0].max_tx_power= 16;
          ptr_setreg_ap->setRegionApFrameSnd.channel_info[1].first_channel= 52;
          ptr_setreg_ap->setRegionApFrameSnd.channel_info[1].no_of_channels= 4;
          ptr_setreg_ap->setRegionApFrameSnd.channel_info[1].max_tx_power= 23;
          ptr_setreg_ap->setRegionApFrameSnd.channel_info[2].first_channel= 100;
          ptr_setreg_ap->setRegionApFrameSnd.channel_info[2].no_of_channels= 5;
          ptr_setreg_ap->setRegionApFrameSnd.channel_info[2].max_tx_power= 23;
          ptr_setreg_ap->setRegionApFrameSnd.channel_info[3].first_channel= 132;
          ptr_setreg_ap->setRegionApFrameSnd.channel_info[3].no_of_channels= 3;
          ptr_setreg_ap->setRegionApFrameSnd.channel_info[3].max_tx_power= 23;
          ptr_setreg_ap->setRegionApFrameSnd.channel_info[4].first_channel= 149;
          ptr_setreg_ap->setRegionApFrameSnd.channel_info[4].no_of_channels= 5;
          ptr_setreg_ap->setRegionApFrameSnd.channel_info[4].max_tx_power= 29;

        }
      }
    break;

  }



}
#endif
