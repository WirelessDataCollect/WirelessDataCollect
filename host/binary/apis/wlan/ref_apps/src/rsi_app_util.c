/**
 * @file            rsi_app_util.c
 * @version         3.6
 * @date            2013-June-16
 *
 * Copyright(C) Redpine Signals 2013
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file. 
 *
 * @brief UTIL: Generic util functions such as swapping which are not tied to anything.
 *
 * @section Description
 * This file implements misc utilities/functions.
 *
 * @section Improvements
 * asciihex_2_num() function is added.
 */


/**
 * Include files
 */
#include "rsi_global.h"
#include "rsi_app_util.h"
#ifdef WLAN_ENABLE
#include "rsi_app.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**
 * Global defines
 */

#if 0
/*================================================*/
/**
 * @fn             void rsi_print_n_chars (char* st, int n)
 * @brief          Print n characters from the string passed
 * @param[in]      char* st,string to print from
 * @param[in]      int n,number of characters to print
 * @param[out]     none
 * @return         none
 */
void rsi_print_n_chars (int8* st, int16 n)
{
   int16         i;

   for (i = 0; i < n; i++) {
      putchar(st[i]);
   }
}

#endif


/*=============================================================================*/
/**
 * @fn             int8 * rsi_bytes6_to_ascii_mac_addr(uint8 *hexAddr)
 * @brief          Convert an uint8 6-Byte array to  : notation MAC address
 * @param[in]      uint8 *hexAddress, Address to convert
 * @param[in]      uint8 *strBuf, pointer to a dummy String to hold the MAC address
 * @param[out]     none
 * @return         int8 * destString, pointer to the string with the data
 */
int8 * rsi_bytes6_to_ascii_mac_addr(uint8 *hexAddr,uint8 *strBuf)
{
   uint8         i;                  //! loop counter
   uint8         cBuf[3];            //! character buffer
   uint8         *destString;

   strBuf[0] = 0;                     //! make  strcat think the array is empty
   for (i = 0; i < 5; i++) {          //! MAC Address is 6 bytes long
      //! This will take care of the first5 bytes
      sprintf ((char *)cBuf, "%02x", (((uint8*)hexAddr)[i]));
      cBuf[2] = 0;                     //! terminate the string
      destString =(uint8 *) strcat((char *)strBuf,(char *) cBuf);
      destString = (uint8 *)strcat((char *)strBuf, (char *)":");
   }
   //! take care of the last entry outside the loop, there is no . after the last octet
   sprintf ((char *)cBuf, "%02x", (((uint8*)hexAddr)[i]));
   cBuf[2] = 0;                                             
   //! terminate the string
   destString = (uint8 *)strcat((char *)strBuf,(char *) cBuf);
   return (int8 *) destString;
}


/*=============================================================================*/
/**
 * @fn             void rsi_swap_2bytes(uint8 *buffer)
 * @brief          swap the first 2 bytes of an array
 * @param[in]      uint8 *buffer,pointer to buffer of data to convert
 * @param[out]     none
 * @return         value returned in the array passed
 */
void rsi_swap_2bytes(uint8 *buffer)
{
   uint8         tmp;

   tmp = buffer[0];
   buffer[0] = buffer[1];
   buffer[1] = tmp;
}


/*=============================================================================*/
/**
 * @fn             void rsi_swap_4bytes(uint8 *buffer)
 * @brief          swap the byte order of a 4 Byte array
 * @param[in]      uint8 *buffer,pointer to buffer of data to convert
 * @param[out]     none
 * @return         value returned in the array passed
 */
void rsi_swap_4bytes(uint8 *buffer)
{
   uint8         tmp;

   tmp = buffer[0];
   buffer[0] = buffer[3];
   buffer[3] = tmp;
   tmp = buffer[1];
   buffer[1] = buffer[2];
   buffer[2] = tmp;
}


/*=============================================================================*/
/**
 * @fn            void rsi_print_uint8_as_binary(uint8 number)
 * @brief         print an uint8 number in binary, as in: 0x31 --> 00110001
 * @param[in]     uint8 number to print
 * @param[out]    none
 * @return        value returned in the array passed
 */
#if 0
void rsi_print_uint8_as_binary(uint8 number)
{
   uint16         i;                  // loop counter

   i = 1<<(sizeof(number) * 8 - 1);


   while (i > 0) {
      if (number & i) {
         printf("1");
      }
      else {
         printf("0");
      }
      i >>= 1;
   }
}
#endif


