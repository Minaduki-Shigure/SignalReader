/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 UART.c
* 附属文件-Dependencies:  	 UART.h; msp430f6638.h;
                                                        Hardware_Profile.h; Generic.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■ "UART 通用异步接收/发送装置" -驱动程序(内部资源)
	01) 通用串行通信接口(USCI)带有一个硬件模块，支持多种串行通信模式。
	02) 通用串行通信接口(USCI)模块支持多种串行通信模式。不同
的 USCI 模块支持不同的模式。不同 USCI模块名称中含有不同的字母。
例如，USCI_A不同于 USCI_B，等等。如果同一芯片中有 1个以上相同
的USCI模块，以递增的数字命名这些模块。例如，如果 1 个芯片有
两个 USCI_A 模块，可将它们命名为 USCI_A0和USCI_A1。可以参阅具体
芯片的数据手册来确定芯片上含有的 USCI模块。 

	USCI_Ax模块支持： 
		(1) UART模式 
		(2) IrDA通信的脉冲整形 
		(3) LIN通信的自动波特率检测 
		(4) SPI模式 
	USCI_Bx模块支持： 
		(1) IIC模式 
		(2) SPI模式 
	03)    04)    05)    06)	
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

#include "Generic.h"	//常用程序编程规范、函数集 -头文件-Generic Type Definitions

#include "Hardware_Profile.h"  //处理器"硬件配置文件" -Hardware specific definitions for Processor



#include "msp430f6638.h"   // "处理器"头文件: 内部寄存相关定义等(处理器内部资源) 

#include "UART.h"   //"UART 通用异步接收/发送装置" -驱动程序(内部资源)-头文件



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////



/****************************************************************************
*函数名-Function:	void Disable_UART_A(void)
*描述- Description:		禁用UART_A 模块
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note： ▲01)	▲02) 	▲03) 	▲04)  
*****************************************************************************/
void Disable_UART_A(void) //禁用UART_A 模块
{

	UCA1IE &=~UCRXIE;	//禁止" 接收中断"  // Disable USCI_A0 RX interrupt
}


/****************************************************************************
*函数名-Function:	void Send_OneByte_UART_A(void)
*描述- Description:		UART_A 发送一个字节数据--"UART_A 通用异步接收/发送装置"
*输入参数-Input:	byte:  要发送的字节数据
*输出参数-output:	None
*注意事项-Note： ▲01)	▲02) 	▲03) 	▲04)  
*****************************************************************************/
void Send_OneByte_UART_A(unsigned char byte) //UART_A 发送一个字节数据--"UART _A通用异步接收/发送装置"
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
*函数名-Function:	void Send_String_UART_A(unsigned char *txArray)
*描述- Description:		UART_A 发送字符串--"UART_A 通用异步接收/发送装置"
*输入参数-Input:	txArray: 要发送的字符串数组
*输出参数-output:	None
*注意事项-Note： ▲01)	▲02) 	▲03) 	▲04)  
*****************************************************************************/
void Send_String_UART_A(unsigned char *txArray)  //UART _A发送字符串--"UART_A通用异步接收/发送装置"
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
*函数名-Function:	void Initial_IrDA_UART(void)
*描述- Description:		初始化设置:  "IrDA_UART  红外串口通信"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Initial_IrDA_UART(void)  //初始化设置:  "IrDA_UART  红外串口通信"
{
//==**配置"A模块"多路复用器TS3A5017: 选择IN2 、IN1**==============//
	mConfig_TS3A5017_A_IN2(0);  //IN2 =0
	mConfig_TS3A5017_A_IN1(1);  //IN1 =1	 //选择s2


//care 下面语句一定要有，从SPI切到UART时
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
	 UCA1IE &=~UCRXIE;	//禁止" 接收中断"  // Disable USCI_A0 RX interrupt
	 
}


/****************************************************************************
*函数名-Function:	void Initial_RS232_UART(void)
*描述- Description:		初始化设置:  "RS232_UART  串口通信"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Initial_RS232_UART(void)  //初始化设置:  "RS232_UART  串口通信"
{
//==**配置"A模块"多路复用器TS3A5017: 选择IN2 、IN1**==============//
	mConfig_TS3A5017_A_IN2(1);	//IN2 =1
	mConfig_TS3A5017_A_IN1(0);	//IN1 =0	 //选择s3


//care 下面语句一定要有，从SPI切到UART时
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
*函数名-Function:	void Initial_RS485_UART(void)
*描述- Description:		初始化设置:  "RS485_UART  串口通信"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Initial_RS485_UART(void) //初始化设置:  "RS485_UART  串口通信"
{
//	P5DIR|=BIT6;
//	RE;    // 设置RS485芯片处于接收状态


//==**配置"A模块"多路复用器TS3A5017: 选择IN2 、IN1**==============//
	mConfig_TS3A5017_A_IN2(1);	//IN2 =1
	mConfig_TS3A5017_A_IN1(1);	//IN1 =1	 //选择s4


	//timer b

	//   TBCCTL0 = CCIE;                           // CCR0 interrupt enabled
	//   TBCCR0 = 16384;
	//   TBCTL = TBSSEL_1 + MC_1  + TBCLR;          // SMCLK, contmode, clear TBR


//care 下面语句一定要有，从SPI切到UART时
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












