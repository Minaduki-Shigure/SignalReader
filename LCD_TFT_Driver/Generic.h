/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 Generic.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■ 常用程序编程规范、函数集 -头文件-Generic Type Definitions
	01) 常用变量定义集
	02) 常用宏定义集    
	03) 常用功能函数集 
	04)    05)    06)	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 注意事项-Attention : 	
	▲01) 编程格式和程序分类，还没有整理
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


#ifndef __Generic_H
#define __Generic_H


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"宏定义**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**项目"专用"宏定义**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
extern unsigned char ASCII_Table[21];  //0--F字符 和  常用字符 显示表

////////////////////////////////////////////////////////////////////////////
//==**Temp*全局变量**===================================//
//--**调试用的中间变量，最后可以去掉的**---------------//
//extern unsigned char G_TempBuf[50];
extern unsigned char G_TempChar;  //测试临时用的"字节"变量
//extern unsigned int G_TempWord;   //测试临时用的"单字"变量
//extern unsigned long G_TempDword; //测试临时用的"双字"变量

////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////


/*  UnComment the following macro to use AND_OR mask based setting, Comment it to use AND based macros */
//#define USE_AND_OR

#define PUBLIC
#define PROTECTED
#define PRIVATE                 static
//#define _ENUM 




#include "stdint.h" //定义了一些整数类型(标准C库的头文件)
	//  例:uint8_t; uint16_t 都在"stdint.h"头文件定义
	// 按照posix标准，一般整型对应的*_t类型


//#define uchar unsigned char
//#define uint unsigned int


typedef uint32_t  u32;	 //unsigned long
typedef uint16_t  u16;  //unsigned int
typedef uint8_t   u8;   //unsigned char 
//typedef signed char int8_t;
//typedef unsigned char uint8_t;




//**********************
//软件提取库
//***********************
/* 兼容一般程序员的常用写法 */
typedef unsigned char	uchar;
typedef unsigned int	uint;
typedef unsigned long	ulong;
typedef signed 	char schar;
typedef signed 	int	sint;
typedef signed 	long slong;

/* 为方便移植，建议使用下面写法 */
typedef unsigned char	bool;
typedef unsigned char	uint8;
typedef unsigned int	uint16;
typedef unsigned long   uint32;
typedef signed  char	sint8;
typedef signed	int		sint16;
typedef signed	long	sint32;
typedef signed  char	int8;
typedef signed  int		int16;
typedef signed  long	int32;

//*************************************
//硬件提取库
//*************************************
/* hard configs */
#ifndef flash
	#define flash	const
#endif

#ifndef code
	#define code	const
#endif


union FLAGBIT
{ uint8 FLAG;
  struct
  {   
   unsigned f0:1;		unsigned f1:1;
   unsigned f2:1;		unsigned f3:1;
   unsigned f4:1;		unsigned f5:1;
   unsigned f6:1;		unsigned f7:1;
  }b;
 };


union FLAGBIT16
{ 
	unsigned int FLAG16;
	unsigned char FLAG8[2];
	struct
	{   
		unsigned f0:1;		unsigned f1:1;
		unsigned f2:1;		unsigned f3:1;
		unsigned f4:1;		unsigned f5:1;
		unsigned f6:1;		unsigned f7:1;
		unsigned f8:1;		unsigned f9:1;
		unsigned f10:1;		unsigned f11:1;
		unsigned f12:1;		unsigned f13:1;
		unsigned f14:1;		unsigned f15:1;     
	}b;
}; 






/* 如果你手头上的RAM实在很紧，不如尝试下面的define～ */
//#define _CALLOC(a)		( (a *)calloc(n,sizeof(a)) )
//#define _MALLOC(a)		( (a *)malloc(sizeof(a)) )
//#define _MIN(a,b)			( (a) < (b) ? (a) : (b) )
//#define _MAX(a,b)			( (a) > (b) ? (a) : (b) )
//#define _EXCHANGE(a,b)	{ int t; t=a; a=b; b=t; }
//#define _TOLOWER(c)		( (c)+32 )
//#define _TOUPPER(c)		( (c)-32 )

//#ifndef BIT
//#define BIT(x)	( 1<<(x) )
//#endif

