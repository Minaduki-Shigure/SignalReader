/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 TM1638.c
* 附属文件-Dependencies:  	 TM1638.h; Hardware_Profile.h; Generic.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■  "TM1638 数码管驱动器" -驱动程序(外部资源) 
	01) LED 高压驱动: 显示模式 10 段×8 位
	02) 辉度调节电路（占空比8 级可调）
	03) 带键盘扫描: 8×3 bit
	04) 串行接口（CLK，STB，DIO）  
	05) 振荡方式：RC 振荡（450KHz+5%）   
	06)	管脚功能说明：
		DIO (数据输入/输出) : 在时钟上升沿输入/输出串行数据，从低位开始；
		STB (片选) : 在上升或下降沿初始化串行接口，
		                       随后等待接收指令。STB 为低后的第一个字节
		                       作为指令，当处理指令时，当前其它处理被终止。
		                       当STB 为高时，CLK 被忽略.
		CLK (时钟输入) : 上升沿输入/输出串行数据。
		K1～K3 (键扫数据输入) : 输入该脚的数据在显示周期结束后被锁存
		Seg1/ks1~seg8/ks8 (输出"段") : 段输出（也用作键扫描）,"P管"开漏输出
		Seg9～Seg10 (输出"段") : 段输出，"P管"开漏输出
		Grid1～Grid8  (输出"位") : 位输出，"N管"开漏输出
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 注意事项-Attention : 	
	▲01) 引脚DIO 口输出数据时为N管开漏输出，
			在读键的时候需要外接1K-10K的上拉电阻。  
	▲02) DIO在时钟的下降沿控制N管的动作，此时读数时不稳定
			在时钟的上升沿读数才时稳定。读取数据时，从串行
			时钟CLK 的第8 个上升沿开始设置指令到CLK 下降沿
			读数据之间需要一个等待时间Twait (最小1μS)。
	▲03) 写LED显示数据的时候，按照从低位地址到高位地址，
			从字节的低位到高位操作；在运用中没有使用到的
			SEG输出口，在对应的BIT地址位写0。   
	▲04) TM1638最多可以读4个字节，不允许多读。
	▲05) 矩阵按键扫描: ，先发读键命令后，开始读取按键数据
			BYTE1—BYTE4字节，读数据从低位开始输出.   
			读数据字节只能按顺序从BYTE1-BYTE4读取，不可跨字节读。   
	▲06) 当K1与KS8，K2与KS8，K3与KS8三个按键同时按下时，
			此时BYTE4所读数据的B4，B5，B6位均为1   
	▲07) "组合键"只能是"同一个KS"，不同的"K"引脚才能做组合键；
		同一个"K"与不同的"KS"引脚不可以做成组合键使用。 
	▲08)  
	▲09)  
	▲10) 
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



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
union FLAGBIT16 TM1638_FlagBits;  //"TM1638"用到的时间标志位


unsigned char G_TM1638_DispMode = 0; //TM1638的显示辉度变量


////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////
	//"数码管LED_Segment" 显示表格
						     // 0      1      2      3        4       5      6      7        8      9      A        B      C       D       E      F       .        +      -      =   AllOn  AllOff,   I,       r,     U
unsigned char LedSeg_Tab[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x80,0x60,0x40,0x48,0xff,0x00,0x30,0x50,0x3E};
												


/****************************************************************************
*函数名-Function:	static void TM1638_Write(unsigned char Data) 
*描述- Description:	写数据函数(TM1638)
*输入参数-Input:	Data : 8位的数据
*输出参数-output:	None
*注意事项-Note：	
	▲01) 在函数的返回类型前加上static 关键字，函数即被定义
		为静态函数。静态函数与普通函数不同，它只能在声明
		它的文件当中可见，不能被其它文件使用。 
	▲02)  从"低位"开始
	▲03)    ▲04)  
*****************************************************************************/
static void TM1638_Write(unsigned char Data)   //写数据函数(TM1638)
{
	unsigned char i = 0;
	
	for(i = 0; i < 8; i++)
	{
		mLow_TM1638_CLK;  //CLK 输出"低"

		if(Data & 0x01) 
		{
			mHigh_TM1638_DIO; //DIO输出"高"
		}
		else
		{
			mLow_TM1638_DIO; //DIO输出"低"
		}

		mHigh_TM1638_CLK;  //CLK 输出"高"

		Data >>= 1;
	}
}



