1. Overview
  This folder contains reference project to execute in User Space
  (Windows/Linux). 
  This project uses binary messages to interface with the module

1.1 
 |================| 
 | Application    | 
 | -------------- | 
 | Core APIs      | 
 | -------------- |User Space 
 | Interface Layer| 
 | -------------- |
 |     HAL        |
 ==================


2. Interfaces supported
     UART
     USB-CDC

3. Supported modes
     WLAN only
     ZigBee only

4. Directory structure
   Application  : This folder contains following sample applications
       wlan     : Sample application for WLAN
       zb       : Sample application for ZigBee

5. Steps to build and run  
  Application  : 
      wlan     : 
         1. Set configurations in host/binary/apis/wlan/ref_apps/include/rsi_config.h
         2. Give command 'make wlan' in src folder.
         3. Executable generated is 'rsi_wsc_uart_app' 
         4. Run generated executable by giving command './rsi_wsc_uart_app' 
      zb       : 
         1. Set configurations in host/binary/apis/zb/ref_apps/include/rsi_zigb_config.h
         2. Give command 'make zigbee' in src folder.
         3. Executable generated is 'rsi_wsc_uart_app' 
         4. Run generated executable by giving command './rsi_wsc_uart_app' 
     
  
        

