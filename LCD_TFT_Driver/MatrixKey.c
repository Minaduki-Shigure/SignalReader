/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 MatrixKey.c
* �����ļ�-Dependencies:  	 MatrixKey.h; TM1638.h; Speaker.h;
                                                        Hardware_Profile.h; Generic.h; 
* �ļ�����-File Description:	 ( Դ����-Source File) 
	��  "���󰴼�" -��������(�ⲿ��Դ)
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




#include "Generic.h"	//���ó����̹淶�������� -ͷ�ļ�-Generic Type Definitions

#include "Hardware_Profile.h"  //������"Ӳ�������ļ�" -Hardware specific definitions for Processor




#include "Speaker.h"   //"Speaker ������" -��������(�ⲿ��Դ)-ͷ�ļ�


#include "TM1638.h"  // "TM1638 �����������" -��������(�ⲿ��Դ) -ͷ�ļ�

#include "MatrixKey.h"   //"���󰴼�" -��������(�ⲿ��Դ)-ͷ�ļ�


////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////

union FLAGBIT16 MatrixKeyFlagBits;  //���󰴼��õ��ı�־λ����

unsigned char G_MatrixKeyValue = M_NullMatrixKey;  //����󰴼������İ���ֵ (����һ�㳣�õİ���)


unsigned char G_MatrixKeyBuf[32];  //��������Ķ������ֵ
unsigned char G_MatrixKeyCnt = 0;  //������������ָ��

unsigned char G_TotalKeyNum = 0;  //��������ְ����ܸ���
unsigned char G_DecimalPoint = 0;  //��������ְ�����С����λ��(���ڹ����ʾ)
unsigned char G_KeyPlace_Row = 0;    //(��)�������ò���λ��(���)��ʼλ��
unsigned char G_KeyPlace_Column = 0; //(��)�������ò���λ��(���)��ʼλ��
unsigned int  G_KeyValue_Addr = 0;  //�ɼ�������а����浽EEPROM/Flashָ����ַ




////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////



unsigned char pMatrixKeyResult = 0;  //���ھ��󰴼��˲�
unsigned char pMatrixKeyBuffer = 0;
unsigned char pMatrixKeyCnt = 0;     //����ʱ�������õļ�����
unsigned char pMatrixKeyNullCnt = 0; //����ʱ�������õļ�����

unsigned int  pLongMatrixKeyCnt = 0;  //����������.//ʱ��Ϊ10ms("ѭ��"ִ��һ�γ���)




/****************************************************************************
*������-Function:	void Scan_MatrixKey(void)
*����- Description:	"�������"ɨ�裬5msɨ��һ�ΰ���(�ж���)	
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) ���ж���ɨ��System_1ms_Task(); 
	��02)    ��03)    ��04)  
*****************************************************************************/
void Scan_MatrixKey(void)
{         
//rKeyResult = G_InPut165_01;     //����ֵ(��74HC165�ĵ�һ���ֽڲ���)����
//pMatrixKeyResult = pMatrixKeyResult & M_MatrixKeyUsed;		
//pMatrixKeyResult = Sample_MatrixKey(); //�����������ɨ��

		//�����������
	pMatrixKeyResult = Read_MatrixKey_TM1638();  //�����󰴼�ֵ(TM1638)

	if(pMatrixKeyResult != M_NullMatrixKey)         //�м�����
	{
		pMatrixKeyNullCnt = 0;  //����ʱ�������õļ�����
	
		F_MatrixKeyHave = 1; 
	} 
	else
	{
		F_MatrixKeyHave = 0;
		
		pMatrixKeyNullCnt ++;
		if(pMatrixKeyNullCnt >= M_MatrixKeyDelayTime)
		{
			pMatrixKeyNullCnt = 0;  //����ʱ�������õļ�����
			F_MatrixKeyNull = 1;

			pMatrixKeyBuffer = M_NullMatrixKey;  //��������������Ϊ��Ч����
			G_MatrixKeyValue = M_NullMatrixKey;  //��������������Ϊ��Ч����
		}
		
		pMatrixKeyCnt = 0;          //Լ20ms�����õ�
	}
	 
	if(F_MatrixKeyHave)
    {
		if(pMatrixKeyResult != pMatrixKeyBuffer)
		{
			pMatrixKeyBuffer = pMatrixKeyResult;
			pMatrixKeyCnt = 0;
		}
		else
		{
			pMatrixKeyCnt ++;
			if(pMatrixKeyCnt >= M_MatrixKeyDelayTime)   //(4+1)*5ms= 25ms  
			{
				pMatrixKeyCnt = 0;
				if(F_MatrixKeyNull)    //���ݱ�־λF_MatrixKeyNull��ʹ����ֻ���ٵ������ٰ�����Ч
				{
					G_MatrixKeyValue = pMatrixKeyBuffer;
					
					if(G_MatrixKeyValue != M_NullMatrixKey)
					{
						F_MatrixKeyRead = 1;
			
						F_MatrixKeyNull = 0;
						pMatrixKeyNullCnt = 0;  //����ʱ�������õļ�����

				//�а������£��򿪷�����
			//Open_Buzz_Speaker(M_200MS_BUZZ);  //�򿪷�����(Speaker ������)�Ķ�ʱ��

							//�а�������ʱ����һֱ�����������ʹҺ��һֱ��ʾ
						/////G_BackLightCnt = G_BackLightNum; 
						
						/////F_AlarmBuzz = 0;	//�����ⰴ�����£��ر���
						
						/////if(!F_StartBuzz)	//��������������������ֲ�ͬ���ȵķ�������(�ѳ��и�һ������ֿ���)
						/////{
						/////	BuzzTimeNum = M_Buzz200ms;	//�а�������ʱ,������ͨ������,������200ms									
						/////	F_StartBuzz = 1; 
						/////}	
						
					}
				}
			}
		}

    }	

/***************
	if(F_CloseLcm)    //good //���֮ǰҺ����ʾΪʡ��״̬���а������£���Һ������ִ�а�������
	{
		if(F_MatrixKeyRead)
		{
			F_MatrixKeyRead = 0; 
			F_CloseLcm = 0;
			G_BackLightCnt = G_BackLightNum; //�а�������ʱ����һֱ�����������ʹҺ��һֱ��ʾ
			MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч
		
		}
	}
	*********************/
	
}


