/************************************************************
* �ļ�����: STC15_PWM.h
* ����:  ������
* �汾:  1.1
* ����:  2017/4/27
* ����:  Ӳ��pwm�Ŀ⺯��ͷ�ļ�
* ��ʷ�޸ļ�¼: // ��ʷ�޸ļ�¼
* <����> <ʱ��> <�汾 > <����>
* �ܳ��� 2017/5/6 1.1   ����Ӳ��pwm�����ã�ֻ��Ҫ�����򵥵ĺ������ñ���Գ�ʼ������һ·pwm
***********************************************************/
#ifndef __STC15_PWM_H__
#define __STC15_PWM_H__
#include    "config.h"
                             /*********��������ͽӿں���***********/
/************************************
Ӳ��PWMio����
PWM_N| io  | �ڶ���
PWM2 :P3.7 -> P2.7
PWM3 :P2.1 -> P4.5
PWM4 :P2.2 -> P4.4
PWM5 :P2.3 -> P4.2
PWM6 :P1.6 -> P0.7
PWM7 :P1.7 -> P0.6
************************************/
 void setPWM_DIV(u8 PWM_N,u8 DIV);
 u8 getPWM_DIV(u8 PWM_N);
void open_PWM_ALL(void);
void close_PWM_ALL(void);
void close_PWM_N(u8 PWM_N);
void open_PWM_N(u8 PWM_N);
bit getPWM_state(u8 PWM_N) ;
	/*************************************************
* ��������: u32 getPWM_period(void )
* ����: ��ȡ�����õ�pwmƵ����Ϣ
* ����: ��
* ���: ��
* ����ֵ: pwmƵ��
* ����˵��: ��û������pwm��Ƶ�ʾ͵��ô˺����򷵻ز�ȷ����ֵ��
*************************************************/
u32  get_PWM_period(u8 PWN_N);



/*************************************************
* ��������: float getPWM_n_duty(u8 PWM_N)
* ����: ����PWM_N��ռ�ձ���Ϣ
* ����: u8 PWM_N
* ���: ��
* ����ֵ: PWM_N��ռ�ձ���Ϣ,float��ʽ
* ����˵��: ��û������pwm��ռ�ձȾ͵��ô˺����򷵻ز�ȷ����ֵ��
*************************************************/
float get_PWM_N_duty(u8 PWM_N);






/*************************************************
* ��������:void PWM_period(u16 Hz)
* ����: ����Ӳ��pwm��ͬһƵ�� ��������Ƶ������
* �����������õĺ���:
* 1.PWM_SET_PERIOD
* ���ñ������ĺ���:
* ����:
* 1.u16 Hz:Ҫ�����pwm��Ƶ�ʣ���Ϊ�������Ĳ���ֵ������Ӳ�����ޣ�����ı�����6��pwm��Ƶ��
* ���: ��
* ����ֵ: ��
* ����: �˺���ֻ������pwm�ļ�������ʼֵ���Ӷ����pwm��ͬƵ�ʵ������
        �������ڵ�Ƭ��Ӳ�����ޣ������Ե�����ÿ·pwm��Ƶ�ʽ����޸ģ�
        ֻ��һ��ȫ�ġ�
*************************************************/
void set_PWM_period(u8 PWM_N,u16 Hz)  ;




/*************************************************
* ��������: void PWM_duty(u8 PWM_N,float duty)
* ����: �޸�ĳһ·pwm��ռ�ձ� ��������ռ�ձ�����
* �����������õĺ���:
* ���ñ������ĺ���:
* ����:
* 1.u8 PWM_N �� ��һ·pwm
* 2.float duty��ռ�ձȣ�ʹ��С������0.8����80%��ռ�ձ�
* ���: ��
* ����ֵ: ��
* ����˵��:
*************************************************/
void set_PWM_duty(u8 PWM_N,float duty);



static u8 PWM_SET_PERIOD(u16 period);
static u8 PWM_SET_T12_PERIOD(u8 PWM_N, u16 period1, u16 period2);
//u8   PWM_SET_PERIOD(u16 period);
//u8   PWM_SET_T12_PERIOD(u8 PWM_N,u16 period1,u32 period2);
//void PWM_Inilize(u8 PWM_N,PWM_InitTypeDef *PWMx);
//u8 PWM_N,
             /******************�ڲ�����������鿴********************/
