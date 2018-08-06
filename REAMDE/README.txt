注意点：

1、SPI输出命令给WiFi模组后，会返回响应用Read_PKT()函数


备忘：


1、设置频段

wifi_main.c--->

retval = rsi_band(RSI_BAND); 

2、选择天线

wifi_main.c--->

retval = rsi_select_antenna(1,8,8);//1：外部UFL天线，8:2.4GHz增益，8:5GHz增益

3、UDP的opensocket的开启

wifi_main.c--->

OpenSocket("192.168.100.2",5002,5001,RSI_SOCKET_LUDP );是否需要

4、concurrent模式还是AP模式？？？







