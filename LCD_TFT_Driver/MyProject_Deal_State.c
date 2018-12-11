/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 MyProject_Deal_State.c
* 附属文件-Dependencies:  	 System_HeadFile.h; 	
* 文件描述-File Description:	 ( 源程序-Source File) 
	■ 具体项目: "处理"各系统"状态"下的事务 (状态机)
	01)    02)     03)    04)    05)    06)	
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



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////

/****************************************************************************
*函数名-Function:	void Deal_Main_ModifyTime(void)
*描述- Description:	//处理//Main█"实时时间"修改状态
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_Main_ModifyTime(void) //处理//Main█"实时时间"修改状态
{
////////////////////////////////////////////////////////////////////////////
//==**闪烁显示按键值和按键位置**=====================//
	Blink_ModifyTime(); //处理"实时时间"修改状态下的闪烁

////////////////////////////////////////////////////////////////////////////
//==**按键 处理**=======================================//

////////////////////////////////////////////////////////////////////////////
//--**IO按键 处理**---------------------------------------------------//

	Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"

////////////////////////////////////////////////////////////////////////////
//--**矩阵按键 处理**-----------------------------------------------//
if(F_MatrixKeyRead)
{
	F_MatrixKeyRead = 0;
	
	switch(G_MatrixKeyValue)
	{		
		case MatrixKey_0:  //"数字0键"	
		case MatrixKey_1:  //"数字1键"		
		case MatrixKey_2:  //"数字2键"		
		case MatrixKey_3:  //"数字3键"		
		case MatrixKey_4:  //"数字4键"		
		case MatrixKey_5:  //"数字5键"					
		case MatrixKey_6:  //"数字6键"			
		case MatrixKey_7:  //"数字7键"			
		case MatrixKey_8:  //"数字8键"			
		case MatrixKey_9:  //"数字9键"		
//--**采样按键值**----------------------------------------//
			G_MatrixKeyBuf[G_MatrixKeyCnt] = G_MatrixKeyValue; //缓存当前按键值到按键缓冲区

			Disp_ModifyTimeState(); //显示时间修改过程
			G_MatrixKeyCnt ++; //缓冲按键数组指针加1
			
//要存15个按键值:年(4个)+月(2个)+日(2个)+时(2个)+分(2个)+秒(2个)+星期(1个)
			if(G_MatrixKeyCnt >= G_TotalKeyNum)  
			{
				G_MatrixKeyCnt = 0;
			}

			Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
			break;
	
		case MatrixKey_Return:	 //"返回键"
			Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
			Initial_MainState(MAIN_Basic_Settings);//Main█Basic_Settings菜单选择(工作时)
			break;
			
		case MatrixKey_OK:	//"确定键"
			Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
			G_Year_SetBuf = G_MatrixKeyBuf[0]*1000 + G_MatrixKeyBuf[1]*100 + G_MatrixKeyBuf[2]*10 + G_MatrixKeyBuf[3];
			G_Month_SetBuf = G_MatrixKeyBuf[4]*10 + G_MatrixKeyBuf[5];
			G_Date_SetBuf = G_MatrixKeyBuf[6]*10 + G_MatrixKeyBuf[7];
			G_Hour_SetBuf = G_MatrixKeyBuf[8]*10 + G_MatrixKeyBuf[9];
			G_Minute_SetBuf = G_MatrixKeyBuf[10]*10 + G_MatrixKeyBuf[11];
			G_Second_SetBuf = G_MatrixKeyBuf[12]*10 + G_MatrixKeyBuf[13];
			G_Week_SetBuf = G_MatrixKeyBuf[14];
			
//--**判断输入时间是否合法**-------------------------------------//
			if(Check_RTC_InputModifyDate()) 	 //没有检测"星期"是否输入有错
			{
				Modify_RealTime_RTC();//修改RTC实时时钟
				
				Initial_MainState(MAIN_Basic_Settings);//装载//Main█Basic_Settings菜单选择(工作时)
			}
			else
			{	
				Dis_ModifyTimeError() ;  //显示"错误: 时间输入有误!"
				Disp_ModifyTimeState(); //显示时间修改过程
				
				G_MatrixKeyCnt = 0;  //从第1位(年的千位)重新输入
				Open_Buzzer(M_Buzz1s);   //报警:  让蜂鸣叫指定时间
			}  

			break;
	
		default:  
			break;	
		
	}
}




}



/****************************************************************************
*函数名-Function:	void Deal_Main_Self_Check(void)
*描述- Description:	处理//Main█系统自检状态
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_Main_Self_Check(void) //处理//Main█系统自检状态
{
	
//==**显示处理**============================//
	F_Update_RealTime = NO; 	//此时，不刷新"实时时间"	 
	F_Update_Temperature = NO;	//此时，不刷新"实时温度"  
	F_Update_CurrentValue = NO; //此时，不刷新"INA21x 实时电流值" 
	F_Update_Power = NO;		//此时，不刷新"锂电池电量"

//==**按键 处理**===========================//
	if(!F_Timing)  // 人为定时结束后，自动进入工作状态(工作时)
	{
		Initial_MainState(MAIN_Working_State);//装载 //Main█进入工作状态(工作时)
	}
}




/****************************************************************************
*函数名-Function:	void Deal_MAIN_Basic_Settings(void)
*描述- Description:	//处理//Main█Basic_Settings菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_MAIN_Basic_Settings(void) //处理//Main█Basic_Settings菜单选择(工作时)
{
////////////////////////////////////////////////////////////////////////////
//==**显示处理**========================================//
	unsigned char hour_H,hour_L,minute_H,minute_L,second_H,second_L;

	hour_H = RTCHOUR >> 4;
	hour_L = RTCHOUR & 0x0F;
	minute_H = RTCMIN >> 4;
	minute_L = RTCMIN & 0x0F;
	second_H = RTCSEC >> 4;
	second_L = RTCSEC & 0x0F;

	Disp_LED_Segment(0,0,hour_H,hour_L,DISP_Minus_LedSeg,minute_H,minute_L,DISP_Minus_LedSeg,second_H,second_L);


////////////////////////////////////////////////////////////////////////////
//--**IO按键 处理**---------------------------------------------------//
	Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"

////////////////////////////////////////////////////////////////////////////
//--**矩阵按键 处理**-----------------------------------------------//

	if(Detect_MatrixKey_1()) //"数字1键"//1.Restart Self-Test
	{
		Initial_MainState(MAIN_Restart); //装载//Main█ 重启，并系统自检--Restart Self-Test       
	}
	  
	if(Detect_MatrixKey_2()) //"数字2键"//2.Time Setting
	{
		Initial_MainState(MAIN_ModifyTime); //装载//Main█"实时时间"修改状态
	}

}



/****************************************************************************
*函数名-Function:	void Deal_MAIN_Basic_Check(void)
*描述- Description:	//处理//Main█Basic_Check 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_MAIN_Basic_Check(void) //处理//Main█Basic_Check 菜单选择(工作时)
{
////////////////////////////////////////////////////////////////////////////
//==**显示处理**========================================//

////////////////////////////////////////////////////////////////////////////
//==**按键 处理**=======================================//

////////////////////////////////////////////////////////////////////////////
//--**IO按键 处理**---------------------------------------------------//

	Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"


////////////////////////////////////////////////////////////////////////////
//--**矩阵按键 处理**-----------------------------------------------//
	if(Detect_MatrixKey_1()) //"数字1键"//1.LED_Diode
	{
		Initial_WorkState(WORK_Led_Diode_Test); //装载//Work▓Led_Diode_Test 测试(工作时)
	}

	if(Detect_MatrixKey_2()) //"数字2键"//2.LED_Segment
	{
		Initial_WorkState(WORK_LED_Segment_Test); //装载//Work▓LED_Segment_Test 测试(工作时)
	}

	if(Detect_MatrixKey_3()) //"数字3键"//3.LCD_Segment
	{
		Initial_WorkState(WORK_LCD_Segment_Test); //装载//Work▓LCD_Segment_Test 测试(工作时)
	}

	if(Detect_MatrixKey_4()) //"数字4键"//4.Buzzer-Alarm
	{
		Initial_WorkState(WORK_Buzzer_Test); //装载//Work▓Buzzer_Test 测试(工作时)
	}

	if(Detect_MatrixKey_5()) //"数字5键"//5.Speaker
	{
		Initial_WorkState(WORK_Speaker_Test); //装载//Work▓Speaker_Test 测试(工作时)
	}	
	
	if(Detect_MatrixKey_6()) //"数字6键"//6.Microphone
	{
		Initial_WorkState(WORK_Microphone_Test); //装载//Work▓Microphone_Test 测试(工作时)
	}	

	if(Detect_MatrixKey_7()) //"数字7键"//7.Battery Fuel Gauge
	{
		Initial_WorkState(WORK_BQ27410_Test); //装载//Work▓BQ27410_FuelGauge_Test 测试(工作时)
	}	

}



/****************************************************************************
*函数名-Function:	void Deal_MAIN_LCD_TFT_Test(void)
*描述- Description:	//处理//Main█LCD_TFT_Test 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_MAIN_LCD_TFT_Test(void) //处理//Main█LCD_TFT_Test 菜单选择(工作时)
{
////////////////////////////////////////////////////////////////////////////
//==**显示处理**========================================//

////////////////////////////////////////////////////////////////////////////
//==**按键 处理**=======================================//

////////////////////////////////////////////////////////////////////////////
//--**IO按键 处理**---------------------------------------------------//

	Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"

////////////////////////////////////////////////////////////////////////////
//--**矩阵按键 处理**-----------------------------------------------//
	if(Detect_MatrixKey_1()) //"数字1键"
	{
		Initial_WorkState(WORK_Line_LCD_TFT); //装载//Work▓Line_LCD_TFT 测试(工作时)
	}

	if(Detect_MatrixKey_2()) //"数字2键"
	{
		Initial_WorkState(WORK_Rectangle_LCD_TFT); //装载//Work▓Rectangle_LCD_TFT 测试(工作时)
	}

	if(Detect_MatrixKey_3()) //"数字3键"
	{
		Initial_WorkState(WORK_Circle_LCD_TFT); //装载//Work▓Circle_LCD_TFT 测试(工作时)
	}

	if(Detect_MatrixKey_4()) //"数字4键"
	{
		Initial_WorkState(WORK_FillArea_LCD_TFT); //装载//Work▓FillArea_LCD_TFT 测试(工作时)
	}

	if(Detect_MatrixKey_5()) //"数字5键"//
	{
		Initial_WorkState(WORK_Chinese_LCD_TFT); //装载//Work▓Chinese_LCD_TFT 测试(工作时)
	}	
	
	if(Detect_MatrixKey_6()) //"数字6键"//
	{
		Initial_WorkState(WORK_Clear_LCD_TFT); //装载//Work▓Clear_LCD_TFT 测试(工作时)
	}

}


/****************************************************************************
*函数名-Function:	void Deal_MAIN_MatrixKey_Test(void)
*描述- Description:	//处理//Main█MatrixKey_Test 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_MAIN_MatrixKey_Test(void) //处理//Main█MatrixKey_Test 菜单选择(工作时)
{
////////////////////////////////////////////////////////////////////////////
//==**显示处理**========================================//

////////////////////////////////////////////////////////////////////////////
//==**按键 处理**=======================================//


////////////////////////////////////////////////////////////////////////////
//--**矩阵按键 处理**-----------------------------------------------//
	Disp_MatrixKey_Press(); //根据按下的"矩阵按键"，在测试区域显示"按键值"

////////////////////////////////////////////////////////////////////////////
//--**IO按键 处理**---------------------------------------------------//

	Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"

}


/****************************************************************************
*函数名-Function:	void Deal_MAIN_TouchPads_Test(void)
*描述- Description:	//处理//Main█TouchPads_Test 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_MAIN_TouchPads_Test(void) //处理//Main█TouchPads_Test 菜单选择(工作时)
{
////////////////////////////////////////////////////////////////////////////
//==**按键 处理**=======================================//


////////////////////////////////////////////////////////////////////////////
//--**矩阵按键 处理**-----------------------------------------------//

////////////////////////////////////////////////////////////////////////////
//==**功能模块处理**======================================//
	F_En_Scan_MatrixKey = NO;  //禁止扫描"矩阵按键扫描"
	
	//Initial_Touch_Pad();  //初始化设置: "Touch_Pads 电容按键" 
	Deal_Touch_Pad();  //处理: "Touch_Pads 电容按键"
	
	F_En_Scan_MatrixKey = YES;	//允许中断中扫描"矩阵按键扫描"
	
	switch (G_SliderPosition)
	{
		case 0: 
			//Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
			break;
			
		case 1: 
			Disp_LED_Segment(0,0,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg);

				//有按键按下，打开蜂鸣器
			Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间

			G_LcdBuf[TestLine06][TestColumn01]= 'T';
			G_LcdBuf[TestLine06][TestColumn02]= 'P';
			G_LcdBuf[TestLine06][TestColumn03]= '1';
			F_Update_TestLine06 = YES;
			break;

		case 2: 
			Disp_LED_Segment(0,0,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg);

				//有按键按下，打开蜂鸣器
			Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间

			G_LcdBuf[TestLine06][TestColumn05]= 'T';
			G_LcdBuf[TestLine06][TestColumn06]= 'P';
			G_LcdBuf[TestLine06][TestColumn07]= '2';
			F_Update_TestLine06 = YES;
			break;

		case 3: 
			Disp_LED_Segment(0,0,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg);

				//有按键按下，打开蜂鸣器
			Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
			
			G_LcdBuf[TestLine06][TestColumn09]= 'T';
			G_LcdBuf[TestLine06][TestColumn10]= 'P';
			G_LcdBuf[TestLine06][TestColumn11]= '3';
			F_Update_TestLine06 = YES;
			break;
		
		case 4: 
			Disp_LED_Segment(0,0,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg);

				//有按键按下，打开蜂鸣器
			Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间

			G_LcdBuf[TestLine06][TestColumn13]= 'T';
			G_LcdBuf[TestLine06][TestColumn14]= 'P';
			G_LcdBuf[TestLine06][TestColumn15]= '4';
			F_Update_TestLine06 = YES;
			break;

		case 5: 
			Disp_LED_Segment(0,0,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg);

				//有按键按下，打开蜂鸣器
			Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间

			G_LcdBuf[TestLine06][TestColumn17]= 'T';
			G_LcdBuf[TestLine06][TestColumn18]= 'P';
			G_LcdBuf[TestLine06][TestColumn19]= '5';
			F_Update_TestLine06 = YES;
			break;

		case (255 / 17):
			break;
	}

////////////////////////////////////////////////////////////////////////////
//--**IO按键 处理**---------------------------------------------------//

	Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"


}



/****************************************************************************
*函数名-Function:	void Deal_INA210_Current_Test(void)
*描述- Description:	//处理//Main█INA210_Current_Test 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_INA210_Current_Test(void) //处理//Main█INA210_Current_Test 菜单选择(工作时)
{
////////////////////////////////////////////////////////////////////////////
//==**AD采样相关**======================================//

////////////////////////////////////////////////////////////////////////////
//==**显示处理**========================================//
	if(F_500ms_INA21x_InTest)  //500ms 刷新显示 INA21x 实时"监测电流值"
	{
		F_500ms_INA21x_InTest = 0;
		
////////////////////////////////////////////////////////////////////////////
//--**显示处理:  "彩屏LCD_TFT" **------------------------------------//
		Disp_INA21x_Current_InTest(); //在"测试行"显示: INA21x 实时"监测电流值"

////////////////////////////////////////////////////////////////////////////
//--**显示处理:  "动态数码管LED_Segment"**-----------------------//
		Disp_LED_Segment(0,6,DISP_OFF_LedSeg,DISP_OFF_LedSeg,(unsigned char)(G_INA21x_AdResult/1000),(unsigned char)((G_INA21x_AdResult % 1000)/100),(unsigned char)((G_INA21x_AdResult % 100)/10),G_INA21x_AdResult % 10,DISP_OFF_LedSeg,DISP_A_LedSeg);
	}


////////////////////////////////////////////////////////////////////////////
//==**按键 处理**=======================================//

////////////////////////////////////////////////////////////////////////////
//--**IO按键 处理**---------------------------------------------------//

	Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"
}




/****************************************************************************
*函数名-Function:	void Deal_MAIN_Potentiometer_Test(void)
*描述- Description:	//处理//Main█Potentiometer_Test 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_MAIN_Potentiometer_Test(void) //处理//Main█Potentiometer_Test 菜单选择(工作时)
{
	unsigned char a,b,c;
	
	a = (unsigned char)(G_LastAdResult/1000);
	b = (unsigned char)((G_LastAdResult % 1000)/100);
	c = (G_LastAdResult % 100)/10;
	if(G_LastAdResult < 30) c = 0; //在电位器旋到最小值时，显示电压会在0.01,0.02,.000之间显示，加上这条，可以在电位器旋到最小值时，显示0.00

////////////////////////////////////////////////////////////////////////////
//==**AD采样相关**======================================//
		//多次采样"Potentiometer电位计"AD值，并进行处理
	Deal_ADC12_A(M_Potentiometer_AdNum); // 处理采样结果: 将多次采样值，进行排序，去掉两头，对中间的几个AD值求平均，得到最后的AD值。

////////////////////////////////////////////////////////////////////////////
//==**显示处理**========================================//
	if(F_500ms_Reflash_Potentiometer)  //500ms 刷新"电压值"(电位计 )
	{
		F_500ms_Reflash_Potentiometer = 0;
		
////////////////////////////////////////////////////////////////////////////
//--**显示处理:  "彩屏LCD_TFT" **------------------------------------//
		Disp_Potentiometer_InTest();//在"测试行"显示: 电位计Potentiometer 实时"电压值"

////////////////////////////////////////////////////////////////////////////
//--**显示处理:  "动态数码管LED_Segment"**-----------------------//
		Disp_LED_Segment(0,3,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,a,b,c);
	}

////////////////////////////////////////////////////////////////////////////
//==**按键 处理**=======================================//

////////////////////////////////////////////////////////////////////////////
//--**IO按键 处理**---------------------------------------------------//

	Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"

////////////////////////////////////////////////////////////////////////////
//--**矩阵按键 处理**-----------------------------------------------//

}


/****************************************************************************
*函数名-Function:	void Deal_MAIN_NTC_HR202_Test(void)
*描述- Description:	//处理//Main█NTC_HR202_Test(温湿度) 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_MAIN_NTC_HR202_Test(void) //处理//Main█NTC_HR202_Test(温湿度) 菜单选择(工作时)
{
	int NTC_TMP_Ad;
	unsigned char a,b,c,d,bai,shi,ge;

	
	Deal_NTC_Temperature(); //处理 "NTC 电阻温度传感器" : AD采样，AD数据处理，显示处理

	Deal_HR202_Humidity(); //处理 "HR202_Humidity 电阻型湿度传感器"
////////////////////////////////////////////////////////////////////////////
//==**显示处理**========================================//
	if(F_500ms_NTC_HR202_InTest)  //500ms 刷新在测试区域，刷新LCD_TFT显示NTC（温度）、HR202（湿度）	
	{
		F_500ms_NTC_HR202_InTest = 0;
	
		Disp_NTC_TMP(G_NTC_Temperature); //显示: 实时"NTC 热敏电阻值"对应的温度


////////////////////////////////////////////////////////////////////////////
//--**显示处理:  "动态数码管LED_Segment"**-----------------------//
		NTC_TMP_Ad = G_NTC_Temperature;
		if(NTC_TMP_Ad < 0)
		{
			NTC_TMP_Ad = - NTC_TMP_Ad;
			a = DISP_Minus_LedSeg;
			b = (unsigned char)((NTC_TMP_Ad % 1000)/100);  //十位
			c = (unsigned char)((NTC_TMP_Ad % 100)/10);    //个位
			d = (unsigned char)(NTC_TMP_Ad % 10);		   //小数第一位
		
			if(b == 0) 
			{
				a = DISP_OFF_LedSeg;
				b = DISP_Minus_LedSeg;
			}
		}
		else
		{
			a = (unsigned char)(NTC_TMP_Ad/1000);
			b = (unsigned char)((NTC_TMP_Ad % 1000)/100);
			c = (unsigned char)((NTC_TMP_Ad % 100)/10);
			d = (unsigned char)(NTC_TMP_Ad % 10);
		
			if(a == 0) 
			{
				a = DISP_OFF_LedSeg;
			}
			else if((a == 0)&&(b == 0))
			{
				a = DISP_OFF_LedSeg;
				b = DISP_OFF_LedSeg;
			}
		}
///////////////////////////////////////////////////////////////////
		bai = G_HR202_Humidity/100;
		if(bai == 0 ) bai = DISP_OFF_LedSeg;
		
		shi = (G_HR202_Humidity / 10)% 10;
		ge = G_HR202_Humidity % 10;


		Disp_LED_Segment(0,6,a,b,c,d,DISP_OFF_LedSeg,bai,shi,ge);
	}

////////////////////////////////////////////////////////////////////////////
//==**按键 处理**=======================================//

////////////////////////////////////////////////////////////////////////////
//--**IO按键 处理**---------------------------------------------------//
	Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"

////////////////////////////////////////////////////////////////////////////
//--**矩阵按键 处理**-----------------------------------------------//

}


/****************************************************************************
*函数名-Function:	void Deal_MAIN_Step_Motor_Test(void)
*描述- Description:	//处理//Main█Step_Motor_Test 菜单选择(工作时) 
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_MAIN_Step_Motor_Test(void) //处理//Main█Step_Motor_Test 菜单选择(工作时) 
{
	unsigned char a = 0;
	unsigned char b = 0;
	//unsigned char c = 0;
	
	unsigned char s1 = 0;
	unsigned char s2 = 0;
	unsigned char s3 = 0;
	unsigned char s4 = 0;


////////////////////////////////////////////////////////////////////////////
//==**采样电位计AD值,作为转速给定值**================//
		//多次采样"Potentiometer电位计"AD值，并进行处理
	Deal_ADC12_A(M_Potentiometer_AdNum); // 处理采样结果: 将多次采样值，进行排序，去掉两头，对中间的几个AD值求平均，得到最后的AD值。


////////////////////////////////////////////////////////////////////////////
//==**按键 处理**=======================================//

////////////////////////////////////////////////////////////////////////////
//--**矩阵按键 处理**-----------------------------------------------//
	if(Detect_MatrixKey_1()) //"数字1键"//1.Positive Rotation
	{
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
		
		if(G_Step_WorkState != STATE_Positive_Step_Motor)
		{
			G_Step_WorkState = STATE_Positive_Step_Motor;
			Initial_WorkState(WORK_Positive_Step_Motor); //装载//Work▓Positive_Step_Motor 测试(工作时)
		}
	}

	if(Detect_MatrixKey_2()) //"数字2键"//2.Reverse Rotation
	{
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
		
		if(G_Step_WorkState != STATE_Reverse_Step_Motor)
		{
			G_Step_WorkState = STATE_Reverse_Step_Motor;
			Initial_WorkState(WORK_Reverse_Step_Motor); //装载//Work▓Reverse_Step_Motor 测试(工作时)
		}
	}

	if(Detect_MatrixKey_3()) //"数字3键"//3.Stop Step-Moter
	{
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
		
		G_Step_WorkState = STATE_Stop_Step_Motor;
		Initial_WorkState(WORK_Stop_Step_Motor); //装载//Work▓Stop_Step_Motor 测试(工作时)
	}


////////////////////////////////////////////////////////////////////////////
//==**显示处理**========================================//


	if(F_500ms_Reflash_Step_Motor)  //500ms 刷新"转速" --"Step_Motor 步进电机"
	{
		F_500ms_Reflash_Step_Motor = 0;


		Deal_Speed_Step_Motor(); // 计算步进电转速

////////////////////////////////////////////////////////////////////////////
//--**显示处理:  "彩屏LCD_TFT" **------------------------------------//
			//在"测试电机"显示速度给定电压值: 电位计Potentiometer 实时"电压值"
		Disp_Potentiometer_Motor();

		Disp_Speed_Step_Motor(); //在"测试Step_Motor"显示电机速度

////////////////////////////////////////////////////////////////////////////
//--**显示处理:  "动态数码管LED_Segment"**-----------------------//
	//电位计显示相关
		a = (unsigned char)(G_LastAdResult/1000);
		b = (unsigned char)((G_LastAdResult % 1000)/100);
		//c = (unsigned char)(G_LastAdResult % 100)/10;
//		if(G_LastAdResult < 30) c = 0; //在电位器旋到最小值时，显示电压会在0.01,0.02,.000之间显示，加上这条，可以在电位器旋到最小值时，显示0.00

	//转速显示相关
		s3 = (unsigned char)(G_Step_Speed /1000);
		s2 = (unsigned char)((G_Step_Speed % 1000)/100);
		s1 = (unsigned char)(G_Step_Speed % 100)/10;


		if(G_Step_WorkState  == STATE_Reverse_Step_Motor) //反转显示处理
		{
			s4 = DISP_Minus_LedSeg; //显示"负号"(不显示0)		
		
			if(s3 == 0) 
			{
				s4 = DISP_OFF_LedSeg; //显示"暗码"(不显示0)	
				s3 = DISP_Minus_LedSeg; //显示"负号"(不显示0)	
			}
		}
		else if(G_Step_WorkState	== STATE_Positive_Step_Motor) //正转显示处理
		{
			s4 = DISP_OFF_LedSeg;
			if(s3 == 0) s3 = DISP_OFF_LedSeg; //显示"暗码"(不显示0)
		}
		
		Disp_LED_Segment(8,2,a,b,DISP_OFF_LedSeg,DISP_OFF_LedSeg,s4,s3,s2,s1);
	}


////////////////////////////////////////////////////////////////////////////
//--**IO按键 处理**---------------------------------------------------//
	Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"

}


/****************************************************************************
*函数名-Function:	void Deal_MAIN_DC_Motor_Test(void)
*描述- Description:	//处理//Main█DC_Motor_Test 菜单选择(工作时) 
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_MAIN_DC_Motor_Test(void) //处理//Main█DC_Motor_Test 菜单选择(工作时) 
{
	unsigned char a = 0;
	unsigned char b = 0;
//unsigned char c = 0;

	unsigned int speed = 0;
	
	unsigned char s1 = 0;
	unsigned char s2 = 0;
	unsigned char s3 = 0;
	unsigned char s4 = 0;
	unsigned char s5 = 0;

////////////////////////////////////////////////////////////////////////////
//==**采样电位计AD值,作为转速给定值**===================//
		//多次采样"Potentiometer电位计"AD值，并进行处理
	Deal_ADC12_A(M_Potentiometer_AdNum); // 处理采样结果: 将多次采样值，进行排序，去掉两头，对中间的几个AD值求平均，得到最后的AD值。


////////////////////////////////////////////////////////////////////////////
//==**按键 处理**===========================================//


////////////////////////////////////////////////////////////////////////////
//--**矩阵按键 处理**-----------------------------------------------//
	if(Detect_MatrixKey_1()) //"数字1键"//1.Positive Rotation
	{
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
		
		if(G_DC_WorkState == STATE_Reverse_DC_Motor)
		{
			G_DC_WorkState = STATE_Positive_DC_Motor;
			Initial_WorkState(WORK_Idle_DC_Motor); //装载//Work▓Idle_DC_Motor 测试(工作时)
		}
		else
		{
			G_DC_WorkState = STATE_Positive_DC_Motor;
			Initial_WorkState(WORK_Positive_DC_Motor); //装载//Work▓Positive_DC_Motor 测试(工作时)
		}
	}

	if(Detect_MatrixKey_2()) //"数字2键"//2.Reverse Rotation
	{
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
		
		if(G_DC_WorkState == STATE_Positive_DC_Motor)
		{
			G_DC_WorkState = STATE_Reverse_DC_Motor;
			Initial_WorkState(WORK_Idle_DC_Motor); //装载//Work▓Idle_DC_Motor 测试(工作时)
		}
		else 
		{
			G_DC_WorkState = STATE_Reverse_DC_Motor;
			Initial_WorkState(WORK_Reverse_DC_Motor); //装载//Work▓Reverse_DC_Motor 测试(工作时)
		}
	}

	if(Detect_MatrixKey_3()) //"数字3键"//3.Stop DC-Moter
	{
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
		G_DC_WorkState = STATE_Stop_DC_Motor;
		Initial_WorkState(WORK_Stop_DC_Motor); //装载//Work▓Stop_DC_Motor 测试(工作时)
	}


////////////////////////////////////////////////////////////////////////////
//==**显示处理**========================================//
	if(F_500ms_Reflash_DC_Motor)  //500ms 刷新"转速" ("DC_Motor 直流电机")
	{
		F_500ms_Reflash_DC_Motor = 0;

		speed = (G_DC_Speed * 60) / 3;  // 将转速脉冲转成"实际转速值"r/min单位

		
////////////////////////////////////////////////////////////////////////////
//--**显示处理:  "彩屏LCD_TFT" **------------------------------------//
			//在"测试电机"显示速度给定电压值: 电位计Potentiometer 实时"电压值"
		Disp_Potentiometer_Motor();

		Disp_Speed_DC_Motor();//在"测试DC_Motor"显示电机速度

////////////////////////////////////////////////////////////////////////////
//--**显示处理:  "动态数码管LED_Segment"**-----------------------//
	//电位计显示相关
		a = (unsigned char)(G_LastAdResult/1000);
		b = (unsigned char)((G_LastAdResult % 1000)/100);
//c = (unsigned char)(G_LastAdResult % 100)/10;
		//if(G_LastAdResult < 30) c = 0; //在电位器旋到最小值时，显示电压会在0.01,0.02,.000之间显示，加上这条，可以在电位器旋到最小值时，显示0.00

	//转速显示相关
		if(G_DC_WorkState  == STATE_Positive_DC_Motor)  //正转显示处理
		{
			s5 = DISP_OFF_LedSeg;//显示"暗码"(不显示0)
			s4 = (unsigned char)(speed/1000);
			s3 = (unsigned char)((speed % 1000)/100);
			s2 = (unsigned char)(speed % 100)/10;
			s1 = (unsigned char)(speed % 10);
			if((s4 == 0)&&(s3 == 0)&&(s2 == 0)) s2 = DISP_OFF_LedSeg;	
			if((s4 == 0)&&(s3 == 0)) s3 = DISP_OFF_LedSeg;
			if(s4 == 0) s4 = DISP_OFF_LedSeg; //显示"暗码"(不显示0)
		}
		else if(G_DC_WorkState  == STATE_Reverse_DC_Motor) //反转显示处理
		{
			s5 = DISP_OFF_LedSeg;//显示"暗码"(不显示0)
			s4 = (unsigned char)(speed/1000);
			s3 = (unsigned char)((speed % 1000)/100);
			s2 = (unsigned char)(speed % 100)/10;
			s1 = (unsigned char)(speed % 10);
			if((s4 == 0)&&(s3 == 0)&&(s2 == 0))
			{
				s5 = DISP_OFF_LedSeg;//显示"暗码"(不显示0)
			 	s4 = DISP_OFF_LedSeg;//显示"暗码"(不显示0)
				s3 = DISP_OFF_LedSeg;//显示"暗码"(不显示0)
				s2 = DISP_Minus_LedSeg; //显示"负号"(不显示0)
			}
			if((s4 == 0)&&(s3 == 0))
			{
				s5 = DISP_OFF_LedSeg;//显示"暗码"(不显示0)
			 	s4 = DISP_OFF_LedSeg;//显示"暗码"(不显示0)
				s3 = DISP_Minus_LedSeg; //显示"负号"(不显示0)
			}
			if(s4 == 0) 
			{
				s5 = DISP_OFF_LedSeg;//显示"暗码"(不显示0)
				s4 = DISP_Minus_LedSeg; //显示"负号"(不显示0)		
			}
			else if(s4 != 0) s5 = DISP_Minus_LedSeg; //显示"负号"(不显示0)	
				
		}
		Disp_LED_Segment(0,8,a,b,DISP_OFF_LedSeg,s5,s4,s3,s2,s1);
	}

////////////////////////////////////////////////////////////////////////////
//--**IO按键 处理**---------------------------------------------------//
	Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"

}



/****************************************************************************
*函数名-Function:	void Deal_MAIN_TMP006_Temperature(void)
*描述- Description:	//处理//Main█TMP006_Temperature 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_MAIN_TMP006_Temperature(void) //处理//Main█TMP006_Temperature 菜单选择(工作时)
{
	int b = 0;
    unsigned char a4,a3,a2,a1;



////////////////////////////////////////////////////////////////////////////
//==**模块 处理**===========================================//
	b = (int)(TMP006_Temperature * 10);  //将"实际温度值"放到10倍，用于显示
	if(b < 0)  //负温度值
	{
		b  = (-1) * b;
		a4 =  b / 1000; 
		a3 =  b / 100;
		a2 = (b / 10) % 10;
		a1 =  b % 10;	

		if((a4 == 0)&&(a3 == 0))
		{
			a4 = DISP_OFF_LedSeg;//显示"暗码"(不显示0)
			a3 = DISP_Minus_LedSeg; //显示"负号"(不显示0)
		}
		if(a4 == 0) a4 = DISP_Minus_LedSeg; //显示"负号"(不显示0)		
	}
	else //正温度值
	{
		a4 =  b / 1000; 
		a3 = (b % 1000) / 100;
		a2 = (b % 100) / 10;
		a1 =  b % 10;	
		
		if((a4 == 0)&&(a3 == 0)) a3 = DISP_OFF_LedSeg;
		if(a4 == 0) a4 = DISP_OFF_LedSeg; //显示"暗码"(不显示0)
	}
		//在数码管上，显示"温度"
	Disp_LED_Segment(0,4,DISP_OFF_LedSeg,DISP_OFF_LedSeg,a4,a3,a2,a1,DISP_OFF_LedSeg,DISP_C_LedSeg);

	if(F_500ms_TemperatureInTest)
	{
		F_500ms_TemperatureInTest = 0;
		Disp_TMP006_TemperatureInTest();//在LCD_TFT上，显示"温度"
	}

////////////////////////////////////////////////////////////////////////////
//==**按键 处理**=======================================//

////////////////////////////////////////////////////////////////////////////
//--**IO按键 处理**---------------------------------------------------//
	Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"

////////////////////////////////////////////////////////////////////////////
//--**矩阵按键 处理**-----------------------------------------------//

}


/****************************************************************************
*函数名-Function:	void Deal_MAIN_TMP100_Temperature(void)
*描述- Description:	//处理//Main█TMP100_Temperature 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_MAIN_TMP100_Temperature(void) //处理//Main█TMP100_Temperature 菜单选择(工作时)
{

}




/****************************************************************************
*函数名-Function:	void Deal_MAIN_IrDA_UART(void)
*描述- Description:	//处理//Main█IrDA_UART 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_MAIN_IrDA_UART(void) //处理//Main█IrDA_UART 菜单选择(工作时)
{
//Close_LCD_Segment(); //关闭"段式LCD_Segment"

////////////////////////////////////////////////////////////////////////////
//==**按键 处理**=======================================//

	////////////////////////////////////////////////////////////////////////////
	//==**模块 处理**===========================================//
	Deal_IrDA_UART();	//处理 "IrDA_UART  红外串口通信"
	
	mTurn_LED_YELLOW;  //"翻转" LED_YELLOW //表示正在进行红处数据通信

	///////////////////////////////////////////////////////////////////////////
	if(G_RxData_IrDA == '1')	//如果红外接收到的数据为"A"
	{
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
			//接收到正确的红外信号，数码管全亮
		Disp_LED_Segment(0,0,DISP_I_LedSeg,DISP_r_LedSeg,DISP_d_LedSeg,DISP_A_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_1_LedSeg);
	}
	else
	{
		Disp_LED_Segment(0,0,DISP_I_LedSeg,DISP_r_LedSeg,DISP_d_LedSeg,DISP_A_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
	}
	
	///////////////////////////////////////////////////////////////////
	if(F_500ms_IrDA)
	{
		F_500ms_IrDA = 0;
		Disp_IrDA_Test(); //显示IrDA是否收到数据
	}
	 
////////////////////////////////////////////////////////////////////////////
//--**IO按键 处理**---------------------------------------------------//
	Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"

}



/****************************************************************************
*函数名-Function:	void Deal_MAIN_RS232_UART(void)
*描述- Description:	//处理//Main█RS232_UART 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_MAIN_RS232_UART(void) //处理//Main█RS232_UART 菜单选择(工作时)
{
////////////////////////////////////////////////////////////////////////////
//==**模块 处理**===========================================//
////////////////////////////////////////////////////////////////////////////
//==**按键 处理**=======================================//
	Initial_RS232_UART();  //初始化设置:  "RS232_UART  串口通信"

	while(1)
	{
		if(F_250ms_Turn)
		{
			mOpen_LED_GREEN; 
		}
		else
		{
			mClose_LED_GREEN;
		}
	

	////////////////////////////////////////////////////////////////////////////
	//--**矩阵按键 处理**-----------------------------------------------//
		if(Detect_MatrixKey_1())
		{
			mTurn_LED_YELLOW;  //翻转黄色LED
			F_EnUpdate_RS232 = 1;
			Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间

			F_HL_TestLine03 = YES;
			F_Update_TestLine03 = YES;
			
			Open_Timing_Task(500);
			
			Deal_RS232_UART(); //处理 "RS232 串口通信"			
		}
		
		if((!F_Timing) && F_EnUpdate_RS232) 
		{
			F_EnUpdate_RS232 = 0;
			F_Update_TestLine03 = YES;
		}


	
	////////////////////////////////////////////////////////////////////////////
	//--**用于退出死循环**--------------------------------------------//
		if(G_RxData_RS232 == '1')
		{
			G_RxData_RS232 = 0xFF;	//清接收缓存

			Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
			
			WaitingDelayMs(50);//延时50ms(因为，UART与其他模块引脚复用，不延时的话，有些数据就发不出去)
				//接收到'1'，数码管显示'1'
			Disp_LED_Segment(0,0,DISP_2_LedSeg,DISP_3_LedSeg,DISP_2_LedSeg,DISP_OFF_LedSeg,DISP_Minus_LedSeg,DISP_Minus_LedSeg,DISP_OFF_LedSeg,DISP_1_LedSeg);
			Disp_RS232_Char_1(); //显示RS232收到数据"1"		
//break; 
		}
		else if(G_RxData_RS232 == '2')
		{
			G_RxData_RS232 = 0xFF;	//清接收缓存

			Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
			
			WaitingDelayMs(50);//延时50ms(因为，UART与其他模块引脚复用，不延时的话，有些数据就发不出去)
				//接收到'2'，数码管显示'2'
			Disp_LED_Segment(0,0,DISP_2_LedSeg,DISP_3_LedSeg,DISP_2_LedSeg,DISP_OFF_LedSeg,DISP_Minus_LedSeg,DISP_Minus_LedSeg,DISP_OFF_LedSeg,DISP_2_LedSeg);
			Disp_RS232_Char_2(); //显示RS232收到数据"2"	
//break; 
		}
		else if(G_RxData_RS232 != 0xFF)
		{
			G_RxData_RS232 = 0xFF;	//清接收缓存
			WaitingDelayMs(50);//延时50ms(因为，UART与其他模块引脚复用，不延时的话，有些数据就发不出去)
				//接收到'其他字符'，数码管显示'全暗'
			Disp_LED_Segment(0,0,DISP_2_LedSeg,DISP_3_LedSeg,DISP_2_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
			Disp_RS232_None(); //清显示RS232收到数据
//break; 
		}

		Deal_Main_Loop();  //主循环中的，循环执行的操作(显示、采样)

	////////////////////////////////////////////////////////////////////////////
	//--**IO按键 处理**---------------------------------------------------//
		Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"

		if(G_KeyCnt != 13) break;  //用于退出死循环
	}

////////////////////////////////////////////////////////////////////////////
//--**IO按键 处理**---------------------------------------------------//
	Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"

}



/****************************************************************************
*函数名-Function:	void Deal_MAIN_RS485_UART(void)
*描述- Description:	//处理//Main█RS485_UART 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_MAIN_RS485_UART(void) //处理//Main█RS485_UART 菜单选择(工作时)
{
////////////////////////////////////////////////////////////////////////////
//==**模块 处理**===========================================//
////////////////////////////////////////////////////////////////////////////
//==**按键 处理**=======================================//

	Initial_RS485_UART();  //初始化设置:  "RS485_UART  串口通信"
	
	while(1)
	{		
		if(F_250ms_Turn)
		{
			mOpen_LED_GREEN; 
		}
		else
		{
			mClose_LED_GREEN;
		}

	////////////////////////////////////////////////////////////////////////////
	//--**矩阵按键 处理**-----------------------------------------------//
		if(Detect_MatrixKey_1())
		{
			F_EnUpdate_RS485 = 1;
			Open_Buzzer(BuzzTime_Key);	//按键有效时，让蜂鸣叫指定时间
			F_HL_TestLine03 = YES;
			F_Update_TestLine03 = YES;
			F_Update_TestLine04 = YES;

			Open_Timing_Task(500);

			Sent_OneByte_RS485_UART('1');  //RS485通过UART发送一个字节数据	
			mTurn_LED_YELLOW;  //翻转黄色LED
		}
		
		if(Detect_MatrixKey_2())
		{
			F_EnUpdate_RS485 = 1;
			Open_Buzzer(BuzzTime_Key);	//按键有效时，让蜂鸣叫指定时间
			F_HL_TestLine04 = YES;
			F_Update_TestLine03 = YES;
			F_Update_TestLine04 = YES;

			Open_Timing_Task(500);

			Sent_OneByte_RS485_UART('2');  //RS485通过UART发送一个字节数据	
			mTurn_LED_YELLOW;  //翻转黄色LED
		}

		if((!F_Timing) && F_EnUpdate_RS485) 
		{
			F_EnUpdate_RS485 = 0;
			F_Update_TestLine03 = YES;
			F_Update_TestLine04 = YES;
		}

	////////////////////////////////////////////////////////////////////////////
	//--**用于退出死循环**--------------------------------------------//
		if(G_RxData_RS485 == '1')
		{
			G_RxData_RS485 = 0xFF;  //清接收缓存
			
			Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
			
				//接收到'1'，数码管显示'1'
			Disp_LED_Segment(0,0,DISP_4_LedSeg,DISP_8_LedSeg,DISP_5_LedSeg,DISP_OFF_LedSeg,DISP_Minus_LedSeg,DISP_Minus_LedSeg,DISP_OFF_LedSeg,DISP_1_LedSeg);
			Disp_RS485_Char_1(); //显示RS485收到数据"1"		
//break; 
		}
		else if(G_RxData_RS485 == '2')
		{
			G_RxData_RS485 = 0xFF;	//清接收缓存

			Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
			
				//接收到'2'，数码管显示'2'
			Disp_LED_Segment(0,0,DISP_4_LedSeg,DISP_8_LedSeg,DISP_5_LedSeg,DISP_OFF_LedSeg,DISP_Minus_LedSeg,DISP_Minus_LedSeg,DISP_OFF_LedSeg,DISP_2_LedSeg);
			Disp_RS485_Char_2(); //显示RS485收到数据"2"	
	//break; 
		}

		Deal_Main_Loop();  //主循环中的，循环执行的操作(显示、采样)

		////////////////////////////////////////////////////////////////////////////
		//--**IO按键 处理**---------------------------------------------------//
		Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"
			
		if(G_KeyCnt != 14) break;  
	}

////////////////////////////////////////////////////////////////////////////
//--**IO按键 处理**---------------------------------------------------//
	Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"

}



/****************************************************************************
*函数名-Function:	void Deal_MAIN_CC1101_Test(void)
*描述- Description:	//处理//Main█CC1101_Test 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_MAIN_CC1101_Test(void) //处理//Main█CC1101_Test 菜单选择(工作时)
{
////////////////////////////////////////////////////////////////////////////
//==**按键 处理**=======================================//
	Initial_CC1101();  //初始化设置:  "CC1101 低功耗射频收发器"

	while(1)
	{		
		if(F_250ms_Turn)
		{
			mOpen_LED_GREEN; 
		}
		else
		{
			mClose_LED_GREEN;
		}
	
	////////////////////////////////////////////////////////////////////////////
	//==**模块 处理**===========================================//
		Deal_CC1101();	//处理"CC1101 低功耗射频收发器"

	////////////////////////////////////////////////////////////////////////////
	//--**矩阵按键 处理**-----------------------------------------------//
	
		if(F_EnUpdate_CC1101) 
		{
			F_EnUpdate_CC1101 = 0;
			F_Update_TestLine03 = YES;
			F_Update_TestLine04 = YES;
			break; 
		}

	
		if( (Detect_MatrixKey_1())&& (!F_Timing))
		{
			mTurn_LED_YELLOW;  //翻转黄色LED
			F_EnUpdate_CC1101 = 1;
			Open_Buzzer(BuzzTime_Key);	//按键有效时，让蜂鸣叫指定时间	
			F_HL_TestLine03 = YES;
			F_Update_TestLine03 = YES;
			F_Update_TestLine04 = YES;
			
			Open_Timing_Task(1000);
			
			Send_OneByte_CC1101('1'); //发送一个字节数据-- "CC1101 低功耗射频收发器"
			break;
		}
		if( (Detect_MatrixKey_2())&& (!F_Timing))
		{
			mTurn_LED_YELLOW;   //翻转黄色LED
			F_EnUpdate_CC1101 = 1;
			Open_Buzzer(BuzzTime_Key);	//按键有效时，让蜂鸣叫指定时间
			F_HL_TestLine04 = YES;
			F_Update_TestLine03 = YES;
			F_Update_TestLine04 = YES;

			Open_Timing_Task(1000);

			Send_OneByte_CC1101('2'); //发送一个字节数据-- "CC1101 低功耗射频收发器"
			break;
		}


	////////////////////////////////////////////////////////////////////////////
	//--**用于退出死循环**--------------------------------------------//
		if(G_RxData_CC1101 == '1')
		{
			G_RxData_CC1101 = 0xFF;	//清接收缓存
			Open_Buzzer(BuzzTime_Key);	//按键有效时，让蜂鸣叫指定时间
			
				//接收到'1'，数码管显示'1'
			Disp_LED_Segment(0,0,DISP_C_LedSeg,DISP_C_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_0_LedSeg,DISP_1_LedSeg,DISP_OFF_LedSeg,DISP_1_LedSeg);
			Disp_CC1101_Char_1(); //显示CC1101收到数据"1" 	
			break; 
		}
		else if(G_RxData_CC1101 == '2')
		{
			G_RxData_CC1101 = 0xFF;	//清接收缓存
			Open_Buzzer(BuzzTime_Key);	//按键有效时，让蜂鸣叫指定时间

				//接收到'2'，数码管显示'2'
			Disp_LED_Segment(0,0,DISP_C_LedSeg,DISP_C_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_0_LedSeg,DISP_1_LedSeg,DISP_OFF_LedSeg,DISP_2_LedSeg);
			Disp_CC1101_Char_2(); //显示CC1101收到数据"2" 
			break; 
		}
		
	F_En_Scan_MatrixKey = NO;  //禁止扫描"矩阵按键扫描"
	Scan_MatrixKey(); //"矩阵键盘"扫描，5ms扫描一次按键(中断里) 	
	Deal_LED_Segment();//"数码管LED_Segment": 处理不同"工作模式"
	F_En_Scan_MatrixKey = YES;  //使能"矩阵按键扫描"




	////////////////////////////////////////////////////////////////////////////
	//--**IO按键 处理**---------------------------------------------------//
		Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"

		if(G_KeyCnt != 15) break;  
	}

////////////////////////////////////////////////////////////////////////////
//--**IO按键 处理**---------------------------------------------------//
	Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"

}


/****************************************************************************
*函数名-Function:	void Deal_MAIN_SD_Card_Test(void)
*描述- Description:		//处理//Main█SD_Card_Test 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_MAIN_SD_Card_Test(void) //处理//Main█SD_Card_Test 菜单选择(工作时)
{
	char keyVal[1];

////////////////////////////////////////////////////////////////////////////
//==**按键 处理**=======================================//
	Initial_SD_Card();  //初始化设置: "SD_Card SD卡"
//Initial_Osccon_SD_Card(); //初始化晶振--"SD_Card SD卡"
		
	while(1)
	{		
		if(F_250ms_Turn)
		{
			mOpen_LED_GREEN; 
		}
		else
		{
			mClose_LED_GREEN;
		}

	////////////////////////////////////////////////////////////////////////////
	//--**矩阵按键 处理**-----------------------------------------------//
		F_En_Scan_MatrixKey = NO;  //禁止扫描"矩阵按键扫描"
		Scan_MatrixKey(); //"矩阵键盘"扫描，5ms扫描一次按键(中断里) 	
		Deal_LED_Segment();//"数码管LED_Segment": 处理不同"工作模式"
		F_En_Scan_MatrixKey = YES;  //使能"矩阵按键扫描"
	
		if(G_MatrixKeyValue != M_NullMatrixKey)
		{
			switch(G_MatrixKeyValue)
			{		
				case MatrixKey_0:  //"数字0键"	
				case MatrixKey_1:  //"数字1键"		
				case MatrixKey_2:  //"数字2键"		
				case MatrixKey_3:  //"数字3键"		
				case MatrixKey_4:  //"数字4键"		
				case MatrixKey_5:  //"数字5键"					
				case MatrixKey_6:  //"数字6键"			
				case MatrixKey_7:  //"数字7键"			
				case MatrixKey_8:  //"数字8键"			
				case MatrixKey_9:  //"数字9键"
					G_Data_SD_Write = G_MatrixKeyValue;
					Open_Buzzer(BuzzTime_Key);	//按键有效时，让蜂鸣叫指定时间
					Disp_LED_Segment(0,0,DISP_5_LedSeg,DISP_d_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,G_Data_SD_Write,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
					Deal_LED_Segment();//"数码管LED_Segment": 处理不同"工作模式"
					
					keyVal[0] = G_MatrixKeyValue+48;
					G_MatrixKeyValue = M_NullMatrixKey;

					WriteFile("SD_write.txt", (char *)keyVal, 1);

					if(SD_State == STATE_SD_ERROR)
					{
						SD_State = STATE_SD_IDLE;
					}
					else
					{
						GetFile("SD_write.txt");
						
						G_Data_SD_Read = SD_Buf[SD_Num-1]-48;
						
						Open_Buzzer(BuzzTime_Key);	//按键有效时，让蜂鸣叫指定时间
						
						
						Disp_LED_Segment(0,0,DISP_5_LedSeg,DISP_d_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,G_Data_SD_Write,DISP_OFF_LedSeg,DISP_OFF_LedSeg,G_Data_SD_Read);	
						Deal_LED_Segment();//"数码管LED_Segment": 处理不同"工作模式"
						mTurn_LED_YELLOW;  //翻转黄色LED
					}
					Deal_LCD_TFT();//LCD_TFT 显示控制//只更新内容变化的显示部分
					break;
					
				default:	break;		
			}
		}



	////////////////////////////////////////////////////////////////////////////
	//--**IO按键 处理**---------------------------------------------------//
		Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"
	
		if(G_KeyCnt != 16)
		{
				//因为SD卡的相关测试时，修改了晶振，故这里重新初使化,还原之前的晶振配置
			//Osccon_Initial();//晶振初始化函数:配置相关晶振参数
			break;  
		}
			
	}

}



/****************************************************************************
*函数名-Function:	void Deal_MAIN_MassStorage_Test(void)
*描述- Description:	//处理//Main█MassStorage_Test 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_MAIN_MassStorage_Test(void) //处理//Main█MassStorage_Test 菜单选择(工作时)
{

	////////////////////////////////////////////////////////////////////////////
	//--**矩阵按键 处理**-----------------------------------------------//
	if(Detect_MatrixKey_1())
	{
		mOpen_LED_YELLOW;  //打开黄色LED
		Open_Buzzer(BuzzTime_Key);	//按键有效时，让蜂鸣叫指定时间

F_HL_TestLine03 = YES;
F_Update_TestLine03 = YES;
F_Update_TestLine04 = YES;
		
Deal_LCD_TFT();//LCD_TFT 显示控制//只更新内容变化的显示部分
		
		Initial_MainState(MAIN_MassStorage_USB); //装载//Main█MassStorage_USB 菜单选择(工作时)	
	}
	
	
	if(Detect_MatrixKey_2())
	{
		mClose_LED_YELLOW;  //关闭黄色LED
		Open_Buzzer(BuzzTime_Key);	//按键有效时，让蜂鸣叫指定时间


		Disable_USB_SD_Card_Reader();  //禁用:	"USB_SD_Card_Reader 读卡器(USB-SD卡)"
		
		F_HL_TestLine04 = YES;
		F_Update_TestLine03 = YES;
		F_Update_TestLine04 = YES;

		Deal_LCD_TFT();//LCD_TFT 显示控制//只更新内容变化的显示部分
	}	

////////////////////////////////////////////////////////////////////////////
//--**IO按键 处理**---------------------------------------------------//
	Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"

}





/****************************************************************************
*函数名-Function:	void Deal_MAIN_MassStorage_USB(void)
*描述- Description:	  	处理 //Main█MassStorage_USB 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_MAIN_MassStorage_USB(void) //处理 //Main█MassStorage_USB 菜单选择(工作时)
{
	Initial_USB_SD_Card_Reader();  //初始化设置:  "USB_SD_Card_Reader 读卡器(USB-SD卡)"
	
	while(1)
	{		
		if(F_250ms_Turn)
		{
			mOpen_LED_GREEN; 
		}
		else
		{
			mClose_LED_GREEN;
		}
		

		////////////////////////////////////////////////////////////////////////////
		//--**矩阵按键 处理**-----------------------------------------------//

		if(Detect_MatrixKey_1())
		{
			mOpen_LED_YELLOW;  //打开黄色LED
			Open_Buzzer(BuzzTime_Key);	//按键有效时，让蜂鸣叫指定时间
			
			Disp_LED_Segment(0,0,DISP_U_LedSeg,DISP_5_LedSeg,DISP_b_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_1_LedSeg);

			F_HL_TestLine03 = YES;
			F_Update_TestLine03 = YES;
			F_Update_TestLine04 = YES;
					
			Deal_LCD_TFT();//LCD_TFT 显示控制//只更新内容变化的显示部分
					
			Initial_USB_SD_Card_Reader();  //初始化设置:  "USB_SD_Card_Reader 读卡器(USB-SD卡)"
		}

		if(Detect_MatrixKey_2())
		{
			Open_Buzzer(BuzzTime_Key);	//按键有效时，让蜂鸣叫指定时间
			mClose_LED_YELLOW;  //关闭黄色LED

			Disable_USB_SD_Card_Reader();  //禁用:	"USB_SD_Card_Reader 读卡器(USB-SD卡)"

			Disp_LED_Segment(0,0,DISP_U_LedSeg,DISP_5_LedSeg,DISP_b_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_0_LedSeg);

			F_HL_TestLine04 = YES;
			F_Update_TestLine03 = YES;
			F_Update_TestLine04 = YES;

			Deal_LCD_TFT();//LCD_TFT 显示控制//只更新内容变化的显示部分
		}	

		Deal_USB_SD_Card_Reader();	//处理"USB_SD_Card_Reader 读卡器(USB-SD卡)"


	F_En_Scan_MatrixKey = NO;  //禁止扫描"矩阵按键扫描"
	Scan_MatrixKey(); //"矩阵键盘"扫描，5ms扫描一次按键(中断里) 	
	Deal_LED_Segment();//"数码管LED_Segment": 处理不同"工作模式"
	F_En_Scan_MatrixKey = YES;	//使能"矩阵按键扫描"
	

		if(G_KeyCnt != 17)
		{
			Open_Buzzer(BuzzTime_Key);	//按键有效时，让蜂鸣叫指定时间
			mClose_LED_YELLOW;	//关闭黄色LED
			
			Disable_USB_SD_Card_Reader();  //禁用:	"USB_SD_Card_Reader 读卡器(USB-SD卡)"
			
			break;	
		}	
	////////////////////////////////////////////////////////////////////////////
	//--**IO按键 处理**---------------------------------------------------//
		Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"

	}

}



/****************************************************************************
*函数名-Function:	void Deal_MAIN_MassStorage_USB(void)
*描述- Description:	  	处理 //Main█MassStorage_USB 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*******************************************************
void Deal_MAIN_MassStorage_USB(void) //处理 //Main█MassStorage_USB 菜单选择(工作时)
{
	Initial_USB_SD_Card_Reader();  //初始化设置:  "USB_SD_Card_Reader 读卡器(USB-SD卡)"
	
	while(1)
	{		
		if(F_250ms_Turn)
		{
			mOpen_LED_GREEN; 
		}
		else
		{
			mClose_LED_GREEN;
		}
		
		Deal_USB_SD_Card_Reader();	//处理"USB_SD_Card_Reader 读卡器(USB-SD卡)"

		////////////////////////////////////////////////////////////////////////////
		//--**矩阵按键 处理**-----------------------------------------------//

		if(Detect_MatrixKey_2())
		{
			Disable_USB_SD_Card_Reader();  //禁用:	"USB_SD_Card_Reader 读卡器(USB-SD卡)"

		WaitingDelayMs(1000);
			//因为退出USB时,发现会影响LCD_TFT 显示。
			//故，退出USB ,  进行软件复位，重新开机
		mReset_Soft;   //"软件复位"

			mClose_LED_YELLOW;  //关闭黄色LED
		}	
**********************/

