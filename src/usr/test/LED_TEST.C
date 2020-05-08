# include<reg52.h>
# include<string.h>
#include <rtx51tny.h>


#include "LED_TEST.H"
#include "DEV\led_display.h"

unsigned int i;
unsigned int j,m,n;

struct time ctime={22,21,0};

void Init1() _task_ 0

{
	LedDisplayInit();		  //驱动初始化
	
	os_create_task (1);
	os_create_task (2);
	os_create_task (3);
	os_delete_task (0);
}
void LED_display() _task_ 1
{
	//任务1：刷新数码管
	while (1)
	{
//		LedDisplayPuts(& ctime);
		LedDisplayScan();
		 
		os_wait (K_TMO, 2, 0);
	}	
}
void clock() _task_ 2
{  //任务2：时钟
	while (1)
	{
		if (++ ctime.sec == 60){
		 	ctime.sec = 0;
			if (++ ctime.min == 60)	{
				ctime.min = 0;
				if (++ ctime.hour == 24){
					ctime.hour = 0;
				}
			}
		}
		LedDisplayBuf[0] = ctime.hour / 10;
		LedDisplayBuf[1] =	ctime.hour % 10;
		LedDisplayBuf[1] =	LedDisplayBuf[1] | 0x80;
		LedDisplayBuf[2] =	ctime.min / 10;
		LedDisplayBuf[3] =	ctime.min % 10;
		LedDisplayBuf[4] =	ctime.sec / 10;
		LedDisplayBuf[5] =	ctime.sec % 10;
		os_wait (K_TMO, 50000, 0);
		os_wait (K_TMO, 50000, 0);
		os_wait (K_TMO, 50000, 0);
		os_wait (K_TMO, 50000, 0);
		os_wait (K_TMO, 50000, 0);
		os_wait (K_TMO, 50000, 0);
		os_wait (K_TMO, 50000, 0);
		os_wait (K_TMO, 50000, 0);
		os_wait (K_TMO, 50000, 0);
		os_wait (K_TMO, 50000, 0);
		os_wait (K_TMO, 50000, 0);
		os_wait (K_TMO, 50000, 0);
	}
}
void LED_SS() _task_ 3
{	//发光二极管闪烁
	unsigned int css=0x01;

	P1=0xFF;

	while (1)
	{
		P1=css^0xFF;
		
		if (css==0x80){
			css=0X01;
		}
		else  {
		css<<=1;
		}

		os_wait (K_TMO, 50000, 0);
		os_wait (K_TMO, 50000, 0);
	}	
}
