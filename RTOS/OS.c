/********************************
*FileName:	 OS_C
*Author	 :   JZHG1992
*Versions:	 V1.0
*********************************/

#include "OS.H"

#ifdef OS

/************************************
*		 系统任务执行频度参数
*************************************/

u8 Task_Delay[TASK_MAX];
/************************************
*		 系统中断服务函数
*************************************/

void OS_ISR(void) interrupt 1
{
	u8 i;
	TH0 = 256 - (OS_CLOCK / TASK_CLOCK) / 12 / 256; // 赋初值200Hz
	TL0 = 256 - (OS_CLOCK / TASK_CLOCK) / 12 % 256;
	for (i = 0; i < TASK_MAX; i++)
	{
		if (Task_Delay[i] != 0)
		{
			Task_Delay[i] --;

		}
	}
}

/************************************
*		 系统定时器时钟初始化
*************************************/

void OS_Timer0_Init(void)
{
	u8 i;

	for (i = 0; i < TASK_MAX; i++)
	{
		Task_Delay[i] = 0;   // 复位系统任务执行频度参数		
	}
	TMOD = (TMOD & 0xf0) | 0x01; // 设置定时器0方式1
	TH0 = 256 - (OS_CLOCK / TASK_CLOCK) / 12 / 256; // 赋初值200Hz
	TL0 = 256 - (OS_CLOCK / TASK_CLOCK) / 12 % 256;
	TR0 = 1;  // 使能定时器0
	ET0 = 1;  // 使能定时器0中断
}

/************************************
*		 系统任务调度函数
*************************************/

void OS_Task_Run(void(*ptask)())
{
	(*ptask)();
}
void OS_Run()
{
	u8 i;
	for(;;)
	{

		for (i = 0; i < TASK_MAX; i++)
		{

			if (Task_Delay[i] == 0)
			{

				OS_Task_Run(task[i]);
				break;
			}
		}

	}

}
	

#endif



