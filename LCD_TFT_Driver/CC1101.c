/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=
* 文件名-FileName:			 CC1101.c
* 附属文件-Dependencies:  	 CC1101.h; Hardware_Profile.h; Generic.h;
* 文件描述-File Description:	 ( 源程序-Source File) 
	■"CC1101 低功耗射频收发器"-驱动程序(外部资源)
	01)CC1101 低功耗（低于 1GHz）射频收发器_Low-Power Sub-1 GHz RF Transceiver  
	02) CC1101是一款低于1GHz高性能射频收发器，设计旨在用于
极低功耗RF应用。其主要针对工业、科研和医疗(ISM)以及
短距离无线通信设备(SRD)。CC1101可提供对数据包处理、数据
缓冲、突发传输、接收信号强度指示(RSSI)、空闲信道评估(CCA)、
链路质量指示以及无线唤醒(WOR)的广泛硬件支持。CC1101在
代码、封装和外引脚方面均与CC1100兼容，可用于全球最为常用
的开放式低于1GHz频率的RF设计。
	03) CC1101芯片是 Chipcon（已被 TI收购）推出的一款低成本单片射频
的 UHF收发器。主要应用于低功耗无线应用设计。
	04)该芯片电路主要设定为在 315、433、868 和 915MHz 的 ISM
（工业，科学和医学）,集成了一个软件可编程的调制解调器。
	05)	应用领域:
		●超低功耗无线收发器 ●无线传感网络 
		●家庭和楼宇自动化       ●高级抄表架构(AMI) 
		●无线计量                              ●无线报警安全系统
	06)	性能参数:
●387.0MHz～464.0MHz工作频段。
●高灵敏度(433MHz，0.6kbps，1%误码率时为-116dBm)。
●低电流消耗(接收模式，433MHz，1.2kbps时仅16.0mA)。
●最高可设置为+10dBm的发射功率。
●支持0.6kbps～500kbps的数据传输速率，数据传输率最高可达 500kbps。
●支持多种调制模式(OOK、ASK、GFSK、2-FSK、4-FSK和MSK)。
●提供对同步字检测、地址校验、灵活的数据包长度以及自动CRC处理的支持。
●支持RSSI(接收信号强度指示)和LQI(链路质量指示)。
●通过4线SPI接口与MCU连接，同时提供2个可设定功能的通用数字输出引脚。
●独立的64字节RXFIFO和TX FIFO。
●工作电压范围：1.9V～3.6V，待机模式下电流仅为200nA。
●工作温度范围：-40℃～+85℃	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 注意事项-Attention : 	
	▲01)SIP 接口的待机模式、发送模式以及接收等工作模式都通过 
SPI 指令进行设置。
	▲02)可以通过 GDO0 或 GDO2 引脚高低电平状态来判断数据的发送
或接收是否完成。 
	▲03)P8SEL &= ~0X0C;  //care 一定要加这条语句，不然会与UART冲突
	▲04)    ▲05)    ▲06)     
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


#include "CC1101.h"   //"CC1101 低功耗射频收发器"-驱动程序(外部资源)-头文件



////////////////////////////////////////////////////////////////////////////
//==**全局变量定义**Global variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned char G_RxData_CC1101 = 0xFF;  //缓存 "RS485_UART   串口通信"接收到的数据


////////////////////////////////////////////////////////////////////////////
//==**局部变量定义**Local variables**========================//
////////////////////////////////////////////////////////////////////////////
unsigned char TxBuf[8]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};//8字节, 如果需要更长的数据包,请正确设置
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

#define 	WRITE_BURST     	0x40						//连续写入
#define 	READ_SINGLE     	0x80						//读
#define 	READ_BURST      	0xC0						//连续读
#define 	BYTES_IN_RXFIFO     0x7F  						//接收缓冲区的有效字节数
#define 	CRC_OK              0x80 						//CRC校验通过位标志
//*****************************************************************************************

#define CSN         	    BIT1    //PJ.1--->>CSN
#define SPI_MOSI_A          BIT5	//P8.5--->>SPI_MOSI_A  //V3.0为SPI_B
//#define SPI_MISO_A1         BIT6	//P8.6--->>SPI_MISO_A1
#define CLK_A               BIT4	//P8.4--->>CLA_A
//#define GDO0     	        BIT3	//PJ.3--->>GD00
//#define GDO2     	        BIT2	//PJ.2--->>GD02

//控制口置1操作语句宏定义
#define	CSN_SET  	        PJOUT |= CSN
#define	SPI_MOSI_A_SET  	P8OUT |= SPI_MOSI_A
//#define	SPI_MISO_A1_SET  	P8OUT |= SPI_MISO_A1
#define	CLK_A_SET  	        P8OUT |= CLK_A
//#define	GDO0_SET  	        PJOUT |= GDO0
//#define	GDO2_SET  	        PJOUT |= GDO2

//控制口置0操作语句宏定义
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


////----------------------------------------按键端口-------------------------------------------------------
//#define	  KEY     =P3^4;
////----------------------------------------LED显示端口---------------------------------------------------
//#define     LED     =P3^5;



