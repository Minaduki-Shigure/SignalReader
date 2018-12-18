/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 LCD_Segment.c
* �����ļ�-Dependencies:  	 LCD_Segment.h; Hardware_Profile.h;  Generic.h;
* �ļ�����-File Description:	 ( Դ����-Source File) 
	��"��ʽLCD_Segment" -��������(�ⲿ��Դ)
	01) 
	//LCDMEM[0] = dp;  //��Ӧ"������"��"��ط���"+"��6���ַ�"(���ұ߿�ʼ��)
	//LCDMEM[1] = dp;  //��Ӧ"�м�"��"��ط���"+"��5���ַ�"(���ұ߿�ʼ��)
	//LCDMEM[2] = dp;  //��Ӧ"������"��"��ط���"+"��ؿ�ͼ"+"��4���ַ�"(���ұ߿�ʼ��)
	//LCDMEM[3] = dp;  //��Ӧ"�����"��"С����"+"��3���ַ�"(���ұ߿�ʼ��)
	//LCDMEM[4] = dp;  //��Ӧ"�м�"��"С����"+"��2���ַ�"(���ұ߿�ʼ��)
	//LCDMEM[5] = dp;  //��Ӧ"���ұ�"��"С����"+"��1���ַ�"(���ұ߿�ʼ��)
	02)     03)    04)    05)    06)	
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



#include "Generic.h"	//���ó����̹淶�������� -ͷ�ļ�-Generic Type Definitions

#include "Hardware_Profile.h"  //������"Ӳ�������ļ�" -Hardware specific definitions for Processor


#include "LCD_Segment.h" // "��ʽLCD_Segment"  -��������(�ⲿ��Դ)-ͷ�ļ�



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//--**"��ʽLCD_Segment" *ȫ�ֱ�־λ**------------------------------//
union FLAGBIT16 LCD_Seg_FlagBits; //"LCD_Segment"��ر�־λ����


unsigned char G_Mode_LCD_Segment = 0; //"LCD_Segment" ����ģʽ
unsigned char G_Last_Mode_LCD_Segment = 0; //������һ��"����ģʽ"



unsigned char G_LcdSeg_Cnt = 0; //"��ʽLCD_Segment"���õ��ļ�����(�����ַ�ѭ����ʾ)

unsigned char G_LcdSegBuf[7]; //"��ʽLCD_Segment"��ʾ��������//G_LcdSegBuf[0]��Ӧ��"�ұ�"����ʾ�ַ�


////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////
	//"��ʽLCD_Segment" ��ʾ���
const unsigned char LcdSeg_Tab[] = { // As used in 430 Day Watch Demo board
		aa+bb+cc+dd+ee+ff,         //LcdSeg_Tab[0] // Displays "0"
		bb+cc,                     //LcdSeg_Tab[1]  // Displays "1"
		aa+bb+dd+ee+gg,            //LcdSeg_Tab[2]  // Displays "2"
		aa+bb+cc+dd+gg,            //LcdSeg_Tab[3]  // Displays "3"
		bb+cc+ff+gg,               //LcdSeg_Tab[4]  // Displays "4"
		aa+cc+dd+ff+gg,            //LcdSeg_Tab[5]  // Displays "5"
		aa+cc+dd+ee+ff+gg,         //LcdSeg_Tab[6]  // Displays "6"
		aa+bb+cc,                  //LcdSeg_Tab[7]  // Displays "7"
		aa+bb+cc+dd+ee+ff+gg,      //LcdSeg_Tab[8]  // Displays "8"
		aa+bb+cc+dd+ff+gg,         //LcdSeg_Tab[9]  // Displays "9"
		aa+bb+cc+ee+ff+gg,         //LcdSeg_Tab[10]  // Displays "A"
		cc+dd+ee+ff+gg,            //LcdSeg_Tab[11]  // Displays "b"
		aa+dd+ee+ff,               //LcdSeg_Tab[12] // Displays "C"
		bb+cc+dd+ee+gg,            //LcdSeg_Tab[13] // Displays "d"
		aa+dd+ee+ff+gg,            //LcdSeg_Tab[14] // Displays "E"
		aa+ee+ff+gg,               //LcdSeg_Tab[15] // Displays "F"
		dp, 					   //LcdSeg_Tab[16] // Displays "."(С����)
		ff+gg,					   //LcdSeg_Tab[17] // Displays "+"(�Ӻ�,����)	
		gg, 					   //LcdSeg_Tab[18] // Displays "-"(����,����)
		dd+gg,					   //LcdSeg_Tab[19] // Displays "="(���ں�)
		aa+bb+cc+dd+ee+ff+gg+dp,   //LcdSeg_Tab[20] // Displays "full"
		0                          //LcdSeg_Tab[21] // Displays "����"
};



