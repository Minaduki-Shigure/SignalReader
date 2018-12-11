/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 LCD_Segment.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■"段式LCD_Segment" -驱动程序(外部资源)-头文件
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



#ifndef  __LCD_Segment_H 
#define  __LCD_Segment_H 





////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"宏定义**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//==**""段式LCD_Segment" 各单独小段的宏 定义**============//
#define  dd  (0x01)
#define  cc  (0x20)
#define  bb  (0x40) //不能定义为 #define  b  (0x40),因为在  FLAGBIT中有用到"b"
#define  aa  (0x80)
#define  dp  (0x10)
#define  gg  (0x04)
#define  ff  (0x08)
#define  ee  (0x02)

////////////////////////////////////////////////////////////////////////////
//==**"段式LCD_Segment" 显示表格对应的"显示字符"**=======//
#define	DISP_MaxNum_LcdSeg ( 22 ) //DISP◎"共有22个显示字符""段式LCD_Segment" 

#define	DISP_0_LcdSeg     ( 0 ) //DISP◎"0"--"段式LCD_Segment" 
#define	DISP_1_LcdSeg     ( 1 ) //DISP◎"1"--"段式LCD_Segment" 
#define	DISP_2_LcdSeg     ( 2 ) //DISP◎"2"--"段式LCD_Segment" 
#define	DISP_3_LcdSeg     ( 3 ) //DISP◎"3"--"段式LCD_Segment" 
#define	DISP_4_LcdSeg     ( 4 ) //DISP◎"4"--"段式LCD_Segment" 
#define	DISP_5_LcdSeg     ( 5 ) //DISP◎"5"--"段式LCD_Segment" 
#define	DISP_6_LcdSeg     ( 6 ) //DISP◎"6"--"段式LCD_Segment" 
#define	DISP_7_LcdSeg     ( 7 ) //DISP◎"7"--"段式LCD_Segment" 
#define	DISP_8_LcdSeg     ( 8 ) //DISP◎"8"--"段式LCD_Segment" 
#define	DISP_9_LcdSeg     ( 9 ) //DISP◎"9"--"段式LCD_Segment" 

#define	DISP_A_LcdSeg     ( 10 ) //DISP◎"A"--"段式LCD_Segment"
#define	DISP_b_LcdSeg     ( 11 ) //DISP◎"b"--"段式LCD_Segment"
#define	DISP_c_LcdSeg     ( 12 ) //DISP◎"C"--"段式LCD_Segment"
#define	DISP_d_LcdSeg     ( 13 ) //DISP◎"d"--"段式LCD_Segment"
#define	DISP_E_LcdSeg     ( 14 ) //DISP◎"E"--"段式LCD_Segment" 
#define	DISP_F_LcdSeg     ( 15 ) //DISP◎"F"--"段式LCD_Segment" 

#define	DISP_Point_LcdSeg ( 16 ) //DISP◎"."(小数点)--"段式LCD_Segment" 
#define	DISP_Plus_LcdSeg  ( 17 ) //DISP◎"+"(加号,正号)--"段式LCD_Segment" 
#define	DISP_Minus_LcdSeg ( 18 ) //DISP◎"-"(减号,负号)--"段式LCD_Segment" 
#define	DISP_Equal_LcdSeg ( 19 ) //DISP◎"="(等于号)--"段式LCD_Segment" 

#define	DISP_ON_LcdSeg    ( 20 ) //DISP◎"全亮"--"段式LCD_Segment" 
#define	DISP_OFF_LcdSeg   ( 21 ) //DISP◎"暗码"--"段式LCD_Segment" 




////////////////////////////////////////////////////////////////////////////
//==**"此模块(段式LCD_Segment)专用"工作模式"宏定义**=====//

#define	MODE_Idle_LCD_Segment           (0) //Mode〓空闲(不做任何操作)(段式LCD_Segment)
#define	MODE_Open_LCD_Segment           (1) //Mode〓"打开"此模块(段式LCD_Segment)
#define	MODE_Close_LCD_Segment          (2) //Mode〓"关闭"此模块(段式LCD_Segment)	
#define	MODE_Refresh_LCD_Segment        (3) //Mode〓更新显示(段式LCD_Segment)
#define	MODE_OpenBackLight_LCD_Segment  (4) //Mode〓"打开"背光(段式LCD_Segment)		
#define	MODE_CloseBackLight_LCD_Segment (5) //Mode〓"关闭"背光(段式LCD_Segment)		
		



