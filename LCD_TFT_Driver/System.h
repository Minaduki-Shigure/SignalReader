/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 System.h
* �����ļ�-Dependencies:  	 None	
* �ļ�����-File Description:	 ( ͷ�ļ�-Header File )
	��"ϵͳ" ���ù��ܺ�����-ͷ�ļ�
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



#ifndef __System_H
#define __System_H


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"�궨��**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////

//#define M_Self_Check_Time  (5000)  //5000 ms= 5 s
#define M_Self_Check_Time  (2000)  //3000 ms


////////////////////////////////////////////////////////////////////////////
//==**��Ŀ"ר��"�궨��**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////i////////////////////////////////
//==**ϵͳʱ���־λ����**time bit flag define**===============//
extern union FLAGBIT16 TimeFlag1Bits;  //ʱ�亯����־λ����1
#define  G_TimeFlag1Bits      TimeFlag1Bits.FLAG16  
#define	 F_Timing             TimeFlag1Bits.b.f0  //Ϊ1ʱ��������Ϊ��ʱ�� ,��ʱ�����Զ�����(��1msΪʱ��,��������)
#define	 F_SuspendTiming	  TimeFlag1Bits.b.f1  //Ϊ1ʱ��ֻ����ͣ��Ϊ��ʱ�� (��1msΪʱ��,��������)    
#define  F_Timing_In_Work     TimeFlag1Bits.b.f2  //Ϊ1ʱ��������Ϊ��ʱ��(���ڹ�������),��ʱ�����Զ�����(��1msΪʱ��,��������)
//#define  F_500us              TimeFlag1Bits.b.f3  //ϵͳ��ʱ0.5ms = 500us��־λ
#define	 F_1ms                TimeFlag1Bits.b.f4  //ϵͳ��ʱ1ms��־λ
#define	 F_10ms_TaskClock	  TimeFlag1Bits.b.f5  //ϵͳ10ms��־λ//���ڳ�����ѭ������10ms    
#define	 F_10MS	  TimeFlag1Bits.b.f6  
#define	 F_100ms              TimeFlag1Bits.b.f7  //ϵͳ��ʱ100ms��־λ
#define	 F_250ms              TimeFlag1Bits.b.f8  //ϵͳ��ʱ250ms��־λ
#define	 F_250ms_Turn	      TimeFlag1Bits.b.f9  //������˸ʱ��Ϊ250ms��˸һ��,������ܻ�Һ���˵�����ʱ   
#define	 F_250ms_Working_Led  TimeFlag1Bits.b.f10 //���ڵ�Ƭ����������ʱ������ָʾ��һֱ��˸(250ms��˸һ��) 
//#define  F_	       TimeFlag1Bits.b.f11	
#define	 F_500ms	          TimeFlag1Bits.b.f12 //ϵͳ��ʱ500ms��־λ
//#define  F_	   TimeFlag1Bits.b.f13	   		
//#define  F_	   TimeFlag1Bits.b.f14	 		
#define  F_1s	               TimeFlag1Bits.b.f15 //ϵͳ��ʱ1���־λ 

