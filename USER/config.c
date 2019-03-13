/**
  ******************************************************************************
  * @file    config.c
  * @author  zju.nesc.iotlab 浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    13-March-2019
  * @brief   parameters configuraton functions   参数配置方法
  ******************************************************************************
  */

//-------------include---------------//
#include "config.h"
#include "stmflash.h"
#include "usart.h"
#include "string.h"
#include "crc.h"
#include "typetrans.h"
#include "userwifi.h"
#include "core_cm4.h"
#include "rsi_api.h"
#include <stdlib.h>
#include <stdio.h>

u8   RSI_JOIN_SSID[RSI_JOIN_SSID_MAX_LENGTH] = "418_Lab_5G";             /*!< WIFI名称>*/
u8   RSI_PSK[RSI_PSK_MAX_LENGTH]             = "518518518";              /*!< WIFI密码>*/
u8   nodeId                                  = 1;                        /*!< 节点ID，0-255>*/
u32  RSI_WIFI_OPER_MODE                      = RSI_WIFI_CLIENT_MODE_VAL; /*!< CLIENT或者AP模式>*/
u8   RSI_IP_CFG_MODE                         = RSI_DHCP_IP_MODE;         /*!< @ RSI_DHCP_IP_MODE or RSI_STATIC_IP_MODE >*/
u8   RSI_BAND                                = RSI_DUAL_BAND;            /*!< @ RSI_BAND_2P4GHZ or RSI_BAND_5GHZ or RSI_DUAL_BAND>*/
u8   BOARD_STA                               = BOARD_INITING;            /*!< 板子的状态>*/
u8   catPara[PARA_CAT_CH_MAX_LENGTH]         = {0};                      /*!< 存储连接后的数据>*/
u8   localhost[IPV4_LENGTH]                  = {0};                      /*!< 本地ip>*/


/**
  * @brief  下载系统运行所需的参数
  * @param  sta：板子状态
  *          @arg BOARD_INITING:正在初始化
  *          @arg BOARD_INITED:初始化完成
  *          @arg BOARD_RUNNING:正在主程序运行
  * @retval 存储参数的数组的字节长度，包括总长度市值、数据、分隔符、crc、结束符等
  */
void setBoardSta(u8 sta){
	BOARD_STA  = sta;
}

/**
  * @brief  下载系统运行所需的参数
  * @param  startAddr：Flash起始地址
  * @retval 存储参数的数组的字节长度，包括总长度市值、数据、分隔符、crc、结束符等
  */
u32 getCatParaChLenInFlash(u32 startAddr){
	u32 catParaChLen;
	if(FLASH_HEAD_LENGTH_BYTES==4){//32bits保存
		catParaChLen = (u32)STMFLASH_ReadWord(startAddr);
	}else if(FLASH_HEAD_LENGTH_BYTES==2){  //16bits保存
		catParaChLen = (u32)STMFLASH_ReadHalfWord(startAddr);
	}else if(FLASH_HEAD_LENGTH_BYTES==1){  //8bits保存
		catParaChLen = (u32)STMFLASH_ReadByte(startAddr);
	}
	return catParaChLen;
}

/**
  * @brief  读取扇区的参数，并解析、校验
  * @param  catPara：存储读取的参数的数组指针
  * @param  startAddr：参数读取的起始地址
  *          @arg FLASH_SAVE_ADDR_MAIN：主存储扇区起始地址
  *          @arg FLASH_SAVE_ADDR_BACKUP：备份存储扇区起始地址
  * @retval 参数读取状态
  *          @arg LOAD_PARA_CRC_ERROR
  *          @arg LOAD_PARA_TOO_LONG_ERROR
  *          @arg LOAD_PARA_POINTER_NULL
  *          @arg LOAD_PARA_SUCCESS
  */
