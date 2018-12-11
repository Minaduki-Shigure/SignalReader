/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 Buzzer.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■"锋鸣器" -驱动程序-头文件(外部资源)
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


#ifndef  __Buzzer_H 
#define  __Buzzer_H 


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"宏定义**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////

	 //==care--以10ms为基础单位
#define M_Buzz200ms  (20)  //蜂鸣器叫200ms 
#define M_Buzz500ms  (50)  //蜂鸣器叫500ms

#define M_Buzz1s     (100) //蜂鸣器叫1s
#define M_Buzz2s     (200) //蜂鸣器叫2s



//////////////////////////////////////////////////////////////////////////////////
//===**全局变量定义**Export variable**蜂鸣器相关变量===========//
//////////////////////////////////////////////////////////////////////////////////

	//========**常用的蜂鸣器**===========//
extern union FLAGBIT16 BuzzFlagBits;  //蜂鸣器用到的标志位定义
#define  G_BuzzFlagBits	  BuzzFlagBits.FLAG16  
#define  F_StartBuzz      BuzzFlagBits.b.f0   //为1启动常用蜂鸣器   
#define  F_AlarmBuzz	  BuzzFlagBits.b.f1   //为1启动报警蜂鸣器(根据BuzzAlarmCycleNum的值，可以更改蜂鸣器周期)
//#define   F_	BuzzFlagBits.b.f2  
//#define   F_	BuzzFlagBits.b.f3  
//#define   F_	BuzzFlagBits.b.f4 
//#define   F_	BuzzFlagBits.b.f5    
//#define   F_	BuzzFlagBits.b.f6  
//#define   F_	BuzzFlagBits.b.f7 
//#define   F_	BuzzFlagBits.b.f8      
//#define   F_	BuzzFlagBits.b.f9     
//#define   F_	BuzzFlagBits.b.f10    
//#define   F_	BuzzFlagBits.b.f11      
//#define   F_	BuzzFlagBits.b.f12      
//#define   F_	BuzzFlagBits.b.f13      
//#define   F_	BuzzFlagBits.b.f14     
//#define   F_	BuzzFlagBits.b.f15     


extern unsigned long BuzzTime_Key;    //按键有效时，蜂鸣器响的时间



////////////////////////////////////////////////////////////////////////////
//==**项目"专用"宏定义**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
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

extern void Check_Alarm_Buzz(void);   //报警用,在中断中，检查是否启动蜂鸣器,蜂鸣器周期可改

extern void Check_OutputBuzz(void);  //在中断里，每10ms检测蜂鸣器功能(包括:常用和报警用)

extern void Open_Buzzer(unsigned long buzzTime);  //打开蜂鸣器(并指定响的时间)


extern void Enable_AlarmBuzzer(unsigned int cycleTime);  //打开:报警蜂鸣器(并指定报警周期)(以10ms为时间单位)

extern void Disable_AlarmBuzzer(void);  //关闭:报警蜂鸣器


#endif  //-- __Buzzer_H --// 





