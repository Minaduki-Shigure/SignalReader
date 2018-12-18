/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 BQ27410_FuelGauge.c
* �����ļ�-Dependencies:  	 BQ27410_FuelGauge.h; Hardware_Profile.h; Generic.h; I2C.h; System.h; MyProject_Set_LCD_TFT.h;LCD_Segment.h; LCD_TFT_ILI9325.h;
* �ļ�����-File Description:	 ( Դ����-Source File) 
	��"BQ27410_FuelGauge ﮵�ص�������"-��������(�ⲿ��Դ)
	01)I2C  ������ϵͳ΢��������, ����ֱ�ӵ�����ӹ��ܵ�ϵͳ��������
	02) ���ṩʣ��������(mAh)�����״̬(%)����ص�ѹ(mV) ����Ϣ��
	03) ������1-Series LiCoO2 ���Ӧ�õĵ�ص�������
	04)���ڻ�ר��Impedance Track? �����������õ�ص������
	05)	������LDO ʹ������ֱ��ͨ������鹩,�����Ƕ��ʽ��ɲ�ж����鹤��
	06)�ɸ��ݵ���ϻ�������Էŵ��Լ��¶ȣ����ʵĵ�Ч�ʽ����Զ�����
	07)΢�����������ṩ��
		�C ׼ȷ�ĵ�ص������
		�C ֧�ֵ���¶ȱ�����ڲ��¶ȴ�����
		�C �����ó��״̬(SOC) �жϼ�   
	08)Ӧ��
		�C ���ܵ绰
		�C PDA
		�C ������������������
		�C �ֳ��ն��豸
		�C MP3 ���ý�岥����

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ע������-Attention : 	
	��01)
 	��02) 	��03)	��04)    ��05)    ��06)     
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  
* �޸ļ�¼-Change History:   
	����   ʱ��        �汾  ��������
	Author 	 Date		   Rev      Comment
	-------------------------------------------------------------------------------
	BlueS	2013-09-25	  1.0	   
			xxxx-xx-xx	  x.x	   
			xxxx-xx-xx	  x.x				
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
* ��˾-Company: 			CS-EMLAB  Co. , Ltd.
* ������Э��-Software License Agreement:
	Copyright (C) 2012-2020 	CS-EMLAB  Co. , Ltd.	All rights reserved.	

*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/


#include "Generic.h"	//���ó����̹淶�������� -ͷ�ļ�-Generic Type Definitions

#include "Hardware_Profile.h"  //������"Ӳ�������ļ�" -Hardware specific definitions for Processor


#include "BQ27410_FuelGauge.h"   //"BQ27410_FuelGauge ﮵�ص�������"-��������(�ⲿ��Դ)-ͷ�ļ�


#include "I2C.h"   //"I2C" -��������-ͷ�ļ�(�������ڲ���Դ) 

#include "System.h"	 //"ϵͳ" ���ù��ܺ�����-ͷ�ļ�
	//������Ŀ: LCD_TFTҺ����ʾ����(�������е�Һ������) -ͷ�ļ�
#include "MyProject_Set_LCD_TFT.h"  

#include "LCD_Segment.h" // "��ʽLCD_Segment"  -��������(�ⲿ��Դ)-ͷ�ļ�

#include "LCD_TFT_ILI9325.h"  // "����LCD_TFT_ILI9325" -��������(�ⲿ��Դ) -ͷ�ļ�



	#include "LED_Segment.h" //"��̬�����LED_Segment" -��������(�ⲿ��Դ)-ͷ�ļ�
	#include "TM1638.h"  // "TM1638 �����������" -��������(�ⲿ��Դ) -ͷ�ļ�
	#include "MatrixKey.h"   //"���󰴼�" -��������(�ⲿ��Դ)-ͷ�ļ�



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
u16 BQ27410_Charge = 0;  //BQ27410 ������﮵�ص���ֵ
u8 BQ27410_ChargeKind = 0;  //BQ27410 ������﮵�ص���ֵ�ļ���


////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////


