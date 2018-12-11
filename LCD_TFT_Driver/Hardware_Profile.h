/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 Hardware_Profile.h
* 附属文件-Dependencies:  	 msp430f6638.h	
* 文件描述-File Description:	 ( 头文件-Header File )
	■ 处理器"硬件配置文件" -头文件-Hardware specific definitions for Processor
	01) 处理器IO口使用宏定义，统一在Hardware_Profile.h 定义     
	02)      03)    04)    05)    06)	
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


#ifndef __Hardware_Profile_H
#define __Hardware_Profile_H


#include "msp430f6638.h"   // "处理器"头文件: 内部寄存相关定义等



////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"宏定义**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//==**单片机内部定义**================================//

#define mClose_WDT      (WDTCTL = WDTPW + WDTHOLD)  // 关闭看门狗
#define mClr_WDTCNT     (WDTCTL = WDTPW + WDTCNTCL) // 清看门狗(对于MSP430单片机)
#define	mNop	        (__no_operation())    //空操作指令(用于"短延时"或"调试")

//#define	mEnable_GIE     (__bis_SR_register(GIE))  // 开启总中断
#define	mEnable_GIE     (_EINT())  // 开启总中断GIE
#define	mDisable_GIE    (_DINT())  // 关闭总中断GIE

#define	mReset_Soft    (PMMCTL0 |= PMMSWPOR) //"软件复位" (MSP430单片机)



#define	Fosc_System	    (12)		//系统运行频率 unit:MHz (倍频后，即最终的)
////////////////////////////////////////////////////////////////////////////
//==** 系统频率MCLK =12M  (DCO  FLL倍频到12MHz)   **==============//
	//ms级的死等延时，调用WaitingDelayMs(n); //死等待延时n个ms(包含清看门狗操作)
	//us级的死等延时，调用mDelay_Cycles(n);	//死等待延时n个时钟周期
#define mDelay_Cycles(n) (__delay_cycles(n)) // 死等待延时"n"个时钟周期.
	//例: __delay_cycles(12000000); //(1/12M)*12000000=1s

#define M_Delay_1us   (12)   //死等延时"1us" //系统频率为12 M时
#define M_Delay_2us   (24)   //死等延时"2us" //系统频率为12 M时
#define M_Delay_5us   (60)  //死等延时"5us" //系统频率为12 M时

#define M_Delay_10us  (120)      //死等延时"10us"//系统频率为12 M时
#define M_Delay_100us (1200)     //死等延时"100us"//系统频率为12 M时
#define M_Delay_1ms   (12000)    //死等延时"1ms"//系统频率为12 M时(示波器实测1.02ms)
#define M_Delay_1s    (12000000) //死等延时"1s"//系统频率为12 M时(示波器实测1.02s)


#define CPU_F ((double)12000000)
#define _delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define _delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))


////////////////////////////////////////////////////////////////////////////
//==** 系统频率MCLK =20M  (DCO  FLL倍频到20MHz)   **==============//

/********************************************
	//ms级的死等延时，调用WaitingDelayMs(n); //死等待延时n个ms(包含清看门狗操作)
	//us级的死等延时，调用mDelay_Cycles(n);	//死等待延时n个时钟周期
#define mDelay_Cycles(n) (__delay_cycles(n)) // 死等待延时"n"个时钟周期.
	//例: __delay_cycles(20000000); //约980ms ≈ (1/20M)*20000000=1s(系统频率>20M(通过倍频))

#define M_Delay_1us   (20)   //死等延时"1us" //系统频率为20 M时
#define M_Delay_2us   (40)   //死等延时"2us" //系统频率为20 M时
#define M_Delay_5us   (100)  //死等延时"5us" //系统频率为20 M时

#define M_Delay_10us  (200)   //死等延时"10us"
#define M_Delay_100us  (2000)   //死等延时"100us"

//#define M_Delay_1s    (20000000)  //死等延时"1s"	      //care 系统频率(大于)约为20M
//#define M_Delay_500ms (10000000) //死等延时"500ms"	//care 系统频率(大于)约为20M
//#define M_Delay_5ms   (100000)  //死等延时"5ms"	    //care 系统频率(大于)约为20M
//#define M_Delay_1ms   (20000)  //死等延时"1ms"	    //care 系统频率(大于)约为20M
//#define M_Delay_250us (5000)  //死等延时"250us"	    //care 系统频率(大于)约为20M
//#define M_Delay_50us (1000)  //死等延时"50us"	    //care 系统频率(大于)约为20M

#define CPU_F ((double)20000000)
#define _delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define _delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))
********************************************/




////////////////////////////////////////////////////////////////////////////
//==**单片机IO口使用宏定义,统一在HardwareProfile.h定义**===//
//==**适用于**MSP430F5xx_6xx 的单片机**====================//
/*****************************

//==**配置"功能选择寄存器"：IO为外围模块功能引脚或IO引脚**IO bits Function Pin/IO Pin**====//
#define mSelect_Xxx_FunctionPin  (P1SEL |= BIT) //配置引脚为"外围模块功能"引脚
#define mSelect_Xxx_IoPin (P1SEL &= (~BIT))     //配置引脚为"IO"引脚

//==**配置"方向寄存器"：IO为输入或输出**IO bits Input/Output**===================//
#define mSetOut_Xxx   (P1DIR |= BIT)         //配置引脚为"输出"
#define mSetIn_Xxx     (P1DIR &= (~BIT))    //配置引脚为"输入"

//==**配置"输出寄存器"：输出高电平或低电平**IO bits Set/Clr**===============//
#define mHigh_Xxx   (P1OUT |= BIT)           //引脚输出"高电平(1)"
#define mLow_Xxx    (P1OUT &= (~BIT))      //引脚输出"低电平(0)"

#define mTurn_Xxx    (P1OUT ^= BIT)        //"翻转"引脚输出状态

#define mOpen_Xxx   (P1OUT |= BIT)         //引脚输出对应"打开"功能
#define mClose_Xxx   (P1OUT &= (~BIT))    //引脚输出对应"关闭"功能

//==**配置 "上拉或下拉电阻使能寄存器"：使能或禁止此功能**IO bits PULL Enabled/Disabled**===//
#define mPullEnabled_Xxx(n)   (P1REN |= BIT)        //使能--上拉/下拉功能
#define mPullDisabled_Xxx(n)  (P1REN &= (~BIT))   //禁止--上拉/下拉功能

//==**配置 "输出寄存器(复用)"：选择引脚上拉或下拉**IO bits PullUp/PullDown**======//
#define mPullUp_Xxx(n)        (P1OUT |= BIT)      //配置引脚"上拉"功能
#define mPullDown_Xxx(n)    (P1OUT &= (BIT) )   //配置引脚"下拉"功能


//==**读取"输入寄存器"：返回引脚的电平值**IO bits Input**================//
#define mRead_Xxx(n)   (P1IN&n?1:0 )      //读取引脚电平值


//#define _MIN(a,b)			( (a) < (b) ? (a) : (b) )
//#define _MAX(a,b)			( (a) > (b) ? (a) : (b) )
*****************************/


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//==**内部"资源IO口使用宏定义**=======================//


	//--**UART串口*IO口使用宏定义**----------------//
