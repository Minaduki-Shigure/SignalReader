/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 RTC.c
* 附属文件-Dependencies:  	 RTC.h; MyProject_Set_LCD_TFT.h; msp430f6638.h; System.h;  Hardware_Profile.h; Generic.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■"RTC 内部实时时钟" -驱动程序(处理器内部资源) 
	01) MSP430F6638 只有一个实时时钟模块(RTC_B)，RTC_B 仅支持日历功。
	02) 由于RTC_B 分频系数出厂时已设置为固定值，为了提供准确
	      的1s 时基单元，该模块时钟源必须为32.768KHz。 
	03) 如果 VCC 关闭，它仍然可以通过电池供电而自动运行。
	04) 此外，该模块还 具有报警和校准功能，并且能工作在
	      超低功耗LPMx.5 模式下。
	05)
	06)	
	07)	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 注意事项-Attention : 	
	▲01) 若要打开RTC相关中，请配置
			A) 在Init_RTC()中取消屏蔽//RTCCTL0 |= RTCRDYIE + RTCTEVIE + RTCAIE;  
			B)在Interrupt.c中取消屏蔽RTC中断服务程序
	▲02)     ▲03)    ▲04)    ▲05)    ▲06)     
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

#include "RTC.h"   //"RTC 内部实时时钟" -驱动程序-头文件(处理器内部资源) 



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
union FLAGBIT16 RTC_FlagBits;   //"RTC 内部实时时钟"相关标志位变量


	//读出缓存数组
unsigned char G_RTC_ReadBuf[24];



							
	//修改缓存数组BCD码(RTC) :   年_H,年_L,月,Week, 日,  时, 分,  秒
unsigned char G_RTC_WriteBuf[8]  = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

unsigned int  G_Year_SetBuf = 0;   //"年"值(修改时间)(采用十进制)
unsigned char G_Month_SetBuf = 0;  //"月"值(修改时间)(采用十进制)
unsigned char G_Date_SetBuf = 0;   //"日"值(修改时间)(采用十进制)

unsigned char G_Hour_SetBuf = 0;   //"小时"值(修改时间)(采用十进制)
unsigned char G_Minute_SetBuf = 0; //"分钟"值(修改时间)(采用十进制)
unsigned char G_Second_SetBuf = 0; //"秒"值(修改时间)(采用十进制)

unsigned char G_Week_SetBuf = 0;   //"星期"值(修改时间)(采用十进制)


unsigned char G_LastSecondBuf = 0;  //存上次"秒"时间,用于时间变化刷新时间
unsigned char G_LastMinuteBuf = 0;  //存上次"分钟"时间
unsigned char G_LastHourBuf = 0;    //存上次"小时"时间


//星期一： MON = Monday         //星期二：TUE = Tuesday   
//星期三： WED = Wednesday    //星期四：THU = Thursday 
//星期五： FRI = Friday             //星期六：SAT = Saturday 
//星期天： SUN = Sunday

////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////



/****************************************************************************
*函数名-Function:	void Init_RTC_B(void)
*描述- Description:	初始化: RTC_B 实时时钟
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Init_RTC_B(void)
{
////////////////////////////////////////////////////////////////////////////
//==**RTCCTL01*Real-Time Clock Control 0 and 1 Register**============//
		// 关闭RTC，将RTC日历计数器设为BCD模式，时间事件为每小时改变一次
    RTCCTL01 = RTCBCD + RTCHOLD + RTCTEV_1;
		//RTCBCD   Real-time clock BCD select. Selects BCD counting for real-time clock.
		//RTCHOLD  Real-time clock hold //0b = Real-time clock is operational. //1b = The calendar is stopped as well as the prescale counters, RT0PS, and RT1PS.
		//RTCTEV_1  Real-time clock time interrupt event//01b = Hour changed  //00b = Minute changed  //10b = Every day at midnight (00:00)  //11b = Every day at noon (12:00)

////////////////////////////////////////////////////////////////////////////
//==**设置起始时间**===================================//
/*********************************************/
		//BCD码// 设置起始时间，2013年01月01日，00:00:00，星期二
	RTCYEAR = 0x2013; //年
	RTCMON	= 0x01;   //月
	RTCDAY	= 0x01;   //日//Day of Month Register
	
	RTCHOUR = 0x00;   //时
	RTCMIN  = 0x00;   //分
	RTCSEC  = 0x00;   //秒
	
	RTCDOW	= 0x02;   //星期//Day of Week Register
	


