/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 MyProject_Deal_State.c
* �����ļ�-Dependencies:  	 System_HeadFile.h; 	
* �ļ�����-File Description:	 ( Դ����-Source File) 
	�� ������Ŀ: "����"��ϵͳ"״̬"�µ����� (״̬��)
	01)    02)     03)    04)    05)    06)	
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



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////

/****************************************************************************
*������-Function:	void Deal_Main_ModifyTime(void)
*����- Description:	//����//Main��"ʵʱʱ��"�޸�״̬
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_Main_ModifyTime(void) //����//Main��"ʵʱʱ��"�޸�״̬
{
////////////////////////////////////////////////////////////////////////////
//==**��˸��ʾ����ֵ�Ͱ���λ��**=====================//
	Blink_ModifyTime(); //����"ʵʱʱ��"�޸�״̬�µ���˸

////////////////////////////////////////////////////////////////////////////
//==**���� ����**=======================================//

////////////////////////////////////////////////////////////////////////////
//--**IO���� ����**---------------------------------------------------//

	Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"

////////////////////////////////////////////////////////////////////////////
//--**���󰴼� ����**-----------------------------------------------//
if(F_MatrixKeyRead)
{
	F_MatrixKeyRead = 0;
	
	switch(G_MatrixKeyValue)
	{		
		case MatrixKey_0:  //"����0��"	
		case MatrixKey_1:  //"����1��"		
		case MatrixKey_2:  //"����2��"		
		case MatrixKey_3:  //"����3��"		
		case MatrixKey_4:  //"����4��"		
		case MatrixKey_5:  //"����5��"					
		case MatrixKey_6:  //"����6��"			
		case MatrixKey_7:  //"����7��"			
		case MatrixKey_8:  //"����8��"			
		case MatrixKey_9:  //"����9��"		
//--**��������ֵ**----------------------------------------//
			G_MatrixKeyBuf[G_MatrixKeyCnt] = G_MatrixKeyValue; //���浱ǰ����ֵ������������

			Disp_ModifyTimeState(); //��ʾʱ���޸Ĺ���
			G_MatrixKeyCnt ++; //���尴������ָ���1
			
//Ҫ��15������ֵ:��(4��)+��(2��)+��(2��)+ʱ(2��)+��(2��)+��(2��)+����(1��)
			if(G_MatrixKeyCnt >= G_TotalKeyNum)  
			{
				G_MatrixKeyCnt = 0;
			}

			Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
			break;
	
		case MatrixKey_Return:	 //"���ؼ�"
			Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
			Initial_MainState(MAIN_Basic_Settings);//Main��Basic_Settings�˵�ѡ��(����ʱ)
			break;
			
		case MatrixKey_OK:	//"ȷ����"
			Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
			G_Year_SetBuf = G_MatrixKeyBuf[0]*1000 + G_MatrixKeyBuf[1]*100 + G_MatrixKeyBuf[2]*10 + G_MatrixKeyBuf[3];
			G_Month_SetBuf = G_MatrixKeyBuf[4]*10 + G_MatrixKeyBuf[5];
			G_Date_SetBuf = G_MatrixKeyBuf[6]*10 + G_MatrixKeyBuf[7];
			G_Hour_SetBuf = G_MatrixKeyBuf[8]*10 + G_MatrixKeyBuf[9];
			G_Minute_SetBuf = G_MatrixKeyBuf[10]*10 + G_MatrixKeyBuf[11];
			G_Second_SetBuf = G_MatrixKeyBuf[12]*10 + G_MatrixKeyBuf[13];
			G_Week_SetBuf = G_MatrixKeyBuf[14];
			
//--**�ж�����ʱ���Ƿ�Ϸ�**-------------------------------------//
			if(Check_RTC_InputModifyDate()) 	 //û�м��"����"�Ƿ������д�
			{
				Modify_RealTime_RTC();//�޸�RTCʵʱʱ��
				
				Initial_MainState(MAIN_Basic_Settings);//װ��//Main��Basic_Settings�˵�ѡ��(����ʱ)
			}
			else
			{	
				Dis_ModifyTimeError() ;  //��ʾ"����: ʱ����������!"
				Disp_ModifyTimeState(); //��ʾʱ���޸Ĺ���
				
				G_MatrixKeyCnt = 0;  //�ӵ�1λ(���ǧλ)��������
				Open_Buzzer(M_Buzz1s);   //����:  �÷�����ָ��ʱ��
			}  

			break;
	
		default:  
			break;	
		
	}
}




}



/****************************************************************************
*������-Function:	void Deal_Main_Self_Check(void)
*����- Description:	����//Main��ϵͳ�Լ�״̬
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_Main_Self_Check(void) //����//Main��ϵͳ�Լ�״̬
{
	
//==**��ʾ����**============================//
	F_Update_RealTime = NO; 	//��ʱ����ˢ��"ʵʱʱ��"	 
	F_Update_Temperature = NO;	//��ʱ����ˢ��"ʵʱ�¶�"  
	F_Update_CurrentValue = NO; //��ʱ����ˢ��"INA21x ʵʱ����ֵ" 
	F_Update_Power = NO;		//��ʱ����ˢ��"﮵�ص���"

//==**���� ����**===========================//
	if(!F_Timing)  // ��Ϊ��ʱ�������Զ����빤��״̬(����ʱ)
	{
		Initial_MainState(MAIN_Working_State);//װ�� //Main�����빤��״̬(����ʱ)
	}
}




/****************************************************************************
*������-Function:	void Deal_MAIN_Basic_Settings(void)
*����- Description:	//����//Main��Basic_Settings�˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_MAIN_Basic_Settings(void) //����//Main��Basic_Settings�˵�ѡ��(����ʱ)
{
////////////////////////////////////////////////////////////////////////////
//==**��ʾ����**========================================//
	unsigned char hour_H,hour_L,minute_H,minute_L,second_H,second_L;

	hour_H = RTCHOUR >> 4;
	hour_L = RTCHOUR & 0x0F;
	minute_H = RTCMIN >> 4;
	minute_L = RTCMIN & 0x0F;
	second_H = RTCSEC >> 4;
	second_L = RTCSEC & 0x0F;

	Disp_LED_Segment(0,0,hour_H,hour_L,DISP_Minus_LedSeg,minute_H,minute_L,DISP_Minus_LedSeg,second_H,second_L);


////////////////////////////////////////////////////////////////////////////
//--**IO���� ����**---------------------------------------------------//
	Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"

////////////////////////////////////////////////////////////////////////////
//--**���󰴼� ����**-----------------------------------------------//

	if(Detect_MatrixKey_1()) //"����1��"//1.Restart Self-Test
	{
		Initial_MainState(MAIN_Restart); //װ��//Main�� ��������ϵͳ�Լ�--Restart Self-Test       
	}
	  
	if(Detect_MatrixKey_2()) //"����2��"//2.Time Setting
	{
		Initial_MainState(MAIN_ModifyTime); //װ��//Main��"ʵʱʱ��"�޸�״̬
	}

}



/****************************************************************************
*������-Function:	void Deal_MAIN_Basic_Check(void)
*����- Description:	//����//Main��Basic_Check �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_MAIN_Basic_Check(void) //����//Main��Basic_Check �˵�ѡ��(����ʱ)
{
////////////////////////////////////////////////////////////////////////////
//==**��ʾ����**========================================//

////////////////////////////////////////////////////////////////////////////
//==**���� ����**=======================================//

////////////////////////////////////////////////////////////////////////////
//--**IO���� ����**---------------------------------------------------//

	Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"


////////////////////////////////////////////////////////////////////////////
//--**���󰴼� ����**-----------------------------------------------//
	if(Detect_MatrixKey_1()) //"����1��"//1.LED_Diode
	{
		Initial_WorkState(WORK_Led_Diode_Test); //װ��//Work��Led_Diode_Test ����(����ʱ)
	}

	if(Detect_MatrixKey_2()) //"����2��"//2.LED_Segment
	{
		Initial_WorkState(WORK_LED_Segment_Test); //װ��//Work��LED_Segment_Test ����(����ʱ)
	}

	if(Detect_MatrixKey_3()) //"����3��"//3.LCD_Segment
	{
		Initial_WorkState(WORK_LCD_Segment_Test); //װ��//Work��LCD_Segment_Test ����(����ʱ)
	}

	if(Detect_MatrixKey_4()) //"����4��"//4.Buzzer-Alarm
	{
		Initial_WorkState(WORK_Buzzer_Test); //װ��//Work��Buzzer_Test ����(����ʱ)
	}

	if(Detect_MatrixKey_5()) //"����5��"//5.Speaker
	{
		Initial_WorkState(WORK_Speaker_Test); //װ��//Work��Speaker_Test ����(����ʱ)
	}	
	
	if(Detect_MatrixKey_6()) //"����6��"//6.Microphone
	{
		Initial_WorkState(WORK_Microphone_Test); //װ��//Work��Microphone_Test ����(����ʱ)
	}	

	if(Detect_MatrixKey_7()) //"����7��"//7.Battery Fuel Gauge
	{
		Initial_WorkState(WORK_BQ27410_Test); //װ��//Work��BQ27410_FuelGauge_Test ����(����ʱ)
	}	

}



/****************************************************************************
*������-Function:	void Deal_MAIN_LCD_TFT_Test(void)
*����- Description:	//����//Main��LCD_TFT_Test �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_MAIN_LCD_TFT_Test(void) //����//Main��LCD_TFT_Test �˵�ѡ��(����ʱ)
{
////////////////////////////////////////////////////////////////////////////
//==**��ʾ����**========================================//

////////////////////////////////////////////////////////////////////////////
//==**���� ����**=======================================//

////////////////////////////////////////////////////////////////////////////
//--**IO���� ����**---------------------------------------------------//

	Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"

////////////////////////////////////////////////////////////////////////////
//--**���󰴼� ����**-----------------------------------------------//
	if(Detect_MatrixKey_1()) //"����1��"
	{
		Initial_WorkState(WORK_Line_LCD_TFT); //װ��//Work��Line_LCD_TFT ����(����ʱ)
	}

	if(Detect_MatrixKey_2()) //"����2��"
	{
		Initial_WorkState(WORK_Rectangle_LCD_TFT); //װ��//Work��Rectangle_LCD_TFT ����(����ʱ)
	}

	if(Detect_MatrixKey_3()) //"����3��"
	{
		Initial_WorkState(WORK_Circle_LCD_TFT); //װ��//Work��Circle_LCD_TFT ����(����ʱ)
	}

	if(Detect_MatrixKey_4()) //"����4��"
	{
		Initial_WorkState(WORK_FillArea_LCD_TFT); //װ��//Work��FillArea_LCD_TFT ����(����ʱ)
	}

	if(Detect_MatrixKey_5()) //"����5��"//
	{
		Initial_WorkState(WORK_Chinese_LCD_TFT); //װ��//Work��Chinese_LCD_TFT ����(����ʱ)
	}	
	
	if(Detect_MatrixKey_6()) //"����6��"//
	{
		Initial_WorkState(WORK_Clear_LCD_TFT); //װ��//Work��Clear_LCD_TFT ����(����ʱ)
	}

}


/****************************************************************************
*������-Function:	void Deal_MAIN_MatrixKey_Test(void)
*����- Description:	//����//Main��MatrixKey_Test �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_MAIN_MatrixKey_Test(void) //����//Main��MatrixKey_Test �˵�ѡ��(����ʱ)
{
////////////////////////////////////////////////////////////////////////////
//==**��ʾ����**========================================//

////////////////////////////////////////////////////////////////////////////
//==**���� ����**=======================================//


////////////////////////////////////////////////////////////////////////////
//--**���󰴼� ����**-----------------------------------------------//
	Disp_MatrixKey_Press(); //���ݰ��µ�"���󰴼�"���ڲ���������ʾ"����ֵ"

////////////////////////////////////////////////////////////////////////////
//--**IO���� ����**---------------------------------------------------//

	Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"

}


/****************************************************************************
*������-Function:	void Deal_MAIN_TouchPads_Test(void)
*����- Description:	//����//Main��TouchPads_Test �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_MAIN_TouchPads_Test(void) //����//Main��TouchPads_Test �˵�ѡ��(����ʱ)
{
////////////////////////////////////////////////////////////////////////////
//==**���� ����**=======================================//


////////////////////////////////////////////////////////////////////////////
//--**���󰴼� ����**-----------------------------------------------//

////////////////////////////////////////////////////////////////////////////
//==**����ģ�鴦��**======================================//
	F_En_Scan_MatrixKey = NO;  //��ֹɨ��"���󰴼�ɨ��"
	
	//Initial_Touch_Pad();  //��ʼ������: "Touch_Pads ���ݰ���" 
	Deal_Touch_Pad();  //����: "Touch_Pads ���ݰ���"
	
	F_En_Scan_MatrixKey = YES;	//�����ж���ɨ��"���󰴼�ɨ��"
	
	switch (G_SliderPosition)
	{
		case 0: 
			//Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
			break;
			
		case 1: 
			Disp_LED_Segment(0,0,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg);

				//�а������£��򿪷�����
			Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��

			G_LcdBuf[TestLine06][TestColumn01]= 'T';
			G_LcdBuf[TestLine06][TestColumn02]= 'P';
			G_LcdBuf[TestLine06][TestColumn03]= '1';
			F_Update_TestLine06 = YES;
			break;

		case 2: 
			Disp_LED_Segment(0,0,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg);

				//�а������£��򿪷�����
			Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��

			G_LcdBuf[TestLine06][TestColumn05]= 'T';
			G_LcdBuf[TestLine06][TestColumn06]= 'P';
			G_LcdBuf[TestLine06][TestColumn07]= '2';
			F_Update_TestLine06 = YES;
			break;

		case 3: 
			Disp_LED_Segment(0,0,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg);

				//�а������£��򿪷�����
			Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
			
			G_LcdBuf[TestLine06][TestColumn09]= 'T';
			G_LcdBuf[TestLine06][TestColumn10]= 'P';
			G_LcdBuf[TestLine06][TestColumn11]= '3';
			F_Update_TestLine06 = YES;
			break;
		
		case 4: 
			Disp_LED_Segment(0,0,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg);

				//�а������£��򿪷�����
			Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��

			G_LcdBuf[TestLine06][TestColumn13]= 'T';
			G_LcdBuf[TestLine06][TestColumn14]= 'P';
			G_LcdBuf[TestLine06][TestColumn15]= '4';
			F_Update_TestLine06 = YES;
			break;

		case 5: 
			Disp_LED_Segment(0,0,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg);

				//�а������£��򿪷�����
			Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��

			G_LcdBuf[TestLine06][TestColumn17]= 'T';
			G_LcdBuf[TestLine06][TestColumn18]= 'P';
			G_LcdBuf[TestLine06][TestColumn19]= '5';
			F_Update_TestLine06 = YES;
			break;

		case (255 / 17):
			break;
	}

////////////////////////////////////////////////////////////////////////////
//--**IO���� ����**---------------------------------------------------//

	Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"


}



/****************************************************************************
*������-Function:	void Deal_INA210_Current_Test(void)
*����- Description:	//����//Main��INA210_Current_Test �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_INA210_Current_Test(void) //����//Main��INA210_Current_Test �˵�ѡ��(����ʱ)
{
////////////////////////////////////////////////////////////////////////////
//==**AD�������**======================================//

////////////////////////////////////////////////////////////////////////////
//==**��ʾ����**========================================//
	if(F_500ms_INA21x_InTest)  //500ms ˢ����ʾ INA21x ʵʱ"������ֵ"
	{
		F_500ms_INA21x_InTest = 0;
		
////////////////////////////////////////////////////////////////////////////
//--**��ʾ����:  "����LCD_TFT" **------------------------------------//
		Disp_INA21x_Current_InTest(); //��"������"��ʾ: INA21x ʵʱ"������ֵ"

////////////////////////////////////////////////////////////////////////////
//--**��ʾ����:  "��̬�����LED_Segment"**-----------------------//
		Disp_LED_Segment(0,6,DISP_OFF_LedSeg,DISP_OFF_LedSeg,(unsigned char)(G_INA21x_AdResult/1000),(unsigned char)((G_INA21x_AdResult % 1000)/100),(unsigned char)((G_INA21x_AdResult % 100)/10),G_INA21x_AdResult % 10,DISP_OFF_LedSeg,DISP_A_LedSeg);
	}


////////////////////////////////////////////////////////////////////////////
//==**���� ����**=======================================//

////////////////////////////////////////////////////////////////////////////
//--**IO���� ����**---------------------------------------------------//

	Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"
}




/****************************************************************************
*������-Function:	void Deal_MAIN_Potentiometer_Test(void)
*����- Description:	//����//Main��Potentiometer_Test �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_MAIN_Potentiometer_Test(void) //����//Main��Potentiometer_Test �˵�ѡ��(����ʱ)
{
	unsigned char a,b,c;
	
	a = (unsigned char)(G_LastAdResult/1000);
	b = (unsigned char)((G_LastAdResult % 1000)/100);
	c = (G_LastAdResult % 100)/10;
	if(G_LastAdResult < 30) c = 0; //�ڵ�λ��������Сֵʱ����ʾ��ѹ����0.01,0.02,.000֮����ʾ�����������������ڵ�λ��������Сֵʱ����ʾ0.00

////////////////////////////////////////////////////////////////////////////
//==**AD�������**======================================//
		//��β���"Potentiometer��λ��"ADֵ�������д���
	Deal_ADC12_A(M_Potentiometer_AdNum); // ����������: ����β���ֵ����������ȥ����ͷ�����м�ļ���ADֵ��ƽ�����õ�����ADֵ��

////////////////////////////////////////////////////////////////////////////
//==**��ʾ����**========================================//
	if(F_500ms_Reflash_Potentiometer)  //500ms ˢ��"��ѹֵ"(��λ�� )
	{
		F_500ms_Reflash_Potentiometer = 0;
		
////////////////////////////////////////////////////////////////////////////
//--**��ʾ����:  "����LCD_TFT" **------------------------------------//
		Disp_Potentiometer_InTest();//��"������"��ʾ: ��λ��Potentiometer ʵʱ"��ѹֵ"

////////////////////////////////////////////////////////////////////////////
//--**��ʾ����:  "��̬�����LED_Segment"**-----------------------//
		Disp_LED_Segment(0,3,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,a,b,c);
	}

////////////////////////////////////////////////////////////////////////////
//==**���� ����**=======================================//

////////////////////////////////////////////////////////////////////////////
//--**IO���� ����**---------------------------------------------------//

	Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"

////////////////////////////////////////////////////////////////////////////
//--**���󰴼� ����**-----------------------------------------------//

}


/****************************************************************************
*������-Function:	void Deal_MAIN_NTC_HR202_Test(void)
*����- Description:	//����//Main��NTC_HR202_Test(��ʪ��) �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_MAIN_NTC_HR202_Test(void) //����//Main��NTC_HR202_Test(��ʪ��) �˵�ѡ��(����ʱ)
{
	int NTC_TMP_Ad;
	unsigned char a,b,c,d,bai,shi,ge;

	
	Deal_NTC_Temperature(); //���� "NTC �����¶ȴ�����" : AD������AD���ݴ�����ʾ����

	Deal_HR202_Humidity(); //���� "HR202_Humidity ������ʪ�ȴ�����"
////////////////////////////////////////////////////////////////////////////
//==**��ʾ����**========================================//
	if(F_500ms_NTC_HR202_InTest)  //500ms ˢ���ڲ�������ˢ��LCD_TFT��ʾNTC���¶ȣ���HR202��ʪ�ȣ�	
	{
		F_500ms_NTC_HR202_InTest = 0;
	
		Disp_NTC_TMP(G_NTC_Temperature); //��ʾ: ʵʱ"NTC ��������ֵ"��Ӧ���¶�


////////////////////////////////////////////////////////////////////////////
//--**��ʾ����:  "��̬�����LED_Segment"**-----------------------//
		NTC_TMP_Ad = G_NTC_Temperature;
		if(NTC_TMP_Ad < 0)
		{
			NTC_TMP_Ad = - NTC_TMP_Ad;
			a = DISP_Minus_LedSeg;
			b = (unsigned char)((NTC_TMP_Ad % 1000)/100);  //ʮλ
			c = (unsigned char)((NTC_TMP_Ad % 100)/10);    //��λ
			d = (unsigned char)(NTC_TMP_Ad % 10);		   //С����һλ
		
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
//==**���� ����**=======================================//

////////////////////////////////////////////////////////////////////////////
//--**IO���� ����**---------------------------------------------------//
	Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"

////////////////////////////////////////////////////////////////////////////
//--**���󰴼� ����**-----------------------------------------------//

}


/****************************************************************************
*������-Function:	void Deal_MAIN_Step_Motor_Test(void)
*����- Description:	//����//Main��Step_Motor_Test �˵�ѡ��(����ʱ) 
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_MAIN_Step_Motor_Test(void) //����//Main��Step_Motor_Test �˵�ѡ��(����ʱ) 
{
	unsigned char a = 0;
	unsigned char b = 0;
	//unsigned char c = 0;
	
	unsigned char s1 = 0;
	unsigned char s2 = 0;
	unsigned char s3 = 0;
	unsigned char s4 = 0;


////////////////////////////////////////////////////////////////////////////
//==**������λ��ADֵ,��Ϊת�ٸ���ֵ**================//
		//��β���"Potentiometer��λ��"ADֵ�������д���
	Deal_ADC12_A(M_Potentiometer_AdNum); // ����������: ����β���ֵ����������ȥ����ͷ�����м�ļ���ADֵ��ƽ�����õ�����ADֵ��


////////////////////////////////////////////////////////////////////////////
//==**���� ����**=======================================//

////////////////////////////////////////////////////////////////////////////
//--**���󰴼� ����**-----------------------------------------------//
	if(Detect_MatrixKey_1()) //"����1��"//1.Positive Rotation
	{
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
		
		if(G_Step_WorkState != STATE_Positive_Step_Motor)
		{
			G_Step_WorkState = STATE_Positive_Step_Motor;
			Initial_WorkState(WORK_Positive_Step_Motor); //װ��//Work��Positive_Step_Motor ����(����ʱ)
		}
	}

	if(Detect_MatrixKey_2()) //"����2��"//2.Reverse Rotation
	{
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
		
		if(G_Step_WorkState != STATE_Reverse_Step_Motor)
		{
			G_Step_WorkState = STATE_Reverse_Step_Motor;
			Initial_WorkState(WORK_Reverse_Step_Motor); //װ��//Work��Reverse_Step_Motor ����(����ʱ)
		}
	}

	if(Detect_MatrixKey_3()) //"����3��"//3.Stop Step-Moter
	{
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
		
		G_Step_WorkState = STATE_Stop_Step_Motor;
		Initial_WorkState(WORK_Stop_Step_Motor); //װ��//Work��Stop_Step_Motor ����(����ʱ)
	}


////////////////////////////////////////////////////////////////////////////
//==**��ʾ����**========================================//


	if(F_500ms_Reflash_Step_Motor)  //500ms ˢ��"ת��" --"Step_Motor �������"
	{
		F_500ms_Reflash_Step_Motor = 0;


		Deal_Speed_Step_Motor(); // ���㲽����ת��

////////////////////////////////////////////////////////////////////////////
//--**��ʾ����:  "����LCD_TFT" **------------------------------------//
			//��"���Ե��"��ʾ�ٶȸ�����ѹֵ: ��λ��Potentiometer ʵʱ"��ѹֵ"
		Disp_Potentiometer_Motor();

		Disp_Speed_Step_Motor(); //��"����Step_Motor"��ʾ����ٶ�

////////////////////////////////////////////////////////////////////////////
//--**��ʾ����:  "��̬�����LED_Segment"**-----------------------//
	//��λ����ʾ���
		a = (unsigned char)(G_LastAdResult/1000);
		b = (unsigned char)((G_LastAdResult % 1000)/100);
		//c = (unsigned char)(G_LastAdResult % 100)/10;
//		if(G_LastAdResult < 30) c = 0; //�ڵ�λ��������Сֵʱ����ʾ��ѹ����0.01,0.02,.000֮����ʾ�����������������ڵ�λ��������Сֵʱ����ʾ0.00

	//ת����ʾ���
		s3 = (unsigned char)(G_Step_Speed /1000);
		s2 = (unsigned char)((G_Step_Speed % 1000)/100);
		s1 = (unsigned char)(G_Step_Speed % 100)/10;


		if(G_Step_WorkState  == STATE_Reverse_Step_Motor) //��ת��ʾ����
		{
			s4 = DISP_Minus_LedSeg; //��ʾ"����"(����ʾ0)		
		
			if(s3 == 0) 
			{
				s4 = DISP_OFF_LedSeg; //��ʾ"����"(����ʾ0)	
				s3 = DISP_Minus_LedSeg; //��ʾ"����"(����ʾ0)	
			}
		}
		else if(G_Step_WorkState	== STATE_Positive_Step_Motor) //��ת��ʾ����
		{
			s4 = DISP_OFF_LedSeg;
			if(s3 == 0) s3 = DISP_OFF_LedSeg; //��ʾ"����"(����ʾ0)
		}
		
		Disp_LED_Segment(8,2,a,b,DISP_OFF_LedSeg,DISP_OFF_LedSeg,s4,s3,s2,s1);
	}


////////////////////////////////////////////////////////////////////////////
//--**IO���� ����**---------------------------------------------------//
	Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"

}


/****************************************************************************
*������-Function:	void Deal_MAIN_DC_Motor_Test(void)
*����- Description:	//����//Main��DC_Motor_Test �˵�ѡ��(����ʱ) 
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_MAIN_DC_Motor_Test(void) //����//Main��DC_Motor_Test �˵�ѡ��(����ʱ) 
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
//==**������λ��ADֵ,��Ϊת�ٸ���ֵ**===================//
		//��β���"Potentiometer��λ��"ADֵ�������д���
	Deal_ADC12_A(M_Potentiometer_AdNum); // ����������: ����β���ֵ����������ȥ����ͷ�����м�ļ���ADֵ��ƽ�����õ�����ADֵ��


////////////////////////////////////////////////////////////////////////////
//==**���� ����**===========================================//


////////////////////////////////////////////////////////////////////////////
//--**���󰴼� ����**-----------------------------------------------//
	if(Detect_MatrixKey_1()) //"����1��"//1.Positive Rotation
	{
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
		
		if(G_DC_WorkState == STATE_Reverse_DC_Motor)
		{
			G_DC_WorkState = STATE_Positive_DC_Motor;
			Initial_WorkState(WORK_Idle_DC_Motor); //װ��//Work��Idle_DC_Motor ����(����ʱ)
		}
		else
		{
			G_DC_WorkState = STATE_Positive_DC_Motor;
			Initial_WorkState(WORK_Positive_DC_Motor); //װ��//Work��Positive_DC_Motor ����(����ʱ)
		}
	}

	if(Detect_MatrixKey_2()) //"����2��"//2.Reverse Rotation
	{
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
		
		if(G_DC_WorkState == STATE_Positive_DC_Motor)
		{
			G_DC_WorkState = STATE_Reverse_DC_Motor;
			Initial_WorkState(WORK_Idle_DC_Motor); //װ��//Work��Idle_DC_Motor ����(����ʱ)
		}
		else 
		{
			G_DC_WorkState = STATE_Reverse_DC_Motor;
			Initial_WorkState(WORK_Reverse_DC_Motor); //װ��//Work��Reverse_DC_Motor ����(����ʱ)
		}
	}

	if(Detect_MatrixKey_3()) //"����3��"//3.Stop DC-Moter
	{
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
		G_DC_WorkState = STATE_Stop_DC_Motor;
		Initial_WorkState(WORK_Stop_DC_Motor); //װ��//Work��Stop_DC_Motor ����(����ʱ)
	}


////////////////////////////////////////////////////////////////////////////
//==**��ʾ����**========================================//
	if(F_500ms_Reflash_DC_Motor)  //500ms ˢ��"ת��" ("DC_Motor ֱ�����")
	{
		F_500ms_Reflash_DC_Motor = 0;

		speed = (G_DC_Speed * 60) / 3;  // ��ת������ת��"ʵ��ת��ֵ"r/min��λ

		
////////////////////////////////////////////////////////////////////////////
//--**��ʾ����:  "����LCD_TFT" **------------------------------------//
			//��"���Ե��"��ʾ�ٶȸ�����ѹֵ: ��λ��Potentiometer ʵʱ"��ѹֵ"
		Disp_Potentiometer_Motor();

		Disp_Speed_DC_Motor();//��"����DC_Motor"��ʾ����ٶ�

////////////////////////////////////////////////////////////////////////////
//--**��ʾ����:  "��̬�����LED_Segment"**-----------------------//
	//��λ����ʾ���
		a = (unsigned char)(G_LastAdResult/1000);
		b = (unsigned char)((G_LastAdResult % 1000)/100);
//c = (unsigned char)(G_LastAdResult % 100)/10;
		//if(G_LastAdResult < 30) c = 0; //�ڵ�λ��������Сֵʱ����ʾ��ѹ����0.01,0.02,.000֮����ʾ�����������������ڵ�λ��������Сֵʱ����ʾ0.00

	//ת����ʾ���
		if(G_DC_WorkState  == STATE_Positive_DC_Motor)  //��ת��ʾ����
		{
			s5 = DISP_OFF_LedSeg;//��ʾ"����"(����ʾ0)
			s4 = (unsigned char)(speed/1000);
			s3 = (unsigned char)((speed % 1000)/100);
			s2 = (unsigned char)(speed % 100)/10;
			s1 = (unsigned char)(speed % 10);
			if((s4 == 0)&&(s3 == 0)&&(s2 == 0)) s2 = DISP_OFF_LedSeg;	
			if((s4 == 0)&&(s3 == 0)) s3 = DISP_OFF_LedSeg;
			if(s4 == 0) s4 = DISP_OFF_LedSeg; //��ʾ"����"(����ʾ0)
		}
		else if(G_DC_WorkState  == STATE_Reverse_DC_Motor) //��ת��ʾ����
		{
			s5 = DISP_OFF_LedSeg;//��ʾ"����"(����ʾ0)
			s4 = (unsigned char)(speed/1000);
			s3 = (unsigned char)((speed % 1000)/100);
			s2 = (unsigned char)(speed % 100)/10;
			s1 = (unsigned char)(speed % 10);
			if((s4 == 0)&&(s3 == 0)&&(s2 == 0))
			{
				s5 = DISP_OFF_LedSeg;//��ʾ"����"(����ʾ0)
			 	s4 = DISP_OFF_LedSeg;//��ʾ"����"(����ʾ0)
				s3 = DISP_OFF_LedSeg;//��ʾ"����"(����ʾ0)
				s2 = DISP_Minus_LedSeg; //��ʾ"����"(����ʾ0)
			}
			if((s4 == 0)&&(s3 == 0))
			{
				s5 = DISP_OFF_LedSeg;//��ʾ"����"(����ʾ0)
			 	s4 = DISP_OFF_LedSeg;//��ʾ"����"(����ʾ0)
				s3 = DISP_Minus_LedSeg; //��ʾ"����"(����ʾ0)
			}
			if(s4 == 0) 
			{
				s5 = DISP_OFF_LedSeg;//��ʾ"����"(����ʾ0)
				s4 = DISP_Minus_LedSeg; //��ʾ"����"(����ʾ0)		
			}
			else if(s4 != 0) s5 = DISP_Minus_LedSeg; //��ʾ"����"(����ʾ0)	
				
		}
		Disp_LED_Segment(0,8,a,b,DISP_OFF_LedSeg,s5,s4,s3,s2,s1);
	}

////////////////////////////////////////////////////////////////////////////
//--**IO���� ����**---------------------------------------------------//
	Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"

}



/****************************************************************************
*������-Function:	void Deal_MAIN_TMP006_Temperature(void)
*����- Description:	//����//Main��TMP006_Temperature �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_MAIN_TMP006_Temperature(void) //����//Main��TMP006_Temperature �˵�ѡ��(����ʱ)
{
	int b = 0;
    unsigned char a4,a3,a2,a1;



////////////////////////////////////////////////////////////////////////////
//==**ģ�� ����**===========================================//
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
			a4 = DISP_OFF_LedSeg;//��ʾ"����"(����ʾ0)
			a3 = DISP_Minus_LedSeg; //��ʾ"����"(����ʾ0)
		}
		if(a4 == 0) a4 = DISP_Minus_LedSeg; //��ʾ"����"(����ʾ0)		
	}
	else //���¶�ֵ
	{
		a4 =  b / 1000; 
		a3 = (b % 1000) / 100;
		a2 = (b % 100) / 10;
		a1 =  b % 10;	
		
		if((a4 == 0)&&(a3 == 0)) a3 = DISP_OFF_LedSeg;
		if(a4 == 0) a4 = DISP_OFF_LedSeg; //��ʾ"����"(����ʾ0)
	}
		//��������ϣ���ʾ"�¶�"
	Disp_LED_Segment(0,4,DISP_OFF_LedSeg,DISP_OFF_LedSeg,a4,a3,a2,a1,DISP_OFF_LedSeg,DISP_C_LedSeg);

	if(F_500ms_TemperatureInTest)
	{
		F_500ms_TemperatureInTest = 0;
		Disp_TMP006_TemperatureInTest();//��LCD_TFT�ϣ���ʾ"�¶�"
	}

////////////////////////////////////////////////////////////////////////////
//==**���� ����**=======================================//

////////////////////////////////////////////////////////////////////////////
//--**IO���� ����**---------------------------------------------------//
	Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"

////////////////////////////////////////////////////////////////////////////
//--**���󰴼� ����**-----------------------------------------------//

}


/****************************************************************************
*������-Function:	void Deal_MAIN_TMP100_Temperature(void)
*����- Description:	//����//Main��TMP100_Temperature �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_MAIN_TMP100_Temperature(void) //����//Main��TMP100_Temperature �˵�ѡ��(����ʱ)
{

}




/****************************************************************************
*������-Function:	void Deal_MAIN_IrDA_UART(void)
*����- Description:	//����//Main��IrDA_UART �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_MAIN_IrDA_UART(void) //����//Main��IrDA_UART �˵�ѡ��(����ʱ)
{
//Close_LCD_Segment(); //�ر�"��ʽLCD_Segment"

////////////////////////////////////////////////////////////////////////////
//==**���� ����**=======================================//

	////////////////////////////////////////////////////////////////////////////
	//==**ģ�� ����**===========================================//
	Deal_IrDA_UART();	//���� "IrDA_UART  ���⴮��ͨ��"
	
	mTurn_LED_YELLOW;  //"��ת" LED_YELLOW //��ʾ���ڽ��к촦����ͨ��

	///////////////////////////////////////////////////////////////////////////
	if(G_RxData_IrDA == '1')	//���������յ�������Ϊ"A"
	{
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
			//���յ���ȷ�ĺ����źţ������ȫ��
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
		Disp_IrDA_Test(); //��ʾIrDA�Ƿ��յ�����
	}
	 
////////////////////////////////////////////////////////////////////////////
//--**IO���� ����**---------------------------------------------------//
	Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"

}



/****************************************************************************
*������-Function:	void Deal_MAIN_RS232_UART(void)
*����- Description:	//����//Main��RS232_UART �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_MAIN_RS232_UART(void) //����//Main��RS232_UART �˵�ѡ��(����ʱ)
{
////////////////////////////////////////////////////////////////////////////
//==**ģ�� ����**===========================================//
////////////////////////////////////////////////////////////////////////////
//==**���� ����**=======================================//
	Initial_RS232_UART();  //��ʼ������:  "RS232_UART  ����ͨ��"

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
	//--**���󰴼� ����**-----------------------------------------------//
		if(Detect_MatrixKey_1())
		{
			mTurn_LED_YELLOW;  //��ת��ɫLED
			F_EnUpdate_RS232 = 1;
			Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��

			F_HL_TestLine03 = YES;
			F_Update_TestLine03 = YES;
			
			Open_Timing_Task(500);
			
			Deal_RS232_UART(); //���� "RS232 ����ͨ��"			
		}
		
		if((!F_Timing) && F_EnUpdate_RS232) 
		{
			F_EnUpdate_RS232 = 0;
			F_Update_TestLine03 = YES;
		}


	
	////////////////////////////////////////////////////////////////////////////
	//--**�����˳���ѭ��**--------------------------------------------//
		if(G_RxData_RS232 == '1')
		{
			G_RxData_RS232 = 0xFF;	//����ջ���

			Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
			
			WaitingDelayMs(50);//��ʱ50ms(��Ϊ��UART������ģ�����Ÿ��ã�����ʱ�Ļ�����Щ���ݾͷ�����ȥ)
				//���յ�'1'���������ʾ'1'
			Disp_LED_Segment(0,0,DISP_2_LedSeg,DISP_3_LedSeg,DISP_2_LedSeg,DISP_OFF_LedSeg,DISP_Minus_LedSeg,DISP_Minus_LedSeg,DISP_OFF_LedSeg,DISP_1_LedSeg);
			Disp_RS232_Char_1(); //��ʾRS232�յ�����"1"		
//break; 
		}
		else if(G_RxData_RS232 == '2')
		{
			G_RxData_RS232 = 0xFF;	//����ջ���

			Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
			
			WaitingDelayMs(50);//��ʱ50ms(��Ϊ��UART������ģ�����Ÿ��ã�����ʱ�Ļ�����Щ���ݾͷ�����ȥ)
				//���յ�'2'���������ʾ'2'
			Disp_LED_Segment(0,0,DISP_2_LedSeg,DISP_3_LedSeg,DISP_2_LedSeg,DISP_OFF_LedSeg,DISP_Minus_LedSeg,DISP_Minus_LedSeg,DISP_OFF_LedSeg,DISP_2_LedSeg);
			Disp_RS232_Char_2(); //��ʾRS232�յ�����"2"	
//break; 
		}
		else if(G_RxData_RS232 != 0xFF)
		{
			G_RxData_RS232 = 0xFF;	//����ջ���
			WaitingDelayMs(50);//��ʱ50ms(��Ϊ��UART������ģ�����Ÿ��ã�����ʱ�Ļ�����Щ���ݾͷ�����ȥ)
				//���յ�'�����ַ�'���������ʾ'ȫ��'
			Disp_LED_Segment(0,0,DISP_2_LedSeg,DISP_3_LedSeg,DISP_2_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
			Disp_RS232_None(); //����ʾRS232�յ�����
//break; 
		}

		Deal_Main_Loop();  //��ѭ���еģ�ѭ��ִ�еĲ���(��ʾ������)

	////////////////////////////////////////////////////////////////////////////
	//--**IO���� ����**---------------------------------------------------//
		Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"

		if(G_KeyCnt != 13) break;  //�����˳���ѭ��
	}

////////////////////////////////////////////////////////////////////////////
//--**IO���� ����**---------------------------------------------------//
	Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"

}



/****************************************************************************
*������-Function:	void Deal_MAIN_RS485_UART(void)
*����- Description:	//����//Main��RS485_UART �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_MAIN_RS485_UART(void) //����//Main��RS485_UART �˵�ѡ��(����ʱ)
{
////////////////////////////////////////////////////////////////////////////
//==**ģ�� ����**===========================================//
////////////////////////////////////////////////////////////////////////////
//==**���� ����**=======================================//

	Initial_RS485_UART();  //��ʼ������:  "RS485_UART  ����ͨ��"
	
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
	//--**���󰴼� ����**-----------------------------------------------//
		if(Detect_MatrixKey_1())
		{
			F_EnUpdate_RS485 = 1;
			Open_Buzzer(BuzzTime_Key);	//������Чʱ���÷�����ָ��ʱ��
			F_HL_TestLine03 = YES;
			F_Update_TestLine03 = YES;
			F_Update_TestLine04 = YES;

			Open_Timing_Task(500);

			Sent_OneByte_RS485_UART('1');  //RS485ͨ��UART����һ���ֽ�����	
			mTurn_LED_YELLOW;  //��ת��ɫLED
		}
		
		if(Detect_MatrixKey_2())
		{
			F_EnUpdate_RS485 = 1;
			Open_Buzzer(BuzzTime_Key);	//������Чʱ���÷�����ָ��ʱ��
			F_HL_TestLine04 = YES;
			F_Update_TestLine03 = YES;
			F_Update_TestLine04 = YES;

			Open_Timing_Task(500);

			Sent_OneByte_RS485_UART('2');  //RS485ͨ��UART����һ���ֽ�����	
			mTurn_LED_YELLOW;  //��ת��ɫLED
		}

		if((!F_Timing) && F_EnUpdate_RS485) 
		{
			F_EnUpdate_RS485 = 0;
			F_Update_TestLine03 = YES;
			F_Update_TestLine04 = YES;
		}

	////////////////////////////////////////////////////////////////////////////
	//--**�����˳���ѭ��**--------------------------------------------//
		if(G_RxData_RS485 == '1')
		{
			G_RxData_RS485 = 0xFF;  //����ջ���
			
			Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
			
				//���յ�'1'���������ʾ'1'
			Disp_LED_Segment(0,0,DISP_4_LedSeg,DISP_8_LedSeg,DISP_5_LedSeg,DISP_OFF_LedSeg,DISP_Minus_LedSeg,DISP_Minus_LedSeg,DISP_OFF_LedSeg,DISP_1_LedSeg);
			Disp_RS485_Char_1(); //��ʾRS485�յ�����"1"		
//break; 
		}
		else if(G_RxData_RS485 == '2')
		{
			G_RxData_RS485 = 0xFF;	//����ջ���

			Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
			
				//���յ�'2'���������ʾ'2'
			Disp_LED_Segment(0,0,DISP_4_LedSeg,DISP_8_LedSeg,DISP_5_LedSeg,DISP_OFF_LedSeg,DISP_Minus_LedSeg,DISP_Minus_LedSeg,DISP_OFF_LedSeg,DISP_2_LedSeg);
			Disp_RS485_Char_2(); //��ʾRS485�յ�����"2"	
	//break; 
		}

		Deal_Main_Loop();  //��ѭ���еģ�ѭ��ִ�еĲ���(��ʾ������)

		////////////////////////////////////////////////////////////////////////////
		//--**IO���� ����**---------------------------------------------------//
		Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"
			
		if(G_KeyCnt != 14) break;  
	}

////////////////////////////////////////////////////////////////////////////
//--**IO���� ����**---------------------------------------------------//
	Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"

}



/****************************************************************************
*������-Function:	void Deal_MAIN_CC1101_Test(void)
*����- Description:	//����//Main��CC1101_Test �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_MAIN_CC1101_Test(void) //����//Main��CC1101_Test �˵�ѡ��(����ʱ)
{
////////////////////////////////////////////////////////////////////////////
//==**���� ����**=======================================//
	Initial_CC1101();  //��ʼ������:  "CC1101 �͹�����Ƶ�շ���"

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
	//==**ģ�� ����**===========================================//
		Deal_CC1101();	//����"CC1101 �͹�����Ƶ�շ���"

	////////////////////////////////////////////////////////////////////////////
	//--**���󰴼� ����**-----------------------------------------------//
	
		if(F_EnUpdate_CC1101) 
		{
			F_EnUpdate_CC1101 = 0;
			F_Update_TestLine03 = YES;
			F_Update_TestLine04 = YES;
			break; 
		}

	
		if( (Detect_MatrixKey_1())&& (!F_Timing))
		{
			mTurn_LED_YELLOW;  //��ת��ɫLED
			F_EnUpdate_CC1101 = 1;
			Open_Buzzer(BuzzTime_Key);	//������Чʱ���÷�����ָ��ʱ��	
			F_HL_TestLine03 = YES;
			F_Update_TestLine03 = YES;
			F_Update_TestLine04 = YES;
			
			Open_Timing_Task(1000);
			
			Send_OneByte_CC1101('1'); //����һ���ֽ�����-- "CC1101 �͹�����Ƶ�շ���"
			break;
		}
		if( (Detect_MatrixKey_2())&& (!F_Timing))
		{
			mTurn_LED_YELLOW;   //��ת��ɫLED
			F_EnUpdate_CC1101 = 1;
			Open_Buzzer(BuzzTime_Key);	//������Чʱ���÷�����ָ��ʱ��
			F_HL_TestLine04 = YES;
			F_Update_TestLine03 = YES;
			F_Update_TestLine04 = YES;

			Open_Timing_Task(1000);

			Send_OneByte_CC1101('2'); //����һ���ֽ�����-- "CC1101 �͹�����Ƶ�շ���"
			break;
		}


	////////////////////////////////////////////////////////////////////////////
	//--**�����˳���ѭ��**--------------------------------------------//
		if(G_RxData_CC1101 == '1')
		{
			G_RxData_CC1101 = 0xFF;	//����ջ���
			Open_Buzzer(BuzzTime_Key);	//������Чʱ���÷�����ָ��ʱ��
			
				//���յ�'1'���������ʾ'1'
			Disp_LED_Segment(0,0,DISP_C_LedSeg,DISP_C_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_0_LedSeg,DISP_1_LedSeg,DISP_OFF_LedSeg,DISP_1_LedSeg);
			Disp_CC1101_Char_1(); //��ʾCC1101�յ�����"1" 	
			break; 
		}
		else if(G_RxData_CC1101 == '2')
		{
			G_RxData_CC1101 = 0xFF;	//����ջ���
			Open_Buzzer(BuzzTime_Key);	//������Чʱ���÷�����ָ��ʱ��

				//���յ�'2'���������ʾ'2'
			Disp_LED_Segment(0,0,DISP_C_LedSeg,DISP_C_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_0_LedSeg,DISP_1_LedSeg,DISP_OFF_LedSeg,DISP_2_LedSeg);
			Disp_CC1101_Char_2(); //��ʾCC1101�յ�����"2" 
			break; 
		}
		
	F_En_Scan_MatrixKey = NO;  //��ֹɨ��"���󰴼�ɨ��"
	Scan_MatrixKey(); //"�������"ɨ�裬5msɨ��һ�ΰ���(�ж���) 	
	Deal_LED_Segment();//"�����LED_Segment": ����ͬ"����ģʽ"
	F_En_Scan_MatrixKey = YES;  //ʹ��"���󰴼�ɨ��"




	////////////////////////////////////////////////////////////////////////////
	//--**IO���� ����**---------------------------------------------------//
		Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"

		if(G_KeyCnt != 15) break;  
	}

////////////////////////////////////////////////////////////////////////////
//--**IO���� ����**---------------------------------------------------//
	Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"

}


/****************************************************************************
*������-Function:	void Deal_MAIN_SD_Card_Test(void)
*����- Description:		//����//Main��SD_Card_Test �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_MAIN_SD_Card_Test(void) //����//Main��SD_Card_Test �˵�ѡ��(����ʱ)
{
	char keyVal[1];

////////////////////////////////////////////////////////////////////////////
//==**���� ����**=======================================//
	Initial_SD_Card();  //��ʼ������: "SD_Card SD��"
//Initial_Osccon_SD_Card(); //��ʼ������--"SD_Card SD��"
		
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
	//--**���󰴼� ����**-----------------------------------------------//
		F_En_Scan_MatrixKey = NO;  //��ֹɨ��"���󰴼�ɨ��"
		Scan_MatrixKey(); //"�������"ɨ�裬5msɨ��һ�ΰ���(�ж���) 	
		Deal_LED_Segment();//"�����LED_Segment": ����ͬ"����ģʽ"
		F_En_Scan_MatrixKey = YES;  //ʹ��"���󰴼�ɨ��"
	
		if(G_MatrixKeyValue != M_NullMatrixKey)
		{
			switch(G_MatrixKeyValue)
			{		
				case MatrixKey_0:  //"����0��"	
				case MatrixKey_1:  //"����1��"		
				case MatrixKey_2:  //"����2��"		
				case MatrixKey_3:  //"����3��"		
				case MatrixKey_4:  //"����4��"		
				case MatrixKey_5:  //"����5��"					
				case MatrixKey_6:  //"����6��"			
				case MatrixKey_7:  //"����7��"			
				case MatrixKey_8:  //"����8��"			
				case MatrixKey_9:  //"����9��"
					G_Data_SD_Write = G_MatrixKeyValue;
					Open_Buzzer(BuzzTime_Key);	//������Чʱ���÷�����ָ��ʱ��
					Disp_LED_Segment(0,0,DISP_5_LedSeg,DISP_d_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,G_Data_SD_Write,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
					Deal_LED_Segment();//"�����LED_Segment": ����ͬ"����ģʽ"
					
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
						
						Open_Buzzer(BuzzTime_Key);	//������Чʱ���÷�����ָ��ʱ��
						
						
						Disp_LED_Segment(0,0,DISP_5_LedSeg,DISP_d_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,G_Data_SD_Write,DISP_OFF_LedSeg,DISP_OFF_LedSeg,G_Data_SD_Read);	
						Deal_LED_Segment();//"�����LED_Segment": ����ͬ"����ģʽ"
						mTurn_LED_YELLOW;  //��ת��ɫLED
					}
					Deal_LCD_TFT();//LCD_TFT ��ʾ����//ֻ�������ݱ仯����ʾ����
					break;
					
				default:	break;		
			}
		}



	////////////////////////////////////////////////////////////////////////////
	//--**IO���� ����**---------------------------------------------------//
		Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"
	
		if(G_KeyCnt != 16)
		{
				//��ΪSD������ز���ʱ���޸��˾��񣬹��������³�ʹ��,��ԭ֮ǰ�ľ�������
			//Osccon_Initial();//�����ʼ������:������ؾ������
			break;  
		}
			
	}

}



/****************************************************************************
*������-Function:	void Deal_MAIN_MassStorage_Test(void)
*����- Description:	//����//Main��MassStorage_Test �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_MAIN_MassStorage_Test(void) //����//Main��MassStorage_Test �˵�ѡ��(����ʱ)
{

	////////////////////////////////////////////////////////////////////////////
	//--**���󰴼� ����**-----------------------------------------------//
	if(Detect_MatrixKey_1())
	{
		mOpen_LED_YELLOW;  //�򿪻�ɫLED
		Open_Buzzer(BuzzTime_Key);	//������Чʱ���÷�����ָ��ʱ��

F_HL_TestLine03 = YES;
F_Update_TestLine03 = YES;
F_Update_TestLine04 = YES;
		
Deal_LCD_TFT();//LCD_TFT ��ʾ����//ֻ�������ݱ仯����ʾ����
		
		Initial_MainState(MAIN_MassStorage_USB); //װ��//Main��MassStorage_USB �˵�ѡ��(����ʱ)	
	}
	
	
	if(Detect_MatrixKey_2())
	{
		mClose_LED_YELLOW;  //�رջ�ɫLED
		Open_Buzzer(BuzzTime_Key);	//������Чʱ���÷�����ָ��ʱ��


		Disable_USB_SD_Card_Reader();  //����:	"USB_SD_Card_Reader ������(USB-SD��)"
		
		F_HL_TestLine04 = YES;
		F_Update_TestLine03 = YES;
		F_Update_TestLine04 = YES;

		Deal_LCD_TFT();//LCD_TFT ��ʾ����//ֻ�������ݱ仯����ʾ����
	}	

////////////////////////////////////////////////////////////////////////////
//--**IO���� ����**---------------------------------------------------//
	Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"

}





/****************************************************************************
*������-Function:	void Deal_MAIN_MassStorage_USB(void)
*����- Description:	  	���� //Main��MassStorage_USB �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_MAIN_MassStorage_USB(void) //���� //Main��MassStorage_USB �˵�ѡ��(����ʱ)
{
	Initial_USB_SD_Card_Reader();  //��ʼ������:  "USB_SD_Card_Reader ������(USB-SD��)"
	
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
		//--**���󰴼� ����**-----------------------------------------------//

		if(Detect_MatrixKey_1())
		{
			mOpen_LED_YELLOW;  //�򿪻�ɫLED
			Open_Buzzer(BuzzTime_Key);	//������Чʱ���÷�����ָ��ʱ��
			
			Disp_LED_Segment(0,0,DISP_U_LedSeg,DISP_5_LedSeg,DISP_b_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_1_LedSeg);

			F_HL_TestLine03 = YES;
			F_Update_TestLine03 = YES;
			F_Update_TestLine04 = YES;
					
			Deal_LCD_TFT();//LCD_TFT ��ʾ����//ֻ�������ݱ仯����ʾ����
					
			Initial_USB_SD_Card_Reader();  //��ʼ������:  "USB_SD_Card_Reader ������(USB-SD��)"
		}

		if(Detect_MatrixKey_2())
		{
			Open_Buzzer(BuzzTime_Key);	//������Чʱ���÷�����ָ��ʱ��
			mClose_LED_YELLOW;  //�رջ�ɫLED

			Disable_USB_SD_Card_Reader();  //����:	"USB_SD_Card_Reader ������(USB-SD��)"

			Disp_LED_Segment(0,0,DISP_U_LedSeg,DISP_5_LedSeg,DISP_b_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_0_LedSeg);

			F_HL_TestLine04 = YES;
			F_Update_TestLine03 = YES;
			F_Update_TestLine04 = YES;

			Deal_LCD_TFT();//LCD_TFT ��ʾ����//ֻ�������ݱ仯����ʾ����
		}	

		Deal_USB_SD_Card_Reader();	//����"USB_SD_Card_Reader ������(USB-SD��)"


	F_En_Scan_MatrixKey = NO;  //��ֹɨ��"���󰴼�ɨ��"
	Scan_MatrixKey(); //"�������"ɨ�裬5msɨ��һ�ΰ���(�ж���) 	
	Deal_LED_Segment();//"�����LED_Segment": ����ͬ"����ģʽ"
	F_En_Scan_MatrixKey = YES;	//ʹ��"���󰴼�ɨ��"
	

		if(G_KeyCnt != 17)
		{
			Open_Buzzer(BuzzTime_Key);	//������Чʱ���÷�����ָ��ʱ��
			mClose_LED_YELLOW;	//�رջ�ɫLED
			
			Disable_USB_SD_Card_Reader();  //����:	"USB_SD_Card_Reader ������(USB-SD��)"
			
			break;	
		}	
	////////////////////////////////////////////////////////////////////////////
	//--**IO���� ����**---------------------------------------------------//
		Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"

	}

}



/****************************************************************************
*������-Function:	void Deal_MAIN_MassStorage_USB(void)
*����- Description:	  	���� //Main��MassStorage_USB �˵�ѡ��(����ʱ)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*******************************************************
void Deal_MAIN_MassStorage_USB(void) //���� //Main��MassStorage_USB �˵�ѡ��(����ʱ)
{
	Initial_USB_SD_Card_Reader();  //��ʼ������:  "USB_SD_Card_Reader ������(USB-SD��)"
	
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
		
		Deal_USB_SD_Card_Reader();	//����"USB_SD_Card_Reader ������(USB-SD��)"

		////////////////////////////////////////////////////////////////////////////
		//--**���󰴼� ����**-----------------------------------------------//

		if(Detect_MatrixKey_2())
		{
			Disable_USB_SD_Card_Reader();  //����:	"USB_SD_Card_Reader ������(USB-SD��)"

		WaitingDelayMs(1000);
			//��Ϊ�˳�USBʱ,���ֻ�Ӱ��LCD_TFT ��ʾ��
			//�ʣ��˳�USB ,  ���������λ�����¿���
		mReset_Soft;   //"�����λ"

			mClose_LED_YELLOW;  //�رջ�ɫLED
		}	
**********************/