/****************************************************************************
*函数名-Function:	static unsigned char TM1638_Read(void) 
*描述- Description:	读数据函数(TM1638)
*输入参数-Input:	Nonew
*输出参数-output:	Data : 返回读到的数据(8位)
*注意事项-Note：	
	▲01) 在函数的返回类型前加上static 关键字，函数即被定义
		为静态函数。静态函数与普通函数不同，它只能在声明
		它的文件当中可见，不能被其它文件使用。   
	▲02) 从"低位"开始   
	▲03) 	读取数据时，从串行时钟CLK 的第8 个上升沿开始设置指令
   	         到CLK 下降沿读数据之间需要一个等待时间Twait (最小1μS)
	▲04)  
*****************************************************************************/
static unsigned char TM1638_Read(void)   //  读数据函数(TM1638)
{
	unsigned char i = 0;
	unsigned char Data = 0;

	mSetIn_TM1638_DIO;	 //配置DIO为"输入"引脚

	for(i = 0; i < 8; i++)
	{
		
		Data >>= 1; 
		mLow_TM1638_CLK;  //CLK 输出"低"
		
	//读取数据时，从串行时钟CLK 的第8 个上升沿开始设置指令
	//到CLK 下降沿读数据之间需要一个等待时间Twait (最小1μS)。
		mDelay_Cycles(M_Delay_2us);
		
		

		if(mRead_TM1638_DIO) Data |= 0x80; // 读取"DIO电平"
		else  Data &= 0x7f;
		
		mHigh_TM1638_CLK;  //CLK 输出"高"
		
		
	}
	return (Data);
}



/****************************************************************************
*函数名-Function:	static void TM1638_Set_CMD(unsigned char Cmd)  
*描述- Description:	写命令字(TM1638)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01) 在函数的返回类型前加上static 关键字，函数即被定义
		为静态函数。静态函数与普通函数不同，它只能在声明
		它的文件当中可见，不能被其它文件使用。 
	▲02)     ▲03)    ▲04)  
*****************************************************************************/
static void TM1638_Set_CMD(unsigned char Cmd)  //写命令字(TM1638)
{
	mLow_TM1638_STB;  //STB 输出"低"	

	TM1638_Write(Cmd);

	mHigh_TM1638_STB;  //STB 输出"高"
}




