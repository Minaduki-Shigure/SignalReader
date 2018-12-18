/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 LCD_TFT_ILI9325.h
* �����ļ�-Dependencies:  	 None	
* �ļ�����-File Description:	 ( ͷ�ļ�-Header File )
	�� "����LCD_TFT_ILI9325" -��������-ͷ�ļ�(�ⲿ��Դ) 
	01) 	     02)     03)    04)    05)    06)	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ע������-Attention : 	
	��01)  Ҫװ��ͷ�ļ� "stdint.h" (������һЩ��������(��׼C���ͷ�ļ�))	
							��:uint8_t; uint16_t ����"stdint.h"ͷ�ļ�����
							����posix��׼��һ�����Ͷ�Ӧ��*_t����
	��02)     ��03)    ��04)    ��05)    ��06)     
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
* �޸ļ�¼-Change History:   
	����   ʱ��        �汾  ��������
	Author 	 Date		   Rev      Comment
	-------------------------------------------------------------------------------
	BlueS	2012-08-01	  1.0	   
			xxxx-xx-xx	  x.x	   
			xxxx-xx-xx	  x.x				
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
* ��˾-Company: 			CS-EMLAB  Co. , Ltd.
* ������Э��-Software License Agreement:
	Copyright (C) 2012-2020 	CS-EMLAB  Co. , Ltd.	All rights reserved.	

*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#ifndef __LCD_TFT_ILI9325_H   //"����LCD_TFT_ILI9325" -��������-ͷ�ļ�(�ⲿ��Դ) 
#define __LCD_TFT_ILI9325_H 



////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"�궨��**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////


//������ɫ
#define BLACK	     0x0000  // ��ɫ    0,   0,   0
#define WHITE	     0xFFFF  // ��ɫ    255, 255, 255  

#define RED  	     0xF800  // ��ɫ    255,   0,   0    
#define BRED         0XF81F
#define BRRED 	     0XFC07  //�غ�ɫ
#define GRED 	     0XFFE0
#define MAROON       0x7800  //���ɫ  127,   0,   0      
#define MAGENTA      0xF81F  //Ʒ��    255,   0, 255      

#define BROWN 	     0XBC40  //��ɫ


#define GREEN        0x07E0  //��ɫ    0, 255,   0     
//#define LGREEN       0x07FC  //ǳ��ɫ 
//#define LGREEN       0x07FA  //ǳ��ɫ 
#define LGREEN       0x07F8  //ǳ��ɫ 



#define OLIVE        0x7BE0  //�����  127, 127,   0      
#define DGREEN       0x03E0  //����ɫ  0,  127,  0
#define DCYAN        0x03EF  //����ɫ  0,  127, 127       


#define BLUE 	     0x001F  //��ɫ    0,   0, 255     
#define GBLUE	     0X07FF  //ǳ��ɫ//��ʾ�ַ���ʱ������������ɫ��Ϊ����ɫ
#define LBLUE	     0X07FF  //ǳ��ɫ
#define NAVY         0x000F  //����ɫ  0,   0, 127
#define CYAN         0x07FF  //��ɫ    0, 255, 255               


#define YELLOW       0xFFE0  //��ɫ    255, 255, 0       


#define GRAY0        0xEF7D  //��ɫ0 3165 00110 001011 00101
#define GRAY1        0x8410  //��ɫ1      00000 000000 00000
#define GRAY2        0x4208  //��ɫ2  1111111111011111
#define GRAY  		 0X8430  //��ɫ

#define DGRAY        0x7BEF  //���ɫ  127, 127, 127      

#define PURPLE       0x780F  //��ɫ    127,   0, 127     



//GUI��ɫ
#define DARKBLUE     0X01CF	 //����ɫ
#define LIGHTBLUE    0X7D7C  //ǳ��ɫ
#define GRAYBLUE     0X5458  //����ɫ
//������ɫΪPANEL����ɫ

#define LIGHTGREEN   0X841F  //ǳ��ɫ
//#define LIGHTGRAY    0XEF5B  //ǳ��ɫ(PANNEL)
#define LGRAY 	     0XC618  //ǳ��ɫ //�Ұ�ɫ  192, 192, 192     
#define LGRAYBLUE    0XA651  //ǳ����ɫ
#define LBBLUE       0X2B12  //ǳ����ɫ





////////////////////////////////////////////////////////////////////////////
//==**��Ŀ"ר��"�궨��**Project-specific macro**===================//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//--**"ʵ����ʾ"�궨��**-------------------------------------------//

#define M_Vertical_FONT (16) //����"��ֱ���"   //������ʾ"�о�"
#define M_Horizontal_FONT (8) //����"ˮƽ���"   //������ʾ"�ַ����"


    //����ÿһ"��"��"�е�ַ"(�а����о�)
#define M_01Line   (0)                           //��ʾ��"01"�е��е�ַ
#define M_02Line   (M_01Line + M_Vertical_FONT)  //��ʾ��"02"�е��е�ַ
#define M_03Line   (M_02Line + M_Vertical_FONT)  //��ʾ��"03"�е��е�ַ
#define M_04Line   (M_03Line + M_Vertical_FONT)  //��ʾ��"04"�е��е�ַ
#define M_05Line   (M_04Line + M_Vertical_FONT)  //��ʾ��"05"�е��е�ַ
#define M_06Line   (M_05Line + M_Vertical_FONT)  //��ʾ��"06"�е��е�ַ
#define M_07Line   (M_06Line + M_Vertical_FONT)  //��ʾ��"07"�е��е�ַ
#define M_08Line   (M_07Line + M_Vertical_FONT)  //��ʾ��"08"�е��е�ַ
#define M_09Line   (M_08Line + M_Vertical_FONT)  //��ʾ��"09"�е��е�ַ
#define M_10Line   (M_09Line + M_Vertical_FONT)  //��ʾ��"10"�е��е�ַ
#define M_11Line   (M_10Line + M_Vertical_FONT)  //��ʾ��"11"�е��е�ַ
#define M_12Line   (M_11Line + M_Vertical_FONT)  //��ʾ��"12"�е��е�ַ
#define M_13Line   (M_12Line + M_Vertical_FONT)  //��ʾ��"13"�е��е�ַ
#define M_14Line   (M_13Line + M_Vertical_FONT)  //��ʾ��"14"�е��е�ַ
#define M_15Line   (M_14Line + M_Vertical_FONT)  //��ʾ��"15"�е��е�ַ
//#define M_16Line   (M_15Line + M_Vertical_FONT)  //��ʾ��"16"�е��е�ַ
//#define M_17Line   (M_16Line + M_Vertical_FONT)  //��ʾ��"17"�е��е�ַ
//#define M_18Line   (M_17Line + M_Vertical_FONT)  //��ʾ��"18"�е��е�ַ
//#define M_19Line   (M_18Line + M_Vertical_FONT)  //��ʾ��"19"�е��е�ַ
//#define M_20Line   (M_19Line + M_Vertical_FONT)  //��ʾ��"20"�е��е�ַ


