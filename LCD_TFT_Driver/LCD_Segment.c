/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 LCD_Segment.c
* 附属文件-Dependencies:  	 LCD_Segment.h; Hardware_Profile.h;  Generic.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■"段式LCD_Segment" -驱动程序(外部资源)
	01) 
	//LCDMEM[0] = dp;  //对应"最上面"的"电池符号"+"第6个字符"(从右边开始算)
	//LCDMEM[1] = dp;  //对应"中间"的"电池符号"+"第5个字符"(从右边开始算)
	//LCDMEM[2] = dp;  //对应"最下面"的"电池符号"+"电池框图"+"第4个字符"(从右边开始算)
	//LCDMEM[3] = dp;  //对应"最左边"的"小数点"+"第3个字符"(从右边开始算)
	//LCDMEM[4] = dp;  //对应"中间"的"小数点"+"第2个字符"(从右边开始算)
	//LCDMEM[5] = dp;  //对应"最右边"的"小数点"+"第1个字符"(从右边开始算)
	02)     03)    04)    05)    06)	
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


#include "LCD_Segment.h" // "段式LCD_Segment"  -驱动程序(外部资源)-头文件



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//--**"段式LCD_Segment" *全局标志位**------------------------------//
union FLAGBIT16 LCD_Seg_FlagBits; //"LCD_Segment"相关标志位变量


unsigned char G_Mode_LCD_Segment = 0; //"LCD_Segment" 工作模式
unsigned char G_Last_Mode_LCD_Segment = 0; //保存上一次"工作模式"



unsigned char G_LcdSeg_Cnt = 0; //"段式LCD_Segment"中用到的计数器(用于字符循环显示)

unsigned char G_LcdSegBuf[7]; //"段式LCD_Segment"显示缓存数组//G_LcdSegBuf[0]对应最"右边"的显示字符


////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////
	//"段式LCD_Segment" 显示表格
const unsigned char LcdSeg_Tab[] = { // As used in 430 Day Watch Demo board
		aa+bb+cc+dd+ee+ff,         //LcdSeg_Tab[0] // Displays "0"
		bb+cc,                     //LcdSeg_Tab[1]  // Displays "1"
		aa+bb+dd+ee+gg,            //LcdSeg_Tab[2]  // Displays "2"
		aa+bb+cc+dd+gg,            //LcdSeg_Tab[3]  // Displays "3"
		bb+cc+ff+gg,               //LcdSeg_Tab[4]  // Displays "4"
		aa+cc+dd+ff+gg,            //LcdSeg_Tab[5]  // Displays "5"
		aa+cc+dd+ee+ff+gg,         //LcdSeg_Tab[6]  // Displays "6"
		aa+bb+cc,                  //LcdSeg_Tab[7]  // Displays "7"
		aa+bb+cc+dd+ee+ff+gg,      //LcdSeg_Tab[8]  // Displays "8"
		aa+bb+cc+dd+ff+gg,         //LcdSeg_Tab[9]  // Displays "9"
		aa+bb+cc+ee+ff+gg,         //LcdSeg_Tab[10]  // Displays "A"
		cc+dd+ee+ff+gg,            //LcdSeg_Tab[11]  // Displays "b"
		aa+dd+ee+ff,               //LcdSeg_Tab[12] // Displays "C"
		bb+cc+dd+ee+gg,            //LcdSeg_Tab[13] // Displays "d"
		aa+dd+ee+ff+gg,            //LcdSeg_Tab[14] // Displays "E"
		aa+ee+ff+gg,               //LcdSeg_Tab[15] // Displays "F"
		dp, 					   //LcdSeg_Tab[16] // Displays "."(小数点)
		ff+gg,					   //LcdSeg_Tab[17] // Displays "+"(加号,正号)	
		gg, 					   //LcdSeg_Tab[18] // Displays "-"(减号,负号)
		dd+gg,					   //LcdSeg_Tab[19] // Displays "="(等于号)
		aa+bb+cc+dd+ee+ff+gg+dp,   //LcdSeg_Tab[20] // Displays "full"
		0                          //LcdSeg_Tab[21] // Displays "暗码"
};