//#define UART1_TX_TRIS   TRISFbits.TRISF3	//uart1发送引脚
//#define UART1_RX_TRIS   TRISFbits.TRISF2	//uart1接收引脚
	

	////////////////////////////////////////////////////////////////////////////
	//==**SPI_B *IO口使用宏定义**=============================//

	//--**P8.4 引脚: SPI_B_CLK (P8.4/UCB1CLK/UCA1STE/S11)** -------------------//
#define SPI_B_CLK_SEL  (P8SEL)
#define SPI_B_CLK_DIR  (P8DIR)  
#define SPI_B_CLK_PORT (P8OUT)
	
#define SPI_B_CLK_IO   (BIT4)	
	
		//配置引脚为"外围模块功能"引脚
#define mSelect_SPI_B_CLK_FunctionPin  (SPI_B_CLK_SEL |= SPI_B_CLK_IO) 
	
		//配置"SPI_B_CLK" 引脚为"输出"
#define mSetOut_SPI_B_CLK (SPI_B_CLK_DIR |= SPI_B_CLK_IO)  
	
		//配置引脚为"输出",并输出"高电平"
#define mHigh_SPI_B_CLK  {SPI_B_CLK_DIR |= SPI_B_CLK_IO; SPI_B_CLK_PORT |= SPI_B_CLK_IO;}      //引脚输出"高电平(1)"
		//配置引脚为"输出",并输出"低电平"
#define mLow_SPI_B_CLK   {SPI_B_CLK_DIR |= SPI_B_CLK_IO; SPI_B_CLK_PORT &= ~SPI_B_CLK_IO;}    //引脚输出"低电平(0)"
	
	
	//--**P8.5 引脚: SPI_B_MOSI (P8.5/UCB1SIMO/UCB1SDA/S10)** ----------------//
#define SPI_B_MOSI_SEL  (P8SEL)
#define SPI_B_MOSI_DIR  (P8DIR)  
#define SPI_B_MOSI_PORT (P8OUT)
	
#define SPI_B_MOSI_IO   (BIT5)
	
		//配置引脚为"外围模块功能"引脚
#define mSelect_SPI_B_MOSI_FunctionPin  (SPI_B_MOSI_SEL |= SPI_B_MOSI_IO) 
	
		 //配置"SPI_B_MOSI" 引脚为"输出"
#define mSetOut_SPI_B_MOSI (SPI_B_MOSI_DIR |= SPI_B_MOSI_IO)  
	
			//配置引脚为"输出",并"输出高电平"
#define mHigh_SPI_B_MOSI {SPI_B_MOSI_DIR |= SPI_B_MOSI_IO; SPI_B_MOSI_PORT |= SPI_B_MOSI_IO;}   
			//配置引脚为"输出",并"输出低电平"
#define mLow_SPI_B_MOSI {SPI_B_MOSI_DIR |= SPI_B_MOSI_IO; SPI_B_MOSI_PORT &= ~SPI_B_MOSI_IO;}   
	
	
	
	//--**P8.6引脚: SPI_B_MISO (P8.6/UCB1SOMI/UCB1SCL/S9)** ----------------//
#define SPI_B_MISO_SEL  (P8SEL)
#define SPI_B_MISO_DIR  (P8DIR)  
#define SPI_B_MISO_PORT (P8OUT)
	
#define SPI_B_MISO_IO   (BIT6)
	
		//配置引脚为"外围模块功能"引脚
#define mSelect_SPI_B_MISO_FunctionPin  (SPI_B_MISO_SEL |= SPI_B_MISO_IO) 
	
		 //配置"SPI_B_MISO" 引脚为"输入"
#define mSetIn_SPI_B_MISO (SPI_B_MISO_DIR &= (~SPI_B_MISO_IO))  
	
		//配置"SPI_B_MISO" 引脚为"输出"
#define mSetOut_SPI_B_MISO (SPI_B_MISO_DIR |= SPI_B_MISO_IO)  
	
	
			//配置引脚为"输出",并"输出高电平"
#define mHigh_SPI_B_MISO {SPI_B_MISO_DIR |= SPI_B_MISO_IO; SPI_B_MISO_PORT |= SPI_B_MISO_IO;}   
			//配置引脚为"输出",并"输出低电平"
#define mLow_SPI_B_MISO {SPI_B_MISO_DIR |= SPI_B_MISO_IO; SPI_B_MISO_PORT &= ~SPI_B_MISO_IO;}   
	




	////////////////////////////////////////////////////////////////////////////
	//==**Potentiometer *ADC12_A--IO口使用宏定义**=================//
//--**P6.6引脚: P6.6/CB6/A6/DAC0** --------------------------------------//
#define Potentiometer_Ad_SEL  (P6SEL)
#define Potentiometer_Ad_DIR  (P6DIR)  
#define Potentiometer_Ad_IO   (BIT6)

	//配置引脚为"外围模块功能"引脚
#define mSelect_Potentiometer_Ad (Potentiometer_Ad_SEL |= Potentiometer_Ad_IO) 
	 //配置引脚为"输入"
#define mSetIn_Potentiometer_Ad (Potentiometer_Ad_DIR &= (~Potentiometer_Ad_IO))  


	////////////////////////////////////////////////////////////////////////////
	//==**INA21x *ADC12_A--IO口使用宏定义**=====================//
//--**P6.7引脚** -------------------------------------------//
#define INA21x_Ad_SEL  (P6SEL)
#define INA21x_Ad_DIR  (P6DIR)  
#define INA21x_Ad_IO   (BIT7)

	//配置引脚为"外围模块功能"引脚
#define mSelect_INA21x_Ad (INA21x_Ad_SEL |= INA21x_Ad_IO) 
	 //配置引脚为"输入"
#define mSetIn_INA21x_Ad (INA21x_Ad_DIR &= (~INA21x_Ad_IO))  


	////////////////////////////////////////////////////////////////////////////
	//==**NTC_Temperature 温度传感器**==========================//
//--**P6.5引脚** ADC12_A--IO口使用宏定义**----------//
#define NTC_TMP_Ad_SEL  (P6SEL)
#define NTC_TMP_Ad_DIR  (P6DIR)  
#define NTC_TMP_Ad_IO   (BIT5)

	//配置引脚为"外围模块功能"引脚
#define mSelect_NTC_TMP_Ad (NTC_TMP_Ad_SEL |= NTC_TMP_Ad_IO) 

	 //配置引脚为"输入"
#define mSetIn_NTC_TMP_Ad (NTC_TMP_Ad_DIR &= (~NTC_TMP_Ad_IO))  


//--**P2.5引脚: P2.5/P2MAP5** ADC12_A--IO口使用宏定义**----------//
//#define NTC_TMP_Power_DIR  (P2DIR)  
//#define NTC_TMP_Power_PORT (P2OUT)
//#define NTC_TMP_Power_IO   (BIT5)

	  //配置引脚为"输出",并打开NTC的工作电源(输出"高电平")
