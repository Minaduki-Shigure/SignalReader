/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 LCD_TFT_ILI9325.h
* 附属文件-Dependencies:  	 None	
* 文件描述-File Description:	 ( 头文件-Header File )
	■ "彩屏LCD_TFT_ILI9325" -驱动程序-头文件(外部资源) 
	01) 	     02)     03)    04)    05)    06)	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 注意事项-Attention : 	
	▲01)  要装载头文件 "stdint.h" (定义了一些整数类型(标准C库的头文件))	
							例:uint8_t; uint16_t 都在"stdint.h"头文件定义
							按照posix标准，一般整型对应的*_t类型
	▲02)     ▲03)    ▲04)    ▲05)    ▲06)     
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
* 修改记录-Change History:   
	作者   时间        版本  内容描述
	Author 	 Date		   Rev      Comment
	-------------------------------------------------------------------------------
	BlueS	2012-08-01	  1.0	   
			xxxx-xx-xx	  x.x	   
			xxxx-xx-xx	  x.x				
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
* 公司-Company: 			CS-EMLAB  Co. , Ltd.
* 软件许可协议-Software License Agreement:
	Copyright (C) 2012-2020 	CS-EMLAB  Co. , Ltd.	All rights reserved.	

*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/

#ifndef __LCD_TFT_ILI9325_H   //"彩屏LCD_TFT_ILI9325" -驱动程序-头文件(外部资源) 
#define __LCD_TFT_ILI9325_H 



////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"宏定义**Module-specific macro**==============//
////////////////////////////////////////////////////////////////////////////


//画笔颜色
#define BLACK	     0x0000  // 黑色    0,   0,   0
#define WHITE	     0xFFFF  // 白色    255, 255, 255  

#define RED  	     0xF800  // 红色    255,   0,   0    
#define BRED         0XF81F
#define BRRED 	     0XFC07  //棕红色
#define GRED 	     0XFFE0
#define MAROON       0x7800  //深红色  127,   0,   0      
#define MAGENTA      0xF81F  //品红    255,   0, 255      

#define BROWN 	     0XBC40  //棕色


#define GREEN        0x07E0  //绿色    0, 255,   0     
//#define LGREEN       0x07FC  //浅绿色 
//#define LGREEN       0x07FA  //浅绿色 
#define LGREEN       0x07F8  //浅绿色 



#define OLIVE        0x7BE0  //橄榄绿  127, 127,   0      
#define DGREEN       0x03E0  //深绿色  0,  127,  0
#define DCYAN        0x03EF  //深青色  0,  127, 127       


#define BLUE 	     0x001F  //蓝色    0,   0, 255     
#define GBLUE	     0X07FF  //浅蓝色//显示字符串时，采用这种颜色作为背景色
#define LBLUE	     0X07FF  //浅蓝色
#define NAVY         0x000F  //深蓝色  0,   0, 127
#define CYAN         0x07FF  //青色    0, 255, 255               


#define YELLOW       0xFFE0  //黄色    255, 255, 0       


#define GRAY0        0xEF7D  //灰色0 3165 00110 001011 00101
#define GRAY1        0x8410  //灰色1      00000 000000 00000
#define GRAY2        0x4208  //灰色2  1111111111011111
#define GRAY  		 0X8430  //灰色

#define DGRAY        0x7BEF  //深灰色  127, 127, 127      

#define PURPLE       0x780F  //紫色    127,   0, 127     



//GUI颜色
#define DARKBLUE     0X01CF	 //深蓝色
#define LIGHTBLUE    0X7D7C  //浅蓝色
#define GRAYBLUE     0X5458  //灰蓝色
//以上三色为PANEL的颜色

#define LIGHTGREEN   0X841F  //浅绿色
//#define LIGHTGRAY    0XEF5B  //浅灰色(PANNEL)
#define LGRAY 	     0XC618  //浅灰色 //灰白色  192, 192, 192     
#define LGRAYBLUE    0XA651  //浅灰蓝色
#define LBBLUE       0X2B12  //浅棕蓝色





////////////////////////////////////////////////////////////////////////////
//==**项目"专用"宏定义**Project-specific macro**===================//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//--**"实际显示"宏定义**-------------------------------------------//

#define M_Vertical_FONT (16) //字体"垂直宽度"   //定义显示"行距"
#define M_Horizontal_FONT (8) //字体"水平宽度"   //定义显示"字符间距"


    //定义每一"行"的"行地址"(有包括行距)
#define M_01Line   (0)                           //显示第"01"行的行地址
#define M_02Line   (M_01Line + M_Vertical_FONT)  //显示第"02"行的行地址
#define M_03Line   (M_02Line + M_Vertical_FONT)  //显示第"03"行的行地址
#define M_04Line   (M_03Line + M_Vertical_FONT)  //显示第"04"行的行地址
#define M_05Line   (M_04Line + M_Vertical_FONT)  //显示第"05"行的行地址
#define M_06Line   (M_05Line + M_Vertical_FONT)  //显示第"06"行的行地址
#define M_07Line   (M_06Line + M_Vertical_FONT)  //显示第"07"行的行地址
#define M_08Line   (M_07Line + M_Vertical_FONT)  //显示第"08"行的行地址
#define M_09Line   (M_08Line + M_Vertical_FONT)  //显示第"09"行的行地址
#define M_10Line   (M_09Line + M_Vertical_FONT)  //显示第"10"行的行地址
#define M_11Line   (M_10Line + M_Vertical_FONT)  //显示第"11"行的行地址
#define M_12Line   (M_11Line + M_Vertical_FONT)  //显示第"12"行的行地址
#define M_13Line   (M_12Line + M_Vertical_FONT)  //显示第"13"行的行地址
#define M_14Line   (M_13Line + M_Vertical_FONT)  //显示第"14"行的行地址
#define M_15Line   (M_14Line + M_Vertical_FONT)  //显示第"15"行的行地址
//#define M_16Line   (M_15Line + M_Vertical_FONT)  //显示第"16"行的行地址
//#define M_17Line   (M_16Line + M_Vertical_FONT)  //显示第"17"行的行地址
//#define M_18Line   (M_17Line + M_Vertical_FONT)  //显示第"18"行的行地址
//#define M_19Line   (M_18Line + M_Vertical_FONT)  //显示第"19"行的行地址
//#define M_20Line   (M_19Line + M_Vertical_FONT)  //显示第"20"行的行地址


