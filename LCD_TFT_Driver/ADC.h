/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 ADC.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■ "ADC"模数转换模块 -驱动程序-头文件(处理器内部资源) 
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

#ifndef  __ADC_H 
#define  __ADC_H 


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"宏定义**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////
#define M_AdSampleNum  (16) //AD采样次数，再取平均值 



////////////////////////////////////////////////////////////////////////////
//==**项目"专用"宏定义**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////
#define M_Potentiometer_AdNum ( 6  ) //Potentiometer电位器使用AD6(第6 AD通道)
#define M_INA21x_AdNum        ( 7 ) //INA21x监测电流，使用AD7(第7 AD通道)
#define M_NTC_TMP_AdNum       ( 12 ) //"NTC 电阻温度传感器"使用AD12 (第12 AD通道)




////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
extern union FLAGBIT16 ADC_FlagBits; //"ADC模数转换"相关标志位变量
#define  G_ADC_FlagBits   ADC_FlagBits.FLAG16  
#define	 F_500ms_Reflash_Potentiometer ADC_FlagBits.b.f0 //为1时，刷新LCD_TFT显示"电压值"(电位计 )
//#define	 F_      ADC_FlagBits.b.f1  //为1时，
//#define	 F_      ADC_FlagBits.b.f2  //为1时，
//#define	 F_      ADC_FlagBits.b.f3  //为1时，
//#define	 F_      ADC_FlagBits.b.f4  //为1时，
//#define	 F_      ADC_FlagBits.b.f5  //为1时，
//#define	 F_      ADC_FlagBits.b.f6  //为1时，
//#define	 F_      ADC_FlagBits.b.f7  //为1时，
//#define	 F_      ADC_FlagBits.b.f8  //为1时，
//#define	 F_      ADC_FlagBits.b.f9  //为1时，
//#define	 F_      ADC_FlagBits.b.f10 //为1时，
//#define	 F_      ADC_FlagBits.b.f11 //为1时，
//#define	 F_      ADC_FlagBits.b.f12 //为1时，
//#define	 F_      ADC_FlagBits.b.f13 //为1时， 
//#define	 F_      ADC_FlagBits.b.f14 //为1时，
//#define	 F_      ADC_FlagBits.b.f15 //为1时，  

extern unsigned int G_LastAdResult;    //把M_AdSampleNum次AD采样值从小到大排序后，求得的最后AD计算值



////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
//==**"函数"宏定义**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"函数声明**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////

extern void ADC12_A_Initial(void); //ADC12_A  内部资源初始化 

extern void Open_ADC12_A(void); // 打开ADC12_A模块
extern void Close_ADC12_A(void); // 关闭ADC12_A模块

	//启动ADC_12_A模块，选择指定AD通道，并采样一次AD值。
extern unsigned int Sample_ADC12_A(unsigned char AD_Num);


////////////////////////////////////////////////////////////////////////////
//==**"外部" API 函数声明**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

	//处理采样结果: 将多次采样值，进行排序，去掉两头，对中间的几个AD值求平均，得到最后的AD值。
extern void Deal_ADC12_A(unsigned char AD_Num);  




#endif   /* __ADC_H  */





