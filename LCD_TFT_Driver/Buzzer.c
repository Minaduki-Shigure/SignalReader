/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 Buzzer.c
* 附属文件-Dependencies:  	 Buzzer.h; Hardware_Profile.h; Generic.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■"锋鸣器" -驱动程序(外部资源)
	01)     02)     03)    04)    05)    06)	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 注意事项-Attention : 	
	▲01)   care--有源蜂鸣器( 直接输出高电平，可驱动锋鸣器)
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


#include "Buzzer.h"   //"锋鸣器"-驱动程序(外部资源)-头文件





////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////

//==**常用的蜂鸣器**======================================//
union FLAGBIT16 BuzzFlagBits;  //蜂鸣器用到的标志位定义

unsigned long BuzzTime_Key = 0;    //按键有效时，蜂鸣器响的时间



////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**===========================//
////////////////////////////////////////////////////////////////////////////

unsigned long BuzzTimeNum;    //蜂鸣器响的时间，与标志位F_StartBuzz配合使用

//==**报警用的蜂鸣器**==================================//
unsigned int BuzzAlarmCycleCnt;         //蜂鸣器响的报警周期计数器
unsigned int BuzzAlarmCycleNum;         //蜂鸣器响的报警周期



/****************************************************************************
*函数名-Function:	void Check_Alarm_Buzz(void)
*描述- Description:		报警用,在中断中，检查是否启动蜂鸣器,蜂鸣器周期可改
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01)计数器在中断里以20ms为单位，BuzzCycleCNT与BuzzCycleNUM同时使用
	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Check_Alarm_Buzz(void)   //报警用,在中断中，检查是否启动蜂鸣器,蜂鸣器周期可改
{		
	BuzzAlarmCycleCnt ++;
	if(BuzzAlarmCycleCnt >= BuzzAlarmCycleNum)
	{
		BuzzAlarmCycleCnt = 0;	
	    mTurn_BUZZER;    //蜂鸣器使能取反
	}	
	if(BuzzAlarmCycleNum == 0) mOpen_BUZZER;   //周期BuzzCycleNum为0时，认为一直打开蜂鸣器
}



/****************************************************************************
*函数名-Function:	void Check_OutputBuzz(void)
*描述- Description:		在中断里，每10ms检测蜂鸣器功能(包括:常用和报警用)
*输入参数-Input:	None  为蜂鸣器响的时间(以10ms为单位)
*输出参数-output:	None
*注意事项-Note：	
	▲01)计数器在中断里以10ms为单位，BuzzCycleCNT与BuzzCycleNUM同时使用
	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Check_OutputBuzz(void)  //在中断里，每10ms检测蜂鸣器功能(包括:常用和报警用)
{
	if(F_StartBuzz)	 //为1启动常用蜂鸣器，//此标志位启动后，到时间到后，自动清0
	{
mOpen_BUZZER;        //开蜂鸣器
		BuzzTimeNum--;
		if(BuzzTimeNum == 0)
		{
			F_StartBuzz = 0;
			mClose_BUZZER;         //关蜂鸣器
		}
	}
	
	else if(F_AlarmBuzz)  //此标志位，记得，不用时要人为清0
	{
		Check_Alarm_Buzz();    //报警用,在中断中，检查是否启动蜂鸣器,蜂鸣器周期可改
	}
	
	else
	{
		mClose_BUZZER;          //关蜂鸣器
	}
}



/****************************************************************************
*函数名-Function:	void Open_Buzzer(unsigned long buzzTime) 
*描述- Description:		打开蜂鸣器(并指定响的时间)(以10ms为时间单位)
*输入参数-Input:	buzzTime: 蜂鸣器 --响的时间(以10ms为时间单位)
*输出参数-output:	None
*注意事项-Note：	
	▲01)  在中断中，对定时时间计数器，进行递减   
	▲02)  定时到后，自动清"定时标志位"	  
	▲03)    ▲04)  
*****************************************************************************/
void Open_Buzzer(unsigned long buzzTime)  //打开蜂鸣器(并指定响的时间)(以10ms为时间单位)
{
	BuzzTimeNum = buzzTime;	//定时(时基为1ms)//给自减计数器附初值
	F_StartBuzz = YES; //为1启动常用蜂鸣器    //定时到后自动清此标志位	 
}


/****************************************************************************
*函数名-Function:	void Enable_AlarmBuzzer(unsigned int cycleTime)
*描述- Description:		打开:报警蜂鸣器(并指定报警周期)(以10ms为时间单位)
*输入参数-Input:	cycleTime: 蜂鸣器 --报警周期(以10ms为时间单位)
*输出参数-output:	None
*注意事项-Note：	
	▲01)  关闭报警时，要人为对F_AlarmBuzz位清零。
	▲02) 	▲03)    ▲04)  
*****************************************************************************/
void Enable_AlarmBuzzer(unsigned int cycleTime)  //打开:报警蜂鸣器(并指定报警周期)(以10ms为时间单位)
{
	BuzzAlarmCycleCnt = 0;	
	BuzzAlarmCycleNum = cycleTime;	
	F_AlarmBuzz = YES; //为1启动报警蜂鸣器(根据BuzzAlarmCycleNum的值，可以更改蜂鸣器周期) 
}


/****************************************************************************
*函数名-Function:	void Disable_AlarmBuzzer(void) 
*描述- Description:		关闭:报警蜂鸣器
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01)  关闭报警时，要人为对F_AlarmBuzz位清零。
	▲02) 	▲03)    ▲04)  
*****************************************************************************/
void Disable_AlarmBuzzer(void)  //关闭:报警蜂鸣器
{
	F_AlarmBuzz = NO; //为0，关闭报警蜂鸣器//为1启动报警蜂鸣器
}



