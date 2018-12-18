/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* �ļ���-FileName:			 CC1101.c
* �����ļ�-Dependencies:  	 CC1101.h; Hardware_Profile.h; Generic.h;
* �ļ�����-File Description:	 ( Դ����-Source File) 
	��"CC1101 �͹�����Ƶ�շ���"-��������(�ⲿ��Դ)
	01)CC1101 �͹��ģ����� 1GHz����Ƶ�շ���_Low-Power Sub-1 GHz RF Transceiver  
	02) CC1101��һ�����1GHz��������Ƶ�շ��������ּ������
���͹���RFӦ�á�����Ҫ��Թ�ҵ�����к�ҽ��(ISM)�Լ�
�̾�������ͨ���豸(SRD)��CC1101���ṩ�����ݰ���������
���塢ͻ�����䡢�����ź�ǿ��ָʾ(RSSI)�������ŵ�����(CCA)��
��·����ָʾ�Լ����߻���(WOR)�Ĺ㷺Ӳ��֧�֡�CC1101��
���롢��װ�������ŷ������CC1100���ݣ�������ȫ����Ϊ����
�Ŀ���ʽ����1GHzƵ�ʵ�RF��ơ�
	03) CC1101оƬ�� Chipcon���ѱ� TI�չ����Ƴ���һ��ͳɱ���Ƭ��Ƶ
�� UHF�շ�������ҪӦ���ڵ͹�������Ӧ����ơ�
	04)��оƬ��·��Ҫ�趨Ϊ�� 315��433��868 �� 915MHz �� ISM
����ҵ����ѧ��ҽѧ��,������һ������ɱ�̵ĵ��ƽ������
	05)	Ӧ������:
		�񳬵͹��������շ��� �����ߴ������� 
		���ͥ��¥���Զ���       ��߼�����ܹ�(AMI) 
		�����߼���                              �����߱�����ȫϵͳ
	06)	���ܲ���:
��387.0MHz��464.0MHz����Ƶ�Ρ�
���������(433MHz��0.6kbps��1%������ʱΪ-116dBm)��
��͵�������(����ģʽ��433MHz��1.2kbpsʱ��16.0mA)��
����߿�����Ϊ+10dBm�ķ��书�ʡ�
��֧��0.6kbps��500kbps�����ݴ������ʣ����ݴ�������߿ɴ� 500kbps��
��֧�ֶ��ֵ���ģʽ(OOK��ASK��GFSK��2-FSK��4-FSK��MSK)��
���ṩ��ͬ���ּ�⡢��ַУ�顢�������ݰ������Լ��Զ�CRC�����֧�֡�
��֧��RSSI(�����ź�ǿ��ָʾ)��LQI(��·����ָʾ)��
��ͨ��4��SPI�ӿ���MCU���ӣ�ͬʱ�ṩ2�����趨���ܵ�ͨ������������š�
�������64�ֽ�RXFIFO��TX FIFO��
������ѹ��Χ��1.9V��3.6V������ģʽ�µ�����Ϊ200nA��
�����¶ȷ�Χ��-40�桫+85��	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ע������-Attention : 	
	��01)SIP �ӿڵĴ���ģʽ������ģʽ�Լ����յȹ���ģʽ��ͨ�� 
SPI ָ��������á�
	��02)����ͨ�� GDO0 �� GDO2 ���Ÿߵ͵�ƽ״̬���ж����ݵķ���
������Ƿ���ɡ� 
	��03)P8SEL &= ~0X0C;  //care һ��Ҫ��������䣬��Ȼ����UART��ͻ
	��04)    ��05)    ��06)     
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


#include "Generic.h"	//���ó����̹淶�������� -ͷ�ļ�-Generic Type Definitions

#include "Hardware_Profile.h"  //������"Ӳ�������ļ�" -Hardware specific definitions for Processor


#include "CC1101.h"   //"CC1101 �͹�����Ƶ�շ���"-��������(�ⲿ��Դ)-ͷ�ļ�



////////////////////////////////////////////////////////////////////////////
//==**ȫ�ֱ�������**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned char G_RxData_CC1101 = 0xFF;  //���� "RS485_UART   ����ͨ��"���յ�������


////////////////////////////////////////////////////////////////////////////
//==**�ֲ���������**Local variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned char TxBuf[8]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};//8�ֽ�, �����Ҫ���������ݰ�,����ȷ����
unsigned char RxBuf[8]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};


/*
IN1            P3.4 --->> TS3A5017DR PIN_IN1
IN2            P3.5 --->> TS3A5017DR PIN_IN2
5017_4_IN1 ?   P4.5 --->> TS3A5017DR PIN_IN1
5017_4_IN2 ?   P4.4 --->> TS3A5017DR PIN_IN2

CSN            P5.2 --->> CC1101 --SPI_CS
SPI_MOSI_A     P8.2 --->> CC1101 --SPI_MOSI_A
SPI_MISO_A1 ?  P8.3 --->> CC1101 --SPI_MISO_A1
CLK_A          P8.1 --->> CC1101 --CLK
GDO0           P1.2 --->> CC1101 --GDO0
GDO2           P6.4 --->> CC1101 --GDO2
*/


//#define CPU_F ((double)20000000)
//#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
//#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))