/****************************************************************************
*������-Function:	unsigned char Detect_MatrixKey(void)
*����- Description:	�����û�а���,�����ذ���ֵ(����һ�㳣�õİ���)
*�������-Input:	None
*�������-output:	���尴��ֵ(�ް������򷵻�"0xFF")
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_MatrixKey(void)  //�����û�а���,�����ذ���ֵ(����һ�㳣�õİ���)
{     
	unsigned char i;
	
	if(G_MatrixKeyValue != M_NullMatrixKey) 
	{
		i = G_MatrixKeyValue;
		G_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		
	}
	else i = 0xFF;  //0xFFΪ��Ч��
	
	return(i);
}


/****************************************************************************
*������-Function:	unsigned char Detect_Press_MatrixKey(void)
*����- Description:	����󰴼������İ���ֵ(����ִ�У��ɿ�ֹͣ)
*�������-Input:	None
*�������-output:	���尴��ֵ(�ް������򷵻�"0xFF")
*ע������-Note��	
	��01) ��ֵ�����������尴��ֵ
	��02) ����"����"����ʼĳ������������"�ɿ�"��ֹͣ����
	��03)    ��04)  
*****************************************************************************/
unsigned char Detect_Press_MatrixKey(void) //����󰴼������İ���ֵ(����ִ�У��ɿ�ֹͣ)
{     
	unsigned char i;
	
	if(G_MatrixKeyValue != M_NullMatrixKey) 
	{
		i = G_MatrixKeyValue;
		//care ���尴��ֵG_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
	}
	else i = 0xFF;  //0xFFΪ��Ч��
	
	return(i);
}


/****************************************************************************
*������-Function:	unsigned char Detect_Long_MatrixKey(unsigned char SecondNum)
*����- Description:	(����X����Ч)�����û�г����İ���,�����ذ���ֵ
*�������-Input:	������ʱ��X��(��λ:��)
*�������-output:	���尴��ֵ(�ް������򷵻�"0xFF")
*ע������-Note��	
	��01) ��ֵ�����������尴��ֵ
	��02) ��if(Detect_Long_MatrixKey(10) == 5)   //�������"5��"10��,��ִ��if�������� 
	��03)    ��04)  
*****************************************************************************/
unsigned char Detect_Long_MatrixKey(unsigned char SecondNum)//(����X����Ч)�����û�г����İ���,�����ذ���ֵ
{     
	unsigned char pLong_MatrixKey = M_NullMatrixKey;
	
	if(pMatrixKeyBuffer != M_NullMatrixKey)
	{
		pLongMatrixKeyCnt++;  //ʱ��Ϊ10ms
		if(pLongMatrixKeyCnt > SecondNum*100)  //����ʱ��ΪpNum/100��
		{
			pLongMatrixKeyCnt = 0; //�峤��������.

			pLong_MatrixKey = pMatrixKeyBuffer;
			
			//BuzzTimeNum = M_Buzz1s; //�޸ĳɹ��򱣴�ɹ���//������ͨ������,����������1��		 							
			//F_StartBuzz = 1; 
		}
	}
	else pLongMatrixKeyCnt = 0; //�峤��������.

	return (pLong_MatrixKey);
}




