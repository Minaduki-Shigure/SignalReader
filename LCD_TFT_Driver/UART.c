/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 UART.c
* �����ļ�-Dependencies:  	 UART.h; msp430f6638.h;
                                                        Hardware_Profile.h; Generic.h;
* �ļ�����-File Description:	 ( Դ����-Source File) 
	�� "UART ͨ���첽����/����װ��" -��������(�ڲ���Դ)
	01) ͨ�ô���ͨ�Žӿ�(USCI)����һ��Ӳ��ģ�飬֧�ֶ��ִ���ͨ��ģʽ��
	02) ͨ�ô���ͨ�Žӿ�(USCI)ģ��֧�ֶ��ִ���ͨ��ģʽ����ͬ
�� USCI ģ��֧�ֲ�ͬ��ģʽ����ͬ USCIģ�������к��в�ͬ����ĸ��
���磬USCI_A��ͬ�� USCI_B���ȵȡ����ͬһоƬ���� 1��������ͬ
��USCIģ�飬�Ե���������������Щģ�顣���磬��� 1 ��оƬ��
���� USCI_A ģ�飬�ɽ���������Ϊ USCI_A0��USCI_A1�����Բ��ľ���
оƬ�������ֲ���ȷ��оƬ�Ϻ��е� USCIģ�顣 

	USCI_Axģ��֧�֣� 
		(1) UARTģʽ 
		(2) IrDAͨ�ŵ��������� 
		(3) LINͨ�ŵ��Զ������ʼ�� 
		(4) SPIģʽ 
	USCI_Bxģ��֧�֣� 
		(1) IICģʽ 
		(2) SPIģʽ 
	03)    04)    05)    06)	
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



#include "msp430f6638.h"   // "������"ͷ�ļ�: �ڲ��Ĵ���ض����(�������ڲ���Դ) 

#include "UART.h"   //"UART ͨ���첽����/����װ��" -��������(�ڲ���Դ)-ͷ�ļ�



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////



/****************************************************************************
*������-Function:	void Disable_UART_A(void)
*����- Description:		����UART_A ģ��
*�������-Input:	None
*�������-output:	None
*ע������-Note�� ��01)	��02) 	��03) 	��04)  
*****************************************************************************/
void Disable_UART_A(void) //����UART_A ģ��
{

	UCA1IE &=~UCRXIE;	//��ֹ" �����ж�"  // Disable USCI_A0 RX interrupt
}


/****************************************************************************
*������-Function:	void Send_OneByte_UART_A(void)
*����- Description:		UART_A ����һ���ֽ�����--"UART_A ͨ���첽����/����װ��"
*�������-Input:	byte:  Ҫ���͵��ֽ�����
*�������-output:	None
*ע������-Note�� ��01)	��02) 	��03) 	��04)  
*****************************************************************************/
void Send_OneByte_UART_A(unsigned char byte) //UART_A ����һ���ֽ�����--"UART _Aͨ���첽����/����װ��"
{

	unsigned int Cnt = 0;
	
	
	Cnt = 0;  //
	while (!(UCA1IFG&UCTXIFG))
	{
		Cnt ++;  //
			if(Cnt > 50000) break;			  
	}

	
    UCA1TXBUF = byte;
}


/****************************************************************************
*������-Function:	void Send_String_UART_A(unsigned char *txArray)
*����- Description:		UART_A �����ַ���--"UART_A ͨ���첽����/����װ��"
*�������-Input:	txArray: Ҫ���͵��ַ�������
*�������-output:	None
*ע������-Note�� ��01)	��02) 	��03) 	��04)  
*****************************************************************************/
void Send_String_UART_A(unsigned char *txArray)  //UART _A�����ַ���--"UART_Aͨ���첽����/����װ��"
{
	unsigned int Cnt = 0;


	while(*txArray != 0)
	{
		Cnt = 0;  //
		while (!(UCA1IFG&UCTXIFG))
		{
			Cnt ++;  //
				if(Cnt > 50000) break;			  
		}

		UCA1TXBUF = *txArray;
		txArray ++;
	}
}



