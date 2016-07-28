#ifndef __ST7565_H
#define __ST7565_H

#include<intrins.h>

//---�����ֿ�ͷ�ļ�
#define CHAR_CODE


//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

//--��ʱʹ�õ�IO��--//
#define DATA_PORT P0
sbit LCD12864_CS   = P2^6;
sbit LCD12864_RSET = P2^7;
sbit LCD12864_RS   = P2^4;
sbit LCD12864_RW   = P1^0;
sbit LCD12864_RD   = P2^5;

//--����ȫ�ֺ���--//
void LcdSt7565_Write(uchar cmd,at,dat);
void Lcd12864_Init();
void Lcd12864_ClearScreen(uchar temp);
uchar Lcd12864_Write16CnCHAR(uchar x, uchar y, at, uchar *cn);

#endif
