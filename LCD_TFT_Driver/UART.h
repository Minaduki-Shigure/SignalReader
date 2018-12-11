/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 UART.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■ "UART 通用异步接收/发送装置" -驱动程序(内部资源)-头文件
	01)     02)     03)    04)    05)    06)	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 注意事项-Attention : 	
	▲01)     ▲02)     ▲03)    ▲04)    ▲05)    ▲06)     
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
* 修改记录-Change History:   
	作者   时间        版本  内容描述
	Author 	 Date		   Rev      Comment
	-------------------------------------------------------------------------------
	BlueS	2012-12-12	  1.0	   
			xxxx-xx-xx	  x.x	   
			xxxx-xx-xx	  x.x				
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
* 公司-Company: 			CS-EMLAB  Co. , Ltd.
* 软件许可协议-Software License Agreement:
	Copyright (C) 2012-2020 	CS-EMLAB  Co. , Ltd.	All rights reserved.	

*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#ifndef  __UART_H 
#define  __UART_H 

#include "msp430F6638.h"
#include "stdio.h"

////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"宏定义**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////


/***********************
//以下部分需要用户配置
#define UART_TXBUFSIZE      16                //发送FIFO容量
#define UART_RXBUFSIZE      16                //接收FIFO容量
#define UART_MODULE         UART_UCA0         //SPI通信接口选用的模块

//以下部分用户请勿修改
#define F_ACLK              (32768)
#define UART_UCA0           (0)
#define UART_UCA1           (1)


#if   (UART_MODULE == UART_UCA0)
  #define UART_TXD_PORT       P8OUT           //定义TXD  ->  P8.2
  #define UART_TXD_DIR        P8DIR
  #define UART_TXD_SEL        P8SEL
  #define UART_TXD_PIN        BIT2
  
  #define UART_RXD_PORT       P8OUT           //定义RXD  ->  P8.3
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
  #define UART_TXD_PORT       P4OUT           //定义TXD  ->  P4.4
  #define UART_TXD_DIR        P4DIR
  #define UART_TXD_SEL        P4SEL
  #define UART_TXD_PIN        BIT4
  
  #define UART_RXD_PORT       P4OUT           //定义RXD  ->  P4.5
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
//==**项目"专用"宏定义**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
  
extern unsigned char G_RxData_IrDA;  //缓存 "IrDA_UART  红外串口通信"接收到的数据

extern unsigned char G_RxData_RS232; //缓存 "RS232_UART   串口通信"接收到的数据

extern unsigned char G_RxData_RS485; //缓存 "RS485_UART   串口通信"接收到的数据



////////////////////////////////////////////////////////////////////////////
//==**"函数"宏定义**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"函数"宏定义**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"函数声明**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////

//外部函数声明
//extern char UART_Init(long int Baud,char Parity,char DataBits,char StopBits);
//extern char UART_PutChar(unsigned char Chr);
//extern char UART_GetChar(unsigned char *Chr);
//extern unsigned int UART_GetCharsInRxBuf(void);
//extern void UART_ClrRxBuf(void);
//extern char UART_IsTxEmpty(void);


///////////////////////////////////////////////////////////////////////////

extern void Disable_UART_A(void); //禁用UART_A 模块

extern void Send_OneByte_UART_A(unsigned char byte); //UART_A 发送一个字节数据--"UART_A 通用异步接收/发送装置"


extern void Send_String_UART_A(unsigned char *txArray);  //UART_A 发送字符串--"UART_A通用异步接收/发送装置"




////////////////////////////////////////////////////////////////////////////
//==**"外部" API 函数声明**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

extern void Initial_IrDA_UART(void);  //初始化设置:  "IrDA_UART  红外串口通信"
extern void Deal_IrDA_UART(void);   //处理 "IrDA_UART  红外串口通信"


extern void Initial_RS232_UART(void);  //初始化设置:  "RS232_UART  串口通信"
extern void Deal_RS232_UART(void); //处理 "RS232 串口通信"


extern void Initial_RS485_UART(void); //初始化设置:  "RS485_UART  串口通信"
extern void Sent_OneByte_RS485_UART(unsigned char byte); //RS485通过UART发送一个字节数据



#endif   /* __UART_H  */





