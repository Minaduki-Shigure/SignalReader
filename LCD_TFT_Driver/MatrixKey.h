/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 MatrixKey.h
* �����ļ�-Dependencies:  	 None	
* �ļ�����-File Description:	 ( ͷ�ļ�-Header File )
	��"���󰴼�" -��������(�ⲿ��Դ)-ͷ�ļ�
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


#ifndef  __MatrixKey_H 
#define  __MatrixKey_H 


/****************************************************************************
       ������IO��ʹ�ú궨�壬ͳһ��Hardware_Profile.h ����    

////////////////////////////////////////////////////////////////////////////
//==**������**PIC24F �ĵ�Ƭ��**==========================//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//==**������*IO��ʹ�ú궨��**==========================//

#define Buzz_TRIS	   TRISBbits.TRISB11 
#define Buzz_IO		   LATBbits.LATB11		 //���������IO��


////////////////////////////////////////////////////////////////////////////
//==**���󰴼�*IO��ʹ�ú궨��**=======================//

#define Y1_MatrixKey_IO   LATBbits.LATB12  //���//���󰴼���1��
#define Y1_MatrixKey_TRIS TRISBbits.TRISB12 


#define Y2_MatrixKey_IO   LATBbits.LATB8  //���//���󰴼���2��
#define Y2_MatrixKey_TRIS TRISBbits.TRISB8 

#define Y3_MatrixKey_IO   LATBbits.LATB9  //���//���󰴼���3��
#define Y3_MatrixKey_TRIS TRISBbits.TRISB9

#define MatrixKey_PORT    PORTB
#define MatrixKey_LAT     LATB


#define X1_MatrixKey_PT   PORTBbits.PORTB0  //����//���󰴼���1��
#define X1_MatrixKey_TRIS TRISBbits.TRISB0

#define X2_MatrixKey_PT   PORTBbits.PORTB1  //����//���󰴼���2��
#define X2_MatrixKey_TRIS TRISBbits.TRISB1

#define X3_MatrixKey_PT   PORTBbits.PORTB2  //����//���󰴼���3��
#define X3_MatrixKey_TRIS TRISBbits.TRISB2

#define X4_MatrixKey_PT   PORTBbits.PORTB3  //����//���󰴼���4��
#define X4_MatrixKey_TRIS TRISBbits.TRISB3

#define X5_MatrixKey_PT   PORTBbits.PORTB13  //����//���󰴼���5��
#define X5_MatrixKey_TRIS TRISBbits.TRISB13

////////////////////////////////////////////////////////////////////////////
//==**������**PIC18F ��PIC16Fϵ�еĵ�Ƭ��**===============//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//==**������*IO��ʹ�ú궨��**==========================//

#define Buzz_TRIS        TRISA4
#define Buzz_IO          RA4       //���������IO��


////////////////////////////////////////////////////////////////////////////
//==**���󰴼�*IO��ʹ�ú궨��**=======================//

#define Y1_MatrixKey_IO   LATB0  //���//���󰴼���1��
#define Y1_MatrixKey_TRIS 0TRISB0 


#define Y2_MatrixKey_IO  LATB1  //���//���󰴼���2��
#define Y2_MatrixKey_TRIS TRISB1

#define Y3_MatrixKey_IO   LATB2  //���//���󰴼���3��
#define Y3_MatrixKey_TRIS TRISB2

#define Y3_MatrixKey_IO   LATB3  //���//���󰴼���4��
#define Y3_MatrixKey_TRIS TRISB3

#define MatrixKey_PORT    PORTB
#define MatrixKey_LAT     LATB


#define X1_MatrixKey_PT   PORTB4  //����//���󰴼���1��
#define X1_MatrixKey_TRIS TRISB4

#define X2_MatrixKey_PT  PORTB5  //����//���󰴼���2��
#define X2_MatrixKey_TRIS TRISB5

#define X3_MatrixKey_PT   PORTB6  //����//���󰴼���3��
#define X3_MatrixKey_TRIS TRISB6

#define X4_MatrixKey_PT   PORTB7 //����//���󰴼���4��
#define X4_MatrixKey_TRIS TRISB7

***********************************************************************************/




////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"�궨��**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////

#define M_MatrixKeyDelayTime (2)   //���ڵ�������������(������ʱ��)����5msΪʱ��

#define M_MatrixKeyUsed      (0xFF)   //���ڶ����8��������������Ϊֻʹ�õ�1,2����ʱ������ M_MatrixKeyUsed��0x03 

#define M_NullMatrixKey      (0xFF)//���尴��Ϊ��Ч��


////////////////////////////////////////////////////////////////////////////
//--**"���󰴼�ֵ"�궨��**---------------------------------------//
////////////////////////////////////////////////////////////////////////////

#define MatrixKey_0      (0)    //����"����0��"
#define MatrixKey_1      (1)    //����"����1��"
#define MatrixKey_2      (2)    //����"����2��"
#define MatrixKey_3      (3)    //����"����3��"
#define MatrixKey_4      (4)    //����"����4��"
#define MatrixKey_5      (5)    //����"����5��"
#define MatrixKey_6      (6)    //����"����6��"
#define MatrixKey_7      (7)    //����"����7��"
#define MatrixKey_8      (8)    //����"����8��"
#define MatrixKey_9      (9)    //����"����9��"
#define MatrixKey_A      (0x0A) //����"����A��"
#define MatrixKey_B      (0x0B) //����"����B��"
#define MatrixKey_C      (0x0C) //����"����C��"
#define MatrixKey_D      (0x0D) //����"����D��"
#define MatrixKey_E      (0x0E) //����"����E��"
#define MatrixKey_F      (0x0F) //����"����F��"

#define MatrixKey_AC     (0x13) //����"AC��"
#define MatrixKey_Plus   (0x12) //����"+ ��"
#define MatrixKey_Minus  (0x11) //����"-��"
#define MatrixKey_Equal  (0x10) //����"=��"

#define MatrixKey_Return (0x13) //����"���ؼ�"
#define MatrixKey_OK     (0x10) //����"ȷ����"





/*****
////////////////////////////////////////////////////////////////////////////
//--**"����ʱ""���󰴼�ֵ"�궨��**----------------------------//
////////////////////////////////////////////////////////////////////////////

#define MatrixKey_Up       (0xFF)   //����"�Ϸ���"   
#define MatrixKey_Down   (0xFF)   //����"�·���"
#define MatrixKey_Left      (0x0A)   //����"���"
#define MatrixKey_Right    (0x0B)   //����"�Ҽ�"


#define MatrixKey_Return   (0x0C)   //����"���ؼ�"
#define MatrixKey_Delete   (0x0C)   //����"ɾ����"

#define MatrixKey_Menu    (0x0D)   //����"�˵���"
#define MatrixKey_Ok        (0x0E)   //����"ȷ����"


#define MatrixKey_Modify   (0x0D)   //����"�޸ļ�"

#define MatrixKey_Option   (0xFF)   //����"ѡ���"

////////////////////////////////////////////////////////////////////////////
//--**"���ƹ���ʱ""���󰴼�ֵ"�궨��**----------------------//
////////////////////////////////////////////////////////////////////////////

#define MatrixKey_Start     (0xFF)   //����"���м�"ֵ

#define MatrixKey_Stop     (0xFF)   //����"ֹͣ��"ֵ

#define MatrixKey_Test      (0xFF)   //����"���Լ�"ֵ

****/




////////////////////////////////////////////////////////////////////////////
//==**��Ŀ"ר��"�궨��**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
extern union FLAGBIT16 MatrixKeyFlagBits; //���󰴼��õ��ı�־λ����
#define  G_MatrixKeyFlagBits MatrixKeyFlagBits.FLAG16  
//#define	 F_MatrixScanKey   MatrixKeyFlagBits.b.f0    
#define  F_MatrixKeyHave     MatrixKeyFlagBits.b.f1
#define  F_MatrixKeyRead	 MatrixKeyFlagBits.b.f2	
#define  F_MatrixKeyNull     MatrixKeyFlagBits.b.f3	
#define  F_Ok_LongMatrixKey	 MatrixKeyFlagBits.b.f4   //"ȷ����"������־λ   
//#define   F_	MatrixKeyFlagBits.b.f5	
//#define  F_	MatrixKeyFlagBits.b.f6	
//#define  F_	MatrixKeyFlagBits.b.f7    
//#define   F_	MatrixKeyFlagBits.b.f8      
//#define   F_	MatrixKeyFlagBits.b.f9     
//#define   F_	MatrixKeyFlagBits.b.f10    
//#define   F_	MatrixKeyFlagBits.b.f11      
//#define   F_	MatrixKeyFlagBits.b.f12      
//#define   F_	MatrixKeyFlagBits.b.f13      
//#define   F_	MatrixKeyFlagBits.b.f14     
//#define   F_	MatrixKeyFlagBits.b.f15      
     