/*=============================================================================*/
/**
 * @fn             int16 rsi_is_uint8_in_list(uint8 arg, uint8 *list, uint8 nargs)
 * @brief          check if a uint8 number is in a list
 * @param[in]      uint8 arg,number to be checked in the list
 * @param[in]      uint8 *list,list of numbers to check against
 * @param[in]      uint8 nargs,number of arguments
 * @param[out]     none
 * @return         value returned in the array passed
 */
int16 rsi_in_uint8_list(uint8 arg, uint8 *list, uint8 nargs)
{
   int16            retval;       //! return value, TRUE or FALSE
   uint8            i;            //! loop counter

   retval = RSI_FALSE;                                                
   //! start off with a false, if we find a match, then change to a true to return
   for (i = 0; i < nargs; i++) {
      if (arg == list[i]) {
         retval = RSI_TRUE;
         break;
      }
   }

   return retval;
}


/*=============================================================================*/
/**
 * @fn             int8 * rsi_bytes4_to_ascii_dot_addr(uint8 *hexAddr, uint8 *strBuf)
 * @brief          Convert an uint8 4-Byte array to  . notation network address
 * @param[in]      uint8 *hexAddress, Address to convert
 * @param[in]      uint8 *strBuf, String Pointer to hold the Concatenated String
 * @param[out]     none
 * @return         char * destString, pointer to the string with the data
 */
int8 * rsi_bytes4_to_ascii_dot_addr(uint8 *hexAddr,uint8 *strBuf)
{
  uint8         i;                     //! loop counter
  uint8         ii;                    //! loop counter
  int8         cBuf[4];                //! character buffer
  int8         *destString;

  strBuf[0] = 0;                        //! make  strcat think the array is empty
  for (i = 0; i < 3; i++) {             //! we are assuming IPV4, so 4 bytes
    //! This will take care of the first 3 bytes
    //! zero out the character buffer since we don't know how long the string will be
    for(ii = 0; ii < sizeof(cBuf); ii++) { cBuf[ii] = 0; }   
    sprintf ((char *)cBuf, "%d", (((uint8*)hexAddr)[i]));
    destString =(int8 *) strcat((char *)strBuf,(char *) cBuf);
    destString = (int8 *)strcat((char *)strBuf,(char *) ".");
  }
  //! take care of the last entry outside the loop, there is no . after the last octet
  //! zero out the character buffer since we don't know how long the string will be
  for(ii = 0; ii < sizeof(cBuf); ii++) { cBuf[ii] = 0; }      
  sprintf ((char *)cBuf, "%d", (((uint8*)hexAddr)[i]));
  destString = (int8 *) strcat((char *)strBuf,(char *) cBuf);
  return destString;
}

/*=============================================================================*/
/**
 * @fn         int8 asciihex_2_num ( int8 ascii_hex_in)
 * @brief      Convert given ASCII hex notation to descimal notation (used for mac address)
 * @param[in]  int8 ascii_hex_in, byte in ascii hex format
 * @return     value in hex num
 */
 
int8 asciihex_2_num(int8 ascii_hex_in)
{
   if((ascii_hex_in >= '0') && (ascii_hex_in <= '9'))
      return (ascii_hex_in - '0');
   if((ascii_hex_in >= 'A') && (ascii_hex_in <= 'F'))
      return (ascii_hex_in - 'A' + 10);
   if((ascii_hex_in >= 'a') && (ascii_hex_in <= 'f'))      
      return (ascii_hex_in - 'a' + 10);
   
   return 0;
}

/*=============================================================================*/
/**
 * @fn            int8 rsi_charhex_2_dec ( uint8 *cBuf)
 * @brief         Convert given ASCII hex notation to descimal notation (used for mac address)
 * @param[in]     int8 *cBuf, ASCII hex notation string
 * @return        value in integer
 */
int8 rsi_charhex_2_dec ( int8 *cBuf)
{
   int8 k=0;
   uint8 i;
   for(i=0;i<strlen((char*)cBuf);i++)
    {
      k = ((k*16) + asciihex_2_num(cBuf[i])); 
     }
    return k;
}    

/*=============================================================================*/
/**
 * @fn            void rsi_ascii_mac_address_to_6bytes(uint8 *hexAddr, int8 *asciiMacAddress)
 * @brief         Convert an ASCII : notation MAC address to a 6-byte hex address
 * @param[in      int8 *asciiMacFormatAddress, source address to convert, must be a null terminated string
 * @param[out]    uint8 *hexAddr, converted address is returned here 
 * @return        none
 */
