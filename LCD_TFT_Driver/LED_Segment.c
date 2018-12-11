/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 LED_Segment.c
* 附属文件-Dependencies:  	 LED_Segment.h; TM1638.h;  Hardware_Profile.h;  Generic.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■"动态数码管LED_Segment" -驱动程序(外部资源)
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


#include "TM1638.h"  // "TM1638 数码管驱动器" -驱动程序(外部资源) -头文件

#include "LED_Segment.h" //"动态数码管LED_Segment" -驱动程序(外部资源)-头文件



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//--**"动态数码管LED_Segment" *全局标志位**------------------------------//
union FLAGBIT16 LED_Seg_FlagBits; //"动态数码管LED_Segment" 相关标志位变量

unsigned char G_Mode_LED_Segment = 0; //"动态数码管LED_Segment" 工作模式
unsigned char G_Last_Mode_LED_Segment = 0; //保存上一次"工作模式"


unsigned char G_LedSeg_Cnt = 0; //"动态数码管LED_Segment" 中用到的计数器(用于字符循环显示)
unsigned char G_LedSegBuf[10]; //"动态数码管LED_Segment" 显示缓存数组//G_LedSegBuf[0]对应最"右边"的显示字符


unsigned char G_Brightness_LedSeg = 0;  //亮度调节-"动态数码管LED_Segment" 
	//亮度变量-"动态数码管LED_Segment"
unsigned char G_BrightnessKind = M_Brightness_1_LedSeg;   //默认:亮度为1(最暗)--"动态数码管LED_Segment" 

    

////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////





/****************************************************************************
*函数名-Function:	void Open_LED_Segment(void)
*描述- Description:	初使化: 显示"开"+辉度"PWM为1/16" (最暗)("动态数码管LED_Segment" )
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Open_LED_Segment(void)  //初使化: 显示"开"+辉度"PWM为1/16" (最暗)("动态数码管LED_Segment" )
{
////////////////////////////////////////////////////////////////////////////
//==**"动态数码管LED_Segment" 辉度控制**==================//
			//亮度为1(暗)--"动态数码管LED_Segment" 
//blues// G_Brightness_LedSeg = M_Brightness_1_LedSeg;	
	Open_Display_TM1638(); //打开显示(初始化):显示"开"+辉度"PWM为1/16" (最暗)(TM1638)

}

/****************************************************************************
*函数名-Function:	void Close_LED_Segment(void)
*描述- Description:	关闭LED_Segment 模块("动态数码管LED_Segment" )
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Close_LED_Segment(void) //关闭LED_Segment 模块("动态数码管LED_Segment" )
{
////////////////////////////////////////////////////////////////////////////
//==**"动态数码管LED_Segment" 辉度控制**==================//
		//亮度为0 (显示关)--"动态数码管LED_Segment" 
	//G_Brightness_LedSeg = M_Brightness_OFF_LedSeg;
		//清显示缓存数组
	Disp_LED_Segment(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);

	Close_Display_TM1638();//设置显示模式:显示关(TM1638)
}




/****************************************************************************
*函数名-Function:	void Deal_Brightness_LED_Segment(void)
*描述- Description:	处理数码管"辉度(亮度)"("动态数码管LED_Segment" )
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_Brightness_LED_Segment(void) //处理数码管"辉度(亮度)"
{
		//处理"动态数码管LED_Segment" :显示关，显示开，调节"辉度PWM"(TM1638)
	Deal_Brightness_TM1638(G_Brightness_LedSeg); 
}




/****************************************************************************
*函数名-Function:	void Refresh_LED_Segment(void)
*描述- Description:	更新显示("动态数码管LED_Segment" )
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01)  
	//G_LedSegBuf[0];  //对应"第1个"显示字符(数码管)
	//G_LedSegBuf[1];  //对应"第2个"显示字符(数码管)
	//G_LedSegBuf[2];  //对应"第3个"显示字符(数码管)
	//G_LedSegBuf[3];  //对应"第4个"显示字符(数码管)
	//G_LedSegBuf[4];  //对应"第5个"显示字符(数码管)
	//G_LedSegBuf[5];  //对应"第6个"显示字符(数码管)
	//G_LedSegBuf[6];  //对应"第7个"显示字符(数码管)
	//G_LedSegBuf[7];  //对应"第8个"显示字符(数码管)
	//G_LedSegBuf[8];  //对应"第1处小数点"显示字符(数码管)
	//G_LedSegBuf[9];  //对应"第2处小数点"显示字符(数码管)

	▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Refresh_LED_Segment(void) //更新显示("动态数码管LED_Segment" )
{
////////////////////////////////////////////////////////////////////////////
//==**刷新显示("动态数码管LED_Segment" )**=================//
		//向TM1638显示地址写要"显示的数据"(TM1638)
	Write_DispData_TM1638(G_LedSegBuf[9],G_LedSegBuf[8],G_LedSegBuf[7],G_LedSegBuf[6],G_LedSegBuf[5],G_LedSegBuf[4],G_LedSegBuf[3],G_LedSegBuf[2],G_LedSegBuf[1],G_LedSegBuf[0]);
}





/****************************************************************************
*函数名-Function:	void Init_Mode_LED_Segment(void)
*描述- Description:	初使化"工作模式"("动态数码管LED_Segment" )
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Init_Mode_LED_Segment(unsigned char Mode) //初使化"工作模式"("动态数码管LED_Segment" )
{
	G_Last_Mode_LED_Segment = G_Mode_LED_Segment;//保存"上一次"的"工作模式"

	G_Mode_LED_Segment = Mode;


	
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
*函数名-Function:	void Deal_LED_Segment(void)
*描述- Description:	"动态数码管LED_Segment" : 处理不同"工作模式"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：
	▲01)   	▲02) 	  ▲03)   	▲04)  
*****************************************************************************/
void Deal_LED_Segment(void) //"动态数码管LED_Segment" : 处理不同"工作模式"
{
////////////////////////////////////////////////////////////////////////////
//==** **=================================================//
		//--care--care--TM1638,一个API在中断中调用，一个API在主循环中调用。如果在执行主循环的API时，进入中断里的TM1638的API,就会产生干扰
		//下面语句，保证这两个API,不会在同一时间内被调用
	F_En_Scan_MatrixKey = NO;  //禁止扫描"矩阵按键扫描"

	switch(G_Mode_LED_Segment) 
	{
case MODE_Idle_LED_Segment:	//Mode〓空闲(不做任何操作)("动态数码管LED_Segment" )
	
	break;	

case MODE_Open_LED_Segment:	//Mode〓"打开"此模块("动态数码管LED_Segment" )
		//显示"开"+辉度"PWM为1/16" (最暗)("动态数码管LED_Segment" )
	Open_LED_Segment();
		//执行一遍操作后，回到//Mode〓更新显示("动态数码管LED_Segment" )
	G_Mode_LED_Segment = MODE_Refresh_LED_Segment; 	
	break;	

case MODE_Close_LED_Segment: //Mode〓"关闭"此模块("动态数码管LED_Segment" )	
		//关闭LED_Segment ("动态数码管LED_Segment" )
	Close_LED_Segment();
	break;	

case MODE_Refresh_LED_Segment: //Mode〓更新显示("动态数码管LED_Segment" )
		//处理数码管"辉度(亮度)"("动态数码管LED_Segment" )
	Deal_Brightness_LED_Segment();

	Refresh_LED_Segment(); //更新显示("动态数码管LED_Segment" )
	break;	

////////////////////////////////////////////////////////////////////////////
default:
	break;
	}

	F_En_Scan_MatrixKey = YES;  //使能"矩阵按键扫描"


}



