/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 Touch_Pad.c
* 附属文件-Dependencies:  	 Touch_Pad.h; CTS_HAL.h; CTS_Layer.h; msp430f6638.h;
								Hardware_Profile.h; Generic.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■"Touch_Pads 电容按键" -驱动程序(外部资源)
	01)按键即是一个焊盘，与地构成一个感应电容，在周围环境
不变的情况下电容固定为微小值，具有固定的充放电时间，而
当有一个导体向电极靠近时，会形成耦合电容，这样就会改变
固有的充放电时间，而手指就是这样的导体。通过测量充放电
时间的改变即可检测按键是否有按下。
	02)利用感应电容,电阻构成的 RC 回路，检测充放电时间变化量。
	03)操作原理：通过“开放式”电容器结构，即可构建单触式
感应电容器，以便通过其他导体（手指）对电场进行干扰。其
中，按键板与其周围的接地板之间将形成电容器。当手指靠近
电容器的上方区域，它会干扰电场，从而引起电容发生相应变化。
	04)  	05)    06)	
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


	//Touch Pads 库
#include"CTS\structure.h"
#include"CTS\CTS_Layer.h"
#include"CTS\CTS_HAL.h"

#include "Touch_Pad.h"   //"Touch_Pad 电容按键" -驱动程序(外部资源)-头文件



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned int G_SliderPosition = 0;


////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////


/****************************************************************************
*函数名-Function:	void Initial_Touch_Pad(void)
*描述- Description:		初始化设置:  "Touch_Pads 电容按键" 
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Initial_Touch_Pad(void)  //初始化设置: "Touch_Pads 电容按键" 
{
//configure CapTouchs ports
P3OUT &=~0x01;
P3DIR  &= ~0X01;  //P3.0为

P6OUT &= ~0X1F;
P6DIR &= ~0X1F;  //P6.0, P6.1, P6.2, P6.3, P6.4  //输入

/*	P3OUT &=~0x7e;
	P3DIR |= 0x7e;
	P6OUT = 0X00;
	P6DIR = 0X00;
*/

	TI_CAPT_Init_Baseline(&slider);				
	TI_CAPT_Update_Baseline(&slider,5);

}



/****************************************************************************
*函数名-Function:	void Deal_Touch_Pad(void)
*描述- Description:		处理: "Touch_Pads 电容按键"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    	▲02)    	▲03)        ▲04)  
*****************************************************************************/
void Deal_Touch_Pad(void)  //处理: "Touch_Pads 电容按键"
{
	G_SliderPosition = TI_CAPT_Slider(&slider);	
	

if(G_SliderPosition<10) G_SliderPosition += 19;
	G_SliderPosition = (G_SliderPosition + 17)/18;  //V2.0

//G_SliderPosition = (G_SliderPosition + 18)/20;  //V3.0


/************
if(G_SliderPosition<10) G_SliderPosition += 19;
	G_SliderPosition = (G_SliderPosition + 17)/18;  //V2.0


switch (G_SliderPosition)
{
	case 0: 
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		break;
		
	case 1: 
		Disp_LED_Segment(0,0,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg);

		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 21]= 'P';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 22]= 'a';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 23]= 'd';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 24]= '1';
		F_Refresh_TestLine05 = YES;
		break;

	case 2: 
		Disp_LED_Segment(0,0,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg);

		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 16]= 'P';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 17]= 'a';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 18]= 'd';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 19]= '2';
		F_Refresh_TestLine05 = YES;
		break;

	case 3: 
		Disp_LED_Segment(0,0,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg);

		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 11]= 'P';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 12]= 'a';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 13]= 'd';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 14]= '3';
		F_Refresh_TestLine05 = YES;
		break;
	
	case 4: 
		Disp_LED_Segment(0,0,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg);

		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 6]= 'P';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 7]= 'a';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 8]= 'd';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 9]= '4';
		F_Refresh_TestLine05 = YES;
		break;
	
	case 5: 
		Disp_LED_Segment(0,0,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg);

		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 1]= 'P';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 2]= 'a';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 3]= 'd';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 4]= '5';
		F_Refresh_TestLine05 = YES;
		break;
	
	case (255 / 17):
		break;
}

*************/
}

