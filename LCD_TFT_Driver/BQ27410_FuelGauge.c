/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 BQ27410_FuelGauge.c
* 附属文件-Dependencies:  	 BQ27410_FuelGauge.h; Hardware_Profile.h; Generic.h; I2C.h; System.h; MyProject_Set_LCD_TFT.h;LCD_Segment.h; LCD_TFT_ILI9325.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■"BQ27410_FuelGauge 锂电池电量监测计"-驱动程序(外部资源)
	01)I2C  可连接系统微处理器端, 具有直接电池连接功能的系统电量监测计
	02) 可提供剩余电池容量(mAh)、充电状态(%)、电池电压(mV) 等信息。
	03) 适用于1-Series LiCoO2 电池应用的电池电量监测计
	04)基于获专利Impedance Track? 技术的易配置电池电量监测
	05)	集成型LDO 使器件能直接通过电池组供,可配合嵌入式或可拆卸电池组工作
	06)可根据电池老化、电池自放电以及温度／速率的低效率进行自动调整
	07)微处理器外设提供：
		– 准确的电池电量监测
		– 支持电池温度报告的内部温度传感器
		– 可配置充电状态(SOC) 中断级   
	08)应用
		– 智能电话
		– PDA
		– 数码相机与数码摄像机
		– 手持终端设备
		– MP3 或多媒体播放器

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 注意事项-Attention : 	
	▲01)
 	▲02) 	▲03)	▲04)    ▲05)    ▲06)     
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
* 修改记录-Change History:   
	作者   时间        版本  内容描述
	Author 	 Date		   Rev      Comment
	-------------------------------------------------------------------------------
	BlueS	2013-09-25	  1.0	   
			xxxx-xx-xx	  x.x	   
			xxxx-xx-xx	  x.x				
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
* 公司-Company: 			CS-EMLAB  Co. , Ltd.
* 软件许可协议-Software License Agreement:
	Copyright (C) 2012-2020 	CS-EMLAB  Co. , Ltd.	All rights reserved.	

*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/


#include "Generic.h"	//常用程序编程规范、函数集 -头文件-Generic Type Definitions

#include "Hardware_Profile.h"  //处理器"硬件配置文件" -Hardware specific definitions for Processor


#include "BQ27410_FuelGauge.h"   //"BQ27410_FuelGauge 锂电池电量监测计"-驱动程序(外部资源)-头文件


#include "I2C.h"   //"I2C" -驱动程序-头文件(处理器内部资源) 

#include "System.h"	 //"系统" 常用功能函数集-头文件
	//具体项目: LCD_TFT液晶显示部份(包括所有的液晶内容) -头文件
#include "MyProject_Set_LCD_TFT.h"  

#include "LCD_Segment.h" // "段式LCD_Segment"  -驱动程序(外部资源)-头文件

#include "LCD_TFT_ILI9325.h"  // "彩屏LCD_TFT_ILI9325" -驱动程序(外部资源) -头文件



	#include "LED_Segment.h" //"动态数码管LED_Segment" -驱动程序(外部资源)-头文件
	#include "TM1638.h"  // "TM1638 数码管驱动器" -驱动程序(外部资源) -头文件
	#include "MatrixKey.h"   //"矩阵按键" -驱动程序(外部资源)-头文件



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
u16 BQ27410_Charge = 0;  //BQ27410 采样的锂电池电量值
u8 BQ27410_ChargeKind = 0;  //BQ27410 采样的锂电池电量值的级别


////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////