////////////////////////////////////////////////////////////////////////////
//==**使能RTC 模块**=====================================//
		//RTCHOLD  Real-time clock hold //0b = Real-time clock is operational. //1b = The calendar is stopped as well as the prescale counters, RT0PS, and RT1PS.
    RTCCTL01 &= ~RTCHOLD;
		
		
////////////////////////////////////////////////////////////////////////////
//==**设置报警时间**===================================//
		// 设置报警时间，每周一，07:00:00
//RTCAHOUR = 0x87;
//RTCAMIN  = 0x80;
//RTCADOW  = 0x81;  //Real-Time Clock Day of Week Alarm Register
		// 使能每秒中断、时间事件、报警中断
		
////////////////////////////////////////////////////////////////////////////
//==**中断相关*RTCCTL0*Real-Time Clock Control 0 Register**============//

//RTCCTL0 |= RTCRDYIE + RTCTEVIE + RTCAIE;     // Enable interrupt
		//RTCRDYIE   Real-time clock ready interrupt enable.
		//RTCTEVIE   Real-time clock time event interrupt enable. In modules supporting LPMx.5 this interrupt can be used as LPMx.5 wake-up event.
		//RTCAIE      Real-time clock alarm interrupt enable. In modules supporting LPMx.5 this interrupt can be used as LPMx.5 wake-up event.
		
}



