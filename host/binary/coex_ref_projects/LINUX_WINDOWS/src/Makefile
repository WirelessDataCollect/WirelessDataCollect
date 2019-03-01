# Makefile for WiSeConnect Application
TOP_DIR := $(PWD)
RM=/bin/rm -f
PROGNAME=rsi_wsc_uart_app
CC       = gcc
LINKS= -lpthread

API_PATH = ../../../apis
COEX_APP_PATH = ../../coex_app_framework

#HAL source files
HAL_SRC= $(API_PATH)/hal/src
PLAT_HAL_SRC= ./hal/src/

#Interface source files
INTF_SRC = $(API_PATH)/intf/spi/src/
UART_INTF_SRC = $(API_PATH)/intf/uart/src/

#WLAN source files
WLAN_CORE_SRC = $(API_PATH)/wlan/core/src/
WLAN_REF_APPS_SRC = $(API_PATH)/wlan/ref_apps/src/

#BT source files
BT_CORE_SRC = $(API_PATH)/bt/core/src
BT_REF_APPS_SRC = $(API_PATH)/bt/ref_apps/src

#BLE source files
BLE_CORE_SRC = $(API_PATH)/ble/core/src
BLE_REF_APPS_SRC = $(API_PATH)/ble/ref_apps/src

#ZB source files
ZB_CORE_SRC = $(API_PATH)/zb/core/src
ZB_REF_APPS_SRC=$(API_PATH)/zb/ref_apps/src/

WLAN_APP_SRC = $(COEX_APP_PATH)/wlan/src/
BT_ZB_APP_SRC = $(COEX_APP_PATH)/bt_zb/src/
COEX_APP_SRC = $(COEX_APP_PATH)/common/src/

CFLAGS= -g -Os -Wall -fno-strict-aliasing $(INCLUDES)
CFLAGS+= -I../include
CFLAGS+= -I$(COEX_APP_PATH)/wlan/include/
CFLAGS+= -I$(COEX_APP_PATH)/bt_zb/include/
CFLAGS+= -I$(COEX_APP_PATH)/common/include/
CFLAGS+= -I$(API_PATH)/zb/core/include
CFLAGS+= -I$(API_PATH)/hal/include
CFLAGS+= -I$(API_PATH)/wlan/core/include
CFLAGS+= -I$(API_PATH)/wlan/ref_apps/include
CFLAGS+= -I$(API_PATH)/zb/ref_apps/include
CFLAGS+= -DENABLE_DEBUG_PRINTS
CFLAGS+= -DRSI_DEBUG_PRINT
CFLAGS+= -I $(API_PATH)/bt/core/include
CFLAGS+= -I $(API_PATH)/ble/core/include

CFLAGS+= -I$(API_PATH)/wlan/core/include/
CFLAGS+= -I$(API_PATH)/wlan/ref_apps/include/
CFLAGS+= -I$(API_PATH)/hal/include/
CFLAGS+= -I$(API_PATH)/intf/spi/include/
CFLAGS+= -I$(API_PATH)/intf/uart/include/
CFLAGS+= -I$(API_PATH)/bt/ref_apps/include
CFLAGS+= -I$(API_PATH)/ble/ref_apps/include

CFLAGS+= -D COEX_APP_CHANGES
CFLAGS+= -D WLAN_RAW_DATA_TEST
#CFLAGS+= -D PWR_SAVE
#CFLAGS+= -D RSI_BLE_MASTER
CFLAGS+= -D RSI_TEST_DBG
#CFLAGS+= -D RSI_WLAN_DEEPSLP_DBG
#CFLAGS+= -D RSI_BLE_DEEPSLP_DBG
CFLAGS+= -D APP_DEBUG

ifeq ($(MAKECMDGOALS),apitest)
CFLAGS += -D ZB_API_TEST
CFLAGS+= -DZB_ONLY
CFLAGS+= -DZB_ENABLE
CFLAGS+= -DENABLE_ZB_NL
CFLAGS+= -DLINUX_PLATFORM
endif

