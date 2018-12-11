/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 Generic.c
* 附属文件-Dependencies:  	 Generic.h; Hardware_Profile.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■常用程序编程规范、函数集 -Generic Type Definitions
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

#include "Hardware_Profile.h"  //处理器"硬件配置文件" -Hardware specific definitions for Processor

#include "Generic.h"	//常用程序编程规范、函数集 -头文件-Generic Type Definitions


////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned char ASCII_Table[21]={"0123456789ABCDEF.+- "};  //0--F字符 和  常用字符 显示表
								

////////////////////////////////////////////////////////////////////////////
//==**Temp*全局变量**===================================//
//--**调试用的中间变量，最后可以去掉的**---------------//

//unsigned char G_TempBuf[50]= {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
//                              0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
//                              0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
//                              0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
//                              0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
unsigned char G_TempChar = 0 ;    //测试临时用的"字节"变量
//unsigned int G_TempWord = 0 ;     //测试临时用的"单字"变量
//unsigned long G_TempDword = 0 ;   //测试临时用的"双字"变量


////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////



/****************************************************************************
*函数名-Function:	void Copy_Array_AtoB(unsigned char *RxPoint,const unsigned char *TxPoint,unsigned char Cnt)
*描述- Description:		把数组tx[第x个开始]中cnt个数，复制到数组Rx[第y个开始]
*输入参数-Input:	TxPoint: 数组Array_A;  RxPoint: 数组Array_B;   Cnt: 复制字节个数
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Copy_Array_AtoB(unsigned char *RxPoint,const unsigned char *TxPoint,unsigned char Cnt)
{
	for( ; Cnt > 0; Cnt--)
	{
        *RxPoint = *TxPoint;
        RxPoint++;
        TxPoint++;
	}        
}



/****************************************************************************
*函数名-Function:	void Sent_DataToArray(unsigned char *ArrayPoint,unsigned char DataValue,unsigned int Cnt)
*描述- Description:		将Cnt个相同的Data数据复制到数组Array[x]之后的Cnt个元素
*输入参数-Input:	ArrayPoint: 目的数组;  DataValue: 字节数据;   Cnt: 复制字节个数  
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Sent_DataToArray(unsigned char *ArrayPoint,unsigned char DataValue,unsigned int Cnt)
{
	for( ; Cnt > 0; Cnt--)
    {
    	*ArrayPoint = DataValue;
		ArrayPoint++;
    }
}


/****************************************************************************
*函数名-Function:	void WaitingDelayMs(unsigned int TimeData)  
*描述- Description:		死等待延时x毫秒
*输入参数-Input:	TimeData: 要延时ms值，例WaitingDelayMs(1);  //表示死等待延时1ms
*输出参数-output:	None
*注意事项-Note：	
	▲01) 与系统频率有关,DCO倍频为12MHz时取t1 = 60 (当前系统频率12M)
	            与系统频率有关,DCO倍频为20MHz时取t1 = 107 
	▲02) TimeData  = TimeData *10 = 100时，延时为10ms   
	▲03) 里面"清看门狗"操作   
	▲04) ms级的死等延时，调用WaitingDelayMs(n); //死等待延时n个ms(包含清看门狗操作)
	            us级的死等延时，调用mDelay_Cycles(n);	//死等待延时n个时钟周期 
*****************************************************************************/
void WaitingDelayMs(unsigned int TimeData)  
{
	unsigned char t1;
	unsigned int t2;

	TimeData = TimeData *10;   //晶振为20MHz时,TimeData = 100时，延时为10ms
	
	for(t2 = TimeData; t2 != 0; t2--)
	{
		for(t1 = 60; t1 != 0; t1--)
		{      
//mClr_WDTCNT;  // 清看门狗
			
			mNop; mNop; mNop; mNop;   //空操作指令(用于"短延时"或"调试")
			mNop; mNop; mNop; mNop; 
			mNop; mNop; mNop; mNop;   
		}
	}
}


/****************************************************************************
*函数名-Function:	void WaitingDelayMs(unsigned int TimeData)  
*描述- Description:		死等待延时x毫秒
*输入参数-Input:	TimeData: 要延时ms值，例WaitingDelayMs(1);  //表示死等待延时1ms
*输出参数-output:	None
*注意事项-Note：	
	▲01) 与系统频率有关, 晶振为20MHz时(用t1 = 107)
	▲02) TimeData  = TimeData *10 = 100时，延时为10ms   
	▲03) 里面"清看门狗"操作   
	▲04) ms级的死等延时，调用WaitingDelayMs(n); //死等待延时n个ms(包含清看门狗操作)
	            us级的死等延时，调用mDelay_Cycles(n);	//死等待延时n个时钟周期 
***************************************************************
void WaitingDelayMs(unsigned int TimeData)  
{
	unsigned char t1;
	unsigned int t2;

	TimeData = TimeData *10;   //晶振为20MHz时,TimeData = 100时，延时为10ms
	
	for(t2 = TimeData; t2 != 0; t2--)
	{
		for(t1 = 107; t1 != 0; t1--)
		{      
			mClr_WDTCNT;  // 清看门狗
			
			mNop; mNop; mNop; mNop;   //空操作指令(用于"短延时"或"调试")
			mNop; mNop; mNop; mNop; 
			mNop; mNop; mNop; mNop;   
		}
	}
}

**************/


