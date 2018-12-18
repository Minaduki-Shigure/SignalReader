/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 Generic.h
* �����ļ�-Dependencies:  	 None	
* �ļ�����-File Description:	 ( ͷ�ļ�-Header File )
	�� ���ó����̹淶�������� -ͷ�ļ�-Generic Type Definitions
	01) ���ñ������弯
	02) ���ú궨�弯    
	03) ���ù��ܺ����� 
	04)    05)    06)	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ע������-Attention : 	
	��01) ��̸�ʽ�ͳ�����࣬��û������
	��02)     ��03)    ��04)    ��05)    ��06)       
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
* �޸ļ�¼-Change History:   
	����   ʱ��        �汾  ��������
	Author 	 Date		   Rev      Comment
	-------------------------------------------------------------------------------
	BlueS	2012-12-12	  1.0	   
			xxxx-xx-xx	  x.x	   
			xxxx-xx-xx	  x.x				
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
* ��˾-Company: 			CS-EMLAB  Co. , Ltd.
* ������Э��-Software License Agreement:
	Copyright (C) 2012-2020 	CS-EMLAB  Co. , Ltd.	All rights reserved.	

*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/


#ifndef __Generic_H
#define __Generic_H


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"�궨��**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**��Ŀ"ר��"�궨��**Project-specific macro**================//
////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
extern unsigned char ASCII_Table[21];  //0--F�ַ� ��  �����ַ� ��ʾ��

////////////////////////////////////////////////////////////////////////////
//==**Temp*ȫ�ֱ���**===================================//
//--**�����õ��м������������ȥ����**---------------//
//extern unsigned char G_TempBuf[50];
extern unsigned char G_TempChar;  //������ʱ�õ�"�ֽ�"����
//extern unsigned int G_TempWord;   //������ʱ�õ�"����"����
//extern unsigned long G_TempDword; //������ʱ�õ�"˫��"����

////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////


/*  UnComment the following macro to use AND_OR mask based setting, Comment it to use AND based macros */
//#define USE_AND_OR

#define PUBLIC
#define PROTECTED
#define PRIVATE                 static
//#define _ENUM 




#include "stdint.h" //������һЩ��������(��׼C���ͷ�ļ�)
	//  ��:uint8_t; uint16_t ����"stdint.h"ͷ�ļ�����
	// ����posix��׼��һ�����Ͷ�Ӧ��*_t����


//#define uchar unsigned char
//#define uint unsigned int


typedef uint32_t  u32;	 //unsigned long
typedef uint16_t  u16;  //unsigned int
typedef uint8_t   u8;   //unsigned char 
//typedef signed char int8_t;
//typedef unsigned char uint8_t;




//**********************
//�����ȡ��
//***********************
/* ����һ�����Ա�ĳ���д�� */
typedef unsigned char	uchar;
typedef unsigned int	uint;
typedef unsigned long	ulong;
typedef signed 	char schar;
typedef signed 	int	sint;
typedef signed 	long slong;

/* Ϊ������ֲ������ʹ������д�� */
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
//Ӳ����ȡ��
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






/* �������ͷ�ϵ�RAMʵ�ںܽ������糢�������define�� */
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
����ȫ�ƣ����ݲ���
�������ܣ�
ע�����D<=999999,C<=6
��ʾ˵��������speaData(12,2)���õ�dataElem[0]=2��dataElem[1]=1
��    �룺
��    �أ���
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
*������ Function Name: ChangeDecIntoHex(dec)
*�������� Description: ʮ����ǿ��ת��Ϊʮ������(��ʮ����ת��BCD��)
*������� Parameters : ʮ������
*�������Return Value: None
*ע������  Attention ��
       ����changeIntToHex��33����return 0x33
       ֻ�ܶ�"��λ"ʮ������������ת��
**************************************************************/
#define ChangeDecIntoHex(dec) ( ( ((dec)/10) <<4 ) + ((dec)%10) )



/*--------------------------------------------------------------------
����ȫ�ƣ�ʮ���ƻ�Ϊʮ�����ƣ�����ʮ���Ƹ�ʽ����
�������ܣ�
ע��������α���Ϊ unsigned ���ͣ�������λ�����������һ��
��ʾ˵��������converseIntToHex��33����return 21
��    �룺
��    �أ�
--------------------------------------------------------------------*/
//#define converseIntToHex(dec)	( ( ((dec)>>4) *10 ) + ((dec)%16) )
/*--------------------------------------------------------------------
����ȫ�ƣ�ʮ������ǿ��ת��Ϊʮ����
�������ܣ�
ע��������α���Ϊ unsigned ���ͣ�������λ�����������һ��
��ʾ˵��������changeHexToInt��0x33����return 33
��    �룺
��    �أ�
--------------------------------------------------------------------*/
//#define changeHexToInt(hex)		( ( ((hex)>>4) *10 ) + ((hex)%16) )
/*--------------------------------------------------------------------
����ȫ�ƣ�ʮ�����ƻ�Ϊʮ���ƣ�������ʮ�����Ƹ�ʽ����
�������ܣ�
ע�����
��ʾ˵��������converseHexToInt��0x33����return 0x51
��    �룺
��    �أ�
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


/*************һ��������Ĭ��ֵ*********************************/
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
//==**"����"�궨��**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"��������**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"�ⲿ" API ��������**Exported  API funcitions**===============//
////////////////////////////////////////////////////////////////////////////
	//������tx[��x����ʼ]��cnt���������Ƶ�����Rx[��y����ʼ]
extern void Copy_Array_AtoB(unsigned char *RxPoint,const unsigned char *TxPoint,unsigned char Cnt);

	//��Cnt����ͬ��Data���ݸ��Ƶ�����Array[x]֮���Cnt��Ԫ��
extern void Sent_DataToArray(unsigned char *ArrayPoint,unsigned char DataValue,unsigned int Cnt);

	//���ȴ���ʱx����
extern void WaitingDelayMs(unsigned int TimeData);





#endif   /* __Generic_H*/