//#define mOpen_NTC_TMP_Power {NTC_TMP_Power_DIR |= NTC_TMP_Power_IO; NTC_TMP_Power_PORT |= NTC_TMP_Power_IO;} //引脚输出"高电平(1)"

	  //配置引脚为"输出",并关闭NTC的工作电源(输出"低电平")
//#define mClose_NTC_TMP_Power {NTC_TMP_Power_DIR |= NTC_TMP_Power_IO; NTC_TMP_Power_PORT &= ~NTC_TMP_Power_IO;} //引脚输出"低电平(0)"


	////////////////////////////////////////////////////////////////////////////
	//==**HR202_Humidity 电阻型湿度传感器**====================//
//--**P3.3引脚** Timer1_CCR2--IO口使用宏定义**------//
#define HR202_CCR3_SEL  (P3SEL)
#define HR202_CCR3_DIR  (P3DIR)  
#define HR202_CCR3_IO   (BIT3)
	//配置引脚为"外围模块功能"引脚
#define mSelect_HR202_CCR3 (HR202_CCR3_SEL |= HR202_CCR3_IO) 
	 //配置引脚为"输入"
#define mSetIn_HR202_CCR3 (HR202_CCR3_DIR &= (~HR202_CCR3_IO))  


	////////////////////////////////////////////////////////////////////////////
	//==**IIC_B 模块--"TMP006,TMP100温度传感器"**===================//

//--**P8.5 引脚: IIC_B_SDA (P8.5/UCB1SIMO/UCB1SDA/S10)** ----------------//
#define IIC_B_SDA_SEL  (P8SEL)
#define IIC_B_SDA_REN  (P8REN)  
#define IIC_B_SDA_DIR  (P8DIR)  
#define IIC_B_SDA_IO   (BIT5)
	//配置引脚为"外围模块功能"引脚
#define mSelect_IIC_B_SDA_FunctionPin (IIC_B_SDA_SEL |= IIC_B_SDA_IO) 
#define mPullEnabled_IIC_B_SDA (IIC_B_SDA_REN |= IIC_B_SDA_IO)   //使能--上拉/下拉功能


//--**P8.6引脚: IIC_B_SCK (P8.6/UCB1SOMI/UCB1SCL/S9)** ----------------//
#define IIC_B_SCK_SEL  (P8SEL)
#define IIC_B_SCK_REN  (P8REN) 
#define IIC_B_SCK_DIR  (P8DIR)  
#define IIC_B_SCK_PORT (P8OUT)
#define IIC_B_SCK_IO   (BIT6)
	//配置引脚为"外围模块功能"引脚
#define mSelect_IIC_B_SCK_FunctionPin (IIC_B_SCK_SEL |= IIC_B_SCK_IO) 
#define mPullEnabled_IIC_B_SCK (IIC_B_SCK_REN |= IIC_B_SCK_IO)   //使能--上拉/下拉功能
	 //配置"IIC_B_SCK" 引脚为"输出"
#define mSetOut_IIC_B_SCK (IIC_B_SCK_DIR |= IIC_B_SCK_IO)  


 
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//==**外部"资源IO口使用宏定义**=======================//


	////////////////////////////////////////////////////////////////////////////
	//==**单片机正常工作指示灯*IO口使用宏定义**=========//
	//==**系统正常工作时，指示灯每250ms闪一次)**=========//

//--**P4.5  引脚: 单片机正常工作指示灯** ---------------------//
#define WORKING_LED_DIR  (P4DIR)  
#define WORKING_LED_PORT (P4OUT)
#define WORKING_LED_IO   (BIT5)
   
	 //配置引脚为"输出",并"翻转"引脚输出状态
#define mTurn_Working_Led  {WORKING_LED_DIR |= WORKING_LED_IO; WORKING_LED_PORT ^= WORKING_LED_IO;}              

	//配置引脚为"输出",并"点亮"工作指示灯
#define mOpen_Working_Led  {WORKING_LED_DIR |= WORKING_LED_IO; WORKING_LED_PORT |= WORKING_LED_IO;}   

	//配置引脚为"输出",并"熄灭"工作指示灯
#define mClose_Working_Led {WORKING_LED_DIR |= WORKING_LED_IO; WORKING_LED_PORT &= (~WORKING_LED_IO);} 



	////////////////////////////////////////////////////////////////////////////
	//==***LED发光二极管**IO口使用宏定义**=================//

//--**P4.6  引脚: LED_YELLOW** -------------------------------------------//
#define LED_YELLOW_DIR  (P4DIR)  
#define LED_YELLOW_PORT (P4OUT)
#define LED_YELLOW_IO   (BIT6)
	//配置引脚为"输出",并"点亮"LED_YELLOW
#define mOpen_LED_YELLOW  {LED_YELLOW_DIR |= LED_YELLOW_IO; LED_YELLOW_PORT |= LED_YELLOW_IO;}   
	//配置引脚为"输出",并"熄灭"LED_YELLOW
#define mClose_LED_YELLOW {LED_YELLOW_DIR |= LED_YELLOW_IO; LED_YELLOW_PORT &= (~LED_YELLOW_IO);} 
	 //配置引脚为"输出",并"翻转"引脚输出状态
#define mTurn_LED_YELLOW  {LED_YELLOW_DIR |= LED_YELLOW_IO; LED_YELLOW_PORT ^= LED_YELLOW_IO;}              


//--**P4.5  引脚: LED_GREEN** -------------------------------------------//
#define LED_GREEN_DIR   (P4DIR)  
#define LED_GREEN_PORT  (P4OUT)
#define LED_GREEN_IO    (BIT5)
	//配置引脚为"输出",并"点亮"LED_GREEN
#define mOpen_LED_GREEN  {LED_GREEN_DIR |= LED_GREEN_IO; LED_GREEN_PORT |= LED_GREEN_IO;}   
	//配置引脚为"输出",并"熄灭"LED_GREEN
#define mClose_LED_GREEN {LED_GREEN_DIR |= LED_GREEN_IO; LED_GREEN_PORT &= (~LED_GREEN_IO);} 
	 //配置引脚为"输出",并"翻转"引脚输出状态
#define mTurn_LED_GREEN  {LED_GREEN_DIR |= LED_GREEN_IO; LED_GREEN_PORT ^= LED_GREEN_IO;}              


//--**P4.4  引脚: LED_RED** -------------------------------------------//
#define LED_RED_DIR     (P4DIR)    
#define LED_RED_PORT    (P4OUT)
#define LED_RED_IO      (BIT4)
	//配置引脚为"输出",并"点亮"LED_RED
#define mOpen_LED_RED  {LED_RED_DIR |= LED_RED_IO; LED_RED_PORT |= LED_RED_IO;}   
	//配置引脚为"输出",并"熄灭"LED_RED
