/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 RTC.c
* �����ļ�-Dependencies:  	 RTC.h; MyProject_Set_LCD_TFT.h; msp430f6638.h; System.h;  Hardware_Profile.h; Generic.h;
* �ļ�����-File Description:	 ( Դ����-Source File) 
	��"RTC �ڲ�ʵʱʱ��" -��������(�������ڲ���Դ) 
	01) MSP430F6638 ֻ��һ��ʵʱʱ��ģ��(RTC_B)��RTC_B ��֧����������
	02) ����RTC_B ��Ƶϵ������ʱ������Ϊ�̶�ֵ��Ϊ���ṩ׼ȷ
	      ��1s ʱ����Ԫ����ģ��ʱ��Դ����Ϊ32.768KHz�� 
	03) ��� VCC �رգ�����Ȼ����ͨ����ع�����Զ����С�
	04) ���⣬��ģ�黹 ���б�����У׼���ܣ������ܹ�����
	      ���͹���LPMx.5 ģʽ�¡�
	05)
	06)	
	07)	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ע������-Attention : 	
	��01) ��Ҫ��RTC����У�������
			A) ��Init_RTC()��ȡ������//RTCCTL0 |= RTCRDYIE + RTCTEVIE + RTCAIE;  
			B)��Interrupt.c��ȡ������RTC�жϷ������
	��02)     ��03)    ��04)    ��05)    ��06)     
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

#include "System.h"	 //"ϵͳ" ���ù��ܺ�����-ͷ�ļ�

	//������Ŀ: LCD_TFTҺ����ʾ����(�������е�Һ������) -ͷ�ļ�
#include "MyProject_Set_LCD_TFT.h"  

#include "RTC.h"   //"RTC �ڲ�ʵʱʱ��" -��������-ͷ�ļ�(�������ڲ���Դ) 



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
union FLAGBIT16 RTC_FlagBits;   //"RTC �ڲ�ʵʱʱ��"��ر�־λ����


	//������������
unsigned char G_RTC_ReadBuf[24];



							
	//�޸Ļ�������BCD��(RTC) :   ��_H,��_L,��,Week, ��,  ʱ, ��,  ��
unsigned char G_RTC_WriteBuf[8]  = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

unsigned int  G_Year_SetBuf = 0;   //"��"ֵ(�޸�ʱ��)(����ʮ����)
unsigned char G_Month_SetBuf = 0;  //"��"ֵ(�޸�ʱ��)(����ʮ����)
unsigned char G_Date_SetBuf = 0;   //"��"ֵ(�޸�ʱ��)(����ʮ����)

unsigned char G_Hour_SetBuf = 0;   //"Сʱ"ֵ(�޸�ʱ��)(����ʮ����)
unsigned char G_Minute_SetBuf = 0; //"����"ֵ(�޸�ʱ��)(����ʮ����)
unsigned char G_Second_SetBuf = 0; //"��"ֵ(�޸�ʱ��)(����ʮ����)

unsigned char G_Week_SetBuf = 0;   //"����"ֵ(�޸�ʱ��)(����ʮ����)


unsigned char G_LastSecondBuf = 0;  //���ϴ�"��"ʱ��,����ʱ��仯ˢ��ʱ��
unsigned char G_LastMinuteBuf = 0;  //���ϴ�"����"ʱ��
unsigned char G_LastHourBuf = 0;    //���ϴ�"Сʱ"ʱ��


//����һ�� MON = Monday         //���ڶ���TUE = Tuesday   
//�������� WED = Wednesday    //�����ģ�THU = Thursday 
//�����壺 FRI = Friday             //��������SAT = Saturday 
//�����죺 SUN = Sunday

////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////



