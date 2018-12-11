/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 MatrixKey.c
* 附属文件-Dependencies:  	 MatrixKey.h; TM1638.h; Speaker.h;
                                                        Hardware_Profile.h; Generic.h; 
* 文件描述-File Description:	 ( 源程序-Source File) 
	■  "矩阵按键" -驱动程序(外部资源)
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




#include "Generic.h"	//常用程序编程规范、函数集 -头文件-Generic Type Definitions

#include "Hardware_Profile.h"  //处理器"硬件配置文件" -Hardware specific definitions for Processor




#include "Speaker.h"   //"Speaker 扬声器" -驱动程序(外部资源)-头文件


#include "TM1638.h"  // "TM1638 数码管驱动器" -驱动程序(外部资源) -头文件

#include "MatrixKey.h"   //"矩阵按键" -驱动程序(外部资源)-头文件


////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////

union FLAGBIT16 MatrixKeyFlagBits;  //矩阵按键用到的标志位定义

unsigned char G_MatrixKeyValue = M_NullMatrixKey;  //存矩阵按键解码后的按键值 (对于一般常用的按键)


unsigned char G_MatrixKeyBuf[32];  //缓存输入的多个按键值
unsigned char G_MatrixKeyCnt = 0;  //按键缓存数组指针

unsigned char G_TotalKeyNum = 0;  //输入的数字按键总个数
unsigned char G_DecimalPoint = 0;  //输入的数字按键的小数点位置(用于光标显示)
unsigned char G_KeyPlace_Row = 0;    //(行)按键设置参数位置(光标)开始位置
unsigned char G_KeyPlace_Column = 0; //(列)按键设置参数位置(光标)开始位置
unsigned int  G_KeyValue_Addr = 0;  //采集完的所有按键存到EEPROM/Flash指定地址




////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////



unsigned char pMatrixKeyResult = 0;  //用于矩阵按键滤波
unsigned char pMatrixKeyBuffer = 0;
unsigned char pMatrixKeyCnt = 0;     //按下时，消抖用的计数器
unsigned char pMatrixKeyNullCnt = 0; //弹起时，消抖用的计数器

unsigned int  pLongMatrixKeyCnt = 0;  //长按计数器.//时基为10ms("循环"执行一次程序)




/****************************************************************************
*函数名-Function:	void Scan_MatrixKey(void)
*描述- Description:	"矩阵键盘"扫描，5ms扫描一次按键(中断里)	
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01) 在中断里扫描System_1ms_Task(); 
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Scan_MatrixKey(void)
{         
//rKeyResult = G_InPut165_01;     //按键值(从74HC165的第一个字节采样)更新
//pMatrixKeyResult = pMatrixKeyResult & M_MatrixKeyUsed;		
//pMatrixKeyResult = Sample_MatrixKey(); //采样矩阵键盘扫描

		//采样矩阵键盘
	pMatrixKeyResult = Read_MatrixKey_TM1638();  //读矩阵按键值(TM1638)

	if(pMatrixKeyResult != M_NullMatrixKey)         //有键按下
	{
		pMatrixKeyNullCnt = 0;  //弹起时，消抖用的计数器
	
		F_MatrixKeyHave = 1; 
	} 
	else
	{
		F_MatrixKeyHave = 0;
		
		pMatrixKeyNullCnt ++;
		if(pMatrixKeyNullCnt >= M_MatrixKeyDelayTime)
		{
			pMatrixKeyNullCnt = 0;  //弹起时，消抖用的计数器
			F_MatrixKeyNull = 1;

			pMatrixKeyBuffer = M_NullMatrixKey;  //按键弹起消抖后，为无效按键
			G_MatrixKeyValue = M_NullMatrixKey;  //按键弹起消抖后，为无效按键
		}
		
		pMatrixKeyCnt = 0;          //约20ms消抖用的
	}
	 
	if(F_MatrixKeyHave)
    {
		if(pMatrixKeyResult != pMatrixKeyBuffer)
		{
			pMatrixKeyBuffer = pMatrixKeyResult;
			pMatrixKeyCnt = 0;
		}
		else
		{
			pMatrixKeyCnt ++;
			if(pMatrixKeyCnt >= M_MatrixKeyDelayTime)   //(4+1)*5ms= 25ms  
			{
				pMatrixKeyCnt = 0;
				if(F_MatrixKeyNull)    //根据标志位F_MatrixKeyNull，使按键只有再弹开后，再按才有效
				{
					G_MatrixKeyValue = pMatrixKeyBuffer;
					
					if(G_MatrixKeyValue != M_NullMatrixKey)
					{
						F_MatrixKeyRead = 1;
			
						F_MatrixKeyNull = 0;
						pMatrixKeyNullCnt = 0;  //弹起时，消抖用的计数器

				//有按键按下，打开蜂鸣器
			//Open_Buzz_Speaker(M_200MS_BUZZ);  //打开蜂鸣器(Speaker 扬声器)的定时器

							//有按键按下时，则一直在清计数器，使液晶一直显示
						/////G_BackLightCnt = G_BackLightNum; 
						
						/////F_AlarmBuzz = 0;	//有任意按键按下，关报警
						
						/////if(!F_StartBuzz)	//加入这个条件，可以驱分不同长度的蜂鸣叫声(把长叫跟一般叫驱分开来)
						/////{
						/////	BuzzTimeNum = M_Buzz200ms;	//有按键按下时,启动普通蜂鸣器,锋鸣器200ms									
						/////	F_StartBuzz = 1; 
						/////}	
						
					}
				}
			}
		}

    }	

/***************
	if(F_CloseLcm)    //good //如果之前液晶显示为省电状态，有按键按下，开液晶，不执行按键动作
	{
		if(F_MatrixKeyRead)
		{
			F_MatrixKeyRead = 0; 
			F_CloseLcm = 0;
			G_BackLightCnt = G_BackLightNum; //有按键按下时，则一直在清计数器，使液晶一直显示
			MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效
		
		}
	}
	*********************/
	
}


