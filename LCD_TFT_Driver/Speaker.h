/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 Speaker.h
* �����ļ�-Dependencies:  	 None	
* �ļ�����-File Description:	 ( ͷ�ļ�-Header File )
	��"Speaker ������" -��������(�ⲿ��Դ)-ͷ�ļ�
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



#ifndef  __Speaker_H 
#define  __Speaker_H 


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"�궨��**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////
#define  M_100MS_Speaker  (100) //��������: 100ms

#define  M_200MS_Speaker  (200) //��������: 200ms
#define  M_500MS_Speaker  (500) //��������: 500ms

#define  M_1S_Speaker     (1000) //��������: 1s






////////////////////////////////////////////////////////////////////////////
//==**��Ŀ"ר��"�궨��**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
extern union FLAGBIT16 SpeakerFlagBits;  //"Speaker ������"�õ��ı�־λ����
#define  G_SpeakerFlagBits  SpeakerFlagBits.FLAG16  
#define  F_StartSpeaker     SpeakerFlagBits.b.f0   //Ϊ1������������(Speaker ������)   
//#define  F_Disable_Buzz 	SpeakerFlagBits.b.f1   //Ϊ1�����÷�����(Speaker ������)   
//#define   F_	SpeakerFlagBits.b.f2  
//#define   F_	SpeakerFlagBits.b.f3  
//#define   F_	SpeakerFlagBits.b.f4  
//#define   F_	SpeakerFlagBits.b.f5  
//#define   F_	SpeakerFlagBits.b.f6  
//#define   F_	SpeakerFlagBits.b.f7 
//#define   F_	SpeakerFlagBits.b.f8      
//#define   F_	SpeakerFlagBits.b.f9     
//#define   F_	SpeakerFlagBits.b.f10    
//#define   F_	SpeakerFlagBits.b.f11      
//#define   F_	SpeakerFlagBits.b.f12      
//#define   F_	SpeakerFlagBits.b.f13      
//#define   F_	SpeakerFlagBits.b.f14     
//#define   F_	SpeakerFlagBits.b.f15     



////////////////////////////////////////////////////////////////////////////
//==**"����"�궨��**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"��������**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**"�ⲿ" API ��������**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

extern void Disable_Speaker(void); //��ֹ:  "Speaker ������" 


extern void Deal_Song_Tone_Speaker(void); //�����ض��������ɶ�ӦƵ�ʵĲ���-- "Speaker ������" 
extern void Deal_Song_Beat_Speaker(void); //���Ʋ��Ÿ����������ͽ��� -- "Speaker ������" 

extern void Play_a_Song_Speaker(void); //��ʼ������:  ����һ������--"Speaker ������" 

/////////////////////////////////////////////////////////////////////////////////
extern void Mic_Record_Speaker_Play(void); //��˷�¼����ͨ��DMA ����DACͨ������������

/////////////////////////////////////////////////////////////////
extern void Open_Buzz_Speaker(unsigned long timeValue);  //�򿪷�����(Speaker ������)�Ķ�ʱ��	

extern void Initial_Buzz_Speaker(void);  //��ʼ������:  ������ -- "Speaker ������" 

extern void Deal_Buzz_Speaker(void);  //��������� -- "Speaker ������" 

extern void Check_Buzz_Speaker(void);   //���ж������Ƿ����: ������ -- "Speaker ������" (����:���úͱ�����)



#endif   /* __Speaker_H  */





