/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 Speaker.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■"Speaker 扬声器" -驱动程序(外部资源)-头文件
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



#ifndef  __Speaker_H 
#define  __Speaker_H 


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"宏定义**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////
#define  M_100MS_Speaker  (100) //蜂鸣器叫: 100ms

#define  M_200MS_Speaker  (200) //蜂鸣器叫: 200ms
#define  M_500MS_Speaker  (500) //蜂鸣器叫: 500ms

#define  M_1S_Speaker     (1000) //蜂鸣器叫: 1s






////////////////////////////////////////////////////////////////////////////
//==**项目"专用"宏定义**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
extern union FLAGBIT16 SpeakerFlagBits;  //"Speaker 扬声器"用到的标志位定义
#define  G_SpeakerFlagBits  SpeakerFlagBits.FLAG16  
#define  F_StartSpeaker     SpeakerFlagBits.b.f0   //为1，启动蜂鸣器(Speaker 扬声器)   
//#define  F_Disable_Buzz 	SpeakerFlagBits.b.f1   //为1，禁用蜂鸣器(Speaker 扬声器)   
//#define   F_	SpeakerFlagBits.b.f2  
//#define   F_	SpeakerFlagBits.b.f3  
//#define   F_	SpeakerFlagBits.b.f4  
//#define   F_	SpeakerFlagBits.b.f5  
//#define   F_	SpeakerFlagBits.b.f6  
//#define   F_	SpeakerFlagBits.b.f7 
//#define   F_	SpeakerFlagBits.b.f8      
//#define   F_	SpeakerFlagBits.b.f9     
//#define   F_	SpeakerFlagBits.b.f10    
//#define   F_	SpeakerFlagBits.b.f11      
//#define   F_	SpeakerFlagBits.b.f12      
//#define   F_	SpeakerFlagBits.b.f13      
//#define   F_	SpeakerFlagBits.b.f14     
//#define   F_	SpeakerFlagBits.b.f15     



////////////////////////////////////////////////////////////////////////////
//==**"函数"宏定义**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"函数声明**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**"外部" API 函数声明**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

extern void Disable_Speaker(void); //禁止:  "Speaker 扬声器" 


extern void Deal_Song_Tone_Speaker(void); //根据特定音符生成对应频率的波形-- "Speaker 扬声器" 
extern void Deal_Song_Beat_Speaker(void); //控制播放歌曲的音符和节拍 -- "Speaker 扬声器" 

extern void Play_a_Song_Speaker(void); //初始化设置:  播放一首音乐--"Speaker 扬声器" 

/////////////////////////////////////////////////////////////////////////////////
extern void Mic_Record_Speaker_Play(void); //麦克风录音后，通过DMA 传给DAC通过扬声器播放

/////////////////////////////////////////////////////////////////
extern void Open_Buzz_Speaker(unsigned long timeValue);  //打开蜂鸣器(Speaker 扬声器)的定时器	

extern void Initial_Buzz_Speaker(void);  //初始化设置:  蜂鸣器 -- "Speaker 扬声器" 

extern void Deal_Buzz_Speaker(void);  //处理蜂鸣器 -- "Speaker 扬声器" 

extern void Check_Buzz_Speaker(void);   //在中断里，检查是否结束: 蜂鸣器 -- "Speaker 扬声器" (包括:常用和报警用)



#endif   /* __Speaker_H  */





