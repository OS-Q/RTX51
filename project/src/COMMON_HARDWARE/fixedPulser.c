/************************************************************
* ��֯���ƣ�
* �ļ�����: K:\��Ƭ�����\���Ӵ���������\HARDWARE\COMMON_HARDWARE\FIXEDPULSER.C
* ����:   �ܳ���  
* �汾:  1.0  
* ����:     2017/07/18
* ����:	���������̶�������������
* ��ʷ�޸ļ�¼:
* <����> <ʱ��> <�汾 > <����>
* 
***********************************************************/

#include "fixedPulser.h"
#include "../BSP/STC15_PWM.h"
#include "../BSP/GPIO.H"
#include <limits.h>
#define PULSER_NUM	1	//������Ҫʹ�ö��ٸ����巢����

struct Pulser //���巢�����йز������ݽṹ
{
	u32 count;  //�������
	u16 Hz;     //����Ƶ��
	u8 state;   //���巢������ǰ״̬

};

static struct Pulser g_pulser[PULSER_NUM];  //���巢������Ϣ�洢����

bool setPulse(u8 pulser_num, u16 Hz, u32 count)
{
	set_PWM_period(PWM_7, Hz);
	g_pulser[pulser_num].Hz = Hz;
	g_pulser[pulser_num].count = count;

	return 1;
}
bool openPulser(u8 pulser_num)
{
	open_PWM_N(PWM_7);
	g_pulser[pulser_num].state = ON;

	return 1;
}
bool closePulser(u8 pulser_num)
{

	close_PWM_N(pulser_num + 5);

	g_pulser[pulser_num].state = OFF;
	return 1;

}
bool getPulserState(u8 pulser_num)
{

	return g_pulser[pulser_num].state;

}
void PulserInit(void)//��ʼ������
{
	/************************************
Ӳ��PWM io����
PWM_N| ��һ��| �ڶ���
PWM2 :P3.7 -> P2.7
PWM3 :P2.1 -> P4.5
PWM4 :P2.2 -> P4.4
PWM5 :P2.3 -> P4.2
PWM6 :P1.6 -> P0.7
PWM7 :P1.7 -> P0.6
************************************/


	GPIO_InitTypeDef    GPIO_InitStructure;     //�ṹ����
	PWM_InitTypeDef  PWM_InitStructure;
	GPIO_InitStructure.Mode = GPIO_PullUp;       //ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP

	GPIO_InitStructure.Pin = GPIO_Pin_7;    //ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
	GPIO_Inilize(GPIO_P1, &GPIO_InitStructure);  //��ʼ��
	P17 = 1;
	set_PWM_duty(PWM_7, PWM_DEFAULT_DUTY); //ʹ��Ĭ��0.5��ռ�ձ�

	PWM_UNLOCK;
	PWM_InitStructure.PWM_GOTO_ADC = DISABLE;            //ENABLE=����������ʱ ����ADC
	PWM_InitStructure.PWM_V_INIT = PWM_LOW;             //PWM_HIGHT=��ʼ�ߵ�ƽ  PWM_LOW=��ʼ�͵�ƽ
	PWM_InitStructure.PWM_0ISR_EN = DISABLE;           //ENABLE=ʹ��PWM�����������ж�  DISABLE=�ر�PWM�����������ж� �� CBIF��Ȼ�ᱻӲ����λ
	PWM_InitStructure.PWM_OUT_EN = ENABLE;               //ENABLE=PWMͨ��x�Ķ˿�ΪPWM��������� ��PWM���η���������
	PWM_InitStructure.PWM_UNUSUAL_EN = DISABLE;         //ENABLE=ʹ��PWM���ⲿ�쳣��⹦��
	PWM_InitStructure.PWM_UNUSUAL_OUT = DISABLE;       //ENABLE=�����쳣ʱ��PWM��Ӧ������ڻ��� ��������ģʽ
	PWM_InitStructure.PWM_UNUSUAL_ISR_EN = DISABLE;      //ENABLE=ʹ���쳣����ж� DISABLE=�ر��쳣����ж� ��FDIF��Ȼ�ᱻӲ����λ
	PWM_InitStructure.PWM_UNUSUAL_CMP0_EN = DISABLE;     //ENABLE=�쳣���ԴΪ�Ƚ�������� ���ȽϽ��Ϊ��ʱ ����PWM�쳣
	PWM_InitStructure.PWM_UNUSUAL_P24_EN = DISABLE;      //ENABLE=�쳣���ԴΪP24/PWMFLT ��P24=1 ����PWM�쳣
	PWM_InitStructure.PWM_CLOCK = PWM_Clock_NT;          //PWM_Clock_NT=PWM��ʱ��Դ��ϵͳʱ�Ӿ���Ƶ���ʱ��  PWM_Clock_Timer2_OF=PWM��ʱ��Դ��TMER2���������
	PWM_InitStructure.PWM_CLOCK_DIV = 15;              //��PWM_CLOCK=PWM_Clock_NTʱ PWM��ʱ��Դ��ϵͳʱ��/(PS[3:0]+1)
	PWM_InitStructure.PWM_SELECTx_IO = PWM_SELECT_N;     //PWM_SELECT_N=PWM��һѡ��IO�� PWM_SELECT_N_2=PWM�ڶ�ѡ��IO��
	PWM_InitStructure.PWM_ISRx_EN = ENABLE;           //ENABLE=ʹ��PWMx�ж� ʹ�ܵ�һ��ת��ڶ���ת�ж�
	PWM_InitStructure.PWM_T1x_EN = DISABLE;           //ENABLE=ʹ�ܵ�һ��ת�ж�
	PWM_InitStructure.PWM_T2x_EN = ENABLE;          //ENABLE=ʹ�ܵڶ���ת�ж�
	PWM_InitStructure.PWM_EN = DISABLE;                //ENABLE=PWMʹ�� ������PWM�������úú�������� ������رպ��ڴ򿪣���PWM���������´�0����

//	PWM_Inilize(PWM_6, &PWM_InitStructure);
	PWM_Inilize(PWM_7, &PWM_InitStructure);

	PWM_LOCK;
	setPWM_DIV(PWM_7, 16);
}

