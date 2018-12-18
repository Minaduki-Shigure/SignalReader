/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 LCD_Segment.h
* �����ļ�-Dependencies:  	 None	
* �ļ�����-File Description:	 ( ͷ�ļ�-Header File )
	��"��ʽLCD_Segment" -��������(�ⲿ��Դ)-ͷ�ļ�
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



#ifndef  __LCD_Segment_H 
#define  __LCD_Segment_H 





////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"�궨��**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//==**""��ʽLCD_Segment" ������С�εĺ� ����**============//
#define  dd  (0x01)
#define  cc  (0x20)
#define  bb  (0x40) //���ܶ���Ϊ #define  b  (0x40),��Ϊ��  FLAGBIT�����õ�"b"
#define  aa  (0x80)
#define  dp  (0x10)
#define  gg  (0x04)
#define  ff  (0x08)
#define  ee  (0x02)

////////////////////////////////////////////////////////////////////////////
//==**"��ʽLCD_Segment" ��ʾ����Ӧ��"��ʾ�ַ�"**=======//
#define	DISP_MaxNum_LcdSeg ( 22 ) //DISP��"����22����ʾ�ַ�""��ʽLCD_Segment" 

#define	DISP_0_LcdSeg     ( 0 ) //DISP��"0"--"��ʽLCD_Segment" 
#define	DISP_1_LcdSeg     ( 1 ) //DISP��"1"--"��ʽLCD_Segment" 
#define	DISP_2_LcdSeg     ( 2 ) //DISP��"2"--"��ʽLCD_Segment" 
#define	DISP_3_LcdSeg     ( 3 ) //DISP��"3"--"��ʽLCD_Segment" 
#define	DISP_4_LcdSeg     ( 4 ) //DISP��"4"--"��ʽLCD_Segment" 
#define	DISP_5_LcdSeg     ( 5 ) //DISP��"5"--"��ʽLCD_Segment" 
#define	DISP_6_LcdSeg     ( 6 ) //DISP��"6"--"��ʽLCD_Segment" 
#define	DISP_7_LcdSeg     ( 7 ) //DISP��"7"--"��ʽLCD_Segment" 
#define	DISP_8_LcdSeg     ( 8 ) //DISP��"8"--"��ʽLCD_Segment" 
#define	DISP_9_LcdSeg     ( 9 ) //DISP��"9"--"��ʽLCD_Segment" 

#define	DISP_A_LcdSeg     ( 10 ) //DISP��"A"--"��ʽLCD_Segment"
#define	DISP_b_LcdSeg     ( 11 ) //DISP��"b"--"��ʽLCD_Segment"
#define	DISP_c_LcdSeg     ( 12 ) //DISP��"C"--"��ʽLCD_Segment"
#define	DISP_d_LcdSeg     ( 13 ) //DISP��"d"--"��ʽLCD_Segment"
#define	DISP_E_LcdSeg     ( 14 ) //DISP��"E"--"��ʽLCD_Segment" 
#define	DISP_F_LcdSeg     ( 15 ) //DISP��"F"--"��ʽLCD_Segment" 

#define	DISP_Point_LcdSeg ( 16 ) //DISP��"."(С����)--"��ʽLCD_Segment" 
#define	DISP_Plus_LcdSeg  ( 17 ) //DISP��"+"(�Ӻ�,����)--"��ʽLCD_Segment" 
#define	DISP_Minus_LcdSeg ( 18 ) //DISP��"-"(����,����)--"��ʽLCD_Segment" 
#define	DISP_Equal_LcdSeg ( 19 ) //DISP��"="(���ں�)--"��ʽLCD_Segment" 

#define	DISP_ON_LcdSeg    ( 20 ) //DISP��"ȫ��"--"��ʽLCD_Segment" 
#define	DISP_OFF_LcdSeg   ( 21 ) //DISP��"����"--"��ʽLCD_Segment" 




////////////////////////////////////////////////////////////////////////////
//==**"��ģ��(��ʽLCD_Segment)ר��"����ģʽ"�궨��**=====//

#define	MODE_Idle_LCD_Segment           (0) //Mode������(�����κβ���)(��ʽLCD_Segment)
#define	MODE_Open_LCD_Segment           (1) //Mode��"��"��ģ��(��ʽLCD_Segment)
#define	MODE_Close_LCD_Segment          (2) //Mode��"�ر�"��ģ��(��ʽLCD_Segment)	
#define	MODE_Refresh_LCD_Segment        (3) //Mode��������ʾ(��ʽLCD_Segment)
#define	MODE_OpenBackLight_LCD_Segment  (4) //Mode��"��"����(��ʽLCD_Segment)		
#define	MODE_CloseBackLight_LCD_Segment (5) //Mode��"�ر�"����(��ʽLCD_Segment)		
		



