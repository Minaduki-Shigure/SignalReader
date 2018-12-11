/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 HR202_Humidity.c
* 附属文件-Dependencies:  	 HR202_Humidity.h;  CD405x_Multiplexer.h; NTC_Temperature.h;
								 Timer.h; MyProject_Set_LCD_TFT.h;
								 Hardware_Profile.h; Generic.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■ "HR202_Humidity 电阻型湿度传感器" -驱动程序(外部资源)
	01) HR202 湿敏电阻是采用有机高分子材料的一种新型的湿度
敏感元件，感湿范围宽，长期使用性能稳定。
	02) HR202电阻值随着所测空气湿度的增大而减小。
	03) 常用两种方法:将电阻的变化量转变为计算机接受的信号
	一、是将HR202 置于运放与阻容组成的桥式振荡电路中，所产生
的正弦波电压信号	经整流、直流放大、再A/D 转换为数字信号;
	另一种是将HR202 置于555 振荡电路中，将电阻值的变化转为
与之呈反比的电压频率信号，可直接被计算机所采集。
	04) 当外界湿度变化时,HR202 两端电阻值发生改变，从而改变
定时电路的输出频率。因此只要测出555 的输出频率，并根据
湿度与输出频率的关系，即可求得环境的湿度。
	05)    06)	
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


	//具体项目: LCD_TFT液晶显示部份(包括所有的液晶内容) -头文件
#include "MyProject_Set_LCD_TFT.h"  


#include "msp430f6638.h"   // "处理器"头文件: 内部寄存相关定义等(处理器内部资源) 

#include "Timer.h"     //"定时器" -驱动程序 -头文件(处理器内部资源)


#include "NTC_Temperature.h"  //"NTC 电阻温度传感器" -驱动程序(外部资源)-头文件

#include "CD405x_Multiplexer.h"   //"CD405x_Multiplexer多路选择模拟开关"  -驱动程序(外部资源)-头文件

#include "HR202_Humidity.h"   //"HR202_Humidity 电阻型湿度传感器" -驱动程序(外部资源)-头文件



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
union FLAGBIT16 HR202_Humidity_FlagBits; //"HR202_Humidity 电阻型湿度传感器"相关标志位变量

unsigned char G_HR202_Humidity = 0;  //存最后得到的"湿度值"


////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////

unsigned long G_HR202_Frequency = 0;   //"湿度值"相应频率值(1s内的脉冲次数)

unsigned int  G_HR202_FrequencyStart = 0;  //"湿度值"脉冲第1上升沿(测相应频率)
unsigned int  G_HR202_FrequencyEnd = 0;   //"湿度值"脉冲第2上升沿(测相应频率)
unsigned char G_HR202_FrequencyCnt = 0;  //2:表示第1上升沿,  3:表示第2上升沿,





const unsigned long HR_202[13][15] = {
{0       ,0       ,6400000,2900000,1400000,700000,370000,190000,105000,62000,38000,23000,15500,10500,7100},
{0       ,10000000,4600000,2100000,1000000,500000,260000,140000,80000 ,48000,30000,18000,12000,8200 ,5300},
{0       ,7000000 ,3200000,1500000,750000 ,380000,200000,110000,62000 ,37000,24000,15000,10000,6800 ,4700},
{10000000,5000000 ,2300000,1100000,540000 ,280000,150000,84000 ,50000 ,30000,19000,12000,8000 ,5500 ,4000},
{6700000 ,3400000 ,1750000,850000 ,420000 ,210000,115000,64000 ,39000 ,24000,15500,10000,7000 ,4800 ,3300},
{5000000 ,2600000 ,1300000,630000 ,310000 ,160000,87000 ,49000 ,31000 ,19500,13000,8400 ,5700 ,4000 ,2800},
{3900000 ,1900000 ,970000 ,460000 ,235000 ,125000,69000 ,39000 ,25000 ,16000,10500,7200 ,5000 ,3500 ,2500},
{3000000 ,1500000 ,740000 ,380000 ,190000 ,100000,56000 ,33000 ,20000 ,13000,9000 ,6200 ,4300 ,3100 ,2200},
{2400000 ,1100000 ,570000 ,280000 ,140000 ,78000 ,45000 ,27000 ,17500 ,11500,8000 ,5600 ,3900 ,2800 ,2000},
{1750000 ,880000  ,420000 ,210000 ,110000 ,64000 ,38000 ,24000 ,15000 ,10000,7000 ,4900 ,3400 ,2400 ,1800},
{1450000 ,700000  ,340000 ,170000 ,88000  ,50000 ,31000 ,19500 ,13000 ,8600 ,6000 ,4200 ,3000 ,2100 ,1550},
{1150000 ,560000  ,270000 ,130000 ,70000  ,41000 ,25000 ,17000 ,11000 ,7600 ,5400 ,3800 ,2700 ,1900 ,1400},
{970000  ,450000  ,215000 ,150000 ,57000  ,34000 ,21000 ,14000 ,9400  ,6800 ,4800 ,3400 ,2500 ,1800 ,1300}
};




