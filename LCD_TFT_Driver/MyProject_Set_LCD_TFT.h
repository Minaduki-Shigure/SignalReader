/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 MyProject_Set_LCD_TFT.h
* �����ļ�-Dependencies:  	 None	
* �ļ�����-File Description:	 ( ͷ�ļ�-Header File )
	�� ������Ŀ: LCD_TFTҺ����ʾ����(�������е�Һ������)-ͷ�ļ�
	01)     02)     03)    04)    05)    06)	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ע������-Attention : 	
	��01)     ��02)     ��03)    ��04)    ��05)    ��06)     
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



#ifndef  __MyProject_Set_LCD_TFT_H 
#define  __MyProject_Set_LCD_TFT_H 






////////////////////////////////////////////////////////////////////////////
//==**"����"�궨��**General macro**==========================//
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
//==**����Ŀ"ר��"�궨��**Project-specific macro**==============//
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"����"�궨��**Functions macro**=========================//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**"��ģ��ר��"��������**Exported Module-specific funcitions**====//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//==**��Ŀ"ר��" API ��������**Exported Project-specific API funcitions**=//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
//--**��ʾ:  "����" �����ʾ**-------------------------------------//
////////////////////////////////////////////////////////////////////////////


extern void Disp_RTC_CurrentTime(void);  //��ʾ: RTC ʵʱʱ��


extern void Disp_INA21x_CurrentValue(unsigned int INA21x_Ad); //��ʾ: INA21x ʵʱ"������ֵ"




////////////////////////////////////////////////////////////////////////////
//---**��ʾ:  "�˵�ѡ��" �����ʾ**------------------------------//
////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////
//--**��ʾ:  "��������" �൱��ʾ**-------------------------------//
////////////////////////////////////////////////////////////////////////////

extern void Disp_MAIN_ModifyTime(void);//��ʾ//Main��"ʵʱʱ��"�޸�״̬
extern void Disp_ModifyTimeState(void); //��ʾʱ���޸Ĺ���
extern void Blink_ModifyTime(void);  //����"ʵʱʱ��"�޸�״̬�µ���˸
extern void Dis_ModifyTimeError(void);  //��ʾ"����: ʱ����������!"




extern void Disp_Set_ScreenSaver(void); //��ʾ"��������"����(LCD)



////////////////////////////////////////////////////////////////////////////
//--**��ʾ:  "����״̬"�µ��൱��ʾ**-------------------------//
////////////////////////////////////////////////////////////////////////////


extern void Disp_01Page_MenuLine(void);  //��ʾ��1ҳ"�����˵�"(LCD)(1.Work_A  2.Work_B  3.Work_C  4.Work_D

extern void Disp_02Page_MenuLine(void);  //��ʾ��2ҳ"�����˵�"(LCD)(1.Work_A  2.Work_B  3.Work_C  4.Work_D




extern void Disp_SelectFlag(void);  //��ʾ"ѡ�б�־"  "=>"


extern void Disp_MAIN_Basic_Settings(void);  //��ʾ//Main��Basic_Settings �˵�ѡ��(����ʱ)

extern void Disp_MAIN_Basic_Check(void);  //��ʾ//Main��Basic_Check �˵�ѡ��(����ʱ)

extern void Disp_MAIN_LCD_TFT_Test(void);  //��ʾ//Main��LCD_TFT_Test �˵�ѡ��(����ʱ)

extern void Disp_MAIN_MatrixKey_Test(void);  //��ʾ//Main��MatrixKey_Test �˵�ѡ��(����ʱ)

extern void Disp_MatrixKey_Press(void); //���ݰ��µ�"���󰴼�"���ڲ���������ʾ"����ֵ"

	
	//��ʾ//Main��TouchPads_Test �˵�ѡ��(����ʱ)
extern void Disp_MAIN_TouchPads_Test(void);  

	//��ʾ//Main��INA21x_Current_Test �˵�ѡ��(����ʱ)
extern void Disp_MAIN_INA21x_Current_Test(void);

	//��"������"��ʾ: INA21x ʵʱ"������ֵ"
