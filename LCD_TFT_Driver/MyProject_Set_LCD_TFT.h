/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 MyProject_Set_LCD_TFT.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■ 具体项目: LCD_TFT液晶显示部份(包括所有的液晶内容)-头文件
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



#ifndef  __MyProject_Set_LCD_TFT_H 
#define  __MyProject_Set_LCD_TFT_H 






////////////////////////////////////////////////////////////////////////////
//==**"常用"宏定义**General macro**==========================//
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
//==**此项目"专用"宏定义**Project-specific macro**==============//
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"函数"宏定义**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"函数声明**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**项目"专用" API 函数声明**Exported Project-specific API funcitions**=//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//--**显示:  "常用" 相关显示**-------------------------------------//
////////////////////////////////////////////////////////////////////////////


extern void Disp_RTC_CurrentTime(void);  //显示: RTC 实时时钟


extern void Disp_INA21x_CurrentValue(unsigned int INA21x_Ad); //显示: INA21x 实时"监测电流值"




////////////////////////////////////////////////////////////////////////////
//---**显示:  "菜单选择" 相关显示**------------------------------//
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
//--**显示:  "参数设置" 相当显示**-------------------------------//
////////////////////////////////////////////////////////////////////////////

extern void Disp_MAIN_ModifyTime(void);//显示//Main█"实时时间"修改状态
extern void Disp_ModifyTimeState(void); //显示时间修改过程
extern void Blink_ModifyTime(void);  //处理"实时时间"修改状态下的闪烁
extern void Dis_ModifyTimeError(void);  //显示"错误: 时间输入有误!"




extern void Disp_Set_ScreenSaver(void); //显示"屏保功能"设置(LCD)



////////////////////////////////////////////////////////////////////////////
//--**显示:  "工作状态"下的相当显示**-------------------------//
////////////////////////////////////////////////////////////////////////////


extern void Disp_01Page_MenuLine(void);  //显示第1页"工作菜单"(LCD)(1.Work_A  2.Work_B  3.Work_C  4.Work_D

extern void Disp_02Page_MenuLine(void);  //显示第2页"工作菜单"(LCD)(1.Work_A  2.Work_B  3.Work_C  4.Work_D




extern void Disp_SelectFlag(void);  //显示"选中标志"  "=>"


extern void Disp_MAIN_Basic_Settings(void);  //显示//Main█Basic_Settings 菜单选择(工作时)

extern void Disp_MAIN_Basic_Check(void);  //显示//Main█Basic_Check 菜单选择(工作时)

extern void Disp_MAIN_LCD_TFT_Test(void);  //显示//Main█LCD_TFT_Test 菜单选择(工作时)

extern void Disp_MAIN_MatrixKey_Test(void);  //显示//Main█MatrixKey_Test 菜单选择(工作时)

extern void Disp_MatrixKey_Press(void); //根据按下的"矩阵按键"，在测试区域显示"按键值"

	
	//显示//Main█TouchPads_Test 菜单选择(工作时)
extern void Disp_MAIN_TouchPads_Test(void);  

	//显示//Main█INA21x_Current_Test 菜单选择(工作时)
extern void Disp_MAIN_INA21x_Current_Test(void);

	//在"测试行"显示: INA21x 实时"监测电流值"
extern void Disp_INA21x_Current_InTest(void);


	//显示//Main█Potentiometer_Test 菜单选择(工作时)
extern void Disp_MAIN_Potentiometer_Test(void);  
	//在"测试行"显示: 电位计Potentiometer 实时"电压值"
extern void Disp_Potentiometer_InTest(void);


	//显示//Main█NTC_HR202_Test(温湿度) 菜单选择(工作时)
extern void Disp_MAIN_NTC_HR202_Test(void);

extern void Disp_NTC_TMP(int NTC_TMP_Ad);  //显示: 实时"NTC 热敏电阻值"对应的温度

extern void Disp_HR202_Humidity(unsigned char humidity); //显示: "HR202_Humidity " 湿度





	//显示//Main█Step_Motor_Test 菜单选择(工作时) 
extern void Disp_MAIN_Step_Motor_Test(void);


	//显示//Main█DC_Motor_Test 菜单选择(工作时)  
extern void Disp_MAIN_DC_Motor_Test(void);
	//在"测试电机"显示速度给定电压值: 电位计Potentiometer 实时"电压值"
extern void Disp_Potentiometer_Motor(void);
extern void Disp_Speed_Step_Motor(void); //在"测试Step_Motor"显示电机速度
extern void Disp_Speed_DC_Motor(void); //在"测试DC_Motor"显示电机速度



	//显示//Main█TMP006_Temperature 菜单选择(工作时) 
extern void Disp_MAIN_TMP006_Temperature(void);
extern void Disp_TMP006_Temperature(void); //在LCD_TFT上，显示"温度"
extern void Disp_TMP006_TemperatureInTest(void);//在LCD_TFT上，显示"温度"

	
	//显示//Main█TMP100_Temperature 菜单选择(工作时) 
extern void Disp_MAIN_TMP100_Temperature(void);


extern void Disp_MAIN_IrDA_UART(void); //显示//Main█IrDA_UART 菜单选择(工作时)
extern void Disp_IrDA_Test(void); //显示IrDA是否收到数据



extern void Disp_MAIN_RS232_UART(void); //显示//Main█RS232_UART 菜单选择(工作时)
extern void Disp_RS232_Char_1(void); //显示RS485收到数据"1" (字符)	
extern void Disp_RS232_Char_2(void); //显示RS485收到数据"2" (字符)	
extern void Disp_RS232_None(void); //清显示RS232收到数据


extern void Disp_MAIN_RS485_UART(void); //显示//Main█RS485_UART 菜单选择(工作时)
extern void Disp_RS485_Char_1(void); //显示RS485收到数据"1" (字符)	
extern void Disp_RS485_Char_2(void); //显示RS485收到数据"2" (字符)	



extern void Disp_MAIN_CC1101_Test(void); //显示//Main█CC1101_Test 菜单选择(工作时)
extern void Disp_CC1101_Char_1(void); //显示CC1101收到数据"1" (字符)	
extern void Disp_CC1101_Char_2(void); //显示CC1101收到数据"2" (字符)		




extern void Disp_MAIN_SD_Card_Test(void);  //显示//Main█SD_Card_Test 菜单选择(工作时)
extern void Disp_SD_Card_Char(void); //显示SD_Card读到的数据 (字符)		


extern void Disp_MAIN_MassStorage_Test(void); //显示//Main█MassStorage_Test 菜单选择(工作时)

#endif   /* __MyProject_Set_LCD_TFT_H  */





