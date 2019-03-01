/**
 * @file        rsi_uart.c
 * Copyright(C) 2013 Redpine Signals Inc.
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * T:vshis program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief MAIN, Top level file, it all starts here
 *
 * @section Description
 * This file contains API's to write and read to serial device 
 * It also has RecvThread and serial device initialization API's too 
 * 
 */

#include "rsi_nl_app.h"
#include "rsi_serial.h"
#include <termios.h>

#define BAUDRATE B115200
#define RSI_PRE_DESC_LEN 4
char *serial_device[] = {"/dev/ttyUSB0", "/dev/ttyACM0"};


uint8 card_ready_frame[16] = { 0x0, 0x40, 0x89, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
int rsi_uart_read_term(uint8 *buf, uint16 len);
int rsi_uart_dummy_read(uint16 len);
int rsi_uart_read(uint8 *buf, uint16 len);
struct termios tio;


/*==============================================*/
/**
 * @fn          int16 rsi_serial_frame_write(uint8 *packet_buffer, int16 length)
 * @brief       frame writing api 
 * @param[in]   packet buffer that has to be written on to the socket
 * @return      errCode
 *              0  = SUCCESS
 *              else failure
 */
int16 rsi_serial_frame_write(uint8 *packet_buffer, int16 length)
{
    int16 retval = 0;
    retval = write(rsi_linux_app_cb.ttyfd, packet_buffer, length);
    /* Return success */
    return retval;
}

/*==============================================*/
/**
 * @fn          void rsi_serial_init(void)
 * @brief       Serial device initialization
 * @param[out]  int16
 * @return      errCode
 *              0  = SUCCESS
 *              else failure
 * @section description
 * This is to initialize serial device for communicating
 * over UART/USB-serial.
 */

int16 rsi_serial_init(int port)
{
  int fd; 
  bzero(&tio, sizeof(tio));
  fd = open(serial_device[port], O_RDWR| O_NOCTTY );
  rsi_linux_app_cb.ttyfd = fd; 

  if (fd == -1) 
  {
    perror("open_port: Unable to open serial interface- ");
    return 1;
  } 
  else 
  {
    tio.c_iflag     = 0;
    tio.c_oflag     = 0;
    tio.c_cflag     = BAUDRATE|CS8 |CLOCAL| CREAD;
    tio.c_lflag     = 0;
    tio.c_cc[VMIN]  = 1;
    tio.c_cc[VTIME] = 0;
    tio.c_cc[VEOF]  = 4;     /* Ctrl-d */
 
    tcflush(rsi_linux_app_cb.ttyfd, TCIFLUSH);    
    tcsetattr(rsi_linux_app_cb.ttyfd, TCSANOW, &tio);
    return 0;
  }
}


/*=================================================*/
/**
 * @fn          void &RecvSerialThreadBody(void *arg)
 * @brief       Receive thread function
 * @param[in]   void *arg, receive thread func argument
 * @param[out]  none
 * @return      none
 * @section description
 * This is Recv thread function which will receive packets
 * from LMAC over serial device
 */
uint8 only_once;
void * RecvSerialThreadBody(void * arg )
{
  //! This thread reads from UART interface and sends it to kernel through NL socket
  //! need to first 4 bytes and so
  //! need to change receive logic similar to SPI
  int16 retval = 0;
  uint16 size_param = 0;
  pkt_struct_t *rcvPktPtr;
  uint16 desc_offset = 0;
  uint16 actual_len = 0; 
  uint8 dummy_buf[20];
  do {
    rcvPktPtr = (pkt_struct_t*) malloc( sizeof(pkt_struct_t) );
    rcvPktPtr->data = (uint8*) malloc(RSI_MAX_PAYLOAD_SIZE);

    if(only_once)
    {
	
      //! Read first 4 bytes
      rsi_uart_read(dummy_buf, RSI_PRE_DESC_LEN);
      actual_len = *(uint16*)(dummy_buf);
      desc_offset = *(uint16*)(dummy_buf + 2);
      
      if (desc_offset > RSI_PRE_DESC_LEN) 
        rsi_uart_dummy_read(desc_offset - RSI_PRE_DESC_LEN); //only for usb cdc

      //! Read actual data
      rsi_uart_read(rcvPktPtr->data, actual_len - desc_offset);

      size_param = ((*(uint16 *)&rcvPktPtr->data[0]) & 0xfff);
      size_param += RSI_FRAME_DESC_LEN;
      if((rcvPktPtr->data[2] == 0xA4)&&(rcvPktPtr->data[1] == 0x40)&&(rsi_linux_app_cb.serial_type == UART))
      {
	     if(rcvPktPtr->data[16] == 0x1)
	     {
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL0,"\n UART FLOW CONTROL ENABLED\n");
#endif
           tio.c_cflag |= CRTSCTS;
           tcsetattr(rsi_linux_app_cb.ttyfd, TCSANOW, &tio);
         }
         else
         {
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL0,"\n UART FLOW CONTROL DISABLED\n");
#endif
           tio.c_cflag &= (~CRTSCTS);
           tcsetattr(rsi_linux_app_cb.ttyfd, TCSANOW, &tio);
         }
	  }
    }
    else
    {
      if (rsi_linux_app_cb.serial_type == USB_CDC) {

          rsi_uart_read(dummy_buf, 4);
          if(dummy_buf[0] == 'L')
          {
            rsi_uart_read(&dummy_buf[4],(sizeof("Loading Done") + 1 - 4));
          }
          else
          {
            actual_len = *(uint16*)(dummy_buf);
            desc_offset = *(uint16*)(dummy_buf + 2);

            if (desc_offset > RSI_PRE_DESC_LEN) 
              rsi_uart_dummy_read(desc_offset - RSI_PRE_DESC_LEN); //only for usb cdc

            //! Read actual data
            rsi_uart_read(rcvPktPtr->data, actual_len - desc_offset);

          }
      }
      only_once = 1;
      size_param = RSI_FRAME_DESC_LEN;
      memcpy(rcvPktPtr->data, card_ready_frame, RSI_FRAME_DESC_LEN);
    }

    /* Send recvd device data to driver */
    retval = rsi_execute_cmd_serial_to_driver(rcvPktPtr->data, size_param);
    if (retval)
    {
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL0,"\nunable to send data to serial port\n");
#endif
    }

    //! Free the data buffer
    rsi_free(rcvPktPtr->data);
    rsi_free(rcvPktPtr);
  }while(1);
}

