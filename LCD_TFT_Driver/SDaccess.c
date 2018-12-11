/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 SDaccess.c
* 附属文件-Dependencies:  	 SDaccess.h; ff.h; msp430.h; 
* 文件描述-File Description:	 ( 源程序-Source File) 
	■"SD_Card SD卡"-驱动程序(外部资源)
	01)SD卡（Secure Digital Memory Card）中文翻译为安全数码卡，
是一种基于半导体快闪记忆器的新一代记忆设备，它被
广泛地于便携式装置上使用。
	02)SD卡在24mm×32mm×2.1mm的体积内结合了〔SanDisk〕快闪
记忆卡控制与MLC（Multilevel Cell）技术和Toshiba（东芝）0.16u及
0.13u的NAND技术，通过9针的接口界面与专门的驱动器相连接，
不需要额外的电源来保持其上记忆的信息。
	03)SD卡的技术是基于MultiMedia卡（MMC）格式上发展而来，
大小和MMC卡差不多。MMC卡可以被新的SD设备存取，兼容性
则取决于应用软件，但SD卡却不可以被MMC设备存取。（SD卡
外型采用了与MMC卡厚度一样的导轨式设计，SD卡结构以使
SD设备可以适合MMC卡)。 
	04) SD卡接口除了保留MMC卡的7针外，还在两边加多了2针，
作为数据线。采用了NAND型Flash Memory，基本上和SmartMedia的
一样，平均数据传输率能达到2MB/s。
	05)    	06)	
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

#include "Hardware_Profile.h"  //处理器"硬件配置文件" -Hardware specific definitions for Processor


#include <stdint.h>

#include "msp430.h"

#include "HAL_PMM.h"  //F5xx_F6xx_Core_Lib//系统电源管理模块-头文件 
#include "HAL_UCS.h"  //F5xx_F6xx_Core_Lib//系统时钟配置-头文件 

#include "SDaccess.h" //"SD_Card SD卡"-驱动程序(外部资源)-头文件
#include "ff.h"
#include "diskio.h"             /* Common include file for FatFs and disk I/O layer */


////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned char G_Data_SD_Read = 0xFF;  //缓存 "SD_Card SD卡"的一个字节数据
unsigned char G_Data_SD_Write = 0xFF;  //缓存 "SD_Card SD卡"的一个字节数据

unsigned char SD_State = 0;   //BlueS//记录SD卡的状态



char SD_Buf[100]; //255  //SD卡数据缓存数组
unsigned int SD_Cnt = 0; //SD卡数据缓存数组指针   


unsigned int SD_Num = 0;   
unsigned int SD_Write_Num = 0; 


////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////



/****************************************************************************
*函数名-Function:	FRESULT WriteFile(char* fileName, char* text, WORD size)
*描述- Description:		写SD卡: 新建一个文件，并定入指定大小的数据
*输入参数-Input:	fileName; text; size
*输出参数-output:	None
*注意事项-Note：	▲01)    	▲02)    	▲03)    ▲04)  
**********************************************************
FRESULT WriteFile(char* fileName, char* text, WORD size) //写SD卡: 新建一个文件，并定入指定大小的数据
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
*函数名-Function:	FRESULT WriteFile(char* fileName, char* text, WORD size)
*描述- Description:		写SD卡: 新建一个文件，并定入指定大小的数据
*输入参数-Input:	fileName; text; size
*输出参数-output:	None
*注意事项-Note：	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
FRESULT WriteFile(char* fileName, char* text, WORD size) //写SD卡: 新建一个文件，并定入指定大小的数据
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
*函数名-Function:	FRESULT GetFile(char* fileName)
*描述- Description:		读SD卡: 从指定文件读取
*输入参数-Input:	fileName
*输出参数-output:	None
*注意事项-Note：	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
FRESULT GetFile(char* fileName) //读SD卡: 从指定文件读取
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
*函数名-Function:	void die(FRESULT rc)
*描述- Description:		读写SD卡出问错时，进入低功耗模式
*输入参数-Input:	rc
*输出参数-output:	None
*注意事项-Note：	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void die(FRESULT rc) //读写SD卡出问错时，进入低功耗模式
{
	SD_State = STATE_SD_ERROR;

	// Wait in low power mode 3 until a button is pressed
//BlueS //__bis_SR_register(LPM3_bits + GIE);


}




//////////BlueS 新增////////////////////////////////////////////////


/****************************************************************************
*函数名-Function:	void Initial_SD_Card(void)
*描述- Description:		初始化设置: "SD_Card SD卡"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Initial_SD_Card(void)  //初始化设置: "SD_Card SD卡"
{
	mSPI_All_Disable;  //关闭所有SPI模块的使能

/****
mSPI_All_Disable; //禁用所有用到SPI_B的模块

P8SEL |= BIT4; 
P8SEL |= BIT5; 
P8SEL |= BIT6; 

//P8REN &= ~BIT4;
//P8REN &= ~BIT5;
//P8REN &= ~BIT6;

////////////////////////////////////////////////////////////////////////////
//==**配置"B模块"多路复用器TS3A5017: 选择IN2 、IN1**==============//
	mConfig_TS3A5017_B_IN2(0);	//IN2 =0
	mConfig_TS3A5017_B_IN1(1);	//IN1 =1	 //选择s2
	****/
}



/****************************************************************************
*函数名-Function:	void Initial_Osccon_SD_Card(void)
*描述- Description:		初始化晶振--"SD_Card SD卡"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Initial_Osccon_SD_Card(void) //初始化晶振--"SD_Card SD卡"
{

	//IO初始化，在放在"晶振"配置的前面
//P1DIR |= BIT0;		 // ACLK set out to pins
//P1SEL |= BIT0;	   		

//==care=下面之两句一定要有，不知道为什么?//////////////////
//P3DIR |= BIT4;							  // SMCLK set out to pins
//P3SEL |= BIT4;							  

 
/*************************************
//==care=倍频到20M, 程序一定要放在这里,不然会影响到RTC//////
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
	 UCSCTL4 |= SELS_4;   //SMCLK选择DCOCLKDIV (倍频后的频率)

									 
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
*函数名-Function:	void Initial_Osccon_SD_Card(void)
*描述- Description:		初始化晶振--"SD_Card SD卡"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************
void Initial_Osccon_SD_Card(void) //初始化晶振--"SD_Card SD卡"
{

	//IO初始化，在放在"晶振"配置的前面
//P1DIR |= BIT0;		 // ACLK set out to pins
//P1SEL |= BIT0;	   		

//==care=下面之两句一定要有，不知道为什么?//////////////////
//P3DIR |= BIT4;							  // SMCLK set out to pins
//P3SEL |= BIT4;							  

 

//==care=倍频到20M, 程序一定要放在这里,不然会影响到RTC//////
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


