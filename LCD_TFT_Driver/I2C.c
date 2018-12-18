/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 I2C.c
* �����ļ�-Dependencies:  	 I2C.h; msp430f6638.h; Hardware_Profile.h; Generic.h;
* �ļ�����-File Description:	 ( Դ����-Source File) 
	��  "I2C" -��������-(�������ڲ���Դ) 
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


#include "msp430f6638.h"   // "������"ͷ�ļ�: �ڲ��Ĵ���ض����(�������ڲ���Դ) 

#include "I2C.h"   //"I2C" -��������-ͷ�ļ�(�������ڲ���Դ) 


////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////

/****************************************************************************
*������-Function:	void  I2C_B_Initial(unsigned char slaveAddress)
*����- Description:		I2C_B �ڲ���Դ��ʼ��
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)   	��02)    ��03)    ��04)  
*****************************************************************************/
void  I2C_B_Initial(unsigned char slaveAddress)  //I2C_B �ڲ���Դ��ʼ��
{
	//--care--һ��Ҫ����������//"LCD_B �˿ڿ��ƼĴ���"�������
	LCDBPCTL0 = 0;


////////////////////////////////////////////////////////////////////////////
//==**ģ��IO�˿ڳ�ʼ��**===============================//

//--**P8.5 ����: IIC_B_SDA (P8.5/UCB1SIMO/UCB1SDA/S10)** ----------------//
	mSelect_IIC_B_SDA_FunctionPin; //��������Ϊ"��Χģ�鹦��"����
	mPullEnabled_IIC_B_SDA; //ʹ��--����/��������
	
//care -ʹ������/�����󣬻�Ҫ����P8OUT ��ѡ������������
//���⣬ʹ�ܺ�δ����������������
	
//--**P8.6����: IIC_B_SCK (P8.6/UCB1SOMI/UCB1SCL/S9)** ----------------//
	mSelect_IIC_B_SCK_FunctionPin; //��������Ϊ"��Χģ�鹦��"����
	mPullEnabled_IIC_B_SCK; //ʹ��--����/��������
	mSetOut_IIC_B_SCK;  ////����"IIC_B_SCK" ����Ϊ"���"
//care -ʹ������/�����󣬻�Ҫ����P8OUT ��ѡ������������
//���⣬ʹ�ܺ�δ����������������



////////////////////////////////////////////////////////////////////////////
//==**IIC_Bģ���������**===================================//

	////////////////////////////////////////////////////////////////////////////
	//--**�Ƚ���IIC_Bģ��**----------------------------------------------//
	UCB1CTL1 |= UCSWRST;  // Put state machine in reset
		//UCSWRST ʹ�������λ��//1 ʹ�ܣ�USCI�߼������ڸ�λ״̬��//0 ��ֹ��USCI��λ�ͷš

    UCB1CTL0 = UCMST + UCMODE_3 + UCSYNC;  // ѡ����ΪI2C������ͬ��ģʽ// I2C Master, synchronous mode
    UCB1CTL1 = UCSSEL_2 + UCSWRST;   // ����SMCLK������SW��λ	// Use SMCLK, keep SW reset
//UCB1BR0 = 12;           // fSCL = SMCLK/12 =4M/12= 333kHz
	UCB1BR0 = 36;	  // fSCL = SMCLK/12 =12M/36= 333kHz

    UCB1BR1 = 0;
    UCB1I2CSA = slaveAddress;      // ���ôӻ���ַ// Set Slave Address 
    UCB1CTL1 &= ~UCSWRST;     // ���SW��λ	// Clear SW reset, resume operation 	
}




/****************************************************************************
*������-Function:	unsigned int Read_Word_IIC_B(unsigned char Address)
*����- Description:		ͨ��IIC_B ������(һ����)��
*�������-Input:	Address: ģ���ڲ���ַ
*�������-output:	rxData: ����������
*ע������-Note��	��01)   	��02)    ��03)    ��04)  
************************************************************
unsigned int Read_Word_IIC_B(unsigned char address) //ͨ��IIC_B ������(һ����)
{
	unsigned int rxData = 0;  //IIC ����������

	I2C_IFG &= ~I2C_RX_IFG;
    while(I2C_CTL1 & STOP);            // �ȴ����߿���

    I2C_CTL1 |= START+UCTR;            // ����ģʽ

    TXBUF  = address;                      // �����ֵ�ַ
    while(!(I2C_IFG & I2C_TX_IFG));   // �ȴ��ֵ�ַ�������

    I2C_CTL1 &= ~UCTR;                 // ��ģʽ
    while(I2C_CTL1 & STOP);
    I2C_CTL1 |= START;                 // ����START

    while( !(I2C_IFG & I2C_RX_IFG));  // �ȴ��ӻ���������
    rxData = RXBUF << 8;
    while( !(I2C_IFG & I2C_RX_IFG));  //�ȴ��ӻ���������
    rxData += RXBUF;

    UCB1CTL1 |=UCTXNACK;              // ����ֹͣλ��NACKλ
    UCB1CTL1 |=UCTXSTP;

	return (rxData);
}

*****************/



