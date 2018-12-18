/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 MyProject.c
* �����ļ�-Dependencies:  	 MyProject.h; System_HeadFile.h;	
* �ļ�����-File Description:	 ( Դ����-Source File)
	�� ������Ŀ: �ܹ��ܳ���
	01) ϵͳ״ֵ̬����
	02) EEPROM ��ַ����
	03) Flash ��ַ����   
	04) ������Ŀ�ı�������    
	05)    06)	
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

#include "MyProject.h"	//������Ŀ: �ܹ��ܳ���-ͷ�ļ�


////////////////////////////////////////////////////////////////////////////
//==**"������Ŀ" ȫ�ֱ�������**Global variables**============//
////////////////////////////////////////////////////////////////////////////

union FLAGBIT16 WorkFlagBits;   //����ʱ,�õ��ı�־λ


unsigned char G_KeyCnt = 0; // ���ڰ���ѡ��˵�

unsigned char G_SOS_Cnt = 0; // ����Led ʵ��SOS ����




////////////////////////////////////////////////////////////////////////////
//==**"������Ŀ" �ֲ���������**Local variables**=============//
////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////////////////////////////////////
//==**"������Ŀ" ר�ú���**============================//
////////////////////////////////////////////////////////////////////////////


/****************************************************************************
*������-Function:	void Detect_Key_WorkMenu(void)
*����- Description:	��"Key1","Key2"����ѡ��"�����˵�"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) 	��02)    ��03)    ��04)  
*****************************************************************************/
void Detect_Key_WorkMenu(void)
{
	if(Detect_Key_1())//"Key_1", ��"����ѡ��" �����˵�
	{
		G_KeyCnt -- ;
		if(G_KeyCnt == 0) G_KeyCnt = 17;

		Select_WorkMenu();//ѡ��"�����˵�"
	}

	if(Detect_Key_2())  //"Key_2", ��"����ѡ��" �����˵�
	{
		G_KeyCnt ++ ;
		if(G_KeyCnt >= 18) G_KeyCnt = 1;
		
		Select_WorkMenu();//ѡ��"�����˵�"
	}
}


/****************************************************************************
*������-Function:	void Select_WorkMenu(void)
*����- Description:	ѡ��"�����˵�"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) 	��02)    ��03)    ��04)  
*****************************************************************************/
void Select_WorkMenu(void)
{
	switch(G_KeyCnt)
	{
		case 1: 
			Initial_MainState(MAIN_Basic_Settings); //װ��//Main��Basic_Settings�˵�ѡ��(����ʱ)
			break;

		case 2: 
			Initial_MainState(MAIN_Basic_Check); //װ��//Main��Basic_Check �˵�ѡ��(����ʱ)
			break;

		case 3:
			Initial_MainState(MAIN_LCD_TFT_Test); //װ��//Main��LCD_TFT_Test �˵�ѡ��(����ʱ)
			break;
			
		case 4:
			Initial_MainState(MAIN_MatrixKey_Test); //װ��//Main��MatrixKey_Test �˵�ѡ��(����ʱ)
			break;

		case 5:
			Initial_MainState(MAIN_TouchPads_Test); //װ��//Main��TouchPads_Test �˵�ѡ��(����ʱ)
			break;	

		case 6:
			Initial_MainState(MAIN_INA21x_Current_Test); //װ��//Main��INA21x_Current_Test �˵�ѡ��(����ʱ)
			break;

		case 7:
			Initial_MainState(MAIN_TMP006_Temperature); //װ��//Main��TMP006_Temperature �˵�ѡ��(����ʱ)
			break;
			
		case 8:
			Initial_MainState(MAIN_Potentiometer_Test); //װ��//Main��Potentiometer_Test �˵�ѡ��(����ʱ)
			break;	

		case 9:
			Initial_MainState(MAIN_DC_Motor_Test); //װ��//Main��DC_Motor_Test �˵�ѡ��(����ʱ) 
			break;			

		case 10:
			Initial_MainState(MAIN_Step_Motor_Test); //װ��//Main��Step_Motor_Test �˵�ѡ��(����ʱ) 
			break;	

		case 11:
			Initial_MainState(MAIN_NTC_HR202_Test); //װ�� //Main��NTC_HR202_Test(��ʪ��) �˵�ѡ��(����ʱ)
			break;	
			
		case 12:
			Initial_MainState(MAIN_IrDA_UART); //װ��//Main��IrDA_UART �˵�ѡ��(����ʱ)
			break;		

		case 13:
			Initial_MainState(MAIN_RS232_UART); //װ��//Main��RS232_UART �˵�ѡ��(����ʱ)
			break;		

		case 14:
			Initial_MainState(MAIN_RS485_UART); //װ��//Main��RS485_UART �˵�ѡ��(����ʱ)
			break;		

		case 15:
			mSPI_All_Disable;  //�ر�����SPIģ���ʹ��
			Initial_MainState(MAIN_CC1101_Test); //װ��//Main��CC1101_Test �˵�ѡ��(����ʱ)
			break;		

		case 16:
			mSPI_All_Disable;  //�ر�����SPIģ���ʹ��
			Initial_MainState(MAIN_SD_Card_Test); //װ��//Main��SD_Card_Test �˵�ѡ��(����ʱ)
			break;		

		case 17:
			mSPI_All_Disable;  //�ر�����SPIģ���ʹ��
			Initial_MainState(MAIN_MassStorage_Test); //װ��//Main��MassStorage_Test �˵�ѡ��(����ʱ)
			break;	

	///////////////////////////////////////////////////
		default : break;

	}

}