u8 loadParaAndCheck(u8 * catPara,u32 startAddr){
	/*先读出长度*/
	u32 catParaChLen = getCatParaChLenInFlash(startAddr);
	#if PRINT_UART_LOG
	printf("Para Array Length : %d\r\n",catParaChLen);
	#endif
	if(catParaChLen>=PARA_CAT_CH_MAX_LENGTH){
//		#if PRINT_UART_LOG
//		printf("Load Para Too Long Error!\r\n");
//		#endif
		return LOAD_PARA_TOO_LONG_ERROR;
	}
	memset(catPara,0,PARA_CAT_CH_MAX_LENGTH);//全部赋值0
	STMFLASH_ReadBytes(startAddr,catPara,catParaChLen);//读取main区中所有数据
	/*CRC校验*/
	#if PRINT_UART_LOG
	printf("Checking CRC...\r\n");
	#endif
	CRC_TYPE crc = CalCrc(0, (c8 *)catPara,catParaChLen- sizeof(FLASH_LABLE_TYPE) - FLASH_CRC_BYTE_LENGTH,0x8005);
	/*计算得到crc转化为字符串，长度固定，高位补0*/
	u8 crcStr[FLASH_CRC_BYTE_LENGTH+1];memset(crcStr,'0',FLASH_CRC_BYTE_LENGTH);crcStr[FLASH_CRC_BYTE_LENGTH]=0;//初始化"00000\0"
	u8 * crcStrItoa = itoa(crc);
	memcpy((char *)crcStr,crcStrItoa,strlen((c8*)crcStrItoa));//转化为字符串
	/*获取在flash中的crc字符串*/
	u8 crcStrFlash[FLASH_CRC_BYTE_LENGTH+1]={0};memcpy(crcStrFlash,catPara+catParaChLen-sizeof(FLASH_LABLE_TYPE)-FLASH_CRC_BYTE_LENGTH,FLASH_CRC_BYTE_LENGTH);
	#if PRINT_UART_LOG
	printf("CRC Computed : %s \r\nCRC in Flash : %s\r\n",crcStr,crcStrFlash);
	#endif
	if(strcmp((c8*)crcStr,(c8*)crcStrFlash) != 0){//对比
		#if PRINT_UART_LOG
		printf("CRC Check Error!\r\n");
		#endif
		return LOAD_PARA_CRC_ERROR;
	}else{
		#if PRINT_UART_LOG
		printf("CRC Check Correct!\r\n");
		#endif
	}
	#if PRINT_UART_LOG
	printf("Paras Unzipping...\r\n");
	#endif
	/*分割数据*/
	u32 paraStartAddr =(u32) (catPara + FLASH_HEAD_LENGTH_BYTES);//数据存储开始的位置，在数组中的下标
	/**SSID*/
	u32 splitAddr = (u32) strchr((c8 *)(paraStartAddr),FLASH_LABEL_SPLIT);//得到分隔符的地址
	memcpy((u8 *)RSI_JOIN_SSID,(u8 *)paraStartAddr,splitAddr - paraStartAddr);*(RSI_JOIN_SSID+splitAddr - paraStartAddr) = 0;//最后放一个0
	paraStartAddr = splitAddr+1;//开始下一个数据
	#if PRINT_UART_LOG
	printf("RSI_JOIN_SSID : %s\r\n",RSI_JOIN_SSID);
	#endif
	/*PSK*/
	splitAddr = (u32) strchr((c8 *)(paraStartAddr),FLASH_LABEL_SPLIT);//得到分隔符的地址
	memcpy((u8 *)RSI_PSK,(u8 *)paraStartAddr,splitAddr - paraStartAddr);*(RSI_PSK+splitAddr - paraStartAddr) = 0;//最后放一个0
	paraStartAddr = splitAddr+1;//开始下一个数据
	#if PRINT_UART_LOG
	printf("RSI_PSK : %s\r\n",RSI_PSK);
	#endif
	/*nodeId*/
	splitAddr = (u32) strchr((c8 *)(paraStartAddr),FLASH_LABEL_SPLIT);//得到分隔符的地址
	u8 nodeIdStrTemp[NODE_ID_2STR_MAX_LEN+1]={0};memcpy(nodeIdStrTemp,(u8 *)paraStartAddr,splitAddr - paraStartAddr); //拷贝到strTemp空间
	nodeId =(u8)atoi((c8 *)nodeIdStrTemp);
	paraStartAddr = splitAddr+1;//开始下一个数据
	#if PRINT_UART_LOG
	printf("nodeId : %d\r\n",nodeId);
	#endif	
	/*Server Ip  （destIp_txrx）*/
	u8 ipStrTemp[IPV4_1GROUP_STR_LENGTH+1]={0};//缓存一个组，如"192\0"
	for(u8 i = 0;i<4;i++){
		splitAddr = (u32) strchr((c8 *)(paraStartAddr),FLASH_LABEL_SPLIT);//得到分隔符的地址
		if(splitAddr == NULL){//防止出现找不到分隔符的问题
			destIp_txrx[0]=DESTIP_TXRX_GROUP1;destIp_txrx[1]=DESTIP_TXRX_GROUP2;
			destIp_txrx[2]=DESTIP_TXRX_GROUP3;destIp_txrx[3]=DESTIP_TXRX_GROUP4;
			return LOAD_PARA_POINTER_NULL;
		}
		memset(ipStrTemp,0,IPV4_1GROUP_STR_LENGTH+1);//清零
		memcpy(ipStrTemp,(u8 *)paraStartAddr,splitAddr - paraStartAddr); //拷贝到strTemp空间
		destIp_txrx[i] =(u8)atoi((c8 *)ipStrTemp);
		paraStartAddr = splitAddr+1;//开始下一个
	}
	#if PRINT_UART_LOG
	printf("destIp_txrx : %d.%d.%d.%d\r\n",destIp_txrx[0],destIp_txrx[1],destIp_txrx[2],destIp_txrx[3]);
	#endif
	return LOAD_PARA_SUCCESS;
}


/**
  * @brief  利用loadParaAndCheck得到主存储区或者备份存储区的数据
  * @param  None
  * @retval None
  */
void loadParafromMainOrBackupFlash(void){
	#if PRINT_UART_LOG
	printf("Load Paras Start ...\r\n");
	printf("Loading Main Flash Paras...\r\n");
	#endif
	if(loadParaAndCheck(catPara,FLASH_SAVE_ADDR_MAIN) != LOAD_PARA_SUCCESS){//下载参数不成功
		#if PRINT_UART_LOG
		printf("Loading Main Flash Paras Unsuccessfully!\r\n");
		printf("Loading Backup Flash Paras...\r\n");
		#endif
		if(loadParaAndCheck(catPara,FLASH_SAVE_ADDR_BACKUP) != LOAD_PARA_SUCCESS){
			#if PRINT_UART_LOG
			printf("Loading Backup Flash Paras Unsuccessfully!\r\n");
			#endif			
		}else{
			#if PRINT_UART_LOG
			printf("Loading Main Flash Paras Successfully!\r\n");
			#endif				
		}
	}else{
		#if PRINT_UART_LOG
		printf("Loading Main Flash Paras Successfully!\r\n");
		#endif	
	}
}

