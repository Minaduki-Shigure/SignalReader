/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 Interrupt.c
* �����ļ�-Dependencies:  	 DC_Motor.h;  HR202_Humidity.h;  MyProject.h; System.h;
								 msp430f6638.h; Hardware_Profile.h; Generic.h;
* �ļ�����-File Description:	 ( Դ����-Source File) 
	�� �жϴ������(�������ڲ���Դ) -Interrupt service routine 
	01)      02)     03)    04)    05)    06)	
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


#include "msp430f6638.h"   // "������"ͷ�ļ�: �ڲ��Ĵ���ض����

#include "System.h"	 //"ϵͳ" ���ù��ܺ�����-ͷ�ļ�

#include "MyProject.h"	//������Ŀ: �ܹ��ܳ���-ͷ�ļ�

#include "HR202_Humidity.h"   //"HR202_Humidity ������ʪ�ȴ�����" -��������(�ⲿ��Դ)-ͷ�ļ�

#include "Step_Motor.h"   //"Step_Motor �������" -��������(�ⲿ��Դ)-ͷ�ļ�

#include "DC_Motor.h"   //"DC_Motor ֱ�����"-��������(�ⲿ��Դ)-ͷ�ļ�

#include "UART.h"   //"UART ͨ���첽����/����װ��" -��������(�ڲ���Դ)-ͷ�ļ�

#include "Speaker.h"   //"Speaker ������" -��������(�ⲿ��Դ)-ͷ�ļ�


////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////

/****************************************************************************
*������-Function:	__interrupt void TIMER0_B1_ISR(void)  // Timer0_B1  �жϴ������
*����- Description:		ϵͳÿ " 1ms"�ж�һ����Ϊ�����ж�ʱ��
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) TIMER0_Bʹ�������ж�����,CCR0���ȼ����ռ��B0_VECTOR;  
	��02) TIMER0_B������жϺ�CCR1 CCR2 CCR3 CCR4 CCR5 CCR6ռ��B1_VECTOR 
	��03) ����B1_VECTOR��7���ж���ͨ��TBIV�ж������Ĵ�����
		     �������ĸ������жϣ��������ȼ���     
	��04) 
*******************************************************
#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void)  // Timer0_B1  �жϴ������
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
		
		case 14:   //14��Ӧ��ʱ�����ʱ�����ж������Ĵ���TBIV��ֵ	
			System_Clock();  //ͨ��"ϵͳʱ��"����: ������ʱΪ1ms,10ms, 20ms, 100ms,��
			break;
			
		default: break;
	}
}
**********************/

/****************************************************************************
*������-Function:	__interrupt void TIMER0_A1_ISR(void)  // Timer0_A1 �жϴ������
*����- Description:		ϵͳÿ " 1ms"�ж�һ����Ϊ�����ж�ʱ��
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) TIMERAʹ�������ж�����,CCR0���ȼ����ռ��A0_VECTOR;  
	��02) TIMERA������жϺ�CCR1 CCR2ռ��A1_VECTOR 
	��03) ����A1_VECTOR�������ж���ͨ��TAIV�ж������Ĵ�����
		     �����ĸ������жϣ��������ȼ���     
	��04) 
*****************************************************************************/
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void)  // Timer0_A1 �жϴ������
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
		
		case 14:   //14��Ӧ��ʱ�����ʱ�����ж������Ĵ���TA2IV��ֵ	
			System_Clock();  //ͨ��"ϵͳʱ��"����: ������ʱΪ1ms,10ms, 20ms, 100ms,��
			
			break;
			
		default: break;
	}
}





/****************************************************************************
*������-Function:	__interrupt void TIMER2_A1_ISR(void)  // Timer2_A1 �жϴ������
*����- Description:		ϵͳÿ " 1ms"�ж�һ����Ϊ�����ж�ʱ��
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01) TIMERAʹ�������ж�����,CCR0���ȼ����ռ��A0_VECTOR;  
	��02) TIMERA������жϺ�CCR1 CCR2ռ��A1_VECTOR 
	��03) ����A1_VECTOR�������ж���ͨ��TAIV�ж������Ĵ�����
		     �����ĸ������жϣ��������ȼ���     
	��04) 
******************************************
#pragma vector=TIMER2_A1_VECTOR
__interrupt void TIMER2_A1_ISR(void)  // Timer2_A1 �жϴ������
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
		
		case 14:   //14��Ӧ��ʱ�����ʱ�����ж������Ĵ���TA2IV��ֵ	
			System_Clock();  //ͨ��"ϵͳʱ��"����: ������ʱΪ1ms,10ms, 20ms, 100ms,��
			
			break;
			
		default: break;
	}
}
***********************************/



