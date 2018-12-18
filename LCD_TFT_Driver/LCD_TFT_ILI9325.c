/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 LCD_TFT_ILI9325.c
* �����ļ�-Dependencies:  	 LCD_TFT_ILI9325.H; SPI.h; System.h; Hardware_Profile.h; Generic.h;
* �ļ�����-File Description:	 ( Դ����-Source File)
	�� "����LCD_TFT_ILI9325" -��������(�ⲿ��Դ)
	01)  ��������оƬ:ILI9325C
	02) ��LCD_TFT����:240xRGBx320,������ʾ20�У�ÿ����ʾ30���ַ�(15������)   
	03) 	��ʾ����: Transmissive��ȫ͸ʽ����2.4TFT��COG��  ��ʾɫ��: 262K��
	04)  �ӽ� ��12��       ���� ��240 (RGB) (W) ��320H) Pixels��
	05)  MPU ϵͳ�ӿ�( MPU System Interface )
              ILI9325 ��һ��16λ�ı�ַ�Ĵ�����IR����һ��18λ��д���ݼĴ�����WDR����һ��18λ�Ķ����ݼĴ�����RDR����
              ��ַ�Ĵ�����IR���洢���Կ��ƼĴ������ڲ���GRAM��ָ����Ϣ��д���ݼĴ�����WDR��������ʱ�洢Ҫ
              ��д�����ƼĴ������ڲ���GRAM�е����ݡ������ݼĴ�����RDR��������ʱ�洢��GRAM�ж�ȡ�����ݡ�
              MPU��Ҫд���ڲ�GRAM�����ݣ�����д��д���ݼĴ�����WDR����Ȼ�������ڲ������Զ���д���ڲ���GRAM �С�
              Ҫ��ȡ������Ҫͨ�������ݼĴ�����RDR�����ڲ�GRAM �ж�ȡ�������Ч���ݽ��������������ߣ�
              ��ILI9325���ڲ���GRAM�ж�ȡ��һ�����ݵ�ʱ����Ч���ݽ���ILI9325�����˵ڶ��ζ�����֮�󱻶�����
	06)	ILI9325����оƬ������
	��1��ΪQVGA TFT LCD��ʾ�ĵ�оƬ���������
	��2��֧��240RGB��320���أ�������ʾ262144��ɫ�ʡ�
	��3��֧��MVA��Multi_domain Vertical Aligement�෶Χ��ֱ���У����ӽ���ʾ��
	��4�����720ͨ��Դ��������320ͨ���ż�������
	��5���ڲ�����172800�ֽڵ�GRAM(ͼ���ڴ�)
	��6�������ڴ�����д����
		֧������ϵͳ���ٽӿڣ�
		��1��i80ϵͳӵ��8λ��9λ��16λ��18λ����λ��ĸ��ٽӿڣ���
		��2��������Χ�ӿ�(SPI)��
		��3����6λ��16λ��18λλ���RGB�ӿڣ�VSYNC,HSYNC,DOTCLK,ENABLE,DB[17:0]��
		��4��VSYNC�ӿ�(System interface + VSYNC)
		�ӿ�ģʽͨ������IM[3:0]Pins�����ơ�
	��7���ڲ������Ӳ����λ��
	��8���������ܣ�x1/2,x1/4����
	��9��դԴ���ƶ�������档
	��10��Window��ַ���������ڲ�GRAM��ָ��һ����������
	��11���ḻ��ɫ����ʾ������
	��12���ֲ������������û�ָ����LCD���ϲ���������ʾ��
	��13�������������������Һ��������ѹˮ׼��6��(x6)��
	��14�����ܹ���
	     * 8ɫģʽ
	     * ����ģʽ
	     * ˯��ģʽ
	��15���͹������Ľṹ
		IOVcc = 1.65V-3.3V(interface I/O)
		Vcc = 2.4-3.3V
		Vci = 2.5-3.3V
	��16��LCD������ѹ��
		Դ��/VCOM ��ѹ
			DVDH-GND = 4.5V-6.0V
			VCL-GND = -2.0V~-3.0V
			VCI-VCL <= 6.0V
		�ż�������ѹ��
			VGH-GND = 10~20V
			VGL-GND = -5V~-15V
			VGH-VGL <=32V
		VCOM������ѹ��
			VCOMH = 3.0V-(DDVDH-0.5)V
			VCOML = (VCL+0.5)V~0V
			VCOMH - VCOML <= 6.0V
	��17��һ��TFT-LCD �洢���ݣ�Cst ONLY	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ע������-Attention : 	
	��01) ������С��ʱ����Ҫע��������ʼˮƽ�ʹ�ֱ�������ʼ��ַ�ͽ�����ַ��
	���ʱ������ˮƽ�ʹ�ֱ�������ʼ��ַ�ͽ�����ַ��Ϊ�˿�����ʾ����
	��ʼ��ַ�ͽ�����ַ�����������ϵĵ�ַ�������������Сһ���ͼƬ��
	��С����Ϊ120 * 160 ��ʾ����100��100��������ϣ���ʼ��ַ��Ҫ����Ϊ100��
	ˮƽ������ַ����Ϊ219����ֱ������ַΪ259�������Ͳ����ͼƬд��ͷ��
	Ҳ������ˮƽ�ʹ�ֱ��ʼ�ͽ�����ַ������ʾ����������дͼƬ�����ݵ�
	ʱ��9325�Ͳ���д�������ĵط���Ҳ�����޶��˸������������ϵ�����Χ��
	��Ҫ�ǵ�����R20H,R21H,������ֵ��ȷ������д�����ݸ��¿�ʼ�����꣬Ҳ����
	ͨ��R20H��R21Hȷ����������Ǹ��ط���ʼ�������ݣ��������ݵķ�Χ������ˮƽ
	�ʹ�ֱ�������ʼ��ַ�ͽ�����ַȷ���ġ�ע��R20H��R21Hȷ���������һ��
	Ҫ����ʵ�������ڣ�����ͼƬ�ǲ�����ʾ�ġ���������԰�R20H��R21H����Ϊ100,
	�����������Ϊ99�������(99,99)�������Ǹո�ȷ���������ڣ�����ͼƬ�Ͳ�����ʾ��
	��02) 
	��03) 
	��04) 
	��05)  	    
	��06) ��Ҫ�������ĵط�
	  A) 	  	  B)  	  C)    	  D)     
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
* �޸ļ�¼-Change History:   
	����   ʱ��        �汾  ��������
	Author 	 Date		   Rev      Comment
	-------------------------------------------------------------------------------
	BlueS	2013-08-01	  1.0	   
			xxxx-xx-xx	  x.x	   
			xxxx-xx-xx	  x.x				
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
* ��˾-Company: 			CS-EMLAB  Co. , Ltd.
* ������Э��-Software License Agreement:
	Copyright (C) 2012-2020 	CS-EMLAB  Co. , Ltd.	All rights reserved.	

*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/



#include "Generic.h"	//���ó����̹淶�������� -ͷ�ļ�-Generic Type Definitions

#include "Hardware_Profile.h"  //������"Ӳ�������ļ�" -Hardware specific definitions for Processor

#include "System.h"	 //"ϵͳ" ���ù��ܺ�����-ͷ�ļ�


#include "SPI.h"     //"SPI ͬ����������ӿ�" -�������� -ͷ�ļ�(�������ڲ���Դ)

#include "LCD_TFT_FONT.h"  // Һ�������ֿ�(���ġ�Ӣ��)-ͷ�ļ�(�ⲿ��Դ) 

#include "LCD_TFT_ILI9325.h"  // "����LCD_TFT_ILI9325" -��������(�ⲿ��Դ) -ͷ�ļ�



#include "BQ27410_FuelGauge.h"   //"BQ27410_FuelGauge ﮵�ص�������"-��������(�ⲿ��Դ)-ͷ�ļ�



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//--**"����LCD_TFT_ILI9325"*ȫ�ֱ�־λ**-----------------------------//
union FLAGBIT16  LCD_TFT_FlagBits;	//"����LCD_TFT_ILI9325"��ر�־λ����

	//�˱�����Ϊ0:��ʾ�����ݸ�����ʾ	
union FLAGBIT16 Update_01Bits;	//"����LCD_TFT_ILI9325"ˢ����ʾ��ر�־λ����
union FLAGBIT16 Update_02Bits;	//"����LCD_TFT_ILI9325"ˢ����ʾ��ر�־λ����
union FLAGBIT16 Update_03Bits;	//"����LCD_TFT_ILI9325"ˢ����ʾ��ر�־λ����


union FLAGBIT16 hightLight_01Bits;	//"����LCD_TFT_ILI9325"ˢ����ʾ��ر�־λ����
union FLAGBIT16 hightLight_02Bits;	//"����LCD_TFT_ILI9325"ˢ����ʾ��ر�־λ����



u8 G_LcdBuf[15][41]; //"����LCD_TFT_ILI9325"��ʾ���ݻ�������(15��,ÿ��40�ַ�)//care--ÿ�е�41������Ԫ��Ϊ"\0"


////////////////////////////////////////////////////////////////////////////
//--**�����ɫ����**------------------------------------------------//
u16 AD_Point = BLACK;      //����"�����"--"������ɫ": Ĭ��Ϊ"��ɫ"
u16 AD_Back = WHITE;       //����"�����"--"������ɫ": Ĭ��Ϊ"��ɫ"

u16 Menu_Point = BLACK;    //����"�˵���"--"������ɫ": Ĭ��Ϊ"��ɫ"
u16 Menu_Back = LBLUE;     //����"�˵���"--"������ɫ": Ĭ��Ϊ"ǳ��ɫ"
u16 HL_Menu_Point = LBLUE; //����"���ײ˵���"--"������ɫ": Ĭ��Ϊ"ǳ��ɫ"
u16 HL_Menu_Back = BLACK;  //����"���ײ˵���"--"������ɫ": Ĭ��Ϊ"��ɫ"

u16 Test_Point = BLACK;    //����"������"--"������ɫ": Ĭ��Ϊ"��ɫ"
u16 Test_Back = LGREEN;    //����"������"--"������ɫ": Ĭ��Ϊ"ǳ��ɫ"
u16 HL_Test_Point = LGREEN; //����"���ײ�����"--"������ɫ": Ĭ��Ϊ"ǳ��ɫ"
u16 HL_Test_Back = BLACK;  //����"���ײ�����"--"������ɫ": Ĭ��Ϊ"��ɫ"

u16 Monitor_Point = BLACK; //����"�����"--"������ɫ": Ĭ��Ϊ"��ɫ"
u16 Monitor_Back = WHITE;  //����"�����"--"������ɫ": Ĭ��Ϊ"��ɫ"

u16 Fixed_Point = RED;   //����"�ض��Ĺ̶�����ɫ"--"������ɫ": Ĭ��Ϊ"��ɫ"(����:��ַ���汾�š���������������)
u16 Fixed_Back = WHITE;    //����"�����"--"������ɫ": Ĭ��Ϊ"��ɫ"(����:��ַ���汾�š���������������)






///////////////////////////////////////////////////////////////////////////////////
u16 POINT_COLOR = BLACK;  //����"������ɫ": Ĭ��Ϊ"��ɫ"
u16 BACK_COLOR = WHITE;   //����"������ɫ": Ĭ��Ϊ"��ɫ"




////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////

const unsigned char Msg_ClearLine_LCD_TFT[] =  {"                           \0"}; // (��28�ֽ�) 




/****************************************************************************
*������-Function:	void ILI9325_WriteByte(u8 data)
*����- Description:		SPI��ILI9325 ������дһ���ֽ�����
*�������-Input:	data: 8λ���ֽ�����
*�������-output:	None
*ע������-Note��	
	��01) ���ģ��SPI
	��02)    ��03)    ��04)  
***********************************************
void ILI9325_WriteByte(u8 data)  //SPI��ILI9325 ������дһ���ֽ�����
{
	u8 i = 0;

	//SPI д����ʱ��ʼ
	mLow_LCD_TFT_CS; //��������Ϊ"���",��"����͵�ƽ"

	for(i = 8; i > 0; i--)
	{
		//SPI �������
		if(data & 0x80) 
		{
			mHigh_LCD_TFT_SDA; //���λΪ"1"//��������Ϊ"���",��"����ߵ�ƽ"
		}
		else
		{
			mLow_LCD_TFT_SDA; //���λΪ"0"////��������Ϊ"���",��"����͵�ƽ"
		}

		mLow_LCD_TFT_CLK;	 //��������Ϊ"���",��"����͵�ƽ"
		mHigh_LCD_TFT_CLK; //��������Ϊ"���",��"����ߵ�ƽ"

		data <<= 1; 
	}
	
	mHigh_LCD_TFT_CS; //��������Ϊ"���",��"����ߵ�ƽ"
}
******************************/


/****************************************************************************
*������-Function:	void ILI9325_WriteRegIndex(u16 index)
*����- Description:		��ILI9325��д"��������Ĵ�����ַ"
*�������-Input:	index: 16λ�Ŀ�������Ĵ�����ַ
*�������-output:	None
*ע������-Note��	
	��01) ѡ������RS(A0): //0:  ѡ������Ĵ��� //1: ѡ�����ݼĴ���
	��02)    ��03)    ��04)  
*****************************************************************************/
void ILI9325_WriteRegIndex(u16 index) //��ILI9325��д"��������Ĵ�����ַ"
{
	mLow_LCD_TFT_RS;  //��������Ϊ"���",��"����͵�ƽ" //0:  ѡ������Ĵ���

//	ILI9325_WriteByte(index >> 8);  //���ֽ�//���ģ��SPI, дһ���ֽ�����
//	ILI9325_WriteByte(index);       //���ֽ�//���ģ��SPI, дһ���ֽ�����

	Send_OneByte_SPI_B(index >> 8);  //���ֽ�
	Send_OneByte_SPI_B(index);  	 //���ֽ�
}


/****************************************************************************
*������-Function:	void ILI9325_WriteData(u16 data)
*����- Description:		��ILI9325��д"16 λ����"
*�������-Input:	data: 16λ������
*�������-output:	None
*ע������-Note��	
	��01) ѡ������RS(A0): //0:  ѡ������Ĵ��� //1: ѡ�����ݼĴ���
	��02)    ��03)    ��04)  
*****************************************************************************/
void ILI9325_WriteData(u16 data)  //��ILI9325��д"16 λ����"
{

	mHigh_LCD_TFT_RS; //��������Ϊ"���",��"����ߵ�ƽ"  //1: ѡ�����ݼĴ���

//	ILI9325_WriteByte(data >> 8);	//���ֽ�//���ģ��SPI, дһ���ֽ�����
//	ILI9325_WriteByte(data);		//���ֽ�//���ģ��SPI, дһ���ֽ�����


	Send_OneByte_SPI_B(data >> 8);	//���ֽ�	//	start byte RS=1,RW=0----Write a GRAM data
	Send_OneByte_SPI_B(data);        //���ֽ�

}