/****************************************************************************
*������-Function:	unsigned char Detect_MatrixKey_0(void)
*����- Description:	���"0" ���󰴼� ��û�а���
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_0(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_0) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}



/****************************************************************************
*������-Function:	unsigned char Detect_MatrixKey_1(void)
*����- Description:	���"1" ���󰴼� ��û�а���
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_1(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_1) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*������-Function:	unsigned char Detect_MatrixKey_2(void)
*����- Description:	���"2" ���󰴼� ��û�а���
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_2(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_2) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*������-Function:	unsigned char Detect_MatrixKey_3(void)
*����- Description:	���"3" ���󰴼� ��û�а���
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_3(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_3) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}

/****************************************************************************
*������-Function:	unsigned char Detect_MatrixKey_4(void)
*����- Description:	���"4" ���󰴼� ��û�а���
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_4(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_4) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*������-Function:	unsigned char Detect_MatrixKey_5(void)
*����- Description:	���"5" ���󰴼� ��û�а���
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_5(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_5) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*������-Function:	unsigned char Detect_MatrixKey_6(void)
*����- Description:	���"6" ���󰴼� ��û�а���
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_6(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_6) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*������-Function:	unsigned char Detect_MatrixKey_7(void)
*����- Description:	���"7" ���󰴼� ��û�а���
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_7(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_7) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*������-Function:	unsigned char Detect_MatrixKey_8(void)
*����- Description:	���"8" ���󰴼� ��û�а���
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_8(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_8) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}

/****************************************************************************
*������-Function:	unsigned char Detect_MatrixKey_9(void)
*����- Description:	���"9" ���󰴼� ��û�а���
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_9(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_9) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*������-Function:	unsigned char Detect_MatrixKey_A(void)
*����- Description:	���"A" ���󰴼� ��û�а���
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_A(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_A) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*������-Function:	unsigned char Detect_MatrixKey_B(void)
*����- Description:	���"B" ���󰴼� ��û�а���
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_B(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_B) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}



/****************************************************************************
*������-Function:	unsigned char Detect_MatrixKey_C(void)
*����- Description:	���"C" ���󰴼� ��û�а���
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_C(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_C) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*������-Function:	unsigned char Detect_MatrixKey_D(void)
*����- Description:	���"D" ���󰴼� ��û�а���
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_D(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_D) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}

/****************************************************************************
*������-Function:	unsigned char Detect_MatrixKey_E(void)
*����- Description:	���"E" ���󰴼� ��û�а���
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_E(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_E) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*������-Function:	unsigned char Detect_MatrixKey_F(void)
*����- Description:	���"F" ���󰴼� ��û�а���
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_F(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_F) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}



/****************************************************************************
*������-Function:	unsigned char Detect_MatrixKey_AC(void)
*����- Description:	���"AC" ���󰴼� ��û�а���
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_AC(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_AC) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*������-Function:	unsigned char Detect_MatrixKey_Plus(void)
*����- Description:	���"+" ���󰴼� ��û�а���
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_Plus(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_Plus) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}


/****************************************************************************
*������-Function:	unsigned char Detect_MatrixKey_Minus(void)
*����- Description:	���"-" ���󰴼� ��û�а���
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_Minus(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_Minus) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}



/****************************************************************************
*������-Function:	unsigned char Detect_MatrixKey_Equal(void)
*����- Description:	���"=" ���󰴼� ��û�а���
*�������-Input:	None
*�������-output:	1: �а��´˼� 0: û�а��´˼�
*ע������-Note��	
	��01) ��ֵ���������������������0���ٲ���
	��02)    ��03)    ��04)  
*****************************************************************************/
unsigned char Detect_MatrixKey_Equal(void)  
{	  
	unsigned char i;
	if(G_MatrixKeyValue == MatrixKey_Equal) 
	{
		G_MatrixKeyValue = M_NullMatrixKey;   //care �����൱�ڶ԰�����0(�����ֻ��һ����Ч)
		i = 1;
	}
	else i = 0;

	return(i);
}