/****************************************************************************
*������-Function:	void Initial_BQ27410_FuelGauge(void)
*����- Description:		��ʼ��BQ27410������:  IIC_B����,�����л���IIC����
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)    ��04)  
*****************************************************************************/
void Initial_BQ27410_FuelGauge(void)  //��ʼ��BQ27410������:  IIC_B����,�����л���IIC����
{
	mSPI_All_Disable;//����LCD_segment��IIC(TMP006)ʱ��Ҫ���������õ�SPI_B��ģ��



////////////////////////////////////////////////////////////////////////////
//==**����"Bģ��"��·������TS3A5017: ѡ��IN2 ��IN1**=========//
		//IN2=0; IN1=0; ��ӦI2C_B ����(I2C_SCK_B; I2C_SDA_B)
	mConfig_TS3A5017_B_IN2(0);  //IN2 =0
	mConfig_TS3A5017_B_IN1(0);  //IN1 =0	 //ѡ��s1

////////////////////////////////////////////////////////////////////////////
//==**����IIC_B**============================================//
	I2C_B_Initial(ADDR_SLAVE_BQ27410);  //I2C_B �ڲ���Դ��ʼ��

}


/****************************************************************************
*������-Function:	void Sample_BQ27410_FuelGauge(void)
*����- Description: 	BQ27410 ����﮵�صĵ���
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)		��02)	 ��03)	  ��04)  
*****************************************************************************/
void Sample_BQ27410_FuelGauge(void)  //BQ27410 ����﮵�صĵ���
{
	u16 temp = 0;  

////////////////////////////////////////////////////////////////////////////
//==**����һ��BQ27410 ������**==============================//
	Initial_BQ27410_FuelGauge();  //��ʼ��BQ27410������:  IIC_B����,�����л���IIC����
		//��BQ27410��0x00��ַ,д��һ����(0x000C)
	Write_Word_IIC_B(0x00,0x0C,0x00); //ͨ��IIC_B ��ӻ���ĳ���Ĵ���дһ����
	
	Initial_BQ27410_FuelGauge();  //��ʼ��BQ27410������:  IIC_B����,�����л���IIC����
	temp = Read_Word_IIC_B(ADDR_Charge_BQ27410);//����BQ27410������ ����ֵ,��ת��Ϊ"ʵ�� ����ֵ"

	
	BQ27410_Charge = (temp << 8) & 0xFF00;
	BQ27410_Charge +=(temp >> 8) & 0x00FF;

		//900mAh��﮵�س������BQ27410�Ĳ���ֵΪ1240����õ�ѹ4.15V
		//900mAh��﮵�ط�����BQ27410�Ĳ���ֵΪ0000����õ�ѹ3.44V
		//����ȡ1230Ϊ��Ӧ�����ֵ900mAh,��֮��ı���n=1230/900=1.366667
	BQ27410_Charge = (unsigned int)(BQ27410_Charge / 1.366667);  //ת��Ϊ0--900mAH ��Χ�ĵ���
	if(BQ27410_Charge >= 900)  BQ27410_Charge = 900;

///////////////////////////////////////////////////
		//����=  0  //û��//��������
	if(BQ27410_Charge == 0) BQ27410_ChargeKind = CHARGE_0_BQ27410; 
		//0<����<= 9%  //����//��������
	if((BQ27410_Charge > 0)&&(BQ27410_Charge < 90)) BQ27410_ChargeKind = CHARGE_0_9_BQ27410;    
		//10%<=����<= 33%  //��������
	if((BQ27410_Charge >= 90)&&(BQ27410_Charge < 306)) BQ27410_ChargeKind = CHARGE_10_33_BQ27410;   
		//34%<=����<= 66%  //��������
	if((BQ27410_Charge >= 306)&&(BQ27410_Charge < 603)) BQ27410_ChargeKind = CHARGE_34_66_BQ27410;  
		//67%<=����<= 99%  //��������
	if((BQ27410_Charge >= 603)&&(BQ27410_Charge < 900)) BQ27410_ChargeKind = CHARGE_67_99_BQ27410;  
		//����= 100%  //������//��������
	if(BQ27410_Charge >= 900) BQ27410_ChargeKind = CHARGE_100_BQ27410; 
	
}
	





/****************************************************************************
*������-Function:	void Deal_BQ27410_FuelGauge(void)
*����- Description: 	����BQ27410 ������
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)		��02)	 ��03)	  ��04)  
*****************************************************************************/
void Deal_BQ27410_FuelGauge(void)  //����BQ27410 ������
{
////////////////////////////////////////////////////////////////////////////
//==**ϵͳÿ1s ��ȡ"ʵʱBQ27410������ ����ֵ"**====================//
	if(F_1s_BQ27410)	//ϵͳÿ500ms ��ȡ"ʵʱBQ27410������ ����ֵ"
	{
		F_1s_BQ27410 = 0;

Sample_BQ27410_FuelGauge();  //BQ27410 ����﮵�صĵ���

//Display_BQ27410_LED_Segment();  //�����LCD����ʾBQ27410 �����õ��ĵ���ֵ
		F_Update_Power = YES; //ˢ��:"﮵�ص�ʵʱ����"  (Ϊ1ʱ)

	//_delay_ms(100);
	}
}
	

