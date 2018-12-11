/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 MyProject_Set_LCD_TFT.c
* 附属文件-Dependencies:  	 MyProject_Set_LCD_TFT.h; System_HeadFile.h; 
* 文件描述-File Description:	 ( 源程序-Source File) 
	■ 具体项目: LCD_TFT液晶显示部份(包括所有的液晶内容)
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

	//具体项目: LCD_TFT液晶显示部份(包括所有的液晶内容) -头文件
#include "MyProject_Set_LCD_TFT.h"  



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//--**显示: "广告"**---------------------------------------------------//
////////////////////////////////////////////////////////////////////////////

//const unsigned char Msg_AD_1[] = {"  Welcome to MSP430F6638   \0"}; //22 (总28字节) 
//const unsigned char Msg_AD_2[] = {"    http://www.ti.com      \0"}; //17(总28字节) 
//const unsigned char Msg_AD_3[] = {"Error A  6638-V1.0  Error'C\0"}; //(总28字节)  // "版本号 " 广告


//const unsigned char Msg_Temp[] = {"123456789abcdefgADCDEFGHIJK\0"};


////////////////////////////////////////////////////////////////////////////
//--**显示: "实时时间"**--------------------------------------------//
////////////////////////////////////////////////////////////////////////////
//const unsigned char Msg_RealTime[] = {"2012-12-12 00:00:00 FRI\0"}; 

const unsigned char Msg_Error_ModifyTime[] = {"Setting Error!      \0"}; // (总21字节) 
const unsigned char Msg_Error_ReEnter[] =    {"Please Re-enter!    \0"}; // (总21字节) 







////////////////////////////////////////////////////////////////////////////
//--**显示: " 工作菜单"**-------------------------------------------//
////////////////////////////////////////////////////////////////////////////
const unsigned char Msg_ClearLine[] =  {"                           \0"}; // (总28字节) 
const unsigned char Msg_SelectFlag[] = {"=>"}; // (总2字节) //选中标志

const unsigned char Msg_01Page_MenuLine_01[] = {"      M E N U      \0"}; // (总20字节) 
const unsigned char Msg_01Page_MenuLine_02[] = {"01.Basic--Setting  \0"}; // (总20字节) 
const unsigned char Msg_01Page_MenuLine_03[] = {"02.Basic--Check    \0"}; // (总20字节) 
const unsigned char Msg_01Page_MenuLine_04[] = {"03.LCD_TFT         \0"}; // (总20字节) 
const unsigned char Msg_01Page_MenuLine_05[] = {"04.Matrix Key      \0"}; // (总20字节) 
const unsigned char Msg_01Page_MenuLine_06[] = {"05.Touch Pads      \0"}; // (总20字节) 
const unsigned char Msg_01Page_MenuLine_07[] = {"06.INA21x--Current \0"}; // (总20字节) 
const unsigned char Msg_01Page_MenuLine_08[] = {"07.TMP006          \0"}; // (总20字节) 
const unsigned char Msg_01Page_MenuLine_09[] = {"08.Volt Meter--ADC \0"}; // (总20字节) 
const unsigned char Msg_01Page_MenuLine_10[] = {"09.DC--Motor       \0"}; // (总20字节) 
const unsigned char Msg_01Page_MenuLine_11[] = {"10.Step--Motor     \0"}; // (总20字节) 
const unsigned char Msg_01Page_MenuLine_12[] = {"11.NTC and HR202   \0"}; // (总20字节) 

const unsigned char Msg_02Page_MenuLine_01[] = {"      M E N U      \0"}; // (总20字节) 
const unsigned char Msg_02Page_MenuLine_02[] = {"12.IrDA  - UART    \0"}; // (总20字节) 
const unsigned char Msg_02Page_MenuLine_03[] = {"13.RS232 - UART    \0"}; // (总20字节) 
const unsigned char Msg_02Page_MenuLine_04[] = {"14.RS485 - UART    \0"}; // (总20字节) 
const unsigned char Msg_02Page_MenuLine_05[] = {"15.CC1101 - 433MHz \0"}; // (总20字节) 
const unsigned char Msg_02Page_MenuLine_06[] = {"16.SD Card         \0"}; // (总20字节) 
const unsigned char Msg_02Page_MenuLine_07[] = {"17.USB - SD Card   \0"}; // (总20字节) 
const unsigned char Msg_02Page_MenuLine_08[] = {"                   \0"}; // (总20字节) 
const unsigned char Msg_02Page_MenuLine_09[] = {"                   \0"}; // (总20字节) 
const unsigned char Msg_02Page_MenuLine_10[] = {"                   \0"}; // (总20字节) 
const unsigned char Msg_02Page_MenuLine_11[] = {"                   \0"}; // (总20字节) 
const unsigned char Msg_02Page_MenuLine_12[] = {"                   \0"}; // (总20字节) 




////////////////////////////////////////////////////////////////////////////
//--**显示: " 工作测试内容"**--------------------------------------//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//--**"工作状态" 标志**---------------------------------------------//


////////////////////////////////////////////////////////////////////////////
//--**01.工作菜单"的测试内容**----------------------------------//