/****************************************************************************
*������-Function:	void Init_RTC_B(void)
*����- Description:	��ʼ��: RTC_B ʵʱʱ��
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Init_RTC_B(void)
{
////////////////////////////////////////////////////////////////////////////
//==**RTCCTL01*Real-Time Clock Control 0 and 1 Register**============//
		// �ر�RTC����RTC������������ΪBCDģʽ��ʱ���¼�ΪÿСʱ�ı�һ��
    RTCCTL01 = RTCBCD + RTCHOLD + RTCTEV_1;
		//RTCBCD   Real-time clock BCD select. Selects BCD counting for real-time clock.
		//RTCHOLD  Real-time clock hold //0b = Real-time clock is operational. //1b = The calendar is stopped as well as the prescale counters, RT0PS, and RT1PS.
		//RTCTEV_1  Real-time clock time interrupt event//01b = Hour changed  //00b = Minute changed  //10b = Every day at midnight (00:00)  //11b = Every day at noon (12:00)

////////////////////////////////////////////////////////////////////////////
//==**������ʼʱ��**===================================//
/*********************************************/
		//BCD��// ������ʼʱ�䣬2013��01��01�գ�00:00:00�����ڶ�
	RTCYEAR = 0x2013; //��
	RTCMON	= 0x01;   //��
	RTCDAY	= 0x01;   //��//Day of Month Register
	
	RTCHOUR = 0x00;   //ʱ
	RTCMIN  = 0x00;   //��
	RTCSEC  = 0x00;   //��
	
	RTCDOW	= 0x02;   //����//Day of Week Register
	


////////////////////////////////////////////////////////////////////////////
//==**ʹ��RTC ģ��**=====================================//
		//RTCHOLD  Real-time clock hold //0b = Real-time clock is operational. //1b = The calendar is stopped as well as the prescale counters, RT0PS, and RT1PS.
    RTCCTL01 &= ~RTCHOLD;
		
		
////////////////////////////////////////////////////////////////////////////
//==**���ñ���ʱ��**===================================//
		// ���ñ���ʱ�䣬ÿ��һ��07:00:00
//RTCAHOUR = 0x87;
//RTCAMIN  = 0x80;
//RTCADOW  = 0x81;  //Real-Time Clock Day of Week Alarm Register
		// ʹ��ÿ���жϡ�ʱ���¼��������ж�
		
////////////////////////////////////////////////////////////////////////////
//==**�ж����*RTCCTL0*Real-Time Clock Control 0 Register**============//

//RTCCTL0 |= RTCRDYIE + RTCTEVIE + RTCAIE;     // Enable interrupt
		//RTCRDYIE   Real-time clock ready interrupt enable.
		//RTCTEVIE   Real-time clock time event interrupt enable. In modules supporting LPMx.5 this interrupt can be used as LPMx.5 wake-up event.
		//RTCAIE      Real-time clock alarm interrupt enable. In modules supporting LPMx.5 this interrupt can be used as LPMx.5 wake-up event.
		
}



