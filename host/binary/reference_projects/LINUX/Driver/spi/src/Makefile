#*HEADER*******************************************************************
#Copyright (c)
#All rights reserved
#This software embodies materials and concepts that are confidential
#to Redpine Signals and is made available solely pursuant to the terms
#of a written license agreement with Redpine Signals
#
#Project name : WiSeConnect
#Module name  : Linux SPI Driver
#File Name    : Makefile
#
#File Description:
#    This is the Makefile For RSI Linux SPI Driver
#        
#
#Author :
#
#Rev History:
#Ver        By             date       Description
#---------------------------------------------------------
#1.1        Srinivas                    Initial version
#---------------------------------------------------------
#*END*********************************************************************

#KERNELDIR=/work/venkateshl/venky/sam9/AT91SAM9G35-EK/atmel/linux-2.6.39
KERNELDIR=/work/Godavari/linux-2.6.30

ifeq ($(DRIVER_DIR),)
DRIVER_DIR=$(PWD)
endif

CORE_SRC=../../../../../apis/wlan/core/src
HAL_SRC=../../../../../apis/hal/src
INTF_SRC=../../../../../apis/intf/spi/src
INTF_INCUDE=$(DRIVER_DIR)/../../../../../apis/intf/spi/include
CORE_INCLUDE=$(DRIVER_DIR)/../../../../../apis/wlan/core/include
REF_APPS_INCLUDE=$(DRIVER_DIR)/../../../../../apis/wlan/ref_apps/include
COMMON_INCLUDE=$(DRIVER_DIR)/../../../../../reference_projects/LINUX/Driver/common/include/
COMMON_SRC=../../common/src

EXTRA_CFLAGS += -DLINUX 
EXTRA_CFLAGS += -DSPI_INTERFACE
#EXTRA_CFLAGS += -DENABLE_WMM_FEATURE

#specify the target platform
#EXTRA_CFLAGS += -DX86 
#EXTRA_CFLAGS += -DSAM9_G20
#EXTRA_CFLAGS += -DSAM9_G35
EXTRA_CFLAGS += -DSAM9_G45

#EXTRA_CFLAGS += -DRSI_DEBUG_PRINT
EXTRA_CFLAGS += -I$(CORE_INCLUDE)
EXTRA_CFLAGS += -I$(DRIVER_DIR)/../include
EXTRA_CFLAGS += -I$(INTF_INCUDE)
EXTRA_CFLAGS += -I$(COMMON_INCLUDE)
EXTRA_CFLAGS += -I$(REF_APPS_INCLUDE)
EXTRA_CFLAGS += -I$(KERNELDIR)/include
EXTRA_CFLAGS += -I$(KERNELDIR)
EXTRA_CFLAGS += -Wimplicit
EXTRA_CFLAGS += -w
EXTRA_CFLAGS += -Wstrict-prototypes

SRC_FILES :=  $(COMMON_SRC)/rsi_linux_netlink.o \
              $(COMMON_SRC)/rsi_net_device.o \
	            $(COMMON_SRC)/rsi_linux_specific.o \
              $(COMMON_SRC)/rsi_linux_data.o \
	      $(COMMON_SRC)/rsi_core_wmm.o \
	            $(INTF_SRC)/rsi_spi_frame_rd_wr.o \
	            $(INTF_SRC)/rsi_spi_functs.o \
              $(INTF_SRC)/rsi_spi_mem_rd_wr.o \
              $(INTF_SRC)/rsi_spi_reg_rd_wr.o \
              $(INTF_SRC)/rsi_spi_iface_init.o\
              $(CORE_SRC)/rsi_execute_cmd.o \
	            $(CORE_SRC)/rsi_build_frame_descriptor.o \
	            $(CORE_SRC)/rsi_send_boot_insn.o \
	            $(CORE_SRC)/rsi_gpio_config.o \
							$(CORE_SRC)/rsi_lib_util.o \
							rsi_hal_mcu_ioports.o \
	            rsi_hal_mcu_spi.o \

obj-m := $(INSTALLDIR)rpsspi.o
$(INSTALLDIR)rpsspi-objs :=  ${SRC_FILES}

all:
	@echo "Compiling driver code"
	make -C $(KERNELDIR) SUBDIRS=$(PWD) modules

clean:
	@echo "Cleaning driver binary files"
	rm -rf $(INSTALLDIR)rpsspi.* 
	rm -rf $(INSTALLDIR)*.rpsspi.*.*
	rm -rf *.o *.mod.* *.symvers
	rm -rf .rps*
	rm -rf .rsi*
	rm -rf .tmp_versions
	rm -rf modules.order
	rm -rf $(CORE_SRC)/.rsi*
	rm -rf $(INTF_SRC)/.rsi*
	rm -rf $(INTF_SRC)/*.o 
	rm -rf $(CORE_SRC)/*.o 
	rm -rf $(COMMON_SRC)/*.cmd 
