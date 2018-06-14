#include "LED.H"
#include "../../BSP/STC15_PWM.h"
#include "../../BSP/delay.h"
#include "../../BSP/GPIO.h"


static bit Board_LED_State=OFF;
bit Board_LED_Init(void)
{
	  GPIO_InitTypeDef    GPIO_InitStructure;     //结构定义
    GPIO_InitStructure.Pin  = 5;      //指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
    GPIO_InitStructure.Mode = GPIO_PullUp;       //指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(GPIO_P5,&GPIO_InitStructure);  //初始化
    open_Board_LED();
	  delay_ms(200);
	  close_Board_LED();
	  delay_ms(200);
	 return 1;
}
void open_Board_LED(void)
{
	 P55=0;
	 Board_LED_State=ON;
}
void close_Board_LED(void)
{
	P55=1;
	Board_LED_State=OFF;

}
void blink(u8 time)
{
		while(time--)
		{
			  open_Board_LED();
				delay_ms(200);
				close_Board_LED();
				delay_ms(200);
			
		}
}
bit getBoard_LED_State(void)
{
	 return Board_LED_State;
}
void Board_LED_PWM(u8 luminance)
{
	   if(Board_LED_State)
		 {
			 
			 
		 }
	
}