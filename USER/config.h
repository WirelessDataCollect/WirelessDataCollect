/**
  ******************************************************************************
  * @file    config.h
  * @author  zju.nesc.iotlab 浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    13-March-2019
  * @brief   parameters configuraton functions   参数配置方法
  ******************************************************************************
  */

#ifndef __CONFIG_H__
#define __CONFIG_H__ 

//-------------include---------------//
#include "sys.h"
#include "usart.h"


/** 
  * @brief  读flash时候的状态
  * @{
  */ 
typedef enum
{ 
	LOAD_PARA_CRC_ERROR = 0,  /*!< CRC校验失败>*/
	LOAD_PARA_TOO_LONG_ERROR, /*!< 参数太长>*/
	LOAD_PARA_POINTER_NULL,   /*!< 没有找到特定的地址>*/
	LOAD_PARA_SUCCESS         /*!< 读取参数成功>*/
	
}FLASH_Load_Status;
/**
  * @}
  */

/** 
  * @brief  写flash时候的状态
  * @{
  */ 
typedef enum
{ 
    WRITE_PARA_FAILED = 0,/*!< 保存失败>*/
	WRITE_PARA_SUCCESS   /*!< 保存成功>*/
}FLASH_Write_Status;
/**
  * @}
  */


/** 
  * @brief  写要发送的frame时候的状态
  * @{
  */ 
typedef enum
{ 
    WRITE_FRAME_JOIN_SSID_TOO_LONG = 0,/*!< SSID太长>*/
	WRITE_FRAME_PSK_TOO_LONG,  /*!< PSK太长>*/
	WRITE_FRAME_SUCCESS  /*!< 写成功>*/
}FRAME_Write_Status;
/**
  * @}
  */

/** 
  * @brief  板子运行的状态
  * @{
  */ 
typedef enum
{ 
    BOARD_INITING = 0,  /*!< 正在初始化>*/
	BOARD_INITED,       /*!< 初始化完成>*/
	BOARD_RUNNING,      /*!< 正在主程序运行>*/
}BOARD_Status;
/**
  * @}
  */

/** 
  * @brief  flash内存储数据的各种符号，包括分割、结束等
  * @{
  */
#define FLASH_LABLE_TYPE              u8        /*!< 分割Flash中数据的分隔符字节长度>*/
#define	FLASH_LABEL_END               ('\r')    /*!< 结束标志>*/
#define	FLASH_LABEL_SPLIT             ('\n')    /*!< 分割两个数据、IP>*/
#define	IP_GROUP_SPLIT                ('.')     /*!< !!在flash中仍然使用\n!! 串口设置时分割两个IP的小组，如命令"SET_SERVER_IP 192.168.0.1">*/
/**
  * @}
  */

/** 
  * @brief  定义串口指令相关
  * @note !!! 每次添加新的指令都要到getHelp函数中添加说明文档
  * @{
  */
/** !设置参数的命令*/
#define CMD_SET_JOIN_SSID      "SET_RSI_JOIN_SSID"   /*!< 设置SSID>*/
#define CMD_SET_PSK            "SET_RSI_PSK"         /*!< 设置PSK>*/
#define CMD_SET_NODE_ID        "SET_NODE_ID"         /*!< 设置节点id>*/
#define CMD_SET_SERVER_IP      "SET_SERVER_IP"       /*!< 设置私有云服务器IP>*/
#define CMD_SET_MASTER_CLK     "SET_MASTER_CLK"      /*!< 设置是否是主时钟>*/
/** !纯命令*/
#define CMD_HELP               "HELP"                /*!< 输出帮助>*/
#define CMD_GET_PARA           "GET_PARA"            /*!< 输出参数情况>*/
#define CMD_SAVE_ALL_PARA      "SAVE_ALL_PARA"       /*!< 保存所有参数>*/
#define CMD_RESET_SYSTEM       "RESET_SYSTEM"        /*!< 系统重启>*/
/**
  * @}
  */
  
/** 
  * @brief  可设参数的相关属性
  * @{
  */
#define RSI_JOIN_SSID_MAX_LENGTH   64        /*!< 最长支持的wifi名称字节长度>*/
#define RSI_PSK_MAX_LENGTH         34        /*!< 最长支持的wifi密码字节长度>*/
#define NODE_ID_2STR_MAX_LEN       3         /*!< id号转化为字符串后的最长长度，如255->"255"，对应修改nodeId数据类型>*/
#define PARA_CAT_CH_MAX_LENGTH     (USART_REC_CMD_LEN+USART_REC_VAL_LEN+50)  /*!< 数据整合到一起后的长度u8>*/

#define RSI_JOIN_SSID_STRNAME      "RSI_JOIN_SSID"   /*!< SSID的变量名>*/
extern u8 RSI_JOIN_SSID[RSI_JOIN_SSID_MAX_LENGTH];   /*!< ssid变量>*/

#define RSI_PSK_STRNAME            "RSI_PSK"    /*!< PSK的变量名>*/
extern u8 RSI_PSK[RSI_PSK_MAX_LENGTH];          /*!< PSK变量>*/

#define NODE_ID_STRNAME            "nodeId"     /*!< 节点ID号的变量名>*/
extern u8 nodeId;                               /*!< 节点ID号，需要对应修改NODE_ID_2STR_MAX_LEN>*/

#define SERVER_IP_STRNAME          "destIp_txrx"  /*!< 私有云服务器IP的变量名>*/
/**
  * @}
  */

/** 
  * @brief  FLASH的相关属性
  * @note   给程序留了4*16KB+64KB（扇区0-4）
  * @{
  */
