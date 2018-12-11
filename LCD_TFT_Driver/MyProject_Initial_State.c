/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 MyPrimacy_Initial_State.c
* 附属文件-Dependencies:  	 System_HeadFile.h; 	
* 文件描述-File Description:	 ( 源程序-Source File) 
	■ 具体项目: "初使化" 各"系统状态" (状态机)
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




#include "System_HeadFile.h"   //引入: 系统全部头文件集(包含所有使用到的头文件)



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////



/****************************************************************************
*函数名-Function:	void Initial_MainState(unsigned int MainMode)
*描述- Description:	"初使化" 各"系统状态Main█" (状态机)
						01)更新系统状态值；02)完成显示内容初使化；
						03)相关变量初始化
*输入参数-Input:	MainMode: 系统状态值
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Initial_MainState(unsigned int MainMode)
{
	G_Last_MainState = G_MainState;  //保存"上一次"系统状态值
	G_MainState = MainMode;



	switch(MainMode) 
	{
////////////////////////////////////////////////////////////////////////////
//==**待机\常用状态值: 0x00--0xFF **=======================//
////////////////////////////////////////////////////////////////////////////


case MAIN_Restart:  //Main█ 重启，并系统自检--Restart Self-Test     
	Open_Buzzer(BuzzTime_Key);	//按键有效时，让蜂鸣叫指定时间
	WaitingDelayMs(BuzzTime_Key*10);
	mReset_Soft;   //"软件复位"
	break;

case MAIN_Self_Check:  //Main█系统自检状态
//--**动作处理(相应的IO口输出)**------------------------------//
	mOpen_LED_YELLOW;  //配置引脚为"输出",并"点亮"LED_YELLOW
	mOpen_LED_GREEN;   //配置引脚为"输出",并"点亮"LED_GREEN
	mOpen_LED_RED;     //配置引脚为"输出",并"点亮"LED_RED

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
LCD_TFT_Show_StandbyPage(); //显示"待机页面"-"彩屏LCD_TFT_ILI9325"	


//--**需更新的"数码管LED"显示内容**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //亮度为1(暗)--"动态数码管LED_Segment" 
		//所有显示字符: //DISP◎"全亮"--"动态数码管LED_Segment" 
		//"显示字符"更新到"显示缓存数组"("动态数码管LED_Segment" )
	Disp_LED_Segment(0,0,DISP_ON_LedSeg,DISP_ON_LedSeg,DISP_ON_LedSeg,DISP_ON_LedSeg,DISP_ON_LedSeg,DISP_ON_LedSeg,DISP_ON_LedSeg,DISP_ON_LedSeg);
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);
	

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
		//所有显示字符: //DISP◎"全亮"--"段式LCD_Segment" //"显示字符"更新到"显示缓存数组"(段式LCD_Segment)
	Disp_LCD_Segment(0,DISP_ON_LcdSeg,DISP_ON_LcdSeg,DISP_ON_LcdSeg,DISP_ON_LcdSeg,DISP_ON_LcdSeg,DISP_ON_LcdSeg);
		//Mode〓"打开"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Open_LCD_Segment);


//--**"标志位+变量"的相关初使化**---------------------------//
Open_Buzz_Speaker(M_Self_Check_Time);  //打开蜂鸣器(Speaker 扬声器)的定时器
Enable_AlarmBuzzer(M_Buzz200ms);	//打开:报警蜂鸣器(并指定报警周期)(以10ms为时间单位)

	//F_SecondChange = 1; 	//一上电或返回待机状态，可以马上显示时间,不需要等1s后才刷新时间
	Open_Timing_Task(M_Self_Check_Time);//打开系统定时，定时给定的时间值(中断内)
	Initial_WorkState(WORK_Test_IdleState); //装载//Work▓"测试时"的空闲状态(工作时)
	break;


////////////////////////////////////////////////////////////////////////////
//==**主菜单状态值: 0x100--0x1FF **=========================//
////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	//--**基本参数: "时间修改"菜单0x200--0x21F **-------------------//
	////////////////////////////////////////////////////////////////////////////
case MAIN_ModifyTime:  //Main█"实时时间"修改状态
//--**动作处理(相应的IO口输出)**------------------------------//
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	
//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_ModifyTime();//显示//Main█"实时时间"修改状态
	
//--**需更新的"数码管LED"显示内容**-------------------------//
//--**需更新的"段式LCD_Segment"显示内容**--------------------//

//--**"标志位+变量"的相关初使化**---------------------------//
		//要存15个按键值:年(4个)+月(2个)+日(2个)+时(2个)+分(2个)+秒(2个)+星期(1个)
	G_TotalKeyNum = 15;	//输入的数字按键总个数	
	G_MatrixKeyCnt = 0;  //清按键缓存指针

	G_MatrixKeyBuf[0]  = (unsigned char)(RTCYEAR >> 12);  //存"千位"(年)(ASSII码)
	G_MatrixKeyBuf[1]  = (unsigned char)((RTCYEAR >> 8) & 0x000F); 	//存"百位"(年)(ASSII码)
	G_MatrixKeyBuf[2]  = (unsigned char)((RTCYEAR >> 4) & 0x000F); //存"十位"(年)(ASSII码)
	G_MatrixKeyBuf[3]  = (unsigned char)(RTCYEAR & 0x000F); 	//存"个位"(年)(ASSII码)

	G_MatrixKeyBuf[4]  = RTCMON >> 4;  //存"十位"(月)
	G_MatrixKeyBuf[5]  = RTCMON & 0x0F; //存"个位"(月)
	
	G_MatrixKeyBuf[6]  = RTCDAY >> 4; //存"十位"(日)
	G_MatrixKeyBuf[7]  = RTCDAY & 0x0F; //存"个位"(日)
	
	G_MatrixKeyBuf[8]  = RTCHOUR >> 4;  //存"十位"(小时)
	G_MatrixKeyBuf[9]  = RTCHOUR & 0x0F; //存"个位"(小时)
	
	G_MatrixKeyBuf[10] = RTCMIN >> 4;  //存"十位"(分钟)
	G_MatrixKeyBuf[11] = RTCMIN & 0x0F;  //存"个位"(分钟)
	
	G_MatrixKeyBuf[12] = RTCSEC >> 4;  //存"十位"(秒)
	G_MatrixKeyBuf[13] = RTCSEC & 0x0F;  //存"个位"(秒)
	
	G_MatrixKeyBuf[14] = RTCDOW;  //存""(星期)


	G_KeyPlace_Row = TestLine08;	  //(行)按键设置参数位置(光标)开始位置
	G_KeyPlace_Column = TestColumn03; //(列)按键设置参数位置(光标)开始位置

	Initial_WorkState(WORK_Test_IdleState); //装载//Work▓"测试时"的空闲状态(工作时)
	break;


////////////////////////////////////////////////////////////////////////////
//==**工作"菜单"状态值: 0x7000--0x7FFF**====================//
////////////////////////////////////////////////////////////////////////////

case MAIN_Working_State: //Main█进入工作状态(工作时)
	
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW;  //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_GREEN;   //配置引脚为"输出",并"熄灭"LED_GREEN
	mClose_LED_RED;	   //配置引脚为"输出",并"熄灭"LED_RED

	Disable_AlarmBuzzer();	//关闭:报警蜂鸣器
	Disable_Speaker(); //禁止:	"Speaker 扬声器" 
	
//--**需更新的"段式LCD_Segment"显示内容**--------------------//
	Disp_LCD_Segment(0,DISP_OFF_LcdSeg,DISP_OFF_LcdSeg,DISP_OFF_LcdSeg,DISP_OFF_LcdSeg,DISP_OFF_LcdSeg,DISP_OFF_LcdSeg);
	Refresh_LCD_Segment(G_LcdSegBuf[6],G_LcdSegBuf[5],G_LcdSegBuf[4],G_LcdSegBuf[3],G_LcdSegBuf[2],G_LcdSegBuf[1],G_LcdSegBuf[0]); 
		//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);
	Close_LCD_Segment();  //关闭"段式LCD_Segment"


//--**需更新的"数码管LED"显示内容**-------------------------//
		//亮度为0 (显示关)--"动态数码管LED_Segment" 
	G_Brightness_LedSeg = M_Brightness_OFF_LedSeg;
		//清显示缓存数组
	Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
	Refresh_LED_Segment(); //更新显示("动态数码管LED_Segment" )
		//Mode〓"关闭"此模块("动态数码管LED_Segment" )	
	Init_Mode_LED_Segment(MODE_Close_LED_Segment);


//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	LCD_TFT_Show_WorkPage(); //显示"工作页面"-"彩屏LCD_TFT_ILI9325"  
	

//--**"标志位+变量"的相关初使化**---------------------------//
	F_Update_RealTime = YES;	//一上电或返回待机状态，可以马上显示时间,不需要等1s后才刷新时间
	F_Update_Temperature = YES;
	F_Update_CurrentValue = YES;
	F_Update_Power = YES;
	
	G_KeyCnt = 1;  //第"01.xxx"菜单，开始
	
	Initial_MainState(MAIN_Basic_Settings); //装载//Main█Basic_Settings菜单选择(工作时)
	Initial_WorkState(WORK_Test_IdleState); //装载//Work▓"测试时"的空闲状态(工作时)
	break;

case MAIN_Basic_Settings:  //Main█Basic_Settings菜单选择(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	Disable_AlarmBuzzer();	//关闭:报警蜂鸣器
	Disable_Speaker();      //禁止: "Speaker 扬声器" 

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_01Page_MenuLine();  //显示第1页"工作菜单"(LCD)(1.Work_A  2.Work_B	3.Work_C  4.Work_D

	Disp_MAIN_Basic_Settings();  //显示//Main█Basic_Settings 菜单选择(工作时)
		//--care--显示: 选中标志放在此程序后面
	Disp_SelectFlag(); //显示"选中标志" 

//--**需更新的"数码管LED"显示内容**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //亮度为1(暗)--"动态数码管LED_Segment" 
		//所有显示字符://DISP◎"暗码"--"动态数码管LED_Segment" 
		//"显示字符"更新到"显示缓存数组"("动态数码管LED_Segment" )
	Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);


//--**需更新的"段式LCD_Segment"显示内容**--------------------//
		//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);


//--**"标志位+变量"的相关初使化**---------------------------//
	Initial_WorkState(WORK_Test_IdleState); //装载//Work▓"测试时"的空闲状态(工作时)
		//因为SD卡的相关测试时，修改了晶振，故这里重新初使化,还原之前的晶振配置
//Osccon_Initial();//晶振初始化函数:配置相关晶振参数
	
	break;


case MAIN_Basic_Check:  //Main█Basic_Check 菜单选择(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	Disable_AlarmBuzzer();	//关闭:报警蜂鸣器
	Disable_Speaker();      //禁止: "Speaker 扬声器" 

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	//Disp_01Page_MenuLine();  //显示第1页"工作菜单"(LCD)(1.Work_A  2.Work_B	3.Work_C  4.Work_D
	Disp_MAIN_Basic_Check();  //显示//Main█Basic_Check 菜单选择(工作时)
		//--care--显示: 选中标志放在此程序后面
	Disp_SelectFlag(); //显示"选中标志" 

//--**需更新的"数码管LED"显示内容**-------------------------//
		//Mode〓"关闭"此模块("动态数码管LED_Segment" )	
	Init_Mode_LED_Segment(MODE_Close_LED_Segment);

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
		//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	Initial_WorkState(WORK_Test_IdleState); //装载//Work▓"测试时"的空闲状态(工作时)
	break;


case MAIN_LCD_TFT_Test: //Main█LCD_TFT_Test 菜单选择(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	Disable_AlarmBuzzer();	//关闭:报警蜂鸣器
	Disable_Speaker(); //禁止:	"Speaker 扬声器" 

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_LCD_TFT_Test();  //显示//Main█LCD_TFT_Test 菜单选择(工作时)
	mUpdate_All_TestLine;  //刷新所有" 测试行"
	
		//--care--显示: 选中标志放在此程序后面
	Disp_SelectFlag(); //显示"选中标志"

//--**需更新的"数码管LED"显示内容**-------------------------//
		//Mode〓"关闭"此模块("动态数码管LED_Segment" )	
	Init_Mode_LED_Segment(MODE_Close_LED_Segment);

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
		//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	Initial_WorkState(WORK_Test_IdleState); //装载//Work▓"测试时"的空闲状态(工作时)
	break;

case MAIN_MatrixKey_Test:  //Main█MatrixKey_Test 菜单选择(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	
//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_MatrixKey_Test();  //显示//Main█MatrixKey_Test 菜单选择(工作时)
		//--care--显示: 选中标志放在此程序后面
	Disp_SelectFlag(); //显示"选中标志" "=>"

//--**需更新的"数码管LED"显示内容**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //亮度为1(暗)--"动态数码管LED_Segment" 
		//所有显示字符://DISP◎"暗码"--"动态数码管LED_Segment" 
		//"显示字符"更新到"显示缓存数组"("动态数码管LED_Segment" )
	Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);

		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);


//--**需更新的"段式LCD_Segment"显示内容**--------------------//
			//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	Initial_WorkState(WORK_Test_IdleState); //装载//Work▓"测试时"的空闲状态(工作时)
	break;

case MAIN_TouchPads_Test:  //Main█TouchPads_Test 菜单选择(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_TouchPads_Test();  //显示//Main█TouchPads_Test 菜单选择(工作时)
		//--care--显示: 选中标志放在此程序后面
	Disp_SelectFlag(); //显示"选中标志" "=>"

//--**需更新的"数码管LED"显示内容**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //亮度为1(暗)--"动态数码管LED_Segment" 
		//所有显示字符://DISP◎"暗码"--"动态数码管LED_Segment" 
	Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
			//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	F_En_Scan_MatrixKey = NO;  //禁止扫描"矩阵按键扫描"
	Initial_Touch_Pad();  //初始化设置: "Touch_Pads 电容按键" 
	F_En_Scan_MatrixKey = YES;	//允许中断中扫描"矩阵按键扫描"

	Initial_WorkState(WORK_Test_IdleState); //装载//Work▓"测试时"的空闲状态(工作时)
	break;

case MAIN_INA21x_Current_Test:  //Main█INA21x_Current_Test 菜单选择(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_INA21x_Current_Test();  //显示//Main█INA21x_Current_Test 菜单选择(工作时)
		//--care--显示: 选中标志放在此程序后面
	Disp_SelectFlag(); //显示"选中标志" "=>"

//--**需更新的"数码管LED"显示内容**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //亮度为1(暗)--"动态数码管LED_Segment" 
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

	
//--**需更新的"段式LCD_Segment"显示内容**--------------------//
			//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	ADC12_A_Initial(); //ADC12_A	内部资源初始化
	Initial_WorkState(WORK_Test_IdleState); //装载//Work▓"测试时"的空闲状态(工作时)
	break;

case MAIN_TMP006_Temperature:  //Main█TMP006_Temperature 菜单选择(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_TMP006_Temperature();  //显示//Main█TMP006_Temperature 菜单选择(工作时)
		//--care--显示: 选中标志放在此程序后面
	Disp_SelectFlag(); //显示"选中标志" "=>"

//--**需更新的"数码管LED"显示内容**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //亮度为1(暗)--"动态数码管LED_Segment" 
		//"显示字符"更新到"显示缓存数组"("动态数码管LED_Segment" )
	Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
		//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);


//--**"标志位+变量"的相关初使化**---------------------------//
	Initial_WorkState(WORK_Test_IdleState); //装载//Work▓"测试时"的空闲状态(工作时)
	break;

case MAIN_TMP100_Temperature:  //Main█TMP100_Temperature 菜单选择(工作时)
	break;

case MAIN_Potentiometer_Test:  //Main█Potentiometer_Test 菜单选择(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_Potentiometer_Test();  //显示//Main█Potentiometer_Test 菜单选择(工作时)
		//--care--显示: 选中标志放在此程序后面
	Disp_SelectFlag(); //显示"选中标志" "=>"

//--**需更新的"数码管LED"显示内容**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //亮度为1(暗)--"动态数码管LED_Segment" 
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

	
//--**需更新的"段式LCD_Segment"显示内容**--------------------//
			//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	ADC12_A_Initial(); //ADC12_A  内部资源初始化
	Disable_Step_Motor(); //禁止-"Step_Motor 步进电机"
	Disable_DC_Motor();  //禁止-"DC_Motor 直流电机"
	Initial_WorkState(WORK_Test_IdleState); //装载//Work▓"测试时"的空闲状态(工作时)
	break;
	
	
case MAIN_DC_Motor_Test:  //Main█DC_Motor_Test 菜单选择(工作时) 
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);	//按键有效时，让蜂鸣叫指定时间
	
//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_DC_Motor_Test();	//显示//Main█DC_Motor_Test 菜单选择(工作时) 
	mUpdate_All_TestLine;  //刷新所有" 测试行"
	
		//--care--显示: 选中标志放在此程序后面
	Disp_SelectFlag(); //显示"选中标志" "=>"

//--**需更新的"数码管LED"显示内容**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //亮度为1(暗)--"动态数码管LED_Segment" 
		//"显示字符"更新到"显示缓存数组"("动态数码管LED_Segment" )
	Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
		//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	Disable_Step_Motor();  //禁止-"Step_Motor 步进电机"

	DC_Motor_Initial();  //初始化设置:	"DC_Motor 直流电机"
	G_DC_WorkState = STATE_Idle_DC_Motor;
	Initial_WorkState(WORK_Idle_DC_Motor); //装载//Work▓Idle_DC_Motor 测试(工作时)
	break;


case MAIN_Step_Motor_Test:  //Main█Step_Motor_Test 菜单选择(工作时) 
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_Step_Motor_Test();  //显示//Main█Step_Motor_Test 菜单选择(工作时) 
	mUpdate_All_TestLine;  //刷新所有" 测试行"

		//--care--显示: 选中标志放在此程序后面
	Disp_SelectFlag(); //显示"选中标志" "=>"

//--**需更新的"数码管LED"显示内容**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //亮度为1(暗)--"动态数码管LED_Segment" 
		//"显示字符"更新到"显示缓存数组"("动态数码管LED_Segment" )
	Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
			//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	Disable_DC_Motor();  //禁止-"DC_Motor 直流电机"

	Step_Motor_Initial();  //初始化设置:  "Step_Motor 步进电机"
	G_Step_WorkState = STATE_Idle_Step_Motor;
	Initial_WorkState(WORK_Idle_Step_Motor); //装载//Work▓Idle_Step_Motor 测试(工作时)
	break;


case MAIN_NTC_HR202_Test:  //Main█NTC_HR202_Test(温湿度) 菜单选择(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_01Page_MenuLine();  //显示第1页"工作菜单"(LCD)(1.Work_A  2.Work_B	3.Work_C  4.Work_D

	Disp_MAIN_NTC_HR202_Test();  //显示//Main█NTC_HR202_Test(温湿度) 菜单选择(工作时)
		//--care--显示: 选中标志放在此程序后面
	Disp_SelectFlag(); //显示"选中标志" "=>"

//--**需更新的"数码管LED"显示内容**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //亮度为1(暗)--"动态数码管LED_Segment" 
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

	
//--**需更新的"段式LCD_Segment"显示内容**--------------------//
			//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	Disable_Step_Motor(); //禁止-"Step_Motor 步进电机"
	Disable_DC_Motor();  //禁止-"DC_Motor 直流电机"
	Disable_UART_A(); //禁用UART_A 模块
	
	HR202_Humidity_Initial();  //初始化设置:  "HR202_Humidity 电阻型湿度传感器"

	Initial_WorkState(WORK_Test_IdleState); //装载//Work▓"测试时"的空闲状态(工作时)
	break;


case MAIN_IrDA_UART:  //Main█IrDA_UART 菜单选择(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	Disable_Step_Motor(); //禁止-"Step_Motor 步进电机"
	Disable_DC_Motor();  //禁止-"DC_Motor 直流电机"

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_02Page_MenuLine();  //显示第2页"工作菜单"(LCD)(1.Work_A  2.Work_B	3.Work_C  4.Work_D
	Disp_MAIN_IrDA_UART();  //显示//Main█IrDA_UART 菜单选择(工作时)

		//--care--显示: 选中标志放在此程序后面
	Disp_SelectFlag(); //显示"选中标志" "=>"

//--**需更新的"数码管LED"显示内容**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //亮度为1(暗)--"动态数码管LED_Segment" 
		//"显示字符"更新到"显示缓存数组"("动态数码管LED_Segment" )
	Disp_LED_Segment(0,0,DISP_I_LedSeg,DISP_r_LedSeg,DISP_d_LedSeg,DISP_A_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

	
//--**需更新的"段式LCD_Segment"显示内容**--------------------//
		//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	Initial_WorkState(WORK_Test_IdleState); //装载//Work▓"测试时"的空闲状态(工作时)
	break;


case MAIN_RS232_UART:  //Main█RS232_UART 菜单选择(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_RS232_UART();  //显示//Main█RS232_UART 菜单选择(工作时)

		//--care--显示: 选中标志放在此程序后面
	Disp_SelectFlag(); //显示"选中标志" "=>"

//--**需更新的"数码管LED"显示内容**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //亮度为1(暗)--"动态数码管LED_Segment" 
		//"显示字符"更新到"显示缓存数组"("动态数码管LED_Segment" )
	Disp_LED_Segment(0,0,DISP_2_LedSeg,DISP_3_LedSeg,DISP_2_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

	
//--**需更新的"段式LCD_Segment"显示内容**--------------------//
		//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	Initial_WorkState(WORK_Test_IdleState); //装载//Work▓"测试时"的空闲状态(工作时)
	break;



case MAIN_RS485_UART:  //Main█RS485_UART 菜单选择(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	
//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_RS485_UART();  //显示//Main█RS485_UART 菜单选择(工作时)

		//--care--显示: 选中标志放在此程序后面
	Disp_SelectFlag(); //显示"选中标志" "=>"

//--**需更新的"数码管LED"显示内容**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //亮度为1(暗)--"动态数码管LED_Segment" 
		//"显示字符"更新到"显示缓存数组"("动态数码管LED_Segment" )
	Disp_LED_Segment(0,0,DISP_4_LedSeg,DISP_8_LedSeg,DISP_5_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

	
//--**需更新的"段式LCD_Segment"显示内容**--------------------//
		//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	Initial_WorkState(WORK_Test_IdleState); //装载//Work▓"测试时"的空闲状态(工作时)
	break;


case MAIN_CC1101_Test:  //Main█CC1101_Test 菜单选择(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_CC1101_Test();  //显示//Main█CC1101_Test 菜单选择(工作时)

		//--care--显示: 选中标志放在此程序后面
	Disp_SelectFlag(); //显示"选中标志" "=>"

//--**需更新的"数码管LED"显示内容**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //亮度为1(暗)--"动态数码管LED_Segment" 
		//"显示字符"更新到"显示缓存数组"("动态数码管LED_Segment" )
	Disp_LED_Segment(0,0,DISP_C_LedSeg,DISP_C_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_0_LedSeg,DISP_1_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

	
//--**需更新的"段式LCD_Segment"显示内容**--------------------//
		//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	Initial_WorkState(WORK_Test_IdleState); //装载//Work▓"测试时"的空闲状态(工作时)
	Disable_UART_A(); //禁用UART_A 模块
	
	//G_Update_03Bits = 0;
		//因为SD卡的相关测试时，修改了晶振，故这里重新初使化,还原之前的晶振配置
	//Osccon_Initial();//晶振初始化函数:配置相关晶振参数
	//G_Update_03Bits = 0;
	break;


case MAIN_SD_Card_Test:  //Main█SD_Card_Test 菜单选择(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	
//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_SD_Card_Test();  //显示//Main█SD_Card_Test 菜单选择(工作时)

		//--care--显示: 选中标志放在此程序后面
	Disp_SelectFlag(); //显示"选中标志" "=>"

//--**需更新的"数码管LED"显示内容**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //亮度为1(暗)--"动态数码管LED_Segment" 
		//"显示字符"更新到"显示缓存数组"("动态数码管LED_Segment" )
	Disp_LED_Segment(0,0,DISP_5_LedSeg,DISP_d_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

	
//--**需更新的"段式LCD_Segment"显示内容**--------------------//
		//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	SD_Cnt = 0; //SD卡数据缓存数组指针   
//SD_Num = 0;
	SD_Num = 0;
	SD_Write_Num = 0;

	Initial_WorkState(WORK_Test_IdleState); //装载//Work▓"测试时"的空闲状态(工作时)
	break;



case MAIN_MassStorage_Test:  //Main█MassStorage_Test 菜单选择(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	
//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_02Page_MenuLine();  //显示第2页"工作菜单"(LCD)(1.Work_A  2.Work_B	3.Work_C  4.Work_D
	Disp_MAIN_MassStorage_Test();  //显示//Main█MassStorage_Test 菜单选择(工作时)

		//--care--显示: 选中标志放在此程序后面
	Disp_SelectFlag(); //显示"选中标志" "=>"

//--**需更新的"数码管LED"显示内容**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //亮度为1(暗)--"动态数码管LED_Segment" 
		//"显示字符"更新到"显示缓存数组"("动态数码管LED_Segment" )
	Disp_LED_Segment(0,0,DISP_U_LedSeg,DISP_5_LedSeg,DISP_b_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_0_LedSeg);
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
		//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	
	//Osccon_Initial();
	//G_Update_03Bits = 0;
	Initial_WorkState(WORK_Test_IdleState); //装载//Work▓"测试时"的空闲状态(工作时)
	break;


case MAIN_MassStorage_USB:  //Main█MassStorage_USB 菜单选择(工作时)
	Disp_LED_Segment(0,0,DISP_U_LedSeg,DISP_5_LedSeg,DISP_b_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_1_LedSeg);
	// 没有什么可初使化，因为在MAIN_MassStorage_Test  初使化过了
	//G_Update_03Bits = 0;
	break;




////////////////////////////////////////////////////////////////////////////
default:
	break;
	}
	
}

/***************************************************************************
case :  //Main█
//--**动作处理(相应的IO口输出)**------------------------------//

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
//--**需更新的"数码管LED"显示内容**-------------------------//
//--**需更新的"段式LCD_Segment"显示内容**--------------------//

//--**"标志位+变量"的相关初使化**---------------------------//

	break;

*************************************************************************/





