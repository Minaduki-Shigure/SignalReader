/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 Key.c
* �����ļ�-Dependencies:  	 Key.h; Speaker.h; Hardware_Profile.h; Generic.h;
* �ļ�����-File Description:	 ( Դ����-Source File) 
	��  "IO ����" -��������(�ⲿ��Դ)
	01)     02)     03)    04)    05)    06)	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ע������-Attention : 	
	��01)   care--��Դ����������Ƶ��һ����1-5k��Ƶ�ʣ�����Ϊ4K
	��02)     ��03)    ��04)    ��05)    ��06)     
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


#include "Speaker.h"   //"Speaker ������" -��������(�ⲿ��Դ)-ͷ�ļ�

#include "Key.h"   //"IO ����" -��������(�ⲿ��Դ)-ͷ�ļ�





////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
union FLAGBIT16 KeyFlagBits;  //�����õ��ı�־λ����



////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////

unsigned char KeyValue = 0;  //�水�������İ���ֵ (����һ�㳣�õİ���)


unsigned char pKeyResult = 0;
unsigned char pKeyBuffer = 0;
unsigned char pKeyBuffer1 = 0;
unsigned char pKeyCnt = 0;     //����ʱ�������õļ�����
unsigned char pKeyNullCnt = 0; //����ʱ�������õļ�����

unsigned int  pLongKeyCnt = 0;  //����������.//ʱ��Ϊ10ms ("ѭ��"ִ��һ�γ���)




/****************************************************************************
*������-Function:	void Scan_Key(void)
*����- Description:	"IO�ڼ���"ɨ�裬5msɨ��һ�ΰ���(�ж���)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) ���ж���ɨ��System_1ms_Task(); 
	��02)    ��03)    ��04)  
*****************************************************************************/
void Scan_Key(void)
{          
//pKeyResult = G_InPut165_01;     //����ֵ(��74HC165�ĵ�һ���ֽڲ���)����

	mSetIn_Key_1_IO;  //����Key_1 ��IO��Ϊ"����"����
	mSetIn_Key_2_IO;  //����Key_2 ��IO��Ϊ"����"����

	pKeyResult = Key_IN;//����ֵIOֵ����

	pKeyResult = pKeyResult & M_KeyUsed;		
	
	if(pKeyResult != M_KeyUsed)         //�м�����
	{
		pKeyNullCnt = 0;  //����ʱ�������õļ�����
	
		F_KeyHave = 1; 
	} 
	else
	{
		F_KeyHave = 0;
		
		pKeyNullCnt ++;
		if(pKeyNullCnt >= M_KeyDelayTime)
		{
			pKeyNullCnt = 0;  //����ʱ�������õļ�����
			F_KeyNull = 1;

			pKeyBuffer = M_NullKey;  //��������������Ϊ��Ч����
			KeyValue = M_NullKey;  //��������������Ϊ��Ч����
		}
		
		pKeyCnt = 0;          //Լ20ms�����õ�
	}

	if(pKeyResult == 0x08) pKeyBuffer = 1;       //����1
	else if(pKeyResult == 0x04) pKeyBuffer = 2;  //����2

	//if(pKeyResult == 0x0E) pKeyBuffer = 1;       //����1
	//else if(pKeyResult == 0x0D) pKeyBuffer = 2;  //����2
	//else if(pKeyResult == 0x0B) pKeyBuffer = 3;  //����3
	//else if(pKeyResult == 0X07) pKeyBuffer = 4;  //����4
	//else if(pKeyResult == 0X2F) pKeyBuffer = 5;  //����5
	//else if(pKeyResult == 0X1F) pKeyBuffer = 6;  //����6
	/////else if(pKeyResult == 0XBF) pKeyBuffer = 7;  //����7
	/////else if(pKeyResult == 0X7F) pKeyBuffer = 8;  //����8
	//else if((F_Sw7_165==0)&&(F_Sw8_165==0)) pKeyBuffer = 9;  //����9 //7����8��ͬʱ����ʱ�İ���ֵ����Ϊ9

		 //��������İ�������Ϊ��Ч����//good,���õ���������ͬʱ���²���Ч�����,һ��Ҫ��������ĳ���else rKeyBuffer = M_NullKey; 
	else pKeyBuffer = M_NullKey; 


	if(F_KeyHave)
    {
		if(pKeyBuffer != pKeyBuffer1)
		{
			pKeyBuffer1 = pKeyBuffer;
			pKeyCnt = 0;
		}
		else
		{
			pKeyCnt++;
			if(pKeyCnt >= M_KeyDelayTime)   //(4+1)*5ms= 25ms  
			{
				pKeyCnt = 0;
				if(F_KeyNull)    //���ݱ�־λF_KeyNull��ʹ����ֻ���ٵ������ٰ�����Ч
				{
					KeyValue = pKeyBuffer;

					if(KeyValue != M_NullKey)
					{
						F_KeyRead = 1;
	
		//�а������£��򿪷�����
	//Open_Buzz_Speaker(M_200MS_BUZZ);  //�򿪷�����(Speaker ������)�Ķ�ʱ��
	
						F_KeyNull = 0;
						pKeyNullCnt = 0;  //����ʱ�������õļ�����
					}
				}
			}
		}

    }	

}