/****************************************************************************
*������-Function:	void LCD_TFT_WriteReg(u8 index, u16 data)
*����- Description:		����ILI9325�Ĵ�����ֵ(�Ĵ���ַ+�Ĵ���ֵ)
*�������-Input:	index: 16λ�Ĵ���ַ ;  data: 16λ�Ĵ���ֵ
*�������-output:	None
*ע������-Note��	
	��01) 	��02)    ��03)    ��04)  
*****************************************************************************/
void LCD_TFT_WriteReg(u8 index, u16 data)  //����ILI9325�Ĵ�����ֵ(�Ĵ���ַ+�Ĵ���ֵ)
{
	ILI9325_WriteRegIndex(index);
	ILI9325_WriteData(data);
}


/****************************************************************************
*������-Function:	void LCD_TFT_WriteRAM_CMD(void)
*����- Description:		��ILI9325д"GRAM�����ַ"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) дGRAM����ʱ,����ILI9325д"GRAM�����ַ"
	��02)    ��03)    ��04)  
*****************************************************************************/
void LCD_TFT_WriteRAM_CMD(void) //��ILI9325д"GRAM�����ַ"
{
	ILI9325_WriteRegIndex(0x22);   //дRAM
}


/****************************************************************************
*������-Function:	void LCD_TFT_WriteRAM_CMD(void)
*����- Description:		��ILI9325д"GRAM����"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) дGRAM����ʱ,����ILI9325д"GRAM�����ַ"
	��02)    ��03)    ��04)  
*****************************************************************************/
void LCD_TFT_WriteRAM(u16 RGB_data)  //��ILI9325д"GRAM����"
{
    ILI9325_WriteData(RGB_data); //дGRAM����
}


/****************************************************************************
*������-Function:	void Init_LCD_TFT_ILI9325(void)
*����- Description:		"����LCD_TFT_ILI9325" ��ʹ��: ���������Դ�ĳ�ʼ��
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Init_LCD_TFT_ILI9325(void) //"����LCD_TFT_ILI9325" ��ʹ��: ���������Դ�ĳ�ʼ��
{
////////////////////////////////////////////////////////////////////////////
//==**�������**===========================================//
		//����: ����ߵ�ƽ(ռ�ձ�Ϊ100%)(��ʱ��������)
	mOpen_LCD_TFT_BackLight; //��������Ϊ"���",��"��""����LCD_TFT"����

				
////////////////////////////////////////////////////////////////////////////
//==**��ʼ��: "����LCD_TFT_ILI9325"  IO�˿�**====================//
	Init_GPIO_LCD_TFT_ILI9325();  //��ʼ��: "����LCD_TFT_ILI9325"  IO�˿�

	
////////////////////////////////////////////////////////////////////////////
//==**��λ"����LCD_TFT_ILI9325"ģ��**==========================//
	Reset_LCD_TFT_ILI9325(); //��λ"����LCD_TFT_ILI9325"ģ��


////////////////////////////////////////////////////////////////////////////
//==**��ʼ��: "����LCD_TFT_ILI9325"  ����оƬ�ļĴ���**=======//
	Init_Register_LCD_TFT_ILI9325();  //��ʼ��: "����LCD_TFT_ILI9325"  ����оƬ�ļĴ���

////////////////////////////////////////////////////////////////////////////
//==**��ʼ��:  ����Զ������**===========================//
	LCD_TFT_ClearDisBuf();   //��ʾ������������(����:�Ϳո�20H)-"����LCD_TFT_ILI9325"  
	G_LCD_TFT_FlagBits = 0;  //"����LCD_TFT_ILI9325"��ر�־λ����
	G_Update_01Bits = 0;     //���������ʾʹ��λ
	G_Update_02Bits = 0;     //���������ʾʹ��λ
	G_Update_03Bits = 0;     //���������ʾʹ��λ

	G_hightLight_01Bits = 0;
	G_hightLight_02Bits = 0;


	AD_Point = BLACK;      //����"�����"--"������ɫ": Ĭ��Ϊ"��ɫ"
	AD_Back = WHITE;       //����"�����"--"������ɫ": Ĭ��Ϊ"��ɫ"

	Menu_Point = BLACK;    //����"�˵���"--"������ɫ": Ĭ��Ϊ"��ɫ"
	Menu_Back = LBLUE;     //����"�˵���"--"������ɫ": Ĭ��Ϊ"ǳ��ɫ"
	HL_Menu_Point = Menu_Back; //����"���ײ˵���"--"������ɫ": Ĭ��Ϊ"ǳ��ɫ"
	HL_Menu_Back = Menu_Point;  //����"���ײ˵���"--"������ɫ": Ĭ��Ϊ"��ɫ"
	
	
	Test_Point = BLUE;    //����"������"--"������ɫ": Ĭ��Ϊ"��ɫ"
	Test_Back = LGREEN;    //����"������"--"������ɫ": Ĭ��Ϊ"ǳ��ɫ"
	HL_Test_Point = Test_Back; //����"���ײ�����"--"������ɫ": Ĭ��Ϊ"ǳ��ɫ"
	HL_Test_Back = Test_Point;  //����"���ײ�����"--"������ɫ": Ĭ��Ϊ"��ɫ"
	
	Monitor_Point = BLACK; //����"�����"--"������ɫ": Ĭ��Ϊ"��ɫ"
	Monitor_Back = WHITE;  //����"�����"--"������ɫ": Ĭ��Ϊ"��ɫ"

	Fixed_Point = MAGENTA;   //����"�ض��Ĺ̶�����ɫ"--"������ɫ": Ĭ��Ϊ"��ɫ"(����:��ַ���汾�š���������������)
	Fixed_Back = WHITE;    //����"�����"--"������ɫ": Ĭ��Ϊ"��ɫ"(����:��ַ���汾�š���������������)

}

   
/****************************************************************************
*������-Function:	void Init_GPIO_LCD_TFT_ILI9325(void)
*����- Description:		��ʼ��: "����LCD_TFT_ILI9325"  IO�˿�
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Init_GPIO_LCD_TFT_ILI9325(void)  //��ʼ��: "����LCD_TFT_ILI9325"  IO�˿�
{
	
	mSPI_All_Disable;  //�ر�����SPIģ���ʹ��

	

//mSPI_Select_LCD_TFT; //SPI��������LCD_TFTʱ��Ҫ���������õ�SPI��ģ��  

////////////////////////////////////////////////////////////////////////////
//==**IO�ڵ�������ó�ʼ��**==============================//


//--**P2.7 ����: ����LCD_TFT��λ** ----------------------------------//
	mSetOut_LCD_TFT_Reset; //��������Ϊ"���"
	mClose_LCD_TFT_Reset;  //���"��"��ƽ=="�ر�"��λ����


//--**P8.6 ����: LCD_TFT ������Ĵ��������ݼĴ���ѡ������RS(A0)** -------------//
	//0:  ѡ������Ĵ��� //1: ѡ�����ݼĴ���
	mSelect_LCD_TFT_RS_IoPin;  //��������Ϊͨ������"IO"����
	mSetOut_LCD_TFT_RS; 	   //��������Ϊ"���"
	mLow_LCD_TFT_RS;		   //��������Ϊ"���",��"����͵�ƽ" //0:	ѡ������Ĵ���
	
	
//���ģ��SPI
//--**P8.4 ����: LCD_TFT ��ʱ������CLK** -------------------//
	//mSelect_LCD_TFT_CLK_IoPin; //��������Ϊͨ������"IO"����
	//mSetOut_LCD_TFT_CLK;		 //��������Ϊ"���"
	//mLow_LCD_TFT_CLK; 		 //"����͵�ƽ"


//���ģ��SPI
//--**P8.5 ����: LCD_TFT ����������SDA(MOSI)** -------------------//
	//mSelect_LCD_TFT_SDA_IoPin;  //��������Ϊͨ������"IO"����
	//mSetOut_LCD_TFT_SDA;		  //��������Ϊ"���"
	//mLow_LCD_TFT_SDA; 		  //"����͵�ƽ"

////////////////////////////////////////////////////////////////////////////
//==**SPI �˿ڳ�ʼ��**===================================//
	Initial_SPI_B();  //SPI_B ģ���ʼ��:�˿ڳ�ʼ��������SPI����
	

////////////////////////////////////////////////////////////////////////////
//==**����"Bģ��"��·������TS3A5017: ѡ��IN2 ��IN1**=========//
		// IN2=0; IN1=1; ��ӦSPI_B ����(CLK_B; SPI_MOSI_B; SPI_MISO_B)
	mConfig_TS3A5017_B_IN2(0);  //IN2 = 0
	mConfig_TS3A5017_B_IN1(1);  //IN1 = 1

//--**P2.6 ����: LCD_TFTʹ������CS ("��"��Ч)** -------------------//
mSetOut_LCD_TFT_CS; //��������Ϊ"���"
mLow_LCD_TFT_CS; //"����͵�ƽ"


}


/****************************************************************************
*������-Function:	void Reset_LCD_TFT_ILI9325(void)
*����- Description:		��λ"����LCD_TFT_ILI9325"ģ��
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01)��ϵͳƵ���й�(��ʱ����),��ֲʱ��Ҫע��   
	��02) 
	��03)    ��04)  
*****************************************************************************/
void Reset_LCD_TFT_ILI9325(void) //��λ"����LCD_TFT_ILI9325"ģ��
{
	mClose_LCD_TFT_Reset; //��������Ϊ"���",��"�ر�"��λ����
	_delay_ms(1);
	
	mOpen_LCD_TFT_Reset; //��������Ϊ"���",��"ʹ��"��λ����(��λ"��"��ƽ��Ч)
	_delay_ms(10);
	
	mClose_LCD_TFT_Reset; //��������Ϊ"���",��"�ر�"��λ����
	_delay_ms(50);
}



