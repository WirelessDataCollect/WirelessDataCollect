# 1、备忘

### 1、设置频段

wifi_main.c--->

retval = rsi_band(RSI_BAND); 

### 2、选择天线

wifi_main.c--->

retval = rsi_select_antenna(1,8,8);//1：外部UFL天线，8:2.4GHz增益，8:5GHz增益

# 2、程序框图

* 主程序

Initialization初始化     ---->   创建数据收发txrx的socket和同步sync的socket   ------>     接收来自局域网中PC的命令       ----->

设置主机地址        ----->      设置同步时钟，Time_Sync_Flag=1     ------->     设置允许发送信息     ----->      

第一次可能发送一个只包含同步时间的信息，Time_Sync_Flag=0        ---->       后面正常发送信息

* 定时器中断

1、1ms采集一次数据

2、如果是主时钟设备，每SYNC_INTERVAL_TIME*1ms发送一次时钟同步信号

# 3、系统命令
## 3.1 串口/AP模式命令

```cpp
/** !设置参数的命令*/
#define CMD_SET_JOIN_SSID      "SET_RSI_JOIN_SSID"   /*!< 设置SSID>*/
#define CMD_SET_PSK            "SET_RSI_PSK"         /*!< 设置PSK>*/
#define CMD_SET_NODE_ID        "SET_NODE_ID"         /*!< 设置节点id>*/
#define CMD_SET_SERVER_IP      "SET_SERVER_IP"       /*!< 设置私有云服务器IP>*/
/** !纯命令*/
#define CMD_HELP               "HELP"                /*!< 输出帮助>*/
#define CMD_GET_PARA           "GET_PARA"            /*!< 输出参数情况>*/
#define CMD_SAVE_ALL_PARA      "SAVE_ALL_PARA"       /*!< 保存所有参数>*/
#define CMD_RESET_SYSTEM       "RESET_SYSTEM"        /*!< 系统重启>*/
```

## 3.2 上位机-节点交互

```cpp
#define  GET_TIME_SYNC_PC           0xa1   /*!< 来自上位机的同步信号>*/
#define  RETURN_INFO                0xa2   /*!< 返回信息>*/
#define  GET_TEST_NAME              0xa3   /*!< 获取测试名称>*/
#define  GET_TIME_SYNC_MAIN_CLOCK   0xa4   /*!< 来自主机的同步信号>*/
#define  GET_WIFI_SEND_EN           0xa5   /*!< 数据采集和发送使能>*/
#define  GET_WIFI_SEND_DISABLE      0xa6   /*!< 数据采集和发送失能>*/
#define  GET_CHANNEL_MODEL          0xa7   /*!< 设置通道的电流/电压模式>*/
#define  GET_CAN_FILTER_ID          0xa8   /*!< CAN数据采集的ID列表设置>*/
#define  GET_REMOTE_IP_PORT         0xa9   /*!< 设置发送数据对象（私有云服务器）IP>*/
#define  PAGING                     0xaa   /*!< 寻呼信号>*/
```
