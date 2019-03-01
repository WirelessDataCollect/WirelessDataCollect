/**
 * @file       rsi_hal_mcu_uart.c
 * @version    1.0
 * @date       2014-Sept-23
 *
 * Copyright(C) Redpine Signals 2011
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 * @brief: HAL UART API
 *
 * @Description:
 * This file Contains all the API's related to HAL 
 *
 */


/**
 * Includes
 */

#ifdef WINDOWS
#include <windows.h>
#else
#include <sys/io.h>
#include <fcntl.h>            
#include <unistd.h>
#include <termios.h>
#endif
#ifdef ZB_ENABLE
#include "rsi_zigb_global.h"
#elif WLAN_ENABLE
#include "rsi_global.h"
#endif
#include "platform_specific.h"
#include "rsi_serial.h"

/**
 * Global Variables
 */
extern rsi_linux_app_cb_t rsi_linux_app_cb;

#ifdef WINDOWS
void system_error(char *name) {
  // Retrieve, format, and print out a message from the last error.  The 
  // `name' that's passed should be in the form of a present tense noun 
  // (phrase) such as "opening file".
  //
  char *ptr = NULL;
  FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER |
      FORMAT_MESSAGE_FROM_SYSTEM,
      0,
      GetLastError(),
      0,
      (char *)&ptr,
      1024,
      NULL);

  fprintf(stderr, "\nError %s: %s\n", name, ptr);
  LocalFree(ptr);
}
#endif

/*==================================================================*/
/**
 * @fn         int16 rsi_uart_send(uint8_t *ptrBuf,uint16 bufLen,uint8_t *valBuf,uint8_t mode)
 * @param[in]  uint8_t *ptrBuf, pointer to the buffer with the data to be sent/received
 * @param[in]  uint16 bufLen, number of bytes to send
 * @param[out] None
 * @return     0, 0=success
 * @section description  
 * This API is used to send data to the Wi-Fi module through the UART interface.
 */
int16_t rsi_uart_send(uint8_t *ptrBuf, uint16_t bufLen)
{
  int16_t retval = 0;
#ifdef WINDOWS
  DWORD written;
  retval = WriteFile(rsi_linux_app_cb.ttyfd, ptrBuf, bufLen, &written, NULL);
#else
  retval = write(rsi_linux_app_cb.ttyfd, ptrBuf, bufLen);
#endif
  return retval;
}


/*==================================================================*/
/**
 * @fn         int16 rsi_uart_recv(uint8_t *ptrBuf,uint16 bufLen,uint8_t mode)
 * @param[in]  uint8_t *ptrBuf, pointer to the buffer with the data to be sent/received
 * @param[in]  uint16 bufLen, number of bytes to send
 * @param[out] None
 * @return     0, 0=success
 * @description 
 * This API is used to receive data from Wi-Fi module through the UART interface.
 */
int16_t rsi_uart_recv(uint8_t *ptrBuf, uint16_t bufLen)
{
  int16_t i = 0;
  uint8_t ch = 0;
#ifdef WINDOWS
  DWORD read, Err;
  COMSTAT CST;
#endif
  do
  {
#ifdef WINDOWS
    while(1)
    {
      ClearCommError(rsi_linux_app_cb.ttyfd, (LPDWORD)&Err, &CST);
      if(CST.cbInQue != 0)break;
      Sleep(10);
    }
    ReadFile(rsi_linux_app_cb.ttyfd, &ch, 1, &read, NULL);
#else
    read(rsi_linux_app_cb.ttyfd, &ch, 1);
#endif
    ptrBuf[i++] = ch;
  }while (i != bufLen);

  return i;
}

/*==================================================================*/
/**
 * @fn         uint8_t rsi_uart_byte_read()
 * @param[in]  none
 * @param[out] None
 * @return     read character
 * @description 
 * This API is used to read the byte data from module through the UART interface.
 */
uint8_t rsi_uart_byte_read()
{
  uint8_t ch = 0;
#ifdef WINDOWS 
  DWORD read, Err;
  COMSTAT CST;
  while(1)
  {
    ClearCommError(rsi_linux_app_cb.ttyfd, (LPDWORD)&Err, &CST);
    if(CST.cbInQue != 0)break;
    Sleep(10);
  } 
  Err = ReadFile(rsi_linux_app_cb.ttyfd, &ch, 1, &read, NULL);
  if(!Err) printf("error reading\n");
#else
  read(rsi_linux_app_cb.ttyfd, &ch, 1);
#endif
  return ch;
}

/*==================================================================*/
/**
 * @fn         uint8_t rsi_serial_fifo_status()
 * @param[in]  none
 * @param[out] None
 * @return     status
 *             0 - if empty
 *             1 - if not empty
 * @description 
 * This API is used to read the status.
 */
uint8_t rsi_serial_fifo_status()
{
  /* In Case of OS based code */
  return 1;
  /* In Case of MCU  port return 1 if serial fifo is not empty
   * return 0 in case of serial fifo is empty */
}

