# Makefile for WiSeConnect Application
TOP_DIR := $(PWD)
RM=/bin/rm -f
#CC=/work/venkateshl/venky/sam9/AT91SAM9G35-EK/atmel/arm-2007q1/bin/arm-none-linux-gnueabi-gcc
CC=gcc
PROGNAME=rsi_serial
INCLUDES=  -I./ -I/work/colibri-2.6-kernel/include/
LINKS= -lpthread

CORE_SRC=../../../../../apis/wlan/core/src/

CFLAGS= -g -Os -Wall -fno-strict-aliasing $(INCLUDES)
CFLAGS+= -DENABLE_DEBUG_PRINTS
CFLAGS+= -I../include
CFLAGS+= -DRSI_DEBUG_PRINT
CFLAGS+= -DLINUX_PLATFORM
CFLAGS+= -DENABLE_SERIAL_NL 
CFLAGS+= -Dm32 

OBJS = main.o \
 rsi_uart.o \
 rsi_nl_app.o \
 $(CORE_SRC)rsi_lib_util.o 
 

.c.o:
	$(RM) $@
	$(CC) $(CFLAGS)  -o $*.o  -c $*.c

all: clean $(OBJS)
	$(CC) $(CFLAGS) $(LINKS) -o $(PROGNAME) $(OBJS) 

clean:
	$(RM)  $(OBJS) $(PROGNAME) core *~
