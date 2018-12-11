/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 MatrixKey.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■"矩阵按键" -驱动程序(外部资源)-头文件
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


#ifndef  __MatrixKey_H 
#define  __MatrixKey_H 


/****************************************************************************
       处理器IO口使用宏定义，统一在Hardware_Profile.h 定义    

////////////////////////////////////////////////////////////////////////////
//==**适用于**PIC24F 的单片机**==========================//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//==**蜂鸣器*IO口使用宏定义**==========================//

#define Buzz_TRIS	   TRISBbits.TRISB11 
#define Buzz_IO		   LATBbits.LATB11		 //蜂鸣器输出IO口


////////////////////////////////////////////////////////////////////////////
//==**矩阵按键*IO口使用宏定义**=======================//

#define Y1_MatrixKey_IO   LATBbits.LATB12  //输出//矩阵按键第1列
#define Y1_MatrixKey_TRIS TRISBbits.TRISB12 


#define Y2_MatrixKey_IO   LATBbits.LATB8  //输出//矩阵按键第2列
#define Y2_MatrixKey_TRIS TRISBbits.TRISB8 

#define Y3_MatrixKey_IO   LATBbits.LATB9  //输出//矩阵按键第3列
#define Y3_MatrixKey_TRIS TRISBbits.TRISB9

#define MatrixKey_PORT    PORTB
#define MatrixKey_LAT     LATB


#define X1_MatrixKey_PT   PORTBbits.PORTB0  //输入//矩阵按键第1行
#define X1_MatrixKey_TRIS TRISBbits.TRISB0

#define X2_MatrixKey_PT   PORTBbits.PORTB1  //输入//矩阵按键第2行
#define X2_MatrixKey_TRIS TRISBbits.TRISB1

#define X3_MatrixKey_PT   PORTBbits.PORTB2  //输入//矩阵按键第3行
#define X3_MatrixKey_TRIS TRISBbits.TRISB2

#define X4_MatrixKey_PT   PORTBbits.PORTB3  //输入//矩阵按键第4行
#define X4_MatrixKey_TRIS TRISBbits.TRISB3

#define X5_MatrixKey_PT   PORTBbits.PORTB13  //输入//矩阵按键第5行
#define X5_MatrixKey_TRIS TRISBbits.TRISB13

////////////////////////////////////////////////////////////////////////////
//==**适用于**PIC18F 或PIC16F系列的单片机**===============//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//==**蜂鸣器*IO口使用宏定义**==========================//

#define Buzz_TRIS        TRISA4
#define Buzz_IO          RA4       //蜂鸣器输出IO口


////////////////////////////////////////////////////////////////////////////
//==**矩阵按键*IO口使用宏定义**=======================//

#define Y1_MatrixKey_IO   LATB0  //输出//矩阵按键第1列
#define Y1_MatrixKey_TRIS 0TRISB0 


#define Y2_MatrixKey_IO  LATB1  //输出//矩阵按键第2列
#define Y2_MatrixKey_TRIS TRISB1

#define Y3_MatrixKey_IO   LATB2  //输出//矩阵按键第3列
#define Y3_MatrixKey_TRIS TRISB2

#define Y3_MatrixKey_IO   LATB3  //输出//矩阵按键第4列
#define Y3_MatrixKey_TRIS TRISB3

#define MatrixKey_PORT    PORTB
#define MatrixKey_LAT     LATB


#define X1_MatrixKey_PT   PORTB4  //输入//矩阵按键第1行
#define X1_MatrixKey_TRIS TRISB4

#define X2_MatrixKey_PT  PORTB5  //输入//矩阵按键第2行
#define X2_MatrixKey_TRIS TRISB5

#define X3_MatrixKey_PT   PORTB6  //输入//矩阵按键第3行
#define X3_MatrixKey_TRIS TRISB6

#define X4_MatrixKey_PT   PORTB7 //输入//矩阵按键第4行
#define X4_MatrixKey_TRIS TRISB7

***********************************************************************************/




////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"宏定义**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////

#define M_MatrixKeyDelayTime (2)   //用于调整按键灵敏度(即消抖时间)，以5ms为时基