/****************************************************************************
*������-Function:	void EnModule_LCD_Segment(unsigned char EnBit)
*����- Description:	�򿪻��߹ر�Һ��LCD_B ģ��
*�������-Input:	EnBit=YES(1): ��LCD_Bģ�飻EnBit=N)(0): �ر�LCD_Bģ�飻
*�������-output:	None
*ע������-Note��	
	��01) LCDON ģ����ʹ��λ-LCD on. This bit turns the LCD_B module on or off.    
	��02)    ��03)    ��04)  
*****************************************************************************/
void EnModule_LCD_Segment(unsigned char EnBit) //�򿪻��߹ر�Һ��LCD_B ģ��
{
	if(EnBit == YES)
	{
		//��Һ��LCD_B ģ��
		LCDBCTL0 |= LCDON;
	}
	else if(EnBit == NO)
	{
		//�ر�Һ��LCD_B ģ��
		LCDBCTL0 &= ~LCDON;
	}
}



/****************************************************************************
*������-Function:	void EnAllSeg_LCD_Segment(unsigned char EnBit)
*����- Description:	ʹ�ܻ��ֹ����LCD_B��(��������Һ����(����)����˸)
*�������-Input:	EnBit=YES(1): ʹ������LCD_B�ε���ʾ; EnBit=N)(0): ��ֹ����LCD_B�ε���ʾ;
*�������-output:	None
*ע������-Note��	
	��01) LCDSON ����Һ����ʹ��λ-  This bit supports flashing LCD applications by turning off all segment lines, while leaving the LCD timing generator and R33 enabled.
			//0b = All LCD segments are off.
			//1b = All LCD segments are enabled and on or off according to their corresponding memory location.
	��02)    ��03)    ��04)  
*****************************************************************************/
void EnAllSeg_LCD_Segment(unsigned char EnBit) //ʹ�ܻ��ֹ����LCD_B��(��������Һ����(����)����˸)
{
	if(EnBit == NO)
	{
		LCDBCTL0 &= ~LCDSON;
	}
	else if(EnBit == YES)
	{
		LCDBCTL0 |= LCDSON;
	}
}


/****************************************************************************
*������-Function:	void Clear_LCD_Segment(void)
*����- Description:	����: ����������ڲ���"��ʽLCD ��ʾ����"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) //LCDMEM[]  //Ϊ�������ڲ���"��ʽLCD ��ʾ����"
	��02)    ��03)    ��04)  
*****************************************************************************/
void Clear_LCD_Segment(void)  //����: ����������ڲ���"��ʽLCD ��ʾ����"
{
     unsigned char i = 0;
     for(i = 0; i < 6; i++) //6��LCD���ַ�
     {
    	 LCDMEM[i] = 0;  //0 : ��ʾ��ʾΪ"����"
     }
}