#define mClose_LED_RED {LED_RED_DIR |= LED_RED_IO; LED_RED_PORT &= (~LED_RED_IO);} 
	 //配置引脚为"输出",并"翻转"引脚输出状态
#define mTurn_LED_RED  {LED_RED_DIR |= LED_RED_IO; LED_RED_PORT ^= LED_RED_IO;}              




	////////////////////////////////////////////////////////////////////////////
	//==***IO按键**IO口使用宏定义**=========================//

//--**P4.2 引脚:  Key_1 (IO 按键)** -------------------//
//--**P4.3 引脚:  Key_2 (IO 按键)**--------------------//

#define Key_DIR    (P4DIR)  
#define Key_IN     (P4IN)
#define Key_1_IO   (BIT2)
#define Key_2_IO   (BIT3)

#define mSetIn_Key_1_IO   (Key_DIR &= (~Key_1_IO)) //配置引脚为"输入"
#define mSetIn_Key_2_IO   (Key_DIR &= (~Key_2_IO)) //配置引脚为"输入"



	////////////////////////////////////////////////////////////////////////////
	//==**蜂鸣器*IO口使用宏定义**==========================//
//--**P4.1  引脚: BUZZER** -------------------------------------------//
#define BUZZER_DIR     (P4DIR)    
#define BUZZER_PORT    (P4OUT)
#define BUZZER_IO      (BIT1)

	//配置引脚为"输出",并"打开"蜂鸣器
#define mOpen_BUZZER  {BUZZER_DIR |= BUZZER_IO; BUZZER_PORT |= BUZZER_IO;}   
	//配置引脚为"输出",并"关闭"蜂鸣器
#define mClose_BUZZER {BUZZER_DIR |= BUZZER_IO; BUZZER_PORT &= (~BUZZER_IO);} 
	//配置引脚为"输出",并"翻转"引脚输出状态
#define mTurn_BUZZER  {BUZZER_DIR |= BUZZER_IO; BUZZER_PORT ^= BUZZER_IO;}              



	////////////////////////////////////////////////////////////////////////////
	//==**"TM1638 数码管驱动器"*IO口使用宏定义**============//

//--**P3.5 引脚: DIO (数据输入/输出) ** ----------------------------//
#define TM1638_DIO_DIR  (P3DIR)  
#define TM1638_DIO_PORT (P3OUT)
#define TM1638_DIO_IN   (P3IN)   
#define TM1638_DIO_IO   (BIT5)

#define mSetOut_TM1638_DIO (TM1638_DIO_DIR |= TM1638_DIO_IO) //配置引脚为"输出"
	//配置引脚为"输出",并输出"高电平"
#define mHigh_TM1638_DIO  {TM1638_DIO_DIR |= TM1638_DIO_IO; TM1638_DIO_PORT |= TM1638_DIO_IO;} //引脚输出"高电平(1)"
	//配置引脚为"输出",并输出"低电平"
#define mLow_TM1638_DIO {TM1638_DIO_DIR |= TM1638_DIO_IO; TM1638_DIO_PORT &= (~TM1638_DIO_IO);} //引脚输出"低电平(0)"

#define mSetIn_TM1638_DIO (TM1638_DIO_DIR &= ~TM1638_DIO_IO) //配置引脚为"输入"
#define mRead_TM1638_DIO  (TM1638_DIO_IN & TM1638_DIO_IO ? 1 : 0)  //读取引脚"电平"

//--**P3.2 引脚: STB (片选)  ** -----------------------------------------//
#define TM1638_STB_DIR  (P3DIR)  
#define TM1638_STB_PORT (P3OUT)
#define TM1638_STB_IO   (BIT2)

	//配置引脚为"输出",并输出"高电平"
#define mHigh_TM1638_STB  {TM1638_STB_DIR |= TM1638_STB_IO; TM1638_STB_PORT |= TM1638_STB_IO;}      //引脚输出"高电平(1)"
	//配置引脚为"输出",并输出"低电平"
#define mLow_TM1638_STB   {TM1638_STB_DIR |= TM1638_STB_IO; TM1638_STB_PORT &= ~TM1638_STB_IO;}    //引脚输出"低电平(0)"

//--**P3.4 引脚: CLK (时钟输入) ** -----------------------------------//
#define TM1638_CLK_DIR  (P3DIR)  
#define TM1638_CLK_PORT (P3OUT)
#define TM1638_CLK_IO   (BIT4)

	//配置引脚为"输出",并输出"高电平"
#define mHigh_TM1638_CLK  {TM1638_CLK_DIR |= TM1638_CLK_IO; TM1638_CLK_PORT |= TM1638_CLK_IO;}      //引脚输出"高电平(1)"
	//配置引脚为"输出",并输出"低电平"
#define mLow_TM1638_CLK   {TM1638_CLK_DIR |= TM1638_CLK_IO; TM1638_CLK_PORT &= ~TM1638_CLK_IO;}    //引脚输出"低电平(0)"


	////////////////////////////////////////////////////////////////////////////
	//==**"LCD_Segment 段式LCD" 驱动器*IO口使用宏定义**========//

//--**P8.0 引脚:  LCD_Segment背光(1有效)** ---------------------------//
#define LCD_SEG_BackLight_DIR  (P8DIR)  
#define LCD_SEG_BackLight_PORT (P8OUT)
#define LCD_SEG_BackLight_IO   (BIT0)

	//配置引脚为"输出",并"打开"LCD_Segment 背光
#define mOpen_LCD_SEG_BackLight {LCD_SEG_BackLight_DIR |= LCD_SEG_BackLight_IO; LCD_SEG_BackLight_PORT |= LCD_SEG_BackLight_IO;}   
	//配置引脚为"输出",并"关闭"LCD_Segment 背光
#define mClose_LCD_SEG_BackLight {LCD_SEG_BackLight_DIR |= LCD_SEG_BackLight_IO; LCD_SEG_BackLight_PORT &= (~LCD_SEG_BackLight_IO);} 


//--**P5.5, P5.4, P5.3引脚:  用作LCD_B驱动引脚** ----------------------//
#define LCD_SEG_COM_SEL  (P5SEL)
#define LCD_SEG_COM_DIR  (P5DIR)  
#define LCD_SEG_COM_PORT (P5OUT)
#define LCD_SEG_COM_IO   (BIT3 + BIT4 + BIT5)

	//配置引脚为"外围模块功能"引脚
#define mSelect_LCD_SEG_FunctionPin (LCD_SEG_COM_SEL |= LCD_SEG_COM_IO) //P5.5, P5.4, P5.3 用作LCD_B驱动引脚(配置引脚为"外围模块功能"引脚 )
	//配置引脚为"通用数字IO"引脚
#define mSelect_LCD_SEG_IoPin (LCD_SEG_COM_SEL &= ~LCD_SEG_COM_IO) 

#define mSetOut_LCD_SEG_COM (LCD_SEG_COM_DIR |= LCD_SEG_COM_IO)   //设置引脚都为"输出"
#define mSetIn_LCD_SEG_COM (LCD_SEG_COM_DIR &= ~LCD_SEG_COM_IO)    //设置引脚都为"输入"

	//配置引脚为"输出",并输出"高电平"
