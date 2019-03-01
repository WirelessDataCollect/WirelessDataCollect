/**
 * @file       rsi_multicast_filter.c
 * @version    1.0
 * @date       2014-Mar-03
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief Multicast filter: Multicast filtering 
 *
 * @section Description
 * This file contains the functions to send  multicast mac address to filter and supporting functions
 *
 *
 */


/**
 * Includes
 */
#include "rsi_global.h"


/*==============================================*/
/**
 * @fn          lmac_crc8_c 
 * @brief       This function is a crc function 
 *              6 bit value
 * @param[in]   uint8   crc byte input 
 * @param[in]   uint8   accumulated crc
 * @param[in]   uint8   last byte crc
 * @param[out]  uint8   6bit crc 
 *                 
 * @section description 
 * This API is used to calcuste crc for given byte and accumulate crc.
 */
uint8 lmac_crc8_c(uint8 crc8_din, uint8 crc8_state, uint8 end)
{
    uint8  din     [8] ;
    uint8  state   [8] ;
    uint8  state_c [8] ;
    uint8  crc8_out    ;

    din[0] = ((crc8_din & BIT(7)) >> 7) ;
    din[1] = ((crc8_din & BIT(6)) >> 6) ;
    din[2] = ((crc8_din & BIT(5)) >> 5) ;
    din[3] = ((crc8_din & BIT(4)) >> 4) ;
    din[4] = ((crc8_din & BIT(3)) >> 3) ;
    din[5] = ((crc8_din & BIT(2)) >> 2) ;
    din[6] = ((crc8_din & BIT(1)) >> 1) ;
    din[7] = ((crc8_din & BIT(0)) >> 0) ;

    state[0] = ((crc8_state & BIT(0)) >> 0) ;
    state[1] = ((crc8_state & BIT(1)) >> 1) ;
    state[2] = ((crc8_state & BIT(2)) >> 2) ;
    state[3] = ((crc8_state & BIT(3)) >> 3) ;
    state[4] = ((crc8_state & BIT(4)) >> 4) ;
    state[5] = ((crc8_state & BIT(5)) >> 5) ;
    state[6] = ((crc8_state & BIT(6)) >> 6) ;
    state[7] = ((crc8_state & BIT(7)) >> 7) ;

    state_c[7] = (state[7]^din[7])^(state[6]^din[6])^
                    (state[5]^din[5]);
    
    state_c[6] = (state[6]^din[6])^(state[5]^din[5])^
                    (state[4]^din[4]);

    state_c[5] = (state[5]^din[5])^(state[4]^din[4])^
                    (state[3]^din[3]);

    state_c[4] = (state[4]^din[4])^(state[3]^din[3])^
                    (state[2]^din[2]);
    
    state_c[3] = (state[1]^din[1])^(state[2]^din[2])^
                    (state[3]^din[3])^(state[7]^din[7]);

    state_c[2] = (state[0]^din[0])^(state[1]^din[1])^
                    (state[2]^din[2])^(state[6]^din[6]);

    state_c[1] = (state[0]^din[0])^(state[1]^din[1])^
                    (state[6]^din[6]);
   
    state_c[0] = (state[0]^din[0])^(state[7]^din[7])^
                    (state[6]^din[6]);    
    if(!end){
      crc8_out =    
        ((state_c[0] & BIT(0)) << 0)
        | ((state_c[1] & BIT(0)) << 1)
        | ((state_c[2] & BIT(0)) << 2)
        | ((state_c[3] & BIT(0)) << 3)
        | ((state_c[4] & BIT(0)) << 4)
        | ((state_c[5] & BIT(0)) << 5)
        | ((state_c[6] & BIT(0)) << 6)
        | ((state_c[7] & BIT(0)) << 7)
        ;
    }
    else{
      crc8_out =    
        ((state_c[7] & BIT(0)) << 0)
        | ((state_c[6] & BIT(0)) << 1)
        | ((state_c[5] & BIT(0)) << 2)
        | ((state_c[4] & BIT(0)) << 3)
        | ((state_c[3] & BIT(0)) << 4)
        | ((state_c[2] & BIT(0)) << 5);

         crc8_out = ~crc8_out;
         crc8_out &= 0x3f; 
    }
    return(crc8_out);
}

/*==============================================*/
/**
 * @fn          multicast_mac_hash 
 * @brief       This function is to calculate 6bit hash value for given mac address 
 * @param[in]   uint8   pointer to mac address 
 * @param[out]  uint8   6bit hash value 
 *                 
 * @section description 
 * This API is used to calculate 6bit hash value from given mac address.
 */

uint8 multicast_mac_hash(uint8 *mac)
{
  uint8 i, crc = 0xff;
  for(i=0; i<6 ; i++){
    crc = lmac_crc8_c(mac[i],crc, ((i == 5)?1:0));
  }
  return (crc);
}

/*===========================================================================
 *
 * @fn          int16 rsi_multicast_mac_filter(uint8 cmd, uint8 MAC)
 * @brief       Sends the multicast filter bitmap to the Wi-Fi module
 * @param[in]   uint8 cmd LS 2 bits are used as command and possible values are
 *              0 = RSI_MULTICAST_MAC_ADD_BIT
 *              1 = RSI_MULTICAST_MAC_CLEAR_BIT
 *              2 = RSI_MULTICAST_MAC_CLEAR_ALL
 *              3 = RSI_MULTICAST_MAC_SET_ALL
 * @param[in]   uint8 MAC[6] , Multicast MAC address to be filter
 * @param[out]  none
 * @return      errCode
 *              SPI:
 *              -1 = SPI busy / Timeout
 *              -2 = SPI Failure
 *              -3 = BUFFER FULL
 *              0  = SUCCESS
 *              UART/USB/USB-CDC:
 *              -2 = Command issue failed
 *              0  = SUCCESS
 * @section description 
 * This API is used to set/reset the Multicast MAC address bitmap to filter multicast packets. This API should be called only 
 * after the rsi_init API.
 *
 * @section prerequisite 
 * rsi_init should be done successfully  
 */

int16 rsi_multicast_mac_filter(uint8 cmd, uint8 MAC[6])
{
  int16       retval;
  uint16      uMcastBitMapFrame;

#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL3,"\r\n\nMac Filter Start ");
#endif
  uMcastBitMapFrame = (uint16)(cmd);
  if((cmd == RSI_MULTICAST_MAC_ADD_BIT) || (cmd == RSI_MULTICAST_MAC_CLEAR_BIT)){
    uMcastBitMapFrame |= (multicast_mac_hash(MAC) << 8);//返回一个6bit的hash
  }
  retval = rsi_execute_cmd((uint8 *)rsi_frameCmdMcastFilter, (uint8 *)&uMcastBitMapFrame, 2);
  return retval;
}