/**
  * @brief  写入字（4字节）数据，改变（INC增加）写地址WriteAddr
  * @param  pBuff：要写入的数据的指针
  * @param  WriteAddr：要写入的Flash地址
  * @param  WordLen：数据字（32位）长
  * @retval 写入状态
  *          @arg WRITE_PARA_FAILED
  *          @arg WRITE_PARA_SUCCESS
  */
u8 writeFlashWordsIncAddr(u32 * pBuff,u32 * WriteAddr,u16 WordLen){
	for(int i =0;i<WordLen;i+=1){
		if(FLASH_ProgramByte(*WriteAddr,*(pBuff + i)) != FLASH_COMPLETE){//写入数据		 
			return WRITE_PARA_FAILED;	//写入异常
		}
		*WriteAddr += 4;//4byte为单位
	}
	return WRITE_PARA_SUCCESS;
}

/**
  * @brief  写入字（4字节）数据，不改变（INC增加）写地址WriteAddr
  * @param  pBuff：要写入的数据的指针
  * @param  WriteAddr：要写入的Flash地址
  * @param  WordLen：数据字（32位）长
  * @retval 写入状态
  *          @arg WRITE_PARA_FAILED
  *          @arg WRITE_PARA_SUCCESS
  */
u8 writeFlashWords(u32 * pBuff,u32 WriteAddr,u16 WordLen){
	u32 writeAddrNow = WriteAddr;
	for(int i =0;i<WordLen;i+=1){
		if(FLASH_ProgramByte(writeAddrNow,*(pBuff + i)) != FLASH_COMPLETE){//写入数据		 
			return WRITE_PARA_FAILED;	//写入异常
		}
		writeAddrNow += 4;//4byte为单位
	}
	return WRITE_PARA_SUCCESS;
}

/**
  * @brief  写入字节数据，改变（INC增加）写地址WriteAddr
  * @param  pBuff：要写入的数据的指针
  * @param  WriteAddr：要写入的Flash地址
  * @param  WordLen：数据字节（8位）长
  * @retval 写入状态
  *          @arg WRITE_PARA_FAILED
  *          @arg WRITE_PARA_SUCCESS
  */
u8 writeFlashByteIncAddr(u8 * pBuff,u32 * WriteAddr,u16 u8Len){
	for(int i =0;i<u8Len;i+=1){
		if(FLASH_ProgramByte(*WriteAddr,*(pBuff + i))!=FLASH_COMPLETE){ //写入数据		
			return WRITE_PARA_FAILED;	//写入异常
		}
		*WriteAddr += 1;//1byte为单位
	}
	return WRITE_PARA_SUCCESS;
}


/**
  * @brief  写入字节数据，不改变（INC增加）写地址WriteAddr
  * @param  pBuff：要写入的数据的指针
  * @param  WriteAddr：要写入的Flash地址
  * @param  WordLen：数据字节（8位）长
  * @retval 写入状态
  *          @arg WRITE_PARA_FAILED
  *          @arg WRITE_PARA_SUCCESS
  */
u8 writeFlashByte(u8 * pBuff,u32 WriteAddr,u16 u8Len){
	u32 writeAddrNow = WriteAddr;
	for(int i =0;i<u8Len;i+=1){
		if(FLASH_ProgramByte(writeAddrNow,*(pBuff + i))!=FLASH_COMPLETE)//写入数据
		{
			return WRITE_PARA_FAILED;	//写入异常
		}
		writeAddrNow += 1;//1byte为单位
	}
	return WRITE_PARA_SUCCESS;
}

/**
  * @brief  获取保存所有数据所需的空间，包括数据长度、分隔符、数据、结束符
  * @note   根据当前的参数情况获取，不固定
  * @param  None
  * @retval 存储参数总字节长度
  */
u32 getParaLen(void){
	u16 catChLen = 0;
	/*总字节长*/
	catChLen += FLASH_HEAD_LENGTH_BYTES;
	/*SSID*/
	catChLen += strlen((c8*)RSI_JOIN_SSID);
	/*分隔符*/
	catChLen += sizeof(FLASH_LABLE_TYPE); 
	/*PSK*/
	catChLen += strlen((c8*)RSI_PSK);
	/*分隔符*/
	catChLen += sizeof(FLASH_LABLE_TYPE);
	/*nodeId，转化为字符串后的长度，如23->"23"，则为长度2*/
	catChLen += strlen((c8 *)itoa(nodeId)); 
	/*分隔符*/
	catChLen += sizeof(FLASH_LABLE_TYPE);
	/*IP*/
	catChLen += strlen((c8 *)itoa(destIp_txrx[0]));//IP第1组
	catChLen += sizeof(FLASH_LABLE_TYPE);
	catChLen += strlen((c8 *)itoa(destIp_txrx[1]));//IP第2组
	catChLen += sizeof(FLASH_LABLE_TYPE); 
	catChLen += strlen((c8 *)itoa(destIp_txrx[2]));//IP第3组
	catChLen += sizeof(FLASH_LABLE_TYPE);
	catChLen += strlen((c8 *)itoa(destIp_txrx[3]));//IP第4组
	catChLen += sizeof(FLASH_LABLE_TYPE);
	/*CRC校验*/
	catChLen += FLASH_CRC_BYTE_LENGTH;//加入一个CRC校验

	/*结束符*/
	catChLen += sizeof(FLASH_LABLE_TYPE); //结束符号占用1byte
//#if PRINT_UART_LOG	
//	printf("strlen(RSI_JOIN_SSID) : %d\r\n",strlen((c8*)RSI_JOIN_SSID));
//	printf("FLASH_LABEL_SPLIT : %d\r\n",sizeof(FLASH_LABLE_TYPE));
//	printf("strlen(RSI_PSK) : %d\r\n",strlen((c8*)RSI_PSK));
//	printf("CRC_TYPE : %d\r\n",FLASH_CRC_BYTE_LENGTH);
//	printf("FLASH_LABEL_END : %d\r\n",sizeof(FLASH_LABLE_TYPE));
//#endif
	return 	catChLen;
}

