#ifndef __CONFIG_H__
#define __CONFIG_H__ 
#include "sys.h"
#include "usart.h"

/*
读flash时候的状态
*/
typedef enum
{ 
	LOAD_PARA_CRC_ERROR = 0,
	LOAD_PARA_TOO_LONG_ERROR, //太长
	LOAD_PARA_SUCCESS
	
}FLASH_Load_Status;

/*
写flash时候的状态
*/
typedef enum
{ 
    WRITE_PARA_FAILED = 0,//保存失败
	WRITE_PARA_SUCCESS   //保存成功
}FLASH_Write_Status;

/*
写要发送的frame时候的状态
*/
typedef enum
{ 
    WRITE_FRAME_JOIN_SSID_TOO_LONG = 0,//SSID太长
	WRITE_FRAME_PSK_TOO_LONG,  //PSK太长
	
	WRITE_FRAME_SUCCESS
}FRAME_Write_Status;
/*
flash内存储数据的各种符号，包括分割、结束
*/
#define FLASH_LABLE_TYPE      u8
#define	FLASH_LABEL_END      ('\r')//结束标志
#define	FLASH_LABEL_SPLIT    ('\n')//分割



//*************************
//定义指令
//
//*************************
//  !!!!! 注意：每次添加新的指令都要到getHelp函数中添加说明文档
#define CMD_SET_JOIN_SSID      "SET_RSI_JOIN_SSID"  //设置SSID
#define CMD_SET_PSK            "SET_RSI_PSK"  //设置PSK

#define CMD_HELP               "HELP"//输出帮助
#define CMD_SAVE_ALL_PARA      "SAVE_ALL_PARA"//保存所有参数
#define CMD_RESET_SYSTEM       "RESET_SYSTEM"  //系统重启




#define RSI_JOIN_SSID_MAX_LENGTH   64  //最长支持的wifi名称byte位数
#define RSI_PSK_MAX_LENGTH         34  //最长支持的wifi名称byte位数
#define PARA_CAT_CH_MAX_LENGTH   (USART_REC_CMD_LEN+USART_REC_VAL_LEN+50)  //数据整合到一起后的长度u8

#define USART_REC_CMD_LEN  		 100  	//定义最大cmd接收字节数100
#define USART_REC_VAL_LEN  		 100  	//定义最大Value接收字节数100

#define RSI_JOIN_SSID_STRNAME "RSI_JOIN_SSID"
extern u8 RSI_JOIN_SSID[RSI_JOIN_SSID_MAX_LENGTH];  //要加入的ssid
#define RSI_PSK_STRNAME "RSI_PSK"
extern u8 RSI_PSK[RSI_PSK_MAX_LENGTH];  //要加入的ssid的psk@ PSK.If we are using WPA2, this is the key, In open mode NULL

#define FLASH_HEAD_LENGTH_BYTES        4   //flash头部存储的数据字节长          
#define FLASH_SAVE_ADDR_MAIN           ADDR_FLASH_SECTOR_5  //数据保存的开始地址(主)128KB，给程序留了4*16KB+64KB（扇区0-4）
#define FLASH_SAVE_ADDR_BACKUP         ADDR_FLASH_SECTOR_6  //数据保存备份开始地址128KB
#define FLASH_SAVE_SECTOR_MAIN         FLASH_Sector_5
#define FLASH_SAVE_SECTOR_BACKUP       FLASH_Sector_6


#define FLASH_SAVE_BYTE_MAX_LENGTH     (128*1024)//最多保存的数据字节数

//usart命令的处理
#define CMD_VALUE_SPLIT_CHAR           ' '  //CMD和数值的分割
#define CMD_VALUE_NOT_SPLIT_STA        0   //还没有到达分割点
#define CMD_VALUE_SPLITED_STA          1   //到达cmd和value分割点

typedef enum
{ 
    CMD_VALUE_SPLIT_ERROR = 0,//split失败
	CMD_VALUE_SPLIT_OK,   //split成功
	CMD_SPLIT_OK,         //只有cmd
	NONE_CMD_VALUE_MSG   //没有cmd和value信息
}CMD_VALUE_Split_Status;

typedef enum
{ 
    CMD_NOT_COMPLETED = 0, //cmd指令还没有完整
	CMD_COMPLETED   //cmd指令已经完整了
}CMD_Receive_Status;


extern u8 catPara[PARA_CAT_CH_MAX_LENGTH];



void writeSectorPara(void);//保存参数
u8 splitCmd(volatile CMD_QUEUE * pQueue,u8 * pCmd,u8 * pValue);
u8 dealCmdMsg(volatile CMD_QUEUE * pQueue);
u8 loadParaAndCheck(u8 * catPara,u32 startAddr);//读取并校验数据
u8 updateFrameParas(void);//更新数据帧内的参数
void getHelp(void);
#endif