/****************************************************************************
*������-Function:	void Open_LCD_Segment(void)
*����- Description:	��LCD_Segment (��ʹ��): LCD_Segment �ڲ��Ĵ�������; �˿ڳ�ʼ����
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Open_LCD_Segment(void) //��LCD_Segment (��ʹ��): LCD_Segment �ڲ��Ĵ�������; �˿ڳ�ʼ����
{
////////////////////////////////////////////////////////////////////////////
//==**��ʽLCD_Segment�������**===========================//

	mOpen_LCD_SEG_BackLight; //��������Ϊ"���",��"��"LCD_Segment ����

////////////////////////////////////////////////////////////////////////////
//==**"LCD_B ���ƼĴ���"�������(MCUģ��Ĵ���)**=======//
//--care--�� "LCDON ģ����ʹ��λ=0"ʱ����������LCDBCTL0

	EnModule_LCD_Segment(NO);  //�ر�Һ��LCD_B ģ��//֮���������LCDBCTL0	
	LCDBCTL0 =LCDDIV0 + LCDPRE0 +  LCDMX1 + LCDSSEL + LCDMX1 + LCD4MUX ;


////////////////////////////////////////////////////////////////////////////
//==**LCD_Bģ���ʼ��:�˿ڳ�ʼ��������LCD_B����(LCD_Segment )**===========================//

//	LCD_B_Initial_LCD_Segment(); //LCD_Bģ���ʼ��:�˿ڳ�ʼ��������LCD_B����(LCD_Segment )


}


/****************************************************************************
*������-Function:	void Close_LCD_Segment(void)
*����- Description:		�ر�"��ʽLCD_Segment"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Close_LCD_Segment(void) //�ر�"��ʽLCD_Segment"
{
////////////////////////////////////////////////////////////////////////////
//==**��ʽLCD_Segment�������**===========================//
	mClose_LCD_SEG_BackLight;//��������Ϊ"���",��"�ر�"LCD_Segment ���� 

////////////////////////////////////////////////////////////////////////////
//==**����������ڲ���"��ʽLCD ��ʾ����"**============//
	Clear_LCD_Segment(); //����: ����������ڲ���"��ʽLCD ��ʾ����"

////////////////////////////////////////////////////////////////////////////
//==**"LCD_B ���ƼĴ���"�������(MCUģ��Ĵ���)**=======//
	EnAllSeg_LCD_Segment(NO); //��ֹ����LCD_B��(��������Һ����(����)����˸)
	EnModule_LCD_Segment(NO); //�ر�Һ��LCD_B ģ��

	//--care--һ��Ҫ����������//"LCD_B �˿ڿ��ƼĴ���"�������
	LCDBPCTL0 = 0;
	mSelect_LCD_SEG_IoPin;//��������Ϊ"IO"����
	mSetIn_LCD_SEG_COM;  //�������Ŷ�Ϊ"����"

}



/****************************************************************************
*������-Function:	void Initial_LCD_Segment_LCD_B(void)
*����- Description:	LCD_Bģ���ʼ��:�˿ڳ�ʼ��������LCD_B����(LCD_Segment )
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Initial_LCD_Segment_LCD_B(void) //LCD_Bģ���ʼ��:�˿ڳ�ʼ��������LCD_B����(LCD_Segment )
{
	mSPI_All_Disable;//����LCD_segment��IIC(TMP006)ʱ��Ҫ���������õ�SPI_B��ģ��




////////////////////////////////////////////////////////////////////////////
//==**��������Ϊ"��Χģ�鹦��"����**=================//

	mSelect_LCD_SEG_FunctionPin;//P5.5, P5.4, P5.3 ����LCD_B��������(��������Ϊ"��Χģ�鹦��"���� )
	mSetOut_LCD_SEG_COM;  //�������Ŷ�Ϊ"���"


////////////////////////////////////////////////////////////////////////////
//==**"LCD_B �˿ڿ��ƼĴ���"�������(MCUģ��Ĵ���)**==//
		//--care--һ��Ҫ����������//"LCD_B �˿ڿ��ƼĴ���"�������
	LCDBPCTL0 = LCDS0 + LCDS1 + LCDS2 + LCDS3 + LCDS4 + LCDS5 + LCDS6+ LCDS7 + LCDS8 \
				+ LCDS9 + LCDS10+ LCDS11;

////////////////////////////////////////////////////////////////////////////
//==**��ʽLCD_Segment ��ʼ״̬����**=====================//
	
	EnAllSeg_LCD_Segment(YES); //ʹ������LCD_B��(��������Һ����(����)����˸)
		
	EnModule_LCD_Segment(YES);  //��Һ��LCD_B ģ��	

////////////////////////////////////////////////////////////////////////////
//==**���ö�·������TS3A5017: ѡ��"LCD_Bģ��"**===========//
//--care--��·��������ѡ��һ��Ҫ������ǰ��
//--care--�����л���LCD_B, �ٳ�ʼ��LCD_B
//--care--���л���SPI_B (LCD_TFT) �����෴
		//IN2=1; IN1=0; ��ӦSEG9; SEG10; SEG11; ����

//	mHigh_LCD_TFT_CS; //��������Ϊ"���",��"����ߵ�ƽ"
//mDelay_Cycles(3000);

	mConfig_TS3A5017_B_IN2(1);  //IN2 = 1
	mConfig_TS3A5017_B_IN1(0);  //IN1 = 0

	
}


/****************************************************************************
*������-Function:	void Refresh_LCD_Segment(unsigned char pointNum,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1)
*����- Description:	������ʾ(��ʽLCD_Segment)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Refresh_LCD_Segment(unsigned char pointNum,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1) //������ʾ(��ʽLCD_Segment)
{
	Initial_LCD_Segment_LCD_B(); //LCD_Bģ���ʼ��:�˿ڳ�ʼ��������LCD_B����(LCD_Segment )

////////////////////////////////////////////////////////////////////////////
//==**ˢ����ʾ(��ʽLCD_Segment)**=========================//

	if(pointNum == 1) LCDMEM[5] = LcdSeg_Tab[NO_1] | dp; //ˢ�µ�"1"���ַ�(���ұ�����) (��ʽLCD_Segment)
	else LCDMEM[5] = LcdSeg_Tab[NO_1];//ˢ�µ�"1"���ַ�(���ұ�����) (��ʽLCD_Segment)

	if(pointNum == 2) LCDMEM[4] = LcdSeg_Tab[NO_2] | dp; //ˢ�µ�"2"���ַ�(���ұ�����) (��ʽLCD_Segment)
	else LCDMEM[4] = LcdSeg_Tab[NO_2];//ˢ�µ�"2"���ַ�(���ұ�����) (��ʽLCD_Segment)

	if(pointNum == 3) LCDMEM[3] = LcdSeg_Tab[NO_3] | dp; //ˢ�µ�"3"���ַ�(���ұ�����) (��ʽLCD_Segment)
	else LCDMEM[3] = LcdSeg_Tab[NO_3];//ˢ�µ�"3"���ַ�(���ұ�����) (��ʽLCD_Segment)

	if(pointNum == 4) LCDMEM[2] = LcdSeg_Tab[NO_4] | dp;//ˢ�µ�"4"���ַ�(���ұ�����) (��ʽLCD_Segment)	 
	else LCDMEM[2] = LcdSeg_Tab[NO_4];//ˢ�µ�"4"���ַ�(���ұ�����) (��ʽLCD_Segment)

	if(pointNum == 5)
	{
		LCDMEM[2] = LCDMEM[2] | dp;  //��ʾ"��ؿ�"+��͵���
		LCDMEM[1] = LcdSeg_Tab[NO_5] | dp;//ˢ�µ�"5"���ַ�(���ұ�����) (��ʽLCD_Segment)
	}
	else LCDMEM[1] = LcdSeg_Tab[NO_5];//ˢ�µ�"5"���ַ�(���ұ�����) (��ʽLCD_Segment)

	if(pointNum == 6)
	{
		LCDMEM[2] = LCDMEM[2] | dp;  //��ʾ"��ؿ�"+��͵���
		LCDMEM[1] = LCDMEM[1] | dp;  //��ʾ"��ؿ�"+�м����
		LCDMEM[0] = LcdSeg_Tab[NO_6] | dp;//ˢ�µ�"6"���ַ�(���ұ�����) (��ʽLCD_Segment)
	}
	else LCDMEM[0] = LcdSeg_Tab[NO_6];//ˢ�µ�"6"���ַ�(���ұ�����) (��ʽLCD_Segment)

}



/****************************************************************************
*������-Function:	void Init_Mode_LCD_Segment(void)
*����- Description:	��ʹ��"����ģʽ"(��ʽLCD_Segment)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Init_Mode_LCD_Segment(unsigned char Mode) //��ʹ��"����ģʽ"(��ʽLCD_Segment)
{
	G_Last_Mode_LCD_Segment = G_Mode_LCD_Segment;//����"��һ��"��"����ģʽ"

	G_Mode_LCD_Segment = Mode;


	
			/*************************************************
			switch(Data) 
			{
			////////////////////////////////////////////////////////////////////////////
			//==** **=================================================//
				case :	
					break;	
			////////////////////////////////////////////////////////////////////////////
				default:	break;
			}
			*************************************************/

}


