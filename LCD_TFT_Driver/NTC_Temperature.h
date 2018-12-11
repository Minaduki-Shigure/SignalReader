/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 NTC_Temperature.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■"NTC 电阻温度传感器" -驱动程序(外部资源)-头文件
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

#ifndef  __NTC_Temperature_H 
#define  __NTC_Temperature_H 


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"宏定义**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////
#define M_NTC_TMP_AdSampleNum  (16) //AD采样次数，再取平均值 




////////////////////////////////////////////////////////////////////////////
//==**项目"专用"宏定义**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
extern union FLAGBIT16 NTC_TMP_FlagBits;  //"NTC 电阻温度传感器" 相关标志位变量
#define  G_NTC_TMP_FlagBits       NTC_TMP_FlagBits.FLAG16  
#define	 F_500ms_Reflash_NTC_TMP  NTC_TMP_FlagBits.b.f0  //为1时，在常用区域，刷新LCD_TFT的显示("NTC 电阻温度传感器"  )
#define	 F_500ms_NTC_HR202_InTest NTC_TMP_FlagBits.b.f1  //为1时，在测试区域，刷新LCD_TFT显示NTC（温度）、HR202（湿度）
//#define	 F_      NTC_TMP_FlagBits.b.f2  //为1时，
//#define	 F_      NTC_TMP_FlagBits.b.f3  //为1时，
//#define	 F_      NTC_TMP_FlagBits.b.f4  //为1时，
//#define	 F_      NTC_TMP_FlagBits.b.f5  //为1时，
//#define	 F_      NTC_TMP_FlagBits.b.f6  //为1时，
//#define	 F_      NTC_TMP_FlagBits.b.f7  //为1时，
//#define	 F_      NTC_TMP_FlagBits.b.f8  //为1时，
//#define	 F_      NTC_TMP_FlagBits.b.f9  //为1时，
//#define	 F_      NTC_TMP_FlagBits.b.f10 //为1时，
//#define	 F_      NTC_TMP_FlagBits.b.f11 //为1时，
//#define	 F_      NTC_TMP_FlagBits.b.f12 //为1时，
//#define	 F_      NTC_TMP_FlagBits.b.f13 //为1时， 
//#define	 F_      NTC_TMP_FlagBits.b.f14 //为1时，
//#define	 F_      NTC_TMP_FlagBits.b.f15 //为1时，  


extern int G_NTC_Temperature; //把M_NTC_TMP_AdSampleNum次AD采样值从小到大排序后，并转化为最后的实际物理量




////////////////////////////////////////////////////////////////////////////
//==**"函数"宏定义**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"函数声明**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////

	//转换"NTC 电阻温度传感器" AD值为实际"温度值"
extern int ConverseToTemperature(long R);

extern void Sample_NTC_TMP_AD(void); //多次采样"NTC 电阻温度传感器" AD

////////////////////////////////////////////////////////////////////////////
//==**"外部" API 函数声明**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

	//处理 "NTC 电阻温度传感器" : AD采样，AD数据处理，显示处理
extern void Deal_NTC_Temperature(void);







#endif   /* __NTC_Temperature_H  */