//***************更多功率参数设置可详细参考DATACC1100英文文档中第48-49页的参数表******************
//INT8U PaTabel[8] = {0x04 ,0x04 ,0x04 ,0x04 ,0x04 ,0x04 ,0x04 ,0x04};  //-30dBm   功率最小
unsigned char PaTabel[8] = {0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60};  //0dBm
//INT8U PaTabel[8] = {0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0};   //10dBm     功率最大
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
	INT8U FSCTRL2;		//自已加的
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
//函数名：delay(unsigned int s)
//输入：时间
//输出：无
//功能描述：普通廷时,内部用
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
//函数名：CpuInit()
//输入：无
//输出：无
//功能描述：SPI初始化程序
*****************************************************************************************/
void CpuInit(void)
{
	SpiInit();
	delay(1000);
}
	

//*****************************************************************************************
//函数名：SpisendByte(INT8U dat)
//输入：发送的数据
//输出：无
//功能描述：SPI发送一个字节
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
//函数名：void RESET_CC1100(void)
//输入：无
//输出：无
//功能描述：复位CC1100
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


       SpiTxRxByte(CCxxx0_SRES); 		//写入复位命令
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
//函数名：void POWER_UP_RESET_CC1100(void)
//输入：无
//输出：无
//功能描述：上电复位CC1100
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
	RESET_CC1100();   		//复位CC1100
}

//*****************************************************************************************
//函数名：void halSpiWriteReg(INT8U addr, INT8U value)
//输入：地址和配置字
//输出：无
//功能描述：SPI写寄存器
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

    SpiTxRxByte(addr);		//写地址
    SpiTxRxByte(value);		//写入配置
//    CSN = 1;
    CSN_SET;
}

//*****************************************************************************************
//函数名：void halSpiWriteBurstReg(INT8U addr, INT8U *buffer, INT8U count)
//输入：地址，写入缓冲区，写入个数
//输出：无
//功能描述：SPI连续写配置寄存器
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
//函数名：void halSpiStrobe(INT8U strobe)
//输入：命令
//输出：无
//功能描述：SPI写命令
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

    SpiTxRxByte(strobe);		//写入命令
//    CSN = 1;
    CSN_SET;
}