//定义每一"字符"的"列"地址(有包括字符间距)
#define M_01Column   (0) 				               //显示第"01 字符"的"列地址"
#define M_02Column   (M_01Column + M_Horizontal_FONT)  //显示第"02 字符"的"列地址"
#define M_03Column   (M_02Column + M_Horizontal_FONT)  //显示第"03 字符"的"列地址"
#define M_04Column   (M_03Column + M_Horizontal_FONT)  //显示第"04 字符"的"列地址"
#define M_05Column   (M_04Column + M_Horizontal_FONT)  //显示第"05 字符"的"列地址"
#define M_06Column   (M_05Column + M_Horizontal_FONT)  //显示第"06 字符"的"列地址"
#define M_07Column   (M_06Column + M_Horizontal_FONT)  //显示第"07 字符"的"列地址"
#define M_08Column   (M_07Column + M_Horizontal_FONT)  //显示第"08 字符"的"列地址"
#define M_09Column   (M_08Column + M_Horizontal_FONT)  //显示第"09 字符"的"列地址"
#define M_10Column   (M_09Column + M_Horizontal_FONT)  //显示第"10字符"的"列地址"
#define M_11Column   (M_10Column + M_Horizontal_FONT)  //显示第"11字符"的"列地址"
#define M_12Column   (M_11Column + M_Horizontal_FONT)  //显示第"12字符"的"列地址"
#define M_13Column   (M_12Column + M_Horizontal_FONT)  //显示第"13字符"的"列地址"
#define M_14Column   (M_13Column + M_Horizontal_FONT)  //显示第"14字符"的"列地址"
#define M_15Column   (M_14Column + M_Horizontal_FONT)  //显示第"15字符"的"列地址"
#define M_16Column   (M_15Column + M_Horizontal_FONT)  //显示第"16字符"的"列地址"
#define M_17Column   (M_16Column + M_Horizontal_FONT)  //显示第"17字符"的"列地址"
#define M_18Column   (M_17Column + M_Horizontal_FONT)  //显示第"18字符"的"列地址"
#define M_19Column   (M_18Column + M_Horizontal_FONT)  //显示第"19字符"的"列地址"
#define M_20Column   (M_19Column + M_Horizontal_FONT)  //显示第"20字符"的"列地址"
#define M_21Column   (M_20Column + M_Horizontal_FONT)  //显示第"21字符"的"列地址"
#define M_22Column   (M_21Column + M_Horizontal_FONT)  //显示第"22字符"的"列地址"
#define M_23Column   (M_22Column + M_Horizontal_FONT)  //显示第"23字符"的"列地址"
#define M_24Column   (M_23Column + M_Horizontal_FONT)  //显示第"24字符"的"列地址"
#define M_25Column   (M_24Column + M_Horizontal_FONT)  //显示第"25字符"的"列地址"
#define M_26Column   (M_25Column + M_Horizontal_FONT)  //显示第"26字符"的"列地址"
#define M_27Column   (M_26Column + M_Horizontal_FONT)  //显示第"27字符"的"列地址"
#define M_28Column   (M_27Column + M_Horizontal_FONT)  //显示第"28字符"的"列地址"
#define M_29Column   (M_28Column + M_Horizontal_FONT)  //显示第"29字符"的"列地址"
#define M_30Column   (M_29Column + M_Horizontal_FONT)  //显示第"30字符"的"列地址"
#define M_31Column   (M_30Column + M_Horizontal_FONT)  //显示第"31字符"的"列地址"
#define M_32Column   (M_31Column + M_Horizontal_FONT)  //显示第"32字符"的"列地址"
#define M_33Column   (M_32Column + M_Horizontal_FONT)  //显示第"33字符"的"列地址"
#define M_34Column   (M_33Column + M_Horizontal_FONT)  //显示第"34字符"的"列地址"
#define M_35Column   (M_34Column + M_Horizontal_FONT)  //显示第"35字符"的"列地址"
#define M_36Column   (M_35Column + M_Horizontal_FONT)  //显示第"36字符"的"列地址"
#define M_37Column   (M_36Column + M_Horizontal_FONT)  //显示第"37字符"的"列地址"
#define M_38Column   (M_37Column + M_Horizontal_FONT)  //显示第"38字符"的"列地址"
#define M_39Column   (M_38Column + M_Horizontal_FONT)  //显示第"39字符"的"列地址"
#define M_40Column   (M_39Column + M_Horizontal_FONT)  //显示第"40字符"的"列地址"



////////////////////////////////////////////////////////////////////////////
//--**"显示内容缓冲数组"宏定义**------------------------------//
    //定义每一"行"的"行地址"(用于"显示内容缓冲数组")
#define M_01LineBuf    (0)  
#define M_02LineBuf    (1)  
#define M_03LineBuf    (2)  
#define M_04LineBuf    (3)  
#define M_05LineBuf    (4)  
#define M_06LineBuf    (5)  
#define M_07LineBuf    (6)  
#define M_08LineBuf    (7)  
#define M_09LineBuf    (8) 
#define M_10LineBuf    (9) 
#define M_11LineBuf    (10) 
#define M_12LineBuf    (11) 
#define M_13LineBuf    (12) 
#define M_14LineBuf    (13) 
#define M_15LineBuf    (14) 
//#define M_16LineBuf    (15) 
//#define M_17LineBuf    (16) 
//#define M_18LineBuf    (17) 
//#define M_19LineBuf    (18) 
//#define M_20LineBuf    (19) 


    //定义每一"列"的"列地址"(用于"显示内容缓冲数组")
