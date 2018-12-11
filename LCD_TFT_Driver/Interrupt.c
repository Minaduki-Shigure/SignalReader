/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 Interrupt.c
* 附属文件-Dependencies:  	 DC_Motor.h;  HR202_Humidity.h;  MyProject.h; System.h;
								 msp430f6638.h; Hardware_Profile.h; Generic.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■ 中断处理程序(处理器内部资源) -Interrupt service routine 
	01)      02)     03)    04)    05)    06)	
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


#include "msp430f6638.h"   // "处理器"头文件: 内部寄存相关定义等

#include "System.h"	 //"系统" 常用功能函数集-头文件

#include "MyProject.h"	//具体项目: 总功能程序-头文件

#include "HR202_Humidity.h"   //"HR202_Humidity 电阻型湿度传感器" -驱动程序(外部资源)-头文件

#include "Step_Motor.h"   //"Step_Motor 步进电机" -驱动程序(外部资源)-头文件

#include "DC_Motor.h"   //"DC_Motor 直流电机"-驱动程序(外部资源)-头文件

#include "UART.h"   //"UART 通用异步接收/发送装置" -驱动程序(内部资源)-头文件

#include "Speaker.h"   //"Speaker 扬声器" -驱动程序(外部资源)-头文件


////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////

/****************************************************************************
*函数名-Function:	__interrupt void TIMER0_B1_ISR(void)  // Timer0_B1  中断处理程序
*描述- Description:		系统每 " 1ms"中断一次作为基本中断时基
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01) TIMER0_B使用两个中断向量,CCR0优先级最高占用B0_VECTOR;  
	▲02) TIMER0_B的溢出中断和CCR1 CCR2 CCR3 CCR4 CCR5 CCR6占用B1_VECTOR 
	▲03) 其中B1_VECTOR这7个中断又通过TBIV中断向量寄存器，
		     来区分哪个产生中断，并有优先级。     
	▲04) 
*******************************************************
#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void)  // Timer0_B1  中断处理程序
{
	switch( __even_in_range(TBIV,14) )
	{
		case  0: break; 						 // No interrupt
		case  2: break; 						 // CCR1 not used
		case  4: break; 						 // CCR2 not used
		case  6: break; 						 // CCR3 not used
		case  8: break; 						 // CCR4 not used
		case 10: break; 						 // CCR5 not used
		case 12: break; 						 // CCR6 not used
		
		case 14:   //14对应定时器溢出时，在中断向量寄存器TBIV的值	
			System_Clock();  //通用"系统时钟"处理: 产生定时为1ms,10ms, 20ms, 100ms,等
			break;
			
		default: break;
	}
}
**********************/

/****************************************************************************
*函数名-Function:	__interrupt void TIMER0_A1_ISR(void)  // Timer0_A1 中断处理程序
*描述- Description:		系统每 " 1ms"中断一次作为基本中断时基
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01) TIMERA使用两个中断向量,CCR0优先级最高占用A0_VECTOR;  
	▲02) TIMERA的溢出中断和CCR1 CCR2占用A1_VECTOR 
	▲03) 其中A1_VECTOR这三个中断又通过TAIV中断向量寄存器，
		     区分哪个产生中断，并有优先级。     
	▲04) 
*****************************************************************************/
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void)  // Timer0_A1 中断处理程序
{
	switch(__even_in_range(TA0IV,14))
	{
		case  0: break; 						 // No interrupt
		case  2: break; 						 // CCR1 not used
		case  4: break; 						 // CCR2 not used
		case  6: break; 						 // reserved
		case  8: break; 						 // reserved
		case 10: break; 						 // reserved
		case 12: break; 						 // reserved
		
		case 14:   //14对应定时器溢出时，在中断向量寄存器TA2IV的值	
			System_Clock();  //通用"系统时钟"处理: 产生定时为1ms,10ms, 20ms, 100ms,等
			
			break;
			
		default: break;
	}
}