/**
  * @brief  将所有要保存的数据都连接起来,中间用分隔符分开
  * @param  None
  * @retval 数据的长度，不包括最后的'\0'
  *         0：表示分配失败
  */
u32 getCatPara(void){
	/*获取要保存的参数的字节长度*/
	u32 catParaLen = getParaLen();
	#if PRINT_UART_LOG
	printf("catParaLen = %d\r\n",catParaLen);
	#endif	
	u32 i=0;
	//存chLen
	for(;i<FLASH_HEAD_LENGTH_BYTES;i++){
		*(catPara+i) = (u8)(catParaLen>>(8*i));
	}
	//存ssid
	memcpy(catPara+i,RSI_JOIN_SSID,strlen((c8*)RSI_JOIN_SSID));i += strlen((c8*)RSI_JOIN_SSID);
	*(catPara+i) = FLASH_LABEL_SPLIT;i += sizeof(FLASH_LABLE_TYPE);//分隔符1byte
	//存PSK
	memcpy(catPara+i,RSI_PSK,strlen((c8*)RSI_PSK));i += strlen((c8*)RSI_PSK);
	*(catPara+i) = FLASH_LABEL_SPLIT;i += sizeof(FLASH_LABLE_TYPE);//分隔符1byte
	//存nodeId
	u8 nodeIdStr[NODE_ID_2STR_MAX_LEN+1] = {0};strcpy((char *)nodeIdStr,(c8 *)itoa(nodeId));//转化为Str
	memcpy((char *)(catPara+i),(c8 *)nodeIdStr,strlen((c8*)nodeIdStr));i += strlen((c8*)nodeIdStr);//拷贝
	*(catPara+i) = FLASH_LABEL_SPLIT;i += sizeof(FLASH_LABLE_TYPE);//分隔符1byte
	//存IP，包括四个byte"IP1\nIP2\nIP3\nIP4"，IPV4_STR_LENGTH = 15,包括中间的分割符
	//1.创建,注：由于itoa指向一个地址，所以不能用4个指针同时指向，会造成指向最有一个ip组
	u8 ip1[IPV4_1GROUP_STR_LENGTH+1]={0};strcpy((char *)ip1,(c8 *)itoa(destIp_txrx[0]));
	u8 ip2[IPV4_1GROUP_STR_LENGTH+1]={0};strcpy((char *)ip2,(c8 *)itoa(destIp_txrx[1]));
	u8 ip3[IPV4_1GROUP_STR_LENGTH+1]={0};strcpy((char *)ip3,(c8 *)itoa(destIp_txrx[2]));
	u8 ip4[IPV4_1GROUP_STR_LENGTH+1]={0};strcpy((char *)ip4,(c8 *)itoa(destIp_txrx[3]));
	//2.写入数组
	memcpy((char *)(catPara+i),ip1,strlen((c8 *)ip1));i += strlen((c8 *)ip1);
	*(catPara+i) = FLASH_LABEL_SPLIT;i += sizeof(FLASH_LABLE_TYPE);//分隔符1byte
	memcpy((char *)(catPara+i),ip2,strlen((c8 *)ip2));i += strlen((c8 *)ip2);
	*(catPara+i) = FLASH_LABEL_SPLIT;i += sizeof(FLASH_LABLE_TYPE);//分隔符1byte	
	memcpy((char *)(catPara+i),ip3,strlen((c8 *)ip3));i += strlen((c8 *)ip3);
	*(catPara+i) = FLASH_LABEL_SPLIT;i += sizeof(FLASH_LABLE_TYPE);//分隔符1byte
	memcpy((char *)(catPara+i),ip4,strlen((c8 *)ip4));i += strlen((c8 *)ip4);
	*(catPara+i) = FLASH_LABEL_SPLIT;i += sizeof(FLASH_LABLE_TYPE);//分隔符1byte
	//存crc
	CRC_TYPE crc = CalCrc(0, (c8 *)catPara,catParaLen- FLASH_CRC_BYTE_LENGTH - sizeof(FLASH_LABLE_TYPE),0x8005);//得到crc,把结束符号和crc位都去掉
	#if PRINT_UART_LOG
	printf("GET CRC VAL : %d\r\n",crc);
	#endif
	u8 * crcStr = itoa(crc);
	u8 crcStrKeepZero[FLASH_CRC_BYTE_LENGTH+1] = {0};
	memset(crcStrKeepZero,'0',FLASH_CRC_BYTE_LENGTH);//'0'...'0''\0'
	memcpy(crcStrKeepZero,crcStr,strlen((c8 *)crcStr));//不会擅自在后面加'\0'
	memcpy(catPara+i,crcStrKeepZero,strlen((c8*)crcStrKeepZero));i += strlen((c8*)crcStrKeepZero);//crcStr
	#if PRINT_UART_LOG
	printf("GET CRC STR VAL : %s\r\n",crcStrKeepZero);
	#endif
//	for(u16 i_this;i_this<sizeof(CRC_TYPE);i++,i_this++){//存crc16
//		*(catPara+i) = (u8)(crc>>(8*i_this));
//	}
	*(catPara+i) = FLASH_LABEL_END;i += sizeof(FLASH_LABLE_TYPE);//结尾
	*(catPara+i) = '\0';//不需要也可以，calloc初始化的时候已经全部初始化为0
	#if PRINT_UART_LOG
	printf("catPara : %s len : %d\r\n",catPara+FLASH_HEAD_LENGTH_BYTES,strlen((c8*)(catPara+FLASH_HEAD_LENGTH_BYTES)));
	#endif
	
	if(catParaLen-FLASH_HEAD_LENGTH_BYTES == strlen((c8 *) (catPara + FLASH_HEAD_LENGTH_BYTES))){
	#if PRINT_UART_LOG
		printf("LEN IS CORRECT!\r\n");
	#endif
	}else{
	#if PRINT_UART_LOG
		printf("LEN %d(Real : %d) IS NOT CORRECT!\r\n",strlen((c8 *) (catPara + FLASH_HEAD_LENGTH_BYTES)),catParaLen-FLASH_HEAD_LENGTH_BYTES);
	#endif
	}
	return catParaLen;
}

