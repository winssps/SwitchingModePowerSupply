#include"stc12c5a.h"
#include"intrins.h"
#include"tlc2543.h"  //ad
#include"main.h"    //主要注释
#include"st7565.c"  //12864

#include "x9103.c"

sbit s1 = P1^3;
sbit s2 = P1^4;
sbit s3 = P1^5;
sbit s4 = P1^6;
sbit s5 = P1^7;


/****************************************
*五路AD： 分别采样10次，
*IN0:输入电压、
*IN1:输出电压、
*IN3、IN3:输出电流（1）、
*IN4:负载识别	  电阻
********************************************/
unsigned int xdata AD_[5][10] = 0;
double temp[5] = 0;
uint  AD_num[5]=0,e = 0;
uchar aps=0,adtime=0,ad_chunnel = 0,showts = 0;

uchar ocp = 30;//过流保护  一次0.1

bit d2buff = 0,ocpbuff = 0,load = 0;

void delay(uint t)
{
	while(t--);
}

/*  硬件SPI
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

/*************软件模拟SPI*****************************/
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



/************费尔曼滤波*****************
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

/******************冒泡排序****************************/
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

/*******************计算平均值*******************************************/
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

/****************12864显示结果********************/
void ad_show()
{

	/**********************输入电压**********************************/
		lcd_putnumstr(64,0,0,AD_num[0]/10000);
		lcd_putnumstr(72,0,0,AD_num[0]%10000/1000);
		Lcd12864_Write16CnCHAR(80,0,0,".");
		lcd_putnumstr(88,0,0,AD_num[0]%10000%1000/100);
		lcd_putnumstr(96,0,0,AD_num[0]%10000%1000%100/10);

    /******************************输出电流****************************/
		lcd_putnumstr(64,2,0,AD_num[1]/1000);
		Lcd12864_Write16CnCHAR(72,2,0,".");
		lcd_putnumstr(80,2,0,AD_num[1]%1000/100);
		lcd_putnumstr(88,2,0,AD_num[1]%1000%100/10);

    /******************************输出电压****************************/
		lcd_putnumstr(64,4,0,AD_num[3]/1000);
		Lcd12864_Write16CnCHAR(72,4,0,".");
		lcd_putnumstr(80,4,0,AD_num[3]%1000/100);
		lcd_putnumstr(88,4,0,AD_num[3]%1000%100/10);

		if(load)
		{
			
			lcd_putnumstr(40,6,0,ocp/10);
			Lcd12864_Write16CnCHAR(48,6,0,".");
			lcd_putnumstr(56,6,0,ocp%10);

			lcd_putnumstr(88,6,0,AD_num[4]/1000);
			lcd_putnumstr(96,6,0,AD_num[4]%1000/100);
			lcd_putnumstr(104,6,0,AD_num[4]%1000%100/10);
			lcd_putnumstr(112,6,0,AD_num[4]%1000%100%10);
		}
		else if(!load) 
		{
    /******************************过流保护****************************/
			
			lcd_putnumstr(56,6,0,ocp/10);
			Lcd12864_Write16CnCHAR(64,6,0,".");
			lcd_putnumstr(72,6,0,ocp%10);	
		}
}

uchar x9c = 0;


double JRvalue(double value)
{
	double Iz = value / 1000.0;
	double Jr = (3.00 - value)/Iz;
	return Jr;
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
	P4SW = 0x70;
//	x9cInit();  //
	Lcd12864_Init();
	Lcd12864_ClearScreen(0x00);//12864清屏
	Lcd12864_Write16CnCHAR(0,0,0,"Uin  :        V");
	Lcd12864_Write16CnCHAR(0,2,0,"Iout :        A");
	Lcd12864_Write16CnCHAR(0,4,0,"Uout :        V");
	ocpOff;
}

void systemRun()
{
  uchar test = 0,swvalue = 0;
  Lcd12864_Write16CnCHAR(0,6,0,"OCP  :      ");
  while(test == 0)
  {
  	  ad_show();
  	  swvalue = swit();
	  if(swvalue != 0xff)
	  {
	  	 switch(swvalue)
		 {
		 	 case 1 : x9cc(1,0,1);break;
			 case 2 : x9cc(1,1,1);break;
			 case 3 : if(ocp < 40)ocp += 1;x9cc(0,0,1);break;
			 case 4 : if(ocp > 5)ocp -= 1;x9cc(0,1,1);break;
			 case 5 : 
			 		load = ~load;LED2 = 1;
			 		Lcd12864_Write16CnCHAR(0,6,0,"               ");
					Lcd12864_Write16CnCHAR(0,6,0,"OCP:     R:   ");
			 		test = 1;
			 			break;
					default:break;
			 
		 }
		 delay(5000);
		 while(swit() != 0xff);
	  }	
  }
  while(test == 1)
  {
  	  ad_show();
  	  swvalue = swit();
	  if(swvalue != 0xff)
	  {
	  	 switch(swvalue)
		 {
		 	 case 1 : break;
			 case 2 :  break;
			 case 3 : if(ocp < 40)ocp += 1;;break;
			 case 4 : if(ocp > 5)ocp -= 1;break;
			 case 5 : 
			 		load = ~load;LED2 = 1;
			 		Lcd12864_Write16CnCHAR(0,6,0,"               ");
					Lcd12864_Write16CnCHAR(0,6,0,"OCP  :      ");
			 		test = 0;
			 			break;
					default:break;
			 
		 }
		 delay(5000);
		 while(swit() != 0xff);
	  }	
  }

}

uchar sw()
{
	uchar te = 0xff;
	if(s1 == 0)te = 1;
	if(s2 == 0)te = 2;
	if(s3 == 0)te = 3;
	if(s4 == 0)te = 4;
	return te;
}


void zd1() interrupt 1
{
	unsigned char i=0;
	TH0 = (65536-200)/256;
	TL0 = (65536-200)%256;
	e++;
	adtime++;
	if(adtime == 10)//2.0ms 采样一次  分别四路
	{
		adtime = 0;
		AD_[ad_chunnel][aps] = readAD(ad_chunnel);
		ad_chunnel++;
	}
	if(ad_chunnel == 5){ad_chunnel = 0;aps++;}

	if(aps == 10) //100ms 计算一次
	{
		aps = 0;
		for(i = 0;i < 5;i++) 
		{
			bubble(AD_[i],10);            //冒泡
			temp[i]  = Average(AD_[i],1,9); //平均值
		                	//输入电压
			 if(i == 0){temp[i] = ((temp[i] * 6.0) * addTcl2543) *1000;}
			 else if(i == 1){temp[i] = (((temp[i] * 2.0) * addTcl2543) *1000.0);}
			 else if(i == 3){temp[i] = (((temp[i] * 2.0) * addTcl2543) *1000.0);}
			 else if(i == 4) {
				temp[i] = (temp[i] * addTcl2543);
			 	temp[i] = JRvalue(temp[i]);
				}			
		}
	}
	if(e == 5000) //1s 输出一次
	{
		d2buff = ~d2buff;
		if(!load)LED2 = d2buff;
		e = 0;
		AD_num[showts] = temp[showts];
		showts++;
		if(showts == 5)showts=0;
	}
}

void main()
{
	systemInit();
//	x9cInit();  //	    
	while(1)
	{
			
		systemRun();
	//	ad_show();
	}
}



