/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 TM1638.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■ "TM1638 数码管驱动器" -驱动程序-头文件(外部资源) 
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



#ifndef  __TM1638_H
#define  __TM1638_H


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"宏定义**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//--**显示命令(数码管)**宏定义**-------------------------------//
#define Disp_Mode_Off   (0x80) //显示"关"

#define Disp_Mode_1_16  (0x88) //显示"开"+辉度"PWM为1/16" (最暗)
#define Disp_Mode_2_16  (0x89) //显示"开"+辉度"PWM为2/16"
#define Disp_Mode_4_16  (0x8A) //显示"开"+辉度"PWM为4/16"
#define Disp_Mode_10_16 (0x8B) //显示"开"+辉度"PWM为10/16"
#define Disp_Mode_11_16 (0x8C) //显示"开"+辉度"PWM为11/16"
#define Disp_Mode_12_16 (0x8D) //显示"开"+辉度"PWM为12/16"
#define Disp_Mode_13_16 (0x8E) //显示"开"+辉度"PWM为13/16"
#define Disp_Mode_14_16 (0x8F) //显示"开"+辉度"PWM为14/16" (最亮)


////////////////////////////////////////////////////////////////////////////
//==**命令设置*宏定义**================================//

////////////////////////////////////////////////////////////////////////////
//--**数据命令***宏定义**-----------------------------------------//
#define CMD_IncreaseAddr_TM1638 (0X40) //Cmd★地址模式设置: 自动地址增加(数据命令)
#define CMD_FixedAddr_TM1638    (0X44) //Cmd★地址模式设置: 固定地址(数据命令)



////////////////////////////////////////////////////////////////////////////
//--**地址命令***宏定义**-----------------------------------------//
#define	CMD_DispAddr_TM1638	(0xC0)  //Cmd★显示地址命令

#define	ADDR_No1_TM1638	 (0xC6)  //Addr＠第"1位"数码管(从最右边算起) 显示地址(TM1638)
#define	ADDR_No2_TM1638	 (0xC4)  //Addr＠第"2位"数码管(从最右边算起) 显示地址(TM1638)
#define	ADDR_No3_TM1638	 (0xC2)  //Addr＠第"3位"数码管(从最右边算起) 显示地址(TM1638)
#define	ADDR_No4_TM1638	 (0xC0)  //Addr＠第"4位"数码管(从最右边算起) 显示地址(TM1638)
#define	ADDR_No5_TM1638	 (0xCE)  //Addr＠第"5位"数码管(从最右边算起) 显示地址(TM1638)
#define	ADDR_No6_TM1638	 (0xCC)  //Addr＠第"6位"数码管(从最右边算起) 显示地址(TM1638)
#define	ADDR_No7_TM1638	 (0xCA)  //Addr＠第"7位"数码管(从最右边算起) 显示地址(TM1638)
#define	ADDR_No8_TM1638	 (0xC8)  //Addr＠第"8位"数码管(从最右边算起) 显示地址(TM1638)



////////////////////////////////////////////////////////////////////////////
//==**"动态数码管LED_Segment" 显示表格对应"显示字符"**===//
#define	DISP_MaxNum_LedSeg ( 22 ) //DISP◎"共有22个显示字符""动态数码管LED_Segment" 

#define	DISP_0_LedSeg     ( 0 ) //DISP◎"0"--"动态数码管LED_Segment" 
#define	DISP_1_LedSeg     ( 1 ) //DISP◎"1"--"动态数码管LED_Segment" 
#define	DISP_2_LedSeg     ( 2 ) //DISP◎"2"--"动态数码管LED_Segment" 
#define	DISP_3_LedSeg     ( 3 ) //DISP◎"3"--"动态数码管LED_Segment" 
#define	DISP_4_LedSeg     ( 4 ) //DISP◎"4"--"动态数码管LED_Segment" 
#define	DISP_5_LedSeg     ( 5 ) //DISP◎"5"--"动态数码管LED_Segment" 
#define	DISP_6_LedSeg     ( 6 ) //DISP◎"6"--"动态数码管LED_Segment" 
#define	DISP_7_LedSeg     ( 7 ) //DISP◎"7"--"动态数码管LED_Segment" 
#define	DISP_8_LedSeg     ( 8 ) //DISP◎"8"--"动态数码管LED_Segment" 
#define	DISP_9_LedSeg     ( 9 ) //DISP◎"9"--"动态数码管LED_Segment" 

#define	DISP_A_LedSeg     ( 10 ) //DISP◎"A"--"动态数码管LED_Segment" 
#define	DISP_b_LedSeg     ( 11 ) //DISP◎"b"--"动态数码管LED_Segment" 
#define	DISP_C_LedSeg     ( 12 ) //DISP◎"C"--"动态数码管LED_Segment" 
#define	DISP_d_LedSeg     ( 13 ) //DISP◎"d"--"动态数码管LED_Segment" 
#define	DISP_E_LedSeg     ( 14 ) //DISP◎"E"--"动态数码管LED_Segment" 
#define	DISP_F_LedSeg     ( 15 ) //DISP◎"F"--"动态数码管LED_Segment" 

