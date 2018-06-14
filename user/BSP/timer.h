#ifndef __TIMER_H
#define __TIMER_H
#include    "config.h"
#define Timer0                      0
#define Timer1                      1
#define Timer2                      2
#define Timer3                      3
#define Timer4                      4
#define TIM_16BitAutoReload         0
#define TIM_16Bit                   1
#define TIM_8BitAutoReload          2
#define TIM_16BitAutoReloadNoMask   3
#define TIM_CLOCK_1T                0
#define TIM_CLOCK_12T               1
#define TIM_CLOCK_Ext               2
typedef struct
{
	u8  TIM_Mode;       //工作模式,     TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	u8  TIM_Polity;     //优先级设置    PolityHigh,PolityLow
	u8  TIM_Interrupt;  //中断允许      ENABLE,DISABLE
	u8  TIM_ClkSource;  //时钟源        TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	u8  TIM_ClkOut;     //可编程时钟输出,   ENABLE,DISABLE
	u16 TIM_Value;      //装载初值
	u8  TIM_Run;        //是否运行      ENABLE,DISABLE
} TIM_InitTypeDef;
//************************************
// Method:    timerInit
// FullName:  timerInit
// Access:    public 
// Returns:   void
// Qualifier: 定时器初始化函数，使用用户定时器和绝对时间获取函数之前请再setup中调用此函数完成初始化
//************************************
void timerInit();


//************************************
// Method:    setTimeout
// FullName:  setTimeout
// Access:    public 
// Returns:   void
// Qualifier: 设置定时器的定时时间
// Parameter: u8 whichTimer：哪一个定时器
// Parameter: u16 time：需要定时的时间，单位ms
//************************************
void setTimeout(u8 whichTimer, u16 time);

//************************************
// Method:    getTimerout
// FullName:  getTimerout
// Access:    public 
// Returns:   u16
// Qualifier:
// Parameter: u8 whichTimer
//************************************
u16 getTimerout(u8 whichTimer);
//************************************
// Method:    stopTimer
// FullName:  stopTimer
// Access:    public 
// Returns:   void
// Qualifier: 停止对应的定时器
// Parameter: u8 whichTimer
//************************************
void stopTimer(u8 whichTimer);
//************************************
// Method:    isActiveTimer
// FullName:  isActiveTimer
// Access:    public 
// Returns:   bit
// Qualifier: 若当前定时器正在定时着返回1，否则为0
// Parameter: u8 whichTimer
//************************************
bit isActiveTimer(u8 whichTimer);
//************************************
// Method:    isExpiredTimer
// FullName:  isExpiredTimer
// Access:    public 
// Returns:   bit
// Qualifier: 若定时器的定时时间已到则返回1
// Parameter: u8 whichTimer
//************************************
bit isExpiredTimer(u8 whichTimer);
//************************************
// Method:    isStopped
// FullName:  isStopped
// Access:    public 
// Returns:   bit
// Qualifier: 若定时器已经被停止则返回1
// Parameter: u8 whichtimer
//************************************
bit isStopped(u8 whichtimer);
//************************************
// Method:    restartTimer
// FullName:  restartTimer
// Access:    public 
// Returns:   void
// Qualifier: 初始化并打开定时器，需要先设置好定时时间或频率
// Parameter: u8 whichTimer
//************************************
void restartTimer(u8 whichTimer);
//************************************
// Method:    onRestartTimer
// FullName:  onRestartTimer
// Access:    public 
// Returns:   bit
// Qualifier: 当定时器定时结束后返回1，并自动调用restart（），重新定时，并以此循环
// Parameter: u8 whichTimer
//************************************
bit onRestartTimer(u8 whichTimer);

u8  Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx);
u16 getMicros(void);
u16 getMillis(void);
u8 getSeconds(void);
u8 getMinutes(void);
u8 getHours(void);
u8 getDays(void);

#endif
