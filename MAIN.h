/******************************************************************************/
#ifndef __MAIN_H_
#define __MAIN_H_
/******************************************************************************/

#define uchar unsigned char 
#define uint unsigned int 

#define addo 5.0000/1023.0000
#define addTcl2543 3.0000/4095.0000

sbit LED2 = P3^6;
sbit sw1 = P5^1;
sbit sw2 = P5^0;
sbit sw3 = P2^4;
sbit sw4 = P2^3;
sbit sw5 = P3^7;


sbit OCPIO = P2^2;

void delay(uint t);
uint readAD(uchar chunnel);
void bubble(unsigned int* array,uchar len);
double Average(unsigned int *array,unsigned char index,unsigned char len);
void ad_show();
uint xpd(double value);
uchar swit();
void zdInit();
void system_Init();
void system_Run();


/******************************************************************************/
#endif
/******************************************************************************/