/**
  * @brief  写保存所有参数的数据到主和备份扇区
  * @param  None
  * @retval None
  */
void writeSectorPara(void){
	u32 catParaLen = getCatPara();
//	if(catParaLen){//如果长度是0，说明保存数据的数组分配失败了。不写，直接返回	
//		printf("\r\nCALLOC Failed!\r\nStop Writing Flash!\r\n");	
//		return;
//	}
	FLASH_Status status =FLASH_EraseSector(FLASH_SAVE_SECTOR_MAIN,VoltageRange_3);//擦除掉变量主存储区的所有数据
	if(status != FLASH_COMPLETE){//未成功擦除数据，保存失败
	#if PRINT_UART_LOG
		printf("Main flash Erased Unsuccessfully!\r\n");
	#endif
	}else{
	#if PRINT_UART_LOG
		printf("Main flash Erased Successfully!\r\n");
	#endif
	}
	if(writeFlashByte(catPara,FLASH_SAVE_ADDR_MAIN,catParaLen) == WRITE_PARA_FAILED){ //失败
	#if PRINT_UART_LOG
		printf("Main flash Writen Unsuccessfully!\r\n");
	#endif
	}else{
	#if PRINT_UART_LOG
		printf("Main flash Writen Successfully!\r\n\r\n");
	#endif
	}
	status = FLASH_EraseSector(FLASH_SAVE_SECTOR_BACKUP,VoltageRange_3);//擦除掉变量主存储区的所有数据
	if(status != FLASH_COMPLETE){//未成功擦除数据，保存失败
	#if PRINT_UART_LOG
		printf("Backup flash Erased Unsuccessfully!\r\n");
	#endif
	}else{
	#if PRINT_UART_LOG
		printf("Backup flash Erased Successfully!\r\n");
	#endif
	}
	if(writeFlashByte(catPara,FLASH_SAVE_ADDR_BACKUP,catParaLen) == WRITE_PARA_FAILED){
	#if PRINT_UART_LOG
		printf("Backup flash Writen Unsuccessfully!\r\n");
	#endif
	}else{
	#if PRINT_UART_LOG
		printf("Backup flash Writen Successfully!\r\n");
	#endif
	}
}

/**
  * @brief  给某个地址赋值0
  * @param  None
  * @retval None
  */
void putZero(u8 * pChar,u16 i){
	*(pChar+i) = 0;
}


/**
  * @brief  获取splitCmd函数需要返回的状态
  * @param  pCmd：存储命令CMD（字符串）的地址，字符串
  * @param  pValue：存储信息（需要设置的参数等）的地址，字符串格式（数字也表示为字符串，需要转化到数字）
  * @retval 命令/信息情况
  *         @arg CMD_VALUE_SPLIT_ERROR
  *         @arg CMD_VALUE_SPLIT_OK
  *         @arg CMD_SPLIT_OK
  */
u8 getSplitCmdFunReturn(u8* pCmd,u8 * pValue){
	if(*pValue != 0  &&  *pCmd != 0){//cmd和val都不是空的
		return CMD_VALUE_SPLIT_OK;
	}else if(*pCmd != 0){ //如果cmd不是空的
		return CMD_SPLIT_OK;
	}else{//两个都是空的返回error，表示没有指令或者分割指令失败
		return CMD_VALUE_SPLIT_ERROR;
	}
}