ifeq ($(MAKECMDGOALS),wlan)
CFLAGS+= -D WLAN_ENABLE
CFLAGS+= -DLINUX_PLATFORM
CFLAGS+= -DRSI_HAL
endif

ifeq ($(MAKECMDGOALS),bt)
CFLAGS+= -D BT_ENABLE
CFLAGS+= -DLINUX_PLATFORM
CFLAGS+= -DRSI_HAL
endif

ifeq ($(MAKECMDGOALS),ble)
CFLAGS+= -D BLE_ENABLE
CFLAGS+= -D FSM_BASED_BLE_APP
CFLAGS+= -DLINUX_PLATFORM
CFLAGS+= -DRSI_HAL
endif

ifeq ($(MAKECMDGOALS),zb)
CFLAGS+= -DZB_ONLY
CFLAGS+= -DSWITCH_APP
CFLAGS+= -DZB_ENABLE
CFLAGS+= -DENABLE_ZB_NL
CFLAGS+= -DLINUX_PLATFORM
CFLAGS+= -DRSI_HAL
endif

ifeq ($(MAKECMDGOALS),wlan_ble)
CFLAGS+= -D WLAN_ENABLE
CFLAGS+= -D BLE_ENABLE
CFLAGS+= -D FSM_BASED_BLE_APP
CFLAGS+= -DLINUX_PLATFORM
CFLAGS+= -DRSI_HAL
endif


ifeq ($(MAKECMDGOALS),wlan_zb)
CFLAGS+= -D WLAN_ENABLE
CFLAGS+= -DZB_ONLY
CFLAGS+= -DSWITCH_APP
CFLAGS+= -DZB_ENABLE
CFLAGS+= -DENABLE_ZB_NL
CFLAGS+= -DLINUX_PLATFORM
CFLAGS+= -DRSI_HAL
endif

ifeq ($(MAKECMDGOALS),wlan_bt)
CFLAGS+= -D WLAN_ENABLE
CFLAGS+= -D BT_ENABLE
CFLAGS+= -DLINUX_PLATFORM
CFLAGS+= -DRSI_HAL
endif

OBJS = main.o \
    $(COEX_APP_SRC)rsi_common_apis.o \
    $(COEX_APP_SRC)rsi_common_event_handlers.o \
    $(COEX_APP_SRC)rsi_event.o \
    $(COEX_APP_SRC)rsi_main.o \
    $(COEX_APP_SRC)rsi_scheduler.o  \
    $(COEX_APP_SRC)rsi_utils.o  \
    $(WLAN_REF_APPS_SRC)/rsi_app_util.o \
    $(WLAN_CORE_SRC)/rsi_lib_util.o \
    $(WLAN_APP_SRC)/rsi_coex_execute_cmd.o \
    $(WLAN_APP_SRC)/rsi_send_raw_data.o \
    $(WLAN_APP_SRC)/rsi_wlan_event_handler.o \
    $(BT_ZB_APP_SRC)/rsi_bt_coex_execute_cmd.o \
    $(BT_ZB_APP_SRC)/rsi_bt_zb_event_handler.o \
    $(BT_ZB_APP_SRC)/rsi_zigb_coex_execute_cmd.o \
    $(INTF_SRC)/rsi_spi_functs.o \
    $(INTF_SRC)/rsi_spi_iface_init.o \
    $(INTF_SRC)/rsi_spi_mem_rd_wr.o \
    $(INTF_SRC)/rsi_spi_reg_rd_wr.o \
    $(PLAT_HAL_SRC)rsi_hal_mcu_uart.o \
    $(PLAT_HAL_SRC)/rsi_uart_frame_rd_wr.o \
    $(HAL_SRC)/rsi_hal_mcu_ioports.o \
    $(HAL_SRC)/rsi_hal_mcu_spi.o \
    $(HAL_SRC)/rsi_hal_mcu_timers.o \
    $(HAL_SRC)/rsi_hal_mcu_interrupt.o 

