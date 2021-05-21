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
	u8  TIM_Mode;       //����ģʽ,     TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
	u8  TIM_Polity;     //���ȼ�����    PolityHigh,PolityLow
	u8  TIM_Interrupt;  //�ж�����      ENABLE,DISABLE
	u8  TIM_ClkSource;  //ʱ��Դ        TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	u8  TIM_ClkOut;     //�ɱ��ʱ�����,   ENABLE,DISABLE
	u16 TIM_Value;      //װ�س�ֵ
	u8  TIM_Run;        //�Ƿ�����      ENABLE,DISABLE
} TIM_InitTypeDef;
//************************************
// Method:    timerInit
// FullName:  timerInit
// Access:    public 
// Returns:   void
// Qualifier: ��ʱ����ʼ��������ʹ���û���ʱ���;���ʱ���ȡ����֮ǰ����setup�е��ô˺�����ɳ�ʼ��
//************************************
void timerInit();


//************************************
// Method:    setTimeout
// FullName:  setTimeout
// Access:    public 
// Returns:   void
// Qualifier: ���ö�ʱ���Ķ�ʱʱ��
// Parameter: u8 whichTimer����һ����ʱ��
// Parameter: u16 time����Ҫ��ʱ��ʱ�䣬��λms
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
// Qualifier: ֹͣ��Ӧ�Ķ�ʱ��
// Parameter: u8 whichTimer
//************************************
void stopTimer(u8 whichTimer);
//************************************
// Method:    isActiveTimer
// FullName:  isActiveTimer
// Access:    public 
// Returns:   bit
// Qualifier: ����ǰ��ʱ�����ڶ�ʱ�ŷ���1������Ϊ0
// Parameter: u8 whichTimer
//************************************
bit isActiveTimer(u8 whichTimer);
//************************************
// Method:    isExpiredTimer
// FullName:  isExpiredTimer
// Access:    public 
// Returns:   bit
// Qualifier: ����ʱ���Ķ�ʱʱ���ѵ��򷵻�1
// Parameter: u8 whichTimer
//************************************
bit isExpiredTimer(u8 whichTimer);
//************************************
// Method:    isStopped
// FullName:  isStopped
// Access:    public 
// Returns:   bit
// Qualifier: ����ʱ���Ѿ���ֹͣ�򷵻�1
// Parameter: u8 whichtimer
//************************************
bit isStopped(u8 whichtimer);
//************************************
// Method:    restartTimer
// FullName:  restartTimer
// Access:    public 
// Returns:   void
// Qualifier: ��ʼ�����򿪶�ʱ������Ҫ�����úö�ʱʱ���Ƶ��
// Parameter: u8 whichTimer
//************************************
void restartTimer(u8 whichTimer);
//************************************
// Method:    onRestartTimer
// FullName:  onRestartTimer
// Access:    public 
// Returns:   bit
// Qualifier: ����ʱ����ʱ�����󷵻�1�����Զ�����restart���������¶�ʱ�����Դ�ѭ��
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