#define FLASH_HEAD_LENGTH_BYTES        4                    /*!< flash头部存储的数据字节长度  >*/        
#define FLASH_SAVE_ADDR_MAIN           ADDR_FLASH_SECTOR_5  /*!< 保存数据的开始地址(主) >*/  
#define FLASH_SAVE_ADDR_BACKUP         ADDR_FLASH_SECTOR_6  /*!< 保存数据备份开始地址 >*/  
#define FLASH_SAVE_SECTOR_MAIN         FLASH_Sector_5       /*!< 主存储区：扇区5，共128KB  >*/ 
#define FLASH_SAVE_SECTOR_BACKUP       FLASH_Sector_6       /*!< 备份存储区：扇区6，共128KB  >*/ 
#define FLASH_SAVE_BYTE_MAX_LENGTH     (128*1024)           /*!< 最多保存的数据字节数，根据每个FLASH扇区的情况而定，5、6扇区存储空间128KB >*/
/**
  * @}
  */

/** 
  * @brief  USART/AP模式下的命令/信息长度，及分割符号
  * @{
  */
#define USART_REC_CMD_LEN  		   100  	     /*!< 定义最大cmd接收字节数100，UART和AP模式均存储在该处>*/
#define USART_REC_VAL_LEN  		   100  	     /*!< 定义最大Value接收字节数100，UART和AP模式均存储在该处>*/

#define CMD_VALUE_SPLIT_CHAR           ' '       /*!< CMD和数值的分割>*/
/**
  * @}
  */
 

/** 
  * @brief  模式代号，定义不同的模式的数字代号
  * @note   本设备只使用CLIENT和AP模式
  * @{
  */ 
extern u32 RSI_WIFI_OPER_MODE;                /*!< 模式>*/
#define RSI_WIFI_CLIENT_MODE_VAL       0      /*!< CLIENT（客户端）模式>*/
#define RSI_WIFI_P2P_MODE_VAL          1      /*!< P2P模式>*/
#define RSI_WIFI_ENTERPRISE_MODE_VAL   2      /*!< ENTERPRISE模式>*/
#define RSI_WIFI_AP_MODE_VAL           6      /*!< AP模式>*/
#define RSI_WIFI_PER_MODE_VAL          8      /*!< PER模式>*/
#define RSI_WIFI_CONCURRENT_MODE_VAL   9      /*!< CONCURRENT（协程）模式>*/
/**
  * @}
  */


/** 
  * @brief  AP名称
  * @{
  */ 
#define NODE_AP_NAME_HEAD       "SORL_WIRELESS_NODE_"  /*!< 节点作为AP的时候的名称前缀，后面加上nodeId>*/
/**
  * @}
  */
  
/** 
  * @brief  IP属性
  * @{
  */ 
#define IPV4_LENGTH                 4  /*!< IPV4的字节长度，如{192.168.3.1}>*/
#define IPV4_STR_LENGTH            15  /*!< IPV4的转化为字符串占用的byte个数，如192.169.0.1->"192.168.0.1"，占用11位,最多15位}>*/
#define IPV4_1GROUP_STR_LENGTH      3  /*!< IPV4的一个组的转化为字符串占用的byte个数，如192"192"，占用3位}>*/
/**
  * @}
  */
  
  
/** 
  * @brief  是否已经到达CMD和VAL的分割符
  * @{
  */ 
typedef enum{ 
    CMD_VALUE_NOT_SPLIT_STA      =     0,         /*!< 未到达分割点>*/
    CMD_VALUE_SPLITED_STA    					  /*!< 到达cmd和value分割点>*/
}CMD_VAL_Get_Split_sta;
/**
  * @}
  */

/** 
  * @brief  CMD和VAL分割情况
  * @{
  */ 
typedef enum
{ 
    CMD_VALUE_SPLIT_ERROR = 0,    /*!< 分割失败,表示没有指令或者分割指令失败>*/
	CMD_VALUE_SPLIT_OK,           /*!< 分割成功>*/
	CMD_SPLIT_OK,                 /*!< 获取CMD成功，只有纯命令>*/
	NONE_CMD_VALUE_MSG            /*!< **真的**没有cmd和value信息>*/
}CMD_VALUE_Split_Status;
/**
  * @}
  */

/** 
  * @brief  命令是否接受完毕（以\r\n结束）
  * @{
  */ 
typedef enum
{ 
    CMD_NOT_COMPLETED = 0,   /*!< cmd指令还没有完整>*/
	CMD_COMPLETED            /*!< cmd指令已经完整了>*/
}CMD_Receive_Status;
/**
  * @}
  */

//!缓存需要保存到Flash中的数据，包括数据长度、参数、分隔符、结束符、CRC等
extern u8 catPara[PARA_CAT_CH_MAX_LENGTH];
//!节点ID
extern u8 nodeId;
//!静态地址 或 DHCP动态地址，一般AP模式下静态，CLIENT模式下DHCP
extern u8 RSI_IP_CFG_MODE;
//!带宽，支持2.4GHz、5GHz、双频
extern u8 RSI_BAND;
//!节点运行状态  @enum BOARD_Status
extern u8 BOARD_STA;
//!节点的当前IP
extern u8 localhost[IPV4_LENGTH];
//!我是不是主时钟
extern u8 IAM_MASTER_CLOCK;

void writeSectorPara(void);
u8 splitCmd(volatile CMD_QUEUE * pQueue,u8 * pCmd,u8 * pValue);
void dealCmdMsg(volatile CMD_QUEUE * pQueue);
u8 loadParaAndCheck(u8 * catPara,u32 startAddr);
u8 updateFrameParas(void);
void getHelp(void);
void getPara(void);
void setFactory(void);
void loadParafromMainOrBackupFlash(void);
void setBoardSta(u8 sta);
u32 getParaLen(void);
#endif

