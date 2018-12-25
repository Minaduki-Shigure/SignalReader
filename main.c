#include <msp430.h>
#include <stdint.h>
#include "HAL_UCS.h"

#define NumOfResult     8
#define Max_Volt        3.3
#define Accu_Adc        4095
#define REC_CAP         256

uint32_t  results[NumOfResult+1];
uint16_t  average;
uint16_t  index = 0;
uint8_t con[10] , trans_v[10], lcd_data[10];
uint16_t  xp = 0;
uint16_t  yp = 0;
uint16_t  yp1 = 0;
uint16_t  record[REC_CAP];
uint16_t  maxvalue;
uint16_t  minvalue;
uint16_t  Vpp=0;
uint16_t  Freq;
uint16_t  FreqCycle;
uint16_t  div=0;
uint8_t   flagstat = 0;
uint16_t  flagone;
uint16_t  flagtwo;

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
        //��Һ����ʾ
        LCDBCTL0 |= LCDON;
    }
    else if(doit==0)
    {
        //�ر�Һ����ʾ
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

void LCD_Clear(void)//����
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
     // ��,�����ͱ��
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

    // ת��Ϊchar��
     for(j = 0; j < i; j++)
         if(output[j] > 9)
             output[j] = output[j] + 55;
         else output[j] += 48;

    // �ַ���ȡ��
     for(k = 0; k < i / 2; k++)
     {
         char tmp;
         tmp = output[k];
         output[k] = output[i - k - 1];
         output[i - k - 1] = tmp;
     }

    return i;
 }

uint16_t mymax(uint16_t *num)
{
    uint16_t whyitissohardtofindavariablenotused = 0;
    int cnt = 0;
    for (cnt = 0; cnt < REC_CAP; cnt ++)
    {
        if (num[cnt] > whyitissohardtofindavariablenotused)
            whyitissohardtofindavariablenotused = num[cnt];
    }
    return whyitissohardtofindavariablenotused;
}

