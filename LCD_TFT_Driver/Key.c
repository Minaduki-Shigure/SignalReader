/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 Key.c
* 附属文件-Dependencies:  	 Key.h; Speaker.h; Hardware_Profile.h; Generic.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■  "IO 按键" -驱动程序(外部资源)
	01)     02)     03)    04)    05)    06)	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 注意事项-Attention : 	
	▲01)   care--无源蜂鸣器驱动频率一般在1-5k的频率，常用为4K
	▲02)     ▲03)    ▲04)    ▲05)    ▲06)     
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


#include "Generic.h"	//常用程序编程规范、函数集 -头文件-Generic Type Definitions


#include "Hardware_Profile.h"  //处理器"硬件配置文件" -Hardware specific definitions for Processor


#include "Speaker.h"   //"Speaker 扬声器" -驱动程序(外部资源)-头文件

#include "Key.h"   //"IO 按键" -驱动程序(外部资源)-头文件





////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
union FLAGBIT16 KeyFlagBits;  //按键用到的标志位定义



////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////

unsigned char KeyValue = 0;  //存按键解码后的按键值 (对于一般常用的按键)


unsigned char pKeyResult = 0;
unsigned char pKeyBuffer = 0;
unsigned char pKeyBuffer1 = 0;
unsigned char pKeyCnt = 0;     //按下时，消抖用的计数器
unsigned char pKeyNullCnt = 0; //弹起时，消抖用的计数器

unsigned int  pLongKeyCnt = 0;  //长按计数器.//时基为10ms ("循环"执行一次程序)




