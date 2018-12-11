/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 MyProject.c
* 附属文件-Dependencies:  	 MyProject.h; System_HeadFile.h;	
* 文件描述-File Description:	 ( 源程序-Source File)
	■ 具体项目: 总功能程序
	01) 系统状态值分配
	02) EEPROM 地址分配
	03) Flash 地址分配   
	04) 具体项目的变量定义    
	05)    06)	
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



#include "System_HeadFile.h"   //引入: 系统全部头文件集(包含所有使用到的头文件)

#include "MyProject.h"	//具体项目: 总功能程序-头文件


////////////////////////////////////////////////////////////////////////////
//==**"具体项目" 全局变量定义**Global variables**============//
////////////////////////////////////////////////////////////////////////////

union FLAGBIT16 WorkFlagBits;   //工作时,用到的标志位


unsigned char G_KeyCnt = 0; // 用于按键选择菜单

unsigned char G_SOS_Cnt = 0; // 用于Led 实现SOS 功能




////////////////////////////////////////////////////////////////////////////
//==**"具体项目" 局部变量定义**Local variables**=============//
////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////
//==**"具体项目" 专用函数**============================//
////////////////////////////////////////////////////////////////////////////


/****************************************************************************
*函数名-Function:	void Detect_Key_WorkMenu(void)
*描述- Description:	按"Key1","Key2"上下选择"工作菜单"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01) 	▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Detect_Key_WorkMenu(void)
{
	if(Detect_Key_1())//"Key_1", 则"向上选择" 工作菜单
	{
		G_KeyCnt -- ;
		if(G_KeyCnt == 0) G_KeyCnt = 17;

		Select_WorkMenu();//选择"工作菜单"
	}

	if(Detect_Key_2())  //"Key_2", 则"向下选择" 工作菜单
	{
		G_KeyCnt ++ ;
		if(G_KeyCnt >= 18) G_KeyCnt = 1;
		
		Select_WorkMenu();//选择"工作菜单"
	}
}


/****************************************************************************
*函数名-Function:	void Select_WorkMenu(void)
*描述- Description:	选择"工作菜单"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01) 	▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Select_WorkMenu(void)
{
	switch(G_KeyCnt)
	{
		case 1: 
			Initial_MainState(MAIN_Basic_Settings); //装载//Main█Basic_Settings菜单选择(工作时)
			break;

		case 2: 
			Initial_MainState(MAIN_Basic_Check); //装载//Main█Basic_Check 菜单选择(工作时)
			break;

		case 3:
			Initial_MainState(MAIN_LCD_TFT_Test); //装载//Main█LCD_TFT_Test 菜单选择(工作时)
			break;
			
		case 4:
			Initial_MainState(MAIN_MatrixKey_Test); //装载//Main█MatrixKey_Test 菜单选择(工作时)
			break;

		case 5:
			Initial_MainState(MAIN_TouchPads_Test); //装载//Main█TouchPads_Test 菜单选择(工作时)
			break;	

		case 6:
			Initial_MainState(MAIN_INA21x_Current_Test); //装载//Main█INA21x_Current_Test 菜单选择(工作时)
			break;

		case 7:
			Initial_MainState(MAIN_TMP006_Temperature); //装载//Main█TMP006_Temperature 菜单选择(工作时)
			break;
			
		case 8:
			Initial_MainState(MAIN_Potentiometer_Test); //装载//Main█Potentiometer_Test 菜单选择(工作时)
			break;	

		case 9:
			Initial_MainState(MAIN_DC_Motor_Test); //装载//Main█DC_Motor_Test 菜单选择(工作时) 
			break;			

		case 10:
			Initial_MainState(MAIN_Step_Motor_Test); //装载//Main█Step_Motor_Test 菜单选择(工作时) 
			break;	

		case 11:
			Initial_MainState(MAIN_NTC_HR202_Test); //装载 //Main█NTC_HR202_Test(温湿度) 菜单选择(工作时)
			break;	
			
		case 12:
			Initial_MainState(MAIN_IrDA_UART); //装载//Main█IrDA_UART 菜单选择(工作时)
			break;		

		case 13:
			Initial_MainState(MAIN_RS232_UART); //装载//Main█RS232_UART 菜单选择(工作时)
			break;		

		case 14:
			Initial_MainState(MAIN_RS485_UART); //装载//Main█RS485_UART 菜单选择(工作时)
			break;		

		case 15:
			mSPI_All_Disable;  //关闭所有SPI模块的使能
			Initial_MainState(MAIN_CC1101_Test); //装载//Main█CC1101_Test 菜单选择(工作时)
			break;		

		case 16:
			mSPI_All_Disable;  //关闭所有SPI模块的使能
			Initial_MainState(MAIN_SD_Card_Test); //装载//Main█SD_Card_Test 菜单选择(工作时)
			break;		

		case 17:
			mSPI_All_Disable;  //关闭所有SPI模块的使能
			Initial_MainState(MAIN_MassStorage_Test); //装载//Main█MassStorage_Test 菜单选择(工作时)
			break;	

	///////////////////////////////////////////////////
		default : break;

	}

}



/****************************************************************************
*函数名-Function:	void SOS_Function(void)
*描述- Description:	Led_Diode(发光二极管) 实现SOS 求救功能
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01) 	▲02)    ▲03)    ▲04)  
*****************************************************************************/
void SOS_Function(void)
{
	if(!F_Timing)  // 人为定时结束后，自动进入工作状态(工作时)
	{
		
//SOS功能: 1短亮300ms→2短暗300ms→3短亮300ms→4短暗300ms→5短亮300ms
//    →6长暗1.8s→7长亮900ms→8短暗300ms→9长亮900ms→10短暗300m
//→11长亮900ms→12长暗1.8s   （高电平为"亮",	低电平为"暗"）

		switch(G_SOS_Cnt) 
		{
	case 1:	 // 1短亮300ms
		mOpen_LED_YELLOW;  //配置引脚为"输出",并"点亮"LED_YELLOW 
		mOpen_LED_GREEN;  //配置引脚为"输出",并"点亮"LED_GREEN
		mOpen_LED_RED;  //配置引脚为"输出",并"点亮"LED_RED
		Open_Timing_Task(300);//打开系统定时，定时给定的时间值(中断内)
		break;	

	case 2:  //2短暗300ms
		mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
		mClose_LED_GREEN; //配置引脚为"输出",并"熄灭"LED_GREEN 
		mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
		Open_Timing_Task(300);//打开系统定时，定时给定的时间值(中断内)
		break;	

	case 3:	 //3短亮300ms
		mOpen_LED_YELLOW;  //配置引脚为"输出",并"点亮"LED_YELLOW 
		mOpen_LED_GREEN;  //配置引脚为"输出",并"点亮"LED_GREEN
		mOpen_LED_RED;  //配置引脚为"输出",并"点亮"LED_RED
		Open_Timing_Task(300);//打开系统定时，定时给定的时间值(中断内)
		break;

	case 4: //4短暗300ms
		mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
		mClose_LED_GREEN; //配置引脚为"输出",并"熄灭"LED_GREEN 
		mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
		Open_Timing_Task(300);//打开系统定时，定时给定的时间值(中断内)
		break;	

	case 5: //5短亮300ms
		mOpen_LED_YELLOW;  //配置引脚为"输出",并"点亮"LED_YELLOW 
		mOpen_LED_GREEN;  //配置引脚为"输出",并"点亮"LED_GREEN
		mOpen_LED_RED;	//配置引脚为"输出",并"点亮"LED_RED
		Open_Timing_Task(300);//打开系统定时，定时给定的时间值(中断内)
		break;

	case 6: //6长暗1.8s
		mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
		mClose_LED_GREEN; //配置引脚为"输出",并"熄灭"LED_GREEN 
		mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
		Open_Timing_Task(1800);//打开系统定时，定时给定的时间值(中断内)
		break;	

	case 7: //7长亮900ms
		mOpen_LED_YELLOW;  //配置引脚为"输出",并"点亮"LED_YELLOW 
		mOpen_LED_GREEN;  //配置引脚为"输出",并"点亮"LED_GREEN
		mOpen_LED_RED;	//配置引脚为"输出",并"点亮"LED_RED
		Open_Timing_Task(900);//打开系统定时，定时给定的时间值(中断内)
		break;

	case 8: //8短暗300ms
		mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
		mClose_LED_GREEN; //配置引脚为"输出",并"熄灭"LED_GREEN 
		mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
		Open_Timing_Task(300);//打开系统定时，定时给定的时间值(中断内)
		break;	

	case 9: //9长亮900ms
		mOpen_LED_YELLOW;  //配置引脚为"输出",并"点亮"LED_YELLOW 
		mOpen_LED_GREEN;  //配置引脚为"输出",并"点亮"LED_GREEN
		mOpen_LED_RED;	//配置引脚为"输出",并"点亮"LED_RED
		Open_Timing_Task(900);//打开系统定时，定时给定的时间值(中断内)
		break;

	case 10: //10短暗300m
		mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
		mClose_LED_GREEN; //配置引脚为"输出",并"熄灭"LED_GREEN 
		mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
		Open_Timing_Task(300);//打开系统定时，定时给定的时间值(中断内)
		break;	
		
	case 11: //11长亮900ms 
		mOpen_LED_YELLOW;  //配置引脚为"输出",并"点亮"LED_YELLOW 
		mOpen_LED_GREEN;  //配置引脚为"输出",并"点亮"LED_GREEN
		mOpen_LED_RED;	//配置引脚为"输出",并"点亮"LED_RED
		Open_Timing_Task(900);//打开系统定时，定时给定的时间值(中断内)
		break;

	case 12: //12长暗1.8s  
		mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
		mClose_LED_GREEN; //配置引脚为"输出",并"熄灭"LED_GREEN 
		mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
		Open_Timing_Task(1800);//打开系统定时，定时给定的时间值(中断内)
		break;	
////////////////////////////////////////////////////////////////////////////
	default:
		break;
		}
		
		G_SOS_Cnt ++;
		if(G_SOS_Cnt >= 13) G_SOS_Cnt = 1;

	}

}