/**
  * @brief  专门为函数splitCmd的清理变量方法
  * @param  pQueue：存储命令（包括信息）的存储空间（队列）地址
  * @param  pCmd：存储命令的地址
  * @param  pValue：存储信息的地址
  * @param  i_cmd：pCmd需要清零的地址（pCmd+i_cmd）
  * @param  i_val：pValue需要清零的地址（pValue+i_val）
  * @retval None
  */
static void clearPara4SplitCmd(volatile CMD_QUEUE * pQueue,u8 * pCmd,u8 * pValue,u16 i_cmd,u16 i_val){
		uart_queue_clear(pQueue);
		putZero(pValue,i_val);
		putZero(pCmd,i_cmd);	
}

/**
  * @brief  从存储命令和信息的队列中，分割出命令(cmd)和信息(value)
  * @param  pQueue：存储命令（包括信息）的存储空间（队列）地址
  * @param  pCmd：存储命令的地址
  * @param  pValue：存储信息的地址
  * @retval CMD和VAL分割情况
  *         @arg CMD_VALUE_SPLIT_ERROR
  *         @arg CMD_VALUE_SPLIT_OK
  *         @arg CMD_SPLIT_OK
  *         @arg NONE_CMD_VALUE_MSG
  */
u8 splitCmd(volatile CMD_QUEUE * pQueue,u8 * pCmd,u8 * pValue)
{
	u16 i_cmd=0,i_val=0;
	u8 SplitFlag = CMD_VALUE_NOT_SPLIT_STA;
	u8 uart_data;
	u16 length = uart_queue_length(pQueue); //得到长度	
	for(u16 forNum = 0;pQueue->CmdCompleteFlag==CMD_COMPLETED;)//一次cmd完成了
	{		
		if(forNum >= length){  //超过了数据个数
			clearPara4SplitCmd(pQueue,pCmd,pValue,i_cmd,i_val);
			#if PRINT_UART_LOG
				printf("CMD Has No \\r\\n!\r\n");
			#endif			
			return CMD_VALUE_SPLIT_ERROR;
		}
		uart_data = uart_queue_pop(pQueue);
		forNum++;
		
		if(uart_data == CMD_VALUE_SPLIT_CHAR && SplitFlag != CMD_VALUE_SPLITED_STA)//分隔符来了而且只能来一次也就是支持输入"SET    111"这样的数据，不会把后面几个空格当做分隔符
		{
			SplitFlag = CMD_VALUE_SPLITED_STA;
		}
		else //不是分隔符
		{
//			printf("%c",uart_data);
			if(uart_data != '\r')
			{
				if(uart_data == '\n') //前面没有'\r'直接出现了\n
				{
					clearPara4SplitCmd(pQueue,pCmd,pValue,i_cmd,i_val);
					#if PRINT_UART_LOG
						printf("CMD Has No \\r!\r\n");
					#endif
					return CMD_VALUE_SPLIT_ERROR;
				}		
				if(SplitFlag == CMD_VALUE_NOT_SPLIT_STA) //还没有到分隔符，也就是还在获取cmd
				{
					*(pCmd+i_cmd) = uart_data;
					i_cmd++;
				}
				else
				{
					*(pValue+i_val) = uart_data;
					i_val++;
				}

			}
			else if(uart_data == '\r' && uart_queue_pop(pQueue) == '\n')  //\r\n   结束符号
			{
				clearPara4SplitCmd(pQueue,pCmd,pValue,i_cmd,i_val);
				return getSplitCmdFunReturn(pCmd,pValue);//正常停止时，需要判断是cmd还是cmd+val
			}	
			else if(uart_data == '\r' && uart_queue_pop(pQueue) != '\n') //出现了"\r" "非\n"的情况
			{
				clearPara4SplitCmd(pQueue,pCmd,pValue,i_cmd,i_val);
				#if PRINT_UART_LOG
					printf("CMD Has No \\n!\r\n");
				#endif
				return CMD_VALUE_SPLIT_ERROR;
			}
		}
	}
	return NONE_CMD_VALUE_MSG;
	
}


/**
  * @brief  重启控制器MCU
  * @note   不要随便使用，设置为static
  * @param  None
  * @retval None
  */
static void SystemReset(void){
	__DSB();                                                     /* Ensure all outstanding memory accesses included
															  buffered write are completed before reset */
	SCB->AIRCR  = ((0x5FA << SCB_AIRCR_VECTKEY_Pos)      |
				(SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) |
				SCB_AIRCR_SYSRESETREQ_Msk);                   /* Keep priority group unchanged */
	__DSB();                                                     /* Ensure completion of memory access */
	while(1);  
}

/**
  * @brief  获取串口/AP模式帮助文档
  * @note   每次添加命令都要更新
  * @note   主要针对串口，AP模式部分指令不支持
  * @param  None
  * @retval None
  */
