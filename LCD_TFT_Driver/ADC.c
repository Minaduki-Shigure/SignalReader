/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 ADC.c
* 附属文件-Dependencies:  	 ADC.h; msp430f6638.h; Hardware_Profile.h; Generic.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■ "ADC"模数转换模块 -驱动程序(处理器内部资源) 
	01) MSP430F6638 的ADC12_A模数转换模块支持12 位精度模数转换，
具有一个12 位的逐次渐进（SAR）内核.主要由具有采样与保持
功能的12 位转换器内核、采样选择控制、参考电压发生器
以及16 个字转换控制缓冲区组成。
	02) ADC12 模块的主要特性：12 位转换精度，1 位非线形误差，
1 位非线形积分误差；多种时钟源给ADC12 模块，本身自带时钟
发生器；内置温度传感器；8 路外部通道和4 路内部通道；
TimerA/TimerB 硬件触发器；内置参考电压源和6 种参考电压组合；
4 种模式的模数转换；16bit 的转换缓存；ADC12 关闭支持超低功耗；
采用速度快，最高200Kbps；自动扫描；DMA 使能。
	03) ADC12 提供4 种转换模式，分别是单通道单次转换、序列
通道多次转换、单通道多次转换、序列通道多次转换。
	04) ADC12_A模块包括一个内置的参考电压，提供3 个可选电压
等级，1.5V，2.0V和2.5V。每一个参考电压都可以作为内部参考
电压或输出到外部引脚Vref+。设置ADC12REFON = 1，将使能ADC12_A模块
的参考电压。当ADC12REF2_5=1时，内部参考电压为2.5V。
当ADC12REF2_5=0 时，参考电压为1.5V。
	05) ADC12_A支持8 位、10 位及12 位分辨率模式，可以通过ADC12RES
位	选择。模数转换分别需要9、11、及13 个ADC12CLK 周期
	06) 当使用片上的温度传感器时，采样周期必须大于30us。
温度传感器的偏移误差可能比较大，在实际大部分应用中需要
进行校准。实际使用的温度校准值见TLV描述符.	
	07)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 注意事项-Attention : 	
	▲01)输入模拟电压的最转换结果满足公式：
						NADC=4095×(Vin – VR-)/(VR+ - VR-)
	▲02)     ▲03)    ▲04)    ▲05)    ▲06)     
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


#include "msp430f6638.h"   // "处理器"头文件: 内部寄存相关定义等(处理器内部资源) 


#include "TM1638.h"  // "TM1638 数码管驱动器" -驱动程序(外部资源) -头文件


#include "ADC.h"   //"ADC"模数转换模块 -驱动程序-头文件(处理器内部资源) 



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
union FLAGBIT16 ADC_FlagBits; //"ADC模数转换"相关标志位变量

unsigned int G_LastAdResult = 0; //把M_AdSampleNum次AD采样值从小到大排序后，求得的最后AD计算值


////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned int pAdBuf[M_AdSampleNum];  //数组用于缓存M_AdSampleNum次AD的采样值   
unsigned char pAdCnt = 0;  //pAdBuf[]对应的指针  