/****************************************************************************
*������-Function:	unsigned int Read_Word_IIC_B(unsigned char Address)
*����- Description:		ͨ��IIC_B ������(һ����)��
*�������-Input:	Address: ģ���ڲ���ַ
*�������-output:	rxData: ����������
*ע������-Note��	
	��01) ����TMP006  �Ƚ��յ����ֽ�Ϊ���ֽ�(��)
	��02)  ����BQ27410  �Ƚ��յ����ֽ�Ϊ���ֽ�(��)  
	��03)    ��04)  
*****************************************************************************/
unsigned int Read_Word_IIC_B(unsigned char address) //ͨ��IIC_B ������(һ����)
{
	unsigned int rxData = 0;  //IIC ����������
	unsigned int Cnt = 0;  //

	I2C_IFG &= ~I2C_RX_IFG;

	Cnt = 0;  //
    while(I2C_CTL1 & STOP)
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // �ȴ����߿���            
    }


    I2C_CTL1 |= START+UCTR;            // ����ģʽ

    TXBUF  = address;                      // �����ֵ�ַ
   
	Cnt = 0;  //
    while(!(I2C_IFG & I2C_TX_IFG))   // �ȴ��ֵ�ַ�������
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // �ȴ����߿���            
    }


    I2C_CTL1 &= ~UCTR;                 // ��ģʽ

	Cnt = 0;  //
    while(I2C_CTL1 & STOP)
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // �ȴ����߿���            
    }
    
    I2C_CTL1 |= START;                 // ����START

    
	Cnt = 0;  //
    while( !(I2C_IFG & I2C_RX_IFG))  // �ȴ��ӻ���������
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // �ȴ����߿���            
    }
	
    rxData = RXBUF << 8;

	Cnt = 0;  //
    while( !(I2C_IFG & I2C_RX_IFG))  //�ȴ��ӻ���������
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // �ȴ����߿���            
    }
	
    rxData += RXBUF;

    UCB1CTL1 |=UCTXNACK;              // ����ֹͣλ��NACKλ
    UCB1CTL1 |=UCTXSTP;

	return (rxData);
}




/****************************************************************************
*������-Function:	void Write_Word_IIC_B(u8 cmd,u8 data1,u8 data2)
*����- Description:		ͨ��IIC_B ��ӻ���ĳ���Ĵ���дһ����
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) дһ����ʱ������BQ27410  ��д���ֽ�Ϊ���ֽ�data1(�͵�ַ)  
	           ��:Write_Word_IIC_B(0x00,0x0c,0x00); //ָ���ַ0x00д��һ����(ֵΪ0x000C)
	��02)    ��03)    ��04)  
*****************************************************************************/
void Write_Word_IIC_B(u8 cmd,u8 data1,u8 data2) //ͨ��IIC_B ��ӻ���ĳ���Ĵ���дһ����
{
	unsigned int Cnt = 0;  //

	

    I2C_CTL1 |= START + UCTR;          //����ģʽ             I2C TX, start condition


	Cnt = 0;  //
    TXBUF  = cmd;                      // �����ֵ�ַ
    while(!(I2C_IFG & I2C_TX_IFG))   // �ȴ��ֵ�ַ�������
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // �ȴ����߿���            
    }

	Cnt = 0;  //
    TXBUF  = data1;                      // �����ֵ�ַ
    while(!(I2C_IFG & I2C_TX_IFG))   // �ȴ��ֵ�ַ�������
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // �ȴ����߿���            
    }

	Cnt = 0;  //
    TXBUF  = data2;                      // �����ֵ�ַ
    while(!(I2C_IFG & I2C_TX_IFG))   // �ȴ��ֵ�ַ�������
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // �ȴ����߿���            
    }



    while (UCB1CTL1 & UCTXSTP);             // Ensure stop condition got sent

}



/****************************************************************************
*������-Function:	void Write_Word_IIC_B(u8 cmd,u8 data1,u8 data2)
*����- Description:		ͨ��IIC_B ��ӻ���ĳ���Ĵ���дһ����
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)   	��02)    ��03)    ��04)  
***********************************************************
void Write_Word_IIC_B(u8 cmd,u8 data1,u8 data2) //ͨ��IIC_B ��ӻ���ĳ���Ĵ���дһ����
{
	TxData[2]=cmd;
    TxData[1]=data1;
    TxData[0]=data2;
    TXByteCtr=3;                       // Load TX byte counter
	

	UCB1IE |= UCTXIE;                  // Enable TX interrupt

	flag = 2;

    I2C_CTL1 |= START + UCTR;          //����ģʽ             I2C TX, start condition

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
    	    UCB1CTL1 |=UCTXSTP;               // ����ֹͣλUCB0CTL1 |= UCTXSTP;                    // I2C stop condition
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
   	    UCB1CTL1 |=UCTXSTP;               // ����ֹͣλUCB0CTL1 |= UCTXSTP;                    // I2C stop condition
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