/****************************************************************************
*������-Function:	void SOS_Function(void)
*����- Description:	Led_Diode(���������) ʵ��SOS ��ȹ���
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) 	��02)    ��03)    ��04)  
*****************************************************************************/
void SOS_Function(void)
{
	if(!F_Timing)  // ��Ϊ��ʱ�������Զ����빤��״̬(����ʱ)
	{
		
//SOS����: 1����300ms��2�̰�300ms��3����300ms��4�̰�300ms��5����300ms
//    ��6����1.8s��7����900ms��8�̰�300ms��9����900ms��10�̰�300m
//��11����900ms��12����1.8s   ���ߵ�ƽΪ"��",	�͵�ƽΪ"��"��

		switch(G_SOS_Cnt) 
		{
	case 1:	 // 1����300ms
		mOpen_LED_YELLOW;  //��������Ϊ"���",��"����"LED_YELLOW 
		mOpen_LED_GREEN;  //��������Ϊ"���",��"����"LED_GREEN
		mOpen_LED_RED;  //��������Ϊ"���",��"����"LED_RED
		Open_Timing_Task(300);//��ϵͳ��ʱ����ʱ������ʱ��ֵ(�ж���)
		break;	

	case 2:  //2�̰�300ms
		mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
		mClose_LED_GREEN; //��������Ϊ"���",��"Ϩ��"LED_GREEN 
		mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
		Open_Timing_Task(300);//��ϵͳ��ʱ����ʱ������ʱ��ֵ(�ж���)
		break;	

	case 3:	 //3����300ms
		mOpen_LED_YELLOW;  //��������Ϊ"���",��"����"LED_YELLOW 
		mOpen_LED_GREEN;  //��������Ϊ"���",��"����"LED_GREEN
		mOpen_LED_RED;  //��������Ϊ"���",��"����"LED_RED
		Open_Timing_Task(300);//��ϵͳ��ʱ����ʱ������ʱ��ֵ(�ж���)
		break;

	case 4: //4�̰�300ms
		mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
		mClose_LED_GREEN; //��������Ϊ"���",��"Ϩ��"LED_GREEN 
		mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
		Open_Timing_Task(300);//��ϵͳ��ʱ����ʱ������ʱ��ֵ(�ж���)
		break;	

	case 5: //5����300ms
		mOpen_LED_YELLOW;  //��������Ϊ"���",��"����"LED_YELLOW 
		mOpen_LED_GREEN;  //��������Ϊ"���",��"����"LED_GREEN
		mOpen_LED_RED;	//��������Ϊ"���",��"����"LED_RED
		Open_Timing_Task(300);//��ϵͳ��ʱ����ʱ������ʱ��ֵ(�ж���)
		break;

	case 6: //6����1.8s
		mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
		mClose_LED_GREEN; //��������Ϊ"���",��"Ϩ��"LED_GREEN 
		mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
		Open_Timing_Task(1800);//��ϵͳ��ʱ����ʱ������ʱ��ֵ(�ж���)
		break;	

	case 7: //7����900ms
		mOpen_LED_YELLOW;  //��������Ϊ"���",��"����"LED_YELLOW 
		mOpen_LED_GREEN;  //��������Ϊ"���",��"����"LED_GREEN
		mOpen_LED_RED;	//��������Ϊ"���",��"����"LED_RED
		Open_Timing_Task(900);//��ϵͳ��ʱ����ʱ������ʱ��ֵ(�ж���)
		break;

	case 8: //8�̰�300ms
		mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
		mClose_LED_GREEN; //��������Ϊ"���",��"Ϩ��"LED_GREEN 
		mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
		Open_Timing_Task(300);//��ϵͳ��ʱ����ʱ������ʱ��ֵ(�ж���)
		break;	

	case 9: //9����900ms
		mOpen_LED_YELLOW;  //��������Ϊ"���",��"����"LED_YELLOW 
		mOpen_LED_GREEN;  //��������Ϊ"���",��"����"LED_GREEN
		mOpen_LED_RED;	//��������Ϊ"���",��"����"LED_RED
		Open_Timing_Task(900);//��ϵͳ��ʱ����ʱ������ʱ��ֵ(�ж���)
		break;

	case 10: //10�̰�300m
		mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
		mClose_LED_GREEN; //��������Ϊ"���",��"Ϩ��"LED_GREEN 
		mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
		Open_Timing_Task(300);//��ϵͳ��ʱ����ʱ������ʱ��ֵ(�ж���)
		break;	
		
	case 11: //11����900ms 
		mOpen_LED_YELLOW;  //��������Ϊ"���",��"����"LED_YELLOW 
		mOpen_LED_GREEN;  //��������Ϊ"���",��"����"LED_GREEN
		mOpen_LED_RED;	//��������Ϊ"���",��"����"LED_RED
		Open_Timing_Task(900);//��ϵͳ��ʱ����ʱ������ʱ��ֵ(�ж���)
		break;

	case 12: //12����1.8s  
		mClose_LED_YELLOW; //��������Ϊ"���",��"Ϩ��"LED_YELLOW
		mClose_LED_GREEN; //��������Ϊ"���",��"Ϩ��"LED_GREEN 
		mClose_LED_RED; //��������Ϊ"���",��"Ϩ��"LED_RED
		Open_Timing_Task(1800);//��ϵͳ��ʱ����ʱ������ʱ��ֵ(�ж���)
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
*������-Function:	void Deal_Main_Loop(void)
*����- Description:	       ��ѭ���еģ�ѭ��ִ�еĲ���(��ʾ������)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) 	��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_Main_Loop(void)  //��ѭ���еģ�ѭ��ִ�еĲ���(��ʾ������)
{
////////////////////////////////////////////////////////////////////////////
//==**������ʾ: "����LCD_TFT"**===============================//
	Deal_LCD_TFT();//LCD_TFT ��ʾ����//ֻ�������ݱ仯����ʾ����

////////////////////////////////////////////////////////////////////////////
//==**������ʾ: "��ʽLCD_Segment"**===========================//
	Deal_LCD_Segment();//"��ʽLCD_Segment": ����ͬ"����ģʽ"

////////////////////////////////////////////////////////////////////////////
//==**������ʾ: "�����LED_Segment"**=========================//
	Deal_LED_Segment();//"�����LED_Segment": ����ͬ"����ģʽ"

	if((G_WorkState != WORK_Speaker_Test)&&(G_WorkState != WORK_LCD_Segment_Test))
	{
		////////////////////////////////////////////////////////////////////////////
		//==**ϵͳÿ100ms ��ȡ"ʵʱʱ��"**======================//
		Deal_RTC(); //����" RTC ʵʱʱ��":����ʵʱʱ�䣬��ʾʵʱʱ��

		////////////////////////////////////////////////////////////////////////////
		//==**ϵͳÿ100ms ����һ��"TMP006 �¶�"**====================//
		Deal_TMP006_Temperature();	//����TMP006 �¶�,�õ�����"ʵ���¶�ֵ"

		////////////////////////////////////////////////////////////////////////////
		//==**ϵͳÿ100ms ����һ��"������ֵ"**================//
		Deal_INA21x();	//���� "INA21x �������������": AD������AD���ݴ�����ʾ����			
	}

}