//����ÿһ"�ַ�"��"��"��ַ(�а����ַ����)
#define M_01Column   (0) 				               //��ʾ��"01 �ַ�"��"�е�ַ"
#define M_02Column   (M_01Column + M_Horizontal_FONT)  //��ʾ��"02 �ַ�"��"�е�ַ"
#define M_03Column   (M_02Column + M_Horizontal_FONT)  //��ʾ��"03 �ַ�"��"�е�ַ"
#define M_04Column   (M_03Column + M_Horizontal_FONT)  //��ʾ��"04 �ַ�"��"�е�ַ"
#define M_05Column   (M_04Column + M_Horizontal_FONT)  //��ʾ��"05 �ַ�"��"�е�ַ"
#define M_06Column   (M_05Column + M_Horizontal_FONT)  //��ʾ��"06 �ַ�"��"�е�ַ"
#define M_07Column   (M_06Column + M_Horizontal_FONT)  //��ʾ��"07 �ַ�"��"�е�ַ"
#define M_08Column   (M_07Column + M_Horizontal_FONT)  //��ʾ��"08 �ַ�"��"�е�ַ"
#define M_09Column   (M_08Column + M_Horizontal_FONT)  //��ʾ��"09 �ַ�"��"�е�ַ"
#define M_10Column   (M_09Column + M_Horizontal_FONT)  //��ʾ��"10�ַ�"��"�е�ַ"
#define M_11Column   (M_10Column + M_Horizontal_FONT)  //��ʾ��"11�ַ�"��"�е�ַ"
#define M_12Column   (M_11Column + M_Horizontal_FONT)  //��ʾ��"12�ַ�"��"�е�ַ"
#define M_13Column   (M_12Column + M_Horizontal_FONT)  //��ʾ��"13�ַ�"��"�е�ַ"
#define M_14Column   (M_13Column + M_Horizontal_FONT)  //��ʾ��"14�ַ�"��"�е�ַ"
#define M_15Column   (M_14Column + M_Horizontal_FONT)  //��ʾ��"15�ַ�"��"�е�ַ"
#define M_16Column   (M_15Column + M_Horizontal_FONT)  //��ʾ��"16�ַ�"��"�е�ַ"
#define M_17Column   (M_16Column + M_Horizontal_FONT)  //��ʾ��"17�ַ�"��"�е�ַ"
#define M_18Column   (M_17Column + M_Horizontal_FONT)  //��ʾ��"18�ַ�"��"�е�ַ"
#define M_19Column   (M_18Column + M_Horizontal_FONT)  //��ʾ��"19�ַ�"��"�е�ַ"
#define M_20Column   (M_19Column + M_Horizontal_FONT)  //��ʾ��"20�ַ�"��"�е�ַ"
#define M_21Column   (M_20Column + M_Horizontal_FONT)  //��ʾ��"21�ַ�"��"�е�ַ"
#define M_22Column   (M_21Column + M_Horizontal_FONT)  //��ʾ��"22�ַ�"��"�е�ַ"
#define M_23Column   (M_22Column + M_Horizontal_FONT)  //��ʾ��"23�ַ�"��"�е�ַ"
#define M_24Column   (M_23Column + M_Horizontal_FONT)  //��ʾ��"24�ַ�"��"�е�ַ"
#define M_25Column   (M_24Column + M_Horizontal_FONT)  //��ʾ��"25�ַ�"��"�е�ַ"
#define M_26Column   (M_25Column + M_Horizontal_FONT)  //��ʾ��"26�ַ�"��"�е�ַ"
#define M_27Column   (M_26Column + M_Horizontal_FONT)  //��ʾ��"27�ַ�"��"�е�ַ"
#define M_28Column   (M_27Column + M_Horizontal_FONT)  //��ʾ��"28�ַ�"��"�е�ַ"
#define M_29Column   (M_28Column + M_Horizontal_FONT)  //��ʾ��"29�ַ�"��"�е�ַ"
#define M_30Column   (M_29Column + M_Horizontal_FONT)  //��ʾ��"30�ַ�"��"�е�ַ"
#define M_31Column   (M_30Column + M_Horizontal_FONT)  //��ʾ��"31�ַ�"��"�е�ַ"
#define M_32Column   (M_31Column + M_Horizontal_FONT)  //��ʾ��"32�ַ�"��"�е�ַ"
#define M_33Column   (M_32Column + M_Horizontal_FONT)  //��ʾ��"33�ַ�"��"�е�ַ"
#define M_34Column   (M_33Column + M_Horizontal_FONT)  //��ʾ��"34�ַ�"��"�е�ַ"
#define M_35Column   (M_34Column + M_Horizontal_FONT)  //��ʾ��"35�ַ�"��"�е�ַ"
#define M_36Column   (M_35Column + M_Horizontal_FONT)  //��ʾ��"36�ַ�"��"�е�ַ"
#define M_37Column   (M_36Column + M_Horizontal_FONT)  //��ʾ��"37�ַ�"��"�е�ַ"
#define M_38Column   (M_37Column + M_Horizontal_FONT)  //��ʾ��"38�ַ�"��"�е�ַ"
#define M_39Column   (M_38Column + M_Horizontal_FONT)  //��ʾ��"39�ַ�"��"�е�ַ"
#define M_40Column   (M_39Column + M_Horizontal_FONT)  //��ʾ��"40�ַ�"��"�е�ַ"



