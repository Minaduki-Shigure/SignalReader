/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 MyPrimacy_Initial_State.c
* �����ļ�-Dependencies:  	 System_HeadFile.h; 	
* �ļ�����-File Description:	 ( Դ����-Source File) 
	�� ������Ŀ: "��ʹ��" ��"ϵͳ״̬" (״̬��)
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



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////



/****************************************************************************
*������-Function:	void Initial_MainState(unsigned int MainMode)
*����- Description:	"��ʹ��" ��"ϵͳ״̬Main��" (״̬��)
						01)����ϵͳ״ֵ̬��02)�����ʾ���ݳ�ʹ����
						03)��ر�����ʼ��
*�������-Input:	MainMode: ϵͳ״ֵ̬
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Initial_MainState(unsigned int MainMode)
{
	G_Last_MainState = G_MainState;  //����"��һ��"ϵͳ״ֵ̬
	G_MainState = MainMode;



	switch(MainMode) 
	{
////////////////////////////////////////////////////////////////////////////
//==**����\����״ֵ̬: 0x00--0xFF **=======================//
////////////////////////////////////////////////////////////////////////////


case MAIN_Restart:  //Main�� ��������ϵͳ�Լ�--Restart Self-Test     
	Open_Buzzer(BuzzTime_Key);	//������Чʱ���÷�����ָ��ʱ��
	WaitingDelayMs(BuzzTime_Key*10);
	mReset_Soft;   //"�����λ"
	break;

case MAIN_Self_Check:  //Main��ϵͳ�Լ�״̬
//--**��������(��Ӧ��IO�����)**------------------------------//
	mOpen_LED_YELLOW;  //��������Ϊ"���",��"����"LED_YELLOW
	mOpen_LED_GREEN;   //��������Ϊ"���",��"����"LED_GREEN
	mOpen_LED_RED;     //��������Ϊ"���",��"����"LED_RED

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
LCD_TFT_Show_StandbyPage(); //��ʾ"����ҳ��"-"����LCD_TFT_ILI9325"	


//--**����µ�"�����LED"��ʾ����**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //����Ϊ1(��)--"��̬�����LED_Segment" 
		//������ʾ�ַ�: //DISP��"ȫ��"--"��̬�����LED_Segment" 
		//"��ʾ�ַ�"���µ�"��ʾ��������"("��̬�����LED_Segment" )
	Disp_LED_Segment(0,0,DISP_ON_LedSeg,DISP_ON_LedSeg,DISP_ON_LedSeg,DISP_ON_LedSeg,DISP_ON_LedSeg,DISP_ON_LedSeg,DISP_ON_LedSeg,DISP_ON_LedSeg);
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);
	

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
		//������ʾ�ַ�: //DISP��"ȫ��"--"��ʽLCD_Segment" //"��ʾ�ַ�"���µ�"��ʾ��������"(��ʽLCD_Segment)
	Disp_LCD_Segment(0,DISP_ON_LcdSeg,DISP_ON_LcdSeg,DISP_ON_LcdSeg,DISP_ON_LcdSeg,DISP_ON_LcdSeg,DISP_ON_LcdSeg);
		//Mode��"��"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Open_LCD_Segment);


//--**"��־λ+����"����س�ʹ��**---------------------------//
Open_Buzz_Speaker(M_Self_Check_Time);  //�򿪷�����(Speaker ������)�Ķ�ʱ��
Enable_AlarmBuzzer(M_Buzz200ms);	//��:����������(��ָ����������)(��10msΪʱ�䵥λ)

	//F_SecondChange = 1; 	//һ�ϵ�򷵻ش���״̬������������ʾʱ��,����Ҫ��1s���ˢ��ʱ��
	Open_Timing_Task(M_Self_Check_Time);//��ϵͳ��ʱ����ʱ������ʱ��ֵ(�ж���)
	Initial_WorkState(WORK_Test_IdleState); //װ��//Work��"����ʱ"�Ŀ���״̬(����ʱ)
	break;


////////////////////////////////////////////////////////////////////////////
//==**���˵�״ֵ̬: 0x100--0x1FF **=========================//
////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	//--**��������: "ʱ���޸�"�˵�0x200--0x21F **-------------------//
	////////////////////////////////////////////////////////////////////////////
case MAIN_ModifyTime:  //Main��"ʵʱʱ��"�޸�״̬
//--**��������(��Ӧ��IO�����)**------------------------------//
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	
//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_ModifyTime();//��ʾ//Main��"ʵʱʱ��"�޸�״̬
	
//--**����µ�"�����LED"��ʾ����**-------------------------//
//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//

//--**"��־λ+����"����س�ʹ��**---------------------------//
		//Ҫ��15������ֵ:��(4��)+��(2��)+��(2��)+ʱ(2��)+��(2��)+��(2��)+����(1��)
	G_TotalKeyNum = 15;	//��������ְ����ܸ���	
	G_MatrixKeyCnt = 0;  //�尴������ָ��

	G_MatrixKeyBuf[0]  = (unsigned char)(RTCYEAR >> 12);  //��"ǧλ"(��)(ASSII��)
	G_MatrixKeyBuf[1]  = (unsigned char)((RTCYEAR >> 8) & 0x000F); 	//��"��λ"(��)(ASSII��)
	G_MatrixKeyBuf[2]  = (unsigned char)((RTCYEAR >> 4) & 0x000F); //��"ʮλ"(��)(ASSII��)
	G_MatrixKeyBuf[3]  = (unsigned char)(RTCYEAR & 0x000F); 	//��"��λ"(��)(ASSII��)

	G_MatrixKeyBuf[4]  = RTCMON >> 4;  //��"ʮλ"(��)
	G_MatrixKeyBuf[5]  = RTCMON & 0x0F; //��"��λ"(��)
	
	G_MatrixKeyBuf[6]  = RTCDAY >> 4; //��"ʮλ"(��)
	G_MatrixKeyBuf[7]  = RTCDAY & 0x0F; //��"��λ"(��)
	
	G_MatrixKeyBuf[8]  = RTCHOUR >> 4;  //��"ʮλ"(Сʱ)
	G_MatrixKeyBuf[9]  = RTCHOUR & 0x0F; //��"��λ"(Сʱ)
	
	G_MatrixKeyBuf[10] = RTCMIN >> 4;  //��"ʮλ"(����)
	G_MatrixKeyBuf[11] = RTCMIN & 0x0F;  //��"��λ"(����)
	
	G_MatrixKeyBuf[12] = RTCSEC >> 4;  //��"ʮλ"(��)
	G_MatrixKeyBuf[13] = RTCSEC & 0x0F;  //��"��λ"(��)
	
	G_MatrixKeyBuf[14] = RTCDOW;  //��""(����)


	G_KeyPlace_Row = TestLine08;	  //(��)�������ò���λ��(���)��ʼλ��
	G_KeyPlace_Column = TestColumn03; //(��)�������ò���λ��(���)��ʼλ��

	Initial_WorkState(WORK_Test_IdleState); //װ��//Work��"����ʱ"�Ŀ���״̬(����ʱ)
	break;


////////////////////////////////////////////////////////////////////////////
//==**����"�˵�"״ֵ̬: 0x7000--0x7FFF**====================//
////////////////////////////////////////////////////////////////////////////

case MAIN_Working_State: //Main�����빤��״̬(����ʱ)
	
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW;  //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_GREEN;   //��������Ϊ"���",��"Ϩ��"LED_GREEN
	mClose_LED_RED;	   //��������Ϊ"���",��"Ϩ��"LED_RED

	Disable_AlarmBuzzer();	//�ر�:����������
	Disable_Speaker(); //��ֹ:	"Speaker ������" 
	
//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
	Disp_LCD_Segment(0,DISP_OFF_LcdSeg,DISP_OFF_LcdSeg,DISP_OFF_LcdSeg,DISP_OFF_LcdSeg,DISP_OFF_LcdSeg,DISP_OFF_LcdSeg);
	Refresh_LCD_Segment(G_LcdSegBuf[6],G_LcdSegBuf[5],G_LcdSegBuf[4],G_LcdSegBuf[3],G_LcdSegBuf[2],G_LcdSegBuf[1],G_LcdSegBuf[0]); 
		//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);
	Close_LCD_Segment();  //�ر�"��ʽLCD_Segment"


//--**����µ�"�����LED"��ʾ����**-------------------------//
		//����Ϊ0 (��ʾ��)--"��̬�����LED_Segment" 
	G_Brightness_LedSeg = M_Brightness_OFF_LedSeg;
		//����ʾ��������
	Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
	Refresh_LED_Segment(); //������ʾ("��̬�����LED_Segment" )
		//Mode��"�ر�"��ģ��("��̬�����LED_Segment" )	
	Init_Mode_LED_Segment(MODE_Close_LED_Segment);


//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	LCD_TFT_Show_WorkPage(); //��ʾ"����ҳ��"-"����LCD_TFT_ILI9325"  
	

//--**"��־λ+����"����س�ʹ��**---------------------------//
	F_Update_RealTime = YES;	//һ�ϵ�򷵻ش���״̬������������ʾʱ��,����Ҫ��1s���ˢ��ʱ��
	F_Update_Temperature = YES;
	F_Update_CurrentValue = YES;
	F_Update_Power = YES;
	
	G_KeyCnt = 1;  //��"01.xxx"�˵�����ʼ
	
	Initial_MainState(MAIN_Basic_Settings); //װ��//Main��Basic_Settings�˵�ѡ��(����ʱ)
	Initial_WorkState(WORK_Test_IdleState); //װ��//Work��"����ʱ"�Ŀ���״̬(����ʱ)
	break;

case MAIN_Basic_Settings:  //Main��Basic_Settings�˵�ѡ��(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	Disable_AlarmBuzzer();	//�ر�:����������
	Disable_Speaker();      //��ֹ: "Speaker ������" 

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_01Page_MenuLine();  //��ʾ��1ҳ"�����˵�"(LCD)(1.Work_A  2.Work_B	3.Work_C  4.Work_D

	Disp_MAIN_Basic_Settings();  //��ʾ//Main��Basic_Settings �˵�ѡ��(����ʱ)
		//--care--��ʾ: ѡ�б�־���ڴ˳������
	Disp_SelectFlag(); //��ʾ"ѡ�б�־" 

//--**����µ�"�����LED"��ʾ����**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //����Ϊ1(��)--"��̬�����LED_Segment" 
		//������ʾ�ַ�://DISP��"����"--"��̬�����LED_Segment" 
		//"��ʾ�ַ�"���µ�"��ʾ��������"("��̬�����LED_Segment" )
	Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);


//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
		//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);


//--**"��־λ+����"����س�ʹ��**---------------------------//
	Initial_WorkState(WORK_Test_IdleState); //װ��//Work��"����ʱ"�Ŀ���״̬(����ʱ)
		//��ΪSD������ز���ʱ���޸��˾��񣬹��������³�ʹ��,��ԭ֮ǰ�ľ�������
//Osccon_Initial();//�����ʼ������:������ؾ������
	
	break;


case MAIN_Basic_Check:  //Main��Basic_Check �˵�ѡ��(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	Disable_AlarmBuzzer();	//�ر�:����������
	Disable_Speaker();      //��ֹ: "Speaker ������" 

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	//Disp_01Page_MenuLine();  //��ʾ��1ҳ"�����˵�"(LCD)(1.Work_A  2.Work_B	3.Work_C  4.Work_D
	Disp_MAIN_Basic_Check();  //��ʾ//Main��Basic_Check �˵�ѡ��(����ʱ)
		//--care--��ʾ: ѡ�б�־���ڴ˳������
	Disp_SelectFlag(); //��ʾ"ѡ�б�־" 

//--**����µ�"�����LED"��ʾ����**-------------------------//
		//Mode��"�ر�"��ģ��("��̬�����LED_Segment" )	
	Init_Mode_LED_Segment(MODE_Close_LED_Segment);

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
		//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	Initial_WorkState(WORK_Test_IdleState); //װ��//Work��"����ʱ"�Ŀ���״̬(����ʱ)
	break;


case MAIN_LCD_TFT_Test: //Main��LCD_TFT_Test �˵�ѡ��(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	Disable_AlarmBuzzer();	//�ر�:����������
	Disable_Speaker(); //��ֹ:	"Speaker ������" 

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_LCD_TFT_Test();  //��ʾ//Main��LCD_TFT_Test �˵�ѡ��(����ʱ)
	mUpdate_All_TestLine;  //ˢ������" ������"
	
		//--care--��ʾ: ѡ�б�־���ڴ˳������
	Disp_SelectFlag(); //��ʾ"ѡ�б�־"

//--**����µ�"�����LED"��ʾ����**-------------------------//
		//Mode��"�ر�"��ģ��("��̬�����LED_Segment" )	
	Init_Mode_LED_Segment(MODE_Close_LED_Segment);

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
		//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	Initial_WorkState(WORK_Test_IdleState); //װ��//Work��"����ʱ"�Ŀ���״̬(����ʱ)
	break;

case MAIN_MatrixKey_Test:  //Main��MatrixKey_Test �˵�ѡ��(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	
//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_MatrixKey_Test();  //��ʾ//Main��MatrixKey_Test �˵�ѡ��(����ʱ)
		//--care--��ʾ: ѡ�б�־���ڴ˳������
	Disp_SelectFlag(); //��ʾ"ѡ�б�־" "=>"

//--**����µ�"�����LED"��ʾ����**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //����Ϊ1(��)--"��̬�����LED_Segment" 
		//������ʾ�ַ�://DISP��"����"--"��̬�����LED_Segment" 
		//"��ʾ�ַ�"���µ�"��ʾ��������"("��̬�����LED_Segment" )
	Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);

		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);


//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
			//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	Initial_WorkState(WORK_Test_IdleState); //װ��//Work��"����ʱ"�Ŀ���״̬(����ʱ)
	break;

case MAIN_TouchPads_Test:  //Main��TouchPads_Test �˵�ѡ��(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_TouchPads_Test();  //��ʾ//Main��TouchPads_Test �˵�ѡ��(����ʱ)
		//--care--��ʾ: ѡ�б�־���ڴ˳������
	Disp_SelectFlag(); //��ʾ"ѡ�б�־" "=>"

//--**����µ�"�����LED"��ʾ����**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //����Ϊ1(��)--"��̬�����LED_Segment" 
		//������ʾ�ַ�://DISP��"����"--"��̬�����LED_Segment" 
	Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
			//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	F_En_Scan_MatrixKey = NO;  //��ֹɨ��"���󰴼�ɨ��"
	Initial_Touch_Pad();  //��ʼ������: "Touch_Pads ���ݰ���" 
	F_En_Scan_MatrixKey = YES;	//�����ж���ɨ��"���󰴼�ɨ��"

	Initial_WorkState(WORK_Test_IdleState); //װ��//Work��"����ʱ"�Ŀ���״̬(����ʱ)
	break;

case MAIN_INA21x_Current_Test:  //Main��INA21x_Current_Test �˵�ѡ��(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_INA21x_Current_Test();  //��ʾ//Main��INA21x_Current_Test �˵�ѡ��(����ʱ)
		//--care--��ʾ: ѡ�б�־���ڴ˳������
	Disp_SelectFlag(); //��ʾ"ѡ�б�־" "=>"

//--**����µ�"�����LED"��ʾ����**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //����Ϊ1(��)--"��̬�����LED_Segment" 
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

	
//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
			//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	ADC12_A_Initial(); //ADC12_A	�ڲ���Դ��ʼ��
	Initial_WorkState(WORK_Test_IdleState); //װ��//Work��"����ʱ"�Ŀ���״̬(����ʱ)
	break;

case MAIN_TMP006_Temperature:  //Main��TMP006_Temperature �˵�ѡ��(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_TMP006_Temperature();  //��ʾ//Main��TMP006_Temperature �˵�ѡ��(����ʱ)
		//--care--��ʾ: ѡ�б�־���ڴ˳������
	Disp_SelectFlag(); //��ʾ"ѡ�б�־" "=>"

//--**����µ�"�����LED"��ʾ����**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //����Ϊ1(��)--"��̬�����LED_Segment" 
		//"��ʾ�ַ�"���µ�"��ʾ��������"("��̬�����LED_Segment" )
	Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
		//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);


//--**"��־λ+����"����س�ʹ��**---------------------------//
	Initial_WorkState(WORK_Test_IdleState); //װ��//Work��"����ʱ"�Ŀ���״̬(����ʱ)
	break;

case MAIN_TMP100_Temperature:  //Main��TMP100_Temperature �˵�ѡ��(����ʱ)
	break;

case MAIN_Potentiometer_Test:  //Main��Potentiometer_Test �˵�ѡ��(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_Potentiometer_Test();  //��ʾ//Main��Potentiometer_Test �˵�ѡ��(����ʱ)
		//--care--��ʾ: ѡ�б�־���ڴ˳������
	Disp_SelectFlag(); //��ʾ"ѡ�б�־" "=>"

//--**����µ�"�����LED"��ʾ����**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //����Ϊ1(��)--"��̬�����LED_Segment" 
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

	
//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
			//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	ADC12_A_Initial(); //ADC12_A  �ڲ���Դ��ʼ��
	Disable_Step_Motor(); //��ֹ-"Step_Motor �������"
	Disable_DC_Motor();  //��ֹ-"DC_Motor ֱ�����"
	Initial_WorkState(WORK_Test_IdleState); //װ��//Work��"����ʱ"�Ŀ���״̬(����ʱ)
	break;
	
	
case MAIN_DC_Motor_Test:  //Main��DC_Motor_Test �˵�ѡ��(����ʱ) 
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);	//������Чʱ���÷�����ָ��ʱ��
	
//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_DC_Motor_Test();	//��ʾ//Main��DC_Motor_Test �˵�ѡ��(����ʱ) 
	mUpdate_All_TestLine;  //ˢ������" ������"
	
		//--care--��ʾ: ѡ�б�־���ڴ˳������
	Disp_SelectFlag(); //��ʾ"ѡ�б�־" "=>"

//--**����µ�"�����LED"��ʾ����**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //����Ϊ1(��)--"��̬�����LED_Segment" 
		//"��ʾ�ַ�"���µ�"��ʾ��������"("��̬�����LED_Segment" )
	Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
		//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	Disable_Step_Motor();  //��ֹ-"Step_Motor �������"

	DC_Motor_Initial();  //��ʼ������:	"DC_Motor ֱ�����"
	G_DC_WorkState = STATE_Idle_DC_Motor;
	Initial_WorkState(WORK_Idle_DC_Motor); //װ��//Work��Idle_DC_Motor ����(����ʱ)
	break;


case MAIN_Step_Motor_Test:  //Main��Step_Motor_Test �˵�ѡ��(����ʱ) 
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_Step_Motor_Test();  //��ʾ//Main��Step_Motor_Test �˵�ѡ��(����ʱ) 
	mUpdate_All_TestLine;  //ˢ������" ������"

		//--care--��ʾ: ѡ�б�־���ڴ˳������
	Disp_SelectFlag(); //��ʾ"ѡ�б�־" "=>"

//--**����µ�"�����LED"��ʾ����**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //����Ϊ1(��)--"��̬�����LED_Segment" 
		//"��ʾ�ַ�"���µ�"��ʾ��������"("��̬�����LED_Segment" )
	Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
			//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	Disable_DC_Motor();  //��ֹ-"DC_Motor ֱ�����"

	Step_Motor_Initial();  //��ʼ������:  "Step_Motor �������"
	G_Step_WorkState = STATE_Idle_Step_Motor;
	Initial_WorkState(WORK_Idle_Step_Motor); //װ��//Work��Idle_Step_Motor ����(����ʱ)
	break;


case MAIN_NTC_HR202_Test:  //Main��NTC_HR202_Test(��ʪ��) �˵�ѡ��(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_01Page_MenuLine();  //��ʾ��1ҳ"�����˵�"(LCD)(1.Work_A  2.Work_B	3.Work_C  4.Work_D

	Disp_MAIN_NTC_HR202_Test();  //��ʾ//Main��NTC_HR202_Test(��ʪ��) �˵�ѡ��(����ʱ)
		//--care--��ʾ: ѡ�б�־���ڴ˳������
	Disp_SelectFlag(); //��ʾ"ѡ�б�־" "=>"

//--**����µ�"�����LED"��ʾ����**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //����Ϊ1(��)--"��̬�����LED_Segment" 
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

	
//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
			//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	Disable_Step_Motor(); //��ֹ-"Step_Motor �������"
	Disable_DC_Motor();  //��ֹ-"DC_Motor ֱ�����"
	Disable_UART_A(); //����UART_A ģ��
	
	HR202_Humidity_Initial();  //��ʼ������:  "HR202_Humidity ������ʪ�ȴ�����"

	Initial_WorkState(WORK_Test_IdleState); //װ��//Work��"����ʱ"�Ŀ���״̬(����ʱ)
	break;


case MAIN_IrDA_UART:  //Main��IrDA_UART �˵�ѡ��(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	Disable_Step_Motor(); //��ֹ-"Step_Motor �������"
	Disable_DC_Motor();  //��ֹ-"DC_Motor ֱ�����"

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_02Page_MenuLine();  //��ʾ��2ҳ"�����˵�"(LCD)(1.Work_A  2.Work_B	3.Work_C  4.Work_D
	Disp_MAIN_IrDA_UART();  //��ʾ//Main��IrDA_UART �˵�ѡ��(����ʱ)

		//--care--��ʾ: ѡ�б�־���ڴ˳������
	Disp_SelectFlag(); //��ʾ"ѡ�б�־" "=>"

//--**����µ�"�����LED"��ʾ����**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //����Ϊ1(��)--"��̬�����LED_Segment" 
		//"��ʾ�ַ�"���µ�"��ʾ��������"("��̬�����LED_Segment" )
	Disp_LED_Segment(0,0,DISP_I_LedSeg,DISP_r_LedSeg,DISP_d_LedSeg,DISP_A_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

	
//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
		//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	Initial_WorkState(WORK_Test_IdleState); //װ��//Work��"����ʱ"�Ŀ���״̬(����ʱ)
	break;


case MAIN_RS232_UART:  //Main��RS232_UART �˵�ѡ��(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_RS232_UART();  //��ʾ//Main��RS232_UART �˵�ѡ��(����ʱ)

		//--care--��ʾ: ѡ�б�־���ڴ˳������
	Disp_SelectFlag(); //��ʾ"ѡ�б�־" "=>"

//--**����µ�"�����LED"��ʾ����**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //����Ϊ1(��)--"��̬�����LED_Segment" 
		//"��ʾ�ַ�"���µ�"��ʾ��������"("��̬�����LED_Segment" )
	Disp_LED_Segment(0,0,DISP_2_LedSeg,DISP_3_LedSeg,DISP_2_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

	
//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
		//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	Initial_WorkState(WORK_Test_IdleState); //װ��//Work��"����ʱ"�Ŀ���״̬(����ʱ)
	break;



case MAIN_RS485_UART:  //Main��RS485_UART �˵�ѡ��(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	
//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_RS485_UART();  //��ʾ//Main��RS485_UART �˵�ѡ��(����ʱ)

		//--care--��ʾ: ѡ�б�־���ڴ˳������
	Disp_SelectFlag(); //��ʾ"ѡ�б�־" "=>"

//--**����µ�"�����LED"��ʾ����**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //����Ϊ1(��)--"��̬�����LED_Segment" 
		//"��ʾ�ַ�"���µ�"��ʾ��������"("��̬�����LED_Segment" )
	Disp_LED_Segment(0,0,DISP_4_LedSeg,DISP_8_LedSeg,DISP_5_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

	
//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
		//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	Initial_WorkState(WORK_Test_IdleState); //װ��//Work��"����ʱ"�Ŀ���״̬(����ʱ)
	break;


case MAIN_CC1101_Test:  //Main��CC1101_Test �˵�ѡ��(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_CC1101_Test();  //��ʾ//Main��CC1101_Test �˵�ѡ��(����ʱ)

		//--care--��ʾ: ѡ�б�־���ڴ˳������
	Disp_SelectFlag(); //��ʾ"ѡ�б�־" "=>"

//--**����µ�"�����LED"��ʾ����**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //����Ϊ1(��)--"��̬�����LED_Segment" 
		//"��ʾ�ַ�"���µ�"��ʾ��������"("��̬�����LED_Segment" )
	Disp_LED_Segment(0,0,DISP_C_LedSeg,DISP_C_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_0_LedSeg,DISP_1_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

	
//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
		//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	Initial_WorkState(WORK_Test_IdleState); //װ��//Work��"����ʱ"�Ŀ���״̬(����ʱ)
	Disable_UART_A(); //����UART_A ģ��
	
	//G_Update_03Bits = 0;
		//��ΪSD������ز���ʱ���޸��˾��񣬹��������³�ʹ��,��ԭ֮ǰ�ľ�������
	//Osccon_Initial();//�����ʼ������:������ؾ������
	//G_Update_03Bits = 0;
	break;


case MAIN_SD_Card_Test:  //Main��SD_Card_Test �˵�ѡ��(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	
//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_SD_Card_Test();  //��ʾ//Main��SD_Card_Test �˵�ѡ��(����ʱ)

		//--care--��ʾ: ѡ�б�־���ڴ˳������
	Disp_SelectFlag(); //��ʾ"ѡ�б�־" "=>"

//--**����µ�"�����LED"��ʾ����**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //����Ϊ1(��)--"��̬�����LED_Segment" 
		//"��ʾ�ַ�"���µ�"��ʾ��������"("��̬�����LED_Segment" )
	Disp_LED_Segment(0,0,DISP_5_LedSeg,DISP_d_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

	
//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
		//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	SD_Cnt = 0; //SD�����ݻ�������ָ��   
//SD_Num = 0;
	SD_Num = 0;
	SD_Write_Num = 0;

	Initial_WorkState(WORK_Test_IdleState); //װ��//Work��"����ʱ"�Ŀ���״̬(����ʱ)
	break;



case MAIN_MassStorage_Test:  //Main��MassStorage_Test �˵�ѡ��(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	
//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_02Page_MenuLine();  //��ʾ��2ҳ"�����˵�"(LCD)(1.Work_A  2.Work_B	3.Work_C  4.Work_D
	Disp_MAIN_MassStorage_Test();  //��ʾ//Main��MassStorage_Test �˵�ѡ��(����ʱ)

		//--care--��ʾ: ѡ�б�־���ڴ˳������
	Disp_SelectFlag(); //��ʾ"ѡ�б�־" "=>"

//--**����µ�"�����LED"��ʾ����**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //����Ϊ1(��)--"��̬�����LED_Segment" 
		//"��ʾ�ַ�"���µ�"��ʾ��������"("��̬�����LED_Segment" )
	Disp_LED_Segment(0,0,DISP_U_LedSeg,DISP_5_LedSeg,DISP_b_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_0_LedSeg);
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
		//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	
	//Osccon_Initial();
	//G_Update_03Bits = 0;
	Initial_WorkState(WORK_Test_IdleState); //װ��//Work��"����ʱ"�Ŀ���״̬(����ʱ)
	break;


case MAIN_MassStorage_USB:  //Main��MassStorage_USB �˵�ѡ��(����ʱ)
	Disp_LED_Segment(0,0,DISP_U_LedSeg,DISP_5_LedSeg,DISP_b_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_1_LedSeg);
	// û��ʲô�ɳ�ʹ������Ϊ��MAIN_MassStorage_Test  ��ʹ������
	//G_Update_03Bits = 0;
	break;




////////////////////////////////////////////////////////////////////////////
default:
	break;
	}
	
}

/***************************************************************************
case :  //Main��
//--**��������(��Ӧ��IO�����)**------------------------------//

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
//--**����µ�"�����LED"��ʾ����**-------------------------//
//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//

//--**"��־λ+����"����س�ʹ��**---------------------------//

	break;

*************************************************************************/