void getHelp(void){
	#if PRINT_UART_LOG
		printf("\r\n============  Help Document  ============ \r\n\r\n");
		//CMD + VAL
		printf("- SET_RSI_JOIN_SSID    : Set RSI_JOIN_SSID\r\n  E.G. SET_RSI_JOIN_SSID SORL_WIFI\r\n\r\n");
		printf("- SET_RSI_PSK          : Set RSI_PSK\r\n  E.G. SET_RSI_PSK 123456\r\n\r\n");
	    printf("- SET_NODE_ID          : Set Id of the Node\r\n  E.G. SET_NODE_ID 1\r\n\r\n");
		printf("- SET_SERVER_IP        : Set IP of the Server\r\n  E.G. SET_SERVER_IP 115.159.154.160\r\n\r\n");
		//CMD
		printf("- HELP                 : Print Help Document\r\n  E.G. HELP\r\n\r\n");
		printf("- GET_PARA             : Print Parameters List\r\n  E.G. GET_PARA\r\n\r\n");
		printf("- SAVE_ALL_PARA        : Save All Parameters in Flash\r\n  E.G. SAVE_ALL_PARA\r\n\r\n");
		printf("- RESET_SYSTEM         : Reboot MCU\r\n  E.G. RESET_SYSTEM\r\n\r\n");
	#endif
}

/**
  * @brief  输出参数到串口
  * @note   每次添加命令都要更新
  * @param  None
  * @retval None
  */
void getPara(void){
	#if PRINT_UART_LOG
		printf("\r\n============  Parameter List  ============ \r\n\r\n");
		printf("RSI_JOIN_SSID     :      %s\r\n",RSI_JOIN_SSID);
		printf("RSI_PSK           :      %s\r\n",RSI_PSK);
		printf("nodeId            :      %d\r\n",nodeId);
		printf("destIp_txrx       :      %d.%d.%d.%d\r\n",destIp_txrx[0],destIp_txrx[1],destIp_txrx[2],destIp_txrx[3]);
		printf("localhost         :      %d.%d.%d.%d\r\n",localhost[0],localhost[1],localhost[2],localhost[3]);
		printf("test_name         :      %s\r\n",adc_queue.test_name);
		if(RSI_WIFI_OPER_MODE == RSI_WIFI_CLIENT_MODE_VAL){
			printf("Module Mode       :      CLIENT\r\n");
		}else if(RSI_WIFI_OPER_MODE == RSI_WIFI_AP_MODE_VAL){
			printf("Module Mode       :      AP\r\n");
		}
		if(RSI_IP_CFG_MODE == RSI_DHCP_IP_MODE){
			printf("Module Ip Mode    :      DHCP\r\n");
		}else if(RSI_IP_CFG_MODE == RSI_WIFI_AP_MODE_VAL){
			printf("Module Ip Mode    :      STATIC\r\n");
		}
		if(RSI_BAND == RSI_DUAL_BAND){
			printf("Frequency Band    :      DUAL BAND(2.4/5GHz)\r\n");
		}else if(RSI_BAND == RSI_BAND_5GHZ){
			printf("Frequency Band    :      5GHz\r\n");
		}else if(RSI_BAND == RSI_BAND_2P4GHZ){
			printf("Frequency Band    :      2.4GHz\r\n");
		}		
				
	#endif
}

/**
  * @brief  处理已分割的纯命令
  * @param  cmd：命令指针
  * @retval None
  */
void handleCmd(c8 * cmd){
#if PRINT_UART_LOG
	printf("Received CMD:\r\n  %s\r\n",cmd);
#endif
	if(strcmp(cmd,CMD_HELP) == 0){//帮助文件
		getHelp();
	}else if(strcmp(cmd,CMD_GET_PARA) == 0){
#if PRINT_UART_LOG
		getPara();
#endif		
	}else if(strcmp(cmd,CMD_SAVE_ALL_PARA) == 0){//保存所有数据到flash
#if PRINT_UART_LOG
		printf("Saving All Paras\r\n");
#endif
		FLASH_Unlock();//解锁 
		FLASH_DataCacheCmd(DISABLE);//FLASH擦除期间,必须禁止数据缓存
		writeSectorPara();
		FLASH_DataCacheCmd(ENABLE);	//FLASH擦除结束,开启数据缓存
		FLASH_Lock();//上锁
#if PRINT_UART_LOG
		printf("Saving Process End\r\n");
#endif
	}else if(strcmp(cmd,CMD_RESET_SYSTEM) == 0){//重新启动wifi
#if PRINT_UART_LOG
		printf("Reset...\r\n");
#endif
        SystemReset();                                      /* wait until reset */
	}
}

/**
  * @brief  设置字符串类参数
  * @param  val：参数数值（字符串）
  * @param  obj：要设置的对象指针（字符串）
  * @param  objName：要设置的对象的字符串名称
  * @retval None
  */
void setStrVal(c8 * val,c8 * obj,c8 * objName){
#if PRINT_UART_LOG	
	printf("Setting %s...\r\n",objName);
#endif
	memcpy((u8 *)obj,val,strlen(val));
	memset((u8 *)(obj+strlen(val)),'\0',1);//最后面赋值0
#if PRINT_UART_LOG
	printf("Now %s = \"%s\"\r\n",objName,obj);
	printf("Setted %s OK\r\n",objName);
	printf("To Save Flash.Send \"%s\"\r\n",CMD_SAVE_ALL_PARA);	
#endif
}


/**
  * @brief  设置字符串类参数
  * @param  val：参数数值（字符串），需要从字符串转化为数字，如'15'需要转化为(u8)15
  * @param  obj：要设置的对象指针（8位无符号整数类型）
  * @param  objName：要设置的对象的字符串名称
  * @retval None
  */