#define mHigh_LCD_SEG_COM  {mSetOut_LCD_SEG_COM; LCD_SEG_COM_PORT |= LCD_SEG_COM_IO;}     
	//配置引脚为"输出",并输出"低电平"
#define mLow_LCD_SEG_COM   {mSetOut_LCD_SEG_COM; LCD_SEG_COM_PORT &= ~LCD_SEG_COM_IO;}   





	////////////////////////////////////////////////////////////////////////////
	//==**LCD_TFT 液晶显示器*IO口使用宏定义**===============//
//--**P5.2 引脚: 控制LCD_TFT背光** ----------------------------------//
	//根据引脚输出的占空比，调试背光亮度
#define LCD_TFT_BackLight_DIR  (P5DIR)  
#define LCD_TFT_BackLight_PORT (P5OUT)
#define LCD_TFT_BackLight_IO   (BIT2)

	//引脚: 输出高电平(占空比为100%)(此时背光最亮)
	//配置引脚为"输出",并"打开"LCD_TFT背光
#define mOpen_LCD_TFT_BackLight {LCD_TFT_BackLight_DIR |= LCD_TFT_BackLight_IO; LCD_TFT_BackLight_PORT |= LCD_TFT_BackLight_IO;}   

	//引脚: 输出低电平(占空比为  0%)(此时背光关闭)
	//配置引脚为"输出",并"关闭"LCD_TFT背光
#define mClose_LCD_TFT_BackLight {LCD_TFT_BackLight_DIR |= LCD_TFT_BackLight_IO; LCD_TFT_BackLight_PORT &= (~LCD_TFT_BackLight_IO);} 


//--**P2.6 引脚: LCD_TFT使能引脚CS ("低"有效)** -------------------//
#define LCD_TFT_CS_DIR  (P2DIR)  
#define LCD_TFT_CS_PORT (P2OUT)
#define LCD_TFT_CS_IO   (BIT6)

	//配置引脚都为"输出"
#define mSetOut_LCD_TFT_CS (LCD_TFT_CS_DIR |= LCD_TFT_CS_IO) 
	//输出"高"电平
#define mHigh_LCD_TFT_CS (LCD_TFT_CS_PORT |= LCD_TFT_CS_IO) 
	//输出"低"电平
#define mLow_LCD_TFT_CS  (LCD_TFT_CS_PORT &= ~LCD_TFT_CS_IO)
		//配置引脚为"输出",并"使能"LCD_TFT 模块(低电平有效)
#define mOpen_LCD_TFT_CS  {LCD_TFT_CS_DIR |= LCD_TFT_CS_IO; LCD_TFT_CS_PORT &= (~LCD_TFT_CS_IO);} 
		//配置引脚为"输出",并"禁用"LCD_TFT 模块
#define mClose_LCD_TFT_CS {LCD_TFT_CS_DIR |= LCD_TFT_CS_IO; LCD_TFT_CS_PORT |= LCD_TFT_CS_IO;} 
			
	//配置引脚为"输出" ,并"触发"CS引脚信号(产生下降沿)
#define mTrigger_LCD_TFT_CS {LCD_TFT_CS_DIR |= LCD_TFT_CS_IO; LCD_TFT_CS_PORT |= LCD_TFT_CS_IO; LCD_TFT_CS_PORT &= ~LCD_TFT_CS_IO;} 


//--**P2.7 引脚: 控制LCD_TFT复位** ----------------------------------//
#define LCD_TFT_Reset_DIR  (P2DIR)  
#define LCD_TFT_Reset_PORT (P2OUT)
#define LCD_TFT_Reset_IO   (BIT7)

	//配置引脚都为"输出"
#define mSetOut_LCD_TFT_Reset (LCD_TFT_Reset_DIR |= LCD_TFT_Reset_IO) 
	//输出"低"电平"==使能"复位功能(复位"低"电平有效)
#define mOpen_LCD_TFT_Reset  (LCD_TFT_Reset_PORT &= ~LCD_TFT_Reset_IO)  
	//输出"高"电平=="关闭"复位功能
#define mClose_LCD_TFT_Reset (LCD_TFT_Reset_PORT |= LCD_TFT_Reset_IO)


//--**P8.4 引脚: LCD_TFT 的时钟引脚CLK** -------------------//
#define LCD_TFT_CLK_SEL  (P8SEL)
#define LCD_TFT_CLK_DIR  (P8DIR)  
#define LCD_TFT_CLK_PORT (P8OUT)
#define LCD_TFT_CLK_IO   (BIT4)

	//配置引脚为通用数字"IO"引脚
#define mSelect_LCD_TFT_CLK_IoPin  (LCD_TFT_CLK_SEL &= ~LCD_TFT_CLK_IO) 
	//配置引脚都为"输出"
#define mSetOut_LCD_TFT_CLK (LCD_TFT_CLK_DIR |= LCD_TFT_CLK_IO) 
	//输出"高"电平
#define mHigh_LCD_TFT_CLK (LCD_TFT_CLK_PORT |= LCD_TFT_CLK_IO)   
	//输出"低"电平	
#define mLow_LCD_TFT_CLK  (LCD_TFT_CLK_PORT &= ~LCD_TFT_CLK_IO)   


//--**P8.5 引脚: LCD_TFT 的数据引脚SDA(MOSI)** -------------------//
#define LCD_TFT_SDA_SEL  (P8SEL)
#define LCD_TFT_SDA_DIR  (P8DIR)  
#define LCD_TFT_SDA_PORT (P8OUT)
#define LCD_TFT_SDA_IO   (BIT5)

	//配置引脚为通用数字"IO"引脚
#define mSelect_LCD_TFT_SDA_IoPin  (LCD_TFT_SDA_SEL &= ~LCD_TFT_SDA_IO) 
	//配置引脚都为"输出"
#define mSetOut_LCD_TFT_SDA (LCD_TFT_SDA_DIR |= LCD_TFT_SDA_IO) 
	//输出"高"电平
#define mHigh_LCD_TFT_SDA (LCD_TFT_SDA_PORT |= LCD_TFT_SDA_IO)
	//输出"低"电平
#define mLow_LCD_TFT_SDA  (LCD_TFT_SDA_PORT &= ~LCD_TFT_SDA_IO) 


//--**P8.6 引脚: LCD_TFT 的命令寄存器、数据寄存器选择引脚RS(A0)** -------------//
//0:  选择命令寄存器 //1: 选择数据寄存器
#define LCD_TFT_RS_SEL  (P8SEL)
#define LCD_TFT_RS_DIR  (P8DIR)  
#define LCD_TFT_RS_PORT (P8OUT)
#define LCD_TFT_RS_IO   (BIT6)

	//配置引脚为通用数字"IO"引脚
#define mSelect_LCD_TFT_RS_IoPin  (LCD_TFT_RS_SEL &= ~LCD_TFT_RS_IO) 
	//配置引脚都为"输出"