ZB_OBJS = $(ZB_CORE_SRC)/rsi_zigb_frame_desc.o \
	$(ZB_CORE_SRC)/rsi_zigb_api.o \
	$(ZB_CORE_SRC)/rsi_zigb_utility.o \
	$(ZB_CORE_SRC)/rsi_zigb_build_frame_descriptor.o \
	$(ZB_CORE_SRC)/rsi_zigb_app_frame_process.o \
	$(ZB_CORE_SRC)/rsi_zigb_oper_mode.o \
	$(ZB_CORE_SRC)/rsi_zigb_delay.o \
	$(ZB_REF_APPS_SRC)/rsi_zigb_app_cb_handler.o \
	$(ZB_REF_APPS_SRC)/rsi_zigb_config.o \
	$(ZB_REF_APPS_SRC)/rsi_zigb_state_mc.o \
	$(ZB_REF_APPS_SRC)/rsi_zigb_api_test.o 

WLAN_OBJS = $(WLAN_REF_APPS_SRC)/rsi_config_init.o \
    $(WLAN_REF_APPS_SRC)/rsi_wifi_state_mc.o \
    $(WLAN_REF_APPS_SRC)/rsi_buildHttpExtendedHeader.o \
    $(WLAN_CORE_SRC)/rsi_build_frame_descriptor.o \
    $(WLAN_CORE_SRC)/rsi_select_antenna.o \
    $(WLAN_CORE_SRC)/rsi_api.o \
    $(WLAN_CORE_SRC)/rsi_band.o \
    $(WLAN_CORE_SRC)/rsi_cfg_enable.o \
    $(WLAN_CORE_SRC)/rsi_cfg_get.o \
    $(WLAN_CORE_SRC)/rsi_cfg_save.o \
    $(WLAN_CORE_SRC)/rsi_disconnect.o \
    $(WLAN_CORE_SRC)/rsi_dns_query.o \
    $(WLAN_CORE_SRC)/rsi_dns_server.o \
    $(WLAN_CORE_SRC)/rsi_gpio_config.o \
    $(WLAN_CORE_SRC)/rsi_http_get.o \
    $(WLAN_CORE_SRC)/rsi_http_post.o \
    $(WLAN_CORE_SRC)/rsi_init.o \
    $(WLAN_CORE_SRC)/rsi_interrupt_handler.o \
    $(WLAN_CORE_SRC)/rsi_ip_param_set.o \
    $(WLAN_CORE_SRC)/rsi_join.o \
    $(WLAN_CORE_SRC)/rsi_ltcp_conn_status.o \
    $(WLAN_CORE_SRC)/rsi_module_soft_reset.o \
    $(WLAN_CORE_SRC)/rsi_oper_mode.o \
    $(WLAN_CORE_SRC)/rsi_p2p_config.o \
    $(WLAN_CORE_SRC)/rsi_psk.o \
    $(WLAN_CORE_SRC)/rsi_ping_request.o \
    $(WLAN_CORE_SRC)/rsi_query_conn_status.o \
    $(WLAN_CORE_SRC)/rsi_query_fw_version.o \
    $(WLAN_CORE_SRC)/rsi_query_go_parms.o \
    $(WLAN_CORE_SRC)/rsi_query_mac_address.o \
    $(WLAN_CORE_SRC)/rsi_query_net_parms.o \
    $(WLAN_CORE_SRC)/rsi_query_rssi.o \
    $(WLAN_CORE_SRC)/rsi_query_snr.o \
    $(WLAN_CORE_SRC)/rsi_register_interrupt_irq.o \
    $(WLAN_CORE_SRC)/rsi_scan.o \
    $(WLAN_CORE_SRC)/rsi_bg_scan.o \
    $(WLAN_CORE_SRC)/rsi_send_data.o \
    $(WLAN_CORE_SRC)/rsi_send_ludp_data.o \
    $(WLAN_CORE_SRC)/rsi_set_ap_config.o \
    $(WLAN_CORE_SRC)/rsi_set_certificate.o \
    $(WLAN_CORE_SRC)/rsi_set_eap.o \
    $(WLAN_CORE_SRC)/rsi_set_mac_addr.o \
    $(WLAN_CORE_SRC)/rsi_set_region.o \
    $(WLAN_CORE_SRC)/rsi_set_wepkey.o \
    $(WLAN_CORE_SRC)/rsi_sleep_timer.o \
    $(WLAN_CORE_SRC)/rsi_socket.o \
    $(WLAN_CORE_SRC)/rsi_socket_close.o \
    $(WLAN_CORE_SRC)/rsi_web_fields.o \
    $(WLAN_CORE_SRC)/rsi_load_web_page.o  \
    $(WLAN_CORE_SRC)/rsi_send_url_rsp.o  \
    $(WLAN_CORE_SRC)rsi_snmp_enable.o \
    $(WLAN_CORE_SRC)rsi_snmp_get_rsp.o \
    $(WLAN_CORE_SRC)rsi_snmp_get_next_rsp.o \
    $(WLAN_CORE_SRC)rsi_snmp_trap.o 
    #$(WLAN_CORE_SRC)/rsi_power_mode.o \
    $(WLAN_CORE_SRC)/rsi_sys_init.o\

