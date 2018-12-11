/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* ÎÄ¼şÃû-FileName:			 I2C.c
* ¸½ÊôÎÄ¼ş-Dependencies:  	 I2C.h; msp430f6638.h; Hardware_Profile.h; Generic.h;
* ÎÄ¼şÃèÊö-File Description:	 ( Ô´³ÌĞò-Source File) 
	¡ö  "I2C" -Çı¶¯³ÌĞò-(´¦ÀíÆ÷ÄÚ²¿×ÊÔ´) 
	01)     02)     03)    04)    05)    06)	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ×¢ÒâÊÂÏî-Attention : 	
	¡ø01)     ¡ø02)     ¡ø03)    ¡ø04)    ¡ø05)    ¡ø06)     
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
* ĞŞ¸Ä¼ÇÂ¼-Change History:   
	×÷Õß   Ê±¼ä        °æ±¾  ÄÚÈİÃèÊö
	Author 	 Date		   Rev      Comment
	-------------------------------------------------------------------------------
	BlueS	2012-12-12	  1.0	   
			xxxx-xx-xx	  x.x	   
			xxxx-xx-xx	  x.x				
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
* ¹«Ë¾-Company: 			CS-EMLAB  Co. , Ltd.
* Èí¼şĞí¿ÉĞ­Òé-Software License Agreement:
	Copyright (C) 2012-2020 	CS-EMLAB  Co. , Ltd.	All rights reserved.	

*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/



#include "Generic.h"	//³£ÓÃ³ÌĞò±à³Ì¹æ·¶¡¢º¯Êı¼¯ -Í·ÎÄ¼ş-Generic Type Definitions

#include "Hardware_Profile.h"  //´¦ÀíÆ÷"Ó²¼şÅäÖÃÎÄ¼ş" -Hardware specific definitions for Processor


#include "msp430f6638.h"   // "´¦ÀíÆ÷"Í·ÎÄ¼ş: ÄÚ²¿¼Ä´æÏà¹Ø¶¨ÒåµÈ(´¦ÀíÆ÷ÄÚ²¿×ÊÔ´) 

#include "I2C.h"   //"I2C" -Çı¶¯³ÌĞò-Í·ÎÄ¼ş(´¦ÀíÆ÷ÄÚ²¿×ÊÔ´) 


////////////////////////////////////////////////////////////////////////////
//==**È«¾Ö±äÁ¿¶¨Òå**Global variables**========================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**¾Ö²¿±äÁ¿¶¨Òå**Local variables**========================//
////////////////////////////////////////////////////////////////////////////