/****************************************************************************
*������-Function:	void Init_Register_LCD_TFT_ILI9325(void)
*����- Description:		��ʼ��: "����LCD_TFT_ILI9325"  ����оƬ�ļĴ���
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Init_Register_LCD_TFT_ILI9325(void)  //��ʼ��: "����LCD_TFT_ILI9325"  ����оƬ�ļĴ���
{

//////////////////////////////////////////////////////////////
//==Start Initial Sequence===============================//
//--Set internal timing----------------------------------//
	LCD_TFT_WriteReg(0x00E3, 0x3008); // Set internal timing
	LCD_TFT_WriteReg(0x00E7, 0x0012); // Set internal timing
	LCD_TFT_WriteReg(0x00EF, 0x1231); // Set internal timing

//--��ַ�Ĵ�����IR��:ָ���Ĵ����ĵ�ַR00h ~ RFFh����Ҫ���ʵ�RAM�ĵ�ַ��----------------------------------//
//--״̬��ȡ(RS)��ӳ��ILI9325�ڲ���״̬��//L[7:0] ָʾĿǰ��������TFT����������λ��----------------------------------//
//--���� ��R00h��//�����üĴ���ʱ���������롱9325��H������----------------------------------//

//--�����������(R01h)--SM=0--SS=1 -------------------------------//
	//SM=0������ɨ��//SM=1������ɨ��--����ʱ���ɷŴ���ʾͼ�񣬵����ؽ���
	//SS:��Դ������ѡ�������ת�䷽��--ѡ�����������ʾ�������������ʾ
		//��SS=0 ���ת�䷽���Ǵ�S1��S720  //��SS=1 ���ת�䷽���Ǵ�S720 ��S1
#if defined USE_HORIZONTAL_LCD_TFT    //ʹ�õ�"ˮƽ(����)��ʾģʽ"
	LCD_TFT_WriteReg(0x0001, 0x0100); // ��SS=1//��Ҫ��"R01h"	��"R03h"	��"R60h"	
		
#elif defined USE_VERTICAL_LCD_TFT       //ʹ�õ�"��ֱ(����)��ʾģʽ"
	LCD_TFT_WriteReg(0x0001, 0x0100); // ��SS=0//��Ҫ��"R01h"	��"R03h"	��"R60h"	
#endif

//--LCD�������ο���(R02h)--B/C= 1--EOR=1------------------------------//
	//B/C= 0��֡/����λ// B/C= 1���з�ת
	//EOR: EOR=1��B/C=1 �����з�ת
	LCD_TFT_WriteReg(0x0002, 0x0700); // set 1 line inversion

//--����ģʽ(R03h)--TRI = 1--DFI= 0--BGR = 0--ORG = 0--I/D[1:0]=11--AM = 0--------//
	//TRI: ��TRI = 1��ʱ����8λ����ģʽ������ 8bit * 3����ģ�Ҳ���Ǵ��������ֽڵ��ڲ���RAM��
	    //ͬ��Ҳ֧��16λ���ݵ�ģʽ����ʹ��SPIģʽ��ʾ26��ɫ��Ҳ����˵��TRI = 1 ��ʱ��
		//������ֽ��������϶�����������һλ����ʾ26��ɫ��ʱ�����õģ�����ʹ��8λ���ݽӿڵ�ʱ��
		//���Ҫ�������Ӧ�������ã�����ע���������Ҫ��ʱ��Ҫ����Ϊ0.
	//DFI : �������ڲ�RAM�������ݵĵ�ģʽ����һλ��Ҫ��TRI��������ʹ�õġ�
	//BGR ����д�����к����
		//BGR = 0 : ����RGB˳��д���ص�����ݡ�//BGR = 1:  ����RGB����ΪBGR,д��GRAM
	//ORG : ��һ�����ڵĵ�ַ����ȷ���Ժ󣬸�������I/D�����ã����ƶ�ԭʼ��ַ��������д���ڵ�ַ��ʱ��������ܽ���ʹ�ܡ�
	//ע�⣺1����ORG =1 ��ʱ������R20H,R21H,��ԭʼ��ַ��ʱ��ֻ������0x0000  // 2����RAM������ʱ��Ҫ��֤ORG = 0;
		//ORG = 0: ԭʼ��ַ�ǲ��ƶ��ġ���������£���ͨ��ָ����ַ������д�����ģ������ַ�Ǹ��ݴ�����ʾ�����GRAM�ĵ�ַ��
		//ORG = 1:ԭʼ��ַ�Ǹ���I/D��������Ӧ���ƶ��ġ�
	//��һ�������������ɼĴ���R50h ~R53h ������ʱ��GRAM �����ַ���½�������I/D[1:0]��AM λ��������ȷ����
	//I/D[1:0] ����ȷ���ò�����ȷ����ʾͼƬ��������ʱ������ʾ������ͼƬ������img2lcd��ͼƬ���������ҷ����Ƿ��ģ�
		//�������� ���߶��Ƿ��ģ��Ǿ�����Ҫ�޸�����ĵط��ˣ����Ը�������ķ�����ѡ����ʵ�I/D.
	//I/D[1:0]=11=������һ����������ʱ��I/D[1:0]λ���Ƶ�ַ��������AC���Զ����ӻ��߼���1
	//����ط���AM��ѡ��ֱ��Ӱ��img2lcd�����ɨ�跽ʽ�������һλ���ǿ���ɨ�跽ʽ�ġ�
	//AM: ����GRAM�ĸ��·���
		//AM = 0: ��ˮƽ������µ�ַ//AM = 1: �ڴ�ֱ������µ�ַ
			//@ˮƽ����:������ ��ֱ����:����
#if defined USE_HORIZONTAL_LCD_TFT    //ʹ�õ�"ˮƽ(����)��ʾģʽ"
	LCD_TFT_WriteReg(0x0003, 0x1038); // ��AM=1//��Ҫ��"R01h"	��"R03h"	��"R60h"	
		
#elif defined USE_VERTICAL_LCD_TFT       //ʹ�õ�"��ֱ(����)��ʾģʽ"
	LCD_TFT_WriteReg(0x0003, 0x1030); // ��AM=0//��Ҫ��"R01h"	��"R03h"	��"R60h"	
#endif

  
//--�������ƼĴ���(R04h)--RCV[1:0]=00--RCH[1:0]=00--RSZ[1:0]=00---------//
//�����������ã�������//�Ե���Ϊ1/2Ϊ����Ҫע��һ�£�����ͼ����9325�Լ������ģ���������Ȼ��Ҫ��ԭʼͼ�������ȫ��д�뵽9325��ֻ������9325��һ��ȫ�������ݶ�д���ڲ���GRAM,���Ǹ��ݵ���������ѡ��İ�ԭʼͼ�������д��GRAM��
	//RCV[1:0]:ͬ�����RCHԭ����һ���ģ����������֤��ֱ�����ϼ�ȥ�������ص������ܱ�RSZ������
		//00=0���أ�1����=1RGB�� //01=1����  //10=2����  //11=3����
	//RCH[1:0]: ������ͼ���С��ʱ������ˮƽ���µ����ص�ĸ�����ʵ���Ͼ����õ�ǰ��ͼ���ˮƽ���ظ�������С��ˮƽ���ظ���ȡģ��
		//ԭ�����������ͼ�񲻿��������ܱ���С1/2������1/4���������ͼ��ˮƽ���ص���15���������Ҫ��СΪ1/2��
		//����15����2���������ģ�����Ϊ1��RCH[1:0]���ʱ�������Ϊ1��ʵ���Ͼ��Ǳ�֤���ԭʼͼ��ˮƽ��ȥ�������ص������ܱ�RSZ������
		//00=0���أ�1����=1RGB�� //01=1����  //10=2����  //11=3����
	//��������RSZ��ILI9325�������RSZ���õĲ���������ͼƬ�Ĵ�С�����ʱ��ˮƽ�ʹ�ֱ��������򶼻�ı䡣
	//RSZ[1:0] : ���õ���������RSZ����˼����resizeing��
		//00=������(X1)   //01=X1 /2   //10=�趨��ֹ   //11=X1  /4
	LCD_TFT_WriteReg(0x0004, 0x0000); // Resize register


//////////////////////////////////////////////////////////////
//==��ʾ����===================================//

//--��ʾ����2(R08h)--FP[3:0]=010--BP[3:0]=010--���ú���غ�ǰ��------------//
	//FP[3:0]�� BP[3:0] λ �ֱ�ָ��ǰ��������ڵ��к��� ��porch ���أ���� ��periods ���ڣ�
	//���趨FP[3:0]�� BP[3:0] ֵʱҪ��֤���������
		//BP + FP �� 16 lines       FP �� 2 lines       BP �� 2 lines
		//FP[3:0]=010== 2 Lines
		//BP[3:0]=010== 2 Lines
	LCD_TFT_WriteReg(0x0008, 0x0202); // set the back porch and front porch

//--��ʾ����3 (R09h)--PTS[2:0]=000--PTG[1:0]=00--ISC[3:0]=0000--���÷���ʾ��ʱ����------//
	//PTS[2:0]���ò���ʾ�����������ڵ�Դ�������
	//ע�⣺1.�ڲ���ʾ�������ڽ�����ѹʱ��Ƶ�ʺ���ֹ�Ҷ��˷ſ�����ߵ�ԴЧ��
	          //2.�ڲ�����ʾ���������ż��������������PTG[1:0]λ������
		//��PTS[2]=1 �����Ҷȵ��˷ţ�����V0��V63���Ĳ�������ֹ������ʾ ��������ѹʱ��Ƶ�ʽ�����ԭ��ʱ�ӵ�һ�룬�Լ��ٹ������ġ�
		//PTS[2:0]=000=Positive Polarity=V63, Negative Polarity=V0
	//PTG[1:0] ���� ����ʾ�����ɨ��ģʽ��
		//00=Normal scan;    01=Setting Prohibited   10=Interval scan;  11=Setting Prohibited
	//ISC[3:0]: ���趨PTG[1:0]=10 ѡ��ɨ����ʱ��ָ���������ڷ���ʾ�����ɨ�������ڣ�ɨ�������趨Ϊ��0~29֡�����е�����ֵ��ÿ��ɨ�����ڼ��Զ��ᷴת��
		//ISC[3:0]=0000==ɨ��������Ϊ0֡
	LCD_TFT_WriteReg(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]

//--��ʾ����4(R0Ah)--FMARKOE=0--FMI[2:0]=000--֡��ǹ���-----//
	//��FMARKOE=1����FMI[2:0]����������λ������ILI9325��ʼ����FMARK�ź�
	//FMI[2:0] ������ʾ������д���ں����ݴ������ʣ�����FMARK�źŵ�������
		//FMI[2:0]=000=������Ϊ1֡ //001=������Ϊ2֡
	    //011=������Ϊ4֡//101=������Ϊ5֡//����=Setting Disabled
	LCD_TFT_WriteReg(0x000A, 0x0000); // FMARK function

//--RGB��ʾ�ӿڿ���1(R0Ch)--ENC[2:0] =000--RM=0--DM[1:0] =00--RIM[1:0] =00------//
	//ENC[2:0] ͨ��RGB�ӿ�����GRAM ��д����
		//000=1֡  001=2֡  010=3֡  011=4֡
		//100=5֡  101=6֡  110=7֡  111=8֡
	//RM ѡ�����GRAM �Ľӿڵ�ͨ��RGB�ӿ�д��ʾ���ݵ�ʱ������RM=1
	//ע��1���Ĵ���ֻ��ͨ��ϵͳ�ӿڻ�����SPI�ӿ����趨
		   //2��ģʽת������RGN����ӿ�����ͼ����
		//0=System interface/VSYNC interface    1=RGB interface
	//DM[1:0] ѡ����ʾ����ģʽ
	//DM[1:0] �������������ڲ�ʱ�Ӳ���ģʽ���ⲿ��ʾ�ӿڲ���ģʽ֮���л���
	//��ֹ��RGB�ӿڲ���ģʽ��VSYNC�ӿڲ���ģʽ֮���л���
		//DM[1:0] =00=Internal system clock   01=RGB interface  10=VSYNC interface  11=Setting disabled
	//RIM[1:0] ѡ��RGB���ݽӿڿ��
	//ע��1���Ĵ���ֻ����ϵͳ�ӿ�����
	       //2����ת���ӿڵ�ʱ��֤һ���������ݣ� 3 ���㣩������ϡ�
		//00=18-bit RGB interface(1 tansfer/pixel)   01=16-bit RGB interface(1 tansfer/pixel)
		//10= 6-bit RGB interface(3 tansfer/pixel)    11=Setting Disabled
	LCD_TFT_WriteReg(0x000C, 0x0000); // RGB interface setting

//--֡���λ(R0Dh)--EMP[8:0]=00000000--֡���λ��--------------------------//
	//EMP[8:0] ����֡ѭ�������λ�ã�֡������
	//��FMP[8:0]=0 ��һ������������ FMARK �ڵ�һ��ʾ���ڵ� ��ʼ ��������� ���
    //��֤��9��h000 �Q FMP �Q BP+NL+FP
	LCD_TFT_WriteReg(0x000D, 0x0000); // Frame marker Position

//--RGB��ʾ�ӿڿ���2 (R0Fh)--VSPL = 0--HSPL = 0--EPL=0--DPL=0-------------//
	//VSPL: ����VSYNC�ŵ��źż���
		//VSPL = 0 �͵�ƽ��Ч    //VSPL = 1 �ߵ�ƽ��Ч
	//HSPL:����HSYNC�ŵ��źż���
		//HSPL = 0 �͵�ƽ��Ч    //HSPL = 1 �ߵ�ƽ��Ч
	//EPL: ����ʹ�ܽŵ��źż���
		//EPL=0 ��ENBLE=0 ����DB17-0 ��д�� ����ENBLE=1 ���ܽ���д���ݲ���
		//EPL=1 ��ENBLE=1 ����DB17-0 ��д�� ����ENBLE=0 ���ܽ���д���ݲ���
	//DPL: ����DOTCLK�ŵ��ź��������
		//DPL=0 ������ DOTCLK �����������  DPL=1 ������ DOTCLK ���½������
	LCD_TFT_WriteReg(0x000F, 0x0000); // RGB interface polarity


//////////////////////////////////////////////////////////////
//==��Դ����Power On sequence =======================//

//--��Դ����1(R10h)--SAP=0--BT[3:0] =000--APE=0--AP[2:0]=000--DSTB=0--SLP=0--STB=0--------------//
	//SAP��Դ�����������
		//SAP=0��Դ������ֹ   //SAP=1��Դ����ʹ��
	//BT[3:0] ����ʹ����ѹ��·�Ĳ���//Ϊ������ѹѡ�������ѹ������Ϊ�˼��ٹ�������������С�ĵ�ѹ����
	//����APE=1 ���ݵ�Դ����˳��ʼ����
	//AP[2:0]: ��LCD��Դ������·���������˷ŵ�·���ȶ�����������ȶ���������
	//���LCD ��������������Ҳ�����˵������ġ��ڲ���ʾ���ڣ�����AP[2:0]=000
	//ֹͣ�����˷ŵ�·�����ߵ�·��ѹ���ٵ������ġ�
		//AP[2:0]=000=Gamma Driver amplifiersΪHalt; Source Driver amplifiers ΪHalt��//001=Gamma Driver amplifiersΪ1; Source Driver amplifiers Ϊ1��
			    //010=Gamma Driver amplifiersΪ1; Source Driver amplifiers Ϊ0.75��   //011=Gamma Driver amplifiersΪ1; Source Driver amplifiers Ϊ0.5��
			    //100=Gamma Driver amplifiersΪ0.75; Source Driver amplifiers Ϊ1��   //101=Gamma Driver amplifiersΪ0.75; Source Driver amplifiers Ϊ0.75��
			    //110=Gamma Driver amplifiersΪ0.75; Source Driver amplifiers Ϊ0.5��//111=Gamma Driver amplifiersΪ0.5; Source Driver amplifiers Ϊ0.5��
	//DSTB:��DSTB=1 ,ILI9325������ȴ���ģʽ�� ����ȴ���ģʽ���ڲ��߼���Դ�����ر��Լ��ٵ�Դ���ģ�
		//GRAM��ָ�����ݲ��ᱻ��������ȴ���ģʽ�£��˳���ȴ���ģʽ��������Ҫ����λ��
	//SLP: ��SLP=1��ILI9325 ����˯��ģʽ������RC��������ʾ������ֹͣ���Լ��ٵ�Դ���ġ� 
		//��˯��ģʽ��GRAM���ݺ�ָ��ᱻ���£�����ͨ����������ָ�a���˳�˯��ģʽ��SLP=0�� b����ʼ��
	//STB: ��STB=1 ,ILI9325�������ģʽ������GRAM ��Դ�����⣬��ʾ����ֹͣ�Լ��ٵ�Դ���ġ�
		//�ڴ���ģʽ��GRAM���ݺ�ָ��ᱻ���£�����ͨ����������ָ�a���˳�����ģʽ��STB�� b����ʼ��
	LCD_TFT_WriteReg(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
	
//--��Դ����2 (R11h)--DC1[2:0] =000--DC0[2:0] =000--VC[2:0]=111-------------//	
	//ע�⣺��֤ fDCDC1��fDCDC2 ���趨 DC0[2:0] ��DC1[2:0] ��ʱ��
	//DC1[2:0] ѡ����ѹ��·2�Ĺ���Ƶ�ʡ����ߵ���ѹ��·����Ƶ�ʿ��������ѹ��·��������������ʾ���������ǻ����ӵ������ģ���������Ƶ����Ҫ�ۺϿ�����ʾ�����͵�·���ġ�
		//000=Step-upƵ��Ϊ Fosc/8    //010=Step-upƵ��Ϊ Fosc/16    //011=Step-upƵ��Ϊ Fosc/32
		//100=Step-upƵ��Ϊ Fosc/64  //101=Step-upƵ��Ϊ Fosc/128  //110=Step-upƵ��Ϊ Fosc/256
		//111=Halt Step-up Circuit2
	//DC0[2:0] ѡ����ѹ��·1�Ĺ���Ƶ�ʡ����ߵ���ѹ��·����Ƶ�ʿ��������ѹ��·��������������ʾ���������ǻ����ӵ������ģ���������Ƶ����Ҫ�ۺϿ�����ʾ�����͵�·���ġ�
		//000=Step-upƵ��Ϊ Fosc/2     //010=Step-upƵ��Ϊ Fosc/4    //011=Step-upƵ��Ϊ Fosc/8
		//100=Step-upƵ��Ϊ Fosc/16  //101=Step-upƵ��Ϊ Fosc/32   //110=Step-upƵ��Ϊ Fosc/64
		//111=Halt Step-up Circuit1
	//VC[2:0] :���ò����ο���ѹVci1 �ı�������
		//000=0.95*Vci   001=0.90*Vci    010=0.85*Vci    011=0.80*Vci  
		//100=0.75*Vci   101=0.70*Vci    110=Disabled     111=1.0 *Vci
	LCD_TFT_WriteReg(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
	
//--��Դ����3 (R12h)--VCIRE=0--PON=0--VHR[3:0] =0000--------------//	
	//VCIRE: ѡ���ⲿ�ο���ѹVci �����ڲ��ο���ѹVCIR
		//VCIRE=0 �ⲿ�ο���ѹVci (Ĭ��)  //VCIRE =1  �ڲ��ο���ѹ 2.5V
	//PON :���Ƶ�·3��VGL������Ŀ��͹�
		//PON=0 VGL output is disabled     //PON=1 VGL output is enabled
	//VHR[3:0] ����Ӧ����VREG1OUT��������ķŴ����ʣ�1.6~1.9����VREG1OUT����VCOM���ͻҶȵ�ѹ�������Ĳο���
	//��Vci<2.5V���ڲ��ο���ѹ������Vci��ͬ. ȷ�� VC ��VRH���趨������VREG1OUT �Q (DDVDH - 0.2)V.
		//��VCIRE=0ʱ��0000=VREG1OUT=Halt�� 0001=VREG1OUT=Vci*2.00;    0010=VREG1OUT=Vci*2.05; ...
		//��VCIRE=1ʱ��0000=VREG1OUT=Halt�� 0001=VREG1OUT=2.5V*2.00;  0010=VREG1OUT=2.5V*2.05; ...
	LCD_TFT_WriteReg(0x0012, 0x0000); // VREG1OUT voltage
	
//--��Դ����4(R13h)--VDV[4:0]=00000--------------------------------//
	//VDV[4:0] ѡ��VREG1OUT���� ������Vcom�Ľ�����ѹ��� ��ΧΪ0.70 ~1.24  x VREG1OUT
		//����VDV[4:0]��Vcom����С��6V
		//00000= Vcom amplitude= VREG1OUT *0.70;  00001= Vcom amplitude= VREG1OUT *0.72; ...
	LCD_TFT_WriteReg(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
	_delay_ms(200); // Dis-charge capacitor power voltage
	
//--��Դ����1(R10h)----------------------------------//
	//SAP=1��Դ����ʹ��
	//BT[3:0]=6=����DDVDH=Vci1*2;  VCL=-Vci1; VGH=Vci1*4; VGL=-Vci1*3
	//APE=1 ���ݵ�Դ����˳��ʼ����
	//AP[2:0]001=Gamma Driver amplifiersΪ1; Source Driver amplifiers Ϊ1��
	//DSTB=0,ILI9325 û�н�����ȴ���ģʽ
	//SLP =0,ILI9325 û�н���˯��ģʽ
	//STB =0,ILI9325 û�н������ģʽ
	LCD_TFT_WriteReg(0x0010, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB

//--��Դ����2 (R11h)----------------------------------//
	//DC1[2:0] =010==ѡ����ѹ��·2�Ĺ���Ƶ��=Step-upƵ��Ϊ Fosc/16  
	//DC0[2:0] =010==ѡ����ѹ��·1�Ĺ���Ƶ��=Step-upƵ��Ϊ Fosc/4  
	//VC[2:0] =111=���ò����ο���ѹVci1 �ı�������=1.0 *Vci
	LCD_TFT_WriteReg(0x0011, 0x0227); // R11h=0x0221 at VCI=3.3V, DC1[2:0], DC0[2:0], VC[2:0]
	_delay_ms(50); // Delay 50ms
	
//--��Դ����3 (R12h)----------------------------------//	
	//VCIRE=0 �ⲿ�ο���ѹVci (Ĭ��)  
	//PON=1 VGL output is enabled  //PON :���Ƶ�·3��VGL������Ŀ��͹�
	//VHR[3:0] ����Ӧ����VREG1OUT��������ķŴ����ʣ�1.6~1.9����VREG1OUT����VCOM���ͻҶȵ�ѹ�������Ĳο���
	//VCIRE=0���ʵ�VHR[3:0]=1100=����VREG1OUT=Vci*1.80; 
	LCD_TFT_WriteReg(0x0012, 0x001C); // External reference voltage= Vci;
	_delay_ms(50); // Delay 50ms
	
//--��Դ����4(R13h)------------------------------------//
	//VDV[4:0] ѡ��VREG1OUT���� ������Vcom�Ľ�����ѹ��� ��ΧΪ0.70 ~1.24  x VREG1OUT
	//VDV[4:0] =11000= ����Vcom amplitude= VREG1OUT *1.10;    //care//����VDV[4:0]��Vcom����С��6V
	LCD_TFT_WriteReg(0x0013, 0x1800); // R13=1200 when R12=009D;VDV[4:0] for VCOM amplitude
	
//--��Դ���� 7(R29h)----------------------------------//
	//VCM[5:0] �����ڲ� VcomH ��ѹ=VREG1OUT * 0.825
	LCD_TFT_WriteReg(0x0029, 0x001C); // R29=000C when R12=009D;VCM[5:0] for VCOMH

//--֡���ʺ���ɫ����(R2Bh)----------------------------------//
	//FRS[3:0]=1101=���ڲ�����Ӧ�����𵴵�·��ʱ������֡����=128
	LCD_TFT_WriteReg(0x002B, 0x000D); // Frame Rate = 91Hz
	_delay_ms(50); // Delay 50ms

//--GRAM ˮƽλ�üĴ�����ַ 0x20----------------------------------//
	//AD[16:0] ���ñ�ַ��������AC���ĳ�ʼ����ֵ��
	//��ַ��������AC�������AM ��I/Dλ���������Զ��ĸ�������ֵ��������д���ڲ���GARM ��ʱ��
	//�����ڲ�GRAM�ж�����ʱ��ַ�����������Զ���������ֵ��
		//AD[16:0]=00000000=ѡ��GRAM Data Map=��1�� GRAM Data  
	LCD_TFT_WriteReg(0x0020, 0x0000); // GRAM horizontal Address

//--GRAM ��ֱλ�üĴ�����ַ 0x21----------------------------------//
	//AD[16:0] ���ñ�ַ��������AC���ĳ�ʼ����ֵ��
	//��ַ��������AC�������AM ��I/Dλ���������Զ��ĸ�������ֵ��������д���ڲ���GARM ��ʱ��
	//�����ڲ�GRAM�ж�����ʱ��ַ�����������Զ���������ֵ��
		//AD[16:0]=00000000=ѡ��GRAM Data Map=��1�� GRAM Data  
	LCD_TFT_WriteReg(0x0021, 0x0000); // GRAM Vertical Address

//--д���ݵ�GRAM(R22h)------------------------------------------------------//
//--��GRAM �ж����ݣ�Read Data from GRAM (R22h)��--------------------------//


////////////////////////////////////////////////////////////////
//==٤��У��(R30h��R3Dh)==Adjust the Gamma Curve ========//
	LCD_TFT_WriteReg(0x0030, 0x0007);
	LCD_TFT_WriteReg(0x0031, 0x0302);
	LCD_TFT_WriteReg(0x0032, 0x0105);
	LCD_TFT_WriteReg(0x0035, 0x0206);
	LCD_TFT_WriteReg(0x0036, 0x0808);
	LCD_TFT_WriteReg(0x0037, 0x0206);
	LCD_TFT_WriteReg(0x0038, 0x0504);
	LCD_TFT_WriteReg(0x0039, 0x0007);
	LCD_TFT_WriteReg(0x003C, 0x0105);
	LCD_TFT_WriteReg(0x003D, 0x0808);

//////////////////////////////////////////////////////////////////////////////////////////
//==��������=Set GRAM area  =���ڱ�ַ������ GRAM ��ַ�ռ�֮��=========//

//--ˮƽ���򴰿�-------------------------------//
	//���趨��Щλʱ���뱣֤ ��"00h" �� HSA[7:0]< HEA[7:0] ��"EFh"=239. ��"04h"�Q HEA-HSA.
	//ͨ������HSA��HEAλ�ܹ��޶�д����ʱ���GRAM��ˮƽ����
	//HSA��HEAλ�����ڿ�ʼдRAM����֮ǰ���趨�á�
	LCD_TFT_WriteReg(0x0050, 0x0000); //ˮƽ���򴰿ڱ�ַ����ʼλ�� Horizontal GRAM Start Address
	LCD_TFT_WriteReg(0x0051, 0x00EF); //ˮƽ���򴰿ڱ�ַ����ֹλ�� Horizontal GRAM End Address

//--��ֱ���򴰿�-------------------------------//
	//���趨��Щλʱ���뱣֤ ��"000h"��VSA[8:0]<VEA[8:0]��"13Fh"=319
	//VSA �� VEA λ�ܹ��޶�д����ʱ��� GRAM �Ĵ�ֱ����
	//VSA �� VEA λ�����ڿ�ʼд RAM ����֮ǰ���趨�á�
	LCD_TFT_WriteReg(0x0052, 0x0000); //��ֱ���򴰿ڱ�ַ����ʼλ�� Vertical GRAM Start Address
	LCD_TFT_WriteReg(0x0053, 0x013F); //��ֱ���򴰿ڱ�ַ����ֹλ�� Vertical GRAM End Address

///////////////////////////////////////////////////////////////
//==��ɨ������=Gate Scan Control (R60h, R61h, R6Ah)========//

//--R60h--GS = 1--NL[5:0]=27H--SCN[5:0] =000000---------------//
	//GS: Sets the direction of scan by the gate driver in the range determined by SCN[4:0] and NL[4:0].//
		//GS = 0, the scan direction is from G1 to G320.  //GS = 1, the scan direction is from G320 to G1
	//NL[5:0]: Sets the number of lines to drive the LCD at an interval of 8 lines.
		//The GRAM address mapping is not affected by the number of lines set by NL[5:0]. 
		//The number of lines must be the same or more than the number of lines necessary for the size of the liquid crystal panel.
		//NL[5:0]=27H=LCD Drive Line=320 line
	//SCN[5:0] The ILI9325C allows to specify the gate line from which the gate driver starts to scan by setting the SCN[5:0] bits.
		//SCN[5:0] =000000 =Scanning Start Position=G320(��GS=1)  //��SMλ��GSλ�йء�

#if defined USE_HORIZONTAL_LCD_TFT    //ʹ�õ�"ˮƽ(����)��ʾģʽ"
	LCD_TFT_WriteReg(0x0060, 0x2700); //��GS=0//��Ҫ��"R01h"	��"R03h"	��"R60h"	

#elif defined USE_VERTICAL_LCD_TFT       //ʹ�õ�"��ֱ(����)��ʾģʽ"
	LCD_TFT_WriteReg(0x0060, 0xA700); //��GS=1//��Ҫ��"R01h"	��"R03h"	��"R60h"	
#endif


//--R61h--NDL=0--VLE=0--REV=1-------------------------------//
	//NDL: Sets the source driver output level in the non-display area.
		//NDL=0=Positive PolarityΪV63��Negative PolarityΪV0��
		//NDL=1=Positive PolarityΪV0�� Negative PolarityΪV63��
	//VLE: Vertical scroll display enable bit. When VLE = 1, the ILI9325C starts displaying the base image from the line 
		//(of the physical display) determined by VL[8:0] bits. VL[8:0] sets the amount of scrolling, which is the number of lines 
		//to shift the start line of the display from the first line of the physical display. Note that the partial image display position is not affected by the base image scrolling.
		//The vertical scrolling is not available in external display interface operation. In this case, make sure to set VLE = "0".
	//REV: Enables the grayscale inversion of the image by setting REV=1.
	LCD_TFT_WriteReg(0x0061, 0x0001); // NDL,VLE, REV

//--R6Ah--VL[8:0]=00000000-------------------------------//
	//VL[8:0]: Sets the scrolling amount of base image. The base image is scrolled in vertical direction and displayed from 
		//the line determined by VL[8:0]. Make sure that VL[8:0] <= 320
	LCD_TFT_WriteReg(0x006A, 0x0000); // set scrolling line


//--SPI Read/Write Control (R66h, Write Only)-------------------------------//


////////////////////////////////////////////////////////////////
//==�ֲ���ʾ����=Partial Display Control ================//

//--Partial Image 1 Display Position (R80h)------------------------------//
	//PTDP0[8:0]: Sets the display start position of partial image 1. The display areas of the partial images 1 and 2 must not overlap each another.
	LCD_TFT_WriteReg(0x0080, 0x0000);
	
//--Partial Image 1 RAM Start/End Address (R81h, R82h)-------------------//
	//PTSA0[8:0] PTEA0[8:0]: Sets the start line address and the end line address of the RAM area 
	//storing the data of partial image 1. Make sure PTSA0[8:0]  PTEA0[8:0].
	LCD_TFT_WriteReg(0x0081, 0x0000);
	LCD_TFT_WriteReg(0x0082, 0x0000);
	
//--Partial Image 2 Display Position (R83h)------------------------------//
	//PTDP1[8:0]: Sets the display start position of partial image 2 The display areas of the partial images 1 and 2 must not overlap each another.
	LCD_TFT_WriteReg(0x0083, 0x0000);

//--Partial Image 2 RAM Start/End Address (R84h, R85h)--------------------//
	//PTSA1[8:0] PTEA1[8:0]: Sets the start line address and the end line address of the RAM area 
	//storing the data of partial image 2 Make sure PTSA1[8:0]  PTEA1[8:0].
	LCD_TFT_WriteReg(0x0084, 0x0000);
	LCD_TFT_WriteReg(0x0085, 0x0000);
	
////////////////////////////////////////////////////////////////
//==Panel Control ====================================//

//--Panel Interface Control 1 (R90h)----------------------------//
	//RTNI[4:0]: Sets 1H (line) clock number of internal clock operating mode. 
	//In this mode, ILI9325C display operation is synchronized with internal clock signal.
		//RTNI[4:0]=10000=Clocks/LineΪ16 clocks
	//DIVI[1:0]: Sets the division ratio of internal clock frequency.
		//DIVI[1:0]=00=Division RatioΪ1��Internal Operation Clock Frequency=fosc / 1��
	LCD_TFT_WriteReg(0x0090, 0x0010);

//--Panel Interface Control 2 (R92h)---------------------------//
	//Note: The gate output non-overlap period is defined by the number of frequency-divided internal clocks, 
		//the frequency of which is determined by instruction (DIVI), from the reference point.
	//NOWI[2:0]: Sets the gate output non-overlap period when ILI9325C display operation is synchronized with internal clock signal.
		//NOWI[2:0]=000=Gate Non-overlap Period=Setting inhibited
	LCD_TFT_WriteReg(0x0092, 0x0000);

//--Panel Interface Control 3 (R93h)-----------------------------------//	
	LCD_TFT_WriteReg(0x0093, 0x0003);

//--Panel Interface Control 4 (R95h)-----------------------------------//
	//DIVE[1:0]: Sets the division ratio of DOTCLK when ILI9325C display operation is synchronized with RGB interface signals.
	LCD_TFT_WriteReg(0x0095, 0x0110);

//--Panel Interface Control 5 (R97h)-----------------------------------//	
	//NOWE[3:0]: Sets the gate output non-overlap period when the ILI9325C display operation is synchronized with RGB interface signals.
		//NOWE[3:0]=0000=Gate Non-overlap Period=Setting inhibited
	LCD_TFT_WriteReg(0x0097, 0x0000);
	LCD_TFT_WriteReg(0x0098, 0x0000);

////////////////////////////////////////////////////////////////
//==�����Ĵ���==================================//
//--OTP VCM Programming Control (RA1h)  //--OTP VCM Status and Enable (RA2h)   //--OTP Programming ID Key (RA5h)
//--Write Display Brightness Value (RB1h)  //--Read Display Brightness Value (RB2h) 
//--Write CTRL Display Value (RB3h)         //--Read CTRL Display Value (RB4h)   
//--Write Content Adaptive Brightness Control Value (RB5h)    //--Read Content Adaptive Brightness Control Value (RB6h) 
//--Write CABC Minimum Brightness (RBEh)   //--Read CABC Minimum Brightness (RBFh)   
//--CABC Control 1 (RC7h)  //--CABC Control 1 (RC8h)   //--CABC Control 2 (RC9h)   //--CABC Control 3 (RCAh)  
//--CABC Control 4 (RCBh)   //--CABC Control 5 (RCCh)  //--CABC Control 6 (RCDh)   //--CABC Control 7 (RCEh) 


////////////////////////////////////////////////////////////////
//==��ʾʹ��=====================================//	
//--��ʾ����1 (R07h)--PTDE1/0 = 0--BASEE=1--GON=1; DTE=1--CL=0--D[1:0] = 11-----------------//
	//PTDE[1:0] ����ͼ��2 �Ͳ���ͼ��1 ʹ��λ
		//PTDE1/0 = 0: �رղ���ͼ�񣬽���ʾ����ͼ��
		//PTDE1/0 = 1: ������ͼ�����û���ͼ����ʾʹ��λΪ0��BASEE=0��
	//BASEE ����ͼ����ʾλ��(D [1:0]���ñ�BASEE�����и��ߵ�����Ȩ��)
		//��BASEE=0  û�л���ͼ����ʾ��ILI9325����Һ���ڲ�����ʾ������߽�����ʾ����ͼ��
		//��BASEE=1  ��ʾ����ͼ��
	//GON �� DTE �ǰ������µ� ���趨G1��G320 ����������������.
		//GON=0; DTE=0; ==G1��G320���VGH    //GON=0; DTE=1; ==G1��G320���VGH
		//GON=1; DTE=0; ==G1��G320���VGL    //GON=1; DTE=1; ==G1��G320������ʾ���
	//CL=0=262144ɫ��ʾģʽ��ѡ��//CL=1=8ɫ��ʾģʽ��ѡ��
	//D[1:0] �趨D[1:0]=11 ������ʾ�����趨D[1:0]=00 ������ʾ��
	//ͨ����GON, DTE λ�������趨��D[1:0] ���趨��ʾ���Ƶ� ����ء�
	//��D1=0 ����û����ʾ�����е�Դ����ʵ͵�ƽ���Լ���LCD�ý�����AC����ѹ����Һ��ʱ�����ĳ��/�ŵ������
		//D[1:0] = ��01��, ���ر���ʾ��ILI9325��Ȼ�����ڲ�����ʾ������
		//D[1:0] = ��00��, ���ر���ʾʱ ILI9325 ���ڲ���ʾ������ȫֹͣ��
		//D[1:0] = ��11��, ����ʾ
	LCD_TFT_WriteReg(0x0007, 0x0133); // 262K color and display ON
	
}


/****************************************************************************
*������-Function:	void LCD_TFT_SetWindow(u16 xSta, u16 ySta, u16 xEnd, u16 yEnd)
*����- Description:		������ʾ���ڵ������С(�����յ�)-"����LCD_TFT_ILI9325"  
*�������-Input:	(xSta,ySta):����������ꣻ (yStat,yEnd):�����յ�����
*�������-output:	None
*ע������-Note��	
	��01) x<=239  ; y<=319
	��02)    ��03)    ��04)  
*****************************************************************************/
void LCD_TFT_SetWindow(u16 xSta, u16 ySta, u16 xEnd, u16 yEnd)  //������ʾ���ڵ������С(�����յ�)-"����LCD_TFT_ILI9325"  
{
	ILI9325_WriteRegIndex(0x50); //ˮƽ��ʼ����
	ILI9325_WriteData(xSta);

	ILI9325_WriteRegIndex(0x52); //��ֱ��ʼ����
	ILI9325_WriteData(ySta);


	ILI9325_WriteRegIndex(0x51);  //ˮƽ��������
	ILI9325_WriteData(xEnd);

	ILI9325_WriteRegIndex(0x53);  //��ֱ��������
	ILI9325_WriteData(yEnd);

	//LCD_WriteRegIndex(0x22);
}


