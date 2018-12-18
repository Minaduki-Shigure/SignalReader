/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 LED_Segment.c
* �����ļ�-Dependencies:  	 LED_Segment.h; TM1638.h;  Hardware_Profile.h;  Generic.h;
* �ļ�����-File Description:	 ( Դ����-Source File) 
	��"��̬�����LED_Segment" -��������(�ⲿ��Դ)
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


#include "TM1638.h"  // "TM1638 �����������" -��������(�ⲿ��Դ) -ͷ�ļ�

#include "LED_Segment.h" //"��̬�����LED_Segment" -��������(�ⲿ��Դ)-ͷ�ļ�



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//--**"��̬�����LED_Segment" *ȫ�ֱ�־λ**------------------------------//
union FLAGBIT16 LED_Seg_FlagBits; //"��̬�����LED_Segment" ��ر�־λ����

unsigned char G_Mode_LED_Segment = 0; //"��̬�����LED_Segment" ����ģʽ
unsigned char G_Last_Mode_LED_Segment = 0; //������һ��"����ģʽ"


unsigned char G_LedSeg_Cnt = 0; //"��̬�����LED_Segment" ���õ��ļ�����(�����ַ�ѭ����ʾ)
unsigned char G_LedSegBuf[10]; //"��̬�����LED_Segment" ��ʾ��������//G_LedSegBuf[0]��Ӧ��"�ұ�"����ʾ�ַ�


unsigned char G_Brightness_LedSeg = 0;  //���ȵ���-"��̬�����LED_Segment" 
	//���ȱ���-"��̬�����LED_Segment"
unsigned char G_BrightnessKind = M_Brightness_1_LedSeg;   //Ĭ��:����Ϊ1(�)--"��̬�����LED_Segment" 

    

////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////





/****************************************************************************
*������-Function:	void Open_LED_Segment(void)
*����- Description:	��ʹ��: ��ʾ"��"+�Զ�"PWMΪ1/16" (�)("��̬�����LED_Segment" )
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Open_LED_Segment(void)  //��ʹ��: ��ʾ"��"+�Զ�"PWMΪ1/16" (�)("��̬�����LED_Segment" )
{
////////////////////////////////////////////////////////////////////////////
//==**"��̬�����LED_Segment" �Զȿ���**==================//
			//����Ϊ1(��)--"��̬�����LED_Segment" 
//blues// G_Brightness_LedSeg = M_Brightness_1_LedSeg;	
	Open_Display_TM1638(); //����ʾ(��ʼ��):��ʾ"��"+�Զ�"PWMΪ1/16" (�)(TM1638)

}

/****************************************************************************
*������-Function:	void Close_LED_Segment(void)
*����- Description:	�ر�LED_Segment ģ��("��̬�����LED_Segment" )
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Close_LED_Segment(void) //�ر�LED_Segment ģ��("��̬�����LED_Segment" )
{
////////////////////////////////////////////////////////////////////////////
//==**"��̬�����LED_Segment" �Զȿ���**==================//
		//����Ϊ0 (��ʾ��)--"��̬�����LED_Segment" 
	//G_Brightness_LedSeg = M_Brightness_OFF_LedSeg;
		//����ʾ��������
	Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);

	Close_Display_TM1638();//������ʾģʽ:��ʾ��(TM1638)
}




/****************************************************************************
*������-Function:	void Deal_Brightness_LED_Segment(void)
*����- Description:	���������"�Զ�(����)"("��̬�����LED_Segment" )
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Deal_Brightness_LED_Segment(void) //���������"�Զ�(����)"
{
		//����"��̬�����LED_Segment" :��ʾ�أ���ʾ��������"�Զ�PWM"(TM1638)
	Deal_Brightness_TM1638(G_Brightness_LedSeg); 
}




/****************************************************************************
*������-Function:	void Refresh_LED_Segment(void)
*����- Description:	������ʾ("��̬�����LED_Segment" )
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01)  
	//G_LedSegBuf[0];  //��Ӧ"��1��"��ʾ�ַ�(�����)
	//G_LedSegBuf[1];  //��Ӧ"��2��"��ʾ�ַ�(�����)
	//G_LedSegBuf[2];  //��Ӧ"��3��"��ʾ�ַ�(�����)
	//G_LedSegBuf[3];  //��Ӧ"��4��"��ʾ�ַ�(�����)
	//G_LedSegBuf[4];  //��Ӧ"��5��"��ʾ�ַ�(�����)
	//G_LedSegBuf[5];  //��Ӧ"��6��"��ʾ�ַ�(�����)
	//G_LedSegBuf[6];  //��Ӧ"��7��"��ʾ�ַ�(�����)
	//G_LedSegBuf[7];  //��Ӧ"��8��"��ʾ�ַ�(�����)
	//G_LedSegBuf[8];  //��Ӧ"��1��С����"��ʾ�ַ�(�����)
	//G_LedSegBuf[9];  //��Ӧ"��2��С����"��ʾ�ַ�(�����)

	��02)    ��03)    ��04)  
*****************************************************************************/
void Refresh_LED_Segment(void) //������ʾ("��̬�����LED_Segment" )
{
////////////////////////////////////////////////////////////////////////////
//==**ˢ����ʾ("��̬�����LED_Segment" )**=================//
		//��TM1638��ʾ��ַдҪ"��ʾ������"(TM1638)
	Write_DispData_TM1638(G_LedSegBuf[9],G_LedSegBuf[8],G_LedSegBuf[7],G_LedSegBuf[6],G_LedSegBuf[5],G_LedSegBuf[4],G_LedSegBuf[3],G_LedSegBuf[2],G_LedSegBuf[1],G_LedSegBuf[0]);
}