/*--------------------------------------------------------------------
函数全称：数据拆字
函数功能：
注意事项：D<=999999,C<=6
提示说明：调用speaData(12,2)，得到dataElem[0]=2，dataElem[1]=1
输    入：
返    回：无
--------------------------------------------------------------------*/
/*uint8 dataElem[6];
void speaData(uint32 dat,sint8 len)
{
    uint8 i;
    uint32 j,y;
    for(i=0,j=1;i<len;i++)
    {
        y=dat/j;
        dataElem[i]=y%10;
        j*=10;
    }
}*/


/*************************************************************
*函数名 Function Name: ChangeDecIntoHex(dec)
*函数功能 Description: 十进制强制转换为十六进制(把十进制转成BCD码)
*输入参数 Parameters : 十进制数
*输出参数Return Value: None
*注意事项  Attention ：
       调用changeIntToHex（33），return 0x33
       只能对"两位"十进制数，进行转换
**************************************************************/
#define ChangeDecIntoHex(dec) ( ( ((dec)/10) <<4 ) + ((dec)%10) )



/*--------------------------------------------------------------------
函数全称：十进制化为十六进制，并以十进制格式返回
函数功能：
注意事项：传参必须为 unsigned 类型，否则移位结果可能吓你一跳
提示说明：调用converseIntToHex（33），return 21
输    入：
返    回：
--------------------------------------------------------------------*/
//#define converseIntToHex(dec)	( ( ((dec)>>4) *10 ) + ((dec)%16) )
/*--------------------------------------------------------------------
函数全称：十六进制强制转换为十进制
函数功能：
注意事项：传参必须为 unsigned 类型，否则移位结果可能吓你一跳
提示说明：调用changeHexToInt（0x33），return 33
输    入：
返    回：
--------------------------------------------------------------------*/
//#define changeHexToInt(hex)		( ( ((hex)>>4) *10 ) + ((hex)%16) )
/*--------------------------------------------------------------------
函数全称：十六进制化为十进制，，并以十六进制格式返回
函数功能：
注意事项：
提示说明：调用converseHexToInt（0x33），return 0x51
输    入：
返    回：
--------------------------------------------------------------------*/
//#define converseHexToInt(hex)	( ( ((hex)/10) <<4 ) + ((hex)%10) )


/**************************************************************/
#ifndef _WINDOWS

typedef unsigned char       BYTE;               // 8-bit
typedef unsigned int  	    WORD;               // 16-bit
typedef unsigned long       DWORD;              // 32-bit

typedef unsigned int        UINT;
typedef unsigned char       UINT8;              // other name for 8-bit integer
typedef unsigned short      UINT16;             // other name for 16-bit integer
typedef unsigned long       UINT32;             // other name for 32-bit integer
 
#endif


/*************一般程序定义的默认值*********************************/
#define YES   	(1)	
#define NO  	(0)	


#define BIT_0   (0x0001)
#define BIT_1   (0x0002)
#define BIT_2   (0x0004)
#define BIT_3   (0x0008)
#define BIT_4   (0x0010)
#define BIT_5   (0x0020)
#define BIT_6   (0x0040)
#define BIT_7   (0x0080)
#define BIT_8   (0x0100)
#define BIT_9   (0x0200)

#define BIT_10  (0x0400)
#define BIT_11  (0x0800)
#define BIT_12  (0x1000)
#define BIT_13  (0x2000)
#define BIT_14  (0x4000)
#define BIT_15  (0x8000)

#define BIT_A   (0x0400)
#define BIT_B   (0x0800)
#define BIT_C   (0x1000)
#define BIT_D   (0x2000)
#define BIT_E   (0x4000)
#define BIT_F   (0x8000)



//#define NULL			0
//#define EOF			-1
//#define TRUE   		1
//#define FALSE  		0
/*

					#define OPEN   	(1)	
					#define CLOSE  	(0)  
					#define HIGH  	(1)  
					#define LOW  		(0)	
*/

//#define ON			1
//#define OFF			0
//#define ENABLE   		1
//#define DISABLE		0
//#define CRR			1
//#define ERR			0
//#define RIGHT			1
//#define WRONG			0
//#define SUCCESS		1
//#define FAILURE		0
//#define PI			3.1415926	