#define		INT8U		unsigned char
#define		INT16U		unsigned int

#define 	WRITE_BURST     	0x40						//����д��
#define 	READ_SINGLE     	0x80						//��
#define 	READ_BURST      	0xC0						//������
#define 	BYTES_IN_RXFIFO     0x7F  						//���ջ���������Ч�ֽ���
#define 	CRC_OK              0x80 						//CRCУ��ͨ��λ��־
//*****************************************************************************************

#define CSN         	    BIT1    //PJ.1--->>CSN
#define SPI_MOSI_A          BIT5	//P8.5--->>SPI_MOSI_A  //V3.0ΪSPI_B
//#define SPI_MISO_A1         BIT6	//P8.6--->>SPI_MISO_A1
#define CLK_A               BIT4	//P8.4--->>CLA_A
//#define GDO0     	        BIT3	//PJ.3--->>GD00
//#define GDO2     	        BIT2	//PJ.2--->>GD02

//���ƿ���1�������궨��
#define	CSN_SET  	        PJOUT |= CSN
#define	SPI_MOSI_A_SET  	P8OUT |= SPI_MOSI_A
//#define	SPI_MISO_A1_SET  	P8OUT |= SPI_MISO_A1
#define	CLK_A_SET  	        P8OUT |= CLK_A
//#define	GDO0_SET  	        PJOUT |= GDO0
//#define	GDO2_SET  	        PJOUT |= GDO2

//���ƿ���0�������궨��
#define	CSN_CLR  	        PJOUT &= ~CSN
#define	SPI_MOSI_A_CLR  	P8OUT &= ~SPI_MOSI_A
//#define	SPI_MISO_A1_CLR  	P8OUT &= ~SPI_MISO_A1
#define	CLK_A_CLR  	        P8OUT &= ~CLK_A
//#define	GDO0_CLR  	        PJOUT &= ~GDO0
//#define	GDO2_CLR         	PJOUT &= ~GDO2

#define MISO                P8DIR &= ~BIT6       //MISO
#define GDO0                PJDIR &= ~BIT3       //GDO0
#define GDO2                PJDIR &= ~BIT2       //GDO2

//#define 	GDO0	=P1^0;
//#define 	GDO2	=P1^1;
//#define	MISO	=P1^6;
//#define	MOSI	=P1^7;
//#define	SCK		=P1^2;
//#define 	CSN		=P1^5;


////----------------------------------------�����˿�-------------------------------------------------------
//#define	  KEY     =P3^4;
////----------------------------------------LED��ʾ�˿�---------------------------------------------------
//#define     LED     =P3^5;



//***************���๦�ʲ������ÿ���ϸ�ο�DATACC1100Ӣ���ĵ��е�48-49ҳ�Ĳ�����******************
//INT8U PaTabel[8] = {0x04 ,0x04 ,0x04 ,0x04 ,0x04 ,0x04 ,0x04 ,0x04};  //-30dBm   ������С
unsigned char PaTabel[8] = {0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60};  //0dBm
//INT8U PaTabel[8] = {0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0};   //10dBm     �������
//*****************************************************************************************
void SpiInit(void);
void CpuInit(void);
void RESET_CC1100(void);
void POWER_UP_RESET_CC1100(void);
void halSpiWriteReg(INT8U addr, INT8U value);
void halSpiWriteBurstReg(INT8U addr, INT8U *buffer, INT8U count);
void halSpiStrobe(INT8U strobe);
INT8U halSpiReadReg(INT8U addr);
void halSpiReadBurstReg(INT8U addr, INT8U *buffer, INT8U count);
INT8U halSpiReadStatus(INT8U addr);
void halRfWriteRfSettings(void);
void halRfSendPacket(INT8U *txBuffer, INT8U size); 
INT8U halRfReceivePacket(INT8U *rxBuffer, INT8U *length);  
//*****************************************************************************************
// CC1100 STROBE, CONTROL AND STATUS REGSITER
#define CCxxx0_IOCFG2       0x00        // GDO2 output pin configuration
#define CCxxx0_IOCFG1       0x01        // GDO1 output pin configuration
#define CCxxx0_IOCFG0       0x02        // GDO0 output pin configuration
#define CCxxx0_FIFOTHR      0x03        // RX FIFO and TX FIFO thresholds
#define CCxxx0_SYNC1        0x04        // Sync word, high INT8U
#define CCxxx0_SYNC0        0x05        // Sync word, low INT8U
#define CCxxx0_PKTLEN       0x06        // Packet length
#define CCxxx0_PKTCTRL1     0x07        // Packet automation control
#define CCxxx0_PKTCTRL0     0x08        // Packet automation control
#define CCxxx0_ADDR         0x09        // Device address
#define CCxxx0_CHANNR       0x0A        // Channel number
#define CCxxx0_FSCTRL1      0x0B        // Frequency synthesizer control
#define CCxxx0_FSCTRL0      0x0C        // Frequency synthesizer control
#define CCxxx0_FREQ2        0x0D        // Frequency control word, high INT8U
#define CCxxx0_FREQ1        0x0E        // Frequency control word, middle INT8U
#define CCxxx0_FREQ0        0x0F        // Frequency control word, low INT8U
#define CCxxx0_MDMCFG4      0x10        // Modem configuration
#define CCxxx0_MDMCFG3      0x11        // Modem configuration
#define CCxxx0_MDMCFG2      0x12        // Modem configuration
#define CCxxx0_MDMCFG1      0x13        // Modem configuration
#define CCxxx0_MDMCFG0      0x14        // Modem configuration
#define CCxxx0_DEVIATN      0x15        // Modem deviation setting
#define CCxxx0_MCSM2        0x16        // Main Radio Control State Machine configuration
#define CCxxx0_MCSM1        0x17        // Main Radio Control State Machine configuration
#define CCxxx0_MCSM0        0x18        // Main Radio Control State Machine configuration
#define CCxxx0_FOCCFG       0x19        // Frequency Offset Compensation configuration
#define CCxxx0_BSCFG        0x1A        // Bit Synchronization configuration
#define CCxxx0_AGCCTRL2     0x1B        // AGC control
#define CCxxx0_AGCCTRL1     0x1C        // AGC control
#define CCxxx0_AGCCTRL0     0x1D        // AGC control
#define CCxxx0_WOREVT1      0x1E        // High INT8U Event 0 timeout
#define CCxxx0_WOREVT0      0x1F        // Low INT8U Event 0 timeout
#define CCxxx0_WORCTRL      0x20        // Wake On Radio control
#define CCxxx0_FREND1       0x21        // Front end RX configuration
#define CCxxx0_FREND0       0x22        // Front end TX configuration
#define CCxxx0_FSCAL3       0x23        // Frequency synthesizer calibration
#define CCxxx0_FSCAL2       0x24        // Frequency synthesizer calibration
#define CCxxx0_FSCAL1       0x25        // Frequency synthesizer calibration
#define CCxxx0_FSCAL0       0x26        // Frequency synthesizer calibration
#define CCxxx0_RCCTRL1      0x27        // RC oscillator configuration
#define CCxxx0_RCCTRL0      0x28        // RC oscillator configuration
#define CCxxx0_FSTEST       0x29        // Frequency synthesizer calibration control
#define CCxxx0_PTEST        0x2A        // Production test
#define CCxxx0_AGCTEST      0x2B        // AGC test
#define CCxxx0_TEST2        0x2C        // Various test settings
#define CCxxx0_TEST1        0x2D        // Various test settings
#define CCxxx0_TEST0        0x2E        // Various test settings