/****************************************************************************
*函数名-Function:	void EnModule_LCD_Segment(unsigned char EnBit)
*描述- Description:	打开或者关闭液晶LCD_B 模块
*输入参数-Input:	EnBit=YES(1): 打开LCD_B模块；EnBit=N)(0): 关闭LCD_B模块；
*输出参数-output:	None
*注意事项-Note：	
	▲01) LCDON 模块总使能位-LCD on. This bit turns the LCD_B module on or off.    
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
void EnModule_LCD_Segment(unsigned char EnBit) //打开或者关闭液晶LCD_B 模块
{
	if(EnBit == YES)
	{
		//打开液晶LCD_B 模块
		LCDBCTL0 |= LCDON;
	}
	else if(EnBit == NO)
	{
		//关闭液晶LCD_B 模块
		LCDBCTL0 &= ~LCDON;
	}
}



/****************************************************************************
*函数名-Function:	void EnAllSeg_LCD_Segment(unsigned char EnBit)
*描述- Description:	使能或禁止所有LCD_B段(用于所有液晶段(整屏)的闪烁)
*输入参数-Input:	EnBit=YES(1): 使能所有LCD_B段的显示; EnBit=N)(0): 禁止所有LCD_B段的显示;
*输出参数-output:	None
*注意事项-Note：	
	▲01) LCDSON 所有液晶段使能位-  This bit supports flashing LCD applications by turning off all segment lines, while leaving the LCD timing generator and R33 enabled.
			//0b = All LCD segments are off.
			//1b = All LCD segments are enabled and on or off according to their corresponding memory location.
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
void EnAllSeg_LCD_Segment(unsigned char EnBit) //使能或禁止所有LCD_B段(用于所有液晶段(整屏)的闪烁)
{
	if(EnBit == NO)
	{
		LCDBCTL0 &= ~LCDSON;
	}
	else if(EnBit == YES)
	{
		LCDBCTL0 |= LCDSON;
	}
}


/****************************************************************************
*函数名-Function:	void Clear_LCD_Segment(void)
*描述- Description:	清屏: 清除处理器内部的"段式LCD 显示缓存"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01) //LCDMEM[]  //为处理器内部的"段式LCD 显示缓存"
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Clear_LCD_Segment(void)  //清屏: 清除处理器内部的"段式LCD 显示缓存"
{
     unsigned char i = 0;
     for(i = 0; i < 6; i++) //6个LCD段字符
     {
    	 LCDMEM[i] = 0;  //0 : 表示显示为"暗码"
     }
}




/****************************************************************************
*函数名-Function:	void Open_LCD_Segment(void)
*描述- Description:	打开LCD_Segment (初使化): LCD_Segment 内部寄存器配置; 端口初始化等
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Open_LCD_Segment(void) //打开LCD_Segment (初使化): LCD_Segment 内部寄存器配置; 端口初始化等
{
////////////////////////////////////////////////////////////////////////////
//==**段式LCD_Segment背光控制**===========================//

	mOpen_LCD_SEG_BackLight; //配置引脚为"输出",并"打开"LCD_Segment 背光

////////////////////////////////////////////////////////////////////////////
//==**"LCD_B 控制寄存器"相关配置(MCU模块寄存器)**=======//
//--care--在 "LCDON 模块总使能位=0"时，才能设置LCDBCTL0

	EnModule_LCD_Segment(NO);  //关闭液晶LCD_B 模块//之后才能设置LCDBCTL0	
	LCDBCTL0 =LCDDIV0 + LCDPRE0 +  LCDMX1 + LCDSSEL + LCDMX1 + LCD4MUX ;


////////////////////////////////////////////////////////////////////////////
//==**LCD_B模块初始化:端口初始化、配置LCD_B功能(LCD_Segment )**===========================//

//	LCD_B_Initial_LCD_Segment(); //LCD_B模块初始化:端口初始化、配置LCD_B功能(LCD_Segment )


}


/****************************************************************************
*函数名-Function:	void Close_LCD_Segment(void)
*描述- Description:		关闭"段式LCD_Segment"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Close_LCD_Segment(void) //关闭"段式LCD_Segment"
{
////////////////////////////////////////////////////////////////////////////
//==**段式LCD_Segment背光控制**===========================//
	mClose_LCD_SEG_BackLight;//配置引脚为"输出",并"关闭"LCD_Segment 背光 

////////////////////////////////////////////////////////////////////////////
//==**清除处理器内部的"段式LCD 显示缓存"**============//
	Clear_LCD_Segment(); //清屏: 清除处理器内部的"段式LCD 显示缓存"

////////////////////////////////////////////////////////////////////////////
//==**"LCD_B 控制寄存器"相关配置(MCU模块寄存器)**=======//
	EnAllSeg_LCD_Segment(NO); //禁止所有LCD_B段(用于所有液晶段(整屏)的闪烁)
	EnModule_LCD_Segment(NO); //关闭液晶LCD_B 模块

	//--care--一定要加上这个语句//"LCD_B 端口控制寄存器"相关配置
	LCDBPCTL0 = 0;
	mSelect_LCD_SEG_IoPin;//配置引脚为"IO"引脚
	mSetIn_LCD_SEG_COM;  //设置引脚都为"输入"

}



/****************************************************************************
*函数名-Function:	void Initial_LCD_Segment_LCD_B(void)
*描述- Description:	LCD_B模块初始化:端口初始化、配置LCD_B功能(LCD_Segment )
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Initial_LCD_Segment_LCD_B(void) //LCD_B模块初始化:端口初始化、配置LCD_B功能(LCD_Segment )
{
	mSPI_All_Disable;//驱动LCD_segment和IIC(TMP006)时，要禁用所有用到SPI_B的模块




////////////////////////////////////////////////////////////////////////////
//==**配置引脚为"外围模块功能"引脚**=================//

	mSelect_LCD_SEG_FunctionPin;//P5.5, P5.4, P5.3 用作LCD_B驱动引脚(配置引脚为"外围模块功能"引脚 )
	mSetOut_LCD_SEG_COM;  //设置引脚都为"输出"


////////////////////////////////////////////////////////////////////////////
//==**"LCD_B 端口控制寄存器"相关配置(MCU模块寄存器)**==//
		//--care--一定要加上这个语句//"LCD_B 端口控制寄存器"相关配置
	LCDBPCTL0 = LCDS0 + LCDS1 + LCDS2 + LCDS3 + LCDS4 + LCDS5 + LCDS6+ LCDS7 + LCDS8 \
				+ LCDS9 + LCDS10+ LCDS11;

////////////////////////////////////////////////////////////////////////////
//==**段式LCD_Segment 初始状态设置**=====================//
	
	EnAllSeg_LCD_Segment(YES); //使能所有LCD_B段(用于所有液晶段(整屏)的闪烁)
		
	EnModule_LCD_Segment(YES);  //打开液晶LCD_B 模块	

////////////////////////////////////////////////////////////////////////////
//==**配置多路复用器TS3A5017: 选择"LCD_B模块"**===========//
//--care--多路复用器的选择，一定要放在最前面
//--care--即先切换到LCD_B, 再初始化LCD_B
//--care--与切换到SPI_B (LCD_TFT) 步骤相反
		//IN2=1; IN1=0; 对应SEG9; SEG10; SEG11; 引脚

//	mHigh_LCD_TFT_CS; //配置引脚为"输出",并"输出高电平"
//mDelay_Cycles(3000);

	mConfig_TS3A5017_B_IN2(1);  //IN2 = 1
	mConfig_TS3A5017_B_IN1(0);  //IN1 = 0

	
}


/****************************************************************************
*函数名-Function:	void Refresh_LCD_Segment(unsigned char pointNum,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1)
*描述- Description:	更新显示(段式LCD_Segment)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Refresh_LCD_Segment(unsigned char pointNum,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1) //更新显示(段式LCD_Segment)
{
	Initial_LCD_Segment_LCD_B(); //LCD_B模块初始化:端口初始化、配置LCD_B功能(LCD_Segment )

////////////////////////////////////////////////////////////////////////////
//==**刷新显示(段式LCD_Segment)**=========================//

	if(pointNum == 1) LCDMEM[5] = LcdSeg_Tab[NO_1] | dp; //刷新第"1"个字符(从右边算起) (段式LCD_Segment)
	else LCDMEM[5] = LcdSeg_Tab[NO_1];//刷新第"1"个字符(从右边算起) (段式LCD_Segment)

	if(pointNum == 2) LCDMEM[4] = LcdSeg_Tab[NO_2] | dp; //刷新第"2"个字符(从右边算起) (段式LCD_Segment)
	else LCDMEM[4] = LcdSeg_Tab[NO_2];//刷新第"2"个字符(从右边算起) (段式LCD_Segment)

	if(pointNum == 3) LCDMEM[3] = LcdSeg_Tab[NO_3] | dp; //刷新第"3"个字符(从右边算起) (段式LCD_Segment)
	else LCDMEM[3] = LcdSeg_Tab[NO_3];//刷新第"3"个字符(从右边算起) (段式LCD_Segment)

	if(pointNum == 4) LCDMEM[2] = LcdSeg_Tab[NO_4] | dp;//刷新第"4"个字符(从右边算起) (段式LCD_Segment)	 
	else LCDMEM[2] = LcdSeg_Tab[NO_4];//刷新第"4"个字符(从右边算起) (段式LCD_Segment)

	if(pointNum == 5)
	{
		LCDMEM[2] = LCDMEM[2] | dp;  //显示"电池框"+最低电量
		LCDMEM[1] = LcdSeg_Tab[NO_5] | dp;//刷新第"5"个字符(从右边算起) (段式LCD_Segment)
	}
	else LCDMEM[1] = LcdSeg_Tab[NO_5];//刷新第"5"个字符(从右边算起) (段式LCD_Segment)

	if(pointNum == 6)
	{
		LCDMEM[2] = LCDMEM[2] | dp;  //显示"电池框"+最低电量
		LCDMEM[1] = LCDMEM[1] | dp;  //显示"电池框"+中间电量
		LCDMEM[0] = LcdSeg_Tab[NO_6] | dp;//刷新第"6"个字符(从右边算起) (段式LCD_Segment)
	}
	else LCDMEM[0] = LcdSeg_Tab[NO_6];//刷新第"6"个字符(从右边算起) (段式LCD_Segment)

}



/****************************************************************************
*函数名-Function:	void Init_Mode_LCD_Segment(void)
*描述- Description:	初使化"工作模式"(段式LCD_Segment)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Init_Mode_LCD_Segment(unsigned char Mode) //初使化"工作模式"(段式LCD_Segment)
{
	G_Last_Mode_LCD_Segment = G_Mode_LCD_Segment;//保存"上一次"的"工作模式"

	G_Mode_LCD_Segment = Mode;


	
			/*************************************************
			switch(Data) 
			{
			////////////////////////////////////////////////////////////////////////////
			//==** **=================================================//
				case :	
					break;	
			////////////////////////////////////////////////////////////////////////////
				default:	break;
			}
			*************************************************/

}