const unsigned char Msg_01Test_Line01[] = {"  01.Basic--Setting \0"}; // (总21字节) 
const unsigned char Msg_01Test_Line02[] = {"1.Restart Self-Test \0"}; // (总21字节) 
const unsigned char Msg_01Test_Line03[] = {"2.Time Setting      \0"}; // (总21字节) 
const unsigned char Msg_01Test_Line04[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_01Test_Line05[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_01Test_Line06[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_01Test_Line07[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_01Test_Line08[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_01Test_Line09[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_01Test_Line10[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_01Test_Line11[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_01Test_Line12[] = {"                    \0"}; // (总21字节) 


////////////////////////////////////////////////////////////////////////////
//--**02.工作菜单"的测试内容**----------------------------------//
const unsigned char Msg_02Test_Line01[] = {"  02.Basic--Check   \0"}; // (总21字节) 
const unsigned char Msg_02Test_Line02[] = {"1.LED_Diode - SOS   \0"}; // (总21字节) 
const unsigned char Msg_02Test_Line03[] = {"2.LED_Segment       \0"}; // (总21字节) 
const unsigned char Msg_02Test_Line04[] = {"3.LCD_Segment       \0"}; // (总21字节) 
const unsigned char Msg_02Test_Line05[] = {"4.Buzzer - Alarm    \0"}; // (总21字节) 
const unsigned char Msg_02Test_Line06[] = {"5.Speaker - Sing    \0"}; // (总21字节) 
const unsigned char Msg_02Test_Line07[] = {"6.Microphone -Record\0"}; // (总21字节) 
const unsigned char Msg_02Test_Line08[] = {"7.Battery Fuel Gauge\0"}; // (总21字节) 
const unsigned char Msg_02Test_Line09[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_02Test_Line10[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_02Test_Line11[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_02Test_Line12[] = {"                    \0"}; // (总21字节) 


////////////////////////////////////////////////////////////////////////////
//--**03.工作菜单"的测试内容**----------------------------------//
const unsigned char Msg_03Test_Line01[] = {"  03.LCD_TFT        \0"}; // (总21字节) 
const unsigned char Msg_03Test_Line02[] = {"1.Line              \0"}; // (总21字节) 
const unsigned char Msg_03Test_Line03[] = {"2.Rectangle         \0"}; // (总21字节) 
const unsigned char Msg_03Test_Line04[] = {"3.Circle            \0"}; // (总21字节) 
const unsigned char Msg_03Test_Line05[] = {"4.Fill Area         \0"}; // (总21字节) 
const unsigned char Msg_03Test_Line06[] = {"5.Chinese           \0"}; // (总21字节) 
const unsigned char Msg_03Test_Line07[] = {"6.Clear             \0"}; // (总21字节) 
const unsigned char Msg_03Test_Line08[] = {"********************\0"}; // (总21字节) 
const unsigned char Msg_03Test_Line09[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_03Test_Line10[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_03Test_Line11[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_03Test_Line12[] = {"                    \0"}; // (总21字节) 


////////////////////////////////////////////////////////////////////////////
//--**04.工作菜单"的测试内容**----------------------------------//
const unsigned char Msg_04Test_Line01[] = {"  04.Matrix Key     \0"}; // (总21字节) 
const unsigned char Msg_04Test_Line02[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_04Test_Line03[] = {"Press the matrix key\0"}; // (总21字节) 
const unsigned char Msg_04Test_Line04[] = {"one by one.         \0"}; // (总21字节) 
const unsigned char Msg_04Test_Line05[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_04Test_Line06[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_04Test_Line07[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_04Test_Line08[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_04Test_Line09[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_04Test_Line10[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_04Test_Line11[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_04Test_Line12[] = {"                    \0"}; // (总21字节) 


////////////////////////////////////////////////////////////////////////////
//--**05.工作菜单"的测试内容**----------------------------------//
const unsigned char Msg_05Test_Line01[] = {"  05.Touch Pads     \0"}; // (总21字节) 
const unsigned char Msg_05Test_Line02[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_05Test_Line03[] = {"Press the touch pads\0"}; // (总21字节) 
const unsigned char Msg_05Test_Line04[] = {"one by one.         \0"}; // (总21字节) 
const unsigned char Msg_05Test_Line05[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_05Test_Line06[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_05Test_Line07[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_05Test_Line08[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_05Test_Line09[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_05Test_Line10[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_05Test_Line11[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_05Test_Line12[] = {"                    \0"}; // (总21字节) 


////////////////////////////////////////////////////////////////////////////
//--**06.工作菜单"的测试内容**----------------------------------//
const unsigned char Msg_06Test_Line01[] = {"  06.INA21x--Current\0"}; // (总21字节) 
const unsigned char Msg_06Test_Line02[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_06Test_Line03[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_06Test_Line04[] = {"Current: FFF mA     \0"}; // (总21字节) 
const unsigned char Msg_06Test_Line05[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_06Test_Line06[] = {"The LED_Segment also\0"}; // (总21字节) 
const unsigned char Msg_06Test_Line07[] = {"displays the current\0"}; // (总21字节) 
const unsigned char Msg_06Test_Line08[] = {"value.              \0"}; // (总21字节) 
const unsigned char Msg_06Test_Line09[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_06Test_Line10[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_06Test_Line11[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_06Test_Line12[] = {"                    \0"}; // (总21字节) 





////////////////////////////////////////////////////////////////////////////
//--**07.工作菜单"的测试内容**----------------------------------//
const unsigned char Msg_07Test_Line01[] = {"  07.TMP006         \0"}; // (总21字节) 
const unsigned char Msg_07Test_Line02[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_07Test_Line03[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_07Test_Line04[] = {"Temperature:FFF.F 'C\0"}; // (总21字节) 
const unsigned char Msg_07Test_Line05[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_07Test_Line06[] = {"The LED_Segment also\0"}; // (总21字节) 
const unsigned char Msg_07Test_Line07[] = {"displays temperature\0"}; // (总21字节) 
const unsigned char Msg_07Test_Line08[] = {"value.              \0"}; // (总21字节) 
const unsigned char Msg_07Test_Line09[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_07Test_Line10[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_07Test_Line11[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_07Test_Line12[] = {"                    \0"}; // (总21字节) 


////////////////////////////////////////////////////////////////////////////
//--**08.工作菜单"的测试内容**----------------------------------//
const unsigned char Msg_08Test_Line01[] = {"  08.Volt Meter--ADC\0"}; // (总21字节) 
const unsigned char Msg_08Test_Line02[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_08Test_Line03[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_08Test_Line04[] = {"Voltage: F.FF V     \0"}; // (总21字节) 
const unsigned char Msg_08Test_Line05[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_08Test_Line06[] = {"The LED_Segment also\0"}; // (总21字节) 
const unsigned char Msg_08Test_Line07[] = {"displays the voltage\0"}; // (总21字节) 
const unsigned char Msg_08Test_Line08[] = {"value.              \0"}; // (总21字节) 
const unsigned char Msg_08Test_Line09[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_08Test_Line10[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_08Test_Line11[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_08Test_Line12[] = {"                    \0"}; // (总21字节) 





////////////////////////////////////////////////////////////////////////////
//--**09.工作菜单"的测试内容**----------------------------------//
const unsigned char Msg_09Test_Line01[] = {"  09.DC--Motor      \0"}; // (总21字节) 
const unsigned char Msg_09Test_Line02[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_09Test_Line03[] = {"1.Positive Rotation \0"}; // (总21字节) 
const unsigned char Msg_09Test_Line04[] = {"2.Reverse Rotation  \0"}; // (总21字节) 
const unsigned char Msg_09Test_Line05[] = {"3.Stop DC-Motor     \0"}; // (总21字节) 
const unsigned char Msg_09Test_Line06[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_09Test_Line07[] = {"Voltage: F.F V      \0"}; // (总21字节) 
const unsigned char Msg_09Test_Line08[] = {"  Speed: FFFFF r/min\0"}; // (总21字节) 
const unsigned char Msg_09Test_Line09[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_09Test_Line10[] = {"The LED_Segment also\0"}; // (总21字节) 
const unsigned char Msg_09Test_Line11[] = {"displays the voltage\0"}; // (总21字节) 
const unsigned char Msg_09Test_Line12[] = {"and speed.          \0"}; // (总21字节) 

////////////////////////////////////////////////////////////////////////////
//--**10.工作菜单"的测试内容**----------------------------------//
const unsigned char Msg_10Test_Line01[] = {"  10.Step--Motor    \0"}; // (总21字节) 
const unsigned char Msg_10Test_Line02[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_10Test_Line03[] = {"1.Positive Rotation \0"}; // (总21字节) 
const unsigned char Msg_10Test_Line04[] = {"2.Reverse Rotation  \0"}; // (总21字节) 
const unsigned char Msg_10Test_Line05[] = {"3.Stop Step-Motor   \0"}; // (总21字节) 
const unsigned char Msg_10Test_Line06[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_10Test_Line07[] = {"Voltage: F.F V      \0"}; // (总21字节) 
const unsigned char Msg_10Test_Line08[] = {"  Speed: FFF.F r/min\0"}; // (总21字节) 
const unsigned char Msg_10Test_Line09[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_10Test_Line10[] = {"The LED_Segment also\0"}; // (总21字节) 
const unsigned char Msg_10Test_Line11[] = {"displays the voltage\0"}; // (总21字节) 
const unsigned char Msg_10Test_Line12[] = {"and speed.          \0"}; // (总21字节) 


////////////////////////////////////////////////////////////////////////////
//--**11.工作菜单"的测试内容**----------------------------------//
const unsigned char Msg_11Test_Line01[] = {"  11.NTC and HR202  \0"}; // (总21字节) 
const unsigned char Msg_11Test_Line02[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_11Test_Line03[] = {"Temperature:FFF.F 'C\0"}; // (总21字节) 
const unsigned char Msg_11Test_Line04[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_11Test_Line05[] = {"   Humidity: FFF %RH\0"}; // (总21字节) 
const unsigned char Msg_11Test_Line06[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_11Test_Line07[] = {"The LED_Segment also\0"}; // (总21字节) 
const unsigned char Msg_11Test_Line08[] = {"displays temperature\0"}; // (总21字节) 
const unsigned char Msg_11Test_Line09[] = {"and humidity.       \0"}; // (总21字节) 
const unsigned char Msg_11Test_Line10[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_11Test_Line11[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_11Test_Line12[] = {"                    \0"}; // (总21字节) 


////////////////////////////////////////////////////////////////////////////
//--**12.工作菜单"的测试内容**----------------------------------//
const unsigned char Msg_12Test_Line01[] = {"  12.IrDA  - UART   \0"}; // (总21字节) 
const unsigned char Msg_12Test_Line02[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_12Test_Line03[] = {"Take something on   \0"}; // (总21字节) 
const unsigned char Msg_12Test_Line04[] = {"the front of the    \0"}; // (总21字节) 
const unsigned char Msg_12Test_Line05[] = {"IrDA receiver.      \0"}; // (总21字节) 
const unsigned char Msg_12Test_Line06[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_12Test_Line07[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_12Test_Line08[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_12Test_Line09[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_12Test_Line10[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_12Test_Line11[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_12Test_Line12[] = {"                    \0"}; // (总21字节) 

const unsigned char Msg_12Test_TXT1[] =   {"  IrDA receives '1' \0"}; // (总28字节) 
const unsigned char Msg_12Test_TXT2[] =   {"                    \0"}; // (总21字节) 




////////////////////////////////////////////////////////////////////////////
//--**13.工作菜单"的测试内容**----------------------------------//
const unsigned char Msg_13Test_Line01[] = {"  13.RS232 - UART   \0"}; // (总21字节) 
const unsigned char Msg_13Test_Line02[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_13Test_Line03[] = {"1.Send 'RS232' to PC\0"}; // (总21字节) 
const unsigned char Msg_13Test_Line04[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_13Test_Line05[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_13Test_Line06[] = {"If PC sends data to \0"}; // (总21字节) 
const unsigned char Msg_13Test_Line07[] = {"6638, the 6638 will \0"}; // (总21字节) 
const unsigned char Msg_13Test_Line08[] = {"sent it back.       \0"}; // (总21字节) 
const unsigned char Msg_13Test_Line09[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_13Test_Line10[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_13Test_Line11[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_13Test_Line12[] = {"                    \0"}; // (总21字节) 

const unsigned char Msg_13Test_TXT1[] =   {"  6638 receives '1' \0"}; // (总21字节) 
const unsigned char Msg_13Test_TXT2[] =   {"  6638 receives '2'.\0"}; // (总21字节) 
const unsigned char Msg_13Test_TXT3[] =   {"                    \0"}; // (总21字节) 






////////////////////////////////////////////////////////////////////////////
//--**14.工作菜单"的测试内容**----------------------------------//
const unsigned char Msg_14Test_Line01[] = {"  14.RS485 - UART   \0"}; // (总21字节) 
const unsigned char Msg_14Test_Line02[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_14Test_Line03[] = {"1.Send '1' to others\0"}; // (总21字节) 
const unsigned char Msg_14Test_Line04[] = {"2.Send '2' to others\0"}; // (总21字节) 
const unsigned char Msg_14Test_Line05[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_14Test_Line06[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_14Test_Line07[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_14Test_Line08[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_14Test_Line09[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_14Test_Line10[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_14Test_Line11[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_14Test_Line12[] = {"                    \0"}; // (总21字节) 

const unsigned char Msg_14Test_TXT1[] =   {" RS485 receives '1'.\0"}; //  (总21字节) 
const unsigned char Msg_14Test_TXT2[] =   {" RS485 receives '2'.\0"}; //  (总21字节)  

////////////////////////////////////////////////////////////////////////////
//--**15.工作菜单"的测试内容**----------------------------------//
const unsigned char Msg_15Test_Line01[] = {"  15.CC1101 - 433MHz\0"}; // (总21字节) 
const unsigned char Msg_15Test_Line02[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_15Test_Line03[] = {"1.Send '1' to others\0"}; // (总21字节) 
const unsigned char Msg_15Test_Line04[] = {"2.Send '2' to others\0"}; // (总21字节) 
const unsigned char Msg_15Test_Line05[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_15Test_Line06[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_15Test_Line07[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_15Test_Line08[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_15Test_Line09[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_15Test_Line10[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_15Test_Line11[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_15Test_Line12[] = {"                    \0"}; // (总21字节) 

const unsigned char Msg_15Test_TXT1[] =   {"CC1101 receives '1'.\0"}; //  (总21字节) 
const unsigned char Msg_15Test_TXT2[] =   {"CC1101 receives '2'.\0"}; //  (总21字节)  


////////////////////////////////////////////////////////////////////////////
//--**16.工作菜单"的测试内容**----------------------------------//
const unsigned char Msg_16Test_Line01[] = {"  15.SD Card        \0"}; // (总21字节) 
const unsigned char Msg_16Test_Line02[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_16Test_Line03[] = {"Key--Write:         \0"}; // (总21字节) 
const unsigned char Msg_16Test_Line04[] = {"Key-- Read:         \0"}; // (总21字节) 
const unsigned char Msg_16Test_Line05[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_16Test_Line06[] = {"Press a matrix key, \0"}; // (总21字节) 
const unsigned char Msg_16Test_Line07[] = {"6638 will write the \0"}; // (总21字节) 
const unsigned char Msg_16Test_Line08[] = {"key value into SD.  \0"}; // (总21字节) 
const unsigned char Msg_16Test_Line09[] = {"Then, use a PC to   \0"}; // (总21字节) 
const unsigned char Msg_16Test_Line10[] = {"read the data of SD.\0"}; // (总21字节) 
const unsigned char Msg_16Test_Line11[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_16Test_Line12[] = {"                    \0"}; // (总21字节) 





////////////////////////////////////////////////////////////////////////////
//--**17.工作菜单"的测试内容**----------------------------------//
const unsigned char Msg_17Test_Line01[] = {"  17.USB - SD Card  \0"}; // (总21字节) 
const unsigned char Msg_17Test_Line02[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_17Test_Line03[] = {"1.Connect to PC     \0"}; // (总21字节) 
const unsigned char Msg_17Test_Line04[] = {"2.Disconnect        \0"}; // (总21字节) 
const unsigned char Msg_17Test_Line05[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_17Test_Line06[] = {"                    \0"}; // (总21字节) 
const unsigned char Msg_17Test_Line07[] = {"Connect the 'USB1'  \0"}; // (总21字节) 
const unsigned char Msg_17Test_Line08[] = {"(on 6638) to PC with\0"}; // (总21字节) 
const unsigned char Msg_17Test_Line09[] = {"a usb cable.        \0"}; // (总21字节) 
const unsigned char Msg_17Test_Line10[] = {"If connected,you can\0"}; // (总21字节) 
const unsigned char Msg_17Test_Line11[] = {"see 'removable disk'\0"}; // (总21字节) 
const unsigned char Msg_17Test_Line12[] = {"on your PC.         \0"}; // (总21字节) 




////////////////////////////////////////////////////////////////////////////
//--**显示: " 基本参数设置菜单"**-------------------------------//
////////////////////////////////////////////////////////////////////////////
//const unsigned char Msg_BasicMenu_1[] = {"基本参数设置"}; //(第1行)
//const unsigned char Msg_BasicMenu_2[] = {" 1、时间修改"};  //(第3行)
//const unsigned char Msg_BasicMenu_3[] = {" 2、屏保功能"};  //(第4行)
//const unsigned char Msg_BasicMenu_4[] = {" 3、密码修改"};  //(第5行)


////////////////////////////////////////////////////////////////////////////
//--**显示: " 时间修改菜单"**-------------------------------------//
////////////////////////////////////////////////////////////////////////////
//const unsigned char Msg_Set_Time_1[] = {"时间修改"}; //(第1行)
//const unsigned char Msg_Set_Time_2[] = {"----年--月--日--: --"}; //共20字节  //(第3行)	   


////////////////////////////////////////////////////////////////////////////
//--**显示: " 屏保功能修改菜单"**-------------------------------//
////////////////////////////////////////////////////////////////////////////
//const unsigned char Msg_Set_ScreenSaver_1[] = {"屏保功能修改"}; //(第1行)
   
//const unsigned char Msg_Set_ScreenSaver_2[] = {"1.屏保选择: "};  //(第3行)
//const unsigned char Msg_Set_ScreenSaver_3[] = {"2.屏保时间: ---- 秒"};  //(第4行)



////////////////////////////////////////////////////////////////////////////
//--**显示: "帐户"**---------------------------------------------------//
////////////////////////////////////////////////////////////////////////////
//const unsigned char Msg_Count_1[] = {"请输入 6位数字密码"}; //(第1行)
//const unsigned char Msg_Count_2[] = {"输入密码: ------"};   //(第3行)

//const unsigned char Msg_Count_3[] = {"修改管理员密码"}; //共14字节//(第1行)
//const unsigned char Msg_Count_4[] = {"输入新密码: ------"}; //共18字节//(第3行)	   





////////////////////////////////////////////////////////////////////////////
//--**显示: " 设置正确"**--------------------------------------------//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//--**显示: " 设置错误"**--------------------------------------------//
////////////////////////////////////////////////////////////////////////////
//const unsigned char Msg_Error_1[]={"请重新输入"};  //(30字节)



////////////////////////////////////////////////////////////////////////////
//--**显示: " 工作状态下"**-----------------------------------------//
////////////////////////////////////////////////////////////////////////////

//const unsigned char Msg_Work_1[] = {""}; //(30字节)







////////////////////////////////////////////////////////////////////////////
//--**显示:  "常用" 相关显示**-------------------------------------//
///////////////////////////////////////////////////////////////////////////





/****************************************************************************
*函数名-Function:	void Disp_RTC_CurrentTime(void)
*描述- Description:	显示: RTC 实时时钟
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_RTC_CurrentTime(void)
{
	if(F_SecondChange_RTC)
	{
		F_SecondChange_RTC = 0;
		
		Copy_Array_AtoB(&G_LcdBuf[M_15LineBuf][M_01ColumnBuf], G_RTC_ReadBuf, 23);
		
		F_Update_RealTime = YES;	 //刷新:"实时时间"	
	}
}



/****************************************************************************
*函数名-Function:	void Disp_INA21x_CurrentValue(unsigned int INA21x_Ad)
*描述- Description:	显示: INA21x 实时"监测电流值"
*输入参数-Input:	INA21x_Ad : 要显示的实际电流值
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_INA21x_CurrentValue(unsigned int INA21x_Ad)
{
	unsigned char b,c,d;  
	
//	a = (unsigned char)(INA21x_Ad/1000);
	b = (unsigned char)((INA21x_Ad % 1000)/100);
	c = (unsigned char)((INA21x_Ad % 100)/10);
	d = (unsigned char)(INA21x_Ad % 10);


		//刷新要显示的"实际电流值"，单位A,显示250A
	//G_LcdBuf[M_15LineBuf][M_24ColumnBuf] = ASCII_Table[a];   //个位
	//G_LcdBuf[M_15LineBuf][M_Start_Column_Buf+1] = '.';   //小数点
	G_LcdBuf[M_15LineBuf][M_31ColumnBuf] = ASCII_Table[b];	 //第一位
	if(b == 0) G_LcdBuf[M_15LineBuf][M_31ColumnBuf] = 0x20;
	G_LcdBuf[M_15LineBuf][M_32ColumnBuf] = ASCII_Table[c];   //第二位
	G_LcdBuf[M_15LineBuf][M_33ColumnBuf] = ASCII_Table[d];   //第三位
	G_LcdBuf[M_15LineBuf][M_34ColumnBuf] = 'm';   
	G_LcdBuf[M_15LineBuf][M_35ColumnBuf] = 'A';  

	F_Update_CurrentValue = YES; //刷新:"INA21x 实时电流值" 
}






/****************************************************************************
*函数名-Function:	void Disp_NTC_TMP(int NTC_TMP_Ad)
*描述- Description:	显示: 实时"NTC 热敏电阻值"对应的温度
*输入参数-Input:	NTC_TMP_Ad :  NTC 最后得出的温度值(经过处理)
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_NTC_TMP(int NTC_TMP_Ad)
{
	unsigned char a,b,c,d;
	
	if(NTC_TMP_Ad < 0)
	{
		NTC_TMP_Ad = - NTC_TMP_Ad;
		
		b = (unsigned char)((NTC_TMP_Ad % 1000)/100);  //十位
		c = (unsigned char)((NTC_TMP_Ad % 100)/10);    //个位
		d = (unsigned char)(NTC_TMP_Ad % 10);          //小数第一位

		G_LcdBuf[TestLine03][TestColumn13] = '-';//百位 
		G_LcdBuf[TestLine03][TestColumn14] = ASCII_Table[b]; //十位
		G_LcdBuf[TestLine03][TestColumn15] = ASCII_Table[c]; //个位
		G_LcdBuf[TestLine03][TestColumn16] = '.'; //小数点
		G_LcdBuf[TestLine03][TestColumn17] = ASCII_Table[d]; //小数第一位

		if(b == 0) 
		{
			G_LcdBuf[TestLine03][TestColumn13] = 0x20;//百位
			G_LcdBuf[TestLine03][TestColumn14] = '-'; //十位	
		}

	}
	else
	{
		a = (unsigned char)(NTC_TMP_Ad/1000);
		b = (unsigned char)((NTC_TMP_Ad % 1000)/100);
		c = (unsigned char)((NTC_TMP_Ad % 100)/10);
		d = (unsigned char)(NTC_TMP_Ad % 10);

		G_LcdBuf[TestLine03][TestColumn13] = ASCII_Table[a];//百位	 
		G_LcdBuf[TestLine03][TestColumn14] = ASCII_Table[b]; //十位
		G_LcdBuf[TestLine03][TestColumn15] = ASCII_Table[c]; //个位
		G_LcdBuf[TestLine03][TestColumn16] = '.'; //小数点
		G_LcdBuf[TestLine03][TestColumn17] = ASCII_Table[d]; //小数第一位

		if(a == 0) 
		{
			G_LcdBuf[TestLine03][TestColumn13] = 0x20; //百位	 
		}
		else if((a == 0)&&(b == 0))
		{
			G_LcdBuf[TestLine03][TestColumn13] = 0x20; //百位	
			G_LcdBuf[TestLine03][TestColumn14] = 0x20; //十位	
		}
	}

		//刷新要显示的"实际湿度值值"，显示123.4'C

//G_LcdBuf[TestLine03][M_Start_Column_Buf+25] = '\'';   
//G_LcdBuf[TestLine03][M_Start_Column_Buf+26] = 'C';  

	F_Update_TestLine03 = YES; //刷新:""测试行"" 
}


/****************************************************************************
*函数名-Function:	void Disp_HR202_Humidity(unsigned char humidity)
*描述- Description:	显示: "HR202_Humidity " 湿度
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_HR202_Humidity(unsigned char humidity)
{
	G_LcdBuf[TestLine05][TestColumn14] = ASCII_Table[humidity /100];   //百位
	if((humidity /100) == 0) G_LcdBuf[TestLine05][TestColumn14] = 0x20;   //百位
	
	G_LcdBuf[TestLine05][TestColumn15] = ASCII_Table[(humidity /10)% 10];   //十位
	G_LcdBuf[TestLine05][TestColumn16] = ASCII_Table[humidity % 10];   //个位
//G_LcdBuf[TestLine05][M_Start_Column_Buf+26] = '%'; //单位 

	F_Update_TestLine05 = YES; //刷新:""测试行"" 
}




////////////////////////////////////////////////////////////////////////////
//--**显示:  "菜单选择" 相当显示**-------------------------------//
////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////
//--**显示:  "参数设置" 相关显示**-------------------------------//
////////////////////////////////////////////////////////////////////////////


/****************************************************************************
*函数名-Function:	void Disp_MAIN_ModifyTime(void)
*描述- Description:	//显示//Main█"实时时间"修改状态
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_MAIN_ModifyTime(void)//显示//Main█"实时时间"修改状态
{

	F_HL_TestLine03 = YES;	 //反白2.Time Setting
	F_Update_TestLine03 = YES;

		//修改的"2013-01-01"
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn03], G_RTC_ReadBuf, 11);
	G_LcdBuf[TestLine08][TestColumn14] = '\0';  //送结束符'\0'	
	F_Update_TestLine08 = YES;	//显示修改的"2013-01-01"

		//修改的"00:00:00"
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn03],&G_RTC_ReadBuf[11], 9);
	G_LcdBuf[TestLine09][TestColumn14] = '\0';  //送结束符'\0'	
	F_Update_TestLine09 = YES;	//显示修改的"00:00:00"

		//修改的"星期"
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn03],&G_RTC_ReadBuf[20], 4);
	G_LcdBuf[TestLine10][TestColumn14] = '\0';  //送结束符'\0'	
	F_Update_TestLine10 = YES;  //显示修改的"星期"
}	

/****************************************************************************
*函数名-Function:	void Disp_ModifyTimeState(void)
*描述- Description:	显示时间修改过程
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_ModifyTimeState(void) //显示时间修改过程
{
	//读取当前修改的时间值
			//显示修改中的"年"值--千、百、十、个位
	G_LcdBuf[TestLine08][TestColumn03] = ASCII_Table[G_MatrixKeyBuf[0]];
	G_LcdBuf[TestLine08][TestColumn03+1] = ASCII_Table[G_MatrixKeyBuf[1]];
	G_LcdBuf[TestLine08][TestColumn03+2] = ASCII_Table[G_MatrixKeyBuf[2]];
	G_LcdBuf[TestLine08][TestColumn03+3] = ASCII_Table[G_MatrixKeyBuf[3]];
	
			//显示修改中的"月"值--十、个位
	G_LcdBuf[TestLine08][TestColumn03+5] = ASCII_Table[G_MatrixKeyBuf[4]];
	G_LcdBuf[TestLine08][TestColumn03+6] = ASCII_Table[G_MatrixKeyBuf[5]];

			//显示修改中的"日"值--十、个位
	G_LcdBuf[TestLine08][TestColumn03+8] = ASCII_Table[G_MatrixKeyBuf[6]];
	G_LcdBuf[TestLine08][TestColumn03+9] = ASCII_Table[G_MatrixKeyBuf[7]];

			//显示修改中的"小时"值--十、个位
	G_LcdBuf[TestLine09][TestColumn03] = ASCII_Table[G_MatrixKeyBuf[8]];
	G_LcdBuf[TestLine09][TestColumn03+1] = ASCII_Table[G_MatrixKeyBuf[9]];

			//显示修改中的"分钟"值--十、个位
	G_LcdBuf[TestLine09][TestColumn03+3] = ASCII_Table[G_MatrixKeyBuf[10]];
	G_LcdBuf[TestLine09][TestColumn03+4] = ASCII_Table[G_MatrixKeyBuf[11]];

			//显示修改中的"秒"值--十、个位
	G_LcdBuf[TestLine09][TestColumn03+6] = ASCII_Table[G_MatrixKeyBuf[12]];
	G_LcdBuf[TestLine09][TestColumn03+7] = ASCII_Table[G_MatrixKeyBuf[13]];

		//显示修改中的"星期"值
	switch(G_MatrixKeyBuf[14]) 
	{
		case 1:   //星期一
			G_LcdBuf[TestLine10][TestColumn03]   = 'M';
			G_LcdBuf[TestLine10][TestColumn03+1] = 'O';
			G_LcdBuf[TestLine10][TestColumn03+2] = 'N';
			break;	
			
		case 2:   //星期二
			G_LcdBuf[TestLine10][TestColumn03]   = 'T';
			G_LcdBuf[TestLine10][TestColumn03+1] = 'U';
			G_LcdBuf[TestLine10][TestColumn03+2] = 'E';
			break;	

		case 3:   //星期三
			G_LcdBuf[TestLine10][TestColumn03]   = 'W';
			G_LcdBuf[TestLine10][TestColumn03+1] = 'E';
			G_LcdBuf[TestLine10][TestColumn03+2] = 'D';
			break;	

		case 4:   //星期四
			G_LcdBuf[TestLine10][TestColumn03]   = 'T';
			G_LcdBuf[TestLine10][TestColumn03+1] = 'H';
			G_LcdBuf[TestLine10][TestColumn03+2] = 'U';
			break;	

		case 5:   //星期五
			G_LcdBuf[TestLine10][TestColumn03]   = 'F';
			G_LcdBuf[TestLine10][TestColumn03+1] = 'R';
			G_LcdBuf[TestLine10][TestColumn03+2] = 'I';
			break;	
			
		case 6:   //星期六
			G_LcdBuf[TestLine10][TestColumn03]   = 'S';
			G_LcdBuf[TestLine10][TestColumn03+1] = 'A';
			G_LcdBuf[TestLine10][TestColumn03+2] = 'T';
			break;	
			
		case 7:   //星期日
			G_LcdBuf[TestLine10][TestColumn03]   = 'S';
			G_LcdBuf[TestLine10][TestColumn03+1] = 'U';
			G_LcdBuf[TestLine10][TestColumn03+2] = 'N';
			break;	

////////////////////////////////////////////////////////////////////////////
		default:	//不是1到7的显示"Err" 表示错误
			G_LcdBuf[TestLine10][TestColumn03]   = 'E';
			G_LcdBuf[TestLine10][TestColumn03+1] = 'r';
			G_LcdBuf[TestLine10][TestColumn03+2] = 'r';
			break;
	}

	F_Update_TestLine08 = YES;	//显示修改的"2013-01-01"
	F_Update_TestLine09 = YES;	//显示修改的"00:00:00"
	F_Update_TestLine10 = YES;  //显示修改的"星期"
}	


/****************************************************************************
*函数名-Function:	void Blink_ModifyTime(void)
*描述- Description:	处理"实时时间"修改状态下的闪烁
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Blink_ModifyTime(void)  //处理"实时时间"修改状态下的闪烁
{
	unsigned char Array[3];
	
	switch(G_MatrixKeyCnt) 
	{
//--**年**---------------------------------------------------------------//
		case 0:   //闪烁"千位"--年
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row,G_KeyPlace_Column,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;		
		case 1: //闪烁"百位"--年
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row,G_KeyPlace_Column+1,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;		
		case 2: //闪烁"十位"--年
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row,G_KeyPlace_Column+2,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;		
		case 3: //闪烁"个位"--年
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row,G_KeyPlace_Column+3,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;		
			
//--**月**---------------------------------------------------------------//
		case 4: //闪烁"十位"--月
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row,G_KeyPlace_Column+5,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;		
		case 5: //闪烁"个位"--月
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row,G_KeyPlace_Column+6,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;	

//--**日**---------------------------------------------------------------//
		case 6: //闪烁"十位"--日
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row,G_KeyPlace_Column+8,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;		
		case 7: //闪烁"个位"--日
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row,G_KeyPlace_Column+9,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;	

//--**小时**---------------------------------------------------------------//
		case 8: //闪烁"十位"--小时
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row+1,G_KeyPlace_Column,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;		
		case 9: //闪烁"个位"--小时
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row+1,G_KeyPlace_Column+1,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;	

//--**分钟**---------------------------------------------------------------//
		case 10: //闪烁"十位"--分钟
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row+1,G_KeyPlace_Column+3,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;		
		case 11: //闪烁"个位"--分钟
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row+1,G_KeyPlace_Column+4,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;	

//--**秒**---------------------------------------------------------------//
		case 12: //闪烁"十位"--秒
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row+1,G_KeyPlace_Column+6,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;		
		case 13: //闪烁"个位"--秒
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row+1,G_KeyPlace_Column+7,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;	

//--**星期**---------------------------------------------------------------//
		case 14: //闪烁"星期"
					//显示修改中的"星期"值
				switch(G_MatrixKeyBuf[14]) 
				{
					case 1:   //星期一
						Array[0] = 'M';
						Array[1] = 'O';
						Array[2] = 'N';
						break;	

					case 2:   //星期二
						Array[0] = 'T';
						Array[1] = 'U';
						Array[2] = 'E';
						break;

					case 3:   //星期三
						Array[0] = 'W';
						Array[1] = 'E';
						Array[2] = 'D';
						break;
			
					case 4:   //星期四
						Array[0] = 'T';
						Array[1] = 'H';
						Array[2] = 'U';
						break;
		
					case 5:   //星期五
						Array[0] = 'F';
						Array[1] = 'R';
						Array[2] = 'I';
						break;
						
					case 6:   //星期六
						Array[0] = 'S';
						Array[1] = 'A';
						Array[2] = 'T';
						break;	

					case 7:   //星期日
						Array[0] = 'S';
						Array[1] = 'U';
						Array[2] = 'N';
						break;

			////////////////////////////////////////////////////////////////////////////
					default:    //不是1到7的显示"Err" 表示错误
						Array[0] = 'E';
						Array[1] = 'r';
						Array[2] = 'r';
						break;
				}

			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row+2,G_KeyPlace_Column,Array,3);
			break;		

////////////////////////////////////////////////////////////////////////////
		default:
			break;
	}

}



/****************************************************************************
*函数名-Function:	void Dis_ModifyTimeError(void)
*描述- Description:	显示"错误: 时间输入有误!"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Dis_ModifyTimeError(void)  //显示"错误: 时间输入有误!"
{
		//显示:  Setting error!	Please re-enter! 
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01], Msg_Error_ModifyTime, 21);

	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01], Msg_Error_ReEnter, 21);

	F_Update_TestLine11 = YES;	//显示刷新
	F_Update_TestLine12 = YES;	//显示刷新
}






/****************************************************************************
*函数名-Function:	void Disp_Set_ScreenSaver(void)
*描述- Description:	显示"屏保功能"设置(LCD)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_Set_ScreenSaver(void)
{

}	








////////////////////////////////////////////////////////////////////////////
//--**显示:  "工作状态"下的相当显示**-------------------------//
////////////////////////////////////////////////////////////////////////////


/****************************************************************************
*函数名-Function:	void Disp_01Page_MenuLine(void)
*描述- Description:		显示第1页"工作菜单"(LCD)(1.Work_A  2.Work_B  3.Work_C  4.Work_D
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_01Page_MenuLine(void)
{
		// 显示: 第"01 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine01][MenuColumn01], Msg_01Page_MenuLine_01, 20);
		// 显示: 第"02 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine02][MenuColumn01], Msg_01Page_MenuLine_02, 20);
		// 显示: 第"03 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine03][MenuColumn01], Msg_01Page_MenuLine_03, 20);
		// 显示: 第"04 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine04][MenuColumn01], Msg_01Page_MenuLine_04, 20);
		// 显示: 第"05 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine05][MenuColumn01], Msg_01Page_MenuLine_05, 20);
		// 显示: 第"06 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine06][MenuColumn01], Msg_01Page_MenuLine_06, 20);
		// 显示: 第"07 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine07][MenuColumn01], Msg_01Page_MenuLine_07, 20);
		// 显示: 第"08 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine08][MenuColumn01], Msg_01Page_MenuLine_08, 20);
		// 显示: 第"09 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine09][MenuColumn01], Msg_01Page_MenuLine_09, 20);
		// 显示: 第"10 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine10][MenuColumn01], Msg_01Page_MenuLine_10, 20);
		// 显示: 第"11 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine11][MenuColumn01], Msg_01Page_MenuLine_11, 20);
		// 显示: 第"12 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine12][MenuColumn01], Msg_01Page_MenuLine_12, 20);

	mUpdate_All_MenuLine;  //刷新所有"菜单行"
}


/****************************************************************************
*函数名-Function:	void Disp_02Page_MenuLine(void)
*描述- Description:	显示第2页"工作菜单"(LCD)(1.Work_A  2.Work_B  3.Work_C  4.Work_D
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_02Page_MenuLine(void)
{
		// 显示: 第"01 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine01][MenuColumn01], Msg_02Page_MenuLine_01, 20);
		// 显示: 第"02 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine02][MenuColumn01], Msg_02Page_MenuLine_02, 20);
		// 显示: 第"03 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine03][MenuColumn01], Msg_02Page_MenuLine_03, 20);
		// 显示: 第"04 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine04][MenuColumn01], Msg_02Page_MenuLine_04, 20);
		// 显示: 第"05 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine05][MenuColumn01], Msg_02Page_MenuLine_05, 20);
		// 显示: 第"06 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine06][MenuColumn01], Msg_02Page_MenuLine_06, 20);
		// 显示: 第"07 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine07][MenuColumn01], Msg_02Page_MenuLine_07, 20);
		// 显示: 第"08 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine08][MenuColumn01], Msg_02Page_MenuLine_08, 20);
		// 显示: 第"09 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine09][MenuColumn01], Msg_02Page_MenuLine_09, 20);
		// 显示: 第"10 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine10][MenuColumn01], Msg_02Page_MenuLine_10, 20);
		// 显示: 第"11 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine11][MenuColumn01], Msg_02Page_MenuLine_11, 20);
		// 显示: 第"12 菜单行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine12][MenuColumn01], Msg_02Page_MenuLine_12, 20);

	mUpdate_All_MenuLine;  //刷新所有"菜单行"

}




/****************************************************************************
*函数名-Function:	void Disp_SelectFlag(void)
*描述- Description:	显示"选中标志"  "=>"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_SelectFlag(void)
{
	switch(G_KeyCnt)
	{
		case 1: //反白，选择"01.xxxx"菜单项
			F_HL_MenuLine02 = YES;  
			
			F_Update_MenuLine07 = YES; 
			F_Update_MenuLine02 = YES;  
			F_Update_MenuLine03 = YES;  
			break;
	
		case 2: //反白，选择"02.xxxx"菜单项
			F_HL_MenuLine03 = YES;  
			
			F_Update_MenuLine02 = YES;  
			F_Update_MenuLine03 = YES;  
			F_Update_MenuLine04 = YES;  
			break;
	
		case 3: //反白，选择"03.xxxx"菜单项
			F_HL_MenuLine04 = YES;  
			
			F_Update_MenuLine03 = YES;  
			F_Update_MenuLine04 = YES;  
			F_Update_MenuLine05 = YES;  
			break;
			
		case 4: //反白，选择"04.xxxx"菜单项
			F_HL_MenuLine05 = YES;  
			
			F_Update_MenuLine04 = YES;  
			F_Update_MenuLine05 = YES;  
			F_Update_MenuLine06 = YES;  
			break;

		case 5: //反白，选择"05.xxxx"菜单项
			F_HL_MenuLine06 = YES;  
			
			F_Update_MenuLine05 = YES;  
			F_Update_MenuLine06 = YES;  
			F_Update_MenuLine07 = YES;  
			break;

		case 6: //反白，选择"06.xxxx"菜单项
			F_HL_MenuLine07 = YES;  
			
			F_Update_MenuLine06 = YES;  
			F_Update_MenuLine07 = YES;  
			F_Update_MenuLine08 = YES;  
			break;
			
		case 7: //反白，选择"07.xxxx"菜单项
			F_HL_MenuLine08 = YES;  
			
			F_Update_MenuLine07 = YES;  
			F_Update_MenuLine08 = YES;  
			F_Update_MenuLine09 = YES;  
			break;

		case 8: //反白，选择"08.xxxx"菜单项
			F_HL_MenuLine09 = YES;  
			
			F_Update_MenuLine08 = YES;  
			F_Update_MenuLine09 = YES;  
			F_Update_MenuLine10 = YES;  
			break;

		case 9: //反白，选择"09.xxxx"菜单项
			F_HL_MenuLine10 = YES;  
			
			F_Update_MenuLine09 = YES;  
			F_Update_MenuLine10 = YES;  
			F_Update_MenuLine11 = YES;  
			break;


		case 10: //反白，选择"10.xxxx"菜单项
			F_HL_MenuLine11 = YES;  
			
			F_Update_MenuLine10 = YES;  
			F_Update_MenuLine11 = YES;  
			F_Update_MenuLine12 = YES;  
			break;	

		case 11: //反白，选择"11.xxxx"菜单项
			F_HL_MenuLine12 = YES;  
			
			F_Update_MenuLine11 = YES;  
			F_Update_MenuLine12 = YES;  
			F_Update_MenuLine02 = YES;  
			break;
			
		case 12: //反白，选择"12.xxxx"菜单项
			F_HL_MenuLine02 = YES;  
			
			F_Update_MenuLine12 = YES;  
			F_Update_MenuLine02 = YES;  
			F_Update_MenuLine03 = YES;  
			break;

		case 13: //反白，选择"13.xxxx"菜单项
			F_HL_MenuLine03 = YES;  
			
			F_Update_MenuLine02 = YES;  
			F_Update_MenuLine03 = YES;  
			F_Update_MenuLine04 = YES;  
			break;

		case 14: //反白，选择"14.xxxx"菜单项
			F_HL_MenuLine04 = YES;  
			
			F_Update_MenuLine03 = YES;  
			F_Update_MenuLine04 = YES;  
			F_Update_MenuLine05 = YES;  
			break;

		case 15: //反白，选择"15.xxxx"菜单项
			F_HL_MenuLine05 = YES;  
			
			F_Update_MenuLine04 = YES;  
			F_Update_MenuLine05 = YES;  
			F_Update_MenuLine06 = YES; 
			break;


		case 16: //反白，选择"16.xxxx"菜单项
			F_HL_MenuLine06 = YES;  
			
			F_Update_MenuLine05 = YES;  
			F_Update_MenuLine06 = YES;  
			F_Update_MenuLine07 = YES; 	
			break;

		case 17: //反白，选择"17.xxxx"菜单项
			F_HL_MenuLine07 = YES;  
			
			F_Update_MenuLine06 = YES;  
			F_Update_MenuLine07 = YES;  
			F_Update_MenuLine02 = YES; 
			break;		
///////////////////////////////////////////////////////////////////////////////////
		default : break;
	
	}



}


/****************************************************************************
*函数名-Function:	void Disp_MAIN_Basic_Settings(void)
*描述- Description:	显示//Main█Basic_Settings 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_MAIN_Basic_Settings(void)
{
		// 显示: 第"01 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_01Test_Line01, 21);
		// 显示: 第"02 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_01Test_Line02, 21);
		// 显示: 第"03 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_01Test_Line03, 21);
		// 显示: 第"04 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_01Test_Line04, 21);
		// 显示: 第"05 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_01Test_Line05, 21);
		// 显示: 第"06 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_01Test_Line06, 21);
		// 显示: 第"07 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_01Test_Line07, 21);
		// 显示: 第"08 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_01Test_Line08, 21);
		// 显示: 第"09 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_01Test_Line09, 21);
		// 显示: 第"10 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_01Test_Line10, 21);
		// 显示: 第"11 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_01Test_Line11, 21);
		// 显示: 第"12 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_01Test_Line12, 21);

	mUpdate_All_TestLine;  //刷新所有" 测试行"
}





/****************************************************************************
*函数名-Function:	void Disp_MAIN_Basic_Check(void)
*描述- Description:	显示//Main█Basic_Check 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_MAIN_Basic_Check(void)
{
		// 显示: 第"01 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_02Test_Line01, 21);
		// 显示: 第"02 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_02Test_Line02, 21);
		// 显示: 第"03 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_02Test_Line03, 21);
		// 显示: 第"04 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_02Test_Line04, 21);
		// 显示: 第"05 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_02Test_Line05, 21);
		// 显示: 第"06 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_02Test_Line06, 21);
		// 显示: 第"07 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_02Test_Line07, 21);
		// 显示: 第"08 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_02Test_Line08, 21);
		// 显示: 第"09 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_02Test_Line09, 21);
		// 显示: 第"10 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_02Test_Line10, 21);
		// 显示: 第"11 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_02Test_Line11, 21);
		// 显示: 第"12 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_02Test_Line12, 21);

	mUpdate_All_TestLine;  //刷新所有" 测试行"
}




/****************************************************************************
*函数名-Function:	void Disp_MAIN_LCD_TFT_Test(void)
*描述- Description:	显示//Main█LCD_TFT_Test 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_MAIN_LCD_TFT_Test(void)
{
		// 显示: 第"01 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_03Test_Line01, 21);
		// 显示: 第"02 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_03Test_Line02, 21);
		// 显示: 第"03 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_03Test_Line03, 21);
		// 显示: 第"04 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_03Test_Line04, 21);
		// 显示: 第"05 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_03Test_Line05, 21);
		// 显示: 第"06 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_03Test_Line06, 21);
		// 显示: 第"07 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_03Test_Line07, 21);
		// 显示: 第"08 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_03Test_Line08, 21);
		// 显示: 第"09 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_03Test_Line09, 21);
		// 显示: 第"10 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_03Test_Line10, 21);
		// 显示: 第"11 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_03Test_Line11, 21);
		// 显示: 第"12 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_03Test_Line12, 21);

}


/****************************************************************************
*函数名-Function:	void Disp_MAIN_MatrixKey_Test(void)
*描述- Description:	显示//Main█MatrixKey_Test 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_MAIN_MatrixKey_Test(void)
{
		// 显示: 第"01 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_04Test_Line01, 21);
		// 显示: 第"02 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_04Test_Line02, 21);
		// 显示: 第"03 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_04Test_Line03, 21);
		// 显示: 第"04 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_04Test_Line04, 21);
		// 显示: 第"05 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_04Test_Line05, 21);
		// 显示: 第"06 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_04Test_Line06, 21);
		// 显示: 第"07 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_04Test_Line07, 21);
		// 显示: 第"08 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_04Test_Line08, 21);
		// 显示: 第"09 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_04Test_Line09, 21);
		// 显示: 第"10 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_04Test_Line10, 21);
		// 显示: 第"11 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_04Test_Line11, 21);
		// 显示: 第"12 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_04Test_Line12, 21);

	mUpdate_All_TestLine;  //刷新所有" 测试行"

}



/****************************************************************************
*函数名-Function:	void Disp_MatrixKey_Press(void)
*描述- Description:	根据按下的"矩阵按键"，在测试区域显示"按键值"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01) 	▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_MatrixKey_Press(void)
{
	if(Detect_MatrixKey_1()) //"数字1键"
	{	
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_1_LedSeg);
		G_LcdBuf[TestLine06][TestColumn03]= '1';
		F_Update_TestLine06 = YES;

		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	}
	
	if(Detect_MatrixKey_2()) //"数字2键"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_2_LedSeg);
		G_LcdBuf[TestLine06][TestColumn06]= '2';
		F_Update_TestLine06 = YES; 

		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	}

	if(Detect_MatrixKey_3()) //"数字3键"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_3_LedSeg);
		G_LcdBuf[TestLine06][TestColumn09]= '3';
		F_Update_TestLine06 = YES; 

		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	}
	if(Detect_MatrixKey_A()) //"A键"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_A_LedSeg);
		G_LcdBuf[TestLine06][TestColumn12]= 'A';
		F_Update_TestLine06 = YES; 


		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	}
	
	if(Detect_MatrixKey_AC()) //"AC键"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_A_LedSeg,DISP_C_LedSeg);
		G_LcdBuf[TestLine06][TestColumn15]= 'A';
		G_LcdBuf[TestLine06][TestColumn16]= 'C';
		F_Update_TestLine06 = YES; 
		
		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	}
	
/////////////////////////////////////////////////////////////
	if(Detect_MatrixKey_4()) //"数字4键"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_4_LedSeg);
		G_LcdBuf[TestLine07][TestColumn03]= '4';
		F_Update_TestLine07 = YES;

		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	}
	
	if(Detect_MatrixKey_5()) //"数字5键"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_5_LedSeg);
		G_LcdBuf[TestLine07][TestColumn06]= '5';
		F_Update_TestLine07 = YES; 

		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	}

	if(Detect_MatrixKey_6()) //"数字6键"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_6_LedSeg);
		G_LcdBuf[TestLine07][TestColumn09]= '6';
		F_Update_TestLine07 = YES; 

		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	}
	if(Detect_MatrixKey_B()) //"B键"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_b_LedSeg);
		G_LcdBuf[TestLine07][TestColumn12]= 'B';
		F_Update_TestLine07 = YES; 

		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	}

	if(Detect_MatrixKey_Plus()) //"+键"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_Plus_LedSeg);
		G_LcdBuf[TestLine07][TestColumn15]= '+';
		F_Update_TestLine07 = YES; 

		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	}
	
/////////////////////////////////////////////////////////////////
	if(Detect_MatrixKey_7()) //"数字7键"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_7_LedSeg);	
		G_LcdBuf[TestLine08][TestColumn03]= '7';
		F_Update_TestLine08 = YES;

		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	}
	
	if(Detect_MatrixKey_8()) //"数字8键"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_8_LedSeg);
		G_LcdBuf[TestLine08][TestColumn06]= '8';
		F_Update_TestLine08 = YES; 

		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	}

	if(Detect_MatrixKey_9()) //"数字9键"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_9_LedSeg);
		G_LcdBuf[TestLine08][TestColumn09]= '9';
		F_Update_TestLine08 = YES; 

		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	}
	if(Detect_MatrixKey_C()) //"C键"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_C_LedSeg);
		G_LcdBuf[TestLine08][TestColumn12]= 'C';
		F_Update_TestLine08 = YES; 

		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	}

	if(Detect_MatrixKey_Minus()) //"-键"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_Minus_LedSeg);
		G_LcdBuf[TestLine08][TestColumn15]= '-';
		F_Update_TestLine08 = YES; 

		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	}
/////////////////////////////////////////////////////////////////
	if(Detect_MatrixKey_0()) //"数字0键"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_0_LedSeg);
		G_LcdBuf[TestLine09][TestColumn03]= '0';
		F_Update_TestLine09 = YES;

		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	}
	
	if(Detect_MatrixKey_F()) //"数字F键"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_F_LedSeg);
		G_LcdBuf[TestLine09][TestColumn06]= 'F';
		F_Update_TestLine09 = YES; 

		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	}

	if(Detect_MatrixKey_E()) //"数字E键"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_E_LedSeg);
		G_LcdBuf[TestLine09][TestColumn09]= 'E';
		F_Update_TestLine09 = YES; 

		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	}
	
	if(Detect_MatrixKey_D()) //"D键"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_d_LedSeg);
		G_LcdBuf[TestLine09][TestColumn12]= 'D';
		F_Update_TestLine09 = YES; 

		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	}

	if(Detect_MatrixKey_Equal()) //"=键"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_Equal_LedSeg);
		G_LcdBuf[TestLine09][TestColumn15]= '=';
		F_Update_TestLine09 = YES; 

		Open_Buzzer(BuzzTime_Key);  //按键有效时，让蜂鸣叫指定时间
	}
/////////////////////////////////////////////////////////////////

}


/****************************************************************************
*函数名-Function:	void Disp_MAIN_TouchPads_Test(void)
*描述- Description:	显示//Main█TouchPads_Test 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_MAIN_TouchPads_Test(void)
{
		// 显示: 第"01 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_05Test_Line01, 21);
		// 显示: 第"02 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_05Test_Line02, 21);
		// 显示: 第"03 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_05Test_Line03, 21);
		// 显示: 第"04 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_05Test_Line04, 21);
		// 显示: 第"05 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_05Test_Line05, 21);
		// 显示: 第"06 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_05Test_Line06, 21);
		// 显示: 第"07 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_05Test_Line07, 21);
		// 显示: 第"08 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_05Test_Line08, 21);
		// 显示: 第"09 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_05Test_Line09, 21);
		// 显示: 第"10 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_05Test_Line10, 21);
		// 显示: 第"11 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_05Test_Line11, 21);
		// 显示: 第"12 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_05Test_Line12, 21);

	mUpdate_All_TestLine;  //刷新所有" 测试行"
}


/****************************************************************************
*函数名-Function:	void Disp_MAIN_INA21x_Current_Test(void)
*描述- Description:	显示//Main█INA210_Current_Test 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_MAIN_INA21x_Current_Test(void)
{
		// 显示: 第"01 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_06Test_Line01, 21);
		// 显示: 第"02 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_06Test_Line02, 21);
		// 显示: 第"03 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_06Test_Line03, 21);
		// 显示: 第"04 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_06Test_Line04, 21);
		// 显示: 第"05 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_06Test_Line05, 21);
		// 显示: 第"06 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_06Test_Line06, 21);
		// 显示: 第"07 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_06Test_Line07, 21);
		// 显示: 第"08 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_06Test_Line08, 21);
		// 显示: 第"09 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_06Test_Line09, 21);
		// 显示: 第"10 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_06Test_Line10, 21);
		// 显示: 第"11 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_06Test_Line11, 21);
		// 显示: 第"12 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_06Test_Line12, 21);

	mUpdate_All_TestLine;  //刷新所有" 测试行"
}



/****************************************************************************
*函数名-Function:	void Disp_INA21x_Current_InTest(void)
*描述- Description:	在"测试行"显示: INA21x 实时"监测电流值"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_INA21x_Current_InTest(void)
{
	unsigned char b,c,d;  
	
//	a = (unsigned char)(G_INA21x_AdResult/1000);
	b = (unsigned char)((G_INA21x_AdResult % 1000)/100);
	c = (unsigned char)((G_INA21x_AdResult % 100)/10);
	d = (unsigned char)(G_INA21x_AdResult % 10);


		//刷新要显示的"实际电流值"，单位A,显示250A
	G_LcdBuf[TestLine04][TestColumn10] = ASCII_Table[b];	 //第一位
	if(b == 0) G_LcdBuf[TestLine04][TestColumn10] = 0x20;
	
	G_LcdBuf[TestLine04][TestColumn11] = ASCII_Table[c];	 //第二位
	G_LcdBuf[TestLine04][TestColumn12] = ASCII_Table[d];	 //第三位

	F_Update_TestLine04 = YES; //刷新:""测试行"" 
}




/****************************************************************************
*函数名-Function:	void Disp_MAIN_Potentiometer_Test(void)
*描述- Description:	显示//Main█Potentiometer_Test 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_MAIN_Potentiometer_Test(void)
{
		// 显示: 第"01 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_08Test_Line01, 21);
		// 显示: 第"02 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_08Test_Line02, 21);
		// 显示: 第"03 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_08Test_Line03, 21);
		// 显示: 第"04 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_08Test_Line04, 21);
		// 显示: 第"05 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_08Test_Line05, 21);
		// 显示: 第"06 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_08Test_Line06, 21);
		// 显示: 第"07 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_08Test_Line07, 21);
		// 显示: 第"08 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_08Test_Line08, 21);
		// 显示: 第"09 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_08Test_Line09, 21);
		// 显示: 第"10 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_08Test_Line10, 21);
		// 显示: 第"11 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_08Test_Line11, 21);
		// 显示: 第"12 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_08Test_Line12, 21);

	mUpdate_All_TestLine;  //刷新所有" 测试行"
}



/****************************************************************************
*函数名-Function:	void Disp_Potentiometer_InTest(void)
*描述- Description:	在"测试行"显示: 电位计Potentiometer 实时"电压值"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_Potentiometer_InTest(void)
{
	unsigned char a,b,c;
	
	a = (unsigned char)(G_LastAdResult/1000);
	b = (unsigned char)((G_LastAdResult % 1000)/100);
	c = (G_LastAdResult % 100)/10;
	if(G_LastAdResult < 30) c = 0; //在电位器旋到最小值时，显示电压会在0.01,0.02,.000之间显示，加上这条，可以在电位器旋到最小值时，显示0.00


		//刷新要显示的"实际电压值"，单位A,显示3.29 V
	G_LcdBuf[TestLine04][TestColumn10] = ASCII_Table[a];   //个位
	G_LcdBuf[TestLine04][TestColumn11] = '.';   //小数点
	G_LcdBuf[TestLine04][TestColumn12] = ASCII_Table[b];	 //小数第一位
	G_LcdBuf[TestLine04][TestColumn13] = ASCII_Table[c];   //小数第二位
	G_LcdBuf[TestLine04][TestColumn14] = ' ';   
	G_LcdBuf[TestLine04][TestColumn15] = 'V';   

	F_Update_TestLine04 = YES; //刷新:""测试行"" 
}


/****************************************************************************
*函数名-Function:	void Disp_MAIN_NTC_HR202_Test(void)
*描述- Description:	显示//Main█NTC_HR202_Test(温湿度) 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_MAIN_NTC_HR202_Test(void)
{
		// 显示: 第"01 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_11Test_Line01, 21);
		// 显示: 第"02 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_11Test_Line02, 21);
		// 显示: 第"03 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_11Test_Line03, 21);
		// 显示: 第"04 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_11Test_Line04, 21);
		// 显示: 第"05 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_11Test_Line05, 21);
		// 显示: 第"06 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_11Test_Line06, 21);
		// 显示: 第"07 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_11Test_Line07, 21);
		// 显示: 第"08 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_11Test_Line08, 21);
		// 显示: 第"09 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_11Test_Line09, 21);
		// 显示: 第"10 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_11Test_Line10, 21);
		// 显示: 第"11 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_11Test_Line11, 21);
		// 显示: 第"12 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_11Test_Line12, 21);

	mUpdate_All_TestLine;  //刷新所有" 测试行"
}



/****************************************************************************
*函数名-Function:	void Disp_MAIN_Step_Motor_Test(void)
*描述- Description:	显示//Main█Step_Motor_Test 菜单选择(工作时) 
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_MAIN_Step_Motor_Test(void)
{
		// 显示: 第"01 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_10Test_Line01, 21);
		// 显示: 第"02 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_10Test_Line02, 21);
		// 显示: 第"03 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_10Test_Line03, 21);
		// 显示: 第"04 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_10Test_Line04, 21);
		// 显示: 第"05 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_10Test_Line05, 21);
		// 显示: 第"06 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_10Test_Line06, 21);
		// 显示: 第"07 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_10Test_Line07, 21);
		// 显示: 第"08 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_10Test_Line08, 21);
		// 显示: 第"09 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_10Test_Line09, 21);
		// 显示: 第"10 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_10Test_Line10, 21);
		// 显示: 第"11 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_10Test_Line11, 21);
		// 显示: 第"12 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_10Test_Line12, 21);

}



/****************************************************************************
*函数名-Function:	void Disp_MAIN_DC_Motor_Test(void)
*描述- Description:	显示//Main█DC_Motor_Test 菜单选择(工作时)  
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_MAIN_DC_Motor_Test(void)
{
		// 显示: 第"01 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_09Test_Line01, 21);
		// 显示: 第"02 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_09Test_Line02, 21);
		// 显示: 第"03 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_09Test_Line03, 21);
		// 显示: 第"04 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_09Test_Line04, 21);
		// 显示: 第"05 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_09Test_Line05, 21);
		// 显示: 第"06 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_09Test_Line06, 21);
		// 显示: 第"07 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_09Test_Line07, 21);
		// 显示: 第"08 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_09Test_Line08, 21);
		// 显示: 第"09 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_09Test_Line09, 21);
		// 显示: 第"10 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_09Test_Line10, 21);
		// 显示: 第"11 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_09Test_Line11, 21);
		// 显示: 第"12 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_09Test_Line12, 21);

	
}


/****************************************************************************
*函数名-Function:	void Disp_Potentiometer_Motor(void)
*描述- Description:	在"测试电机"显示速度给定电压值: 电位计Potentiometer 实时"电压值"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_Potentiometer_Motor(void)
{
	unsigned char a,b;
	
	a = (unsigned char)(G_LastAdResult/1000);
	b = (unsigned char)((G_LastAdResult % 1000)/100);
//c = (G_LastAdResult % 100)/10;
//	if(G_LastAdResult < 30) c = 0; //在电位器旋到最小值时，显示电压会在0.01,0.02,.000之间显示，加上这条，可以在电位器旋到最小值时，显示0.00


		//刷新要显示的"实际电压值"，单位A,显示3.29 V
	G_LcdBuf[TestLine07][TestColumn10] = ASCII_Table[a];   //个位
	G_LcdBuf[TestLine07][TestColumn11] = '.';   //小数点
	G_LcdBuf[TestLine07][TestColumn12] = ASCII_Table[b];	 //小数第一位
	G_LcdBuf[TestLine07][TestColumn13] = ' ';   
	G_LcdBuf[TestLine07][TestColumn14] = 'V';   

	F_Update_TestLine07 = YES; //刷新:""测试行"" 
}


/****************************************************************************
*函数名-Function:	void Disp_Speed_Step_Motor(void)
*描述- Description:		在"测试Step_Motor"显示电机速度
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_Speed_Step_Motor(void) //在"测试Step_Motor"显示电机速度
{
	unsigned char s1 = 0;
	unsigned char s2 = 0;
	unsigned char s3 = 0;
	unsigned char s4 = 0;


//转速显示相关
	s3 = (unsigned char)(G_Step_Speed /1000);
	s2 = (unsigned char)((G_Step_Speed % 1000)/100);
	s1 = (unsigned char)(G_Step_Speed % 100)/10;



	if(G_Step_WorkState  == STATE_Reverse_Step_Motor) //反转显示处理
	{
		s4 = 18; //显示"负号"(不显示0)		

		if(s3 == 0) 
		{
			s4 = 19; //显示"暗码"(不显示0)	
			s3 = 18; //显示"负号"(不显示0)	
		}
			

	}
	else if(G_Step_WorkState  == STATE_Positive_Step_Motor) //正转显示处理
	{
		s4 = 19;  // 显示"暗码"(不显示0)
		if(s3 == 0) s3 = 19; //显示"暗码"(不显示0)
	}

		//刷新要显示的"转速"，单位r/min,
	G_LcdBuf[TestLine08][TestColumn10] = ASCII_Table[s4]; 
	G_LcdBuf[TestLine08][TestColumn11] = ASCII_Table[s3]; //百位	 
	G_LcdBuf[TestLine08][TestColumn12] = ASCII_Table[s2]; //十位  
//G_LcdBuf[TestLine08][TestColumn13] = '.'; //  
	G_LcdBuf[TestLine08][TestColumn14] = ASCII_Table[s1]; //个位  

	F_Update_TestLine08 = YES; //刷新:""测试行"" 
}







/****************************************************************************
*函数名-Function:	void Disp_Speed_DC_Motor(void)
*描述- Description:	在"测试DC_Motor"显示电机速度
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_Speed_DC_Motor(void)
{
	unsigned int speed = 0;
	
	unsigned char a1 = 0;
	unsigned char a2 = 0;
	unsigned char a3 = 0;
	unsigned char a4 = 0;
	unsigned char a5 = 0;


	speed = (G_DC_Speed * 60) / 3;  // 将转速脉冲转成"实际转速值" r/min 单位

//转速显示相关
	if(G_DC_WorkState  == STATE_Positive_DC_Motor)  //正转显示处理
	{
		a5 = 19; //显示"暗码"(不显示0)
			
		a4 = (unsigned char)(speed/1000);
		a3 = (unsigned char)((speed % 1000)/100);
		a2 = (unsigned char)(speed % 100)/10;
		a1 = (unsigned char)(speed % 10);
		if((a4 == 0)&&(a3 == 0)&&(a2 == 0)) a2 = 19;	
		if((a4 == 0)&&(a3 == 0)) a3 = 19;
		if(a4 == 0) a4 = 19; //显示"暗码"(不显示0)
	}
	
	else if(G_DC_WorkState  == STATE_Reverse_DC_Motor) //反转显示处理
	{
		a5 = 19; //显示"暗码"(不显示0)
		a4 = (unsigned char)(speed/1000);
		a3 = (unsigned char)((speed % 1000)/100);
		a2 = (unsigned char)(speed % 100)/10;
		a1 = (unsigned char)(speed % 10);
		if((a4 == 0)&&(a3 == 0)&&(a2 == 0))
		{
			a5 = 19; //显示"暗码"(不显示0)
		 	a4 = 19;//显示"暗码"(不显示0)
			a3 = 19;//显示"暗码"(不显示0)
			a2 = 18; //显示"负号"(不显示0)
		}
		if((a4 == 0)&&(a3 == 0))
		{
			a5 = 19; //显示"暗码"(不显示0)
		 	a4 = 19;//显示"暗码"(不显示0)
			a3 = 18; //显示"负号"(不显示0)
		}
		if(a4 == 0) 
		{
			a5 = 19; //显示"暗码"(不显示0)
			a4 = 18; //显示"负号"(不显示0)		
		}
		else if(a4 != 0) a5 = 18; //显示"负号"(不显示0)	
		
	}

		//刷新要显示的"转速"，单位r/min,
	G_LcdBuf[TestLine08][TestColumn10] = ASCII_Table[a5]; //
	G_LcdBuf[TestLine08][TestColumn11] = ASCII_Table[a4]; //千位  
	G_LcdBuf[TestLine08][TestColumn12] = ASCII_Table[a3]; //百位	 
	G_LcdBuf[TestLine08][TestColumn13] = ASCII_Table[a2]; //十位  
	G_LcdBuf[TestLine08][TestColumn14] = ASCII_Table[a1]; //个位  

	F_Update_TestLine08 = YES; //刷新:""测试行"" 
}




/****************************************************************************
*函数名-Function:	void Disp_MAIN_TMP006_Temperature(void)
*描述- Description:	显示//Main█TMP006_Temperature 菜单选择(工作时) 
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_MAIN_TMP006_Temperature(void)
{
		// 显示: 第"01 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_07Test_Line01, 21);
		// 显示: 第"02 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_07Test_Line02, 21);
		// 显示: 第"03 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_07Test_Line03, 21);
		// 显示: 第"04 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_07Test_Line04, 21);
		// 显示: 第"05 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_07Test_Line05, 21);
		// 显示: 第"06 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_07Test_Line06, 21);
		// 显示: 第"07 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_07Test_Line07, 21);
		// 显示: 第"08 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_07Test_Line08, 21);
		// 显示: 第"09 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_07Test_Line09, 21);
		// 显示: 第"10 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_07Test_Line10, 21);
		// 显示: 第"11 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_07Test_Line11, 21);
		// 显示: 第"12 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_07Test_Line12, 21);

	mUpdate_All_TestLine;  //刷新所有" 测试行"
}


/****************************************************************************
*函数名-Function:	void Disp_TMP006_TemperatureInTest(void)
*描述- Description:		在LCD_TFT上，显示"温度"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_TMP006_TemperatureInTest(void)//在LCD_TFT上，显示"温度"
{	
	int b = 0;
	unsigned char a4,a3,a2,a1;

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
			a4 = 19;//显示"暗码"(不显示0)
			a3 = 18; //显示"负号"(不显示0)
		}
		if(a4 == 0) a4 = 18; //显示"负号"(不显示0)	
	}
	else //正温度值
	{
		a4 =  b / 1000; 
		a3 = (b % 1000) / 100;
		a2 = (b % 100) / 10;
		a1 =  b % 10;	
		
		if((a4 == 0)&&(a3 == 0)) a3 = 19;//显示"暗码"(不显示0)
		if(a4 == 0) a4 = 19;//显示"暗码"(不显示0)
	}

		//刷新要显示的"实际温度"
	G_LcdBuf[TestLine04][TestColumn13] = ASCII_Table[a4];//百位	
	G_LcdBuf[TestLine04][TestColumn14] = ASCII_Table[a3]; //十位
	G_LcdBuf[TestLine04][TestColumn15] = ASCII_Table[a2]; //个位
	G_LcdBuf[TestLine04][TestColumn16] = '.'; //小数点
	G_LcdBuf[TestLine04][TestColumn17] = ASCII_Table[a1]; //小数第一位
	
	F_Update_TestLine04 = YES; //刷新:"实时温度"  (为1时)
}




/****************************************************************************
*函数名-Function:	void Disp_TMP006_Temperature(void)
*描述- Description:		在LCD_TFT上，显示"温度"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_TMP006_Temperature(void)//在LCD_TFT上，显示"温度"
{	
	int d = 0;
    unsigned char aa4,aa3,aa2,aa1;

	d = (int)(TMP006_Temperature * 10);  //将"实际温度值"放到10倍，用于显示
	if(d < 0)  //负温度值
	{
		d  = (-1) * d;
		aa4 =  d / 1000; 
		aa3 =  d / 100;
		aa2 = (d / 10) % 10;
		aa1 =  d % 10;	

		if((aa4 == 0)&&(aa3 == 0))
		{
			aa4 = 19;//显示"暗码"(不显示0)
			aa3 = 18; //显示"负号"(不显示0)
		}
		if(aa4 == 0) aa4 = 18; //显示"负号"(不显示0)	
	}
	else //正温度值
	{
		aa4 =  d / 1000; 
		aa3 = (d % 1000) / 100;
		aa2 = (d % 100) / 10;
		aa1 =  d % 10;	
		
		if((aa4 == 0)&&(aa3 == 0)) aa3 = 19;//显示"暗码"(不显示0)
		if(aa4 == 0) aa4 = 19;//显示"暗码"(不显示0)
	}

		//刷新要显示的"实际温度"
	G_LcdBuf[M_15LineBuf][M_24ColumnBuf] = ASCII_Table[aa4];//百位	
	G_LcdBuf[M_15LineBuf][M_25ColumnBuf] = ASCII_Table[aa3]; //十位
	G_LcdBuf[M_15LineBuf][M_26ColumnBuf] = ASCII_Table[aa2]; //个位
	G_LcdBuf[M_15LineBuf][M_27ColumnBuf] = '.'; //小数点
	G_LcdBuf[M_15LineBuf][M_28ColumnBuf] = ASCII_Table[aa1]; //小数第一位
//G_LcdBuf[M_15LineBuf][M_29ColumnBuf] = 'c';	 
//G_LcdBuf[M_15LineBuf][M_30ColumnBuf] = '\0';	

	F_Update_Temperature = YES; //刷新:"实时温度"  (为1时)

}


/****************************************************************************
*函数名-Function:	void Disp_MAIN_TMP100_Temperature(void)
*描述- Description:	显示//Main█TMP100_Temperature 菜单选择(工作时) 
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_MAIN_TMP100_Temperature(void)
{
}

/****************************************************************************
*函数名-Function:	void Disp_TMP100_Temperature(void)
*描述- Description:		在LCD_TFT上，显示"温度"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_TMP100_Temperature(void)//在LCD_TFT上，显示"温度"
{	
}



/****************************************************************************
*函数名-Function:	void Disp_MAIN_IrDA_UART(void)
*描述- Description:		显示//Main█IrDA_UART 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_MAIN_IrDA_UART(void) //显示//Main█IrDA_UART 菜单选择(工作时)
{
		// 显示: 第"01 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_12Test_Line01, 21);
		// 显示: 第"02 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_12Test_Line02, 21);
		// 显示: 第"03 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_12Test_Line03, 21);
		// 显示: 第"04 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_12Test_Line04, 21);
		// 显示: 第"05 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_12Test_Line05, 21);
		// 显示: 第"06 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_12Test_Line06, 21);
		// 显示: 第"07 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_12Test_Line07, 21);
		// 显示: 第"08 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_12Test_Line08, 21);
		// 显示: 第"09 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_12Test_Line09, 21);
		// 显示: 第"10 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_12Test_Line10, 21);
		// 显示: 第"11 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_12Test_Line11, 21);
		// 显示: 第"12 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_12Test_Line12, 21);

	mUpdate_All_TestLine;  //刷新所有" 测试行"

}

/****************************************************************************
*函数名-Function:	void Disp_IrDA_Test(void)
*描述- Description:		显示IrDA是否收到数据
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_IrDA_Test(void) //显示IrDA是否收到数据
{
	if(G_RxData_IrDA == '1')  //如果红外接收到的数据为"1"
	{
		Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_12Test_TXT1, 21);
	}
	else
	{
		Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_12Test_TXT2, 21);
	}
	
	F_Update_TestLine07 = YES;//刷新:""测试行"" 
}


  
/****************************************************************************
*函数名-Function:	void Disp_MAIN_RS232_UART(void)
*描述- Description:		//显示//Main█RS232_UART 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_MAIN_RS232_UART(void) //显示//Main█RS232_UART 菜单选择(工作时)
{
		// 显示: 第"01 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_13Test_Line01, 21);
		// 显示: 第"02 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_13Test_Line02, 21);
		// 显示: 第"03 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_13Test_Line03, 21);
		// 显示: 第"04 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_13Test_Line04, 21);
		// 显示: 第"05 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_13Test_Line05, 21);
		// 显示: 第"06 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_13Test_Line06, 21);
		// 显示: 第"07 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_13Test_Line07, 21);
		// 显示: 第"08 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_13Test_Line08, 21);
		// 显示: 第"09 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_13Test_Line09, 21);
		// 显示: 第"10 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_13Test_Line10, 21);
		// 显示: 第"11 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_13Test_Line11, 21);
		// 显示: 第"12 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_13Test_Line12, 21);

	mUpdate_All_TestLine;  //刷新所有" 测试行"

}


/****************************************************************************
*函数名-Function:	void Disp_RS232_Char_1(void)
*描述- Description:		显示RS232收到数据"1" (字符)	
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_RS232_Char_1(void) //显示RS232收到数据"1" (字符)	
{
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01], Msg_13Test_TXT1, 21);
	F_Update_TestLine10 = YES;//刷新:""测试行"" 
}


/****************************************************************************
*函数名-Function:	void Disp_RS232_Char_2(void)
*描述- Description:		显示RS232收到数据"2" (字符)	
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_RS232_Char_2(void) //显示RS232收到数据"2" (字符)	
{
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01], Msg_13Test_TXT2, 21);

	F_Update_TestLine10 = YES;//刷新:""测试行"" 
}


/****************************************************************************
*函数名-Function:	void Disp_RS232_None(void)
*描述- Description:		//清显示RS232收到数据
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_RS232_None(void) //清显示RS232收到数据
{
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01], Msg_13Test_TXT3, 21);

	F_Update_TestLine10 = YES;//刷新:""测试行"" 
}



/****************************************************************************
*函数名-Function:	void Disp_MAIN_RS485_UART(void)
*描述- Description:		//显示//Main█RS485_UART 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_MAIN_RS485_UART(void) //显示//Main█RS485_UART 菜单选择(工作时)
{
		// 显示: 第"01 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_14Test_Line01, 21);
		// 显示: 第"02 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_14Test_Line02, 21);
		// 显示: 第"03 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_14Test_Line03, 21);
		// 显示: 第"04 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_14Test_Line04, 21);
		// 显示: 第"05 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_14Test_Line05, 21);
		// 显示: 第"06 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_14Test_Line06, 21);
		// 显示: 第"07 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_14Test_Line07, 21);
		// 显示: 第"08 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_14Test_Line08, 21);
		// 显示: 第"09 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_14Test_Line09, 21);
		// 显示: 第"10 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_14Test_Line10, 21);
		// 显示: 第"11 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_14Test_Line11, 21);
		// 显示: 第"12 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_14Test_Line12, 21);

	mUpdate_All_TestLine;  //刷新所有" 测试行"
}


/****************************************************************************
*函数名-Function:	void Disp_RS485_Char_1(void)
*描述- Description:		显示RS485收到数据"1" (字符)	
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_RS485_Char_1(void) //显示RS485收到数据"1" (字符)	
{
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01], Msg_14Test_TXT1, 21);
	F_Update_TestLine07 = YES;//刷新:""测试行"" 
}


/****************************************************************************
*函数名-Function:	void Disp_RS485_Char_2(void)
*描述- Description:		显示RS485收到数据"2" (字符)	
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_RS485_Char_2(void) //显示RS485收到数据"2" (字符)	
{
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01], Msg_14Test_TXT2, 21);
	F_Update_TestLine07 = YES;//刷新:""测试行"" 
}



/****************************************************************************
*函数名-Function:	void Disp_MAIN_CC1101_Test(void)
*描述- Description:		//显示//Main█CC1101_Test 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_MAIN_CC1101_Test(void) //显示//Main█CC1101_Test 菜单选择(工作时)
{
		// 显示: 第"01 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_15Test_Line01, 21);
		// 显示: 第"02 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_15Test_Line02, 21);
		// 显示: 第"03 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_15Test_Line03, 21);
		// 显示: 第"04 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_15Test_Line04, 21);
		// 显示: 第"05 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_15Test_Line05, 21);
		// 显示: 第"06 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_15Test_Line06, 21);
		// 显示: 第"07 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_15Test_Line07, 21);
		// 显示: 第"08 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_15Test_Line08, 21);
		// 显示: 第"09 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_15Test_Line09, 21);
		// 显示: 第"10 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_15Test_Line10, 21);
		// 显示: 第"11 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_15Test_Line11, 21);
		// 显示: 第"12 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_15Test_Line12, 21);

	mUpdate_All_TestLine;  //刷新所有" 测试行"
}


/****************************************************************************
*函数名-Function:	void Disp_CC1101_Char_1(void)
*描述- Description:		显示CC1101收到数据"1"  (字符)		
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_CC1101_Char_1(void) //显示CC1101收到数据"1"  (字符)		
{
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01], Msg_15Test_TXT1, 21);
	F_Update_TestLine07 = YES;//刷新:""测试行"" 
}


/****************************************************************************
*函数名-Function:	void Disp_CC1101_Char_2(void)
*描述- Description:		显示CC1101收到数据"2"  (字符)		
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_CC1101_Char_2(void) //显示CC1101收到数据"2"  (字符)		
{
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01], Msg_15Test_TXT2, 21);
	F_Update_TestLine07 = YES;//刷新:""测试行"" 
}






/****************************************************************************
*函数名-Function:	void Disp_MAIN_SD_Card_Test(void)
*描述- Description:		 //显示//Main█SD_Card_Test 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_MAIN_SD_Card_Test(void)  //显示//Main█SD_Card_Test 菜单选择(工作时)
{
		// 显示: 第"01 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_16Test_Line01, 21);
		// 显示: 第"02 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_16Test_Line02, 21);
		// 显示: 第"03 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_16Test_Line03, 21);
		// 显示: 第"04 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_16Test_Line04, 21);
		// 显示: 第"05 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_16Test_Line05, 21);
		// 显示: 第"06 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_16Test_Line06, 21);
		// 显示: 第"07 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_16Test_Line07, 21);
		// 显示: 第"08 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_16Test_Line08, 21);
		// 显示: 第"09 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_16Test_Line09, 21);
		// 显示: 第"10 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_16Test_Line10, 21);
		// 显示: 第"11 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_16Test_Line11, 21);
		// 显示: 第"12 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_16Test_Line12, 21);

	mUpdate_All_TestLine;  //刷新所有" 测试行"

}


/****************************************************************************
*函数名-Function:	void Disp_SD_Card_Char(void)
*描述- Description:		显示SD_Card读到的数据 (字符)		
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_SD_Card_Char(void) //显示SD_Card读到的数据 (字符)		
{
	G_LcdBuf[TestLine03][TestColumn13] = ASCII_Table[G_Data_SD_Read]; 
	G_LcdBuf[TestLine04][TestColumn13] = ASCII_Table[G_Data_SD_Write]; 

	F_Update_TestLine03 = YES;//刷新:""测试行"" 
	F_Update_TestLine04 = YES;//刷新:""测试行"" 
}



/****************************************************************************
*函数名-Function:	void Disp_MAIN_MassStorage_Test(void)
*描述- Description:		//显示//Main█MassStorage_Test 菜单选择(工作时)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Disp_MAIN_MassStorage_Test(void) //显示//Main█MassStorage_Test 菜单选择(工作时)
{
		// 显示: 第"01 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_17Test_Line01, 21);
		// 显示: 第"02 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_17Test_Line02, 21);
		// 显示: 第"03 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_17Test_Line03, 21);
		// 显示: 第"04 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_17Test_Line04, 21);
		// 显示: 第"05 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_17Test_Line05, 21);
		// 显示: 第"06 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_17Test_Line06, 21);
		// 显示: 第"07 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_17Test_Line07, 21);
		// 显示: 第"08 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_17Test_Line08, 21);
		// 显示: 第"09 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_17Test_Line09, 21);
		// 显示: 第"10 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_17Test_Line10, 21);
		// 显示: 第"11 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_17Test_Line11, 21);
		// 显示: 第"12 测试行"(工作)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_17Test_Line12, 21);

	mUpdate_All_TestLine;  //刷新所有" 测试行"


}






