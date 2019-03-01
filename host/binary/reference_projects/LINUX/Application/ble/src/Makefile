# Makefile for WiSeConnect Application
TOP_DIR := $(PWD)
RM=/bin/rm -f
#CC=/work/venkateshl/venky/sam9/AT91SAM9G35-EK/atmel/arm-2007q1/bin/arm-none-linux-gnueabi-gcc
CC=gcc
PROGNAME=rsi_wsc_ble_app
INCLUDES=  -I./ -I/work/colibri-2.6-kernel/include/
LINKS= -lpthread

BT_REF_APPS_SRC =../../../../../apis/bt/ref_apps/src/
BLE_REF_APPS_SRC =../../../../../apis/ble/ref_apps/src/
WLAN_REF_APPS_SRC =../../../../../apis/wlan/ref_apps/src/
BT_CORE_SRC=../../../../../apis/bt/core/src/
BLE_CORE_SRC=../../../../../apis/ble/core/src/
WLAN_CORE_SRC=../../../../../apis/wlan/core/src/
HAL_SRC=../../../../../apis/hal/src/
WLAN_LINUX_SRC=../../wlan/src/
CFLAGS= -g -Os -Wall -fno-strict-aliasing -fpack-struct=4 $(INCLUDES)
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
CFLAGS+= -I../../../../../apis/ble/ref_apps/include
CFLAGS+= -DBLE_ENABLE
CFLAGS+= -DBT_ENABLE
CFLAGS+= -DENABLE_BT_NL
CFLAGS+= -DRSI_DEBUG_PRINT
CFLAGS+= -DLINUX_PLATFORM

OBJS = main.o \
 $(WLAN_REF_APPS_SRC)rsi_app_util.o \
 $(BLE_REF_APPS_SRC)rsi_ble_config_init.o \
 $(BLE_REF_APPS_SRC)ble_main.o \
 $(BLE_REF_APPS_SRC)ble_app.o \
 $(WLAN_LINUX_SRC)rsi_hal_mcu_interrupt.o \
 $(WLAN_LINUX_SRC)rsi_linux_apis.o \
 $(WLAN_LINUX_SRC)rsi_ioctl_app.o \
 $(BT_CORE_SRC)rsi_bt_build_frame_descriptor.o \
 $(BLE_CORE_SRC)rsi_ble_api.o \
 $(BLE_CORE_SRC)rsi_ble_core.o \
 $(BT_CORE_SRC)rsi_bt_generic.o \
 $(BLE_CORE_SRC)rsi_ble_gatt.o \
 $(WLAN_CORE_SRC)rsi_lib_util.o \
 $(BT_CORE_SRC)rsi_bt_register_interrupt_irq.o \
 ../../bt/src/rsi_bt_linux_apis.o \
 $(WLAN_LINUX_SRC)rsi_nl_app.o 

.c.o:
	$(RM) $@
	$(CC) $(CFLAGS)  -o $*.o  -c $*.c

all: $(OBJS)
	$(CC) $(CFLAGS) $(LINKS) -o $(PROGNAME) $(OBJS) 

clean:
	$(RM)  $(OBJS) $(PROGNAME) core *~
