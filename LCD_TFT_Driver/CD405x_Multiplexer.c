/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 CD405x_Multiplexer.c
* �����ļ�-Dependencies:  	 CD405x_Multiplexer.h; Hardware_Profile.h; Generic.h;
* �ļ�����-File Description:	 ( Դ����-Source File) 
	��"CD405x_Multiplexer��·ѡ��ģ�⿪��"  -��������(�ⲿ��Դ)
	01) CD4052B ��˫��ѡһģ�⿪�أ�ÿ����ѡһģ�⿪�طֱ�
��2 �������ƿ������롣
	02) INH ��������롰1����ƽʱ��������ѡһģ�⿪������ͨ����Ϊ�ض�״̬��
	03) �ܿ�����ֿ����봫��ģ���źŵ�ѹ��Χ������3��15V��ģ��15Vp-p
	04)     05)      06)	
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


#include "CD405x_Multiplexer.h"   //"CD405x_Multiplexer��·ѡ��ģ�⿪��"  -��������(�ⲿ��Դ)-ͷ�ļ�



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////





/****************************************************************************
*������-Function:	void CD405x_SelectChannel(unsigned channel)
*����- Description:	ѡ��ָ��ͨ��("CD405x_Multiplexer��·ѡ��ģ�⿪��" )
*�������-Input:	channel : Ҫѡ���ͨ��
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void CD405x_SelectChannel(unsigned channel)
{
 	//mOpen_CD405x_INH; //��������Ϊ"���",��"ʹ��"CD405x ģ��("��"��ƽ��Ч)

	switch(channel)
	{
		case CD405x_Humidity: //CD405x�е�"Humidity  ʪ��"
			mConfig_CD405x_A(0);  //A  =  0 //IN1
			mConfig_CD405x_B(0);  //B  =  0  //IN2
			break;

		case CD405x_Step_Motor:  //CD405x�е�"Step_Motor �������"
			mConfig_CD405x_A(0);  //A  =  0 //IN1
			mConfig_CD405x_B(1);  //B  =  0  //IN2
			break;
			
		case CD405x_DC_Motor:  //CD405x�е�"DC_Motor ֱ�����"
			mConfig_CD405x_A(1);  //A  =  0 //IN1
			mConfig_CD405x_B(0);  //B  =  0  //IN2
			break;
			
		default: break;

	}
}