#define M_01ColumnBuf (0)  
#define M_02ColumnBuf (1)  
#define M_03ColumnBuf (2)  
#define M_04ColumnBuf (3)  
#define M_05ColumnBuf (4)  
#define M_06ColumnBuf (5)  
#define M_07ColumnBuf (6)  
#define M_08ColumnBuf (7)  
#define M_09ColumnBuf (8)  
#define M_10ColumnBuf (9)  
#define M_11ColumnBuf (10)  
#define M_12ColumnBuf (11)  
#define M_13ColumnBuf (12)  
#define M_14ColumnBuf (13)  
#define M_15ColumnBuf (14)  
#define M_16ColumnBuf (15)  
#define M_17ColumnBuf (16)  
#define M_18ColumnBuf (17)  
#define M_19ColumnBuf (18)  
#define M_20ColumnBuf (19)  
#define M_21ColumnBuf (20)  
#define M_22ColumnBuf (21)  
#define M_23ColumnBuf (22)  
#define M_24ColumnBuf (23)  
#define M_25ColumnBuf (24)  
#define M_26ColumnBuf (25)  
#define M_27ColumnBuf (26)  
#define M_28ColumnBuf (27)  
#define M_29ColumnBuf (28)  
#define M_30ColumnBuf (29)
#define M_31ColumnBuf (30)  
#define M_32ColumnBuf (31)  
#define M_33ColumnBuf (32)  
#define M_34ColumnBuf (33)  
#define M_35ColumnBuf (34)  
#define M_36ColumnBuf (35)  
#define M_37ColumnBuf (36)  
#define M_38ColumnBuf (37)  
#define M_39ColumnBuf (38)  
#define M_40ColumnBuf (39)



////////////////////////////////////////////////////////////////////////////
//==**"菜单区"  相关宏定义**===============================//
////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	//--**"菜单区"的"行、列地址"**------------------------------------//
#define M_Line_Gap  (8)

#define M_MenuLine_01  (M_02Line + M_Line_Gap) //第"01 菜单行"
#define M_MenuLine_02  (M_03Line + M_Line_Gap) //第"02 菜单行"
#define M_MenuLine_03  (M_04Line + M_Line_Gap) //第"03 菜单行"
#define M_MenuLine_04  (M_05Line + M_Line_Gap) //第"04 菜单行"
#define M_MenuLine_05  (M_06Line + M_Line_Gap) //第"05 菜单行"
#define M_MenuLine_06  (M_07Line + M_Line_Gap) //第"06 菜单行"
#define M_MenuLine_07  (M_08Line + M_Line_Gap) //第"07 菜单行"
#define M_MenuLine_08  (M_09Line + M_Line_Gap) //第"08 菜单行"
#define M_MenuLine_09  (M_10Line + M_Line_Gap) //第"09 菜单行"
#define M_MenuLine_10  (M_11Line + M_Line_Gap) //第"10 菜单行"
#define M_MenuLine_11  (M_12Line + M_Line_Gap) //第"11 菜单行"
#define M_MenuLine_12  (M_13Line + M_Line_Gap) //第"12 菜单行"

//////////////////////////////////////////////////////////////////////
#define M_MenuColumn_01  (M_01Column) //第"01 菜单列"//菜单区的第一列
#define M_MenuColumn_19  (M_19Column) //第"19 菜单列"//菜单区的最后列


	////////////////////////////////////////////////////////////////////////////
	//--**"菜单区"的"行、列"-显示缓冲数组**----------------------//
#define MenuLine01   (M_02LineBuf) //第"01 菜单行"-显示缓冲数组
#define MenuLine02   (M_03LineBuf) //第"02 菜单行"-显示缓冲数组
#define MenuLine03   (M_04LineBuf) //第"03 菜单行"-显示缓冲数组
#define MenuLine04   (M_05LineBuf) //第"04 菜单行"-显示缓冲数组
#define MenuLine05   (M_06LineBuf) //第"05 菜单行"-显示缓冲数组
#define MenuLine06   (M_07LineBuf) //第"06 菜单行"-显示缓冲数组
#define MenuLine07   (M_08LineBuf) //第"07 菜单行"-显示缓冲数组
#define MenuLine08   (M_09LineBuf) //第"08 菜单行"-显示缓冲数组
#define MenuLine09   (M_10LineBuf) //第"09 菜单行"-显示缓冲数组
#define MenuLine10   (M_11LineBuf) //第"10 菜单行"-显示缓冲数组
#define MenuLine11   (M_12LineBuf) //第"11 菜单行"-显示缓冲数组
#define MenuLine12   (M_13LineBuf) //第"12 菜单行"-显示缓冲数组