/*==============================================*/
/**
 * @fn          void open_serial(void)
 * @brief       Open the serial device
 * @param[out]  none
 * @return      none
 * @section description
 * This is to configure the serial port
 */
#ifndef WINDOWS
void open_serial()
{
  int fd;
  struct termios newtio;

  /* Open modem device for reading and writing and not as controlling tty
   * because we don't want to get killed if linenoise sends CTRL-C. 
   */
  fd = open(RSI_UART_DEVICE, O_RDWR/* | O_NOCTTY */); 

  if (fd <0) {
    perror(RSI_UART_DEVICE); exit(-1); 
  }

  /* clear struct for new port settings */
  bzero(&newtio, sizeof(newtio)); 

  /* 
   * BAUDRATE: Set bps rate. You could also use cfsetispeed and cfsetospeed.
   * CRTSCTS : output hardware flow control (only used if the cable has
   * all necessary lines. See sect. 7 of Serial-HOWTO)
   * CS8     : 8n1 (8bit,no parity,1 stopbit)
   * CLOCAL  : local connection, no modem contol
   * CREAD   : enable receiving characters
   */
  newtio.c_cflag = BAUDRATE  | CS8 | CLOCAL | CREAD;//| CRTSCTS

  /*
   * IGNPAR  : ignore bytes with parity errors
   * ICRNL   : map CR to NL (otherwise a CR input on the other computer
   * will not terminate input)
   * otherwise make device raw (no other input processing)
   */
  newtio.c_iflag = IGNPAR;// | ICRNL;

  /* Raw output */
  newtio.c_oflag = 0;

  /*
   * ICANON  : enable canonical input
   * disable all echo functionality, and don't send signals to calling program
   */
  newtio.c_lflag = 0;

  /* 
   * initialize all control characters 
   * default values can be found in /usr/include/termios.h, and are given
   * in the comments, but we don't need them here
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
  
  /* now clean the modem line and activate the settings for the port
   */
  tcflush(fd, TCIFLUSH);
  tcsetattr(fd,TCSANOW,&newtio);

  rsi_linux_app_cb.ttyfd = fd;
}
#endif

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

int16_t rsi_serial_init(void)
{
  int fd; 
#ifdef WINDOWS
  COMMTIMEOUTS timeouts;
  DCB port;
  DWORD mode;
  char port_name[128] = "\\\\.\\COM13";
  // open the comm port.
  fd = CreateFile(port_name,
      GENERIC_READ | GENERIC_WRITE,
      0, 
      NULL, 
      OPEN_EXISTING,
      FILE_ATTRIBUTE_NORMAL,
      NULL);

  if ( INVALID_HANDLE_VALUE == fd) {
    system_error("opening file\n");
    return 1;
  }
  // get the current DCB, and adjust a few bits to our liking.
  memset(&port, 0, sizeof(port));
  port.DCBlength = sizeof(port);
  if ( !GetCommState(fd, &port))
    system_error("getting comm state");
  if (!BuildCommDCB("baud=115200 parity=n data=8 stop=1", &port))
    system_error("building comm DCB");
  if (!SetCommState(fd, &port))
    system_error("adjusting port settings");

  timeouts.ReadIntervalTimeout = 50;
  timeouts.ReadTotalTimeoutMultiplier = 50;
  timeouts.ReadTotalTimeoutConstant = 50;
  timeouts.WriteTotalTimeoutMultiplier = 50;
  timeouts.WriteTotalTimeoutConstant = 50;
  if (!SetCommTimeouts(fd, &timeouts))
    system_error("setting port time-outs.");
  rsi_linux_app_cb.ttyfd = fd;
  return 0;
#else
  struct termios tio;
  memset(&tio, 0, sizeof(tio));

  fd = open(RSI_UART_DEVICE, O_RDWR | O_NOCTTY | O_NDELAY);
  rsi_linux_app_cb.ttyfd = fd; 

  if (fd == -1) 
  {
    perror("open_port: Unable to open /dev/ttyUSB0 - ");
    return 1;
  } 
  else 
  {
    tio.c_iflag     = 0;
    tio.c_oflag     = 0;
    tio.c_cflag     = CS8 | CREAD | CLOCAL;
    tio.c_lflag     = ICANON;
    tio.c_cc[VMIN]  = 4;
    tio.c_cc[VTIME] = 0;

    cfsetospeed(&tio, B115200);
    cfsetispeed(&tio, B115200);

    tcflush(rsi_linux_app_cb.ttyfd, TCIFLUSH);    
    tcsetattr(rsi_linux_app_cb.ttyfd, TCSANOW, &tio);
#ifdef RSI_DEBUG_PRINT
      RSI_DPRINT(RSI_PL13,"Serial connection established\n");
#endif      
     open_serial();
    return 0;
  }
#endif
}

