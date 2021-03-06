/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 I2C.c
* 附属文件-Dependencies:  	 I2C.h; msp430f6638.h; Hardware_Profile.h; Generic.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■  "I2C" -驱动程序-(处理器内部资源) 
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



#include "Generic.h"	//常用程序编程规范、函数集 -头文件-Generic Type Definitions

#include "Hardware_Profile.h"  //处理器"硬件配置文件" -Hardware specific definitions for Processor


#include "msp430f6638.h"   // "处理器"头文件: 内部寄存相关定义等(处理器内部资源) 

#include "I2C.h"   //"I2C" -驱动程序-头文件(处理器内部资源) 


////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////

/****************************************************************************
*函数名-Function:	void  I2C_B_Initial(unsigned char slaveAddress)
*描述- Description:		I2C_B 内部资源初始化
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)   	▲02)    ▲03)    ▲04)  
*****************************************************************************/
void  I2C_B_Initial(unsigned char slaveAddress)  //I2C_B 内部资源初始化
{
	//--care--一定要加上这个语句//"LCD_B 端口控制寄存器"相关配置
	LCDBPCTL0 = 0;


////////////////////////////////////////////////////////////////////////////
//==**模块IO端口初始化**===============================//

//--**P8.5 引脚: IIC_B_SDA (P8.5/UCB1SIMO/UCB1SDA/S10)** ----------------//
	mSelect_IIC_B_SDA_FunctionPin; //配置引脚为"外围模块功能"引脚
	mPullEnabled_IIC_B_SDA; //使能--上拉/下拉功能
	
//care -使能上拉/下拉后，还要配制P8OUT 来选择上拉或下拉
//此外，使能后，未设置是上拉或下拉
	
//--**P8.6引脚: IIC_B_SCK (P8.6/UCB1SOMI/UCB1SCL/S9)** ----------------//
	mSelect_IIC_B_SCK_FunctionPin; //配置引脚为"外围模块功能"引脚
	mPullEnabled_IIC_B_SCK; //使能--上拉/下拉功能
	mSetOut_IIC_B_SCK;  ////配置"IIC_B_SCK" 引脚为"输出"
//care -使能上拉/下拉后，还要配制P8OUT 来选择上拉或下拉
//此外，使能后，未设置是上拉或下拉



////////////////////////////////////////////////////////////////////////////
//==**IIC_B模块参数配置**===================================//

	////////////////////////////////////////////////////////////////////////////
	//--**先禁用IIC_B模块**----------------------------------------------//
	UCB1CTL1 |= UCSWRST;  // Put state machine in reset
		//UCSWRST 使能软件复位。//1 使能，USCI逻辑保持在复位状态。//0 禁止。USCI复位释放�

    UCB1CTL0 = UCMST + UCMODE_3 + UCSYNC;  // 选择作为I2C主机，同步模式// I2C Master, synchronous mode
    UCB1CTL1 = UCSSEL_2 + UCSWRST;   // 采用SMCLK，保持SW复位	// Use SMCLK, keep SW reset
//UCB1BR0 = 12;           // fSCL = SMCLK/12 =4M/12= 333kHz
	UCB1BR0 = 36;	  // fSCL = SMCLK/12 =12M/36= 333kHz

    UCB1BR1 = 0;
    UCB1I2CSA = slaveAddress;      // 设置从机地址// Set Slave Address 
    UCB1CTL1 &= ~UCSWRST;     // 清除SW复位	// Clear SW reset, resume operation 	
}