#define PWM_2           0
#define PWM_3           1
#define PWM_4           2
#define PWM_5           3
#define PWM_6           4
#define PWM_7           5
#define PWM_HIGHT  1
#define PWM_LOW    0
#define PWM_Clock_NT        0
#define PWM_Clock_Timer2_OF 1
#define PWM_SELECT_N        0
#define PWM_SELECT_N_2      1
////////////������///////////////////////////////////////////////////////////
///////////////////////////////////////////////
#define PWM_DEFAULT_PERIOD 5000
#define PWM_DEFAULT_DUTY 0.5f


//PWM�Ĵ�������ʹ�� �����ֹ�Ļ� ���ǹ���PWM�ļĴ��������ܲ���
#define PWM_UNLOCK    P_SW2|=0X80      /*ʹ��*/
#define PWM_LOCK      P_SW2&=(~0X80)   /*��ֹ*/

///////////////////////////////////////////////
//PWM�ܿ���
#define PWM_ALL_EN        PWMCR|=(1<<7)
#define PWM_ALL_NO        PWMCR&=(~(1<<7))
//PWM�μ�����
#define PWM_N_EN(PWM_N)   PWMCR|=(1<<(PWM_N))
#define PWM_N_NO(PWM_N)   PWMCR&=(~(1<<(PWM_N)))

////PWM��Ӧ�ܽų�ʼֵ
////i=PWM_2~PWM_7
//#define PWM_INIT_HIGHT(i)        PWMCFG|=(1<<(i));
//#define PWM_INIT_LOW(i)          PWMCFG&=(~(1<<(i)))
typedef struct
{
    u8 PWM_GOTO_ADC;            //ENABLE=����������ʱ ����ADC
    u8 PWM_V_INIT;              //PWM_HIGHT=��ʼ�ߵ�ƽ  PWM_LOW=��ʼ�͵�ƽ
    u8 PWM_0ISR_EN;             //ENABLE=ʹ��PWM�����������ж�  DISABLE=�ر�PWM�����������ж� �� CBIF��Ȼ�ᱻӲ����λ
    u8 PWM_OUT_EN;              //ENABLE=PWMͨ��x�Ķ˿�ΪPWM��������� ��PWM���η���������
    u8 PWM_UNUSUAL_EN;          //ENABLE=ʹ��PWM���ⲿ�쳣��⹦��
    u8 PWM_UNUSUAL_OUT;         //ENABLE=�����쳣ʱ��PWM��Ӧ������ڻ��� ��������ģʽ
    u8 PWM_UNUSUAL_ISR_EN;      //ENABLE=ʹ���쳣����ж� DISABLE=�ر��쳣����ж� ��FDIF��Ȼ�ᱻӲ����λ
    u8 PWM_UNUSUAL_CMP0_EN;     //ENABLE=�쳣���ԴΪ�Ƚ�������� ���ȽϽ��Ϊ��ʱ ����PWM�쳣
    u8 PWM_UNUSUAL_P24_EN;      //ENABLE=�쳣���ԴΪP24/PWMFLT ��P24=1 ����PWM�쳣
    u8 PWM_CLOCK;               //PWM_Clock_NT=PWM��ʱ��Դ��ϵͳʱ�Ӿ���Ƶ���ʱ��  PWM_Clock_Timer2_OF=PWM��ʱ��Դ��TMER2���������
    u8 PWM_CLOCK_DIV;           //��PWM_CLOCK=PWM_Clock_NTʱ PWM��ʱ��Դ��ϵͳʱ��/(PS[3:0]+1)
    u8 PWM_SELECTx_IO;          //PWM_SELECT_N=PWM��һѡ��IO�� PWM_SELECT_N_2=PWM�ڶ�ѡ��IO��
    u8 PWM_ISRx_EN;             //ENABLE=ʹ��PWMx�ж� ʹ�ܵ�һ��ת��ڶ���ת�ж�
    u8 PWM_T1x_EN;              //ENABLE=ʹ�ܵ�һ��ת�ж�
    u8 PWM_T2x_EN;              //ENABLE=ʹ�ܵڶ���ת�ж�
    u8 PWM_EN;                  //ENABLE=PWMʹ�� ������PWM�������úú�������� ������رպ��ڴ򿪣���PWM���������´�0����
} PWM_InitTypeDef;
 void PWM_Inilize(u8 PWM_N,PWM_InitTypeDef *PWMx);
                             

#endif