void setU8Val(u8 * val,u8 * obj,c8 * objName){//设置string value
#if PRINT_UART_LOG	
	printf("Setting %s...\r\n",objName);
#endif
	u8 valU8 = atoi((c8*)val);
	memcpy((u8 *)obj,&valU8,sizeof(u8));
#if PRINT_UART_LOG
	printf("Now %s = %d\r\n",objName,*obj);
	printf("Setted %s OK\r\n",objName);
	printf("To Save Flash.Send \"%s\"\r\n",CMD_SAVE_ALL_PARA);	
#endif
}

/**
  * @brief  设置字符串类参数
  * @param  val：IP参数数值地址，需要从字符串转化为u8数组，每个u8数字以IP_GROUP_SPLIT隔开
  * @param  obj：要设置的对象指针（u8数组）
  * @param  objName：要设置的对象的字符串名称
  * @retval None
  */
void setIpVal(u8 * val,u8 * obj,c8 * objName){
#if PRINT_UART_LOG	
	printf("Setting %s...\r\n",objName);
#endif
	u32 startAddr = (u32)(val);//起始地址
	u32 splitAddr;//分割出来的分隔符地址
	u8 ip_n[IPV4_1GROUP_STR_LENGTH+1] = {0};//存储IP内一个小组
	for(u8 i = 0;i<3;i++){//前三个
		splitAddr = (u32)strchr((c8 *)startAddr,IP_GROUP_SPLIT);//得到第一个分隔符地址
		memcpy(ip_n,(u8 *)startAddr,splitAddr - startAddr);destIp_txrx[i] = (u8)atoi((c8 *)ip_n);
		memset(ip_n,0,IPV4_1GROUP_STR_LENGTH+1);//清零	
		startAddr = splitAddr+1;//开始下一个
	}
	//第四个
	strcpy((char *)ip_n,(c8*)startAddr);destIp_txrx[3] = (u8)atoi((c8 *)ip_n);
#if PRINT_UART_LOG
	printf("Now %s = %d.%d.%d.%d\r\n",objName,destIp_txrx[0],destIp_txrx[1],destIp_txrx[2],destIp_txrx[3]);
	printf("Setted %s OK\r\n",objName);
	printf("To Save Flash.Send \"%s\"\r\n",CMD_SAVE_ALL_PARA);	
#endif
}

/**
  * @brief  处理已分割的命令和信息
  * @param  cmd：命令指针
  * @param  val：信息指针
  * @retval None
  */
void handleCmdVal(c8 * cmd,c8 * val){
#if PRINT_UART_LOG
	printf("RECEIVED\r\n  CMD : %s \r\n  VAL : %s\r\n",cmd,val);
#endif
	if(!strcmp(cmd,CMD_SET_JOIN_SSID)){  //设置ssid
		setStrVal(val,(c8*)RSI_JOIN_SSID,RSI_JOIN_SSID_STRNAME);
	}else if(!strcmp(cmd,CMD_SET_PSK)){  //设置psk
		setStrVal(val,(c8*)RSI_PSK,RSI_PSK_STRNAME);
	}else if(!strcmp(cmd,CMD_SET_NODE_ID)){  //设置节点id
		setU8Val((u8 *)val,&nodeId,NODE_ID_STRNAME);
	}else if(!strcmp(cmd,CMD_SET_SERVER_IP)){//设置服务器IP
		setIpVal((u8 * )val,(u8 * )destIp_txrx,SERVER_IP_STRNAME);
	}
	

}

/**
  * @brief  处理命令和信息分割错误
  * @note   目前不做任何处理
  * @param  None
  * @retval 0
  */
u8 handleSplitError(){
	//TODO
	return 0;
}

/**
  * @brief  处理未分割的命令和信息，包括纯命令
  * @param  pQueue：存储命令和信息的队列
  * @retval None
  */
void dealCmdMsg(volatile CMD_QUEUE * pQueue){
	u8 cmd[USART_REC_CMD_LEN];
	u8 val[USART_REC_VAL_LEN];
	u8 SplitSta = splitCmd(&CMD_RX_BUF,cmd,val);
	switch(SplitSta){
		case CMD_VALUE_SPLIT_OK:   //cmd   value都有
			handleCmdVal((c8 *)cmd,(c8 *)val);
			break;
		case CMD_SPLIT_OK:  //直接受到了cmd
			handleCmd((c8 *)cmd);
			break;
		case CMD_VALUE_SPLIT_ERROR: //数据split出错
			handleSplitError();
		#if PRINT_UART_LOG
			printf("Received CMD ERROR\r\n");
		#endif
			break;
		case NONE_CMD_VALUE_MSG:   //没有接收到数据
//		#if PRINT_UART_LOG
//			printf("None CMD\r\n");
//		#endif
			break;
		default:
			
			break;
	}
}

/**
  * @brief  出厂设置，在flash中写入信息
  * @note   必须先进行延时功能的初始化(delay_init)
  * @param  None
  * @retval None
  */
void setFactory(void){
	FLASH_Unlock();//解锁 
	FLASH_DataCacheCmd(DISABLE);//FLASH擦除期间,必须禁止数据缓存	
	writeSectorPara();	
	FLASH_DataCacheCmd(ENABLE);	//FLASH擦除结束,开启数据缓存
	FLASH_Lock();//上锁	
}