/****************************************************************************
*函数名-Function:	__interrupt void TIMER2_A1_ISR(void)  // Timer2_A1 中断处理程序
*描述- Description:		系统每 " 1ms"中断一次作为基本中断时基
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01) TIMERA使用两个中断向量,CCR0优先级最高占用A0_VECTOR;  
	▲02) TIMERA的溢出中断和CCR1 CCR2占用A1_VECTOR 
	▲03) 其中A1_VECTOR这三个中断又通过TAIV中断向量寄存器，
		     区分哪个产生中断，并有优先级。     
	▲04) 
******************************************
#pragma vector=TIMER2_A1_VECTOR
__interrupt void TIMER2_A1_ISR(void)  // Timer2_A1 中断处理程序
{
	switch(__even_in_range(TA2IV,14))
	{
		case  0: break; 						 // No interrupt
		case  2: break; 						 // CCR1 not used
		case  4: break; 						 // CCR2 not used
		case  6: break; 						 // reserved
		case  8: break; 						 // reserved
		case 10: break; 						 // reserved
		case 12: break; 						 // reserved
		
		case 14:   //14对应定时器溢出时，在中断向量寄存器TA2IV的值	
			System_Clock();  //通用"系统时钟"处理: 产生定时为1ms,10ms, 20ms, 100ms,等
			
			break;
			
		default: break;
	}
}
***********************************/



/****************************************************************************
*函数名-Function:	__interrupt void TIMER1_A1_ISR(void)
*描述- Description:		TIMER1 中断服务程序(TIMERA的溢出中断和CCR1 CCR2 CCR3占用A1_VECTOR)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR(void) //TIMER1_CCR2 中断
{
	switch(__even_in_range(TA1IV,14))
	{
		case  0: break;      // No interrupt
		case  2: break;      // CCR1 not used
			                               
		case  4:      // CCR2 used
			if(G_MainState == MAIN_Step_Motor_Test)  //"Step_Motor 步进电机"
			{
		//Sample_Step_Motor_Frequency();//采样"Step_Motor 步进电机"转速(1s内的脉冲次数)
			}
			else if(G_MainState == MAIN_DC_Motor_Test) //"DC_Motor 直流电机"
			{
				Sample_DC_Motor_Frequency();//采样"DC_Motor 直流电机"转速(1s内的脉冲次数)
			}
			else //在测试直流电机、步进电机时，因为引脚复用（CCR3），故在测试电机时，不采样湿度对应的频率
			{
				Sample_HR202_Frequency();//采样"湿度值"相应频率值
			}
			break; 

		case  6: break;    // CCR3  not  used
		case  8: break;                          // reserved
		case 10: break;                          // reserved
		case 12: break;                          // reserved
		case 14: 
			if(G_WorkState == WORK_Speaker_Test)
			{
				Deal_Song_Beat_Speaker(); //控制播放歌曲的音符和节拍 -- "Speaker 扬声器" 
			}
			break;   //未使用//溢出中断 // overflow

		default: break;
	}
}



/****************************************************************************
*函数名-Function:	__interrupt void TIMER2_A0_ISR(void)
*描述- Description:		TIMER2 中断服务程序(CCR0占用)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
#pragma vector=TIMER2_A0_VECTOR
__interrupt void TIMER2_A0_ISR(void)
{
	Deal_Step_Motor();  //中断中处理步进电机(正反转,转速)
}



/****************************************************************************
*函数名-Function:	__interrupt void USCI_A1_ISR(void)
*描述- Description:		USCI_A1 中断服务程序
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
	switch(__even_in_range(UCA1IV,4))
	{
		case 0: break;                  // Vector 0 - no interrupt
		case 2:
			if(G_MainState == MAIN_RS232_UART)//Main█RS232_UART 菜单选择(工作时)
			{
				while (!(UCA1IFG&UCTXIFG));
				UCA1TXBUF = UCA1RXBUF;
				G_RxData_RS232 = UCA1RXBUF;
			}

			else if(G_MainState == MAIN_RS485_UART)//Main█RS485_UART 菜单选择(工作时)
			{
				
					//while (!(UCA1IFG&UCTXIFG));
					
					//DE;  // 设置485芯片处于发送状态
					//WaitingDelayMs(1);

				G_RxData_RS485 = UCA1RXBUF;
				
					//UCA1TXBUF = UCA1RXBUF;
					
					//WaitingDelayMs(1);
					//RE;  // 设置485芯片处于接收状态	
			}
			break;

		case 4: break;            // Vector 4 - TXIFG
		default: break;
	}

}


/****************************************************************************
*函数名-Function:	__interrupt void TIMER1_A0_ISR(void)
*描述- Description:		TIMER1_A0 中断服务程序-- 根据特定音符生成对应频率的波形 
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01)(TIMERA的溢出中断和CCR0 占用A0_VECTOR)
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)  // 根据特定音符生成对应频率的波形 
{
	if(G_WorkState == WORK_Speaker_Test)
	{
		Deal_Song_Tone_Speaker();  //根据特定音符生成对应频率的波形-- "Speaker 扬声器"  
	}
	else 
	{
		Deal_Buzz_Speaker();  //处理蜂鸣器 -- "Speaker 扬声器" 
	}
}


/****************************************************************************
*函数名-Function:	__interrupt void TIMER1_A1_ISR(void)
*描述- Description:		TIMER1_A1 中断服务程序--控制播放歌曲的音符和节拍 
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01)(TIMERA的溢出中断和CCR1 CCR2占用A1_VECTOR)
	▲02)    ▲03)    ▲04)  
****************************************************
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR(void)   //控制播放歌曲的音符和节拍 
{
	switch(__even_in_range(TA1IV,14))
	{
		case  0: break;    // 无中断            // No interrupt
		case  2: break;    // CCR1 未使用   // CCR1 not used
		case  4: break;    // CCR2 未使用   // CCR2 not used
		case  6: break;    // 保留                  // reserved
		case  8: break;    // 保留                  // reserved
		case 10: break;    // 保留                  // reserved
		case 12: break;    // 保留                  // reserved
		case 14:		   //溢出中断 // overflow
			if(G_WorkState == WORK_Speaker_Test)
			{
				Deal_Song_Beat_Speaker(); //控制播放歌曲的音符和节拍 -- "Speaker 扬声器" 
			}
			break;
		default: break;
	}
}
*************************/




