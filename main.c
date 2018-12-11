#include <msp430.h>
#include <stdint.h>
#include "HAL_UCS.h"

#define NumOfResult     8
#define Max_Volt        3.3
#define Accu_Adc        4095

uint32_t  results[NumOfResult+1];
uint16_t  average;
uint16_t  index = 0;
uint8_t con[10] , trans_v[10], lcd_data[10];

unsigned static int t = 0;
unsigned int mode2=0;   //PWM

#define STD 2000
#define XT2_PORT_SEL            P7SEL
#define XT2_ENABLE              (BIT2+BIT3)

#define d    0x01
#define c    0x20
#define b    0x40
#define a    0x80
#define dp   0x10
#define g    0x04
#define f    0x08
#define e    0x02

const char char_gen[] = {               // As used in 430 Day Watch Demo board
  a+b+c+d+e+f,                          // Displays "0"
  b+c,                                  // Displays "1"
  a+b+d+e+g,                            // Displays "2"
  a+b+c+d+g,                            // Displays "3"
  b+c+f+g,                              // Displays "4"
  a+c+d+f+g,                            // Displays "5"
  a+c+d+e+f+g,                          // Displays "6"
  a+b+c,                                // Displays "7"
  a+b+c+d+e+f+g,                        // Displays "8"
  a+b+c+d+f+g,                          // Displays "9"
  a+b+c+e+f+g,                          // Displays "A"
  c+d+e+f+g,                            // Displays "b"
  a+d+e+f,                              // Displays "c"
  b+c+d+e+g,                            // Displays "d"
  a+d+e+f+g,                            // Displays "E"
  a+e+f+g,                              // Displays "f"
  a+b+c+d+f+g,                          // Displays "g"
  c+e+f+g,                              // Displays "h"
  b+c,                                  // Displays "i"
  b+c+d,                                // Displays "j"
  b+c+e+f+g,                            // Displays "k"
  d+e+f,                                // Displays "L"
  a+b+c+e+f,                            // Displays "n"
  a+b+c+d+e+f+g+dp                      // Displays "full"
};

const char char_gen_dp[] = {               // As used in 430 Day Watch Demo board
  a+b+c+d+e+f+dp,                          // Displays "0"
  b+c+dp,                                  // Displays "1"
  a+b+d+e+g+dp,                            // Displays "2"
  a+b+c+d+g+dp,                            // Displays "3"
  b+c+f+g+dp,                              // Displays "4"
  a+c+d+f+g+dp,                            // Displays "5"
  a+c+d+e+f+g+dp,                          // Displays "6"
  a+b+c+dp,                                // Displays "7"
  a+b+c+d+e+f+g+dp,                        // Displays "8"
  a+b+c+d+f+g+dp,                          // Displays "9"
  a+b+c+e+f+g,                          // Displays "A"
  c+d+e+f+g,                            // Displays "b"
  a+d+e+f,                              // Displays "c"
  b+c+d+e+g,                            // Displays "d"
  a+d+e+f+g,                            // Displays "E"
  a+e+f+g,                              // Displays "f"
  a+b+c+d+f+g,                          // Displays "g"
  c+e+f+g,                              // Displays "h"
  b+c,                                  // Displays "i"
  b+c+d,                                // Displays "j"
  b+c+e+f+g,                            // Displays "k"
  d+e+f,                                // Displays "L"
  a+b+c+e+f,                            // Displays "n"
  g,                                    // Displays "-"
  dp,                                   // Displays "dp"
  a+b+c+d+e+f+g+dp                      // Displays "full"
};

/*port function select*/
void Init_TS3A5017DR(void)
{
    // Configure TS3A5017DR  IN1 and IN2
    P1DIR |= BIT6 + BIT7;   //P3.4 : IN1 ; P3.5 : IN2   set as output
    P1OUT &= ~BIT7;          //IN1 = 0
    P1OUT |= BIT6;         //IN2 = 1
}

