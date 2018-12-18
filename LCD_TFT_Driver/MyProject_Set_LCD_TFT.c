/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 MyProject_Set_LCD_TFT.c
* �����ļ�-Dependencies:  	 MyProject_Set_LCD_TFT.h; System_HeadFile.h; 
* �ļ�����-File Description:	 ( Դ����-Source File) 
	�� ������Ŀ: LCD_TFTҺ����ʾ����(�������е�Һ������)
	01)     02)     03)    04)    05)    06)	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ע������-Attention : 	
	��01)     ��02)     ��03)    ��04)    ��05)    ��06)     
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
* �޸ļ�¼-Change History:   
	����   ʱ��        �汾  ��������
	Author 	 Date		   Rev      Comment
	-------------------------------------------------------------------------------
	BlueS	2012-12-12	  1.0	   
			xxxx-xx-xx	  x.x	   
			xxxx-xx-xx	  x.x				
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
* ��˾-Company: 			CS-EMLAB  Co. , Ltd.
* ������Э��-Software License Agreement:
	Copyright (C) 2012-2020 	CS-EMLAB  Co. , Ltd.	All rights reserved.	

*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/


#include "System_HeadFile.h"   //����: ϵͳȫ��ͷ�ļ���(��������ʹ�õ���ͷ�ļ�)

	//������Ŀ: LCD_TFTҺ����ʾ����(�������е�Һ������) -ͷ�ļ�
#include "MyProject_Set_LCD_TFT.h"  



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//--**��ʾ: "���"**---------------------------------------------------//
////////////////////////////////////////////////////////////////////////////

//const unsigned char Msg_AD_1[] = {"  Welcome to MSP430F6638   \0"}; //22 (��28�ֽ�) 
//const unsigned char Msg_AD_2[] = {"    http://www.ti.com      \0"}; //17(��28�ֽ�) 
//const unsigned char Msg_AD_3[] = {"Error A  6638-V1.0  Error'C\0"}; //(��28�ֽ�)  // "�汾�� " ���


//const unsigned char Msg_Temp[] = {"123456789abcdefgADCDEFGHIJK\0"};


////////////////////////////////////////////////////////////////////////////
//--**��ʾ: "ʵʱʱ��"**--------------------------------------------//
////////////////////////////////////////////////////////////////////////////
//const unsigned char Msg_RealTime[] = {"2012-12-12 00:00:00 FRI\0"}; 

const unsigned char Msg_Error_ModifyTime[] = {"Setting Error!      \0"}; // (��21�ֽ�) 
const unsigned char Msg_Error_ReEnter[] =    {"Please Re-enter!    \0"}; // (��21�ֽ�) 







////////////////////////////////////////////////////////////////////////////
//--**��ʾ: " �����˵�"**-------------------------------------------//
////////////////////////////////////////////////////////////////////////////
const unsigned char Msg_ClearLine[] =  {"                           \0"}; // (��28�ֽ�) 
const unsigned char Msg_SelectFlag[] = {"=>"}; // (��2�ֽ�) //ѡ�б�־

const unsigned char Msg_01Page_MenuLine_01[] = {"      M E N U      \0"}; // (��20�ֽ�) 
const unsigned char Msg_01Page_MenuLine_02[] = {"01.Basic--Setting  \0"}; // (��20�ֽ�) 
const unsigned char Msg_01Page_MenuLine_03[] = {"02.Basic--Check    \0"}; // (��20�ֽ�) 
const unsigned char Msg_01Page_MenuLine_04[] = {"03.LCD_TFT         \0"}; // (��20�ֽ�) 
const unsigned char Msg_01Page_MenuLine_05[] = {"04.Matrix Key      \0"}; // (��20�ֽ�) 
const unsigned char Msg_01Page_MenuLine_06[] = {"05.Touch Pads      \0"}; // (��20�ֽ�) 
const unsigned char Msg_01Page_MenuLine_07[] = {"06.INA21x--Current \0"}; // (��20�ֽ�) 
const unsigned char Msg_01Page_MenuLine_08[] = {"07.TMP006          \0"}; // (��20�ֽ�) 
const unsigned char Msg_01Page_MenuLine_09[] = {"08.Volt Meter--ADC \0"}; // (��20�ֽ�) 
const unsigned char Msg_01Page_MenuLine_10[] = {"09.DC--Motor       \0"}; // (��20�ֽ�) 
const unsigned char Msg_01Page_MenuLine_11[] = {"10.Step--Motor     \0"}; // (��20�ֽ�) 
const unsigned char Msg_01Page_MenuLine_12[] = {"11.NTC and HR202   \0"}; // (��20�ֽ�) 

const unsigned char Msg_02Page_MenuLine_01[] = {"      M E N U      \0"}; // (��20�ֽ�) 
const unsigned char Msg_02Page_MenuLine_02[] = {"12.IrDA  - UART    \0"}; // (��20�ֽ�) 
const unsigned char Msg_02Page_MenuLine_03[] = {"13.RS232 - UART    \0"}; // (��20�ֽ�) 
const unsigned char Msg_02Page_MenuLine_04[] = {"14.RS485 - UART    \0"}; // (��20�ֽ�) 
const unsigned char Msg_02Page_MenuLine_05[] = {"15.CC1101 - 433MHz \0"}; // (��20�ֽ�) 
const unsigned char Msg_02Page_MenuLine_06[] = {"16.SD Card         \0"}; // (��20�ֽ�) 
const unsigned char Msg_02Page_MenuLine_07[] = {"17.USB - SD Card   \0"}; // (��20�ֽ�) 
const unsigned char Msg_02Page_MenuLine_08[] = {"                   \0"}; // (��20�ֽ�) 
const unsigned char Msg_02Page_MenuLine_09[] = {"                   \0"}; // (��20�ֽ�) 
const unsigned char Msg_02Page_MenuLine_10[] = {"                   \0"}; // (��20�ֽ�) 
const unsigned char Msg_02Page_MenuLine_11[] = {"                   \0"}; // (��20�ֽ�) 
const unsigned char Msg_02Page_MenuLine_12[] = {"                   \0"}; // (��20�ֽ�) 




////////////////////////////////////////////////////////////////////////////
//--**��ʾ: " ������������"**--------------------------------------//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//--**"����״̬" ��־**---------------------------------------------//


////////////////////////////////////////////////////////////////////////////
//--**01.�����˵�"�Ĳ�������**----------------------------------//

