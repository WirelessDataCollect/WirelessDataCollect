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



### 2018-8-27

回滚到最初的接受命令放置在while中

因为在send数据时，也有spi，如果在中断中放入了spi，则会被打断，出现卡死的问题。


<del>
1、opensocket的ReadPKT重新使用（8-24删除了）

2、为了避免在中断中，Order_anal()函数中的checkPKT将IP更新命令和信息缓存check掉

原来的逻辑问题：OpenSocket放在Order_anal函数中。OpenSocket发送关闭原socket的信息----》等待返回信息 ----》  消息到来，但是无法打断中断（OpenSocket在中断中等待）
----》 Opensocket还在等待消息，直到等待时间到  ----》  再一次进入中断，Order_anal解析了数据，并将pending减1   ----》   OpenSocket始终没有接收到返回信息

现在的逻辑：Order_anal中，接收到数据IP和端口更新命令后，不进行关闭旧socket打开新socket。而是置位flag，告诉外界和中断（所以中断也不会check掉缓存）要更新IP和端口了。  ----》   在while中更新数据IP和端口    ----》flag清除。

3、在rsi_spi_send中加入了时间限定

如果time++超过50000次，则跳出。防止卡死。

</del>

### 2018-8-24

1、加入从时钟收到同步信号闪烁灯信号

2、删掉opensocket的readPKT（这里有问题，所以后面继续修改，不能删除）

因为在中断中调用了数据接收，会check掉

3、加入GET_TEST

用于返回本机ID给上位机

### 2018-8-13
1、添加设备对上位机命令的回复

以[0xa2,命令,设备id]的形式

2、不同设备不同通道的电流电压采集设置

以上位机命令的形式实现

### 2018-8-11
1、数据采集函数只有在开始发送命令收到后再开始。

定时器中断中的修改。

2、更新时钟时，LED2闪烁。

### 2018-8-9
1、wifi_send_package中的moduleSocket要改为dest

这里指定二楼远程ip和远程的端口。

2end_Sync_Time修改

下标调换，人看起来更加直观

不用改了，因为STM32是小端模式，小位数存在低地址，高位数存在高地址

3、destSocket_sync和moduleSocket_sync改成一样

4、led1和led2=0


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
	