void Init_lcd(void)
{
        LCDBCTL0 =LCDDIV0 + LCDPRE0 +  LCDMX1 + LCDSSEL + LCDMX1 + LCD4MUX ;

        LCDBPCTL0 = LCDS0 + LCDS1 + LCDS2 + LCDS3 + LCDS4 + LCDS5 + LCDS6+ LCDS7 + LCDS8
                + LCDS9 + LCDS10 + LCDS11 ;
        P5SEL  = 0xfc;
}

void LcdGo(unsigned char doit)
{
    if(doit==1)
    {
        //打开液晶显示
        LCDBCTL0 |= LCDON;
    }
    else if(doit==0)
    {
        //关闭液晶显示
        LCDBCTL0 &= ~LCDON;
    }
}

void LcdBlink(unsigned char doit)
{
    if(doit==0)
    {
        LCDBCTL0 &= ~LCDSON;
    }
    else if(doit==1)
    {
        LCDBCTL0 |= LCDSON;
    }
}

void LCD_Clear(void)//清屏
{
     unsigned char index;
     for (index=0; index<12; index++)
     {
         LCDMEM[index] = 0;
     }
}

void Backlight_Enable(void)
{
  P8DIR |= BIT0;
  P8OUT |= BIT0;
}

int16_t Trans_val(uint16_t number,uint16_t system, uint8_t *output)
 {
     // 商,余数和标记
    int16_t Quotient, Balance, i = 0, j , k;

    int32_t  caltmp;
    uint16_t Curr_Volt;

    caltmp = number;
    caltmp = (caltmp << 5) + number; //caltmp = Hex_Val * 33

    caltmp = (caltmp << 6) + (caltmp << 5) + (caltmp << 1); //caltmp = caltmp * 100
    Curr_Volt = caltmp >> 12; //Curr_Volt = caltmp / 2^n=4096


    Quotient = Curr_Volt;

    do
     {
         Balance = Quotient % system;
         output[i++] = Balance;
     } while (Quotient /= system);

    // 转换为char型
     for(j = 0; j < i; j++)
         if(output[j] > 9)
             output[j] = output[j] + 55;
         else output[j] += 48;

    // 字符串取反
     for(k = 0; k < i / 2; k++)
     {
         char tmp;
         tmp = output[k];
         output[k] = output[i - k - 1];
         output[i - k - 1] = tmp;
     }

    return i;
 }

int16_t Translator(uint16_t number, uint8_t *output)
{
    int16_t Quotient, Balance, i = 0,j ,k;
    Quotient = number;
    uint8_t tmp[4] = {0};

    for (i = 0; i < 4;)
    {
        Balance = Quotient % 10;
        tmp[i++] = Balance;
        Quotient /= 10;
    }

    for (j = 0; j < i; j++)
    {
        output[i - j - 1] = tmp[j] + 48;
    }

    return i;
}

int16_t Conversion(uint16_t number,uint16_t system, uint8_t *output)
 {
     // 商,余数和标记
    int16_t Quotient, Balance, i = 0,j ,k;
    Quotient = number;

    do
     {
         Balance = Quotient % system;
         output[i++] = Balance;
     } while (Quotient /= system);

    // 转换为char型
     for(j = 0; j < i; j++)
         if(output[j] > 9)
             output[j] = output[j] + 55;
         else output[j] += 48;

    // 字符串取反
     for(k = 0; k < i / 2; k++)
     {
         char tmp;
         tmp = output[k];
         output[k] = output[i - k - 1];
         output[i - k - 1] = tmp;
     }

    return i;
 }

void DAC_Init(void)
{
    P7DIR|=BIT6;
    P7SEL|=BIT6;

    DAC12_1CTL0 = DAC12IR + DAC12SREF_1 +
            DAC12AMP_5 + DAC12ENC + DAC12CALON+DAC12OPS;

}

/**
 * main.c
 */