/****************************************************************************
*函数名-Function:	void Deal_Main_Loop(void)
*描述- Description:	       主循环中的，循环执行的操作(显示、采样)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01) 	▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_Main_Loop(void)  //主循环中的，循环执行的操作(显示、采样)
{
////////////////////////////////////////////////////////////////////////////
//==**处理显示: "彩屏LCD_TFT"**===============================//
	Deal_LCD_TFT();//LCD_TFT 显示控制//只更新内容变化的显示部分

////////////////////////////////////////////////////////////////////////////
//==**处理显示: "段式LCD_Segment"**===========================//
	Deal_LCD_Segment();//"段式LCD_Segment": 处理不同"工作模式"

////////////////////////////////////////////////////////////////////////////
//==**处理显示: "数码管LED_Segment"**=========================//
	Deal_LED_Segment();//"数码管LED_Segment": 处理不同"工作模式"

	if((G_WorkState != WORK_Speaker_Test)&&(G_WorkState != WORK_LCD_Segment_Test))
	{
		////////////////////////////////////////////////////////////////////////////
		//==**系统每100ms 读取"实时时间"**======================//
		Deal_RTC(); //处理" RTC 实时时钟":采样实时时间，显示实时时间

		////////////////////////////////////////////////////////////////////////////
		//==**系统每100ms 采样一次"TMP006 温度"**====================//
		Deal_TMP006_Temperature();	//处理TMP006 温度,得到最后的"实际温度值"

		////////////////////////////////////////////////////////////////////////////
		//==**系统每100ms 采样一次"监测电流值"**================//
		Deal_INA21x();	//处理 "INA21x 电流分流监控器": AD采样，AD数据处理，显示处理			
	}

}