/****************************************************************************
*函数名-Function:	unsigned char Detect_MatrixKey(void)
*描述- Description:	检测有没有按键,并返回按键值(对于一般常用的按键)
*输入参数-Input:	None
*输出参数-output:	具体按键值(无按键，则返回"0xFF")
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_MatrixKey(void)  //检测有没有按键,并返回按键值(对于一般常用的按键)
{     
	unsigned char i;
	
	if(G_MatrixKeyValue != M_NullMatrixKey) 
	{
		i = G_MatrixKeyValue;
		G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		
	}
	else i = 0xFF;  //0xFF为无效键
	
	return(i);
}


/****************************************************************************
*函数名-Function:	unsigned char Detect_Press_MatrixKey(void)
*描述- Description:	存矩阵按键解码后的按键值(按下执行，松开停止)
*输入参数-Input:	None
*输出参数-output:	具体按键值(无按键，则返回"0xFF")
*注意事项-Note：	
	▲01) 键值采样到，不清按键值
	▲02) 按键"按下"，开始某个工作。按键"松开"，停止工作
	▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_Press_MatrixKey(void) //存矩阵按键解码后的按键值(按下执行，松开停止)
{     
	unsigned char i;
	
	if(G_MatrixKeyValue != M_NullMatrixKey) 
	{
		i = G_MatrixKeyValue;
		//care 不清按键值G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
	}
	else i = 0xFF;  //0xFF为无效键
	
	return(i);
}


/****************************************************************************
*函数名-Function:	unsigned char Detect_Long_MatrixKey(unsigned char SecondNum)
*描述- Description:	(长按X秒有效)检测有没有长按的按键,并返回按键值
*输入参数-Input:	长按的时间X秒(单位:秒)
*输出参数-output:	具体按键值(无按键，则返回"0xFF")
*注意事项-Note：	
	▲01) 键值采样到，不清按键值
	▲02) 例if(Detect_Long_MatrixKey(10) == 5)   //如果长按"5键"10秒,则执行if后面的语句 
	▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_Long_MatrixKey(unsigned char SecondNum)//(长按X秒有效)检测有没有长按的按键,并返回按键值
{     
	unsigned char pLong_MatrixKey = M_NullMatrixKey;
	
	if(pMatrixKeyBuffer != M_NullMatrixKey)
	{
		pLongMatrixKeyCnt++;  //时基为10ms
		if(pLongMatrixKeyCnt > SecondNum*100)  //长按时间为pNum/100秒
		{
			pLongMatrixKeyCnt = 0; //清长按计数器.

			pLong_MatrixKey = pMatrixKeyBuffer;
			
			//BuzzTimeNum = M_Buzz1s; //修改成功或保存成功后//启动普通蜂鸣器,锋鸣器长叫1秒		 							
			//F_StartBuzz = 1; 
		}
	}
	else pLongMatrixKeyCnt = 0; //清长按计数器.

	return (pLong_MatrixKey);
}




/****************************************************************************
*函数名-Function:	unsigned char Detect_MatrixKey_0(void)
*描述- Description:	检测"0" 矩阵按键 有没有按下
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_0(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_0) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}



/****************************************************************************
*函数名-Function:	unsigned char Detect_MatrixKey_1(void)
*描述- Description:	检测"1" 矩阵按键 有没有按下
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_1(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_1) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*函数名-Function:	unsigned char Detect_MatrixKey_2(void)
*描述- Description:	检测"2" 矩阵按键 有没有按下
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_2(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_2) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*函数名-Function:	unsigned char Detect_MatrixKey_3(void)
*描述- Description:	检测"3" 矩阵按键 有没有按下
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_3(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_3) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}

/****************************************************************************
*函数名-Function:	unsigned char Detect_MatrixKey_4(void)
*描述- Description:	检测"4" 矩阵按键 有没有按下
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_4(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_4) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*函数名-Function:	unsigned char Detect_MatrixKey_5(void)
*描述- Description:	检测"5" 矩阵按键 有没有按下
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_5(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_5) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*函数名-Function:	unsigned char Detect_MatrixKey_6(void)
*描述- Description:	检测"6" 矩阵按键 有没有按下
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_6(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_6) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*函数名-Function:	unsigned char Detect_MatrixKey_7(void)
*描述- Description:	检测"7" 矩阵按键 有没有按下
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_7(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_7) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*函数名-Function:	unsigned char Detect_MatrixKey_8(void)
*描述- Description:	检测"8" 矩阵按键 有没有按下
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_8(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_8) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}

/****************************************************************************
*函数名-Function:	unsigned char Detect_MatrixKey_9(void)
*描述- Description:	检测"9" 矩阵按键 有没有按下
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_9(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_9) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*函数名-Function:	unsigned char Detect_MatrixKey_A(void)
*描述- Description:	检测"A" 矩阵按键 有没有按下
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_A(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_A) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*函数名-Function:	unsigned char Detect_MatrixKey_B(void)
*描述- Description:	检测"B" 矩阵按键 有没有按下
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_B(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_B) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}



/****************************************************************************
*函数名-Function:	unsigned char Detect_MatrixKey_C(void)
*描述- Description:	检测"C" 矩阵按键 有没有按下
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_C(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_C) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*函数名-Function:	unsigned char Detect_MatrixKey_D(void)
*描述- Description:	检测"D" 矩阵按键 有没有按下
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_D(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_D) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}

/****************************************************************************
*函数名-Function:	unsigned char Detect_MatrixKey_E(void)
*描述- Description:	检测"E" 矩阵按键 有没有按下
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_E(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_E) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*函数名-Function:	unsigned char Detect_MatrixKey_F(void)
*描述- Description:	检测"F" 矩阵按键 有没有按下
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_F(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_F) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}



/****************************************************************************
*函数名-Function:	unsigned char Detect_MatrixKey_AC(void)
*描述- Description:	检测"AC" 矩阵按键 有没有按下
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_AC(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_AC) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*函数名-Function:	unsigned char Detect_MatrixKey_Plus(void)
*描述- Description:	检测"+" 矩阵按键 有没有按下
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_Plus(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_Plus) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*函数名-Function:	unsigned char Detect_MatrixKey_Minus(void)
*描述- Description:	检测"-" 矩阵按键 有没有按下
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_Minus(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_Minus) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}



/****************************************************************************
*函数名-Function:	unsigned char Detect_MatrixKey_Equal(void)
*描述- Description:	检测"=" 矩阵按键 有没有按下
*输入参数-Input:	None
*输出参数-output:	1: 有按下此键 0: 没有按下此键
*注意事项-Note：	
	▲01) 键值采样到，并用完后，马上清0，再采样
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_Equal(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_Equal) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care 这里相当于对按键清0(即令按键只有一次有效)
		i = 1;
	}
	else i = 0;

	return(i);
}





/****************************************************************************
*函数名-Function:	unsigned char Sample_MatrixKey(void)
*描述- Description:	采样矩阵键盘扫描
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01) 在中断里扫描System_1ms_Task(); 
	▲02)    ▲03)    ▲04)  
**************************************************
unsigned char Sample_MatrixKey(void)
{
	unsigned char i,j;
	unsigned int L_MatrixKeyIOData; //按键IO口的实际值
	unsigned char L_MatrixKeyValue;//采样后的解码的按键值
	
	Y1_MatrixKey_TRIS = 0;  //设列为输出口
	Y2_MatrixKey_TRIS = 0;
	Y3_MatrixKey_TRIS = 0;
	
	X1_MatrixKey_TRIS = 1; //设行为输入口
	X2_MatrixKey_TRIS = 1;
	X3_MatrixKey_TRIS = 1;
	X4_MatrixKey_TRIS = 1;
	X5_MatrixKey_TRIS = 1;

		//扫描之前，先令按键初使值为"无键"0xFF //care 只能放在这里
	L_MatrixKeyValue = 0xFF; //没有按键按下时的按键值设为0xFF


	for(i = 0; i < 3 ; i++)       //3列*5行矩阵扫描
	{
		switch(i)
		{	
			case 0:   
				Y1_MatrixKey_IO = 0;  //第1列输出为低电平
				Y2_MatrixKey_IO = 1;
				Y3_MatrixKey_IO = 1;
				break;
			
			case 1: 
				Y1_MatrixKey_IO = 1;  //第2列输出为低电平
				Y2_MatrixKey_IO = 0;
				Y3_MatrixKey_IO = 1;
				break;
			
			case 2:  
				Y1_MatrixKey_IO = 1;  //第3列输出为低电平
				Y2_MatrixKey_IO = 1;
				Y3_MatrixKey_IO = 0;
				break;
			
			default:	  
				break;

		}

		for(j = 0; j < 5 ; j++)
		{		
			L_MatrixKeyIOData = MatrixKey_PORT & 0x200F;  //0x200F对应的是RB0,RB1,RB2,RB3,RB13   ,为矩阵行值
				//矩阵按健实际值= 矩阵行值| 列值
			L_MatrixKeyIOData = L_MatrixKeyIOData | (MatrixKey_LAT & 0x1300);  //0x1300对应的是RB8,RB9,RB12   ,为矩阵列值



			switch(L_MatrixKeyIOData)
			{
	//还要判断是否是多个按键的按下的情况		
				case 0x230E:  //"1键" 
					L_MatrixKeyValue = 1;
					break;
			
				case 0x230D:  //"4键" 
					L_MatrixKeyValue = 4;
					break;
				
				case 0x230B:  //"7键" 
					L_MatrixKeyValue = 7;
					break;

				
				case 0x2307:  //"左键" 
					L_MatrixKeyValue = 0x0A;
					break;		
				
				case 0x030F:  //"ESC退出键" 
					L_MatrixKeyValue = 0x0C;
					break;



				case 0x320E:  //"2键" 
					L_MatrixKeyValue = 2;
					break;
			
				case 0x320D:  //"5键" 
					L_MatrixKeyValue = 5;
					break;

				
				case 0x320B:  //"8键" 
					L_MatrixKeyValue = 8;
					break;

				
				case 0x3207:  //"0键" 
					L_MatrixKeyValue = 0;
					break;		
				
				case 0x120F:  //"MENU菜单键" 
					L_MatrixKeyValue = 0x0D;
					break;

				case 0x310E:  //"3键" 
					L_MatrixKeyValue = 3;
					break;
			
				case 0x310D:  //"6键" 
					L_MatrixKeyValue = 6;
					break;

				
				case 0x310B:  //"9键" 
					L_MatrixKeyValue = 9;
					break;

				
				case 0x3107:  //"右键" 
					L_MatrixKeyValue = 0x0B;
					break;		
				
				case 0x110F:  //"Enter确定键" 
					L_MatrixKeyValue = 0x0E;
					break;
					
				//case :  
					
				//	break;

				default:	//"无键" 
				//	L_MatrixKeyValue = 0xFF;  //没有按键按下时的按键值设为0xFF
					break;
			}
				

			
		}
	}

	return (L_MatrixKeyValue); //返回按键值
	
}
***************************/


/****************************************************************************
*函数名-Function:	void Decode_MatrixKey(void)
*描述- Description:	矩阵键盘处理
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01)    ▲02)    ▲03)    ▲04)  
********************************************
void Decode_MatrixKey(void)
{  

////////////////////////////////////////////////////////////////////////////
//==**检测按键是否有按下**============================//
	if(F_MatrixKeyRead)  //约每5ms扫描一次按键,
	{
		F_MatrixKeyRead = 0; 
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






