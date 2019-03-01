# Makefile for WiSeConnect Application
TOP_DIR := $(PWD)
RM=/bin/rm -f
#CC=/work/venkateshl/venky/sam9/AT91SAM9G35-EK/atmel/arm-2007q1/bin/arm-none-linux-gnueabi-gcc
CC=gcc
PROGNAME=rsi_wsc_zigb_app
WLAN_PROGNAME=rsi_wsc_wifi_app
INCLUDES=  -I./ -I/work/colibri-2.6-kernel/include/
LINKS= -lpthread

REF_APPS_SRC =../../../../../apis/zb/ref_apps/src
CORE_SRC=../../../../../apis/zb/core/src
HAL_SRC=../../../../apis/hal/src/
WLAN_CORE_SRC=../../../../../apis/wlan/core/src/
WLAN_REF_APPS_SRC =../../../../../apis/wlan/ref_apps/src/
WLAN_LINUX_SRC=../../wlan/src

CFLAGS= -g -Os -Wall -fno-strict-aliasing $(INCLUDES)
CFLAGS+= -I../include
CFLAGS+= -I../../wlan/include
CFLAGS+= -I../../../../../apis/zb/core/include
CFLAGS+= -I../../../../../apis/zb/ref_apps/include
CFLAGS+= -I../../../../../apis/wlan/core/include
CFLAGS+= -I../../../../../apis/hal/include
CFLAGS+= -I../../../../../apis/intf/spi/include
CFLAGS+= -I../../../../../apis/wlan/ref_apps/include

#CFLAGS+= -DENABLE_DEBUG_PRINTS
#CFLAGS+= -DRSI_DEBUG_PRINT
CFLAGS += -DZB_DEBUG
CFLAGS += -DSWITCH_APP
CFLAGS += -DLINUX_PLATFORM
CFLAGS += -D ZB_ENABLE
CFLAGS += -D ENABLE_ZB_NL

ifeq ($(MAKECMDGOALS),apitest)
CFLAGS += -D ZB_API_TEST
endif


OBJS += main.o \
	   $(CORE_SRC)/rsi_zigb_frame_desc.o \
	   $(CORE_SRC)/rsi_zigb_api.o \
	   $(CORE_SRC)/rsi_zigb_utility.o \
		 $(CORE_SRC)/rsi_zigb_build_frame_descriptor.o \
	   $(CORE_SRC)/rsi_zigb_app_frame_process.o \
		 $(REF_APPS_SRC)/rsi_zigb_app_cb_handler.o \
		 $(REF_APPS_SRC)/rsi_zigb_config.o \
		 $(REF_APPS_SRC)/rsi_zigb_api_test.o \
		 $(REF_APPS_SRC)/zigb_main.o \
	   rsi_zigb_linux_apis.o \
	   $(WLAN_LINUX_SRC)/rsi_nl_app.o \
	   $(WLAN_LINUX_SRC)/rsi_hal_mcu_interrupt.o \
		 $(WLAN_CORE_SRC)rsi_lib_util.o


.c.o:
	$(RM) $@
	$(CC) $(CFLAGS)  -o $*.o  -c $*.c

all: switch

switch: clean $(OBJS)
	$(CC) $(CFLAGS) $(LINKS) -o $(PROGNAME) $(OBJS)

wlan:
	$(RM) $(WLAN_PROGNAME) 
	make -C $(WLAN_LINUX_SRC) clean
	make -C $(WLAN_LINUX_SRC) 
	cp $(WLAN_LINUX_SRC)/rsi_wsc_app $(WLAN_PROGNAME)

apitest: clean $(OBJS)
	$(CC) $(CFLAGS) $(LINKS) -o $(PROGNAME) $(OBJS)

zb: clean $(OBJS)
	$(CC) $(CFLAGS) $(LINKS) -o $(PROGNAME) $(OBJS)

clean:
	$(RM)  $(OBJS) $(OBJS_API) $(PROGNAME) $(PROGNAME1) core *~