/****************************************************************************
*函数名-Function:	unsigned int Read_Word_IIC_B(unsigned char Address)
*描述- Description:		通过IIC_B 读数据(一个字)，
*输入参数-Input:	Address: 模块内部地址
*输出参数-output:	rxData: 读到的数据
*注意事项-Note：	▲01)   	▲02)    ▲03)    ▲04)  
************************************************************
unsigned int Read_Word_IIC_B(unsigned char address) //通过IIC_B 读数据(一个字)
{
	unsigned int rxData = 0;  //IIC 读到的数据

	I2C_IFG &= ~I2C_RX_IFG;
    while(I2C_CTL1 & STOP);            // 等待总线空闲

    I2C_CTL1 |= START+UCTR;            // 发送模式

    TXBUF  = address;                      // 发送字地址
    while(!(I2C_IFG & I2C_TX_IFG));   // 等待字地址发送完毕

    I2C_CTL1 &= ~UCTR;                 // 读模式
    while(I2C_CTL1 & STOP);
    I2C_CTL1 |= START;                 // 发送START

    while( !(I2C_IFG & I2C_RX_IFG));  // 等待从机返回数据
    rxData = RXBUF << 8;
    while( !(I2C_IFG & I2C_RX_IFG));  //等待从机返回数据
    rxData += RXBUF;

    UCB1CTL1 |=UCTXNACK;              // 发送停止位和NACK位
    UCB1CTL1 |=UCTXSTP;

	return (rxData);
}

*****************/



/****************************************************************************
*函数名-Function:	unsigned int Read_Word_IIC_B(unsigned char Address)
*描述- Description:		通过IIC_B 读数据(一个字)，
*输入参数-Input:	Address: 模块内部地址
*输出参数-output:	rxData: 读到的数据
*注意事项-Note：	
	▲01) 对于TMP006  先接收到的字节为高字节(字)
	▲02)  对于BQ27410  先接收到的字节为低字节(字)  
	▲03)    ▲04)  
*****************************************************************************/
unsigned int Read_Word_IIC_B(unsigned char address) //通过IIC_B 读数据(一个字)
{
	unsigned int rxData = 0;  //IIC 读到的数据
	unsigned int Cnt = 0;  //

	I2C_IFG &= ~I2C_RX_IFG;

	Cnt = 0;  //
    while(I2C_CTL1 & STOP)
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // 等待总线空闲            
    }


    I2C_CTL1 |= START+UCTR;            // 发送模式

    TXBUF  = address;                      // 发送字地址
   
	Cnt = 0;  //
    while(!(I2C_IFG & I2C_TX_IFG))   // 等待字地址发送完毕
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // 等待总线空闲            
    }


    I2C_CTL1 &= ~UCTR;                 // 读模式

	Cnt = 0;  //
    while(I2C_CTL1 & STOP)
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // 等待总线空闲            
    }
    
    I2C_CTL1 |= START;                 // 发送START

    
	Cnt = 0;  //
    while( !(I2C_IFG & I2C_RX_IFG))  // 等待从机返回数据
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // 等待总线空闲            
    }
	
    rxData = RXBUF << 8;

	Cnt = 0;  //
    while( !(I2C_IFG & I2C_RX_IFG))  //等待从机返回数据
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // 等待总线空闲            
    }
	
    rxData += RXBUF;

    UCB1CTL1 |=UCTXNACK;              // 发送停止位和NACK位
    UCB1CTL1 |=UCTXSTP;

	return (rxData);
}