//////////////////////////////////////////////////////////////////////////
extern union FLAGBIT16 TimeFlag2Bits;  //ʱ�亯����־λ����2
#define  G_TimeFlag2Bits     TimeFlag2Bits.FLAG16  
#define	 F_100ms_ReadTime    TimeFlag2Bits.b.f0 //ϵͳ��ʱÿ100ms��һ��"ʵʱʱ��"
#define	 F_1ms_LCD           TimeFlag2Bits.b.f1 //������LCD�ȴ�Busy�ź�ʱ��ÿ1ms�ۼ�1��������һ������ֵʱ����Һ����λ
#define	 F_1ms_Uart          TimeFlag2Bits.b.f2 //���ڴ��ڵȴ�Ӧ���ź�ÿ1ms�ۼ�1  
#define  F_500ms_Temperature TimeFlag2Bits.b.f3	//ϵͳ��ʱÿ500ms��һ��"ʵʱTMP�¶�ֵ"
#define  F_500ms_TemperatureInTest TimeFlag2Bits.b.f4 //ϵͳ��ʱÿ500ms��һ��"ʵʱTMP�¶�ֵ"
#define  F_500ms_IrDA        TimeFlag2Bits.b.f5  //IrDA   //ϵͳ��ʱÿ500ms 
#define  F_1s_BQ27410	     TimeFlag2Bits.b.f6  //ϵͳÿ1s ��ȡ"ʵʱBQ27410������ ����ֵ"
#define  F_1s_BQ27410InTest  TimeFlag2Bits.b.f7  //ϵͳÿ1s ��ȡ"ʵʱBQ27410������ ����ֵ"
//#define  F_1s_CC1101       TimeFlag2Bits.b.f8   //CC1101//ϵͳ��ʱÿ1s 
//#define  F_	   TimeFlag2Bits.b.f9	 
//#define  F_	   TimeFlag2Bits.b.f10	 
//#define  F_	   TimeFlag2Bits.b.f11	 
//#define  F_	   TimeFlag2Bits.b.f12	 
//#define  F_	   TimeFlag2Bits.b.f13	 
//#define  F_	   TimeFlag2Bits.b.f14 
//#define  F_	   TimeFlag2Bits.b.f15	 

	





////////////////////////////////////////////////////////////////////////////
//==**ϵͳʱ�����������**============================//
extern unsigned long G_TimingCnt; //��Ϊ��ʱ������(��1msΪʱ��,��������)

extern unsigned long G_Timing_InWork_Cnt; //(�����еĶ�ʱ)��Ϊ��ʱ������(��1msΪʱ��,��������)




//extern unsigned char  G_1msCnt;    //ϵͳ��ʱ1ms������
extern unsigned char G_10msCnt;   //ϵͳ��ʱ10ms������
extern unsigned char G_100msCnt;  //ϵͳ��ʱ100ms������
extern unsigned int G_250msCnt;  //ϵͳ��ʱ250ms������
extern unsigned int G_500msCnt;  //ϵͳ��ʱ500ms������
extern unsigned int G_1Csnt;     //ϵͳ��ʱ1s������

////////////////////////////////////////////////////////////////////////////
//���ж��У���ͬ�ĵ�G_1ms_Case �� 1 msִ���ж��еĲ�������
//good ����������ʹ���ж��г���ִ�е���ʱ�����С
//�ŵ����Switch�е��ӳ���Ϊִ��ʱ��Ƚϳ����ӳ���
//��������У���С�ж���ʱ��
extern unsigned char G_1ms_Case;  


////////////////////////////////////////////////////////////////////////////
//==**ϵͳ״̬������**=================================//
extern unsigned int G_MainState;      //Mainϵͳ״̬���� 
extern unsigned int G_Last_MainState; //������һ��ϵͳ״̬���� 

//extern volatile unsigned char G_UsersType;     //�û�����:�߼�����Ա����ͨ����Ա

extern union FLAGBIT SystemFlagBits;	//ϵͳ��־λ����
#define  G_SystemFlag1Bits  SystemFlagBits.FLAG 
//#define			 SystemFlagBits.b.f0	 
//#define			 SystemFlagBits.b.f1	 
//#define  F_Set_Success    SystemFlagBits.b.f2 //Ϊ1ʱ�����ñ���ɹ�		  
//#define  F_Set_Error	SystemFlagBits.b.f3	 //Ϊ1ʱ�����ô���
//#define  F_		SystemFlagBits.b.f4   
//#define  F_		SystemFlagBits.b.f5  
//#define  F_		SystemFlagBits.b.f6   
//#define  F_		SystemFlagBits.b.f7  



////////////////////////////////////////////////////////////////////////////
//==**��������ʱ,�õ���״̬����**====================//
extern unsigned int G_WorkState;	      //ϵͳ����״̬���� 
extern unsigned int G_Last_WorkState;  //������һ�ι���״̬���� 



