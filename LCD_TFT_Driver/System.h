/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 System.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■"系统" 常用功能函数集-头文件
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



#ifndef __System_H
#define __System_H


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"宏定义**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////

//#define M_Self_Check_Time  (5000)  //5000 ms= 5 s
#define M_Self_Check_Time  (2000)  //3000 ms


////////////////////////////////////////////////////////////////////////////
//==**项目"专用"宏定义**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////i////////////////////////////////
//==**系统时间标志位定义**time bit flag define**===============//
extern union FLAGBIT16 TimeFlag1Bits;  //时间函数标志位定义1
#define  G_TimeFlag1Bits      TimeFlag1Bits.FLAG16  
#define	 F_Timing             TimeFlag1Bits.b.f0  //为1时，启动人为定时器 ,定时到后，自动清零(以1ms为时基,减计数器)
#define	 F_SuspendTiming	  TimeFlag1Bits.b.f1  //为1时，只是暂停人为定时器 (以1ms为时基,减计数器)    
#define  F_Timing_In_Work     TimeFlag1Bits.b.f2  //为1时，启动人为定时器(用于工作运行),定时到后，自动清零(以1ms为时基,减计数器)
//#define  F_500us              TimeFlag1Bits.b.f3  //系统定时0.5ms = 500us标志位
#define	 F_1ms                TimeFlag1Bits.b.f4  //系统定时1ms标志位
#define	 F_10ms_TaskClock	  TimeFlag1Bits.b.f5  //系统10ms标志位//用于程序主循环周期10ms    
#define	 F_10MS	  TimeFlag1Bits.b.f6  
#define	 F_100ms              TimeFlag1Bits.b.f7  //系统定时100ms标志位
#define	 F_250ms              TimeFlag1Bits.b.f8  //系统定时250ms标志位
#define	 F_250ms_Turn	      TimeFlag1Bits.b.f9  //参数闪烁时间为250ms闪烁一次,在数码管或液晶菜单设置时   
#define	 F_250ms_Working_Led  TimeFlag1Bits.b.f10 //用于单片机正常工作时，工作指示灯一直闪烁(250ms闪烁一次) 
//#define  F_	       TimeFlag1Bits.b.f11	
#define	 F_500ms	          TimeFlag1Bits.b.f12 //系统定时500ms标志位
//#define  F_	   TimeFlag1Bits.b.f13	   		
//#define  F_	   TimeFlag1Bits.b.f14	 		
#define  F_1s	               TimeFlag1Bits.b.f15 //系统定时1秒标志位 

//////////////////////////////////////////////////////////////////////////
extern union FLAGBIT16 TimeFlag2Bits;  //时间函数标志位定义2
#define  G_TimeFlag2Bits     TimeFlag2Bits.FLAG16  
#define	 F_100ms_ReadTime    TimeFlag2Bits.b.f0 //系统定时每100ms读一次"实时时钟"
#define	 F_1ms_LCD           TimeFlag2Bits.b.f1 //用于在LCD等待Busy信号时，每1ms累加1，但超过一定计数值时，则液晶复位
#define	 F_1ms_Uart          TimeFlag2Bits.b.f2 //用于串口等待应答信号每1ms累加1  
#define  F_500ms_Temperature TimeFlag2Bits.b.f3	//系统定时每500ms读一次"实时TMP温度值"
#define  F_500ms_TemperatureInTest TimeFlag2Bits.b.f4 //系统定时每500ms读一次"实时TMP温度值"
#define  F_500ms_IrDA        TimeFlag2Bits.b.f5  //IrDA   //系统定时每500ms 
#define  F_1s_BQ27410	     TimeFlag2Bits.b.f6  //系统每1s 读取"实时BQ27410采样的 电量值"
#define  F_1s_BQ27410InTest  TimeFlag2Bits.b.f7  //系统每1s 读取"实时BQ27410采样的 电量值"
//#define  F_1s_CC1101       TimeFlag2Bits.b.f8   //CC1101//系统定时每1s 
//#define  F_	   TimeFlag2Bits.b.f9	 
//#define  F_	   TimeFlag2Bits.b.f10	 
//#define  F_	   TimeFlag2Bits.b.f11	 
//#define  F_	   TimeFlag2Bits.b.f12	 
//#define  F_	   TimeFlag2Bits.b.f13	 
//#define  F_	   TimeFlag2Bits.b.f14 
//#define  F_	   TimeFlag2Bits.b.f15	 

	





////////////////////////////////////////////////////////////////////////////
//==**系统时间计数器变量**============================//
extern unsigned long G_TimingCnt; //人为定时计数器(以1ms为时基,减计数器)

extern unsigned long G_Timing_InWork_Cnt; //(工作中的定时)人为定时计数器(以1ms为时基,减计数器)




//extern unsigned char  G_1msCnt;    //系统定时1ms计数器
extern unsigned char G_10msCnt;   //系统定时10ms计数器
extern unsigned char G_100msCnt;  //系统定时100ms计数器
extern unsigned int G_250msCnt;  //系统定时250ms计数器
extern unsigned int G_500msCnt;  //系统定时500ms计数器
extern unsigned int G_1Csnt;     //系统定时1s计数器

