/************************************************************
* �ļ�����: timer.c
* ����: �ܳ���
* �汾: 1.0
* ����: 2017/4/29
* ����: //
* ��Ҫ�������书�� : ��ʱ����ʹ�ã���Timer1����Timer2�ɹ�����ʹ��
* ��ʷ�޸ļ�¼: // ��ʷ�޸ļ�¼
* <����> <ʱ��> <�汾 > <����>
* �ܳ��� 2017/4/29 ����˴��ļ�˵��ע��
***********************************************************/
//////////////////////��ʱ������Ӧ��/////////////////////////////////////// 
/*


				setTimeout(Timer1,5000); //���ö�ʱ����ʱ���� ,5��
				while(1)
				{
					if(isExpiredTimer(Timer1))   //����ﵽ��ʱʱ��
					{
						 stopTimer(Timer1);//�ﵽ��ʱʱ���һ��Ҫ�رն�ʱ����������޷��ظ�ʹ�ö�ʱ��
						//��ʱʱ�䵽����Ĵ���д����
					}
					else//���δ�ﵽ��ʱʱ���ʱ��δ����
					{


							restartTimer(Timer1);


					}
				}
*/
///////////////////////////////////////////////////////////////		 
#include	"timer.h"
#include "USART1.h"
#include <limits.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
enum
{
	ACTIVE, EXPIRED, STOPPED
}
Timer1_state = STOPPED,
Timer2_state = STOPPED;

static u16 Timer1_temp = 0;
static u16 Timer2_temp = 0;
static u16 micros = 0;//����ʱ���ȡ����
static u16 millis = 0;//����ʱ���ȡ����
static u8 seconds = 0;
static u8 minutes = 0;
static u8 hours = 0;
static u8 days = 0;




struct TimerInfo
{
	u16 Timeout;
	u16 Hz;
}
timer1_struct = { 0,0 },
timer2_struct = { 0,0 };
//************************************
// Method:    timerInit
// FullName:  timerInit
// Access:    public 
// Returns:   void
// Qualifier: ��ʱ����ʼ��������ʹ���û���ʱ���;���ʱ���ȡ����֮ǰ����setup�е��ô˺�����ɳ�ʼ��
//************************************
void timerInit()
{
	TIM_InitTypeDef		TIM_InitStructure1;	//�û��Զ��嶨ʱ��ʹ��
	TIM_InitTypeDef		TIM_InitStructure2;	//����ʱ���ȡʹ��
	u8 Error_Code = 0;

	TIM_InitStructure1.TIM_Mode = TIM_16BitAutoReload;	//ָ������ģʽ,16λ�Զ���װģʽ    TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,\\
																																																									TIM_16BitAutoReloadNoMask
	TIM_InitStructure1.TIM_Polity = PolityLow;			//ָ���ж����ȼ�, PolityHigh,PolityLow
	TIM_InitStructure1.TIM_Interrupt = ENABLE;				//�ж��Ƿ�����,   ENABLE��DISABLE
	TIM_InitStructure1.TIM_ClkSource = TIM_CLOCK_1T;	//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure1.TIM_ClkOut = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure1.TIM_Run = DISABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	TIM_InitStructure1.TIM_Value = 65536UL - (MAIN_Fosc / 1000);		//��ֵ,1000us

	TIM_InitStructure2.TIM_Mode = TIM_16BitAutoReload;	//ָ������ģʽ,16λ�Զ���װģʽ   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,\\
  																																																									TIM_16BitAutoReloadNoMask
	TIM_InitStructure2.TIM_Polity = PolityLow;			//ָ���ж����ȼ�, PolityHigh,PolityLow
	TIM_InitStructure2.TIM_Interrupt = ENABLE;				//�ж��Ƿ�����,   ENABLE��DISABLE
	TIM_InitStructure2.TIM_ClkSource = TIM_CLOCK_1T;	//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
	TIM_InitStructure2.TIM_ClkOut = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
	TIM_InitStructure2.TIM_Run = ENABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
	TIM_InitStructure2.TIM_Value = 65536UL - (MAIN_Fosc / 100000UL);		//��ֵ,10us
	//�û��Զ��嶨ʱ��		

	if (!(Error_Code = Timer_Inilize(Timer1, &TIM_InitStructure1)))//==0
	{
		PrintString1("Timer1 initializing succeed \n");
	}
	else if (Error_Code) //==1
	{
		PrintString1("Timer1 initializing failed \n");
	}
	else
	{
		PrintString1("Timer1 initializing failed \n");
	}

	//�û��Զ��嶨ʱ��	
	if (!(Error_Code = Timer_Inilize(Timer3, &TIM_InitStructure1)))//==0
	{
		PrintString1("Timer3 initializing succeed \n");
	}
	else if (Error_Code) //==1
	{
		PrintString1("Timer3 initializing failed \n");
	}
	else
	{
		PrintString1("Timer3 initializing failed \n");
	}
	//����ʱ���ȡʹ��	
	if (!(Error_Code = Timer_Inilize(Timer4, &TIM_InitStructure2)))//==0
	{
		PrintString1("Timer4 initializing succeed \n");
	}
	else if (Error_Code) //==1
	{
		PrintString1("Timer4 initializing failed \n");
	}
	else
	{
		PrintString1("Timer4 initializing failed \n");
	}



}