/****************************************************************************
*º¯ÊıÃû-Function:	void  I2C_B_Initial(unsigned char slaveAddress)
*ÃèÊö- Description:		I2C_B ÄÚ²¿×ÊÔ´³õÊ¼»¯
*ÊäÈë²ÎÊı-Input:	None
*Êä³ö²ÎÊı-output:	None
*×¢ÒâÊÂÏî-Note£º	¡ø01)   	¡ø02)    ¡ø03)    ¡ø04)  
*****************************************************************************/
void  I2C_B_Initial(unsigned char slaveAddress)  //I2C_B ÄÚ²¿×ÊÔ´³õÊ¼»¯
{
	//--care--Ò»¶¨Òª¼ÓÉÏÕâ¸öÓï¾ä//"LCD_B ¶Ë¿Ú¿ØÖÆ¼Ä´æÆ÷"Ïà¹ØÅäÖÃ
	LCDBPCTL0 = 0;


////////////////////////////////////////////////////////////////////////////
//==**Ä£¿éIO¶Ë¿Ú³õÊ¼»¯**===============================//

//--**P8.5 Òı½Å: IIC_B_SDA (P8.5/UCB1SIMO/UCB1SDA/S10)** ----------------//
	mSelect_IIC_B_SDA_FunctionPin; //ÅäÖÃÒı½ÅÎª"ÍâÎ§Ä£¿é¹¦ÄÜ"Òı½Å
	mPullEnabled_IIC_B_SDA; //Ê¹ÄÜ--ÉÏÀ­/ÏÂÀ­¹¦ÄÜ
	
//care -Ê¹ÄÜÉÏÀ­/ÏÂÀ­ºó£¬»¹ÒªÅäÖÆP8OUT À´Ñ¡ÔñÉÏÀ­»òÏÂÀ­
//´ËÍâ£¬Ê¹ÄÜºó£¬Î´ÉèÖÃÊÇÉÏÀ­»òÏÂÀ­
	
//--**P8.6Òı½Å: IIC_B_SCK (P8.6/UCB1SOMI/UCB1SCL/S9)** ----------------//
	mSelect_IIC_B_SCK_FunctionPin; //ÅäÖÃÒı½ÅÎª"ÍâÎ§Ä£¿é¹¦ÄÜ"Òı½Å
	mPullEnabled_IIC_B_SCK; //Ê¹ÄÜ--ÉÏÀ­/ÏÂÀ­¹¦ÄÜ
	mSetOut_IIC_B_SCK;  ////ÅäÖÃ"IIC_B_SCK" Òı½ÅÎª"Êä³ö"
//care -Ê¹ÄÜÉÏÀ­/ÏÂÀ­ºó£¬»¹ÒªÅäÖÆP8OUT À´Ñ¡ÔñÉÏÀ­»òÏÂÀ­
//´ËÍâ£¬Ê¹ÄÜºó£¬Î´ÉèÖÃÊÇÉÏÀ­»òÏÂÀ­



////////////////////////////////////////////////////////////////////////////
//==**IIC_BÄ£¿é²ÎÊıÅäÖÃ**===================================//

	////////////////////////////////////////////////////////////////////////////
	//--**ÏÈ½ûÓÃIIC_BÄ£¿é**----------------------------------------------//
	UCB1CTL1 |= UCSWRST;  // Put state machine in reset
		//UCSWRST Ê¹ÄÜÈí¼ş¸´Î»¡£//1 Ê¹ÄÜ£¬USCIÂß¼­±£³ÖÔÚ¸´Î»×´Ì¬¡£//0 ½ûÖ¹¡£USCI¸´Î»ÊÍ·Å¡

    UCB1CTL0 = UCMST + UCMODE_3 + UCSYNC;  // Ñ¡Ôñ×÷ÎªI2CÖ÷»ú£¬Í¬²½Ä£Ê½// I2C Master, synchronous mode
    UCB1CTL1 = UCSSEL_2 + UCSWRST;   // ²ÉÓÃSMCLK£¬±£³ÖSW¸´Î»	// Use SMCLK, keep SW reset
//UCB1BR0 = 12;           // fSCL = SMCLK/12 =4M/12= 333kHz
	UCB1BR0 = 36;	  // fSCL = SMCLK/12 =12M/36= 333kHz

    UCB1BR1 = 0;
    UCB1I2CSA = slaveAddress;      // ÉèÖÃ´Ó»úµØÖ·// Set Slave Address 
    UCB1CTL1 &= ~UCSWRST;     // Çå³ıSW¸´Î»	// Clear SW reset, resume operation 	
}




/****************************************************************************
*º¯ÊıÃû-Function:	unsigned int Read_Word_IIC_B(unsigned char Address)
*ÃèÊö- Description:		Í¨¹ıIIC_B ¶ÁÊı¾İ(Ò»¸ö×Ö)£¬
*ÊäÈë²ÎÊı-Input:	Address: Ä£¿éÄÚ²¿µØÖ·
*Êä³ö²ÎÊı-output:	rxData: ¶Áµ½µÄÊı¾İ
*×¢ÒâÊÂÏî-Note£º	¡ø01)   	¡ø02)    ¡ø03)    ¡ø04)  
************************************************************
unsigned int Read_Word_IIC_B(unsigned char address) //Í¨¹ıIIC_B ¶ÁÊı¾İ(Ò»¸ö×Ö)
{
	unsigned int rxData = 0;  //IIC ¶Áµ½µÄÊı¾İ

	I2C_IFG &= ~I2C_RX_IFG;
    while(I2C_CTL1 & STOP);            // µÈ´ı×ÜÏß¿ÕÏĞ

    I2C_CTL1 |= START+UCTR;            // ·¢ËÍÄ£Ê½

    TXBUF  = address;                      // ·¢ËÍ×ÖµØÖ·
    while(!(I2C_IFG & I2C_TX_IFG));   // µÈ´ı×ÖµØÖ··¢ËÍÍê±Ï

    I2C_CTL1 &= ~UCTR;                 // ¶ÁÄ£Ê½
    while(I2C_CTL1 & STOP);
    I2C_CTL1 |= START;                 // ·¢ËÍSTART

    while( !(I2C_IFG & I2C_RX_IFG));  // µÈ´ı´Ó»ú·µ»ØÊı¾İ
    rxData = RXBUF << 8;
    while( !(I2C_IFG & I2C_RX_IFG));  //µÈ´ı´Ó»ú·µ»ØÊı¾İ
    rxData += RXBUF;

    UCB1CTL1 |=UCTXNACK;              // ·¢ËÍÍ£Ö¹Î»ºÍNACKÎ»
    UCB1CTL1 |=UCTXSTP;

	return (rxData);
}

*****************/



