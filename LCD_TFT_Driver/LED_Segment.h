/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 LED_Segment.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■"动态数码管LED_Segment" -驱动程序(外部资源)-头文件
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



#ifndef  __LED_Segment_H 
#define  __LED_Segment_H 





////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"宏定义**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////






/////////////////////////////////////////////////////////////////////////////////
//==**"动态数码管LED_Segment" 亮度宏定义**===================//
#define	M_Brightness_OFF_LedSeg ( 0 ) //亮度为0 (显示关)--"动态数码管LED_Segment" 
#define	M_Brightness_1_LedSeg   ( 1 ) //亮度为1(最暗)--"动态数码管LED_Segment" 
#define	M_Brightness_2_LedSeg   ( 2 ) //亮度为2--"动态数码管LED_Segment" 
#define	M_Brightness_3_LedSeg   ( 3 ) //亮度为3--"动态数码管LED_Segment" 
#define	M_Brightness_4_LedSeg   ( 4 ) //亮度为4--"动态数码管LED_Segment" 
#define	M_Brightness_5_LedSeg   ( 5 ) //亮度为5--"动态数码管LED_Segment" 
#define	M_Brightness_6_LedSeg   ( 6 ) //亮度为6--"动态数码管LED_Segment" 
#define	M_Brightness_7_LedSeg   ( 7 ) //亮度为7--"动态数码管LED_Segment" 
#define	M_Brightness_8_LedSeg   ( 8 ) //亮度为8(最亮)--"动态数码管LED_Segment" 





/////////////////////////////////////////////////////////////////////////////////
//==**"此模块(动态数码管LED_Segment )专用"工作模式"宏定义**=//
#define	MODE_Idle_LED_Segment       (0) //Mode〓空闲(不做任何操作)("动态数码管LED_Segment" )
#define	MODE_Open_LED_Segment       (1) //Mode〓"打开"此模块("动态数码管LED_Segment" )
#define	MODE_Close_LED_Segment      (2) //Mode〓"关闭"此模块("动态数码管LED_Segment" )	
#define	MODE_Refresh_LED_Segment    (3) //Mode〓更新显示("动态数码管LED_Segment" )



////////////////////////////////////////////////////////////////////////////
//==**项目"专用"宏定义**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
//--**"动态数码管LED_Segment" *全局标志位**------------------------------//
extern union FLAGBIT16 LED_Seg_FlagBits; //"动态数码管LED_Segment" 相关标志位变量
#define  G_LED_Seg_FlagBits   LED_Seg_FlagBits.FLAG16  
#define	 F_500ms_LedSeg       LED_Seg_FlagBits.b.f0  //"动态数码管LED_Segment" 显示"间隔"时间
#define	 F_En_Scan_MatrixKey  LED_Seg_FlagBits.b.f1  //为1时，使能"矩阵按键扫描",  为0时，禁止扫描"矩阵按键扫描"
//#define	 F_      LED_Seg_FlagBits.b.f2  //为1时，
//#define	 F_      LED_Seg_FlagBits.b.f3  //为1时，
//#define	 F_      LED_Seg_FlagBits.b.f4  //为1时，
//#define	 F_      LED_Seg_FlagBits.b.f5  //为1时，
//#define	 F_      LED_Seg_FlagBits.b.f6  //为1时，
//#define	 F_      LED_Seg_FlagBits.b.f7  //为1时，
//#define	 F_      LED_Seg_FlagBits.b.f8  //为1时，
//#define	 F_      LED_Seg_FlagBits.b.f9  //为1时，
//#define	 F_      LED_Seg_FlagBits.b.f10 //为1时，
//#define	 F_      LED_Seg_FlagBits.b.f11 //为1时，
//#define	 F_      LED_Seg_FlagBits.b.f12 //为1时，
//#define	 F_      LED_Seg_FlagBits.b.f13 //为1时， 
//#define	 F_      LED_Seg_FlagBits.b.f14 //为1时，
//#define	 F_      LED_Seg_FlagBits.b.f15 //为1时，  


extern unsigned char G_Mode_LED_Segment; //"动态数码管LED_Segment" 工作模式
extern unsigned char G_Last_Mode_LED_Segment; //保存上一次"工作模式"

extern unsigned char G_LedSeg_Cnt; //"动态数码管LED_Segment" 中用到的计数器(用于字符循环显示)
extern unsigned char G_LedSegBuf[10]; //"动态数码管LED_Segment" 显示缓存数组//G_LedSegBuf[0]对应最"右边"的显示字符

extern unsigned char G_Brightness_LedSeg;  //亮度调节-"动态数码管LED_Segment" 
extern unsigned char G_BrightnessKind;     //亮度变量-"动态数码管LED_Segment" 




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

	//显示"开"+辉度"PWM为1/16" (最暗)("动态数码管LED_Segment" )
extern void Open_LED_Segment(void);

	//关闭LED_Segment ("动态数码管LED_Segment" )
extern void Close_LED_Segment(void);

	//处理数码管"辉度(亮度)"("动态数码管LED_Segment" )
extern void Deal_Brightness_LED_Segment(void);

	//更新显示("动态数码管LED_Segment" )
extern void Refresh_LED_Segment(void);


	//初使化"工作模式"("动态数码管LED_Segment" )
extern void Init_Mode_LED_Segment(unsigned char Mode);

	//"动态数码管LED_Segment" : 处理不同"工作模式"
extern void Deal_LED_Segment(void);

	//"显示字符"更新到"显示缓存数组"("动态数码管LED_Segment" )
extern void Disp_LED_Segment(unsigned char pointNum1,unsigned char pointNum2,unsigned char NO_8,unsigned char NO_7,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1);


#endif   /* __LED_Segment_H  */