/****************************************************************************
*������-Function:	unsigned char Sample_MatrixKey(void)
*����- Description:	�����������ɨ��
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) ���ж���ɨ��System_1ms_Task(); 
	��02)    ��03)    ��04)  
**************************************************
unsigned char Sample_MatrixKey(void)
{
	unsigned char i,j;
	unsigned int L_MatrixKeyIOData; //����IO�ڵ�ʵ��ֵ
	unsigned char L_MatrixKeyValue;//������Ľ���İ���ֵ
	
	Y1_MatrixKey_TRIS = 0;  //����Ϊ�����
	Y2_MatrixKey_TRIS = 0;
	Y3_MatrixKey_TRIS = 0;
	
	X1_MatrixKey_TRIS = 1; //����Ϊ�����
	X2_MatrixKey_TRIS = 1;
	X3_MatrixKey_TRIS = 1;
	X4_MatrixKey_TRIS = 1;
	X5_MatrixKey_TRIS = 1;

		//ɨ��֮ǰ���������ʹֵΪ"�޼�"0xFF //care ֻ�ܷ�������
	L_MatrixKeyValue = 0xFF; //û�а�������ʱ�İ���ֵ��Ϊ0xFF


	for(i = 0; i < 3 ; i++)       //3��*5�о���ɨ��
	{
		switch(i)
		{	
			case 0:   
				Y1_MatrixKey_IO = 0;  //��1�����Ϊ�͵�ƽ
				Y2_MatrixKey_IO = 1;
				Y3_MatrixKey_IO = 1;
				break;
			
			case 1: 
				Y1_MatrixKey_IO = 1;  //��2�����Ϊ�͵�ƽ
				Y2_MatrixKey_IO = 0;
				Y3_MatrixKey_IO = 1;
				break;
			
			case 2:  
				Y1_MatrixKey_IO = 1;  //��3�����Ϊ�͵�ƽ
				Y2_MatrixKey_IO = 1;
				Y3_MatrixKey_IO = 0;
				break;
			
			default:	  
				break;

		}

		for(j = 0; j < 5 ; j++)
		{		
			L_MatrixKeyIOData = MatrixKey_PORT & 0x200F;  //0x200F��Ӧ����RB0,RB1,RB2,RB3,RB13   ,Ϊ������ֵ
				//���󰴽�ʵ��ֵ= ������ֵ| ��ֵ
			L_MatrixKeyIOData = L_MatrixKeyIOData | (MatrixKey_LAT & 0x1300);  //0x1300��Ӧ����RB8,RB9,RB12   ,Ϊ������ֵ



			switch(L_MatrixKeyIOData)
			{
	//��Ҫ�ж��Ƿ��Ƕ�������İ��µ����		
				case 0x230E:  //"1��" 
					L_MatrixKeyValue = 1;
					break;
			
				case 0x230D:  //"4��" 
					L_MatrixKeyValue = 4;
					break;
				
				case 0x230B:  //"7��" 
					L_MatrixKeyValue = 7;
					break;

				
				case 0x2307:  //"���" 
					L_MatrixKeyValue = 0x0A;
					break;		
				
				case 0x030F:  //"ESC�˳���" 
					L_MatrixKeyValue = 0x0C;
					break;



				case 0x320E:  //"2��" 
					L_MatrixKeyValue = 2;
					break;
			
				case 0x320D:  //"5��" 
					L_MatrixKeyValue = 5;
					break;

				
				case 0x320B:  //"8��" 
					L_MatrixKeyValue = 8;
					break;

				
				case 0x3207:  //"0��" 
					L_MatrixKeyValue = 0;
					break;		
				
				case 0x120F:  //"MENU�˵���" 
					L_MatrixKeyValue = 0x0D;
					break;

				case 0x310E:  //"3��" 
					L_MatrixKeyValue = 3;
					break;
			
				case 0x310D:  //"6��" 
					L_MatrixKeyValue = 6;
					break;

				
				case 0x310B:  //"9��" 
					L_MatrixKeyValue = 9;
					break;

				
				case 0x3107:  //"�Ҽ�" 
					L_MatrixKeyValue = 0x0B;
					break;		
				
				case 0x110F:  //"Enterȷ����" 
					L_MatrixKeyValue = 0x0E;
					break;
					
				//case :  
					
				//	break;

				default:	//"�޼�" 
				//	L_MatrixKeyValue = 0xFF;  //û�а�������ʱ�İ���ֵ��Ϊ0xFF
					break;
			}
				

			
		}
	}

	return (L_MatrixKeyValue); //���ذ���ֵ
	
}
***************************/


/****************************************************************************
*������-Function:	void Decode_MatrixKey(void)
*����- Description:	������̴���
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01)    ��02)    ��03)    ��04)  
********************************************
void Decode_MatrixKey(void)
{  

////////////////////////////////////////////////////////////////////////////
//==**��ⰴ���Ƿ��а���**============================//
	if(F_MatrixKeyRead)  //Լÿ5msɨ��һ�ΰ���,
	{
		F_MatrixKeyRead = 0; 
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