////////////////////////////////////////////////////////////////////////////
//==**项目"专用"宏定义**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//--**LCD_Segment*全局标志位**-------------------------------------//

extern union FLAGBIT16 LCD_Seg_FlagBits;	//"段式LCD_Segment"相关标志位变量
#define  G_LCD_Seg_FlagBits LCD_Seg_FlagBits.FLAG16  
#define	 F_500ms_LcdSeg     LCD_Seg_FlagBits.b.f0  //"段式LCD_Segment"显示"间隔"时间
//#define	 F_      LCD_Seg_FlagBits.b.f1  //为1时，
//#define	 F_      LCD_Seg_FlagBits.b.f2  //为1时，
//#define	 F_      LCD_Seg_FlagBits.b.f3  //为1时，
//#define	 F_      LCD_Seg_FlagBits.b.f4  //为1时，
//#define	 F_      LCD_Seg_FlagBits.b.f5  //为1时，
//#define	 F_      LCD_Seg_FlagBits.b.f6  //为1时，
//#define	 F_      LCD_Seg_FlagBits.b.f7  //为1时，
//#define	 F_      LCD_Seg_FlagBits.b.f8  //为1时，
//#define	 F_      LCD_Seg_FlagBits.b.f9  //为1时，
//#define	 F_      LCD_Seg_FlagBits.b.f10 //为1时，
//#define	 F_      LCD_Seg_FlagBits.b.f11 //为1时，
//#define	 F_      LCD_Seg_FlagBits.b.f12 //为1时，
//#define	 F_      LCD_Seg_FlagBits.b.f13 //为1时， 
//#define	 F_      LCD_Seg_FlagBits.b.f14 //为1时，
//#define	 F_      LCD_Seg_FlagBits.b.f15 //为1时，  

extern unsigned char G_Mode_LCD_Segment; //"段式LCD_Segment"工作模式
extern unsigned char G_Last_Mode_LCD_Segment; //保存上一次"工作模式"


extern unsigned char G_LcdSeg_Cnt; //"段式LCD_Segment"中用到的计数器(用于字符循环显示)

extern unsigned char G_LcdSegBuf[7]; //"段式LCD_Segment"显示缓存数组//G_LcdSegBuf[0]对应最"右边"的显示字符




////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
//==**"函数"宏定义**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"函数声明**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////
	//打开或者关闭液晶LCD_B 模块
extern void EnModule_LCD_Segment(unsigned char EnBit);  

	//使能或禁止所有LCD_B段(用于所有液晶段(整屏)的闪烁)
extern void EnAllSeg_LCD_Segment(unsigned char EnBit); 

	//清屏: 清除处理器内部的"段式LCD 显示缓存"
extern void Clear_LCD_Segment(void);   


extern void Open_LCD_Segment(void); //打开LCD_Segment (初使化): LCD_Segment 内部寄存器配置; 端口初始化等

extern void Close_LCD_Segment(void);  //关闭"段式LCD_Segment"


extern void Initial_LCD_Segment_LCD_B(void); //LCD_B模块初始化:端口初始化、配置LCD_B功能(LCD_Segment )

	 //更新显示(段式LCD_Segment)
extern void Refresh_LCD_Segment(unsigned char pointNum,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1); 


////////////////////////////////////////////////////////////////////////////
//==**"外部" API 函数声明**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

	//初使化"工作模式"(段式LCD_Segment)
extern void Init_Mode_LCD_Segment(unsigned char Mode);

	//"段式LCD_Segment": 处理不同"工作模式"
extern void Deal_LCD_Segment(void);  

	//"显示字符"更新到"显示缓存数组"(段式LCD_Segment)
extern void Disp_LCD_Segment(unsigned char pointNum,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1);


#endif   /* __LCD_Segment_H  */





