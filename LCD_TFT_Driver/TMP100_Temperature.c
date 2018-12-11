/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 TMP100_Temperature.c
* 附属文件-Dependencies:  	 TMP100_Temperature.h;  I2C.h;
								Hardware_Profile.h; Generic.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■ "TMP100_Temperature 温度传感器" -驱动程序(外部资源)
	01)TMP100(具有 I2C 串行接口的数字温度传感器)Digital Temperature Sensor with I2C Serial Interface
	02)TMP100 是德州仪器公司的一款超低功耗数字温度传感器芯片，可以采用SMbus 或者I2C 总线与该芯片通信。
	03) 采用指针的方式访问寄存器。
	04)  工作电压范围：2.7V~5.5V 
	05)超低功耗：45μA  （待机时0.1μA） 
	06)接口方式：I2C二线串行接口 
	07)可编程分辨率：9-Bits  到  12-Bits 
	08)操作频率：  100 KHz /400KHz/3.4MHz 
	09)精度：测量温度在-25℃~85℃时，为±2℃在-55℃~125℃时，为±3℃ 
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


#include "I2C.h"   //"I2C" -驱动程序-头文件(处理器内部资源) 

#include "TMP100_Temperature.h"   //"TMP100_Temperature 温度传感器" -驱动程序(外部资源)-头文件



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
float TMP100_Temperature = 0;  //TMP100采样的温度值,转换后的"实际温度值"


////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////
const float Tmp100_Table[12]={128,64,32,16,8,4,2,1,0.5,0.25,0.125,0.0625};


/****************************************************************************
*函数名-Function:	void Initial_TMP100_Temperature(void)
*描述- Description:		初始化TMP100:  IIC_B配置,引脚切换到IIC引脚("TMP100_Temperature 温度传感器")
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Initial_TMP100_Temperature(void)  //初始化TMP100:  IIC_B配置,引脚切换到IIC引脚(TMP100_Temperature 温度传感器")
{
////////////////////////////////////////////////////////////////////////////
//==**配置多路复用器TS3A5017: 选择IN2 、IN1**==============//
		//IN2=1; IN1=1; 对应I2C_B 引脚(I2C_SCK_B; I2C_SDA_B)
	mConfig_TS3A5017_B_IN2(1);  //IN2 = 1
	mConfig_TS3A5017_B_IN1(1);  //IN1 = 1	 //s4

////////////////////////////////////////////////////////////////////////////
//==**配置IIC_B**============================================//
	I2C_B_Initial(ADDR_SLAVE_TMP100);  //I2C_B 内部资源初始化

}




/****************************************************************************
*函数名-Function:	float Tmp100_Convert_Temperature(unsigned int data)
*描述- Description:		将TMP100温度值转换为"实际温度值"
*输入参数-Input:	data
*输出参数-output:	temperature
*注意事项-Note：	
	▲01)注意"温度有可能为负值"    
	▲02)    	▲03)    ▲04)  
*****************************************************************************/
float Tmp100_Convert_Temperature(unsigned int data)  //将TMP100温度值转换为"实际温度值"
{
	float temperature = 0;
	unsigned char negative = 0;  //为1，表示温度为负数
	unsigned char i = 0;

	if(data & 0x8000) //温度为负值
	{
		data ^= 0xFFFF;  //求补码的绝对值:取反加1
		data = data +1;
		negative = 1;
	}
	else negative = 0;
  
	for(i = 0; i < 12; i++, data <<= 1)
	{
		if(data & 0x8000) temperature += Tmp100_Table[i];
	}
	
	if(negative == 1) temperature = (-1)*temperature;
	
	return (temperature);
}

/****************************************************************************
*函数名-Function:	void Deal_TMP100_Temperature(void)
*描述- Description: 	处理TMP100 温度,得到最后的"实际温度值"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)		▲02)	 ▲03)	  ▲04)  
*****************************************************************************/
void Deal_TMP100_Temperature(void)  //处理TMP100温度,得到最后的"实际温度值"
{

////////////////////////////////////////////////////////////////////////////
//==**初始化TMP100**=========================================//
	Initial_TMP100_Temperature();  //初始化TMP100:  IIC_B配置,引脚切换到IIC引脚("TMP100_Temperature  温度传感器")


////////////////////////////////////////////////////////////////////////////
//==**读出TMP100采样的温度值,并转换为"实际温度值"**====//
			//0x00为TMP100温度寄存器地址 //通过IIC_B 读数据(一个字)
	TMP100_Temperature = Tmp100_Convert_Temperature(Read_Word_IIC_B(ADDR_TMP_TMP100));
}
	


