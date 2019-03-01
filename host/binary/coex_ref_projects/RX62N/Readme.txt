1. Overview
    This folder contains reference project for RX62N micro controller.
    Project files are provided for HEW IDE. This project uses binary messages to interface with the module

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
    SPI
    UART
    Selecting the inerface :
    1. Open host/binary/apis/wlan/ref_apps/include/rsi_config.h
    2. Assign RSI_UART or RSI_SPI to RSI_INTERFACE macro


3. Supported modes
    WLAN Only
    BLE Only
    WLAN+BLE
    BT Only
    WLAN+BT
    ZB Only
    WLAN+ZB

4. Directory structure
    build   : This folder contains all RX62N project related files
    hal     : This folder contains hal files ported for RX62N platform 

5. Steps to build and run  

    a. Choosing the configuration :
     1. Select/configure WLAN related parameters(mode, ssid etc.) as per API guide in 
        host/binary/apis/wlan/ref_apps/include/rsi_config.h
     2. Select/configure BT_LE related parameters as per API guide in 
        host/binary/apis/ble/ref_apps/include/rsi_ble_config.h
     3. Select/configure BT related parameters as per API guide in 
        host/binary/apis/bt/ref_apps/include/rsi_bt_config.h

    b. Choosing the mode : 
      Defualt project build(files, defines) provided supports WLAN+BLE. 
      For other configurations, following changes have to be done in the project provided.
      WLAN : 
         1. Select RSI_COEX_MODE 0 and DISABLE RSI_NO_WLAN_MODE in host/binary/apis/wlan/ref_apps/include/rsi_config.h
         2. Remove BLE_ENABLE macro from defines in toolchain options

      BT_LE : 
         1. Select RSI_COEX_MODE 13 and ENABLE RSI_NO_WLAN_MODE in host/binary/apis/wlan/ref_apps/include/rsi_config.h

      WLAN+BT_LE : 
         1. Select RSI_COEX_MODE 13 and DISABLE RSI_NO_WLAN_MODE in host/binary/apis/wlan/ref_apps/include/rsi_config.h

      BT : 
         1. Select RSI_COEX_MODE 5 and ENABLE RSI_NO_WLAN_MODE in host/binary/apis/wlan/ref_apps/include/rsi_config.h
         2. Add BT_ENABLE macro in the defines in toolchain options
         3. Remove BLE_ENABLE macro in the defines in toolchain options
         4. Exclude following files from compilation which are mentioned below
              ble_app.c
              ble_main.c
              rsi_ble_api.c
              rsi_ble_config_init.c
              rsi_ble_core.c
              rsi_ble_gatt.c
         5. Add following BT related files for compilation
              host/binary/apis/bt/ref_apps/src/bt_main.c
              host/binary/apis/bt/ref_apps/src/bt_app.c
              host/binary/apis/bt/core/src/rsi_bt_core.c
              host/binary/apis/bt/core/src/rsi_bt_api.c
              host/binary/apis/bt/core/src/rsi_bt_spp.c
              host/binary/apis/bt/ref_apps/src/rsi_bt_state_mc.c
              host/binary/apis/bt/ref_apps/src/rsi_bt_config_init.c

      WLAN+BT : 
         1. Select RSI_COEX_MODE 5 and DISABLE RSI_NO_WLAN_MODE in host/binary/apis/wlan/ref_apps/include/rsi_config.h
         2. Add BT_ENABLE macro in the defines in toolchain options
         3. Remove BLE_ENABLE macro in the defines in toolchain options
         4. Exclude files from compilation which are mentioned below
              ble_app.c
              ble_main.c
              rsi_ble_api.c
              rsi_ble_config_init.c
              rsi_ble_core.c
              rsi_ble_gatt.c
							rsi_bt_coex_execute_cmd.c
         5. Add following BT related files for compilation
              host/binary/apis/bt/ref_apps/src/bt_main.c
              host/binary/apis/bt/ref_apps/src/bt_app.c
              host/binary/apis/bt/core/src/rsi_bt_core.c
              host/binary/apis/bt/core/src/rsi_bt_api.c
              host/binary/apis/bt/core/src/rsi_bt_spp.c
              host/binary/apis/bt/ref_apps/src/rsi_bt_state_mc.c
              host/binary/apis/bt/ref_apps/src/rsi_bt_config_init.c
      
      ZB : 
         1. Select RSI_COEX_MODE 3 and ENABLE RSI_NO_WLAN_MODE in host/binary/apis/wlan/ref_apps/include/rsi_config.h
         2. Add ZB_ENABLE macro in the defines in toolchain options
         3. Remove BLE_ENABLE macro in the defines in toolchain options
         4. Exclude files from compilation which are mentioned below
              ble_app.c
              ble_main.c
              rsi_ble_api.c
              rsi_ble_config_init.c
              rsi_ble_core.c
              rsi_ble_gatt.c
							rsi_bt_build_frame_descriptor.c
							rsi_bt_generic.c
							rsi_bt_register_interrupt_irq.c
							rsi_bt_coex_execute_cmd.c
         5. Add following ZB related files for compilation
				 			host/binary/apis/zb/core/src/rsi_zigb_frame_desc.c
							host/binary/apis/zb/core/src/rsi_zigb_api.c
							host/binary/apis/zb/core/src/rsi_zigb_utility.c
							host/binary/apis/zb/core/src/rsi_zigb_build_frame_descriptor.c
							host/binary/apis/zb/core/src/rsi_zigb_app_frame_process.c
							host/binary/apis/zb/core/src/rsi_zigb_oper_mode.c
							host/binary/apis/zb/core/src/rsi_zigb_delay.c
							host/binary/apis/zb/ref_apps/src/rsi_zigb_app_cb_handler.c
							host/binary/apis/zb/ref_apps/src/rsi_zigb_config.c
							host/binary/apis/zb/ref_apps/src/rsi_zigb_state_mc.c
							host/binary/apis/zb/ref_apps/src/rsi_zigb_api_test.c

      WLAN+ZB : 
         1. Select RSI_COEX_MODE 3 and DISABLE RSI_NO_WLAN_MODE in host/binary/apis/wlan/ref_apps/include/rsi_config.h
         2. Add ZB_ENABLE macro in the defines in toolchain options
         3. Remove BLE_ENABLE macro in the defines in toolchain options
         4. Exclude files from compilation which are mentioned below
              ble_app.c
              ble_main.c
              rsi_ble_api.c
              rsi_ble_config_init.c
              rsi_ble_core.c
              rsi_ble_gatt.c
							rsi_bt_build_frame_descriptor.c
							rsi_bt_generic.c
							rsi_bt_register_interrupt_irq.c
         5. Add following ZB related files for compilation
				 			host/binary/apis/zb/core/src/rsi_zigb_frame_desc.c
							host/binary/apis/zb/core/src/rsi_zigb_api.c
							host/binary/apis/zb/core/src/rsi_zigb_utility.c
							host/binary/apis/zb/core/src/rsi_zigb_build_frame_descriptor.c
							host/binary/apis/zb/core/src/rsi_zigb_app_frame_process.c
							host/binary/apis/zb/core/src/rsi_zigb_oper_mode.c
							host/binary/apis/zb/core/src/rsi_zigb_delay.c
							host/binary/apis/zb/ref_apps/src/rsi_zigb_app_cb_handler.c
							host/binary/apis/zb/ref_apps/src/rsi_zigb_config.c
							host/binary/apis/zb/ref_apps/src/rsi_zigb_state_mc.c
							host/binary/apis/zb/ref_apps/src/rsi_zigb_api_test.c

    c. Building and Running:
         1. Select 'Build All' from 'Build' menu in IDE
         2. This will compile and load application onto RX62N