/****************************************************************************
*������-Function:	void Display_BQ27410_LCD_Segment(void)
*����- Description: 	�ڶ�ʽLCD����ʾBQ27410 �����õ��ĵ���ֵ
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)		��02)	 ��03)	  ��04)  
*****************************************************************************/
void Display_BQ27410_LCD_Segment(void)  //�ڶ�ʽLCD����ʾBQ27410 �����õ��ĵ���ֵ
{
	u8 s1,s2,s3;
	u8 chargeKind = 0;
	u8 flag02 = DISP_OFF_LcdSeg; //��ʾ"����"
	u8 flag01 = DISP_OFF_LcdSeg; //��ʾ"����"


	flag02 = (unsigned char)((BQ27410_Charge/9)/10);  //��ʾ��ǰ������ռ��(ʮλ)
	flag01 = (unsigned char)((BQ27410_Charge/9)%10);  //��ʾ��ǰ������ռ��(��λ)



	s3 = (unsigned char)(BQ27410_Charge/100);
	s2 = (unsigned char)((BQ27410_Charge % 100)/10);
	s1 = (unsigned char)(BQ27410_Charge % 10);

	if((s3 == 0)&&(s2 == 0)) s2 = DISP_OFF_LcdSeg;
	if(s3 == 0) s3 = DISP_OFF_LcdSeg; //��ʾ"����"
	

	switch(BQ27410_ChargeKind) 
	{
		case CHARGE_0_BQ27410:	//����=  0  //û��//��������
			chargeKind = 0;    //"0"��ʾ����ʾ��ط���
			flag02 = DISP_0_LcdSeg;  //��ʾ"0" :��ʾ�����û��
			flag01 = DISP_0_LcdSeg;  //��ʾ"0" :��ʾ�����û��

			s3 = DISP_0_LcdSeg; //��ʾ"0"
			s2 = DISP_0_LcdSeg; //��ʾ"0"
			s1 = DISP_0_LcdSeg; //��ʾ"0"
			break;	
			
		case CHARGE_0_9_BQ27410: //0<����<= 9%  //����//��������
			if(F_250ms_Turn)	//��û��,������˸"1 ���+��ؿ�"
			{
				chargeKind = 4;    //"4"��ʾ��ʾ"1 ���+��ؿ�"
				flag01 = (unsigned char)((BQ27410_Charge/9)%10);  //��ʾ��ǰ������ռ��(��λ)
			}
			else
			{
				chargeKind = 0;    //"0"��ʾ����ʾ��ط���
				flag01 = DISP_OFF_LcdSeg;  //��ʾ"����"
			}
			flag02 = DISP_OFF_LcdSeg;  //��ʾ"����"
			break;	
			
		case CHARGE_10_33_BQ27410: //10%<=����<= 33%  //��������
			chargeKind = 4;    //"4"��ʾ��ʾ"1 ���+��ؿ�"
			break;	
			
		case CHARGE_34_66_BQ27410: //34%<=����<= 66%  //��������
			chargeKind = 5;    //"5"��ʾ��ʾ"2 ���+��ؿ�"
			break;	
			
		case CHARGE_67_99_BQ27410: //67%<=����<= 99%  //��������
			chargeKind = 6;    //"6"��ʾ��ʾ"3 ���+��ؿ�"
			break;	
			
		case CHARGE_100_BQ27410: //����= 100%  //������//��������
			chargeKind = 6;    //"6"��ʾ��ʾ"3 ���+��ؿ�"
			flag02 = DISP_F_LcdSeg;  //��ʾ"F" :��ʾ�������
			flag01 = DISP_F_LcdSeg;  //��ʾ"F" :��ʾ�������
			break;	

		default:	break;
	}

	Disp_LCD_Segment(chargeKind,flag02,flag01,DISP_OFF_LcdSeg,s3,s2,s1);
	mOpen_LCD_SEG_BackLight; //��������Ϊ"���",��"��"LCD_Segment ����
	
}
	