/****************
if(Detect_MatrixKey_3())
{
Disable_USB_SD_Card_Reader();  //����:	"USB_SD_Card_Reader ������(USB-SD��)"
USB_reset();

WaitingDelayMs(5000);
		
//mDisable_GIE;  //��ֹ���ж�



//��ΪUSB ����ز���ʱ���޸��˾��񣬹��������³�ʹ��,��ԭ֮ǰ�ľ�������
Osccon_Initial();//�����ʼ������:������ؾ������
Timer2_Initial(); //��ʱ��A2��ʼ������(����ϵͳÿ1ms�Զ��ж�һ��)
//mEnable_GIE;	// �������ж�

SPI_B_Initial_LCD_TFT();	//SPI_Bģ���ʼ��:�˿ڳ�ʼ��������SPI (LCD_TFT )
WaitingDelayMs(5000);
break;	

}
**************/
	/****************

	////////////////////////////////////////////////////////////////////////////
	//--**IO���� ����**---------------------------------------------------//
		Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"

		if(G_KeyCnt != 18)
		{
		
//mDisable_GIE;  //��ֹ���ж�
//WaitingDelayMs(3000);

	//Disable_USB_SD_Card_Reader();  //����:	"USB_SD_Card_Reader ������(USB-SD��)"
	//USB_reset();

//��ΪUSB ����ز���ʱ���޸��˾��񣬹��������³�ʹ��,��ԭ֮ǰ�ľ�������
//Osccon_Initial();//�����ʼ������:������ؾ������
//Timer2_Initial(); //��ʱ��A2��ʼ������(����ϵͳÿ1ms�Զ��ж�һ��)
//SPI_B_Initial_LCD_TFT();	//SPI_Bģ���ʼ��:�˿ڳ�ʼ��������SPI (LCD_TFT )

//WaitingDelayMs(3000); 	
//mEnable_GIE;  // �������ж�



			WaitingDelayMs(1000);
				//��Ϊ�˳�USBʱ,���ֻ�Ӱ��LCD_TFT ��ʾ��
				//�ʣ��˳�USB ,  ���������λ�����¿���
			mReset_Soft;   //"�����λ"
			break;	
			
		}	
	}

}
**************/