void rsi_ascii_mac_address_to_6bytes(uint8 *hexAddr, int8 *asciiMacAddress)
{
  uint8         i;                  //! loop counter
  uint8         cBufPos;            //! which char in the ASCII representation
  uint8         byteNum;            //! which byte in the 32BitHexAddress
  int8         cBuf[6];             //! temporary buffer

  byteNum = 0;
  cBufPos = 0;
  for (i = 0; i < strlen((char *)asciiMacAddress); i++) {
    //! this will take care of the first 5 octets
    if (asciiMacAddress[i] == ':') {      //! we are at the end of the address octet
      cBuf[cBufPos] = 0;                  //! terminate the string
      cBufPos = 0;                        //! reset for the next char
      hexAddr[byteNum++] = (uint8)rsi_charhex_2_dec((int8 *)cBuf);   //! convert the strint to an integer
    }
    else {
      cBuf[cBufPos++] = asciiMacAddress[i];
    }
  }
  //! handle the last octet                  //! we are at the end of the string with no .
  cBuf[cBufPos] = 0x00;                     //! terminate the string
  hexAddr[byteNum] = (uint8)rsi_charhex_2_dec((int8 *)cBuf);      //! convert the strint to an integer
}



/*=============================================================================*/
/**
 * @fn	    		void rsi_ascii_mac_address_to_6Bytes_rev(uint8 *hexAddr, int8 *asciiMacAddress)
 * @brief		    Convert an ASCII : notation MAC address to a 6-byte hex address
 * @param[in		int8 *asciiMacFormatAddress, source address to convert, must be a null terminated string
 * @param[out]	uint8 *hexAddr, converted address is returned here 
 * @return	  	none
 */
void rsi_ascii_mac_address_to_6bytes_rev(uint8 *hexAddr, int8 *asciiMacAddress)
{
  uint8			i;						  //! loop counter
  uint8		  cBufPos;				//! which char in the ASCII representation
  uint8			byteNum;				//! which byte in the 32BitHexAddress
  int8			cBuf[6];				//! temporary buffer

  byteNum = 5;
  cBufPos = 0;
  for (i = 0; i < strlen((char *)asciiMacAddress); i++) {
    // this will take care of the first 5 octets
    if (asciiMacAddress[i] == ':') {			//! we are at the end of the address octet
      cBuf[cBufPos] = 0;						      //! terminate the string
      cBufPos = 0;							          //! reset for the next char
      hexAddr[byteNum--] = (uint8)rsi_charhex_2_dec((int8 *)cBuf);	//! convert the strint to an integer
    }
    else {
      cBuf[cBufPos++] = asciiMacAddress[i];
    }
  }
  // handle the last octet						//! we are at the end of the string with no .
  cBuf[cBufPos] = 0x00;							  //! terminate the string
  hexAddr[byteNum] = (uint8)rsi_charhex_2_dec((int8 *)cBuf);		//! convert the strint to an integer
}



/*=============================================================================*/
/**
 * @fn            void rsi_ascii_dot_address_to_4bytes(uint8 *hexAddr, int8 *asciiDotAddress)
 * @brief         Convert an ASCII . notation network address to 4-byte hex address
 * @param[in]     int8 *asciiDotFormatAddress, source address to convert, must be a null terminated string
 * @param[out]    uint8 *hexAddr,   Output value is passed back in the 4-byte Hex Address
 * @return        none
 */
void rsi_ascii_dot_address_to_4bytes(uint8 *hexAddr, int8 *asciiDotAddress)
{
  uint8         i;                                             
  //! loop counter
  uint8         cBufPos;                                       
  //! which char in the ASCII representation
  uint8         byteNum;                                       
  //! which byte in the 32BitHexAddress
  int8         cBuf[4];                                       
  //! character buffer

  byteNum = 0;
  cBufPos = 0;
  for (i = 0; i < strlen((char *)asciiDotAddress); i++) {
    //! this will take care of the first 3 octets
    if (asciiDotAddress[i] == '.') {                              
       //! we are at the end of the address octet
      cBuf[cBufPos] = 0;                                       
      //! terminate the string
      cBufPos = 0;                                          
      //! reset for the next char
      hexAddr[byteNum++] = (uint8)atoi((char *)cBuf);                        
      //! convert the strint to an integer
    }
    else {
      cBuf[cBufPos++] = asciiDotAddress[i];
    }
  }
  //! handle the last octet                                       
  //! we are at the end of the string with no .
  cBuf[cBufPos] = 0x00;                                          
  //! terminate the string
  hexAddr[byteNum] = (uint8)atoi((char *)cBuf);                              
  //! convert the strint to an integer
}
#ifdef WLAN_ENABLE
/*=========================================================================*/
/**
 * @fn          void register_socket_protocol(rsi_api  *ptrStrApi)
 * @brief       Register socket information
 * @param[in]   rsi_api  *ptrStrApi,pointer to global parameter structure
 * @param[out]  none
 * @return      none
 *          
 * @section description 
 * This funtion is used to link the socket number with the protocol.
 * It also tags the socket with its protocol. 
 */