static u32 g_PWM_7tmp = 0;//��������
static u32 g_PWM_6tmp = 0;//��������
static u32 g_PWM_5tmp = 0;//��������
static u32 g_PWM_4tmp = 0;//��������
static u32 g_PWM_3tmp = 0;//��������
static u32 g_PWM_2tmp = 0;//��������

/***************������Ϊ˽�к�������������ģ�********************************/
static void PWM_Routine(void) interrupt 22   //�ж�ִ�г���������������ĸ�������ʱ�رշ�����
{
	//  PWMIF &= (~(1 << 6));  //��������־λ
	if (PWMIF ^ 5 == 1)//PWM_7
	{
		PWMIF &= (~(1 << 5));  //��������־λ

		if (g_PWM_7tmp++ >= g_pulser[PULSER_1].count)
		{
			g_pulser[PULSER_1].count = 0;
			close_PWM_N(PWM_7);
		}
	}
	else if (PWMIF ^ 4 == 1)//PWM_6
	{
		PWMIF &= (~(1 << 4));  //��������־λ
		if (g_PWM_6tmp++ >= g_pulser[PULSER_2].count)
		{
			g_pulser[PULSER_2].count = 0;
			close_PWM_N(PWM_6);
		}
	}
	else if (PWMIF ^ 3 == 1)
	{
		PWMIF &= (~(1 << 3));  //��������־λ
	}
	else if (PWMIF ^ 2 == 1)
	{
		PWMIF &= (~(1 << 2));  //��������־λ

	}
	else if (PWMIF ^ 1 == 1)
	{
		PWMIF &= (~(1 << 1));  //��������־λ
	}
	else if (PWMIF ^ 0 == 1)
	{
		PWMIF &= (~(1 << 1));  //��������־λ
	}
	else
	{

	}

}

//static void PWMFD_Routine(void) interrupt 23
//{
//
//}