/****************************************************************************
*������-Function:	void Deal_MainState(void)
*����- Description:	 "����"��ϵͳMain��"״̬"�µ����� (״̬��)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_MainState(void)
{
	switch(G_MainState) 
	{
////////////////////////////////////////////////////////////////////////////
//==**����\����״ֵ̬: 0x01--0xFF **=======================//
////////////////////////////////////////////////////////////////////////////

case MAIN_Restart:  //Main�� ��������ϵͳ�Լ�--Restart Self-Test     
	break;

case MAIN_Self_Check:	//Main��ϵͳ�Լ�״̬
	Deal_Main_Self_Check();  //����//Main��ϵͳ�Լ�״̬
	break;	


////////////////////////////////////////////////////////////////////////////
//==**���˵�״ֵ̬: 0x100--0x1FF **=========================//
////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	//--**��������: "ʱ���޸�"�˵�0x200--0x21F **-------------------//
	////////////////////////////////////////////////////////////////////////////
case MAIN_ModifyTime:  //Main��"ʵʱʱ��"�޸�״̬
	Deal_Main_ModifyTime(); //����//Main��"ʵʱʱ��"�޸�״̬
	break;

////////////////////////////////////////////////////////////////////////////
//==**����"�˵�"״ֵ̬: 0x7000--0x7FFF**====================//
////////////////////////////////////////////////////////////////////////////

case MAIN_Working_State:	//Main�����빤��״̬(����ʱ)
	
	break;	
	
case MAIN_Basic_Settings:	//Main��Basic_Settings�˵�ѡ��(����ʱ)
	Deal_MAIN_Basic_Settings(); //����//Main��Basic_Settings�˵�ѡ��(����ʱ)
	break;

case MAIN_Basic_Check:	//Main��Basic_Check �˵�ѡ��(����ʱ)
	Deal_MAIN_Basic_Check(); //����//Main��Basic_Check �˵�ѡ��(����ʱ)
	break;

case MAIN_LCD_TFT_Test:	//Main��LCD_TFT_Test �˵�ѡ��(����ʱ)
	Deal_MAIN_LCD_TFT_Test(); //����//Main��LCD_TFT_Test �˵�ѡ��(����ʱ)
	break;

case MAIN_MatrixKey_Test:	//Main��MatrixKey_Test �˵�ѡ��(����ʱ)
	Deal_MAIN_MatrixKey_Test(); //����//Main��MatrixKey_Test �˵�ѡ��(����ʱ)
	break;

case MAIN_TouchPads_Test:	//Main��TouchPads_Test �˵�ѡ��(����ʱ)
	Deal_MAIN_TouchPads_Test(); //����//Main��TouchPads_Test �˵�ѡ��(����ʱ)
	break;

case MAIN_INA21x_Current_Test:  //Main��INA21x_Current_Test �˵�ѡ��(����ʱ)
	Deal_INA210_Current_Test(); //����//Main��INA210_Current_Test �˵�ѡ��(����ʱ)
	break;

case MAIN_TMP006_Temperature:  //Main��TMP006_Temperature �˵�ѡ��(����ʱ)
	Deal_MAIN_TMP006_Temperature(); //����//Main��TMP006_Temperature �˵�ѡ��(����ʱ)
	break;

case MAIN_TMP100_Temperature:  //Main��TMP100_Temperature �˵�ѡ��(����ʱ)
	Deal_MAIN_TMP100_Temperature(); //����//Main��TMP100_Temperature �˵�ѡ��(����ʱ)
	break;

case MAIN_Potentiometer_Test:	//Main��Potentiometer_Test �˵�ѡ��(����ʱ)
	Deal_MAIN_Potentiometer_Test(); //����//Main��Potentiometer_Test �˵�ѡ��(����ʱ)
	break;

case MAIN_DC_Motor_Test:  //Main��DC_Motor_Test �˵�ѡ��(����ʱ) 
	Deal_MAIN_DC_Motor_Test(); //����///Main��DC_Motor_Test �˵�ѡ��(����ʱ) 
	break;

case MAIN_Step_Motor_Test:  //Main��Step_Motor_Test �˵�ѡ��(����ʱ) 
	Deal_MAIN_Step_Motor_Test(); //����//Main��Step_Motor_Test �˵�ѡ��(����ʱ) 
	break;

case MAIN_NTC_HR202_Test:  //Main��NTC_HR202_Test(��ʪ��) �˵�ѡ��(����ʱ)
	Deal_MAIN_NTC_HR202_Test(); //����//Main��NTC_HR202_Test(��ʪ��) �˵�ѡ��(����ʱ)
	break;

case MAIN_IrDA_UART:  //Main��IrDA_UART �˵�ѡ��(����ʱ)
	Deal_MAIN_IrDA_UART(); //����//Main��IrDA_UART �˵�ѡ��(����ʱ)
	break;

case MAIN_RS232_UART:  //Main��RS232_UART �˵�ѡ��(����ʱ)
	Deal_MAIN_RS232_UART(); //����//Main��RS232_UART �˵�ѡ��(����ʱ)
	break;

case MAIN_RS485_UART:  //Main��RS485_UART �˵�ѡ��(����ʱ)
	Deal_MAIN_RS485_UART(); //����//Main��RS485_UART �˵�ѡ��(����ʱ)
	break;





case MAIN_CC1101_Test:  //Main��CC1101_Test �˵�ѡ��(����ʱ)
	Deal_MAIN_CC1101_Test(); //����//Main��CC1101_Test �˵�ѡ��(����ʱ)
	break;

case MAIN_SD_Card_Test: //Main��SD_Card_Test �˵�ѡ��(����ʱ)
	Deal_MAIN_SD_Card_Test(); //����//Main��SD_Card_Test �˵�ѡ��(����ʱ)
	break;

case MAIN_MassStorage_Test:	//Main��MassStorage_Test �˵�ѡ��(����ʱ)
	Deal_MAIN_MassStorage_Test(); //����//Main��MassStorage_Test �˵�ѡ��(����ʱ)
	break;

case MAIN_MassStorage_USB:  //Main��MassStorage_USB �˵�ѡ��(����ʱ)
	Deal_MAIN_MassStorage_USB(); //���� //Main��MassStorage_USB �˵�ѡ��(����ʱ)
	break;


////////////////////////////////////////////////////////////////////////////
	default:
		break;
	}
}





/****************************************************************************
*������-Function:	void Deal_WorkState(void)
*����- Description:	 "����"������Work��"״̬"�µ����� (״̬��)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_WorkState(void)
{

////////////////////////////////////////////////////////////////////////////
//==**��������: **0x8000--0x8FFF** ===========================//
////////////////////////////////////////////////////////////////////////////

	switch(G_WorkState) 
	{
////////////////////////////////////////////////////////////////////////////
//==**"����ʱ"�Ŀ���״̬** ============================//

case WORK_Test_IdleState: //Work��"����ʱ"�Ŀ���״̬(����ʱ)

	break;

////////////////////////////////////////////////////////////////////////////
//==**"��ز���" ( �����˵�)** ===========================//

case WORK_Self_Check: //Work��Self_Check ����(����ʱ)
	break;	

case WORK_Led_Diode_Test: //Work��Led_Diode_Test ����(����ʱ)
////////////////////////////////////////////////////////////////////////////
//==**��������(��Ӧ��IO�����)**=======================//
	SOS_Function();  //Led_Diode(���������) ʵ��SOS ��ȹ���
	break;	
	
case WORK_LED_Segment_Test: //Work��LED_Segment_Test ����(����ʱ)
////////////////////////////////////////////////////////////////////////////
//==**��������(��Ӧ��IO�����)**=======================//
	if(F_500ms_LedSeg) //"��̬�����LED_Segment" ��ʾ"���"ʱ��
	{ 
		F_500ms_LedSeg = 0;
		
			//"����""��̬�����LED_Segment" : ͬʱ"ѭ��"��ʾ"��ͬ"�ַ�
		Disp_LED_Segment(0,0,G_LedSeg_Cnt,G_LedSeg_Cnt,G_LedSeg_Cnt,G_LedSeg_Cnt,G_LedSeg_Cnt,G_LedSeg_Cnt,G_LedSeg_Cnt,G_LedSeg_Cnt);

		G_LedSeg_Cnt ++;//"��̬�����LED_Segment"���õ��ļ�����(�����ַ�ѭ����ʾ)
		if(G_LedSeg_Cnt >= DISP_MaxNum_LedSeg) G_LedSeg_Cnt =0 ;  //22���ַ�(�������ʾ����)	
	}

////////////////////////////////////////////////////////////////////////////
//--**���󰴼� ����**-----------------------------------------------//
	if(Detect_MatrixKey_AC()) //"AC��"//
	{
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
			//Mode��"�ر�"��ģ��("��̬�����LED_Segment" )	
		Init_Mode_LED_Segment(MODE_Close_LED_Segment);
	}
	if(Detect_MatrixKey_Plus()) //"+ ��"//
	{
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
		G_Brightness_LedSeg ++;  //��������("��̬�����LED_Segment" )	
		if(G_Brightness_LedSeg >= 9) G_Brightness_LedSeg = M_Brightness_1_LedSeg;
	}
	if(Detect_MatrixKey_Minus()) //"-��"//
	{
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
		G_Brightness_LedSeg --;  //��С����("��̬�����LED_Segment" )	
		if(G_Brightness_LedSeg == 0) G_Brightness_LedSeg = M_Brightness_8_LedSeg;
	}
	if(Detect_MatrixKey_Equal()) //"=��"//
	{
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
		
		G_Brightness_LedSeg = G_BrightnessKind;   //����Ϊ1(��)--"��̬�����LED_Segment" 
			//Mode��"��"��ģ��("��̬�����LED_Segment" )
		Init_Mode_LED_Segment(MODE_Open_LED_Segment);
	}
	break;	

case WORK_LCD_Segment_Test: //Work��LCD_Segment_Test ����(����ʱ)
////////////////////////////////////////////////////////////////////////////
//==**��������(��Ӧ��IO�����)**=======================//
	if(F_500ms_LcdSeg)//"��ʽLCD_Segment"��ʾ"���"ʱ��
	{
		F_500ms_LcdSeg = 0;
		
			//"����""��ʽLCD_Segment": ͬʱ"ѭ��"��ʾ"��ͬ"�ַ�
		Disp_LCD_Segment(0,G_LcdSeg_Cnt,G_LcdSeg_Cnt,G_LcdSeg_Cnt,G_LcdSeg_Cnt,G_LcdSeg_Cnt,G_LcdSeg_Cnt);

		G_LcdSeg_Cnt ++;//"��ʽLCD_Segment"���õ��ļ�����(�����ַ�ѭ����ʾ)
		if(G_LcdSeg_Cnt >= DISP_MaxNum_LcdSeg) G_LcdSeg_Cnt = 0 ;  //22���ַ�(�������ʾ����)	
	}


////////////////////////////////////////////////////////////////////////////
//--**���󰴼� ����**-----------------------------------------------//
	if(Detect_MatrixKey_AC()) //"AC��"//
	{
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
			//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
		Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);
	}
	if(Detect_MatrixKey_Plus()) //"+ ��"//
	{
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
			//Mode��"��"����(��ʽLCD_Segment)		
		Init_Mode_LCD_Segment(MODE_OpenBackLight_LCD_Segment);
	}

	if(Detect_MatrixKey_Minus()) //"-��"//
	{
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
			//Mode��"�ر�"����(��ʽLCD_Segment)		
		Init_Mode_LCD_Segment(MODE_CloseBackLight_LCD_Segment);
	}
	if(Detect_MatrixKey_Equal()) //"=��"//
	{
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
			//Mode��������ʾ(��ʽLCD_Segment)
		Init_Mode_LCD_Segment(MODE_Refresh_LCD_Segment);
	}
	break;

case WORK_Buzzer_Test: //Work��Buzzer_Test ����(����ʱ)
	break;

case WORK_Speaker_Test: //Work��Speaker_Test ����(����ʱ)
	break;
	
case WORK_Microphone_Test: //Work��Microphone_Test ����(����ʱ)
	Mic_Record_Speaker_Play(); //��˷�¼����ͨ��DMA ����DACͨ������������
	break;

case WORK_BQ27410_Test: //Work��BQ27410_FuelGauge_Test ����(����ʱ)
////////////////////////////////////////////////////////////////////////////
//==**��������(��Ӧ��IO�����)**=======================//

	if(F_1s_BQ27410InTest) //ϵͳÿ1s ��ȡ"ʵʱBQ27410������ ����ֵ"
	{
		F_1s_BQ27410InTest = 0;
		F_En_Scan_MatrixKey = NO;  //��ֹɨ��"���󰴼�ɨ��"
		//_delay_us(50);
		//_delay_ms(50);
Sample_BQ27410_FuelGauge();  //BQ27410 ����﮵�صĵ���
		//_delay_ms(50);
		F_En_Scan_MatrixKey = YES;  //ʹ��"���󰴼�ɨ��"
	}

	Display_BQ27410_LCD_Segment();  //�ڶ�ʽLCD����ʾBQ27410 �����õ��ĵ���ֵ
	break;



////////////////////////////////////////////////////////////////////////////
//==**"��ز���" ( �����˵�)** ===========================//

case WORK_Line_LCD_TFT:  //Work��Line_LCD_TFT ����(����ʱ)
	break;


case WORK_Rectangle_LCD_TFT:  //Work��Rectangle_LCD_TFT ����(����ʱ)
	break;

case WORK_Circle_LCD_TFT:  //Work��Circle_LCD_TFT ����(����ʱ)
	break;

case WORK_FillArea_LCD_TFT:  //Work��FillArea_LCD_TFT ����(����ʱ)
	break;

case WORK_Chinese_LCD_TFT:  //Work��Chinese_LCD_TFT ����(����ʱ)
	break;
	
case WORK_Clear_LCD_TFT:  //Work��Clear_LCD_TFT ����(����ʱ)
	break;


////////////////////////////////////////////////////////////////////////////
//==**"��ز���" ( �����˵�)** ===========================//
case WORK_Idle_Step_Motor:      //Work��Idle_Step_Motor ����(����ʱ)
	Stop_Step_Motor();  //ͣת-"Step_Motor �������"
	break;

case WORK_Stop_Step_Motor:      //Work��Stop_DC_Motor ����(����ʱ)
	Stop_Step_Motor();  //ͣת-"Step_Motor �������"
	break;

case WORK_Positive_Step_Motor:  //Work��Positive_Step_Motor ����(����ʱ)
	break;
	
case WORK_Reverse_Step_Motor:   //Work��Reverse_Step_Motor ����(����ʱ)
	break;




////////////////////////////////////////////////////////////////////////////
//==**"��ز���" ( �����˵�)** ===========================//
case WORK_Idle_DC_Motor:      //Work��Idle_DC_Motor ����(����ʱ)
	Stop_DC_Motor();  //ͣת-"DC_Motor ֱ�����"
	G_DC_SpeedCnt = 0; //��Ƶ�ʼ����������²���
	
	if( !F_Timing_In_Work )  //��ʱ�����󣬵��ͣת����ʼ���л���
	{
		if(G_DC_WorkState == STATE_Positive_DC_Motor)
		{
			Initial_WorkState(WORK_Positive_DC_Motor); //װ��//Work��Positive_DC_Motor ����(����ʱ)
		}
		else if(G_DC_WorkState == STATE_Reverse_DC_Motor)		
		{
			Initial_WorkState(WORK_Reverse_DC_Motor); //װ��//Work��Reverse_DC_Motor ����(����ʱ)
		}
	}
	break;

case WORK_Stop_DC_Motor:      //Work��Stop_DC_Motor ����(����ʱ)
	Stop_DC_Motor();  //ͣת-"DC_Motor ֱ�����"
	G_DC_SpeedCnt = 0; //��Ƶ�ʼ����������²���
	break;

case WORK_Positive_DC_Motor:  //Work��Positive_DC_Motor ����(����ʱ)
	Positive_DC_Motor();  //��ת-"DC_Motor ֱ�����"(���ݵ�λ�Ƶ�ѹ���е���)
	break;
	
case WORK_Reverse_DC_Motor:   //Work��Reverse_DC_Motor ����(����ʱ)
	Reverse_DC_Motor();	//��ת-"DC_Motor ֱ�����"(���ݵ�λ�Ƶ�ѹ���е���)
	break;



////////////////////////////////////////////////////////////////////////////
//==**"��ز���" ( �����˵�)** ===========================//


////////////////////////////////////////////////////////////////////////////
//==**"��ز���" ( �����˵�)** ===========================//


////////////////////////////////////////////////////////////////////////////
//==**"��ز���" ( �����˵�)** ===========================//





////////////////////////////////////////////////////////////////////////////
default:
	break;
	}
}





/****************************************************************************
*������-Function:	void Deal_MAIN_DC_Motor_Test(void)
*����- Description:	//����//Main��DC_Motor_Test �˵�ѡ��(����ʱ) 
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
******************************************************
void Deal_MAIN_DC_Motor_Test(void) //����//Main��DC_Motor_Test �˵�ѡ��(����ʱ) 
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
//==**������λ��ADֵ,��Ϊת�ٸ���ֵ**================//
		//��β���"Potentiometer��λ��"ADֵ�������д���
	Deal_ADC12_A(M_Potentiometer_AdNum); // ����������: ����β���ֵ����������ȥ����ͷ�����м�ļ���ADֵ��ƽ�����õ�����ADֵ��


////////////////////////////////////////////////////////////////////////////
//==**���� ����**=======================================//


////////////////////////////////////////////////////////////////////////////
//--**���󰴼� ����**-----------------------------------------------//
	if(Detect_MatrixKey_1()) //"����1��"//1.Positive Rotation
	{
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
		
		if(G_DC_WorkState == STATE_Reverse_DC_Motor)
		{
			G_DC_WorkState = STATE_Positive_DC_Motor;
			Initial_WorkState(WORK_Idle_DC_Motor); //װ��//Work��Idle_DC_Motor ����(����ʱ)
		}
		else
		{
			G_DC_WorkState = STATE_Positive_DC_Motor;
			Initial_WorkState(WORK_Positive_DC_Motor); //װ��//Work��Positive_DC_Motor ����(����ʱ)
		}
	}

	if(Detect_MatrixKey_2()) //"����2��"//2.Reverse Rotation
	{
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
		
		if(G_DC_WorkState == STATE_Positive_DC_Motor)
		{
			G_DC_WorkState = STATE_Reverse_DC_Motor;
			Initial_WorkState(WORK_Idle_DC_Motor); //װ��//Work��Idle_DC_Motor ����(����ʱ)
		}
		else 
		{
			G_DC_WorkState = STATE_Reverse_DC_Motor;
			Initial_WorkState(WORK_Reverse_DC_Motor); //װ��//Work��Reverse_DC_Motor ����(����ʱ)
		}
	}

	if(Detect_MatrixKey_3()) //"����3��"//3.Stop DC-Moter
	{
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
		G_DC_WorkState = STATE_Stop_DC_Motor;
		Initial_WorkState(WORK_Stop_DC_Motor); //װ��//Work��Stop_DC_Motor ����(����ʱ)
	}


////////////////////////////////////////////////////////////////////////////
//==**��ʾ����**========================================//
	if(F_500ms_Reflash_DC_Motor)  //500ms ˢ��"ת��" ("DC_Motor ֱ�����")
	{
		F_500ms_Reflash_DC_Motor = 0;

		speed = G_DC_Speed / 3;  // ��ת������ת��"ʵ��ת��ֵ"r/s��λ

////////////////////////////////////////////////////////////////////////////
//--**��ʾ����:  "����LCD_TFT" **------------------------------------//
			//��"���Ե��"��ʾ�ٶȸ�����ѹֵ: ��λ��Potentiometer ʵʱ"��ѹֵ"
		Disp_Potentiometer_Motor();

		Disp_Speed_DC_Motor();//��"����DC_Motor"��ʾ����ٶ�

////////////////////////////////////////////////////////////////////////////
//--**��ʾ����:  "��̬�����LED_Segment"**-----------------------//
	//��λ����ʾ���
		a = (unsigned char)(G_LastAdResult/1000);
		b = (unsigned char)((G_LastAdResult % 1000)/100);
		c = (unsigned char)(G_LastAdResult % 100)/10;
		if(G_LastAdResult < 30) c = 0; //�ڵ�λ��������Сֵʱ����ʾ��ѹ����0.01,0.02,.000֮����ʾ�����������������ڵ�λ��������Сֵʱ����ʾ0.00

	//ת����ʾ���
		if(G_DC_WorkState  == STATE_Positive_DC_Motor)  //��ת��ʾ����
		{
			s4 = (unsigned char)(speed/1000);
			s3 = (unsigned char)((speed % 1000)/100);
			s2 = (unsigned char)(speed % 100)/10;
			s1 = (unsigned char)(speed % 10);
			if((s4 == 0)&&(s3 == 0)&&(s2 == 0)) s2 = DISP_OFF_LedSeg;	
			if((s4 == 0)&&(s3 == 0)) s3 = DISP_OFF_LedSeg;
			if(s4 == 0) s4 = DISP_OFF_LedSeg; //��ʾ"����"(����ʾ0)
		}
		else if(G_DC_WorkState  == STATE_Reverse_DC_Motor) //��ת��ʾ����
		{
			s4 = (unsigned char)(speed/1000);
			s3 = (unsigned char)((speed % 1000)/100);
			s2 = (unsigned char)(speed % 100)/10;
			s1 = (unsigned char)(speed % 10);
			if((s4 == 0)&&(s3 == 0)&&(s2 == 0))
			{
			 	s4 = DISP_OFF_LedSeg;//��ʾ"����"(����ʾ0)
				s3 = DISP_OFF_LedSeg;//��ʾ"����"(����ʾ0)
				s2 = DISP_Minus_LedSeg; //��ʾ"����"(����ʾ0)
			}
			if((s4 == 0)&&(s3 == 0))
			{
			 	s4 = DISP_OFF_LedSeg;//��ʾ"����"(����ʾ0)
				s3 = DISP_Minus_LedSeg; //��ʾ"����"(����ʾ0)
			}
			if(s4 == 0) s4 = DISP_Minus_LedSeg; //��ʾ"����"(����ʾ0)			
		}
		Disp_LED_Segment(0,8,a,b,c,DISP_OFF_LedSeg,s4,s3,s2,s1);
	}

////////////////////////////////////////////////////////////////////////////
//--**IO���� ����**---------------------------------------------------//
	Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"

}
***********************/




