/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 Step_Motor.c
* �����ļ�-Dependencies:  	 Step_Motor.h; CD405x_Multiplexer.h; Timer.h; ADC.h;
                                                        Hardware_Profile.h; Generic.h;
* �ļ�����-File Description:	 ( Դ����-Source File) 
	�� "Step_Motor �������"-��������(�ⲿ��Դ)
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


#include "Generic.h"	//���ó����̹淶�������� -ͷ�ļ�-Generic Type Definitions

#include "Hardware_Profile.h"  //������"Ӳ�������ļ�" -Hardware specific definitions for Processor


#include "ADC.h"   //"ADC"ģ��ת��ģ�� -��������-ͷ�ļ�(�������ڲ���Դ) 
#include "Timer.h"     //"��ʱ��" -�������� -ͷ�ļ�(�������ڲ���Դ)



#include "CD405x_Multiplexer.h"   //"CD405x_Multiplexer��·ѡ��ģ�⿪��"  -��������(�ⲿ��Դ)-ͷ�ļ�

#include "Step_Motor.h"   //"Step_Motor �������" -��������(�ⲿ��Դ)-ͷ�ļ�



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
union FLAGBIT Step_Motor_FlagBits; //"Step_Motor �������"��ر�־λ����


unsigned int G_Step_Speed = 0;   //"Step_Motor �������"ת��

unsigned char G_Step_WorkState = 0; //����״̬-"Step_Motor �������"

////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////


/****************************************************************************
*������-Function:	void Enable_Step_Motor(void)
*����- Description:		ʹ��-"Step_Motor �������"
*�������-Input:	None
*�������-output:	None
*ע������-Note��
	��01) ʹ��-"Step_Motor �������"��"��ֹ"-"DC_Motor ֱ�����"
	��02)    	��03)    ��04)  
*****************************************************************************/
void Enable_Step_Motor(void) //ʹ��-"Step_Motor �������"
{
////////////////////////////////////////////////////////////////////////////
//==**"ʹ��""Step_Motor �������"(��ӦDRV8833��nSleep����)**===//
	mOpen_Step_Motor_nSleep;//��������Ϊ"���",��"ʹ��"����("��"��ƽ��Ч)


////////////////////////////////////////////////////////////////////////////
//==**"��ֹ"-"DC_Motor ֱ�����"(��ӦDRV8833��nSleep����)**===//
	mClose_DC_Motor_nSleep; //��������Ϊ"���",��"��ֹ"����(�ͣ�����͹���)
}


/****************************************************************************
*������-Function:	void Disable_Step_Motor(void)
*����- Description:		��ֹ-"Step_Motor �������"
*�������-Input:	None
*�������-output:	None
*ע������-Note��
	��01) "ֹͣ"-"Step_Motor �������"
	��02) "��ֹ"-"Step_Motor �������"
	��03)"DRV8833 ˫·_H_�Žӵ��������"
1) �ܹ���������ֱ��(DC)�����һ��˫���Բ������
2) ��MOSFET ��ͨ����,���Դ��ѹ��Χ��2.7V ��10.8V
3) ÿ��H �ŵ��������Ϊ1.5-ARMS��2APP����VM=5V ��25�������£�
	��04)	
*****************************************************************************/
void Disable_Step_Motor(void)  //��ֹ-"Step_Motor �������"
{
	G_Step_WorkState = STATE_Idle_Step_Motor;
////////////////////////////////////////////////////////////////////////////
//==**"ֹͣ"" �������"(��ӦDRV8833��AIN1��BIN1����)**=====//
//Stop_DC_Motor();  //ͣת-"DC_Motor ֱ�����"
//Stop_PWM_DC_Motor();  //ֹͣPWM���-"DC_Motor ֱ�����"

	mLow_Step_Motor_AIN1;//��������Ϊ"���",�����"��"��ƽ
	mLow_Step_Motor_AIN2;//��������Ϊ"���",�����"��"��ƽ
	mLow_Step_Motor_BIN1;//��������Ϊ"���",�����"��"��ƽ
	mLow_Step_Motor_BIN2;//��������Ϊ"���",�����"��"��ƽ


////////////////////////////////////////////////////////////////////////////
//==**"��ֹ"-"Step_Motor �������"(��ӦDRV8833��nSleep����)**==//
	mClose_Step_Motor_nSleep; //��������Ϊ"���",��"��ֹ"����(�ͣ�����͹���)
	
}