//*****************************************************************************************
//函数名：INT8U halSpiReadReg(INT8U addr)
//输入：地址
//输出：该寄存器的配置字
//功能描述：SPI读寄存器
//*****************************************************************************************
INT8U halSpiReadReg(INT8U addr) 
{
	unsigned int Cnt = 0;
	
	INT8U temp, value;
    temp = addr|READ_SINGLE;//读寄存器命令
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
//函数名：void halSpiReadBurstReg(INT8U addr, INT8U *buffer, INT8U count)
//输入：地址，读出数据后暂存的缓冲区，读出配置个数
//输出：无
//功能描述：SPI连续写配置寄存器
//*****************************************************************************************
void halSpiReadBurstReg(INT8U addr, INT8U *buffer, INT8U count) 
{
	unsigned int Cnt = 0;


    INT8U i,temp;
	temp = addr | READ_BURST;		//写入要读的配置寄存器地址和读命令
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
//函数名：INT8U halSpiReadReg(INT8U addr)
//输入：地址
//输出：该状态寄存器当前值
//功能描述：SPI读状态寄存器
//*****************************************************************************************
INT8U halSpiReadStatus(INT8U addr) 
{
	unsigned int Cnt = 0;


    INT8U value,temp;
	temp = addr | READ_BURST;		//写入要读的状态寄存器的地址同时写入读命令
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
//函数名：void halRfWriteRfSettings(RF_SETTINGS *pRfSettings)
//输入：无
//输出：无
//功能描述：配置CC1100的寄存器
//*****************************************************************************************
void halRfWriteRfSettings(void) 
{

	halSpiWriteReg(CCxxx0_FSCTRL0,  rfSettings.FSCTRL2);//自已加的
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
//函数名：void halRfSendPacket(INT8U *txBuffer, INT8U size)
//输入：发送的缓冲区，发送数据个数
//输出：无
//功能描述：CC1100发送一组数据
//*****************************************************************************************

void halRfSendPacket(INT8U *txBuffer, INT8U size) 
{
	unsigned int Cnt = 0;

	halSpiWriteReg(CCxxx0_TXFIFO, size);
    halSpiWriteBurstReg(CCxxx0_TXFIFO, txBuffer, size);	//写入要发送的数据

    halSpiStrobe(CCxxx0_STX);		//进入发送模式发送数据

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
    halSpiStrobe(CCxxx0_SRX);		//进入接收状态
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
	INT8U i=4;// 循环测试次数
    temp = CCxxx0_SNOP|READ_SINGLE;//读寄存器命令
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
    INT8U i=(*length)*4;  // 具体多少要根据datarate和length来决定

    halSpiStrobe(CCxxx0_SRX);		//进入接收状态
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
    if ((halSpiReadStatus(CCxxx0_RXBYTES) & BYTES_IN_RXFIFO)) //如果接的字节数不为0
	{
        packetLength = halSpiReadReg(CCxxx0_RXFIFO);//读出第一个字节，此字节为该帧数据长度
        if (packetLength <= *length) 		//如果所要的有效数据长度小于等于接收到的数据包的长度
		{
            halSpiReadBurstReg(CCxxx0_RXFIFO, rxBuffer, packetLength); //读出所有接收到的数据
            *length = packetLength;				//把接收数据长度的修改为当前数据的长度
        
            // Read the 2 appended status bytes (status[0] = RSSI, status[1] = LQI)
            halSpiReadBurstReg(CCxxx0_RXFIFO, status, 2); 	//读出CRC校验位
			halSpiStrobe(CCxxx0_SFRX);		//清洗接收缓冲区
            return (status[1] & CRC_OK);			//如果校验成功返回接收成功
        }
		 else 
		{
            *length = packetLength;
            halSpiStrobe(CCxxx0_SFRX);		//清洗接收缓冲区
            return 0;
        }
    } 
	else
 	return 0;
}



void GPIO_Init(void)
{
	//P8SEL &= ~0X0E;  //care 一定要加这条语句，不然会与UART冲突

mSPI_All_Disable;  //关闭所有SPI模块的使能


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
//==**配置"B模块"多路复用器TS3A5017: 选择IN2 、IN1**==============//
	mConfig_TS3A5017_B_IN2(0);  //IN2 =0
	mConfig_TS3A5017_B_IN1(1);  //IN1 =1	 //选择s2
}




/****************************************************************************
*函数名-Function:	void Initial_CC1101(void)
*描述- Description:		初始化设置:  "CC1101 低功耗射频收发器"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note：	▲01)    	▲02)    	▲03)    ▲04)  
*****************************************************************************/
void Initial_CC1101(void)  //初始化设置:  "CC1101 低功耗射频收发器"
{
	GPIO_Init();

	CpuInit();  //SPI初始化程序
	POWER_UP_RESET_CC1100(); //上电复位CC1100

	halRfWriteRfSettings();  //配置CC1100的寄存器
	halSpiWriteBurstReg(CCxxx0_PATABLE, PaTabel, 8); //SPI连续写配置寄存器
//TxBuf[1] = 1 ;
//TxBuf[2] = 1 ;
	halRfSendPacket(TxBuf,8);	// Transmit Tx buffer data
//	delay(6000);
//_EINT(); 
}


/****************************************************************************
*函数名-Function:	void Send_OneByte_CC1101(unsigned char byte)
*描述- Description:		发送一个字节数据-- "CC1101 低功耗射频收发器"
*输入参数-Input:	byte: 要发送的一个字节数据
*输出参数-output:	None
*注意事项-Note： ▲01)	▲02) 	▲03) 	▲04)  
*****************************************************************************/
void Send_OneByte_CC1101(unsigned char byte) //发送一个字节数据-- "CC1101 低功耗射频收发器"
{
	TxBuf[0] = byte;
			// 1 :表示只发送一个字节数据
	halRfSendPacket(TxBuf,1);	//CC1100发送一组数据 //  Transmit TX buffer data

	TxBuf[0] = 0xFF;   //0xFF  表示无效数据//相当于清除缓存

	//delay(500);
}


/****************************************************************************
*函数名-Function:	void Send_String_CC1101(void)
*描述- Description:		CC1101发送字符串-- "CC1101 低功耗射频收发器"
*输入参数-Input:	txArray: 要发送的字符串数组
*输出参数-output:	None
*注意事项-Note： 
	▲01) 因为发送缓冲数组，共8个单元，故最多可发送8个字节
	▲02) 	▲03) 	▲04)  
*****************************************************************************/
void Send_String_CC1101(void)  //CC1101发送字符串-- "CC1101 低功耗射频收发器"
{
//TxBuf[1] = 1 ;
	halRfSendPacket(TxBuf,8);	//CC1100发送一组数据 //  Transmit TX buffer data
//	TxBuf[1] = 0xFF;   //0xFF  表示无效数据//相当于清除缓存
//	TxBuf[2] = 0xFF;
//	delay(500);
//P4OUT &= ~(BIT1 + BIT2 + BIT3);

}



/****************************************************************************
*函数名-Function:	void Deal_CC1101(void)
*描述- Description:		处理"CC1101 低功耗射频收发器"
*输入参数-Input:	None
*输出参数-output:	None
*注意事项-Note： 
	▲01) 因为接收缓冲数组，共8个单元，故最多可接收8个字节
	▲02) 	▲03) 	▲04)  
*****************************************************************************/
void Deal_CC1101(void)  //处理"CC1101 低功耗射频收发器"
{
	INT8U leng =8;//接收的数据长度
	
		
	//如果接收到数据
	if(halRfReceivePacket(RxBuf,&leng))
	{
		G_RxData_CC1101 = RxBuf[0];
//		delay(1000);
//		P4OUT |= BIT1 + BIT2 + BIT3;
//		_NOP();
	}
	


}