/****************************************************************************
*������-Function:	void Deal_LCD_Segment(void)
*����- Description:	"��ʽLCD_Segment": ����ͬ"����ģʽ"
*�������-Input:	None
*�������-output:	None
*ע������-Note��
	��01)
	//LCDMEM[0] = dp;  //��Ӧ"������"��"��ط���"+"��6���ַ�"(���ұ߿�ʼ��)
	//LCDMEM[1] = dp;  //��Ӧ"�м�"��"��ط���"+"��5���ַ�"(���ұ߿�ʼ��)
	//LCDMEM[2] = dp;  //��Ӧ"������"��"��ط���"+"��ؿ�ͼ"+"��4���ַ�"(���ұ߿�ʼ��)
	//LCDMEM[3] = dp;  //��Ӧ"�����"��"С����"+"��3���ַ�"(���ұ߿�ʼ��)
	//LCDMEM[4] = dp;  //��Ӧ"�м�"��"С����"+"��2���ַ�"(���ұ߿�ʼ��)
	//LCDMEM[5] = dp;  //��Ӧ"���ұ�"��"С����"+"��1���ַ�"(���ұ߿�ʼ��)
	��02) 	  ��03)   	��04)  
*****************************************************************************/
void Deal_LCD_Segment(void) //"��ʽLCD_Segment": ����ͬ"����ģʽ"
{
	

	switch(G_Mode_LCD_Segment) 
	{
////////////////////////////////////////////////////////////////////////////
//==** **=================================================//
case MODE_Idle_LCD_Segment:	//Mode������(�����κβ���)(��ʽLCD_Segment)
	
	break;	

case MODE_Open_LCD_Segment:	//Mode��"��"��ģ��(��ʽLCD_Segment)
	Open_LCD_Segment(); 	//��LCD_Segment (��ʹ��): LCD_Segment �ڲ��Ĵ�������; �˿ڳ�ʼ����

		//ִ��һ������󣬻ص�//Mode��������ʾ(��ʽLCD_Segment)
	G_Mode_LCD_Segment = MODE_Refresh_LCD_Segment; 
	break;	

case MODE_Close_LCD_Segment: //Mode��"�ر�"��ģ��(��ʽLCD_Segment)
	Close_LCD_Segment();  //�ر�"��ʽLCD_Segment"

		//care//ִֻ��һ���������󣬻ص�����ģʽ
	G_Mode_LCD_Segment = MODE_Idle_LCD_Segment; 
	break;	

case MODE_Refresh_LCD_Segment: //Mode��������ʾ(��ʽLCD_Segment)
		//������ʾ(��ʽLCD_Segment)
	Refresh_LCD_Segment(G_LcdSegBuf[6],G_LcdSegBuf[5],G_LcdSegBuf[4],G_LcdSegBuf[3],G_LcdSegBuf[2],G_LcdSegBuf[1],G_LcdSegBuf[0]);  

	//care  //���ﲻ��ת��"MODE_Idle_LCD_Segment",��ϵͳÿ��ѭ����ˢ���������߿���������
	break;	

case MODE_OpenBackLight_LCD_Segment: //Mode��"��"����(��ʽLCD_Segment)	

	mOpen_LCD_SEG_BackLight; //��������Ϊ"���",��"��"LCD_Segment ����

		//�����һ��Ϊ"Mode��������ʾ",����Mode��������ʾ
	if(G_Last_Mode_LCD_Segment == MODE_Refresh_LCD_Segment)
	{
			//ִ��һ������󣬻ص�//Mode��������ʾ(��ʽLCD_Segment)
		G_Mode_LCD_Segment = MODE_Refresh_LCD_Segment; 
	}
			//�����һ��Ϊ"Mode��"�ر�"��ģ��",����Mode������
	else if(G_Last_Mode_LCD_Segment == MODE_Close_LCD_Segment)
	{
			//ִ��һ������󣬻ص�//Mode������(�����κβ���)(��ʽLCD_Segment)
		G_Mode_LCD_Segment = MODE_Idle_LCD_Segment; 
	}
	break;	


case MODE_CloseBackLight_LCD_Segment: //Mode��"�ر�"����(��ʽLCD_Segment)	

	mClose_LCD_SEG_BackLight;//��������Ϊ"���",��"�ر�"LCD_Segment ���� 

		//�����һ��Ϊ"Mode��������ʾ",����Mode��������ʾ
	if(G_Last_Mode_LCD_Segment == MODE_Refresh_LCD_Segment)
	{
			//ִ��һ������󣬻ص�//Mode��������ʾ(��ʽLCD_Segment)
		G_Mode_LCD_Segment = MODE_Refresh_LCD_Segment; 
	}
			//�����һ��Ϊ"Mode��"�ر�"��ģ��",����Mode������
	else if(G_Last_Mode_LCD_Segment == MODE_Close_LCD_Segment)
	{
			//ִ��һ������󣬻ص�//Mode������(�����κβ���)(��ʽLCD_Segment)
		G_Mode_LCD_Segment = MODE_Idle_LCD_Segment; 
	}
	break;	

			


////////////////////////////////////////////////////////////////////////////
//==** **=================================================//

	
////////////////////////////////////////////////////////////////////////////
default:
	break;
	}

}


