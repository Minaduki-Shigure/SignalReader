/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 Speaker.c
* 附属文件-Dependencies:  	 Speaker.h; math.h; msp430f6638.h;
                                                        Hardware_Profile.h;  Generic.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■  "Speaker 扬声器" -驱动程序(外部资源)
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

#include "System.h"	 //"系统" 常用功能函数集-头文件
#include "MyProject.h"	//具体项目: 总功能程序-头文件


#include "Speaker.h"   //"Speaker 扬声器" -驱动程序(外部资源)-头文件

#include <math.h>


////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
union FLAGBIT16 SpeakerFlagBits;  //"Speaker 扬声器"用到的标志位定义
  



////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned long G_Timing_Speaker_Cnt = 0; //蜂鸣器(Speaker 扬声器)的定时器计数器



#define PI 3.1415926

int sin_table[10];    // 正弦波数组 
int *sin_data_pr;  // 指向正弦波数组的指针 




	// 低音、中音、高音的1,2,3,4,5,6,7音阶对应的声音频率数组  
int key_table[22]={261,293,329,349,391,440,493,  533,587,659,698,783,880,987,  1046,1174,1318,1396,1567,1760,1975};
int period_table[21];  //对应的声音的周期数组 

//两只老虎
//int song_tone_table[32]={7,8,9,7,7,8,9,7,9,10,11,9,10,11,11,12,11,10,9,7,11,12,11,10,9,7,7,11,7,7,11,7};
//int song_long_table[32]={4,4,4,4,4,4,4,4,4,4,8,4,4,8,2,2,2,2,4,4,2,2,2,2,4,4,4,4,8,4,4,8};

//生日歌//音符数组 5   5   6   5   1.   7   5   5    6   5   2.  1.   5   5  5.   3.  1.   7   4.  4.  3.  1.   2.   1.
//int song_tone_table[24]=  { 4, 4, 5, 4, 7, 6, 4, 4, 5, 4, 8, 7, 4, 4,11, 9, 7, 6,10,10, 9, 7, 8, 7};  //低音版
//int song_tone_table[24]=  {11,11,12,11,14,13,11,11,12,11,15,14,11,11,18,16,14,13,17,17,16,14,15,16}; //高音版
	//低音版+ 高音版
//int song_tone_table[48]=  { 4, 4, 5, 4, 7, 6, 4, 4, 5, 4, 8, 7, 4, 4,11, 9, 7, 6,10,10, 9, 7, 8, 7,11,11,12,11,14,13,11,11,12,11,15,14,11,11,18,16,14,13,17,17,16,14,15,16};

//生日歌//音符数组 5   5   6   5   1.   7   5   5    6   5   2.  1.   5   5  5.   3.  1.   7   4.  4.  3.  1.   2.   1.
             //                      1   1   2   1    4   3    1   1   2   1   5    4    1  1   1.   6   4   3    7   7   6    4   5    4  
int song_tone_table[48]=  { 0, 0, 1, 0, 3, 2, 0, 0, 1, 0, 4, 3, 0, 0, 7, 5, 3, 2, 6, 6, 5, 3, 4, 3, 4, 4, 5, 4, 7, 6, 4, 4, 5, 4, 8, 7, 4, 4,11, 9, 7, 6,10,10, 9, 7, 8, 7};


//生日歌//节拍数组//播放速度控制
//int song_long_table[24]={2,2,4,4,4,8,2,2,4,4,4,8,2,2, 5,4,5,8, 2, 2,4,4,4,8};
//int song_long_table[24]={10,10,20,20,20,40,10,10,20,20,20,40,10,10,25,20,25,40,10,10,20,20,20,40};
//int song_long_table[24]={12,12,22,22,22,42,12,12,22,22,22,42,12,12,27,22,27,42,12,12,22,22,22,42};
int song_long_table[24]={36,36,66,66,66,126,36,36,66,66,66,126,36,36,81,66,81,126,36,36,66,66,66,126};


//int song_long_table[24]={8,8,16,16,16,32,8,8,16,16,16,32,8,8, 20,16,20,32, 8, 8,16,16,16,32};


int key;
int m,n;
int k;