/****************************************************************************
*������-Function:	void Disp_BQ27410_FuelGauge(void)
*����- Description:		��LCD_TFT�ϣ���ʾ"﮵��":״̬+����
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    ��02)    ��03)    ��04)  
*****************************************************************************/
void Disp_BQ27410_FuelGauge(void)//��LCD_TFT�ϣ���ʾ"﮵��":״̬+����
{	
	
switch(BQ27410_ChargeKind) 
{
	case CHARGE_0_BQ27410:	//����=  0  //û��//��������
			//"�������"
		LCD_TFT_DrawRectangle(M_15Line,M_37Column,M_15Line+13,M_40Column+2,RED); 
		LCD_TFT_DrawRectangle(M_15Line+4,M_40Column+2,M_15Line+9,M_40Column+5,RED); 
			//"����ֵ"--��ߵ�01��������
		LCD_TFT_FillRectangle(M_15Line+2,M_37Column+2,M_15Line+11,M_37Column+7,Monitor_Back);
			//"����ֵ"--��ߵ�02��������
		LCD_TFT_FillRectangle(M_15Line+2,M_38Column+2,M_15Line+11,M_38Column+7,Monitor_Back);
			//"����ֵ"--��ߵ�03��������
		LCD_TFT_FillRectangle(M_15Line+2,M_39Column+2,M_15Line+11,M_39Column+7,Monitor_Back);
		break;	
		
	case CHARGE_0_9_BQ27410: //0<����<= 9%  //����//��������
			//"�������"
		LCD_TFT_DrawRectangle(M_15Line,M_37Column,M_15Line+13,M_40Column+2,Monitor_Point); 
		LCD_TFT_DrawRectangle(M_15Line+4,M_40Column+2,M_15Line+9,M_40Column+5,Monitor_Point); 
			//"����ֵ"--��ߵ�01��������
		LCD_TFT_FillRectangle(M_15Line+2,M_37Column+2,M_15Line+11,M_37Column+7,RED);
			//"����ֵ"--��ߵ�02��������
		LCD_TFT_FillRectangle(M_15Line+2,M_38Column+2,M_15Line+11,M_38Column+7,Monitor_Back);
			//"����ֵ"--��ߵ�03��������
		LCD_TFT_FillRectangle(M_15Line+2,M_39Column+2,M_15Line+11,M_39Column+7,Monitor_Back);
		break;	
		
	case CHARGE_10_33_BQ27410: //10%<=����<= 33%  //��������
			//"�������"
		LCD_TFT_DrawRectangle(M_15Line,M_37Column,M_15Line+13,M_40Column+2,Monitor_Point); 
		LCD_TFT_DrawRectangle(M_15Line+4,M_40Column+2,M_15Line+9,M_40Column+5,Monitor_Point); 
			//"����ֵ"--��ߵ�01��������
		LCD_TFT_FillRectangle(M_15Line+2,M_37Column+2,M_15Line+11,M_37Column+7,Monitor_Point);
			//"����ֵ"--��ߵ�02��������
		LCD_TFT_FillRectangle(M_15Line+2,M_38Column+2,M_15Line+11,M_38Column+7,Monitor_Back);
			//"����ֵ"--��ߵ�03��������
		LCD_TFT_FillRectangle(M_15Line+2,M_39Column+2,M_15Line+11,M_39Column+7,Monitor_Back);
		break;	
		
	case CHARGE_34_66_BQ27410: //34%<=����<= 66%  //��������
			//"�������"
		LCD_TFT_DrawRectangle(M_15Line,M_37Column,M_15Line+13,M_40Column+2,Monitor_Point); 
		LCD_TFT_DrawRectangle(M_15Line+4,M_40Column+2,M_15Line+9,M_40Column+5,Monitor_Point); 
			//"����ֵ"--��ߵ�01��������
		LCD_TFT_FillRectangle(M_15Line+2,M_37Column+2,M_15Line+11,M_37Column+7,Monitor_Point);
			//"����ֵ"--��ߵ�02��������
		LCD_TFT_FillRectangle(M_15Line+2,M_38Column+2,M_15Line+11,M_38Column+7,Monitor_Point);
			//"����ֵ"--��ߵ�03��������
		LCD_TFT_FillRectangle(M_15Line+2,M_39Column+2,M_15Line+11,M_39Column+7,Monitor_Back);

		break;	
		
	case CHARGE_67_99_BQ27410: //67%<=����<= 99%  //��������
			//"�������"
		LCD_TFT_DrawRectangle(M_15Line,M_37Column,M_15Line+13,M_40Column+2,Monitor_Point); 
		LCD_TFT_DrawRectangle(M_15Line+4,M_40Column+2,M_15Line+9,M_40Column+5,Monitor_Point); 
			//"����ֵ"--��ߵ�01��������
		LCD_TFT_FillRectangle(M_15Line+2,M_37Column+2,M_15Line+11,M_37Column+7,Monitor_Point);
			//"����ֵ"--��ߵ�02��������
		LCD_TFT_FillRectangle(M_15Line+2,M_38Column+2,M_15Line+11,M_38Column+7,Monitor_Point);
			//"����ֵ"--��ߵ�03��������
		LCD_TFT_FillRectangle(M_15Line+2,M_39Column+2,M_15Line+11,M_39Column+7,Monitor_Point);
		break;	
		
	case CHARGE_100_BQ27410: //����= 100%  //������//��������
			//"�������"
		LCD_TFT_DrawRectangle(M_15Line,M_37Column,M_15Line+13,M_40Column+2,Fixed_Point); 
		LCD_TFT_DrawRectangle(M_15Line+4,M_40Column+2,M_15Line+9,M_40Column+5,Fixed_Point); 
			//"����ֵ"--��ߵ�01��������
		LCD_TFT_FillRectangle(M_15Line+2,M_37Column+2,M_15Line+11,M_37Column+7,Fixed_Point);
			//"����ֵ"--��ߵ�02��������
		LCD_TFT_FillRectangle(M_15Line+2,M_38Column+2,M_15Line+11,M_38Column+7,Fixed_Point);
			//"����ֵ"--��ߵ�03��������
		LCD_TFT_FillRectangle(M_15Line+2,M_39Column+2,M_15Line+11,M_39Column+7,Fixed_Point);

		break;	

	default:	break;
}

	
}