/****************************************************************************
*������-Function:	void Disp_LCD_Segment(unsigned char pointNum,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1)
*����- Description:	"��ʾ�ַ�"���µ�"��ʾ��������"(��ʽLCD_Segment)
*�������-Input:	pointNum:С�����λ��; NO_8~NO_1:�����ҵĶ�ʽLCD_Segment ��ʾֵ
*�������-output:	None
*ע������-Note��
	��01)    
	//G_LcdSegBuf[0];  //��Ӧ"��1���ַ�"+"���ұ�"��"С����"(���ұ߿�ʼ��)
	//G_LcdSegBuf[1];  //��Ӧ"��2���ַ�"+"�м�"��"С����"(���ұ߿�ʼ��)
	//G_LcdSegBuf[2];  //��Ӧ"��3���ַ�"+"�����"��"С����"(���ұ߿�ʼ��)
	//G_LcdSegBuf[3];  //��Ӧ"��4���ַ�"+"������"��"��ط���"+"��ؿ�ͼ"(���ұ߿�ʼ��)
	//G_LcdSegBuf[4];  //��Ӧ"��5���ַ�"+"�м�"��"��ط���"(���ұ߿�ʼ��)
	//G_LcdSegBuf[5];  //��Ӧ"��6���ַ�"+"������"��"��ط���"(���ұ߿�ʼ��)
	��02) �� Disp_LCD_Segment(2,6,5,4,3,2,1); //��ʽ���ҵ�����ʾͼΪ"6543.21"
	��03)    ��04)  
*****************************************************************************/
void Disp_LCD_Segment(unsigned char pointNum,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1)
{
	G_LcdSegBuf[0] = NO_1;//��Ӧ"��1���ַ�"+"���ұ�"��"С����"(���ұ߿�ʼ��)
	G_LcdSegBuf[1] = NO_2;
	G_LcdSegBuf[2] = NO_3;
	G_LcdSegBuf[3] = NO_4;
	G_LcdSegBuf[4] = NO_5;
	G_LcdSegBuf[5] = NO_6;
	G_LcdSegBuf[6] = pointNum;
}



