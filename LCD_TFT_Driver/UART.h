/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 UART.h
* �����ļ�-Dependencies:  	 None	
* �ļ�����-File Description:	 ( ͷ�ļ�-Header File )
	�� "UART ͨ���첽����/����װ��" -��������(�ڲ���Դ)-ͷ�ļ�
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

#ifndef  __UART_H 
#define  __UART_H 

#include "msp430F6638.h"
#include "stdio.h"

////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"�궨��**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////


/***********************
//���²�����Ҫ�û�����
#define UART_TXBUFSIZE      16                //����FIFO����
#define UART_RXBUFSIZE      16                //����FIFO����
#define UART_MODULE         UART_UCA0         //SPIͨ�Žӿ�ѡ�õ�ģ��

//���²����û������޸�
#define F_ACLK              (32768)
#define UART_UCA0           (0)
#define UART_UCA1           (1)


#if   (UART_MODULE == UART_UCA0)
  #define UART_TXD_PORT       P8OUT           //����TXD  ->  P8.2
  #define UART_TXD_DIR        P8DIR
  #define UART_TXD_SEL        P8SEL
  #define UART_TXD_PIN        BIT2
  
  #define UART_RXD_PORT       P8OUT           //����RXD  ->  P8.3
  #define UART_RXD_DIR        P8DIR
  #define UART_RXD_SEL        P8SEL
  #define UART_RXD_PIN        BIT3

  #define USCI_Ax_VECTOR      USCI_A0_VECTOR
  #define UCAxCTL0            UCA0CTL0
  #define UCAxCTL1            UCA0CTL1
  #define UCAxBRW             UCA0BRW
  #define UCAxMCTL            UCA0MCTL
  #define UCAxIFG             UCA0IFG
  #define UCAxIE              UCA0IE
  #define UCAxIV              UCA0IV
  #define UCAxTXBUF           UCA0TXBUF
  #define UCAxRXBUF           UCA0RXBUF
  #define UCAxSTAT            UCA0STAT
#elif (UART_MODULE == UART_UCA1)
  #define UART_TXD_PORT       P4OUT           //����TXD  ->  P4.4
  #define UART_TXD_DIR        P4DIR
  #define UART_TXD_SEL        P4SEL
  #define UART_TXD_PIN        BIT4
  
  #define UART_RXD_PORT       P4OUT           //����RXD  ->  P4.5
  #define UART_RXD_DIR        P4DIR
  #define UART_RXD_SEL        P4SEL
  #define UART_RXD_PIN        BIT5

  #define USCI_Ax_VECTOR      USCI_A1_VECTOR
  #define UCAxCTL0            UCA1CTL0
  #define UCAxCTL1            UCA1CTL1
  #define UCAxBRW             UCA1BRW
  #define UCAxMCTL            UCA1MCTL
  #define UCAxIFG             UCA1IFG
  #define UCAxIE              UCA1IE
  #define UCAxIV              UCA1IV
  #define UCAxTXBUF           UCA1TXBUF
  #define UCAxRXBUF           UCA1RXBUF
  #define UCAxSTAT            UCA1STAT
#endif
**********************/


////////////////////////////////////////////////////////////////////////////
//==**��Ŀ"ר��"�궨��**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
  
extern unsigned char G_RxData_IrDA;  //���� "IrDA_UART  ���⴮��ͨ��"���յ�������

extern unsigned char G_RxData_RS232; //���� "RS232_UART   ����ͨ��"���յ�������

extern unsigned char G_RxData_RS485; //���� "RS485_UART   ����ͨ��"���յ�������



////////////////////////////////////////////////////////////////////////////
//==**"����"�궨��**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"����"�궨��**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"��������**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////

//�ⲿ��������
//extern char UART_Init(long int Baud,char Parity,char DataBits,char StopBits);
//extern char UART_PutChar(unsigned char Chr);
//extern char UART_GetChar(unsigned char *Chr);
//extern unsigned int UART_GetCharsInRxBuf(void);
//extern void UART_ClrRxBuf(void);
//extern char UART_IsTxEmpty(void);


///////////////////////////////////////////////////////////////////////////

extern void Disable_UART_A(void); //����UART_A ģ��

extern void Send_OneByte_UART_A(unsigned char byte); //UART_A ����һ���ֽ�����--"UART_A ͨ���첽����/����װ��"


extern void Send_String_UART_A(unsigned char *txArray);  //UART_A �����ַ���--"UART_Aͨ���첽����/����װ��"




////////////////////////////////////////////////////////////////////////////
//==**"�ⲿ" API ��������**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

extern void Initial_IrDA_UART(void);  //��ʼ������:  "IrDA_UART  ���⴮��ͨ��"
extern void Deal_IrDA_UART(void);   //���� "IrDA_UART  ���⴮��ͨ��"


extern void Initial_RS232_UART(void);  //��ʼ������:  "RS232_UART  ����ͨ��"
extern void Deal_RS232_UART(void); //���� "RS232 ����ͨ��"


extern void Initial_RS485_UART(void); //��ʼ������:  "RS485_UART  ����ͨ��"
extern void Sent_OneByte_RS485_UART(unsigned char byte); //RS485ͨ��UART����һ���ֽ�����



#endif   /* __UART_H  */