/*====================================================*/
/**
 * @fn          int16 rsi_execute_cmd_serial_to_driver(uint8 *payloadparam,uint16 size_param)
 * @brief       Common function for all the commands.
 * @param[in]   uint8 *descparam, pointer to the frame descriptor parameter structure
 * @param[in]   uint8 *payloadparam, pointer to the command payload parameter structure
 * @param[in]   uint16 size_param, size of the payload for the command
 * @return      errCode
 *              -2 = Command issue failed
 *              0  = SUCCESS
 * @section description
 * This is a common function used to process a command to the Wi-Fi module.
 */

int16 rsi_execute_cmd_serial_to_driver(uint8 *payloadparam, uint16 size_param)
{
  int16       retval = 0;
  uint8       *cmd_buff;
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL14,"\nrsi_execute_cmd_serial_to_driver\n");
#endif

  //! Prepare nl_socket data to transfer it to driver
  cmd_buff = rsi_prepare_nl_cmdbuff(payloadparam, size_param);

  if(rsi_send_usr_cmd(cmd_buff, GET_SEND_LENGTH(cmd_buff)) < 0)
  {
    retval = -2;
  }
  if(retval < 0)
  {
    RSI_DPRINT(RSI_PL13,"Unable to issue command\n");
  }

  //! Free the command buffer
  rsi_free(cmd_buff);

  return retval;
}