/****************************************************************************
*函数名-Function:	__interrupt void USCI_B1_ISR(void)
*描述- Description:		SPI_B 中断服务程序
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01) 	▲02) 	▲03) 	▲04) 
***************************************************
#pragma vector=USCI_B1_VECTOR
__interrupt void USCI_B1_ISR(void)
{
	switch(__even_in_range(UCB1IV,4))
	{
		case 0:break;                             // Vector 0 - no interrupt
		
		case 2: // Vector 2 - RXIFG //接收中断标志。UCxRXBUF接收到1个完整字符时，UCRXIFG置位。                   
//G_TempChar = UCB1RXBUF;
		
			//while (!(UCB1IFG&UCTXIFG));             // USCI_B1 TX buffer ready?
			//UCB0TXBUF = UCB0RXBUF;
			break;
			
		case 4: // Vector 4 - TXIFG //发送中断标志位。当UCxTXBUF为空时，UCTXIFG置位。
			break;                             

		default: break;
	}
}
**************************/





/****************************************************************************
*函数名-Function:	__interrupt void RTC_ISR(void)// RTC_B 中断处理程序
*描述- Description:	系统每 "500us = 0.5ms"中断一次作为基本中断时基
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：		▲01) 	▲02) 	▲03) 	▲04) 
*******************************************************

#pragma vector=RTC_VECTOR
__interrupt void RTC_ISR(void)
{
    switch (__even_in_range(RTCIV, RTC_RT1PSIFG))
    {
        // Vector RTC_NONE：无中断挂起
        case RTC_NONE:  // Vector RTC_NONE: No Interrupt pending
            break;

        // Vector RTC_RTCRDYIFG：RTC就绪
        case RTC_RTCRDYIFG:   // Vector RTC_RTCRDYIFG: RTC ready

// 	LED_OUT ^= Green_LED;	// 绿灯每秒闪烁一次	// Toggle green LED every second
//if(alarmflag == 1)	// 每周一早上7点整报警，红灯每秒闪烁一次
//	LED_OUT ^= Red_LED; // Toggle RED LED every second when time is up to 7:00am on 1st day of week
            break;

		// Vector RTC_RTCTEVIFG：RTC间隔定时器，由于配置时间事件为每分钟改变一次，
		// 即每分钟都会置位该中断标志位，跳入到此状态
        case RTC_RTCTEVIFG:   // Vector RTC_RTCTEVIFG: RTC interval timer
			break;

        // Vector RTC_RTCAIFG：RTC用户报警
        case RTC_RTCAIFG:  // Vector RTC_RTCAIFG: RTC user alarm
//	alarmflag = 1;	// 每周一早上7点整报警，进此入口// Interrupts 7:00am on 1st day of week
            break;

        // Vector RTC_RT0PSIFG：RTC预分频器0
        case RTC_RT0PSIFG: // Vector RTC_RT0PSIFG: RTC prescaler 0
			break;

        // Vector RTC_RT1PSIFG：RTC预分频器1
        case RTC_RT1PSIFG: // Vector RTC_RT1PSIFG: RTC prescaler 1

			break;

        // Default case
        default:
            break;
    }
}
**********************/






