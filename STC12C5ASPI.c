/*------------------------------------------------------------------*/
/* --- STC MCU Limited ---------------------------------------------*/
/* --- STC12C5Axx Series MCU SPI Demo(1 master and 1 slave) --------*/
/*                单主单从   中断方式              */
/* --- Mobile: (86)13922805190 -------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ---------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966----------------------*/
/* --- Web: www.STCMCU.com -----------------------------------------*/
/* --- Web: www.GXWMCU.com -----------------------------------------*/
/* If you want to use the program or the program referenced in the  */
/* article, please specify in which data and procedures from STC    */
/*------------------------------------------------------------------*/

#include "reg51.h"
#define MASTER                  //define:master undefine:slave
#define FOSC        11059200L
#define BAUD        (256 - FOSC / 32 / 115200)

typedef unsigned char BYTE;
typedef unsigned int WORD;
typedef unsigned long DWORD;

sfr  AUXR       =   0x8e;       //Auxiliary register

sfr SPSTAT      =   0xcd;       //SPI status register
#define SPIF        0x80        //SPSTAT.7
#define WCOL        0x40        //SPSTAT.6
sfr SPCTL       =   0xce;       //SPI control register
#define SSIG        0x80        //SPCTL.7
#define SPEN        0x40        //SPCTL.6
#define DORD        0x20        //SPCTL.5
#define MSTR        0x10        //SPCTL.4
#define CPOL        0x08        //SPCTL.3
#define CPHA        0x04        //SPCTL.2
#define SPDHH       0x00        //CPU_CLK/4
#define SPDH        0x01        //CPU_CLK/16
#define SPDL        0x02        //CPU_CLK/64
#define SPDLL       0x03        //CPU_CLK/128
sfr SPDAT       =   0xcf;       //SPI data register
sbit SPISS      =   P1^3;       //SPI slave select, connect to slave' SS(P1.4) pin

sfr IE2         =   0xAF;       //interrupt enable rgister 2
#define ESPI        0x02        //IE2.1

void InitUart();
void InitSPI();
void SendUart(BYTE dat);        //send data to PC
BYTE RecvUart();                //receive data from PC

///////////////////////////////////////////////////////////

void main()
{
    InitUart();                 //initial UART
    InitSPI();                  //initial SPI
    IE2 |= ESPI;
    EA = 1;

    while (1)
    {
#ifdef MASTER                   //for master (receive UART data from PC and send it to slave, in the meantime
                                //            receive SPI data from slave and send it to PC)
        ACC = RecvUart();
        SPISS = 0;              //pull low slave SS
        SPDAT = ACC;            //trigger SPI send
#endif
    }
}

///////////////////////////////////////////////////////////

void spi_isr() interrupt 9 using 1     //SPI interrupt routine 9 (004BH)
{
    SPSTAT = SPIF | WCOL;       //clear SPI status
#ifdef MASTER
    SPISS = 1;                  //push high slave SS
    SendUart(SPDAT);            //return received SPI data
#else                           //for salve (receive SPI data from master and
    SPDAT = SPDAT;              //           send previous SPI data to master)
#endif
}

///////////////////////////////////////////////////////////

void InitUart()
{
    SCON = 0x5a;                //set UART mode as 8-bit variable baudrate
    TMOD = 0x20;                //timer1 as 8-bit auto reload mode
    AUXR = 0x40;                //timer1 work at 1T mode
    TH1 = TL1 = BAUD;           //115200 bps
    TR1 = 1;
}

///////////////////////////////////////////////////////////

void InitSPI()
{
    SPDAT = 0;                  //initial SPI data
    SPSTAT = SPIF | WCOL;       //clear SPI status
#ifdef MASTER
    SPCTL = SPEN | MSTR;        //master mode
#else
    SPCTL = SPEN;               //slave mode
#endif
}

///////////////////////////////////////////////////////////

void SendUart(BYTE dat)
{
    while (!TI);                //wait pre-data sent
    TI = 0;                     //clear TI flag
    SBUF = dat;                 //send current data
}

///////////////////////////////////////////////////////////

BYTE RecvUart()
{
    while (!RI);                //wait receive complete
    RI = 0;                     //clear RI flag
    return SBUF;                //return receive data
}

