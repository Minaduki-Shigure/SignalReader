/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 SDaccess.c
* �����ļ�-Dependencies:  	 SDaccess.h; ff.h; msp430.h; 
* �ļ�����-File Description:	 ( Դ����-Source File) 
	��"SD_Card SD��"-��������(�ⲿ��Դ)
	01)SD����Secure Digital Memory Card�����ķ���Ϊ��ȫ���뿨��
��һ�ֻ��ڰ뵼���������������һ�������豸������
�㷺���ڱ�Яʽװ����ʹ�á�
	02)SD����24mm��32mm��2.1mm������ڽ���ˡ�SanDisk������
���俨������MLC��Multilevel Cell��������Toshiba����֥��0.16u��
0.13u��NAND������ͨ��9��Ľӿڽ�����ר�ŵ������������ӣ�
����Ҫ����ĵ�Դ���������ϼ������Ϣ��
	03)SD���ļ����ǻ���MultiMedia����MMC����ʽ�Ϸ�չ������
��С��MMC����ࡣMMC�����Ա��µ�SD�豸��ȡ��������
��ȡ����Ӧ���������SD��ȴ�����Ա�MMC�豸��ȡ����SD��
���Ͳ�������MMC�����һ���ĵ���ʽ��ƣ�SD���ṹ��ʹ
SD�豸�����ʺ�MMC��)�� 
	04) SD���ӿڳ��˱���MMC����7���⣬�������߼Ӷ���2�룬
��Ϊ�����ߡ�������NAND��Flash Memory�������Ϻ�SmartMedia��
һ����ƽ�����ݴ������ܴﵽ2MB/s��
	05)    	06)	
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

#include "Hardware_Profile.h"  //������"Ӳ�������ļ�" -Hardware specific definitions for Processor


#include <stdint.h>

#include "msp430.h"

#include "HAL_PMM.h"  //F5xx_F6xx_Core_Lib//ϵͳ��Դ����ģ��-ͷ�ļ� 
#include "HAL_UCS.h"  //F5xx_F6xx_Core_Lib//ϵͳʱ������-ͷ�ļ� 

#include "SDaccess.h" //"SD_Card SD��"-��������(�ⲿ��Դ)-ͷ�ļ�
#include "ff.h"
#include "diskio.h"             /* Common include file for FatFs and disk I/O layer */


////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned char G_Data_SD_Read = 0xFF;  //���� "SD_Card SD��"��һ���ֽ�����
unsigned char G_Data_SD_Write = 0xFF;  //���� "SD_Card SD��"��һ���ֽ�����

unsigned char SD_State = 0;   //BlueS//��¼SD����״̬



char SD_Buf[100]; //255  //SD�����ݻ�������
unsigned int SD_Cnt = 0; //SD�����ݻ�������ָ��   


unsigned int SD_Num = 0;   
unsigned int SD_Write_Num = 0; 


////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////



/****************************************************************************
*������-Function:	FRESULT WriteFile(char* fileName, char* text, WORD size)
*����- Description:		дSD��: �½�һ���ļ���������ָ����С������
*�������-Input:	fileName; text; size
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)    ��04)  
**********************************************************
FRESULT WriteFile(char* fileName, char* text, WORD size) //дSD��: �½�һ���ļ���������ָ����С������
{
	static unsigned int i=0;
		i++;
    // Result code
    FRESULT rc;
    // File system object
    FATFS fatfs;
    // File object
    FIL fil;
    UINT bw;

    // Register volume work area (never fails)
    f_mount(0, &fatfs);

    // Open file
    rc = f_open(&fil, fileName, FA_WRITE | FA_CREATE_ALWAYS);
    if (rc)
    {
        die(rc);
    }

    //fffffffffccccccccccccccc
    f_lseek(&fil,f_tell(&fil)+i-1);
    // Write to file
    rc = f_write(&fil, text, size, &bw);
    if (rc)
    {
        die(rc);
    }

    // Close the file
    rc = f_close(&fil);
    if (rc)
    {
        die(rc);
    }

    return rc;
}
*******************/



/****************************************************************************
*������-Function:	FRESULT WriteFile(char* fileName, char* text, WORD size)
*����- Description:		дSD��: �½�һ���ļ���������ָ����С������
*�������-Input:	fileName; text; size
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)    ��04)  
*****************************************************************************/
FRESULT WriteFile(char* fileName, char* text, WORD size) //дSD��: �½�һ���ļ���������ָ����С������
{
	static unsigned int i=0;

	i++;

	SD_Write_Num ++;
	
    // Result code
    FRESULT rc;
    // File system object
    FATFS fatfs;
    // File object
    FIL fil;
    UINT bw;

    // Register volume work area (never fails)
    f_mount(0, &fatfs);

    // Open file
    rc = f_open(&fil, fileName, FA_WRITE | FA_CREATE_ALWAYS);
    if (rc)
    {
        die(rc);
    }

    //fffffffffccccccccccccccc
    f_lseek(&fil,f_tell(&fil)+SD_Write_Num-1);
    // Write to file
    rc = f_write(&fil, text, size, &bw);
    if (rc)
    {
        die(rc);
    }

    // Close the file
    rc = f_close(&fil);
    if (rc)
    {
        die(rc);
    }

    return rc;
}