////////////////////////////////////////////////////////////////////////////
//--**"��ʾ���ݻ�������"�궨��**------------------------------//
    //����ÿһ"��"��"�е�ַ"(����"��ʾ���ݻ�������")
#define M_01LineBuf    (0)  
#define M_02LineBuf    (1)  
#define M_03LineBuf    (2)  
#define M_04LineBuf    (3)  
#define M_05LineBuf    (4)  
#define M_06LineBuf    (5)  
#define M_07LineBuf    (6)  
#define M_08LineBuf    (7)  
#define M_09LineBuf    (8) 
#define M_10LineBuf    (9) 
#define M_11LineBuf    (10) 
#define M_12LineBuf    (11) 
#define M_13LineBuf    (12) 
#define M_14LineBuf    (13) 
#define M_15LineBuf    (14) 
//#define M_16LineBuf    (15) 
//#define M_17LineBuf    (16) 
//#define M_18LineBuf    (17) 
//#define M_19LineBuf    (18) 
//#define M_20LineBuf    (19) 


    //����ÿһ"��"��"�е�ַ"(����"��ʾ���ݻ�������")
#define M_01ColumnBuf (0)  
#define M_02ColumnBuf (1)  
#define M_03ColumnBuf (2)  
#define M_04ColumnBuf (3)  
#define M_05ColumnBuf (4)  
#define M_06ColumnBuf (5)  
#define M_07ColumnBuf (6)  
#define M_08ColumnBuf (7)  
#define M_09ColumnBuf (8)  
#define M_10ColumnBuf (9)  
#define M_11ColumnBuf (10)  
#define M_12ColumnBuf (11)  
#define M_13ColumnBuf (12)  
#define M_14ColumnBuf (13)  
#define M_15ColumnBuf (14)  
#define M_16ColumnBuf (15)  
#define M_17ColumnBuf (16)  
#define M_18ColumnBuf (17)  
#define M_19ColumnBuf (18)  
#define M_20ColumnBuf (19)  
#define M_21ColumnBuf (20)  
#define M_22ColumnBuf (21)  
#define M_23ColumnBuf (22)  
#define M_24ColumnBuf (23)  
#define M_25ColumnBuf (24)  
#define M_26ColumnBuf (25)  
#define M_27ColumnBuf (26)  
#define M_28ColumnBuf (27)  
#define M_29ColumnBuf (28)  
#define M_30ColumnBuf (29)
#define M_31ColumnBuf (30)  
#define M_32ColumnBuf (31)  
#define M_33ColumnBuf (32)  
#define M_34ColumnBuf (33)  
#define M_35ColumnBuf (34)  
#define M_36ColumnBuf (35)  
#define M_37ColumnBuf (36)  
#define M_38ColumnBuf (37)  
#define M_39ColumnBuf (38)  
#define M_40ColumnBuf (39)



////////////////////////////////////////////////////////////////////////////
//==**"�˵���"  ��غ궨��**===============================//
////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	//--**"�˵���"��"�С��е�ַ"**------------------------------------//
#define M_Line_Gap  (8)

#define M_MenuLine_01  (M_02Line + M_Line_Gap) //��"01 �˵���"
#define M_MenuLine_02  (M_03Line + M_Line_Gap) //��"02 �˵���"
#define M_MenuLine_03  (M_04Line + M_Line_Gap) //��"03 �˵���"
#define M_MenuLine_04  (M_05Line + M_Line_Gap) //��"04 �˵���"
#define M_MenuLine_05  (M_06Line + M_Line_Gap) //��"05 �˵���"
#define M_MenuLine_06  (M_07Line + M_Line_Gap) //��"06 �˵���"
#define M_MenuLine_07  (M_08Line + M_Line_Gap) //��"07 �˵���"
#define M_MenuLine_08  (M_09Line + M_Line_Gap) //��"08 �˵���"
#define M_MenuLine_09  (M_10Line + M_Line_Gap) //��"09 �˵���"
#define M_MenuLine_10  (M_11Line + M_Line_Gap) //��"10 �˵���"
#define M_MenuLine_11  (M_12Line + M_Line_Gap) //��"11 �˵���"
#define M_MenuLine_12  (M_13Line + M_Line_Gap) //��"12 �˵���"

//////////////////////////////////////////////////////////////////////
#define M_MenuColumn_01  (M_01Column) //��"01 �˵���"//�˵����ĵ�һ��
#define M_MenuColumn_19  (M_19Column) //��"19 �˵���"//�˵����������


	////////////////////////////////////////////////////////////////////////////
	//--**"�˵���"��"�С���"-��ʾ��������**----------------------//
#define MenuLine01   (M_02LineBuf) //��"01 �˵���"-��ʾ��������
#define MenuLine02   (M_03LineBuf) //��"02 �˵���"-��ʾ��������
#define MenuLine03   (M_04LineBuf) //��"03 �˵���"-��ʾ��������
#define MenuLine04   (M_05LineBuf) //��"04 �˵���"-��ʾ��������
#define MenuLine05   (M_06LineBuf) //��"05 �˵���"-��ʾ��������
#define MenuLine06   (M_07LineBuf) //��"06 �˵���"-��ʾ��������
#define MenuLine07   (M_08LineBuf) //��"07 �˵���"-��ʾ��������
#define MenuLine08   (M_09LineBuf) //��"08 �˵���"-��ʾ��������
#define MenuLine09   (M_10LineBuf) //��"09 �˵���"-��ʾ��������
#define MenuLine10   (M_11LineBuf) //��"10 �˵���"-��ʾ��������
#define MenuLine11   (M_12LineBuf) //��"11 �˵���"-��ʾ��������
#define MenuLine12   (M_13LineBuf) //��"12 �˵���"-��ʾ��������

#define MenuColumn01 (M_01ColumnBuf) //��"01 �˵���"-��ʾ��������
#define MenuColumn02 (M_02ColumnBuf) //��"02 �˵���"-��ʾ��������
#define MenuColumn03 (M_03ColumnBuf) //��"03 �˵���"-��ʾ��������
#define MenuColumn04 (M_04ColumnBuf) //��"04 �˵���"-��ʾ��������
#define MenuColumn05 (M_05ColumnBuf) //��"05 �˵���"-��ʾ��������
#define MenuColumn06 (M_06ColumnBuf) //��"06 �˵���"-��ʾ��������
#define MenuColumn07 (M_07ColumnBuf) //��"07 �˵���"-��ʾ��������
#define MenuColumn08 (M_08ColumnBuf) //��"08 �˵���"-��ʾ��������
#define MenuColumn09 (M_09ColumnBuf) //��"09 �˵���"-��ʾ��������
#define MenuColumn10 (M_10ColumnBuf) //��"10 �˵���"-��ʾ��������
#define MenuColumn11 (M_11ColumnBuf) //��"11 �˵���"-��ʾ��������
#define MenuColumn12 (M_12ColumnBuf) //��"12 �˵���"-��ʾ��������
#define MenuColumn13 (M_13ColumnBuf) //��"13 �˵���"-��ʾ��������
#define MenuColumn14 (M_14ColumnBuf) //��"14 �˵���"-��ʾ��������
#define MenuColumn15 (M_15ColumnBuf) //��"15 �˵���"-��ʾ��������
#define MenuColumn16 (M_16ColumnBuf) //��"16 �˵���"-��ʾ��������
#define MenuColumn17 (M_17ColumnBuf) //��"17 �˵���"-��ʾ��������
#define MenuColumn18 (M_18ColumnBuf) //��"18 �˵���"-��ʾ��������
#define MenuColumn19 (M_19ColumnBuf) //��"19 �˵���"-��ʾ��������


////////////////////////////////////////////////////////////////////////////
//==**"������"  ��غ궨��**===============================//
////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	//--**"������"��"�С��е�ַ"**------------------------------------//
#define M_TestLine_01  (M_02Line + M_Line_Gap) //��"01 ������"
#define M_TestLine_02  (M_03Line + M_Line_Gap) //��"02 ������"
#define M_TestLine_03  (M_04Line + M_Line_Gap) //��"03 ������"
#define M_TestLine_04  (M_05Line + M_Line_Gap) //��"04 ������"
#define M_TestLine_05  (M_06Line + M_Line_Gap) //��"05 ������"
#define M_TestLine_06  (M_07Line + M_Line_Gap) //��"06 ������"
#define M_TestLine_07  (M_08Line + M_Line_Gap) //��"07 ������"
#define M_TestLine_08  (M_09Line + M_Line_Gap) //��"08 ������"
#define M_TestLine_09  (M_10Line + M_Line_Gap) //��"09 ������"
#define M_TestLine_10  (M_11Line + M_Line_Gap) //��"10 ������"
#define M_TestLine_11  (M_12Line + M_Line_Gap) //��"11 ������"
#define M_TestLine_12  (M_13Line + M_Line_Gap) //��"12 ������"

////////////////////////////////////////////////////////////////////////////
#define M_TestColumn_01  (M_21Column) //��"01 ������"//�������ĵ�һ��
#define M_TestColumn_02  (M_22Column) //��"02 ������"
#define M_TestColumn_03  (M_23Column) //��"03 ������"
#define M_TestColumn_04  (M_24Column) //��"04 ������"
#define M_TestColumn_05  (M_25Column) //��"05 ������"
#define M_TestColumn_06  (M_26Column) //��"06 ������"
#define M_TestColumn_07  (M_27Column) //��"07 ������"
#define M_TestColumn_08  (M_28Column) //��"08 ������"
#define M_TestColumn_09  (M_29Column) //��"09 ������"
#define M_TestColumn_10  (M_30Column) //��"10 ������"
#define M_TestColumn_11  (M_31Column) //��"11 ������"
#define M_TestColumn_12  (M_32Column) //��"12 ������"
#define M_TestColumn_13  (M_33Column) //��"13 ������"
#define M_TestColumn_14  (M_34Column) //��"14 ������"
#define M_TestColumn_15  (M_35Column) //��"15 ������"
#define M_TestColumn_16  (M_36Column) //��"16 ������"
#define M_TestColumn_17  (M_37Column) //��"17 ������"
#define M_TestColumn_18  (M_38Column) //��"18 ������"
#define M_TestColumn_19  (M_39Column) //��"19 ������"
#define M_TestColumn_20  (M_40Column) //��"20 ������"//�������������


	////////////////////////////////////////////////////////////////////////////
	//--**"������"��"�С���"-��ʾ��������**----------------------//
#define TestLine01   (M_02LineBuf) //��"01 ������"-��ʾ��������
#define TestLine02   (M_03LineBuf) //��"02 ������"-��ʾ��������
#define TestLine03   (M_04LineBuf) //��"03 ������"-��ʾ��������
#define TestLine04   (M_05LineBuf) //��"04 ������"-��ʾ��������
#define TestLine05   (M_06LineBuf) //��"05 ������"-��ʾ��������
#define TestLine06   (M_07LineBuf) //��"06 ������"-��ʾ��������
#define TestLine07   (M_08LineBuf) //��"07 ������"-��ʾ��������
#define TestLine08   (M_09LineBuf) //��"08 ������"-��ʾ��������
#define TestLine09   (M_10LineBuf) //��"09 ������"-��ʾ��������
#define TestLine10   (M_11LineBuf) //��"10 ������"-��ʾ��������
#define TestLine11   (M_12LineBuf) //��"11 ������"-��ʾ��������
#define TestLine12   (M_13LineBuf) //��"12 ������"-��ʾ��������

#define TestColumn01 (M_21ColumnBuf) //��"01 ������"-��ʾ��������
#define TestColumn02 (M_22ColumnBuf) //��"02 ������"-��ʾ��������
#define TestColumn03 (M_23ColumnBuf) //��"03 ������"-��ʾ��������
#define TestColumn04 (M_24ColumnBuf) //��"04 ������"-��ʾ��������
#define TestColumn05 (M_25ColumnBuf) //��"05 ������"-��ʾ��������
#define TestColumn06 (M_26ColumnBuf) //��"06 ������"-��ʾ��������
#define TestColumn07 (M_27ColumnBuf) //��"07 ������"-��ʾ��������
#define TestColumn08 (M_28ColumnBuf) //��"08 ������"-��ʾ��������
#define TestColumn09 (M_29ColumnBuf) //��"09 ������"-��ʾ��������
#define TestColumn10 (M_30ColumnBuf) //��"10 ������"-��ʾ��������
#define TestColumn11 (M_31ColumnBuf) //��"11 ������"-��ʾ��������
#define TestColumn12 (M_32ColumnBuf) //��"12 ������"-��ʾ��������
#define TestColumn13 (M_33ColumnBuf) //��"13 ������"-��ʾ��������
#define TestColumn14 (M_34ColumnBuf) //��"14 ������"-��ʾ��������
#define TestColumn15 (M_35ColumnBuf) //��"15 ������"-��ʾ��������
#define TestColumn16 (M_36ColumnBuf) //��"16 ������"-��ʾ��������
#define TestColumn17 (M_37ColumnBuf) //��"17 ������"-��ʾ��������
#define TestColumn18 (M_38ColumnBuf) //��"18 ������"-��ʾ��������
#define TestColumn19 (M_39ColumnBuf) //��"19 ������"-��ʾ��������
#define TestColumn20 (M_40ColumnBuf) //��"20 ������"-��ʾ��������




////////////////////////////////////////////////////////////////////////////
//--**������ʾģʽ:���������**--------------------------------//
//--care-- ����2���궨�壬ֻ��"1"����Ч
#define USE_HORIZONTAL_LCD_TFT   //ʹ�õ�"ˮƽ(����)��ʾģʽ"
//#define USE_VERTICAL_LCD_TFT     //ʹ�õ�"��ֱ(����)��ʾģʽ"


////////////////////////////////////////////////////////////////////////////
//--**���������С**------------------------------------------------//
#define FONT1206   (1) //����12*6
#define FONT1608   (2) //����16*8








//#define WIDTH       240                 /* ��ʾ���240*/
//#define HEIGHT      320
//#define USE_HORIZONTAL 


#define M_Space_ASCII      (0x20) //"�ո�"��ASCII��






////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//--**"����LCD_TFT_ILI9325"*ȫ�ֱ�־λ**-----------------------------//
extern union FLAGBIT16 LCD_TFT_FlagBits;  //"����LCD_TFT_ILI9325"��ر�־λ����
#define  G_LCD_TFT_FlagBits    LCD_TFT_FlagBits.FLAG16  
//#define	 F_Refresh_LCD_TFT     LCD_TFT_FlagBits.b.f0  //Ϊ1ʱ��ˢ��Һ����ʾ(ˢ��ʹ��λ)  
#define	 F_ReSet_LCD_TFT       LCD_TFT_FlagBits.b.f1  //Ϊ1ʱ����λ����"����LCD_TFT"Һ��ģ��   
#define	 F_Clear_LCD_TFT       LCD_TFT_FlagBits.b.f2  //Ϊ1ʱ����"����LCD_TFT"��������
#define  F_Close_LCD_TFT       LCD_TFT_FlagBits.b.f3  //Ϊ1ʱ���ر�Һ�������Һ������ˢ��  
//#define	 F_TimeRefresh_LCD_TFT LCD_TFT_FlagBits.b.f4  //Ϊ1ʱ��"����LCD_TFT"ˢ��ʱ��
//#define	 F_EnCursor_LCD_TFT    LCD_TFT_FlagBits.b.f5  //Ϊ1ʱ����˸��ʾ���("����LCD_TFT")
//#define	 F_         LCD_TFT_FlagBits.b.f6   //Ϊ1ʱ��
//#define	 F__Open_CursorFlash         LCD_TFT_FlagBits.b.f7  ////Ϊ1ʱ�� �������˸��ʾ,������0 
//#define	 F_Close_CursorFlash      LCD_TFT_FlagBits.b.f8  ////Ϊ1ʱ�� ��ֹ�����˸,������0 
//#define	 F       LCD_TFT_FlagBits.b.f9  //Ϊ1ʱ��
//#define	 F_      LCD_TFT_FlagBits.b.f10   //Ϊ1ʱ��
//#define	 F_Clear_TestArea           LCD_TFT_FlagBits.b.f11    //Ϊ1ʱ��ֻ�Բ�����������
#define	 F_250ms_Blink_Key_LCD_TFT	LCD_TFT_FlagBits.b.f12    //Ϊ1ʱ�� ��˸ָ��"����λ��" --"����LCD_TFT"(������˸�˵�)
#define	 F_250ms_Blink_Line_LCD_TFT	LCD_TFT_FlagBits.b.f13    //Ϊ1ʱ�� ��˸ָ���� --"����LCD_TFT"(������˸�˵�)
#define	 F_EnCopyDispBuf_LCD	    LCD_TFT_FlagBits.b.f14    //Ϊ1ʱ��ʹ�ܸ���"��ʾ��������" (������˸�˵�)
#define	 F_LCD_TFT_Timing	        LCD_TFT_FlagBits.b.f15    //�������β���"����LCD_TFT"�ļ����ʱʱ�� 



	//�˱�����Ϊ0:��ʾ�����ݸ�����ʾ	
extern union FLAGBIT16  Update_01Bits;	//"����LCD_TFT_ILI9325"ˢ����ʾ��ر�־λ����
#define  G_Update_01Bits       Update_01Bits.FLAG16  
#define	 F_Update_AdLine       Update_01Bits.b.f0  //ˢ��:"01�й��"  (Ϊ1ʱ)