////////////////////////////////////////////////////////////////////////////
//==**��Ŀ"ר��"�궨��**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//--**LCD_Segment*ȫ�ֱ�־λ**-------------------------------------//

extern union FLAGBIT16 LCD_Seg_FlagBits;	//"��ʽLCD_Segment"��ر�־λ����
#define  G_LCD_Seg_FlagBits LCD_Seg_FlagBits.FLAG16  
#define	 F_500ms_LcdSeg     LCD_Seg_FlagBits.b.f0  //"��ʽLCD_Segment"��ʾ"���"ʱ��
//#define	 F_      LCD_Seg_FlagBits.b.f1  //Ϊ1ʱ��
//#define	 F_      LCD_Seg_FlagBits.b.f2  //Ϊ1ʱ��
//#define	 F_      LCD_Seg_FlagBits.b.f3  //Ϊ1ʱ��
//#define	 F_      LCD_Seg_FlagBits.b.f4  //Ϊ1ʱ��
//#define	 F_      LCD_Seg_FlagBits.b.f5  //Ϊ1ʱ��
//#define	 F_      LCD_Seg_FlagBits.b.f6  //Ϊ1ʱ��
//#define	 F_      LCD_Seg_FlagBits.b.f7  //Ϊ1ʱ��
//#define	 F_      LCD_Seg_FlagBits.b.f8  //Ϊ1ʱ��
//#define	 F_      LCD_Seg_FlagBits.b.f9  //Ϊ1ʱ��
//#define	 F_      LCD_Seg_FlagBits.b.f10 //Ϊ1ʱ��
//#define	 F_      LCD_Seg_FlagBits.b.f11 //Ϊ1ʱ��
//#define	 F_      LCD_Seg_FlagBits.b.f12 //Ϊ1ʱ��
//#define	 F_      LCD_Seg_FlagBits.b.f13 //Ϊ1ʱ�� 
//#define	 F_      LCD_Seg_FlagBits.b.f14 //Ϊ1ʱ��
//#define	 F_      LCD_Seg_FlagBits.b.f15 //Ϊ1ʱ��  

extern unsigned char G_Mode_LCD_Segment; //"��ʽLCD_Segment"����ģʽ
extern unsigned char G_Last_Mode_LCD_Segment; //������һ��"����ģʽ"


extern unsigned char G_LcdSeg_Cnt; //"��ʽLCD_Segment"���õ��ļ�����(�����ַ�ѭ����ʾ)

extern unsigned char G_LcdSegBuf[7]; //"��ʽLCD_Segment"��ʾ��������//G_LcdSegBuf[0]��Ӧ��"�ұ�"����ʾ�ַ�




////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
//==**"����"�궨��**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"��������**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////
	//�򿪻��߹ر�Һ��LCD_B ģ��
extern void EnModule_LCD_Segment(unsigned char EnBit);  

	//ʹ�ܻ��ֹ����LCD_B��(��������Һ����(����)����˸)
extern void EnAllSeg_LCD_Segment(unsigned char EnBit); 

	//����: ����������ڲ���"��ʽLCD ��ʾ����"
extern void Clear_LCD_Segment(void);   


extern void Open_LCD_Segment(void); //��LCD_Segment (��ʹ��): LCD_Segment �ڲ��Ĵ�������; �˿ڳ�ʼ����

extern void Close_LCD_Segment(void);  //�ر�"��ʽLCD_Segment"


extern void Initial_LCD_Segment_LCD_B(void); //LCD_Bģ���ʼ��:�˿ڳ�ʼ��������LCD_B����(LCD_Segment )

	 //������ʾ(��ʽLCD_Segment)
extern void Refresh_LCD_Segment(unsigned char pointNum,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1); 


////////////////////////////////////////////////////////////////////////////
//==**"�ⲿ" API ��������**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

	//��ʹ��"����ģʽ"(��ʽLCD_Segment)
extern void Init_Mode_LCD_Segment(unsigned char Mode);

	//"��ʽLCD_Segment": ����ͬ"����ģʽ"
extern void Deal_LCD_Segment(void);  

	//"��ʾ�ַ�"���µ�"��ʾ��������"(��ʽLCD_Segment)
extern void Disp_LCD_Segment(unsigned char pointNum,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1);


#endif   /* __LCD_Segment_H  */