#define mSetOut_LCD_TFT_RS (LCD_TFT_RS_DIR |= LCD_TFT_RS_IO) 
	//输出"高"电平 //1: 选择数据寄存器
#define mHigh_LCD_TFT_RS (LCD_TFT_RS_PORT |= LCD_TFT_RS_IO) 
	//输出"低"电平 //0:  选择命令寄存器
#define mLow_LCD_TFT_RS  (LCD_TFT_RS_PORT &= ~LCD_TFT_RS_IO) 



	////////////////////////////////////////////////////////////////////////////
	//==**"A模块"多路复用器TS3A5017 模块*IO口使用宏定义**==========//

	//--**P7.5 引脚: 连接到多路复用器:引脚IN1** -------------------//
#define TS3A5017_A_IN1_DIR  (P7DIR)  
#define TS3A5017_A_IN1_PORT (P7OUT)
#define TS3A5017_A_IN1_IO   (BIT5)
			
#define mSetOut_TS3A5017_A_IN1 (TS3A5017_A_IN1_DIR |= TS3A5017_A_IN1_IO)   //设置IN1引脚都为"输出"
#define mHigh_TS3A5017_A_IN1   (TS3A5017_A_IN1_PORT |= TS3A5017_A_IN1_IO)    //引脚输出"高电平(1)"
#define mLow_TS3A5017_A_IN1    (TS3A5017_A_IN1_PORT &= (~TS3A5017_A_IN1_IO)) //引脚输出"低电平(0)"
			
#define mConfig_TS3A5017_A_IN1(IN1) {mSetOut_TS3A5017_A_IN1; IN1 ? mHigh_TS3A5017_A_IN1 : mLow_TS3A5017_A_IN1;} 
			
	//--**P7.4 引脚: 连接到多路复用器:引脚IN2** -------------------//
#define TS3A5017_A_IN2_DIR  (P7DIR)  
#define TS3A5017_A_IN2_PORT (P7OUT)
#define TS3A5017_A_IN2_IO   (BIT4)	
			
#define mSetOut_TS3A5017_A_IN2 (TS3A5017_A_IN2_DIR |= TS3A5017_A_IN2_IO)   //设置IN2引脚都为"输出"
#define mHigh_TS3A5017_A_IN2   (TS3A5017_A_IN2_PORT |= TS3A5017_A_IN2_IO)    //引脚输出"高电平(1)"
#define mLow_TS3A5017_A_IN2    (TS3A5017_A_IN2_PORT &= (~TS3A5017_A_IN2_IO)) //引脚输出"低电平(0)"
			
#define mConfig_TS3A5017_A_IN2(IN2) {mSetOut_TS3A5017_A_IN2; IN2 ? mHigh_TS3A5017_A_IN2 : mLow_TS3A5017_A_IN2;} 
		



	////////////////////////////////////////////////////////////////////////////
	//==**"B 模块"多路复用器TS3A5017*IO口使用宏定义**==========//
//--**P1.7 引脚: 连接到多路复用器:引脚IN1** -------------------//
#define TS3A5017_B_IN1_DIR  (P1DIR)  
#define TS3A5017_B_IN1_PORT (P1OUT)
#define TS3A5017_B_IN1_IO   (BIT7)
	
#define mSetOut_TS3A5017_B_IN1 (TS3A5017_B_IN1_DIR |= TS3A5017_B_IN1_IO)   //设置IN1引脚都为"输出"
#define mHigh_TS3A5017_B_IN1   (TS3A5017_B_IN1_PORT |= TS3A5017_B_IN1_IO)    //引脚输出"高电平(1)"
#define mLow_TS3A5017_B_IN1    (TS3A5017_B_IN1_PORT &= (~TS3A5017_B_IN1_IO)) //引脚输出"低电平(0)"
	
#define mConfig_TS3A5017_B_IN1(IN1) {mSetOut_TS3A5017_B_IN1; IN1 ? mHigh_TS3A5017_B_IN1 : mLow_TS3A5017_B_IN1;} 
	
//--**P1.6 引脚: 连接到多路复用器:引脚IN2** -------------------//
#define TS3A5017_B_IN2_DIR  (P1DIR)  
#define TS3A5017_B_IN2_PORT (P1OUT)
#define TS3A5017_B_IN2_IO   (BIT6)	
	
#define mSetOut_TS3A5017_B_IN2 (TS3A5017_B_IN2_DIR |= TS3A5017_B_IN2_IO)   //设置IN2引脚都为"输出"
#define mHigh_TS3A5017_B_IN2   (TS3A5017_B_IN2_PORT |= TS3A5017_B_IN2_IO)    //引脚输出"高电平(1)"
#define mLow_TS3A5017_B_IN2    (TS3A5017_B_IN2_PORT &= (~TS3A5017_B_IN2_IO)) //引脚输出"低电平(0)"
	
#define mConfig_TS3A5017_B_IN2(IN2) {mSetOut_TS3A5017_B_IN2; IN2 ? mHigh_TS3A5017_B_IN2 : mLow_TS3A5017_B_IN2;} 






	////////////////////////////////////////////////////////////////////////////
	//==**"CD405x_Multiplexer多路选择模拟开关" *IO口使用宏定义**=//
//--**P2.4 引脚: 连接到CD405x: 引脚INH** ---------------------------//
//#define CD405x_INH_DIR  (P2DIR)  
//#define CD405x_INH_PORT (P2OUT)
//#define CD405x_INH_IO   (BIT4)	

	//配置引脚为"输出",并"使能"CD405x 模块("低"电平有效)
//#define mOpen_CD405x_INH {CD405x_INH_DIR |= CD405x_INH_IO; CD405x_INH_PORT &= ~CD405x_INH_IO;}   
	//配置引脚为"输出",并"禁用"CD405x 模块("高"电平有效)
//#define mClose_CD405x_INH {CD405x_INH_DIR |= CD405x_INH_IO; CD405x_INH_PORT |= CD405x_INH_IO;}   


//--**P2.5 引脚: 连接到CD405x: 引脚A** -----------------------------//
#define CD405x_A_DIR  (P2DIR)  
#define CD405x_A_PORT (P2OUT)
#define CD405x_A_IO   (BIT5)	

#define mSetOut_CD405x_A (CD405x_A_DIR |= CD405x_A_IO)   //设置引脚都为"输出"
#define mHigh_CD405x_A   (CD405x_A_PORT |= CD405x_A_IO)    //引脚输出"高电平(1)"
#define mLow_CD405x_A    (CD405x_A_PORT &= (~CD405x_A_IO)) //引脚输出"低电平(0)"

#define mConfig_CD405x_A(n) {mSetOut_CD405x_A; n ? mHigh_CD405x_A : mLow_CD405x_A;} 



//--**P2.0 引脚: 连接到CD405x: 引脚B** -----------------------------//
#define CD405x_B_DIR  (P2DIR)  
#define CD405x_B_PORT (P2OUT)
#define CD405x_B_IO   (BIT0)

