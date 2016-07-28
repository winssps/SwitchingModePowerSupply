#include"stc12c5a.h"
#include"intrins.h"
#include"tlc2543.h"  //ad
#include"main.h"    //主要注释
#include"st7565.c"  //12864

#include "x9103.c"

//#include "lcd_drive.c"
//#include "gui.c"


unsigned int xdata AD_[4][10] = 0;
double temp[4] = 0;
uint  AD_num[4]=0,e = 0;
uchar aps=0,adtime=0,ad_chunnel = 0,showts = 0;



void delay(uint t)
{
	while(t--);
}

/*
void InitSPI()
{
	AUXR1 = 0X00;
    SPDAT = 0;      //initial SPI data
    SPSTAT = SPIF | WCOL;    //SPI状态寄存器
    SPCTL = SPEN | MSTR | SPSPEEDH;        //SPI控制寄存器
}

uchar WriteByte(uchar temp)
{
//	SPCTL = SPEN | MSTR | SPSPEEDH;        //SPI控制寄存器
	SPDAT = temp;
    while (!(SPSTAT & SPIF));   //wait send complete
    SPSTAT = SPIF | WCOL;       //spi状态寄存器
	delay(20);
	return SPDAT;
}

*/
/*
uint revAD(uchar chunnel)
{
	uint doc = 0 , a = 0, b = 0;
	ad_cs = 0;
	a = WriteByte( (chunnel<<4) | 0x0c );
	b = WriteByte(0);
	ad_cs = 1;
	a <<= 8;
	doc = a | b;
	doc >>= 4;
	return doc;
}*/

uint readAD(uchar chunnel)
{
	uchar i = 0,dout = ad_chunnel_select[chunnel];
	uint din=0;
	_nop_();
	_nop_();
	_nop_();
	ad_cs = 0;
//	ad_clock = 0;

	for(i = 0;i < 16;i++)
	{
		ad_clock = 1;
		if(dout & 0x80)ad_in = 1;
		else ad_in = 0;
		dout <<=1;
		ad_clock = 0;
		_nop_();
	}
	for(i=0;i<16;i++)
	{
		
		if(ad_out == 1)din |= 0x0001;
		ad_clock = 1;
		din <<= 1;
		ad_clock = 0;
		_nop_();
	}
	ad_cs = 1;
	din >>= 4;
	return (din);
}



/*
double KalmanFilter(const double ResrcData,
					double ProcessNiose_Q,
					double MeasureNoise_R)
{
double R = MeasureNoise_R;
double Q = ProcessNiose_Q;

    static double x_last;

    double x_mid = x_last;
    double x_now;

    static double p_last;

    double p_mid ;
    double p_now;
    double kg;        

    x_mid=x_last; //x_last=x(k-1|k-1),x_mid=x(k|k-1)
    p_mid=p_last+Q; //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=??
    kg=p_mid/(p_mid+R); //kg?kalman filter,R???
    x_now=x_mid+kg*(ResrcData-x_mid);
            
    p_now=(1-kg)*p_mid;  

    p_last = p_now; 
    x_last = x_now; 

    return x_now;
}
*/


void bubble(unsigned int* array,uchar len)
{
	uchar i = 0,j = 0;
	unsigned int tmp;
	for(i = 0;i < len;i++)
	    {
	        for(j=0;j < len;j++)
	        {
	            if(array[j] > array[i])
	            {
	                tmp = array[j];
	                array[j] = array[i];
	                array[i] = tmp;
	            }
	        } 
	    }
}


double Average(unsigned int *array,unsigned char index,unsigned char len)
{
  double aver=0,count=index;
 int i;
 for(i=index;i<(len-index);i++)
 {
   aver+=array[i]; 
  aver/=(double)(count++==index?1:2); 
 }
 return aver;
}


void ad_show()
{
		lcd_putnumstr(0,4,0,AD_num[0]/10000);
		Lcd12864_Write16CnCHAR(8,4,0,".");
		lcd_putnumstr(16,4,0,AD_num[0]%10000/1000);
		lcd_putnumstr(24,4,0,AD_num[0]%10000%1000/100);
		lcd_putnumstr(32,4,0,AD_num[0]%10000%1000%100/10);
		lcd_putnumstr(40,4,0,AD_num[0]%10000%1000%100%10);

				lcd_putnumstr(80,4,0,AD_num[1]/10000);
		Lcd12864_Write16CnCHAR(88,4,0,".");
		lcd_putnumstr(96,4,0,AD_num[1]%10000/1000);
		lcd_putnumstr(104,4,0,AD_num[1]%10000%1000/100);
		lcd_putnumstr(112,4,0,AD_num[1]%10000%1000%100/10);
		lcd_putnumstr(120,4,0,AD_num[1]%10000%1000%100%10);

				lcd_putnumstr(0,6,0,AD_num[2]/10000);
		Lcd12864_Write16CnCHAR(8,6,0,".");
		lcd_putnumstr(16,6,0,AD_num[2]%10000/1000);
		lcd_putnumstr(24,6,0,AD_num[2]%10000%1000/100);
		lcd_putnumstr(32,6,0,AD_num[2]%10000%1000%100/10);
		lcd_putnumstr(40,6,0,AD_num[2]%10000%1000%100%10);

				lcd_putnumstr(80,6,0,AD_num[3]/10000);
		Lcd12864_Write16CnCHAR(88,6,0,".");
		lcd_putnumstr(96,6,0,AD_num[3]%10000/1000);
		lcd_putnumstr(104,6,0,AD_num[3]%10000%1000/100);
		lcd_putnumstr(112,6,0,AD_num[3]%10000%1000%100/10);
		lcd_putnumstr(120,6,0,AD_num[3]%10000%1000%100%10);

}

uchar x9c = 0;


uint xpd(double value)
{
 	static const Vcc = 5.15 , R1 = 524;
	double tmp = (Vcc - value)/R1;
	double R2 = value / tmp;
	return ((R2 + 50)/10);
}


void zd1() interrupt 1
{
	unsigned char i=0;
	TH0 = (65536-250)/256;
	TL0 = (65536-250)%256;
	e++;
	adtime++;
	if(adtime == 10)//2.5ms 采样一次  分别四路
	{
		adtime = 0;
		AD_[ad_chunnel][aps] = readAD(ad_chunnel);
		ad_chunnel++;
	}
	if(ad_chunnel == 4){ad_chunnel = 0;aps++;}

	if(aps == 10) //100ms 计算一次
	{
		aps = 0;
		for(i = 0;i < 4;i++) 
		{
			bubble(AD_[i],10);            //冒泡
			temp[i]  = Average(AD_[i],1,9); //平均值
			temp[i] = (temp[i] * addTcl2543) *10000;		
		}
	}
	if(e == 1000) //1s 输出一次
	{
		e = 0;
		AD_num[showts] = temp[showts];
		showts++;
		if(showts == 4)showts=0;
	
	}
	
}

void main(void)
{

	TMOD = 0x01;
	TH0 = (65536-250)/256;
	TL0 = (65536-250)%256;
	ET0 = 1;
	TR0 = 1;
	EA = 1;
	
	x9cInit();  //
	x9c10Run(1,60);
//	x9c10Run(0,90);
	Lcd12864_Init();
	Lcd12864_ClearScreen(0x00);//清屏
	Lcd12864_Write16CnCHAR(0,0,0,"Welcome to ");
	Lcd12864_Write16CnCHAR(0,2,0," using the AD/C. ");
	
//	x9c10Run(1,70);
	while(1)
	{
	//	x9c10Run(0,xpd(0.5));
		ad_show();
	}
}