/****************************************************************************
*函数名-Function:	void ADC12_A_Initial(void)
*描述- Description:	ADC12_A  内部资源初始化 
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void ADC12_A_Initial(void) //ADC12_A  内部资源初始化 
{
	REFCTL0 &= ~REFMSTR;                      // Reset REFMSTR to hand over control to   ADC12_A ref control registers
		//REFMSTR  REF 主控制位 //0：参考系统由ADC12_A模块的原先的控制位来控制   //1：参考系统有REFCTL 寄存器来控制，不用考虑ADC12_A   模块中相同的寄存器位              
	                                
		// 打开ADC12，设置采样时间                                     
	//ADC12CTL0 = ADC12ON+ADC12SHT0_15+ADC12REFON+ADC12REF2_5V; // Turn on ADC12, Sampling time  On Reference Generator and set to 2.5V
	ADC12CTL0 = ADC12SHT0_15+ADC12REFON+ADC12REF2_5V; // Turn on ADC12, Sampling time  On Reference Generator and set to 2.5V					
		//ADC12SHT0_15  ADC12_A采样保持时间。这些位定义寄存器ADC12MEM0 到ADC12MEM7 的采样时间的ADC12CLK 数。  //ADC12_A sample-and-hold time.  //These bits define the number of ADC12CLK cycles in the sampling period for registers ADC12MEM0 to ADC12MEM7. 
        //ADC12REFON  ADC12_A 参考电压打开。//1  内部参考电压打开 //0  内部参考电压关闭                    
		//ADC12REF2_5V  ADC12_A参考电压发生器。ADC12REFON 位必须置1。//0  1.5V  //1  2.5V

		// 打开采样定时器，设置转换模式为单通道单次转换模式，ADC12内核时钟源选择ACLK
	ADC12CTL1 = ADC12SHP+ADC12SSEL_3;   // Use sampling timer
		//ADC12SHP  ADC12_A采样保持脉冲模式选择。该位选择采样信号（SAMPCON）的来源是采样定时器的输出，或直接是采样输入信号。//0  SAMPCON 信号来自采样输入信号  //1  SAMPCON 信号来自采样定时器
		//ADC12SSEL_1  ADC12_A时钟源选择//00 MODCLK //01 ACLK  //10 MCLK  //11 SMCLK

	ADC12CTL2 = ADC12RES_2;  //选择ADC 为12位


}



/****************************************************************************
*函数名-Function:	void Open_ADC12_A(void)
*描述- Description:	打开ADC12_A模块
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Open_ADC12_A(void) //打开ADC12_A模块
{
////////////////////////////////////////////////////////////////////////////
//==**ADC12ON   ADC12_A使能位**=============================//
	ADC12CTL0 |= ADC12ON;   // 1  ADC12_A打开

////////////////////////////////////////////////////////////////////////////
//==**ADC12ENC  ADC12_A转换使能**===========================//
	ADC12CTL0 |= ADC12ENC;	//0  ADC12_A禁止//1  ADC12_A使能 // Enable conversions
	
}


/****************************************************************************
*函数名-Function:	void Close_ADC12_A(void)
*描述- Description:	关闭ADC12_A模块
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Close_ADC12_A(void) //关闭ADC12_A模块
{
////////////////////////////////////////////////////////////////////////////
//==**ADC12ON	ADC12_A使能位**==============================//
	ADC12CTL0 &= ~ADC12ON;  // 0  ADC12_A关闭

////////////////////////////////////////////////////////////////////////////
//==**ADC12ENC   ADC12_A转换使能**==========================//
	ADC12CTL0 &= ~ADC12ENC;	 //0  ADC12_A禁止
	
}



/****************************************************************************
*函数名-Function:	unsigned int Sample_ADC12_A(unsigned char AD_Num)
*描述- Description:	启动ADC_12_A模块，选择指定AD通道，并采样一次AD值。
*输入参数-Input:	AD_Num: 要采样的AD通道
*输出参数-output:	返回指定的采样AD值(16位,只用前12位数据)
*注意事项-Note：	
	▲01) 单通道单次转换模式
	▲02) 输入指定的AD通道，返回时，也要选择指定的AD通道
	▲03)  增加新的AD通道时，要在"两个"switch(AD_Num)中 增加相应的程序
	▲04)  
*****************************************************************************/
unsigned int Sample_ADC12_A(unsigned char AD_Num) //启动ADC_12_A模块，选择指定AD通道，并采样一次AD值。
{
	unsigned int AD_Value = 0;
////////////////////////////////////////////////////////////////////////////
//==**关闭ADC12_A模块**==================================//
	Close_ADC12_A(); // 关闭ADC12_A模块
		//--care--在选择通道之前，一定要先关闭ADC12_A模块，
		//--care--再执行下面的程序，不然，不能同时采样两路AD
////////////////////////////////////////////////////////////////////////////
//==**选择要采样的AD通道**=============================//
	switch(AD_Num) 
	{
		case M_Potentiometer_AdNum:	//P6.6-->A6  Potentiometer电位器使用A/D通道6，端口设为第二功能
			mSelect_Potentiometer_Ad; //配置引脚为"外围模块功能"引脚
			mSetIn_Potentiometer_Ad;   //配置引脚为"输入"
				//选择转换开始地址ADC12MEM6(AD6)
			ADC12CTL1 =ADC12CSTARTADD_6+ ADC12SHP+ADC12SSEL_3; //ADC12CSTARTADD_x	ADC12_A转换开始地址。这些位选择哪个转换存储寄存器用于单次转换或序列转换。对应于ADC12MEM0到ADC12MEM15，CSTARTADDx的值是0到0Fh。
				// ADC12MCTL6模拟通道选择6
			ADC12MCTL6 = ADC12INCH_6+ADC12SREF_0;	 // Vr+=Vref+ and Vr-=AVss
				//ADC12SREFx  参考电压选择//000 VR+ = AVCC，VR- = AVSS	
				//ADC12INCHx  输入通道选择//0110b = A6
			break;	
			
		case M_INA21x_AdNum: //P6.7-->A7  INA21x 使用A/D通道7，端口设为第二功能
			mSelect_INA21x_Ad; //配置引脚为"外围模块功能"引脚
			mSetIn_INA21x_Ad;   //配置引脚为"输入"

				//选择转换开始地址ADC12MEM7(AD7)
			ADC12CTL1 =ADC12CSTARTADD_7+ ADC12SHP+ADC12SSEL_3;	//ADC12CSTARTADD_x	ADC12_A转换开始地址。这些位选择哪个转换存储寄存器用于单次转换或序列转换。对应于ADC12MEM0到ADC12MEM15，CSTARTADDx的值是0到0Fh。

				// ADC12MCTL7模拟通道选择7
			ADC12MCTL7 = ADC12INCH_7+ADC12SREF_0;	 // Vr+=Vref+ and Vr-=AVss
				//ADC12SREFx  参考电压选择//000 VR+ = AVCC，VR- = AVSS	
				//ADC12INCHx  输入通道选择//1101b = A13
			break;	

		case M_NTC_TMP_AdNum: //P6.5-->A5 //"NTC 电阻温度传感器"
			mSelect_NTC_TMP_Ad; //配置引脚为"外围模块功能"引脚
			mSetIn_NTC_TMP_Ad;   //配置引脚为"输入"

				//选择转换开始地址ADC12MEM5(AD5)
			ADC12CTL1 =ADC12CSTARTADD_5+ ADC12SHP+ADC12SSEL_3; //ADC12CSTARTADD_x	ADC12_A转换开始地址。这些位选择哪个转换存储寄存器用于单次转换或序列转换。对应于ADC12MEM0到ADC12MEM15，CSTARTADDx的值是0到0Fh。

				// ADC12MCTL5模拟通道选择5
			ADC12MCTL5 = ADC12INCH_5+ADC12SREF_0;  // Vr+=Vref+ and Vr-=AVss
				//ADC12SREFx  参考电压选择//000 VR+ = AVCC，VR- = AVSS	
				//ADC12INCHx  输入通道选择//1101b = A13
			break;	
			

		/////////////////////////////////////////////////////////////////
		default: break;
	}



////////////////////////////////////////////////////////////////////////////
//==** 打开ADC12_A模块**==================================//
	Open_ADC12_A(); //打开ADC12_A模块




////////////////////////////////////////////////////////////////////////////
//==**开始转换**========================================//
	ADC12CTL0 |= ADC12SC;	 // Start conversion
		//ADC12SC  ADC12_A 转换启动位。软件控制采样转换启动。ADC12SC和ADC12ENC位可以在一条指令中置位。
		//ADC12SC自动复位。//0	没有启动采样转换 //1  启动采样转换




////////////////////////////////////////////////////////////////////////////
//==**等待转换结束，并返回指定的采样AD值**=========//
	switch(AD_Num) 
	{
		case M_Potentiometer_AdNum:	//P6.6-->A6  Potentiometer电位器使用A/D通道6，端口设为第二功能
			while (!(ADC12IFG & ADC12IFG6)); //ADC12IFGx  ADC12MEMx中断标志.当相应的ADC12MEMx载入转换结果时这些位置位。当对相应的ADC12MEMx 进行访问时，这些位复位，或通过软件复位。	//0 没有中断挂起  //1 有中断挂起
			AD_Value = ADC12MEM6;
			break;	

		case M_INA21x_AdNum: //P6.7-->A7  	INA21x电位器使用A/D通道7，端口设为第二功能
			while (!(ADC12IFG & ADC12IFG7)); //ADC12IFGx  ADC12MEMx中断标志.当相应的ADC12MEMx载入转换结果时这些位置位。当对相应的ADC12MEMx 进行访问时，这些位复位，或通过软件复位。	//0 没有中断挂起  //1 有中断挂起
			AD_Value = ADC12MEM7;
			break;	

		case M_NTC_TMP_AdNum: //P6.5-->A5 //"NTC 电阻温度传感器"使用AD5 (第5AD通道)
			while (!(ADC12IFG & ADC12IFG5)); //ADC12IFGx  ADC12MEMx中断标志.当相应的ADC12MEMx载入转换结果时这些位置位。当对相应的ADC12MEMx 进行访问时，这些位复位，或通过软件复位。	//0 没有中断挂起  //1 有中断挂起
			AD_Value = ADC12MEM5;
			break;		
			
////////////////////////////////////////////////////////////////////////////
		default: break;
	}
	
////////////////////////////////////////////////////////////////////////////
//==**采样完，关闭ADC12_A模块**========================//
	Close_ADC12_A(); // 关闭ADC12_A模块

////////////////////////////////////////////////////////////////////////////
//==**采样完，返回AD值**===============================//
	return (AD_Value);

}



