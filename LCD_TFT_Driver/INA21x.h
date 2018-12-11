/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 INA21x.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■ "INA21x 电流分流监控器" -驱动程序(外部资源)-头文件
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

#ifndef  __INA21x_H 
#define  __INA21x_H 


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"宏定义**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////

#define M_INA21x_AdSampleNum  (16) //AD采样次数，再取平均值 



////////////////////////////////////////////////////////////////////////////
//==**项目"专用"宏定义**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
extern union FLAGBIT16 INA21x_FlagBits;  //"INA21x 电流分流监控器" 相关标志位变量
#define  G_INA21x_FlagBits      INA21x_FlagBits.FLAG16  
#define	 F_500ms_Reflash_INA21x INA21x_FlagBits.b.f0  //为1时，在常用区域，刷新LCD_TFT 显示("INA21x 电流分流监控器" )
#define	 F_500ms_INA21x_InTest  INA21x_FlagBits.b.f1  //为1时，在测试区域，刷新LCD_TFT 显示("INA21x 电流分流监控器" )
//#define	 F_      INA21x_FlagBits.b.f2  //为1时，
//#define	 F_      INA21x_FlagBits.b.f3  //为1时，
//#define	 F_      INA21x_FlagBits.b.f4  //为1时，
//#define	 F_      INA21x_FlagBits.b.f5  //为1时，
//#define	 F_      INA21x_FlagBits.b.f6  //为1时，
//#define	 F_      INA21x_FlagBits.b.f7  //为1时，
//#define	 F_      INA21x_FlagBits.b.f8  //为1时，
//#define	 F_      INA21x_FlagBits.b.f9  //为1时，
//#define	 F_      INA21x_FlagBits.b.f10 //为1时，
//#define	 F_      INA21x_FlagBits.b.f11 //为1时，
//#define	 F_      INA21x_FlagBits.b.f12 //为1时，
//#define	 F_      INA21x_FlagBits.b.f13 //为1时， 
//#define	 F_      INA21x_FlagBits.b.f14 //为1时，
//#define	 F_      INA21x_FlagBits.b.f15 //为1时，  



extern unsigned int G_INA21x_AdResult; //把M_INA21x_AdSampleNum次AD采样值从小到大排序后，求得的最后AD计算值





////////////////////////////////////////////////////////////////////////////
//==**"函数"宏定义**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"函数声明**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////
extern void Sample_INA21x_AD(void);  //多次采样"INA21x 电流分流监控器"AD

extern void Deal_INA21x(void);  //处理 "INA21x 电流分流监控器": AD采样，AD数据处理，显示处理


////////////////////////////////////////////////////////////////////////////
//==**"外部" API 函数声明**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////







#endif   /* __INA21x_H  */