/****************************************************************************
*函数名-Function:	void Read_RTC_CurrentTime(void)
*描述- Description:	实时读取: RTC 实时时钟
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Read_RTC_CurrentTime(void)
{
	if (G_LastSecondBuf != RTCSEC) //实时"秒"改变
	{  
		F_SecondChange_RTC = 1;                          
		G_LastSecondBuf = RTCSEC;  //保留本次"秒"值
	} 

	if(G_LastMinuteBuf != RTCMIN ) //实时"分钟"改变
	{
		F_MinuteChange_RTC = 1;     
		G_LastMinuteBuf = RTCMIN;  //保留本次"分钟"值
	}
	   
	if(G_LastHourBuf != RTCHOUR )     //实时"小时"改变
	{
		F_HourChange_RTC = 1;    
		G_LastHourBuf = RTCHOUR;     //保留本次"小时"值
	}
	


	G_RTC_ReadBuf[0]  = ASCII_Table[RTCYEAR >> 12];  //存"千位"(年)(ASSII码)
	G_RTC_ReadBuf[1]  = ASCII_Table[(RTCYEAR >> 8) & 0x000F];	//存"百位"(年)(ASSII码)
	G_RTC_ReadBuf[2]  = ASCII_Table[(RTCYEAR >> 4) & 0x000F];	//存"十位"(年)(ASSII码)
	G_RTC_ReadBuf[3]  = ASCII_Table[RTCYEAR & 0x000F];	//存"个位"(年)(ASSII码)
	G_RTC_ReadBuf[4]  = '-';
	G_RTC_ReadBuf[5]  =  ASCII_Table[RTCMON >> 4];	//存"十位"(月)(ASSII码)
	G_RTC_ReadBuf[6]  =  ASCII_Table[RTCMON & 0x0F];	//存"个位"(月)(ASSII码)
	G_RTC_ReadBuf[7]  = '-';
	G_RTC_ReadBuf[8]  =  ASCII_Table[RTCDAY >> 4];	//存"十位"(日)(ASSII码)
	G_RTC_ReadBuf[9]  =  ASCII_Table[RTCDAY & 0x0F];	//存"个位"(日)(ASSII码)
	G_RTC_ReadBuf[10] = ' ';
	G_RTC_ReadBuf[11]  =  ASCII_Table[RTCHOUR >> 4];  //存"十位"(小时)(ASSII码)
	G_RTC_ReadBuf[12]  =  ASCII_Table[RTCHOUR & 0x0F];	//存"个位"(小时)(ASSII码)
	G_RTC_ReadBuf[13] = ':';
	G_RTC_ReadBuf[14]  =  ASCII_Table[RTCMIN >> 4];  //存"十位"(分钟)(ASSII码)
	G_RTC_ReadBuf[15]  =  ASCII_Table[RTCMIN & 0x0F];	//存"个位"(分钟)(ASSII码)
	G_RTC_ReadBuf[16] = ':';
	G_RTC_ReadBuf[17]  =  ASCII_Table[RTCSEC >> 4];  //存"十位"(秒)(ASSII码)
	G_RTC_ReadBuf[18]  =  ASCII_Table[RTCSEC & 0x0F];	//存"个位"(秒)(ASSII码)
	G_RTC_ReadBuf[19] = ' ';

	switch(RTCDOW) 
	{
		case 1:	  //星期一
			G_RTC_ReadBuf[20] = 'M';
			G_RTC_ReadBuf[21] = 'O';
			G_RTC_ReadBuf[22] = 'N';
			break;	
			
		case 2:   //星期二
			G_RTC_ReadBuf[20] = 'T';
			G_RTC_ReadBuf[21] = 'U';
			G_RTC_ReadBuf[22] = 'E';
			break;	

		case 3:   //星期三
			G_RTC_ReadBuf[20] = 'W';
			G_RTC_ReadBuf[21] = 'E';
			G_RTC_ReadBuf[22] = 'D';
			break;	

		case 4:   //星期四
			G_RTC_ReadBuf[20] = 'T';
			G_RTC_ReadBuf[21] = 'H';
			G_RTC_ReadBuf[22] = 'U';
			break;	

		case 5:   //星期五
			G_RTC_ReadBuf[20] = 'F';
			G_RTC_ReadBuf[21] = 'R';
			G_RTC_ReadBuf[22] = 'I';
			break;	
			
		case 6:   //星期六
			G_RTC_ReadBuf[20] = 'S';
			G_RTC_ReadBuf[21] = 'A';
			G_RTC_ReadBuf[22] = 'T';
			break;	
			
		case 7:   //星期日
			G_RTC_ReadBuf[20] = 'S';
			G_RTC_ReadBuf[21] = 'U';
			G_RTC_ReadBuf[22] = 'N';
			break;	

////////////////////////////////////////////////////////////////////////////
		default:	//不是1到7的显示"Err" 表示错误
			G_RTC_ReadBuf[20] = 'E';
			G_RTC_ReadBuf[21] = 'r';
			G_RTC_ReadBuf[22] = 'r';
			break;

	}

}



/****************************************************************************
*函数名-Function:	unsigned char Check_RTC_InputModifyDate(void)
*描述- Description:	检测输入修改时间是否合法
*输入参数-Input:	None
*输出参数-output:	0xFF:合法,0:不合法
*注意事项-Note：	
	▲01) 没有检测"星期"是否输入有错
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char Check_RTC_InputModifyDate(void)
{
	unsigned char Retemp = 0;

if((G_Week_SetBuf >= 1) && (G_Week_SetBuf <= 7))   //如果"星期"在1～7之间，表示正确
{
	if(G_Second_SetBuf < 60)   //如果"秒"小于60，表示正确
	{
		if(G_Minute_SetBuf < 60)   //如果"分钟"小于60，表示正确
		{
			if(G_Hour_SetBuf < 24) //如果"小时"小于24，表示正确
			{                        
				if(G_Month_SetBuf == 2) //如果为2月份
				{
						 //平年: 不能被4整除,或者是能被100 整除，但不能被400整除  
					if((G_Year_SetBuf & 0x03)||(((G_Year_SetBuf%100) == 0)&&((G_Year_SetBuf%400) != 0)))
					{	
						if((G_Date_SetBuf <= 28)&&(G_Date_SetBuf > 0))    
						{
							Retemp = 0xFF;                                                
						} 
					}
					else   //闰年: 能被4或400整除,但不能被100整除         
					{	
						if((G_Date_SetBuf <= 29)&&(G_Date_SetBuf > 0))
						{
							Retemp = 0xFF;
						}

					}
				}		
				else if((G_Month_SetBuf < 8)&&(G_Month_SetBuf > 0))  //判断1月－7月中的月大，月小
				{
					if(G_Month_SetBuf & 0x01)     //月份<8 的奇数为大月
					{
						if((G_Date_SetBuf <= 31)&&(G_Date_SetBuf > 0))     //月大
						{
							Retemp = 0xFF;   
						}
					} 
					else
					{
						if((G_Date_SetBuf <= 30)&&(G_Date_SetBuf > 0))   //月小
						{
							Retemp = 0xFF;   
						}
					}                               
				}
				else 
				{
					if((G_Month_SetBuf < 13) && (G_Month_SetBuf > 7))     //判断8月－12月中的月大，月小
					{
						if(G_Month_SetBuf & 0x01)     //月份>=8 的奇数为小月
						{
							if((G_Date_SetBuf <= 30)&&(G_Date_SetBuf > 0))   //月小
							{
								Retemp = 0xFF;   
							}
						} 
						else
						{
							if((G_Date_SetBuf <= 31)&&(G_Date_SetBuf > 0))    //月大
							{
								Retemp = 0xFF;   
							}
						} 
					}
				}                    
			}
		}
	}
}



	return Retemp;
}


/******************************************************************
*函数名 Function Name: void Modify_PCF8583_Time(void)
*函数功能 Description: 修改PCF8583的日期时间
*输入参数 Parameters : None
*输出参数Return Value: None
*注意事项  Attention ：
	01)写时间到PCF8583时， 同样要先把数据转成BCD码再写入PCF8583
	02)  03) 04)  05) 06)
*******************************************************************/