/****************************************************************************
*函数名-Function:	void Deal_LCD_Segment(void)
*描述- Description:	"段式LCD_Segment": 处理不同"工作模式"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：
	▲01)
	//LCDMEM[0] = dp;  //对应"最上面"的"电池符号"+"第6个字符"(从右边开始算)
	//LCDMEM[1] = dp;  //对应"中间"的"电池符号"+"第5个字符"(从右边开始算)
	//LCDMEM[2] = dp;  //对应"最下面"的"电池符号"+"电池框图"+"第4个字符"(从右边开始算)
	//LCDMEM[3] = dp;  //对应"最左边"的"小数点"+"第3个字符"(从右边开始算)
	//LCDMEM[4] = dp;  //对应"中间"的"小数点"+"第2个字符"(从右边开始算)
	//LCDMEM[5] = dp;  //对应"最右边"的"小数点"+"第1个字符"(从右边开始算)
	▲02) 	  ▲03)   	▲04)  
*****************************************************************************/
void Deal_LCD_Segment(void) //"段式LCD_Segment": 处理不同"工作模式"
{
	

	switch(G_Mode_LCD_Segment) 
	{
////////////////////////////////////////////////////////////////////////////
//==** **=================================================//
case MODE_Idle_LCD_Segment:	//Mode〓空闲(不做任何操作)(段式LCD_Segment)
	
	break;	

case MODE_Open_LCD_Segment:	//Mode〓"打开"此模块(段式LCD_Segment)
	Open_LCD_Segment(); 	//打开LCD_Segment (初使化): LCD_Segment 内部寄存器配置; 端口初始化等

		//执行一遍操作后，回到//Mode〓更新显示(段式LCD_Segment)
	G_Mode_LCD_Segment = MODE_Refresh_LCD_Segment; 
	break;	

case MODE_Close_LCD_Segment: //Mode〓"关闭"此模块(段式LCD_Segment)
	Close_LCD_Segment();  //关闭"段式LCD_Segment"

		//care//只执行一遍上面程序后，回到空闲模式
	G_Mode_LCD_Segment = MODE_Idle_LCD_Segment; 
	break;	

case MODE_Refresh_LCD_Segment: //Mode〓更新显示(段式LCD_Segment)
		//更新显示(段式LCD_Segment)
	Refresh_LCD_Segment(G_LcdSegBuf[6],G_LcdSegBuf[5],G_LcdSegBuf[4],G_LcdSegBuf[3],G_LcdSegBuf[2],G_LcdSegBuf[1],G_LcdSegBuf[0]);  

	//care  //这里不跳转到"MODE_Idle_LCD_Segment",让系统每次循环都刷新输出，提高抗干扰能力
	break;	

case MODE_OpenBackLight_LCD_Segment: //Mode〓"打开"背光(段式LCD_Segment)	

	mOpen_LCD_SEG_BackLight; //配置引脚为"输出",并"打开"LCD_Segment 背光

		//如果上一次为"Mode〓更新显示",返回Mode〓更新显示
	if(G_Last_Mode_LCD_Segment == MODE_Refresh_LCD_Segment)
	{
			//执行一遍操作后，回到//Mode〓更新显示(段式LCD_Segment)
		G_Mode_LCD_Segment = MODE_Refresh_LCD_Segment; 
	}
			//如果上一次为"Mode〓"关闭"此模块",返回Mode〓空闲
	else if(G_Last_Mode_LCD_Segment == MODE_Close_LCD_Segment)
	{
			//执行一遍操作后，回到//Mode〓空闲(不做任何操作)(段式LCD_Segment)
		G_Mode_LCD_Segment = MODE_Idle_LCD_Segment; 
	}
	break;	


case MODE_CloseBackLight_LCD_Segment: //Mode〓"关闭"背光(段式LCD_Segment)	

	mClose_LCD_SEG_BackLight;//配置引脚为"输出",并"关闭"LCD_Segment 背光 

		//如果上一次为"Mode〓更新显示",返回Mode〓更新显示
	if(G_Last_Mode_LCD_Segment == MODE_Refresh_LCD_Segment)
	{
			//执行一遍操作后，回到//Mode〓更新显示(段式LCD_Segment)
		G_Mode_LCD_Segment = MODE_Refresh_LCD_Segment; 
	}
			//如果上一次为"Mode〓"关闭"此模块",返回Mode〓空闲
	else if(G_Last_Mode_LCD_Segment == MODE_Close_LCD_Segment)
	{
			//执行一遍操作后，回到//Mode〓空闲(不做任何操作)(段式LCD_Segment)
		G_Mode_LCD_Segment = MODE_Idle_LCD_Segment; 
	}
	break;	

			


////////////////////////////////////////////////////////////////////////////
//==** **=================================================//

	
////////////////////////////////////////////////////////////////////////////
default:
	break;
	}

}


