/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 TM1638.h
* �����ļ�-Dependencies:  	 None	
* �ļ�����-File Description:	 ( ͷ�ļ�-Header File )
	�� "TM1638 �����������" -��������-ͷ�ļ�(�ⲿ��Դ) 
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



#ifndef  __TM1638_H
#define  __TM1638_H


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"�궨��**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//--**��ʾ����(�����)**�궨��**-------------------------------//
#define Disp_Mode_Off   (0x80) //��ʾ"��"

#define Disp_Mode_1_16  (0x88) //��ʾ"��"+�Զ�"PWMΪ1/16" (�)
#define Disp_Mode_2_16  (0x89) //��ʾ"��"+�Զ�"PWMΪ2/16"
#define Disp_Mode_4_16  (0x8A) //��ʾ"��"+�Զ�"PWMΪ4/16"
#define Disp_Mode_10_16 (0x8B) //��ʾ"��"+�Զ�"PWMΪ10/16"
#define Disp_Mode_11_16 (0x8C) //��ʾ"��"+�Զ�"PWMΪ11/16"
#define Disp_Mode_12_16 (0x8D) //��ʾ"��"+�Զ�"PWMΪ12/16"
#define Disp_Mode_13_16 (0x8E) //��ʾ"��"+�Զ�"PWMΪ13/16"
#define Disp_Mode_14_16 (0x8F) //��ʾ"��"+�Զ�"PWMΪ14/16" (����)


////////////////////////////////////////////////////////////////////////////
//==**��������*�궨��**================================//

////////////////////////////////////////////////////////////////////////////
//--**��������***�궨��**-----------------------------------------//
#define CMD_IncreaseAddr_TM1638 (0X40) //Cmd���ַģʽ����: �Զ���ַ����(��������)
#define CMD_FixedAddr_TM1638    (0X44) //Cmd���ַģʽ����: �̶���ַ(��������)



////////////////////////////////////////////////////////////////////////////
//--**��ַ����***�궨��**-----------------------------------------//
#define	CMD_DispAddr_TM1638	(0xC0)  //Cmd����ʾ��ַ����

#define	ADDR_No1_TM1638	 (0xC6)  //Addr����"1λ"�����(�����ұ�����) ��ʾ��ַ(TM1638)
#define	ADDR_No2_TM1638	 (0xC4)  //Addr����"2λ"�����(�����ұ�����) ��ʾ��ַ(TM1638)
#define	ADDR_No3_TM1638	 (0xC2)  //Addr����"3λ"�����(�����ұ�����) ��ʾ��ַ(TM1638)
#define	ADDR_No4_TM1638	 (0xC0)  //Addr����"4λ"�����(�����ұ�����) ��ʾ��ַ(TM1638)
#define	ADDR_No5_TM1638	 (0xCE)  //Addr����"5λ"�����(�����ұ�����) ��ʾ��ַ(TM1638)
#define	ADDR_No6_TM1638	 (0xCC)  //Addr����"6λ"�����(�����ұ�����) ��ʾ��ַ(TM1638)
#define	ADDR_No7_TM1638	 (0xCA)  //Addr����"7λ"�����(�����ұ�����) ��ʾ��ַ(TM1638)
#define	ADDR_No8_TM1638	 (0xC8)  //Addr����"8λ"�����(�����ұ�����) ��ʾ��ַ(TM1638)



////////////////////////////////////////////////////////////////////////////
//==**"��̬�����LED_Segment" ��ʾ����Ӧ"��ʾ�ַ�"**===//
#define	DISP_MaxNum_LedSeg ( 22 ) //DISP��"����22����ʾ�ַ�""��̬�����LED_Segment" 

#define	DISP_0_LedSeg     ( 0 ) //DISP��"0"--"��̬�����LED_Segment" 
#define	DISP_1_LedSeg     ( 1 ) //DISP��"1"--"��̬�����LED_Segment" 
#define	DISP_2_LedSeg     ( 2 ) //DISP��"2"--"��̬�����LED_Segment" 
#define	DISP_3_LedSeg     ( 3 ) //DISP��"3"--"��̬�����LED_Segment" 
#define	DISP_4_LedSeg     ( 4 ) //DISP��"4"--"��̬�����LED_Segment" 
#define	DISP_5_LedSeg     ( 5 ) //DISP��"5"--"��̬�����LED_Segment" 
#define	DISP_6_LedSeg     ( 6 ) //DISP��"6"--"��̬�����LED_Segment" 
#define	DISP_7_LedSeg     ( 7 ) //DISP��"7"--"��̬�����LED_Segment" 
#define	DISP_8_LedSeg     ( 8 ) //DISP��"8"--"��̬�����LED_Segment" 
#define	DISP_9_LedSeg     ( 9 ) //DISP��"9"--"��̬�����LED_Segment" 

#define	DISP_A_LedSeg     ( 10 ) //DISP��"A"--"��̬�����LED_Segment" 
#define	DISP_b_LedSeg     ( 11 ) //DISP��"b"--"��̬�����LED_Segment" 
#define	DISP_C_LedSeg     ( 12 ) //DISP��"C"--"��̬�����LED_Segment" 
#define	DISP_d_LedSeg     ( 13 ) //DISP��"d"--"��̬�����LED_Segment" 
#define	DISP_E_LedSeg     ( 14 ) //DISP��"E"--"��̬�����LED_Segment" 
#define	DISP_F_LedSeg     ( 15 ) //DISP��"F"--"��̬�����LED_Segment" 