const unsigned char Msg_01Test_Line01[] = {"  01.Basic--Setting \0"}; // (��21�ֽ�) 
const unsigned char Msg_01Test_Line02[] = {"1.Restart Self-Test \0"}; // (��21�ֽ�) 
const unsigned char Msg_01Test_Line03[] = {"2.Time Setting      \0"}; // (��21�ֽ�) 
const unsigned char Msg_01Test_Line04[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_01Test_Line05[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_01Test_Line06[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_01Test_Line07[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_01Test_Line08[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_01Test_Line09[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_01Test_Line10[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_01Test_Line11[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_01Test_Line12[] = {"                    \0"}; // (��21�ֽ�) 


////////////////////////////////////////////////////////////////////////////
//--**02.�����˵�"�Ĳ�������**----------------------------------//
const unsigned char Msg_02Test_Line01[] = {"  02.Basic--Check   \0"}; // (��21�ֽ�) 
const unsigned char Msg_02Test_Line02[] = {"1.LED_Diode - SOS   \0"}; // (��21�ֽ�) 
const unsigned char Msg_02Test_Line03[] = {"2.LED_Segment       \0"}; // (��21�ֽ�) 
const unsigned char Msg_02Test_Line04[] = {"3.LCD_Segment       \0"}; // (��21�ֽ�) 
const unsigned char Msg_02Test_Line05[] = {"4.Buzzer - Alarm    \0"}; // (��21�ֽ�) 
const unsigned char Msg_02Test_Line06[] = {"5.Speaker - Sing    \0"}; // (��21�ֽ�) 
const unsigned char Msg_02Test_Line07[] = {"6.Microphone -Record\0"}; // (��21�ֽ�) 
const unsigned char Msg_02Test_Line08[] = {"7.Battery Fuel Gauge\0"}; // (��21�ֽ�) 
const unsigned char Msg_02Test_Line09[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_02Test_Line10[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_02Test_Line11[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_02Test_Line12[] = {"                    \0"}; // (��21�ֽ�) 


////////////////////////////////////////////////////////////////////////////
//--**03.�����˵�"�Ĳ�������**----------------------------------//
const unsigned char Msg_03Test_Line01[] = {"  03.LCD_TFT        \0"}; // (��21�ֽ�) 
const unsigned char Msg_03Test_Line02[] = {"1.Line              \0"}; // (��21�ֽ�) 
const unsigned char Msg_03Test_Line03[] = {"2.Rectangle         \0"}; // (��21�ֽ�) 
const unsigned char Msg_03Test_Line04[] = {"3.Circle            \0"}; // (��21�ֽ�) 
const unsigned char Msg_03Test_Line05[] = {"4.Fill Area         \0"}; // (��21�ֽ�) 
const unsigned char Msg_03Test_Line06[] = {"5.Chinese           \0"}; // (��21�ֽ�) 
const unsigned char Msg_03Test_Line07[] = {"6.Clear             \0"}; // (��21�ֽ�) 
const unsigned char Msg_03Test_Line08[] = {"********************\0"}; // (��21�ֽ�) 
const unsigned char Msg_03Test_Line09[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_03Test_Line10[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_03Test_Line11[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_03Test_Line12[] = {"                    \0"}; // (��21�ֽ�) 


////////////////////////////////////////////////////////////////////////////
//--**04.�����˵�"�Ĳ�������**----------------------------------//
const unsigned char Msg_04Test_Line01[] = {"  04.Matrix Key     \0"}; // (��21�ֽ�) 
const unsigned char Msg_04Test_Line02[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_04Test_Line03[] = {"Press the matrix key\0"}; // (��21�ֽ�) 
const unsigned char Msg_04Test_Line04[] = {"one by one.         \0"}; // (��21�ֽ�) 
const unsigned char Msg_04Test_Line05[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_04Test_Line06[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_04Test_Line07[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_04Test_Line08[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_04Test_Line09[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_04Test_Line10[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_04Test_Line11[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_04Test_Line12[] = {"                    \0"}; // (��21�ֽ�) 


////////////////////////////////////////////////////////////////////////////
//--**05.�����˵�"�Ĳ�������**----------------------------------//
const unsigned char Msg_05Test_Line01[] = {"  05.Touch Pads     \0"}; // (��21�ֽ�) 
const unsigned char Msg_05Test_Line02[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_05Test_Line03[] = {"Press the touch pads\0"}; // (��21�ֽ�) 
const unsigned char Msg_05Test_Line04[] = {"one by one.         \0"}; // (��21�ֽ�) 
const unsigned char Msg_05Test_Line05[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_05Test_Line06[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_05Test_Line07[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_05Test_Line08[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_05Test_Line09[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_05Test_Line10[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_05Test_Line11[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_05Test_Line12[] = {"                    \0"}; // (��21�ֽ�) 


////////////////////////////////////////////////////////////////////////////
//--**06.�����˵�"�Ĳ�������**----------------------------------//
const unsigned char Msg_06Test_Line01[] = {"  06.INA21x--Current\0"}; // (��21�ֽ�) 
const unsigned char Msg_06Test_Line02[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_06Test_Line03[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_06Test_Line04[] = {"Current: FFF mA     \0"}; // (��21�ֽ�) 
const unsigned char Msg_06Test_Line05[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_06Test_Line06[] = {"The LED_Segment also\0"}; // (��21�ֽ�) 
const unsigned char Msg_06Test_Line07[] = {"displays the current\0"}; // (��21�ֽ�) 
const unsigned char Msg_06Test_Line08[] = {"value.              \0"}; // (��21�ֽ�) 
const unsigned char Msg_06Test_Line09[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_06Test_Line10[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_06Test_Line11[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_06Test_Line12[] = {"                    \0"}; // (��21�ֽ�) 





////////////////////////////////////////////////////////////////////////////
//--**07.�����˵�"�Ĳ�������**----------------------------------//
const unsigned char Msg_07Test_Line01[] = {"  07.TMP006         \0"}; // (��21�ֽ�) 
const unsigned char Msg_07Test_Line02[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_07Test_Line03[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_07Test_Line04[] = {"Temperature:FFF.F 'C\0"}; // (��21�ֽ�) 
const unsigned char Msg_07Test_Line05[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_07Test_Line06[] = {"The LED_Segment also\0"}; // (��21�ֽ�) 
const unsigned char Msg_07Test_Line07[] = {"displays temperature\0"}; // (��21�ֽ�) 
const unsigned char Msg_07Test_Line08[] = {"value.              \0"}; // (��21�ֽ�) 
const unsigned char Msg_07Test_Line09[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_07Test_Line10[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_07Test_Line11[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_07Test_Line12[] = {"                    \0"}; // (��21�ֽ�) 


////////////////////////////////////////////////////////////////////////////
//--**08.�����˵�"�Ĳ�������**----------------------------------//
const unsigned char Msg_08Test_Line01[] = {"  08.Volt Meter--ADC\0"}; // (��21�ֽ�) 
const unsigned char Msg_08Test_Line02[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_08Test_Line03[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_08Test_Line04[] = {"Voltage: F.FF V     \0"}; // (��21�ֽ�) 
const unsigned char Msg_08Test_Line05[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_08Test_Line06[] = {"The LED_Segment also\0"}; // (��21�ֽ�) 
const unsigned char Msg_08Test_Line07[] = {"displays the voltage\0"}; // (��21�ֽ�) 
const unsigned char Msg_08Test_Line08[] = {"value.              \0"}; // (��21�ֽ�) 
const unsigned char Msg_08Test_Line09[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_08Test_Line10[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_08Test_Line11[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_08Test_Line12[] = {"                    \0"}; // (��21�ֽ�) 





////////////////////////////////////////////////////////////////////////////
//--**09.�����˵�"�Ĳ�������**----------------------------------//
const unsigned char Msg_09Test_Line01[] = {"  09.DC--Motor      \0"}; // (��21�ֽ�) 
const unsigned char Msg_09Test_Line02[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_09Test_Line03[] = {"1.Positive Rotation \0"}; // (��21�ֽ�) 
const unsigned char Msg_09Test_Line04[] = {"2.Reverse Rotation  \0"}; // (��21�ֽ�) 
const unsigned char Msg_09Test_Line05[] = {"3.Stop DC-Motor     \0"}; // (��21�ֽ�) 
const unsigned char Msg_09Test_Line06[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_09Test_Line07[] = {"Voltage: F.F V      \0"}; // (��21�ֽ�) 
const unsigned char Msg_09Test_Line08[] = {"  Speed: FFFFF r/min\0"}; // (��21�ֽ�) 
const unsigned char Msg_09Test_Line09[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_09Test_Line10[] = {"The LED_Segment also\0"}; // (��21�ֽ�) 
const unsigned char Msg_09Test_Line11[] = {"displays the voltage\0"}; // (��21�ֽ�) 
const unsigned char Msg_09Test_Line12[] = {"and speed.          \0"}; // (��21�ֽ�) 

////////////////////////////////////////////////////////////////////////////
//--**10.�����˵�"�Ĳ�������**----------------------------------//
const unsigned char Msg_10Test_Line01[] = {"  10.Step--Motor    \0"}; // (��21�ֽ�) 
const unsigned char Msg_10Test_Line02[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_10Test_Line03[] = {"1.Positive Rotation \0"}; // (��21�ֽ�) 
const unsigned char Msg_10Test_Line04[] = {"2.Reverse Rotation  \0"}; // (��21�ֽ�) 
const unsigned char Msg_10Test_Line05[] = {"3.Stop Step-Motor   \0"}; // (��21�ֽ�) 
const unsigned char Msg_10Test_Line06[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_10Test_Line07[] = {"Voltage: F.F V      \0"}; // (��21�ֽ�) 
const unsigned char Msg_10Test_Line08[] = {"  Speed: FFF.F r/min\0"}; // (��21�ֽ�) 
const unsigned char Msg_10Test_Line09[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_10Test_Line10[] = {"The LED_Segment also\0"}; // (��21�ֽ�) 
const unsigned char Msg_10Test_Line11[] = {"displays the voltage\0"}; // (��21�ֽ�) 
const unsigned char Msg_10Test_Line12[] = {"and speed.          \0"}; // (��21�ֽ�) 


////////////////////////////////////////////////////////////////////////////
//--**11.�����˵�"�Ĳ�������**----------------------------------//
const unsigned char Msg_11Test_Line01[] = {"  11.NTC and HR202  \0"}; // (��21�ֽ�) 
const unsigned char Msg_11Test_Line02[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_11Test_Line03[] = {"Temperature:FFF.F 'C\0"}; // (��21�ֽ�) 
const unsigned char Msg_11Test_Line04[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_11Test_Line05[] = {"   Humidity: FFF %RH\0"}; // (��21�ֽ�) 
const unsigned char Msg_11Test_Line06[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_11Test_Line07[] = {"The LED_Segment also\0"}; // (��21�ֽ�) 
const unsigned char Msg_11Test_Line08[] = {"displays temperature\0"}; // (��21�ֽ�) 
const unsigned char Msg_11Test_Line09[] = {"and humidity.       \0"}; // (��21�ֽ�) 
const unsigned char Msg_11Test_Line10[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_11Test_Line11[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_11Test_Line12[] = {"                    \0"}; // (��21�ֽ�) 


////////////////////////////////////////////////////////////////////////////
//--**12.�����˵�"�Ĳ�������**----------------------------------//
const unsigned char Msg_12Test_Line01[] = {"  12.IrDA  - UART   \0"}; // (��21�ֽ�) 
const unsigned char Msg_12Test_Line02[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_12Test_Line03[] = {"Take something on   \0"}; // (��21�ֽ�) 
const unsigned char Msg_12Test_Line04[] = {"the front of the    \0"}; // (��21�ֽ�) 
const unsigned char Msg_12Test_Line05[] = {"IrDA receiver.      \0"}; // (��21�ֽ�) 
const unsigned char Msg_12Test_Line06[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_12Test_Line07[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_12Test_Line08[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_12Test_Line09[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_12Test_Line10[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_12Test_Line11[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_12Test_Line12[] = {"                    \0"}; // (��21�ֽ�) 

const unsigned char Msg_12Test_TXT1[] =   {"  IrDA receives '1' \0"}; // (��28�ֽ�) 
const unsigned char Msg_12Test_TXT2[] =   {"                    \0"}; // (��21�ֽ�) 




////////////////////////////////////////////////////////////////////////////
//--**13.�����˵�"�Ĳ�������**----------------------------------//
const unsigned char Msg_13Test_Line01[] = {"  13.RS232 - UART   \0"}; // (��21�ֽ�) 
const unsigned char Msg_13Test_Line02[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_13Test_Line03[] = {"1.Send 'RS232' to PC\0"}; // (��21�ֽ�) 
const unsigned char Msg_13Test_Line04[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_13Test_Line05[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_13Test_Line06[] = {"If PC sends data to \0"}; // (��21�ֽ�) 
const unsigned char Msg_13Test_Line07[] = {"6638, the 6638 will \0"}; // (��21�ֽ�) 
const unsigned char Msg_13Test_Line08[] = {"sent it back.       \0"}; // (��21�ֽ�) 
const unsigned char Msg_13Test_Line09[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_13Test_Line10[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_13Test_Line11[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_13Test_Line12[] = {"                    \0"}; // (��21�ֽ�) 

const unsigned char Msg_13Test_TXT1[] =   {"  6638 receives '1' \0"}; // (��21�ֽ�) 
const unsigned char Msg_13Test_TXT2[] =   {"  6638 receives '2'.\0"}; // (��21�ֽ�) 
const unsigned char Msg_13Test_TXT3[] =   {"                    \0"}; // (��21�ֽ�) 






////////////////////////////////////////////////////////////////////////////
//--**14.�����˵�"�Ĳ�������**----------------------------------//
const unsigned char Msg_14Test_Line01[] = {"  14.RS485 - UART   \0"}; // (��21�ֽ�) 
const unsigned char Msg_14Test_Line02[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_14Test_Line03[] = {"1.Send '1' to others\0"}; // (��21�ֽ�) 
const unsigned char Msg_14Test_Line04[] = {"2.Send '2' to others\0"}; // (��21�ֽ�) 
const unsigned char Msg_14Test_Line05[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_14Test_Line06[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_14Test_Line07[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_14Test_Line08[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_14Test_Line09[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_14Test_Line10[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_14Test_Line11[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_14Test_Line12[] = {"                    \0"}; // (��21�ֽ�) 

const unsigned char Msg_14Test_TXT1[] =   {" RS485 receives '1'.\0"}; //  (��21�ֽ�) 
const unsigned char Msg_14Test_TXT2[] =   {" RS485 receives '2'.\0"}; //  (��21�ֽ�)  

////////////////////////////////////////////////////////////////////////////
//--**15.�����˵�"�Ĳ�������**----------------------------------//
const unsigned char Msg_15Test_Line01[] = {"  15.CC1101 - 433MHz\0"}; // (��21�ֽ�) 
const unsigned char Msg_15Test_Line02[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_15Test_Line03[] = {"1.Send '1' to others\0"}; // (��21�ֽ�) 
const unsigned char Msg_15Test_Line04[] = {"2.Send '2' to others\0"}; // (��21�ֽ�) 
const unsigned char Msg_15Test_Line05[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_15Test_Line06[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_15Test_Line07[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_15Test_Line08[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_15Test_Line09[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_15Test_Line10[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_15Test_Line11[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_15Test_Line12[] = {"                    \0"}; // (��21�ֽ�) 

const unsigned char Msg_15Test_TXT1[] =   {"CC1101 receives '1'.\0"}; //  (��21�ֽ�) 
const unsigned char Msg_15Test_TXT2[] =   {"CC1101 receives '2'.\0"}; //  (��21�ֽ�)  


////////////////////////////////////////////////////////////////////////////
//--**16.�����˵�"�Ĳ�������**----------------------------------//
const unsigned char Msg_16Test_Line01[] = {"  15.SD Card        \0"}; // (��21�ֽ�) 
const unsigned char Msg_16Test_Line02[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_16Test_Line03[] = {"Key--Write:         \0"}; // (��21�ֽ�) 
const unsigned char Msg_16Test_Line04[] = {"Key-- Read:         \0"}; // (��21�ֽ�) 
const unsigned char Msg_16Test_Line05[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_16Test_Line06[] = {"Press a matrix key, \0"}; // (��21�ֽ�) 
const unsigned char Msg_16Test_Line07[] = {"6638 will write the \0"}; // (��21�ֽ�) 
const unsigned char Msg_16Test_Line08[] = {"key value into SD.  \0"}; // (��21�ֽ�) 
const unsigned char Msg_16Test_Line09[] = {"Then, use a PC to   \0"}; // (��21�ֽ�) 
const unsigned char Msg_16Test_Line10[] = {"read the data of SD.\0"}; // (��21�ֽ�) 
const unsigned char Msg_16Test_Line11[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_16Test_Line12[] = {"                    \0"}; // (��21�ֽ�) 





////////////////////////////////////////////////////////////////////////////
//--**17.�����˵�"�Ĳ�������**----------------------------------//
const unsigned char Msg_17Test_Line01[] = {"  17.USB - SD Card  \0"}; // (��21�ֽ�) 
const unsigned char Msg_17Test_Line02[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_17Test_Line03[] = {"1.Connect to PC     \0"}; // (��21�ֽ�) 
const unsigned char Msg_17Test_Line04[] = {"2.Disconnect        \0"}; // (��21�ֽ�) 
const unsigned char Msg_17Test_Line05[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_17Test_Line06[] = {"                    \0"}; // (��21�ֽ�) 
const unsigned char Msg_17Test_Line07[] = {"Connect the 'USB1'  \0"}; // (��21�ֽ�) 
const unsigned char Msg_17Test_Line08[] = {"(on 6638) to PC with\0"}; // (��21�ֽ�) 
const unsigned char Msg_17Test_Line09[] = {"a usb cable.        \0"}; // (��21�ֽ�) 
const unsigned char Msg_17Test_Line10[] = {"If connected,you can\0"}; // (��21�ֽ�) 
const unsigned char Msg_17Test_Line11[] = {"see 'removable disk'\0"}; // (��21�ֽ�) 
const unsigned char Msg_17Test_Line12[] = {"on your PC.         \0"}; // (��21�ֽ�) 




////////////////////////////////////////////////////////////////////////////
//--**��ʾ: " �����������ò˵�"**-------------------------------//
////////////////////////////////////////////////////////////////////////////
//const unsigned char Msg_BasicMenu_1[] = {"������������"}; //(��1��)
//const unsigned char Msg_BasicMenu_2[] = {" 1��ʱ���޸�"};  //(��3��)
//const unsigned char Msg_BasicMenu_3[] = {" 2����������"};  //(��4��)
//const unsigned char Msg_BasicMenu_4[] = {" 3�������޸�"};  //(��5��)


////////////////////////////////////////////////////////////////////////////
//--**��ʾ: " ʱ���޸Ĳ˵�"**-------------------------------------//
////////////////////////////////////////////////////////////////////////////
//const unsigned char Msg_Set_Time_1[] = {"ʱ���޸�"}; //(��1��)
//const unsigned char Msg_Set_Time_2[] = {"----��--��--��--: --"}; //��20�ֽ�  //(��3��)	   


////////////////////////////////////////////////////////////////////////////
//--**��ʾ: " ���������޸Ĳ˵�"**-------------------------------//
////////////////////////////////////////////////////////////////////////////
//const unsigned char Msg_Set_ScreenSaver_1[] = {"���������޸�"}; //(��1��)
   
//const unsigned char Msg_Set_ScreenSaver_2[] = {"1.����ѡ��: "};  //(��3��)
//const unsigned char Msg_Set_ScreenSaver_3[] = {"2.����ʱ��: ---- ��"};  //(��4��)



////////////////////////////////////////////////////////////////////////////
//--**��ʾ: "�ʻ�"**---------------------------------------------------//
////////////////////////////////////////////////////////////////////////////
//const unsigned char Msg_Count_1[] = {"������ 6λ��������"}; //(��1��)
//const unsigned char Msg_Count_2[] = {"��������: ------"};   //(��3��)

//const unsigned char Msg_Count_3[] = {"�޸Ĺ���Ա����"}; //��14�ֽ�//(��1��)
//const unsigned char Msg_Count_4[] = {"����������: ------"}; //��18�ֽ�//(��3��)	   





////////////////////////////////////////////////////////////////////////////
//--**��ʾ: " ������ȷ"**--------------------------------------------//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//--**��ʾ: " ���ô���"**--------------------------------------------//
////////////////////////////////////////////////////////////////////////////
//const unsigned char Msg_Error_1[]={"����������"};  //(30�ֽ�)



////////////////////////////////////////////////////////////////////////////
//--**��ʾ: " ����״̬��"**-----------------------------------------//
////////////////////////////////////////////////////////////////////////////

//const unsigned char Msg_Work_1[] = {""}; //(30�ֽ�)







////////////////////////////////////////////////////////////////////////////
//--**��ʾ:  "����" �����ʾ**-------------------------------------//
///////////////////////////////////////////////////////////////////////////





/****************************************************************************
*������-Function:	void Disp_RTC_CurrentTime(void)
*����- Description:	��ʾ: RTC ʵʱʱ��
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_RTC_CurrentTime(void)
{
	if(F_SecondChange_RTC)
	{
		F_SecondChange_RTC = 0;
		
		Copy_Array_AtoB(&G_LcdBuf[M_15LineBuf][M_01ColumnBuf], G_RTC_ReadBuf, 23);
		
		F_Update_RealTime = YES;	 //ˢ��:"ʵʱʱ��"	
	}
}



/****************************************************************************
*������-Function:	void Disp_INA21x_CurrentValue(unsigned int INA21x_Ad)
*����- Description:	��ʾ: INA21x ʵʱ"������ֵ"
*�������-Input:	INA21x_Ad : Ҫ��ʾ��ʵ�ʵ���ֵ
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_INA21x_CurrentValue(unsigned int INA21x_Ad)
{
	unsigned char b,c,d;  
	
//	a = (unsigned char)(INA21x_Ad/1000);
	b = (unsigned char)((INA21x_Ad % 1000)/100);
	c = (unsigned char)((INA21x_Ad % 100)/10);
	d = (unsigned char)(INA21x_Ad % 10);


		//ˢ��Ҫ��ʾ��"ʵ�ʵ���ֵ"����λA,��ʾ250A
	//G_LcdBuf[M_15LineBuf][M_24ColumnBuf] = ASCII_Table[a];   //��λ
	//G_LcdBuf[M_15LineBuf][M_Start_Column_Buf+1] = '.';   //С����
	G_LcdBuf[M_15LineBuf][M_31ColumnBuf] = ASCII_Table[b];	 //��һλ
	if(b == 0) G_LcdBuf[M_15LineBuf][M_31ColumnBuf] = 0x20;
	G_LcdBuf[M_15LineBuf][M_32ColumnBuf] = ASCII_Table[c];   //�ڶ�λ
	G_LcdBuf[M_15LineBuf][M_33ColumnBuf] = ASCII_Table[d];   //����λ
	G_LcdBuf[M_15LineBuf][M_34ColumnBuf] = 'm';   
	G_LcdBuf[M_15LineBuf][M_35ColumnBuf] = 'A';  

	F_Update_CurrentValue = YES; //ˢ��:"INA21x ʵʱ����ֵ" 
}






/****************************************************************************
*������-Function:	void Disp_NTC_TMP(int NTC_TMP_Ad)
*����- Description:	��ʾ: ʵʱ"NTC ��������ֵ"��Ӧ���¶�
*�������-Input:	NTC_TMP_Ad :  NTC ���ó����¶�ֵ(��������)
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_NTC_TMP(int NTC_TMP_Ad)
{
	unsigned char a,b,c,d;
	
	if(NTC_TMP_Ad < 0)
	{
		NTC_TMP_Ad = - NTC_TMP_Ad;
		
		b = (unsigned char)((NTC_TMP_Ad % 1000)/100);  //ʮλ
		c = (unsigned char)((NTC_TMP_Ad % 100)/10);    //��λ
		d = (unsigned char)(NTC_TMP_Ad % 10);          //С����һλ

		G_LcdBuf[TestLine03][TestColumn13] = '-';//��λ 
		G_LcdBuf[TestLine03][TestColumn14] = ASCII_Table[b]; //ʮλ
		G_LcdBuf[TestLine03][TestColumn15] = ASCII_Table[c]; //��λ
		G_LcdBuf[TestLine03][TestColumn16] = '.'; //С����
		G_LcdBuf[TestLine03][TestColumn17] = ASCII_Table[d]; //С����һλ

		if(b == 0) 
		{
			G_LcdBuf[TestLine03][TestColumn13] = 0x20;//��λ
			G_LcdBuf[TestLine03][TestColumn14] = '-'; //ʮλ	
		}

	}
	else
	{
		a = (unsigned char)(NTC_TMP_Ad/1000);
		b = (unsigned char)((NTC_TMP_Ad % 1000)/100);
		c = (unsigned char)((NTC_TMP_Ad % 100)/10);
		d = (unsigned char)(NTC_TMP_Ad % 10);

		G_LcdBuf[TestLine03][TestColumn13] = ASCII_Table[a];//��λ	 
		G_LcdBuf[TestLine03][TestColumn14] = ASCII_Table[b]; //ʮλ
		G_LcdBuf[TestLine03][TestColumn15] = ASCII_Table[c]; //��λ
		G_LcdBuf[TestLine03][TestColumn16] = '.'; //С����
		G_LcdBuf[TestLine03][TestColumn17] = ASCII_Table[d]; //С����һλ

		if(a == 0) 
		{
			G_LcdBuf[TestLine03][TestColumn13] = 0x20; //��λ	 
		}
		else if((a == 0)&&(b == 0))
		{
			G_LcdBuf[TestLine03][TestColumn13] = 0x20; //��λ	
			G_LcdBuf[TestLine03][TestColumn14] = 0x20; //ʮλ	
		}
	}

		//ˢ��Ҫ��ʾ��"ʵ��ʪ��ֵֵ"����ʾ123.4'C

//G_LcdBuf[TestLine03][M_Start_Column_Buf+25] = '\'';   
//G_LcdBuf[TestLine03][M_Start_Column_Buf+26] = 'C';  

	F_Update_TestLine03 = YES; //ˢ��:""������"" 
}


/****************************************************************************
*������-Function:	void Disp_HR202_Humidity(unsigned char humidity)
*����- Description:	��ʾ: "HR202_Humidity " ʪ��
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_HR202_Humidity(unsigned char humidity)
{
	G_LcdBuf[TestLine05][TestColumn14] = ASCII_Table[humidity /100];   //��λ
	if((humidity /100) == 0) G_LcdBuf[TestLine05][TestColumn14] = 0x20;   //��λ
	
	G_LcdBuf[TestLine05][TestColumn15] = ASCII_Table[(humidity /10)% 10];   //ʮλ
	G_LcdBuf[TestLine05][TestColumn16] = ASCII_Table[humidity % 10];   //��λ
//G_LcdBuf[TestLine05][M_Start_Column_Buf+26] = '%'; //��λ 

	F_Update_TestLine05 = YES; //ˢ��:""������"" 
}




////////////////////////////////////////////////////////////////////////////
//--**��ʾ:  "�˵�ѡ��" �൱��ʾ**-------------------------------//
////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////
//--**��ʾ:  "��������" �����ʾ**-------------------------------//
////////////////////////////////////////////////////////////////////////////


/****************************************************************************
*������-Function:	void Disp_MAIN_ModifyTime(void)
*����- Description:	//��ʾ//Main��"ʵʱʱ��"�޸�״̬
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_MAIN_ModifyTime(void)//��ʾ//Main��"ʵʱʱ��"�޸�״̬
{

	F_HL_TestLine03 = YES;	 //����2.Time Setting
	F_Update_TestLine03 = YES;

		//�޸ĵ�"2013-01-01"
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn03], G_RTC_ReadBuf, 11);
	G_LcdBuf[TestLine08][TestColumn14] = '\0';  //�ͽ�����'\0'	
	F_Update_TestLine08 = YES;	//��ʾ�޸ĵ�"2013-01-01"

		//�޸ĵ�"00:00:00"
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn03],&G_RTC_ReadBuf[11], 9);
	G_LcdBuf[TestLine09][TestColumn14] = '\0';  //�ͽ�����'\0'	
	F_Update_TestLine09 = YES;	//��ʾ�޸ĵ�"00:00:00"

		//�޸ĵ�"����"
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn03],&G_RTC_ReadBuf[20], 4);
	G_LcdBuf[TestLine10][TestColumn14] = '\0';  //�ͽ�����'\0'	
	F_Update_TestLine10 = YES;  //��ʾ�޸ĵ�"����"
}	

/****************************************************************************
*������-Function:	void Disp_ModifyTimeState(void)
*����- Description:	��ʾʱ���޸Ĺ���
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_ModifyTimeState(void) //��ʾʱ���޸Ĺ���
{
	//��ȡ��ǰ�޸ĵ�ʱ��ֵ
			//��ʾ�޸��е�"��"ֵ--ǧ���١�ʮ����λ
	G_LcdBuf[TestLine08][TestColumn03] = ASCII_Table[G_MatrixKeyBuf[0]];
	G_LcdBuf[TestLine08][TestColumn03+1] = ASCII_Table[G_MatrixKeyBuf[1]];
	G_LcdBuf[TestLine08][TestColumn03+2] = ASCII_Table[G_MatrixKeyBuf[2]];
	G_LcdBuf[TestLine08][TestColumn03+3] = ASCII_Table[G_MatrixKeyBuf[3]];
	
			//��ʾ�޸��е�"��"ֵ--ʮ����λ
	G_LcdBuf[TestLine08][TestColumn03+5] = ASCII_Table[G_MatrixKeyBuf[4]];
	G_LcdBuf[TestLine08][TestColumn03+6] = ASCII_Table[G_MatrixKeyBuf[5]];

			//��ʾ�޸��е�"��"ֵ--ʮ����λ
	G_LcdBuf[TestLine08][TestColumn03+8] = ASCII_Table[G_MatrixKeyBuf[6]];
	G_LcdBuf[TestLine08][TestColumn03+9] = ASCII_Table[G_MatrixKeyBuf[7]];

			//��ʾ�޸��е�"Сʱ"ֵ--ʮ����λ
	G_LcdBuf[TestLine09][TestColumn03] = ASCII_Table[G_MatrixKeyBuf[8]];
	G_LcdBuf[TestLine09][TestColumn03+1] = ASCII_Table[G_MatrixKeyBuf[9]];

			//��ʾ�޸��е�"����"ֵ--ʮ����λ
	G_LcdBuf[TestLine09][TestColumn03+3] = ASCII_Table[G_MatrixKeyBuf[10]];
	G_LcdBuf[TestLine09][TestColumn03+4] = ASCII_Table[G_MatrixKeyBuf[11]];

			//��ʾ�޸��е�"��"ֵ--ʮ����λ
	G_LcdBuf[TestLine09][TestColumn03+6] = ASCII_Table[G_MatrixKeyBuf[12]];
	G_LcdBuf[TestLine09][TestColumn03+7] = ASCII_Table[G_MatrixKeyBuf[13]];

		//��ʾ�޸��е�"����"ֵ
	switch(G_MatrixKeyBuf[14]) 
	{
		case 1:   //����һ
			G_LcdBuf[TestLine10][TestColumn03]   = 'M';
			G_LcdBuf[TestLine10][TestColumn03+1] = 'O';
			G_LcdBuf[TestLine10][TestColumn03+2] = 'N';
			break;	
			
		case 2:   //���ڶ�
			G_LcdBuf[TestLine10][TestColumn03]   = 'T';
			G_LcdBuf[TestLine10][TestColumn03+1] = 'U';
			G_LcdBuf[TestLine10][TestColumn03+2] = 'E';
			break;	

		case 3:   //������
			G_LcdBuf[TestLine10][TestColumn03]   = 'W';
			G_LcdBuf[TestLine10][TestColumn03+1] = 'E';
			G_LcdBuf[TestLine10][TestColumn03+2] = 'D';
			break;	

		case 4:   //������
			G_LcdBuf[TestLine10][TestColumn03]   = 'T';
			G_LcdBuf[TestLine10][TestColumn03+1] = 'H';
			G_LcdBuf[TestLine10][TestColumn03+2] = 'U';
			break;	

		case 5:   //������
			G_LcdBuf[TestLine10][TestColumn03]   = 'F';
			G_LcdBuf[TestLine10][TestColumn03+1] = 'R';
			G_LcdBuf[TestLine10][TestColumn03+2] = 'I';
			break;	
			
		case 6:   //������
			G_LcdBuf[TestLine10][TestColumn03]   = 'S';
			G_LcdBuf[TestLine10][TestColumn03+1] = 'A';
			G_LcdBuf[TestLine10][TestColumn03+2] = 'T';
			break;	
			
		case 7:   //������
			G_LcdBuf[TestLine10][TestColumn03]   = 'S';
			G_LcdBuf[TestLine10][TestColumn03+1] = 'U';
			G_LcdBuf[TestLine10][TestColumn03+2] = 'N';
			break;	

////////////////////////////////////////////////////////////////////////////
		default:	//����1��7����ʾ"Err" ��ʾ����
			G_LcdBuf[TestLine10][TestColumn03]   = 'E';
			G_LcdBuf[TestLine10][TestColumn03+1] = 'r';
			G_LcdBuf[TestLine10][TestColumn03+2] = 'r';
			break;
	}

	F_Update_TestLine08 = YES;	//��ʾ�޸ĵ�"2013-01-01"
	F_Update_TestLine09 = YES;	//��ʾ�޸ĵ�"00:00:00"
	F_Update_TestLine10 = YES;  //��ʾ�޸ĵ�"����"
}	


/****************************************************************************
*������-Function:	void Blink_ModifyTime(void)
*����- Description:	����"ʵʱʱ��"�޸�״̬�µ���˸
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Blink_ModifyTime(void)  //����"ʵʱʱ��"�޸�״̬�µ���˸
{
	unsigned char Array[3];
	
	switch(G_MatrixKeyCnt) 
	{
//--**��**---------------------------------------------------------------//
		case 0:   //��˸"ǧλ"--��
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row,G_KeyPlace_Column,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;		
		case 1: //��˸"��λ"--��
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row,G_KeyPlace_Column+1,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;		
		case 2: //��˸"ʮλ"--��
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row,G_KeyPlace_Column+2,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;		
		case 3: //��˸"��λ"--��
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row,G_KeyPlace_Column+3,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;		
			
//--**��**---------------------------------------------------------------//
		case 4: //��˸"ʮλ"--��
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row,G_KeyPlace_Column+5,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;		
		case 5: //��˸"��λ"--��
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row,G_KeyPlace_Column+6,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;	

//--**��**---------------------------------------------------------------//
		case 6: //��˸"ʮλ"--��
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row,G_KeyPlace_Column+8,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;		
		case 7: //��˸"��λ"--��
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row,G_KeyPlace_Column+9,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;	

//--**Сʱ**---------------------------------------------------------------//
		case 8: //��˸"ʮλ"--Сʱ
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row+1,G_KeyPlace_Column,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;		
		case 9: //��˸"��λ"--Сʱ
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row+1,G_KeyPlace_Column+1,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;	

//--**����**---------------------------------------------------------------//
		case 10: //��˸"ʮλ"--����
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row+1,G_KeyPlace_Column+3,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;		
		case 11: //��˸"��λ"--����
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row+1,G_KeyPlace_Column+4,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;	

//--**��**---------------------------------------------------------------//
		case 12: //��˸"ʮλ"--��
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row+1,G_KeyPlace_Column+6,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;		
		case 13: //��˸"��λ"--��
			Blink_KeyPlace_Lcd_TFT(G_KeyPlace_Row+1,G_KeyPlace_Column+7,&ASCII_Table[G_MatrixKeyBuf[G_MatrixKeyCnt]],1);
			break;	

//--**����**---------------------------------------------------------------//
		case 14: //��˸"����"
					//��ʾ�޸��е�"����"ֵ
				switch(G_MatrixKeyBuf[14]) 
				{
					case 1:   //����һ
						Array[0] = 'M';
						Array[1] = 'O';
						Array[2] = 'N';
						break;	

					case 2:   //���ڶ�
						Array[0] = 'T';
						Array[1] = 'U';
						Array[2] = 'E';
						break;

					case 3:   //������
						Array[0] = 'W';
						Array[1] = 'E';
						Array[2] = 'D';
						break;
			
					case 4:   //������
						Array[0] = 'T';
						Array[1] = 'H';
						Array[2] = 'U';
						break;
		
					case 5:   //������
						Array[0] = 'F';
						Array[1] = 'R';
						Array[2] = 'I';
						break;
						
					case 6:   //������
						Array[0] = 'S';
						Array[1] = 'A';
						Array[2] = 'T';
						break;	

					case 7:   //������
						Array[0] = 'S';
						Array[1] = 'U';
						Array[2] = 'N';
						break;

			////////////////////////////////////////////////////////////////////////////
					default:    //����1��7����ʾ"Err" ��ʾ����
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
*������-Function:	void Dis_ModifyTimeError(void)
*����- Description:	��ʾ"����: ʱ����������!"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Dis_ModifyTimeError(void)  //��ʾ"����: ʱ����������!"
{
		//��ʾ:  Setting error!	Please re-enter! 
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01], Msg_Error_ModifyTime, 21);

	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01], Msg_Error_ReEnter, 21);

	F_Update_TestLine11 = YES;	//��ʾˢ��
	F_Update_TestLine12 = YES;	//��ʾˢ��
}






/****************************************************************************
*������-Function:	void Disp_Set_ScreenSaver(void)
*����- Description:	��ʾ"��������"����(LCD)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_Set_ScreenSaver(void)
{

}	








////////////////////////////////////////////////////////////////////////////
//--**��ʾ:  "����״̬"�µ��൱��ʾ**-------------------------//
////////////////////////////////////////////////////////////////////////////


/****************************************************************************
*������-Function:	void Disp_01Page_MenuLine(void)
*����- Description:		��ʾ��1ҳ"�����˵�"(LCD)(1.Work_A  2.Work_B  3.Work_C  4.Work_D
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_01Page_MenuLine(void)
{
		// ��ʾ: ��"01 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine01][MenuColumn01], Msg_01Page_MenuLine_01, 20);
		// ��ʾ: ��"02 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine02][MenuColumn01], Msg_01Page_MenuLine_02, 20);
		// ��ʾ: ��"03 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine03][MenuColumn01], Msg_01Page_MenuLine_03, 20);
		// ��ʾ: ��"04 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine04][MenuColumn01], Msg_01Page_MenuLine_04, 20);
		// ��ʾ: ��"05 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine05][MenuColumn01], Msg_01Page_MenuLine_05, 20);
		// ��ʾ: ��"06 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine06][MenuColumn01], Msg_01Page_MenuLine_06, 20);
		// ��ʾ: ��"07 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine07][MenuColumn01], Msg_01Page_MenuLine_07, 20);
		// ��ʾ: ��"08 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine08][MenuColumn01], Msg_01Page_MenuLine_08, 20);
		// ��ʾ: ��"09 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine09][MenuColumn01], Msg_01Page_MenuLine_09, 20);
		// ��ʾ: ��"10 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine10][MenuColumn01], Msg_01Page_MenuLine_10, 20);
		// ��ʾ: ��"11 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine11][MenuColumn01], Msg_01Page_MenuLine_11, 20);
		// ��ʾ: ��"12 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine12][MenuColumn01], Msg_01Page_MenuLine_12, 20);

	mUpdate_All_MenuLine;  //ˢ������"�˵���"
}


/****************************************************************************
*������-Function:	void Disp_02Page_MenuLine(void)
*����- Description:	��ʾ��2ҳ"�����˵�"(LCD)(1.Work_A  2.Work_B  3.Work_C  4.Work_D
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_02Page_MenuLine(void)
{
		// ��ʾ: ��"01 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine01][MenuColumn01], Msg_02Page_MenuLine_01, 20);
		// ��ʾ: ��"02 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine02][MenuColumn01], Msg_02Page_MenuLine_02, 20);
		// ��ʾ: ��"03 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine03][MenuColumn01], Msg_02Page_MenuLine_03, 20);
		// ��ʾ: ��"04 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine04][MenuColumn01], Msg_02Page_MenuLine_04, 20);
		// ��ʾ: ��"05 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine05][MenuColumn01], Msg_02Page_MenuLine_05, 20);
		// ��ʾ: ��"06 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine06][MenuColumn01], Msg_02Page_MenuLine_06, 20);
		// ��ʾ: ��"07 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine07][MenuColumn01], Msg_02Page_MenuLine_07, 20);
		// ��ʾ: ��"08 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine08][MenuColumn01], Msg_02Page_MenuLine_08, 20);
		// ��ʾ: ��"09 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine09][MenuColumn01], Msg_02Page_MenuLine_09, 20);
		// ��ʾ: ��"10 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine10][MenuColumn01], Msg_02Page_MenuLine_10, 20);
		// ��ʾ: ��"11 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine11][MenuColumn01], Msg_02Page_MenuLine_11, 20);
		// ��ʾ: ��"12 �˵���"(����)
	Copy_Array_AtoB(&G_LcdBuf[MenuLine12][MenuColumn01], Msg_02Page_MenuLine_12, 20);

	mUpdate_All_MenuLine;  //ˢ������"�˵���"

}




/****************************************************************************
*������-Function:	void Disp_SelectFlag(void)
*����- Description:	��ʾ"ѡ�б�־"  "=>"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_SelectFlag(void)
{
	switch(G_KeyCnt)
	{
		case 1: //���ף�ѡ��"01.xxxx"�˵���
			F_HL_MenuLine02 = YES;  
			
			F_Update_MenuLine07 = YES; 
			F_Update_MenuLine02 = YES;  
			F_Update_MenuLine03 = YES;  
			break;
	
		case 2: //���ף�ѡ��"02.xxxx"�˵���
			F_HL_MenuLine03 = YES;  
			
			F_Update_MenuLine02 = YES;  
			F_Update_MenuLine03 = YES;  
			F_Update_MenuLine04 = YES;  
			break;
	
		case 3: //���ף�ѡ��"03.xxxx"�˵���
			F_HL_MenuLine04 = YES;  
			
			F_Update_MenuLine03 = YES;  
			F_Update_MenuLine04 = YES;  
			F_Update_MenuLine05 = YES;  
			break;
			
		case 4: //���ף�ѡ��"04.xxxx"�˵���
			F_HL_MenuLine05 = YES;  
			
			F_Update_MenuLine04 = YES;  
			F_Update_MenuLine05 = YES;  
			F_Update_MenuLine06 = YES;  
			break;

		case 5: //���ף�ѡ��"05.xxxx"�˵���
			F_HL_MenuLine06 = YES;  
			
			F_Update_MenuLine05 = YES;  
			F_Update_MenuLine06 = YES;  
			F_Update_MenuLine07 = YES;  
			break;

		case 6: //���ף�ѡ��"06.xxxx"�˵���
			F_HL_MenuLine07 = YES;  
			
			F_Update_MenuLine06 = YES;  
			F_Update_MenuLine07 = YES;  
			F_Update_MenuLine08 = YES;  
			break;
			
		case 7: //���ף�ѡ��"07.xxxx"�˵���
			F_HL_MenuLine08 = YES;  
			
			F_Update_MenuLine07 = YES;  
			F_Update_MenuLine08 = YES;  
			F_Update_MenuLine09 = YES;  
			break;

		case 8: //���ף�ѡ��"08.xxxx"�˵���
			F_HL_MenuLine09 = YES;  
			
			F_Update_MenuLine08 = YES;  
			F_Update_MenuLine09 = YES;  
			F_Update_MenuLine10 = YES;  
			break;

		case 9: //���ף�ѡ��"09.xxxx"�˵���
			F_HL_MenuLine10 = YES;  
			
			F_Update_MenuLine09 = YES;  
			F_Update_MenuLine10 = YES;  
			F_Update_MenuLine11 = YES;  
			break;


		case 10: //���ף�ѡ��"10.xxxx"�˵���
			F_HL_MenuLine11 = YES;  
			
			F_Update_MenuLine10 = YES;  
			F_Update_MenuLine11 = YES;  
			F_Update_MenuLine12 = YES;  
			break;	

		case 11: //���ף�ѡ��"11.xxxx"�˵���
			F_HL_MenuLine12 = YES;  
			
			F_Update_MenuLine11 = YES;  
			F_Update_MenuLine12 = YES;  
			F_Update_MenuLine02 = YES;  
			break;
			
		case 12: //���ף�ѡ��"12.xxxx"�˵���
			F_HL_MenuLine02 = YES;  
			
			F_Update_MenuLine12 = YES;  
			F_Update_MenuLine02 = YES;  
			F_Update_MenuLine03 = YES;  
			break;

		case 13: //���ף�ѡ��"13.xxxx"�˵���
			F_HL_MenuLine03 = YES;  
			
			F_Update_MenuLine02 = YES;  
			F_Update_MenuLine03 = YES;  
			F_Update_MenuLine04 = YES;  
			break;

		case 14: //���ף�ѡ��"14.xxxx"�˵���
			F_HL_MenuLine04 = YES;  
			
			F_Update_MenuLine03 = YES;  
			F_Update_MenuLine04 = YES;  
			F_Update_MenuLine05 = YES;  
			break;

		case 15: //���ף�ѡ��"15.xxxx"�˵���
			F_HL_MenuLine05 = YES;  
			
			F_Update_MenuLine04 = YES;  
			F_Update_MenuLine05 = YES;  
			F_Update_MenuLine06 = YES; 
			break;


		case 16: //���ף�ѡ��"16.xxxx"�˵���
			F_HL_MenuLine06 = YES;  
			
			F_Update_MenuLine05 = YES;  
			F_Update_MenuLine06 = YES;  
			F_Update_MenuLine07 = YES; 	
			break;

		case 17: //���ף�ѡ��"17.xxxx"�˵���
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
*������-Function:	void Disp_MAIN_Basic_Settings(void)
*����- Description:	��ʾ//Main��Basic_Settings �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_MAIN_Basic_Settings(void)
{
		// ��ʾ: ��"01 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_01Test_Line01, 21);
		// ��ʾ: ��"02 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_01Test_Line02, 21);
		// ��ʾ: ��"03 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_01Test_Line03, 21);
		// ��ʾ: ��"04 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_01Test_Line04, 21);
		// ��ʾ: ��"05 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_01Test_Line05, 21);
		// ��ʾ: ��"06 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_01Test_Line06, 21);
		// ��ʾ: ��"07 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_01Test_Line07, 21);
		// ��ʾ: ��"08 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_01Test_Line08, 21);
		// ��ʾ: ��"09 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_01Test_Line09, 21);
		// ��ʾ: ��"10 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_01Test_Line10, 21);
		// ��ʾ: ��"11 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_01Test_Line11, 21);
		// ��ʾ: ��"12 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_01Test_Line12, 21);

	mUpdate_All_TestLine;  //ˢ������" ������"
}





/****************************************************************************
*������-Function:	void Disp_MAIN_Basic_Check(void)
*����- Description:	��ʾ//Main��Basic_Check �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_MAIN_Basic_Check(void)
{
		// ��ʾ: ��"01 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_02Test_Line01, 21);
		// ��ʾ: ��"02 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_02Test_Line02, 21);
		// ��ʾ: ��"03 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_02Test_Line03, 21);
		// ��ʾ: ��"04 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_02Test_Line04, 21);
		// ��ʾ: ��"05 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_02Test_Line05, 21);
		// ��ʾ: ��"06 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_02Test_Line06, 21);
		// ��ʾ: ��"07 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_02Test_Line07, 21);
		// ��ʾ: ��"08 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_02Test_Line08, 21);
		// ��ʾ: ��"09 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_02Test_Line09, 21);
		// ��ʾ: ��"10 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_02Test_Line10, 21);
		// ��ʾ: ��"11 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_02Test_Line11, 21);
		// ��ʾ: ��"12 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_02Test_Line12, 21);

	mUpdate_All_TestLine;  //ˢ������" ������"
}




/****************************************************************************
*������-Function:	void Disp_MAIN_LCD_TFT_Test(void)
*����- Description:	��ʾ//Main��LCD_TFT_Test �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_MAIN_LCD_TFT_Test(void)
{
		// ��ʾ: ��"01 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_03Test_Line01, 21);
		// ��ʾ: ��"02 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_03Test_Line02, 21);
		// ��ʾ: ��"03 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_03Test_Line03, 21);
		// ��ʾ: ��"04 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_03Test_Line04, 21);
		// ��ʾ: ��"05 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_03Test_Line05, 21);
		// ��ʾ: ��"06 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_03Test_Line06, 21);
		// ��ʾ: ��"07 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_03Test_Line07, 21);
		// ��ʾ: ��"08 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_03Test_Line08, 21);
		// ��ʾ: ��"09 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_03Test_Line09, 21);
		// ��ʾ: ��"10 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_03Test_Line10, 21);
		// ��ʾ: ��"11 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_03Test_Line11, 21);
		// ��ʾ: ��"12 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_03Test_Line12, 21);

}


/****************************************************************************
*������-Function:	void Disp_MAIN_MatrixKey_Test(void)
*����- Description:	��ʾ//Main��MatrixKey_Test �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_MAIN_MatrixKey_Test(void)
{
		// ��ʾ: ��"01 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_04Test_Line01, 21);
		// ��ʾ: ��"02 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_04Test_Line02, 21);
		// ��ʾ: ��"03 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_04Test_Line03, 21);
		// ��ʾ: ��"04 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_04Test_Line04, 21);
		// ��ʾ: ��"05 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_04Test_Line05, 21);
		// ��ʾ: ��"06 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_04Test_Line06, 21);
		// ��ʾ: ��"07 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_04Test_Line07, 21);
		// ��ʾ: ��"08 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_04Test_Line08, 21);
		// ��ʾ: ��"09 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_04Test_Line09, 21);
		// ��ʾ: ��"10 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_04Test_Line10, 21);
		// ��ʾ: ��"11 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_04Test_Line11, 21);
		// ��ʾ: ��"12 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_04Test_Line12, 21);

	mUpdate_All_TestLine;  //ˢ������" ������"

}



/****************************************************************************
*������-Function:	void Disp_MatrixKey_Press(void)
*����- Description:	���ݰ��µ�"���󰴼�"���ڲ���������ʾ"����ֵ"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) 	��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_MatrixKey_Press(void)
{
	if(Detect_MatrixKey_1()) //"����1��"
	{	
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_1_LedSeg);
		G_LcdBuf[TestLine06][TestColumn03]= '1';
		F_Update_TestLine06 = YES;

		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	}
	
	if(Detect_MatrixKey_2()) //"����2��"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_2_LedSeg);
		G_LcdBuf[TestLine06][TestColumn06]= '2';
		F_Update_TestLine06 = YES; 

		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	}

	if(Detect_MatrixKey_3()) //"����3��"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_3_LedSeg);
		G_LcdBuf[TestLine06][TestColumn09]= '3';
		F_Update_TestLine06 = YES; 

		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	}
	if(Detect_MatrixKey_A()) //"A��"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_A_LedSeg);
		G_LcdBuf[TestLine06][TestColumn12]= 'A';
		F_Update_TestLine06 = YES; 


		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	}
	
	if(Detect_MatrixKey_AC()) //"AC��"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_A_LedSeg,DISP_C_LedSeg);
		G_LcdBuf[TestLine06][TestColumn15]= 'A';
		G_LcdBuf[TestLine06][TestColumn16]= 'C';
		F_Update_TestLine06 = YES; 
		
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	}
	
/////////////////////////////////////////////////////////////
	if(Detect_MatrixKey_4()) //"����4��"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_4_LedSeg);
		G_LcdBuf[TestLine07][TestColumn03]= '4';
		F_Update_TestLine07 = YES;

		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	}
	
	if(Detect_MatrixKey_5()) //"����5��"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_5_LedSeg);
		G_LcdBuf[TestLine07][TestColumn06]= '5';
		F_Update_TestLine07 = YES; 

		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	}

	if(Detect_MatrixKey_6()) //"����6��"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_6_LedSeg);
		G_LcdBuf[TestLine07][TestColumn09]= '6';
		F_Update_TestLine07 = YES; 

		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	}
	if(Detect_MatrixKey_B()) //"B��"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_b_LedSeg);
		G_LcdBuf[TestLine07][TestColumn12]= 'B';
		F_Update_TestLine07 = YES; 

		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	}

	if(Detect_MatrixKey_Plus()) //"+��"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_Plus_LedSeg);
		G_LcdBuf[TestLine07][TestColumn15]= '+';
		F_Update_TestLine07 = YES; 

		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	}
	
/////////////////////////////////////////////////////////////////
	if(Detect_MatrixKey_7()) //"����7��"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_7_LedSeg);	
		G_LcdBuf[TestLine08][TestColumn03]= '7';
		F_Update_TestLine08 = YES;

		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	}
	
	if(Detect_MatrixKey_8()) //"����8��"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_8_LedSeg);
		G_LcdBuf[TestLine08][TestColumn06]= '8';
		F_Update_TestLine08 = YES; 

		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	}

	if(Detect_MatrixKey_9()) //"����9��"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_9_LedSeg);
		G_LcdBuf[TestLine08][TestColumn09]= '9';
		F_Update_TestLine08 = YES; 

		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	}
	if(Detect_MatrixKey_C()) //"C��"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_C_LedSeg);
		G_LcdBuf[TestLine08][TestColumn12]= 'C';
		F_Update_TestLine08 = YES; 

		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	}

	if(Detect_MatrixKey_Minus()) //"-��"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_Minus_LedSeg);
		G_LcdBuf[TestLine08][TestColumn15]= '-';
		F_Update_TestLine08 = YES; 

		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	}
/////////////////////////////////////////////////////////////////
	if(Detect_MatrixKey_0()) //"����0��"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_0_LedSeg);
		G_LcdBuf[TestLine09][TestColumn03]= '0';
		F_Update_TestLine09 = YES;

		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	}
	
	if(Detect_MatrixKey_F()) //"����F��"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_F_LedSeg);
		G_LcdBuf[TestLine09][TestColumn06]= 'F';
		F_Update_TestLine09 = YES; 

		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	}

	if(Detect_MatrixKey_E()) //"����E��"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_E_LedSeg);
		G_LcdBuf[TestLine09][TestColumn09]= 'E';
		F_Update_TestLine09 = YES; 

		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	}
	
	if(Detect_MatrixKey_D()) //"D��"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_d_LedSeg);
		G_LcdBuf[TestLine09][TestColumn12]= 'D';
		F_Update_TestLine09 = YES; 

		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	}

	if(Detect_MatrixKey_Equal()) //"=��"
	{
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_Equal_LedSeg);
		G_LcdBuf[TestLine09][TestColumn15]= '=';
		F_Update_TestLine09 = YES; 

		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	}
/////////////////////////////////////////////////////////////////

}


/****************************************************************************
*������-Function:	void Disp_MAIN_TouchPads_Test(void)
*����- Description:	��ʾ//Main��TouchPads_Test �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_MAIN_TouchPads_Test(void)
{
		// ��ʾ: ��"01 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_05Test_Line01, 21);
		// ��ʾ: ��"02 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_05Test_Line02, 21);
		// ��ʾ: ��"03 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_05Test_Line03, 21);
		// ��ʾ: ��"04 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_05Test_Line04, 21);
		// ��ʾ: ��"05 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_05Test_Line05, 21);
		// ��ʾ: ��"06 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_05Test_Line06, 21);
		// ��ʾ: ��"07 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_05Test_Line07, 21);
		// ��ʾ: ��"08 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_05Test_Line08, 21);
		// ��ʾ: ��"09 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_05Test_Line09, 21);
		// ��ʾ: ��"10 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_05Test_Line10, 21);
		// ��ʾ: ��"11 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_05Test_Line11, 21);
		// ��ʾ: ��"12 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_05Test_Line12, 21);

	mUpdate_All_TestLine;  //ˢ������" ������"
}


/****************************************************************************
*������-Function:	void Disp_MAIN_INA21x_Current_Test(void)
*����- Description:	��ʾ//Main��INA210_Current_Test �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_MAIN_INA21x_Current_Test(void)
{
		// ��ʾ: ��"01 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_06Test_Line01, 21);
		// ��ʾ: ��"02 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_06Test_Line02, 21);
		// ��ʾ: ��"03 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_06Test_Line03, 21);
		// ��ʾ: ��"04 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_06Test_Line04, 21);
		// ��ʾ: ��"05 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_06Test_Line05, 21);
		// ��ʾ: ��"06 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_06Test_Line06, 21);
		// ��ʾ: ��"07 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_06Test_Line07, 21);
		// ��ʾ: ��"08 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_06Test_Line08, 21);
		// ��ʾ: ��"09 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_06Test_Line09, 21);
		// ��ʾ: ��"10 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_06Test_Line10, 21);
		// ��ʾ: ��"11 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_06Test_Line11, 21);
		// ��ʾ: ��"12 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_06Test_Line12, 21);

	mUpdate_All_TestLine;  //ˢ������" ������"
}



/****************************************************************************
*������-Function:	void Disp_INA21x_Current_InTest(void)
*����- Description:	��"������"��ʾ: INA21x ʵʱ"������ֵ"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_INA21x_Current_InTest(void)
{
	unsigned char b,c,d;  
	
//	a = (unsigned char)(G_INA21x_AdResult/1000);
	b = (unsigned char)((G_INA21x_AdResult % 1000)/100);
	c = (unsigned char)((G_INA21x_AdResult % 100)/10);
	d = (unsigned char)(G_INA21x_AdResult % 10);


		//ˢ��Ҫ��ʾ��"ʵ�ʵ���ֵ"����λA,��ʾ250A
	G_LcdBuf[TestLine04][TestColumn10] = ASCII_Table[b];	 //��һλ
	if(b == 0) G_LcdBuf[TestLine04][TestColumn10] = 0x20;
	
	G_LcdBuf[TestLine04][TestColumn11] = ASCII_Table[c];	 //�ڶ�λ
	G_LcdBuf[TestLine04][TestColumn12] = ASCII_Table[d];	 //����λ

	F_Update_TestLine04 = YES; //ˢ��:""������"" 
}




/****************************************************************************
*������-Function:	void Disp_MAIN_Potentiometer_Test(void)
*����- Description:	��ʾ//Main��Potentiometer_Test �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_MAIN_Potentiometer_Test(void)
{
		// ��ʾ: ��"01 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_08Test_Line01, 21);
		// ��ʾ: ��"02 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_08Test_Line02, 21);
		// ��ʾ: ��"03 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_08Test_Line03, 21);
		// ��ʾ: ��"04 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_08Test_Line04, 21);
		// ��ʾ: ��"05 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_08Test_Line05, 21);
		// ��ʾ: ��"06 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_08Test_Line06, 21);
		// ��ʾ: ��"07 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_08Test_Line07, 21);
		// ��ʾ: ��"08 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_08Test_Line08, 21);
		// ��ʾ: ��"09 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_08Test_Line09, 21);
		// ��ʾ: ��"10 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_08Test_Line10, 21);
		// ��ʾ: ��"11 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_08Test_Line11, 21);
		// ��ʾ: ��"12 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_08Test_Line12, 21);

	mUpdate_All_TestLine;  //ˢ������" ������"
}



/****************************************************************************
*������-Function:	void Disp_Potentiometer_InTest(void)
*����- Description:	��"������"��ʾ: ��λ��Potentiometer ʵʱ"��ѹֵ"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_Potentiometer_InTest(void)
{
	unsigned char a,b,c;
	
	a = (unsigned char)(G_LastAdResult/1000);
	b = (unsigned char)((G_LastAdResult % 1000)/100);
	c = (G_LastAdResult % 100)/10;
	if(G_LastAdResult < 30) c = 0; //�ڵ�λ��������Сֵʱ����ʾ��ѹ����0.01,0.02,.000֮����ʾ�����������������ڵ�λ��������Сֵʱ����ʾ0.00


		//ˢ��Ҫ��ʾ��"ʵ�ʵ�ѹֵ"����λA,��ʾ3.29 V
	G_LcdBuf[TestLine04][TestColumn10] = ASCII_Table[a];   //��λ
	G_LcdBuf[TestLine04][TestColumn11] = '.';   //С����
	G_LcdBuf[TestLine04][TestColumn12] = ASCII_Table[b];	 //С����һλ
	G_LcdBuf[TestLine04][TestColumn13] = ASCII_Table[c];   //С���ڶ�λ
	G_LcdBuf[TestLine04][TestColumn14] = ' ';   
	G_LcdBuf[TestLine04][TestColumn15] = 'V';   

	F_Update_TestLine04 = YES; //ˢ��:""������"" 
}


/****************************************************************************
*������-Function:	void Disp_MAIN_NTC_HR202_Test(void)
*����- Description:	��ʾ//Main��NTC_HR202_Test(��ʪ��) �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_MAIN_NTC_HR202_Test(void)
{
		// ��ʾ: ��"01 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_11Test_Line01, 21);
		// ��ʾ: ��"02 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_11Test_Line02, 21);
		// ��ʾ: ��"03 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_11Test_Line03, 21);
		// ��ʾ: ��"04 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_11Test_Line04, 21);
		// ��ʾ: ��"05 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_11Test_Line05, 21);
		// ��ʾ: ��"06 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_11Test_Line06, 21);
		// ��ʾ: ��"07 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_11Test_Line07, 21);
		// ��ʾ: ��"08 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_11Test_Line08, 21);
		// ��ʾ: ��"09 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_11Test_Line09, 21);
		// ��ʾ: ��"10 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_11Test_Line10, 21);
		// ��ʾ: ��"11 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_11Test_Line11, 21);
		// ��ʾ: ��"12 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_11Test_Line12, 21);

	mUpdate_All_TestLine;  //ˢ������" ������"
}



/****************************************************************************
*������-Function:	void Disp_MAIN_Step_Motor_Test(void)
*����- Description:	��ʾ//Main��Step_Motor_Test �˵�ѡ��(����ʱ) 
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_MAIN_Step_Motor_Test(void)
{
		// ��ʾ: ��"01 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_10Test_Line01, 21);
		// ��ʾ: ��"02 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_10Test_Line02, 21);
		// ��ʾ: ��"03 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_10Test_Line03, 21);
		// ��ʾ: ��"04 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_10Test_Line04, 21);
		// ��ʾ: ��"05 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_10Test_Line05, 21);
		// ��ʾ: ��"06 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_10Test_Line06, 21);
		// ��ʾ: ��"07 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_10Test_Line07, 21);
		// ��ʾ: ��"08 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_10Test_Line08, 21);
		// ��ʾ: ��"09 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_10Test_Line09, 21);
		// ��ʾ: ��"10 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_10Test_Line10, 21);
		// ��ʾ: ��"11 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_10Test_Line11, 21);
		// ��ʾ: ��"12 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_10Test_Line12, 21);

}



/****************************************************************************
*������-Function:	void Disp_MAIN_DC_Motor_Test(void)
*����- Description:	��ʾ//Main��DC_Motor_Test �˵�ѡ��(����ʱ)  
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_MAIN_DC_Motor_Test(void)
{
		// ��ʾ: ��"01 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_09Test_Line01, 21);
		// ��ʾ: ��"02 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_09Test_Line02, 21);
		// ��ʾ: ��"03 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_09Test_Line03, 21);
		// ��ʾ: ��"04 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_09Test_Line04, 21);
		// ��ʾ: ��"05 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_09Test_Line05, 21);
		// ��ʾ: ��"06 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_09Test_Line06, 21);
		// ��ʾ: ��"07 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_09Test_Line07, 21);
		// ��ʾ: ��"08 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_09Test_Line08, 21);
		// ��ʾ: ��"09 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_09Test_Line09, 21);
		// ��ʾ: ��"10 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_09Test_Line10, 21);
		// ��ʾ: ��"11 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_09Test_Line11, 21);
		// ��ʾ: ��"12 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_09Test_Line12, 21);

	
}


/****************************************************************************
*������-Function:	void Disp_Potentiometer_Motor(void)
*����- Description:	��"���Ե��"��ʾ�ٶȸ�����ѹֵ: ��λ��Potentiometer ʵʱ"��ѹֵ"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_Potentiometer_Motor(void)
{
	unsigned char a,b;
	
	a = (unsigned char)(G_LastAdResult/1000);
	b = (unsigned char)((G_LastAdResult % 1000)/100);
//c = (G_LastAdResult % 100)/10;
//	if(G_LastAdResult < 30) c = 0; //�ڵ�λ��������Сֵʱ����ʾ��ѹ����0.01,0.02,.000֮����ʾ�����������������ڵ�λ��������Сֵʱ����ʾ0.00


		//ˢ��Ҫ��ʾ��"ʵ�ʵ�ѹֵ"����λA,��ʾ3.29 V
	G_LcdBuf[TestLine07][TestColumn10] = ASCII_Table[a];   //��λ
	G_LcdBuf[TestLine07][TestColumn11] = '.';   //С����
	G_LcdBuf[TestLine07][TestColumn12] = ASCII_Table[b];	 //С����һλ
	G_LcdBuf[TestLine07][TestColumn13] = ' ';   
	G_LcdBuf[TestLine07][TestColumn14] = 'V';   

	F_Update_TestLine07 = YES; //ˢ��:""������"" 
}


/****************************************************************************
*������-Function:	void Disp_Speed_Step_Motor(void)
*����- Description:		��"����Step_Motor"��ʾ����ٶ�
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_Speed_Step_Motor(void) //��"����Step_Motor"��ʾ����ٶ�
{
	unsigned char s1 = 0;
	unsigned char s2 = 0;
	unsigned char s3 = 0;
	unsigned char s4 = 0;


//ת����ʾ���
	s3 = (unsigned char)(G_Step_Speed /1000);
	s2 = (unsigned char)((G_Step_Speed % 1000)/100);
	s1 = (unsigned char)(G_Step_Speed % 100)/10;



	if(G_Step_WorkState  == STATE_Reverse_Step_Motor) //��ת��ʾ����
	{
		s4 = 18; //��ʾ"����"(����ʾ0)		

		if(s3 == 0) 
		{
			s4 = 19; //��ʾ"����"(����ʾ0)	
			s3 = 18; //��ʾ"����"(����ʾ0)	
		}
			

	}
	else if(G_Step_WorkState  == STATE_Positive_Step_Motor) //��ת��ʾ����
	{
		s4 = 19;  // ��ʾ"����"(����ʾ0)
		if(s3 == 0) s3 = 19; //��ʾ"����"(����ʾ0)
	}

		//ˢ��Ҫ��ʾ��"ת��"����λr/min,
	G_LcdBuf[TestLine08][TestColumn10] = ASCII_Table[s4]; 
	G_LcdBuf[TestLine08][TestColumn11] = ASCII_Table[s3]; //��λ	 
	G_LcdBuf[TestLine08][TestColumn12] = ASCII_Table[s2]; //ʮλ  
//G_LcdBuf[TestLine08][TestColumn13] = '.'; //  
	G_LcdBuf[TestLine08][TestColumn14] = ASCII_Table[s1]; //��λ  

	F_Update_TestLine08 = YES; //ˢ��:""������"" 
}







/****************************************************************************
*������-Function:	void Disp_Speed_DC_Motor(void)
*����- Description:	��"����DC_Motor"��ʾ����ٶ�
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_Speed_DC_Motor(void)
{
	unsigned int speed = 0;
	
	unsigned char a1 = 0;
	unsigned char a2 = 0;
	unsigned char a3 = 0;
	unsigned char a4 = 0;
	unsigned char a5 = 0;


	speed = (G_DC_Speed * 60) / 3;  // ��ת������ת��"ʵ��ת��ֵ" r/min ��λ

//ת����ʾ���
	if(G_DC_WorkState  == STATE_Positive_DC_Motor)  //��ת��ʾ����
	{
		a5 = 19; //��ʾ"����"(����ʾ0)
			
		a4 = (unsigned char)(speed/1000);
		a3 = (unsigned char)((speed % 1000)/100);
		a2 = (unsigned char)(speed % 100)/10;
		a1 = (unsigned char)(speed % 10);
		if((a4 == 0)&&(a3 == 0)&&(a2 == 0)) a2 = 19;	
		if((a4 == 0)&&(a3 == 0)) a3 = 19;
		if(a4 == 0) a4 = 19; //��ʾ"����"(����ʾ0)
	}
	
	else if(G_DC_WorkState  == STATE_Reverse_DC_Motor) //��ת��ʾ����
	{
		a5 = 19; //��ʾ"����"(����ʾ0)
		a4 = (unsigned char)(speed/1000);
		a3 = (unsigned char)((speed % 1000)/100);
		a2 = (unsigned char)(speed % 100)/10;
		a1 = (unsigned char)(speed % 10);
		if((a4 == 0)&&(a3 == 0)&&(a2 == 0))
		{
			a5 = 19; //��ʾ"����"(����ʾ0)
		 	a4 = 19;//��ʾ"����"(����ʾ0)
			a3 = 19;//��ʾ"����"(����ʾ0)
			a2 = 18; //��ʾ"����"(����ʾ0)
		}
		if((a4 == 0)&&(a3 == 0))
		{
			a5 = 19; //��ʾ"����"(����ʾ0)
		 	a4 = 19;//��ʾ"����"(����ʾ0)
			a3 = 18; //��ʾ"����"(����ʾ0)
		}
		if(a4 == 0) 
		{
			a5 = 19; //��ʾ"����"(����ʾ0)
			a4 = 18; //��ʾ"����"(����ʾ0)		
		}
		else if(a4 != 0) a5 = 18; //��ʾ"����"(����ʾ0)	
		
	}

		//ˢ��Ҫ��ʾ��"ת��"����λr/min,
	G_LcdBuf[TestLine08][TestColumn10] = ASCII_Table[a5]; //
	G_LcdBuf[TestLine08][TestColumn11] = ASCII_Table[a4]; //ǧλ  
	G_LcdBuf[TestLine08][TestColumn12] = ASCII_Table[a3]; //��λ	 
	G_LcdBuf[TestLine08][TestColumn13] = ASCII_Table[a2]; //ʮλ  
	G_LcdBuf[TestLine08][TestColumn14] = ASCII_Table[a1]; //��λ  

	F_Update_TestLine08 = YES; //ˢ��:""������"" 
}




/****************************************************************************
*������-Function:	void Disp_MAIN_TMP006_Temperature(void)
*����- Description:	��ʾ//Main��TMP006_Temperature �˵�ѡ��(����ʱ) 
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_MAIN_TMP006_Temperature(void)
{
		// ��ʾ: ��"01 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_07Test_Line01, 21);
		// ��ʾ: ��"02 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_07Test_Line02, 21);
		// ��ʾ: ��"03 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_07Test_Line03, 21);
		// ��ʾ: ��"04 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_07Test_Line04, 21);
		// ��ʾ: ��"05 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_07Test_Line05, 21);
		// ��ʾ: ��"06 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_07Test_Line06, 21);
		// ��ʾ: ��"07 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_07Test_Line07, 21);
		// ��ʾ: ��"08 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_07Test_Line08, 21);
		// ��ʾ: ��"09 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_07Test_Line09, 21);
		// ��ʾ: ��"10 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_07Test_Line10, 21);
		// ��ʾ: ��"11 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_07Test_Line11, 21);
		// ��ʾ: ��"12 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_07Test_Line12, 21);

	mUpdate_All_TestLine;  //ˢ������" ������"
}


/****************************************************************************
*������-Function:	void Disp_TMP006_TemperatureInTest(void)
*����- Description:		��LCD_TFT�ϣ���ʾ"�¶�"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_TMP006_TemperatureInTest(void)//��LCD_TFT�ϣ���ʾ"�¶�"
{	
	int b = 0;
	unsigned char a4,a3,a2,a1;

	b = (int)(TMP006_Temperature * 10);  //��"ʵ���¶�ֵ"�ŵ�10����������ʾ
	if(b < 0)  //���¶�ֵ
	{
		b  = (-1) * b;
		a4 =  b / 1000; 
		a3 =  b / 100;
		a2 = (b / 10) % 10;
		a1 =  b % 10;	

		if((a4 == 0)&&(a3 == 0))
		{
			a4 = 19;//��ʾ"����"(����ʾ0)
			a3 = 18; //��ʾ"����"(����ʾ0)
		}
		if(a4 == 0) a4 = 18; //��ʾ"����"(����ʾ0)	
	}
	else //���¶�ֵ
	{
		a4 =  b / 1000; 
		a3 = (b % 1000) / 100;
		a2 = (b % 100) / 10;
		a1 =  b % 10;	
		
		if((a4 == 0)&&(a3 == 0)) a3 = 19;//��ʾ"����"(����ʾ0)
		if(a4 == 0) a4 = 19;//��ʾ"����"(����ʾ0)
	}

		//ˢ��Ҫ��ʾ��"ʵ���¶�"
	G_LcdBuf[TestLine04][TestColumn13] = ASCII_Table[a4];//��λ	
	G_LcdBuf[TestLine04][TestColumn14] = ASCII_Table[a3]; //ʮλ
	G_LcdBuf[TestLine04][TestColumn15] = ASCII_Table[a2]; //��λ
	G_LcdBuf[TestLine04][TestColumn16] = '.'; //С����
	G_LcdBuf[TestLine04][TestColumn17] = ASCII_Table[a1]; //С����һλ
	
	F_Update_TestLine04 = YES; //ˢ��:"ʵʱ�¶�"  (Ϊ1ʱ)
}




/****************************************************************************
*������-Function:	void Disp_TMP006_Temperature(void)
*����- Description:		��LCD_TFT�ϣ���ʾ"�¶�"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_TMP006_Temperature(void)//��LCD_TFT�ϣ���ʾ"�¶�"
{	
	int d = 0;
    unsigned char aa4,aa3,aa2,aa1;

	d = (int)(TMP006_Temperature * 10);  //��"ʵ���¶�ֵ"�ŵ�10����������ʾ
	if(d < 0)  //���¶�ֵ
	{
		d  = (-1) * d;
		aa4 =  d / 1000; 
		aa3 =  d / 100;
		aa2 = (d / 10) % 10;
		aa1 =  d % 10;	

		if((aa4 == 0)&&(aa3 == 0))
		{
			aa4 = 19;//��ʾ"����"(����ʾ0)
			aa3 = 18; //��ʾ"����"(����ʾ0)
		}
		if(aa4 == 0) aa4 = 18; //��ʾ"����"(����ʾ0)	
	}
	else //���¶�ֵ
	{
		aa4 =  d / 1000; 
		aa3 = (d % 1000) / 100;
		aa2 = (d % 100) / 10;
		aa1 =  d % 10;	
		
		if((aa4 == 0)&&(aa3 == 0)) aa3 = 19;//��ʾ"����"(����ʾ0)
		if(aa4 == 0) aa4 = 19;//��ʾ"����"(����ʾ0)
	}

		//ˢ��Ҫ��ʾ��"ʵ���¶�"
	G_LcdBuf[M_15LineBuf][M_24ColumnBuf] = ASCII_Table[aa4];//��λ	
	G_LcdBuf[M_15LineBuf][M_25ColumnBuf] = ASCII_Table[aa3]; //ʮλ
	G_LcdBuf[M_15LineBuf][M_26ColumnBuf] = ASCII_Table[aa2]; //��λ
	G_LcdBuf[M_15LineBuf][M_27ColumnBuf] = '.'; //С����
	G_LcdBuf[M_15LineBuf][M_28ColumnBuf] = ASCII_Table[aa1]; //С����һλ
//G_LcdBuf[M_15LineBuf][M_29ColumnBuf] = 'c';	 
//G_LcdBuf[M_15LineBuf][M_30ColumnBuf] = '\0';	

	F_Update_Temperature = YES; //ˢ��:"ʵʱ�¶�"  (Ϊ1ʱ)

}


/****************************************************************************
*������-Function:	void Disp_MAIN_TMP100_Temperature(void)
*����- Description:	��ʾ//Main��TMP100_Temperature �˵�ѡ��(����ʱ) 
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_MAIN_TMP100_Temperature(void)
{
}

/****************************************************************************
*������-Function:	void Disp_TMP100_Temperature(void)
*����- Description:		��LCD_TFT�ϣ���ʾ"�¶�"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_TMP100_Temperature(void)//��LCD_TFT�ϣ���ʾ"�¶�"
{	
}



/****************************************************************************
*������-Function:	void Disp_MAIN_IrDA_UART(void)
*����- Description:		��ʾ//Main��IrDA_UART �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_MAIN_IrDA_UART(void) //��ʾ//Main��IrDA_UART �˵�ѡ��(����ʱ)
{
		// ��ʾ: ��"01 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_12Test_Line01, 21);
		// ��ʾ: ��"02 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_12Test_Line02, 21);
		// ��ʾ: ��"03 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_12Test_Line03, 21);
		// ��ʾ: ��"04 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_12Test_Line04, 21);
		// ��ʾ: ��"05 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_12Test_Line05, 21);
		// ��ʾ: ��"06 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_12Test_Line06, 21);
		// ��ʾ: ��"07 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_12Test_Line07, 21);
		// ��ʾ: ��"08 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_12Test_Line08, 21);
		// ��ʾ: ��"09 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_12Test_Line09, 21);
		// ��ʾ: ��"10 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_12Test_Line10, 21);
		// ��ʾ: ��"11 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_12Test_Line11, 21);
		// ��ʾ: ��"12 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_12Test_Line12, 21);

	mUpdate_All_TestLine;  //ˢ������" ������"

}

/****************************************************************************
*������-Function:	void Disp_IrDA_Test(void)
*����- Description:		��ʾIrDA�Ƿ��յ�����
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_IrDA_Test(void) //��ʾIrDA�Ƿ��յ�����
{
	if(G_RxData_IrDA == '1')  //���������յ�������Ϊ"1"
	{
		Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_12Test_TXT1, 21);
	}
	else
	{
		Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_12Test_TXT2, 21);
	}
	
	F_Update_TestLine07 = YES;//ˢ��:""������"" 
}


  
/****************************************************************************
*������-Function:	void Disp_MAIN_RS232_UART(void)
*����- Description:		//��ʾ//Main��RS232_UART �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_MAIN_RS232_UART(void) //��ʾ//Main��RS232_UART �˵�ѡ��(����ʱ)
{
		// ��ʾ: ��"01 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_13Test_Line01, 21);
		// ��ʾ: ��"02 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_13Test_Line02, 21);
		// ��ʾ: ��"03 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_13Test_Line03, 21);
		// ��ʾ: ��"04 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_13Test_Line04, 21);
		// ��ʾ: ��"05 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_13Test_Line05, 21);
		// ��ʾ: ��"06 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_13Test_Line06, 21);
		// ��ʾ: ��"07 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_13Test_Line07, 21);
		// ��ʾ: ��"08 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_13Test_Line08, 21);
		// ��ʾ: ��"09 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_13Test_Line09, 21);
		// ��ʾ: ��"10 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_13Test_Line10, 21);
		// ��ʾ: ��"11 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_13Test_Line11, 21);
		// ��ʾ: ��"12 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_13Test_Line12, 21);

	mUpdate_All_TestLine;  //ˢ������" ������"

}


/****************************************************************************
*������-Function:	void Disp_RS232_Char_1(void)
*����- Description:		��ʾRS232�յ�����"1" (�ַ�)	
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_RS232_Char_1(void) //��ʾRS232�յ�����"1" (�ַ�)	
{
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01], Msg_13Test_TXT1, 21);
	F_Update_TestLine10 = YES;//ˢ��:""������"" 
}


/****************************************************************************
*������-Function:	void Disp_RS232_Char_2(void)
*����- Description:		��ʾRS232�յ�����"2" (�ַ�)	
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_RS232_Char_2(void) //��ʾRS232�յ�����"2" (�ַ�)	
{
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01], Msg_13Test_TXT2, 21);

	F_Update_TestLine10 = YES;//ˢ��:""������"" 
}


/****************************************************************************
*������-Function:	void Disp_RS232_None(void)
*����- Description:		//����ʾRS232�յ�����
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_RS232_None(void) //����ʾRS232�յ�����
{
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01], Msg_13Test_TXT3, 21);

	F_Update_TestLine10 = YES;//ˢ��:""������"" 
}



/****************************************************************************
*������-Function:	void Disp_MAIN_RS485_UART(void)
*����- Description:		//��ʾ//Main��RS485_UART �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_MAIN_RS485_UART(void) //��ʾ//Main��RS485_UART �˵�ѡ��(����ʱ)
{
		// ��ʾ: ��"01 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_14Test_Line01, 21);
		// ��ʾ: ��"02 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_14Test_Line02, 21);
		// ��ʾ: ��"03 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_14Test_Line03, 21);
		// ��ʾ: ��"04 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_14Test_Line04, 21);
		// ��ʾ: ��"05 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_14Test_Line05, 21);
		// ��ʾ: ��"06 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_14Test_Line06, 21);
		// ��ʾ: ��"07 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_14Test_Line07, 21);
		// ��ʾ: ��"08 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_14Test_Line08, 21);
		// ��ʾ: ��"09 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_14Test_Line09, 21);
		// ��ʾ: ��"10 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_14Test_Line10, 21);
		// ��ʾ: ��"11 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_14Test_Line11, 21);
		// ��ʾ: ��"12 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_14Test_Line12, 21);

	mUpdate_All_TestLine;  //ˢ������" ������"
}


/****************************************************************************
*������-Function:	void Disp_RS485_Char_1(void)
*����- Description:		��ʾRS485�յ�����"1" (�ַ�)	
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_RS485_Char_1(void) //��ʾRS485�յ�����"1" (�ַ�)	
{
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01], Msg_14Test_TXT1, 21);
	F_Update_TestLine07 = YES;//ˢ��:""������"" 
}


/****************************************************************************
*������-Function:	void Disp_RS485_Char_2(void)
*����- Description:		��ʾRS485�յ�����"2" (�ַ�)	
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_RS485_Char_2(void) //��ʾRS485�յ�����"2" (�ַ�)	
{
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01], Msg_14Test_TXT2, 21);
	F_Update_TestLine07 = YES;//ˢ��:""������"" 
}



/****************************************************************************
*������-Function:	void Disp_MAIN_CC1101_Test(void)
*����- Description:		//��ʾ//Main��CC1101_Test �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_MAIN_CC1101_Test(void) //��ʾ//Main��CC1101_Test �˵�ѡ��(����ʱ)
{
		// ��ʾ: ��"01 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_15Test_Line01, 21);
		// ��ʾ: ��"02 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_15Test_Line02, 21);
		// ��ʾ: ��"03 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_15Test_Line03, 21);
		// ��ʾ: ��"04 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_15Test_Line04, 21);
		// ��ʾ: ��"05 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_15Test_Line05, 21);
		// ��ʾ: ��"06 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_15Test_Line06, 21);
		// ��ʾ: ��"07 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_15Test_Line07, 21);
		// ��ʾ: ��"08 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_15Test_Line08, 21);
		// ��ʾ: ��"09 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_15Test_Line09, 21);
		// ��ʾ: ��"10 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_15Test_Line10, 21);
		// ��ʾ: ��"11 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_15Test_Line11, 21);
		// ��ʾ: ��"12 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_15Test_Line12, 21);

	mUpdate_All_TestLine;  //ˢ������" ������"
}


/****************************************************************************
*������-Function:	void Disp_CC1101_Char_1(void)
*����- Description:		��ʾCC1101�յ�����"1"  (�ַ�)		
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_CC1101_Char_1(void) //��ʾCC1101�յ�����"1"  (�ַ�)		
{
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01], Msg_15Test_TXT1, 21);
	F_Update_TestLine07 = YES;//ˢ��:""������"" 
}


/****************************************************************************
*������-Function:	void Disp_CC1101_Char_2(void)
*����- Description:		��ʾCC1101�յ�����"2"  (�ַ�)		
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_CC1101_Char_2(void) //��ʾCC1101�յ�����"2"  (�ַ�)		
{
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01], Msg_15Test_TXT2, 21);
	F_Update_TestLine07 = YES;//ˢ��:""������"" 
}






/****************************************************************************
*������-Function:	void Disp_MAIN_SD_Card_Test(void)
*����- Description:		 //��ʾ//Main��SD_Card_Test �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_MAIN_SD_Card_Test(void)  //��ʾ//Main��SD_Card_Test �˵�ѡ��(����ʱ)
{
		// ��ʾ: ��"01 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_16Test_Line01, 21);
		// ��ʾ: ��"02 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_16Test_Line02, 21);
		// ��ʾ: ��"03 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_16Test_Line03, 21);
		// ��ʾ: ��"04 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_16Test_Line04, 21);
		// ��ʾ: ��"05 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_16Test_Line05, 21);
		// ��ʾ: ��"06 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_16Test_Line06, 21);
		// ��ʾ: ��"07 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_16Test_Line07, 21);
		// ��ʾ: ��"08 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_16Test_Line08, 21);
		// ��ʾ: ��"09 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_16Test_Line09, 21);
		// ��ʾ: ��"10 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_16Test_Line10, 21);
		// ��ʾ: ��"11 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_16Test_Line11, 21);
		// ��ʾ: ��"12 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_16Test_Line12, 21);

	mUpdate_All_TestLine;  //ˢ������" ������"

}


/****************************************************************************
*������-Function:	void Disp_SD_Card_Char(void)
*����- Description:		��ʾSD_Card���������� (�ַ�)		
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_SD_Card_Char(void) //��ʾSD_Card���������� (�ַ�)		
{
	G_LcdBuf[TestLine03][TestColumn13] = ASCII_Table[G_Data_SD_Read]; 
	G_LcdBuf[TestLine04][TestColumn13] = ASCII_Table[G_Data_SD_Write]; 

	F_Update_TestLine03 = YES;//ˢ��:""������"" 
	F_Update_TestLine04 = YES;//ˢ��:""������"" 
}



/****************************************************************************
*������-Function:	void Disp_MAIN_MassStorage_Test(void)
*����- Description:		//��ʾ//Main��MassStorage_Test �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_MAIN_MassStorage_Test(void) //��ʾ//Main��MassStorage_Test �˵�ѡ��(����ʱ)
{
		// ��ʾ: ��"01 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine01][TestColumn01],Msg_17Test_Line01, 21);
		// ��ʾ: ��"02 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine02][TestColumn01],Msg_17Test_Line02, 21);
		// ��ʾ: ��"03 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine03][TestColumn01],Msg_17Test_Line03, 21);
		// ��ʾ: ��"04 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine04][TestColumn01],Msg_17Test_Line04, 21);
		// ��ʾ: ��"05 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine05][TestColumn01],Msg_17Test_Line05, 21);
		// ��ʾ: ��"06 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine06][TestColumn01],Msg_17Test_Line06, 21);
		// ��ʾ: ��"07 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine07][TestColumn01],Msg_17Test_Line07, 21);
		// ��ʾ: ��"08 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine08][TestColumn01],Msg_17Test_Line08, 21);
		// ��ʾ: ��"09 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine09][TestColumn01],Msg_17Test_Line09, 21);
		// ��ʾ: ��"10 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine10][TestColumn01],Msg_17Test_Line10, 21);
		// ��ʾ: ��"11 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine11][TestColumn01],Msg_17Test_Line11, 21);
		// ��ʾ: ��"12 ������"(����)
	Copy_Array_AtoB(&G_LcdBuf[TestLine12][TestColumn01],Msg_17Test_Line12, 21);

	mUpdate_All_TestLine;  //ˢ������" ������"


}






