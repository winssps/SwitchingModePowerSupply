#include"STC12C5A.h"
//#include"12864.c"
#include"main.h"
#include"st7565.c"

void delay(uint t)
{
	while(t--);
}

void delayMs(uint s)
{
	uint i=0,j=0;
	for(i = s; i > 0;i--)
	{
		for(j = 100;j > 0;j--);
	}
}

void Delay10ms(unsigned int c)
{
    unsigned char a,b;
    for(;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}

void InitADC()
{
	P1M0 = 0XF8;
	P1M1 = 0XF8;
    P1ASF = 0xF8;
//		P1ASF = P13ASF;
    ADC_RES = 0;
	ADC_RESL = 0;
	AUXR1 = 0x00;
    ADC_CONTR = ADC_POWER | ADC_SPEEDHH | ADC_START | 0;
    delay(1100);                       //ADC power-on delay and Start A/D conversion
}

void Initzd1()
{
	TMOD = 0X01;
	TH0 = (65536-50000)/256;
	TL0 = (65536-50000)%256;
	ET0 = 1;
	TR0 = 1;
}

/*----------------------------
ADC interrupt service routine
----------------------------*/
void adc_isr() interrupt 5 using 1
{
    ADC_CONTR &= !ADC_FLAG;         //Clear ADC interrupt flag
  //  adcres = ADC_RES<< 2;              //Get ADC high 8-bit result and Send to UART
//	adcres += ADC_RESL;         //switch to next channel

    ADC_CONTR = ADC_POWER | ADC_SPEEDHH | ADC_START | 0;
}

uint adcres=0;
uint adcNumber;
float temp=0;

void zd1() interrupt 1
{
	TH0 = (65536-50000)/256;
	TL0 = (65536-50000)%256;
//	number = ch-3;	
	adcres = ADC_RES;              //Get ADC high 8-bit result and Send to UART
	adcres *= 4;
	adcres += ADC_RESL;         //switch to next channel
	temp = adcres;
	adcNumber = ((temp*addo)*1000);
}
void main()
{
	uchar i = 0;
	InitADC();
	Initzd1();
	EADC = 1;
	EA = 1;
	Lcd12864_Init();
	Lcd12864_ClearScreen(0x00);//清屏
	Lcd12864_Write16CnCHAR(0,0,0," welcome to Mlog ");
	Lcd12864_Write16CnCHAR(0,2,0,"输入电压: 5.7V");
	Lcd12864_Write16CnCHAR(0,4,0,"输出电压: 12.0V");
	Lcd12864_Write16CnCHAR(0,6,0,"输出功率: xxxx");
	
	while (1)
	{
		lcd_putnumstr(72,6,0,adcNumber/1000);
		Lcd12864_Write16CnCHAR(80,6,0,".");
		lcd_putnumstr(88,6,0,adcNumber%1000/100);	
		lcd_putnumstr(96,6,0,adcNumber%1000%100/10);	
		lcd_putnumstr(104,6,0,adcNumber%1000%100%10);	
	}
}