#define MenuColumn01 (M_01ColumnBuf) //第"01 菜单列"-显示缓冲数组
#define MenuColumn02 (M_02ColumnBuf) //第"02 菜单列"-显示缓冲数组
#define MenuColumn03 (M_03ColumnBuf) //第"03 菜单列"-显示缓冲数组
#define MenuColumn04 (M_04ColumnBuf) //第"04 菜单列"-显示缓冲数组
#define MenuColumn05 (M_05ColumnBuf) //第"05 菜单列"-显示缓冲数组
#define MenuColumn06 (M_06ColumnBuf) //第"06 菜单列"-显示缓冲数组
#define MenuColumn07 (M_07ColumnBuf) //第"07 菜单列"-显示缓冲数组
#define MenuColumn08 (M_08ColumnBuf) //第"08 菜单列"-显示缓冲数组
#define MenuColumn09 (M_09ColumnBuf) //第"09 菜单列"-显示缓冲数组
#define MenuColumn10 (M_10ColumnBuf) //第"10 菜单列"-显示缓冲数组
#define MenuColumn11 (M_11ColumnBuf) //第"11 菜单列"-显示缓冲数组
#define MenuColumn12 (M_12ColumnBuf) //第"12 菜单列"-显示缓冲数组
#define MenuColumn13 (M_13ColumnBuf) //第"13 菜单列"-显示缓冲数组
#define MenuColumn14 (M_14ColumnBuf) //第"14 菜单列"-显示缓冲数组
#define MenuColumn15 (M_15ColumnBuf) //第"15 菜单列"-显示缓冲数组
#define MenuColumn16 (M_16ColumnBuf) //第"16 菜单列"-显示缓冲数组
#define MenuColumn17 (M_17ColumnBuf) //第"17 菜单列"-显示缓冲数组
#define MenuColumn18 (M_18ColumnBuf) //第"18 菜单列"-显示缓冲数组
#define MenuColumn19 (M_19ColumnBuf) //第"19 菜单列"-显示缓冲数组


////////////////////////////////////////////////////////////////////////////
//==**"测试区"  相关宏定义**===============================//
////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	//--**"测试区"的"行、列地址"**------------------------------------//
#define M_TestLine_01  (M_02Line + M_Line_Gap) //第"01 测试行"
#define M_TestLine_02  (M_03Line + M_Line_Gap) //第"02 测试行"
#define M_TestLine_03  (M_04Line + M_Line_Gap) //第"03 测试行"
#define M_TestLine_04  (M_05Line + M_Line_Gap) //第"04 测试行"
#define M_TestLine_05  (M_06Line + M_Line_Gap) //第"05 测试行"
#define M_TestLine_06  (M_07Line + M_Line_Gap) //第"06 测试行"
#define M_TestLine_07  (M_08Line + M_Line_Gap) //第"07 测试行"
#define M_TestLine_08  (M_09Line + M_Line_Gap) //第"08 测试行"
#define M_TestLine_09  (M_10Line + M_Line_Gap) //第"09 测试行"
#define M_TestLine_10  (M_11Line + M_Line_Gap) //第"10 测试行"
#define M_TestLine_11  (M_12Line + M_Line_Gap) //第"11 测试行"
#define M_TestLine_12  (M_13Line + M_Line_Gap) //第"12 测试行"

////////////////////////////////////////////////////////////////////////////
#define M_TestColumn_01  (M_21Column) //第"01 测试列"//测试区的第一列
#define M_TestColumn_02  (M_22Column) //第"02 测试列"
#define M_TestColumn_03  (M_23Column) //第"03 测试列"
#define M_TestColumn_04  (M_24Column) //第"04 测试列"
#define M_TestColumn_05  (M_25Column) //第"05 测试列"
#define M_TestColumn_06  (M_26Column) //第"06 测试列"
#define M_TestColumn_07  (M_27Column) //第"07 测试列"
#define M_TestColumn_08  (M_28Column) //第"08 测试列"
#define M_TestColumn_09  (M_29Column) //第"09 测试列"
#define M_TestColumn_10  (M_30Column) //第"10 测试列"
#define M_TestColumn_11  (M_31Column) //第"11 测试列"
#define M_TestColumn_12  (M_32Column) //第"12 测试列"
#define M_TestColumn_13  (M_33Column) //第"13 测试列"
#define M_TestColumn_14  (M_34Column) //第"14 测试列"
#define M_TestColumn_15  (M_35Column) //第"15 测试列"
#define M_TestColumn_16  (M_36Column) //第"16 测试列"
#define M_TestColumn_17  (M_37Column) //第"17 测试列"
#define M_TestColumn_18  (M_38Column) //第"18 测试列"
#define M_TestColumn_19  (M_39Column) //第"19 测试列"
#define M_TestColumn_20  (M_40Column) //第"20 测试列"//测试区的最后列


	////////////////////////////////////////////////////////////////////////////
	//--**"测试区"的"行、列"-显示缓冲数组**----------------------//
#define TestLine01   (M_02LineBuf) //第"01 测试行"-显示缓冲数组
#define TestLine02   (M_03LineBuf) //第"02 测试行"-显示缓冲数组
#define TestLine03   (M_04LineBuf) //第"03 测试行"-显示缓冲数组
#define TestLine04   (M_05LineBuf) //第"04 测试行"-显示缓冲数组
#define TestLine05   (M_06LineBuf) //第"05 测试行"-显示缓冲数组
#define TestLine06   (M_07LineBuf) //第"06 测试行"-显示缓冲数组
#define TestLine07   (M_08LineBuf) //第"07 测试行"-显示缓冲数组
#define TestLine08   (M_09LineBuf) //第"08 测试行"-显示缓冲数组
#define TestLine09   (M_10LineBuf) //第"09 测试行"-显示缓冲数组
#define TestLine10   (M_11LineBuf) //第"10 测试行"-显示缓冲数组
#define TestLine11   (M_12LineBuf) //第"11 测试行"-显示缓冲数组
#define TestLine12   (M_13LineBuf) //第"12 测试行"-显示缓冲数组