/****************
if(Detect_MatrixKey_3())
{
Disable_USB_SD_Card_Reader();  //禁用:	"USB_SD_Card_Reader 读卡器(USB-SD卡)"
USB_reset();

WaitingDelayMs(5000);
		
//mDisable_GIE;  //禁止总中断



//因为USB 的相关测试时，修改了晶振，故这里重新初使化,还原之前的晶振配置
Osccon_Initial();//晶振初始化函数:配置相关晶振参数
Timer2_Initial(); //定时器A2初始化设置(用于系统每1ms自动中断一次)
//mEnable_GIE;	// 开启总中断

SPI_B_Initial_LCD_TFT();	//SPI_B模块初始化:端口初始化、配置SPI (LCD_TFT )
WaitingDelayMs(5000);
break;	

}
**************/
	/****************

	////////////////////////////////////////////////////////////////////////////
	//--**IO按键 处理**---------------------------------------------------//
		Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"

		if(G_KeyCnt != 18)
		{
		
//mDisable_GIE;  //禁止总中断
//WaitingDelayMs(3000);

	//Disable_USB_SD_Card_Reader();  //禁用:	"USB_SD_Card_Reader 读卡器(USB-SD卡)"
	//USB_reset();

//因为USB 的相关测试时，修改了晶振，故这里重新初使化,还原之前的晶振配置
//Osccon_Initial();//晶振初始化函数:配置相关晶振参数
//Timer2_Initial(); //定时器A2初始化设置(用于系统每1ms自动中断一次)
//SPI_B_Initial_LCD_TFT();	//SPI_B模块初始化:端口初始化、配置SPI (LCD_TFT )

//WaitingDelayMs(3000); 	
//mEnable_GIE;  // 开启总中断



			WaitingDelayMs(1000);
				//因为退出USB时,发现会影响LCD_TFT 显示。
				//故，退出USB ,  进行软件复位，重新开机
			mReset_Soft;   //"软件复位"
			break;	
			
		}	
	}

}
**************/



