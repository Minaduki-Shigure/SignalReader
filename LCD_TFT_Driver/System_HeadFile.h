/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 System_HeadFile.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■ 系统全部头文件集(包含所有使用到的头文件)-头文件
	01) 用于主要程序模块的调用    
	02)     03)    04)    05)    06)	
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




#ifndef __System_HeadFile_H
#define	__System_HeadFile_H

////////////////////////////////////////////////////////////////////////////
//==**软件提取标准库**=================================//
////////////////////////////////////////////////////////////////////////////

//#include <math.h>
//#include <string.h>
//#include <stdio.h>
//#include <macros.h>





////////////////////////////////////////////////////////////////////////////
//==**系统常用--头文件**===============================//
//不用的模块用"//"屏蔽掉，但不要删掉///////////////////////

#include "Generic.h"	//常用程序编程规范、函数集 -头文件-Generic Type Definitions


#include "System.h"	 //"系统" 常用功能函数集-头文件
#include "Hardware_Profile.h"  //处理器"硬件配置文件" -头文件-Hardware specific definitions for Processor




#include "MyProject.h"	//具体项目: 总功能程序-头文件

	//具体项目: LCD_TFT液晶显示部份(包括所有的液晶内容) -头文件
#include "MyProject_Set_LCD_TFT.h"

//#include ".h"

//#include ".h"





////////////////////////////////////////////////////////////////////////////
//==**MCU 内部资源--头文件**============================//
//不用的模块用"//"屏蔽掉，但不要删掉///////////////////////

#include "HAL_PMM.h"  //F5xx_F6xx_Core_Lib//系统电源管理模块-头文件 
#include "HAL_UCS.h"  //F5xx_F6xx_Core_Lib//系统时钟配置-头文件 



#include "msp430f6638.h"   // "处理器"头文件: 内部寄存相关定义等(处理器内部资源) 

#include "Timer.h"     //"定时器" -驱动程序-头文件(处理器内部资源) 

#include "RTC.h"   //"RTC 内部实时时钟" -驱动程序-头文件(处理器内部资源) 

#include "SPI.h"     //"SPI 同步串行外设接口" -驱动程序 -头文件(处理器内部资源)

#include "I2C.h"   //"I2C" -驱动程序-头文件(处理器内部资源) 

#include "ADC.h"   //"ADC"模数转换模块 -驱动程序-头文件(处理器内部资源) 

#include "UART.h"   //"UART 通用异步接收/发送装置" -驱动程序(内部资源)-头文件


	//Touch Pads
#include "CTS_HAL.h"   
#include "CTS_Layer.h"
#include "structure.h"


	//SD Card
#include "SDaccess.h" //"SD_Card SD卡"-驱动程序(外部资源)-头文件

    //USB
#include "MassStorage.h"

//#include ".h"
//#include ".h"


////////////////////////////////////////////////////////////////////////////
//==**外部资源--头文件**===============================//
//不用的模块用"//"屏蔽掉，但不要删掉///////////////////////

#include "TM1638.h"   // "TM1638 数码管驱动器" -驱动程序-头文件(外部资源) 

#include "Key.h"       //"IO 按键" -驱动程序-头文件(外部资源)

#include "Buzzer.h"   //"锋鸣器"-驱动程序(外部资源)-头文件

#include "MatrixKey.h"   //"矩阵按键" -驱动程序(外部资源)-头文件

#include "Speaker.h"   //"Speaker 扬声器" -驱动程序(外部资源)-头文件

//#include "LCD_TFT.h"    // "彩屏LCD_TFT"-驱动程序-头文件(外部资源) 

#include "LCD_TFT_ILI9325.h"  // "彩屏LCD_TFT_ILI9325" -驱动程序(外部资源) -头文件



#include "LCD_Segment.h" //"段式LCD_Segment" -驱动程序(外部资源)-头文件

#include "LED_Segment.h" //"动态数码管LED_Segment" -驱动程序(外部资源)-头文件

#include "Touch_Pad.h"   //"Touch_Pad 电容按键" -驱动程序(外部资源)-头文件

#include "INA21x.h"  // "INA21x 电流分流监控器" -驱动程序(外部资源)-头文件   

#include "BQ27410_FuelGauge.h"   //"BQ27410_FuelGauge 锂电池电量监测计"-驱动程序(外部资源)-头文件


#include "NTC_Temperature.h"  //"NTC 电阻温度传感器" -驱动程序(外部资源)-头文件

#include "CD405x_Multiplexer.h"   //"CD405x_Multiplexer多路选择模拟开关"  -驱动程序(外部资源)-头文件

#include "HR202_Humidity.h"   //"HR202_Humidity 电阻型湿度传感器" -驱动程序(外部资源)-头文件

#include "Step_Motor.h"   //"Step_Motor 步进电机" -驱动程序(外部资源)-头文件

#include "DC_Motor.h"     //"DC_Motor 直流电机" -驱动程序(外部资源)-头文件

#include "TMP006_Temperature.h"   //"TMP006_Temperature 红外温度传感器"-驱动程序(外部资源)-头文件

#include "TMP100_Temperature.h"   //"TMP100_Temperature 温度传感器" -驱动程序(外部资源)-头文件


#include "CC1101.h"   //"CC1101 低功耗射频收发器"-驱动程序(外部资源)-头文件



//#include ".h"
//#include ".h"
//#include ".h"



#endif /*__System_HeadFile_H */






