#include "lcd_drive.h"

/****************************************************************************
*函数名：TFT_WriteCmd
*输  入：cmd：命令
*输  出：
*功  能：写命令。
****************************************************************************/	  

void TFT_WriteCmd(uint cmd)
{
	uchar cmdH, cmdL;
	cmdH = cmd >> 8;
	cmdL = cmd & 0x00FF;
	
	
	TFT_WR = 1;	 		  //初始化WR
	TFT_CS = 0;			  //打开片选
	
	TFT_RD = 1;           //选择写
	TFT_RS = 0;			  //选择命令
	
	
	TFT_DATAPORT = cmdH; //放置命令数据
	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;
	TFT_DATAPORT = cmdL;

	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;

	TFT_CS = 1;			  //关闭片选	
}

/****************************************************************************
*函数名：TFT_WriteData
*输  入： dat：数据
*输  出：
*功  能: 写数据。
****************************************************************************/	  

void TFT_WriteData(uint dat)
{
	uchar datH, datL;
	datH = dat >> 8;
	datL = dat & 0xFF;
	
	TFT_WR = 1;	 		  //初始化WR
	TFT_CS = 0;			  //打开片选
		
	TFT_RD = 1;           //选择写
	TFT_RS = 1;			  //选择发送数据
	

	TFT_DATAPORT = datH;  //放置命令数据
	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;
	TFT_DATAPORT = datL;	

	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;
	
	TFT_CS = 1;			  //关闭片选
}



/****************************************************************************
*函数名：TFT_WriteCmdData
*输  入：cmd：命令
*      ：dat：数据
*输  出：
*功  能：写命令， 写数据。
****************************************************************************/	  
//
//void TFT_WriteCmdData(uint cmd, uint dat)
//{
//	TFT_WriteCmd(cmd);
//	TFT_WriteData(dat);
//}
/****************************************************************************
*函数名：TFT_Init
*输  入：
*输  出：
*功  能：初始化TFT。
****************************************************************************/	  

void TFT_Init(void)
{
	uint i;

	TFT_RST = 1;
	for(i=500; i>0; i--);
	TFT_RST = 0;
	for(i=500; i>0; i--);
	TFT_RST = 1;
	for(i=5000; i>0; i--);
	
	//TFT_CS = 0;
	
//************* Start Initial Sequence **********//

	WriteComm(0xB0);
	WriteData(0x3F);
	WriteData(0x3F);
	for(i=500; i>0; i--);

	WriteComm(0xB3);
	WriteData(0x02);
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x00);

	WriteComm(0xB4);
	WriteData(0x00);

	WriteComm( 0xC0 );
	WriteData( 0x33);	//03
	WriteData( 0x4F);
	WriteData( 0x00);
	WriteData( 0x10);
	WriteData( 0xA2);
	WriteData( 0x00);
	WriteData( 0x01);
	WriteData( 0x00);

	WriteComm( 0xC1 );
	WriteData( 0x01);
	WriteData( 0x02);
	WriteData( 0x20);
	WriteData( 0x08);
	WriteData( 0x08);
	for(i=5000; i>0; i--);

	WriteComm( 0xC3 );
	WriteData(0x01);
	WriteData(0x00);
	WriteData(0x28);
	WriteData(0x08);
	WriteData(0x08);
	for(i=500; i>0; i--);

	WriteComm(0xC4);
	WriteData(0x11 );
	WriteData(0x01);
	WriteData(0x23);
	WriteData(0x04);
	WriteData(0x00);

	WriteComm(0xC8);//Gamma
	WriteData(0x05);
	WriteData(0x0C);
	WriteData(0x0b);
	WriteData(0x15);
	WriteData(0x11);
	WriteData(0x09);
	WriteData(0x05);
	WriteData(0x07);
	WriteData(0x13);
	WriteData(0x10);
	WriteData(0x20);

	WriteData(0x13);
	WriteData(0x07);
	WriteData(0x05);
	WriteData(0x09);
	WriteData(0x11);
	WriteData(0x15);
	WriteData(0x0b);
	WriteData(0x0c);
	WriteData(0x05);
	WriteData(0x05);
	WriteData(0x02);

	
	WriteComm(0xC9);//Gamma
	WriteData(0x05);
	WriteData(0x0C);
	WriteData(0x05);
	WriteData(0x15);
	WriteData(0x11 );
	WriteData(0x09);
	WriteData(0x05);
	WriteData(0x07);
	WriteData(0x13);
	WriteData(0x10);
	WriteData(0x20);
	WriteData(0x13);
	WriteData(0x07);
	WriteData(0x05);
	WriteData(0x09);
	WriteData(0x11);
	WriteData(0x15);
	WriteData(0x0b);
	WriteData(0x0c);
	WriteData(0x05);
	WriteData(0x05);
	WriteData(0x02);

	WriteComm(0xCA);//Gamma
	WriteData(0x05);
	WriteData(0x0C);
	WriteData(0x0b);
	WriteData(0x15);
	WriteData(0x11);
	WriteData(0x09);
	WriteData(0x05);
	WriteData(0x07);
	WriteData(0x13);
	WriteData(0x10);
	WriteData(0x20);
	WriteData(0x13);
	WriteData(0x07);
	WriteData(0x05);
	WriteData(0x09);
	WriteData(0x11);
	WriteData(0x15);
	WriteData(0x0b);
	WriteData(0x0c);
	WriteData(0x05);
	WriteData(0x05);
	WriteData(0x02);

	WriteComm(0xD0);
	WriteData(0x33);
	WriteData(0x53);
	WriteData(0x87);
	WriteData(0x3b);
	WriteData(0x30);
	WriteData(0x00);

	WriteComm(0xD1 );
	WriteData(0x2c);
	WriteData(0x61);
	WriteData(0x10);

	WriteComm(0xD2 );
	WriteData(0x03);
	WriteData(0x24);

	WriteComm(0xD4 );
	WriteData(0x03);
	WriteData(0x24);


	WriteComm(0xE2);
	WriteData(0x3f);
	for(i=500; i>0; i--);

	TFT_WriteCmd(0x35 );
	WriteData(0x00);

	WriteComm(0x36 );
	WriteData(0x40);  //0000

	WriteComm(0x3A );
	WriteData(0x55);//55 16bit color

	WriteComm(0x2A );
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0xEF);

	WriteComm(0x2B );
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x01);
	WriteData(0x3F);

	WriteComm(0x11) ;
	for(i=500; i>0; i--);
	TFT_WriteCmd(0x29);
	for(i=500; i>0; i--);
	TFT_WriteCmd(0x2C) ;
	for(i=500; i>0; i--);
}