void register_socket_protocol(rsi_uSocket *ptrStrApi)
{

  uint16 socket_descriptor = 0;

  //! Get IP version
  uint16 ip_version = rsi_bytes2R_to_uint16(rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.socketFrameRcv.ip_version);

  //! Get socket descriptor
  socket_descriptor  = rsi_bytes2R_to_uint16(rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.socketFrameRcv.socketDescriptor);
  //! ip version
  memcpy((uint8 *)rsi_app_cb.socketsStrArray.socketsArray[socket_descriptor].ip_version, rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.socketFrameRcv.ip_version, 2);
  //! socket descriptor
  memcpy((uint8 *)rsi_app_cb.socketsStrArray.socketsArray[socket_descriptor].socketDescriptor, rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.socketFrameRcv.socketDescriptor, 2);
  //! source port number
  memcpy((uint8 *)rsi_app_cb.socketsStrArray.socketsArray[socket_descriptor].src_port, rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.socketFrameRcv.moduleSocket, 2);
  
  if(ip_version == IP_VERSION_4)
  {
    //! detination ipv4 address
    memcpy((uint8 *)rsi_app_cb.socketsStrArray.socketsArray[socket_descriptor].dest_ip.ipv4_address, ptrStrApi->socketFrameSnd.destIpaddr.ipv4_address, 4);
   
    /* Tag the socket with its protocol in the sockets array structure */
    if (rsi_bytes2R_to_uint16(rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.socketFrameRcv.socketType) == RSI_SOCKET_TCP_CLIENT) 
    {
      rsi_app_cb.socketsStrArray.socketsArray[socket_descriptor].protocol = RSI_PROTOCOL_TCP_V4;
    }
    else if (rsi_bytes2R_to_uint16(rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.socketFrameRcv.socketType) == RSI_SOCKET_TCP_SERVER) 
    {
      rsi_app_cb.socketsStrArray.socketsArray[socket_descriptor].protocol = RSI_PROTOCOL_TCP_V4;
    }
    else if (rsi_bytes2R_to_uint16(rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.socketFrameRcv.socketType) == RSI_SOCKET_UDP_CLIENT) 
    {
      rsi_app_cb.socketsStrArray.socketsArray[socket_descriptor].protocol = RSI_PROTOCOL_UDP_V4;
    }
    else if (rsi_bytes2R_to_uint16(rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.socketFrameRcv.socketType) == RSI_SOCKET_LUDP) 
    {
      rsi_app_cb.socketsStrArray.socketsArray[socket_descriptor].protocol = RSI_PROTOCOL_UDP_V4;
    } 
  }
  else
  {
    //! destination ipv6 address
    memcpy((uint8 *)rsi_app_cb.socketsStrArray.socketsArray[socket_descriptor].dest_ip.ipv6_address, ptrStrApi->socketFrameSnd.destIpaddr.ipv6_address, 16);
    
    /* Tag the socket with its protocol in the sockets array structure */
    if (rsi_bytes2R_to_uint16(rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.socketFrameRcv.socketType) == RSI_SOCKET_TCP_CLIENT) 
    {
      rsi_app_cb.socketsStrArray.socketsArray[socket_descriptor].protocol = RSI_PROTOCOL_TCP_V6;
    }
    else if (rsi_bytes2R_to_uint16(rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.socketFrameRcv.socketType) == RSI_SOCKET_TCP_SERVER) 
    {
      rsi_app_cb.socketsStrArray.socketsArray[socket_descriptor].protocol = RSI_PROTOCOL_TCP_V6;
    }
    else if (rsi_bytes2R_to_uint16(rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.socketFrameRcv.socketType) == RSI_SOCKET_UDP_CLIENT) 
    {
      rsi_app_cb.socketsStrArray.socketsArray[socket_descriptor].protocol = RSI_PROTOCOL_UDP_V6;
    } 
    else if (rsi_bytes2R_to_uint16(rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.socketFrameRcv.socketType) == RSI_SOCKET_LUDP) 
    {
      rsi_app_cb.socketsStrArray.socketsArray[socket_descriptor].protocol = RSI_PROTOCOL_UDP_V6;
    } 

  }
  
  //! destination port
  memcpy((uint8 *)rsi_app_cb.socketsStrArray.socketsArray[socket_descriptor].dest_port, ptrStrApi->socketFrameSnd.destSocket, 2);
}


