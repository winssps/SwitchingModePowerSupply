/******************************************************************************/
#ifndef __MAIN_H_
#define __MAIN_H_
/******************************************************************************/

#define uchar unsigned char 
#define uint unsigned int 

#define addo 5.0000/1023.0000
#define addTcl2543 3.0000/4095.0000

#define ocpOff ocpIo = 0
#define ocpOn ocpIo = 1

sbit LED2 = P3^7;
sbit sw1 = P1^3;
sbit sw2 = P1^4;
sbit sw3 = P1^5;
sbit sw4 = P1^6;
sbit sw5 = P1^7;
sbit ocpIo = P3^6;




void delay(uint t);
uint readAD(uchar chunnel);
void bubble(unsigned int* array,uchar len);
double Average(unsigned int *array,unsigned char index,unsigned char len);
void ad_show();
double JRvalue(double value);
uchar swit();
void zdInit();
void system_Init();
void system_Run();


/******************************************************************************/
#endif
/******************************************************************************/
