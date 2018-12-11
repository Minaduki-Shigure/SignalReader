/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 HR202_Humidity.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■"HR202_Humidity 电阻型湿度传感器" -驱动程序(外部资源)-头文件
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

#ifndef  __HR202_Humidity_H 
#define  __HR202_Humidity_H 


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"宏定义**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**项目"专用"宏定义**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
extern union FLAGBIT16 HR202_Humidity_FlagBits; //"HR202_Humidity 电阻型湿度传感器"相关标志位变量
#define  G_HR202_Humidity_FlagBits HR202_Humidity_FlagBits.FLAG16  
//#define	 F_1s_HR202_Frequency      HR202_Humidity_FlagBits.b.f0  //为1时，"湿度值"相应频率值(1s内的脉冲次数)
#define	 F_500ms_Reflash_Humidity  HR202_Humidity_FlagBits.b.f1  //为1时，在常用区域，刷新LCD_TFT 显示("HR202_Humidity 电阻型湿度传感器" )
#define	 F_250ms_Sample_Humidity   HR202_Humidity_FlagBits.b.f2  //为1时，250ms读取一次湿度值"相应频率值
#define	 F_EnRead_Humidity         HR202_Humidity_FlagBits.b.f3  //为1时，可以读取湿度频率值
//#define	 F_      HR202_Humidity_FlagBits.b.f4  //为1时，
//#define	 F_      HR202_Humidity_FlagBits.b.f5  //为1时，
//#define	 F_      HR202_Humidity_FlagBits.b.f6  //为1时，
//#define	 F_      HR202_Humidity_FlagBits.b.f7  //为1时，
//#define	 F_      HR202_Humidity_FlagBits.b.f8  //为1时，
//#define	 F_      HR202_Humidity_FlagBits.b.f9  //为1时，
//#define	 F_      HR202_Humidity_FlagBits.b.f10 //为1时，
//#define	 F_      HR202_Humidity_FlagBits.b.f11 //为1时，
//#define	 F_      HR202_Humidity_FlagBits.b.f12 //为1时，
//#define	 F_      HR202_Humidity_FlagBits.b.f13 //为1时， 
//#define	 F_      HR202_Humidity_FlagBits.b.f14 //为1时，
//#define	 F_      HR202_Humidity_FlagBits.b.f15 //为1时，  

extern unsigned char G_HR202_Humidity;  //存最后得到的"湿度值"



////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
//==**"函数"宏定义**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"函数声明**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////
	//初始化设置:  "HR202_Humidity 电阻型湿度传感器"
extern void HR202_Humidity_Initial(void);

	//转换"HR202_Humidity 电阻型湿度传感器" 频率值为实际"湿度值"
extern unsigned char ConverseToHumidity(unsigned long R, int temperature);




////////////////////////////////////////////////////////////////////////////
//==**"外部" API 函数声明**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

	//1秒定时到,使能读取HR202与555输出的频率
//extern void HR202_EnRead_Frequency(void);

	//在中断,采样"湿度值"相应频率值
extern void Sample_HR202_Frequency(void);



	//处理 "HR202_Humidity 电阻型湿度传感器"
extern void Deal_HR202_Humidity(void);






#endif   /* __HR202_Humidity_H  */