////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"����"�궨��**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"��������**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"�ⲿ" API ��������**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**ϵͳ��Ƭ����ʹ������**=========================//
////////////////////////////////////////////////////////////////////////////
extern void System_Initial(void);          //   ϵͳ��ʹ�� :��Ƭ���ڲ���Դ+�ⲿ������Դ�ĳ�ʹ�� 

extern void Osccon_Initial(void);  //�����ʼ������:������ؾ������


//extern void System_LoopInitial(void);   //ϵͳ������"ѭ��"��ʹ��,//good �ɷ�ֹ�ڳ���ѭ���У���ʹ�����ݳ��ĵ�


////////////////////////////////////////////////////////////////////////////
//==**ϵͳ������ʹ��(����״̬����ʹ��)**============//
////////////////////////////////////////////////////////////////////////////
extern void System_Variable_Initial(void); //ϵͳ������ʹ��(����״̬����ʹ��)����Ϊ"��λ"��"�ϵ�"�������


////////////////////////////////////////////////////////////////////////////
//==**ϵͳ�ϵ��Լ�**===================================//
////////////////////////////////////////////////////////////////////////////
extern void System_SelfCheck(void); //ϵͳ�ϵ��Լ�:������,��,Һ����ģ���Լ�


////////////////////////////////////////////////////////////////////////////
//==**ͨ��"ϵͳʱ��"����**=============================//
////////////////////////////////////////////////////////////////////////////

extern void System_Working_Led(void);  //��Ƭ����������ָʾ��: 250ms��˸һ��

extern void System_GetLoopClockTick(void); //ÿ��"����"��ʱ10ms��ϵͳ"ѭ��"ִ��һ�γ���

///////////////////////////////////////////////////////////////////////////
extern void System_Clock(void);      //ͨ��"ϵͳʱ��"����: ������ʱΪ1ms,10ms, 20ms, 100ms,��


extern void System_Timing_Task(void); //��1msʱ������Ϊ��ʱ����ʱʱ�������,�����������
extern void Open_Timing_Task(unsigned int TimeValue); //��ϵͳ��ʱ����ʱ������ʱ��ֵ(�ж���)


extern void System_1ms_Task(void);   //����ϵͳ��ʱ"1ms" �µ��������

extern void System_10ms_Task(void);  //����ϵͳ��ʱ"10ms" �µ�������� 

extern void System_100ms_Task(void); //����ϵͳ��ʱ"100ms" �µ��������

extern void System_250ms_Task(void); //����ϵͳ��ʱ"250ms" �µ��������

extern void System_500ms_Task(void); //����ϵͳ��ʱ"500ms" �µ��������

extern void System_1s_Task(void);      //����ϵͳ��ʱ"1s" �µ��������



	//�������õ��Ķ�ʱ����// ��1msʱ������Ϊ��ʱ����ʱʱ�������,�����������
extern void Timing_In_Work(void);  
	//�򿪹����еĶ�ʱ������ʱ������ʱ��ֵ(�ж���)
extern void Open_Timing_In_Work(unsigned long TimeValue);  



////////////////////////////////////////////////////////////////////////////
//==**��Ŀ"ר��" API ��������**Exported Project-specific API funcitions**=//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**ϵͳ״̬���ĺ���**==============================//
////////////////////////////////////////////////////////////////////////////

#define mSet_MainState(n)  (G_MainState = n)   //����ϵͳMain״ֵ̬(����"��ʹ��"״̬)

	//"��ʹ��" ��"ϵͳ״̬Main��" (״̬��)
	//01)����ϵͳ״ֵ̬; 02)�����ʾ���ݳ�ʹ��; 03)��ر�����ʼ��				
extern void Initial_MainState(unsigned int MainMode);

extern void Deal_MainState(void); // "����"��ϵͳMain��"״̬"�µ����� (״̬��)


///////////////////////////////////////////////////////////////////////////

#define mSet_WorkState(n) (G_WorkState = n)   //����ϵͳ����״ֵ̬(����"��ʹ��"״̬)

extern void Initial_WorkState(unsigned int WorkMode); //��ʼ��"����״̬Work��"

extern void Deal_WorkState(void); //"����"������Work��"״̬"�µ����� (״̬��)






#endif  /* __System_H */