/****************************************************************************
*函数名-Function:	void Deal_MainState(void)
*描述- Description:	 "处理"各系统Main█"状态"下的事务 (状态机)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_MainState(void)
{
	switch(G_MainState) 
	{
////////////////////////////////////////////////////////////////////////////
//==**待机\常用状态值: 0x01--0xFF **=======================//
////////////////////////////////////////////////////////////////////////////

case MAIN_Restart:  //Main█ 重启，并系统自检--Restart Self-Test     
	break;

case MAIN_Self_Check:	//Main█系统自检状态
	Deal_Main_Self_Check();  //处理//Main█系统自检状态
	break;	


////////////////////////////////////////////////////////////////////////////
//==**主菜单状态值: 0x100--0x1FF **=========================//
////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	//--**基本参数: "时间修改"菜单0x200--0x21F **-------------------//
	////////////////////////////////////////////////////////////////////////////
case MAIN_ModifyTime:  //Main█"实时时间"修改状态
	Deal_Main_ModifyTime(); //处理//Main█"实时时间"修改状态
	break;

////////////////////////////////////////////////////////////////////////////
//==**工作"菜单"状态值: 0x7000--0x7FFF**====================//
////////////////////////////////////////////////////////////////////////////

case MAIN_Working_State:	//Main█进入工作状态(工作时)
	
	break;	
	
case MAIN_Basic_Settings:	//Main█Basic_Settings菜单选择(工作时)
	Deal_MAIN_Basic_Settings(); //处理//Main█Basic_Settings菜单选择(工作时)
	break;

case MAIN_Basic_Check:	//Main█Basic_Check 菜单选择(工作时)
	Deal_MAIN_Basic_Check(); //处理//Main█Basic_Check 菜单选择(工作时)
	break;

case MAIN_LCD_TFT_Test:	//Main█LCD_TFT_Test 菜单选择(工作时)
	Deal_MAIN_LCD_TFT_Test(); //处理//Main█LCD_TFT_Test 菜单选择(工作时)
	break;

case MAIN_MatrixKey_Test:	//Main█MatrixKey_Test 菜单选择(工作时)
	Deal_MAIN_MatrixKey_Test(); //处理//Main█MatrixKey_Test 菜单选择(工作时)
	break;

case MAIN_TouchPads_Test:	//Main█TouchPads_Test 菜单选择(工作时)
	Deal_MAIN_TouchPads_Test(); //处理//Main█TouchPads_Test 菜单选择(工作时)
	break;

case MAIN_INA21x_Current_Test:  //Main█INA21x_Current_Test 菜单选择(工作时)
	Deal_INA210_Current_Test(); //处理//Main█INA210_Current_Test 菜单选择(工作时)
	break;

case MAIN_TMP006_Temperature:  //Main█TMP006_Temperature 菜单选择(工作时)
	Deal_MAIN_TMP006_Temperature(); //处理//Main█TMP006_Temperature 菜单选择(工作时)
	break;

case MAIN_TMP100_Temperature:  //Main█TMP100_Temperature 菜单选择(工作时)
	Deal_MAIN_TMP100_Temperature(); //处理//Main█TMP100_Temperature 菜单选择(工作时)
	break;

case MAIN_Potentiometer_Test:	//Main█Potentiometer_Test 菜单选择(工作时)
	Deal_MAIN_Potentiometer_Test(); //处理//Main█Potentiometer_Test 菜单选择(工作时)
	break;

case MAIN_DC_Motor_Test:  //Main█DC_Motor_Test 菜单选择(工作时) 
	Deal_MAIN_DC_Motor_Test(); //处理///Main█DC_Motor_Test 菜单选择(工作时) 
	break;

case MAIN_Step_Motor_Test:  //Main█Step_Motor_Test 菜单选择(工作时) 
	Deal_MAIN_Step_Motor_Test(); //处理//Main█Step_Motor_Test 菜单选择(工作时) 
	break;

case MAIN_NTC_HR202_Test:  //Main█NTC_HR202_Test(温湿度) 菜单选择(工作时)
	Deal_MAIN_NTC_HR202_Test(); //处理//Main█NTC_HR202_Test(温湿度) 菜单选择(工作时)
	break;

case MAIN_IrDA_UART:  //Main█IrDA_UART 菜单选择(工作时)
	Deal_MAIN_IrDA_UART(); //处理//Main█IrDA_UART 菜单选择(工作时)
	break;

case MAIN_RS232_UART:  //Main█RS232_UART 菜单选择(工作时)
	Deal_MAIN_RS232_UART(); //处理//Main█RS232_UART 菜单选择(工作时)
	break;

case MAIN_RS485_UART:  //Main█RS485_UART 菜单选择(工作时)
	Deal_MAIN_RS485_UART(); //处理//Main█RS485_UART 菜单选择(工作时)
	break;





case MAIN_CC1101_Test:  //Main█CC1101_Test 菜单选择(工作时)
	Deal_MAIN_CC1101_Test(); //处理//Main█CC1101_Test 菜单选择(工作时)
	break;

case MAIN_SD_Card_Test: //Main█SD_Card_Test 菜单选择(工作时)
	Deal_MAIN_SD_Card_Test(); //处理//Main█SD_Card_Test 菜单选择(工作时)
	break;

case MAIN_MassStorage_Test:	//Main█MassStorage_Test 菜单选择(工作时)
	Deal_MAIN_MassStorage_Test(); //处理//Main█MassStorage_Test 菜单选择(工作时)
	break;

case MAIN_MassStorage_USB:  //Main█MassStorage_USB 菜单选择(工作时)
	Deal_MAIN_MassStorage_USB(); //处理 //Main█MassStorage_USB 菜单选择(工作时)
	break;


////////////////////////////////////////////////////////////////////////////
	default:
		break;
	}
}





/****************************************************************************
*函数名-Function:	void Deal_WorkState(void)
*描述- Description:	 "处理"各工作Work▓"状态"下的事务 (状态机)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_WorkState(void)
{

////////////////////////////////////////////////////////////////////////////
//==**工作运行: **0x8000--0x8FFF** ===========================//
////////////////////////////////////////////////////////////////////////////

	switch(G_WorkState) 
	{
////////////////////////////////////////////////////////////////////////////
//==**"测试时"的空闲状态** ============================//

case WORK_Test_IdleState: //Work▓"测试时"的空闲状态(工作时)

	break;

////////////////////////////////////////////////////////////////////////////
//==**"相关测试" ( 工作菜单)** ===========================//

case WORK_Self_Check: //Work▓Self_Check 测试(工作时)
	break;	

case WORK_Led_Diode_Test: //Work▓Led_Diode_Test 测试(工作时)
////////////////////////////////////////////////////////////////////////////
//==**动作处理(相应的IO口输出)**=======================//
	SOS_Function();  //Led_Diode(发光二极管) 实现SOS 求救功能
	break;	
	
case WORK_LED_Segment_Test: //Work▓LED_Segment_Test 测试(工作时)
////////////////////////////////////////////////////////////////////////////
//==**动作处理(相应的IO口输出)**=======================//
	if(F_500ms_LedSeg) //"动态数码管LED_Segment" 显示"间隔"时间
	{ 
		F_500ms_LedSeg = 0;
		
			//"所有""动态数码管LED_Segment" : 同时"循环"显示"相同"字符
		Disp_LED_Segment(0,0,G_LedSeg_Cnt,G_LedSeg_Cnt,G_LedSeg_Cnt,G_LedSeg_Cnt,G_LedSeg_Cnt,G_LedSeg_Cnt,G_LedSeg_Cnt,G_LedSeg_Cnt);

		G_LedSeg_Cnt ++;//"动态数码管LED_Segment"中用到的计数器(用于字符循环显示)
		if(G_LedSeg_Cnt >= DISP_MaxNum_LedSeg) G_LedSeg_Cnt =0 ;  //22个字符(数码管显示数组)	
	}

////////////////////////////////////////////////////////////////////////////
//--**矩阵按键 处理**-----------------------------------------------//
	if(Detect_MatrixKey_AC()) //"AC键"//
	{
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
			//Mode〓"关闭"此模块("动态数码管LED_Segment" )	
		Init_Mode_LED_Segment(MODE_Close_LED_Segment);
	}
	if(Detect_MatrixKey_Plus()) //"+ 键"//
	{
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
		G_Brightness_LedSeg ++;  //增加亮度("动态数码管LED_Segment" )	
		if(G_Brightness_LedSeg >= 9) G_Brightness_LedSeg = M_Brightness_1_LedSeg;
	}
	if(Detect_MatrixKey_Minus()) //"-键"//
	{
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
		G_Brightness_LedSeg --;  //减小亮度("动态数码管LED_Segment" )	
		if(G_Brightness_LedSeg == 0) G_Brightness_LedSeg = M_Brightness_8_LedSeg;
	}
	if(Detect_MatrixKey_Equal()) //"=键"//
	{
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
		
		G_Brightness_LedSeg = G_BrightnessKind;   //亮度为1(暗)--"动态数码管LED_Segment" 
			//Mode〓"打开"此模块("动态数码管LED_Segment" )
		Init_Mode_LED_Segment(MODE_Open_LED_Segment);
	}
	break;	

case WORK_LCD_Segment_Test: //Work▓LCD_Segment_Test 测试(工作时)
////////////////////////////////////////////////////////////////////////////
//==**动作处理(相应的IO口输出)**=======================//
	if(F_500ms_LcdSeg)//"段式LCD_Segment"显示"间隔"时间
	{
		F_500ms_LcdSeg = 0;
		
			//"所有""段式LCD_Segment": 同时"循环"显示"相同"字符
		Disp_LCD_Segment(0,G_LcdSeg_Cnt,G_LcdSeg_Cnt,G_LcdSeg_Cnt,G_LcdSeg_Cnt,G_LcdSeg_Cnt,G_LcdSeg_Cnt);

		G_LcdSeg_Cnt ++;//"段式LCD_Segment"中用到的计数器(用于字符循环显示)
		if(G_LcdSeg_Cnt >= DISP_MaxNum_LcdSeg) G_LcdSeg_Cnt = 0 ;  //22个字符(数码管显示数组)	
	}


////////////////////////////////////////////////////////////////////////////
//--**矩阵按键 处理**-----------------------------------------------//
	if(Detect_MatrixKey_AC()) //"AC键"//
	{
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
			//Mode〓"关闭"此模块(段式LCD_Segment)
		Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);
	}
	if(Detect_MatrixKey_Plus()) //"+ 键"//
	{
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
			//Mode〓"打开"背光(段式LCD_Segment)		
		Init_Mode_LCD_Segment(MODE_OpenBackLight_LCD_Segment);
	}

	if(Detect_MatrixKey_Minus()) //"-键"//
	{
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
			//Mode〓"关闭"背光(段式LCD_Segment)		
		Init_Mode_LCD_Segment(MODE_CloseBackLight_LCD_Segment);
	}
	if(Detect_MatrixKey_Equal()) //"=键"//
	{
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
			//Mode〓更新显示(段式LCD_Segment)
		Init_Mode_LCD_Segment(MODE_Refresh_LCD_Segment);
	}
	break;

case WORK_Buzzer_Test: //Work▓Buzzer_Test 测试(工作时)
	break;

case WORK_Speaker_Test: //Work▓Speaker_Test 测试(工作时)
	break;
	
case WORK_Microphone_Test: //Work▓Microphone_Test 测试(工作时)
	Mic_Record_Speaker_Play(); //麦克风录音后，通过DMA 传给DAC通过扬声器播放
	break;

case WORK_BQ27410_Test: //Work▓BQ27410_FuelGauge_Test 测试(工作时)
////////////////////////////////////////////////////////////////////////////
//==**动作处理(相应的IO口输出)**=======================//

	if(F_1s_BQ27410InTest) //系统每1s 读取"实时BQ27410采样的 电量值"
	{
		F_1s_BQ27410InTest = 0;
		F_En_Scan_MatrixKey = NO;  //禁止扫描"矩阵按键扫描"
		//_delay_us(50);
		//_delay_ms(50);
Sample_BQ27410_FuelGauge();  //BQ27410 采样锂电池的电量
		//_delay_ms(50);
		F_En_Scan_MatrixKey = YES;  //使能"矩阵按键扫描"
	}

	Display_BQ27410_LCD_Segment();  //在段式LCD上显示BQ27410 采样得到的电量值
	break;



////////////////////////////////////////////////////////////////////////////
//==**"相关测试" ( 工作菜单)** ===========================//

case WORK_Line_LCD_TFT:  //Work▓Line_LCD_TFT 测试(工作时)
	break;


case WORK_Rectangle_LCD_TFT:  //Work▓Rectangle_LCD_TFT 测试(工作时)
	break;

case WORK_Circle_LCD_TFT:  //Work▓Circle_LCD_TFT 测试(工作时)
	break;

case WORK_FillArea_LCD_TFT:  //Work▓FillArea_LCD_TFT 测试(工作时)
	break;

case WORK_Chinese_LCD_TFT:  //Work▓Chinese_LCD_TFT 测试(工作时)
	break;
	
case WORK_Clear_LCD_TFT:  //Work▓Clear_LCD_TFT 测试(工作时)
	break;


////////////////////////////////////////////////////////////////////////////
//==**"相关测试" ( 工作菜单)** ===========================//
case WORK_Idle_Step_Motor:      //Work▓Idle_Step_Motor 测试(工作时)
	Stop_Step_Motor();  //停转-"Step_Motor 步进电机"
	break;

case WORK_Stop_Step_Motor:      //Work▓Stop_DC_Motor 测试(工作时)
	Stop_Step_Motor();  //停转-"Step_Motor 步进电机"
	break;

case WORK_Positive_Step_Motor:  //Work▓Positive_Step_Motor 测试(工作时)
	break;
	
case WORK_Reverse_Step_Motor:   //Work▓Reverse_Step_Motor 测试(工作时)
	break;




////////////////////////////////////////////////////////////////////////////
//==**"相关测试" ( 工作菜单)** ===========================//
case WORK_Idle_DC_Motor:      //Work▓Idle_DC_Motor 测试(工作时)
	Stop_DC_Motor();  //停转-"DC_Motor 直流电机"
	G_DC_SpeedCnt = 0; //清频率计数器，重新采样
	
	if( !F_Timing_In_Work )  //定时结束后，电机停转，开始进行换向
	{
		if(G_DC_WorkState == STATE_Positive_DC_Motor)
		{
			Initial_WorkState(WORK_Positive_DC_Motor); //装载//Work▓Positive_DC_Motor 测试(工作时)
		}
		else if(G_DC_WorkState == STATE_Reverse_DC_Motor)		
		{
			Initial_WorkState(WORK_Reverse_DC_Motor); //装载//Work▓Reverse_DC_Motor 测试(工作时)
		}
	}
	break;

case WORK_Stop_DC_Motor:      //Work▓Stop_DC_Motor 测试(工作时)
	Stop_DC_Motor();  //停转-"DC_Motor 直流电机"
	G_DC_SpeedCnt = 0; //清频率计数器，重新采样
	break;

case WORK_Positive_DC_Motor:  //Work▓Positive_DC_Motor 测试(工作时)
	Positive_DC_Motor();  //正转-"DC_Motor 直流电机"(根据电位计电压进行调速)
	break;
	
case WORK_Reverse_DC_Motor:   //Work▓Reverse_DC_Motor 测试(工作时)
	Reverse_DC_Motor();	//反转-"DC_Motor 直流电机"(根据电位计电压进行调速)
	break;



////////////////////////////////////////////////////////////////////////////
//==**"相关测试" ( 工作菜单)** ===========================//


////////////////////////////////////////////////////////////////////////////
//==**"相关测试" ( 工作菜单)** ===========================//


////////////////////////////////////////////////////////////////////////////
//==**"相关测试" ( 工作菜单)** ===========================//





////////////////////////////////////////////////////////////////////////////
default:
	break;
	}
}





/****************************************************************************
*函数名-Function:	void Deal_MAIN_DC_Motor_Test(void)
*描述- Description:	//处理//Main█DC_Motor_Test 菜单选择(工作时) 
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
******************************************************
void Deal_MAIN_DC_Motor_Test(void) //处理//Main█DC_Motor_Test 菜单选择(工作时) 
{
	unsigned char a = 0;
	unsigned char b = 0;
	unsigned char c = 0;

	unsigned int speed;
	
	unsigned char s1 = 0;
	unsigned char s2 = 0;
	unsigned char s3 = 0;
	unsigned char s4 = 0;

////////////////////////////////////////////////////////////////////////////
//==**采样电位计AD值,作为转速给定值**================//
		//多次采样"Potentiometer电位计"AD值，并进行处理
	Deal_ADC12_A(M_Potentiometer_AdNum); // 处理采样结果: 将多次采样值，进行排序，去掉两头，对中间的几个AD值求平均，得到最后的AD值。


////////////////////////////////////////////////////////////////////////////
//==**按键 处理**=======================================//


////////////////////////////////////////////////////////////////////////////
//--**矩阵按键 处理**-----------------------------------------------//
	if(Detect_MatrixKey_1()) //"数字1键"//1.Positive Rotation
	{
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
		
		if(G_DC_WorkState == STATE_Reverse_DC_Motor)
		{
			G_DC_WorkState = STATE_Positive_DC_Motor;
			Initial_WorkState(WORK_Idle_DC_Motor); //装载//Work▓Idle_DC_Motor 测试(工作时)
		}
		else
		{
			G_DC_WorkState = STATE_Positive_DC_Motor;
			Initial_WorkState(WORK_Positive_DC_Motor); //装载//Work▓Positive_DC_Motor 测试(工作时)
		}
	}

	if(Detect_MatrixKey_2()) //"数字2键"//2.Reverse Rotation
	{
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
		
		if(G_DC_WorkState == STATE_Positive_DC_Motor)
		{
			G_DC_WorkState = STATE_Reverse_DC_Motor;
			Initial_WorkState(WORK_Idle_DC_Motor); //装载//Work▓Idle_DC_Motor 测试(工作时)
		}
		else 
		{
			G_DC_WorkState = STATE_Reverse_DC_Motor;
			Initial_WorkState(WORK_Reverse_DC_Motor); //装载//Work▓Reverse_DC_Motor 测试(工作时)
		}
	}

	if(Detect_MatrixKey_3()) //"数字3键"//3.Stop DC-Moter
	{
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
		G_DC_WorkState = STATE_Stop_DC_Motor;
		Initial_WorkState(WORK_Stop_DC_Motor); //装载//Work▓Stop_DC_Motor 测试(工作时)
	}


////////////////////////////////////////////////////////////////////////////
//==**显示处理**========================================//
	if(F_500ms_Reflash_DC_Motor)  //500ms 刷新"转速" ("DC_Motor 直流电机")
	{
		F_500ms_Reflash_DC_Motor = 0;

		speed = G_DC_Speed / 3;  // 将转速脉冲转成"实际转速值"r/s单位

////////////////////////////////////////////////////////////////////////////
//--**显示处理:  "彩屏LCD_TFT" **------------------------------------//
			//在"测试电机"显示速度给定电压值: 电位计Potentiometer 实时"电压值"
		Disp_Potentiometer_Motor();

		Disp_Speed_DC_Motor();//在"测试DC_Motor"显示电机速度

////////////////////////////////////////////////////////////////////////////
//--**显示处理:  "动态数码管LED_Segment"**-----------------------//
	//电位计显示相关
		a = (unsigned char)(G_LastAdResult/1000);
		b = (unsigned char)((G_LastAdResult % 1000)/100);
		c = (unsigned char)(G_LastAdResult % 100)/10;
		if(G_LastAdResult < 30) c = 0; //在电位器旋到最小值时，显示电压会在0.01,0.02,.000之间显示，加上这条，可以在电位器旋到最小值时，显示0.00

	//转速显示相关
		if(G_DC_WorkState  == STATE_Positive_DC_Motor)  //正转显示处理
		{
			s4 = (unsigned char)(speed/1000);
			s3 = (unsigned char)((speed % 1000)/100);
			s2 = (unsigned char)(speed % 100)/10;
			s1 = (unsigned char)(speed % 10);
			if((s4 == 0)&&(s3 == 0)&&(s2 == 0)) s2 = DISP_OFF_LedSeg;	
			if((s4 == 0)&&(s3 == 0)) s3 = DISP_OFF_LedSeg;
			if(s4 == 0) s4 = DISP_OFF_LedSeg; //显示"暗码"(不显示0)
		}
		else if(G_DC_WorkState  == STATE_Reverse_DC_Motor) //反转显示处理
		{
			s4 = (unsigned char)(speed/1000);
			s3 = (unsigned char)((speed % 1000)/100);
			s2 = (unsigned char)(speed % 100)/10;
			s1 = (unsigned char)(speed % 10);
			if((s4 == 0)&&(s3 == 0)&&(s2 == 0))
			{
			 	s4 = DISP_OFF_LedSeg;//显示"暗码"(不显示0)
				s3 = DISP_OFF_LedSeg;//显示"暗码"(不显示0)
				s2 = DISP_Minus_LedSeg; //显示"负号"(不显示0)
			}
			if((s4 == 0)&&(s3 == 0))
			{
			 	s4 = DISP_OFF_LedSeg;//显示"暗码"(不显示0)
				s3 = DISP_Minus_LedSeg; //显示"负号"(不显示0)
			}
			if(s4 == 0) s4 = DISP_Minus_LedSeg; //显示"负号"(不显示0)			
		}
		Disp_LED_Segment(0,8,a,b,c,DISP_OFF_LedSeg,s4,s3,s2,s1);
	}

////////////////////////////////////////////////////////////////////////////
//--**IO按键 处理**---------------------------------------------------//
	Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"

}
***********************/




