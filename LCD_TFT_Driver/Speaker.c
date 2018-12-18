/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 Speaker.c
* �����ļ�-Dependencies:  	 Speaker.h; math.h; msp430f6638.h;
                                                        Hardware_Profile.h;  Generic.h;
* �ļ�����-File Description:	 ( Դ����-Source File) 
	��  "Speaker ������" -��������(�ⲿ��Դ)
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

#include "System.h"	 //"ϵͳ" ���ù��ܺ�����-ͷ�ļ�
#include "MyProject.h"	//������Ŀ: �ܹ��ܳ���-ͷ�ļ�


#include "Speaker.h"   //"Speaker ������" -��������(�ⲿ��Դ)-ͷ�ļ�

#include <math.h>


////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
union FLAGBIT16 SpeakerFlagBits;  //"Speaker ������"�õ��ı�־λ����
  



////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned long G_Timing_Speaker_Cnt = 0; //������(Speaker ������)�Ķ�ʱ��������



#define PI 3.1415926

int sin_table[10];    // ���Ҳ����� 
int *sin_data_pr;  // ָ�����Ҳ������ָ�� 




	// ������������������1,2,3,4,5,6,7���׶�Ӧ������Ƶ������  
int key_table[22]={261,293,329,349,391,440,493,  533,587,659,698,783,880,987,  1046,1174,1318,1396,1567,1760,1975};
int period_table[21];  //��Ӧ���������������� 

//��ֻ�ϻ�
//int song_tone_table[32]={7,8,9,7,7,8,9,7,9,10,11,9,10,11,11,12,11,10,9,7,11,12,11,10,9,7,7,11,7,7,11,7};
//int song_long_table[32]={4,4,4,4,4,4,4,4,4,4,8,4,4,8,2,2,2,2,4,4,2,2,2,2,4,4,4,4,8,4,4,8};

//���ո�//�������� 5   5   6   5   1.   7   5   5    6   5   2.  1.   5   5  5.   3.  1.   7   4.  4.  3.  1.   2.   1.
//int song_tone_table[24]=  { 4, 4, 5, 4, 7, 6, 4, 4, 5, 4, 8, 7, 4, 4,11, 9, 7, 6,10,10, 9, 7, 8, 7};  //������
//int song_tone_table[24]=  {11,11,12,11,14,13,11,11,12,11,15,14,11,11,18,16,14,13,17,17,16,14,15,16}; //������
	//������+ ������
//int song_tone_table[48]=  { 4, 4, 5, 4, 7, 6, 4, 4, 5, 4, 8, 7, 4, 4,11, 9, 7, 6,10,10, 9, 7, 8, 7,11,11,12,11,14,13,11,11,12,11,15,14,11,11,18,16,14,13,17,17,16,14,15,16};

//���ո�//�������� 5   5   6   5   1.   7   5   5    6   5   2.  1.   5   5  5.   3.  1.   7   4.  4.  3.  1.   2.   1.
             //                      1   1   2   1    4   3    1   1   2   1   5    4    1  1   1.   6   4   3    7   7   6    4   5    4  
int song_tone_table[48]=  { 0, 0, 1, 0, 3, 2, 0, 0, 1, 0, 4, 3, 0, 0, 7, 5, 3, 2, 6, 6, 5, 3, 4, 3, 4, 4, 5, 4, 7, 6, 4, 4, 5, 4, 8, 7, 4, 4,11, 9, 7, 6,10,10, 9, 7, 8, 7};


//���ո�//��������//�����ٶȿ���
//int song_long_table[24]={2,2,4,4,4,8,2,2,4,4,4,8,2,2, 5,4,5,8, 2, 2,4,4,4,8};
//int song_long_table[24]={10,10,20,20,20,40,10,10,20,20,20,40,10,10,25,20,25,40,10,10,20,20,20,40};
//int song_long_table[24]={12,12,22,22,22,42,12,12,22,22,22,42,12,12,27,22,27,42,12,12,22,22,22,42};
int song_long_table[24]={36,36,66,66,66,126,36,36,66,66,66,126,36,36,81,66,81,126,36,36,66,66,66,126};


//int song_long_table[24]={8,8,16,16,16,32,8,8,16,16,16,32,8,8, 20,16,20,32, 8, 8,16,16,16,32};


int key;
int m,n;
int k;


/****************************************************************************
*������-Function:	void Disable_Speaker(void)
*����- Description:		��ֹ:  "Speaker ������" 
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)    ��04)  
*****************************************************************************/
void Disable_Speaker(void) //��ֹ:  "Speaker ������" 
{

	DMA0CTL &= ~DMAEN;
//	ADC12CTL0 &= ~ADC12ENC;
	DAC12_1CTL0 &= ~DAC12ENC;

//	P4OUT &= ~BIT0;  //Microphone power source
//	P4DS &= ~BIT0;
//	P4DIR &= ~BIT0;
	
	P7SEL &= ~BIT6;   //Microphone AD��  //P7.6-->AD14
	
	P5DIR |= BIT6;    //P5.6�ӵ�Speaker �Ŵ���ʹ�ܿ�
	P5OUT |= BIT6;    //P5.6�����ʱ���������ſ��Թ���

	TA1CTL &= ~TAIE;    //�ض�ʱ���ж�
	TA1CCTL0 &= ~CCIE;	  // ��CCR0�ж�
}