/****************************************************************************
*函数名-Function:	void Scan_Key(void)
*描述- Description:	"IO口键盘"扫描，5ms扫描一次按键(中断里)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01) 在中断里扫描System_1ms_Task(); 
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Scan_Key(void)
{          
//pKeyResult = G_InPut165_01;     //按键值(从74HC165的第一个字节采样)更新

	mSetIn_Key_1_IO;  //设置Key_1 的IO口为"输入"引脚
	mSetIn_Key_2_IO;  //设置Key_2 的IO口为"输入"引脚

	pKeyResult = Key_IN;//按键值IO值更新

	pKeyResult = pKeyResult & M_KeyUsed;		
	
	if(pKeyResult != M_KeyUsed)         //有键按下
	{
		pKeyNullCnt = 0;  //弹起时，消抖用的计数器
	
		F_KeyHave = 1; 
	} 
	else
	{
		F_KeyHave = 0;
		
		pKeyNullCnt ++;
		if(pKeyNullCnt >= M_KeyDelayTime)
		{
			pKeyNullCnt = 0;  //弹起时，消抖用的计数器
			F_KeyNull = 1;

			pKeyBuffer = M_NullKey;  //按键弹起消抖后，为无效按键
			KeyValue = M_NullKey;  //按键弹起消抖后，为无效按键
		}
		
		pKeyCnt = 0;          //约20ms消抖用的
	}

	if(pKeyResult == 0x08) pKeyBuffer = 1;       //按键1
	else if(pKeyResult == 0x04) pKeyBuffer = 2;  //按键2

	//if(pKeyResult == 0x0E) pKeyBuffer = 1;       //按键1
	//else if(pKeyResult == 0x0D) pKeyBuffer = 2;  //按键2
	//else if(pKeyResult == 0x0B) pKeyBuffer = 3;  //按键3
	//else if(pKeyResult == 0X07) pKeyBuffer = 4;  //按键4
	//else if(pKeyResult == 0X2F) pKeyBuffer = 5;  //按键5
	//else if(pKeyResult == 0X1F) pKeyBuffer = 6;  //按键6
	/////else if(pKeyResult == 0XBF) pKeyBuffer = 7;  //按键7
	/////else if(pKeyResult == 0X7F) pKeyBuffer = 8;  //按键8
	//else if((F_Sw7_165==0)&&(F_Sw8_165==0)) pKeyBuffer = 9;  //按键9 //7键和8键同时按下时的按键值定义为9

		 //其他情况的按键，作为无效按键//good,当用到两个按键同时按下才有效的情况,一定要加入下面的程序else rKeyBuffer = M_NullKey; 
	else pKeyBuffer = M_NullKey; 


	if(F_KeyHave)
    {
		if(pKeyBuffer != pKeyBuffer1)
		{
			pKeyBuffer1 = pKeyBuffer;
			pKeyCnt = 0;
		}
		else
		{
			pKeyCnt++;
			if(pKeyCnt >= M_KeyDelayTime)   //(4+1)*5ms= 25ms  
			{
				pKeyCnt = 0;
				if(F_KeyNull)    //根据标志位F_KeyNull，使按键只有再弹开后，再按才有效
				{
					KeyValue = pKeyBuffer;

					if(KeyValue != M_NullKey)
					{
						F_KeyRead = 1;
	
		//有按键按下，打开蜂鸣器
	//Open_Buzz_Speaker(M_200MS_BUZZ);  //打开蜂鸣器(Speaker 扬声器)的定时器
	
						F_KeyNull = 0;
						pKeyNullCnt = 0;  //弹起时，消抖用的计数器
					}
				}
			}
		}

    }	

}



/****************************************************************************
*函数名-Function:	unsigned char Detect_Key(void)
*描述- Description:	检测有没有按键,并返回按键值(对于一般常用的按键)
*输入参数-Input:	None
*输出参数-output:	具体按键值(无按键，则返回"0xFF")
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_Key(void)  //检测有没有按键,并返回按键值(对于一般常用的按键)
{     
	unsigned char i;
	
	if(KeyValue != M_NullKey) 
	{
		i = KeyValue;
		KeyValue = M_NullKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		
	}
	else i = 0xFF;  //0xFF为无效键
	
	return(i);
}



/****************************************************************************
*函数名-Function:	unsigned char Detect_Press_Key(void)
*描述- Description:	存按键解码后的按键值(按下执行，松开停止)
*输入参数-Input:	None
*输出参数-output:	具体按键值(无按键，则返回"0xFF")
*注意事项-Note：	
	▲01) 键值采样到，不清按键值
	▲02) 按键"按下"，开始某个工作。按键"松开"，停止工作
	▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_Press_Key(void) //存按键解码后的按键值(按下执行，松开停止)
{     
	unsigned char i;
	
	if(KeyValue != M_NullKey) 
	{
		i = KeyValue;
		//care 不清按键值G_KeyValue = M_NullKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
	}
	else i = 0xFF;  //0xFF为无效键
	
	return(i);
}




/****************************************************************************
*函数名-Function:	unsigned char Detect_Long_Key(unsigned char SecondNum)
*描述- Description:	(长按X秒有效)检测有没有长按的按键,并返回按键值
*输入参数-Input:	长按的时间X秒(单位:秒)
*输出参数-output:	具体按键值(无按键，则返回"0xFF")
*注意事项-Note：	
	▲01) 键值采样到，不清按键值
	▲02)  例if(Detect_Long_Key(10) == 5)   //如果长按"5键"10秒,则执行if后面的语句
	▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_Long_Key(unsigned char SecondNum)//(长按X秒有效)检测有没有长按的按键,并返回按键值
{     
	unsigned char pLongKey = M_NullKey;
	
	if(pKeyBuffer != M_NullKey)
	{
		pLongKeyCnt++;  //时基为10ms
		if(pLongKeyCnt > SecondNum*100)  //长按时间为pNum/100秒
		{
			pLongKeyCnt = 0; //清长按计数器.

			pLongKey = pKeyBuffer;
			
			//BuzzTimeNum = M_Buzz1s; //修改成功或保存成功后//启动普通蜂鸣器,锋鸣器长叫1秒		 							
			//F_StartBuzz = 1; 
		}
	}
	else pLongKeyCnt = 0; //清长按计数器.

	return (pLongKey);
}





/****************************************************************************
*函数名-Function:	unsigned char Detect_Key_1(void)
*描述- Description:	检测有没有按下IO按键"Key1"
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_Key_1(void)  
{	  
	unsigned char i;
	if(KeyValue == Key_1) 
	{
		KeyValue = M_NullKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*函数名-Function:	unsigned char Detect_Key_2(void)
*描述- Description:	检测有没有按下IO按键"Key2"
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_Key_2(void)  
{	  
	unsigned char i;
	if(KeyValue == Key_2) 
	{
		KeyValue = M_NullKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return (i);
}




/****************************************************************************
*函数名-Function:	void Decode_Key(void)
*描述- Description:	IO口键盘处理
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01)    ▲02)    ▲03)    ▲04)  
********************************************
void Decode_Key(void)
{  

////////////////////////////////////////////////////////////////////////////
//==**检测按键是否有按下**============================//
	if(F_KeyRead)  //约每5ms扫描一次按键,
	{
		F_KeyRead = 0; 
		G_BackLightCnt = G_BackLightNum; //有按键按下时，则一直在清计数器，使液晶一直显示

//////F_AlarmBuzz = 0;  //有任意按键按下，关报警
			
		if(!F_StartBuzz)    //加入这个条件，可以驱分不同长度的蜂鸣叫声(把长叫跟一般叫驱分开来)
		{
			BuzzTimeNum = M_Buzz200ms; 	//有按键按下时,启动普通蜂鸣器,锋鸣器200ms		 							
			F_StartBuzz = 1; 
		}

	}

}
*********************************/




