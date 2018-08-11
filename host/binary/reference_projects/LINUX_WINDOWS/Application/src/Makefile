# Makefile for WiSeConnect Application
TOP_DIR := $(PWD)
RM=/bin/rm -f
#CC=/work/venkateshl/venky/sam9/AT91SAM9G35-EK/atmel/arm-2007q1/bin/arm-none-linux-gnueabi-gcc
PROGNAME=rsi_wsc_uart_app
INCLUDES=  -I./ -I/work/colibri-2.6-kernel/include/
LINKS= -lpthread

CORE_SRC=../../../../apis/zb/core/src
REF_APPS_SRC=../../../../apis/zb/ref_apps/src/

WLAN_CORE_SRC=../../../../apis/wlan/core/src/
WLAN_REF_SRC=../../../../apis/wlan/ref_apps/src/
WLAN_HAL_SRC=../../../../apis/hal/src/
WLAN_INTF_SRC=../../../../apis/intf/spi/src/

CFLAGS= -g -Os -Wall -fno-strict-aliasing $(INCLUDES)
CFLAGS+= -I../include
CFLAGS+= -I../../../../apis/zb/core/include
CFLAGS+= -I../../../../apis/hal/include
CFLAGS+= -I../../../../apis/wlan/core/include
CFLAGS+= -I../../../../apis/wlan/ref_apps/include
CFLAGS+= -I../../../../apis/zb/ref_apps/include
CFLAGS+= -DENABLE_DEBUG_PRINTS
CFLAGS+= -DRSI_DEBUG_PRINT

CFLAGS+= -I../../../../apis/wlan/core/include/
CFLAGS+= -I../../../../apis/wlan/ref_apps/include/
CFLAGS+= -I../../../../apis/hal/include/
CFLAGS+= -I../../../../apis/intf/spi/include/
CFLAGS+= -I../../../../apis/intf/uart/include/

	CFLAGS+= -D UART_INTERFACE
ifeq ($(MAKECMDGOALS),apitest)
CFLAGS += -D ZB_API_TEST
CFLAGS+= -DZB_ONLY
CFLAGS+= -DZB_ENABLE
CFLAGS+= -DENABLE_ZB_NL
CFLAGS+= -DLINUX_PLATFORM
endif

ifeq ($(MAKECMDGOALS),wlan)
CFLAGS+= -D WLAN_ENABLE
endif

ifeq ($(MAKECMDGOALS),zigbee)
CFLAGS+= -DZB_ONLY
CFLAGS+= -DSWITCH_APP
CFLAGS+= -DZB_ENABLE
CFLAGS+= -DENABLE_ZB_NL
CFLAGS+= -DLINUX_PLATFORM
endif

OBJS = main.o \
		 rsi_hal_mcu_uart.o \
		 rsi_uart_frame_rd_wr.o  

ZB_OBJS = $(CORE_SRC)/rsi_zigb_frame_desc.o \
		 $(CORE_SRC)/rsi_zigb_api.o \
		 $(CORE_SRC)/rsi_zigb_utility.o \
		 $(CORE_SRC)/rsi_zigb_build_frame_descriptor.o \
	   	 $(CORE_SRC)/rsi_zigb_app_frame_process.o \
		 $(CORE_SRC)/rsi_zigb_execute_cmd.o \
		 $(REF_APPS_SRC)/rsi_zigb_app_cb_handler.o \
		 $(REF_APPS_SRC)/rsi_zigb_config.o \
		 $(REF_APPS_SRC)/rsi_zigb_api_test.o \
		 $(REF_APPS_SRC)/zigb_main.o \
		 $(WLAN_CORE_SRC)/rsi_lib_util.o \
		 $(CORE_SRC)/rsi_zigb_oper_mode.o \
		 $(REF_APPS_SRC)/rsi_zigb_init_oper_mode.o 

WLAN_OBJS = $(WLAN_REF_SRC)/wifi_main.o \
       $(WLAN_REF_SRC)/rsi_app_util.o \
       $(WLAN_REF_SRC)/rsi_config_init.o \
       $(WLAN_REF_SRC)/rsi_buildHttpExtendedHeader.o \
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
       $(WLAN_CORE_SRC)/rsi_execute_cmd.o \
       $(WLAN_CORE_SRC)/rsi_gpio_config.o \
       $(WLAN_CORE_SRC)/rsi_http_get.o \
       $(WLAN_CORE_SRC)/rsi_http_post.o \
       $(WLAN_CORE_SRC)/rsi_init.o \
       $(WLAN_CORE_SRC)/rsi_interrupt_handler.o \
       $(WLAN_CORE_SRC)/rsi_ip_param_set.o \
       $(WLAN_CORE_SRC)/rsi_join.o \
       $(WLAN_CORE_SRC)/rsi_lib_util.o \
       $(WLAN_CORE_SRC)/rsi_ltcp_conn_status.o \
       $(WLAN_CORE_SRC)/rsi_module_soft_reset.o \
       $(WLAN_CORE_SRC)/rsi_oper_mode.o \
       $(WLAN_CORE_SRC)/rsi_p2p_config.o \
       $(WLAN_CORE_SRC)/rsi_ping_request.o \
       $(WLAN_CORE_SRC)/rsi_power_mode.o \
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
       $(WLAN_CORE_SRC)/rsi_send_raw_data.o \
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
       $(WLAN_HAL_SRC)/rsi_hal_mcu_interrupt.o \
       $(WLAN_HAL_SRC)/rsi_hal_mcu_ioports.o \
       $(WLAN_HAL_SRC)/rsi_hal_mcu_spi.o \
       $(WLAN_HAL_SRC)/rsi_hal_mcu_timers.o \
			 $(WLAN_CORE_SRC)rsi_per_mode.o \
 			 $(WLAN_CORE_SRC)rsi_http_abort.o \
 			 $(WLAN_CORE_SRC)rsi_trigger_auto_config.o \
       $(WLAN_CORE_SRC)rsi_snmp_enable.o \
       $(WLAN_CORE_SRC)rsi_snmp_get_rsp.o \
       $(WLAN_CORE_SRC)rsi_snmp_get_next_rsp.o \
       $(WLAN_CORE_SRC)rsi_snmp_trap.o \
       $(WLAN_CORE_SRC)rsi_ftp_client.o 
#      $(WLAN_INTF_SRC)/rsi_spi_functs.o \
       $(WLAN_INTF_SRC)/rsi_spi_iface_init.o \
       $(WLAN_INTF_SRC)/rsi_spi_mem_rd_wr.o \
       $(WLAN_INTF_SRC)/rsi_spi_reg_rd_wr.o \
       $(WLAN_CORE_SRC)/rsi_sys_init.o\



.c.o:
	$(RM) $@
	$(CC) $(CFLAGS)  -o $*.o  -c $*.c

all: clean $(OBJS) $(ZB_OBJS) $(WLAN_OBJS) 
	$(CC) $(CFLAGS) $(LINKS) -o $(PROGNAME) $(OBJS) $(ZB_OBJS) $(WLAN_OBJS) 
wlan : clean $(WLAN_OBJS) $(OBJS) 
	$(CC) $(CFLAGS) $(LINKS) -o $(PROGNAME) $(OBJS) $(WLAN_OBJS)
zigbee : clean $(ZB_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $(LINKS) -o $(PROGNAME) $(OBJS) $(ZB_OBJS)
apitest: clean $(ZB_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $(LINKS) -o $(PROGNAME) $(OBJS) $(ZB_OBJS)

clean:
	$(RM) $(OBJS) $(ZB_OBJS) $(WLAN_OBJS) $(PROGNAME) core *~
