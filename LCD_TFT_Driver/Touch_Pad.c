/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 Touch_Pad.c
* �����ļ�-Dependencies:  	 Touch_Pad.h; CTS_HAL.h; CTS_Layer.h; msp430f6638.h;
								Hardware_Profile.h; Generic.h;
* �ļ�����-File Description:	 ( Դ����-Source File) 
	��"Touch_Pads ���ݰ���" -��������(�ⲿ��Դ)
	01)��������һ�����̣���ع���һ����Ӧ���ݣ�����Χ����
���������µ��ݹ̶�Ϊ΢Сֵ�����й̶��ĳ�ŵ�ʱ�䣬��
����һ��������缫����ʱ�����γ���ϵ��ݣ������ͻ�ı�
���еĳ�ŵ�ʱ�䣬����ָ���������ĵ��塣ͨ��������ŵ�
ʱ��ĸı伴�ɼ�ⰴ���Ƿ��а��¡�
	02)���ø�Ӧ����,���蹹�ɵ� RC ��·������ŵ�ʱ��仯����
	03)����ԭ��ͨ��������ʽ���������ṹ�����ɹ�������ʽ
��Ӧ���������Ա�ͨ���������壨��ָ���Ե糡���и��š���
�У�������������Χ�Ľӵذ�֮�佫�γɵ�����������ָ����
���������Ϸ�����������ŵ糡���Ӷ�������ݷ�����Ӧ�仯��
	04)  	05)    06)	
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


	//Touch Pads ��
#include"CTS\structure.h"
#include"CTS\CTS_Layer.h"
#include"CTS\CTS_HAL.h"

#include "Touch_Pad.h"   //"Touch_Pad ���ݰ���" -��������(�ⲿ��Դ)-ͷ�ļ�



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned int G_SliderPosition = 0;


////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////


/****************************************************************************
*������-Function:	void Initial_Touch_Pad(void)
*����- Description:		��ʼ������:  "Touch_Pads ���ݰ���" 
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)    ��04)  
*****************************************************************************/
void Initial_Touch_Pad(void)  //��ʼ������: "Touch_Pads ���ݰ���" 
{
//configure CapTouchs ports
P3OUT &=~0x01;
P3DIR  &= ~0X01;  //P3.0Ϊ

P6OUT &= ~0X1F;
P6DIR &= ~0X1F;  //P6.0, P6.1, P6.2, P6.3, P6.4  //����

/*	P3OUT &=~0x7e;
	P3DIR |= 0x7e;
	P6OUT = 0X00;
	P6DIR = 0X00;
*/

	TI_CAPT_Init_Baseline(&slider);				
	TI_CAPT_Update_Baseline(&slider,5);

}



/****************************************************************************
*������-Function:	void Deal_Touch_Pad(void)
*����- Description:		����: "Touch_Pads ���ݰ���"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)        ��04)  
*****************************************************************************/
void Deal_Touch_Pad(void)  //����: "Touch_Pads ���ݰ���"
{
	G_SliderPosition = TI_CAPT_Slider(&slider);	
	

if(G_SliderPosition<10) G_SliderPosition += 19;
	G_SliderPosition = (G_SliderPosition + 17)/18;  //V2.0

//G_SliderPosition = (G_SliderPosition + 18)/20;  //V3.0


/************
if(G_SliderPosition<10) G_SliderPosition += 19;
	G_SliderPosition = (G_SliderPosition + 17)/18;  //V2.0


switch (G_SliderPosition)
{
	case 0: 
		Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
		break;
		
	case 1: 
		Disp_LED_Segment(0,0,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg,DISP_1_LedSeg);

		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 21]= 'P';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 22]= 'a';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 23]= 'd';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 24]= '1';
		F_Refresh_TestLine05 = YES;
		break;

	case 2: 
		Disp_LED_Segment(0,0,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg,DISP_2_LedSeg);

		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 16]= 'P';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 17]= 'a';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 18]= 'd';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 19]= '2';
		F_Refresh_TestLine05 = YES;
		break;

	case 3: 
		Disp_LED_Segment(0,0,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg,DISP_3_LedSeg);

		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 11]= 'P';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 12]= 'a';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 13]= 'd';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 14]= '3';
		F_Refresh_TestLine05 = YES;
		break;
	
	case 4: 
		Disp_LED_Segment(0,0,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg,DISP_4_LedSeg);

		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 6]= 'P';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 7]= 'a';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 8]= 'd';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 9]= '4';
		F_Refresh_TestLine05 = YES;
		break;
	
	case 5: 
		Disp_LED_Segment(0,0,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg,DISP_5_LedSeg);

		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 1]= 'P';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 2]= 'a';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 3]= 'd';
		G_LCD_TFT_Buf[M_TestLine_5][M_Start_Column_Buf + 4]= '5';
		F_Refresh_TestLine05 = YES;
		break;
	
	case (255 / 17):
		break;
}

*************/
}