#define M_MatrixKeyUsed      (0xFF)   //用于定义接8个按键，若定义为只使用第1,2个键时，则令 M_MatrixKeyUsed＝0x03 

#define M_NullMatrixKey      (0xFF)//定义按键为无效键


////////////////////////////////////////////////////////////////////////////
//--**"矩阵按键值"宏定义**---------------------------------------//
////////////////////////////////////////////////////////////////////////////

#define MatrixKey_0      (0)    //定义"数字0键"
#define MatrixKey_1      (1)    //定义"数字1键"
#define MatrixKey_2      (2)    //定义"数字2键"
#define MatrixKey_3      (3)    //定义"数字3键"
#define MatrixKey_4      (4)    //定义"数字4键"
#define MatrixKey_5      (5)    //定义"数字5键"
#define MatrixKey_6      (6)    //定义"数字6键"
#define MatrixKey_7      (7)    //定义"数字7键"
#define MatrixKey_8      (8)    //定义"数字8键"
#define MatrixKey_9      (9)    //定义"数字9键"
#define MatrixKey_A      (0x0A) //定义"数字A键"
#define MatrixKey_B      (0x0B) //定义"数字B键"
#define MatrixKey_C      (0x0C) //定义"数字C键"
#define MatrixKey_D      (0x0D) //定义"数字D键"
#define MatrixKey_E      (0x0E) //定义"数字E键"
#define MatrixKey_F      (0x0F) //定义"数字F键"

#define MatrixKey_AC     (0x13) //定义"AC键"
#define MatrixKey_Plus   (0x12) //定义"+ 键"
#define MatrixKey_Minus  (0x11) //定义"-键"
#define MatrixKey_Equal  (0x10) //定义"=键"

#define MatrixKey_Return (0x13) //定义"返回键"
#define MatrixKey_OK     (0x10) //定义"确定键"





/*****
////////////////////////////////////////////////////////////////////////////
//--**"设置时""矩阵按键值"宏定义**----------------------------//
////////////////////////////////////////////////////////////////////////////

#define MatrixKey_Up       (0xFF)   //定义"上翻键"   
#define MatrixKey_Down   (0xFF)   //定义"下翻键"
#define MatrixKey_Left      (0x0A)   //定义"左键"
#define MatrixKey_Right    (0x0B)   //定义"右键"


#define MatrixKey_Return   (0x0C)   //定义"返回键"
#define MatrixKey_Delete   (0x0C)   //定义"删除键"

#define MatrixKey_Menu    (0x0D)   //定义"菜单键"
#define MatrixKey_Ok        (0x0E)   //定义"确定键"


#define MatrixKey_Modify   (0x0D)   //定义"修改键"

#define MatrixKey_Option   (0xFF)   //定义"选择键"

////////////////////////////////////////////////////////////////////////////
//--**"控制工作时""矩阵按键值"宏定义**----------------------//
////////////////////////////////////////////////////////////////////////////

#define MatrixKey_Start     (0xFF)   //定义"运行键"值

#define MatrixKey_Stop     (0xFF)   //定义"停止键"值

#define MatrixKey_Test      (0xFF)   //定义"测试键"值

****/




////////////////////////////////////////////////////////////////////////////
//==**项目"专用"宏定义**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
extern union FLAGBIT16 MatrixKeyFlagBits; //矩阵按键用到的标志位定义
#define  G_MatrixKeyFlagBits MatrixKeyFlagBits.FLAG16  
//#define	 F_MatrixScanKey   MatrixKeyFlagBits.b.f0    
#define  F_MatrixKeyHave     MatrixKeyFlagBits.b.f1
#define  F_MatrixKeyRead	 MatrixKeyFlagBits.b.f2	
#define  F_MatrixKeyNull     MatrixKeyFlagBits.b.f3	
#define  F_Ok_LongMatrixKey	 MatrixKeyFlagBits.b.f4   //"确定键"长按标志位   
//#define   F_	MatrixKeyFlagBits.b.f5	
//#define  F_	MatrixKeyFlagBits.b.f6	
//#define  F_	MatrixKeyFlagBits.b.f7    
//#define   F_	MatrixKeyFlagBits.b.f8      
//#define   F_	MatrixKeyFlagBits.b.f9     
//#define   F_	MatrixKeyFlagBits.b.f10    
//#define   F_	MatrixKeyFlagBits.b.f11      
//#define   F_	MatrixKeyFlagBits.b.f12      
//#define   F_	MatrixKeyFlagBits.b.f13      
//#define   F_	MatrixKeyFlagBits.b.f14     
//#define   F_	MatrixKeyFlagBits.b.f15      
     

