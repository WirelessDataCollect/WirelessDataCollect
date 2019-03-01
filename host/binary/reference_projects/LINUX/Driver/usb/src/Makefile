#*HEADER*******************************************************************
#Copyright (c)
#All rights reserved
#This software embodies materials and concepts that are confidential
#to Redpine Signals and is made available solely pursuant to the terms
#of a written license agreement with Redpine Signals
#
#Project name : WiSeConnect
#Module name  : Linux USB Driver
#File Name    : Makefile
#
#File Description:
#    This is the Makefile For RSI Linux USB Driver
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
KERNELDIR=/usr/src/kernels/3.3.4-5.fc17.i686.PAE/
KERNELDIR=/usr/src/kernels/3.6.10-4.fc18.i686.PAE/
KERNELDIR=/usr/src/kernels/`uname -r`/


ifeq ($(DRIVER_DIR),)
DRIVER_DIR=$(PWD)
endif

CORE_SRC=../../../../../apis/wlan/core/src
INTF_SRC=../../../../../apis/wlan/usb/src
INTF_INCUDE=$(DRIVER_DIR)/../../../../../apis/intf/usb/include
CORE_INCLUDE=$(DRIVER_DIR)/../../../../../apis/wlan/core/include
REF_APPS_INCLUDE=$(DRIVER_DIR)/../../../../../apis/wlan/ref_apps/include
COMMON_INCLUDE=$(DRIVER_DIR)/../../../../../reference_projects/LINUX/Driver/common/include/
COMMON_SRC=../../common/src

EXTRA_CFLAGS += -DLINUX 
EXTRA_CFLAGS += -DUSB_INTERFACE
#EXTRA_CFLAGS += -DENABLE_WMM_FEATURE

EXTRA_CFLAGS += -Dm32

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
EXTRA_CFLAGS += -Wall
EXTRA_CFLAGS += -Wstrict-prototypes

SRC_FILES :=  $(COMMON_SRC)/rsi_linux_netlink.o \
              $(COMMON_SRC)/rsi_net_device.o \
	            $(COMMON_SRC)/rsi_linux_specific.o \
              $(COMMON_SRC)/rsi_linux_data.o \
              $(COMMON_SRC)/rsi_core_wmm.o \
              $(CORE_SRC)/rsi_send_boot_insn.o \
              $(CORE_SRC)/rsi_lib_util.o \
	            rsi_hal_mcu_usb.o 

obj-m := $(INSTALLDIR)rpsusb.o
$(INSTALLDIR)rpsusb-objs :=  ${SRC_FILES}

all:
	@echo "Compiling driver code"
	make -C $(KERNELDIR) SUBDIRS=$(PWD) modules

clean:
	@echo "Cleaning driver binary files"
	rm -rf $(INSTALLDIR)rpsusb.* 
	rm -rf $(INSTALLDIR)*.rpsusb.*.*
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
	rm -rf $(COMMON_SRC)/.*.cmd 
