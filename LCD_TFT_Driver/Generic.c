/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 Generic.c
* �����ļ�-Dependencies:  	 Generic.h; Hardware_Profile.h;
* �ļ�����-File Description:	 ( Դ����-Source File) 
	�����ó����̹淶�������� -Generic Type Definitions
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

#include "Hardware_Profile.h"  //������"Ӳ�������ļ�" -Hardware specific definitions for Processor

#include "Generic.h"	//���ó����̹淶�������� -ͷ�ļ�-Generic Type Definitions


////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned char ASCII_Table[21]={"0123456789ABCDEF.+- "};  //0--F�ַ� ��  �����ַ� ��ʾ��
								

////////////////////////////////////////////////////////////////////////////
//==**Temp*ȫ�ֱ���**===================================//
//--**�����õ��м������������ȥ����**---------------//

//unsigned char G_TempBuf[50]= {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
//                              0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
//                              0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
//                              0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
//                              0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
unsigned char G_TempChar = 0 ;    //������ʱ�õ�"�ֽ�"����
//unsigned int G_TempWord = 0 ;     //������ʱ�õ�"����"����
//unsigned long G_TempDword = 0 ;   //������ʱ�õ�"˫��"����


////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////



/****************************************************************************
*������-Function:	void Copy_Array_AtoB(unsigned char *RxPoint,const unsigned char *TxPoint,unsigned char Cnt)
*����- Description:		������tx[��x����ʼ]��cnt���������Ƶ�����Rx[��y����ʼ]
*�������-Input:	TxPoint: ����Array_A;  RxPoint: ����Array_B;   Cnt: �����ֽڸ���
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Copy_Array_AtoB(unsigned char *RxPoint,const unsigned char *TxPoint,unsigned char Cnt)
{
	for( ; Cnt > 0; Cnt--)
	{
        *RxPoint = *TxPoint;
        RxPoint++;
        TxPoint++;
	}        
}



/****************************************************************************
*������-Function:	void Sent_DataToArray(unsigned char *ArrayPoint,unsigned char DataValue,unsigned int Cnt)
*����- Description:		��Cnt����ͬ��Data���ݸ��Ƶ�����Array[x]֮���Cnt��Ԫ��
*�������-Input:	ArrayPoint: Ŀ������;  DataValue: �ֽ�����;   Cnt: �����ֽڸ���  
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Sent_DataToArray(unsigned char *ArrayPoint,unsigned char DataValue,unsigned int Cnt)
{
	for( ; Cnt > 0; Cnt--)
    {
    	*ArrayPoint = DataValue;
		ArrayPoint++;
    }
}


/****************************************************************************
*������-Function:	void WaitingDelayMs(unsigned int TimeData)  
*����- Description:		���ȴ���ʱx����
*�������-Input:	TimeData: Ҫ��ʱmsֵ����WaitingDelayMs(1);  //��ʾ���ȴ���ʱ1ms
*�������-output:	None
*ע������-Note��	
	��01) ��ϵͳƵ���й�,DCO��ƵΪ12MHzʱȡt1 = 60 (��ǰϵͳƵ��12M)
	            ��ϵͳƵ���й�,DCO��ƵΪ20MHzʱȡt1 = 107 
	��02) TimeData  = TimeData *10 = 100ʱ����ʱΪ10ms   
	��03) ����"�忴�Ź�"����   
	��04) ms����������ʱ������WaitingDelayMs(n); //���ȴ���ʱn��ms(�����忴�Ź�����)
	            us����������ʱ������mDelay_Cycles(n);	//���ȴ���ʱn��ʱ������ 
*****************************************************************************/
void WaitingDelayMs(unsigned int TimeData)  
{
	unsigned char t1;
	unsigned int t2;

	TimeData = TimeData *10;   //����Ϊ20MHzʱ,TimeData = 100ʱ����ʱΪ10ms
	
	for(t2 = TimeData; t2 != 0; t2--)
	{
		for(t1 = 60; t1 != 0; t1--)
		{      
//mClr_WDTCNT;  // �忴�Ź�
			
			mNop; mNop; mNop; mNop;   //�ղ���ָ��(����"����ʱ"��"����")
			mNop; mNop; mNop; mNop; 
			mNop; mNop; mNop; mNop;   
		}
	}
}


/****************************************************************************
*������-Function:	void WaitingDelayMs(unsigned int TimeData)  
*����- Description:		���ȴ���ʱx����
*�������-Input:	TimeData: Ҫ��ʱmsֵ����WaitingDelayMs(1);  //��ʾ���ȴ���ʱ1ms
*�������-output:	None
*ע������-Note��	
	��01) ��ϵͳƵ���й�, ����Ϊ20MHzʱ(��t1 = 107)
	��02) TimeData  = TimeData *10 = 100ʱ����ʱΪ10ms   
	��03) ����"�忴�Ź�"����   
	��04) ms����������ʱ������WaitingDelayMs(n); //���ȴ���ʱn��ms(�����忴�Ź�����)
	            us����������ʱ������mDelay_Cycles(n);	//���ȴ���ʱn��ʱ������ 
***************************************************************
void WaitingDelayMs(unsigned int TimeData)  
{
	unsigned char t1;
	unsigned int t2;

	TimeData = TimeData *10;   //����Ϊ20MHzʱ,TimeData = 100ʱ����ʱΪ10ms
	
	for(t2 = TimeData; t2 != 0; t2--)
	{
		for(t1 = 107; t1 != 0; t1--)
		{      
			mClr_WDTCNT;  // �忴�Ź�
			
			mNop; mNop; mNop; mNop;   //�ղ���ָ��(����"����ʱ"��"����")
			mNop; mNop; mNop; mNop; 
			mNop; mNop; mNop; mNop;   
		}
	}
}

**************/