/****************************************************************************
*������-Function:	void Step_Motor_Initial(void)
*����- Description:		��ʼ������:  "Step_Motor �������"
		1) CD405x�е� "Step_Motor �������"
		2) ����IO: ��ʱ��A0��ʼ������(ʹ��CCR1, CCR3)
		3) ����:  
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)    ��04)  
*****************************************************************************/
void Step_Motor_Initial(void)  //��ʼ������:  "Step_Motor �������"
{
////////////////////////////////////////////////////////////////////////////
//==**CD405x�е� "Step_Motor �������"**======================//
	CD405x_SelectChannel(CD405x_Step_Motor);  //CD405x�е�"Step_Motor �������"

////////////////////////////////////////////////////////////////////////////
//==**����"DRV8833 ˫·_H_�Žӵ��������" **=============//
	mSelect_Step_Motor_BIN1_IoPin;	//��������Ϊ"IO"����
	mSelect_Step_Motor_BIN2_IoPin;	//��������Ϊ"IO"����
	Disable_Step_Motor(); //��ֹ-"Step_Motor �������"

////////////////////////////////////////////////////////////////////////////
//==**����: ��ʱ��A0��ʼ������**==========================//
	Timer2_Initial_Step_Motor(); //��ʱ��A2��ʼ������("Step_Motor �������")

	G_Step_Speed = 0;
}



/****************************************************************************
*������-Function:	void Sample_Step_Motor_Frequency(void)
*����- Description:		����"Step_Motor �������"ת��(1s�ڵ��������)
*�������-Input:	None
*�������-output:	None
*ע������-Note��
	��01) ���ж�TIMER0_A1_ISR()����
	��02)    ��03)    ��04)  
************************************************
void Sample_Step_Motor_Frequency(void)
{

	G_Step_FrequencyCnt++;
	if(G_Step_FrequencyCnt >=4) G_Step_FrequencyCnt = 1;

	if(G_Step_FrequencyCnt == 2) 
	{
		G_Step_FrequencyStart = TA0CCR3;
	}
	else if(G_Step_FrequencyCnt == 3) 
	{
		G_Step_FrequencyEnd = TA0CCR3;

		if()

		
	////////////////////////////////////////////////////////////////////////////
	//==**����:  " TA0CTL (Timer_A0���ƼĴ���)"**==================//
		
		TA0CTL &= ~(MC1 + MC0); //��Timer_A0����ֹͣģʽ
		TA0CCTL3 &= ~ CCIE;     //��ֹCCR3 �ж�
		
		F_EnRead_Step_Motor = YES;
	}
		




	G_Step_SpeedCnt ++;  //�ۼ�Ƶ�ʼ�����("Step_Motor �������")
	
	if(F_1s_Frequency_Step_Motor)
	{
		F_1s_Frequency_Step_Motor = 0;

		G_Step_Speed = G_Step_SpeedCnt;  //����1s�ڵ�Ƶ���������
		
		G_Step_SpeedCnt = 0; //��Ƶ�ʼ����������²���
	}
}
*****************************/



/****************************************************************************
*������-Function:	void Stop_Step_Motor(void)
*����- Description:		ͣת-"Step_Motor �������"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01) 	��02)    	��03)    ��04)  
*****************************************************************************/
void Stop_Step_Motor(void)  //ͣת-"Step_Motor �������"
{
	Disable_Step_Motor(); //��ֹ-"Step_Motor �������"
}


/****************************************************************************
*������-Function:	void Positive_Step_Motor(void)
*����- Description:		��ת-"Step_Motor �������"(���ݵ�λ�Ƶ�ѹ���е���)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01) 	��02)    	��03)    ��04)  
*****************************************************************************/
void Positive_Step_Motor(void)  //��ת-"Step_Motor �������"(���ݵ�λ�Ƶ�ѹ���е���)
{
	static char step = 0;

	unsigned int Set_Speed = 0; 

	Set_Speed = G_LastAdResult/10;
	Set_Speed = Set_Speed*100;   //��G_LastAdResult=3312ʱ��Set_Speed=33100 

		//care==
	if(G_LastAdResult >= 80)
	{
		if(G_LastAdResult >= 3300)
		{
			Set_Speed = 33000;
		}
		TA2CCR0 = 36000 - Set_Speed;  //����-"Step_Motor �������"  

		//==**ʹ��: "Step_Motor �������"**=========================//
		Enable_Step_Motor();  //ʹ��-"Step_Motor �������"

	}
	else if(G_LastAdResult < 80)
	{
		TA2CCR0 = 50000;
		//==**ʹ��: "Step_Motor �������"**=========================//
		Enable_Step_Motor();  //ʹ��-"Step_Motor �������"

	}

//////////////////////////////////////////////////////////////////////////////
	switch(step)
	{
		case 0:
			mHigh_Step_Motor_AIN1; 
			mLow_Step_Motor_AIN2; 
			mHigh_Step_Motor_BIN1;
			mLow_Step_Motor_BIN2;
			break;
			
		case 1: 
			mLow_Step_Motor_AIN1;
			mHigh_Step_Motor_AIN2;
			mHigh_Step_Motor_BIN1;
			mLow_Step_Motor_BIN2;
			break;
			
		case 2:
			mLow_Step_Motor_AIN1; 
			mHigh_Step_Motor_AIN2;
			mLow_Step_Motor_BIN1;
			mHigh_Step_Motor_BIN2;
			break;
			
		case 3:
			mHigh_Step_Motor_AIN1;  
			mLow_Step_Motor_AIN2; 
			mLow_Step_Motor_BIN1;
			mHigh_Step_Motor_BIN2;
			break;
	}
	
	step --;
	if(step > 200) step = 3;
}