/****************************************************************************
*º¯ÊıÃû-Function:	unsigned int Read_Word_IIC_B(unsigned char Address)
*ÃèÊö- Description:		Í¨¹ıIIC_B ¶ÁÊı¾İ(Ò»¸ö×Ö)£¬
*ÊäÈë²ÎÊı-Input:	Address: Ä£¿éÄÚ²¿µØÖ·
*Êä³ö²ÎÊı-output:	rxData: ¶Áµ½µÄÊı¾İ
*×¢ÒâÊÂÏî-Note£º	
	¡ø01) ¶ÔÓÚTMP006  ÏÈ½ÓÊÕµ½µÄ×Ö½ÚÎª¸ß×Ö½Ú(×Ö)
	¡ø02)  ¶ÔÓÚBQ27410  ÏÈ½ÓÊÕµ½µÄ×Ö½ÚÎªµÍ×Ö½Ú(×Ö)  
	¡ø03)    ¡ø04)  
*****************************************************************************/
unsigned int Read_Word_IIC_B(unsigned char address) //Í¨¹ıIIC_B ¶ÁÊı¾İ(Ò»¸ö×Ö)
{
	unsigned int rxData = 0;  //IIC ¶Áµ½µÄÊı¾İ
	unsigned int Cnt = 0;  //

	I2C_IFG &= ~I2C_RX_IFG;

	Cnt = 0;  //
    while(I2C_CTL1 & STOP)
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // µÈ´ı×ÜÏß¿ÕÏĞ            
    }


    I2C_CTL1 |= START+UCTR;            // ·¢ËÍÄ£Ê½

    TXBUF  = address;                      // ·¢ËÍ×ÖµØÖ·
   
	Cnt = 0;  //
    while(!(I2C_IFG & I2C_TX_IFG))   // µÈ´ı×ÖµØÖ··¢ËÍÍê±Ï
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // µÈ´ı×ÜÏß¿ÕÏĞ            
    }


    I2C_CTL1 &= ~UCTR;                 // ¶ÁÄ£Ê½

	Cnt = 0;  //
    while(I2C_CTL1 & STOP)
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // µÈ´ı×ÜÏß¿ÕÏĞ            
    }
    
    I2C_CTL1 |= START;                 // ·¢ËÍSTART

    
	Cnt = 0;  //
    while( !(I2C_IFG & I2C_RX_IFG))  // µÈ´ı´Ó»ú·µ»ØÊı¾İ
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // µÈ´ı×ÜÏß¿ÕÏĞ            
    }
	
    rxData = RXBUF << 8;

	Cnt = 0;  //
    while( !(I2C_IFG & I2C_RX_IFG))  //µÈ´ı´Ó»ú·µ»ØÊı¾İ
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // µÈ´ı×ÜÏß¿ÕÏĞ            
    }
	
    rxData += RXBUF;

    UCB1CTL1 |=UCTXNACK;              // ·¢ËÍÍ£Ö¹Î»ºÍNACKÎ»
    UCB1CTL1 |=UCTXSTP;

	return (rxData);
}




