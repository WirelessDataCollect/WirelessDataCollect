# Makefile for WiSeConnect Application
TOP_DIR := $(PWD)
RM=/bin/rm -f
#CC=/work/Godavari/arm-2007q1/bin/arm-none-linux-gnueabi-gcc
CC=gcc
PROGNAME=rsi_wsc_bt_app
INCLUDES=  -I./ -I/work/colibri-2.6-kernel/include/
LINKS= -lpthread

REF_APPS_SRC =../../../../../apis/bt/ref_apps/src/
WLAN_REF_APPS_SRC =../../../../../apis/wlan/ref_apps/src/
CORE_SRC=../../../../../apis/bt/core/src/
WLAN_CORE_SRC=../../../../../apis/wlan/core/src/
WLAN_LINUX_SRC=../../wlan/src/
HAL_SRC=../../../../../apis/hal/src/
WLAN_LINUX_SRC=../../wlan/src/
CFLAGS= -g -Os -Wall -fno-strict-aliasing $(INCLUDES)
CFLAGS+= -DENABLE_DEBUG_PRINTS
CFLAGS+= -I../include
CFLAGS+= -I../../wlan/include
CFLAGS+= -I../../../../../apis/bt/core/include
CFLAGS+= -I../../../../../apis/ble/core/include
CFLAGS+= -I../../../../../apis/wlan/core/include
CFLAGS+= -I../../../../../apis/hal/include
CFLAGS+= -I../../../../../apis/intf/spi/include
CFLAGS+= -I../../../../../apis/wlan/ref_apps/include
CFLAGS+= -I../../../../../apis/bt/ref_apps/include
CFLAGS+= -DBT_ENABLE
CFLAGS+= -DENABLE_BT_NL
CFLAGS+= -DRSI_DEBUG_PRINT
CFLAGS+= -DLINUX_PLATFORM

OBJS = main.o \
 $(WLAN_REF_APPS_SRC)rsi_app_util.o \
 $(REF_APPS_SRC)rsi_bt_config_init.o \
 $(REF_APPS_SRC)bt_main.o \
 $(REF_APPS_SRC)bt_app.o \
 $(WLAN_LINUX_SRC)rsi_hal_mcu_interrupt.o \
 $(CORE_SRC)rsi_bt_build_frame_descriptor.o \
 $(CORE_SRC)rsi_bt_api.o \
 $(CORE_SRC)rsi_bt_core.o \
 $(CORE_SRC)rsi_bt_generic.o \
 $(CORE_SRC)rsi_bt_spp.o \
 $(WLAN_CORE_SRC)rsi_lib_util.o \
 $(WLAN_LINUX_SRC)rsi_linux_apis.o \
 $(WLAN_LINUX_SRC)rsi_ioctl_app.o \
 $(CORE_SRC)rsi_bt_register_interrupt_irq.o \
 rsi_bt_linux_apis.o \
 $(WLAN_LINUX_SRC)rsi_nl_app.o 

.c.o:
	$(RM) $@
	$(CC) $(CFLAGS)  -o $*.o  -c $*.c

all: $(OBJS)
	$(CC) $(CFLAGS) $(LINKS) -o $(PROGNAME) $(OBJS) 

clean:
	$(RM)  $(OBJS) $(PROGNAME) core *~