#define TestColumn01 (M_21ColumnBuf) //第"01 测试列"-显示缓冲数组
#define TestColumn02 (M_22ColumnBuf) //第"02 测试列"-显示缓冲数组
#define TestColumn03 (M_23ColumnBuf) //第"03 测试列"-显示缓冲数组
#define TestColumn04 (M_24ColumnBuf) //第"04 测试列"-显示缓冲数组
#define TestColumn05 (M_25ColumnBuf) //第"05 测试列"-显示缓冲数组
#define TestColumn06 (M_26ColumnBuf) //第"06 测试列"-显示缓冲数组
#define TestColumn07 (M_27ColumnBuf) //第"07 测试列"-显示缓冲数组
#define TestColumn08 (M_28ColumnBuf) //第"08 测试列"-显示缓冲数组
#define TestColumn09 (M_29ColumnBuf) //第"09 测试列"-显示缓冲数组
#define TestColumn10 (M_30ColumnBuf) //第"10 测试列"-显示缓冲数组
#define TestColumn11 (M_31ColumnBuf) //第"11 测试列"-显示缓冲数组
#define TestColumn12 (M_32ColumnBuf) //第"12 测试列"-显示缓冲数组
#define TestColumn13 (M_33ColumnBuf) //第"13 测试列"-显示缓冲数组
#define TestColumn14 (M_34ColumnBuf) //第"14 测试列"-显示缓冲数组
#define TestColumn15 (M_35ColumnBuf) //第"15 测试列"-显示缓冲数组
#define TestColumn16 (M_36ColumnBuf) //第"16 测试列"-显示缓冲数组
#define TestColumn17 (M_37ColumnBuf) //第"17 测试列"-显示缓冲数组
#define TestColumn18 (M_38ColumnBuf) //第"18 测试列"-显示缓冲数组
#define TestColumn19 (M_39ColumnBuf) //第"19 测试列"-显示缓冲数组
#define TestColumn20 (M_40ColumnBuf) //第"20 测试列"-显示缓冲数组




////////////////////////////////////////////////////////////////////////////
//--**配置显示模式:横向或纵向**--------------------------------//
//--care-- 下面2个宏定义，只能"1"个有效
#define USE_HORIZONTAL_LCD_TFT   //使用的"水平(横向)显示模式"
//#define USE_VERTICAL_LCD_TFT     //使用的"垂直(纵向)显示模式"


////////////////////////////////////////////////////////////////////////////
//--**配置字体大小**------------------------------------------------//
#define FONT1206   (1) //字体12*6
#define FONT1608   (2) //字体16*8








//#define WIDTH       240                 /* 显示宽度240*/
//#define HEIGHT      320
//#define USE_HORIZONTAL 


#define M_Space_ASCII      (0x20) //"空格"的ASCII码






////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//--**"彩屏LCD_TFT_ILI9325"*全局标志位**-----------------------------//
extern union FLAGBIT16 LCD_TFT_FlagBits;  //"彩屏LCD_TFT_ILI9325"相关标志位变量
#define  G_LCD_TFT_FlagBits    LCD_TFT_FlagBits.FLAG16  
//#define	 F_Refresh_LCD_TFT     LCD_TFT_FlagBits.b.f0  //为1时，刷新液晶显示(刷新使能位)  
#define	 F_ReSet_LCD_TFT       LCD_TFT_FlagBits.b.f1  //为1时，复位重启"彩屏LCD_TFT"液晶模块   
#define	 F_Clear_LCD_TFT       LCD_TFT_FlagBits.b.f2  //为1时，对"彩屏LCD_TFT"进行清屏
#define  F_Close_LCD_TFT       LCD_TFT_FlagBits.b.f3  //为1时，关闭液晶背光和液晶内容刷新  
//#define	 F_TimeRefresh_LCD_TFT LCD_TFT_FlagBits.b.f4  //为1时，"彩屏LCD_TFT"刷新时间
//#define	 F_EnCursor_LCD_TFT    LCD_TFT_FlagBits.b.f5  //为1时，闪烁显示光标("彩屏LCD_TFT")
//#define	 F_         LCD_TFT_FlagBits.b.f6   //为1时，
//#define	 F__Open_CursorFlash         LCD_TFT_FlagBits.b.f7  ////为1时， 开光标闪烁显示,用完清0 
//#define	 F_Close_CursorFlash      LCD_TFT_FlagBits.b.f8  ////为1时， 禁止光标闪烁,用完清0 
//#define	 F       LCD_TFT_FlagBits.b.f9  //为1时，
//#define	 F_      LCD_TFT_FlagBits.b.f10   //为1时，
//#define	 F_Clear_TestArea           LCD_TFT_FlagBits.b.f11    //为1时，只对测试区域清屏
#define	 F_250ms_Blink_Key_LCD_TFT	LCD_TFT_FlagBits.b.f12    //为1时， 闪烁指定"按键位置" --"彩屏LCD_TFT"(用于闪烁菜单)
#define	 F_250ms_Blink_Line_LCD_TFT	LCD_TFT_FlagBits.b.f13    //为1时， 闪烁指定行 --"彩屏LCD_TFT"(用于闪烁菜单)
#define	 F_EnCopyDispBuf_LCD	    LCD_TFT_FlagBits.b.f14    //为1时，使能复制"显示缓存数组" (用于闪烁菜单)
#define	 F_LCD_TFT_Timing	        LCD_TFT_FlagBits.b.f15    //用于两次操作"彩屏LCD_TFT"的间隔定时时间 



	//此变量不为0:表示有内容更新显示	
extern union FLAGBIT16  Update_01Bits;	//"彩屏LCD_TFT_ILI9325"刷新显示相关标志位变量
#define  G_Update_01Bits       Update_01Bits.FLAG16  
#define	 F_Update_AdLine       Update_01Bits.b.f0  //刷新:"01行广告"  (为1时)

