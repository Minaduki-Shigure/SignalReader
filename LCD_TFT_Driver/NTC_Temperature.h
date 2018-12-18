/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 NTC_Temperature.h
* �����ļ�-Dependencies:  	 None	
* �ļ�����-File Description:	 ( ͷ�ļ�-Header File )
	��"NTC �����¶ȴ�����" -��������(�ⲿ��Դ)-ͷ�ļ�
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

#ifndef  __NTC_Temperature_H 
#define  __NTC_Temperature_H 


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"�궨��**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////
#define M_NTC_TMP_AdSampleNum  (16) //AD������������ȡƽ��ֵ 




////////////////////////////////////////////////////////////////////////////
//==**��Ŀ"ר��"�궨��**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
extern union FLAGBIT16 NTC_TMP_FlagBits;  //"NTC �����¶ȴ�����" ��ر�־λ����
#define  G_NTC_TMP_FlagBits       NTC_TMP_FlagBits.FLAG16  
#define	 F_500ms_Reflash_NTC_TMP  NTC_TMP_FlagBits.b.f0  //Ϊ1ʱ���ڳ�������ˢ��LCD_TFT����ʾ("NTC �����¶ȴ�����"  )
#define	 F_500ms_NTC_HR202_InTest NTC_TMP_FlagBits.b.f1  //Ϊ1ʱ���ڲ�������ˢ��LCD_TFT��ʾNTC���¶ȣ���HR202��ʪ�ȣ�
//#define	 F_      NTC_TMP_FlagBits.b.f2  //Ϊ1ʱ��
//#define	 F_      NTC_TMP_FlagBits.b.f3  //Ϊ1ʱ��
//#define	 F_      NTC_TMP_FlagBits.b.f4  //Ϊ1ʱ��
//#define	 F_      NTC_TMP_FlagBits.b.f5  //Ϊ1ʱ��
//#define	 F_      NTC_TMP_FlagBits.b.f6  //Ϊ1ʱ��
//#define	 F_      NTC_TMP_FlagBits.b.f7  //Ϊ1ʱ��
//#define	 F_      NTC_TMP_FlagBits.b.f8  //Ϊ1ʱ��
//#define	 F_      NTC_TMP_FlagBits.b.f9  //Ϊ1ʱ��
//#define	 F_      NTC_TMP_FlagBits.b.f10 //Ϊ1ʱ��
//#define	 F_      NTC_TMP_FlagBits.b.f11 //Ϊ1ʱ��
//#define	 F_      NTC_TMP_FlagBits.b.f12 //Ϊ1ʱ��
//#define	 F_      NTC_TMP_FlagBits.b.f13 //Ϊ1ʱ�� 
//#define	 F_      NTC_TMP_FlagBits.b.f14 //Ϊ1ʱ��
//#define	 F_      NTC_TMP_FlagBits.b.f15 //Ϊ1ʱ��  


extern int G_NTC_Temperature; //��M_NTC_TMP_AdSampleNum��AD����ֵ��С��������󣬲�ת��Ϊ����ʵ��������




////////////////////////////////////////////////////////////////////////////
//==**"����"�궨��**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"��������**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////

	//ת��"NTC �����¶ȴ�����" ADֵΪʵ��"�¶�ֵ"
extern int ConverseToTemperature(long R);

extern void Sample_NTC_TMP_AD(void); //��β���"NTC �����¶ȴ�����" AD

////////////////////////////////////////////////////////////////////////////
//==**"�ⲿ" API ��������**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

	//���� "NTC �����¶ȴ�����" : AD������AD���ݴ�����ʾ����
extern void Deal_NTC_Temperature(void);







#endif   /* __NTC_Temperature_H  */