/****************************************************************************
*������-Function:	void Initial_IrDA_UART(void)
*����- Description:		��ʼ������:  "IrDA_UART  ���⴮��ͨ��"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)    ��04)  
*****************************************************************************/
void Initial_IrDA_UART(void)  //��ʼ������:  "IrDA_UART  ���⴮��ͨ��"
{
//==**����"Aģ��"��·������TS3A5017: ѡ��IN2 ��IN1**==============//
	mConfig_TS3A5017_A_IN2(0);  //IN2 =0
	mConfig_TS3A5017_A_IN1(1);  //IN1 =1	 //ѡ��s2


//care �������һ��Ҫ�У���SPI�е�UARTʱ
P8SEL &= ~BIT1; 
P8SEL |= 0X0C;
P8REN &= ~BIT3;   

UCA1CTL0 = UCMODE_0;
//UCA1CTL0 = UCCKPL + UCMSB + UCMST + UCMODE_0 + UCSYNC; 

UCA1CTL1 |= UCSWRST;		  // **Put state machine in reset**
UCA1CTL1 = UCSWRST + UCSSEL_1;		  // CLK = ACLK

	 UCA1BR0 = 0x03;			  // 32kHz/9600=3.41 (see User's Guide)
	 UCA1BR1 = 0x00;			  //
	 UCA1MCTL = UCBRS_3+UCBRF_0;  // Modulation UCBRSx=3, UCBRFx=0
	 UCA1CTL1 &= ~UCSWRST;		  // **Initialize USCI state machine**
	 UCA1IE &=~UCRXIE;	//��ֹ" �����ж�"  // Disable USCI_A0 RX interrupt
	 
}


/****************************************************************************
*������-Function:	void Initial_RS232_UART(void)
*����- Description:		��ʼ������:  "RS232_UART  ����ͨ��"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)    ��04)  
*****************************************************************************/
void Initial_RS232_UART(void)  //��ʼ������:  "RS232_UART  ����ͨ��"
{
//==**����"Aģ��"��·������TS3A5017: ѡ��IN2 ��IN1**==============//
	mConfig_TS3A5017_A_IN2(1);	//IN2 =1
	mConfig_TS3A5017_A_IN1(0);	//IN1 =0	 //ѡ��s3


//care �������һ��Ҫ�У���SPI�е�UARTʱ
P8SEL &= ~BIT1; 
P8SEL |= 0X0C;
P8REN &= ~BIT3;   

UCA1CTL0 = UCMODE_0;

UCA1CTL1 |= UCSWRST;		  // **Put state machine in reset**

UCA1CTL1 = UCSWRST + UCSSEL_1;		  // CLK = ACLK


	UCA1BR0 = 0x03;              // 32kHz/9600=3.41 (see User's Guide)
	UCA1BR1 = 0x00;              //
	UCA1MCTL = UCBRS_3+UCBRF_0;  // Modulation UCBRSx=3, UCBRFx=0
	UCA1CTL1 &= ~UCSWRST;        // **Initialize USCI state machine**
	UCA1IE |= UCRXIE;            // Enable USCI_A0 RX interrupt

}



/****************************************************************************
*������-Function:	void Initial_RS485_UART(void)
*����- Description:		��ʼ������:  "RS485_UART  ����ͨ��"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)    ��04)  
*****************************************************************************/
void Initial_RS485_UART(void) //��ʼ������:  "RS485_UART  ����ͨ��"
{
//	P5DIR|=BIT6;
//	RE;    // ����RS485оƬ���ڽ���״̬


//==**����"Aģ��"��·������TS3A5017: ѡ��IN2 ��IN1**==============//
	mConfig_TS3A5017_A_IN2(1);	//IN2 =1
	mConfig_TS3A5017_A_IN1(1);	//IN1 =1	 //ѡ��s4


	//timer b

	//   TBCCTL0 = CCIE;                           // CCR0 interrupt enabled
	//   TBCCR0 = 16384;
	//   TBCTL = TBSSEL_1 + MC_1  + TBCLR;          // SMCLK, contmode, clear TBR


//care �������һ��Ҫ�У���SPI�е�UARTʱ
P8SEL &= ~BIT1; 
P8SEL |= 0X0C;
P8REN &= ~BIT3;   

UCA1CTL0 = UCMODE_0;


UCA1CTL1 |= UCSWRST;		  // **Put state machine in reset**
UCA1CTL1 = UCSWRST + UCSSEL_1;		  // CLK = ACLK


	UCA1BR0 = 0x03;              // 32kHz/9600=3.41 (see User's Guide)
	UCA1BR1 = 0x00;              //
	UCA1MCTL = UCBRS_3+UCBRF_0;  // Modulation UCBRSx=3, UCBRFx=0
	UCA1CTL1 &= ~UCSWRST;        // **Initialize USCI state machine**
	UCA1IE |= UCRXIE;            // Enable USCI_A0 RX interrupt
}