#define	 F_Update_MenuLine01   Update_01Bits.b.f1  //刷新:""第01 菜单行""  (为1时)
#define	 F_Update_MenuLine02   Update_01Bits.b.f2  //刷新:""第02 菜单行""  (为1时)
#define	 F_Update_MenuLine03   Update_01Bits.b.f3  //刷新:""第03 菜单行""  (为1时)
#define	 F_Update_MenuLine04   Update_01Bits.b.f4  //刷新:""第04 菜单行""  (为1时)
#define	 F_Update_MenuLine05   Update_01Bits.b.f5  //刷新:""第05 菜单行""  (为1时)
#define	 F_Update_MenuLine06   Update_01Bits.b.f6  //刷新:""第06 菜单行""  (为1时)
#define  F_Update_MenuLine07   Update_01Bits.b.f7  //刷新:""第07 菜单行""  (为1时)
#define	 F_Update_MenuLine08   Update_01Bits.b.f8  //刷新:""第08 菜单行""  (为1时)
#define	 F_Update_MenuLine09   Update_01Bits.b.f9  //刷新:""第09 菜单行""  (为1时)
#define	 F_Update_MenuLine10   Update_01Bits.b.f10 //刷新:""第10 菜单行""  (为1时)
#define	 F_Update_MenuLine11   Update_01Bits.b.f11 //刷新:""第11 菜单行""  (为1时)
#define	 F_Update_MenuLine12   Update_01Bits.b.f12 //刷新:""第12 菜单行""  (为1时)
//#define	 F_     Update_01Bits.b.f13 //刷新:
//#define	 F_     Update_01Bits.b.f14 //刷新:
//#define	 F_     Update_01Bits.b.f15 //刷新:


	//此变量不为0:表示有内容更新显示	
extern union FLAGBIT16  Update_02Bits;//"彩屏LCD_TFT_ILI9325"刷新显示相关标志位变量
#define  G_Update_02Bits      Update_02Bits.FLAG16  
//#define	 F_       Update_02Bits.b.f0  // (为1时)
#define	 F_Update_TestLine01   Update_02Bits.b.f1  //刷新:""第01 测试行""  (为1时)
#define	 F_Update_TestLine02   Update_02Bits.b.f2  //刷新:""第02 测试行""  (为1时)
#define	 F_Update_TestLine03   Update_02Bits.b.f3  //刷新:""第03 测试行""  (为1时)
#define	 F_Update_TestLine04   Update_02Bits.b.f4  //刷新:""第04 测试行""  (为1时)
#define	 F_Update_TestLine05   Update_02Bits.b.f5  //刷新:""第05 测试行""  (为1时)
#define	 F_Update_TestLine06   Update_02Bits.b.f6  //刷新:""第06 测试行""  (为1时)
#define	 F_Update_TestLine07   Update_02Bits.b.f7  //刷新:""第07 测试行""  (为1时)
#define	 F_Update_TestLine08   Update_02Bits.b.f8  //刷新:""第08 测试行""  (为1时)
#define	 F_Update_TestLine09   Update_02Bits.b.f9  //刷新:""第09 测试行""  (为1时)
#define	 F_Update_TestLine10   Update_02Bits.b.f10 //刷新:""第10 测试行""  (为1时)
#define	 F_Update_TestLine11   Update_02Bits.b.f11 //刷新:""第11 测试行""  (为1时)
#define	 F_Update_TestLine12   Update_02Bits.b.f12 //刷新:""第12 测试行""  (为1时)
//#define	 F_     Update_02Bits.b.f13 // (为1时)
//#define	 F_  Update_02Bits.b.f14 // (为1时)
//#define	 F_ Update_02Bits.b.f15 //(为1时)


	//此变量不为0:表示有内容更新显示	
extern union FLAGBIT16  Update_03Bits;//"彩屏LCD_TFT_ILI9325"刷新显示相关标志位变量
#define  G_Update_03Bits       Update_03Bits.FLAG16  

#define	 F_Update_RealTime     Update_03Bits.b.f0  //刷新:"实时时间"  (为1时)
#define	 F_Update_Temperature  Update_03Bits.b.f1  //刷新:"实时温度"  (为1时)
#define	 F_Update_CurrentValue Update_03Bits.b.f2  //刷新:"INA21x 实时电流值" (为1时)
#define	 F_Update_Power        Update_03Bits.b.f3  //刷新:""锂电池电量""  (为1时)
//#define	 F_   Update_03Bits.b.f4  // (为1时)
//#define	 F_   Update_03Bits.b.f5  // (为1时)
//#define	 F_   Update_03Bits.b.f6  // (为1时)
//#define	 F_   Update_03Bits.b.f7  // (为1时)
//#define	 F_   Update_03Bits.b.f8  // (为1时)
//#define	 F_   Update_03Bits.b.f9  // (为1时)
//#define	 F_   Update_03Bits.b.f10 // (为1时)
//#define	 F_   Update_03Bits.b.f11 // (为1时)
//#define	 F_   Update_03Bits.b.f12 // (为1时)
//#define	 F_   Update_03Bits.b.f13 // (为1时)
//#define	 F_   Update_03Bits.b.f14 // (为1时)
//#define	 F_   Update_03Bits.b.f15 // (为1时)




