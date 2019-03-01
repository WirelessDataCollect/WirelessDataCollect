1. Overview
   This folder contains reference project to execute coex mode in user space
   for Linux. In the current release support for windows is not there.
   This project uses binary messages to interface with the module.

    a. High level architecture 
    |================| 
    | Application    |
    | -------------- | 
    | Coex Framework |  
    | -------------- | 
    | Core APIs      | 
    | ============== |
    | Interface Layer| 
    | -------------- | 
    |     HAL        |
    ==================


2. Interfaces supported
     UART
     USB-CDC
     1. Open host/binary/apis/wlan/ref_apps/include/rsi_config.h
     2. Select RSI_INTERFACE as RSI_UART
     3. Select proper(USB/ACM) value for RSI_UART_DEVICE

3. Supported modes
     WLAN Only
     BT_LE Only
     WLAN+BT_LE Coex
     BT Only
     WLAN+BT Coex
     ZB Only
     WLAN+ZB Coex

4. Directory structure
     src/main.c : Contains platform related code 
     src/hal : hal layer ported for Linux
     include : platform related include files

5. Steps to build and run  

    a. Choosing the configuration :
     1. Select/configure WLAN related parameters(mode, ssid etc.) as per API guide in 
        host/binary/apis/wlan/ref_apps/include/rsi_config.h
     2. Select/configure BT_LE related parameters as per API guide in 
        host/binary/apis/ble/ref_apps/include/rsi_ble_config.h
     3. Select/configure BT related parameters as per API guide in 
        host/binary/apis/bt/ref_apps/include/rsi_bt_config.h

    b. Choosing the mode : 
      WLAN : 
         1. Select RSI_COEX_MODE 0 and DISABLE RSI_NO_WLAN_MODE in host/binary/apis/wlan/ref_apps/include/rsi_config.h
         2. Give command 'make wlan' in src folder

      BT_LE : 
         1. Select RSI_COEX_MODE 13 and ENABLE RSI_NO_WLAN_MODE in host/binary/apis/wlan/ref_apps/include/rsi_config.h
         2. Give command 'make wlan_ble' in src folder

      WLAN+BT_LE : 
         1. Select RSI_COEX_MODE 13 and DISABLE RSI_NO_WLAN_MODE in host/binary/apis/wlan/ref_apps/include/rsi_config.h
         2. Give command 'make wlan_ble' in src folder

      BT : 
         1. Select RSI_COEX_MODE 5 and ENABLE RSI_NO_WLAN_MODE in host/binary/apis/wlan/ref_apps/include/rsi_config.h
         2. Give command 'make wlan_bt' in src folder

      WLAN+BT : 
         1. Select RSI_COEX_MODE 5 and DISABLE RSI_NO_WLAN_MODE in host/binary/apis/wlan/ref_apps/include/rsi_config.h
         2. Give command 'make wlan_bt' in src folder

      ZB : 
         1. Select RSI_COEX_MODE 3 and ENABLE RSI_NO_WLAN_MODE in host/binary/apis/wlan/ref_apps/include/rsi_config.h
         2. Give command 'make zb' in src folder

      WLAN+ZB : 
         1. Select RSI_COEX_MODE 3 and DISABLE RSI_NO_WLAN_MODE in host/binary/apis/wlan/ref_apps/include/rsi_config.h
         2. Give command 'make wlan_zb' in src folder

    c. Running :
         1. Executable generated is 'rsi_wsc_uart_app' 
         2. Run generated executable by giving command './rsi_wsc_uart_app' 
