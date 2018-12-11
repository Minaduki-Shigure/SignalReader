/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 UART_IrDA.c
* 附属文件-Dependencies:  	 UART.h;  msp430f6638.h;
                                                        Hardware_Profile.h; Generic.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■ "IrDA_UART  红外串口通信" -驱动程序(外部资源)
	01) IrDA 红外数据组织 (Infrared Data Association)
	02) 红外线是波长在750nm至1mm之间的电磁波，它的频率高于
微波而低于可见光，是一种人的眼睛看不到的光线。 
	03)红外通讯一般采用红外波段内的近红外线，波长在0.75um
至25um之间。
	04) 为了保证不同厂商的红外产品能够获得最佳的通讯效果，
红外通讯协议将红外数据通讯所采用的光波波长的范围限定
在850nm至900nm之内。
	05) 由于红外线的波长较短，对障碍物的衍射能力差，所以
更适合应用在需要短距离无线通讯的场合，进行点对点的
直线数据传输。
	06)	IrDA标准包括三个基本的协议和规范：红外物理层连接
规范、红外连接访问协议和红外连接管理协议。IrPHY规范制定
了红外通信硬件设计上的目标和要求；IrLAP和 IrLMP为两个软件层，
负责对连接进行设置，管理和维护。在 IrLAP和 IrLMP基础上，针对
一些特定的红外通信应用领域，IrDA还陆续发布了一些更高级别
的红外协议，如 TinyTP，IrOBEX，IrCOMM，IrLAN，IrTran-P等。
	07) 红外线传输的种类目前主要有以下几种，它们都属于 IrDA 的物理层：
		(1)  默认传输模式 IrDA-SIR（Serial Infrared，串行红外协
	IrDA-SIR，即 IrDA1.0 协议，是最早的也是最基本的传输模式。
它基于 UART，简称 SIR(Serial Infrared，串行红外协议)，提供短程的红外
异步串行传输，采用 3/16 ENDEC 编/解码机制[1]， 使用一个启动位、 
八个数据位和一个停止位。由于受到 UART 通讯速率的限制，
SIR 的最高通讯速率只有 115200 bps，即计算机串行端口的最高速率。

		(2)  快速 IrDA-FIR  （Fast Infrared，快速红外协议）
	IrDA-FIR，即 IrDA1.1 协议，是 IrDA 的高速扩展。与 SIR 相比，由于 FIR 
不再依托 UART，其最高通讯速率有了质的飞跃，可达 4Mbps。FIR 采用
了全新的 4PPM 调制解调，即通过分析脉冲的相位来辨别所传输的
数据信息，其通讯原理与 SIR 截然不同，但由于 FIR在 115.2Kbps以下速率
时依旧采用 SIR 的编码/解码过程，所以它仍可与支持 IrDA-SIR 的低速设
备通讯。IrDA-FIR 设备除支持 9.6K/19.2K/38.4K/57.6K/115.2Kbps 几种速度模式外，
还支持 576 Kbps/1.152M bps/4Mbps 的高速率，但只有在通讯对方也支持 FIR 时，
通讯速率才可提升到更高水平。采用该标准的设备通常有效通信
距离为 1~5 米，同时两个设备的红外线接收发射口也需在一定的角度
范围内相对应，通常是在 30°夹角范围内。 

		(3)  超高速 IrDA  －VFIR（Very Fast Infrared，超高速红外协议）  
	IrDA-VFIR，即 IrDA1.2 协议，超速 IrDA  可提供 16Mbps 高速的传输速度，
接收角度也从传统的 30 度扩展到 120 度，而且功耗更低。它不但
支持 FIR 和 VFIR，也可以同 SIR设备进行数据通讯。  

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



#include "msp430f6638.h"   // "处理器"头文件: 内部寄存相关定义等(处理器内部资源) 

#include "UART.h"   //"UART 通用异步接收/发送装置" -驱动程序(内部资源)-头文件





////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned char G_RxData_IrDA = 0xFF;  //缓存 "IrDA_UART  红外串口通信"接收到的数据



////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////





/****************************************************************************
*函数名-Function:	void Deal_IrDA_UART(void)
*描述- Description:		处理 "IrDA_UART  红外串口通信"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note： ▲01)	▲02) 	▲03) 	▲04)  
*****************************************************************************/
void Deal_IrDA_UART(void)   //处理 "IrDA_UART  红外串口通信"
{
	Initial_IrDA_UART();  //初始化设置:  "IrDA_UART  红外串口通信"

	Send_OneByte_UART_A('1'); //UART_A 发送一个字节数据--"UART_A 通用异步接收/发送装置"

	
	WaitingDelayMs(50);  //延时50ms(因为，UART与其他模块引脚复用，不延时的话，有些数据就发不出去)


	G_RxData_IrDA = UCA1RXBUF;  //采用查询的方式,采样红外接收到的数据
	
	UCA1IFG &= ~UCRXIFG; //请接收中断标志位
	
}





