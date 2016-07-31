#include"x9103.h"


uchar mmdz102=0,mmdz103=0;

/************
*bin : 0 x9c102   1 c9c103  
*fx : 0 加   1 减
*dat : 要走的量程 number
*例如： x9c103(0,0,50)  选中102 往前走 50个量程（500欧姆）
*/



void x9cc(uchar bin,fx,dat)
{
	uchar m = 0;
	X9C103_INC = 1;
	if(bin)X9C103_CS = 0;
		else X9C102_CS = 0;
	X9C103_UD = fx;
	_nop_();
	for(m = 0;m < dat;m++)
	{
		X9C103_INC = 0;
		_nop_();
		_nop_();
		X9C103_INC = 1;
	//	if(bin)X9C103_UD ? mmdz103-- : mmdz103++;
		//S	else X9C103_UD ? mmdz102-- : mmdz102++;
	}
	if(bin)X9C103_CS = 1;
		else X9C102_CS = 1;
}



void x9c10(uchar bin,fx,dat)
{
	uchar m = 0;
	X9C103_INC = 1;
	if(bin)X9C103_CS = 0;
		else X9C102_CS = 0;
	X9C103_UD = fx;
	_nop_();
	for(m = 0;m < dat;m++)
	{
		X9C103_INC = 0;
		_nop_();
		_nop_();
		X9C103_INC = 1;
		if(bin)X9C103_UD ? mmdz103-- : mmdz103++;
			else X9C103_UD ? mmdz102-- : mmdz102++;
	}
	if(bin)X9C103_CS = 1;
		else X9C102_CS = 1;
}


void x9c10Run(uchar bin,dat)
{
	if(dat >= 0 && dat < 100)
	{
		if(bin)
			dat > mmdz103 ? x9c10(1,0,dat - mmdz103) : x9c10(1,1,mmdz103 - dat);
		else
			dat > mmdz102 ? x9c10(0,0,dat - mmdz102) : x9c10(0,1,mmdz102 - dat);
	}	
}


void x9cInit()
{
	x9c10(0,1,100);x9c10(1,1,100);//初始化x9013
	mmdz102 = 1;mmdz103=1; 
}

/*

void main(void)
{
	uchar m=0,n=0;
	x9cInit();
	while(1)
	{
		if(sw1 == 0)//++
		{
			x9c10Run(1,50);
			x9c10Run(0,50);
			delay_nms(1000);
		}
		if(sw2 == 0)//--
		{
			x9c10Run(0,10);
			x9c10Run(1,10);
			delay_nms(1000);
		}
	}
}*/