/****************************************************************************
*������-Function:	void Reverse_Step_Motor(void)
*����- Description:		��ת-"Step_Motor �������"(���ݵ�λ�Ƶ�ѹ���е���)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01) 	��02)    	��03)    ��04)  
*****************************************************************************/
void Reverse_Step_Motor(void)  //��ת-"Step_Motor �������"(���ݵ�λ�Ƶ�ѹ���е���)
{
	static char step = 0;
	
	unsigned int Set_Speed = 0; 

	Set_Speed = G_LastAdResult/10;
	Set_Speed = Set_Speed*100;   //��G_LastAdResult=3312ʱ��Set_Speed=33000 
	
		//care
	if(G_LastAdResult >= 80)
	{
		if(G_LastAdResult >= 3300)
		{
			Set_Speed = 33000;
		}
		TA2CCR0 = 36000 - Set_Speed;  //����-"Step_Motor �������"	
	
		//==**ʹ��: "Step_Motor �������"**=========================//
		Enable_Step_Motor();  //ʹ��-"Step_Motor �������"
	
	}
	else if(G_LastAdResult < 80)
	{
		TA2CCR0 = 50000;
		//==**ʹ��: "Step_Motor �������"**=========================//
		Enable_Step_Motor();  //ʹ��-"Step_Motor �������"
	
	}


//////////////////////////////////////////////////////////////////////////////
	switch(step)
	{
		case 0:
			mHigh_Step_Motor_AIN1; 
			mLow_Step_Motor_AIN2; 
			mHigh_Step_Motor_BIN1;
			mLow_Step_Motor_BIN2;
			break;
			
		case 1: 
			mLow_Step_Motor_AIN1;
			mHigh_Step_Motor_AIN2;
			mHigh_Step_Motor_BIN1;
			mLow_Step_Motor_BIN2;
			break;
			
		case 2:
			mLow_Step_Motor_AIN1; 
			mHigh_Step_Motor_AIN2;
			mLow_Step_Motor_BIN1;
			mHigh_Step_Motor_BIN2;
			break;
			
		case 3:
			mHigh_Step_Motor_AIN1;  
			mLow_Step_Motor_AIN2; 
			mLow_Step_Motor_BIN1;
			mHigh_Step_Motor_BIN2;
			break;
	}
	
	step ++;
	if(step > 3) step = 0;	
}





/****************************************************************************
*������-Function:	void Deal_Step_Motor(void)
*����- Description:		�ж��д��������(����ת,ת��)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) �ж��д��������(����ת,ת��)
	��02)    	��03)    ��04)  
*****************************************************************************/
void Deal_Step_Motor(void)  //�ж��д��������(����ת,ת��)
{
	if(G_Step_WorkState == STATE_Positive_Step_Motor) 
	{
		Positive_Step_Motor(); //��ת-"Step_Motor �������"(���ݵ�λ�Ƶ�ѹ���е���)
	}
	else if(G_Step_WorkState == STATE_Reverse_Step_Motor) 
	{
		Reverse_Step_Motor(); //��ת-"Step_Motor �������"(���ݵ�λ�Ƶ�ѹ���е���)
	}
}



/****************************************************************************
*������-Function:	void Deal_Step_Motor(void)
*����- Description:		���㲽����ת��
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01) 	��02)    	��03)    ��04)  
*****************************************************************************/
void Deal_Speed_Step_Motor(void)  //���㲽����ת�� 
{
    unsigned long a=0;
    unsigned int b = 0;
	unsigned int Set_Speed = 0; 

	Set_Speed = G_LastAdResult/10;
	Set_Speed = Set_Speed*100;   //��G_LastAdResult=3312ʱ��Set_Speed=33000 

	if((G_Step_WorkState == STATE_Positive_Step_Motor)||(G_Step_WorkState == STATE_Reverse_Step_Motor)) 
	{
		if(G_LastAdResult >= 80)
		{
			b = Set_Speed;
			if(G_LastAdResult >= 3300)
			{
				b = 33000;
			}
			
			a = 36000 - b;  //����-"Step_Motor �������"  3285=3200+85
				//ʱ��Ϊ32768Hz, ������18��
				//�������ÿ��һ������ʱ��: a*(1/32768)
				//�������תһȦҪ�õ�ʱ��: T=a*(1/32768) *(360/18)
				//�������ת��=1/T=32768/(a*20)    ת��Ϊr/s,
			G_Step_Speed = (unsigned int)(3276800*60/(a*20));  //ת��Ϊr/min,�Ŵ���100��
		}
		else if(G_LastAdResult < 80)
		{
			G_Step_Speed = 200;
		}

	}
	else G_Step_Speed = 0;
}