/****************************************************************************
*函数名-Function:	void Modify_RealTime_RTC(void)
*描述- Description:	修改RTC实时时钟
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01)  先把数据转成BCD码再写入RTC
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Modify_RealTime_RTC(void)
{ 

//要写入时钟时，
//要不要，先把时钟RTC关闭??????
	//BCD码// 设置起始时间	
//	RTCYEARH = ChangeDecIntoHex((unsigned char)(G_Year_SetBuf / 100));
//	RTCYEARL = ChangeDecIntoHex((unsigned char)(G_Year_SetBuf % 100));
	RTCYEAR = ((ChangeDecIntoHex(G_Year_SetBuf / 100))<<8)+(ChangeDecIntoHex(G_Year_SetBuf % 100));
	RTCMON	= ChangeDecIntoHex(G_Month_SetBuf);
	RTCDAY	= ChangeDecIntoHex(G_Date_SetBuf);   //Day of Month Register

	RTCHOUR = ChangeDecIntoHex(G_Hour_SetBuf);
	RTCMIN	= ChangeDecIntoHex(G_Minute_SetBuf);
	RTCSEC	= ChangeDecIntoHex(G_Second_SetBuf);

	RTCDOW	= ChangeDecIntoHex(G_Week_SetBuf);   //Day of Week Register

}


/****************************************************************************
*函数名-Function:	void Deal_RTC(void)
*描述- Description:	处理" RTC 实时时钟":采样实时时间，显示实时时间
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_RTC(void)
{
////////////////////////////////////////////////////////////////////////////
//==**系统每100ms 读取"实时时间"**======================//
	if(F_100ms_ReadTime)	//系统定时每100ms读一次"实时时钟"
	{
		F_100ms_ReadTime = 0;
	
		Read_RTC_CurrentTime();//实时读取: RTC 实时时钟
	}

////////////////////////////////////////////////////////////////////////////
//--**显示实时时间**-----------------------------------------------//
	Disp_RTC_CurrentTime(); //显示: RTC 实时时钟


}