/****************************************************************************
*������-Function:	void Read_RTC_CurrentTime(void)
*����- Description:	ʵʱ��ȡ: RTC ʵʱʱ��
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Read_RTC_CurrentTime(void)
{
	if (G_LastSecondBuf != RTCSEC) //ʵʱ"��"�ı�
	{  
		F_SecondChange_RTC = 1;                          
		G_LastSecondBuf = RTCSEC;  //��������"��"ֵ
	} 

	if(G_LastMinuteBuf != RTCMIN ) //ʵʱ"����"�ı�
	{
		F_MinuteChange_RTC = 1;     
		G_LastMinuteBuf = RTCMIN;  //��������"����"ֵ
	}
	   
	if(G_LastHourBuf != RTCHOUR )     //ʵʱ"Сʱ"�ı�
	{
		F_HourChange_RTC = 1;    
		G_LastHourBuf = RTCHOUR;     //��������"Сʱ"ֵ
	}
	


	G_RTC_ReadBuf[0]  = ASCII_Table[RTCYEAR >> 12];  //��"ǧλ"(��)(ASSII��)
	G_RTC_ReadBuf[1]  = ASCII_Table[(RTCYEAR >> 8) & 0x000F];	//��"��λ"(��)(ASSII��)
	G_RTC_ReadBuf[2]  = ASCII_Table[(RTCYEAR >> 4) & 0x000F];	//��"ʮλ"(��)(ASSII��)
	G_RTC_ReadBuf[3]  = ASCII_Table[RTCYEAR & 0x000F];	//��"��λ"(��)(ASSII��)
	G_RTC_ReadBuf[4]  = '-';
	G_RTC_ReadBuf[5]  =  ASCII_Table[RTCMON >> 4];	//��"ʮλ"(��)(ASSII��)
	G_RTC_ReadBuf[6]  =  ASCII_Table[RTCMON & 0x0F];	//��"��λ"(��)(ASSII��)
	G_RTC_ReadBuf[7]  = '-';
	G_RTC_ReadBuf[8]  =  ASCII_Table[RTCDAY >> 4];	//��"ʮλ"(��)(ASSII��)
	G_RTC_ReadBuf[9]  =  ASCII_Table[RTCDAY & 0x0F];	//��"��λ"(��)(ASSII��)
	G_RTC_ReadBuf[10] = ' ';
	G_RTC_ReadBuf[11]  =  ASCII_Table[RTCHOUR >> 4];  //��"ʮλ"(Сʱ)(ASSII��)
	G_RTC_ReadBuf[12]  =  ASCII_Table[RTCHOUR & 0x0F];	//��"��λ"(Сʱ)(ASSII��)
	G_RTC_ReadBuf[13] = ':';
	G_RTC_ReadBuf[14]  =  ASCII_Table[RTCMIN >> 4];  //��"ʮλ"(����)(ASSII��)
	G_RTC_ReadBuf[15]  =  ASCII_Table[RTCMIN & 0x0F];	//��"��λ"(����)(ASSII��)
	G_RTC_ReadBuf[16] = ':';
	G_RTC_ReadBuf[17]  =  ASCII_Table[RTCSEC >> 4];  //��"ʮλ"(��)(ASSII��)
	G_RTC_ReadBuf[18]  =  ASCII_Table[RTCSEC & 0x0F];	//��"��λ"(��)(ASSII��)
	G_RTC_ReadBuf[19] = ' ';

	switch(RTCDOW) 
	{
		case 1:	  //����һ
			G_RTC_ReadBuf[20] = 'M';
			G_RTC_ReadBuf[21] = 'O';
			G_RTC_ReadBuf[22] = 'N';
			break;	
			
		case 2:   //���ڶ�
			G_RTC_ReadBuf[20] = 'T';
			G_RTC_ReadBuf[21] = 'U';
			G_RTC_ReadBuf[22] = 'E';
			break;	

		case 3:   //������
			G_RTC_ReadBuf[20] = 'W';
			G_RTC_ReadBuf[21] = 'E';
			G_RTC_ReadBuf[22] = 'D';
			break;	

		case 4:   //������
			G_RTC_ReadBuf[20] = 'T';
			G_RTC_ReadBuf[21] = 'H';
			G_RTC_ReadBuf[22] = 'U';
			break;	

		case 5:   //������
			G_RTC_ReadBuf[20] = 'F';
			G_RTC_ReadBuf[21] = 'R';
			G_RTC_ReadBuf[22] = 'I';
			break;	
			
		case 6:   //������
			G_RTC_ReadBuf[20] = 'S';
			G_RTC_ReadBuf[21] = 'A';
			G_RTC_ReadBuf[22] = 'T';
			break;	
			
		case 7:   //������
			G_RTC_ReadBuf[20] = 'S';
			G_RTC_ReadBuf[21] = 'U';
			G_RTC_ReadBuf[22] = 'N';
			break;	

////////////////////////////////////////////////////////////////////////////
		default:	//����1��7����ʾ"Err" ��ʾ����
			G_RTC_ReadBuf[20] = 'E';
			G_RTC_ReadBuf[21] = 'r';
			G_RTC_ReadBuf[22] = 'r';
			break;

	}

}



/****************************************************************************
*������-Function:	unsigned char Check_RTC_InputModifyDate(void)
*����- Description:	��������޸�ʱ���Ƿ�Ϸ�
*�������-Input:	None
*�������-output:	0xFF:�Ϸ�,0:���Ϸ�
*ע������-Note��	
	��01) û�м��"����"�Ƿ������д�
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Check_RTC_InputModifyDate(void)
{
	unsigned char Retemp = 0;

if((G_Week_SetBuf >= 1) && (G_Week_SetBuf <= 7))   //���"����"��1��7֮�䣬��ʾ��ȷ
{
	if(G_Second_SetBuf < 60)   //���"��"С��60����ʾ��ȷ
	{
		if(G_Minute_SetBuf < 60)   //���"����"С��60����ʾ��ȷ
		{
			if(G_Hour_SetBuf < 24) //���"Сʱ"С��24����ʾ��ȷ
			{                        
				if(G_Month_SetBuf == 2) //���Ϊ2�·�
				{
						 //ƽ��: ���ܱ�4����,�������ܱ�100 �����������ܱ�400����  
					if((G_Year_SetBuf & 0x03)||(((G_Year_SetBuf%100) == 0)&&((G_Year_SetBuf%400) != 0)))
					{	
						if((G_Date_SetBuf <= 28)&&(G_Date_SetBuf > 0))    
						{
							Retemp = 0xFF;                                                
						} 
					}
					else   //����: �ܱ�4��400����,�����ܱ�100����         
					{	
						if((G_Date_SetBuf <= 29)&&(G_Date_SetBuf > 0))
						{
							Retemp = 0xFF;
						}

					}
				}		
				else if((G_Month_SetBuf < 8)&&(G_Month_SetBuf > 0))  //�ж�1�£�7���е��´���С
				{
					if(G_Month_SetBuf & 0x01)     //�·�<8 ������Ϊ����
					{
						if((G_Date_SetBuf <= 31)&&(G_Date_SetBuf > 0))     //�´�
						{
							Retemp = 0xFF;   
						}
					} 
					else
					{
						if((G_Date_SetBuf <= 30)&&(G_Date_SetBuf > 0))   //��С
						{
							Retemp = 0xFF;   
						}
					}                               
				}
				else 
				{
					if((G_Month_SetBuf < 13) && (G_Month_SetBuf > 7))     //�ж�8�£�12���е��´���С
					{
						if(G_Month_SetBuf & 0x01)     //�·�>=8 ������ΪС��
						{
							if((G_Date_SetBuf <= 30)&&(G_Date_SetBuf > 0))   //��С
							{
								Retemp = 0xFF;   
							}
						} 
						else
						{
							if((G_Date_SetBuf <= 31)&&(G_Date_SetBuf > 0))    //�´�
							{
								Retemp = 0xFF;   
							}
						} 
					}
				}                    
			}
		}
	}
}



	return Retemp;
}


/******************************************************************
*������ Function Name: void Modify_PCF8583_Time(void)
*�������� Description: �޸�PCF8583������ʱ��
*������� Parameters : None
*�������Return Value: None
*ע������  Attention ��
	01)дʱ�䵽PCF8583ʱ�� ͬ��Ҫ�Ȱ�����ת��BCD����д��PCF8583
	02)  03) 04)  05) 06)
*******************************************************************/