extern unsigned char G_MatrixKeyValue;  //存矩阵按键解码后的按键值 (对于一般常用的按键)


extern unsigned char G_MatrixKeyBuf[32];  //缓存输入的多个按键值
extern unsigned char G_MatrixKeyCnt;  //按键缓存数组指针

extern unsigned char G_TotalKeyNum;  //输入的数字按键总个数
extern unsigned char G_DecimalPoint;  //输入的数字按键的小数点位置(用于光标显示)
extern unsigned char G_KeyPlace_Row;    //(行)按键设置参数位置(光标)开始位置
extern unsigned char G_KeyPlace_Column; //(列)按键设置参数位置(光标)开始位置

extern unsigned int  G_KeyValue_Addr;  //采集完的所有按键存到EEPROM/Flash指定地址




////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
//==**"函数"宏定义**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"函数声明**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////

//extern unsigned char Sample_MatrixKey(void); //采样矩阵键盘扫描
//extern void Decode_MatrixKey(void);  //矩阵键盘处理



////////////////////////////////////////////////////////////////////////////
//==**"外部" API 函数声明**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////

extern void Scan_MatrixKey(void);  //"矩阵键盘"扫描，5ms扫描一次按键(中断里)	

//extern void Decode_MatrixKey(void); //矩阵键盘处理


extern unsigned char Detect_MatrixKey(void);  //检测有没有按键,并返回按键值(对于一般常用的按键)

extern unsigned char Detect_Press_MatrixKey(void); //存矩阵按键解码后的按键值(按下执行，松开停止)

extern unsigned char Detect_Long_MatrixKey(unsigned char SecondNum);//(长按X秒有效)检测有没有长按的按键,并返回按键值



extern unsigned char Detect_MatrixKey_0(void);//检测"0" 矩阵按键 有没有按下
extern unsigned char Detect_MatrixKey_1(void);//检测"1" 矩阵按键 有没有按下
extern unsigned char Detect_MatrixKey_2(void);//检测"2" 矩阵按键 有没有按下
extern unsigned char Detect_MatrixKey_3(void);//检测"3" 矩阵按键 有没有按下
extern unsigned char Detect_MatrixKey_4(void);//检测"4" 矩阵按键 有没有按下
extern unsigned char Detect_MatrixKey_5(void);//检测"5" 矩阵按键 有没有按下
extern unsigned char Detect_MatrixKey_6(void);//检测"6" 矩阵按键 有没有按下
extern unsigned char Detect_MatrixKey_7(void);//检测"7" 矩阵按键 有没有按下
extern unsigned char Detect_MatrixKey_8(void);//检测"8" 矩阵按键 有没有按下
extern unsigned char Detect_MatrixKey_9(void);//检测"9" 矩阵按键 有没有按下

extern unsigned char Detect_MatrixKey_A(void);//检测"A" 矩阵按键 有没有按下
extern unsigned char Detect_MatrixKey_B(void);//检测"B" 矩阵按键 有没有按下
extern unsigned char Detect_MatrixKey_C(void);//检测"C" 矩阵按键 有没有按下
extern unsigned char Detect_MatrixKey_D(void);//检测"D" 矩阵按键 有没有按下
extern unsigned char Detect_MatrixKey_E(void);//检测"E" 矩阵按键 有没有按下
extern unsigned char Detect_MatrixKey_F(void);//检测"F" 矩阵按键 有没有按下

extern unsigned char Detect_MatrixKey_AC(void);//检测"AC" 矩阵按键 有没有按下
extern unsigned char Detect_MatrixKey_Plus(void);//检测"+" 矩阵按键 有没有按下
extern unsigned char Detect_MatrixKey_Minus(void);//检测"-" 矩阵按键 有没有按下
extern unsigned char Detect_MatrixKey_Equal(void);//检测"=" 矩阵按键 有没有按下











#endif   /* __MatrixKey_H  */