//
//************************************
// Method:    setTimeout
// FullName:  setTimeout
// Access:    public 
// Returns:   void
// Qualifier: ���ö�ʱ���Ķ�ʱʱ��
// Parameter: u8 whichTimer����һ����ʱ��
// Parameter: u16 time����Ҫ��ʱ��ʱ�䣬��λms
//************************************
void setTimeout(u8 whichTimer, u16 time)
{
	if (!(Timer1_state == ACTIVE || Timer2_state == ACTIVE))
	{
		switch (whichTimer)
		{

		case Timer1:
		{
			timer1_struct.Timeout = time;
		};
		case Timer2:
		{
			timer2_struct.Timeout = time;
		};
		default:
			break;
		}
	}
}
//************************************
// Method:    getTimerout
// FullName:  getTimerout
// Access:    public 
// Returns:   u16
// Qualifier:
// Parameter: u8 whichTimer
//************************************
u16 getTimerout(u8 whichTimer)
{
	switch (whichTimer)
	{

	case Timer1:
	{
		return timer1_struct.Timeout;
	};
	break;
	case Timer2:
	{
		return timer2_struct.Timeout;
	};
	break;

	default: return 0;
	}

}
//
//************************************
// Method:    setTimerHertz
// FullName:  setTimerHertz
// Access:    public 
// Returns:   void
// Qualifier: ���ö�ʱ���ķ���Ƶ��
// Parameter: u8 whichTimer����һ����ʱ��
// Parameter: u16 Hz��Ƶ��
//************************************
void setTimerHertz(u8 whichTimer, u16 Hz)
{
	switch (whichTimer)
	{

	case Timer1:
	{
		timer1_struct.Hz = Hz;
	};
	break;
	case Timer2:
	{
		timer2_struct.Hz = Hz;
	};
	break;

	}


}
u16 getTimerHertz(u8 whichTimer)
{
	switch (whichTimer)
	{

		break;
	case Timer1:
	{
		return timer1_struct.Hz;
	};
	break;
	case Timer2:
	{
		return timer2_struct.Hz;
	};
	break;
	default: return 0;
	}
}
//ͣ�ö�ʱ��
//************************************
// Method:    stopTimer
// FullName:  stopTimer
// Access:    public 
// Returns:   void
// Qualifier: ֹͣ��Ӧ�Ķ�ʱ��
// Parameter: u8 whichTimer
//************************************
void stopTimer(u8 whichTimer)
{
	switch (whichTimer)
	{
	case Timer1:
	{
		Timer1_Stop();
		Timer1_state = STOPPED;

	};
	break;
	case Timer2:
	{
		Timer3_Stop();//�˴�����timer3������timer2��timer2�����ˣ���Ϊ��������ʹ����		
		Timer2_state = STOPPED;

	};
	break;
	}

}
//����ʱ����������δ�ﵽ��ʱʱ�䷵��1
//************************************
// Method:    isActiveTimer
// FullName:  isActiveTimer
// Access:    public 
// Returns:   bit
// Qualifier: ����ǰ��ʱ�����ڶ�ʱ�ŷ���1������Ϊ0
// Parameter: u8 whichTimer
//************************************
bit isActiveTimer(u8 whichTimer)
{
	switch (whichTimer)
	{
	case Timer1:
	{
		return  Timer1_state == ACTIVE;

	};
	case Timer2:
	{
		return  Timer2_state == ACTIVE;

	};
	break;
	}
}
//����ʱ�ﵽ�趨ʱ��ʱ����1
//************************************
// Method:    isExpiredTimer
// FullName:  isExpiredTimer
// Access:    public 
// Returns:   bit
// Qualifier: ����ʱ���Ķ�ʱʱ���ѵ��򷵻�1
// Parameter: u8 whichTimer
//************************************
bit isExpiredTimer(u8 whichTimer)
{
	switch (whichTimer)
	{
	case Timer1:
	{
		return  Timer1_state == EXPIRED;
	};
	case Timer2:
	{
		return  Timer2_state == EXPIRED;
	};
	break;
	}


}
//����ʱ����ֹͣʱ����1
//************************************
// Method:    isStopped
// FullName:  isStopped
// Access:    public 
// Returns:   bit
// Qualifier: ����ʱ���Ѿ���ֹͣ�򷵻�1
// Parameter: u8 whichtimer
//************************************
bit isStopped(u8 whichtimer)
{
	switch (whichtimer)
	{
	case Timer1:
	{
		return  Timer1_state == STOPPED;
	};
	case Timer2:
	{
		return  Timer2_state == STOPPED;
	};
	break;
	}
}

