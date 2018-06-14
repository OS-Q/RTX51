# include<reg52.h>
# include<string.h>
# include ".\led_display_cfg.h"
# include ".\led_display.h"

//**********定义全局变量************************
unsigned int num_1ms,num_2ms,num_1000ms;
unsigned char temp[6];
//**********定义中断初始化函数******************
void inter_init()
{
	EA=1;//开总中断
	ET0=1;//中断控制，允许定时器0中断
	TMOD=0X01;//工作模式
	TH0=(65536-1000)/256;//初值高
	TL0=(65536-1000)%256;//初值低
  	TR0=1;	 //启动定时器
}
void main()
{

	
	unsigned char *str6;
	inter_init();
	LedDisplayInit(); //LED初始化，此例为空函数；
	while(1)							  
		{
//*****************************************
		unsigned char sec,hou,min,hou_ge,hou_shi,min_shi,min_ge,sec_shi,sec_ge;
		if (num_1000ms>=950)
		{
			num_1000ms=0;
			if (sec<59)
				{
					sec++;
				}
				else
					{
						sec=0;
						if (min<59)
							{
								min++;
							}
							else
								{
									min=0;
									if (hou<23)
										{
											hou++;
										}
										else
											{
												hou=0;
											}
								}
					}
		hou_shi=hou/10;
		hou_ge=hou%10;
		min_shi=min/10;
		min_ge=min%10;
		sec_shi=sec/10;
		sec_ge=sec%10;

		temp[0]='0'+hou_shi;
		temp[1]='0'+hou_ge;
		temp[2]='0'+min_shi;
		temp[3]='0'+min_ge;
		temp[4]='0'+sec_shi;
		temp[5]='0'+sec_ge;
		str6=&temp[0];
		LedDisplayPuts(str6);

		}

//**********************************************


			if (num_2ms>=2)
				{
					LedDisplayScan();	
					num_2ms=0;
				}

		}

}
void time()interrupt 1 using 1
{
	TH0=(65536-1000)/256;	
	TL0=(65536-1000)%256;
	num_2ms++;
	num_1000ms++;
}