/****************************************************************************
*������-Function:	void LCD_TFT_SetCursor(u16 x, u16 y)
*����- Description:		����GRAM�Ĺ��λ��-"����LCD_TFT_ILI9325"  
*�������-Input:	x: x�� ����;   y:y�� ����
*�������-output:	None
*ע������-Note��	
	��01) x<=239  ; y<=319
	��02)    ��03)    ��04)  
*****************************************************************************/
void LCD_TFT_SetCursor(u16 x, u16 y)  //����GRAM�Ĺ��λ��-"����LCD_TFT_ILI9325"  
{
	LCD_TFT_WriteReg(0x20, x);  // x�� ����
	LCD_TFT_WriteReg(0x21, y);  // y�� ����
}


/****************************************************************************
*������-Function:	void LCD_TFT_ClearDisBuf(void)
*����- Description:		��ʾ������������(����:�Ϳո�20H)-"����LCD_TFT_ILI9325"  
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01)  ֻ������ʾ��������ֵ��Ϊ0x20(��ʾΪ��)��������ͼ�β�����
	��02)    ��03)    ��04)  
*****************************************************************************/
void LCD_TFT_ClearDisBuf(void)   //��ʾ������������(����:�Ϳո�20H)-"����LCD_TFT_ILI9325"  
{
	u8 i,j;
	
	for(j = 0; j < 15; j++)    //"����LCD_TFT_ILI9325"��ʾ���ݻ�������(15��,ÿ��40�ַ�)
	{
		for(i = 0; i < 41; i++)
		{
			G_LcdBuf[j][i] = M_Space_ASCII;
		}
	}
}