/****************************************************************************
*函数名-Function:	void Initial_WorkState(unsigned int WorkMode)
*描述- Description:	初始化"各工作状态Work▓"
*输入参数-Input:	WorkMode: 系统状态值(工作用)
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Initial_WorkState(unsigned int WorkMode) //工作状态初始化
{
	G_Last_WorkState = G_WorkState;  //保存"上一次"系统状态值
	G_WorkState = WorkMode;


////////////////////////////////////////////////////////////////////////////
//==**工作运行: **0x8000--0x8FFF** ===========================//
////////////////////////////////////////////////////////////////////////////
	switch(WorkMode) 
	{
	
////////////////////////////////////////////////////////////////////////////
//==**"测试时"的空闲状态** ============================//

case WORK_Test_IdleState: //Work▓"测试时"的空闲状态(工作时)
	break;

////////////////////////////////////////////////////////////////////////////
//==**"相关测试" ( 工作菜单)** ===========================//
case WORK_Self_Check: //Work▓Self_Check 测试(工作时)
	//mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	//mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	
	//Disable_AlarmBuzzer();	//关闭:报警蜂鸣器
	//Disable_Speaker(); //禁止:	"Speaker 扬声器" 

	//Initial_MainState(MAIN_Self_Check); //装载//Main█系统自检状态 
	break;
	
case WORK_Led_Diode_Test:  //Work▓Led_Diode_Test 测试(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	Disable_AlarmBuzzer();	//关闭:报警蜂鸣器
	Disable_Speaker(); //禁止:	"Speaker 扬声器" 

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_Basic_Check();  //显示//Main█Basic_Check 菜单选择(工作时)
	F_HL_TestLine02 = YES;  
	
//--**需更新的"数码管LED"显示内容**-------------------------//
		//Mode〓"关闭"此模块("动态数码管LED_Segment" )	
	Init_Mode_LED_Segment(MODE_Close_LED_Segment);
//--**需更新的"段式LCD_Segment"显示内容**--------------------//
		//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	G_SOS_Cnt = 1;  //SOS求救信号从短亮开始循环
	break;

case WORK_LED_Segment_Test: //Work▓LED_Segment_Test 测试(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	Disable_AlarmBuzzer();	//关闭:报警蜂鸣器
	Disable_Speaker(); //禁止:	"Speaker 扬声器" 

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_Basic_Check();  //显示//Main█Basic_Check 菜单选择(工作时)
	F_HL_TestLine03 = YES;  
	
//--**需更新的"数码管LED"显示内容**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //亮度为1(暗)--"动态数码管LED_Segment" 
		//所有显示字符://DISP◎"0"--"动态数码管LED_Segment" 
		//"显示字符"更新到"显示缓存数组"("动态数码管LED_Segment" )
	Disp_LED_Segment(0,0,DISP_0_LedSeg,DISP_0_LedSeg,DISP_0_LedSeg,DISP_0_LedSeg,DISP_0_LedSeg,DISP_0_LedSeg,DISP_0_LedSeg,DISP_0_LedSeg);

		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
		//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	G_LedSeg_Cnt = 0;  //"动态数码管LED_Segment" 中用到的计数器(用于字符循环显示)
	break;

case WORK_LCD_Segment_Test: //Work▓LCD_Segment_Test 测试(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	Disable_AlarmBuzzer();	//关闭:报警蜂鸣器
	Disable_Speaker(); //禁止:	"Speaker 扬声器" 

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_Basic_Check();  //显示//Main█Basic_Check 菜单选择(工作时)
	F_HL_TestLine04 = YES;  

//--**需更新的"数码管LED"显示内容**-------------------------//
		//Mode〓"关闭"此模块("动态数码管LED_Segment" )	
	Init_Mode_LED_Segment(MODE_Close_LED_Segment);

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
		//所有显示字符: //DISP◎"DISP_0_LcdSeg"--"段式LCD_Segment" 
	Disp_LCD_Segment(0,DISP_0_LcdSeg,DISP_0_LcdSeg,DISP_0_LcdSeg,DISP_0_LcdSeg,DISP_0_LcdSeg,DISP_0_LcdSeg);//"显示字符"更新到"显示缓存数组"(段式LCD_Segment)
		//Mode〓"打开"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Open_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	G_LcdSeg_Cnt = 0; //"段式LCD_Segment"中用到的计数器(用于字符循环显示)

    F_Update_RealTime = NO;	    //此时，不刷新"实时时间"     
    F_Update_Temperature = NO;  //此时，不刷新"实时温度"  
    F_Update_CurrentValue = NO; //此时，不刷新"INA21x 实时电流值" 
    F_Update_Power = NO;        //此时，不刷新"锂电池电量"
	break;

case WORK_Buzzer_Test: //Work▓Buzzer_Test 测试(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	Enable_AlarmBuzzer(M_Buzz200ms);  //打开:报警蜂鸣器(并指定报警周期)(以10ms为时间单位)
	Disable_Speaker(); //禁止:	"Speaker 扬声器" 

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_Basic_Check();  //显示//Main█Basic_Check 菜单选择(工作时)
	F_HL_TestLine05 = YES;	

//--**需更新的"数码管LED"显示内容**-------------------------//
		//Mode〓"关闭"此模块("动态数码管LED_Segment" )	
	Init_Mode_LED_Segment(MODE_Close_LED_Segment);

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
		//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	break;

case WORK_Speaker_Test: //Work▓Speaker_Test 测试(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	Disable_AlarmBuzzer();	//关闭:报警蜂鸣器
	Disable_Speaker(); //禁止:	"Speaker 扬声器" 
    Play_a_Song_Speaker(); //初始化设置:  播放一首音乐--"Speaker 扬声器" 

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_Basic_Check();  //显示//Main█Basic_Check 菜单选择(工作时)
	F_HL_TestLine06 = YES;	

//--**需更新的"数码管LED"显示内容**-------------------------//
		//Mode〓"关闭"此模块("动态数码管LED_Segment" )	
	Init_Mode_LED_Segment(MODE_Close_LED_Segment);

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
		//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	break;
	
case WORK_Microphone_Test: //Work▓Microphone_Test 测试(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	Disable_AlarmBuzzer();	//关闭:报警蜂鸣器
	Disable_Speaker(); //禁止:	"Speaker 扬声器" 

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_Basic_Check();  //显示//Main█Basic_Check 菜单选择(工作时)
	F_HL_TestLine07 = YES;	

//--**需更新的"数码管LED"显示内容**-------------------------//
		//Mode〓"关闭"此模块("动态数码管LED_Segment" )	
	Init_Mode_LED_Segment(MODE_Close_LED_Segment);

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
		//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	break;


case WORK_BQ27410_Test: //Work▓BQ27410_FuelGauge_Test 测试(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	mClose_LED_YELLOW; //配置引脚为"输出",并"熄灭"LED_YELLOW
	mClose_LED_RED; //配置引脚为"输出",并"熄灭"LED_RED
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	Disable_AlarmBuzzer();	//关闭:报警蜂鸣器
	Disable_Speaker(); //禁止:	"Speaker 扬声器" 

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_Basic_Check();  //显示//Main█Basic_Check 菜单选择(工作时)
	F_HL_TestLine08 = YES;  


//--**需更新的"数码管LED"显示内容**-------------------------//
		//Mode〓"关闭"此模块("动态数码管LED_Segment" )	
	Init_Mode_LED_Segment(MODE_Close_LED_Segment);

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
		//所有显示字符: //DISP◎"DISP_OFF_LcdSeg"--"段式LCD_Segment" 
	Disp_LCD_Segment(0,DISP_OFF_LcdSeg,DISP_OFF_LcdSeg,DISP_OFF_LcdSeg,DISP_OFF_LcdSeg,DISP_OFF_LcdSeg,DISP_OFF_LcdSeg);//"显示字符"更新到"显示缓存数组"(段式LCD_Segment)
		//Mode〓"打开"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Open_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
    F_Update_RealTime = NO;	    //此时，不刷新"实时时间"     
    F_Update_Temperature = NO;  //此时，不刷新"实时温度"  
    F_Update_CurrentValue = NO; //此时，不刷新"INA21x 实时电流值" 
    F_Update_Power = NO;        //此时，不刷新"锂电池电量"
	break;



////////////////////////////////////////////////////////////////////////////
//==**"相关测试" ( 工作菜单)** ===========================//
case WORK_Line_LCD_TFT:  //Work▓Line_LCD_TFT 测试(工作时)
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	
	Disp_MAIN_LCD_TFT_Test();  //显示//Main█LCD_TFT_Test 菜单选择(工作时)
	F_Update_TestLine02=YES;F_Update_TestLine03=YES;F_Update_TestLine04=YES;
	F_Update_TestLine05=YES;F_Update_TestLine06=YES;F_Update_TestLine07=YES;
	F_HL_TestLine02 = YES; 

	Init_GPIO_LCD_TFT_ILI9325();  //初始化: "彩屏LCD_TFT_ILI9325"  IO端口
	LCD_TFT_DrawLine(M_TestLine_09,M_TestColumn_02,M_TestLine_12+13,M_TestColumn_09+5,Fixed_Point);   
	break;

case WORK_Rectangle_LCD_TFT:  //Work▓Rectangle_LCD_TFT 测试(工作时)
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	
	Disp_MAIN_LCD_TFT_Test();  //显示//Main█LCD_TFT_Test 菜单选择(工作时)
	F_Update_TestLine02=YES;F_Update_TestLine03=YES;F_Update_TestLine04=YES;
	F_Update_TestLine05=YES;F_Update_TestLine06=YES;F_Update_TestLine07=YES;
	F_HL_TestLine03 = YES; 

	Init_GPIO_LCD_TFT_ILI9325();  //初始化: "彩屏LCD_TFT_ILI9325"  IO端口
	LCD_TFT_DrawRectangle(M_TestLine_10,M_TestColumn_03,M_TestLine_12,M_TestColumn_09,Fixed_Point);   
	break;


case WORK_Circle_LCD_TFT:  //Work▓Circle_LCD_TFT 测试(工作时)
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间

	Disp_MAIN_LCD_TFT_Test();  //显示//Main█LCD_TFT_Test 菜单选择(工作时)
	F_Update_TestLine02=YES;F_Update_TestLine03=YES;F_Update_TestLine04=YES;
	F_Update_TestLine05=YES;F_Update_TestLine06=YES;F_Update_TestLine07=YES;
	F_HL_TestLine04 = YES; 

	Init_GPIO_LCD_TFT_ILI9325();  //初始化: "彩屏LCD_TFT_ILI9325"  IO端口
	LCD_TFT_DrawCircle(M_TestLine_11-1,M_TestColumn_06,32,Fixed_Point);  
	break;

case WORK_FillArea_LCD_TFT:  //Work▓FillArea_LCD_TFT 测试(工作时)
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间

	Disp_MAIN_LCD_TFT_Test();  //显示//Main█LCD_TFT_Test 菜单选择(工作时)
	F_Update_TestLine02=YES;F_Update_TestLine03=YES;F_Update_TestLine04=YES;
	F_Update_TestLine05=YES;F_Update_TestLine06=YES;F_Update_TestLine07=YES;
	F_HL_TestLine05 = YES; 

	Init_GPIO_LCD_TFT_ILI9325();  //初始化: "彩屏LCD_TFT_ILI9325"  IO端口
	LCD_TFT_FillRectangle(M_TestLine_09,M_TestColumn_11,M_TestLine_12+8,M_TestColumn_19,Fixed_Point);
	break;
	
case WORK_Chinese_LCD_TFT:	//Work▓Chinese_LCD_TFT 测试(工作时)
	Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间

	Disp_MAIN_LCD_TFT_Test();  //显示//Main█LCD_TFT_Test 菜单选择(工作时)
	F_Update_TestLine02=YES;F_Update_TestLine03=YES;F_Update_TestLine04=YES;
	F_Update_TestLine05=YES;F_Update_TestLine06=YES;F_Update_TestLine07=YES;
	F_HL_TestLine06 = YES; 

	Init_GPIO_LCD_TFT_ILI9325();  //初始化: "彩屏LCD_TFT_ILI9325"  IO端口
	LCD_TFT_Show_ChFont2424(M_TestLine_09+4,M_TestColumn_12,0,Test_Back,Fixed_Point); 
	LCD_TFT_Show_ChFont2424(M_TestLine_09+4,M_TestColumn_12+24,1,Test_Back,Fixed_Point); 
	LCD_TFT_Show_ChFont2424(M_TestLine_09+4+24,M_TestColumn_12,2,Test_Back,Fixed_Point); 
	LCD_TFT_Show_ChFont2424(M_TestLine_09+4+24,M_TestColumn_12+24,4,Test_Back,Fixed_Point); 
	break;

case WORK_Clear_LCD_TFT:  //Work▓Clear_LCD_TFT 测试(工作时)
	Open_Buzzer(BuzzTime_Key);	//按键有效时，让蜂鸣叫指定时间

	Disp_MAIN_LCD_TFT_Test();  //显示//Main█LCD_TFT_Test 菜单选择(工作时)
	F_Update_TestLine02=YES;F_Update_TestLine03=YES;F_Update_TestLine04=YES;
	F_Update_TestLine05=YES;F_Update_TestLine06=YES;F_Update_TestLine07=YES;
	F_HL_TestLine07 = YES; 

	Init_GPIO_LCD_TFT_ILI9325();  //初始化: "彩屏LCD_TFT_ILI9325"  IO端口
	LCD_TFT_FillRectangle(M_TestLine_09-1, M_TestColumn_01,M_TestLine_12+15,M_TestColumn_20,Test_Back);
	break;


////////////////////////////////////////////////////////////////////////////
//==**"相关测试" ( 工作菜单)** ===========================//
case WORK_Idle_Step_Motor:      //Work▓Idle_Step_Motor 测试(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	Stop_Step_Motor();  //停转-"Step_Motor 步进电机"

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	
//--**需更新的"数码管LED"显示内容**-------------------------//
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
			//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	break;

case WORK_Stop_Step_Motor:      //Work▓Stop_Step_Motor 测试(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	Stop_Step_Motor();  //停转-"Step_Motor 步进电机"
	
//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_Step_Motor_Test();  //显示//Main█Step_Motor_Test 菜单选择(工作时) 
	F_Update_TestLine03=YES;F_Update_TestLine04=YES;F_Update_TestLine05=YES;
	F_HL_TestLine05 = YES; 

//--**需更新的"数码管LED"显示内容**-------------------------//
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
			//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	break;

	
case WORK_Positive_Step_Motor:  //Work▓Positive_Step_Motor 测试(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_Step_Motor_Test();  //显示//Main█Step_Motor_Test 菜单选择(工作时) 
	F_Update_TestLine03=YES;F_Update_TestLine04=YES;F_Update_TestLine05=YES;
	F_HL_TestLine03 = YES; 

//--**需更新的"数码管LED"显示内容**-------------------------//
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
			//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	break;

	
case WORK_Reverse_Step_Motor:   //Work▓Reverse_Step_Motor 测试(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_Step_Motor_Test();  //显示//Main█Step_Motor_Test 菜单选择(工作时) 
	F_Update_TestLine03=YES;F_Update_TestLine04=YES;F_Update_TestLine05=YES;
	F_HL_TestLine04 = YES; 

//--**需更新的"数码管LED"显示内容**-------------------------//
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
			//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	break;


////////////////////////////////////////////////////////////////////////////
//==**"相关测试" ( 工作菜单)** ===========================//
case WORK_Idle_DC_Motor:      //Work▓Idle_DC_Motor 测试(工作时)
//care--此状态用来，切换正反转的短暂间隔，即在换向前，要先停电机,之后再换向

//--**动作处理(相应的IO口输出)**------------------------------//
	Stop_DC_Motor();  //停转-"DC_Motor 直流电机"

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	
//--**需更新的"数码管LED"显示内容**-------------------------//
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
			//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	G_DC_SpeedCnt = 0;
	G_DC_Speed = 0;
	Open_Timing_In_Work(1500);  //人为定时1.5秒，让电机停转
	break;

case WORK_Stop_DC_Motor:      //Work▓Stop_DC_Motor 测试(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//
	Stop_DC_Motor();  //停转-"DC_Motor 直流电机"
	
//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_DC_Motor_Test();  //显示//Main█DC_Motor_Test 菜单选择(工作时) 
	F_Update_TestLine03=YES;F_Update_TestLine04=YES;F_Update_TestLine05=YES;
	F_HL_TestLine05 = YES; 

//--**需更新的"数码管LED"显示内容**-------------------------//
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
			//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	G_DC_SpeedCnt = 0;
	G_DC_Speed = 0;

	break;

	
case WORK_Positive_DC_Motor:  //Work▓Positive_DC_Motor 测试(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_DC_Motor_Test();  //显示//Main█DC_Motor_Test 菜单选择(工作时) 
	F_Update_TestLine03=YES;F_Update_TestLine04=YES;F_Update_TestLine05=YES;
	F_HL_TestLine03 = YES; 

//--**需更新的"数码管LED"显示内容**-------------------------//
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
			//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	G_DC_SpeedCnt = 0;
	G_DC_Speed = 0;

	break;

	
case WORK_Reverse_DC_Motor:   //Work▓Reverse_DC_Motor 测试(工作时)
//--**动作处理(相应的IO口输出)**------------------------------//

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
	Disp_MAIN_DC_Motor_Test();  //显示//Main█DC_Motor_Test 菜单选择(工作时) 
	F_Update_TestLine03=YES;F_Update_TestLine04=YES;F_Update_TestLine05=YES;
	F_HL_TestLine04 = YES; 

//--**需更新的"数码管LED"显示内容**-------------------------//
		//Mode〓"打开"此模块("动态数码管LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**需更新的"段式LCD_Segment"显示内容**--------------------//
			//Mode〓"关闭"此模块(段式LCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"标志位+变量"的相关初使化**---------------------------//
	G_DC_SpeedCnt = 0;
	G_DC_Speed = 0;

	break;


	



////////////////////////////////////////////////////////////////////////////
//==**"相关测试" ( 工作菜单)** ===========================//



////////////////////////////////////////////////////////////////////////////
//==**"相关测试" ( 工作菜单)** ===========================//


////////////////////////////////////////////////////////////////////////////
//==**"相关测试" ( 工作菜单)** ===========================//



////////////////////////////////////////////////////////////////////////////
//==**"相关测试" ( 工作菜单)** ===========================//



////////////////////////////////////////////////////////////////////////////
//==**: **=========================//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
default:
	
	break;
	}
	
}

/***************************************************************************
case :  //Work▓
//--**动作处理(相应的IO口输出)**------------------------------//

//--**需更新的液晶"LCD_TFT"显示内容**------------------------//
//--**需更新的"数码管LED"显示内容**-------------------------//
//--**需更新的"段式LCD_Segment"显示内容**--------------------//

//--**"标志位+变量"的相关初使化**---------------------------//

	break;

*************************************************************************/