/****************************************************************************
*函数名-Function:	void Disable_Speaker(void)
*描述- Description:		禁止:  "Speaker 扬声器" 
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Disable_Speaker(void) //禁止:  "Speaker 扬声器" 
{

	DMA0CTL &= ~DMAEN;
//	ADC12CTL0 &= ~ADC12ENC;
	DAC12_1CTL0 &= ~DAC12ENC;

//	P4OUT &= ~BIT0;  //Microphone power source
//	P4DS &= ~BIT0;
//	P4DIR &= ~BIT0;
	
	P7SEL &= ~BIT6;   //Microphone AD口  //P7.6-->AD14
	
	P5DIR |= BIT6;    //P5.6接到Speaker 放大器使能口
	P5OUT |= BIT6;    //P5.6输出低时，蜂鸣器才可以工作

	TA1CTL &= ~TAIE;    //关定时器中断
	TA1CCTL0 &= ~CCIE;	  // 关CCR0中断
}


/****************************************************************************
*函数名-Function:	void Play_a_Song_Speaker(void)
*描述- Description:		初始化设置:  播放一首音乐--"Speaker 扬声器" 
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Play_a_Song_Speaker(void) //初始化设置:  播放一首音乐--"Speaker 扬声器" 
{
	unsigned char j = 0;
	double i = 0;
	
	for(j=0;j<10;j++)   //产生正弦波数组 
	{
		i+=PI/5;
		sin_table[j]=(int)((sin(i)+1)*2048);
	}
	sin_data_pr=&sin_table[0];
	
	for(j=0;j<20;j++)  //根据音阶的频率计算其周期 
	{
		period_table[j]=(int)(300000/key_table[j]);
	}


		//AVcc作为参考电压，初始化偏移量校正，端口p7.7(DAC_1)输出 
	DAC12_1CTL0 = DAC12IR + DAC12SREF_1 + DAC12AMP_5 + DAC12ENC + DAC12CALON+DAC12OPS;

	P5DIR |= BIT6;    //P5.6接到Speaker 放大器使能口
	P5OUT &= ~BIT6;   //P5.6输出低时，蜂鸣器才可以工作

	TA1CCTL0 = CCIE;	  // CCR0中断使能  // CCR0 interrupt enabled

	TA1CCR0 = period_table[0];  // 定时为第一个音符的音阶周期 

		// SMCLK+向上计数+清TAR +定时器中断
	TA1CTL = TASSEL_2 + MC_2 + TACLR +TAIE; 		// SMCLK, upmode, clear TAR


}


/****************************************************************************
*函数名-Function:	void Deal_Song_Tone_Speaker(void)
*描述- Description:		根据特定音符生成对应频率的波形 -- "Speaker 扬声器" 
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Deal_Song_Tone_Speaker(void)  //根据特定音符生成对应频率的波形-- "Speaker 扬声器"  
{
	DAC12_1DAT=*sin_data_pr++;   //生成的正弦波在 DAC输出 

	if (sin_data_pr >= &sin_table[10])   //循环输出正弦波 
	{
		sin_data_pr = &sin_table[0];
	}


	DAC12_1DAT &= 0xFFF;      // 数据保持   // Modulo 4096

	TA1CCR0 += period_table[song_tone_table[key]];//定时器 定时某个音符的音阶周期 
}


/****************************************************************************
*函数名-Function:	void Deal_Song_Beat_Speaker(void)
*描述- Description:		控制播放歌曲的音符和节拍 -- "Speaker 扬声器" 
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Deal_Song_Beat_Speaker(void) //控制播放歌曲的音符和节拍 -- "Speaker 扬声器" 
{
	if(k++ == song_long_table[m])  //用变量k记节拍时长 
	{
		k = 0;
		if(++m == 24) m = 0; //第24个音符放完,歌曲结束,重放 
	
		DAC12_1DAT = 0x000;	 //两个音符间隔停顿 
		TA1CCTL0 &=~ CCIE;
		
		if(++n == 1)		   //下一个音符 
		{
			n = 0;
			TA1CCTL0 = CCIE;
			TA1CCR0 = period_table[song_tone_table[key++]]; //下一个音符的音阶周期 
			if(key == 48) key = 0;	 //歌曲结束重放 
		}
	}

}


/****************************************************************************
*函数名-Function:	void Mic_Record_Speaker_Play(void)
*描述- Description:		麦克风录音后，通过DMA 传给DAC通过扬声器播放
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Mic_Record_Speaker_Play(void) //麦克风录音后，通过DMA 传给DAC通过扬声器播放
{
	P7SEL |=BIT6;  //Microphone AD口  //P7.6-->AD14

	P5DIR |= BIT6;     //P5.6接到Speaker 放大器使能口
	P5OUT &= ~BIT6;    //P5.6输出低时，蜂鸣器才可以工作

	ADC12CTL0 = ADC12ON+ADC12SHT0_5+ADC12MSC;
	ADC12CTL1 = ADC12CSTARTADD_14+ADC12SHP+ADC12SSEL_0+ADC12CONSEQ_2;                     // Use sampling timer
	ADC12MCTL14 = ADC12INCH_14;                 
	ADC12CTL0 |= ADC12ENC;

	DAC12_1CTL0 = DAC12IR+DAC12SREF_1 + DAC12AMP_7 + DAC12ENC + DAC12CALON+ DAC12OPS;

	DMACTL0 |= DMA0TSEL3 + DMA0TSEL4;
   	DMA0SA = 0x073Cu;//&ADC12MEM14;                                                                                                                                                                                                                                                                                                                                                                                                                         	DMA0SA = 0x073Cu;//&ADC12MEM14;
	DMA0DA = 0x0794u;//&DAC12_1DAT;
	DMA0SZ = 1;
	DMA0CTL |= DMADT2 + DMAEN;

	ADC12CTL0 |= ADC12SC;
 
}





/****************************************************************************
*函数名-Function:	void Open_Timing_In_Work(unsigned long TimeValue)  
*描述- Description:		打开蜂鸣器(Speaker 扬声器)的定时器		
*输入参数-Input:	timeValue: 定时的时间值(时基为1ms)
*输出参数-output:	None
*注意事项-Note：	
	▲01)  在中断中，对定时时间计数器，进行递减   
	▲02)  定时到后，自动清"定时标志位"	  
	▲03)    ▲04)  
*****************************************************************************/
void Open_Buzz_Speaker(unsigned long timeValue)  //打开蜂鸣器(Speaker 扬声器)的定时器	
{

	Initial_Buzz_Speaker();  //初始化设置:	蜂鸣器 -- "Speaker 扬声器" 
	G_Timing_Speaker_Cnt = timeValue;	//定时(时基为1ms)//给自减计数器附初值
	F_StartSpeaker = 1; //启动常用蜂鸣器(Speaker 扬声器)	 //定时到后自动清此标志位	 

}