/****************************************************************************
*������-Function:	void LCD_TFT_Clear(u16 color)
*����- Description:		ȫ������-"����LCD_TFT_ILI9325"  
*�������-Input:	color: ����������ɫ
*�������-output:	None
*ע������-Note��	��01)     ��02)    ��03)    ��04)  
*****************************************************************************/
void LCD_TFT_Clear(u16 color)   //ȫ������-"����LCD_TFT_ILI9325"  
{
	u32 index = 0;

	LCD_TFT_SetCursor(0x0000, 0x0000);  //����GRAM�Ĺ��λ��(0,0)
	
	LCD_TFT_WriteRAM_CMD(); //��ILI9325д"GRAM�����ַ"
	
	for(index = 0; index < 76800; index++)
	{
		LCD_TFT_WriteRAM(color);   //��ÿ��GRAMд������
	}
}





/****************************************************************************
*������-Function:	void LCD_TFT_DrawPoint(u16 x, u16 y, u16 color)
*����- Description:		����( ָ������,��ɫ)-"����LCD_TFT_ILI9325"  
*�������-Input:	x,y: �������;   color : ��ɫ 
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void LCD_TFT_DrawPoint(u16 x, u16 y, u16 color) //����( ָ������,��ɫ)-"����LCD_TFT_ILI9325"  
{
	LCD_TFT_SetCursor(x, y);//����GRAM�Ĺ��λ��
	
	LCD_TFT_WriteRAM_CMD(); //��ILI9325д"GRAM�����ַ"

	LCD_TFT_WriteRAM(color);//��GRAMд������
}



/****************************************************************************
*������-Function:	void LCD_TFT_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
*����- Description:		����-"����LCD_TFT_ILI9325"  
*�������-Input:	x1,y1: �������;  x2,y2: �յ�����;  color:�ߵ���ɫ  
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void LCD_TFT_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)  //����-"����LCD_TFT_ILI9325"  
{
	u16 t;
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;

	delta_x=x2-x1; //������������
	delta_y=y2-y1;
	
	uRow=x1;
	uCol=y1;
	
	if(delta_x>0)incx=1; //���õ�������
	else if(delta_x==0)incx=0;//��ֱ��
	else {incx=-1;delta_x=-delta_x;}
	
	if(delta_y>0)incy=1;
	else if(delta_y==0)incy=0;//ˮƽ��
	else{incy=-1;delta_y=-delta_y;}
	
	if( delta_x>delta_y)distance=delta_x; //ѡȡ��������������
	else distance=delta_y;
	
	for(t=0;t<=distance+1;t++ )//�������
	{
		LCD_TFT_DrawPoint(uRow,uCol,color);//����
		xerr+=delta_x ;
		yerr+=delta_y ;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}

}



/****************************************************************************
*������-Function:	void LCD_TFT_DrawRectangle(u16 xSta, u16 ySta, u16 xEnd, u16 yEnd,u16 color)
*����- Description:		�����ο�-"����LCD_TFT_ILI9325"  
*�������-Input:	x1,y1: �������;  x2,y2: �յ�����;  color:�ߵ���ɫ  
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void LCD_TFT_DrawRectangle(u16 xSta, u16 ySta, u16 xEnd, u16 yEnd,u16 color)  //�����ο�-"����LCD_TFT_ILI9325"  
{
	LCD_TFT_DrawLine(xSta,ySta,xSta,yEnd,color); 
	LCD_TFT_DrawLine(xSta,yEnd,xEnd,yEnd,color); 
	LCD_TFT_DrawLine(xEnd,yEnd,xEnd,ySta,color); 
	LCD_TFT_DrawLine(xEnd,ySta,xSta,ySta,color); 
}



/****************************************************************************
*������-Function:	void LCD_TFT_DrawCircle(u16 x0,u16 y0,u8 r,u16 color)
*����- Description:		��Բ-"����LCD_TFT_ILI9325"  
*�������-Input:	(x,y):���ĵ�;  r    :�뾶; color:�ߵ���ɫ 
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void LCD_TFT_DrawCircle(u16 x0,u16 y0,u8 r,u16 color)  //��Բ-"����LCD_TFT_ILI9325"  
{
	int a,b;
	int di;
	a=0;b=r;
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_TFT_DrawPoint(x0-b,y0-a,color);             //3
		LCD_TFT_DrawPoint(x0+b,y0-a,color);             //0
		LCD_TFT_DrawPoint(x0-a,y0+b,color);          //   //1
		LCD_TFT_DrawPoint(x0-b,y0-a,color);         //    //  7
		LCD_TFT_DrawPoint(x0-a,y0-b,color);          //   //2
		LCD_TFT_DrawPoint(x0+b,y0+a,color);          //   //4
		LCD_TFT_DrawPoint(x0+a,y0-b,color);             //5
		LCD_TFT_DrawPoint(x0+a,y0+b,color);             //6
		LCD_TFT_DrawPoint(x0-b,y0+a,color);
		a++;
		//ʹ��Bresenham�㷨��Բ
		if(di<0)di +=4*a+6;
		else
		{
			di+=10+4*(a-b);
			b--;
		}
		LCD_TFT_DrawPoint(x0+a,y0+b,color);
	}

}


/****************************************************************************
*������-Function:	void LCD_TFT_FillRectangle(u16 xSta,u16 ySta,u16 xEnd,u16 yEnd,u16 color) 
*����- Description:		���һ��LCD��������(ָ����С����ɫ)-"����LCD_TFT_ILI9325" 
*�������-Input:	(xSta,ySta): �������;  (xEnd,yEnd):�յ�����; color: �����ɫ
*�������-output:	None
*ע������-Note��	
	��01)    �����С:(xEnd-xSta)*(yEnd-ySta)
	��02)   xSta<xEnd;     ySta<yEnd;  
	��03)    ��04)  
*****************************************************************************/
void LCD_TFT_FillRectangle(u16 xSta,u16 ySta,u16 xEnd,u16 yEnd,u16 color)  //���һ��LCD��������(ָ����С����ɫ)-"����LCD_TFT_ILI9325" 
{
	u16 i = 0;
	u16 j = 0;
	u16 Length = 0;

#if defined USE_HORIZONTAL_LCD_TFT    //ʹ�õ�"ˮƽ(����)��ʾģʽ"
	Length = yEnd - ySta + 1;

	for(i = xSta; i <= xEnd; i++)
	{
		LCD_TFT_SetCursor(i,ySta);	 //���ù��λ��
		LCD_TFT_WriteRAM_CMD(); 	 //��ILI9325д"GRAM�����ַ"
		
		for(j = 0; j < Length; j++) LCD_TFT_WriteRAM(color);//��GRAMд������
	}

#elif defined USE_VERTICAL_LCD_TFT       //ʹ�õ�"��ֱ(����)��ʾģʽ"
	Length = xEnd - xSta + 1;

	for(i = ySta; i <= yEnd; i++)
	{
		LCD_TFT_SetCursor(xSta,i);	 //���ù��λ��
		LCD_TFT_WriteRAM_CMD(); 	 //��ILI9325д"GRAM�����ַ"
		
		for(j = 0; j < Length; j++) LCD_TFT_WriteRAM(color);//��GRAMд������
	}

#endif
}


/****************************************************************************
*������-Function:	void LCD_TFT_ShowChar(u16 x,u16 y,u8 AscNum,u8 Font,u16 pointColor,u16 backColor)
*����- Description:		��ʾһ���ַ�( ָ������,�����С,��ɫ)-"����LCD_TFT_ILI9325"  
*�������-Input:	x:  x�� ����;                                       y:  y�� ����;
						AscNum: ��ʾ���ַ�(ASCII��);     Font:�����С 12/16;
						pointColor: ������ɫ;                        backColor: ������ɫ;
*�������-output:	None
*ע������-Note��	
	��01)  x<=232  ; y<=312
	��02) ����ʾ��    LCD_TFT_ShowChar(0,0,'A',FONT1608,BLACK,WHITE);  //������(0,0)��,��ʾ�ַ�A(16*8����,�׵׺���)
	��03)    ��04)  
****************************************************************************/
void LCD_TFT_ShowChar(u16 x,u16 y,u8 AscNum,u8 Font,u16 pointColor,u16 backColor) //��ʾһ���ַ�( ָ������,�����С,��ɫ)-"����LCD_TFT_ILI9325"  
{
    u8  AscChar = 0;
    u8  i = 0;
	u8  j = 0;
	
	u8  VerticalNum = 0;
	u8  horizontalNum = 0;

	AscNum = AscNum - M_Space_ASCII;//�õ�ƫ�ƺ��ֵ//0x20Ϊ�ո�ֵ

///////////////////////////////////////////////////////////////////////
//==ʹ�õ�"ˮƽ(����)��ʾģʽ"
///////////////////////////////////////////////////////////////////////
#if defined USE_HORIZONTAL_LCD_TFT 	//ʹ�õ�"ˮƽ(����)��ʾģʽ"
	u16 yBuf = 0;
	yBuf = y;  //����y ����ֵ

	switch(Font) 
	{
		case FONT1206:	//����12*6
			VerticalNum = 12;
			horizontalNum = 6;
			break;	
			
		case FONT1608:  //����16*8
			VerticalNum = 16;
			horizontalNum = 8;
			break;	
		default:   break;
	}

	/////////////////////////////////////////////////////////////////////////////
	for(i = 0; i < VerticalNum; i++)
	{
		switch(Font) 
		{
			case FONT1206:	//����12*6
				AscChar = asc2_1206[AscNum][i];//����1206����
				break;	
				
			case FONT1608:	//����16*8
				AscChar = asc2_1608[AscNum][i];//����1608����
				break;	
			default:   break;
		}
		
		/////////////////////////////////////////////////////////////////////////////
		for(j = 0; j < horizontalNum; j++)
		{
			if(AscChar & 0x01) LCD_TFT_DrawPoint(x, y, pointColor);  // ���ַ����ĵ�
			else  LCD_TFT_DrawPoint(x, y, backColor);  //���հ״��ĵ�

			AscChar >>= 1;
			y ++;
		}
		
		y = yBuf;
		x ++;
	}


///////////////////////////////////////////////////////////////////////
//==ʹ�õ�"��ֱ(����)��ʾģʽ"
///////////////////////////////////////////////////////////////////////
#elif defined USE_VERTICAL_LCD_TFT  //ʹ�õ�"��ֱ(����)��ʾģʽ"
	u16 xBuf = 0;
	xBuf = x;  //����x ����ֵ

	switch(Font) 
	{
		case FONT1206:	//����12*6
			VerticalNum = 12;
			horizontalNum = 6;
			break;	
			
		case FONT1608:  //����16*8
			VerticalNum = 16;
			horizontalNum = 8;
			break;	
		default:   break;
	}

	/////////////////////////////////////////////////////////////////////////////
	for(i = 0; i < VerticalNum; i++)
	{
		switch(Font) 
		{
			case FONT1206:	//����12*6
				AscChar = asc2_1206[AscNum][i];//����1206����
				break;	
				
			case FONT1608:	//����16*8
				AscChar = asc2_1608[AscNum][i];//����1608����
				break;	
			default:   break;
		}

		/////////////////////////////////////////////////////////////////////////////
		for(j = 0; j < horizontalNum; j++)
		{
			if(AscChar & 0x01) LCD_TFT_DrawPoint(x, y, pointColor);  // ���ַ����ĵ�
			else  LCD_TFT_DrawPoint(x, y, backColor);  //���հ״��ĵ�

			AscChar >>= 1;
			x ++;
		}
		
		x = xBuf;
		y ++;
	}

#endif
}



