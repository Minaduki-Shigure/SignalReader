/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 HR202_Humidity.h
* �����ļ�-Dependencies:  	 None	
* �ļ�����-File Description:	 ( ͷ�ļ�-Header File )
	��"HR202_Humidity ������ʪ�ȴ�����" -��������(�ⲿ��Դ)-ͷ�ļ�
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

#ifndef  __HR202_Humidity_H 
#define  __HR202_Humidity_H 


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"�궨��**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**��Ŀ"ר��"�궨��**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
extern union FLAGBIT16 HR202_Humidity_FlagBits; //"HR202_Humidity ������ʪ�ȴ�����"��ر�־λ����
#define  G_HR202_Humidity_FlagBits HR202_Humidity_FlagBits.FLAG16  
//#define	 F_1s_HR202_Frequency      HR202_Humidity_FlagBits.b.f0  //Ϊ1ʱ��"ʪ��ֵ"��ӦƵ��ֵ(1s�ڵ��������)
#define	 F_500ms_Reflash_Humidity  HR202_Humidity_FlagBits.b.f1  //Ϊ1ʱ���ڳ�������ˢ��LCD_TFT ��ʾ("HR202_Humidity ������ʪ�ȴ�����" )
#define	 F_250ms_Sample_Humidity   HR202_Humidity_FlagBits.b.f2  //Ϊ1ʱ��250ms��ȡһ��ʪ��ֵ"��ӦƵ��ֵ
#define	 F_EnRead_Humidity         HR202_Humidity_FlagBits.b.f3  //Ϊ1ʱ�����Զ�ȡʪ��Ƶ��ֵ
//#define	 F_      HR202_Humidity_FlagBits.b.f4  //Ϊ1ʱ��
//#define	 F_      HR202_Humidity_FlagBits.b.f5  //Ϊ1ʱ��
//#define	 F_      HR202_Humidity_FlagBits.b.f6  //Ϊ1ʱ��
//#define	 F_      HR202_Humidity_FlagBits.b.f7  //Ϊ1ʱ��
//#define	 F_      HR202_Humidity_FlagBits.b.f8  //Ϊ1ʱ��
//#define	 F_      HR202_Humidity_FlagBits.b.f9  //Ϊ1ʱ��
//#define	 F_      HR202_Humidity_FlagBits.b.f10 //Ϊ1ʱ��
//#define	 F_      HR202_Humidity_FlagBits.b.f11 //Ϊ1ʱ��
//#define	 F_      HR202_Humidity_FlagBits.b.f12 //Ϊ1ʱ��
//#define	 F_      HR202_Humidity_FlagBits.b.f13 //Ϊ1ʱ�� 
//#define	 F_      HR202_Humidity_FlagBits.b.f14 //Ϊ1ʱ��
//#define	 F_      HR202_Humidity_FlagBits.b.f15 //Ϊ1ʱ��  

extern unsigned char G_HR202_Humidity;  //�����õ���"ʪ��ֵ"



////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
//==**"����"�궨��**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"��������**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////
	//��ʼ������:  "HR202_Humidity ������ʪ�ȴ�����"
extern void HR202_Humidity_Initial(void);

	//ת��"HR202_Humidity ������ʪ�ȴ�����" Ƶ��ֵΪʵ��"ʪ��ֵ"
extern unsigned char ConverseToHumidity(unsigned long R, int temperature);




////////////////////////////////////////////////////////////////////////////
//==**"�ⲿ" API ��������**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

	//1�붨ʱ��,ʹ�ܶ�ȡHR202��555�����Ƶ��
//extern void HR202_EnRead_Frequency(void);

	//���ж�,����"ʪ��ֵ"��ӦƵ��ֵ
extern void Sample_HR202_Frequency(void);



	//���� "HR202_Humidity ������ʪ�ȴ�����"
extern void Deal_HR202_Humidity(void);






#endif   /* __HR202_Humidity_H  */





