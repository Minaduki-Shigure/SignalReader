/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 Step_Motor.c
* 附属文件-Dependencies:  	 Step_Motor.h; CD405x_Multiplexer.h; Timer.h; ADC.h;
                                                        Hardware_Profile.h; Generic.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■ "Step_Motor 步进电机"-驱动程序(外部资源)
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


#include "Generic.h"	//常用程序编程规范、函数集 -头文件-Generic Type Definitions

#include "Hardware_Profile.h"  //处理器"硬件配置文件" -Hardware specific definitions for Processor


#include "ADC.h"   //"ADC"模数转换模块 -驱动程序-头文件(处理器内部资源) 
#include "Timer.h"     //"定时器" -驱动程序 -头文件(处理器内部资源)



#include "CD405x_Multiplexer.h"   //"CD405x_Multiplexer多路选择模拟开关"  -驱动程序(外部资源)-头文件

#include "Step_Motor.h"   //"Step_Motor 步进电机" -驱动程序(外部资源)-头文件



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
union FLAGBIT Step_Motor_FlagBits; //"Step_Motor 步进电机"相关标志位变量


unsigned int G_Step_Speed = 0;   //"Step_Motor 步进电机"转速

unsigned char G_Step_WorkState = 0; //运行状态-"Step_Motor 步进电机"

////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////


/****************************************************************************
*函数名-Function:	void Enable_Step_Motor(void)
*描述- Description:		使能-"Step_Motor 步进电机"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：
	▲01) 使能-"Step_Motor 步进电机"。"禁止"-"DC_Motor 直流电机"
	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Enable_Step_Motor(void) //使能-"Step_Motor 步进电机"
{
////////////////////////////////////////////////////////////////////////////
//==**"使能""Step_Motor 步进电机"(对应DRV8833的nSleep引脚)**===//
	mOpen_Step_Motor_nSleep;//配置引脚为"输出",并"使能"器件("高"电平有效)


////////////////////////////////////////////////////////////////////////////
//==**"禁止"-"DC_Motor 直流电机"(对应DRV8833的nSleep引脚)**===//
	mClose_DC_Motor_nSleep; //配置引脚为"输出",并"禁止"器件(低：进入低功耗)
}


/****************************************************************************
*函数名-Function:	void Disable_Step_Motor(void)
*描述- Description:		禁止-"Step_Motor 步进电机"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：
	▲01) "停止"-"Step_Motor 步进电机"
	▲02) "禁止"-"Step_Motor 步进电机"
	▲03)"DRV8833 双路_H_桥接电机驱动器"
1) 能够驱动两个直流(DC)电机或一个双极性步进电机
2) 低MOSFET 导通电阻,宽电源电压范围：2.7V 至10.8V
3) 每个H 桥的输出电流为1.5-ARMS、2APP（在VM=5V 和25℃条件下）
	▲04)	
*****************************************************************************/
void Disable_Step_Motor(void)  //禁止-"Step_Motor 步进电机"
{
	G_Step_WorkState = STATE_Idle_Step_Motor;
////////////////////////////////////////////////////////////////////////////
//==**"停止"" 步进电机"(对应DRV8833的AIN1、BIN1引脚)**=====//
//Stop_DC_Motor();  //停转-"DC_Motor 直流电机"
//Stop_PWM_DC_Motor();  //停止PWM输出-"DC_Motor 直流电机"

	mLow_Step_Motor_AIN1;//配置引脚为"输出",并输出"低"电平
	mLow_Step_Motor_AIN2;//配置引脚为"输出",并输出"低"电平
	mLow_Step_Motor_BIN1;//配置引脚为"输出",并输出"低"电平
	mLow_Step_Motor_BIN2;//配置引脚为"输出",并输出"低"电平


////////////////////////////////////////////////////////////////////////////
//==**"禁止"-"Step_Motor 步进电机"(对应DRV8833的nSleep引脚)**==//
	mClose_Step_Motor_nSleep; //配置引脚为"输出",并"禁止"器件(低：进入低功耗)
	
}