/****************************************************************************
*函数名-Function:	void Deal_ADC12_A(unsigned char AD_Num)
*描述- Description:	处理采样结果: 将多次采样值，进行排序，去掉两头，对中间的几个AD值求平均，得到最后的AD值。
*输入参数-Input:	AD_Num: 要采样的AD通道
*输出参数-output:	None
*注意事项-Note：
	▲01) Deal_ADC12_A();  //只能采样1路AD
							不能在同一系统状态下，采样多路AD通道
	▲02) "INA21x 电流分流监控器" 不能调用此API
	▲03) 增加新的AD通道时，要在switch(AD_Num) 增加相应的程序//得到最后的AD值后，转换成相应的物理量
	▲04)  
*****************************************************************************/
void Deal_ADC12_A(unsigned char AD_Num) //处理采样结果: 将多次采样值，进行排序，去掉两头，对中间的几个AD值求平均，得到最后的AD值。
{
  	unsigned char i,k;
  	unsigned int mid;

	pAdBuf[pAdCnt] = Sample_ADC12_A(AD_Num); //数组用于缓存M_AdSampleNum次AD的采样值	 
	pAdCnt ++;	//pAdBuf[]对应的指针  
	
	if(pAdCnt >= M_AdSampleNum)
	{
		pAdCnt = 0;
		for(i = 0; i < M_AdSampleNum-1; i++)	   //对M_AdSampleNum次采样的AD值进行排序,取中间值
		{
			for(k = i+1; k < M_AdSampleNum; k++)	 //排完序后，数组里的数从小到大
			{
				if(pAdBuf[i] > pAdBuf[k])
				{
					mid = pAdBuf[i];
					pAdBuf[i] = pAdBuf[k];	 
					pAdBuf[k] = mid;
				} 
			}
	
		}
			//care若M_AdSampleNum为16次，排序后，取中间4个数求和取平均
		G_LastAdResult = pAdBuf[(M_AdSampleNum/2)-1]+pAdBuf[M_AdSampleNum/2]+pAdBuf[(M_AdSampleNum/2)+1]+pAdBuf[(M_AdSampleNum/2)+2]; 			

		G_LastAdResult = G_LastAdResult/4;

	////////////////////////////////////////////////////////////////////////////
	//==**得到最后的AD值后，转换成相应的物理量**=======//
		switch(AD_Num) 
		{
			case M_Potentiometer_AdNum:	//P6.6-->A6  Potentiometer电位器使用A/D通道6，端口设为第二功能
				G_LastAdResult = (unsigned int)(G_LastAdResult * 0.80855);  //将AD值转成"实际电压值"的1000倍(最大电压3.3对应3300)
				break;	
	
		//	case M_INA21x_AdNum: //P7.5-->A13	INA21x电位器使用A/D通道13，端口设为第二功能
		//		break;		
		
		//	case M_NTC_TMP_AdNum: //P7.4-->A12 //"NTC 电阻温度传感器"使用AD12 (第12 AD通道)
		//		break;	

	        ///////////////////////////////////////////////////////////////////
			default: break;
		}



	}
}



