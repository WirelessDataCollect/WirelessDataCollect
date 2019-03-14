/**
  ******************************************************************************
  * @file    stmflash.c
  * @author  zju.nesc.iotlab 浙江大学NeSC课题组物联网实验室
  * @version V1.0
  * @date    13-March-2019
  * @brief   STM32 flash reading and writting functions   STM32的内部flash读写操作
  ******************************************************************************
  */


//-------------include---------------//
#include "stmflash.h"
#include "delay.h"
#include "usart.h" 
 
 
/**
  * @brief  读取指定地址的字(32位数据) 
  * @param  faddr：读地址
  * @retval 对应数据.
  */
u32 STMFLASH_ReadWord(u32 faddr){
	return *(vu32*)faddr; 
}  

/**
  * @brief  读取指定地址的半字(16位数据) 
  * @param  faddr：读地址
  * @retval 对应数据.
  */
u16 STMFLASH_ReadHalfWord(u32 faddr){
	return *(vu16*)faddr; 
}

/**
  * @brief  读取指定地址的字节(8位数据) 
  * @param  faddr：读地址
  * @retval 对应数据.
  */
u8 STMFLASH_ReadByte(u32 faddr){
	return *(vu8*)faddr; 
}

/**
  * @brief  获取某个地址所在的flash扇区
  * @param  addr：flash地址
  * @retval 0~11,即addr所在的扇区
  */
uint16_t STMFLASH_GetFlashSector(u32 addr){
	if(addr<ADDR_FLASH_SECTOR_1)return FLASH_Sector_0;
	else if(addr<ADDR_FLASH_SECTOR_2)return FLASH_Sector_1;
	else if(addr<ADDR_FLASH_SECTOR_3)return FLASH_Sector_2;
	else if(addr<ADDR_FLASH_SECTOR_4)return FLASH_Sector_3;
	else if(addr<ADDR_FLASH_SECTOR_5)return FLASH_Sector_4;
	else if(addr<ADDR_FLASH_SECTOR_6)return FLASH_Sector_5;
	else if(addr<ADDR_FLASH_SECTOR_7)return FLASH_Sector_6;
	else if(addr<ADDR_FLASH_SECTOR_8)return FLASH_Sector_7;
	else if(addr<ADDR_FLASH_SECTOR_9)return FLASH_Sector_8;
	else if(addr<ADDR_FLASH_SECTOR_10)return FLASH_Sector_9;
	else if(addr<ADDR_FLASH_SECTOR_11)return FLASH_Sector_10; 
	return FLASH_Sector_11;	
}

/**
  * @brief  从指定地址开始写入指定字（32位）长度的数据
  * @note   因为STM32F4的扇区实在太大,没办法本地保存扇区数据,所以本函数
            写地址如果非0XFF,那么会先擦除整个扇区且不保存扇区数据.所以
            写非0XFF的地址,将导致整个扇区数据丢失.建议写之前确保扇区里
            没有重要数据,最好是整个扇区先擦除了,然后慢慢往后写.
  * @param  WriteAddr：起始地址(此地址必须为4的倍数!!)
  * @param  pBuffer：数据指针
  * @param  NumToWrite：字(32位)数(就是要写入的32位数据的个数.) 
  * @retval 0~11,即addr所在的扇区
  */
void STMFLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite){ 
	FLASH_Status status = FLASH_COMPLETE;
	u32 addrx=0;
	u32 endaddr=0;	
	/* 非法地址*/
	if(WriteAddr<STM32_FLASH_BASE||WriteAddr%4){
		return;	
	}
	/* flash解锁*/
	FLASH_Unlock();	
	/* FLASH擦除期间,必须禁止数据缓存*/
	FLASH_DataCacheCmd(DISABLE);

	addrx=WriteAddr;//写入的起始地址				
	endaddr=WriteAddr+NumToWrite*4;	//写入的结束地址
	if(addrx<0X1FFF0000){			//只有主存储区,才需要执行擦除操作!!
		while(addrx<endaddr){		//扫清一切障碍.(对非FFFFFFFF的地方,先擦除)
		
			if(STMFLASH_ReadWord(addrx)!=0XFFFFFFFF){ //有非0XFFFFFFFF的地方,要擦除这个扇区，不是FF不能写
				  /* VCC=2.7~3.6V之间!!*/
				status=FLASH_EraseSector(STMFLASH_GetFlashSector(addrx),VoltageRange_3);
				if(status!=FLASH_COMPLETE){
					break;	
				}
			}else{
				addrx += 4;
			}
		} 
	}
	if(status==FLASH_COMPLETE){
		while(WriteAddr<endaddr){//写数据
			if(FLASH_ProgramWord(WriteAddr,*pBuffer)!=FLASH_COMPLETE){ //写入数据
				break;	//写入异常
			}
		WriteAddr+=4;
		pBuffer++;
		} 
	}
	FLASH_DataCacheCmd(ENABLE);
	FLASH_Lock();
} 

/**
  * @brief  从指定地址开始读出指定字（32位）长度的数据
  * @param  ReadAddr：起始地址
  * @param  pBuffer：数据指针
  * @param  NumToRead：字(4地址)数
  * @retval None
  */
void STMFLASH_ReadWords(u32 ReadAddr,u32 *pBuffer,u32 NumToRead){
	u32 i;
	for(i=0;i<NumToRead;i++){
		/* 读取4个字节.*/
		pBuffer[i]=STMFLASH_ReadWord(ReadAddr);
		/* 地址偏移4个字节.*/
		ReadAddr+=4;	
	}
}

/**
  * @brief  从指定地址开始读出指定字节（8位）长度的数据
  * @param  ReadAddr：起始地址
  * @param  pBuffer：数据指针
  * @param  NumToRead：字节（8位）数
  * @retval None
  */
void STMFLASH_ReadBytes(u32 ReadAddr,u8 *pBuffer,u32 NumToRead){
	u32 i;
	for(i=0;i<NumToRead;i++){
		/* 读取1个字节*/
		pBuffer[i]=STMFLASH_ReadByte(ReadAddr);
		/* 偏移1个字节*/	
		ReadAddr+=1;
	}
}