/****************************************************************************
*函数名-Function:	void Step_Motor_Initial(void)
*描述- Description:		初始化设置:  "Step_Motor 步进电机"
		1) CD405x切到 "Step_Motor 步进电机"
		2) 配置IO: 定时器A0初始化设置(使用CCR1, CCR3)
		3) 配置:  
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Step_Motor_Initial(void)  //初始化设置:  "Step_Motor 步进电机"
{
////////////////////////////////////////////////////////////////////////////
//==**CD405x切到 "Step_Motor 步进电机"**======================//
	CD405x_SelectChannel(CD405x_Step_Motor);  //CD405x切到"Step_Motor 步进电机"

////////////////////////////////////////////////////////////////////////////
//==**配置"DRV8833 双路_H_桥接电机驱动器" **=============//
	mSelect_Step_Motor_BIN1_IoPin;	//配置引脚为"IO"引脚
	mSelect_Step_Motor_BIN2_IoPin;	//配置引脚为"IO"引脚
	Disable_Step_Motor(); //禁止-"Step_Motor 步进电机"

////////////////////////////////////////////////////////////////////////////
//==**配置: 定时器A0初始化设置**==========================//
	Timer2_Initial_Step_Motor(); //定时器A2初始化设置("Step_Motor 步进电机")

	G_Step_Speed = 0;
}



/****************************************************************************
*函数名-Function:	void Sample_Step_Motor_Frequency(void)
*描述- Description:		采样"Step_Motor 步进电机"转速(1s内的脉冲次数)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：
	▲01) 在中断TIMER0_A1_ISR()调用
	▲02)    ▲03)    ▲04)  
************************************************
void Sample_Step_Motor_Frequency(void)
{

	G_Step_FrequencyCnt++;
	if(G_Step_FrequencyCnt >=4) G_Step_FrequencyCnt = 1;

	if(G_Step_FrequencyCnt == 2) 
	{
		G_Step_FrequencyStart = TA0CCR3;
	}
	else if(G_Step_FrequencyCnt == 3) 
	{
		G_Step_FrequencyEnd = TA0CCR3;

		if()

		
	////////////////////////////////////////////////////////////////////////////
	//==**配置:  " TA0CTL (Timer_A0控制寄存器)"**==================//
		
		TA0CTL &= ~(MC1 + MC0); //让Timer_A0处于停止模式
		TA0CCTL3 &= ~ CCIE;     //禁止CCR3 中断
		
		F_EnRead_Step_Motor = YES;
	}
		




	G_Step_SpeedCnt ++;  //累加频率计数器("Step_Motor 步进电机")
	
	if(F_1s_Frequency_Step_Motor)
	{
		F_1s_Frequency_Step_Motor = 0;

		G_Step_Speed = G_Step_SpeedCnt;  //采样1s内的频率脉冲次数
		
		G_Step_SpeedCnt = 0; //清频率计数器，重新采样
	}
}
*****************************/