/****************************************************************************
*������-Function:	void Play_a_Song_Speaker(void)
*����- Description:		��ʼ������:  ����һ������--"Speaker ������" 
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)    ��04)  
*****************************************************************************/
void Play_a_Song_Speaker(void) //��ʼ������:  ����һ������--"Speaker ������" 
{
	unsigned char j = 0;
	double i = 0;
	
	for(j=0;j<10;j++)   //�������Ҳ����� 
	{
		i+=PI/5;
		sin_table[j]=(int)((sin(i)+1)*2048);
	}
	sin_data_pr=&sin_table[0];
	
	for(j=0;j<20;j++)  //�������׵�Ƶ�ʼ��������� 
	{
		period_table[j]=(int)(300000/key_table[j]);
	}


		//AVcc��Ϊ�ο���ѹ����ʼ��ƫ����У�����˿�p7.7(DAC_1)��� 
	DAC12_1CTL0 = DAC12IR + DAC12SREF_1 + DAC12AMP_5 + DAC12ENC + DAC12CALON+DAC12OPS;

	P5DIR |= BIT6;    //P5.6�ӵ�Speaker �Ŵ���ʹ�ܿ�
	P5OUT &= ~BIT6;   //P5.6�����ʱ���������ſ��Թ���

	TA1CCTL0 = CCIE;	  // CCR0�ж�ʹ��  // CCR0 interrupt enabled

	TA1CCR0 = period_table[0];  // ��ʱΪ��һ���������������� 

		// SMCLK+���ϼ���+��TAR +��ʱ���ж�
	TA1CTL = TASSEL_2 + MC_2 + TACLR +TAIE; 		// SMCLK, upmode, clear TAR


}


/****************************************************************************
*������-Function:	void Deal_Song_Tone_Speaker(void)
*����- Description:		�����ض��������ɶ�ӦƵ�ʵĲ��� -- "Speaker ������" 
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)    ��04)  
*****************************************************************************/
void Deal_Song_Tone_Speaker(void)  //�����ض��������ɶ�ӦƵ�ʵĲ���-- "Speaker ������"  
{
	DAC12_1DAT=*sin_data_pr++;   //���ɵ����Ҳ��� DAC��� 

	if (sin_data_pr >= &sin_table[10])   //ѭ��������Ҳ� 
	{
		sin_data_pr = &sin_table[0];
	}


	DAC12_1DAT &= 0xFFF;      // ���ݱ���   // Modulo 4096

	TA1CCR0 += period_table[song_tone_table[key]];//��ʱ�� ��ʱĳ���������������� 
}


/****************************************************************************
*������-Function:	void Deal_Song_Beat_Speaker(void)
*����- Description:		���Ʋ��Ÿ����������ͽ��� -- "Speaker ������" 
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)    ��04)  
*****************************************************************************/
void Deal_Song_Beat_Speaker(void) //���Ʋ��Ÿ����������ͽ��� -- "Speaker ������" 
{
	if(k++ == song_long_table[m])  //�ñ���k�ǽ���ʱ�� 
	{
		k = 0;
		if(++m == 24) m = 0; //��24����������,��������,�ط� 
	
		DAC12_1DAT = 0x000;	 //�����������ͣ�� 
		TA1CCTL0 &=~ CCIE;
		
		if(++n == 1)		   //��һ������ 
		{
			n = 0;
			TA1CCTL0 = CCIE;
			TA1CCR0 = period_table[song_tone_table[key++]]; //��һ���������������� 
			if(key == 48) key = 0;	 //���������ط� 
		}
	}

}


/****************************************************************************
*������-Function:	void Mic_Record_Speaker_Play(void)
*����- Description:		��˷�¼����ͨ��DMA ����DACͨ������������
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)    ��04)  
*****************************************************************************/
void Mic_Record_Speaker_Play(void) //��˷�¼����ͨ��DMA ����DACͨ������������
{
	P7SEL |=BIT6;  //Microphone AD��  //P7.6-->AD14

	P5DIR |= BIT6;     //P5.6�ӵ�Speaker �Ŵ���ʹ�ܿ�
	P5OUT &= ~BIT6;    //P5.6�����ʱ���������ſ��Թ���

	ADC12CTL0 = ADC12ON+ADC12SHT0_5+ADC12MSC;
	ADC12CTL1 = ADC12CSTARTADD_14+ADC12SHP+ADC12SSEL_0+ADC12CONSEQ_2;                     // Use sampling timer
	ADC12MCTL14 = ADC12INCH_14;                 
	ADC12CTL0 |= ADC12ENC;

	DAC12_1CTL0 = DAC12IR+DAC12SREF_1 + DAC12AMP_7 + DAC12ENC + DAC12CALON+ DAC12OPS;

	DMACTL0 |= DMA0TSEL3 + DMA0TSEL4;
   	DMA0SA = 0x073Cu;//&ADC12MEM14;                                                                                                                                                                                                                                                                                                                                                                                                                         	DMA0SA = 0x073Cu;//&ADC12MEM14;
	DMA0DA = 0x0794u;//&DAC12_1DAT;
	DMA0SZ = 1;
	DMA0CTL |= DMADT2 + DMAEN;

	ADC12CTL0 |= ADC12SC;
 
}