/****************************************************************************
*������-Function:	unsigned char Detect_Key(void)
*����- Description:	�����û�а���,�����ذ���ֵ(����һ�㳣�õİ���)
*�������-Input:	None
*�������-output:	���尴��ֵ(�ް������򷵻�"0xFF")
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_Key(void)  //�����û�а���,�����ذ���ֵ(����һ�㳣�õİ���)
{     
	unsigned char i;
	
	if(KeyValue != M_NullKey) 
	{
		i = KeyValue;
		KeyValue = M_NullKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		
	}
	else i = 0xFF;  //0xFFΪ��Ч��
	
	return(i);
}



/****************************************************************************
*������-Function:	unsigned char Detect_Press_Key(void)
*����- Description:	�水�������İ���ֵ(����ִ�У��ɿ�ֹͣ)
*�������-Input:	None
*�������-output:	���尴��ֵ(�ް������򷵻�"0xFF")
*ע������-Note��	
	��01) ��ֵ�����������尴��ֵ
	��02) ����"����"����ʼĳ������������"�ɿ�"��ֹͣ����
	��03)    ��04)  
*****************************************************************************/
unsigned char Detect_Press_Key(void) //�水�������İ���ֵ(����ִ�У��ɿ�ֹͣ)
{     
	unsigned char i;
	
	if(KeyValue != M_NullKey) 
	{
		i = KeyValue;
		//care ���尴��ֵG_KeyValue = M_NullKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
	}
	else i = 0xFF;  //0xFFΪ��Ч��
	
	return(i);
}




/****************************************************************************
*������-Function:	unsigned char Detect_Long_Key(unsigned char SecondNum)
*����- Description:	(����X����Ч)�����û�г����İ���,�����ذ���ֵ
*�������-Input:	������ʱ��X��(��λ:��)
*�������-output:	���尴��ֵ(�ް������򷵻�"0xFF")
*ע������-Note��	
	��01) ��ֵ�����������尴��ֵ
	��02)  ��if(Detect_Long_Key(10) == 5)   //�������"5��"10��,��ִ��if��������
	��03)    ��04)  
*****************************************************************************/
unsigned char Detect_Long_Key(unsigned char SecondNum)//(����X����Ч)�����û�г����İ���,�����ذ���ֵ
{     
	unsigned char pLongKey = M_NullKey;
	
	if(pKeyBuffer != M_NullKey)
	{
		pLongKeyCnt++;  //ʱ��Ϊ10ms
		if(pLongKeyCnt > SecondNum*100)  //����ʱ��ΪpNum/100��
		{
			pLongKeyCnt = 0; //�峤��������.

			pLongKey = pKeyBuffer;
			
			//BuzzTimeNum = M_Buzz1s; //�޸ĳɹ��򱣴�ɹ���//������ͨ������,����������1��		 							
			//F_StartBuzz = 1; 
		}
	}
	else pLongKeyCnt = 0; //�峤��������.

	return (pLongKey);
}





/****************************************************************************
*������-Function:	unsigned char Detect_Key_1(void)
*����- Description:	�����û�а���IO����"Key1"
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_Key_1(void)  
{	  
	unsigned char i;
	if(KeyValue == Key_1) 
	{
		KeyValue = M_NullKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*������-Function:	unsigned char Detect_Key_2(void)
*����- Description:	�����û�а���IO����"Key2"
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_Key_2(void)  
{	  
	unsigned char i;
	if(KeyValue == Key_2) 
	{
		KeyValue = M_NullKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return (i);
}




/****************************************************************************
*������-Function:	void Decode_Key(void)
*����- Description:	IO�ڼ��̴���
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01)    ��02)    ��03)    ��04)  
********************************************
void Decode_Key(void)
{  

////////////////////////////////////////////////////////////////////////////
//==**��ⰴ���Ƿ��а���**============================//
	if(F_KeyRead)  //Լÿ5msɨ��һ�ΰ���,
	{
		F_KeyRead = 0; 
		G_BackLightCnt = G_BackLightNum; //�а�������ʱ����һֱ�����������ʹҺ��һֱ��ʾ

//////F_AlarmBuzz = 0;  //�����ⰴ�����£��ر���
			
		if(!F_StartBuzz)    //��������������������ֲ�ͬ���ȵķ�������(�ѳ��и�һ������ֿ���)
		{
			BuzzTimeNum = M_Buzz200ms; 	//�а�������ʱ,������ͨ������,������200ms		 							
			F_StartBuzz = 1; 
		}

	}

}
*********************************/