/****************************************************************************
*º¯ÊıÃû-Function:	void Write_Word_IIC_B(u8 cmd,u8 data1,u8 data2)
*ÃèÊö- Description:		Í¨¹ıIIC_B Ïò´Ó»úµÄÄ³¸ö¼Ä´æÆ÷Ğ´Ò»¸ö×Ö
*ÊäÈë²ÎÊı-Input:	None
*Êä³ö²ÎÊı-output:	None
*×¢ÒâÊÂÏî-Note£º	
	¡ø01) Ğ´Ò»¸ö×ÖÊ±£¬¶ÔÓÚBQ27410  ÏÈĞ´µÄ×Ö½ÚÎªµÍ×Ö½Údata1(µÍµØÖ·)  
	           Àı:Write_Word_IIC_B(0x00,0x0c,0x00); //Ö¸ÏòµØÖ·0x00Ğ´ÈëÒ»¸ö×Ö(ÖµÎª0x000C)
	¡ø02)    ¡ø03)    ¡ø04)  
*****************************************************************************/
void Write_Word_IIC_B(u8 cmd,u8 data1,u8 data2) //Í¨¹ıIIC_B Ïò´Ó»úµÄÄ³¸ö¼Ä´æÆ÷Ğ´Ò»¸ö×Ö
{
	unsigned int Cnt = 0;  //

	

    I2C_CTL1 |= START + UCTR;          //·¢ËÍÄ£Ê½             I2C TX, start condition


	Cnt = 0;  //
    TXBUF  = cmd;                      // ·¢ËÍ×ÖµØÖ·
    while(!(I2C_IFG & I2C_TX_IFG))   // µÈ´ı×ÖµØÖ··¢ËÍÍê±Ï
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // µÈ´ı×ÜÏß¿ÕÏĞ            
    }

	Cnt = 0;  //
    TXBUF  = data1;                      // ·¢ËÍ×ÖµØÖ·
    while(!(I2C_IFG & I2C_TX_IFG))   // µÈ´ı×ÖµØÖ··¢ËÍÍê±Ï
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // µÈ´ı×ÜÏß¿ÕÏĞ            
    }

	Cnt = 0;  //
    TXBUF  = data2;                      // ·¢ËÍ×ÖµØÖ·
    while(!(I2C_IFG & I2C_TX_IFG))   // µÈ´ı×ÖµØÖ··¢ËÍÍê±Ï
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;  // µÈ´ı×ÜÏß¿ÕÏĞ            
    }



    while (UCB1CTL1 & UCTXSTP);             // Ensure stop condition got sent

}



/****************************************************************************
*º¯ÊıÃû-Function:	void Write_Word_IIC_B(u8 cmd,u8 data1,u8 data2)
*ÃèÊö- Description:		Í¨¹ıIIC_B Ïò´Ó»úµÄÄ³¸ö¼Ä´æÆ÷Ğ´Ò»¸ö×Ö
*ÊäÈë²ÎÊı-Input:	None
*Êä³ö²ÎÊı-output:	None
*×¢ÒâÊÂÏî-Note£º	¡ø01)   	¡ø02)    ¡ø03)    ¡ø04)  
***********************************************************
void Write_Word_IIC_B(u8 cmd,u8 data1,u8 data2) //Í¨¹ıIIC_B Ïò´Ó»úµÄÄ³¸ö¼Ä´æÆ÷Ğ´Ò»¸ö×Ö
{
	TxData[2]=cmd;
    TxData[1]=data1;
    TxData[0]=data2;
    TXByteCtr=3;                       // Load TX byte counter
	

	UCB1IE |= UCTXIE;                  // Enable TX interrupt

	flag = 2;

    I2C_CTL1 |= START + UCTR;          //·¢ËÍÄ£Ê½             I2C TX, start condition

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
    	    UCB1CTL1 |=UCTXSTP;               // ·¢ËÍÍ£Ö¹Î»UCB0CTL1 |= UCTXSTP;                    // I2C stop condition
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
   	    UCB1CTL1 |=UCTXSTP;               // ·¢ËÍÍ£Ö¹Î»UCB0CTL1 |= UCTXSTP;                    // I2C stop condition
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




