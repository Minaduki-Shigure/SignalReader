/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 RTC.h
* �����ļ�-Dependencies:  	 None	
* �ļ�����-File Description:	 ( ͷ�ļ�-Header File )
	��"RTC �ڲ�ʵʱʱ��" -��������-ͷ�ļ�(�������ڲ���Դ) 
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


#ifndef  __RTC_H 
#define  __RTC_H 


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"�궨��**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**��Ŀ"ר��"�궨��**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
extern union FLAGBIT16 RTC_FlagBits;   //"RTC �ڲ�ʵʱʱ��"��ر�־λ����
#define  G_RTC_FlagBits     RTC_FlagBits.FLAG16  
#define	 F_SecondChange_RTC RTC_FlagBits.b.f0  //Ϊ1ʱ��"��"�ı�ʱ--"RTC �ڲ�ʵʱʱ��"
#define	 F_MinuteChange_RTC RTC_FlagBits.b.f1  //Ϊ1ʱ��"����"�ı�ʱ--"RTC �ڲ�ʵʱʱ��"
#define	 F_HourChange_RTC   RTC_FlagBits.b.f2  //Ϊ1ʱ��"Сʱ"�ı�ʱ--"RTC �ڲ�ʵʱʱ��"
//#define	 F_      RTC_FlagBits.b.f3  //Ϊ1ʱ��
//#define	 F_      RTC_FlagBits.b.f4  //Ϊ1ʱ��
//#define	 F_      RTC_FlagBits.b.f5  //Ϊ1ʱ��
//#define	 F_      RTC_FlagBits.b.f6  //Ϊ1ʱ��
//#define	 F_      RTC_FlagBits.b.f7  //Ϊ1ʱ��
//#define	 F_      RTC_FlagBits.b.f8  //Ϊ1ʱ��
//#define	 F_      RTC_FlagBits.b.f9  //Ϊ1ʱ��
//#define	 F_      RTC_FlagBits.b.f10 //Ϊ1ʱ��
//#define	 F_      RTC_FlagBits.b.f11 //Ϊ1ʱ��
//#define	 F_      RTC_FlagBits.b.f12 //Ϊ1ʱ��
//#define	 F_      RTC_FlagBits.b.f13 //Ϊ1ʱ�� 
//#define	 F_      RTC_FlagBits.b.f14 //Ϊ1ʱ��
//#define	 F_      RTC_FlagBits.b.f15 //Ϊ1ʱ��  


	//������������
extern unsigned char G_RTC_ReadBuf[24];	


	//�޸Ļ�������BCD��(RTC) :	 ��_H,��_L,��,Week, ��,  ʱ, ��,  ��
extern unsigned char G_RTC_WriteBuf[8];


extern unsigned int  G_Year_SetBuf;   //"��"ֵ(�޸�ʱ��)(����ʮ����)
extern unsigned char G_Month_SetBuf;  //"��"ֵ(�޸�ʱ��)(����ʮ����)
extern unsigned char G_Date_SetBuf;   //"��"ֵ(�޸�ʱ��)(����ʮ����)

extern unsigned char G_Hour_SetBuf;   //"Сʱ"ֵ(�޸�ʱ��)(����ʮ����)
extern unsigned char G_Minute_SetBuf; //"����"ֵ(�޸�ʱ��)(����ʮ����)
extern unsigned char G_Second_SetBuf; //"��"ֵ(�޸�ʱ��)(����ʮ����)

extern unsigned char G_Week_SetBuf;   //"����"ֵ(�޸�ʱ��)(����ʮ����)



extern unsigned char G_LastSecondBuf;  //���ϴ�"��"ʱ��,����ʱ��仯ˢ��ʱ��
extern unsigned char G_LastMinuteBuf;  //���ϴ�"����"ʱ��
extern unsigned char G_LastHourBuf;    //���ϴ�"Сʱ"ʱ��



////////////////////////////////////////////////////////////////////////////
//==**"����"�궨��**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"��������**Exported Module-specific funcitions**===//
////////////////////////////////////////////////////////////////////////////

extern void Init_RTC_B(void);  //��ʼ��: RTC_B ʵʱʱ��

extern void Read_RTC_CurrentTime(void);//ʵʱ��ȡ: RTC ʵʱʱ��

	//��������޸�ʱ���Ƿ�Ϸ�
extern unsigned char Check_RTC_InputModifyDate(void); 

	//�޸�RTCʵʱʱ��
extern void Modify_RealTime_RTC(void);



////////////////////////////////////////////////////////////////////////////
//==**"�ⲿ" API ��������**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

	//����" RTC ʵʱʱ��":����ʵʱʱ�䣬��ʾʵʱʱ��
extern void Deal_RTC(void); 






#endif   /* __RTC_H  */