// Strobe commands
#define CCxxx0_SRES         0x30        // Reset chip.
#define CCxxx0_SFSTXON      0x31        // Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL=1).
                                        // If in RX/TX: Go to a wait state where only the synthesizer is
                                        // running (for quick RX / TX turnaround).
#define CCxxx0_SXOFF        0x32        // Turn off crystal oscillator.
#define CCxxx0_SCAL         0x33        // Calibrate frequency synthesizer and turn it off
                                        // (enables quick start).
#define CCxxx0_SRX          0x34        // Enable RX. Perform calibration first if coming from IDLE and
                                        // MCSM0.FS_AUTOCAL=1.
#define CCxxx0_STX          0x35        // In IDLE state: Enable TX. Perform calibration first if
                                        // MCSM0.FS_AUTOCAL=1. If in RX state and CCA is enabled:
                                        // Only go to TX if channel is clear.
#define CCxxx0_SIDLE        0x36        // Exit RX / TX, turn off frequency synthesizer and exit
                                        // Wake-On-Radio mode if applicable.
#define CCxxx0_SAFC         0x37        // Perform AFC adjustment of the frequency synthesizer
#define CCxxx0_SWOR         0x38        // Start automatic RX polling sequence (Wake-on-Radio)
#define CCxxx0_SPWD         0x39        // Enter power down mode when CSn goes high.
#define CCxxx0_SFRX         0x3A        // Flush the RX FIFO buffer.
#define CCxxx0_SFTX         0x3B        // Flush the TX FIFO buffer.
#define CCxxx0_SWORRST      0x3C        // Reset real time clock.
#define CCxxx0_SNOP         0x3D        // No operation. May be used to pad strobe commands to two
                                        // INT8Us for simpler software.

#define CCxxx0_PARTNUM      0x30
#define CCxxx0_VERSION      0x31
#define CCxxx0_FREQEST      0x32
#define CCxxx0_LQI          0x33
#define CCxxx0_RSSI         0x34
#define CCxxx0_MARCSTATE    0x35
#define CCxxx0_WORTIME1     0x36
#define CCxxx0_WORTIME0     0x37
#define CCxxx0_PKTSTATUS    0x38
#define CCxxx0_VCO_VC_DAC   0x39
#define CCxxx0_TXBYTES      0x3A
#define CCxxx0_RXBYTES      0x3B

#define CCxxx0_PATABLE      0x3E
#define CCxxx0_TXFIFO       0x3F
#define CCxxx0_RXFIFO       0x3F