/*=========================================================================*/
/**
 * @fn          void unregister_socket_protocol(void)
 * @brief       Unregister socket information
 * @param[in]   none
 * @param[out]  none
 * @return      none
 *          
 * @section description 
 * This funtion is used to delink the socket number with the protocol.
 * It also tags the socket with its protocol. 
 */
void unregister_socket_protocol(void)
{

  uint16 socket_descriptor = 0;
  socket_descriptor  = rsi_bytes2R_to_uint16(rsi_app_cb.uCmdRspFrame->uCmdRspPayLoad.socketCloseFrameRcv.socketDsc);
  memset((uint8 *)&rsi_app_cb.socketsStrArray.socketsArray[socket_descriptor], 0, sizeof(rsi_socketsStr));
}
#endif

/*FUNCTION*********************************************************************
Function Name  : rs22_aToi
Description    : This function converts the string to integer
Returned Value : Converted integer value
Parameters     : 

-----------------+-----+-----+-----+------------------------------
Name             | I/P | O/P | I/O | Purpose
-----------------+-----+-----+-----+------------------------------
src              |  X  |     |     | string to be converted to the integer
src_len          |  X  |     |     | len of the string

*END****************************************************************************/

uint16 rs22_aToi(uint8 *src, uint8 src_len)
{
   uint16 src_index = 0;
   uint16 temp = 0;
   
   for(src_index = 0; src_index < src_len; src_index++)
   {
      temp = temp*10;
      temp = temp + (src[src_index] - 0x30);
   }

   return temp;
}

/*=========================================================================*/
/**
 * @fn          uint16 rsi_convert_ip_to_string(uint8 *num_buff, uint8 *ip_buff)
 * @brief       converts  IP address to string
 * @param[in]   source buffer pointer of IP address
 * @param[in]   destination buffer pointer to store the converted IP address
 * @return      none
 * @section description 
 * This function is used to convert ip address to string  
 */
uint16 rsi_convert_ip_to_string(uint8 *num_buff, uint8 *ip_buff)
{
    uint8 temp_buf[8];
   uint8 temp_buf2[8];
   uint16 temp;
   uint16 num_index = 0, ip_index = 0;
   uint16 temp_index = 0, temp_index2 = 0;
    
    
   memset(ip_buff, 0, 17);
   while (num_index < 4)
   {
      temp = num_buff[num_index++];
      

      do
      {
         temp_buf[temp_index++] = (temp%10) + '0';
         temp = temp/10;
         ip_index++;
      }while(temp);
      rsi_strrev(temp_buf, temp_buf2, temp_index);
       rsi_strcat(temp_buf2, ip_buff + temp_index2, temp_index);
      
      temp_index = 0;
        if (num_index < 4)
           ip_buff[ip_index++] = '.';
         temp_index2 = ip_index;
         
   }
   
   return ip_index;
}

/*=========================================================================*/
/**
 * @fn          uint8 rsi_strrev(void *src, void *dst,uint8 len)
 * @brief       This API is used to reverse the given string
 * @param[in]   source buffer pointer
 * @param[in]   destination buffer pointer
 * @param[in]   length of the string 
 * @return      zero
 * @section description 
 * This function is used to reverse the string  
 */
uint8 rsi_strrev(void *src, void *dst, uint8 len)
{
   uint8 *dst1;
   uint8 *src1;
   dst1 = dst;
   src1 = src;
     
   src1 = src1 + len - 1;
     
   while(len-- != 0)
        *dst1++ = *src1--;
   *dst1 = '\0';
   return 0;
}
/*=========================================================================*/
/**
 * @fn          uint16 rsi_strcat(void *src, void *dst,uint8 len)
 * @brief       This API is used to concatinate the two given strings
 * @param[in]   source buffer pointer
 * @param[in]   destination buffer pointer
 * @param[in]   length of the string 
 * @return      none
 * @section description 
 * This function is used to concatinate the source string to 
 * destination string  
 */
