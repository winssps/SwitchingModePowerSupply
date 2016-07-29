#include <AT89X55.H>
#define		INT8U		unsigned char
#define		INT16U		unsigned int
#include "CC1100.h"
#include "lcd1602.h"
#include "24Cxx.h"
sbit sgn_led=P1^0;   
sbit alarm_led=P1^1;
#define LOCK_ON  P3&=~(1<<7)  //开锁
#define LOCK_OFF P3|=(1<<7)	  //关锁
#define BUZZ_ON  P3&=~(1<<6)  //蜂鸣器开
#define BUZZ_OFF P3|=(1<<6)	  //蜂鸣器关
unsigned char password[6];	  //6位密码值
//按键枚举
typedef enum key_type
{
	 KEY_NONE=255,
   KEY_0=0,
   KEY_1=1,
	KEY_2=2,
	KEY_3=3,
	KEY_4=4,
	KEY_5=5,
	KEY_6=6,
	KEY_7=7,
	KEY_8=8,
	KEY_9=9,
	KEY_DEL=10,
	KEY_ADD=11,
	KEY_INQ=12,
	KEY_SET=13,
	KEY_CLEAR=14,
	KEY_OK=15,

};
 enum  key_type key;

extern void delaynus(unsigned int t);
//======毫秒延时======
void delaynms(unsigned int t)
{
  unsigned int i;
  while(t--)
   for(i=0;i<120;i++)
   {
     
   }
}
//检查密码是否正确，正确返回1
unsigned char check_code(unsigned char *P)
{
   unsigned char i;
   for(i=0;i<6;i++)
   {
     if((*P++)!=password[i])return 0;  //密码不对
   }
  return 1;
}

//毫秒级延时函数
void delay_nms(unsigned int t)
{
  unsigned int i;
  while(t--)
   for(i=0;i<120;i++)
   {
     
   }
}


void main(void)
{
	unsigned char leng =0;
	unsigned char tf =0;
	unsigned char TxBuf[1]={0};	 // 8字节, 如果需要更长的数据包,请正确设置
	unsigned char RxBuf[1]={0};
	unsigned char new_code[6];
	unsigned char input[6],input_position=0;
	bit key_state=0;    //锁的状态
	unsigned char i;
	unsigned char sys_state=0;   //系统状态 0：正常状态  1：输入旧密码  2  输入新密码
	unsigned char error_cnt=0;  //错误次数
	BL=0;	         //背光开
	init_lcd();		 //初始液晶
	LCD_write_string(4,0,"wireless ");
	LCD_write_string(1,1,"password lock");	 //开机显示
	delaynms(1000);
	LCD_Clear();
	while(!CC1100_init())	  //等待初始化RF模块成功
	{
	  alarm_led=!alarm_led;	  //如果初始化不成功，红灯闪烁
	  LCD_write_string(2,1,"RF1100 error");
	}
	alarm_led=1;
	AT24C04_ReadPage(0,password,6);	  //读取6位密码
	for(i=0;i<6;i++)	    //初始化密码
	{
      if(password[i]>9)
	    password[i]=8;
	}
	LCD_Clear();
	LCD_write_string(1,0,"input password ");

	while(1)
	{
		leng =1; // 预计接受1 bytes
   		if(halRfReceivePacket(RxBuf,&leng))//看有没有接收到数据
		{
			BUZZ_ON;                //开蜂鸣器
			key=RxBuf[0];			//获取按键值
			if(	key<10)				//数字按键
			{	 	
			  if(input_position<6)	//少于6位
			  {
			   if(input_position==0) //一个都没输入，先清掉显示区域
			   {
			     LCD_write_string(0,1,"                ");
			   }
			   LCD_write_char(4+input_position,1,key+'0'); //显示输入的数字
				 delay_nms(200);
				 LCD_write_char(4+input_position,1,'*'); //显示*
			   input[input_position]=key;  
			   input_position++;
			  }
			}
			else if	(key==KEY_CLEAR)	  //【清除】按键
			{
			 LCD_write_string(0,1,"                ");
			 input_position=0;
			}
			else if	(key==KEY_DEL)	    //退格按键
			{
			 if(input_position)
			 {
			   input_position--;
			   LCD_write_char(4+input_position,1,' ');
			 }			 
			}
			else if	(key==KEY_OK)	 //【确定】按键
			{
			  if(input_position<6)
				 {
				   LCD_write_string(1,1,"must be 6 code");
				   input_position=0;			   
				 }
			  else if(sys_state<2)	  //输密码开锁状态 或者输旧密码状态
				 {
					if(check_code(input))  //密码正确
					 {
					    sgn_led=0;
						error_cnt=0;	
						if (sys_state==0)	//输密码开锁状态
						{
						    key_state=!key_state;
							if(key_state==1)
						  	 LOCK_ON;
							else
							{
							 LOCK_OFF;
							}
							LCD_write_string(1,1,"password is OK");
						}
						else
						{
						  LCD_Clear();
						  LCD_write_string(3,0,"input new");
						  sys_state=2;   //切换到输入新密码
						}
						
					   input_position=0;
					   delaynms(100);
					   sgn_led=1;	
					 }
					 else  //密码错误
					 {
					   LCD_write_string(1,1,"password error");
					   error_cnt++;
					   if(error_cnt>=3)	 //错误3次以上 报警
					   {
						   alarm_led=0;
						   BUZZ_ON;delaynms(100);BUZZ_OFF;delaynms(100);
						   BUZZ_ON;delaynms(100);BUZZ_OFF;delaynms(100);
						   BUZZ_ON;delaynms(100);BUZZ_OFF;delaynms(100);
						   BUZZ_ON;delaynms(100);BUZZ_OFF;delaynms(100);
						   BUZZ_ON;delaynms(100);BUZZ_OFF;delaynms(100);
						   alarm_led=1;
					   }
					   input_position=0;
					 }
				}
				else if(sys_state==2)	  //第一次输新密码状态
				 {
				   for(i=0;i<6;i++)
				    new_code[i]=input[i]; //保存第一次输入的6位新密码
				   LCD_Clear();
				   LCD_write_string(4,0,"Re-enter");
				   sys_state=3;	   //切换到再次输入新密码
				   input_position=0;
				 }
				else if(sys_state==3)	  //第2次输新密码状态
				 {
				   LCD_Clear();
				   for(i=0;i<6;i++)
				   {
				    if(new_code[i]!=input[i])break;  //2次密码不一致
				   }
				   if(i==6)	 //2次密码一致
				   {
				     LCD_write_string(1,1,"new code set ok");
					 for(i=0;i<6;i++)
				       password[i]=input[i];
					 AT24C04_WritePage(0,password,6);	  //保存6位密码
					 delaynms(1000);
					 LCD_Clear();
					 LCD_write_string(1,0,"input password ");
					 sys_state=0;   //切换到输入密码开锁
					 input_position=0;
				   }
				   else 
				   {
				     LCD_write_string(1,1,"2 codes differ");
					 delaynms(1000);
					 LCD_Clear();
					 LCD_write_string(3,0,"input new");
					 sys_state=2;   //切换到输入新密码
					 input_position=0;
				   }
				   
				   
				 }			 			 
			}
			else if	(key==KEY_SET)		  //设置键
			{
			   LCD_Clear();
			  if(sys_state==0)
			  {
			    sys_state=1;
			    LCD_write_string(3,0,"input old");
				input_position=0;
			  }
			  else 
			  {
			   sys_state=0;
			   LCD_write_string(1,0,"input password ");
			   input_position=0;
			  }			 
			}
			delaynms(30);
			BUZZ_OFF;
		}

	}
	
}