// RF_SETTINGS is a data structure which contains all relevant CCxxx0 registers
typedef struct S_RF_SETTINGS
{
	INT8U FSCTRL2;		//���Ѽӵ�
    INT8U FSCTRL1;   // Frequency synthesizer control.
    INT8U FSCTRL0;   // Frequency synthesizer control.
    INT8U FREQ2;     // Frequency control word, high INT8U.
    INT8U FREQ1;     // Frequency control word, middle INT8U.
    INT8U FREQ0;     // Frequency control word, low INT8U.
    INT8U MDMCFG4;   // Modem configuration.
    INT8U MDMCFG3;   // Modem configuration.
    INT8U MDMCFG2;   // Modem configuration.
    INT8U MDMCFG1;   // Modem configuration.
    INT8U MDMCFG0;   // Modem configuration.
    INT8U CHANNR;    // Channel number.
    INT8U DEVIATN;   // Modem deviation setting (when FSK modulation is enabled).
    INT8U FREND1;    // Front end RX configuration.
    INT8U FREND0;    // Front end RX configuration.
    INT8U MCSM0;     // Main Radio Control State Machine configuration.
    INT8U FOCCFG;    // Frequency Offset Compensation Configuration.
    INT8U BSCFG;     // Bit synchronization Configuration.
    INT8U AGCCTRL2;  // AGC control.
	INT8U AGCCTRL1;  // AGC control.
    INT8U AGCCTRL0;  // AGC control.
    INT8U FSCAL3;    // Frequency synthesizer calibration.
    INT8U FSCAL2;    // Frequency synthesizer calibration.
	INT8U FSCAL1;    // Frequency synthesizer calibration.
    INT8U FSCAL0;    // Frequency synthesizer calibration.
    INT8U FSTEST;    // Frequency synthesizer calibration control
    INT8U TEST2;     // Various test settings.
    INT8U TEST1;     // Various test settings.
    INT8U TEST0;     // Various test settings.
    INT8U IOCFG2;    // GDO2 output pin configuration
    INT8U IOCFG0;    // GDO0 output pin configuration
    INT8U PKTCTRL1;  // Packet automation control.
    INT8U PKTCTRL0;  // Packet automation control.
    INT8U ADDR;      // Device address.
    INT8U PKTLEN;    // Packet length.
} RF_SETTINGS;

/////////////////////////////////////////////////////////////////
const RF_SETTINGS rfSettings = 
{
	0x00,
    0x08,   // FSCTRL1   Frequency synthesizer control.
    0x00,   // FSCTRL0   Frequency synthesizer control.
    0x10,   // FREQ2     Frequency control word, high byte.
    0xA7,   // FREQ1     Frequency control word, middle byte.
    0x62,   // FREQ0     Frequency control word, low byte.
    0x5B,   // MDMCFG4   Modem configuration.
    0xF8,   // MDMCFG3   Modem configuration.
    0x03,   // MDMCFG2   Modem configuration.
    0x22,   // MDMCFG1   Modem configuration.
    0xF8,   // MDMCFG0   Modem configuration.

    0x00,   // CHANNR    Channel number.
    0x47,   // DEVIATN   Modem deviation setting (when FSK modulation is enabled).
    0xB6,   // FREND1    Front end RX configuration.
    0x10,   // FREND0    Front end RX configuration.
    0x18,   // MCSM0     Main Radio Control State Machine configuration.
    0x1D,   // FOCCFG    Frequency Offset Compensation Configuration.
    0x1C,   // BSCFG     Bit synchronization Configuration.
    0xC7,   // AGCCTRL2  AGC control.
    0x00,   // AGCCTRL1  AGC control.
    0xB2,   // AGCCTRL0  AGC control.

    0xEA,   // FSCAL3    Frequency synthesizer calibration.
    0x2A,   // FSCAL2    Frequency synthesizer calibration.
    0x00,   // FSCAL1    Frequency synthesizer calibration.
    0x11,   // FSCAL0    Frequency synthesizer calibration.
    0x59,   // FSTEST    Frequency synthesizer calibration.
    0x81,   // TEST2     Various test settings.
    0x35,   // TEST1     Various test settings.
    0x09,   // TEST0     Various test settings.
    0x0B,   // IOCFG2    GDO2 output pin configuration.
    0x06,   // IOCFG0D   GDO0 output pin configuration. Refer to SmartRF?Studio User Manual for detailed pseudo register explanation.

    0x04,   // PKTCTRL1  Packet automation control.
    0x05,   // PKTCTRL0  Packet automation control.
    0x00,   // ADDR      Device address.
    0x0c    // PKTLEN    Packet length.
};
//*****************************************************************************************
//��������delay(unsigned int s)
//���룺ʱ��
//�������
//������������ͨ͢ʱ,�ڲ���
//*****************************************************************************************		
static void delay(unsigned int s)
{
	unsigned int i;
	for(i=0; i<s; i++);
	for(i=0; i<s; i++);
}


void halWait(INT16U timeout) {
    do {
        _NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
		_NOP();
    } while (--timeout);
}


void SpiInit(void)
{
//	CSN=0;
	CSN_CLR;
//	SCK=0;
	CLK_A_CLR;
//	CSN=1;
	CSN_SET;

}

/*****************************************************************************************
//��������CpuInit()
//���룺��
//�������
//����������SPI��ʼ������
*****************************************************************************************/
void CpuInit(void)
{
	SpiInit();
	delay(1000);
}
	