/****************************************************************************
*函数名-Function:	void Write_Word_IIC_B(u8 cmd,u8 data1,u8 data2)
*描述- Description:		通过IIC_B 向从机的某个寄存器写一个字
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01) 写一个字时，对于BQ27410  先写的字节为低字节data1(低地址)  
	           例:Write_Word_IIC_B(0x00,0x0c,0x00); //指向地址0x00写入一个字(值为0x000C)
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Write_Word_IIC_B(u8 cmd,u8 data1,u8 data2) //通过IIC_B 向从机的某个寄存器写一个字
{
	unsigned int Cnt = 0;  //

	

    I2C_CTL1 |= START + UCTR;          //发送模式             I2C TX, start condition


	Cnt = 0;  //
    TXBUF  = cmd;                      // 发送字地址
    while(!(I2C_IFG & I2C_TX_IFG))   // 等待字地址发送完毕
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // 等待总线空闲            
    }

	Cnt = 0;  //
    TXBUF  = data1;                      // 发送字地址
    while(!(I2C_IFG & I2C_TX_IFG))   // 等待字地址发送完毕
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // 等待总线空闲            
    }

	Cnt = 0;  //
    TXBUF  = data2;                      // 发送字地址
    while(!(I2C_IFG & I2C_TX_IFG))   // 等待字地址发送完毕
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // 等待总线空闲            
    }



    while (UCB1CTL1 & UCTXSTP);             // Ensure stop condition got sent

}



/****************************************************************************
*函数名-Function:	void Write_Word_IIC_B(u8 cmd,u8 data1,u8 data2)
*描述- Description:		通过IIC_B 向从机的某个寄存器写一个字
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)   	▲02)    ▲03)    ▲04)  
***********************************************************
void Write_Word_IIC_B(u8 cmd,u8 data1,u8 data2) //通过IIC_B 向从机的某个寄存器写一个字
{
	TxData[2]=cmd;
    TxData[1]=data1;
    TxData[0]=data2;
    TXByteCtr=3;                       // Load TX byte counter
	

	UCB1IE |= UCTXIE;                  // Enable TX interrupt

	flag = 2;

    I2C_CTL1 |= START + UCTR;          //发送模式             I2C TX, start condition

    while (UCB1CTL1 & UCTXSTP);             // Ensure stop condition got sent

}






//------------------------------------------------------------------------------
// The USCIAB0TX_ISR is structured such that it can be used to transmit any
// number of bytes by pre-loading TXByteCtr with the byte count. Also, TXData
// points to the next byte to transmit.
//------------------------------------------------------------------------------
#pragma vector = USCI_B1_VECTOR
__interrupt void USCI_B1_ISR(void)
{
  switch(__even_in_range(UCB1IV,12))
  {
  case  0: break;                           // Vector  0: No interrupts
  case  2: break;                           // Vector  2: ALIFG
  case  4: break;                           // Vector  4: NACKIFG
  case  6: break;                           // Vector  6: STTIFG
  case  8: break;                           // Vector  8: STPIFG
  case 10: break;                           // Vector 10: RXIFG
  case 12:                                  // Vector 12: TXIFG

   if(flag==1)
    {
        if (TXByteCtr)                            // Check TX byte counter
         {
           TXByteCtr--;
           TXBUF =TxData[TXByteCtr];                 // Load TX buffer                               // Decrement TX byte counter
         }
        else
         {
    	    UCB1CTL1 |=UCTXSTP;               // 发送停止位UCB0CTL1 |= UCTXSTP;                    // I2C stop condition
    	    UCB1IFG&=~I2C_TX_IFG ;                     // Clear USCI_B0 TX int flag
            //IE2 &=~UCB0TXIE;
// __bic_SR_register_on_exit(LPM0_bits); // Exit LPM0__bic_SR_register_on_exit(CPUOFF);      // Exit LPM0
            flag=0;
         }
   }
   if(flag==2)
   {
       if (TXByteCtr)                            // Check TX byte counter
        {
          TXByteCtr--;
          TXBUF =TxData[TXByteCtr];                 // Load TX buffer                               // Decrement TX byte counter
        }
       else
        {
   	    UCB1CTL1 |=UCTXSTP;               // 发送停止位UCB0CTL1 |= UCTXSTP;                    // I2C stop condition
   	    UCB1IFG&=~I2C_TX_IFG ;                     // Clear USCI_B0 TX int flag
           //IE2 &=~UCB0TXIE;
//__bic_SR_register_on_exit(LPM0_bits); // Exit LPM0__bic_SR_register_on_exit(CPUOFF);      // Exit LPM0
           flag=0;
        }
   }

  default: break;
  }
}

******************/




