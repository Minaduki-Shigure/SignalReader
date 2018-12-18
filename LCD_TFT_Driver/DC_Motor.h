/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 DC_Motor.h
* �����ļ�-Dependencies:  	 None	
* �ļ�����-File Description:	 ( ͷ�ļ�-Header File )
	��"DC_Motor ֱ�����"-��������(�ⲿ��Դ)-ͷ�ļ�
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

#ifndef  __DC_Motor_H 
#define  __DC_Motor_H 


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"�궨��**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////
#define STATE_Idle_DC_Motor     ( 0 )  //�ձ�-"DC_Motor ֱ�����"
#define STATE_Positive_DC_Motor ( 1 )  //��ת-"DC_Motor ֱ�����"
#define STATE_Reverse_DC_Motor  ( 2 )  //��ת-"DC_Motor ֱ�����"
#define STATE_Stop_DC_Motor     ( 3 )  //ͣת-"DC_Motor ֱ�����"



////////////////////////////////////////////////////////////////////////////
//==**��Ŀ"ר��"�궨��**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
//////////////////////////////////////////////////////////////////////////// 
extern union FLAGBIT DC_Motor_FlagBits; //"DC_Motor ֱ�����"��ر�־λ����
#define  G_DC_Motor_FlagBits      DC_Motor_FlagBits.FLAG16  
#define	 F_1s_Frequency_DC_Motor  DC_Motor_FlagBits.b.f0  //Ϊ1ʱ��ֱ�����ת��(1s�ڵ��������)
#define	 F_500ms_Reflash_DC_Motor DC_Motor_FlagBits.b.f1  //Ϊ1ʱ��ˢ��LCD_TFT��ʾ"ת��" ("DC_Motor ֱ�����")
//#define	 F_      DC_Motor_FlagBits.b.f2  //Ϊ1ʱ��
//#define	 F_      DC_Motor_FlagBits.b.f3  //Ϊ1ʱ��
//#define	 F_      DC_Motor_FlagBits.b.f4  //Ϊ1ʱ��
//#define	 F_      DC_Motor_FlagBits.b.f5  //Ϊ1ʱ��
//#define	 F_      DC_Motor_FlagBits.b.f6  //Ϊ1ʱ��
//#define	 F_      DC_Motor_FlagBits.b.f7  //Ϊ1ʱ��
//#define	 F_      DC_Motor_FlagBits.b.f8  //Ϊ1ʱ��
//#define	 F_      DC_Motor_FlagBits.b.f9  //Ϊ1ʱ��
//#define	 F_      DC_Motor_FlagBits.b.f10 //Ϊ1ʱ��
//#define	 F_      DC_Motor_FlagBits.b.f11 //Ϊ1ʱ��
//#define	 F_      DC_Motor_FlagBits.b.f12 //Ϊ1ʱ��
//#define	 F_      DC_Motor_FlagBits.b.f13 //Ϊ1ʱ�� 
//#define	 F_      DC_Motor_FlagBits.b.f14 //Ϊ1ʱ��
//#define	 F_      DC_Motor_FlagBits.b.f15 //Ϊ1ʱ��  


extern unsigned int G_DC_SpeedCnt; //DC_Motor ֱ�����"1����CCR3��������Ƶ���ۼ���
extern unsigned int G_DC_Speed;  //DC_Motor ֱ�����"1����CCR3��������Ƶ�ʴ���
extern unsigned char G_DC_WorkState; //����״̬-DC_Motor ֱ�����"



////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
//==**"����"�궨��**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"��������**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////

extern void Disable_DC_Motor(void);  //��ֹ-"DC_Motor ֱ�����"

extern void Enable_DC_Motor(void);  //ʹ��-"DC_Motor ֱ�����"



////////////////////////////////////////////////////////////////////////////
//==**"�ⲿ" API ��������**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

extern void DC_Motor_Initial(void);  //��ʼ������:  "DC_Motor ֱ�����"

	//����"DC_Motor ֱ�����"ת��(1s�ڵ��������)
extern void Sample_DC_Motor_Frequency(void);


extern void Stop_PWM_DC_Motor(void);  //ֹͣPWM���-"DC_Motor ֱ�����"

extern void Stop_DC_Motor(void);  //ͣת-"DC_Motor ֱ�����"

extern void Positive_DC_Motor(void);  //��ת-"DC_Motor ֱ�����"(���ݵ�λ�Ƶ�ѹ���е���)

extern void Reverse_DC_Motor(void);  //��ת-"DC_Motor ֱ�����"(���ݵ�λ�Ƶ�ѹ���е���)





#endif   /* __DC_Motor_H  */





