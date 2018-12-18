/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 Step_Motor.h
* �����ļ�-Dependencies:  	 None	
* �ļ�����-File Description:	 ( ͷ�ļ�-Header File )
	��"Step_Motor �������" -��������(�ⲿ��Դ)-ͷ�ļ�
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

#ifndef  __Step_Motor_H 
#define  __Step_Motor_H 


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"�궨��**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////
#define STATE_Idle_Step_Motor     ( 0 )  //�ձ�-""Step_Motor �������"
#define STATE_Positive_Step_Motor ( 1 )  //��ת-"Step_Motor �������"
#define STATE_Reverse_Step_Motor  ( 2 )  //��ת-"Step_Motor �������"
#define STATE_Stop_Step_Motor     ( 3 )  //ͣת-"Step_Motor �������"



////////////////////////////////////////////////////////////////////////////
//==**��Ŀ"ר��"�궨��**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
  
extern union FLAGBIT Step_Motor_FlagBits; //"Step_Motor �������"��ر�־λ����
#define  G_Step_Motor_FlagBits      Step_Motor_FlagBits.FLAG16  
#define	 F_500ms_Reflash_Step_Motor Step_Motor_FlagBits.b.f0  //Ϊ1ʱ��ˢ��LCD_TFT��ʾ"ת��" ("Step_Motor �������")
//#define	 F_      Step_Motor_FlagBits.b.f1  //Ϊ1ʱ��
//#define	 F_      Step_Motor_FlagBits.b.f2  //Ϊ1ʱ��
//#define	 F_      Step_Motor_FlagBits.b.f3  //Ϊ1ʱ��
//#define	 F_      Step_Motor_FlagBits.b.f4  //Ϊ1ʱ��
//#define	 F_      Step_Motor_FlagBits.b.f5  //Ϊ1ʱ��
//#define	 F_      Step_Motor_FlagBits.b.f6  //Ϊ1ʱ��
//#define	 F_      Step_Motor_FlagBits.b.f7  //Ϊ1ʱ��



extern unsigned int G_Step_Speed;   //"Step_Motor �������"1����CCR3��������Ƶ�ʴ���

extern unsigned char G_Step_WorkState; //����״̬-"Step_Motor �������"

////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
//==**"����"�궨��**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"��������**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////

extern void Enable_Step_Motor(void); //ʹ��-"Step_Motor �������"

extern void Disable_Step_Motor(void);  //��ֹ-"Step_Motor �������"


////////////////////////////////////////////////////////////////////////////
//==**"�ⲿ" API ��������**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

extern void Step_Motor_Initial(void);  //��ʼ������:  "Step_Motor �������"

extern void Stop_Step_Motor(void);     //ͣת-"Step_Motor �������"
extern void Positive_Step_Motor(void); //��ת-"Step_Motor �������"(���ݵ�λ�Ƶ�ѹ���е���)
extern void Reverse_Step_Motor(void); //��ת-"Step_Motor �������"(���ݵ�λ�Ƶ�ѹ���е���)

extern void Deal_Step_Motor(void);  //�ж��д��������(����ת,ת��)

extern void Deal_Speed_Step_Motor(void); // ���㲽����ת��


#endif   /* __Step_Motor_H  */