/****************************************************************************
*������-Function:	void LCD_TFT_ShowString(u16 line,u16 column,u8 *ArrayPoint,u8 Font,u16 pointColor,u16 backColor)
*����- Description:		��ʾ�ַ���( ָ������,�����С,��ɫ)-"����LCD_TFT_ILI9325"  
*�������-Input:	line:    ��Line��;             column:   ��column��;
						*ArrayPoint:�ַ���������ʼ��ַ;     
						Font:�����С 12/16;    pointColor: ������ɫ;     backColor: ������ɫ;
*�������-output:	None
*ע������-Note��	
	��01)  x<=232  ; y<=312
	��02) ����ʾ��   
	��03)    ��04)  
****************************************************************************/
void LCD_TFT_ShowString(u16 line,u16 column,u8 *ArrayPoint,u8 Font,u16 pointColor,u16 backColor) //��ʾ�ַ���( ָ������,�����С,��ɫ)-"����LCD_TFT_ILI9325"  
{
	u16 x = 0;
	u16 y = 0;
	
	u8  VerticalNum = 0;
	u8  horizontalNum = 0;

	u16 max_x = 0;
	u16 max_y = 0;

#if defined USE_HORIZONTAL_LCD_TFT    //ʹ�õ�"ˮƽ(����)��ʾģʽ"
	x = line;
	y = column;

	switch(Font) 
	{
		case FONT1206:	//����12*6
			VerticalNum = 12;
			horizontalNum = 6;
			
			max_x = 234;
			max_y = 314;
			break;	

		case FONT1608:  //����16*8
			VerticalNum = 16;
			horizontalNum = 8;
			
			max_x = 232;
			max_y = 312;
			break;	
		default:   break;
	}

	//////////////////////////////////////////////////////////////////////
    while(*ArrayPoint != '\0')
	{
        if(x > max_x) {x = y = 0; LCD_TFT_Clear(backColor);}
        if(y > max_y) {y = 0; x += VerticalNum;}
		
		LCD_TFT_ShowChar(x,y,*ArrayPoint,Font,pointColor,backColor);
		
		y += horizontalNum;    //�����ַ�ۼӣ�ָ����һ���ַ�����ʾλ��
        ArrayPoint ++;  //����ָ���ۼӣ�ָ����һ���ַ�
    }
	
#elif defined USE_VERTICAL_LCD_TFT       //ʹ�õ�"��ֱ(����)��ʾģʽ"
	x = column;
	y = line;
	switch(Font) 
	{
		case FONT1206:	//����12*6
			VerticalNum = 12;
			horizontalNum = 6;
			break;	
			
		case FONT1608:  //����16*8
			VerticalNum = 16;
			horizontalNum = 8;
			break;	
		default:   break;
	}

	//////////////////////////////////////////////////////////////////////
	while(*ArrayPoint != '\0')
	{		
        if(x > max_x) {x = 0; y += VerticalNum;}
        if(y > max_y) {x = y = 0; LCD_TFT_Clear(backColor);}
		
		LCD_TFT_ShowChar(x,y,*ArrayPoint,Font,pointColor,backColor);
		
		x += horizontalNum;    //�����ַ�ۼӣ�ָ����һ���ַ�����ʾλ��
        ArrayPoint ++;  //����ָ���ۼӣ�ָ����һ���ַ�
    }
#endif
}


/****************************************************************************
*������-Function:	void LCD_TFT_Show_ChFont2424(void)
*����- Description:		��ʾ1��24*24�ĺ���-"����LCD_TFT_ILI9325"  
*�������-Input:	(x,y):������ʾ��λ��    index:tfont24��������ĵڼ�������
						pointColor: ���ֻ�����ɫ;     backColor: ������ɫ;
*�������-output:	None
*ע������-Note��	
	��01) 
	��02)  	 ��03)    ��04)  
****************************************************************************/
void LCD_TFT_Show_ChFont2424(u16 x,u16 y,u8 index,u16 pointColor,u16 backColor) //��ʾ1��24*24�ĺ���-"����LCD_TFT_ILI9325"  
{
	u8 byteNum = 0;
	u8 i = 0;
	u8 temp;
	
	u16 x0=x;
	
	for(byteNum = 0; byteNum < 72; byteNum++)//ÿ��24*24�ĺ��ֵ��� ��72���ֽ�
	{
		//��ά����ÿһά���24�ֽ�
		if(byteNum < 24) temp = tfont24[index*3][byteNum];             //ǰ24���ֽ�
		else if(byteNum < 48) temp=tfont24[index*3 + 1][byteNum - 24]; //��24���ֽ�
		else temp = tfont24[index*3 + 2][byteNum - 48];                //��24���ֽ�
	
		for(i = 0; i < 8; i++)	 //ÿ���ֽ�8λ����
		{
			if(temp & 0x80) LCD_TFT_DrawPoint(x,y,pointColor); //�����ֵĵ�
			else LCD_TFT_DrawPoint(x,y,backColor);   //���հ׵㣨ʹ�ñ���ɫ��
			temp <<= 1;
			x ++;
			if((x-x0) == 24)	  //�ﵽ��������ֵ��ʼ�µ�һ��
			{
				x=x0;
				y++;
				break;
			}
		}
	}
}









/****************************************************************************
*������-Function:	void LCD_TFT_Show_StandbyPage(void)
*����- Description:		��ʾ"����ҳ��"-"����LCD_TFT_ILI9325"  
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01)       ��02)  	 ��03)    ��04)  
****************************************************************************/
void LCD_TFT_Show_StandbyPage(void) //��ʾ"����ҳ��"-"����LCD_TFT_ILI9325"  
{	
	u8  ChNum = 0;
	u16 yStart = 0;
	
	Init_GPIO_LCD_TFT_ILI9325();  //��ʼ��: "����LCD_TFT_ILI9325"  IO�˿�

	
	LCD_TFT_Clear(RED);  //ȫ������-"����LCD_TFT_ILI9325"   
	
	LCD_TFT_Clear(GREEN);  //ȫ������-"����LCD_TFT_ILI9325"	 

	LCD_TFT_Clear(BLUE);  //ȫ������-"����LCD_TFT_ILI9325"	 

	LCD_TFT_FillRectangle(0  , 0, 39,319,RED);
	LCD_TFT_FillRectangle(40 , 0, 79,319,BLACK);
	LCD_TFT_FillRectangle(80 , 0,119,319,BLUE);
	LCD_TFT_FillRectangle(120, 0,159,319,GREEN);
	LCD_TFT_FillRectangle(160, 0,199,319,GBLUE);
	LCD_TFT_FillRectangle(200, 0,239,319,YELLOW);
	
	LCD_TFT_ShowString( 8,90,"TEXAS INSTRUMENTS",FONT1608,WHITE,RED);
	LCD_TFT_ShowString(48,74,"TI University Program",FONT1608,GBLUE,BLACK);

	yStart = 88;
	for(ChNum = 12;ChNum < 18; ChNum++)//MSP430_FFTB
	{
		LCD_TFT_Show_ChFont2424(88,yStart,ChNum,GBLUE,BLUE);  //LIGHTGREEN
		yStart += 24;
	}

	yStart = 76;
	for(ChNum = 0;ChNum < 6; ChNum++) //���е��ӿƼ�
	{
		LCD_TFT_Show_ChFont2424(128,yStart,ChNum,RED,GREEN);
		yStart += 26;
	}

	LCD_TFT_ShowString(168,50,"Deyan Electronic Technology",FONT1608,RED,GBLUE);

	LCD_TFT_ShowString(208,104,"www.gototi.com",FONT1608,BLUE,YELLOW);
	
}



/****************************************************************************
*������-Function:	void LCD_TFT_Show_WorkPage(void)
*����- Description:		��ʾ"����ҳ��"-"����LCD_TFT_ILI9325"  
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01)       ��02)  	 ��03)    ��04)  
****************************************************************************/
void LCD_TFT_Show_WorkPage(void) //��ʾ"����ҳ��"-"����LCD_TFT_ILI9325"  
{	
	
	Init_GPIO_LCD_TFT_ILI9325();  //��ʼ��: "����LCD_TFT_ILI9325"  IO�˿�

	LCD_TFT_Clear(AD_Back);  //(���)ȫ������-"����LCD_TFT_ILI9325"	 

	//����һ����(���)
	LCD_TFT_DrawLine(M_MenuLine_01-1,M_MenuColumn_01,M_MenuLine_01-1,M_TestColumn_20+7,AD_Point);   
	LCD_TFT_DrawLine(M_MenuLine_01-2,M_MenuColumn_01,M_MenuLine_01-2,M_TestColumn_20+7,AD_Point); 
	LCD_TFT_DrawLine(M_MenuLine_01-3,M_MenuColumn_01,M_MenuLine_01-3,M_TestColumn_20+7,AD_Point); 

	//����һ����(���)
	LCD_TFT_DrawLine(M_MenuLine_12+16,M_MenuColumn_01,M_MenuLine_12+16,M_TestColumn_20+7,AD_Point); 
	LCD_TFT_DrawLine(M_MenuLine_12+16+1,M_MenuColumn_01,M_MenuLine_12+16+1,M_TestColumn_20+7,AD_Point); 
	LCD_TFT_DrawLine(M_MenuLine_12+16+2,M_MenuColumn_01,M_MenuLine_12+16+2,M_TestColumn_20+7,AD_Point); 


	//�м�һ����(���)
	LCD_TFT_DrawLine(M_MenuLine_01-1,M_MenuColumn_19+8+2,M_MenuLine_12+16, M_MenuColumn_19+8+2,AD_Point); 
	LCD_TFT_DrawLine(M_MenuLine_01-1,M_MenuColumn_19+8+3,M_MenuLine_12+16, M_MenuColumn_19+8+3,AD_Point); 
	LCD_TFT_DrawLine(M_MenuLine_01-1,M_MenuColumn_19+8+4,M_MenuLine_12+16, M_MenuColumn_19+8+4,AD_Point); 

	//��ʾ�����
	LCD_TFT_ShowString(M_01Line,M_01Column+2,"Welcome to FFTB6638 v3.0",FONT1608,AD_Point,AD_Back);
	LCD_TFT_ShowString(M_01Line,M_12Column+2,"FFTB6638",FONT1608,Fixed_Point,AD_Back);
	LCD_TFT_ShowString(M_01Line,M_22Column+2,"3.0",FONT1608,Fixed_Point,AD_Back);

	LCD_TFT_ShowString(M_01Line,M_27Column-2,"www.gototi.com",FONT1608,AD_Point,AD_Back);
	LCD_TFT_ShowString(M_01Line,M_31Column-2,"gototi",FONT1608,Fixed_Point,AD_Back);

	
	//��"�˵���"
	LCD_TFT_FillRectangle(M_MenuLine_01, M_MenuColumn_01,M_MenuLine_12+15,M_MenuColumn_19+8+1,Menu_Back);

	//��"������"
	LCD_TFT_FillRectangle(M_TestLine_01, M_TestColumn_01-3,M_TestLine_12+15,M_TestColumn_20+7,Test_Back);

	//��ʾ"�����"�Ļ����ַ�(��λ��)
	LCD_TFT_ShowString(M_15Line,M_01Column,"FFFF-FF-FF FF:FF:FF FFF FF.FC FFFmA    ",FONT1608,Monitor_Point,Monitor_Back);
		//���¶ȵĵ�λ�ȵ�"С���" //��Բ-"����LCD_TFT_ILI9325"  
	LCD_TFT_DrawCircle(M_15Line+1,M_29Column+1,1,Monitor_Point); 

	//��"����"����
		//"�������"
	LCD_TFT_DrawRectangle(M_15Line,M_37Column,M_15Line+13,M_40Column+2,Monitor_Point); 
	LCD_TFT_DrawRectangle(M_15Line+4,M_40Column+2,M_15Line+9,M_40Column+5,Monitor_Point); 
		//"����ֵ"--��ߵ�01��������
	LCD_TFT_FillRectangle(M_15Line+2,M_37Column+2,M_15Line+11,M_37Column+7,Monitor_Point);
		//"����ֵ"--��ߵ�02��������
	LCD_TFT_FillRectangle(M_15Line+2,M_38Column+2,M_15Line+11,M_38Column+7,Monitor_Point);
		//"����ֵ"--��ߵ�03��������
	LCD_TFT_FillRectangle(M_15Line+2,M_39Column+2,M_15Line+11,M_39Column+7,Monitor_Point);

}







/****************************************************************************
*������-Function:	void Deal_LCD_TFT(void)
*����- Description:		��ʾ����-"����LCD_TFT_ILI9325"  //ֻ�������ݱ仯����ʾ����
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_LCD_TFT(void) //��ʾ����-"����LCD_TFT_ILI9325"  //ֻ�������ݱ仯����ʾ����
{   

////////////////////////////////////////////////////////////////////////////
//==** �ر�Һ��:��ˢ�¡��رձ���**====================//
    if(F_Close_LCD_TFT)   // �ر�Һ��:��ˢ�¡��رձ���
    {		//����: ����͵�ƽ(ռ�ձ�Ϊ  0%)(��ʱ����ر�)
		mClose_LCD_TFT_BackLight;	//��������Ϊ"���"	 ,��"�ر�"LCD_TFT����
    }

////////////////////////////////////////////////////////////////////////////
//==** ����Һ��:ˢ����ʾ��������**====================//
if(!F_Close_LCD_TFT)
{
		//����: ����ߵ�ƽ(ռ�ձ�Ϊ100%)(��ʱ��������)
	mOpen_LCD_TFT_BackLight; //��������Ϊ"���"  ,��"��"LCD_TFT����


////////////////////////////////////////////////////////////////////////////
//==**�����λLCD_TFT**==================================//
	if(F_ReSet_LCD_TFT) //LCD_TFT��λ����
	{
		F_ReSet_LCD_TFT = 0;
		Reset_LCD_TFT_ILI9325(); //��λ"����LCD_TFT_ILI9325"ģ��
	}

////////////////////////////////////////////////////////////////////////////
//==**"����"����**======================================//
	if(F_Clear_LCD_TFT ) //"����"����	   
	{
		F_Clear_LCD_TFT = 0;	
//LCD_TFT_Clear(BACK_COLOR);  //ȫ������-"����LCD_TFT_ILI9325"  
	}
		
////////////////////////////////////////////////////////////////////////////
//==**����"���ݱ仯"����ʾ����**======================//
	if((G_Update_01Bits != 0) || (G_Update_02Bits != 0)|| (G_Update_03Bits != 0))//"ˢ��"����
	{
		Init_GPIO_LCD_TFT_ILI9325();  //��ʼ��: "����LCD_TFT_ILI9325"  IO�˿�

		Update_LCD_TFT();	//����"���ݱ仯"����ʾ����-"����LCD_TFT_ILI9325"  
		
	}	
}
}





/****************************************************************************
*������-Function:	void Update_LCD_TFT(void)
*����- Description:		����"���ݱ仯"����ʾ����-"����LCD_TFT_ILI9325"  
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) 	��02)    ��03)    ��04)  
*****************************************************************************/
void Update_LCD_TFT(void)  //����"���ݱ仯"����ʾ����-"����LCD_TFT_ILI9325"  
{

////////////////////////////////////////////////////////////////////////////
//==** ˢ��: �����**=======================================//
	if(F_Update_AdLine)  
	{		
		F_Update_AdLine = 0;
		
		//LCD_ShowString(M_01Line_LCD_TFT, M_Start_Column, &G_LCD_TFT_Buf[M_01Row_LCD_TFT][M_Start_Column_Buf]);
		//LCD_TFT_ShowString(M_01Line_LCD_TFT, M_05Char_LCD_TFT,"Welcome to MSP430F6638    ");
	}

/////////////////////////////////////////////////////////////////////////////////
//	if((G_Update_01Bits != 0)||(G_Update_02Bits != 0))
//	{
		Update_MenuLine_LCD_TFT(); //����"�˵���""���ݱ仯"����ʾ����-"����LCD_TFT_ILI9325"  

		Update_TestLine_LCD_TFT(); //����"������""���ݱ仯"����ʾ����-"����LCD_TFT_ILI9325"  
//	}
//	else if(G_Update_03Bits != 0)
//	{
		Update_MonitorLine_LCD_TFT();  //����"�����""���ݱ仯"����ʾ����-"����LCD_TFT_ILI9325"  
//	}

////////////////////////////////////////////////////////////////////////////
//==**��˸��ʾ���("����LCD_TFT")**==========================//

}


