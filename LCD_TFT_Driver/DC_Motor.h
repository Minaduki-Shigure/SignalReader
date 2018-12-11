/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 DC_Motor.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■"DC_Motor 直流电机"-驱动程序(外部资源)-头文件
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

#ifndef  __DC_Motor_H 
#define  __DC_Motor_H 


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"宏定义**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////
#define STATE_Idle_DC_Motor     ( 0 )  //空闭-"DC_Motor 直流电机"
#define STATE_Positive_DC_Motor ( 1 )  //正转-"DC_Motor 直流电机"
#define STATE_Reverse_DC_Motor  ( 2 )  //反转-"DC_Motor 直流电机"
#define STATE_Stop_DC_Motor     ( 3 )  //停转-"DC_Motor 直流电机"



////////////////////////////////////////////////////////////////////////////
//==**项目"专用"宏定义**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
//////////////////////////////////////////////////////////////////////////// 
extern union FLAGBIT DC_Motor_FlagBits; //"DC_Motor 直流电机"相关标志位变量
#define  G_DC_Motor_FlagBits      DC_Motor_FlagBits.FLAG16  
#define	 F_1s_Frequency_DC_Motor  DC_Motor_FlagBits.b.f0  //为1时，直流电机转速(1s内的脉冲次数)
#define	 F_500ms_Reflash_DC_Motor DC_Motor_FlagBits.b.f1  //为1时，刷新LCD_TFT显示"转速" ("DC_Motor 直流电机")
//#define	 F_      DC_Motor_FlagBits.b.f2  //为1时，
//#define	 F_      DC_Motor_FlagBits.b.f3  //为1时，
//#define	 F_      DC_Motor_FlagBits.b.f4  //为1时，
//#define	 F_      DC_Motor_FlagBits.b.f5  //为1时，
//#define	 F_      DC_Motor_FlagBits.b.f6  //为1时，
//#define	 F_      DC_Motor_FlagBits.b.f7  //为1时，
//#define	 F_      DC_Motor_FlagBits.b.f8  //为1时，
//#define	 F_      DC_Motor_FlagBits.b.f9  //为1时，
//#define	 F_      DC_Motor_FlagBits.b.f10 //为1时，
//#define	 F_      DC_Motor_FlagBits.b.f11 //为1时，
//#define	 F_      DC_Motor_FlagBits.b.f12 //为1时，
//#define	 F_      DC_Motor_FlagBits.b.f13 //为1时， 
//#define	 F_      DC_Motor_FlagBits.b.f14 //为1时，
//#define	 F_      DC_Motor_FlagBits.b.f15 //为1时，  


extern unsigned int G_DC_SpeedCnt; //DC_Motor 直流电机"1秒内CCR3采样到的频率累加器
extern unsigned int G_DC_Speed;  //DC_Motor 直流电机"1秒内CCR3采样到的频率次数
extern unsigned char G_DC_WorkState; //运行状态-DC_Motor 直流电机"



////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
//==**"函数"宏定义**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"函数声明**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////

extern void Disable_DC_Motor(void);  //禁止-"DC_Motor 直流电机"

extern void Enable_DC_Motor(void);  //使能-"DC_Motor 直流电机"



////////////////////////////////////////////////////////////////////////////
//==**"外部" API 函数声明**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

extern void DC_Motor_Initial(void);  //初始化设置:  "DC_Motor 直流电机"

	//采样"DC_Motor 直流电机"转速(1s内的脉冲次数)
extern void Sample_DC_Motor_Frequency(void);


extern void Stop_PWM_DC_Motor(void);  //停止PWM输出-"DC_Motor 直流电机"

extern void Stop_DC_Motor(void);  //停转-"DC_Motor 直流电机"

extern void Positive_DC_Motor(void);  //正转-"DC_Motor 直流电机"(根据电位计电压进行调速)

extern void Reverse_DC_Motor(void);  //反转-"DC_Motor 直流电机"(根据电位计电压进行调速)





#endif   /* __DC_Motor_H  */





