/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 INA21x.c
* 附属文件-Dependencies:  	 INA21x.h; ADC.h; MyProject_Set_LCD_TFT.h; 
                                                   Hardware_Profile.h; Generic.h
* 文件描述-File Description:	 ( 源程序-Source File) 
	■  "INA21x 电流分流监控器" -驱动程序(外部资源)
	01) Directional Zer?-Drift Series CURRENT-SHUNT MONITOR
INA210 (电压输出、高侧或者低侧测量，双向零漂移系列电流分流监控器)
	02) INA210，INA211，INA212，INA213，和INA214 是电压输出电流并联
监控器，此监控器能够感测共模电压上-0.3V 至+ 26V 的压降，与
电源电压无关。提供五 个固定增益：50V/V，100V/V，200V/V，500V/V，
或1000V/V。零漂移架构的低偏移使得在整个分流上能够感测的
最大压降低至10mV 满量程。    
	03) 宽共模范围：-0.3V 至26V ;      静态电流：100μA（最大值）  
	04) 偏移电压：±35μV（最大值，INA210）
	05) 增益选择：INA210：200V/V;     INA211: 500V/V;  INA212: 1000V/V;  INA213: 50V/V;  INA214: 100V/V
	06)	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 注意事项-Attention : 	
	▲01) 输入引脚，+IN 和-IN，应该被连接到尽可能靠近分流
电阻器的位置以大大减少任何与分流电阻串联的电阻。
	▲02) 需要电源旁路电容器来实现稳定性。具有嘈杂或者
高阻抗电源的应用也许需要额外耦合电容器来抑制电源噪声。
将旁路电容器连接到接近器件引脚的位置。
	▲03) INA210-INA214 的输入电路能够准确地测量超过其自身电源
电压，V+，的电压。例如，V+ 电源可以为5V，而负载电源电压
可以高至+26V。然而，OUT（输出）端子的输出电压范围受到
电源引脚上电压的限制。请注意，无论器件加电与否，INA210
-INA214 的输入引脚能够耐受整个-0.3V 至+26V 的电压。
	▲04)   ▲05)    ▲06)     
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


#include "ADC.h"   //"ADC"模数转换模块 -驱动程序-头文件(处理器内部资源) 

#include "INA21x.h"  // "INA21x 电流分流监控器" -驱动程序(外部资源)-头文件 


////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
union FLAGBIT16 INA21x_FlagBits;	//"INA21x 电流分流监控器" 相关标志位变量

unsigned int G_INA21x_AdResult = 0; //把M_INA21x_AdSampleNum次AD采样值从小到大排序后，求得的最后AD计算值


////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned int pINA21x_AdBuf[M_INA21x_AdSampleNum];  //数组用于缓存M_INA21x_AdSampleNum次AD的采样值   
unsigned char pINA21x_AdCnt = 0;  //pINA21x_AdBuf[]对应的指针  




/****************************************************************************
*函数名-Function:	void Sample_INA21x_AD(void)
*描述- Description:		多次采样"INA21x 电流分流监控器"AD
	1) 多次采样值，2) 进行排序，3) 去掉两头，
	4) 对中间的几个AD值求平均，得到最后的AD值。
	5) 将最后的AD值，转换成实际物理量值
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：
	▲01)	▲02) 	▲03) 	▲04)  
*****************************************************************************/
void Sample_INA21x_AD(void) //多次采样"INA21x 电流分流监控器"AD
{
  	unsigned char i,k;
  	unsigned int mid;
					//"INA21x 电流分流监控器"使用AD7 (第7  AD通道)
	pINA21x_AdBuf[pINA21x_AdCnt] = Sample_ADC12_A(M_INA21x_AdNum); //数组用于缓存M_INA21x_AdSampleNum次AD的采样值	 
	pINA21x_AdCnt ++;	//pINA21x_AdBuf[]对应的指针  
	
	if(pINA21x_AdCnt >= M_INA21x_AdSampleNum)
	{
		pINA21x_AdCnt = 0;
		
		for(i = 0; i < M_INA21x_AdSampleNum-1; i++)	   //对M_INA21x_AdSampleNum次采样的AD值进行排序,取中间值
		{
			for(k = i+1; k < M_INA21x_AdSampleNum; k++)	 //排完序后，数组里的数从小到大
			{
				if(pINA21x_AdBuf[i] > pINA21x_AdBuf[k])
				{
					mid = pINA21x_AdBuf[i];
					pINA21x_AdBuf[i] = pINA21x_AdBuf[k];	 
					pINA21x_AdBuf[k] = mid;
				} 
			}
	
		}
			//care若M_INA21x_AdSampleNum为16次，排序后，取中间4个数求和取平均
		G_INA21x_AdResult = pINA21x_AdBuf[(M_INA21x_AdSampleNum/2)-1]+pINA21x_AdBuf[M_INA21x_AdSampleNum/2]+pINA21x_AdBuf[(M_INA21x_AdSampleNum/2)+1]+pINA21x_AdBuf[(M_INA21x_AdSampleNum/2)+2]; 			

		G_INA21x_AdResult = G_INA21x_AdResult/4;

////////////////////////////////////////////////////////////////////////////
//==**得到最后的AD值后，转换成相应的物理量**=======//
		//G_INA21x_AdResult = (unsigned int)(G_INA21x_AdResult * 0.1542); //将AD值转化为"实际电流量"
		G_INA21x_AdResult = (unsigned int)(G_INA21x_AdResult * 0.161172); //将AD值转化为"实际电流量"	
			//计算过程:测得的AD电压=(3300/4096)*AD值(mV) =(I*0.1)*50  ==>I=AD*0.161172 
	}
}


/****************************************************************************
*函数名-Function:	void Deal_INA21x(void)
*描述- Description:		处理 "INA21x 电流分流监控器": AD采样，AD数据处理，显示处理
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：
	▲01)	▲02) 	▲03) 	▲04)  
*****************************************************************************/
void Deal_INA21x(void)  //处理 "INA21x 电流分流监控器": AD采样，AD数据处理，显示处理
{
////////////////////////////////////////////////////////////////////////////
//==**系统每10ms 采样一次"监测电流值"**================//
	Sample_INA21x_AD();  //多次采样"INA21x 电流分流监控器"AD
	
////////////////////////////////////////////////////////////////////////////
//==**系统每500ms 读取"实时监测电流值"**===============//
	if(F_500ms_Reflash_INA21x)
	{
		F_500ms_Reflash_INA21x = 0;
		
		Disp_INA21x_CurrentValue(G_INA21x_AdResult); //显示: INA21x 实时"监测电流值"
	}
	
}