/****************************************************************************
*������-Function:	void Init_Mode_LED_Segment(void)
*����- Description:	��ʹ��"����ģʽ"("��̬�����LED_Segment" )
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Init_Mode_LED_Segment(unsigned char Mode) //��ʹ��"����ģʽ"("��̬�����LED_Segment" )
{
	G_Last_Mode_LED_Segment = G_Mode_LED_Segment;//����"��һ��"��"����ģʽ"

	G_Mode_LED_Segment = Mode;


	
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
*������-Function:	void Deal_LED_Segment(void)
*����- Description:	"��̬�����LED_Segment" : ����ͬ"����ģʽ"
*�������-Input:	None
*�������-output:	None
*ע������-Note��
	��01)   	��02) 	  ��03)   	��04)  
*****************************************************************************/
void Deal_LED_Segment(void) //"��̬�����LED_Segment" : ����ͬ"����ģʽ"
{
////////////////////////////////////////////////////////////////////////////
//==** **=================================================//
		//--care--care--TM1638,һ��API���ж��е��ã�һ��API����ѭ���е��á������ִ����ѭ����APIʱ�������ж����TM1638��API,�ͻ��������
		//������䣬��֤������API,������ͬһʱ���ڱ�����
	F_En_Scan_MatrixKey = NO;  //��ֹɨ��"���󰴼�ɨ��"

	switch(G_Mode_LED_Segment) 
	{
case MODE_Idle_LED_Segment:	//Mode������(�����κβ���)("��̬�����LED_Segment" )
	
	break;	

case MODE_Open_LED_Segment:	//Mode��"��"��ģ��("��̬�����LED_Segment" )
		//��ʾ"��"+�Զ�"PWMΪ1/16" (�)("��̬�����LED_Segment" )
	Open_LED_Segment();
		//ִ��һ������󣬻ص�//Mode��������ʾ("��̬�����LED_Segment" )
	G_Mode_LED_Segment = MODE_Refresh_LED_Segment; 	
	break;	

case MODE_Close_LED_Segment: //Mode��"�ر�"��ģ��("��̬�����LED_Segment" )	
		//�ر�LED_Segment ("��̬�����LED_Segment" )
	Close_LED_Segment();
	break;	

case MODE_Refresh_LED_Segment: //Mode��������ʾ("��̬�����LED_Segment" )
		//���������"�Զ�(����)"("��̬�����LED_Segment" )
	Deal_Brightness_LED_Segment();

	Refresh_LED_Segment(); //������ʾ("��̬�����LED_Segment" )
	break;	

////////////////////////////////////////////////////////////////////////////
default:
	break;
	}

	F_En_Scan_MatrixKey = YES;  //ʹ��"���󰴼�ɨ��"


}



/****************************************************************************
*������-Function:	void Disp_LED_Segment(unsigned char pointNum1,unsigned char pointNum2,unsigned char NO_8,unsigned char NO_7,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1)
*����- Description:	"��ʾ�ַ�"���µ�"��ʾ��������"("��̬�����LED_Segment" )
*�������-Input:	pointNum1:�����е�С����λ��(��1��С����);  
						pointNum2:�����е�С����λ��(��2��С����);  
                                         NO_8~NO_1:�����еĸ����������ʾֵ
*�������-output:	None
*ע������-Note��
	��01)    
	//G_LedSegBuf[0];  //��Ӧ"��1���ַ�"
	//G_LedSegBuf[1];  //��Ӧ"��2���ַ�"
	//G_LedSegBuf[2];  //��Ӧ"��3���ַ�"
	//G_LedSegBuf[3];  //��Ӧ"��4���ַ�"
	//G_LedSegBuf[4];  //��Ӧ"��5���ַ�"
	//G_LedSegBuf[5];  //��Ӧ"��6���ַ�"
	//G_LedSegBuf[6];  //��Ӧ"��7���ַ�"
	//G_LedSegBuf[7];  //��Ӧ"��8���ַ�"
	��02) pointNumΪ0ʱ����ʾ����ʾ"С����"
	�� Disp_LED_Segment(8,2,8,7,6,5,4,3,2,1); //��ʽ���ҵ�����ʾͼΪ"8.765432.1"
	      Disp_LED_Segment(0,2,8,7,6,5,4,3,2,1); //��ʽ���ҵ�����ʾͼΪ"8765432.1"
	��03)    ��04)  
*****************************************************************************/
void Disp_LED_Segment(unsigned char pointNum1,unsigned char pointNum2,unsigned char NO_8,unsigned char NO_7,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1)
{
	G_LedSegBuf[0] = NO_1;//��Ӧ"��1���ַ�"+"���ұ�"��"С����"(���ұ߿�ʼ��)
	G_LedSegBuf[1] = NO_2;
	G_LedSegBuf[2] = NO_3;
	G_LedSegBuf[3] = NO_4;
	G_LedSegBuf[4] = NO_5;
	G_LedSegBuf[5] = NO_6;
	G_LedSegBuf[6] = NO_7;
	G_LedSegBuf[7] = NO_8;
	G_LedSegBuf[8] = pointNum1;
	G_LedSegBuf[9] = pointNum2;

}