#define	 F_Update_MenuLine01   Update_01Bits.b.f1  //ˢ��:""��01 �˵���""  (Ϊ1ʱ)
#define	 F_Update_MenuLine02   Update_01Bits.b.f2  //ˢ��:""��02 �˵���""  (Ϊ1ʱ)
#define	 F_Update_MenuLine03   Update_01Bits.b.f3  //ˢ��:""��03 �˵���""  (Ϊ1ʱ)
#define	 F_Update_MenuLine04   Update_01Bits.b.f4  //ˢ��:""��04 �˵���""  (Ϊ1ʱ)
#define	 F_Update_MenuLine05   Update_01Bits.b.f5  //ˢ��:""��05 �˵���""  (Ϊ1ʱ)
#define	 F_Update_MenuLine06   Update_01Bits.b.f6  //ˢ��:""��06 �˵���""  (Ϊ1ʱ)
#define  F_Update_MenuLine07   Update_01Bits.b.f7  //ˢ��:""��07 �˵���""  (Ϊ1ʱ)
#define	 F_Update_MenuLine08   Update_01Bits.b.f8  //ˢ��:""��08 �˵���""  (Ϊ1ʱ)
#define	 F_Update_MenuLine09   Update_01Bits.b.f9  //ˢ��:""��09 �˵���""  (Ϊ1ʱ)
#define	 F_Update_MenuLine10   Update_01Bits.b.f10 //ˢ��:""��10 �˵���""  (Ϊ1ʱ)
#define	 F_Update_MenuLine11   Update_01Bits.b.f11 //ˢ��:""��11 �˵���""  (Ϊ1ʱ)
#define	 F_Update_MenuLine12   Update_01Bits.b.f12 //ˢ��:""��12 �˵���""  (Ϊ1ʱ)
//#define	 F_     Update_01Bits.b.f13 //ˢ��:
//#define	 F_     Update_01Bits.b.f14 //ˢ��:
//#define	 F_     Update_01Bits.b.f15 //ˢ��:


	//�˱�����Ϊ0:��ʾ�����ݸ�����ʾ	
extern union FLAGBIT16  Update_02Bits;//"����LCD_TFT_ILI9325"ˢ����ʾ��ر�־λ����
#define  G_Update_02Bits      Update_02Bits.FLAG16  
//#define	 F_       Update_02Bits.b.f0  // (Ϊ1ʱ)
#define	 F_Update_TestLine01   Update_02Bits.b.f1  //ˢ��:""��01 ������""  (Ϊ1ʱ)
#define	 F_Update_TestLine02   Update_02Bits.b.f2  //ˢ��:""��02 ������""  (Ϊ1ʱ)
#define	 F_Update_TestLine03   Update_02Bits.b.f3  //ˢ��:""��03 ������""  (Ϊ1ʱ)
#define	 F_Update_TestLine04   Update_02Bits.b.f4  //ˢ��:""��04 ������""  (Ϊ1ʱ)
#define	 F_Update_TestLine05   Update_02Bits.b.f5  //ˢ��:""��05 ������""  (Ϊ1ʱ)
#define	 F_Update_TestLine06   Update_02Bits.b.f6  //ˢ��:""��06 ������""  (Ϊ1ʱ)
#define	 F_Update_TestLine07   Update_02Bits.b.f7  //ˢ��:""��07 ������""  (Ϊ1ʱ)
#define	 F_Update_TestLine08   Update_02Bits.b.f8  //ˢ��:""��08 ������""  (Ϊ1ʱ)
#define	 F_Update_TestLine09   Update_02Bits.b.f9  //ˢ��:""��09 ������""  (Ϊ1ʱ)
#define	 F_Update_TestLine10   Update_02Bits.b.f10 //ˢ��:""��10 ������""  (Ϊ1ʱ)
#define	 F_Update_TestLine11   Update_02Bits.b.f11 //ˢ��:""��11 ������""  (Ϊ1ʱ)
#define	 F_Update_TestLine12   Update_02Bits.b.f12 //ˢ��:""��12 ������""  (Ϊ1ʱ)
//#define	 F_     Update_02Bits.b.f13 // (Ϊ1ʱ)
//#define	 F_  Update_02Bits.b.f14 // (Ϊ1ʱ)
//#define	 F_ Update_02Bits.b.f15 //(Ϊ1ʱ)


	//�˱�����Ϊ0:��ʾ�����ݸ�����ʾ	
extern union FLAGBIT16  Update_03Bits;//"����LCD_TFT_ILI9325"ˢ����ʾ��ر�־λ����
#define  G_Update_03Bits       Update_03Bits.FLAG16  

#define	 F_Update_RealTime     Update_03Bits.b.f0  //ˢ��:"ʵʱʱ��"  (Ϊ1ʱ)
#define	 F_Update_Temperature  Update_03Bits.b.f1  //ˢ��:"ʵʱ�¶�"  (Ϊ1ʱ)
#define	 F_Update_CurrentValue Update_03Bits.b.f2  //ˢ��:"INA21x ʵʱ����ֵ" (Ϊ1ʱ)
#define	 F_Update_Power        Update_03Bits.b.f3  //ˢ��:""﮵�ص���""  (Ϊ1ʱ)
//#define	 F_   Update_03Bits.b.f4  // (Ϊ1ʱ)
//#define	 F_   Update_03Bits.b.f5  // (Ϊ1ʱ)
//#define	 F_   Update_03Bits.b.f6  // (Ϊ1ʱ)
//#define	 F_   Update_03Bits.b.f7  // (Ϊ1ʱ)
//#define	 F_   Update_03Bits.b.f8  // (Ϊ1ʱ)
//#define	 F_   Update_03Bits.b.f9  // (Ϊ1ʱ)
//#define	 F_   Update_03Bits.b.f10 // (Ϊ1ʱ)
//#define	 F_   Update_03Bits.b.f11 // (Ϊ1ʱ)
//#define	 F_   Update_03Bits.b.f12 // (Ϊ1ʱ)
//#define	 F_   Update_03Bits.b.f13 // (Ϊ1ʱ)
//#define	 F_   Update_03Bits.b.f14 // (Ϊ1ʱ)
//#define	 F_   Update_03Bits.b.f15 // (Ϊ1ʱ)