/****************************************************************************
*函数名-Function:	void TM1638_Disp_Mode(unsigned char Disp_Mode)
*描述- Description:	设置显示模式:显示关、显示开+辉度调节(不同PWM占空比驱动)(TM1638)
*输入参数-Input:	Data : 要显示的内容(8位的数据)
*输出参数-output:	None
*注意事项-Note：	
	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void TM1638_Disp_Mode(unsigned char Disp_Mode) //设置显示模式:显示关、显示开+辉度调节(不同PWM占空比驱动)(TM1638)
{
	TM1638_Set_CMD(Disp_Mode);//打开显示//亮度最暗为"脉冲宽度为1/16"
}



/****************************************************************************
*函数名-Function:	void Disp_Single_LedSeg(unsigned char Num,unsigned char Disp_Mode,unsigned char Data)  
*描述- Description:	指定"单个"数码管: 以指定"辉度"显示字符(TM1638)
*输入参数-Input:	Num: 第Num个数码管;  Disp_Mode:显示模式;    Data : 要显示的内容(8位的数据)
*输出参数-output:	None
*注意事项-Note：	
	▲01) 驱动"共阴"数码管
	▲02) 输入参数Num: 只能为1,2,3,4,5,6,7,8
		     输入参数Data: 只能为0~21 (其中20:表示Led段"全亮";21:表示Led段"全暗")
	▲03) 例Disp_Single_LedSeg(6, Disp_Mode_1_16, 6) ;  //右边开始的第6个数码管,以辉度"Disp_Mode_1_16"显示"6" 
	▲04)  
*****************************************************************************/
void Disp_Single_LedSeg(unsigned char Num,unsigned char Disp_Mode,unsigned char Data)  //指定"单个"数码管: 以指定"辉度"显示字符(TM1638)
{
	unsigned char LedNum = 0;
	
////////////////////////////////////////////////////////////////////////////
//--**设置"显示"模式**----------------------------------------------//
		//显示关、显示开+辉度调节(不同PWM占空比驱动)
		
	TM1638_Disp_Mode(Disp_Mode);//显示"开"+"脉冲宽度为1/16" (最暗)

////////////////////////////////////////////////////////////////////////////
//--**设置"数据命令"**----------------------------------------------//
	TM1638_Set_CMD(CMD_FixedAddr_TM1638);  //Cmd★设置地址模式: 固定地址(数据命令)


	mLow_TM1638_STB;  //STB 输出"低"	

////////////////////////////////////////////////////////////////////////////
//--**设置"地址"**----------------------------------------------------//
	switch(Num) 
	{
		case 1:	   // 第1个数码管
			LedNum = 6;  
			break;	
			
		case 2:   // 第2个数码管
			LedNum = 4;
			break;	

		case 3:   // 第3个数码管
			LedNum = 2;
			break;	

		case 4:   // 第4个数码管
			LedNum = 0;
			break;	
			
		case 5:   // 第5个数码管
			LedNum = 14;
			break;	
			
		case 6:   // 第6个数码管
			LedNum = 12;
			break;	

		case 7:   // 第7个数码管
			LedNum = 10;
			break;	

		case 8:   // 第8个数码管
			LedNum = 8;
			break;	
////////////////////////////////////////////////////////////////////////////
		default:
			break;
	}



	TM1638_Write(CMD_DispAddr_TM1638 | LedNum);  

////////////////////////////////////////////////////////////////////////////
//--**传输"显示数据"**----------------------------------------------//
	TM1638_Write(LedSeg_Tab[Data]);

	mHigh_TM1638_STB;  //STB 输出"高"
}