void rsi_strcat(void *src, void *dst, uint8 len)
{
   uint8 *dst1;
   uint8 *src1;
   dst1 = dst;
   src1 = src;
  
   while(len-- != 0)
    *dst1++ = *src1++;
   
}
/*=========================================================================*/
/**
 * @fn          uint32 parseHex(uint8 *str)
 * @brief       This API is used tp parse the hex values to the respective decimal values
 * @param[in]   Hex string pointer 
 * @return      decimal value
 * @section description 
 * This function is used to convert the hex value to decimal value
 */
uint32 parseHex(uint8 *str )
{
    uint32 value = 0;
    uint8 i=0;

    for(i= 0 ;i <8 ; i++,++str ) 
      switch( *str )
    {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            value = (value << 4) | (*str & 0xf);
            break;
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
            value = (value << 4 | 9) + (*str & 0xf);
            break;
        case '\0':
        default:
            return value;
    }
   return 0;
}
/*=========================================================================*/
/**
 * @fn          void parse_ipv6_address(uint8 *v,uint8 *buf)
 * @brief       Parse the IPV6 address
 * @param[in]   source IPV6 buffer pointer
 * @param[in]   destination buffer pointer
 * @return      none
 * @section description 
 * This function is used to convert IPV6 Address.
 * destination string  
 */

void parse_ipv6_address(uint8 *v, uint8 *buf)
{
  uint8 value = 0;
  uint8 offset = 0;
  uint8 index = 0;
  uint16 buffer_offset = 0;
  uint8 i = 0;
  uint8 temp_buff[10];
  uint32 v6[4] = {'\0'};
  temp_buff[0] = '\0';
  
  //! Total 8 octets
  for(index = 0; index < 8 ;index++)
  {
    //! each octet contains max of 5 characters including . dot
    for(offset = 0;offset < 5 ; offset++)
    {
      value = buf[buffer_offset++];
      if((value == '.') || (value == ':'))
      {
        break;
      }
      temp_buff[offset] =  value;      
    }
    temp_buff[offset]= '\0';
    if(index % 2 == 0)
    {
      v6[index/2] = (parseHex(temp_buff) << 16);
    }
    else
    {
      v6[index/2] |= parseHex(temp_buff);
    }
    temp_buff[0] = '\0';
  }
  for(i = 0; i < 4; i++)
  {
    rsi_uint32_to_4bytes((v+(4*i)), v6[i]);
  }

}
/*=========================================================================*/
/**
 * @fn          uint8 convert_lower_case_to_upper_case(uint8 lwrcase)
 * @brief       Converts the lower case character to upper case
 * @param[in]   character to convert 
 * @return      converted character
 * @section description 
 * This function is used to convert the given lower case character to upper case
 * destination string  
 */
uint8 convert_lower_case_to_upper_case(uint8 lwrcase)
{
  uint8 digit = (lwrcase >= 'a' && lwrcase <= 'f') ? (lwrcase-0x20) : lwrcase;
  return (digit >= 'A' && digit <= 'F') ? digit - 0x37 : digit - '0';
}

void string2array(uint8 *dst, uint8 *src, uint32 length)
{
  int i = 0,j = 0;
  for(i=0 ,j=0 ; i < (length * 2) && j < length; i+=2,j++)
  {
    if(src[i] && src[i + 1])
    {
      dst[j]  = ((uint16 )convert_lower_case_to_upper_case(src[i])) * 16;
      dst[j] += convert_lower_case_to_upper_case(src[i + 1]); 
    }
    else
    {
      dst[j]  = 0;
    }
  }
    
}


/*=========================================================================*/
/**
 * @fn          void rsi_itoa( uint32 val, uint8 *str)
 * @brief       Converts string to array
 * @param[in]   Pointer to destination array
 * @return      Pointer to source string
 * @section description 
 * This function is used to convert the given string to 
 * destination array
 */
uint8* rsi_itoa(uint32 val, uint8 *str)
{
  int16  ii = 0, jj = 0;
  uint8  tmp[10];
  if(val ==0)
  {
    //! if value is zero then handling
    str[jj] = '0';
    jj++;
    str[jj]='\0';
    return str;
  }

  while( val)
  {
    tmp[ii] = '0' + (val % 10);
    val /= 10;
    ii++;
  }

  for( jj = 0, ii--; ii >= 0; ii--, jj++)
  {
    str[jj] = tmp[ii];
  }
  str[jj]='\0';

  return str;
}