//*****************************************************************************************
//��������SpisendByte(INT8U dat)
//���룺���͵�����
//�������
//����������SPI����һ���ֽ�
//*****************************************************************************************
INT8U SpiTxRxByte(INT8U dat)
{
	INT8U i,temp;
	temp = 0;
	
//	SCK = 0;
	CLK_A_CLR;
	for(i=0; i<8; i++)
	{
		if(dat & 0x80)
		{
//			MOSI = 1;
			SPI_MOSI_A_SET;
		}
		else
//			MOSI = 0;
			SPI_MOSI_A_CLR;
		dat <<= 1;

//		SCK = 1;
		CLK_A_SET;
		_NOP();
		_NOP();

		temp <<= 1;
//		if(MISO)temp++;

		MISO;
		if((P8IN & BIT6)==BIT6)temp++;  /*MISO*/
//		SCK = 0;
		CLK_A_CLR;
		_NOP();
		_NOP();
	}
	return temp;
}

//*****************************************************************************************
//��������void RESET_CC1100(void)
//���룺��
//�������
//������������λCC1100
//*****************************************************************************************
void RESET_CC1100(void) 
{
	unsigned int Cnt = 0;
  
//	CSN = 0;
	CSN_CLR;
//	while (MISO);

	MISO;

	Cnt = 0;  //
    while ((P8IN & BIT6)==BIT6)
    {
    	Cnt ++;  //
    	if(Cnt > 50000) break;            
    }


       SpiTxRxByte(CCxxx0_SRES); 		//д�븴λ����
//	while (MISO);

         MISO;
        
		Cnt = 0;  //
		while ((P8IN & BIT6)==BIT6)
		{
			Cnt ++; 
			if(Cnt > 50000) break;			  
		}

		
//  CSN = 1;
       CSN_SET;
}

//*****************************************************************************************
//��������void POWER_UP_RESET_CC1100(void)
//���룺��
//�������
//�����������ϵ縴λCC1100
//*****************************************************************************************
void POWER_UP_RESET_CC1100(void) 
{
//	CSN = 1;
	CSN_SET;
	halWait(1); 
//	CSN = 0;
	CSN_CLR;
	halWait(1); 
//	CSN = 1;
	CSN_SET;
	halWait(41); 
	RESET_CC1100();   		//��λCC1100
}

//*****************************************************************************************
//��������void halSpiWriteReg(INT8U addr, INT8U value)
//���룺��ַ��������
//�������
//����������SPIд�Ĵ���
//*****************************************************************************************
void halSpiWriteReg(INT8U addr, INT8U value) 
{
	unsigned int Cnt = 0;

//    CSN = 0;
	CSN_CLR;
//    while (MISO);

	MISO;
	
	Cnt = 0;  //
	while ((P8IN & BIT6)==BIT6)
	{
		Cnt ++;  //
			if(Cnt > 50000) break;			  
	}

    SpiTxRxByte(addr);		//д��ַ
    SpiTxRxByte(value);		//д������
//    CSN = 1;
    CSN_SET;
}

//*****************************************************************************************
//��������void halSpiWriteBurstReg(INT8U addr, INT8U *buffer, INT8U count)
//���룺��ַ��д�뻺������д�����
//�������
//����������SPI����д���üĴ���
//*****************************************************************************************
void halSpiWriteBurstReg(INT8U addr, INT8U *buffer, INT8U count) 
{
	unsigned int Cnt = 0;

    INT8U i, temp;
	
	temp = addr | WRITE_BURST;
	
//    CSN = 0;
	CSN_CLR;
//    while (MISO);

	MISO;

	Cnt = 0;  //
	while ((P8IN & BIT6)==BIT6)
	{
		Cnt ++; 
		if(Cnt > 50000) break;			  
	}


	
    SpiTxRxByte(temp);
	
    for (i = 0; i < count; i++)
 	{
        SpiTxRxByte(buffer[i]);
    }
//    CSN = 1;
    CSN_SET;
}

//*****************************************************************************************
//��������void halSpiStrobe(INT8U strobe)
//���룺����
//�������
//����������SPIд����
//*****************************************************************************************
void halSpiStrobe(INT8U strobe) 
{
	unsigned int Cnt = 0;
	
//    CSN = 0;
	CSN_CLR;
//    while (MISO);

	MISO;

	Cnt = 0;  //
	while ((P8IN & BIT6)==BIT6)
	{
		Cnt ++;  //
		if(Cnt > 50000) break;			  
	}

    SpiTxRxByte(strobe);		//д������
//    CSN = 1;
    CSN_SET;
}





//*****************************************************************************************
//��������INT8U halSpiReadReg(INT8U addr)
//���룺��ַ
//������üĴ�����������
//����������SPI���Ĵ���
//*****************************************************************************************
INT8U halSpiReadReg(INT8U addr) 
{
	unsigned int Cnt = 0;
	
	INT8U temp, value;
    temp = addr|READ_SINGLE;//���Ĵ�������
//	CSN = 0;
    CSN_CLR;
//	while (MISO);

	MISO;
	
	Cnt = 0;  //
	while ((P8IN & BIT6)==BIT6)
	{
		Cnt ++;  //
			if(Cnt > 50000) break;			  
	}

	
	SpiTxRxByte(temp);
	value = SpiTxRxByte(0);
//	CSN = 1;
	CSN_SET;
	return value;
}