/****************************************************************************
*函数名-Function:	void Disp_LCD_Segment(unsigned char pointNum,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1)
*描述- Description:	"显示字符"更新到"显示缓存数组"(段式LCD_Segment)
*输入参数-Input:	pointNum:小数点的位置; NO_8~NO_1:从左到右的段式LCD_Segment 显示值
*输出参数-output:	None
*注意事项-Note：
	▲01)    
	//G_LcdSegBuf[0];  //对应"第1个字符"+"最右边"的"小数点"(从右边开始算)
	//G_LcdSegBuf[1];  //对应"第2个字符"+"中间"的"小数点"(从右边开始算)
	//G_LcdSegBuf[2];  //对应"第3个字符"+"最左边"的"小数点"(从右边开始算)
	//G_LcdSegBuf[3];  //对应"第4个字符"+"最下面"的"电池符号"+"电池框图"(从右边开始算)
	//G_LcdSegBuf[4];  //对应"第5个字符"+"中间"的"电池符号"(从右边开始算)
	//G_LcdSegBuf[5];  //对应"第6个字符"+"最上面"的"电池符号"(从右边开始算)
	▲02) 例 Disp_LCD_Segment(2,6,5,4,3,2,1); //表式从右到左显示图为"6543.21"
	▲03)    ▲04)  
*****************************************************************************/
void Disp_LCD_Segment(unsigned char pointNum,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1)
{
	G_LcdSegBuf[0] = NO_1;//对应"第1个字符"+"最右边"的"小数点"(从右边开始算)
	G_LcdSegBuf[1] = NO_2;
	G_LcdSegBuf[2] = NO_3;
	G_LcdSegBuf[3] = NO_4;
	G_LcdSegBuf[4] = NO_5;
	G_LcdSegBuf[5] = NO_6;
	G_LcdSegBuf[6] = pointNum;
}



