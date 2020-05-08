/********************************
*FileName:	 OS_C
*Author	 :   JZHG1992
*Versions:	 V1.0
*********************************/

#include "OS.H"

#ifdef OS

/************************************
*		 ϵͳ����ִ��Ƶ�Ȳ���
*************************************/

u8 Task_Delay[TASK_MAX];
/************************************
*		 ϵͳ�жϷ�����
*************************************/

void OS_ISR(void) interrupt 1
{
	u8 i;
	TH0 = 256 - (OS_CLOCK / TASK_CLOCK) / 12 / 256; // ����ֵ200Hz
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
*		 ϵͳ��ʱ��ʱ�ӳ�ʼ��
*************************************/

void OS_Timer0_Init(void)
{
	u8 i;

	for (i = 0; i < TASK_MAX; i++)
	{
		Task_Delay[i] = 0;   // ��λϵͳ����ִ��Ƶ�Ȳ���		
	}
	TMOD = (TMOD & 0xf0) | 0x01; // ���ö�ʱ��0��ʽ1
	TH0 = 256 - (OS_CLOCK / TASK_CLOCK) / 12 / 256; // ����ֵ200Hz
	TL0 = 256 - (OS_CLOCK / TASK_CLOCK) / 12 % 256;
	TR0 = 1;  // ʹ�ܶ�ʱ��0
	ET0 = 1;  // ʹ�ܶ�ʱ��0�ж�
}

/************************************
*		 ϵͳ������Ⱥ���
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