/****************************************************************************
*������-Function:	void Update_MonitorLine_LCD_TFT(void)
*����- Description:		����"�����""���ݱ仯"��k��ʾ����-"����LCD_TFT_ILI9325"  
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) 	��02)    ��03)    ��04)  
*****************************************************************************/
void Update_MonitorLine_LCD_TFT(void)  //����"�����""���ݱ仯"����ʾ����-"����LCD_TFT_ILI9325"  
{
	if(!F_Update_RealTime)
	{
		////////////////////////////////////////////////////////////////////////////
		//==** ˢ��:"ʵʱ�¶�"**====================================//
		if(F_Update_Temperature)
		{
			F_Update_Temperature = 0;
		
			//�¶�ֵ����ָ���Ĺ̶���ɫ��ʾ
			LCD_TFT_ShowChar(M_15Line,M_24Column, G_LcdBuf[M_15LineBuf][M_24ColumnBuf],FONT1608,Fixed_Point,Monitor_Back);
			LCD_TFT_ShowChar(M_15Line,M_25Column, G_LcdBuf[M_15LineBuf][M_25ColumnBuf],FONT1608,Fixed_Point,Monitor_Back);
			LCD_TFT_ShowChar(M_15Line,M_26Column, G_LcdBuf[M_15LineBuf][M_26ColumnBuf],FONT1608,Fixed_Point,Monitor_Back);
			LCD_TFT_ShowChar(M_15Line,M_28Column, G_LcdBuf[M_15LineBuf][M_28ColumnBuf],FONT1608,Fixed_Point,Monitor_Back);
		}
		
		////////////////////////////////////////////////////////////////////////////
		//==**ˢ��:  "INA21x ʵʱ����ֵ"**============================//
		if(F_Update_CurrentValue) //ˢ��:"INA21x ʵʱ����ֵ"
		{
			F_Update_CurrentValue = 0;
			
			LCD_TFT_ShowChar(M_15Line,M_31Column, G_LcdBuf[M_15LineBuf][M_31ColumnBuf],FONT1608,Fixed_Point,Monitor_Back);
			LCD_TFT_ShowChar(M_15Line,M_32Column, G_LcdBuf[M_15LineBuf][M_32ColumnBuf],FONT1608,Fixed_Point,Monitor_Back);
			LCD_TFT_ShowChar(M_15Line,M_33Column, G_LcdBuf[M_15LineBuf][M_33ColumnBuf],FONT1608,Fixed_Point,Monitor_Back);
		}
		
		////////////////////////////////////////////////////////////////////////////
		//==**ˢ��:  "﮵�ص���"**=================================//
		if(F_Update_Power) //ˢ��:"﮵�ص���"
		{
			F_Update_Power = 0;
			
			Disp_BQ27410_FuelGauge(); //��LCD_TFT�ϣ���ʾ"﮵��":״̬+����
		}
	
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==** ˢ��:"ʵʱʱ��" **====================================//
	else if(F_Update_RealTime)
	{
		F_Update_RealTime = 0;
		//��
		LCD_TFT_ShowChar(M_15Line,M_01Column, G_LcdBuf[M_15LineBuf][M_01ColumnBuf],FONT1608,Monitor_Point,Monitor_Back);
		LCD_TFT_ShowChar(M_15Line,M_02Column, G_LcdBuf[M_15LineBuf][M_02ColumnBuf],FONT1608,Monitor_Point,Monitor_Back);
		LCD_TFT_ShowChar(M_15Line,M_03Column, G_LcdBuf[M_15LineBuf][M_03ColumnBuf],FONT1608,Monitor_Point,Monitor_Back);
		LCD_TFT_ShowChar(M_15Line,M_04Column, G_LcdBuf[M_15LineBuf][M_04ColumnBuf],FONT1608,Monitor_Point,Monitor_Back);
	
		//��
		LCD_TFT_ShowChar(M_15Line,M_06Column, G_LcdBuf[M_15LineBuf][M_06ColumnBuf],FONT1608,Monitor_Point,Monitor_Back);
		LCD_TFT_ShowChar(M_15Line,M_07Column, G_LcdBuf[M_15LineBuf][M_07ColumnBuf],FONT1608,Monitor_Point,Monitor_Back);
	
		//��
		LCD_TFT_ShowChar(M_15Line,M_09Column, G_LcdBuf[M_15LineBuf][M_09ColumnBuf],FONT1608,Monitor_Point,Monitor_Back);
		LCD_TFT_ShowChar(M_15Line,M_10Column, G_LcdBuf[M_15LineBuf][M_10ColumnBuf],FONT1608,Monitor_Point,Monitor_Back);
	
		//ʱ
		LCD_TFT_ShowChar(M_15Line,M_12Column, G_LcdBuf[M_15LineBuf][M_12ColumnBuf],FONT1608,Monitor_Point,Monitor_Back);
		LCD_TFT_ShowChar(M_15Line,M_13Column, G_LcdBuf[M_15LineBuf][M_13ColumnBuf],FONT1608,Monitor_Point,Monitor_Back);
	
		//��
		LCD_TFT_ShowChar(M_15Line,M_15Column, G_LcdBuf[M_15LineBuf][M_15ColumnBuf],FONT1608,Monitor_Point,Monitor_Back);
		LCD_TFT_ShowChar(M_15Line,M_16Column, G_LcdBuf[M_15LineBuf][M_16ColumnBuf],FONT1608,Monitor_Point,Monitor_Back);
	
		//�룬��ָ���Ĺ̶���ɫ��ʾ
		LCD_TFT_ShowChar(M_15Line,M_18Column, G_LcdBuf[M_15LineBuf][M_18ColumnBuf],FONT1608,Fixed_Point,Monitor_Back);
		LCD_TFT_ShowChar(M_15Line,M_19Column, G_LcdBuf[M_15LineBuf][M_19ColumnBuf],FONT1608,Fixed_Point,Monitor_Back);
	
		//����
		LCD_TFT_ShowChar(M_15Line,M_21Column, G_LcdBuf[M_15LineBuf][M_21ColumnBuf],FONT1608,Monitor_Point,Monitor_Back);
		LCD_TFT_ShowChar(M_15Line,M_22Column, G_LcdBuf[M_15LineBuf][M_22ColumnBuf],FONT1608,Monitor_Point,Monitor_Back);
		LCD_TFT_ShowChar(M_15Line,M_23Column, G_LcdBuf[M_15LineBuf][M_23ColumnBuf],FONT1608,Monitor_Point,Monitor_Back);
	
	}

}

/****************************************************************************
*������-Function:	void Update_MenuLine_LCD_TFT(void)
*����- Description:		����"�˵���""���ݱ仯"����ʾ����-"����LCD_TFT_ILI9325"  
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) 	��02)    ��03)    ��04)  
*****************************************************************************/
void Update_MenuLine_LCD_TFT(void)  //����"�˵���""���ݱ仯"����ʾ����-"����LCD_TFT_ILI9325"  
{
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��01 �˵���"**=============================//
	if(F_Update_MenuLine01)
	{
		F_Update_MenuLine01 = 0;
		
		if(F_HL_MenuLine01) 
		{
			F_HL_MenuLine01 = 0;
			LCD_TFT_ShowString(M_MenuLine_01,M_MenuColumn_01,&G_LcdBuf[MenuLine01][MenuColumn01],FONT1608,Menu_Back,Fixed_Point);
		}
		else {LCD_TFT_ShowString(M_MenuLine_01,M_MenuColumn_01,&G_LcdBuf[MenuLine01][MenuColumn01],FONT1608,Fixed_Point,Menu_Back);}		
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��02 �˵���"**=============================//
	if(F_Update_MenuLine02)
	{
		F_Update_MenuLine02 = 0;
		
		if(F_HL_MenuLine02) 
		{
			F_HL_MenuLine02 = 0;
			LCD_TFT_ShowString(M_MenuLine_02,M_MenuColumn_01,&G_LcdBuf[MenuLine02][MenuColumn01],FONT1608,HL_Menu_Point,HL_Menu_Back);
		}
		else 
		{LCD_TFT_ShowString(M_MenuLine_02,M_MenuColumn_01,&G_LcdBuf[MenuLine02][MenuColumn01],FONT1608,Menu_Point,Menu_Back);}
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��03 �˵���"**=============================//
	if(F_Update_MenuLine03)
	{
		F_Update_MenuLine03 = 0;
	
		if(F_HL_MenuLine03) 
		{
			F_HL_MenuLine03 = 0;
			LCD_TFT_ShowString(M_MenuLine_03,M_MenuColumn_01,&G_LcdBuf[MenuLine03][MenuColumn01],FONT1608,HL_Menu_Point,HL_Menu_Back);
		}
		else 
		{LCD_TFT_ShowString(M_MenuLine_03,M_MenuColumn_01,&G_LcdBuf[MenuLine03][MenuColumn01],FONT1608,Menu_Point,Menu_Back);}
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��04 �˵���"**=============================//
	if(F_Update_MenuLine04)
	{
		F_Update_MenuLine04 = 0;
	
		if(F_HL_MenuLine04) 
		{
			F_HL_MenuLine04 = 0;
			LCD_TFT_ShowString(M_MenuLine_04,M_MenuColumn_01,&G_LcdBuf[MenuLine04][MenuColumn01],FONT1608,HL_Menu_Point,HL_Menu_Back);
		}
		else 
		{LCD_TFT_ShowString(M_MenuLine_04,M_MenuColumn_01,&G_LcdBuf[MenuLine04][MenuColumn01],FONT1608,Menu_Point,Menu_Back);}
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��05 �˵���"**=============================//
	if(F_Update_MenuLine05)
	{
		F_Update_MenuLine05 = 0;
		
		if(F_HL_MenuLine05) 
		{
			F_HL_MenuLine05 = 0;
			LCD_TFT_ShowString(M_MenuLine_05,M_MenuColumn_01,&G_LcdBuf[MenuLine05][MenuColumn01],FONT1608,HL_Menu_Point,HL_Menu_Back);
		}
		else 
		{LCD_TFT_ShowString(M_MenuLine_05,M_MenuColumn_01,&G_LcdBuf[MenuLine05][MenuColumn01],FONT1608,Menu_Point,Menu_Back);}
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��06 �˵���"**=============================//
	if(F_Update_MenuLine06)
	{
		F_Update_MenuLine06 = 0;
	
		if(F_HL_MenuLine06) 
		{
			F_HL_MenuLine06 = 0;
			LCD_TFT_ShowString(M_MenuLine_06,M_MenuColumn_01,&G_LcdBuf[MenuLine06][MenuColumn01],FONT1608,HL_Menu_Point,HL_Menu_Back);
		}
		else 
		{LCD_TFT_ShowString(M_MenuLine_06,M_MenuColumn_01,&G_LcdBuf[MenuLine06][MenuColumn01],FONT1608,Menu_Point,Menu_Back);}	
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��07 �˵���"**=============================//
	if(F_Update_MenuLine07)
	{
		F_Update_MenuLine07 = 0;
		
		if(F_HL_MenuLine07) 
		{
			F_HL_MenuLine07 = 0;
			LCD_TFT_ShowString(M_MenuLine_07,M_MenuColumn_01,&G_LcdBuf[MenuLine07][MenuColumn01],FONT1608,HL_Menu_Point,HL_Menu_Back);
		}
		else 
		{LCD_TFT_ShowString(M_MenuLine_07,M_MenuColumn_01,&G_LcdBuf[MenuLine07][MenuColumn01],FONT1608,Menu_Point,Menu_Back);}
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��08 �˵���"**=============================//
	if(F_Update_MenuLine08)
	{
		F_Update_MenuLine08 = 0;
	
		if(F_HL_MenuLine08) 
		{
			F_HL_MenuLine08 = 0;
			LCD_TFT_ShowString(M_MenuLine_08,M_MenuColumn_01,&G_LcdBuf[MenuLine08][MenuColumn01],FONT1608,HL_Menu_Point,HL_Menu_Back);
		}
		else 
		{LCD_TFT_ShowString(M_MenuLine_08,M_MenuColumn_01,&G_LcdBuf[MenuLine08][MenuColumn01],FONT1608,Menu_Point,Menu_Back);}	
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��09 �˵���"**=============================//
	if(F_Update_MenuLine09)
	{
		F_Update_MenuLine09 = 0;
	
		if(F_HL_MenuLine09) 
		{
			F_HL_MenuLine09 = 0;
			LCD_TFT_ShowString(M_MenuLine_09,M_MenuColumn_01,&G_LcdBuf[MenuLine09][MenuColumn01],FONT1608,HL_Menu_Point,HL_Menu_Back);
		}
		else 
		{LCD_TFT_ShowString(M_MenuLine_09,M_MenuColumn_01,&G_LcdBuf[MenuLine09][MenuColumn01],FONT1608,Menu_Point,Menu_Back);}	
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��10 �˵���"**=============================//
	if(F_Update_MenuLine10)
	{
		F_Update_MenuLine10 = 0;
	
		if(F_HL_MenuLine10) 
		{
			F_HL_MenuLine10 = 0;
			LCD_TFT_ShowString(M_MenuLine_10,M_MenuColumn_01,&G_LcdBuf[MenuLine10][MenuColumn01],FONT1608,HL_Menu_Point,HL_Menu_Back);
		}
		else 
		{LCD_TFT_ShowString(M_MenuLine_10,M_MenuColumn_01,&G_LcdBuf[MenuLine10][MenuColumn01],FONT1608,Menu_Point,Menu_Back);}
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��11 �˵���"**=============================//
	if(F_Update_MenuLine11)
	{
		F_Update_MenuLine11 = 0;
	
		if(F_HL_MenuLine11) 
		{
			F_HL_MenuLine11 = 0;
			LCD_TFT_ShowString(M_MenuLine_11,M_MenuColumn_01,&G_LcdBuf[MenuLine11][MenuColumn01],FONT1608,HL_Menu_Point,HL_Menu_Back);
		}
		else 
		{LCD_TFT_ShowString(M_MenuLine_11,M_MenuColumn_01,&G_LcdBuf[MenuLine11][MenuColumn01],FONT1608,Menu_Point,Menu_Back);}
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��12 �˵���"**=============================//
	if(F_Update_MenuLine12)
	{
		F_Update_MenuLine12 = 0;
	
		if(F_HL_MenuLine12) 
		{
			F_HL_MenuLine12 = 0;
			LCD_TFT_ShowString(M_MenuLine_12,M_MenuColumn_01,&G_LcdBuf[MenuLine12][MenuColumn01],FONT1608,HL_Menu_Point,HL_Menu_Back);
		}
		else 
		{LCD_TFT_ShowString(M_MenuLine_12,M_MenuColumn_01,&G_LcdBuf[MenuLine12][MenuColumn01],FONT1608,Menu_Point,Menu_Back);}
	}
	

}


/****************************************************************************
*������-Function:	void Update_TestLine_LCD_TFT(void)
*����- Description:		����"������""���ݱ仯"����ʾ����-"����LCD_TFT_ILI9325"  
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) 	��02)    ��03)    ��04)  
*****************************************************************************/
void Update_TestLine_LCD_TFT(void)  //����"������""���ݱ仯"����ʾ����-"����LCD_TFT_ILI9325"  
{
	////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��01 ������"**=============================//
	if(F_Update_TestLine01)
	{
		F_Update_TestLine01 = 0;
	
		if(F_HL_TestLine01) 
		{
			F_HL_TestLine01 = 0;
			LCD_TFT_ShowString(M_TestLine_01,M_TestColumn_01,&G_LcdBuf[TestLine01][TestColumn01],FONT1608,Test_Back,Fixed_Point);
		}
		else 
		{LCD_TFT_ShowString(M_TestLine_01,M_TestColumn_01,&G_LcdBuf[TestLine01][TestColumn01],FONT1608,Fixed_Point,Test_Back);}
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��02 ������"**=============================//
	if(F_Update_TestLine02)
	{
		F_Update_TestLine02 = 0;
	
		if(F_HL_TestLine02) 
		{
			F_HL_TestLine02 = 0;
			LCD_TFT_ShowString(M_TestLine_02,M_TestColumn_01,&G_LcdBuf[TestLine02][TestColumn01],FONT1608,HL_Test_Point,HL_Test_Back);
		}
		else 
		{LCD_TFT_ShowString(M_TestLine_02,M_TestColumn_01,&G_LcdBuf[TestLine02][TestColumn01],FONT1608,Test_Point,Test_Back);}
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��03 ������"**=============================//
	if(F_Update_TestLine03)
	{
		F_Update_TestLine03 = 0;
		
		if(F_HL_TestLine03) 
		{
			F_HL_TestLine03 = 0;
			LCD_TFT_ShowString(M_TestLine_03,M_TestColumn_01,&G_LcdBuf[TestLine03][TestColumn01],FONT1608,HL_Test_Point,HL_Test_Back);
		}
		else 
		{LCD_TFT_ShowString(M_TestLine_03,M_TestColumn_01,&G_LcdBuf[TestLine03][TestColumn01],FONT1608,Test_Point,Test_Back);}
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��04 ������"**=============================//
	if(F_Update_TestLine04)
	{
		F_Update_TestLine04 = 0;
	
		if(F_HL_TestLine04) 
		{
			F_HL_TestLine04 = 0;
			LCD_TFT_ShowString(M_TestLine_04,M_TestColumn_01,&G_LcdBuf[TestLine04][TestColumn01],FONT1608,HL_Test_Point,HL_Test_Back);
		}
		else 
		{LCD_TFT_ShowString(M_TestLine_04,M_TestColumn_01,&G_LcdBuf[TestLine04][TestColumn01],FONT1608,Test_Point,Test_Back);}
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��05 ������"**=============================//
	if(F_Update_TestLine05)
	{
		F_Update_TestLine05 = 0;
	
		if(F_HL_TestLine05) 
		{
			F_HL_TestLine05 = 0;
			LCD_TFT_ShowString(M_TestLine_05,M_TestColumn_01,&G_LcdBuf[TestLine05][TestColumn01],FONT1608,HL_Test_Point,HL_Test_Back);
			
		}
		else 
		{LCD_TFT_ShowString(M_TestLine_05,M_TestColumn_01,&G_LcdBuf[TestLine05][TestColumn01],FONT1608,Test_Point,Test_Back);}
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��06 ������"**=============================//
	if(F_Update_TestLine06)
	{
		F_Update_TestLine06 = 0;
	
		if(F_HL_TestLine06) 
		{
			F_HL_TestLine06 = 0;
			LCD_TFT_ShowString(M_TestLine_06,M_TestColumn_01,&G_LcdBuf[TestLine06][TestColumn01],FONT1608,HL_Test_Point,HL_Test_Back);
		}
		else 
		{LCD_TFT_ShowString(M_TestLine_06,M_TestColumn_01,&G_LcdBuf[TestLine06][TestColumn01],FONT1608,Test_Point,Test_Back);}	
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��07 ������"**=============================//
	if(F_Update_TestLine07)
	{
		F_Update_TestLine07 = 0;
	
		if(F_HL_TestLine07) 
		{
			F_HL_TestLine07 = 0;
			LCD_TFT_ShowString(M_TestLine_07,M_TestColumn_01,&G_LcdBuf[TestLine07][TestColumn01],FONT1608,HL_Test_Point,HL_Test_Back);
		}
		else 
		{LCD_TFT_ShowString(M_TestLine_07,M_TestColumn_01,&G_LcdBuf[TestLine07][TestColumn01],FONT1608,Test_Point,Test_Back);}
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��08 ������"**=============================//
	if(F_Update_TestLine08)
	{
		F_Update_TestLine08 = 0;
	
		if(F_HL_TestLine08) 
		{
			F_HL_TestLine08 = 0;
			LCD_TFT_ShowString(M_TestLine_08,M_TestColumn_01,&G_LcdBuf[TestLine08][TestColumn01],FONT1608,HL_Test_Point,HL_Test_Back);
		}
		else 
		{LCD_TFT_ShowString(M_TestLine_08,M_TestColumn_01,&G_LcdBuf[TestLine08][TestColumn01],FONT1608,Test_Point,Test_Back);}
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��09 ������"**=============================//
	if(F_Update_TestLine09)
	{
		F_Update_TestLine09 = 0;
	
		if(F_HL_TestLine09) 
		{
			F_HL_TestLine09 = 0;
			LCD_TFT_ShowString(M_TestLine_09,M_TestColumn_01,&G_LcdBuf[TestLine09][TestColumn01],FONT1608,HL_Test_Point,HL_Test_Back);
		}
		else 
		{LCD_TFT_ShowString(M_TestLine_09,M_TestColumn_01,&G_LcdBuf[TestLine09][TestColumn01],FONT1608,Test_Point,Test_Back);}
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��10 ������"**=============================//
	if(F_Update_TestLine10)
	{
		F_Update_TestLine10 = 0;
	
		if(F_HL_TestLine10) 
		{
			F_HL_TestLine10 = 0;
			LCD_TFT_ShowString(M_TestLine_10,M_TestColumn_01,&G_LcdBuf[TestLine10][TestColumn01],FONT1608,HL_Test_Point,HL_Test_Back);
		}
		else 
		{LCD_TFT_ShowString(M_TestLine_10,M_TestColumn_01,&G_LcdBuf[TestLine10][TestColumn01],FONT1608,Test_Point,Test_Back);}
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��11 ������"**=============================//
	if(F_Update_TestLine11)
	{
		F_Update_TestLine11 = 0;
	
		if(F_HL_TestLine11) 
		{
			F_HL_TestLine11 = 0;
			LCD_TFT_ShowString(M_TestLine_11,M_TestColumn_01,&G_LcdBuf[TestLine11][TestColumn01],FONT1608,HL_Test_Point,HL_Test_Back);
		}
		else 
		{LCD_TFT_ShowString(M_TestLine_11,M_TestColumn_01,&G_LcdBuf[TestLine11][TestColumn01],FONT1608,Test_Point,Test_Back);}
	}
	
	////////////////////////////////////////////////////////////////////////////
	//==**ˢ��: ��ʾ"��12 ������"**=============================//
	if(F_Update_TestLine12)
	{
		F_Update_TestLine12 = 0;
	
		if(F_HL_TestLine12) 
		{
			F_HL_TestLine12 = 0;
			LCD_TFT_ShowString(M_TestLine_12,M_TestColumn_01,&G_LcdBuf[TestLine12][TestColumn01],FONT1608,HL_Test_Point,HL_Test_Back);
		}
		else 
		{LCD_TFT_ShowString(M_TestLine_12,M_TestColumn_01,&G_LcdBuf[TestLine12][TestColumn01],FONT1608,Test_Point,Test_Back);}
	}

}



/****************************************************************************
*������-Function:	void Blink_KeyPlace_Lcd_TFT(unsigned char line,unsigned char column,unsigned char *Array,unsigned char Num)
*����- Description:	��˸��ʾ"����λ��(����ֵ)"--"����LCD_TFT" 
*�������-Input:	
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Blink_KeyPlace_Lcd_TFT(unsigned char line,unsigned char column,unsigned char *Array,unsigned char Num) //��˸��ʾ"����λ��(����ֵ)"--"����LCD_TFT" 
{
	if(F_250ms_Blink_Key_LCD_TFT)
	{
		F_250ms_Blink_Key_LCD_TFT = 0;

		if(F_250ms_Turn)	//��˸"���ڲ���"�Ĳ˵�
		{
				//��ʾ:��line�У�column��Array�����е�Num���ַ�
			Copy_Array_AtoB(&G_LcdBuf[line][column], Array, Num);
		}
		else 
		{		
				// ���:��line�У�column�п�ʼ��Num���ַ�
			Copy_Array_AtoB(&G_LcdBuf[line][column], Msg_ClearLine_LCD_TFT, Num);
		}
		
	//	G_LCD_TFT_Buf[line][column+Num] = '\0';
			
	////////////////////////////////////////////////////////////////////////////
	//==**ʹ����Ӧ��Һ����ʾ��**=================================================//

		switch(line) 
		{
			case TestLine01:	
				F_Update_TestLine01 = YES;//ˢ��:"01������"
				break;	

			case TestLine02:	
				F_Update_TestLine02 = YES;//ˢ��:"02������"
				break;	
				
			case TestLine03:	
				F_Update_TestLine03 = YES;//ˢ��:"03������"
				break;		

			case TestLine04:	
				F_Update_TestLine04 = YES;//ˢ��:"04������"
				break;	
				
			case TestLine05:	
				F_Update_TestLine05 = YES;//ˢ��:"05������"
				break;	
				
			case TestLine06:	
				F_Update_TestLine06 = YES;//ˢ��:"06������"
				break;	

			case TestLine07:	
				F_Update_TestLine07 = YES;//ˢ��:"07������"
				break;		
				
			case TestLine08:	
				F_Update_TestLine08 = YES;//ˢ��:"08������"
				break;
				
			case TestLine09:	
				F_Update_TestLine09 = YES;//ˢ��:"09������"
				break;	
			
			case TestLine10:	
				F_Update_TestLine10 = YES;//ˢ��:"10������"
				break;	
						
			case TestLine11:	
				F_Update_TestLine11 = YES;//ˢ��:"11������"
				break;	
							
			case TestLine12:	
				F_Update_TestLine12 = YES;//ˢ��:"12������"
				break;	

	////////////////////////////////////////////////////////////////////////////
			default: 
				break;
		}	
	}

	
}







///*****************************************
// �������ܣ���TFTĳһ�����ɫ
// ���ڲ�����color  ����ɫֵ
//******************************************/
//unsigned int LCD_TFT_ReadPoint(u16 x,u16 y)
//{
//  unsigned int Data;
//  LCD_TFT_SetCursor(x,y);
//
//  //LCD_TFT_ReadData();//���������ֽ�
//  //Data=Lcd_ReadData();
//  ILI9325_WriteData(Data);
//  return Data;
//}
//






/********************************************
//��ָ��λ�� ��ʾ1��48*48�ĺ���
//(x,y):������ʾ��λ��
//index:tfont��������ĵڼ�������
//color:������ֵ���ɫ
void Test_Show_CH_Font48(u16 x,u16 y,u8 index,u16 color,u16 BackColor)
{
        LCD_SELECT();
        BACK_COLOR=BackColor;
	u16 temp,t,t1;
	u16 y0=y; 
	for(t=0;t<288;t++)//ÿ��48*48�ĺ��ֵ��� ��288���ֽ�
		{
		//��ά����ÿһά���72�ֽ�
//		if(0<t<72)
		//temp=tfont48[index*4][t];           //ǰ72���ֽ�
//		else if(72<= t < 144)temp=tfont48[index*4][t-72]; //72���ֽ�
//		else if (144 <= t<216)temp=tfont48[index*4][t-144];         //72���ֽ�
//		else if(216 <= t<288)temp=tfont48[index*4][t-216]; //72���ֽ�
		for(t1=0;t1<8;t1++)	 //ÿ���ֽ�8λ����
			{
			if(temp&0x80)LCD_DrawPoint(x,y,color);//��ʵ�ĵ�
			else LCD_DrawPoint(x,y,WHITE);   //���հ׵㣨ʹ�ñ���ɫ��
			temp<<=1;
			y++;	   //����
			if((y-y0)==48)	  //�ﵽ��������ֵ��ʼ�µ�һ��
				{
				y=y0;
				x++;
				break;
				}
			}
		}
}



//��ָ��λ�� ��ʾ1��16*16�ĺ���
//(x,y):������ʾ��λ��
//index:tfont��������ĵڼ�������
//color:������ֵ���ɫ
void Test_Show_CH_Font16(u16 x,u16 y,u8 index,u16 color,u16 BackColor)
{
	u8 temp,t,t1;
	u16 y0=y;
	
	for(t=0;t<32;t++)//ÿ��16*16�ĺ��ֵ��� ��32���ֽ�(8+8)*2
	{
			//��ά����ÿһά���16�ֽ�
		if(t<16) temp=tfont16[index*2][t];     //ǰ16���ֽ�
		else temp=tfont16[index*2+1][t-16];    //��16���ֽ�

		for(t1=0;t1<8;t1++)	 //ÿ���ֽ�8λ����
		{
			if(temp&0x80) LCD_DrawPoint(x,y,color);//��ʵ�ĵ�
			else LCD_DrawPoint(x,y,BackColor);     //���հ׵㣨ʹ�ñ���ɫ��

			temp<<=1;
			y++;

			if((y-y0)==16)	 //�ﵽ��������ֵ��ʼ�µ�һ��
			{
				y=y0;
				x++;
				break;
			}
		}
	}
}
****************************************************/