BT_OBJS = $(BT_CORE_SRC)/rsi_bt_build_frame_descriptor.o \
	$(BT_CORE_SRC)/rsi_bt_api.o \
	$(BT_CORE_SRC)/rsi_bt_core.o \
	$(BT_CORE_SRC)/rsi_bt_generic.o \
	$(BT_CORE_SRC)/rsi_bt_spp.o \
	$(BT_REF_APPS_SRC)/bt_main.o \
	$(BT_REF_APPS_SRC)/bt_app.o \
	$(BT_REF_APPS_SRC)/rsi_bt_config_init.o \
	$(BT_REF_APPS_SRC)/rsi_bt_state_mc.o 

BLE_OBJS = $(BT_CORE_SRC)/rsi_bt_build_frame_descriptor.o \
    $(BT_CORE_SRC)/rsi_bt_generic.o \
    $(BT_CORE_SRC)/rsi_bt_register_interrupt_irq.o \
 	$(BLE_CORE_SRC)/rsi_ble_api.o \
 	$(BLE_CORE_SRC)/rsi_ble_core.o \
    $(BLE_CORE_SRC)/rsi_ble_gatt.o \
    $(BLE_REF_APPS_SRC)/rsi_ble_config_init.o \
 	$(BLE_REF_APPS_SRC)/ble_main.o \
 	$(BLE_REF_APPS_SRC)/rsi_ble_state_mc.o \
 	$(BLE_REF_APPS_SRC)/ble_app.o 

.c.o:
	$(RM) $@
	$(CC) $(CFLAGS)  -o $*.o  -c $*.c

all:  $(OBJS) $(ZB_OBJS) $(WLAN_OBJS) $(BT_OBJS) $(BLE_OBJS)
	$(CC) $(CFLAGS) $(LINKS) -o $(PROGNAME) $(OBJS) $(ZB_OBJS) $(WLAN_OBJS) $(BT_OBJS) $(BLE_OBJS)
	
wlan :  $(WLAN_OBJS) $(OBJS) 
	$(CC) $(CFLAGS) $(LINKS) -o $(PROGNAME) $(OBJS) $(WLAN_OBJS)

ble :  $(BLE_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $(LINKS) -o $(PROGNAME) $(OBJS) $(BLE_OBJS)

wlan_ble:  $(WLAN_OBJS) $(BLE_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $(LINKS) -o $(PROGNAME) $(OBJS) $(WLAN_OBJS) $(BLE_OBJS)

bt :  $(BT_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $(LINKS) -o $(PROGNAME) $(OBJS) $(BT_OBJS)

wlan_bt:  $(WLAN_OBJS) $(BT_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $(LINKS) -o $(PROGNAME) $(OBJS) $(WLAN_OBJS) $(BT_OBJS)

zb:  $(ZB_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $(LINKS) -o $(PROGNAME) $(OBJS) $(ZB_OBJS)

wlan_zb:  $(WLAN_OBJS) $(ZB_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $(LINKS) -o $(PROGNAME) $(OBJS) $(WLAN_OBJS) $(ZB_OBJS)

clean:
	$(RM) $(OBJS) $(ZB_OBJS) $(WLAN_OBJS) $(BT_OBJS) $(BLE_OBJS) $(PROGNAME) core *~