extern union FLAGBIT16  hightLight_01Bits;//"����LCD_TFT_ILI9325"ˢ����ʾ��ر�־λ����
#define  G_hightLight_01Bits  hightLight_01Bits.FLAG16  
//#define	 F_       hightLight_01Bits.b.f0  
#define	 F_HL_TestLine01  hightLight_01Bits.b.f1  //����ˢ��:""��01 ������""  (Ϊ1ʱ)
#define	 F_HL_TestLine02  hightLight_01Bits.b.f2  //����ˢ��:""��02 ������""  (Ϊ1ʱ)
#define	 F_HL_TestLine03  hightLight_01Bits.b.f3  //����ˢ��:""��03 ������""  (Ϊ1ʱ)
#define	 F_HL_TestLine04  hightLight_01Bits.b.f4  //����ˢ��:""��04 ������""  (Ϊ1ʱ)
#define	 F_HL_TestLine05  hightLight_01Bits.b.f5  //����ˢ��:""��05 ������""  (Ϊ1ʱ)
#define	 F_HL_TestLine06  hightLight_01Bits.b.f6  //����ˢ��:""��06 ������""  (Ϊ1ʱ)
#define	 F_HL_TestLine07  hightLight_01Bits.b.f7  //����ˢ��:""��07 ������""  (Ϊ1ʱ)
#define	 F_HL_TestLine08  hightLight_01Bits.b.f8  //����ˢ��:""��08 ������""  (Ϊ1ʱ)
#define	 F_HL_TestLine09  hightLight_01Bits.b.f9  //����ˢ��:""��09 ������""  (Ϊ1ʱ)
#define	 F_HL_TestLine10  hightLight_01Bits.b.f10 //����ˢ��:""��10 ������""  (Ϊ1ʱ)
#define	 F_HL_TestLine11  hightLight_01Bits.b.f11 //����ˢ��:""��11 ������""  (Ϊ1ʱ)
#define	 F_HL_TestLine12  hightLight_01Bits.b.f12 //����ˢ��:""��12 ������""  (Ϊ1ʱ)
//#define	 F_     hightLight_01Bits.b.f13 
//#define	 F_     hightLight_01Bits.b.f14 
//#define	 F_     hightLight_01Bits.b.f15 


extern union FLAGBIT16  hightLight_02Bits;	//"����LCD_TFT_ILI9325"ˢ����ʾ��ر�־λ����
#define  G_hightLight_02Bits   hightLight_02Bits.FLAG16  
//#define	 F_       hightLight_02Bits.b.f0  
#define	 F_HL_MenuLine01   hightLight_02Bits.b.f1  //����ˢ��:""��01 �˵���""  (Ϊ1ʱ)
#define	 F_HL_MenuLine02   hightLight_02Bits.b.f2  //����ˢ��:""��02 �˵���""  (Ϊ1ʱ)
#define	 F_HL_MenuLine03   hightLight_02Bits.b.f3  //����ˢ��:""��03 �˵���""  (Ϊ1ʱ)
#define	 F_HL_MenuLine04   hightLight_02Bits.b.f4  //����ˢ��:""��04 �˵���""  (Ϊ1ʱ)
#define	 F_HL_MenuLine05   hightLight_02Bits.b.f5  //����ˢ��:""��05 �˵���""  (Ϊ1ʱ)
#define	 F_HL_MenuLine06   hightLight_02Bits.b.f6  //����ˢ��:""��06 �˵���""  (Ϊ1ʱ)
#define  F_HL_MenuLine07   hightLight_02Bits.b.f7  //����ˢ��:""��07 �˵���""  (Ϊ1ʱ)
#define	 F_HL_MenuLine08   hightLight_02Bits.b.f8  //����ˢ��:""��08 �˵���""  (Ϊ1ʱ)
#define	 F_HL_MenuLine09   hightLight_02Bits.b.f9  //����ˢ��:""��09 �˵���""  (Ϊ1ʱ)
#define	 F_HL_MenuLine10   hightLight_02Bits.b.f10 //����ˢ��:""��10 �˵���""  (Ϊ1ʱ)
#define	 F_HL_MenuLine11   hightLight_02Bits.b.f11 //����ˢ��:""��11 �˵���""  (Ϊ1ʱ)
#define	 F_HL_MenuLine12   hightLight_02Bits.b.f12 //����ˢ��:""��12 �˵���""  (Ϊ1ʱ)
//#define	 F_     hightLight_02Bits.b.f13 
//#define	 F_     hightLight_02Bits.b.f14 
//#define	 F_     hightLight_02Bits.b.f15






extern u8 G_LcdBuf[15][41]; //"����LCD_TFT_ILI9325"��ʾ���ݻ�������(15��,ÿ��40�ַ�)//care--ÿ�е�41������Ԫ��Ϊ"\0"


////////////////////////////////////////////////////////////////////////////
//--**�����ɫ����**------------------------------------------------//
extern u16 AD_Point;      //����"�����"--"������ɫ": Ĭ��Ϊ"��ɫ"
extern u16 AD_Back;       //����"�����"--"������ɫ": Ĭ��Ϊ"��ɫ"

extern u16 Menu_Point;    //����"�˵���"--"������ɫ": Ĭ��Ϊ"��ɫ"
extern u16 Menu_Back;     //����"�˵���"--"������ɫ": Ĭ��Ϊ"ǳ��ɫ"
extern u16 HL_Menu_Point; //����"���ײ˵���"--"������ɫ": Ĭ��Ϊ"ǳ��ɫ"
extern u16 HL_Menu_Back;  //����"���ײ˵���"--"������ɫ": Ĭ��Ϊ"��ɫ"

extern u16 Test_Point;    //����"������"--"������ɫ": Ĭ��Ϊ"��ɫ"
extern u16 Test_Back;    //����"������"--"������ɫ": Ĭ��Ϊ"ǳ��ɫ"
extern u16 HL_Test_Point; //����"���ײ�����"--"������ɫ": Ĭ��Ϊ"ǳ��ɫ"
extern u16 HL_Test_Back;  //����"���ײ�����"--"������ɫ": Ĭ��Ϊ"��ɫ"

extern u16 Monitor_Point; //����"�����"--"������ɫ": Ĭ��Ϊ"��ɫ"
extern u16 Monitor_Back;       //����"�����"--"������ɫ": Ĭ��Ϊ"��ɫ"


extern u16 Fixed_Point;   //����"�ض��Ĺ̶�����ɫ"--"������ɫ": Ĭ��Ϊ"��ɫ"(����:��ַ���汾�š���������������)
extern u16 Fixed_Back;    //����"�����"--"������ɫ": Ĭ��Ϊ"��ɫ"(����:��ַ���汾�š���������������)




//////////////////////////////////////////////////////////////////
extern u16 POINT_COLOR;  //����"������ɫ": Ĭ��Ϊ"��ɫ"
extern u16 BACK_COLOR;   //����"������ɫ": Ĭ��Ϊ"��ɫ"

//////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"����"�궨��**Functions macro**============================//
////////////////////////////////////////////////////////////////////////////