#define	DISP_Point_LedSeg ( 16 ) //DISP◎"."(小数点)--"动态数码管LED_Segment" 
#define	DISP_Plus_LedSeg  ( 17 ) //DISP◎"+"(加号,正号)--"动态数码管LED_Segment" 
#define	DISP_Minus_LedSeg ( 18 ) //DISP◎"-"(减号,负号)--"动态数码管LED_Segment" 
#define	DISP_Equal_LedSeg ( 19 ) //DISP◎"="(等于号)--"动态数码管LED_Segment" 

#define	DISP_ON_LedSeg    ( 20 ) //DISP◎"全亮"--"动态数码管LED_Segment" 
#define	DISP_OFF_LedSeg   ( 21 ) //DISP◎"暗码"--"动态数码管LED_Segment" 

#define	DISP_I_LedSeg     ( 22 ) //DISP◎"I"--"动态数码管LED_Segment" 
#define	DISP_r_LedSeg     ( 23 ) //DISP◎"r"--"动态数码管LED_Segment" 
#define	DISP_U_LedSeg     ( 24 ) //DISP◎"U"--"动态数码管LED_Segment" 









////////////////////////////////////////////////////////////////////////////
//==**项目"专用"宏定义**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////


#define	M_LedAllOff_TM1638    (1)  //"所有"数码管: 都关闭显示
#define	M_LedAllOn_TM1638     (2)  //所有数码管的"所有Led段"全亮


#define	M_LedLoopNum_TM1638	 (3)  //"所有"数码管: 同时"循环"显示"相同"字符
#define	M_LedKeyNum_TM1638	 (4)  //根据"按键"，在对应的第"x"个数码管，显示"x"




////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
extern union FLAGBIT16 TM1638_FlagBits;  //"TM1638"用到的时间标志位
#define  G_TM1638_FlagBits TM1638_FlagBits.FLAG16  
//#define  F_         TM1638_FlagBits.b.f0 //为1时，
//#define  F_         TM1638_FlagBits.b.f1  //为1时，
//#define  F_ 	   TM1638_FlagBits.b.f2  //为1时，
//#define  F_	   TM1638_FlagBits.b.f3  //为1时，	 
//#define  F_         TM1638_FlagBits.b.f4  //为1时，
//#define  F_         TM1638_FlagBits.b.f5  //为1时，   
//#define  F_	   TM1638_FlagBits.b.f6  //为1时，   
//#define  F_         TM1638_FlagBits.b.f7  //为1时， 
//#define  F_	   TM1638_FlagBits.b.f8  //为1时，  
//#define  F_	   TM1638_FlagBits.b.f9  //为1时，	 
//#define  F_	   TM1638_FlagBits.b.f10 //为1时，	 
//#define  F_	   TM1638_FlagBits.b.f11 //为1时，	 
//#define  F_	   TM1638_FlagBits.b.f12 //为1时，	 	 
//#define  F_	   TM1638_FlagBits.b.f13 //为1时，	 	 
//#define  F_	   TM1638_FlagBits.b.f14 //为1时，	  
//#define  F_	   TM1638_FlagBits.b.f15 //为1时，	 	 




extern unsigned char G_TM1638_DispMode; //TM1638的显示辉度变量



////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**"函数"宏定义**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"函数声明**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////

	//设置显示模式:显示关、显示开+辉度调节(不同PWM占空比驱动)(TM1638)
extern void TM1638_Disp_Mode(unsigned char Disp_Mode);






////////////////////////////////////////////////////////////////////////////
//==**"外部" API 函数声明**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

	//指定"单个"数码管: 以指定"辉度"显示字符(TM1638)
extern void Disp_Single_LedSeg(unsigned char Num,unsigned char Disp_Mode,unsigned char Data);  


	//设置显示模式:显示关(TM1638)
extern void Close_Display_TM1638(void);

	//打开显示(初始化):显示"开"+辉度"PWM为1/16" (最暗)(TM1638)
extern void Open_Display_TM1638(void);

	//向TM1638显示地址写要"显示的数据"(TM1638)
extern void Write_DispData_TM1638(unsigned char pointNum1,unsigned char pointNum2,unsigned char NO_8,unsigned char NO_7,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1);

	//处理"动态数码管LED_Segment" :显示关，显示开，调节"辉度PWM"(TM1638)
extern void Deal_Brightness_TM1638(unsigned char DispMode);


	//读矩阵按键值(TM1638)
extern unsigned char Read_MatrixKey_TM1638(void);




#endif    /* __TM1638_H */