/****************************************************************************
*函数名-Function:	void Initial_BQ27410_FuelGauge(void)
*描述- Description:		初始化BQ27410电量计:  IIC_B配置,引脚切换到IIC引脚
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Initial_BQ27410_FuelGauge(void)  //初始化BQ27410电量计:  IIC_B配置,引脚切换到IIC引脚
{
	mSPI_All_Disable;//驱动LCD_segment和IIC(TMP006)时，要禁用所有用到SPI_B的模块



////////////////////////////////////////////////////////////////////////////
//==**配置"B模块"多路复用器TS3A5017: 选择IN2 、IN1**=========//
		//IN2=0; IN1=0; 对应I2C_B 引脚(I2C_SCK_B; I2C_SDA_B)
	mConfig_TS3A5017_B_IN2(0);  //IN2 =0
	mConfig_TS3A5017_B_IN1(0);  //IN1 =0	 //选择s1

////////////////////////////////////////////////////////////////////////////
//==**配置IIC_B**============================================//
	I2C_B_Initial(ADDR_SLAVE_BQ27410);  //I2C_B 内部资源初始化

}


/****************************************************************************
*函数名-Function:	void Sample_BQ27410_FuelGauge(void)
*描述- Description: 	BQ27410 采样锂电池的电量
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)		▲02)	 ▲03)	  ▲04)  
*****************************************************************************/
void Sample_BQ27410_FuelGauge(void)  //BQ27410 采样锂电池的电量
{
	u16 temp = 0;  

////////////////////////////////////////////////////////////////////////////
//==**配置一下BQ27410 电量计**==============================//
	Initial_BQ27410_FuelGauge();  //初始化BQ27410电量计:  IIC_B配置,引脚切换到IIC引脚
		//向BQ27410的0x00地址,写入一个字(0x000C)
	Write_Word_IIC_B(0x00,0x0C,0x00); //通过IIC_B 向从机的某个寄存器写一个字
	
	Initial_BQ27410_FuelGauge();  //初始化BQ27410电量计:  IIC_B配置,引脚切换到IIC引脚
	temp = Read_Word_IIC_B(ADDR_Charge_BQ27410);//读出BQ27410采样的 电量值,并转换为"实际 电量值"

	
	BQ27410_Charge = (temp << 8) & 0xFF00;
	BQ27410_Charge +=(temp >> 8) & 0x00FF;

		//900mAh的锂电池充满电后，BQ27410的采样值为1240，测得电压4.15V
		//900mAh的锂电池放完电后，BQ27410的采样值为0000，测得电压3.44V
		//这里取1230为对应的最大值900mAh,故之间的倍数n=1230/900=1.366667
	BQ27410_Charge = (unsigned int)(BQ27410_Charge / 1.366667);  //转换为0--900mAH 范围的电量
	if(BQ27410_Charge >= 900)  BQ27410_Charge = 900;

///////////////////////////////////////////////////
		//电量=  0  //没电//电量级别
	if(BQ27410_Charge == 0) BQ27410_ChargeKind = CHARGE_0_BQ27410; 
		//0<电量<= 9%  //报警//电量级别
	if((BQ27410_Charge > 0)&&(BQ27410_Charge < 90)) BQ27410_ChargeKind = CHARGE_0_9_BQ27410;    
		//10%<=电量<= 33%  //电量级别
	if((BQ27410_Charge >= 90)&&(BQ27410_Charge < 306)) BQ27410_ChargeKind = CHARGE_10_33_BQ27410;   
		//34%<=电量<= 66%  //电量级别
	if((BQ27410_Charge >= 306)&&(BQ27410_Charge < 603)) BQ27410_ChargeKind = CHARGE_34_66_BQ27410;  
		//67%<=电量<= 99%  //电量级别
	if((BQ27410_Charge >= 603)&&(BQ27410_Charge < 900)) BQ27410_ChargeKind = CHARGE_67_99_BQ27410;  
		//电量= 100%  //充满电//电量级别
	if(BQ27410_Charge >= 900) BQ27410_ChargeKind = CHARGE_100_BQ27410; 
	
}
	





/****************************************************************************
*函数名-Function:	void Deal_BQ27410_FuelGauge(void)
*描述- Description: 	处理BQ27410 电量计
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)		▲02)	 ▲03)	  ▲04)  
*****************************************************************************/
void Deal_BQ27410_FuelGauge(void)  //处理BQ27410 电量计
{
////////////////////////////////////////////////////////////////////////////
//==**系统每1s 读取"实时BQ27410采样的 电量值"**====================//
	if(F_1s_BQ27410)	//系统每500ms 读取"实时BQ27410采样的 电量值"
	{
		F_1s_BQ27410 = 0;

Sample_BQ27410_FuelGauge();  //BQ27410 采样锂电池的电量

//Display_BQ27410_LED_Segment();  //数码管LCD上显示BQ27410 采样得到的电量值
		F_Update_Power = YES; //刷新:"锂电池的实时电量"  (为1时)

	//_delay_ms(100);
	}
}
	