void WriteData(uint i)
{
	TFT_WR = 1;	 		  //初始化WR
	TFT_CS = 0;			  //打开片选
	
	TFT_RD = 1;           //选择写
	TFT_RS = 1;			  //选择发送数据
	
	TFT_DATAPORT = i;
 
	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;
	
	TFT_CS = 1;			  //关闭片选	
}

void WriteComm(uint i)
{
	TFT_WR = 1;	 		  //初始化WR
	TFT_CS = 0;			  //打开片选
	
	TFT_RD = 1;           //选择写
	TFT_RS = 0;			  //选择发送数据
	
	TFT_DATAPORT = i;
 
	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;
	
	TFT_CS = 1;			  //关闭片选	
}

/****************************************************************************
*函数名：TFT_SetWindow
*输  入：xStart：起始X坐标
*      ：yStart：起始Y坐标 
*      ：xEnd：结束X坐标
*      ：yEnd：结束Y坐标
*输  出：
*功  能：设置要操作的窗口。
****************************************************************************/	  

void TFT_SetWindow(uint xStart, uint yStart, uint xEnd, uint yEnd)
{					
	WriteComm(0x2A);
	TFT_WriteData(xStart);
	TFT_WriteData(xEnd);
//	WriteData(xStart>>8);
//	WriteData(xStart&0xff);
//	WriteData(xEnd>>8);
//	WriteData(xEnd&0xff);
   
    WriteComm(0x2b);
	TFT_WriteData(yStart);
	TFT_WriteData(yEnd);
//	WriteData(yStart>>8);
//	WriteData(yStart&0xff);
//	WriteData(yEnd>>8);
//	WriteData(yEnd&0xff);
   
    TFT_WriteCmd(0x2c); 
}

void TFT_WriteColorData(uint color)
{
	uint red = 0, blue = 0, green = 0;
	uint RGB[1];
	//--蓝色处理--//
	red = (color & 0x1F);    //取5位蓝色

	//--绿色处理--//
	green = (color >> 5) & 0x3F; //取6位绿色
	
	//--红色处理--//
	blue = (color >> 11) & 0x1F;  //取5位红色

	RGB[0] = ((red << 11) | (green << 6) | blue);
	

	TFT_CS = 0;
	TFT_RS = 1;
	TFT_RD = 1;

	TFT_DATAPORT = RGB[0] >>8;
	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;
	TFT_DATAPORT = RGB[0];
	TFT_WR = 0;			  //写入时序
	TFT_WR = 1;

	TFT_CS = 1;
}

void TFT_Changegrb(uint color,uint *p)
{
	uint red = 0, blue = 0, green = 0;

	//--蓝色处理--//
	red = (color & 0x1F);    //取5位蓝色

	//--绿色处理--//
	green = (color >> 5) & 0x3F; //取6位绿色
	
	//--红色处理--//
	blue = (color >> 11) & 0x1F;  //取5位红色

	*p = ((red << 11) | (green << 6) | blue);

}

/****************************************************************************
*函数名：GUI_Clearcreen
*输  入：backColor：清屏颜色
*输  出：
*功  能：清屏并涂上颜色。
****************************************************************************/
	  
void TFT_ClearScreen(uint color)
{
  	uint i, j;
	uint grb[2];
	TFT_Changegrb(color,grb);

	TFT_SetWindow(0, 0, TFT_XMAX, TFT_YMAX);	 //作用区域
	TFT_CS = 0;
	TFT_RS = 1;
	TFT_RD = 1;

  	for(i=0; i <  TFT_YMAX+1 ; i++)
	{
		for (j=0; j <  TFT_XMAX+1; j++)
		{
		   //TFT_WriteColorData(color);
		    TFT_DATAPORT =grb[0]>>8;
			TFT_WR = 0;			  //写入时序
			TFT_WR = 1;
			TFT_DATAPORT =grb[0];
			TFT_WR = 0;			  //写入时序
			TFT_WR = 1;

		}
	}
	TFT_CS = 1;
}