//*****************************************************************************************
//��������void halSpiReadBurstReg(INT8U addr, INT8U *buffer, INT8U count)
//���룺��ַ���������ݺ��ݴ�Ļ��������������ø���
//�������
//����������SPI����д���üĴ���
//*****************************************************************************************
void halSpiReadBurstReg(INT8U addr, INT8U *buffer, INT8U count) 
{
	unsigned int Cnt = 0;


    INT8U i,temp;
	temp = addr | READ_BURST;		//д��Ҫ�������üĴ�����ַ�Ͷ�����
//    CSN = 0;
	CSN_CLR;
//    while (MISO);

	MISO;
	

	Cnt = 0;  //
	while ((P8IN & BIT6)==BIT6)
	{
		Cnt ++;  //
			if(Cnt > 50000) break;			  
	}

	
	SpiTxRxByte(temp);   
    for (i = 0; i < count; i++) 
	{
        buffer[i] = SpiTxRxByte(0);
    }
//    CSN = 1;
    CSN_SET;
}


//*****************************************************************************************
//��������INT8U halSpiReadReg(INT8U addr)
//���룺��ַ
//�������״̬�Ĵ�����ǰֵ
//����������SPI��״̬�Ĵ���
//*****************************************************************************************
INT8U halSpiReadStatus(INT8U addr) 
{
	unsigned int Cnt = 0;


    INT8U value,temp;
	temp = addr | READ_BURST;		//д��Ҫ����״̬�Ĵ����ĵ�ַͬʱд�������
//    CSN = 0;
	CSN_CLR;
//    while (MISO);

	MISO;
	
	
	Cnt = 0;  //
	while ((P8IN & BIT6)==BIT6)
	{
		Cnt ++;  //
			if(Cnt > 50000) break;			  
	}


    SpiTxRxByte(temp);
	value = SpiTxRxByte(0);
//	CSN = 1;
	CSN_SET;
	return value;
}
//*****************************************************************************************
//��������void halRfWriteRfSettings(RF_SETTINGS *pRfSettings)
//���룺��
//�������
//��������������CC1100�ļĴ���
//*****************************************************************************************
void halRfWriteRfSettings(void) 
{

	halSpiWriteReg(CCxxx0_FSCTRL0,  rfSettings.FSCTRL2);//���Ѽӵ�
    // Write register settings
    halSpiWriteReg(CCxxx0_FSCTRL1,  rfSettings.FSCTRL1);
    halSpiWriteReg(CCxxx0_FSCTRL0,  rfSettings.FSCTRL0);
    halSpiWriteReg(CCxxx0_FREQ2,    rfSettings.FREQ2);
    halSpiWriteReg(CCxxx0_FREQ1,    rfSettings.FREQ1);
    halSpiWriteReg(CCxxx0_FREQ0,    rfSettings.FREQ0);
    halSpiWriteReg(CCxxx0_MDMCFG4,  rfSettings.MDMCFG4);
    halSpiWriteReg(CCxxx0_MDMCFG3,  rfSettings.MDMCFG3);
    halSpiWriteReg(CCxxx0_MDMCFG2,  rfSettings.MDMCFG2);
    halSpiWriteReg(CCxxx0_MDMCFG1,  rfSettings.MDMCFG1);
    halSpiWriteReg(CCxxx0_MDMCFG0,  rfSettings.MDMCFG0);
    halSpiWriteReg(CCxxx0_CHANNR,   rfSettings.CHANNR);
    halSpiWriteReg(CCxxx0_DEVIATN,  rfSettings.DEVIATN);
    halSpiWriteReg(CCxxx0_FREND1,   rfSettings.FREND1);
    halSpiWriteReg(CCxxx0_FREND0,   rfSettings.FREND0);
    halSpiWriteReg(CCxxx0_MCSM0 ,   rfSettings.MCSM0 );
    halSpiWriteReg(CCxxx0_FOCCFG,   rfSettings.FOCCFG);
    halSpiWriteReg(CCxxx0_BSCFG,    rfSettings.BSCFG);
    halSpiWriteReg(CCxxx0_AGCCTRL2, rfSettings.AGCCTRL2);
	halSpiWriteReg(CCxxx0_AGCCTRL1, rfSettings.AGCCTRL1);
    halSpiWriteReg(CCxxx0_AGCCTRL0, rfSettings.AGCCTRL0);
    halSpiWriteReg(CCxxx0_FSCAL3,   rfSettings.FSCAL3);
	halSpiWriteReg(CCxxx0_FSCAL2,   rfSettings.FSCAL2);
	halSpiWriteReg(CCxxx0_FSCAL1,   rfSettings.FSCAL1);
    halSpiWriteReg(CCxxx0_FSCAL0,   rfSettings.FSCAL0);
    halSpiWriteReg(CCxxx0_FSTEST,   rfSettings.FSTEST);
    halSpiWriteReg(CCxxx0_TEST2,    rfSettings.TEST2);
    halSpiWriteReg(CCxxx0_TEST1,    rfSettings.TEST1);
    halSpiWriteReg(CCxxx0_TEST0,    rfSettings.TEST0);
    halSpiWriteReg(CCxxx0_IOCFG2,   rfSettings.IOCFG2);
    halSpiWriteReg(CCxxx0_IOCFG0,   rfSettings.IOCFG0);    
    halSpiWriteReg(CCxxx0_PKTCTRL1, rfSettings.PKTCTRL1);
    halSpiWriteReg(CCxxx0_PKTCTRL0, rfSettings.PKTCTRL0);
    halSpiWriteReg(CCxxx0_ADDR,     rfSettings.ADDR);
    halSpiWriteReg(CCxxx0_PKTLEN,   rfSettings.PKTLEN);
}