/****************************************************************************
*函数名-Function:	void Close_Display_TM1638(void)
*描述- Description:	设置显示模式:显示关(TM1638)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Close_Display_TM1638(void) //设置显示模式:显示关(TM1638)
{
////////////////////////////////////////////////////////////////////////////
//--**设置"显示"模式**----------------------------------------------//
		//显示"关"
	TM1638_Disp_Mode(Disp_Mode_Off);

////////////////////////////////////////////////////////////////////////////
//--**传输"显示数据"**----------------------------------------------//
		//清除显示地址内容//向TM1638显示地址写要"显示的数据"(TM1638)
	Write_DispData_TM1638(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);

}


/****************************************************************************
*函数名-Function:	void Open_Display_TM1638(void)
*描述- Description:	打开显示(初始化):显示"开"+辉度"PWM为1/16" (最暗)(TM1638)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Open_Display_TM1638(void) //打开显示(初始化):显示"开"+辉度"PWM为1/16" (最暗)(TM1638)
{

////////////////////////////////////////////////////////////////////////////
//--**设置"显示"模式**----------------------------------------------//
		//显示"开"+辉度"PWM为1/16" (最暗)
//blues// TM1638_Disp_Mode(Disp_Mode_1_16);


	
////////////////////////////////////////////////////////////////////////////
//--**传输"显示数据"**----------------------------------------------//
		//清除显示地址内容//向TM1638显示地址写要"显示的数据"(TM1638)
	Write_DispData_TM1638(0,0,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg,DISP_OFF_LedSeg);
}



/****************************************************************************
*函数名-Function:	void Write_DispData_TM1638(unsigned char pointNum1,unsigned char pointNum2,unsigned char NO_8,unsigned char NO_7,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1)
*描述- Description:	向	TM1638显示地址写要"显示的数据"(TM1638)
*输入参数-Input:	pointNum1:小数点的位置(第1处小数点);
						pointNum2:小数点的位置(第2处小数点);
                                         NO_8~NO_1:从左到右的数码管LED_Segment显示值
*输出参数-output:	None
*注意事项-Note：	
	▲01) 驱动"共阴"数码管
	▲02) 不显示的数码管，则写入暗码,一次性刷新所有数码管
	▲03) 例 Write_DispData_TM1638(8,2,8,7,6,5,4,3,2,1); //表式从右到左显示图为"8.765432.1"
	                  Write_DispData_TM1638(0,2,8,7,6,5,4,3,2,1); //表式从右到左显示图为"8765432.1"
	▲04)   NO_1--0xC6 (TM1638显示地址);  //对应第"1位"数码管(从最右边算起) 
			NO_2--0xC4(TM1638显示地址);  //对应第"2位"数码管(从最右边算起) 
			NO_3--0xC2(TM1638显示地址);  //对应第"3位"数码管(从最右边算起) 
			NO_4--0xC0(TM1638显示地址);  //对应第"4位"数码管(从最右边算起) 
			NO_5--0xCE(TM1638显示地址);  //对应第"5位"数码管(从最右边算起) 
			NO_6--0xCC(TM1638显示地址);  //对应第"6位"数码管(从最右边算起) 
			NO_7--0xCA(TM1638显示地址);  //对应第"7位"数码管(从最右边算起) 
			NO_8--0xC8(TM1638显示地址);  //对应第"8位"数码管(从最右边算起) 
*****************************************************************************/
void Write_DispData_TM1638(unsigned char pointNum1,unsigned char pointNum2,unsigned char NO_8,unsigned char NO_7,unsigned char NO_6,unsigned char NO_5,unsigned char NO_4,unsigned char NO_3,unsigned char NO_2,unsigned char NO_1)
{
////////////////////////////////////////////////////////////////////////////
//--**设置"显示"模式**----------------------------------------------//
	//显示关、显示开+辉度调节(不同PWM占空比驱动)
//TM1638_Disp_Mode(Disp_Mode);


////////////////////////////////////////////////////////////////////////////
//--**设置"数据命令"**----------------------------------------------//
	TM1638_Set_CMD(CMD_IncreaseAddr_TM1638); //Cmd★设置地址模式: 自动地址增加


////////////////////////////////////////////////////////////////////////////
	mLow_TM1638_STB;  //STB 输出"低"	

////////////////////////////////////////////////////////////////////////////
//--**设置"地址"**----------------------------------------------------//
		//设置地址实际上是设置传送的数据流存放的起始地址。
	TM1638_Write(CMD_DispAddr_TM1638);  //起始显示地址"00H", 之后，地址自动递增


////////////////////////////////////////////////////////////////////////////
//--**传输"显示数据"**----------------------------------------------//
		
	if((pointNum1 == 4)||(pointNum2 == 4)) TM1638_Write(LedSeg_Tab[NO_4] | 0x80);  //TM1638显示地址0xC0: 对应第"4位"数码管
	else TM1638_Write(LedSeg_Tab[NO_4]);  //TM1638显示地址0xC0: 对应第"4位"数码管
	TM1638_Write(0x00); //0xC1//没用到的数码段Seg9、Seg10写入0x00 //16个显示地址中的"奇地址" 


	if((pointNum1 == 3)||(pointNum2 == 3)) TM1638_Write(LedSeg_Tab[NO_3] | 0x80);  //TM1638显示地址0xC2: 对应第"3位"数码管
	else TM1638_Write(LedSeg_Tab[NO_3]);  //TM1638显示地址0xC2: 对应第"3位"数码管
	TM1638_Write(0x00); //0xC3//没用到的数码段Seg9、Seg10写入0x00 //16个显示地址中的"奇地址" 


	if((pointNum1 == 2)||(pointNum2 == 2)) TM1638_Write(LedSeg_Tab[NO_2] | 0x80);  //TM1638显示地址0xC4: 对应第"2位"数码管
	else TM1638_Write(LedSeg_Tab[NO_2]);  //TM1638显示地址0xC4: 对应第"2位"数码管
	TM1638_Write(0x00); //0xC5//没用到的数码段Seg9、Seg10写入0x00 //16个显示地址中的"奇地址" 


	if((pointNum1 == 1)||(pointNum2 == 1)) TM1638_Write(LedSeg_Tab[NO_1] | 0x80);  //TM1638显示地址0xC6: 对应第"1位"数码管
	else TM1638_Write(LedSeg_Tab[NO_1]);  //TM1638显示地址0xC6: 对应第"1位"数码管
	TM1638_Write(0x00); //0xC7//没用到的数码段Seg9、Seg10写入0x00 //16个显示地址中的"奇地址" 


	if((pointNum1 == 8)||(pointNum2 == 8)) TM1638_Write(LedSeg_Tab[NO_8] | 0x80);  //TM1638显示地址0xC8: 对应第"8位"数码管
	else TM1638_Write(LedSeg_Tab[NO_8]);  //TM1638显示地址0xC8: 对应第"8位"数码管
	TM1638_Write(0x00); //0xC9//没用到的数码段Seg9、Seg10写入0x00 //16个显示地址中的"奇地址" 

	if((pointNum1 == 7)||(pointNum2 == 7)) TM1638_Write(LedSeg_Tab[NO_7] | 0x80);  //TM1638显示地址0xCA: 对应第"7位"数码管
	else TM1638_Write(LedSeg_Tab[NO_7]);  //TM1638显示地址0xCA: 对应第"7位"数码管
	TM1638_Write(0x00); //0xCB//没用到的数码段Seg9、Seg10写入0x00 //16个显示地址中的"奇地址" 

	if((pointNum1 == 6)||(pointNum2 == 6)) TM1638_Write(LedSeg_Tab[NO_6] | 0x80);  //TM1638显示地址0xCC: 对应第"6位"数码管
	else TM1638_Write(LedSeg_Tab[NO_6]);  //TM1638显示地址0xCC: 对应第"6位"数码管
	TM1638_Write(0x00); //0xCD//没用到的数码段Seg9、Seg10写入0x00 //16个显示地址中的"奇地址" 

	if((pointNum1 == 5)||(pointNum2 == 5)) TM1638_Write(LedSeg_Tab[NO_5] | 0x80);  //TM1638显示地址0xCE: 对应第"5位"数码管
	else TM1638_Write(LedSeg_Tab[NO_5]);  //TM1638显示地址0xCE: 对应第"5位"数码管
	TM1638_Write(0x00); //0xCF//没用到的数码段Seg9、Seg10写入0x00 //16个显示地址中的"奇地址" 

	mHigh_TM1638_STB;  //STB 输出"高"
}