/****************************************************************************
*������-Function:	void Modify_RealTime_RTC(void)
*����- Description:	�޸�RTCʵʱʱ��
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01)  �Ȱ�����ת��BCD����д��RTC
	��02)    ��03)    ��04)  
*****************************************************************************/
void Modify_RealTime_RTC(void)
{ 

//Ҫд��ʱ��ʱ��
//Ҫ��Ҫ���Ȱ�ʱ��RTC�ر�??????
	//BCD��// ������ʼʱ��	
//	RTCYEARH = ChangeDecIntoHex((unsigned char)(G_Year_SetBuf / 100));
//	RTCYEARL = ChangeDecIntoHex((unsigned char)(G_Year_SetBuf % 100));
	RTCYEAR = ((ChangeDecIntoHex(G_Year_SetBuf / 100))<<8)+(ChangeDecIntoHex(G_Year_SetBuf % 100));
	RTCMON	= ChangeDecIntoHex(G_Month_SetBuf);
	RTCDAY	= ChangeDecIntoHex(G_Date_SetBuf);   //Day of Month Register

	RTCHOUR = ChangeDecIntoHex(G_Hour_SetBuf);
	RTCMIN	= ChangeDecIntoHex(G_Minute_SetBuf);
	RTCSEC	= ChangeDecIntoHex(G_Second_SetBuf);

	RTCDOW	= ChangeDecIntoHex(G_Week_SetBuf);   //Day of Week Register

}


/****************************************************************************
*������-Function:	void Deal_RTC(void)
*����- Description:	����" RTC ʵʱʱ��":����ʵʱʱ�䣬��ʾʵʱʱ��
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_RTC(void)
{
////////////////////////////////////////////////////////////////////////////
//==**ϵͳÿ100ms ��ȡ"ʵʱʱ��"**======================//
	if(F_100ms_ReadTime)	//ϵͳ��ʱÿ100ms��һ��"ʵʱʱ��"
	{
		F_100ms_ReadTime = 0;
	
		Read_RTC_CurrentTime();//ʵʱ��ȡ: RTC ʵʱʱ��
	}

////////////////////////////////////////////////////////////////////////////
//--**��ʾʵʱʱ��**-----------------------------------------------//
	Disp_RTC_CurrentTime(); //��ʾ: RTC ʵʱʱ��


}







