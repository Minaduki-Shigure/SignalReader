/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 SDaccess.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■"SD_Card SD卡"-驱动程序(外部资源)-头文件
	01)     02)     03)    04)    05)    06)	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 注意事项-Attention : 	
	▲01)     ▲02)     ▲03)    ▲04)    ▲05)    ▲06)     
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
* 修改记录-Change History:   
	作者   时间        版本  内容描述
	Author 	 Date		   Rev      Comment
	-------------------------------------------------------------------------------
	BlueS	2012-12-12	  1.0	   
			xxxx-xx-xx	  x.x	   
			xxxx-xx-xx	  x.x				
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
* 公司-Company: 			CS-EMLAB  Co. , Ltd.
* 软件许可协议-Software License Agreement:
	Copyright (C) 2012-2020 	CS-EMLAB  Co. , Ltd.	All rights reserved.	

*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#ifndef  __SDaccess_H 
#define  __SDaccess_H 

#include <stdint.h>
#include "ff.h"

////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"宏定义**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**项目"专用"宏定义**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
extern char SD_Buf[100]; //255 //SD卡数据缓存数组
extern unsigned int SD_Cnt; //SD卡数据缓存数组指针     

extern unsigned int SD_Num;   
extern unsigned int SD_Write_Num;   //BlueS


////////////////////////////////////////////////////////////////////////////
//==**"函数"宏定义**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"函数声明**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////
	//写SD卡: 新建一个文件，并定入指定大小的数据
extern FRESULT WriteFile(char* fileName, char* text, WORD size);

	//读SD卡: 从指定文件读取
extern FRESULT GetFile(char* fileName);

	//读写SD卡出问错时，进入低功耗模式
extern void die(FRESULT rc);


////////////////////////////////////////////////////////////////////////////
//==**"外部" API 函数声明**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

//////////BlueS 新增////////////////////////////////////////////////

#define STATE_SD_IDLE  (0x00)   //SD卡的空闭状态值
#define STATE_SD_ERROR (0xFF)   //SD卡的错误状态值


extern unsigned char G_Data_SD_Read;  //缓存 "SD_Card SD卡"的一个字节数据
extern unsigned char G_Data_SD_Write;  //缓存 "SD_Card SD卡"的一个字节数据

extern unsigned char SD_State;   //BlueS//记录SD卡的状态


extern void Initial_SD_Card(void);  //初始化设置: "SD_Card SD卡"

extern void Initial_Osccon_SD_Card(void); //初始化晶振--"SD_Card SD卡"






#endif   /* __SDaccess_H  */