/****************************************************************************
*函数名-Function:	void Stop_Step_Motor(void)
*描述- Description:		停转-"Step_Motor 步进电机"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01) 	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Stop_Step_Motor(void)  //停转-"Step_Motor 步进电机"
{
	Disable_Step_Motor(); //禁止-"Step_Motor 步进电机"
}


/****************************************************************************
*函数名-Function:	void Positive_Step_Motor(void)
*描述- Description:		正转-"Step_Motor 步进电机"(根据电位计电压进行调速)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01) 	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Positive_Step_Motor(void)  //正转-"Step_Motor 步进电机"(根据电位计电压进行调速)
{
	static char step = 0;

	unsigned int Set_Speed = 0; 

	Set_Speed = G_LastAdResult/10;
	Set_Speed = Set_Speed*100;   //例G_LastAdResult=3312时，Set_Speed=33100 

		//care==
	if(G_LastAdResult >= 80)
	{
		if(G_LastAdResult >= 3300)
		{
			Set_Speed = 33000;
		}
		TA2CCR0 = 36000 - Set_Speed;  //调速-"Step_Motor 步进电机"  

		//==**使能: "Step_Motor 步进电机"**=========================//
		Enable_Step_Motor();  //使能-"Step_Motor 步进电机"

	}
	else if(G_LastAdResult < 80)
	{
		TA2CCR0 = 50000;
		//==**使能: "Step_Motor 步进电机"**=========================//
		Enable_Step_Motor();  //使能-"Step_Motor 步进电机"

	}

//////////////////////////////////////////////////////////////////////////////
	switch(step)
	{
		case 0:
			mHigh_Step_Motor_AIN1; 
			mLow_Step_Motor_AIN2; 
			mHigh_Step_Motor_BIN1;
			mLow_Step_Motor_BIN2;
			break;
			
		case 1: 
			mLow_Step_Motor_AIN1;
			mHigh_Step_Motor_AIN2;
			mHigh_Step_Motor_BIN1;
			mLow_Step_Motor_BIN2;
			break;
			
		case 2:
			mLow_Step_Motor_AIN1; 
			mHigh_Step_Motor_AIN2;
			mLow_Step_Motor_BIN1;
			mHigh_Step_Motor_BIN2;
			break;
			
		case 3:
			mHigh_Step_Motor_AIN1;  
			mLow_Step_Motor_AIN2; 
			mLow_Step_Motor_BIN1;
			mHigh_Step_Motor_BIN2;
			break;
	}
	
	step --;
	if(step > 200) step = 3;
}





/****************************************************************************
*函数名-Function:	void Reverse_Step_Motor(void)
*描述- Description:		反转-"Step_Motor 步进电机"(根据电位计电压进行调速)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01) 	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Reverse_Step_Motor(void)  //反转-"Step_Motor 步进电机"(根据电位计电压进行调速)
{
	static char step = 0;
	
	unsigned int Set_Speed = 0; 

	Set_Speed = G_LastAdResult/10;
	Set_Speed = Set_Speed*100;   //例G_LastAdResult=3312时，Set_Speed=33000 
	
		//care
	if(G_LastAdResult >= 80)
	{
		if(G_LastAdResult >= 3300)
		{
			Set_Speed = 33000;
		}
		TA2CCR0 = 36000 - Set_Speed;  //调速-"Step_Motor 步进电机"	
	
		//==**使能: "Step_Motor 步进电机"**=========================//
		Enable_Step_Motor();  //使能-"Step_Motor 步进电机"
	
	}
	else if(G_LastAdResult < 80)
	{
		TA2CCR0 = 50000;
		//==**使能: "Step_Motor 步进电机"**=========================//
		Enable_Step_Motor();  //使能-"Step_Motor 步进电机"
	
	}


//////////////////////////////////////////////////////////////////////////////
	switch(step)
	{
		case 0:
			mHigh_Step_Motor_AIN1; 
			mLow_Step_Motor_AIN2; 
			mHigh_Step_Motor_BIN1;
			mLow_Step_Motor_BIN2;
			break;
			
		case 1: 
			mLow_Step_Motor_AIN1;
			mHigh_Step_Motor_AIN2;
			mHigh_Step_Motor_BIN1;
			mLow_Step_Motor_BIN2;
			break;
			
		case 2:
			mLow_Step_Motor_AIN1; 
			mHigh_Step_Motor_AIN2;
			mLow_Step_Motor_BIN1;
			mHigh_Step_Motor_BIN2;
			break;
			
		case 3:
			mHigh_Step_Motor_AIN1;  
			mLow_Step_Motor_AIN2; 
			mLow_Step_Motor_BIN1;
			mHigh_Step_Motor_BIN2;
			break;
	}
	
	step ++;
	if(step > 3) step = 0;	
}





/****************************************************************************
*函数名-Function:	void Deal_Step_Motor(void)
*描述- Description:		中断中处理步进电机(正反转,转速)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01) 中断中处理步进电机(正反转,转速)
	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Deal_Step_Motor(void)  //中断中处理步进电机(正反转,转速)
{
	if(G_Step_WorkState == STATE_Positive_Step_Motor) 
	{
		Positive_Step_Motor(); //正转-"Step_Motor 步进电机"(根据电位计电压进行调速)
	}
	else if(G_Step_WorkState == STATE_Reverse_Step_Motor) 
	{
		Reverse_Step_Motor(); //反转-"Step_Motor 步进电机"(根据电位计电压进行调速)
	}
}



/****************************************************************************
*函数名-Function:	void Deal_Step_Motor(void)
*描述- Description:		计算步进电转速
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01) 	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Deal_Speed_Step_Motor(void)  //计算步进电转速 
{
    unsigned long a=0;
    unsigned int b = 0;
	unsigned int Set_Speed = 0; 

	Set_Speed = G_LastAdResult/10;
	Set_Speed = Set_Speed*100;   //例G_LastAdResult=3312时，Set_Speed=33000 

	if((G_Step_WorkState == STATE_Positive_Step_Motor)||(G_Step_WorkState == STATE_Reverse_Step_Motor)) 
	{
		if(G_LastAdResult >= 80)
		{
			b = Set_Speed;
			if(G_LastAdResult >= 3300)
			{
				b = 33000;
			}
			
			a = 36000 - b;  //调速-"Step_Motor 步进电机"  3285=3200+85
				//时钟为32768Hz, 步进角18度
				//步进电机每走一步所需时间: a*(1/32768)
				//步进电机转一圈要用的时间: T=a*(1/32768) *(360/18)
				//步进电机转速=1/T=32768/(a*20)    转速为r/s,
			G_Step_Speed = (unsigned int)(3276800*60/(a*20));  //转速为r/min,放大了100倍
		}
		else if(G_LastAdResult < 80)
		{
			G_Step_Speed = 200;
		}

	}
	else G_Step_Speed = 0;
}