/****************************************************************************
*������-Function:	void Display_BQ27410_LED_Segment(void)
*����- Description: 	�������LED����ʾBQ27410 �����õ��ĵ���ֵ
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)		��02)	 ��03)	  ��04)  
*****************************************************************************/
void Display_BQ27410_LED_Segment(void)  //�����LCD����ʾBQ27410 �����õ��ĵ���ֵ
{
	u8 s1,s2,s3;
	u8 chargeKind = 0;
	u8 flag02 = DISP_OFF_LedSeg; //��ʾ"����"
	u8 flag01 = DISP_OFF_LedSeg; //��ʾ"����"


	flag02 = (unsigned char)((BQ27410_Charge/9)/10);  //��ʾ��ǰ������ռ��(ʮλ)
	flag01 = (unsigned char)((BQ27410_Charge/9)%10);  //��ʾ��ǰ������ռ��(��λ)



	s3 = (unsigned char)(BQ27410_Charge/100);
	s2 = (unsigned char)((BQ27410_Charge % 100)/10);
	s1 = (unsigned char)(BQ27410_Charge % 10);

	if((s3 == 0)&&(s2 == 0)) s2 = DISP_OFF_LcdSeg;
	if(s3 == 0) s3 = DISP_OFF_LcdSeg; //��ʾ"����"
	

	switch(BQ27410_ChargeKind) 
	{
		case CHARGE_0_BQ27410:	//����=  0  //û��//��������
			chargeKind = 0;   
			flag02 = DISP_0_LcdSeg;  //��ʾ"0" :��ʾ�����û��
			flag01 = DISP_0_LcdSeg;  //��ʾ"0" :��ʾ�����û��

			s3 = DISP_0_LcdSeg; //��ʾ"0"
			s2 = DISP_0_LcdSeg; //��ʾ"0"
			s1 = DISP_0_LcdSeg; //��ʾ"0"
			break;	
			
		case CHARGE_0_9_BQ27410: //0<����<= 9%  //����//��������
			chargeKind = 1;   
			break;	
			
		case CHARGE_10_33_BQ27410: //10%<=����<= 33%  //��������
			chargeKind = 2;    
			break;	
			
		case CHARGE_34_66_BQ27410: //34%<=����<= 66%  //��������
			chargeKind = 3;   
			break;	
			
		case CHARGE_67_99_BQ27410: //67%<=����<= 99%  //��������
			chargeKind = 4;    
			break;	
			
		case CHARGE_100_BQ27410: //����= 100%  //������//��������
			chargeKind = 5;    
			flag02 = DISP_F_LedSeg;  //��ʾ"F" :��ʾ�������
			flag01 = DISP_F_LedSeg;  //��ʾ"F" :��ʾ�������
			break;	

		default:	break;
	}


	Disp_LED_Segment(0,0,flag02,flag01,DISP_OFF_LedSeg,chargeKind,DISP_OFF_LedSeg,s3,s2,s1);

	
}
	

