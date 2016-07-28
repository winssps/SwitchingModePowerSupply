#ifndef __LCD_DRIVE_H
#define __LCD_DRIVE_H



//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint  unsigned int
#endif

#ifndef ulong
#define ulong  unsigned long
#endif

//---定义使用的IO口---//
sbit	    TFT_RST = P3^3;   //复位
sbit	    TFT_CS  = P2^7;	  //片选
sbit	    TFT_RS  = P3^2;	  //数据命令选择端
sbit	    TFT_WR  = P2^5;	  //读写控制
sbit        TFT_RD  = P2^6;   //读写控制

#define     TFT_DATAPORT  P0    

//---定义颜色的宏---//
#define WHITE          0xFFFF
#define BLACK          0x0000
#define BLUE           0x001F
#define RED            0xF800
#define MAGENTA        0xF81F
#define GREEN          0x07E0
#define CYAN           0x7FFF
#define YELLOW         0xFFE0		 //定义颜色的宏

//---定义屏的大小---//
#define TFT_XMAX ((uint)319)//		//设置TFT屏的大小
#define TFT_YMAX ((uint)479)//

//-- 声明全局函数 --//
void TFT_WriteCmd(uint cmd);
void TFT_WriteData(uint dat);
void TFT_Init(void);
void TFT_SetWindow(uint xStart, uint yStart, uint xEnd, uint yEnd);
void TFT_ClearScreen(uint color);
void TFT_WriteColorData(uint color);
void WriteData(uint i);
void WriteComm(uint i);
void DispColor(unsigned int color);
void TFT_Changegrb(uint color,uint *p);


#endif