/****************************************************************************
*函数名-Function:	void Initial_Buzz_Speaker(void)
*描述- Description: 	初始化设置:  蜂鸣器 -- "Speaker 扬声器" 
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)		▲02)		▲03)	 ▲04)	
*****************************************************************************/
void Initial_Buzz_Speaker(void)  //初始化设置:  蜂鸣器 -- "Speaker 扬声器" 
{
	unsigned char j = 0;
	double i = 0;
	
	for(j=0;j<10;j++)   //产生正弦波数组 
	{
		i+=PI/5;
		sin_table[j]=(int)((sin(i)+1)*2048);
	}
	sin_data_pr=&sin_table[0];
	
	for(j=0;j<20;j++)  //根据音阶的频率计算其周期 
	{
		period_table[j]=(int)(300000/key_table[j]);
	}
	
		//AVcc作为参考电压，初始化偏移量校正，端口p7.6输出 
	DAC12_1CTL0 = DAC12IR + DAC12SREF_1 + DAC12AMP_5 + DAC12ENC + DAC12CALON+DAC12OPS;

	P5DIR |= BIT6;     //P5.6接到Speaker 放大器使能口
	P5OUT &= ~BIT6;    //P5.6输出低时，蜂鸣器才可以工作

	TA1CCTL0 = CCIE;	  // CCR0中断使能  // CCR0 interrupt enabled

	TA1CCR0 = period_table[0];  // 定时为第一个音符的音阶周期 

		// SMCLK+向上计数+清TAR +定时器中断
	TA1CTL = TASSEL_2 + MC_2 + TACLR +TAIE; 		// SMCLK, upmode, clear TAR

}




/****************************************************************************
*函数名-Function:	void Deal_Buzz_Speaker(void)
*描述- Description:		处理蜂鸣器 -- "Speaker 扬声器" 
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Deal_Buzz_Speaker(void)  //处理蜂鸣器 -- "Speaker 扬声器" 
{
	DAC12_1DAT = *sin_data_pr++;   //生成的正弦波在 DAC输出 

	if (sin_data_pr >= &sin_table[10])   //循环输出正弦波 
	{
		sin_data_pr = &sin_table[0];
	}


	DAC12_1DAT &= 0xFFF;      // 数据保持   // Modulo 4096
				//7表示中音的"Do"
	TA1CCR0 += period_table[7];//定时器 定时某个音符的音阶周期 
}



/****************************************************************************
*函数名-Function:	void Check_Buzz_Speaker(void)
*描述- Description:		在中断里，检查是否结束: 蜂鸣器 -- "Speaker 扬声器" (包括:常用和报警用)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01)计数器在中断里以1ms为单位，  
	▲02)//care 放到中断中去，实时性比较好，就跟数码显示一样，蜂鸣器响的比较均匀 
	▲03)    ▲04)  
*****************************************************************************/
void Check_Buzz_Speaker(void)   //在中断里，检查是否结束: 蜂鸣器 -- "Speaker 扬声器" (包括:常用和报警用)
{
	if(F_StartSpeaker)  //为1启动常用蜂鸣器，//此标志位启动后，到时间到后，自动清0
	{
		G_Timing_Speaker_Cnt --;
		if(G_Timing_Speaker_Cnt == 0)
		{
			F_StartSpeaker = 0;
			
			if(G_WorkState != WORK_Speaker_Test)
			{
					//关蜂鸣器
				Disable_Speaker(); //禁止:	"Speaker 扬声器" 
			}
		}
	}
}



