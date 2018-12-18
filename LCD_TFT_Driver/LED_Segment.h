/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 LED_Segment.h
* �����ļ�-Dependencies:  	 None	
* �ļ�����-File Description:	 ( ͷ�ļ�-Header File )
	��"��̬�����LED_Segment" -��������(�ⲿ��Դ)-ͷ�ļ�
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



#ifndef  __LED_Segment_H 
#define  __LED_Segment_H 





////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"�궨��**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////






/////////////////////////////////////////////////////////////////////////////////
//==**"��̬�����LED_Segment" ���Ⱥ궨��**===================//
#define	M_Brightness_OFF_LedSeg ( 0 ) //����Ϊ0 (��ʾ��)--"��̬�����LED_Segment" 
#define	M_Brightness_1_LedSeg   ( 1 ) //����Ϊ1(�)--"��̬�����LED_Segment" 
#define	M_Brightness_2_LedSeg   ( 2 ) //����Ϊ2--"��̬�����LED_Segment" 
#define	M_Brightness_3_LedSeg   ( 3 ) //����Ϊ3--"��̬�����LED_Segment" 
#define	M_Brightness_4_LedSeg   ( 4 ) //����Ϊ4--"��̬�����LED_Segment" 
#define	M_Brightness_5_LedSeg   ( 5 ) //����Ϊ5--"��̬�����LED_Segment" 
#define	M_Brightness_6_LedSeg   ( 6 ) //����Ϊ6--"��̬�����LED_Segment" 
#define	M_Brightness_7_LedSeg   ( 7 ) //����Ϊ7--"��̬�����LED_Segment" 
#define	M_Brightness_8_LedSeg   ( 8 ) //����Ϊ8(����)--"��̬�����LED_Segment" 





/////////////////////////////////////////////////////////////////////////////////
//==**"��ģ��(��̬�����LED_Segment )ר��"����ģʽ"�궨��**=//
#define	MODE_Idle_LED_Segment       (0) //Mode������(�����κβ���)("��̬�����LED_Segment" )
#define	MODE_Open_LED_Segment       (1) //Mode��"��"��ģ��("��̬�����LED_Segment" )
#define	MODE_Close_LED_Segment      (2) //Mode��"�ر�"��ģ��("��̬�����LED_Segment" )	
#define	MODE_Refresh_LED_Segment    (3) //Mode��������ʾ("��̬�����LED_Segment" )



////////////////////////////////////////////////////////////////////////////
//==**��Ŀ"ר��"�궨��**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
//--**"��̬�����LED_Segment" *ȫ�ֱ�־λ**------------------------------//
extern union FLAGBIT16 LED_Seg_FlagBits; //"��̬�����LED_Segment" ��ر�־λ����
#define  G_LED_Seg_FlagBits   LED_Seg_FlagBits.FLAG16  
#define	 F_500ms_LedSeg       LED_Seg_FlagBits.b.f0  //"��̬�����LED_Segment" ��ʾ"���"ʱ��
#define	 F_En_Scan_MatrixKey  LED_Seg_FlagBits.b.f1  //Ϊ1ʱ��ʹ��"���󰴼�ɨ��",  Ϊ0ʱ����ֹɨ��"���󰴼�ɨ��"
//#define	 F_      LED_Seg_FlagBits.b.f2  //Ϊ1ʱ��
//#define	 F_      LED_Seg_FlagBits.b.f3  //Ϊ1ʱ��
//#define	 F_      LED_Seg_FlagBits.b.f4  //Ϊ1ʱ��
//#define	 F_      LED_Seg_FlagBits.b.f5  //Ϊ1ʱ��
//#define	 F_      LED_Seg_FlagBits.b.f6  //Ϊ1ʱ��
//#define	 F_      LED_Seg_FlagBits.b.f7  //Ϊ1ʱ��
//#define	 F_      LED_Seg_FlagBits.b.f8  //Ϊ1ʱ��
//#define	 F_      LED_Seg_FlagBits.b.f9  //Ϊ1ʱ��
//#define	 F_      LED_Seg_FlagBits.b.f10 //Ϊ1ʱ��
//#define	 F_      LED_Seg_FlagBits.b.f11 //Ϊ1ʱ��
//#define	 F_      LED_Seg_FlagBits.b.f12 //Ϊ1ʱ��
//#define	 F_      LED_Seg_FlagBits.b.f13 //Ϊ1ʱ�� 
//#define	 F_      LED_Seg_FlagBits.b.f14 //Ϊ1ʱ��
//#define	 F_      LED_Seg_FlagBits.b.f15 //Ϊ1ʱ��  


extern unsigned char G_Mode_LED_Segment; //"��̬�����LED_Segment" ����ģʽ
extern unsigned char G_Last_Mode_LED_Segment; //������һ��"����ģʽ"

extern unsigned char G_LedSeg_Cnt; //"��̬�����LED_Segment" ���õ��ļ�����(�����ַ�ѭ����ʾ)
extern unsigned char G_LedSegBuf[10]; //"��̬�����LED_Segment" ��ʾ��������//G_LedSegBuf[0]��Ӧ��"�ұ�"����ʾ�ַ�

extern unsigned char G_Brightness_LedSeg;  //���ȵ���-"��̬�����LED_Segment" 
extern unsigned char G_BrightnessKind;     //���ȱ���-"��̬�����LED_Segment" 




////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
//==**"����"�궨��**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"��������**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
//==**"�ⲿ" API ��������**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

	//��ʾ"��"+�Զ�"PWMΪ1/16" (�)("��̬�����LED_Segment" )
extern void Open_LED_Segment(void);

	//�ر�LED_Segment ("��̬�����LED_Segment" )
extern void Close_LED_Segment(void);

	//���������"�Զ�(����)"("��̬�����LED_Segment" )
extern void Deal_Brightness_LED_Segment(void);

	//������ʾ("��̬�����LED_Segment" )
extern void Refresh_LED_Segment(void);


	//��ʹ��"����ģʽ"("��̬�����LED_Segment" )
extern void Init_Mode_LED_Segment(unsigned char Mode);

	//"��̬�����LED_Segment" : ����ͬ"����ģʽ"
extern void Deal_LED_Segment(void);

	//"��ʾ�ַ�"���µ�"��ʾ��������"("��̬�����LED_Segment" )
extern void Disp_LED_Segment(unsigned char pointNum1,unsigned char pointNum2,unsigned char NO_8,unsigned char NO_7,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1);


#endif   /* __LED_Segment_H  */