extern unsigned char G_MatrixKeyValue;  //����󰴼������İ���ֵ (����һ�㳣�õİ���)


extern unsigned char G_MatrixKeyBuf[32];  //��������Ķ������ֵ
extern unsigned char G_MatrixKeyCnt;  //������������ָ��

extern unsigned char G_TotalKeyNum;  //��������ְ����ܸ���
extern unsigned char G_DecimalPoint;  //��������ְ�����С����λ��(���ڹ����ʾ)
extern unsigned char G_KeyPlace_Row;    //(��)�������ò���λ��(���)��ʼλ��
extern unsigned char G_KeyPlace_Column; //(��)�������ò���λ��(���)��ʼλ��

extern unsigned int  G_KeyValue_Addr;  //�ɼ�������а����浽EEPROM/Flashָ����ַ




////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
//==**"����"�궨��**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"��������**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////

//extern unsigned char Sample_MatrixKey(void); //�����������ɨ��
//extern void Decode_MatrixKey(void);  //������̴���



////////////////////////////////////////////////////////////////////////////
//==**"�ⲿ" API ��������**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

extern void Scan_MatrixKey(void);  //"�������"ɨ�裬5msɨ��һ�ΰ���(�ж���)	

//extern void Decode_MatrixKey(void); //������̴���


extern unsigned char Detect_MatrixKey(void);  //�����û�а���,�����ذ���ֵ(����һ�㳣�õİ���)

extern unsigned char Detect_Press_MatrixKey(void); //����󰴼������İ���ֵ(����ִ�У��ɿ�ֹͣ)

extern unsigned char Detect_Long_MatrixKey(unsigned char SecondNum);//(����X����Ч)�����û�г����İ���,�����ذ���ֵ



extern unsigned char Detect_MatrixKey_0(void);//���"0" ���󰴼� ��û�а���
extern unsigned char Detect_MatrixKey_1(void);//���"1" ���󰴼� ��û�а���
extern unsigned char Detect_MatrixKey_2(void);//���"2" ���󰴼� ��û�а���
extern unsigned char Detect_MatrixKey_3(void);//���"3" ���󰴼� ��û�а���
extern unsigned char Detect_MatrixKey_4(void);//���"4" ���󰴼� ��û�а���
extern unsigned char Detect_MatrixKey_5(void);//���"5" ���󰴼� ��û�а���
extern unsigned char Detect_MatrixKey_6(void);//���"6" ���󰴼� ��û�а���
extern unsigned char Detect_MatrixKey_7(void);//���"7" ���󰴼� ��û�а���
extern unsigned char Detect_MatrixKey_8(void);//���"8" ���󰴼� ��û�а���
extern unsigned char Detect_MatrixKey_9(void);//���"9" ���󰴼� ��û�а���

extern unsigned char Detect_MatrixKey_A(void);//���"A" ���󰴼� ��û�а���
extern unsigned char Detect_MatrixKey_B(void);//���"B" ���󰴼� ��û�а���
extern unsigned char Detect_MatrixKey_C(void);//���"C" ���󰴼� ��û�а���
extern unsigned char Detect_MatrixKey_D(void);//���"D" ���󰴼� ��û�а���
extern unsigned char Detect_MatrixKey_E(void);//���"E" ���󰴼� ��û�а���
extern unsigned char Detect_MatrixKey_F(void);//���"F" ���󰴼� ��û�а���

extern unsigned char Detect_MatrixKey_AC(void);//���"AC" ���󰴼� ��û�а���
extern unsigned char Detect_MatrixKey_Plus(void);//���"+" ���󰴼� ��û�а���
extern unsigned char Detect_MatrixKey_Minus(void);//���"-" ���󰴼� ��û�а���
extern unsigned char Detect_MatrixKey_Equal(void);//���"=" ���󰴼� ��û�а���











#endif   /* __MatrixKey_H  */