extern void Disp_INA21x_Current_InTest(void);


	//��ʾ//Main��Potentiometer_Test �˵�ѡ��(����ʱ)
extern void Disp_MAIN_Potentiometer_Test(void);  
	//��"������"��ʾ: ��λ��Potentiometer ʵʱ"��ѹֵ"
extern void Disp_Potentiometer_InTest(void);


	//��ʾ//Main��NTC_HR202_Test(��ʪ��) �˵�ѡ��(����ʱ)
extern void Disp_MAIN_NTC_HR202_Test(void);

extern void Disp_NTC_TMP(int NTC_TMP_Ad);  //��ʾ: ʵʱ"NTC ��������ֵ"��Ӧ���¶�

extern void Disp_HR202_Humidity(unsigned char humidity); //��ʾ: "HR202_Humidity " ʪ��





	//��ʾ//Main��Step_Motor_Test �˵�ѡ��(����ʱ) 
extern void Disp_MAIN_Step_Motor_Test(void);


	//��ʾ//Main��DC_Motor_Test �˵�ѡ��(����ʱ)  
extern void Disp_MAIN_DC_Motor_Test(void);
	//��"���Ե��"��ʾ�ٶȸ�����ѹֵ: ��λ��Potentiometer ʵʱ"��ѹֵ"
extern void Disp_Potentiometer_Motor(void);
extern void Disp_Speed_Step_Motor(void); //��"����Step_Motor"��ʾ����ٶ�
extern void Disp_Speed_DC_Motor(void); //��"����DC_Motor"��ʾ����ٶ�



	//��ʾ//Main��TMP006_Temperature �˵�ѡ��(����ʱ) 
extern void Disp_MAIN_TMP006_Temperature(void);
extern void Disp_TMP006_Temperature(void); //��LCD_TFT�ϣ���ʾ"�¶�"
extern void Disp_TMP006_TemperatureInTest(void);//��LCD_TFT�ϣ���ʾ"�¶�"

	
	//��ʾ//Main��TMP100_Temperature �˵�ѡ��(����ʱ) 
extern void Disp_MAIN_TMP100_Temperature(void);


extern void Disp_MAIN_IrDA_UART(void); //��ʾ//Main��IrDA_UART �˵�ѡ��(����ʱ)
extern void Disp_IrDA_Test(void); //��ʾIrDA�Ƿ��յ�����



extern void Disp_MAIN_RS232_UART(void); //��ʾ//Main��RS232_UART �˵�ѡ��(����ʱ)
extern void Disp_RS232_Char_1(void); //��ʾRS485�յ�����"1" (�ַ�)	
extern void Disp_RS232_Char_2(void); //��ʾRS485�յ�����"2" (�ַ�)	
extern void Disp_RS232_None(void); //����ʾRS232�յ�����


extern void Disp_MAIN_RS485_UART(void); //��ʾ//Main��RS485_UART �˵�ѡ��(����ʱ)
extern void Disp_RS485_Char_1(void); //��ʾRS485�յ�����"1" (�ַ�)	
extern void Disp_RS485_Char_2(void); //��ʾRS485�յ�����"2" (�ַ�)	



extern void Disp_MAIN_CC1101_Test(void); //��ʾ//Main��CC1101_Test �˵�ѡ��(����ʱ)
extern void Disp_CC1101_Char_1(void); //��ʾCC1101�յ�����"1" (�ַ�)	
extern void Disp_CC1101_Char_2(void); //��ʾCC1101�յ�����"2" (�ַ�)		




extern void Disp_MAIN_SD_Card_Test(void);  //��ʾ//Main��SD_Card_Test �˵�ѡ��(����ʱ)
extern void Disp_SD_Card_Char(void); //��ʾSD_Card���������� (�ַ�)		


extern void Disp_MAIN_MassStorage_Test(void); //��ʾ//Main��MassStorage_Test �˵�ѡ��(����ʱ)

#endif   /* __MyProject_Set_LCD_TFT_H  */