extern union FLAGBIT16  hightLight_01Bits;//"彩屏LCD_TFT_ILI9325"刷新显示相关标志位变量
#define  G_hightLight_01Bits  hightLight_01Bits.FLAG16  
//#define	 F_       hightLight_01Bits.b.f0  
#define	 F_HL_TestLine01  hightLight_01Bits.b.f1  //反白刷新:""第01 测试行""  (为1时)
#define	 F_HL_TestLine02  hightLight_01Bits.b.f2  //反白刷新:""第02 测试行""  (为1时)
#define	 F_HL_TestLine03  hightLight_01Bits.b.f3  //反白刷新:""第03 测试行""  (为1时)
#define	 F_HL_TestLine04  hightLight_01Bits.b.f4  //反白刷新:""第04 测试行""  (为1时)
#define	 F_HL_TestLine05  hightLight_01Bits.b.f5  //反白刷新:""第05 测试行""  (为1时)
#define	 F_HL_TestLine06  hightLight_01Bits.b.f6  //反白刷新:""第06 测试行""  (为1时)
#define	 F_HL_TestLine07  hightLight_01Bits.b.f7  //反白刷新:""第07 测试行""  (为1时)
#define	 F_HL_TestLine08  hightLight_01Bits.b.f8  //反白刷新:""第08 测试行""  (为1时)
#define	 F_HL_TestLine09  hightLight_01Bits.b.f9  //反白刷新:""第09 测试行""  (为1时)
#define	 F_HL_TestLine10  hightLight_01Bits.b.f10 //反白刷新:""第10 测试行""  (为1时)
#define	 F_HL_TestLine11  hightLight_01Bits.b.f11 //反白刷新:""第11 测试行""  (为1时)
#define	 F_HL_TestLine12  hightLight_01Bits.b.f12 //反白刷新:""第12 测试行""  (为1时)
//#define	 F_     hightLight_01Bits.b.f13 
//#define	 F_     hightLight_01Bits.b.f14 
//#define	 F_     hightLight_01Bits.b.f15 


extern union FLAGBIT16  hightLight_02Bits;	//"彩屏LCD_TFT_ILI9325"刷新显示相关标志位变量
#define  G_hightLight_02Bits   hightLight_02Bits.FLAG16  
//#define	 F_       hightLight_02Bits.b.f0  
#define	 F_HL_MenuLine01   hightLight_02Bits.b.f1  //反白刷新:""第01 菜单行""  (为1时)
#define	 F_HL_MenuLine02   hightLight_02Bits.b.f2  //反白刷新:""第02 菜单行""  (为1时)
#define	 F_HL_MenuLine03   hightLight_02Bits.b.f3  //反白刷新:""第03 菜单行""  (为1时)
#define	 F_HL_MenuLine04   hightLight_02Bits.b.f4  //反白刷新:""第04 菜单行""  (为1时)
#define	 F_HL_MenuLine05   hightLight_02Bits.b.f5  //反白刷新:""第05 菜单行""  (为1时)
#define	 F_HL_MenuLine06   hightLight_02Bits.b.f6  //反白刷新:""第06 菜单行""  (为1时)
#define  F_HL_MenuLine07   hightLight_02Bits.b.f7  //反白刷新:""第07 菜单行""  (为1时)
#define	 F_HL_MenuLine08   hightLight_02Bits.b.f8  //反白刷新:""第08 菜单行""  (为1时)
#define	 F_HL_MenuLine09   hightLight_02Bits.b.f9  //反白刷新:""第09 菜单行""  (为1时)
#define	 F_HL_MenuLine10   hightLight_02Bits.b.f10 //反白刷新:""第10 菜单行""  (为1时)
#define	 F_HL_MenuLine11   hightLight_02Bits.b.f11 //反白刷新:""第11 菜单行""  (为1时)
#define	 F_HL_MenuLine12   hightLight_02Bits.b.f12 //反白刷新:""第12 菜单行""  (为1时)
//#define	 F_     hightLight_02Bits.b.f13 
//#define	 F_     hightLight_02Bits.b.f14 
//#define	 F_     hightLight_02Bits.b.f15






extern u8 G_LcdBuf[15][41]; //"彩屏LCD_TFT_ILI9325"显示内容缓冲数组(15行,每行40字符)//care--每行第41个数组元素为"\0"


////////////////////////////////////////////////////////////////////////////
//--**相关颜色定义**------------------------------------------------//
extern u16 AD_Point;      //配置"广告区"--"画笔颜色": 默认为"黑色"
extern u16 AD_Back;       //配置"广告区"--"背景颜色": 默认为"白色"

extern u16 Menu_Point;    //配置"菜单区"--"画笔颜色": 默认为"黑色"
extern u16 Menu_Back;     //配置"菜单区"--"背景颜色": 默认为"浅蓝色"
extern u16 HL_Menu_Point; //配置"反白菜单区"--"画笔颜色": 默认为"浅蓝色"
extern u16 HL_Menu_Back;  //配置"反白菜单区"--"背景颜色": 默认为"黑色"

extern u16 Test_Point;    //配置"测试区"--"画笔颜色": 默认为"黑色"
extern u16 Test_Back;    //配置"测试区"--"背景颜色": 默认为"浅绿色"
extern u16 HL_Test_Point; //配置"反白测试区"--"画笔颜色": 默认为"浅绿色"
extern u16 HL_Test_Back;  //配置"反白测试区"--"背景颜色": 默认为"黑色"

extern u16 Monitor_Point; //配置"监控区"--"画笔颜色": 默认为"黑色"
extern u16 Monitor_Back;       //配置"监控区"--"背景颜色": 默认为"白色"


extern u16 Fixed_Point;   //配置"特定的固定的颜色"--"画笔颜色": 默认为"蓝色"(包括:网址、版本号、监控区的相关数字)
extern u16 Fixed_Back;    //配置"监控区"--"背景颜色": 默认为"白色"(包括:网址、版本号、监控区的相关数字)




//////////////////////////////////////////////////////////////////
extern u16 POINT_COLOR;  //配置"画笔颜色": 默认为"黑色"
extern u16 BACK_COLOR;   //配置"背景颜色": 默认为"白色"

//////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"函数"宏定义**Functions macro**============================//
////////////////////////////////////////////////////////////////////////////

#define mUpdate_All_MenuLine {F_Update_MenuLine01=YES;F_Update_MenuLine02=YES;F_Update_MenuLine03=YES;\
	                          F_Update_MenuLine04=YES;F_Update_MenuLine05=YES;F_Update_MenuLine06=YES;\
	                          F_Update_MenuLine07=YES;F_Update_MenuLine08=YES;F_Update_MenuLine09=YES;\
	                          F_Update_MenuLine10=YES;F_Update_MenuLine11=YES;F_Update_MenuLine12=YES;}   

