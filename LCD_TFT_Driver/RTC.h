/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 RTC.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■"RTC 内部实时时钟" -驱动程序-头文件(处理器内部资源) 
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


#ifndef  __RTC_H 
#define  __RTC_H 


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"宏定义**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**项目"专用"宏定义**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
extern union FLAGBIT16 RTC_FlagBits;   //"RTC 内部实时时钟"相关标志位变量
#define  G_RTC_FlagBits     RTC_FlagBits.FLAG16  
#define	 F_SecondChange_RTC RTC_FlagBits.b.f0  //为1时，"秒"改变时--"RTC 内部实时时钟"
#define	 F_MinuteChange_RTC RTC_FlagBits.b.f1  //为1时，"分钟"改变时--"RTC 内部实时时钟"
#define	 F_HourChange_RTC   RTC_FlagBits.b.f2  //为1时，"小时"改变时--"RTC 内部实时时钟"
//#define	 F_      RTC_FlagBits.b.f3  //为1时，
//#define	 F_      RTC_FlagBits.b.f4  //为1时，
//#define	 F_      RTC_FlagBits.b.f5  //为1时，
//#define	 F_      RTC_FlagBits.b.f6  //为1时，
//#define	 F_      RTC_FlagBits.b.f7  //为1时，
//#define	 F_      RTC_FlagBits.b.f8  //为1时，
//#define	 F_      RTC_FlagBits.b.f9  //为1时，
//#define	 F_      RTC_FlagBits.b.f10 //为1时，
//#define	 F_      RTC_FlagBits.b.f11 //为1时，
//#define	 F_      RTC_FlagBits.b.f12 //为1时，
//#define	 F_      RTC_FlagBits.b.f13 //为1时， 
//#define	 F_      RTC_FlagBits.b.f14 //为1时，
//#define	 F_      RTC_FlagBits.b.f15 //为1时，  


	//读出缓存数组
extern unsigned char G_RTC_ReadBuf[24];	


	//修改缓存数组BCD码(RTC) :	 年_H,年_L,月,Week, 日,  时, 分,  秒
extern unsigned char G_RTC_WriteBuf[8];


extern unsigned int  G_Year_SetBuf;   //"年"值(修改时间)(采用十进制)
extern unsigned char G_Month_SetBuf;  //"月"值(修改时间)(采用十进制)
extern unsigned char G_Date_SetBuf;   //"日"值(修改时间)(采用十进制)

extern unsigned char G_Hour_SetBuf;   //"小时"值(修改时间)(采用十进制)
extern unsigned char G_Minute_SetBuf; //"分钟"值(修改时间)(采用十进制)
extern unsigned char G_Second_SetBuf; //"秒"值(修改时间)(采用十进制)

extern unsigned char G_Week_SetBuf;   //"星期"值(修改时间)(采用十进制)



extern unsigned char G_LastSecondBuf;  //存上次"秒"时间,用于时间变化刷新时间
extern unsigned char G_LastMinuteBuf;  //存上次"分钟"时间
extern unsigned char G_LastHourBuf;    //存上次"小时"时间



////////////////////////////////////////////////////////////////////////////
//==**"函数"宏定义**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"函数声明**Exported Module-specific funcitions**===//
////////////////////////////////////////////////////////////////////////////

extern void Init_RTC_B(void);  //初始化: RTC_B 实时时钟

extern void Read_RTC_CurrentTime(void);//实时读取: RTC 实时时钟

	//检测输入修改时间是否合法
extern unsigned char Check_RTC_InputModifyDate(void); 

	//修改RTC实时时钟
extern void Modify_RealTime_RTC(void);



////////////////////////////////////////////////////////////////////////////
//==**"外部" API 函数声明**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

	//处理" RTC 实时时钟":采样实时时间，显示实时时间
extern void Deal_RTC(void); 






#endif   /* __RTC_H  */