int rsi_uart_dummy_read(uint16 len)
{
  int i = 0;
  uint8 ch = 0;
  do
  {
    read(rsi_linux_app_cb.ttyfd, &ch, 1);
    i++;
  }while (i != len);
  return i;
}

int rsi_uart_read_term(uint8 *buf, uint16 len)
{
  int i = 0;
  uint8 ch = 0;
  do
  {
    read(rsi_linux_app_cb.ttyfd, &ch, 1);
    buf[i++] = ch;
  }while (ch != '\n');

  return i;
}

int rsi_uart_read(uint8 *buf, uint16 len)
{
  int i = 0;
  uint8 ch = 0;
  do
  {
    read(rsi_linux_app_cb.ttyfd, &ch, 1);
    buf[i++] = ch;
  }while (i != len);

  return i;
}

void open_serial(int port)
{
  int fd;
  struct termios newtio;
  /* 
     Open modem device for reading and writing and not as controlling tty
     because we don't want to get killed if linenoise sends CTRL-C.
     */
  fd = open(serial_device[port], O_RDWR/* | O_NOCTTY */);
  if (fd <0) {perror(serial_device[port]); exit(-1); }
  else
  {
#ifdef RSI_DEBUG_PRINT
  RSI_DPRINT(RSI_PL0,"\nopen serial port\n");
#endif
  }


  bzero(&newtio, sizeof(newtio)); /* clear struct for new port settings */

  /* 
BAUDRATE: Set bps rate. You could also use cfsetispeed and cfsetospeed.
CRTSCTS : output hardware flow control (only used if the cable has
all necessary lines. See sect. 7 of Serial-HOWTO)
CS8     : 8n1 (8bit,no parity,1 stopbit)
CLOCAL  : local connection, no modem contol
CREAD   : enable receiving characters
*/
  newtio.c_cflag = BAUDRATE  | CS8 | CLOCAL | CREAD;//| CRTSCTS

  /*
IGNPAR  : ignore bytes with parity errors
ICRNL   : map CR to NL (otherwise a CR input on the other computer
will not terminate input)
otherwise make device raw (no other input processing)
*/
  newtio.c_iflag = IGNPAR;// | ICRNL;

  /*
     Raw output.
     */
  newtio.c_oflag = 0;

  /*
ICANON  : enable canonical input
disable all echo functionality, and don't send signals to calling program
*/
  newtio.c_lflag = 0;

  /* 
     initialize all control characters 
     default values can be found in /usr/include/termios.h, and are given
     in the comments, but we don't need them here
     */
  newtio.c_cc[VINTR]    = 0;     /* Ctrl-c */ 
  newtio.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
  newtio.c_cc[VERASE]   = 0;     /* del */
  newtio.c_cc[VKILL]    = 0;     /* @ */
  newtio.c_cc[VEOF]     = 4;     /* Ctrl-d */
  newtio.c_cc[VTIME]    = 0;     /* inter-character timer unused */
  newtio.c_cc[VMIN]     = 1;     /* blocking read until 1 character arrives */
  newtio.c_cc[VSWTC]    = 0;     /* '\0' */
  newtio.c_cc[VSTART]   = 0;     /* Ctrl-q */ 
  newtio.c_cc[VSTOP]    = 0;     /* Ctrl-s */
  newtio.c_cc[VSUSP]    = 0;     /* Ctrl-z */
  newtio.c_cc[VEOL]     = 0;     /* '\0' */
  newtio.c_cc[VREPRINT] = 0;     /* Ctrl-r */
  newtio.c_cc[VDISCARD] = 0;     /* Ctrl-u */
  newtio.c_cc[VWERASE]  = 0;     /* Ctrl-w */
  newtio.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
  newtio.c_cc[VEOL2]    = 0;     /* '\0' */

  /* 
     now clean the modem line and activate the settings for the port
     */
  tcflush(fd, TCIFLUSH);
  tcsetattr(fd,TCSANOW,&newtio);

  rsi_linux_app_cb.ttyfd = fd;
}

