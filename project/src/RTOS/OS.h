/********************************
*FileName:	 OS_H
*Author	 :   JZHG1992
*Versions:	 V1.0
*********************************/
/********************************
*系统原理：单片机定时器延时中断来产
*	       生系统任务调度节拍，设置
*	       各个任务的执行频度，来调
*    	   度各任务。以实现系统多线
*		   操作。
*********************************/
#ifndef _OS_H_
#define _OS_H_
#include "../USER/USER.h"
#include  "../USER/config.h"

/************************************
*		定义变量类型
*************************************/

#define uchar unsigned char	 // 宏定义uchar
#define uint unsigned int	 // 宏定义uint

/************************************
*		配置系统参数
*这里你可以根据你的需要修改
*************************************/

#define OS_CLOCK  30000000   // 系统晶振频率，单位Hz
#define TASK_CLOCK 400       // 任务中断节拍，单位Hz
#define TASK_MAX   6        // 任务数目

/************************************
*	系统任务外调函数与参数
*************************************/

extern uchar Task_Delay[TASK_MAX];        // 系统任务执行频度参数
extern void OS_Timer0_Init(void);       // 系统定时器时钟初始化
extern void OS_Task_Run(void(*ptask)()); // 系统任务调度函数
extern void(*const task[])();          // 获得任务指针
extern void OS_Run();



//-------------
#endif