/****************************************************************************
*函数名-Function:	void Deal_MAIN_Step_Motor_Test(void)
*描述- Description:	//处理//Main█Step_Motor_Test 菜单选择(工作时) 
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
******************************************************
void Deal_MAIN_Step_Motor_Test(void) //处理//Main█Step_Motor_Test 菜单选择(工作时) 
{
	unsigned char a = 0;
	unsigned char b = 0;
	unsigned char c = 0;
	
	unsigned char s1 = 0;
	unsigned char s2 = 0;
	unsigned char s3 = 0;
	unsigned char s4 = 0;


////////////////////////////////////////////////////////////////////////////
//==**采样电位计AD值,作为转速给定值**================//
		//多次采样"Potentiometer电位计"AD值，并进行处理
	Deal_ADC12_A(M_Potentiometer_AdNum); // 处理采样结果: 将多次采样值，进行排序，去掉两头，对中间的几个AD值求平均，得到最后的AD值。


////////////////////////////////////////////////////////////////////////////
//==**按键 处理**=======================================//

////////////////////////////////////////////////////////////////////////////
//--**矩阵按键 处理**-----------------------------------------------//
	if(Detect_MatrixKey_1()) //"数字1键"//1.Positive Rotation
	{
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
		
		if(G_Step_WorkState != STATE_Positive_Step_Motor)
		{
			G_Step_WorkState = STATE_Positive_Step_Motor;
			Initial_WorkState(WORK_Positive_Step_Motor); //装载//Work▓Positive_Step_Motor 测试(工作时)
		}
	}

	if(Detect_MatrixKey_2()) //"数字2键"//2.Reverse Rotation
	{
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
		
		if(G_Step_WorkState != STATE_Reverse_Step_Motor)
		{
			G_Step_WorkState = STATE_Reverse_Step_Motor;
			Initial_WorkState(WORK_Reverse_Step_Motor); //装载//Work▓Reverse_Step_Motor 测试(工作时)
		}
	}

	if(Detect_MatrixKey_3()) //"数字3键"//3.Stop Step-Moter
	{
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
		
		G_Step_WorkState = STATE_Stop_Step_Motor;
		Initial_WorkState(WORK_Stop_Step_Motor); //装载//Work▓Stop_Step_Motor 测试(工作时)
	}


////////////////////////////////////////////////////////////////////////////
//==**显示处理**========================================//


	if(F_500ms_Reflash_Step_Motor)  //500ms 刷新"转速" --"Step_Motor 步进电机"
	{
		F_500ms_Reflash_Step_Motor = 0;


		Deal_Speed_Step_Motor(); // 计算步进电转速

////////////////////////////////////////////////////////////////////////////
//--**显示处理:  "彩屏LCD_TFT" **------------------------------------//
			//在"测试电机"显示速度给定电压值: 电位计Potentiometer 实时"电压值"
		Disp_Potentiometer_Motor();

		Disp_Speed_Step_Motor(); //在"测试Step_Motor"显示电机速度

////////////////////////////////////////////////////////////////////////////
//--**显示处理:  "动态数码管LED_Segment"**-----------------------//
	//电位计显示相关
		a = (unsigned char)(G_LastAdResult/1000);
		b = (unsigned char)((G_LastAdResult % 1000)/100);
		c = (unsigned char)(G_LastAdResult % 100)/10;
		if(G_LastAdResult < 30) c = 0; //在电位器旋到最小值时，显示电压会在0.01,0.02,.000之间显示，加上这条，可以在电位器旋到最小值时，显示0.00

	//转速显示相关
		s3 = (unsigned char)((G_Step_Speed % 1000)/100);
		s2 = (unsigned char)(G_Step_Speed % 100)/10;
		s1 = (unsigned char)(G_Step_Speed % 10);

		if(G_Step_WorkState  == STATE_Reverse_Step_Motor) //反转显示处理
		{
			s4 = DISP_Minus_LedSeg; //显示"负号"(不显示0)		
		}
		else s4 = DISP_OFF_LedSeg;
		
		Disp_LED_Segment(8,3,a,b,c,DISP_OFF_LedSeg,s4,s3,s2,s1);
	}


////////////////////////////////////////////////////////////////////////////
//--**IO按键 处理**---------------------------------------------------//
	Detect_Key_WorkMenu(); //按"Key1","Key2"上下选择"工作菜单"

}
***********************/