/****************************************************************************
*函数名-Function:	void Deal_Brightness_TM1638(unsigned char DispMode)
*描述- Description:	处理"动态数码管LED_Segment" :显示关，显示开，调节"辉度PWM"(TM1638)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	
	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Deal_Brightness_TM1638(unsigned char DispMode) //处理"动态数码管LED_Segment" :显示关，显示开，调节"辉度PWM"(TM1638)
{
	switch(DispMode) 
	{
////////////////////////////////////////////////////////////////////////////
//==** **=================================================//
		case 0:	
			TM1638_Disp_Mode(Disp_Mode_Off);//显示"关"
			break;	

////////////////////////////////////////////////////////////////////////////
//==** **=================================================//
		case 1: 
			TM1638_Disp_Mode(Disp_Mode_1_16);//显示"开"+辉度"PWM为1/16" (最暗)
			break;	

		case 2: 
			TM1638_Disp_Mode(Disp_Mode_2_16);//显示"开"+辉度"PWM为2/16"
			break;	
			
		case 3: 
			TM1638_Disp_Mode(Disp_Mode_4_16);//显示"开"+辉度"PWM为4/16"
			break;	

		case 4: 
			TM1638_Disp_Mode(Disp_Mode_10_16);//显示"开"+辉度"PWM为10/16"
			break;	

		case 5: 
			TM1638_Disp_Mode(Disp_Mode_11_16);//显示"开"+辉度"PWM为11/16"
			break;	
			
		case 6: 
			TM1638_Disp_Mode(Disp_Mode_12_16);//显示"开"+辉度"PWM为12/16"
			break;	
			
		case 7: 
			TM1638_Disp_Mode(Disp_Mode_13_16);//显示"开"+辉度"PWM为13/16"
			break;	
			
		case 8: 
			TM1638_Disp_Mode(Disp_Mode_14_16);//显示"开"+辉度"PWM为14/16" (最亮)
			break;	
////////////////////////////////////////////////////////////////////////////
		default:
			break;
	}

}



/****************************************************************************
*函数名-Function:	unsigned char Read_MatrixKey_TM1638(void)
*描述- Description:	读矩阵按键值(TM1638)
*输入参数-Input:	NoneData : 8位的数据
*输出参数-output:	返回矩阵"按键值"
*注意事项-Note：	
	▲01) 在函数的返回类型前加上static 关键字，函数即被定义
		为静态函数。静态函数与普通函数不同，它只能在声明
		它的文件当中可见，不能被其它文件使用。 
	▲02)   	▲03)    ▲04)  
*****************************************************************************/
unsigned char Read_MatrixKey_TM1638(void) //读矩阵按键值(TM1638)
{
	unsigned char KeyByte[4];
	unsigned char i = 0;

	mLow_TM1638_STB;  //STB 输出"低"	
	
	TM1638_Write(0x42);
	
	for(i = 0; i < 4; i++)
	{
		KeyByte[i] = TM1638_Read();
	}
	
	mHigh_TM1638_STB;  //STB 输出"高"

	if(KeyByte[0] & BIT_2) return 1;
	else if(KeyByte[0] & BIT_6) return 4;
	else if(KeyByte[0] & BIT_0) return 2;
	else if(KeyByte[0] & BIT_1) return 3;
	else if(KeyByte[0] & BIT_5) return 6;
	else if(KeyByte[0] & BIT_4) return 5;
	else if(KeyByte[1] & BIT_0) return 0xb;
	else if(KeyByte[1] & BIT_4) return 0xc;
	else if(KeyByte[2] & BIT_0) return 0xd;
	else if(KeyByte[2] & BIT_4) return 8;
	else if(KeyByte[1] & BIT_1) return 0xa;
	else if(KeyByte[1] & BIT_5) return 0xb;
	else if(KeyByte[2] & BIT_5) return 9;
	else if(KeyByte[2] & BIT_6) return 7;
	else if(KeyByte[3] & BIT_0) return 0xf;
	else if(KeyByte[3] & BIT_1) return 0xe;
	else if(KeyByte[3] & BIT_2) return 0;
	else if(KeyByte[1] & BIT_2) return 0x13; //"AC" 特殊符号
	else if(KeyByte[1] & BIT_6) return 0x12; // "+" 特殊符号
	else if(KeyByte[2] & BIT_2) return 0x11; //" -" 特殊符号
	else if(KeyByte[2] & BIT_1) return 0x10; //"=" 特殊符号

	return (0xFF);
}