/****************************************************************************
*������-Function:	void Open_Timing_In_Work(unsigned long TimeValue)  
*����- Description:		�򿪷�����(Speaker ������)�Ķ�ʱ��		
*�������-Input:	timeValue: ��ʱ��ʱ��ֵ(ʱ��Ϊ1ms)
*�������-output:	None
*ע������-Note��	
	��01)  ���ж��У��Զ�ʱʱ������������еݼ�   
	��02)  ��ʱ�����Զ���"��ʱ��־λ"	  
	��03)    ��04)  
*****************************************************************************/
void Open_Buzz_Speaker(unsigned long timeValue)  //�򿪷�����(Speaker ������)�Ķ�ʱ��	
{

	Initial_Buzz_Speaker();  //��ʼ������:	������ -- "Speaker ������" 
	G_Timing_Speaker_Cnt = timeValue;	//��ʱ(ʱ��Ϊ1ms)//���Լ�����������ֵ
	F_StartSpeaker = 1; //�������÷�����(Speaker ������)	 //��ʱ�����Զ���˱�־λ	 

}






/****************************************************************************
*������-Function:	void Initial_Buzz_Speaker(void)
*����- Description: 	��ʼ������:  ������ -- "Speaker ������" 
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)		��02)		��03)	 ��04)	
*****************************************************************************/
void Initial_Buzz_Speaker(void)  //��ʼ������:  ������ -- "Speaker ������" 
{
	unsigned char j = 0;
	double i = 0;
	
	for(j=0;j<10;j++)   //�������Ҳ����� 
	{
		i+=PI/5;
		sin_table[j]=(int)((sin(i)+1)*2048);
	}
	sin_data_pr=&sin_table[0];
	
	for(j=0;j<20;j++)  //�������׵�Ƶ�ʼ��������� 
	{
		period_table[j]=(int)(300000/key_table[j]);
	}
	
		//AVcc��Ϊ�ο���ѹ����ʼ��ƫ����У�����˿�p7.6��� 
	DAC12_1CTL0 = DAC12IR + DAC12SREF_1 + DAC12AMP_5 + DAC12ENC + DAC12CALON+DAC12OPS;

	P5DIR |= BIT6;     //P5.6�ӵ�Speaker �Ŵ���ʹ�ܿ�
	P5OUT &= ~BIT6;    //P5.6�����ʱ���������ſ��Թ���

	TA1CCTL0 = CCIE;	  // CCR0�ж�ʹ��  // CCR0 interrupt enabled

	TA1CCR0 = period_table[0];  // ��ʱΪ��һ���������������� 

		// SMCLK+���ϼ���+��TAR +��ʱ���ж�
	TA1CTL = TASSEL_2 + MC_2 + TACLR +TAIE; 		// SMCLK, upmode, clear TAR

}




/****************************************************************************
*������-Function:	void Deal_Buzz_Speaker(void)
*����- Description:		��������� -- "Speaker ������" 
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)    ��04)  
*****************************************************************************/
void Deal_Buzz_Speaker(void)  //��������� -- "Speaker ������" 
{
	DAC12_1DAT = *sin_data_pr++;   //���ɵ����Ҳ��� DAC��� 

	if (sin_data_pr >= &sin_table[10])   //ѭ��������Ҳ� 
	{
		sin_data_pr = &sin_table[0];
	}


	DAC12_1DAT &= 0xFFF;      // ���ݱ���   // Modulo 4096
				//7��ʾ������"Do"
	TA1CCR0 += period_table[7];//��ʱ�� ��ʱĳ���������������� 
}



/****************************************************************************
*������-Function:	void Check_Buzz_Speaker(void)
*����- Description:		���ж������Ƿ����: ������ -- "Speaker ������" (����:���úͱ�����)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01)���������ж�����1msΪ��λ��  
	��02)//care �ŵ��ж���ȥ��ʵʱ�ԱȽϺã��͸�������ʾһ������������ıȽϾ��� 
	��03)    ��04)  
*****************************************************************************/
void Check_Buzz_Speaker(void)   //���ж������Ƿ����: ������ -- "Speaker ������" (����:���úͱ�����)
{
	if(F_StartSpeaker)  //Ϊ1�������÷�������//�˱�־λ�����󣬵�ʱ�䵽���Զ���0
	{
		G_Timing_Speaker_Cnt --;
		if(G_Timing_Speaker_Cnt == 0)
		{
			F_StartSpeaker = 0;
			
			if(G_WorkState != WORK_Speaker_Test)
			{
					//�ط�����
				Disable_Speaker(); //��ֹ:	"Speaker ������" 
			}
		}
	}
}



