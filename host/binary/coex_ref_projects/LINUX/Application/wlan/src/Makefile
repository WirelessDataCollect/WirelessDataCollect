# Makefile for WiSeConnect Application
TOP_DIR := $(PWD)
RM=/bin/rm -f
CC=/work/Godavari/arm-2007q1/bin/arm-none-linux-gnueabi-gcc
CC=gcc
PROGNAME=rsi_wsc_app
INCLUDES=  -I./ -I/work/colibri-2.6-kernel/include/
LINKS= -lpthread

REF_APPS_SRC =../../../../../apis/wlan/ref_apps/src/
CORE_SRC=../../../../../apis/wlan/core/src/
HAL_SRC=../../../../../apis/hal/src/
CFLAGS= -g -Os -Wall
CFLAGS+= -DENABLE_DEBUG_PRINTS
CFLAGS+= -I../include
CFLAGS+= -I../../../../../apis/wlan/core/include
CFLAGS+= -I../../../../../apis/hal/include
CFLAGS+= -I../../../../../apis/intf/spi/include
CFLAGS+= -I../../../../../apis/wlan/ref_apps/include
CFLAGS+= -DRSI_DEBUG_PRINT
CFLAGS+= -DLINUX_PLATFORM
CFLAGS+= -DWLAN_ENABLE
CFLAGS+= -DENABLE_WLAN_NL
CFLAGS+= -Dm32
#CFLAGS+= -DUART_INTERFACE
CFLAGS+= -DSPI_INTERFACE

-include fips.objs

OBJS = main.o \
 $(REF_APPS_SRC)rsi_app_util.o \
 $(REF_APPS_SRC)setregion_countryinfo.o \
 $(REF_APPS_SRC)rsi_config_init.o \
 $(REF_APPS_SRC)wifi_main.o \
 $(REF_APPS_SRC)rsi_user_store_config_init.o\
 $(REF_APPS_SRC)sensor_data.o \
 $(REF_APPS_SRC)rsi_buildHttpExtendedHeader.o \
 $(CORE_SRC)rsi_set_certificate.o \
 $(CORE_SRC)rsi_register_interrupt_irq.o \
 $(CORE_SRC)rsi_select_antenna.o \
 $(CORE_SRC)rsi_set_ap_config.o \
 $(CORE_SRC)rsi_api.o \
 $(CORE_SRC)rsi_band.o \
 $(CORE_SRC)rsi_cfg_enable.o \
 $(CORE_SRC)rsi_cfg_get.o \
 $(CORE_SRC)rsi_cfg_save.o \
 $(CORE_SRC)rsi_disconnect.o \
 $(CORE_SRC)rsi_dns_query.o \
 $(CORE_SRC)rsi_dns_server.o \
 $(CORE_SRC)rsi_http_get.o \
 $(CORE_SRC)rsi_http_post.o \
 $(CORE_SRC)rsi_init.o \
 $(CORE_SRC)rsi_ip_param_set.o \
 $(CORE_SRC)rsi_ipv6_param_set.o \
 $(CORE_SRC)rsi_join.o \
 $(CORE_SRC)rsi_ltcp_conn_status.o \
 $(CORE_SRC)rsi_module_soft_reset.o \
 $(CORE_SRC)rsi_oper_mode.o \
 $(CORE_SRC)rsi_p2p_config.o \
 $(CORE_SRC)rsi_power_mode.o \
 $(CORE_SRC)rsi_query_conn_status.o \
 $(CORE_SRC)rsi_query_fw_version.o \
 $(CORE_SRC)rsi_query_go_parms.o \
 $(CORE_SRC)rsi_query_mac_address.o \
 $(CORE_SRC)rsi_query_net_parms.o \
 $(CORE_SRC)rsi_query_rssi.o \
 $(CORE_SRC)rsi_query_snr.o \
 $(CORE_SRC)rsi_scan.o \
 $(CORE_SRC)rsi_bg_scan.o \
 $(CORE_SRC)rsi_send_data.o \
 $(CORE_SRC)rsi_send_ludp_data.o \
 $(CORE_SRC)rsi_set_eap.o \
 $(CORE_SRC)rsi_set_mac_addr.o \
 $(CORE_SRC)rsi_sleep_timer.o \
 $(CORE_SRC)rsi_socket.o \
 $(CORE_SRC)rsi_socket_close.o \
 $(CORE_SRC)rsi_snmp_enable.o \
 $(CORE_SRC)rsi_snmp_get_rsp.o \
 $(CORE_SRC)rsi_roam_params.o \
 $(CORE_SRC)rsi_ht_caps.o \
 $(CORE_SRC)rsi_wmm_ps.o \
 $(CORE_SRC)rsi_wps_method.o \
 $(CORE_SRC)rsi_per_mode.o \
 $(CORE_SRC)rsi_snmp_get_next_rsp.o \
 $(CORE_SRC)rsi_snmp_trap.o \
 $(CORE_SRC)rsi_web_fields.o \
 $(CORE_SRC)rsi_load_web_page.o \
 $(CORE_SRC)rsi_set_wepkey.o \
 $(CORE_SRC)rsi_lib_util.o \
 $(CORE_SRC)rsi_wireless_fwupgrade.o \
 $(CORE_SRC)rsi_json_create.o \
 $(CORE_SRC)rsi_json_erase_file.o \
 $(CORE_SRC)rsi_webpage_clear_files.o \
 $(CORE_SRC)rsi_webpage_erase_file.o \
 $(CORE_SRC)rsi_bootup_config.o \
 $(CORE_SRC)rsi_multicast.o \
 $(CORE_SRC)rsi_multicast_filter.o \
 $(CORE_SRC)rsi_debug_prints.o \
 $(CORE_SRC)rsi_send_url_rsp.o \
 $(CORE_SRC)rsi_set_region.o \
 $(CORE_SRC)rsi_rejoin_params.o \
 $(CORE_SRC)rsi_psk.o \
 $(CORE_SRC)rsi_user_store_config.o \
 $(CORE_SRC)rsi_set_region_ap.o \
 $(CORE_SRC)rsi_ping_request.o \
 $(CORE_SRC)rsi_send_websocket_data.o \
 $(CORE_SRC)rsi_per_stats.o \
 $(CORE_SRC)rsi_bytes_sent_count.o \
 $(CORE_SRC)rsi_uart_flow_control.o \
 $(CORE_SRC)rsi_rf_current_mode.o \
 $(CORE_SRC)rsi_socket_config.o \
 $(CORE_SRC)rsi_http_abort.o \
 $(CORE_SRC)rsi_trigger_auto_config.o \
 $(CORE_SRC)rsi_http_credentials.o \
 $(CORE_SRC)rsi_fwup_frm_host.o \
 $(CORE_SRC)rsi_ftp_client.o \
 $(CORE_SRC)rsi_sntp_client.o \
 $(CORE_SRC)rsi_mdns_sd.o \
 rsi_hal_mcu_interrupt.o \
 rsi_ioctl_app.o \
 measure_throughputs.o \
 rsi_linux_apis.o \
 rsi_nl_app.o 

.c.o:
	$(RM) $@
	$(CC) $(CFLAGS)   -o $*.o  -c $*.c

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LINKS) -o $(PROGNAME)  

fips: $(OBJS) $(OBJS_FIPS)
	$(CC) $(CFLAGS)  $(OBJS) $(OBJS_FIPS) $(LINKS) -o $(PROGNAME)

clean:
	$(RM) $(OBJS) $(PROGNAME) core *~