/****************************************************************************
*函数名-Function:	void HR202_Humidity_Initial(void)
*描述- Description:	初始化设置:  "HR202_Humidity 电阻型湿度传感器"
		1) CD405x切到"Humidity  湿度
		2) 配置IO:  CCR3的输入口
		3) 配置:  定时器A0初始化设置(使用 CCR3)
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：
	▲01) CCP1 每1秒中断一次
	▲02) CCP3 每57.2us=17.48K Hz中断一次(对应C29=0.1)
	▲03)    ▲04)  
*****************************************************************************/
void HR202_Humidity_Initial(void) //初始化设置:  "HR202_Humidity 电阻型湿度传感器"
{
////////////////////////////////////////////////////////////////////////////
//==**CD405x切到"Humidity  湿度"**============================//
	CD405x_SelectChannel(CD405x_Humidity);//CD405x切到"Humidity  湿度"


////////////////////////////////////////////////////////////////////////////
//==**配置:  定时器A0初始化设置(使用CCR1, CCR3)**=========//
//care--CCR1用于定时1秒，在1秒内，CCR3捕获HR202与555输出的频率
//	Timer0_Initial_HR202_Humidity(); //定时器A0初始化设置(用于"HR202_Humidity 电阻型湿度传感器")


////////////////////////////////////////////////////////////////////////////
//==**初使化: 频率计数器值**==================================//
	G_HR202_Frequency = 0;
}


/****************************************************************************
*函数名-Function:	void Sample_HR202_Frequency(void)
*描述- Description:	在中断,采样"湿度值"相应频率值
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：
	▲01) 在中断TIMER0_A1_ISR()调用
	▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Sample_HR202_Frequency(void) //在中断,采样"湿度值"相应频率值
{
	G_HR202_FrequencyCnt++;
	if(G_HR202_FrequencyCnt >=4) G_HR202_FrequencyCnt = 1;

	if(G_HR202_FrequencyCnt == 2) 
	{
		G_HR202_FrequencyStart = TA1CCR2;
	}
	else if(G_HR202_FrequencyCnt == 3) 
	{
		G_HR202_FrequencyEnd = TA1CCR2;
		
	////////////////////////////////////////////////////////////////////////////
	//==**配置:  " TA0CTL (Timer_A1控制寄存器)"**==================//
		
		TA1CTL &= ~(MC1 + MC0); //让Timer_A1处于停止模式
		TA1CCTL2 &= ~ CCIE;     //禁止CCR2 中断
		
		F_EnRead_Humidity = YES;
	}
		

}




/****************************************************************************
*函数名-Function:	unsigned char ConverseToHumidity(unsigned long R, int temperature)
*描述- Description:	转换"HR202_Humidity 电阻型湿度传感器" 频率值为实际"湿度值"
*输入参数-Input:	R:   temperature: 当前实时温度值
*输出参数-output:	实时湿度值
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
unsigned char ConverseToHumidity(unsigned long R, int temperature)
{
	signed char row,column,limit;
	unsigned char  res;
	
	for(row = 0;row <= 12; row++)   //得到row的值
	{
		if(temperature<=(25*(2*row+1)))
			break;
	}

	if(row == 13)
		row =12;

	
	if(row == 0)
		limit = 2;
	else if(row == 1)
		limit = 1;
	else
		limit = 0;

	
	for(column = 14; column >= limit; column--)  //得到column的值
	{
		if(R <= HR_202[row][column])
			break;
	}

	res = (column + 4) * 5;
	
	if(column == 14)
		res += (HR_202[row][column]-R)*10/(HR_202[row][column-1] - HR_202[row][column]);
	else if(column>=limit)
		res += (HR_202[row][column]-R)*5/(HR_202[row][column] - HR_202[row][column+1]);
	else
	{
		res = (column+5)*5;
		res -= (R - HR_202[row][column+1])*5/(HR_202[row][column+1] - HR_202[row][column+2]);

		if(res < 10)	//如果"湿度值< 10"，则只返回10
			res = 10;
	}

	
	if(res > 99)   //如果"湿度值>99"，则只返回99
		res = 99;
	
	return (res);
}



/****************************************************************************
*函数名-Function:	void Deal_HR202_Humidity(void)
*描述- Description:	处理 "HR202_Humidity 电阻型湿度传感器"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    ▲02)    ▲03)    ▲04)  
*****************************************************************************/
void Deal_HR202_Humidity(void) //处理 "HR202_Humidity 电阻型湿度传感器"
{
	long R;

	if(F_250ms_Sample_Humidity)  //250ms读取一次湿度值"相应频率值
	{
		F_250ms_Sample_Humidity = 0;

		if(!F_EnRead_Humidity)
		{
			Timer1_Initial_HR202_Humidity(); //定时器A1初始化设置(用于"HR202_Humidity 电阻型湿度传感器")
			G_HR202_FrequencyCnt = 0;
		}
	}

	if(F_EnRead_Humidity)
	{
		F_EnRead_Humidity = 0;
		G_HR202_Frequency = (unsigned long)(4000000/(G_HR202_FrequencyEnd - G_HR202_FrequencyStart));
	}

	if(F_500ms_Reflash_Humidity)
	{
		F_500ms_Reflash_Humidity = 0;

			//将CCR3 捕获到的频率值hrFrequency, 进行相应的处理
		R = (720000000/G_HR202_Frequency) - 25000;   //???? care 没看明白
//			R = (720000/G_HR202_Frequency) - 25000;	 //???? care 没看明白

		G_HR202_Humidity = ConverseToHumidity(R,G_NTC_Temperature);

		G_HR202_Humidity +=  20;  //后面的立即数，为人为加上的
		if(G_HR202_Humidity >= 100) G_HR202_Humidity = 100;
			// 处理显示部分"彩屏LCD_TFT"
		Disp_HR202_Humidity(G_HR202_Humidity); //显示: "HR202_Humidity " 湿度
	}
}