/****************************************************************************
*函数名-Function:	void Display_BQ27410_LCD_Segment(void)
*描述- Description: 	在段式LCD上显示BQ27410 采样得到的电量值
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)		▲02)	 ▲03)	  ▲04)  
*****************************************************************************/
void Display_BQ27410_LCD_Segment(void)  //在段式LCD上显示BQ27410 采样得到的电量值
{
	u8 s1,s2,s3;
	u8 chargeKind = 0;
	u8 flag02 = DISP_OFF_LcdSeg; //显示"暗码"
	u8 flag01 = DISP_OFF_LcdSeg; //显示"暗码"


	flag02 = (unsigned char)((BQ27410_Charge/9)/10);  //显示当前电量的占比(十位)
	flag01 = (unsigned char)((BQ27410_Charge/9)%10);  //显示当前电量的占比(个位)



	s3 = (unsigned char)(BQ27410_Charge/100);
	s2 = (unsigned char)((BQ27410_Charge % 100)/10);
	s1 = (unsigned char)(BQ27410_Charge % 10);

	if((s3 == 0)&&(s2 == 0)) s2 = DISP_OFF_LcdSeg;
	if(s3 == 0) s3 = DISP_OFF_LcdSeg; //显示"暗码"
	

	switch(BQ27410_ChargeKind) 
	{
		case CHARGE_0_BQ27410:	//电量=  0  //没电//电量级别
			chargeKind = 0;    //"0"表示不显示电池符号
			flag02 = DISP_0_LcdSeg;  //显示"0" :表示电池已没电
			flag01 = DISP_0_LcdSeg;  //显示"0" :表示电池已没电

			s3 = DISP_0_LcdSeg; //显示"0"
			s2 = DISP_0_LcdSeg; //显示"0"
			s1 = DISP_0_LcdSeg; //显示"0"
			break;	
			
		case CHARGE_0_9_BQ27410: //0<电量<= 9%  //报警//电量级别
			if(F_250ms_Turn)	//快没电,报警闪烁"1 格电+电池框"
			{
				chargeKind = 4;    //"4"表示显示"1 格电+电池框"
				flag01 = (unsigned char)((BQ27410_Charge/9)%10);  //显示当前电量的占比(个位)
			}
			else
			{
				chargeKind = 0;    //"0"表示不显示电池符号
				flag01 = DISP_OFF_LcdSeg;  //显示"暗码"
			}
			flag02 = DISP_OFF_LcdSeg;  //显示"暗码"
			break;	
			
		case CHARGE_10_33_BQ27410: //10%<=电量<= 33%  //电量级别
			chargeKind = 4;    //"4"表示显示"1 格电+电池框"
			break;	
			
		case CHARGE_34_66_BQ27410: //34%<=电量<= 66%  //电量级别
			chargeKind = 5;    //"5"表示显示"2 格电+电池框"
			break;	
			
		case CHARGE_67_99_BQ27410: //67%<=电量<= 99%  //电量级别
			chargeKind = 6;    //"6"表示显示"3 格电+电池框"
			break;	
			
		case CHARGE_100_BQ27410: //电量= 100%  //充满电//电量级别
			chargeKind = 6;    //"6"表示显示"3 格电+电池框"
			flag02 = DISP_F_LcdSeg;  //显示"F" :表示电池满电
			flag01 = DISP_F_LcdSeg;  //显示"F" :表示电池满电
			break;	

		default:	break;
	}

	Disp_LCD_Segment(chargeKind,flag02,flag01,DISP_OFF_LcdSeg,s3,s2,s1);
	mOpen_LCD_SEG_BackLight; //配置引脚为"输出",并"打开"LCD_Segment 背光
	
}
	