/****************************************************************************
*������-Function:	void Deal_MAIN_Step_Motor_Test(void)
*����- Description:	//����//Main��Step_Motor_Test �˵�ѡ��(����ʱ) 
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
******************************************************
void Deal_MAIN_Step_Motor_Test(void) //����//Main��Step_Motor_Test �˵�ѡ��(����ʱ) 
{
	unsigned char a = 0;
	unsigned char b = 0;
	unsigned char c = 0;
	
	unsigned char s1 = 0;
	unsigned char s2 = 0;
	unsigned char s3 = 0;
	unsigned char s4 = 0;


////////////////////////////////////////////////////////////////////////////
//==**������λ��ADֵ,��Ϊת�ٸ���ֵ**================//
		//��β���"Potentiometer��λ��"ADֵ�������д���
	Deal_ADC12_A(M_Potentiometer_AdNum); // ����������: ����β���ֵ����������ȥ����ͷ�����м�ļ���ADֵ��ƽ�����õ�����ADֵ��


////////////////////////////////////////////////////////////////////////////
//==**���� ����**=======================================//

////////////////////////////////////////////////////////////////////////////
//--**���󰴼� ����**-----------------------------------------------//
	if(Detect_MatrixKey_1()) //"����1��"//1.Positive Rotation
	{
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
		
		if(G_Step_WorkState != STATE_Positive_Step_Motor)
		{
			G_Step_WorkState = STATE_Positive_Step_Motor;
			Initial_WorkState(WORK_Positive_Step_Motor); //װ��//Work��Positive_Step_Motor ����(����ʱ)
		}
	}

	if(Detect_MatrixKey_2()) //"����2��"//2.Reverse Rotation
	{
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
		
		if(G_Step_WorkState != STATE_Reverse_Step_Motor)
		{
			G_Step_WorkState = STATE_Reverse_Step_Motor;
			Initial_WorkState(WORK_Reverse_Step_Motor); //װ��//Work��Reverse_Step_Motor ����(����ʱ)
		}
	}

	if(Detect_MatrixKey_3()) //"����3��"//3.Stop Step-Moter
	{
		Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
		
		G_Step_WorkState = STATE_Stop_Step_Motor;
		Initial_WorkState(WORK_Stop_Step_Motor); //װ��//Work��Stop_Step_Motor ����(����ʱ)
	}


////////////////////////////////////////////////////////////////////////////
//==**��ʾ����**========================================//


	if(F_500ms_Reflash_Step_Motor)  //500ms ˢ��"ת��" --"Step_Motor �������"
	{
		F_500ms_Reflash_Step_Motor = 0;


		Deal_Speed_Step_Motor(); // ���㲽����ת��

////////////////////////////////////////////////////////////////////////////
//--**��ʾ����:  "����LCD_TFT" **------------------------------------//
			//��"���Ե��"��ʾ�ٶȸ�����ѹֵ: ��λ��Potentiometer ʵʱ"��ѹֵ"
		Disp_Potentiometer_Motor();

		Disp_Speed_Step_Motor(); //��"����Step_Motor"��ʾ����ٶ�

////////////////////////////////////////////////////////////////////////////
//--**��ʾ����:  "��̬�����LED_Segment"**-----------------------//
	//��λ����ʾ���
		a = (unsigned char)(G_LastAdResult/1000);
		b = (unsigned char)((G_LastAdResult % 1000)/100);
		c = (unsigned char)(G_LastAdResult % 100)/10;
		if(G_LastAdResult < 30) c = 0; //�ڵ�λ��������Сֵʱ����ʾ��ѹ����0.01,0.02,.000֮����ʾ�����������������ڵ�λ��������Сֵʱ����ʾ0.00

	//ת����ʾ���
		s3 = (unsigned char)((G_Step_Speed % 1000)/100);
		s2 = (unsigned char)(G_Step_Speed % 100)/10;
		s1 = (unsigned char)(G_Step_Speed % 10);

		if(G_Step_WorkState  == STATE_Reverse_Step_Motor) //��ת��ʾ����
		{
			s4 = DISP_Minus_LedSeg; //��ʾ"����"(����ʾ0)		
		}
		else s4 = DISP_OFF_LedSeg;
		
		Disp_LED_Segment(8,3,a,b,c,DISP_OFF_LedSeg,s4,s3,s2,s1);
	}


////////////////////////////////////////////////////////////////////////////
//--**IO���� ����**---------------------------------------------------//
	Detect_Key_WorkMenu(); //��"Key1","Key2"����ѡ��"�����˵�"

}
***********************/



