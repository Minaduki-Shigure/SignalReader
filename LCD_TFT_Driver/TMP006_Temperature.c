/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 TMP006_Temperature.c
* 附属文件-Dependencies:  	 TMP006_Temperature.h;  I2C.h;
								Hardware_Profile.h; Generic.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■  "TMP006_Temperature 红外温度传感器" -驱动程序(外部资源)
	01)TMP006(红外热电堆传感器)(非接触式红外温度传感器)Infrared Thermopile Sensor in Chip-Scale Package
	02)TMP006 是德州仪器（TI）推出的业界首款单芯片无源红外线（IR）MEMS 温度传感器。
	03) 采用热电堆吸收被测物体所发射的红外能量，并利用热电堆电压
的对应变化来确定物体的温度，可在无需与物体接触的情况下测量物体的温度。
	04)低电源电流：240uA, 最低电源电压：2.2V
	05)温度范围：-40度～125度
	06)有两个地址引脚，允许连接"8"个器件
	07)SMBus兼容接口
	08)采用指针的方式访问寄存器。
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

#include "System.h"	 //"系统" 常用功能函数集-头文件

	//具体项目: LCD_TFT液晶显示部份(包括所有的液晶内容) -头文件
#include "MyProject_Set_LCD_TFT.h"  



#include "I2C.h"   //"I2C" -驱动程序-头文件(处理器内部资源) 

#include "TMP006_Temperature.h"   //"TMP006_Temperature 红外温度传感器"-驱动程序(外部资源)-头文件



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
float TMP006_Temperature = 0;  //TMP006采样的温度值,转换后的"实际温度值"


////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////
const float Tmp006_Table[13]={256,128,64,32,16,8,4,2,1,0.5,0.25,0.125,0.0625};


/****************************************************************************
*函数名-Function:	void Initial_TMP006_Temperature(void)
*描述- Description:		初始化TMP006:  IIC_B配置,引脚切换到IIC引脚("TMP006_Temperature 红外温度传感器")
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Initial_TMP006_Temperature(void)  //初始化TMP006:  IIC_B配置,引脚切换到IIC引脚("TMP006_Temperature 红外温度传感器")
{
	mSPI_All_Disable;//驱动LCD_segment和IIC(TMP006)时，要禁用所有用到SPI_B的模块

////////////////////////////////////////////////////////////////////////////
//==**配置"B模块"多路复用器TS3A5017: 选择IN2 、IN1**=========//
		//IN2=0; IN1=0; 对应I2C_B 引脚(I2C_SCK_B; I2C_SDA_B)
	mConfig_TS3A5017_B_IN2(0);  //IN2 =0
	mConfig_TS3A5017_B_IN1(0);  //IN1 =0	 //选择s1

////////////////////////////////////////////////////////////////////////////
//==**配置IIC_B**============================================//
	I2C_B_Initial(ADDR_SLAVE_TMP006);  //I2C_B 内部资源初始化

}




/****************************************************************************
*函数名-Function:	float Tmp006_Convert_Temperature(unsigned int data)
*描述- Description:		将TMP006温度值转换为"实际温度值"
*输入参数-Input:	data
*输出参数-output:	temperature
*注意事项-Note：	
	▲01)注意"温度有可能为负值"    
	▲02)    	▲03)    ▲04)  
*****************************************************************************/
float Tmp006_Convert_Temperature(unsigned int data)  //将TMP006温度值转换为"实际温度值"
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
  
	for(i = 0; i < 13; i++, data <<= 1)
	{
		if(data & 0x8000) temperature += Tmp006_Table[i];
	}
	
	if(negative == 1) temperature = (-1)*temperature;
	
	return (temperature);
}

/****************************************************************************
*函数名-Function:	void Deal_TMP006_Temperature(void)
*描述- Description: 	处理TMP006 温度,得到最后的"实际温度值"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)		▲02)	 ▲03)	  ▲04)  
*****************************************************************************/
void Deal_TMP006_Temperature(void)  //处理TMP006 温度,得到最后的"实际温度值"
{

////////////////////////////////////////////////////////////////////////////
//==**系统每500ms 读取"实时TMP温度值"**====================//
	if(F_500ms_Temperature)	//系统定时每100ms读一次"实时TMP温度值"
	{
		F_500ms_Temperature = 0;
	
	////////////////////////////////////////////////////////////////////////////
	//==**初始化TMP006**=========================================//
		Initial_TMP006_Temperature();  //初始化TMP006:	IIC_B配置,引脚切换到IIC引脚("TMP006_Temperature 红外温度传感器")

	////////////////////////////////////////////////////////////////////////////
	//==**读出TMP006采样的温度值,并转换为"实际温度值"**====//
				//0x01为TMP006温度寄存器地址 //通过IIC_B 读数据(一个字)
		TMP006_Temperature = Tmp006_Convert_Temperature(Read_Word_IIC_B(ADDR_TMP_TMP006));
	
		Disp_TMP006_Temperature();//在LCD_TFT上，显示"温度"

	}
}
	