/****************************************************************************
*������-Function:	void Initial_WorkState(unsigned int WorkMode)
*����- Description:	��ʼ��"������״̬Work��"
*�������-Input:	WorkMode: ϵͳ״ֵ̬(������)
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Initial_WorkState(unsigned int WorkMode) //����״̬��ʼ��
{
	G_Last_WorkState = G_WorkState;  //����"��һ��"ϵͳ״ֵ̬
	G_WorkState = WorkMode;


////////////////////////////////////////////////////////////////////////////
//==**��������: **0x8000--0x8FFF** ===========================//
////////////////////////////////////////////////////////////////////////////
	switch(WorkMode) 
	{
	
////////////////////////////////////////////////////////////////////////////
//==**"����ʱ"�Ŀ���״̬** ============================//

case WORK_Test_IdleState: //Work��"����ʱ"�Ŀ���״̬(����ʱ)
	break;

////////////////////////////////////////////////////////////////////////////
//==**"��ز���" ( �����˵�)** ===========================//
case WORK_Self_Check: //Work��Self_Check ����(����ʱ)
	//mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	//mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	
	//Disable_AlarmBuzzer();	//�ر�:����������
	//Disable_Speaker(); //��ֹ:	"Speaker ������" 

	//Initial_MainState(MAIN_Self_Check); //װ��//Main��ϵͳ�Լ�״̬ 
	break;
	
case WORK_Led_Diode_Test:  //Work��Led_Diode_Test ����(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	Disable_AlarmBuzzer();	//�ر�:����������
	Disable_Speaker(); //��ֹ:	"Speaker ������" 

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_Basic_Check();  //��ʾ//Main��Basic_Check �˵�ѡ��(����ʱ)
	F_HL_TestLine02 = YES;  
	
//--**����µ�"�����LED"��ʾ����**-------------------------//
		//Mode��"�ر�"��ģ��("��̬�����LED_Segment" )	
	Init_Mode_LED_Segment(MODE_Close_LED_Segment);
//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
		//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	G_SOS_Cnt = 1;  //SOS����źŴӶ�����ʼѭ��
	break;

case WORK_LED_Segment_Test: //Work��LED_Segment_Test ����(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	Disable_AlarmBuzzer();	//�ر�:����������
	Disable_Speaker(); //��ֹ:	"Speaker ������" 

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_Basic_Check();  //��ʾ//Main��Basic_Check �˵�ѡ��(����ʱ)
	F_HL_TestLine03 = YES;  
	
//--**����µ�"�����LED"��ʾ����**-------------------------//
	G_Brightness_LedSeg = G_BrightnessKind;   //����Ϊ1(��)--"��̬�����LED_Segment" 
		//������ʾ�ַ�://DISP��"0"--"��̬�����LED_Segment" 
		//"��ʾ�ַ�"���µ�"��ʾ��������"("��̬�����LED_Segment" )
	Disp_LED_Segment(0,0,DISP_0_LedSeg,DISP_0_LedSeg,DISP_0_LedSeg,DISP_0_LedSeg,DISP_0_LedSeg,DISP_0_LedSeg,DISP_0_LedSeg,DISP_0_LedSeg);

		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
		//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	G_LedSeg_Cnt = 0;  //"��̬�����LED_Segment" ���õ��ļ�����(�����ַ�ѭ����ʾ)
	break;

case WORK_LCD_Segment_Test: //Work��LCD_Segment_Test ����(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	Disable_AlarmBuzzer();	//�ر�:����������
	Disable_Speaker(); //��ֹ:	"Speaker ������" 

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_Basic_Check();  //��ʾ//Main��Basic_Check �˵�ѡ��(����ʱ)
	F_HL_TestLine04 = YES;  

//--**����µ�"�����LED"��ʾ����**-------------------------//
		//Mode��"�ر�"��ģ��("��̬�����LED_Segment" )	
	Init_Mode_LED_Segment(MODE_Close_LED_Segment);

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
		//������ʾ�ַ�: //DISP��"DISP_0_LcdSeg"--"��ʽLCD_Segment" 
	Disp_LCD_Segment(0,DISP_0_LcdSeg,DISP_0_LcdSeg,DISP_0_LcdSeg,DISP_0_LcdSeg,DISP_0_LcdSeg,DISP_0_LcdSeg);//"��ʾ�ַ�"���µ�"��ʾ��������"(��ʽLCD_Segment)
		//Mode��"��"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Open_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	G_LcdSeg_Cnt = 0; //"��ʽLCD_Segment"���õ��ļ�����(�����ַ�ѭ����ʾ)

    F_Update_RealTime = NO;	    //��ʱ����ˢ��"ʵʱʱ��"     
    F_Update_Temperature = NO;  //��ʱ����ˢ��"ʵʱ�¶�"  
    F_Update_CurrentValue = NO; //��ʱ����ˢ��"INA21x ʵʱ����ֵ" 
    F_Update_Power = NO;        //��ʱ����ˢ��"﮵�ص���"
	break;

case WORK_Buzzer_Test: //Work��Buzzer_Test ����(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	Enable_AlarmBuzzer(M_Buzz200ms);  //��:����������(��ָ����������)(��10msΪʱ�䵥λ)
	Disable_Speaker(); //��ֹ:	"Speaker ������" 

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_Basic_Check();  //��ʾ//Main��Basic_Check �˵�ѡ��(����ʱ)
	F_HL_TestLine05 = YES;	

//--**����µ�"�����LED"��ʾ����**-------------------------//
		//Mode��"�ر�"��ģ��("��̬�����LED_Segment" )	
	Init_Mode_LED_Segment(MODE_Close_LED_Segment);

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
		//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	break;

case WORK_Speaker_Test: //Work��Speaker_Test ����(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	Disable_AlarmBuzzer();	//�ر�:����������
	Disable_Speaker(); //��ֹ:	"Speaker ������" 
    Play_a_Song_Speaker(); //��ʼ������:  ����һ������--"Speaker ������" 

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_Basic_Check();  //��ʾ//Main��Basic_Check �˵�ѡ��(����ʱ)
	F_HL_TestLine06 = YES;	

//--**����µ�"�����LED"��ʾ����**-------------------------//
		//Mode��"�ر�"��ģ��("��̬�����LED_Segment" )	
	Init_Mode_LED_Segment(MODE_Close_LED_Segment);

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
		//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	break;
	
case WORK_Microphone_Test: //Work��Microphone_Test ����(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	Disable_AlarmBuzzer();	//�ر�:����������
	Disable_Speaker(); //��ֹ:	"Speaker ������" 

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_Basic_Check();  //��ʾ//Main��Basic_Check �˵�ѡ��(����ʱ)
	F_HL_TestLine07 = YES;	

//--**����µ�"�����LED"��ʾ����**-------------------------//
		//Mode��"�ر�"��ģ��("��̬�����LED_Segment" )	
	Init_Mode_LED_Segment(MODE_Close_LED_Segment);

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
		//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	break;


case WORK_BQ27410_Test: //Work��BQ27410_FuelGauge_Test ����(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
	mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	Disable_AlarmBuzzer();	//�ر�:����������
	Disable_Speaker(); //��ֹ:	"Speaker ������" 

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_Basic_Check();  //��ʾ//Main��Basic_Check �˵�ѡ��(����ʱ)
	F_HL_TestLine08 = YES;  


//--**����µ�"�����LED"��ʾ����**-------------------------//
		//Mode��"�ر�"��ģ��("��̬�����LED_Segment" )	
	Init_Mode_LED_Segment(MODE_Close_LED_Segment);

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
		//������ʾ�ַ�: //DISP��"DISP_OFF_LcdSeg"--"��ʽLCD_Segment" 
	Disp_LCD_Segment(0,DISP_OFF_LcdSeg,DISP_OFF_LcdSeg,DISP_OFF_LcdSeg,DISP_OFF_LcdSeg,DISP_OFF_LcdSeg,DISP_OFF_LcdSeg);//"��ʾ�ַ�"���µ�"��ʾ��������"(��ʽLCD_Segment)
		//Mode��"��"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Open_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
    F_Update_RealTime = NO;	    //��ʱ����ˢ��"ʵʱʱ��"     
    F_Update_Temperature = NO;  //��ʱ����ˢ��"ʵʱ�¶�"  
    F_Update_CurrentValue = NO; //��ʱ����ˢ��"INA21x ʵʱ����ֵ" 
    F_Update_Power = NO;        //��ʱ����ˢ��"﮵�ص���"
	break;



////////////////////////////////////////////////////////////////////////////
//==**"��ز���" ( �����˵�)** ===========================//
case WORK_Line_LCD_TFT:  //Work��Line_LCD_TFT ����(����ʱ)
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	
	Disp_MAIN_LCD_TFT_Test();  //��ʾ//Main��LCD_TFT_Test �˵�ѡ��(����ʱ)
	F_Update_TestLine02=YES;F_Update_TestLine03=YES;F_Update_TestLine04=YES;
	F_Update_TestLine05=YES;F_Update_TestLine06=YES;F_Update_TestLine07=YES;
	F_HL_TestLine02 = YES; 

	Init_GPIO_LCD_TFT_ILI9325();  //��ʼ��: "����LCD_TFT_ILI9325"  IO�˿�
	LCD_TFT_DrawLine(M_TestLine_09,M_TestColumn_02,M_TestLine_12+13,M_TestColumn_09+5,Fixed_Point);   
	break;

case WORK_Rectangle_LCD_TFT:  //Work��Rectangle_LCD_TFT ����(����ʱ)
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��
	
	Disp_MAIN_LCD_TFT_Test();  //��ʾ//Main��LCD_TFT_Test �˵�ѡ��(����ʱ)
	F_Update_TestLine02=YES;F_Update_TestLine03=YES;F_Update_TestLine04=YES;
	F_Update_TestLine05=YES;F_Update_TestLine06=YES;F_Update_TestLine07=YES;
	F_HL_TestLine03 = YES; 

	Init_GPIO_LCD_TFT_ILI9325();  //��ʼ��: "����LCD_TFT_ILI9325"  IO�˿�
	LCD_TFT_DrawRectangle(M_TestLine_10,M_TestColumn_03,M_TestLine_12,M_TestColumn_09,Fixed_Point);   
	break;


case WORK_Circle_LCD_TFT:  //Work��Circle_LCD_TFT ����(����ʱ)
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��

	Disp_MAIN_LCD_TFT_Test();  //��ʾ//Main��LCD_TFT_Test �˵�ѡ��(����ʱ)
	F_Update_TestLine02=YES;F_Update_TestLine03=YES;F_Update_TestLine04=YES;
	F_Update_TestLine05=YES;F_Update_TestLine06=YES;F_Update_TestLine07=YES;
	F_HL_TestLine04 = YES; 

	Init_GPIO_LCD_TFT_ILI9325();  //��ʼ��: "����LCD_TFT_ILI9325"  IO�˿�
	LCD_TFT_DrawCircle(M_TestLine_11-1,M_TestColumn_06,32,Fixed_Point);  
	break;

case WORK_FillArea_LCD_TFT:  //Work��FillArea_LCD_TFT ����(����ʱ)
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��

	Disp_MAIN_LCD_TFT_Test();  //��ʾ//Main��LCD_TFT_Test �˵�ѡ��(����ʱ)
	F_Update_TestLine02=YES;F_Update_TestLine03=YES;F_Update_TestLine04=YES;
	F_Update_TestLine05=YES;F_Update_TestLine06=YES;F_Update_TestLine07=YES;
	F_HL_TestLine05 = YES; 

	Init_GPIO_LCD_TFT_ILI9325();  //��ʼ��: "����LCD_TFT_ILI9325"  IO�˿�
	LCD_TFT_FillRectangle(M_TestLine_09,M_TestColumn_11,M_TestLine_12+8,M_TestColumn_19,Fixed_Point);
	break;
	
case WORK_Chinese_LCD_TFT:	//Work��Chinese_LCD_TFT ����(����ʱ)
	Open_Buzzer(BuzzTime_Key);  //������Чʱ���÷�����ָ��ʱ��

	Disp_MAIN_LCD_TFT_Test();  //��ʾ//Main��LCD_TFT_Test �˵�ѡ��(����ʱ)
	F_Update_TestLine02=YES;F_Update_TestLine03=YES;F_Update_TestLine04=YES;
	F_Update_TestLine05=YES;F_Update_TestLine06=YES;F_Update_TestLine07=YES;
	F_HL_TestLine06 = YES; 

	Init_GPIO_LCD_TFT_ILI9325();  //��ʼ��: "����LCD_TFT_ILI9325"  IO�˿�
	LCD_TFT_Show_ChFont2424(M_TestLine_09+4,M_TestColumn_12,0,Test_Back,Fixed_Point); 
	LCD_TFT_Show_ChFont2424(M_TestLine_09+4,M_TestColumn_12+24,1,Test_Back,Fixed_Point); 
	LCD_TFT_Show_ChFont2424(M_TestLine_09+4+24,M_TestColumn_12,2,Test_Back,Fixed_Point); 
	LCD_TFT_Show_ChFont2424(M_TestLine_09+4+24,M_TestColumn_12+24,4,Test_Back,Fixed_Point); 
	break;

case WORK_Clear_LCD_TFT:  //Work��Clear_LCD_TFT ����(����ʱ)
	Open_Buzzer(BuzzTime_Key);	//������Чʱ���÷�����ָ��ʱ��

	Disp_MAIN_LCD_TFT_Test();  //��ʾ//Main��LCD_TFT_Test �˵�ѡ��(����ʱ)
	F_Update_TestLine02=YES;F_Update_TestLine03=YES;F_Update_TestLine04=YES;
	F_Update_TestLine05=YES;F_Update_TestLine06=YES;F_Update_TestLine07=YES;
	F_HL_TestLine07 = YES; 

	Init_GPIO_LCD_TFT_ILI9325();  //��ʼ��: "����LCD_TFT_ILI9325"  IO�˿�
	LCD_TFT_FillRectangle(M_TestLine_09-1, M_TestColumn_01,M_TestLine_12+15,M_TestColumn_20,Test_Back);
	break;


////////////////////////////////////////////////////////////////////////////
//==**"��ز���" ( �����˵�)** ===========================//
case WORK_Idle_Step_Motor:      //Work��Idle_Step_Motor ����(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	Stop_Step_Motor();  //ͣת-"Step_Motor �������"

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	
//--**����µ�"�����LED"��ʾ����**-------------------------//
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
			//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	break;

case WORK_Stop_Step_Motor:      //Work��Stop_Step_Motor ����(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	Stop_Step_Motor();  //ͣת-"Step_Motor �������"
	
//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_Step_Motor_Test();  //��ʾ//Main��Step_Motor_Test �˵�ѡ��(����ʱ) 
	F_Update_TestLine03=YES;F_Update_TestLine04=YES;F_Update_TestLine05=YES;
	F_HL_TestLine05 = YES; 

//--**����µ�"�����LED"��ʾ����**-------------------------//
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
			//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	break;

	
case WORK_Positive_Step_Motor:  //Work��Positive_Step_Motor ����(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_Step_Motor_Test();  //��ʾ//Main��Step_Motor_Test �˵�ѡ��(����ʱ) 
	F_Update_TestLine03=YES;F_Update_TestLine04=YES;F_Update_TestLine05=YES;
	F_HL_TestLine03 = YES; 

//--**����µ�"�����LED"��ʾ����**-------------------------//
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
			//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	break;

	
case WORK_Reverse_Step_Motor:   //Work��Reverse_Step_Motor ����(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_Step_Motor_Test();  //��ʾ//Main��Step_Motor_Test �˵�ѡ��(����ʱ) 
	F_Update_TestLine03=YES;F_Update_TestLine04=YES;F_Update_TestLine05=YES;
	F_HL_TestLine04 = YES; 

//--**����µ�"�����LED"��ʾ����**-------------------------//
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
			//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	break;


////////////////////////////////////////////////////////////////////////////
//==**"��ز���" ( �����˵�)** ===========================//
case WORK_Idle_DC_Motor:      //Work��Idle_DC_Motor ����(����ʱ)
//care--��״̬�������л�����ת�Ķ��ݼ�������ڻ���ǰ��Ҫ��ͣ���,֮���ٻ���

//--**��������(��Ӧ��IO�����)**------------------------------//
	Stop_DC_Motor();  //ͣת-"DC_Motor ֱ�����"

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	
//--**����µ�"�����LED"��ʾ����**-------------------------//
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
			//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	G_DC_SpeedCnt = 0;
	G_DC_Speed = 0;
	Open_Timing_In_Work(1500);  //��Ϊ��ʱ1.5�룬�õ��ͣת
	break;

case WORK_Stop_DC_Motor:      //Work��Stop_DC_Motor ����(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//
	Stop_DC_Motor();  //ͣת-"DC_Motor ֱ�����"
	
//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_DC_Motor_Test();  //��ʾ//Main��DC_Motor_Test �˵�ѡ��(����ʱ) 
	F_Update_TestLine03=YES;F_Update_TestLine04=YES;F_Update_TestLine05=YES;
	F_HL_TestLine05 = YES; 

//--**����µ�"�����LED"��ʾ����**-------------------------//
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
			//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	G_DC_SpeedCnt = 0;
	G_DC_Speed = 0;

	break;

	
case WORK_Positive_DC_Motor:  //Work��Positive_DC_Motor ����(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_DC_Motor_Test();  //��ʾ//Main��DC_Motor_Test �˵�ѡ��(����ʱ) 
	F_Update_TestLine03=YES;F_Update_TestLine04=YES;F_Update_TestLine05=YES;
	F_HL_TestLine03 = YES; 

//--**����µ�"�����LED"��ʾ����**-------------------------//
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
			//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	G_DC_SpeedCnt = 0;
	G_DC_Speed = 0;

	break;

	
case WORK_Reverse_DC_Motor:   //Work��Reverse_DC_Motor ����(����ʱ)
//--**��������(��Ӧ��IO�����)**------------------------------//

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
	Disp_MAIN_DC_Motor_Test();  //��ʾ//Main��DC_Motor_Test �˵�ѡ��(����ʱ) 
	F_Update_TestLine03=YES;F_Update_TestLine04=YES;F_Update_TestLine05=YES;
	F_HL_TestLine04 = YES; 

//--**����µ�"�����LED"��ʾ����**-------------------------//
		//Mode��"��"��ģ��("��̬�����LED_Segment" )
	Init_Mode_LED_Segment(MODE_Open_LED_Segment);

//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//
			//Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Init_Mode_LCD_Segment(MODE_Close_LCD_Segment);

//--**"��־λ+����"����س�ʹ��**---------------------------//
	G_DC_SpeedCnt = 0;
	G_DC_Speed = 0;

	break;


	



////////////////////////////////////////////////////////////////////////////
//==**"��ز���" ( �����˵�)** ===========================//



////////////////////////////////////////////////////////////////////////////
//==**"��ز���" ( �����˵�)** ===========================//


////////////////////////////////////////////////////////////////////////////
//==**"��ز���" ( �����˵�)** ===========================//



////////////////////////////////////////////////////////////////////////////
//==**"��ز���" ( �����˵�)** ===========================//



////////////////////////////////////////////////////////////////////////////
//==**: **=========================//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
default:
	
	break;
	}
	
}

/***************************************************************************
case :  //Work��
//--**��������(��Ӧ��IO�����)**------------------------------//

//--**����µ�Һ��"LCD_TFT"��ʾ����**------------------------//
//--**����µ�"�����LED"��ʾ����**-------------------------//
//--**����µ�"��ʽLCD_Segment"��ʾ����**--------------------//

//--**"��־λ+����"����س�ʹ��**---------------------------//

	break;

*************************************************************************/


