#include"stc12c5a.h"
#include"intrins.h"
#include"tlc2543.h"  //ad
#include"main.h"    //��Ҫע��
#include"st7565.c"  //12864

#include "x9103.c"

/****************************************
*��·AD�� �ֱ����10�Σ�
*IN0:�����ѹ��
*IN1:�����ѹ��
*IN2��IN3:���������1��2 ����
*IN4:����ʶ��
********************************************/
unsigned int xdata AD_[5][10] = 0;
double temp[5] = 0;
uint  AD_num[5]=0,e = 0;
uchar aps=0,adtime=0,ad_chunnel = 0,showts = 0;

uchar ocp = 30;//��������  һ��0.1

bit d2buff = 0;

void delay(uint t)
{
	while(t--);
}

/*  Ӳ��SPI
void InitSPI()
{
	AUXR1 = 0X00;
    SPDAT = 0;      //initial SPI data
    SPSTAT = SPIF | WCOL;    //SPI״̬�Ĵ���
    SPCTL = SPEN | MSTR | SPSPEEDH;        //SPI���ƼĴ���
}
uchar WriteByte(uchar temp)
{
//	SPCTL = SPEN | MSTR | SPSPEEDH;        //SPI���ƼĴ���
	SPDAT = temp;
    while (!(SPSTAT & SPIF));   //wait send complete
    SPSTAT = SPIF | WCOL;       //spi״̬�Ĵ���
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

/*************���ģ��SPI*****************************/
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



/************�Ѷ����˲�*****************
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

/******************ð������****************************/
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

/*******************����ƽ��ֵ*******************************************/
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

/****************12864��ʾ���********************/
void ad_show()
{

	/**********************�����ѹ**********************************/
		lcd_putnumstr(32,0,0,AD_num[0]/10000);
		Lcd12864_Write16CnCHAR(40,0,0,".");
		lcd_putnumstr(48,0,0,AD_num[0]%10000/1000);
		lcd_putnumstr(56,0,0,AD_num[0]%10000%1000/100);
//		lcd_putnumstr(64,0,0,AD_num[0]%10000%1000%100/10);
//		lcd_putnumstr(72,0,0,AD_num[0]%10000%1000%100%10);

    /******************************��������****************************/
				lcd_putnumstr(104,0,0,ocp/10);
		Lcd12864_Write16CnCHAR(112,0,0,".");
		lcd_putnumstr(120,0,0,ocp%10);
//		lcd_putnumstr(120,0,0,AD_num[1]%10000%1000/100);
//		lcd_putnumstr(112,0,0,AD_num[1]%10000%1000%100/10);
//		lcd_putnumstr(120,0,0,AD_num[1]%10000%1000%100%10);

    /******************************�����ѹ****************************/
				lcd_putnumstr(40,2,0,AD_num[2]/10000);
		Lcd12864_Write16CnCHAR(48,2,0,".");
		lcd_putnumstr(56,2,0,AD_num[2]%10000/1000);
		lcd_putnumstr(64,2,0,AD_num[2]%10000%1000/100);
//		lcd_putnumstr(64,2,0,AD_num[2]%10000%1000%100/10);
//		lcd_putnumstr(72,2,0,AD_num[2]%10000%1000%100%10);

    /******************************�������****************************/
				lcd_putnumstr(40,4,0,AD_num[3]/10000);
		Lcd12864_Write16CnCHAR(48,4,0,".");
		lcd_putnumstr(56,4,0,AD_num[3]%10000/1000);
		lcd_putnumstr(64,4,0,AD_num[3]%10000%1000/100);
}

uchar x9c = 0;


uint xpd(double value)
{
 	static const Vcc = 5.15 , R1 = 524;
	double tmp = (Vcc - value)/R1;
	double R2 = value / tmp;
	return ((R2 + 50)/10);
}

uchar swit()
{
	uchar te = 0xff;
	if(sw1 == 0)te=1;
	if(sw2 == 0)te=2;
	if(sw3 == 0)te=3;
	if(sw4 == 0)te=4;
	if(sw5 == 0)te=5;
	return te;
}
	

void zdInit()
{
	AUXR = 0x80;
   	TMOD = 0x01;
	TH0 = (65536-200)/256;
	TL0 = (65536-200)%256;
	ET0 = 1;
	TR0 = 1;
	EA = 1;
}

void systemInit()
{
	 zdInit();
	P4SW = P44EN | P45EN | P46EN;
	ocpOff;
	x9cInit();  //
	Lcd12864_Init();
	Lcd12864_ClearScreen(0x00);//12864����
	Lcd12864_Write16CnCHAR(0,0,0,"inV:     OCP:");
	Lcd12864_Write16CnCHAR(0,2,0,"outV:");
	Lcd12864_Write16CnCHAR(0,4,0,"outA:");
}

void systemRun()
{
  uchar test = 0,swvalue = 0;
  while(test == 0)
  {
  	  vad_show();
  	  swvalue = swit();
	  if(swvalue != 0xff)
	  {
	  	 switch(swvalue)
		 {
		 	 case 1 : break;
			 case 2 : if(ocp < 40)ocp += 1; break;
			 case 3 : ocp = 30;break;
			 case 4 : if(ocp > 5)ocp -= 1;break;
			 case 5 : break;
			 
		 }
		 delay(5000);
		 while(swit() != 0xff);
	  }
  }

}


void zd1() interrupt 1
{
	unsigned char i=0;
	TH0 = (65536-200)/256;
	TL0 = (65536-200)%256;
	e++;
	adtime++;
	if(adtime == 10)//2.0ms ����һ��  �ֱ���·
	{
		adtime = 0;
		AD_[ad_chunnel][aps] = readAD(ad_chunnel);
		ad_chunnel++;
	}
	if(ad_chunnel == 5){ad_chunnel = 0;aps++;}

	if(aps == 10) //100ms ����һ��
	{
		aps = 0;
		for(i = 0;i < 5;i++) 
		{
			bubble(AD_[i],10);            //ð��
			temp[i]  = Average(AD_[i],1,9); //ƽ��ֵ
			temp[i] = (temp[i] * addTcl2543) *10000;		
		}
	}
	if(e == 1000) //1s ���һ��
	{
		d2buff = ~d2buff;
		LED2 = d2buff;
		e = 0;
		AD_num[showts] = temp[showts];
		showts++;
		if(showts == 5)showts=0;
	}
}

void main()
{
	systemInit();
	while(1)
	{
		systemRun();
	}
}