#define mSetOut_CD405x_B (CD405x_B_DIR |= CD405x_B_IO)   //设置引脚都为"输出"
#define mHigh_CD405x_B   (CD405x_B_PORT |= CD405x_B_IO)    //引脚输出"高电平(1)"
#define mLow_CD405x_B    (CD405x_B_PORT &= (~CD405x_B_IO)) //引脚输出"低电平(0)"

#define mConfig_CD405x_B(n) {mSetOut_CD405x_B; n ? mHigh_CD405x_B : mLow_CD405x_B;} 


	////////////////////////////////////////////////////////////////////////////
	//==**"DC_Motor 直流电机"*IO口使用宏定义**================//
//--**P2.5引脚: 连接到"DRV8833 ": 引脚nSleep** --DC_Motor-------------//
#define DC_Motor_nSleep_DIR  (P2DIR)  
#define DC_Motor_nSleep_PORT (P2OUT)
#define DC_Motor_nSleep_IO   (BIT5)

	//配置引脚为"输出",并"使能"器件("高"电平有效)
#define mOpen_DC_Motor_nSleep {DC_Motor_nSleep_DIR |= DC_Motor_nSleep_IO; DC_Motor_nSleep_PORT |= DC_Motor_nSleep_IO;}   

	//配置引脚为"输出",并"禁止"器件(低：进入低功耗)
#define mClose_DC_Motor_nSleep {DC_Motor_nSleep_DIR |= DC_Motor_nSleep_IO; DC_Motor_nSleep_PORT &= ~DC_Motor_nSleep_IO;}   


//--**P3.6引脚: 连接到"DRV8833 ": 引脚AIN1和BIN1** --DC_Motor-----//
#define DC_Motor_AIN1_BIN1_SEL  (P3SEL)
#define DC_Motor_AIN1_BIN1_DIR  (P3DIR)  
#define DC_Motor_AIN1_BIN1_PORT (P3OUT)
#define DC_Motor_AIN1_BIN1_IO   (BIT6)

	//配置引脚为"输出",并输出"高"电平
#define mHigh_DC_Motor_AIN1_BIN1 {DC_Motor_AIN1_BIN1_DIR |= DC_Motor_AIN1_BIN1_IO; DC_Motor_AIN1_BIN1_PORT |= DC_Motor_AIN1_BIN1_IO;}   
	//配置引脚为"输出",并输出"低"电平
#define mLow_DC_Motor_AIN1_BIN1 {DC_Motor_AIN1_BIN1_DIR |= DC_Motor_AIN1_BIN1_IO; DC_Motor_AIN1_BIN1_PORT &= ~DC_Motor_AIN1_BIN1_IO;}   
	//配置引脚为"外围模块功能"引脚
#define mSelect_DC_Motor_AIN1_BIN1_FunctionPin (DC_Motor_AIN1_BIN1_SEL |= DC_Motor_AIN1_BIN1_IO) //配置引脚为"外围模块功能"引脚 
	//配置引脚都为"输出"
#define mSetOut_DC_Motor_AIN1_BIN1 (DC_Motor_AIN1_BIN1_DIR |= DC_Motor_AIN1_BIN1_IO)   


//--**P3.7 引脚: 连接到"DRV8833 ": 引脚AIN2和BIN2** --DC_Motor-----//
#define DC_Motor_AIN2_BIN2_SEL  (P3SEL)
#define DC_Motor_AIN2_BIN2_DIR  (P3DIR)  
#define DC_Motor_AIN2_BIN2_PORT (P3OUT)
#define DC_Motor_AIN2_BIN2_IO   (BIT7)

	//配置引脚为"输出",并输出"高"电平
#define mHigh_DC_Motor_AIN2_BIN2 {DC_Motor_AIN2_BIN2_DIR |= DC_Motor_AIN2_BIN2_IO; DC_Motor_AIN2_BIN2_PORT |= DC_Motor_AIN2_BIN2_IO;}   
	//配置引脚为"输出",并输出"低"电平
#define mLow_DC_Motor_AIN2_BIN2 {DC_Motor_AIN2_BIN2_DIR |= DC_Motor_AIN2_BIN2_IO; DC_Motor_AIN2_BIN2_PORT &= ~DC_Motor_AIN2_BIN2_IO;}   
	//配置引脚为"外围模块功能"引脚
#define mSelect_DC_Motor_AIN2_BIN2_FunctionPin (DC_Motor_AIN2_BIN2_SEL |= DC_Motor_AIN2_BIN2_IO)  //配置引脚为"外围模块功能"引脚 
	//配置引脚都为"输出"
#define mSetOut_DC_Motor_AIN2_BIN2 (DC_Motor_AIN2_BIN2_DIR |= DC_Motor_AIN2_BIN2_IO)   


//--**P3.3引脚** 作为转速计数输入引脚TA1_CCR2**--DC_Motor----//
#define DC_Motor_CCR3_SEL  (P3SEL)
#define DC_Motor_CCR3_DIR  (P3DIR)  
#define DC_Motor_CCR3_IO   (BIT3)

#define mSelect_DC_Motor_CCR3 (DC_Motor_CCR3_SEL |= DC_Motor_CCR3_IO) //配置引脚为"外围模块功能"引脚
#define mSetIn_DC_Motor_CCR3 (DC_Motor_CCR3_DIR &= (~DC_Motor_CCR3_IO))  //配置引脚为"输入"





	////////////////////////////////////////////////////////////////////////////
	//==**"Step_Motor 步进电机"*IO口使用宏定义**===============//
//--**P2.0 引脚: 连接到"DRV8833 ": 引脚nSleep** --Step_Motor-------------//
#define Step_Motor_nSleep_DIR  (P2DIR)  
#define Step_Motor_nSleep_PORT (P2OUT)
#define Step_Motor_nSleep_IO   (BIT0)

	//配置引脚为"输出",并"使能"器件("高"电平有效)
#define mOpen_Step_Motor_nSleep {Step_Motor_nSleep_DIR |= Step_Motor_nSleep_IO; Step_Motor_nSleep_PORT |= Step_Motor_nSleep_IO;}   

	//配置引脚为"输出",并"禁止"器件(低：进入低功耗)
#define mClose_Step_Motor_nSleep {Step_Motor_nSleep_DIR |= Step_Motor_nSleep_IO; Step_Motor_nSleep_PORT &= ~Step_Motor_nSleep_IO;}   


//--**P2.4引脚: 连接到"DRV8833 ": 引脚AIN1** --Step_Motor-----//
#define Step_Motor_AIN1_DIR  (P2DIR)  
#define Step_Motor_AIN1_PORT (P2OUT)
#define Step_Motor_AIN1_IO   (BIT4)

	//配置引脚为"输出",并输出"高"电平
#define mHigh_Step_Motor_AIN1 {Step_Motor_AIN1_DIR |= Step_Motor_AIN1_IO; Step_Motor_AIN1_PORT |= Step_Motor_AIN1_IO;}   
	//配置引脚为"输出",并输出"低"电平
