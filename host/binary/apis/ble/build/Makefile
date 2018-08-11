# Makefile for WiSeConnect BT Application
TOP_DIR := $(PWD)
RM=/bin/rm -f
PROGNAME=rsi_wsc_ble_app
INCLUDES=  -I./ -I/work/colibri-2.6-kernel/include/
LINKS= -lpthread

BT_REF_APPS_SRC =../../bt/ref_apps/src
BT_CORE_SRC=../../bt/core/src
BLE_REF_APPS_SRC =../ref_apps/src
BLE_CORE_SRC=../core/src
WLAN_CORE_SRC=../../core/src
WLAN_REF_APPS_SRC=../../ref_apps/src
HAL_SRC=../../hal/src
INTF_SRC=../../intf/spi/src
CFLAGS= -g -Os  $(INCLUDES)
CFLAGS+= -DENABLE_DEBUG_PRINTS
CFLAGS+= -I../core/include/
CFLAGS+= -I../../core/include/
CFLAGS+= -I../../bt/core/include/
CFLAGS+= -I../ref_apps/include/
CFLAGS+= -I../../ref_apps/include/
CFLAGS+= -I../../bt/ref_apps/include/
CFLAGS+= -I../../hal/include/
CFLAGS+= -I../../intf/spi/include/
CFLAGS+= -D BLUETOOTH
#CFLAGS+= -DLINUX_PLATFORM
#CFLAGS+= -DRSI_DEBUG_PRINT


OBJS = $(BLE_REF_APPS_SRC)/main.o \
       $(BLE_REF_APPS_SRC)/ble_main.o \
       $(BLE_REF_APPS_SRC)/ble_app.o \
       $(WLAN_REF_APPS_SRC)/rsi_app_util.o \
       $(BLE_REF_APPS_SRC)/rsi_ble_config_init.o \
			 $(BT_CORE_SRC)/rsi_bt_build_frame_descriptor.o \
			 $(BLE_CORE_SRC)/rsi_ble_api.o \
			 $(BLE_CORE_SRC)/rsi_ble_core.o \
			 $(BT_CORE_SRC)/rsi_bt_execute_cmd.o \
			 $(BT_CORE_SRC)/rsi_bt_generic.o \
			 $(BLE_CORE_SRC)/rsi_ble_gatt.o \
			 $(WLAN_CORE_SRC)/rsi_lib_util.o \
       $(HAL_SRC)/rsi_hal_mcu_interrupt.o \
       $(HAL_SRC)/rsi_hal_mcu_ioports.o \
       $(HAL_SRC)/rsi_hal_mcu_spi.o \
       $(HAL_SRC)/rsi_hal_mcu_timers.o \
       $(INTF_SRC)/rsi_spi_frame_rd_wr.o \
       $(INTF_SRC)/rsi_spi_functs.o \
       $(INTF_SRC)/rsi_spi_iface_init.o \
       $(INTF_SRC)/rsi_spi_mem_rd_wr.o \
       $(INTF_SRC)/rsi_spi_reg_rd_wr.o \

.c.o:
	$(RM) $@
	$(CC) $(CFLAGS)  -o $*.o  -c $*.c

all: $(OBJS)
	$(CC) $(CFLAGS) $(LINKS) -o $(PROGNAME) $(OBJS) 

clean:
	$(RM)  $(OBJS) $(PROGNAME) core *~
