/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 System_HeadFile.h
* �����ļ�-Dependencies:  	 None	
* �ļ�����-File Description:	 ( ͷ�ļ�-Header File )
	�� ϵͳȫ��ͷ�ļ���(��������ʹ�õ���ͷ�ļ�)-ͷ�ļ�
	01) ������Ҫ����ģ��ĵ���    
	02)     03)    04)    05)    06)	
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




#ifndef __System_HeadFile_H
#define	__System_HeadFile_H

////////////////////////////////////////////////////////////////////////////
//==**�����ȡ��׼��**=================================//
////////////////////////////////////////////////////////////////////////////

//#include <math.h>
//#include <string.h>
//#include <stdio.h>
//#include <macros.h>





////////////////////////////////////////////////////////////////////////////
//==**ϵͳ����--ͷ�ļ�**===============================//
//���õ�ģ����"//"���ε�������Ҫɾ��///////////////////////

#include "Generic.h"	//���ó����̹淶�������� -ͷ�ļ�-Generic Type Definitions


#include "System.h"	 //"ϵͳ" ���ù��ܺ�����-ͷ�ļ�
#include "Hardware_Profile.h"  //������"Ӳ�������ļ�" -ͷ�ļ�-Hardware specific definitions for Processor




#include "MyProject.h"	//������Ŀ: �ܹ��ܳ���-ͷ�ļ�

	//������Ŀ: LCD_TFTҺ����ʾ����(�������е�Һ������) -ͷ�ļ�
#include "MyProject_Set_LCD_TFT.h"

//#include ".h"

//#include ".h"





////////////////////////////////////////////////////////////////////////////
//==**MCU �ڲ���Դ--ͷ�ļ�**============================//
//���õ�ģ����"//"���ε�������Ҫɾ��///////////////////////

#include "HAL_PMM.h"  //F5xx_F6xx_Core_Lib//ϵͳ��Դ����ģ��-ͷ�ļ� 
#include "HAL_UCS.h"  //F5xx_F6xx_Core_Lib//ϵͳʱ������-ͷ�ļ� 



#include "msp430f6638.h"   // "������"ͷ�ļ�: �ڲ��Ĵ���ض����(�������ڲ���Դ) 

#include "Timer.h"     //"��ʱ��" -��������-ͷ�ļ�(�������ڲ���Դ) 

#include "RTC.h"   //"RTC �ڲ�ʵʱʱ��" -��������-ͷ�ļ�(�������ڲ���Դ) 

#include "SPI.h"     //"SPI ͬ����������ӿ�" -�������� -ͷ�ļ�(�������ڲ���Դ)

#include "I2C.h"   //"I2C" -��������-ͷ�ļ�(�������ڲ���Դ) 

#include "ADC.h"   //"ADC"ģ��ת��ģ�� -��������-ͷ�ļ�(�������ڲ���Դ) 

#include "UART.h"   //"UART ͨ���첽����/����װ��" -��������(�ڲ���Դ)-ͷ�ļ�


	//Touch Pads
#include "CTS_HAL.h"   
#include "CTS_Layer.h"
#include "structure.h"


	//SD Card
#include "SDaccess.h" //"SD_Card SD��"-��������(�ⲿ��Դ)-ͷ�ļ�

    //USB
#include "MassStorage.h"

//#include ".h"
//#include ".h"


////////////////////////////////////////////////////////////////////////////
//==**�ⲿ��Դ--ͷ�ļ�**===============================//
//���õ�ģ����"//"���ε�������Ҫɾ��///////////////////////

#include "TM1638.h"   // "TM1638 �����������" -��������-ͷ�ļ�(�ⲿ��Դ) 

#include "Key.h"       //"IO ����" -��������-ͷ�ļ�(�ⲿ��Դ)

#include "Buzzer.h"   //"������"-��������(�ⲿ��Դ)-ͷ�ļ�

#include "MatrixKey.h"   //"���󰴼�" -��������(�ⲿ��Դ)-ͷ�ļ�

#include "Speaker.h"   //"Speaker ������" -��������(�ⲿ��Դ)-ͷ�ļ�

//#include "LCD_TFT.h"    // "����LCD_TFT"-��������-ͷ�ļ�(�ⲿ��Դ) 

#include "LCD_TFT_ILI9325.h"  // "����LCD_TFT_ILI9325" -��������(�ⲿ��Դ) -ͷ�ļ�



#include "LCD_Segment.h" //"��ʽLCD_Segment" -��������(�ⲿ��Դ)-ͷ�ļ�

#include "LED_Segment.h" //"��̬�����LED_Segment" -��������(�ⲿ��Դ)-ͷ�ļ�

#include "Touch_Pad.h"   //"Touch_Pad ���ݰ���" -��������(�ⲿ��Դ)-ͷ�ļ�

#include "INA21x.h"  // "INA21x �������������" -��������(�ⲿ��Դ)-ͷ�ļ�   

#include "BQ27410_FuelGauge.h"   //"BQ27410_FuelGauge ﮵�ص�������"-��������(�ⲿ��Դ)-ͷ�ļ�


#include "NTC_Temperature.h"  //"NTC �����¶ȴ�����" -��������(�ⲿ��Դ)-ͷ�ļ�

#include "CD405x_Multiplexer.h"   //"CD405x_Multiplexer��·ѡ��ģ�⿪��"  -��������(�ⲿ��Դ)-ͷ�ļ�

#include "HR202_Humidity.h"   //"HR202_Humidity ������ʪ�ȴ�����" -��������(�ⲿ��Դ)-ͷ�ļ�

#include "Step_Motor.h"   //"Step_Motor �������" -��������(�ⲿ��Դ)-ͷ�ļ�

#include "DC_Motor.h"     //"DC_Motor ֱ�����" -��������(�ⲿ��Դ)-ͷ�ļ�

#include "TMP006_Temperature.h"   //"TMP006_Temperature �����¶ȴ�����"-��������(�ⲿ��Դ)-ͷ�ļ�

#include "TMP100_Temperature.h"   //"TMP100_Temperature �¶ȴ�����" -��������(�ⲿ��Դ)-ͷ�ļ�


#include "CC1101.h"   //"CC1101 �͹�����Ƶ�շ���"-��������(�ⲿ��Դ)-ͷ�ļ�



//#include ".h"
//#include ".h"
//#include ".h"



#endif /*__System_HeadFile_H */