#define mLow_Step_Motor_AIN1 {Step_Motor_AIN1_DIR |= Step_Motor_AIN1_IO; Step_Motor_AIN1_PORT &= ~Step_Motor_AIN1_IO;}   


//--**P2. 3引脚: 连接到"DRV8833 ": 引脚AIN2** --Step_Motor-----------//
#define Step_Motor_AIN2_DIR  (P2DIR)  
#define Step_Motor_AIN2_PORT (P2OUT)
#define Step_Motor_AIN2_IO   (BIT3)

	//配置引脚为"输出",并输出"高"电平
#define mHigh_Step_Motor_AIN2 {Step_Motor_AIN2_DIR |= Step_Motor_AIN2_IO; Step_Motor_AIN2_PORT |= Step_Motor_AIN2_IO;}   
	//配置引脚为"输出",并输出"低"电平
#define mLow_Step_Motor_AIN2 {Step_Motor_AIN2_DIR |= Step_Motor_AIN2_IO; Step_Motor_AIN2_PORT &= ~Step_Motor_AIN2_IO;}   



//--**P3.6 脚: 连接到"DRV8833 ": 引脚BIN1** --Step_Motor-----//
#define Step_Motor_BIN1_SEL  (P3SEL)
#define Step_Motor_BIN1_DIR  (P3DIR)  
#define Step_Motor_BIN1_PORT (P3OUT)
#define Step_Motor_BIN1_IO   (BIT6)

		//配置引脚为"IO"引脚
#define mSelect_Step_Motor_BIN1_IoPin (Step_Motor_BIN1_SEL &= ~Step_Motor_BIN1_IO)  //配置引脚为"IO"引脚

	//配置引脚为"输出",并输出"高"电平
#define mHigh_Step_Motor_BIN1 {Step_Motor_BIN1_DIR |= Step_Motor_BIN1_IO; Step_Motor_BIN1_PORT |= Step_Motor_BIN1_IO;}   
	//配置引脚为"输出",并输出"低"电平
#define mLow_Step_Motor_BIN1 {Step_Motor_BIN1_DIR |= Step_Motor_BIN1_IO; Step_Motor_BIN1_PORT &= ~Step_Motor_BIN1_IO;}   



//--**P3.7 引脚: 连接到"DRV8833 ": 引脚BIN2** --Step_Motor-----//
#define Step_Motor_BIN2_SEL  (P3SEL)
#define Step_Motor_BIN2_DIR  (P3DIR)  
#define Step_Motor_BIN2_PORT (P3OUT)
#define Step_Motor_BIN2_IO   (BIT7)
	//配置引脚为"IO"引脚
#define mSelect_Step_Motor_BIN2_IoPin (Step_Motor_BIN2_SEL &= ~Step_Motor_BIN2_IO)  //配置引脚为"IO"引脚

	//配置引脚为"输出",并输出"高"电平
#define mHigh_Step_Motor_BIN2 {Step_Motor_BIN2_DIR |= Step_Motor_BIN2_IO; Step_Motor_BIN2_PORT |= Step_Motor_BIN2_IO;}   
	//配置引脚为"输出",并输出"低"电平
#define mLow_Step_Motor_BIN2 {Step_Motor_BIN2_DIR |= Step_Motor_BIN2_IO; Step_Motor_BIN2_PORT &= ~Step_Motor_BIN2_IO;}   


//--**P3.3引脚** 作为转速计数输入引脚TA1_CCR2**--Step_Motor----//
#define Step_Motor_CCR3_SEL  (P3SEL)
#define Step_Motor_CCR3_DIR  (P3DIR)  
#define Step_Motor_CCR3_IO   (BIT3)

#define mSelect_Step_Motor_CCR3 (Step_Motor_CCR3_SEL |= Step_Motor_CCR3_IO) //配置引脚为"外围模块功能"引脚
#define mSetIn_Step_Motor_CCR3 (Step_Motor_CCR3_DIR &= (~Step_Motor_CCR3_IO))  //配置引脚为"输入"



	////////////////////////////////////////////////////////////////////////////
	//==**CC1101 模块*IO口使用宏定义**=========================//
//--**PJ.1 引脚: CC1101 模块的使能引脚CS** ----------------------//
#define CC1101_CS_DIR  (PJDIR)  
#define CC1101_CS_PORT (PJOUT)
#define CC1101_CS_IO   (BIT1)
	//配置引脚为"输出",并"使能"CC1101 模块(低电平有效)
#define mOpen_CC1101_CS  {CC1101_CS_DIR |= CC1101_CS_IO; CC1101_CS_PORT &= (~CC1101_CS_IO);} 

	//配置引脚为"输出",并"禁用"CC1101 模块
#define mClose_CC1101_CS {CC1101_CS_DIR |= CC1101_CS_IO; CC1101_CS_PORT |= CC1101_CS_IO;} 


	////////////////////////////////////////////////////////////////////////////
	//==**SD卡模块*IO口使用宏定义**=========================//
//--**PJ.0 引脚: SD卡模块的使能引脚CS** ----------------------//
#define SDcard_CS_DIR  (PJDIR)  
#define SDcard_CS_PORT (PJOUT)
#define SDcard_CS_IO   (BIT0)
	//配置引脚为"输出",并"使能"SD卡模块(低电平有效)
#define mOpen_SDcard_CS  {SDcard_CS_DIR |= SDcard_CS_IO; SDcard_CS_PORT &= (~SDcard_CS_IO);} 

	//配置引脚为"输出",并"禁用"SD卡 模块
#define mClose_SDcard_CS {SDcard_CS_DIR |= SDcard_CS_IO; SDcard_CS_PORT |= SDcard_CS_IO;} 
		

	////////////////////////////////////////////////////////////////////////////
	//==**SPI 各个模块，使能控制**=========================//
	//SPI用于驱动LCD_TFT时，要禁用其他用到SPI的模块
#define mSPI_Select_LCD_TFT {mOpen_LCD_TFT_CS; mClose_CC1101_CS; mClose_SDcard_CS;}              	
	//SPI用于驱动CC1101时，要禁用其他用到SPI的模块
#define mSPI_Select_CC1101  {mOpen_CC1101_CS; mClose_LCD_TFT_CS; mClose_SDcard_CS;}    
	//SPI用于驱动SD卡时，要禁用其他用到SPI的模块
#define mSPI_Select_SDcard  {mOpen_SDcard_CS; mClose_LCD_TFT_CS; mClose_CC1101_CS;}    

	//驱动LCD_segment和IIC(TMP006)时，要禁用所有用到SPI_B的模块
#define mSPI_All_Disable  {mClose_LCD_TFT_CS; mClose_CC1101_CS; mClose_SDcard_CS;}    






////////////////////////////////////////////////////////////////////////////
//==**项目"专用"宏定义**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**"函数"宏定义**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"函数声明**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"外部" API 函数声明**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////




#endif  /* __Hardware_Profile_H */