#define mUpdate_All_MenuLine {F_Update_MenuLine01=YES;F_Update_MenuLine02=YES;F_Update_MenuLine03=YES;\
	                          F_Update_MenuLine04=YES;F_Update_MenuLine05=YES;F_Update_MenuLine06=YES;\
	                          F_Update_MenuLine07=YES;F_Update_MenuLine08=YES;F_Update_MenuLine09=YES;\
	                          F_Update_MenuLine10=YES;F_Update_MenuLine11=YES;F_Update_MenuLine12=YES;}   

#define mUpdate_All_TestLine {F_Update_TestLine01=YES;F_Update_TestLine02=YES;F_Update_TestLine03=YES;\
	                          F_Update_TestLine04=YES;F_Update_TestLine05=YES;F_Update_TestLine06=YES;\
	                          F_Update_TestLine07=YES;F_Update_TestLine08=YES;F_Update_TestLine09=YES;\
	                          F_Update_TestLine10=YES;F_Update_TestLine11=YES;F_Update_TestLine12=YES;}   
	


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"��������**Exported Module-specific funcitions**======//
////////////////////////////////////////////////////////////////////////////

void ILI9325_WriteByte(u8 data);  //SPI��ILI9325 ������дһ���ֽ�����
void ILI9325_WriteRegIndex(u16 index); //��ILI9325��д"��������Ĵ�����ַ"
void ILI9325_WriteData(u16 data);  //��ILI9325��д"16 λ����"


void LCD_TFT_WriteReg(u8 index, u16 data);  //����ILI9325�Ĵ�����ֵ(�Ĵ���ַ+�Ĵ���ֵ)
void LCD_TFT_WriteRAM_CMD(void); //��ILI9325д"GRAM�����ַ"
void LCD_TFT_WriteRAM(u16 RGB_data);  //��ILI9325д"GRAM����"



void LCD_TFT_SetWindow(u16 xSta, u16 ySta, u16 xEnd, u16 yEnd);  //������ʾ���ڵ������С(�����յ�)-"����LCD_TFT_ILI9325"  
void LCD_TFT_SetCursor(u16 x, u16 y);  //����GRAM�Ĺ��λ��-"����LCD_TFT_ILI9325"  



////////////////////////////////////////////////////////////////////////////
//==**"�ⲿ" API ��������**Exported  API funcitions**==================//
////////////////////////////////////////////////////////////////////////////
extern void Init_LCD_TFT_ILI9325(void); //"����LCD_TFT_ILI9325" ��ʹ��: ���������Դ�ĳ�ʼ��
extern void Init_GPIO_LCD_TFT_ILI9325(void);  //��ʼ��: "����LCD_TFT_ILI9325"  IO�˿�
extern void Reset_LCD_TFT_ILI9325(void); //��λ"����LCD_TFT_ILI9325"ģ��
extern void Init_Register_LCD_TFT_ILI9325(void);  //��ʼ��: "����LCD_TFT_ILI9325"  ����оƬ�ļĴ���



extern void LCD_TFT_ClearDisBuf(void);   //��ʾ������������(����:�Ϳո�20H)-"����LCD_TFT_ILI9325"  

extern void LCD_TFT_Clear(u16 color);   //ȫ������-"����LCD_TFT_ILI9325"  

extern void LCD_TFT_DrawPoint(u16 x, u16 y, u16 color); //����( ָ������,��ɫ)-"����LCD_TFT_ILI9325"  

extern void LCD_TFT_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);  //����-"����LCD_TFT_ILI9325"  

extern void LCD_TFT_DrawRectangle(u16 xSta, u16 ySta, u16 xEnd, u16 yEnd,u16 color);  //�����ο�-"����LCD_TFT_ILI9325"  

extern void LCD_TFT_DrawCircle(u16 x0,u16 y0,u8 r,u16 color);  //��Բ-"����LCD_TFT_ILI9325"  


extern void LCD_TFT_FillRectangle(u16 xSta,u16 ySta,u16 xEnd,u16 yEnd,u16 color);  //���һ��LCD��������(ָ����С����ɫ)-"����LCD_TFT_ILI9325" 


	//��ʾһ���ַ�( ָ������,�����С,��ɫ)-"����LCD_TFT_ILI9325"  
extern void LCD_TFT_ShowChar(u16 x,u16 y,u8 AscNum,u8 Font,u16 pointColor,u16 backColor); 
	//��ʾ�ַ���( ָ������,�����С,��ɫ)-"����LCD_TFT_ILI9325"  
extern void LCD_TFT_ShowString(u16 line,u16 column,u8 *ArrayPoint,u8 Font,u16 pointColor,u16 backColor); 

	//��ʾ1��24*24�ĺ���-"����LCD_TFT_ILI9325"  
extern void LCD_TFT_Show_ChFont2424(u16 x,u16 y,u8 index,u16 pointColor,u16 backColor); 




extern void LCD_TFT_Show_StandbyPage(void); //��ʾ"����ҳ��"-"����LCD_TFT_ILI9325"  
extern void LCD_TFT_Show_WorkPage(void); //��ʾ"����ҳ��"-"����LCD_TFT_ILI9325"  



extern void Deal_LCD_TFT(void); //��ʾ����-"����LCD_TFT_ILI9325"  //ֻ�������ݱ仯����ʾ����

extern void Update_LCD_TFT(void);  //����"���ݱ仯"����ʾ����-"����LCD_TFT_ILI9325"  

extern void Update_MonitorLine_LCD_TFT(void);  //����"�����""���ݱ仯"����ʾ����-"����LCD_TFT_ILI9325"  

extern void Update_MenuLine_LCD_TFT(void);  //����"�˵���""���ݱ仯"����ʾ����-"����LCD_TFT_ILI9325"  

extern void Update_TestLine_LCD_TFT(void); //����"������""���ݱ仯"����ʾ����-"����LCD_TFT_ILI9325"  


	//��˸��ʾ"����λ��(����ֵ)"--"����LCD_TFT" 
extern void Blink_KeyPlace_Lcd_TFT(unsigned char line,unsigned char column,unsigned char *Array,unsigned char Num);


#endif  //-- __TFT_ILI9325_H --//