int main(void)
{

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	Init_TS3A5017DR();
	DAC_Init();

	//Init_lcd();                               // lcd初始化
	//LcdGo(1);                                // 打开液晶模块
	//LCD_Clear();                             //清屏
	//Backlight_Enable();

    Init_LCD_TFT_ILI9325(); //"彩屏LCD_TFT_ILI9325" 初使化: 所有相关资源的初始化
    //LCD_TFT_ShowChar(2,2,'A',1,0x001F,0xFFE0);//test lcd tft

	P4DIR|=BIT4+BIT5+BIT6;      //led
	P4IE |= BIT0; // key enable P2.6 interrupt
	P4IFG &= ~(BIT0); // clean interrupt flag

    P6SEL |= BIT1;
    ADC12CTL0 = ADC12ON + ADC12SHT0_15 + ADC12MSC + ADC12REFON + ADC12REF2_5V; // Turn on ADC12, set sampling time
    ADC12CTL1 = ADC12SHP + ADC12CONSEQ_2 + ADC12SSEL_1;       // Use sampling timer, set mode ,set clock ACLK
    ADC12MCTL0 |= ADC12INCH_1;   //change
    ADC12IE = ADC12IE0;                       // Enable ADC12IFG.0
    ADC12CTL0 |= ADC12ENC;                    // Enable conversions
    ADC12CTL0 |= ADC12SC;                     // Start conversion
    _EINT();                                  // Enable all interrupt

    _BIS_SR(LPM4_bits + GIE);                 // Enter LPM4, Enable interrupts
    while(1)
    {
        if((P4IN & BIT2)==0)      //KEY1 pressed
            P4IFG |= BIT0;      //中断挂起 ，准备进入服务函数
        else
            P4IFG &=~BIT0;                        // For debugger
    }
    return 0;
}


#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{

    results[index++] = ADC12MEM0;     // Move results
    if(index == NumOfResult)
    {
        uint16_t i;
        average = 0;

        for(i = 0; i < NumOfResult; i++)
        {
            average += results[i];
            results[i] = 0;
        }
        average >>= 3; //除以8
        index = 0;

        if(average>200)
                P4OUT|=BIT4;
            else
                P4OUT&=~BIT4;
        if(average>2000)
                P4OUT|=BIT5;
            else
                P4OUT&=~BIT5;
            if(average>3200)
                P4OUT|=BIT6;
            else
                P4OUT&=~BIT6;

        Conversion(average , 10, con);
        Trans_val(average , 10, trans_v);

        //LCDMEM[5] = char_gen[con[3]-48];
        //LCDMEM[4] = char_gen[con[2]-48];
        //LCDMEM[3] = char_gen[con[1]-48];
        //LCDMEM[2] = char_gen[con[0]-48];

        Translator(average, lcd_data);

        //New Functions will be listed and debuged here.
        LCD_TFT_ShowChar(2,2,lcd_data[0],2,0x001F,0xFFE0);
        LCD_TFT_ShowChar(2,42,lcd_data[1],2,0x001F,0xFFE0);
        LCD_TFT_ShowChar(2,82,lcd_data[2],2,0x001F,0xFFE0);
        LCD_TFT_ShowChar(2,122,lcd_data[3],2,0x001F,0xFFE0);
        LCD_TFT_ShowString(22,2,lcd_data,2,0x001F,0xFFE0);
        //LCD_TFT_ShowString(u16 line,u16 column,u8 *ArrayPoint,u8 Font,u16 pointColor,u16 backColor);



        //End of new functions.

        for(i=0;i < NumOfResult;i++)
        {
            con[i] = 0 ;
            trans_v[i] = 0;
        }
    }
}

#pragma vector=PORT4_VECTOR
__interrupt void port_4(void)
{
    t+=1;       //按键次数 对应功能
    if(t==3)    t=0;
    switch(t)
    {
        case 0:break;
        case 1:ADC12CTL1|=ADC12ISSH;break;
        case 2:mode2=1;break;
        default:break;
    }
    P4IFG &=~BIT0; // clean interrupt flag
}