#if defined (_ENUM)

typedef enum{FALSE = 0,TRUE = !FALSE}BOOL;
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

#else /* _ENUM */

typedef enum{FALSE = 0,TRUE = 1}BOOL;
typedef enum {RESET = 0, SET = 1} FlagStatus, ITStatus;
typedef enum {DISABLE = 0, ENABLE = 1} FunctionalState;
typedef enum {ERROR = 0, SUCCESS = 1} ErrorStatus;

#endif /* _ENUM */

#define NULL       ((unsigned char)0)
#define U8_MAX     ((unsigned char)255)
#define S8_MAX     ((signed char)127)
#define S8_MIN     ((signed char)-128)
#define U16_MAX    ((unsigned int)65535u)
#define S16_MAX    ((signed int)32767)
#define S16_MIN    ((signed int)-32768)
#define U32_MAX    ((unsigned long)4294967295uL)
#define S32_MAX    ((signed long)2147483647)
#define S32_MIN    ((signed long)-2147483648)

typedef struct
{
    BYTE    b0:     1;
    BYTE    b1:     1;
    BYTE    b2:     1;
    BYTE    b3:     1;
    BYTE    b4:     1;
    BYTE    b5:     1;
    BYTE    b6:     1;
    BYTE    b7:     1;

}BYTE_BITS;
typedef struct
{
    WORD    b0:     1;
    WORD    b1:     1;
    WORD    b2:     1;
    WORD    b3:     1;
    WORD    b4:     1;
    WORD    b5:     1;
    WORD    b6:     1;
    WORD    b7:     1;
    WORD    b8:     1;
    WORD    b9:     1;
    WORD    b10:    1;
    WORD    b11:    1;
    WORD    b12:    1;
    WORD    b13:    1;
    WORD    b14:    1;
    WORD    b15:    1;
}WORD_BITS;

typedef union _BYTE_VAL
{
    BYTE_BITS bits;
    BYTE Val;
} BYTE_VAL;


typedef union _WORD_VAL
{
    WORD Val;
    WORD_BITS   bits;
    struct
    {
        BYTE LB;
        BYTE HB;
    } byte;
    struct
    {
        BYTE_VAL    low;
        BYTE_VAL    high;
    }byteUnion;

    BYTE v[2];   //v[0]=low,  v[1]=high
} WORD_VAL;

typedef union _DWORD_VAL
{
    DWORD Val;
    struct
    {
        BYTE LB;
        BYTE HB;
        BYTE UB;
        BYTE MB;
    } byte;
    struct
    {
        WORD LW;
        WORD HW;
    } word;
    struct
    {
        WORD_VAL    low;
        WORD_VAL    high;
    }wordUnion;
    struct
    {
        BYTE_VAL    lowLSB;
        BYTE_VAL    lowMSB;
        BYTE_VAL    highLSB;
        BYTE_VAL    highMSB;
    }byteUnion;
    BYTE v[4];    //v[0]=lowLSB,  v[1]=lowMSB,  v[2]=highLSB,  v[3]=highMSB
    WORD w[2];    //w[0]=low, w[1]=high
} DWORD_VAL;

#define LSB(a)          ((a).v[0])
#define MSB(a)          ((a).v[1])

#define LOWER_LSB(a)    ((a).v[0])
#define LOWER_MSB(a)    ((a).v[1])
#define UPPER_LSB(a)    ((a).v[2])
#define UPPER_MSB(a)    ((a).v[3])



////////////////////////////////////////////////////////////////////////////
//==**"函数"宏定义**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"函数声明**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"外部" API 函数声明**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////
	//把数组tx[第x个开始]中cnt个数，复制到数组Rx[第y个开始]
extern void Copy_Array_AtoB(unsigned char *RxPoint,const unsigned char *TxPoint,unsigned char Cnt);

	//将Cnt个相同的Data数据复制到数组Array[x]之后的Cnt个元素
extern void Sent_DataToArray(unsigned char *ArrayPoint,unsigned char DataValue,unsigned int Cnt);

	//死等待延时x毫秒
extern void WaitingDelayMs(unsigned int TimeData);





#endif   /* __Generic_H*/


