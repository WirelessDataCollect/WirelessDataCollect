## Wireless Data Collection System
* Attention : the /host is removed in the repository

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

# 2、版本修改内容：

### 2018-8-7

1、修改创建LUDP socket函数

OpenLudpSocket(destIp_txrx,destSocket_txrx,moduleSocket_txrx,&socketDescriptor_txrx);

2、添加区分主时钟和从时钟的#if

用IAM_MASTER_CLOCK区分

3、添加局域网PC端发送同步时间的命令

4、receive_udp_package函数修改

不区分主时钟和从时钟设备，都对命令进行相同的反应

5、判断队列是否大于等于UDP_SEND_SIZE - 10

if(queue_length(adc_queue) >= UDP_SEND_SIZE - 10 )//我觉得>=比较好，万一没来得及发现==UDP_SEND_SIZE - 10的情况呢

6、在定时器中断服务函数中加入了时钟同步程序

Send_Sync_Time()

7、在order_anay中创建和服务器连接的socket

case GET_REMOTE_IP_PORT:            //主机地址
	memcpy(destIp_txrx,&arr[1],4);
	memcpy(&destSocket_txrx,&arr[5],2);
	rsi_socket_close(socketDescriptor_txrx, moduleSocket_txrx);//关闭掉原来的socket
	OpenLudpSocket(destIp_txrx,destSocket_txrx,moduleSocket_txrx,&socketDescriptor_txrx);
	break;
 