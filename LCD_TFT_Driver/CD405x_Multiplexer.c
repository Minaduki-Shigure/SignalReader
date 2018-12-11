/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 CD405x_Multiplexer.c
* 附属文件-Dependencies:  	 CD405x_Multiplexer.h; Hardware_Profile.h; Generic.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■"CD405x_Multiplexer多路选择模拟开关"  -驱动程序(外部资源)
	01) CD4052B 是双四选一模拟开关，每组四选一模拟开关分别
有2 个二进制控制输入。
	02) INH 输入端输入“1”电平时将两组四选一模拟开关所有通道置为关断状态。
	03) 很宽的数字控制与传输模拟信号电压范围：数字3～15V，模拟15Vp-p
	04)     05)      06)	
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


#include "Generic.h"	//常用程序编程规范、函数集 -头文件-Generic Type Definitions

#include "Hardware_Profile.h"  //处理器"硬件配置文件" -Hardware specific definitions for Processor


#include "CD405x_Multiplexer.h"   //"CD405x_Multiplexer多路选择模拟开关"  -驱动程序(外部资源)-头文件



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////





/****************************************************************************
*函数名-Function:	void CD405x_SelectChannel(unsigned channel)
*描述- Description:	选择指定通道("CD405x_Multiplexer多路选择模拟开关" )
*输入参数-Input:	channel : 要选择的通道
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void CD405x_SelectChannel(unsigned channel)
{
 	//mOpen_CD405x_INH; //配置引脚为"输出",并"使能"CD405x 模块("低"电平有效)

	switch(channel)
	{
		case CD405x_Humidity: //CD405x切到"Humidity  湿度"
			mConfig_CD405x_A(0);  //A  =  0 //IN1
			mConfig_CD405x_B(0);  //B  =  0  //IN2
			break;

		case CD405x_Step_Motor:  //CD405x切到"Step_Motor 步进电机"
			mConfig_CD405x_A(0);  //A  =  0 //IN1
			mConfig_CD405x_B(1);  //B  =  0  //IN2
			break;
			
		case CD405x_DC_Motor:  //CD405x切到"DC_Motor 直流电机"
			mConfig_CD405x_A(1);  //A  =  0 //IN1
			mConfig_CD405x_B(0);  //B  =  0  //IN2
			break;
			
		default: break;

	}
}