/****************************************************************************
*������-Function:	FRESULT GetFile(char* fileName)
*����- Description:		��SD��: ��ָ���ļ���ȡ
*�������-Input:	fileName
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)    ��04)  
*****************************************************************************/
FRESULT GetFile(char* fileName) //��SD��: ��ָ���ļ���ȡ
{
//	static unsigned int j=0;
		SD_Num ++;
    FRESULT rc;                                            /* Result code */
    FATFS fatfs;                                           /* File system object */
    FIL fil;                                               /* File object */
    UINT br;

                                                           // accessing the SD card

    f_mount(0, &fatfs);                                    /* Register volume work area (never
                                                            *fails) */

    rc = f_open(&fil, fileName, FA_READ);

    for (;;)
    {
    	  //fffffffffccccccccccccccc
    	//f_lseek(&fil,f_tell(&fil)+(j-1));
        rc = f_read(&fil, SD_Buf, SD_Num, &br);        /* Read a chunk of file */

        if (rc || !br) break;                              /* Error or end of file */
    }
    if (rc)                                                //if error
    {
        f_close(&fil);
                                                           // accessing the SD card
        return rc;
    }

    rc = f_close(&fil);
                                                           // accessing the SD card
    return rc;
}


/****************************************************************************
*������-Function:	void die(FRESULT rc)
*����- Description:		��дSD�����ʴ�ʱ������͹���ģʽ
*�������-Input:	rc
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)    ��04)  
*****************************************************************************/
void die(FRESULT rc) //��дSD�����ʴ�ʱ������͹���ģʽ
{
	SD_State = STATE_SD_ERROR;

	// Wait in low power mode 3 until a button is pressed
//BlueS //__bis_SR_register(LPM3_bits + GIE);


}




//////////BlueS ����////////////////////////////////////////////////


/****************************************************************************
*������-Function:	void Initial_SD_Card(void)
*����- Description:		��ʼ������: "SD_Card SD��"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)    ��04)  
*****************************************************************************/
void Initial_SD_Card(void)  //��ʼ������: "SD_Card SD��"
{
	mSPI_All_Disable;  //�ر�����SPIģ���ʹ��

/****
mSPI_All_Disable; //���������õ�SPI_B��ģ��

P8SEL |= BIT4; 
P8SEL |= BIT5; 
P8SEL |= BIT6; 

//P8REN &= ~BIT4;
//P8REN &= ~BIT5;
//P8REN &= ~BIT6;

////////////////////////////////////////////////////////////////////////////
//==**����"Bģ��"��·������TS3A5017: ѡ��IN2 ��IN1**==============//
	mConfig_TS3A5017_B_IN2(0);	//IN2 =0
	mConfig_TS3A5017_B_IN1(1);	//IN1 =1	 //ѡ��s2
	****/
}



/****************************************************************************
*������-Function:	void Initial_Osccon_SD_Card(void)
*����- Description:		��ʼ������--"SD_Card SD��"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Initial_Osccon_SD_Card(void) //��ʼ������--"SD_Card SD��"
{

	//IO��ʼ�����ڷ���"����"���õ�ǰ��
//P1DIR |= BIT0;		 // ACLK set out to pins
//P1SEL |= BIT0;	   		

//==care=����֮����һ��Ҫ�У���֪��Ϊʲô?//////////////////
//P3DIR |= BIT4;							  // SMCLK set out to pins
//P3SEL |= BIT4;							  

 
/*************************************
//==care=��Ƶ��20M, ����һ��Ҫ��������,��Ȼ��Ӱ�쵽RTC//////
	 SetVCore(PMMCOREV_3);			 // Set Vcore to accomodate for max. allowed system speed
	 UCSCTL3 |= SELREF_2;				 // Set DCO FLL reference = REFO
	// UCSCTL4 |= SELA_2;				 // Set ACLK = REFO
	 Init_FLL_Settle(20000, 630);	// MCLK=DCO = 20MHz // Set system clock to max (20MHz)
*************************/


	SetVCore(PMMCOREV_3);			 // Set Vcore to accomodate for max. allowed system speed

	UCSCTL3 |= SELREF_2;					  // Set DCO FLL reference = REFO

	__bis_SR_register(SCG0);				  // Disable the FLL control loop
	UCSCTL0 = 0x0000;						  // Set lowest possible DCOx, MODx
	UCSCTL1 = DCORSEL_5;					  // Select DCO range 24MHz operation
	UCSCTL2 = FLLD_1 + 374; 				  // Set DCO Multiplier for 12MHz
									  // (N + 1) * FLLRef = Fdco
									  // (374 + 1) * 32768 = 12MHz
									  // Set FLL Div = fDCOCLK/2
	__bic_SR_register(SCG0);				  // Enable the FLL control loop
	

							
	//UCSCTL4 |= SELS_5 + SELM_5; 			  // SMCLK=MCLK=XT2