//*****************************************************************************************
//��������void halRfSendPacket(INT8U *txBuffer, INT8U size)
//���룺���͵Ļ��������������ݸ���
//�������
//����������CC1100����һ������
//*****************************************************************************************

void halRfSendPacket(INT8U *txBuffer, INT8U size) 
{
	unsigned int Cnt = 0;

	halSpiWriteReg(CCxxx0_TXFIFO, size);
    halSpiWriteBurstReg(CCxxx0_TXFIFO, txBuffer, size);	//д��Ҫ���͵�����

    halSpiStrobe(CCxxx0_STX);		//���뷢��ģʽ��������

    // Wait for GDO0 to be set -> sync transmitted
//    while (!GDO0);
    // Wait for GDO0 to be cleared -> end of packet
//    while (GDO0);


	Cnt = 0;  //
	while ((PJIN & BIT3)!=BIT3/*!GDO0*/)
	{
		Cnt ++;  //
		if(Cnt > 50000) break;			  
	}


	Cnt = 0;  //
	while ((PJIN & BIT3)==BIT3/*GDO0*/)
	{
		Cnt ++;  //
		if(Cnt > 50000) break;			  
	}

	halSpiStrobe(CCxxx0_SFTX);
}


void setRxMode(void)
{
    halSpiStrobe(CCxxx0_SRX);		//�������״̬
}

/*
// Bit masks corresponding to STATE[2:0] in the status byte returned on MISO
#define CCxx00_STATE_BM                 0x70
#define CCxx00_FIFO_BYTES_AVAILABLE_BM  0x0F
#define CCxx00_STATE_TX_BM              0x20
#define CCxx00_STATE_TX_UNDERFLOW_BM    0x70
#define CCxx00_STATE_RX_BM              0x10
#define CCxx00_STATE_RX_OVERFLOW_BM     0x60
#define CCxx00_STATE_IDLE_BM            0x00

static INT8U RfGetRxStatus(void)
{
	INT8U temp, spiRxStatus1,spiRxStatus2;
	INT8U i=4;// ѭ�����Դ���
    temp = CCxxx0_SNOP|READ_SINGLE;//���Ĵ�������
	CSN = 0;
	while (MISO);
	SpiTxRxByte(temp);
	spiRxStatus1 = SpiTxRxByte(0);
	do
	{
		SpiTxRxByte(temp);
		spiRxStatus2 = SpiTxRxByte(0);
		if(spiRxStatus1 == spiRxStatus2)
		{
			if( (spiRxStatus1 & CCxx00_STATE_BM) == CCxx00_STATE_RX_OVERFLOW_BM)
			{
               halSpiStrobe(CCxxx0_SFRX);
			   return 0;
			}
		    return 1;
		}
		 spiRxStatus1=spiRxStatus2;
	}
	while(i--);
	CSN = 1;
    return 0;	
}
 */
INT8U halRfReceivePacket(INT8U *rxBuffer, INT8U *length) 
{
    INT8U status[2];
    INT8U packetLength;
    INT8U i=(*length)*4;  // �������Ҫ����datarate��length������

    halSpiStrobe(CCxxx0_SRX);		//�������״̬
    //delay(5);
    //while (!GDO1);
    //while (GDO1);
    delay(2);

    //	while (GDO0)

    GDO0;
	while ((PJIN & BIT3)==BIT3/*GDO0*/)
	{
		delay(2);
		--i;
		if(i<1)
		   return 0; 	    
	}	 
    if ((halSpiReadStatus(CCxxx0_RXBYTES) & BYTES_IN_RXFIFO)) //����ӵ��ֽ�����Ϊ0
	{
        packetLength = halSpiReadReg(CCxxx0_RXFIFO);//������һ���ֽڣ����ֽ�Ϊ��֡���ݳ���
        if (packetLength <= *length) 		//�����Ҫ����Ч���ݳ���С�ڵ��ڽ��յ������ݰ��ĳ���
		{
            halSpiReadBurstReg(CCxxx0_RXFIFO, rxBuffer, packetLength); //�������н��յ�������
            *length = packetLength;				//�ѽ������ݳ��ȵ��޸�Ϊ��ǰ���ݵĳ���
        
            // Read the 2 appended status bytes (status[0] = RSSI, status[1] = LQI)
            halSpiReadBurstReg(CCxxx0_RXFIFO, status, 2); 	//����CRCУ��λ
			halSpiStrobe(CCxxx0_SFRX);		//��ϴ���ջ�����
            return (status[1] & CRC_OK);			//���У��ɹ����ؽ��ճɹ�
        }
		 else 
		{
            *length = packetLength;
            halSpiStrobe(CCxxx0_SFRX);		//��ϴ���ջ�����
            return 0;
        }
    } 
	else
 	return 0;
}