/****************************************************************************
*������-Function:	__interrupt void TIMER1_A1_ISR(void)
*����- Description:		TIMER1 �жϷ������(TIMERA������жϺ�CCR1 CCR2 CCR3ռ��A1_VECTOR)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR(void) //TIMER1_CCR2 �ж�
{
	switch(__even_in_range(TA1IV,14))
	{
		case  0: break;      // No interrupt
		case  2: break;      // CCR1 not used
			                               
		case  4:      // CCR2 used
			if(G_MainState == MAIN_Step_Motor_Test)  //"Step_Motor �������"
			{
		//Sample_Step_Motor_Frequency();//����"Step_Motor �������"ת��(1s�ڵ��������)
			}
			else if(G_MainState == MAIN_DC_Motor_Test) //"DC_Motor ֱ�����"
			{
				Sample_DC_Motor_Frequency();//����"DC_Motor ֱ�����"ת��(1s�ڵ��������)
			}
			else //�ڲ���ֱ��������������ʱ����Ϊ���Ÿ��ã�CCR3�������ڲ��Ե��ʱ��������ʪ�ȶ�Ӧ��Ƶ��
			{
				Sample_HR202_Frequency();//����"ʪ��ֵ"��ӦƵ��ֵ
			}
			break; 

		case  6: break;    // CCR3  not  used
		case  8: break;                          // reserved
		case 10: break;                          // reserved
		case 12: break;                          // reserved
		case 14: 
			if(G_WorkState == WORK_Speaker_Test)
			{
				Deal_Song_Beat_Speaker(); //���Ʋ��Ÿ����������ͽ��� -- "Speaker ������" 
			}
			break;   //δʹ��//����ж� // overflow

		default: break;
	}
}



/****************************************************************************
*������-Function:	__interrupt void TIMER2_A0_ISR(void)
*����- Description:		TIMER2 �жϷ������(CCR0ռ��)
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
#pragma vector=TIMER2_A0_VECTOR
__interrupt void TIMER2_A0_ISR(void)
{
	Deal_Step_Motor();  //�ж��д��������(����ת,ת��)
}



/****************************************************************************
*������-Function:	__interrupt void USCI_A1_ISR(void)
*����- Description:		USCI_A1 �жϷ������
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
	switch(__even_in_range(UCA1IV,4))
	{
		case 0: break;                  // Vector 0 - no interrupt
		case 2:
			if(G_MainState == MAIN_RS232_UART)//Main��RS232_UART �˵�ѡ��(����ʱ)
			{
				while (!(UCA1IFG&UCTXIFG));
				UCA1TXBUF = UCA1RXBUF;
				G_RxData_RS232 = UCA1RXBUF;
			}

			else if(G_MainState == MAIN_RS485_UART)//Main��RS485_UART �˵�ѡ��(����ʱ)
			{
				
					//while (!(UCA1IFG&UCTXIFG));
					
					//DE;  // ����485оƬ���ڷ���״̬
					//WaitingDelayMs(1);

				G_RxData_RS485 = UCA1RXBUF;
				
					//UCA1TXBUF = UCA1RXBUF;
					
					//WaitingDelayMs(1);
					//RE;  // ����485оƬ���ڽ���״̬	
			}
			break;

		case 4: break;            // Vector 4 - TXIFG
		default: break;
	}

}


/****************************************************************************
*������-Function:	__interrupt void TIMER1_A0_ISR(void)
*����- Description:		TIMER1_A0 �жϷ������-- �����ض��������ɶ�ӦƵ�ʵĲ��� 
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01)(TIMERA������жϺ�CCR0 ռ��A0_VECTOR)
	��02)    ��03)    ��04)  
*****************************************************************************/
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)  // �����ض��������ɶ�ӦƵ�ʵĲ��� 
{
	if(G_WorkState == WORK_Speaker_Test)
	{
		Deal_Song_Tone_Speaker();  //�����ض��������ɶ�ӦƵ�ʵĲ���-- "Speaker ������"  
	}
	else 
	{
		Deal_Buzz_Speaker();  //��������� -- "Speaker ������" 
	}
}