#define	DISP_Point_LedSeg ( 16 ) //DISP��"."(С����)--"��̬�����LED_Segment" 
#define	DISP_Plus_LedSeg  ( 17 ) //DISP��"+"(�Ӻ�,����)--"��̬�����LED_Segment" 
#define	DISP_Minus_LedSeg ( 18 ) //DISP��"-"(����,����)--"��̬�����LED_Segment" 
#define	DISP_Equal_LedSeg ( 19 ) //DISP��"="(���ں�)--"��̬�����LED_Segment" 

#define	DISP_ON_LedSeg    ( 20 ) //DISP��"ȫ��"--"��̬�����LED_Segment" 
#define	DISP_OFF_LedSeg   ( 21 ) //DISP��"����"--"��̬�����LED_Segment" 

#define	DISP_I_LedSeg     ( 22 ) //DISP��"I"--"��̬�����LED_Segment" 
#define	DISP_r_LedSeg     ( 23 ) //DISP��"r"--"��̬�����LED_Segment" 
#define	DISP_U_LedSeg     ( 24 ) //DISP��"U"--"��̬�����LED_Segment" 









////////////////////////////////////////////////////////////////////////////
//==**��Ŀ"ר��"�궨��**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////


#define	M_LedAllOff_TM1638    (1)  //"����"�����: ���ر���ʾ
#define	M_LedAllOn_TM1638     (2)  //��������ܵ�"����Led��"ȫ��


#define	M_LedLoopNum_TM1638	 (3)  //"����"�����: ͬʱ"ѭ��"��ʾ"��ͬ"�ַ�
#define	M_LedKeyNum_TM1638	 (4)  //����"����"���ڶ�Ӧ�ĵ�"x"������ܣ���ʾ"x"




////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
extern union FLAGBIT16 TM1638_FlagBits;  //"TM1638"�õ���ʱ���־λ
#define  G_TM1638_FlagBits TM1638_FlagBits.FLAG16  
//#define  F_         TM1638_FlagBits.b.f0 //Ϊ1ʱ��
//#define  F_         TM1638_FlagBits.b.f1  //Ϊ1ʱ��
//#define  F_ 	   TM1638_FlagBits.b.f2  //Ϊ1ʱ��
//#define  F_	   TM1638_FlagBits.b.f3  //Ϊ1ʱ��	 
//#define  F_         TM1638_FlagBits.b.f4  //Ϊ1ʱ��
//#define  F_         TM1638_FlagBits.b.f5  //Ϊ1ʱ��   
//#define  F_	   TM1638_FlagBits.b.f6  //Ϊ1ʱ��   
//#define  F_         TM1638_FlagBits.b.f7  //Ϊ1ʱ�� 
//#define  F_	   TM1638_FlagBits.b.f8  //Ϊ1ʱ��  
//#define  F_	   TM1638_FlagBits.b.f9  //Ϊ1ʱ��	 
//#define  F_	   TM1638_FlagBits.b.f10 //Ϊ1ʱ��	 
//#define  F_	   TM1638_FlagBits.b.f11 //Ϊ1ʱ��	 
//#define  F_	   TM1638_FlagBits.b.f12 //Ϊ1ʱ��	 	 
//#define  F_	   TM1638_FlagBits.b.f13 //Ϊ1ʱ��	 	 
//#define  F_	   TM1638_FlagBits.b.f14 //Ϊ1ʱ��	  
//#define  F_	   TM1638_FlagBits.b.f15 //Ϊ1ʱ��	 	 




extern unsigned char G_TM1638_DispMode; //TM1638����ʾ�Զȱ���



////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**"����"�궨��**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"��������**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////

	//������ʾģʽ:��ʾ�ء���ʾ��+�Զȵ���(��ͬPWMռ�ձ�����)(TM1638)
extern void TM1638_Disp_Mode(unsigned char Disp_Mode);






////////////////////////////////////////////////////////////////////////////
//==**"�ⲿ" API ��������**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

	//ָ��"����"�����: ��ָ��"�Զ�"��ʾ�ַ�(TM1638)
extern void Disp_Single_LedSeg(unsigned char Num,unsigned char Disp_Mode,unsigned char Data);  


	//������ʾģʽ:��ʾ��(TM1638)
extern void Close_Display_TM1638(void);

	//����ʾ(��ʼ��):��ʾ"��"+�Զ�"PWMΪ1/16" (�)(TM1638)
extern void Open_Display_TM1638(void);

	//��TM1638��ʾ��ַдҪ"��ʾ������"(TM1638)
extern void Write_DispData_TM1638(unsigned char pointNum1,unsigned char pointNum2,unsigned char NO_8,unsigned char NO_7,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1);

	//����"��̬�����LED_Segment" :��ʾ�أ���ʾ��������"�Զ�PWM"(TM1638)
extern void Deal_Brightness_TM1638(unsigned char DispMode);


	//�����󰴼�ֵ(TM1638)
extern unsigned char Read_MatrixKey_TM1638(void);




#endif    /* __TM1638_H */