////////////////////////////////////////////////////////////////////////////
//在中断中，不同的第G_1ms_Case 个 1 ms执行中断中的部分任务
//good 这样做可以使在中断中程序执行的总时间大大减小
//放到这个Switch中的子程序为执行时间比较长的子程序，
//分任务进行，减小中断总时间
extern unsigned char G_1ms_Case;  


////////////////////////////////////////////////////////////////////////////
//==**系统状态机变量**=================================//
extern unsigned int G_MainState;      //Main系统状态变量 
extern unsigned int G_Last_MainState; //保存上一次系统状态变量 

//extern volatile unsigned char G_UsersType;     //用户类型:高级管理员、普通管理员

extern union FLAGBIT SystemFlagBits;	//系统标志位定义
#define  G_SystemFlag1Bits  SystemFlagBits.FLAG 
//#define			 SystemFlagBits.b.f0	 
//#define			 SystemFlagBits.b.f1	 
//#define  F_Set_Success    SystemFlagBits.b.f2 //为1时，设置保存成功		  
//#define  F_Set_Error	SystemFlagBits.b.f3	 //为1时，设置错误
//#define  F_		SystemFlagBits.b.f4   
//#define  F_		SystemFlagBits.b.f5  
//#define  F_		SystemFlagBits.b.f6   
//#define  F_		SystemFlagBits.b.f7  



////////////////////////////////////////////////////////////////////////////
//==**工作运行时,用到的状态变量**====================//
extern unsigned int G_WorkState;	      //系统工作状态变量 
extern unsigned int G_Last_WorkState;  //保存上一次工作状态变量 



////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"函数"宏定义**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"函数声明**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"外部" API 函数声明**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**系统单片机初使化程序**=========================//
////////////////////////////////////////////////////////////////////////////
extern void System_Initial(void);          //   系统初使化 :单片机内部资源+外部基本资源的初使化 

extern void Osccon_Initial(void);  //晶振初始化函数:定义相关晶振参数


//extern void System_LoopInitial(void);   //系统程序中"循环"初使化,//good 可防止在程序循环中，初使化内容初改掉


////////////////////////////////////////////////////////////////////////////
//==**系统变量初使化(包括状态机初使化)**============//
////////////////////////////////////////////////////////////////////////////
extern void System_Variable_Initial(void); //系统变量初使化(包括状态机初使化)，分为"复位"和"上电"两种情况


////////////////////////////////////////////////////////////////////////////
//==**系统上电自检**===================================//
////////////////////////////////////////////////////////////////////////////
extern void System_SelfCheck(void); //系统上电自检:蜂鸣器,灯,液晶等模块自检


////////////////////////////////////////////////////////////////////////////
//==**通用"系统时钟"处理**=============================//
////////////////////////////////////////////////////////////////////////////

extern void System_Working_Led(void);  //单片机正常工作指示灯: 250ms闪烁一次

extern void System_GetLoopClockTick(void); //每次"死等"延时10ms后，系统"循环"执行一次程序

///////////////////////////////////////////////////////////////////////////
extern void System_Clock(void);      //通用"系统时钟"处理: 产生定时为1ms,10ms, 20ms, 100ms,等


extern void System_Timing_Task(void); //以1ms时基的人为定时，定时时间可设置,处理相关事务
extern void Open_Timing_Task(unsigned int TimeValue); //打开系统定时，定时给定的时间值(中断内)


extern void System_1ms_Task(void);   //处理系统定时"1ms" 下的相关事务

extern void System_10ms_Task(void);  //处理系统定时"10ms" 下的相关事务 

extern void System_100ms_Task(void); //处理系统定时"100ms" 下的相关事务

extern void System_250ms_Task(void); //处理系统定时"250ms" 下的相关事务

extern void System_500ms_Task(void); //处理系统定时"500ms" 下的相关事务

extern void System_1s_Task(void);      //处理系统定时"1s" 下的相关事务



	//工作中用到的定时器。// 以1ms时基的人为定时，定时时间可设置,处理相关事务
extern void Timing_In_Work(void);  
	//打开工作中的定时器，定时给定的时间值(中断内)
extern void Open_Timing_In_Work(unsigned long TimeValue);  



////////////////////////////////////////////////////////////////////////////
//==**项目"专用" API 函数声明**Exported Project-specific API funcitions**=//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**系统状态机的函数**==============================//
////////////////////////////////////////////////////////////////////////////

#define mSet_MainState(n)  (G_MainState = n)   //设置系统Main状态值(但不"初使化"状态)

	//"初使化" 各"系统状态Main█" (状态机)
	//01)更新系统状态值; 02)完成显示内容初使化; 03)相关变量初始化				
extern void Initial_MainState(unsigned int MainMode);

extern void Deal_MainState(void); // "处理"各系统Main█"状态"下的事务 (状态机)


///////////////////////////////////////////////////////////////////////////

#define mSet_WorkState(n) (G_WorkState = n)   //设置系统工作状态值(但不"初使化"状态)

extern void Initial_WorkState(unsigned int WorkMode); //初始化"工作状态Work▓"

extern void Deal_WorkState(void); //"处理"各工作Work▓"状态"下的事务 (状态机)






#endif  /* __System_H */