/****************************************************************************
*������-Function:	__interrupt void TIMER1_A1_ISR(void)
*����- Description:		TIMER1_A1 �жϷ������--���Ʋ��Ÿ����������ͽ��� 
*�������-Input:	None
*�������-output:	None
*ע������-Note��	
	��01)(TIMERA������жϺ�CCR1 CCR2ռ��A1_VECTOR)
	��02)    ��03)    ��04)  
****************************************************
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR(void)   //���Ʋ��Ÿ����������ͽ��� 
{
	switch(__even_in_range(TA1IV,14))
	{
		case  0: break;    // ���ж�            // No interrupt
		case  2: break;    // CCR1 δʹ��   // CCR1 not used
		case  4: break;    // CCR2 δʹ��   // CCR2 not used
		case  6: break;    // ����                  // reserved
		case  8: break;    // ����                  // reserved
		case 10: break;    // ����                  // reserved
		case 12: break;    // ����                  // reserved
		case 14:		   //����ж� // overflow
			if(G_WorkState == WORK_Speaker_Test)
			{
				Deal_Song_Beat_Speaker(); //���Ʋ��Ÿ����������ͽ��� -- "Speaker ������" 
			}
			break;
		default: break;
	}
}
*************************/




/****************************************************************************
*������-Function:	__interrupt void USCI_B1_ISR(void)
*����- Description:		SPI_B �жϷ������
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01) 	��02) 	��03) 	��04) 
***************************************************
#pragma vector=USCI_B1_VECTOR
__interrupt void USCI_B1_ISR(void)
{
	switch(__even_in_range(UCB1IV,4))
	{
		case 0:break;                             // Vector 0 - no interrupt
		
		case 2: // Vector 2 - RXIFG //�����жϱ�־��UCxRXBUF���յ�1�������ַ�ʱ��UCRXIFG��λ��                   
//G_TempChar = UCB1RXBUF;
		
			//while (!(UCB1IFG&UCTXIFG));             // USCI_B1 TX buffer ready?
			//UCB0TXBUF = UCB0RXBUF;
			break;
			
		case 4: // Vector 4 - TXIFG //�����жϱ�־λ����UCxTXBUFΪ��ʱ��UCTXIFG��λ��
			break;                             

		default: break;
	}
}
**************************/





/****************************************************************************
*������-Function:	__interrupt void RTC_ISR(void)// RTC_B �жϴ������
*����- Description:	ϵͳÿ "500us = 0.5ms"�ж�һ����Ϊ�����ж�ʱ��
*�������-Input:	None
*�������-output:	None
*ע������-Note��		��01) 	��02) 	��03) 	��04) 
*******************************************************

#pragma vector=RTC_VECTOR
__interrupt void RTC_ISR(void)
{
    switch (__even_in_range(RTCIV, RTC_RT1PSIFG))
    {
        // Vector RTC_NONE�����жϹ���
        case RTC_NONE:  // Vector RTC_NONE: No Interrupt pending
            break;

        // Vector RTC_RTCRDYIFG��RTC����
        case RTC_RTCRDYIFG:   // Vector RTC_RTCRDYIFG: RTC ready

// 	LED_OUT ^= Green_LED;	// �̵�ÿ����˸һ��	// Toggle green LED every second
//if(alarmflag == 1)	// ÿ��һ����7�������������ÿ����˸һ��
//	LED_OUT ^= Red_LED; // Toggle RED LED every second when time is up to 7:00am on 1st day of week
            break;

		// Vector RTC_RTCTEVIFG��RTC�����ʱ������������ʱ���¼�Ϊÿ���Ӹı�һ�Σ�
		// ��ÿ���Ӷ�����λ���жϱ�־λ�����뵽��״̬
        case RTC_RTCTEVIFG:   // Vector RTC_RTCTEVIFG: RTC interval timer
			break;

        // Vector RTC_RTCAIFG��RTC�û�����
        case RTC_RTCAIFG:  // Vector RTC_RTCAIFG: RTC user alarm
//	alarmflag = 1;	// ÿ��һ����7�����������������// Interrupts 7:00am on 1st day of week
            break;

        // Vector RTC_RT0PSIFG��RTCԤ��Ƶ��0
        case RTC_RT0PSIFG: // Vector RTC_RT0PSIFG: RTC prescaler 0
			break;

        // Vector RTC_RT1PSIFG��RTCԤ��Ƶ��1
        case RTC_RT1PSIFG: // Vector RTC_RT1PSIFG: RTC prescaler 1

			break;

        // Default case
        default:
            break;
    }
}
**********************/






