#include"MAIN.h"
#include"12864.h"


void yjing(uchar bin,da)
{
	yjrw = 0;
	yjrs = bin;
	yje = 0;
	delay(2);
	P0 = da;
	delay(5);
	yje = 1;
	delay(5);
	yje = 0;
	delay(5);
}

void yjInit()
{
	psb = 1;
	yjing(0,0x30);
	delayMs(10);
	yjing(0,on);
	delayMs(10);
	yjing(0,0x01);
	delayMs(10);
}

void setPosition(uchar x,y)
{
	uchar p = 0;
	switch(x%4)
	{
		case 0 : p = 0x80;break;
		case 1 : p = 0x90;break;
		case 2 : p = 0x88;break;
		case 3 : p = 0x98;break;
		default:break;
	}
	p += y;
	yjing(0,p);
}

void writeStr(uchar *str)
{
	uchar i = 0;

	while(str[i] != '\0')
	{
		yjing(1,str[i++]);
	}
}