#define mUpdate_All_TestLine {F_Update_TestLine01=YES;F_Update_TestLine02=YES;F_Update_TestLine03=YES;\
	                          F_Update_TestLine04=YES;F_Update_TestLine05=YES;F_Update_TestLine06=YES;\
	                          F_Update_TestLine07=YES;F_Update_TestLine08=YES;F_Update_TestLine09=YES;\
	                          F_Update_TestLine10=YES;F_Update_TestLine11=YES;F_Update_TestLine12=YES;}   
	


////////////////////////////////////////////////////////////////////////////
//==**"此模块专用"函数声明**Exported Module-specific funcitions**======//
////////////////////////////////////////////////////////////////////////////

void ILI9325_WriteByte(u8 data);  //SPI向ILI9325 控制器写一个字节数据
void ILI9325_WriteRegIndex(u16 index); //向ILI9325，写"控制命令寄存器地址"
void ILI9325_WriteData(u16 data);  //向ILI9325，写"16 位数据"


void LCD_TFT_WriteReg(u8 index, u16 data);  //配置ILI9325寄存器的值(寄存器址+寄存器值)
void LCD_TFT_WriteRAM_CMD(void); //向ILI9325写"GRAM命令地址"
void LCD_TFT_WriteRAM(u16 RGB_data);  //向ILI9325写"GRAM数据"



void LCD_TFT_SetWindow(u16 xSta, u16 ySta, u16 xEnd, u16 yEnd);  //设置显示窗口的区域大小(起点和终点)-"彩屏LCD_TFT_ILI9325"  
void LCD_TFT_SetCursor(u16 x, u16 y);  //设置GRAM的光标位置-"彩屏LCD_TFT_ILI9325"  



////////////////////////////////////////////////////////////////////////////
//==**"外部" API 函数声明**Exported  API funcitions**==================//
////////////////////////////////////////////////////////////////////////////
extern void Init_LCD_TFT_ILI9325(void); //"彩屏LCD_TFT_ILI9325" 初使化: 所有相关资源的初始化
extern void Init_GPIO_LCD_TFT_ILI9325(void);  //初始化: "彩屏LCD_TFT_ILI9325"  IO端口
extern void Reset_LCD_TFT_ILI9325(void); //复位"彩屏LCD_TFT_ILI9325"模块
extern void Init_Register_LCD_TFT_ILI9325(void);  //初始化: "彩屏LCD_TFT_ILI9325"  控制芯片的寄存器



extern void LCD_TFT_ClearDisBuf(void);   //显示缓存数组清屏(清屏:送空格20H)-"彩屏LCD_TFT_ILI9325"  

extern void LCD_TFT_Clear(u16 color);   //全屏清屏-"彩屏LCD_TFT_ILI9325"  

extern void LCD_TFT_DrawPoint(u16 x, u16 y, u16 color); //画点( 指定坐标,颜色)-"彩屏LCD_TFT_ILI9325"  

extern void LCD_TFT_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);  //画线-"彩屏LCD_TFT_ILI9325"  

extern void LCD_TFT_DrawRectangle(u16 xSta, u16 ySta, u16 xEnd, u16 yEnd,u16 color);  //画矩形框-"彩屏LCD_TFT_ILI9325"  

extern void LCD_TFT_DrawCircle(u16 x0,u16 y0,u8 r,u16 color);  //画圆-"彩屏LCD_TFT_ILI9325"  


extern void LCD_TFT_FillRectangle(u16 xSta,u16 ySta,u16 xEnd,u16 yEnd,u16 color);  //填充一块LCD矩形区域(指定大小、颜色)-"彩屏LCD_TFT_ILI9325" 


	//显示一个字符( 指定坐标,字体大小,颜色)-"彩屏LCD_TFT_ILI9325"  
extern void LCD_TFT_ShowChar(u16 x,u16 y,u8 AscNum,u8 Font,u16 pointColor,u16 backColor); 
	//显示字符串( 指定坐标,字体大小,颜色)-"彩屏LCD_TFT_ILI9325"  
extern void LCD_TFT_ShowString(u16 line,u16 column,u8 *ArrayPoint,u8 Font,u16 pointColor,u16 backColor); 

	//显示1个24*24的汉字-"彩屏LCD_TFT_ILI9325"  
extern void LCD_TFT_Show_ChFont2424(u16 x,u16 y,u8 index,u16 pointColor,u16 backColor); 




extern void LCD_TFT_Show_StandbyPage(void); //显示"待机页面"-"彩屏LCD_TFT_ILI9325"  
extern void LCD_TFT_Show_WorkPage(void); //显示"工作页面"-"彩屏LCD_TFT_ILI9325"  



extern void Deal_LCD_TFT(void); //显示控制-"彩屏LCD_TFT_ILI9325"  //只更新内容变化的显示部分

extern void Update_LCD_TFT(void);  //更新"内容变化"的显示部分-"彩屏LCD_TFT_ILI9325"  

extern void Update_MonitorLine_LCD_TFT(void);  //更新"监控区""内容变化"的显示部分-"彩屏LCD_TFT_ILI9325"  

extern void Update_MenuLine_LCD_TFT(void);  //更新"菜单区""内容变化"的显示部分-"彩屏LCD_TFT_ILI9325"  

extern void Update_TestLine_LCD_TFT(void); //更新"测试区""内容变化"的显示部分-"彩屏LCD_TFT_ILI9325"  


	//闪烁显示"按键位置(参数值)"--"彩屏LCD_TFT" 
extern void Blink_KeyPlace_Lcd_TFT(unsigned char line,unsigned char column,unsigned char *Array,unsigned char Num);


#endif  //-- __TFT_ILI9325_H --//

