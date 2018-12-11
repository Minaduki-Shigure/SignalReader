/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 Step_Motor.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■"Step_Motor 步进电机" -驱动程序(外部资源)-头文件
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

#ifndef  __Step_Motor_H 
#define  __Step_Motor_H 


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"宏定义**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////
#define STATE_Idle_Step_Motor     ( 0 )  //空闭-""Step_Motor 步进电机"
#define STATE_Positive_Step_Motor ( 1 )  //正转-"Step_Motor 步进电机"
#define STATE_Reverse_Step_Motor  ( 2 )  //反转-"Step_Motor 步进电机"
#define STATE_Stop_Step_Motor     ( 3 )  //停转-"Step_Motor 步进电机"



////////////////////////////////////////////////////////////////////////////
//==**项目"专用"宏定义**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
  
extern union FLAGBIT Step_Motor_FlagBits; //"Step_Motor 步进电机"相关标志位变量
#define  G_Step_Motor_FlagBits      Step_Motor_FlagBits.FLAG16  
#define	 F_500ms_Reflash_Step_Motor Step_Motor_FlagBits.b.f0  //为1时，刷新LCD_TFT显示"转速" ("Step_Motor 步进电机")
//#define	 F_      Step_Motor_FlagBits.b.f1  //为1时，
//#define	 F_      Step_Motor_FlagBits.b.f2  //为1时，
//#define	 F_      Step_Motor_FlagBits.b.f3  //为1时，
//#define	 F_      Step_Motor_FlagBits.b.f4  //为1时，
//#define	 F_      Step_Motor_FlagBits.b.f5  //为1时，
//#define	 F_      Step_Motor_FlagBits.b.f6  //为1时，
//#define	 F_      Step_Motor_FlagBits.b.f7  //为1时，



extern unsigned int G_Step_Speed;   //"Step_Motor 步进电机"1秒内CCR3采样到的频率次数

extern unsigned char G_Step_WorkState; //运行状态-"Step_Motor 步进电机"

////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
//==**"函数"宏定义**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"函数声明**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////

extern void Enable_Step_Motor(void); //使能-"Step_Motor 步进电机"

extern void Disable_Step_Motor(void);  //禁止-"Step_Motor 步进电机"


////////////////////////////////////////////////////////////////////////////
//==**"外部" API 函数声明**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

extern void Step_Motor_Initial(void);  //初始化设置:  "Step_Motor 步进电机"

extern void Stop_Step_Motor(void);     //停转-"Step_Motor 步进电机"
extern void Positive_Step_Motor(void); //正转-"Step_Motor 步进电机"(根据电位计电压进行调速)
extern void Reverse_Step_Motor(void); //反转-"Step_Motor 步进电机"(根据电位计电压进行调速)

extern void Deal_Step_Motor(void);  //中断中处理步进电机(正反转,转速)

extern void Deal_Speed_Step_Motor(void); // 计算步进电转速


#endif   /* __Step_Motor_H  */