void GPIO_Init(void)
{
	//P8SEL &= ~0X0E;  //care һ��Ҫ��������䣬��Ȼ����UART��ͻ

mSPI_All_Disable;  //�ر�����SPIģ���ʹ��


P8SEL &= ~BIT4; 
P8SEL &= ~BIT5; 
P8SEL &= ~BIT6; 

P8REN &= ~BIT4;
P8REN &= ~BIT5;
P8REN &= ~BIT6;

	P8DIR |= BIT5;      //P8.5 --->> CC1101 --SPI_MOSI_B
	P8OUT |= BIT5;

	P8DIR &= ~BIT6;      //P8.6 --->> CC1101 --SPI_MISO_B
	P8REN &= ~BIT6;
//P8OUT &= ~BIT3;
//	P8REN &= ~BIT3; 

	P8DIR |= BIT4;      //P8.4 --->> CC1101 --SPI_CLK_B
	P8OUT |= BIT4;

	PJDIR &= ~BIT3;      //PJ.3 --->> CC1101 --GDO0
//PJOUT &= ~BIT3;

	PJDIR &= ~BIT2;      //PJ.2 --->> CC1101 --GDO2
//	PJOUT &= ~BIT2;

////////////////////////////////////////////////////////////////////////////
//==**����"Bģ��"��·������TS3A5017: ѡ��IN2 ��IN1**==============//
	mConfig_TS3A5017_B_IN2(0);  //IN2 =0
	mConfig_TS3A5017_B_IN1(1);  //IN1 =1	 //ѡ��s2
}




/****************************************************************************
*������-Function:	void Initial_CC1101(void)
*����- Description:		��ʼ������:  "CC1101 �͹�����Ƶ�շ���"
*�������-Input:	None
*�������-output:	None
*ע������-Note��	��01)    	��02)    	��03)    ��04)  
*****************************************************************************/
void Initial_CC1101(void)  //��ʼ������:  "CC1101 �͹�����Ƶ�շ���"
{
	GPIO_Init();

	CpuInit();  //SPI��ʼ������
	POWER_UP_RESET_CC1100(); //�ϵ縴λCC1100

	halRfWriteRfSettings();  //����CC1100�ļĴ���
	halSpiWriteBurstReg(CCxxx0_PATABLE, PaTabel, 8); //SPI����д���üĴ���
//TxBuf[1] = 1 ;
//TxBuf[2] = 1 ;
	halRfSendPacket(TxBuf,8);	// Transmit Tx buffer data
//	delay(6000);
//_EINT(); 
}


/****************************************************************************
*������-Function:	void Send_OneByte_CC1101(unsigned char byte)
*����- Description:		����һ���ֽ�����-- "CC1101 �͹�����Ƶ�շ���"
*�������-Input:	byte: Ҫ���͵�һ���ֽ�����
*�������-output:	None
*ע������-Note�� ��01)	��02) 	��03) 	��04)  
*****************************************************************************/
void Send_OneByte_CC1101(unsigned char byte) //����һ���ֽ�����-- "CC1101 �͹�����Ƶ�շ���"
{
	TxBuf[0] = byte;
			// 1 :��ʾֻ����һ���ֽ�����
	halRfSendPacket(TxBuf,1);	//CC1100����һ������ //  Transmit TX buffer data

	TxBuf[0] = 0xFF;   //0xFF  ��ʾ��Ч����//�൱���������

	//delay(500);
}


/****************************************************************************
*������-Function:	void Send_String_CC1101(void)
*����- Description:		CC1101�����ַ���-- "CC1101 �͹�����Ƶ�շ���"
*�������-Input:	txArray: Ҫ���͵��ַ�������
*�������-output:	None
*ע������-Note�� 
	��01) ��Ϊ���ͻ������飬��8����Ԫ�������ɷ���8���ֽ�
	��02) 	��03) 	��04)  
*****************************************************************************/
void Send_String_CC1101(void)  //CC1101�����ַ���-- "CC1101 �͹�����Ƶ�շ���"
{
//TxBuf[1] = 1 ;
	halRfSendPacket(TxBuf,8);	//CC1100����һ������ //  Transmit TX buffer data
//	TxBuf[1] = 0xFF;   //0xFF  ��ʾ��Ч����//�൱���������
//	TxBuf[2] = 0xFF;
//	delay(500);
//P4OUT &= ~(BIT1 + BIT2 + BIT3);

}



/****************************************************************************
*������-Function:	void Deal_CC1101(void)
*����- Description:		����"CC1101 �͹�����Ƶ�շ���"
*�������-Input:	None
*�������-output:	None
*ע������-Note�� 
	��01) ��Ϊ���ջ������飬��8����Ԫ�������ɽ���8���ֽ�
	��02) 	��03) 	��04)  
*****************************************************************************/
void Deal_CC1101(void)  //����"CC1101 �͹�����Ƶ�շ���"
{
	INT8U leng =8;//���յ����ݳ���
	
		
	//������յ�����
	if(halRfReceivePacket(RxBuf,&leng))
	{
		G_RxData_CC1101 = RxBuf[0];
//		delay(1000);
//		P4OUT |= BIT1 + BIT2 + BIT3;
//		_NOP();
	}
	


}