uint16_t mymin(uint16_t *num)
{
    uint16_t whyitissohardtofindavariablenotused = 4096;
    int cnt = 0;
    for (cnt = 0; cnt < REC_CAP; cnt ++)
    {
        if (num[cnt] < whyitissohardtofindavariablenotused)
            whyitissohardtofindavariablenotused = num[cnt];
    }
    return whyitissohardtofindavariablenotused;
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
     // ��,�����ͱ��
    int16_t Quotient, Balance, i = 0,j ,k;
    Quotient = number;

    do
     {
         Balance = Quotient % system;
         output[i++] = Balance;
     } while (Quotient /= system);

    // ת��Ϊchar��
     for(j = 0; j < i; j++)
         if(output[j] > 9)
             output[j] = output[j] + 55;
         else output[j] += 48;

    // �ַ���ȡ��
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

	//Init_lcd();                               // lcd��ʼ��
	//LcdGo(1);                                // ��Һ��ģ��
	//LCD_Clear();                             //����
	//Backlight_Enable();

    Init_LCD_TFT_ILI9325(); //"����LCD_TFT_ILI9325" ��ʹ��: ���������Դ�ĳ�ʼ��
    //LCD_TFT_ShowChar(2,2,'A',1,0x001F,0xFFE0);//test lcd tft
    LCD_TFT_ShowString(2,2,"Vmax",2,0x001F,0xFFE0);
    LCD_TFT_ShowString(22,2,"Vmin",2,0x001F,0xFFE0);
    LCD_TFT_ShowString(42,2,"Vpp",2,0x001F,0xFFE0);
    LCD_TFT_ShowString(2,82,"mV",2,0x001F,0xFFE0);
    LCD_TFT_ShowString(22,82,"mV",2,0x001F,0xFFE0);
    LCD_TFT_ShowString(42,82,"mV",2,0x001F,0xFFE0);
    LCD_TFT_ShowString(62,2,"Min=0, Max=1600",2,0x001F,0xFFE0);

	P4DIR|=BIT4+BIT5+BIT6;      //led
	P4IE |= BIT0; // key enable P2.6 interrupt
	P4IFG &= ~(BIT0); // clean interrupt flag

    P6SEL |= BIT1;
    ADC12CTL0 = ADC12ON + ADC12SHT0_0 + ADC12MSC + ADC12REFON + ADC12REF2_5V; // Turn on ADC12, set sampling time
    //ADC12SHT0_15=1024 ADC12CLK cycles ADC12REF2_5V=REF=2.5V
    ADC12CTL1 = ADC12SHP + ADC12CONSEQ_2 + ADC12SSEL_1;       // Use sampling timer, set mode ,set clock ACLK
    ADC12MCTL0 |= ADC12INCH_1;   //change
    ADC12IE = ADC12IE0;                       // Enable ADC12IFG.0
    ADC12CTL0 |= ADC12ENC;                    // Enable conversions
    ADC12CTL0 |= ADC12SC;                     // Start conversion
    _EINT();                                  // Enable all interrupt

    P1DIR |= BIT0;
    //P1OUT |= BIT0;

    _BIS_SR(LPM4_bits + GIE);                 // Enter LPM4, Enable interrupts
    while(1)
    {
        if((P4IN & BIT2)==0)      //KEY1 pressed
            P4IFG |= BIT0;      //�жϹ��� ��׼�����������
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
        average >>= 3; //����8
        index = 0;


        if (average > 2000)
            P1OUT |= BIT0;
        else
            P1OUT &= ~BIT0;

/*
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
*/

        //Conversion(average , 10, con);
        //Trans_val(average , 10, trans_v);

        //LCDMEM[5] = char_gen[con[3]-48];
        //LCDMEM[4] = char_gen[con[2]-48];
        //LCDMEM[3] = char_gen[con[1]-48];
        //LCDMEM[2] = char_gen[con[0]-48];

        //Translator(average, lcd_data);

        //New Functions will be listed and debuged here.
        //LCD_TFT_ShowChar(2,2,lcd_data[0],2,0x001F,0xFFE0);
        //LCD_TFT_ShowChar(2,42,lcd_data[1],2,0x001F,0xFFE0);
        //LCD_TFT_ShowChar(2,82,lcd_data[2],2,0x001F,0xFFE0);
        //LCD_TFT_ShowChar(2,122,lcd_data[3],2,0x001F,0xFFE0);
        //LCD_TFT_ShowString(2,2,lcd_data,2,0x001F,0xFFE0);
        //LCD_TFT_ShowString(u16 line,u16 column,u8 *ArrayPoint,u8 Font,u16 pointColor,u16 backColor);
        //LCD_TFT_DrawPoint(240-average/16, xp, 0xFFFF);
/*
        record[div++]=average;

        //Vpp Vmax Vmin
        if (div == REC_CAP){
            div = 0;
            maxvalue = mymax(record);
            minvalue = mymin(record);
            Vpp = maxvalue - minvalue;//Vpp=4000��Ӧ1.6V
            maxvalue = maxvalue * 0.4;
            minvalue = minvalue * 0.4;
            Vpp = Vpp * 0.4;
            Translator(maxvalue, lcd_data);
            LCD_TFT_ShowString(2,42,lcd_data,2,0x001F,0xFFE0);
            Translator(minvalue, lcd_data);
            LCD_TFT_ShowString(22,42,lcd_data,2,0x001F,0xFFE0);
            Translator(Vpp, lcd_data);
            LCD_TFT_ShowString(42,42,lcd_data,2,0x001F,0xFFE0);
        }

*/
/*
        //Freq
        if (average >= 300 && average <= 700)
        {
            if (flagstat == 2)
            {
                flagstat = 0;
                flagtwo = div;
                if ((int)(flagtwo - flagone) > 0)
                    FreqCycle = flagtwo - flagone;
                else
                    FreqCycle = 128 + flagtwo - flagone;
            }
            else if (flagstat == 1)
                flagstat++;
            else
            {
                flagstat++;
                flagone = div;
            }
        }
*/





        //��ʾ���β���
        yp = 240 - average / 18;
        LCD_TFT_DrawLine(yp1, xp-1, yp, xp, 0xFFFF);
        xp++;
        if (xp == 320){
            xp = 0;
            LCD_TFT_Clear(0x0000);//�����ٶȵ͵��ķ�ֹͣ
        }
        yp1 = yp;





        //End of new functions.
/*
        for(i=0;i < NumOfResult;i++)
        {
            con[i] = 0 ;
            trans_v[i] = 0;
        }
*/
    }
}

#pragma vector=PORT4_VECTOR
__interrupt void port_4(void)
{
    t+=1;       //�������� ��Ӧ����
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

