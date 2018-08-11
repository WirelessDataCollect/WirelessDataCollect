1. Overview
  This folder contains reference project for linux based platforms. 
  This project uses binary messages to interface with the module

1.1 
 |================| 
 | Application    | 
 | -------------- | User Space
 | Core APIs      | 
 | ============== |
 | Interface Layer| 
 | -------------- | Kernel Space
 |     HAL        |
 ==================

 Applicaiton and core APIs will run in user space
 Interface layer and HAL will run in kernel space

1.2

 |=================|  |=================|  |=================|  |=================|  |=================| 
 | WLAN Application|  | BT Application  |  | BLE Application |  | ZB Application  |  | UART Application| 
 | --------------- |  | --------------- |  | --------------- |  | --------------- |  | --------------- | Applications
 | Core APIs       |  | Core APIs       |  | Core APIs       |  | Core APIs       |  | Core APIs       | 
 |=================|  |=================|  |=================|  |=================|  |=================|
       
 =======================================================================================================
 =====================================| Netlink sockets and IOCTLs |====================================
 =======================================================================================================


                                           |=================|  
                                           | Interface Layer | 
                                           | --------------- | Driver
                                           |      HAL        | 
                                           |=================|

 Applications will communicate to driver through netlink sockets and IOCTLs


2. Interfaces supported
  SPI
  USB
  UART
  USB-CDC

3. Supported modes
  WLAN only
  ZB only
  BT only
  BLE only
  WLAN-ZB coex
  WLAN-BLE coex
  WLAN-BT coex

4. Directory structure
  Application  : This folder contains following sample applications
      wlan     : Sample application for WLAN
      bt       : Sample application for BT
      ble      : Sample application for BLE
      zb       : Sample application for ZigBee
      uart     : Sample application for uart to interact with UART interface

  Driver       : Contains following folders
      common   : Contains common driver files for all interfaces
      spi      : Contains sample driver files specific to SPI interface
      uart     : Contains sample driver files specific to uart interface
      usb      : Contains sample driver files specific to usb interface

5. Steps to build 
  Application  : 
      wlan     : 
         1. Set configurations in host/binary/apis/wlan/ref_apps/include/rsi_config.h
         2. Give command 'make' in wlan/src folder.
         3  Executable generated is 'rsi_wsc_app' 
      bt       : 
         1. Set configurations in host/binary/apis/bt/ref_apps/include/rsi_bt_config.h
         2. Give command 'make' in bt/src folder.
         3  Executable generated is 'rsi_wsc_bt_app' 
      ble      : 
         1. Set configurations in host/binary/apis/ble/ref_apps/include/rsi_ble_config.h
         2. Give command 'make' in ble/src folder.
         3  Executable generated is 'rsi_wsc_ble_app' 
      zb       : 
         1. Set configurations in host/binary/apis/zb/ref_apps/include/rsi_zigb_config.h
         2. Give command 'make' in zb/src folder.
         3  Executable generated is 'rsi_wsc_zb_app' 
      uart     : 
         1. Give command 'make' in uart/src folder.
         2  Executable generated is 'rsi_serial' 

  Driver:
      common   :
         Contains common driver files for all interfaces
      spi      :
         1. Set KERNELDIR to toolchain path for SPI  
         2. Enable SAM9_G20/SAM9_G35/SAM9_G45 flag based on the the spi host
         3. set the cross compiler path in the file Driver/spi/src/make
         4. Give command './make' in Driver/spi/src
         5. kernel module generated is 'rpsspi.ko'
      uart     :
         1. Set KERNELDIR to kernel path
         2. Give command 'make' in Driver/uart/src
         3. kernel module generated is 'rpsuart.ko'
      usb      :
         1. Set KERNELDIR to kernel path
         2. Give command 'make' in Driver/uart/src
         3. kernel module generated is 'rpsusb.ko'

6. Steps to run single protocol modes
  Driver       :
      spi      : insert spi kernel ko module by giving command 'insmod rpsspi.ko'
      uart     : insert uart kernel ko module by giving command 'insmod rpsuart.ko'
      usb      : insert usb kernel ko module by giving command 'insmod rpsusb.ko'
  Application  :
      wlan     : run generated executable by giving command './rsi_wsc_app' 
      bt       : run generated executable by giving command './rsi_wsc_bt_app' 
      ble      : run generated executable by giving command './rsi_wsc_ble_app' 
      zb       : run generated executable by giving command './rsi_wsc_zb_app' 
      uart     : run generated executable by giving command './rsi_serial' and then run executable './rsi_wsc_app'

7. Steps to run coex modes
      WLAN-ZB  :
          1. Insert kernel ko module for SPI/USB/UART/USB-CDC
          2. Run generated executable by giving command './rsi_wsc_zb_app' 
          3. Run generated executable by giving command './rsi_wsc_app'
      WLAN-BT  :
          1. Insert kernel ko module for SPI/USB/UART/USB-CDC
          2. Run generated executable by giving command './rsi_wsc_bt_app' 
          3. Run generated executable by giving command './rsi_wsc_app'
      WLAN-BLE :
          1. Insert kernel ko module for SPI/USB/UART/USB-CDC
          2. Run generated executable by giving command './rsi_wsc_ble_app' 
          3. Run generated executable by giving command './rsi_wsc_app'

  NOTE: To run coex mode in UART/USB-CDC interface after these steps run executable './rsi_serial'