// UCSCTL4 |= SELS_5;     // SMCLK=XT2 = 4MHz

	 UCSCTL4 |= SELA_0;	// ACLK = LFTX1 (by default)=32.768KHz

	 UCSCTL4 &= ~SELS_5;	
	 UCSCTL4 |= SELS_4;   //SMCLKѡ��DCOCLKDIV (��Ƶ���Ƶ��)

									 
////////////////////////////////////////////////////////////////////////////								 

	// Loop until XT1,XT2 & DCO stabilizes - in this case loop until XT2 settles
	do
	{
	  UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
											  // Clear XT2,XT1,DCO fault flags
	  SFRIFG1 &= ~OFIFG;					  // Clear fault flags
	}while (SFRIFG1&OFIFG); 				  // Test oscillator fault flag

	UCSCTL6 &= ~XT2DRIVE0;					  // Decrease XT2 Drive according to  expected frequency


}




/****************************************************************************
*������-Function:	void Initial_Osccon_SD_Card(void)
*����- Description:		��ʼ������--"SD_Card SD��"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************
void Initial_Osccon_SD_Card(void) //��ʼ������--"SD_Card SD��"
{

	//IO��ʼ�����ڷ���"����"���õ�ǰ��
//P1DIR |= BIT0;		 // ACLK set out to pins
//P1SEL |= BIT0;	   		

//==care=����֮����һ��Ҫ�У���֪��Ϊʲô?//////////////////
//P3DIR |= BIT4;							  // SMCLK set out to pins
//P3SEL |= BIT4;							  

 

//==care=��Ƶ��20M, ����һ��Ҫ��������,��Ȼ��Ӱ�쵽RTC//////
	 SetVCore(PMMCOREV_3);			 // Set Vcore to accomodate for max. allowed system speed
	 UCSCTL3 |= SELREF_2;				 // Set DCO FLL reference = REFO
	// UCSCTL4 |= SELA_2;				 // Set ACLK = REFO
	 Init_FLL_Settle(20000, 630);	// MCLK=DCO = 20MHz // Set system clock to max (20MHz)

									 
////////////////////////////////////////////////////////////////////////////								 
	 while(BAKCTL & LOCKIO) 				   // Unlock XT1 pins for operation
		BAKCTL &= ~(LOCKIO);   
	 
	 P7SEL &= ~(BIT2+BIT3); 				   // Port select XT2
	 UCSCTL6 |= XT2OFF;   // Disable XT2 

///	 P7SEL |= BIT2+BIT3;					   // Port select XT2

///	 UCSCTL6 &= ~XT2OFF;					   // Enable XT2 
//	 UCSCTL3 |= SELREF_2;					   // Set DCO FLL reference = REFO
											   // Since LFXT1 is not used,
											   // sourcing FLL with LFXT1 can cause
											   // XT1OFFG flag to set
	//  UCSCTL4 |= SELA_2; 					   // ACLK=REFO=32.768KHz,SMCLK=DCO,MCLK=DCO


	 UCSCTL6 &= ~(XT1OFF);					   // XT1 On
	 UCSCTL6 |= XCAP_3; 					   // Internal load cap 


	// Loop until XT1,XT2 & DCO stabilizes - in this case loop until XT2 settles
	do
	{
	  UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
											  // Clear XT2,XT1,DCO fault flags
	  SFRIFG1 &= ~OFIFG;					  // Clear fault flags
	}while (SFRIFG1&OFIFG); 				  // Test oscillator fault flag

	UCSCTL6 &= ~XT2DRIVE0;					  // Decrease XT2 Drive according to  expected frequency
							
	//UCSCTL4 |= SELS_5 + SELM_5; 			  // SMCLK=MCLK=XT2


// UCSCTL4 |= SELS_5;     // SMCLK=XT2 = 4MHz

	 UCSCTL4 |= SELA_0;	// ACLK = LFTX1 (by default)=32.768KHz
	 
	 UCSCTL4 &= ~SELS_5;	
	 UCSCTL4 |= SELS_4;   


}
************/



/*****************************************
void init_clk(void)
{
//	XT1_PORT_SEL |= XT1_ENABLE;               // Select XT1
	UCSCTL3 |= SELREF_2;                      // Set DCO FLL reference = REFO
	UCSCTL4 |= SELA_2;                        // Set ACLK = REFO

	__bis_SR_register(SCG0);                  // Disable the FLL control loop
	UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
	UCSCTL1 = DCORSEL_5;                      // Select DCO range 24MHz operation
	UCSCTL2 = FLLD_1 + 374;                   // Set DCO Multiplier for 12MHz
		                                      // (N + 1) * FLLRef = Fdco
		                                      // (374 + 1) * 32768 = 12MHz
		                                      // Set FLL Div = fDCOCLK/2
	__bic_SR_register(SCG0);              	  // Enable the FLL control loop
	// Loop until XT1,XT2 & DCO fault flag is cleared
	do
	{
		UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);		// Clear XT2,XT1,DCO fault flags
		SFRIFG1 &= ~OFIFG;                      		// Clear fault flags
	}while (SFRIFG1&OFIFG);                   			// Test oscillator fault flag
}

*******************************/