//
//************************************
// Method:    restartTimer
// FullName:  restartTimer
// Access:    public 
// Returns:   void
// Qualifier: ��ʼ�����򿪶�ʱ������Ҫ�����úö�ʱʱ���Ƶ��
// Parameter: u8 whichTimer
//************************************
void restartTimer(u8 whichTimer)
{
	if (!isActiveTimer(whichTimer))
	{
		switch (whichTimer)
		{
		case Timer1:
		{
			Timer1_Run();
			Timer1_state = ACTIVE;
		};
		break;
		case Timer2:
		{
			Timer3_Run();
			Timer2_state = ACTIVE;
		};
		break;
		default:
			break;
		}



	}
}
//
//************************************
// Method:    onRestartTimer
// FullName:  onRestartTimer
// Access:    public 
// Returns:   bit
// Qualifier: ����ʱ����ʱ�����󷵻�1�����Զ�����restart���������¶�ʱ�����Դ�ѭ��
// Parameter: u8 whichTimer
//************************************
bit onRestartTimer(u8 whichTimer)
{
	if (isExpiredTimer(whichTimer))
	{
		restartTimer(whichTimer);
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}


//��ȡ�ӿ������΢����
u16 getMicros(void)
{

	return  micros;
}
//��ȡ�ӿ�����ĺ�����
u16 getMillis(void)
{
	return millis;
}
u8 getSeconds(void)
{
	return seconds;
}
u8 getMinutes(void)
{
	return minutes;
}
u8 getHours(void)
{
	return hours;
}
u8 getDays(void)
{
	return days;
}

//========================������˽�к�������Ҫ�Ķ������κγ��򣡣���=================//
/********************* Timer1�жϺ���************************/
static void Timer1_ISR(void) interrupt TIMER1_VECTOR
{

	if ((++Timer1_temp) >= timer1_struct.Timeout)
	{
		Timer1_Stop();
		Timer1_temp = 0;
		Timer1_state = EXPIRED;
	}



}


/********************* Timer3�жϺ���************************/
static void timer3_int(void) interrupt TIMER3_VECTOR
{
	if ((++Timer2_temp) >= timer2_struct.Timeout)
	{
		Timer3_Stop();
		Timer2_temp = 0;
		Timer2_state = EXPIRED;
	}

}
/********************* Timer4�жϺ���************************/
//����������
//����������sprintf������ʹ�ò������µ��������ʵ����ֵ��û�д���
static void timer4_int(void) interrupt TIMER4_VECTOR
{


	EA = 0;
	if ((micros += 10) >= 1000)
	{
		micros = 0;
		if ((++millis) >= 1000)
		{
			millis = 0;
			if ((++seconds) >= 60)
			{
				seconds = 0;
				if ((++minutes) >= 60)
				{
					minutes = 0;
					if ((++hours) >= 24)
					{
						hours = 0;
						if ((++days) == UCHAR_MAX)
						{
							days = 0;
						}

					}
				}

			}
		}
	}

	EA = 1;
}
/********************* Timer2�жϺ���************************/
//�˶�ʱ���������ڵĶ�ʱ����
//void Timer2_ISR (void) interrupt TIMER2_VECTOR
//{
//	
//}


// ����: u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
// ����: ��ʱ����ʼ������.
// ����: TIMx: �ṹ����,��ο�timer.h��Ķ���.
// ����: �ɹ�����0, �ղ�������1,���󷵻�2.
// �汾: V1.0, 2012-10-22
//========================================================================
static u8 Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
{
	if (TIM > Timer4)	return 1;	//�ղ���

	if (TIM == Timer0)
	{
		if (TIMx->TIM_Mode > TIM_16BitAutoReloadNoMask)	return 2;	//����
		TR0 = 0;		//ֹͣ����
		ET0 = 0;	//��ֹ�ж�
		PT0 = 0;	//�����ȼ��ж�
		TMOD &= 0xf0;	//��ʱģʽ, 16λ�Զ���װ
		AUXR &= ~0x80;	//12Tģʽ, 
		INT_CLKO &= ~0x01;	//�����ʱ��
		if (TIMx->TIM_Interrupt == ENABLE)		ET0 = 1;	//�����ж�
		if (TIMx->TIM_Polity == PolityHigh)		PT0 = 1;	//�����ȼ��ж�
		TMOD |= TIMx->TIM_Mode;	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ, 3: 16λ�Զ���װ, ���������ж�
		if (TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |= 0x80;	//1T
		if (TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |= 0x04;	//����������Ƶ
		if (TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |= 0x01;	//���ʱ��

		TH0 = (u8)(TIMx->TIM_Value >> 8);
		TL0 = (u8)TIMx->TIM_Value;
		if (TIMx->TIM_Run == ENABLE)	TR0 = 1;	//��ʼ����
		return	0;		//�ɹ�
	}

	if (TIM == Timer1)
	{
		if (TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return 2;	//����
		TR1 = 0;	//ֹͣ����
		ET1 = 0;	//��ֹ�ж�
		PT1 = 0;	//�����ȼ��ж�
		TMOD &= 0x0f;	//��ʱģʽ, 16λ�Զ���װ
		AUXR &= ~0x40;	//12Tģʽ, 
		INT_CLKO &= ~0x02;	//�����ʱ��
		if (TIMx->TIM_Interrupt == ENABLE)		ET1 = 1;	//�����ж�
		if (TIMx->TIM_Polity == PolityHigh)		PT1 = 1;	//�����ȼ��ж�
		TMOD |= (TIMx->TIM_Mode << 4);	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ
		if (TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |= 0x40;	//1T
		if (TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |= 0x40;	//����������Ƶ
		if (TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |= 0x02;	//���ʱ��

		TH1 = (u8)(TIMx->TIM_Value >> 8);
		TL1 = (u8)TIMx->TIM_Value;
		if (TIMx->TIM_Run == ENABLE)	TR1 = 1;	//��ʼ����
		return	0;		//�ɹ�
	}

	if (TIM == Timer2)		//Timer2,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		if (TIMx->TIM_ClkSource > TIM_CLOCK_Ext)	return 2;
		AUXR &= ~0x1c;		//ֹͣ����, ��ʱģʽ, 12Tģʽ
		IE2 &= ~(1 << 2);	//��ֹ�ж�
		INT_CLKO &= ~0x04;	//�����ʱ��
		if (TIMx->TIM_Interrupt == ENABLE)			IE2 |= (1 << 2);	//�����ж�
		if (TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |= (1 << 2);	//1T
		if (TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	AUXR |= (1 << 3);	//����������Ƶ
		if (TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |= 0x04;	//���ʱ��

		TH2 = (u8)(TIMx->TIM_Value >> 8);
		TL2 = (u8)TIMx->TIM_Value;
		if (TIMx->TIM_Run == ENABLE)	AUXR |= (1 << 4);	//��ʼ����
		return	0;		//�ɹ�
	}

	if (TIM == Timer3)		//Timer3,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		if (TIMx->TIM_ClkSource > TIM_CLOCK_Ext)	return 2;
		T4T3M &= 0xf0;		//ֹͣ����, ��ʱģʽ, 12Tģʽ, �����ʱ��
		IE2 &= ~(1 << 5);	//��ֹ�ж�
		if (TIMx->TIM_Interrupt == ENABLE)			IE2 |= (1 << 5);	//�����ж�
		if (TIMx->TIM_ClkSource == TIM_CLOCK_1T)		T4T3M |= (1 << 1);	//1T
		if (TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	T4T3M |= (3 << 1);	//����������Ƶ
		if (TIMx->TIM_ClkOut == ENABLE)	T4T3M |= 1;	//���ʱ��

		TH3 = (u8)(TIMx->TIM_Value >> 8);
		TL3 = (u8)TIMx->TIM_Value;
		if (TIMx->TIM_Run == ENABLE)	T4T3M |= (1 << 3);	//��ʼ����
		return	0;		//�ɹ�
	}

	if (TIM == Timer4)		//Timer4,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		if (TIMx->TIM_ClkSource > TIM_CLOCK_Ext)	return 2;
		T4T3M &= 0x0f;		//ֹͣ����, ��ʱģʽ, 12Tģʽ, �����ʱ��
		IE2 &= ~(1 << 6);	//��ֹ�ж�
		if (TIMx->TIM_Interrupt == ENABLE)			IE2 |= (1 << 6);	//�����ж�
		if (TIMx->TIM_ClkSource == TIM_CLOCK_1T)		T4T3M |= (1 << 5);	//1T
		if (TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	T4T3M |= (3 << 5);	//����������Ƶ
		if (TIMx->TIM_ClkOut == ENABLE)	T4T3M |= (1 << 4);	//���ʱ��

		TH4 = (u8)(TIMx->TIM_Value >> 8);
		TL4 = (u8)TIMx->TIM_Value;
		if (TIMx->TIM_Run == ENABLE)	T4T3M |= (1 << 7);	//��ʼ����
		return	0;		//�ɹ�
	}

	return 2;	//����
}