/****************************************************************************
*函数名-Function:	void Disp_BQ27410_FuelGauge(void)
*描述- Description:		在LCD_TFT上，显示"锂电池":状态+电量
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_BQ27410_FuelGauge(void)//在LCD_TFT上，显示"锂电池":状态+电量
{	
	
switch(BQ27410_ChargeKind) 
{
	case CHARGE_0_BQ27410:	//电量=  0  //没电//电量级别
			//"电量外框"
		LCD_TFT_DrawRectangle(M_15Line,M_37Column,M_15Line+13,M_40Column+2,RED); 
		LCD_TFT_DrawRectangle(M_15Line+4,M_40Column+2,M_15Line+9,M_40Column+5,RED); 
			//"电量值"--左边第01电量方块
		LCD_TFT_FillRectangle(M_15Line+2,M_37Column+2,M_15Line+11,M_37Column+7,Monitor_Back);
			//"电量值"--左边第02电量方块
		LCD_TFT_FillRectangle(M_15Line+2,M_38Column+2,M_15Line+11,M_38Column+7,Monitor_Back);
			//"电量值"--左边第03电量方块
		LCD_TFT_FillRectangle(M_15Line+2,M_39Column+2,M_15Line+11,M_39Column+7,Monitor_Back);
		break;	
		
	case CHARGE_0_9_BQ27410: //0<电量<= 9%  //报警//电量级别
			//"电量外框"
		LCD_TFT_DrawRectangle(M_15Line,M_37Column,M_15Line+13,M_40Column+2,Monitor_Point); 
		LCD_TFT_DrawRectangle(M_15Line+4,M_40Column+2,M_15Line+9,M_40Column+5,Monitor_Point); 
			//"电量值"--左边第01电量方块
		LCD_TFT_FillRectangle(M_15Line+2,M_37Column+2,M_15Line+11,M_37Column+7,RED);
			//"电量值"--左边第02电量方块
		LCD_TFT_FillRectangle(M_15Line+2,M_38Column+2,M_15Line+11,M_38Column+7,Monitor_Back);
			//"电量值"--左边第03电量方块
		LCD_TFT_FillRectangle(M_15Line+2,M_39Column+2,M_15Line+11,M_39Column+7,Monitor_Back);
		break;	
		
	case CHARGE_10_33_BQ27410: //10%<=电量<= 33%  //电量级别
			//"电量外框"
		LCD_TFT_DrawRectangle(M_15Line,M_37Column,M_15Line+13,M_40Column+2,Monitor_Point); 
		LCD_TFT_DrawRectangle(M_15Line+4,M_40Column+2,M_15Line+9,M_40Column+5,Monitor_Point); 
			//"电量值"--左边第01电量方块
		LCD_TFT_FillRectangle(M_15Line+2,M_37Column+2,M_15Line+11,M_37Column+7,Monitor_Point);
			//"电量值"--左边第02电量方块
		LCD_TFT_FillRectangle(M_15Line+2,M_38Column+2,M_15Line+11,M_38Column+7,Monitor_Back);
			//"电量值"--左边第03电量方块
		LCD_TFT_FillRectangle(M_15Line+2,M_39Column+2,M_15Line+11,M_39Column+7,Monitor_Back);
		break;	
		
	case CHARGE_34_66_BQ27410: //34%<=电量<= 66%  //电量级别
			//"电量外框"
		LCD_TFT_DrawRectangle(M_15Line,M_37Column,M_15Line+13,M_40Column+2,Monitor_Point); 
		LCD_TFT_DrawRectangle(M_15Line+4,M_40Column+2,M_15Line+9,M_40Column+5,Monitor_Point); 
			//"电量值"--左边第01电量方块
		LCD_TFT_FillRectangle(M_15Line+2,M_37Column+2,M_15Line+11,M_37Column+7,Monitor_Point);
			//"电量值"--左边第02电量方块
		LCD_TFT_FillRectangle(M_15Line+2,M_38Column+2,M_15Line+11,M_38Column+7,Monitor_Point);
			//"电量值"--左边第03电量方块
		LCD_TFT_FillRectangle(M_15Line+2,M_39Column+2,M_15Line+11,M_39Column+7,Monitor_Back);

		break;	
		
	case CHARGE_67_99_BQ27410: //67%<=电量<= 99%  //电量级别
			//"电量外框"
		LCD_TFT_DrawRectangle(M_15Line,M_37Column,M_15Line+13,M_40Column+2,Monitor_Point); 
		LCD_TFT_DrawRectangle(M_15Line+4,M_40Column+2,M_15Line+9,M_40Column+5,Monitor_Point); 
			//"电量值"--左边第01电量方块
		LCD_TFT_FillRectangle(M_15Line+2,M_37Column+2,M_15Line+11,M_37Column+7,Monitor_Point);
			//"电量值"--左边第02电量方块
		LCD_TFT_FillRectangle(M_15Line+2,M_38Column+2,M_15Line+11,M_38Column+7,Monitor_Point);
			//"电量值"--左边第03电量方块
		LCD_TFT_FillRectangle(M_15Line+2,M_39Column+2,M_15Line+11,M_39Column+7,Monitor_Point);
		break;	
		
	case CHARGE_100_BQ27410: //电量= 100%  //充满电//电量级别
			//"电量外框"
		LCD_TFT_DrawRectangle(M_15Line,M_37Column,M_15Line+13,M_40Column+2,Fixed_Point); 
		LCD_TFT_DrawRectangle(M_15Line+4,M_40Column+2,M_15Line+9,M_40Column+5,Fixed_Point); 
			//"电量值"--左边第01电量方块
		LCD_TFT_FillRectangle(M_15Line+2,M_37Column+2,M_15Line+11,M_37Column+7,Fixed_Point);
			//"电量值"--左边第02电量方块
		LCD_TFT_FillRectangle(M_15Line+2,M_38Column+2,M_15Line+11,M_38Column+7,Fixed_Point);
			//"电量值"--左边第03电量方块
		LCD_TFT_FillRectangle(M_15Line+2,M_39Column+2,M_15Line+11,M_39Column+7,Fixed_Point);

		break;	

	default:	break;
}

	
}


/****************************************************************************
*函数名-Function:	void Display_BQ27410_LED_Segment(void)
*描述- Description: 	在数码管LED上显示BQ27410 采样得到的电量值
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)		▲02)	 ▲03)	  ▲04)  
*****************************************************************************/
void Display_BQ27410_LED_Segment(void)  //数码管LCD上显示BQ27410 采样得到的电量值
{
	u8 s1,s2,s3;
	u8 chargeKind = 0;
	u8 flag02 = DISP_OFF_LedSeg; //显示"暗码"
	u8 flag01 = DISP_OFF_LedSeg; //显示"暗码"


	flag02 = (unsigned char)((BQ27410_Charge/9)/10);  //显示当前电量的占比(十位)
	flag01 = (unsigned char)((BQ27410_Charge/9)%10);  //显示当前电量的占比(个位)



	s3 = (unsigned char)(BQ27410_Charge/100);
	s2 = (unsigned char)((BQ27410_Charge % 100)/10);
	s1 = (unsigned char)(BQ27410_Charge % 10);

	if((s3 == 0)&&(s2 == 0)) s2 = DISP_OFF_LcdSeg;
	if(s3 == 0) s3 = DISP_OFF_LcdSeg; //显示"暗码"
	

	switch(BQ27410_ChargeKind) 
	{
		case CHARGE_0_BQ27410:	//电量=  0  //没电//电量级别
			chargeKind = 0;   
			flag02 = DISP_0_LcdSeg;  //显示"0" :表示电池已没电
			flag01 = DISP_0_LcdSeg;  //显示"0" :表示电池已没电

			s3 = DISP_0_LcdSeg; //显示"0"
			s2 = DISP_0_LcdSeg; //显示"0"
			s1 = DISP_0_LcdSeg; //显示"0"
			break;	
			
		case CHARGE_0_9_BQ27410: //0<电量<= 9%  //报警//电量级别
			chargeKind = 1;   
			break;	
			
		case CHARGE_10_33_BQ27410: //10%<=电量<= 33%  //电量级别
			chargeKind = 2;    
			break;	
			
		case CHARGE_34_66_BQ27410: //34%<=电量<= 66%  //电量级别
			chargeKind = 3;   
			break;	
			
		case CHARGE_67_99_BQ27410: //67%<=电量<= 99%  //电量级别
			chargeKind = 4;    
			break;	
			
		case CHARGE_100_BQ27410: //电量= 100%  //充满电//电量级别
			chargeKind = 5;    
			flag02 = DISP_F_LedSeg;  //显示"F" :表示电池满电
			flag01 = DISP_F_LedSeg;  //显示"F" :表示电池满电
			break;	

		default:	break;
	}


	Disp_LED_Segment(0,0,flag02,flag01,DISP_OFF_LedSeg,chargeKind,DISP_OFF_LedSeg,s3,s2,s1);

	
}
	

