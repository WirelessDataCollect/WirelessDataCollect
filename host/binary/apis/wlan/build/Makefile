# Makefile for WiSeConnect Application
TOP_DIR := $(PWD)
RM=/bin/rm -f
PROGNAME=rsi_wsc_app
INCLUDES=  -I./ -I/work/colibri-2.6-kernel/include/
LINKS= -lpthread

REF_APPS_SRC =../ref_apps/src
CORE_SRC=../core/src
HAL_SRC=../../hal/src
INTF_SPI_SRC=../../intf/spi/src
INTF_UART_SRC=../../intf/uart/src
INTF_USB_SRC=../../intf/usb/src
CFLAGS= -g -Os -Wall -fno-strict-aliasing $(INCLUDES)
#CFLAGS+= -DENABLE_DEBUG_PRINTS
CFLAGS+= -DWLAN_ENABLE
CFLAGS+= -I../core/include/
CFLAGS+= -I../ref_apps/include/
CFLAGS+= -I../../hal/include/
CFLAGS+= -I../../intf/spi/include/
CFLAGS+= -I../../intf/usb/include/
#CFLAGS+= -DLINUX_PLATFORM
#CFLAGS+= -DRSI_DEBUG_PRINT


OBJS = main.o \
       $(REF_APPS_SRC)/wifi_main.o \
       $(REF_APPS_SRC)/rsi_app_util.o \
       $(REF_APPS_SRC)/rsi_config_init.o \
       $(REF_APPS_SRC)/rsi_buildHttpExtendedHeader.o \
			 $(CORE_SRC)/rsi_bootup_config.o \
			 $(CORE_SRC)/rsi_send_boot_insn.o \
			 $(CORE_SRC)/rsi_build_frame_descriptor.o \
			 $(CORE_SRC)/rsi_select_antenna.o \
       $(CORE_SRC)/rsi_api.o \
       $(CORE_SRC)/rsi_sys_init.o\
       $(CORE_SRC)/rsi_band.o \
       $(CORE_SRC)/rsi_cfg_enable.o \
       $(CORE_SRC)/rsi_cfg_get.o \
       $(CORE_SRC)/rsi_cfg_save.o \
       $(CORE_SRC)/rsi_disconnect.o \
       $(CORE_SRC)/rsi_dns_query.o \
       $(CORE_SRC)/rsi_dns_server.o \
       $(CORE_SRC)/rsi_execute_cmd.o \
       $(CORE_SRC)/rsi_gpio_config.o \
       $(CORE_SRC)/rsi_http_get.o \
       $(CORE_SRC)/rsi_http_post.o \
       $(CORE_SRC)/rsi_http_post_data.o \
       $(CORE_SRC)/rsi_init.o \
       $(CORE_SRC)/rsi_interrupt_handler.o \
       $(CORE_SRC)/rsi_ip_param_set.o \
       $(CORE_SRC)/rsi_join.o \
       $(CORE_SRC)/rsi_lib_util.o \
       $(CORE_SRC)/rsi_ltcp_conn_status.o \
       $(CORE_SRC)/rsi_module_soft_reset.o \
       $(CORE_SRC)/rsi_oper_mode.o \
       $(CORE_SRC)/rsi_p2p_config.o \
       $(CORE_SRC)/rsi_ping_request.o \
       $(CORE_SRC)/rsi_power_mode.o \
       $(CORE_SRC)/rsi_query_conn_status.o \
       $(CORE_SRC)/rsi_query_fw_version.o \
       $(CORE_SRC)/rsi_query_go_parms.o \
       $(CORE_SRC)/rsi_query_mac_address.o \
       $(CORE_SRC)/rsi_query_net_parms.o \
       $(CORE_SRC)/rsi_query_rssi.o \
       $(CORE_SRC)/rsi_query_snr.o \
       $(CORE_SRC)/rsi_register_interrupt_irq.o \
       $(CORE_SRC)/rsi_scan.o \
       $(CORE_SRC)/rsi_bg_scan.o \
       $(CORE_SRC)/rsi_send_data.o \
       $(CORE_SRC)/rsi_send_ludp_data.o \
       $(CORE_SRC)/rsi_send_raw_data.o \
       $(CORE_SRC)/rsi_set_ap_config.o \
       $(CORE_SRC)/rsi_set_certificate.o \
       $(CORE_SRC)/rsi_set_eap.o \
       $(CORE_SRC)/rsi_set_mac_addr.o \
       $(CORE_SRC)/rsi_set_region.o \
       $(CORE_SRC)/rsi_set_wepkey.o \
       $(CORE_SRC)/rsi_sleep_timer.o \
       $(CORE_SRC)/rsi_socket.o \
       $(CORE_SRC)/rsi_socket_close.o \
       $(CORE_SRC)/rsi_web_fields.o \
       $(CORE_SRC)/rsi_load_web_page.o  \
       $(CORE_SRC)/rsi_send_url_rsp.o  \
       $(CORE_SRC)/rsi_snmp_trap.o  \
       $(CORE_SRC)/rsi_snmp_get_rsp.o  \
       $(CORE_SRC)/rsi_snmp_get_next_rsp.o  \
       $(CORE_SRC)/rsi_http_abort.o  \
       $(CORE_SRC)/rsi_trigger_auto_config.o  \
       $(CORE_SRC)/rsi_webpage_clear_files.o  \
       $(CORE_SRC)/rsi_per_mode.o  \
       $(CORE_SRC)/rsi_ftp_client.o \
       $(CORE_SRC)/rsi_mdns_sd.o \
       $(CORE_SRC)/rsi_smtp_client.o \
       $(CORE_SRC)/rsi_http_client_put.o \
       $(CORE_SRC)/rsi_pop3_client.o \
       $(CORE_SRC)/rsi_read_data.o \
       $(HAL_SRC)/rsi_hal_mcu_interrupt.o \
       $(HAL_SRC)/rsi_hal_mcu_ioports.o \
       $(HAL_SRC)/rsi_hal_mcu_spi.o \
       $(HAL_SRC)/rsi_hal_mcu_timers.o \
			 $(INTF_SPI_SRC)/rsi_spi_frame_rd_wr.o \
       $(INTF_SPI_SRC)/rsi_spi_functs.o \
       $(INTF_SPI_SRC)/rsi_spi_iface_init.o \
       $(INTF_SPI_SRC)/rsi_spi_mem_rd_wr.o \
       $(INTF_SPI_SRC)/rsi_spi_reg_rd_wr.o \
			 $(INTF_UART_SRC)/rsi_uart_frame_rd_wr.o \
			 $(INTF_USB_SRC)/rsi_usb_frame_rd_wr.o \
			 $(INTF_USB_SRC)/rsi_usb_mem_rd_wr.o \


.c.o:
	$(RM) $@
	$(CC) $(CFLAGS)  -o $*.o  -c $*.c

all: $(OBJS)
	$(CC) $(CFLAGS) $(LINKS) -o $(PROGNAME) $(OBJS) 

clean:
	$(RM)  $(OBJS) $(PROGNAME) core *~