/****************************************************************************
*函数名-Function:	void Disp_LED_Segment(unsigned char pointNum1,unsigned char pointNum2,unsigned char NO_8,unsigned char NO_7,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1)
*描述- Description:	"显示字符"更新到"显示缓存数组"("动态数码管LED_Segment" )
*输入参数-Input:	pointNum1:缓存中的小数点位置(第1处小数点);  
						pointNum2:缓存中的小数点位置(第2处小数点);  
                                         NO_8~NO_1:缓存中的各个数码管显示值
*输出参数-output:	None
*注意事项-Note：
	▲01)    
	//G_LedSegBuf[0];  //对应"第1个字符"
	//G_LedSegBuf[1];  //对应"第2个字符"
	//G_LedSegBuf[2];  //对应"第3个字符"
	//G_LedSegBuf[3];  //对应"第4个字符"
	//G_LedSegBuf[4];  //对应"第5个字符"
	//G_LedSegBuf[5];  //对应"第6个字符"
	//G_LedSegBuf[6];  //对应"第7个字符"
	//G_LedSegBuf[7];  //对应"第8个字符"
	▲02) pointNum为0时，表示不显示"小数点"
	例 Disp_LED_Segment(8,2,8,7,6,5,4,3,2,1); //表式从右到左显示图为"8.765432.1"
	      Disp_LED_Segment(0,2,8,7,6,5,4,3,2,1); //表式从右到左显示图为"8765432.1"
	▲03)    ▲04)  
*****************************************************************************/
void Disp_LED_Segment(unsigned char pointNum1,unsigned char pointNum2,unsigned char NO_8,unsigned char NO_7,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1)
{
	G_LedSegBuf[0] = NO_1;//对应"第1个字符"+"最右边"的"小数点"(从右边开始算)
	G_LedSegBuf[1] = NO_2;
	G_LedSegBuf[2] = NO_3;
	G_LedSegBuf[3] = NO_4;
	G_LedSegBuf[4] = NO_5;
	G_LedSegBuf[5] = NO_6;
	G_LedSegBuf[6] = NO_7;
	G_LedSegBuf[7] = NO_8;
	G_LedSegBuf[8] = pointNum1;
	G_LedSegBuf[9] = pointNum2;

}

