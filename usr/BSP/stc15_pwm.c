/************************************************************
* ��֯���ƣ� ���Ӵ���С��
* �ļ�����: STC15_PWM.C
* ����:  �ܳ���
* �汾:  1.3
* ����:  2017/4/27
* ����:  Ӳ��pwm�Ŀ⺯����io�ڲμ��·�����
* ��ʷ�޸ļ�¼: // ��ʷ�޸ļ�¼
* <����> <ʱ��> <�汾 > <����>
* �ܳ��� 2017/4/27 1.1 �޸���һ���������case��������
* �ܳ��� 2017/5/6  1.2 ������һЩ�������ú���
* �ܳ��� 2017/7/9  1.3 �޸���pwm��Ϣ�ļ�¼�ͷ��ط�ʽ��ʹ�ýṹ�������������Ϣ
***********************************************************/

#include "stc15_pwm.h"
#include "GPIO.h"
//PWM��Ϣ�洢
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

static struct PWM_N_INFO
{
	u32 period;//pwm��Ƶ��
	u8 state;//pwm��������״̬
	float duty;//pwm��ռ�ձ�
	u8 DIV; //Ԥ��Ƶֵ�����������ϵ�Ƶ�ʵ�pwm
};
static  struct PWM_N_INFO PWM_N_INFO[6]; //6��pwm���ݴ洢

//========================================================================
//u8    PWM_Inilize(PWM_InitTypeDef *PWM)
// ����:PWM��ʼ������
// ����:u8 PWM_N:PWM·�����(2~7) PWM: �ṹ����,��ο�pwm.h��Ķ���.
// ����: �ɹ�����0, ���󷵻�1
//========================================================================
void PWM_Inilize(u8 PWM_N, PWM_InitTypeDef *PWMx)
{
	u8 i = 0;
	for (; i < 6; i++)
	{
		PWM_N_INFO[i].period = 0;
		PWM_N_INFO[i].state = 0;
		PWM_N_INFO[i].duty = 0;
		PWM_N_INFO[i].DIV = 1;
	}

	P_SW2 |= 0X80;
	if (ENABLE == PWMx->PWM_GOTO_ADC)            //ENABLE=����������ʱ ����ADC
	{
		PWMCFG |= (1 << 7); //������˼���ǲ���ı�����λ��ֵ
	}
	else
	{
		PWMCFG &= (~(1 << 7)); //��ʵҲ�������ϱߵİ취����������д����˼��ֱ��
	}
	if (PWM_HIGHT == PWMx->PWM_V_INIT)              //PWM_HIGHT=��ʼ�ߵ�ƽ     PWM_LOW=��ʼ�͵�ƽ
	{
		PWMCFG |= (1 << PWM_N);
	}
	else
	{
		PWMCFG &= (~(1 << PWM_N));
	}
	if (ENABLE == PWMx->PWM_0ISR_EN)             //ENABLE=ʹ��PWM�����������ж�  DISABLE=�ر�PWM�����������ж� �� CBIF��Ȼ�ᱻӲ����λ
	{
		PWMCR |= (1 << 6);
	}
	else
	{
		PWMCR &= (~(1 << 6));
	}
	if (ENABLE == PWMx->PWM_OUT_EN)              //ENABLE=PWMͨ��x�Ķ˿�ΪPWM��������� ��PWM���η���������
	{
		PWMCR |= (1 << PWM_N);
	}
	else
	{
		PWMCR &= (~(1 << PWM_N));
	}
	if (ENABLE == PWMx->PWM_UNUSUAL_EN)          //ENABLE=ʹ��PWM���ⲿ�쳣��⹦��
	{
		PWMFDCR = (1 << 5);
	}
	else
	{
		PWMFDCR &= (~(1 << 5));
	}
	if (ENABLE == PWMx->PWM_UNUSUAL_OUT)         //ENABLE=�����쳣ʱ��PWM��Ӧ������ڻ��� ��������ģʽ
	{
		PWMFDCR = (1 << 4);
	}
	else
	{
		PWMFDCR &= (~(1 << 4));
	}
	if (ENABLE == PWMx->PWM_UNUSUAL_ISR_EN)      //ENABLE=ʹ���쳣����ж� DISABLE=�ر��쳣����ж� ��FDIF��Ȼ�ᱻӲ����λ
	{
		PWMFDCR = (1 << 3);
	}
	else
	{
		PWMFDCR &= (~(1 << 3));
	}
	if (ENABLE == PWMx->PWM_UNUSUAL_CMP0_EN)     //ENABLE=�쳣���ԴΪ�Ƚ�������� ���ȽϽ��Ϊ��ʱ ����PWM�쳣
	{
		PWMFDCR = (1 << 2);
	}
	else
	{
		PWMFDCR &= (~(1 << 2));
	}
	if (ENABLE == PWMx->PWM_UNUSUAL_P24_EN)      //ENABLE=�쳣���ԴΪP24/PWMFLT ��P24=1 ����PWM�쳣
	{
		PWMFDCR = (1 << 1);
	}
	else
	{
		PWMFDCR &= (~(1 << 1));
	}
	//  PWMCKS=0;
	if (PWM_Clock_NT == PWMx->PWM_CLOCK)               //PWM_Clock_NT=PWM��ʱ��Դ��ϵͳʱ�Ӿ���Ƶ���ʱ��  PWM_Clock_Timer2_OF=PWM��ʱ��Դ��TMER2���������
	{
		PWMCKS &= (~(1 << 4));
	}
	else
	{
		PWMCKS |= (1 << 4);
	}
	// PWMCKS=0x00;
	PWMCKS |= PWMx->PWM_CLOCK_DIV;           //��PWM_CLOCK=PWM_Clock_NTʱ PWM��ʱ��Դ��ϵͳʱ��/(PS[3:0]+1)
	switch (PWM_N)
	{
	case PWM_2:
	{
		if (PWM_SELECT_N == PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM��һѡ��IO�� PWM_SELECT_N_2=PWM�ڶ�ѡ��IO��
		{
			PWM2CR &= (~(1 << 3));
		}
		else
		{
			PWM2CR |= (1 << 3);
		}
		if (ENABLE == PWMx->PWM_ISRx_EN)             //ENABLE=ʹ��PWMx�ж� ʹ�ܵ�һ��ת��ڶ���ת�ж�
		{
			PWM2CR |= (1 << 2);
		}
		else
		{
			PWM2CR &= (~(1 << 2));
		}
		if (ENABLE == PWMx->PWM_T1x_EN)              //ENABLE=ʹ�ܵ�һ��ת�ж�
		{
			PWM2CR |= (1 << 1);
		}
		else
		{
			PWM2CR &= (~(1 << 1));
		}
		if (ENABLE == PWMx->PWM_T2x_EN)              //ENABLE=ʹ�ܵڶ���ת�ж�
		{
			PWM2CR |= (1 << 0);
		}
		else
		{
			PWM2CR &= (~(1 << 0));
		}
	}
	break;
	case PWM_3:
	{
		if (PWM_SELECT_N == PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM��һѡ��IO�� PWM_SELECT_N_2=PWM�ڶ�ѡ��IO��
		{
			PWM3CR &= (~(1 << 3));
		}
		else
		{
			PWM3CR |= (1 << 3);
		}
		if (ENABLE == PWMx->PWM_ISRx_EN)             //ENABLE=ʹ��PWMx�ж� ʹ�ܵ�һ��ת��ڶ���ת�ж�
		{
			PWM3CR |= (1 << 2);
		}
		else
		{
			PWM3CR &= (~(1 << 2));
		}
		if (ENABLE == PWMx->PWM_T1x_EN)              //ENABLE=ʹ�ܵ�һ��ת�ж�
		{
			PWM3CR |= (1 << 1);
		}
		else
		{
			PWM3CR &= (~(1 << 1));
		}
		if (ENABLE == PWMx->PWM_T2x_EN)              //ENABLE=ʹ�ܵڶ���ת�ж�
		{
			PWM3CR |= (1 << 0);
		}
		else
		{
			PWM3CR &= (~(1 << 0));
		}
	}
	break;
	case PWM_4:
	{
		if (PWM_SELECT_N == PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM��һѡ��IO�� PWM_SELECT_N_2=PWM�ڶ�ѡ��IO��
		{
			PWM4CR &= (~(1 << 3));
		}
		else
		{
			PWM4CR |= (1 << 3);
		}
		if (ENABLE == PWMx->PWM_ISRx_EN)             //ENABLE=ʹ��PWMx�ж� ʹ�ܵ�һ��ת��ڶ���ת�ж�
		{
			PWM4CR |= (1 << 2);
		}
		else
		{
			PWM4CR &= (~(1 << 2));
		}
		if (ENABLE == PWMx->PWM_T1x_EN)              //ENABLE=ʹ�ܵ�һ��ת�ж�
		{
			PWM4CR |= (1 << 1);
		}
		else
		{
			PWM4CR &= (~(1 << 1));
		}
		if (ENABLE == PWMx->PWM_T2x_EN)              //ENABLE=ʹ�ܵڶ���ת�ж�
		{
			PWM4CR |= (1 << 0);
		}
		else
		{
			PWM4CR &= (~(1 << 0));
		}
	}
	break;
	case PWM_5:
	{
		if (PWM_SELECT_N == PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM��һѡ��IO�� PWM_SELECT_N_2=PWM�ڶ�ѡ��IO��
		{
			PWM5CR &= (~(1 << 3));
		}
		else
		{
			PWM5CR |= (1 << 3);
		}
		if (ENABLE == PWMx->PWM_ISRx_EN)             //ENABLE=ʹ��PWMx�ж� ʹ�ܵ�һ��ת��ڶ���ת�ж�
		{
			PWM5CR |= (1 << 2);
		}
		else
		{
			PWM5CR &= (~(1 << 2));
		}
		if (ENABLE == PWMx->PWM_T1x_EN)              //ENABLE=ʹ�ܵ�һ��ת�ж�
		{
			PWM5CR |= (1 << 1);
		}
		else
		{
			PWM5CR &= (~(1 << 1));
		}
		if (ENABLE == PWMx->PWM_T2x_EN)              //ENABLE=ʹ�ܵڶ���ת�ж�
		{
			PWM5CR |= (1 << 0);
		}
		else
		{
			PWM5CR &= (~(1 << 0));
		}
	}
	break;
	case PWM_6:
	{
		if (PWM_SELECT_N == PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM��һѡ��IO�� PWM_SELECT_N_2=PWM�ڶ�ѡ��IO��
		{
			PWM6CR &= (~(1 << 3));
		}
		else
		{
			PWM6CR |= (1 << 3);
		}
		if (ENABLE == PWMx->PWM_ISRx_EN)             //ENABLE=ʹ��PWMx�ж� ʹ�ܵ�һ��ת��ڶ���ת�ж�
		{
			PWM6CR |= (1 << 2);
		}
		else
		{
			PWM6CR &= (~(1 << 2));
		}
		if (ENABLE == PWMx->PWM_T1x_EN)              //ENABLE=ʹ�ܵ�һ��ת�ж�
		{
			PWM6CR |= (1 << 1);
		}
		else
		{
			PWM6CR &= (~(1 << 1));
		}
		if (ENABLE == PWMx->PWM_T2x_EN)              //ENABLE=ʹ�ܵڶ���ת�ж�
		{
			PWM6CR |= (1 << 0);
		}
		else
		{
			PWM6CR &= (~(1 << 0));
		}
	}
	break;
	case PWM_7:
	{
		if (PWM_SELECT_N == PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM��һѡ��IO�� PWM_SELECT_N_2=PWM�ڶ�ѡ��IO��
		{
			PWM7CR &= (~(1 << 3));
		}
		else
		{
			PWM7CR |= (1 << 3);
		}
		if (ENABLE == PWMx->PWM_ISRx_EN)             //ENABLE=ʹ��PWMx�ж� ʹ�ܵ�һ��ת��ڶ���ת�ж�
		{
			PWM7CR |= (1 << 2);
		}
		else
		{
			PWM7CR &= (~(1 << 2));
		}
		if (ENABLE == PWMx->PWM_T1x_EN)              //ENABLE=ʹ�ܵ�һ��ת�ж�
		{
			PWM7CR |= (1 << 1);
		}
		else
		{
			PWM7CR &= (~(1 << 1));
		}
		if (ENABLE == PWMx->PWM_T2x_EN)              //ENABLE=ʹ�ܵڶ���ת�ж�
		{
			PWM7CR |= (1 << 0);
		}
		else
		{
			PWM7CR &= (~(1 << 0));
		}
	}
	break;
	default:
		//      return 1;
		break;
	}
	if (ENABLE == PWMx->PWM_EN)                  //ENABLE=PWMʹ�� ������PWM�������úú�������� ������رպ��ڴ򿪣���PWM���������´�0����
	{
		PWMCR |= (1 << 7);
	}
	else
	{
		PWMCR &= (~(1 << 7));
	}
}
/*************************************************
* ��������: u32 getPWM_period(void )
* ����: ���������õ�pwmƵ����Ϣ
* ����: u8 PWM_N, 2<=N<=7
* ���: ��
* ����ֵ: pwmƵ��
* ����˵��: ��û������pwm��Ƶ�ʾ͵��ô˺�����᷵��0��
*************************************************/
u32 get_PWM_period(u8 PWM_N)
{
	return PWM_N_INFO[PWM_N].period;
}
/*************************************************
* ��������: float getPWM_n_duty(u8 PWM_N)
* ����: ����PWM_N��ռ�ձ���Ϣ
* ����: u8 PWM_N, 2<=N<=7
* ���: ��
* ����ֵ: PWM_N��ռ�ձ���Ϣ,float��ʽ
* ����˵��: ��û������pwm��ռ�ձȾ͵��ô˺�����᷵��0��
*************************************************/
float get_PWM_N_duty(u8 PWM_N)
{
	return  PWM_N_INFO[PWM_N].duty;
}

/*************************************************
* ��������:void PWM_period(u16 Hz)
* ����: ����Ӳ��pwm��ͬһƵ�� ��������Ƶ������
* �����������õĺ���:
* 1.PWM_SET_PERIOD
* ����:u16 Hz:Ҫ�����pwm��Ƶ��,����Ӳ�����ޣ�����ͬʱ�ı�6·pwm��Ƶ��
* ���: ��
* ����ֵ: ��
* ����: �˺���ֻ������pwm�ļ�������ʼֵ���Ӷ����pwm��ͬƵ�ʵ������
		�������ڵ�Ƭ��Ӳ�����ޣ������Ե�����ÿ·pwm��Ƶ�ʽ����޸ģ�
		ֻ��һ��ȫ�ġ�
*************************************************/
void set_PWM_period(u8 PWM_N, u16 Hz)
{
	PWM_N_INFO[PWM_N].period = Hz;
	PWM_UNLOCK;
	PWM_ALL_NO;
	PWM_SET_PERIOD((u16)(MAIN_Fosc / (Hz*PWM_N_INFO[PWM_N].DIV)));
	PWM_LOCK;


}

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
* ����˵��:Ϊ��ֹ��ƽ������ת��������Сռ�ձ�Ϊ0.05�����Ϊ0.95
*          ���������ռ�ձȵ��޶������ڷ��϶�������ռ�ձȡ�������0.05f -> 0.025f
*************************************************/
void set_PWM_duty(u8 PWM_N, float duty)
{
	if (duty > 0.95f)
	{
		duty = 0.95f;
	}
	if (duty < 0.025f)
	{
		duty = 0.025f;
	}
	PWM_N_INFO[PWM_N].duty = duty;//�洢ռ�ձ�ֵ
	PWM_UNLOCK;
	PWM_SET_T12_PERIOD(PWM_N, 0, ((PWM_N_INFO[PWM_N].duty *	(MAIN_Fosc / (PWM_N_INFO[PWM_N].period*PWM_N_INFO[PWM_N].DIV))) * 10 + 5) / 10);
	PWM_LOCK;
}
//************************************
// Method:    setPWM_DIV
// FullName:  setPWM_DIV
// Access:    public 
// Returns:   void
// Qualifier: ����Ԥ����
// Parameter: u8 PWM_N
// Parameter: u8 DIV
//************************************
void setPWM_DIV(u8 PWM_N, u8 DIV)
{
	PWM_N_INFO[PWM_N].DIV = DIV;
}
u8 getPWM_DIV(u8 PWM_N)
{
	return PWM_N_INFO[PWM_N].DIV;
}
void open_PWM_ALL(void)
{
	PWM_UNLOCK;
	PWM_ALL_EN;
	PWM_LOCK;
}
void close_PWM_ALL(void)
{
	PWM_UNLOCK;
	PWM_ALL_NO; //�ܿ���
	PWM_LOCK;

}
void open_PWM_N(u8 PWM_N)
{
	PWM_UNLOCK;
	PWM_N_EN(PWM_N);
	PWM_N_INFO[PWM_N].state = ON;
	PWM_ALL_EN; //�ܿ���,�����ֲ��е�Ҫ��
	PWM_LOCK;


}
void close_PWM_N(u8 PWM_N)
{
	PWM_UNLOCK;
	PWM_N_NO(PWM_N);
	PWM_N_INFO[PWM_N].state = OFF;
	PWM_LOCK;

}
bit get_PWM_N_state(u8 PWM_N)
{

	return  PWM_N_INFO[PWM_N].state;
}

//////////////������Ϊ˽�к�������ֹ�Ķ���//////////////////////
//
//************************************
// Method:    PWM_SET_PERIOD
// FullName:  PWM_SET_PERIOD
// Access:    public static 
// Returns:   u8
// Qualifier: ����PWM����
// Parameter: u16 period
//************************************
static u8 PWM_SET_PERIOD(u16 period)
{
	if (0x8000 > period)
	{
		PWMCL = (u8)(period);
		PWMCH = (u8)(period >> 8);
		return 0;
	}
	else
	{
		return 1;
	}
}

//
//************************************
// Method:    PWM_SET_T12_PERIOD
// FullName:  PWM_SET_T12_PERIOD
// Access:    public static 
// Returns:   u8
// Qualifier: ����PWM��һ�κ͵ڶ��η�ת����
// Parameter: u8 PWM_N
// Parameter: u16 period1
// Parameter: u16 period2
//************************************
static u8 PWM_SET_T12_PERIOD(u8 PWM_N, u16 period1, u16 period2)
{
	switch (PWM_N)
	{
	case PWM_2:
		PWM2T1L = (u8)(period1);
		PWM2T1H = (u8)(period1 >> 8);
		PWM2T2L = (u8)(period2);
		PWM2T2H = (u8)(period2 >> 8);
		return 0;
		break;
	case PWM_3:
		PWM3T1L = (u8)(period1);
		PWM3T1H = (u8)(period1 >> 8);
		PWM3T2L = (u8)(period2);
		PWM3T2H = (u8)(period2 >> 8);
		return 0;
		break;
	case PWM_4:
		PWM4T1L = (u8)(period1);
		PWM4T1H = (u8)(period1 >> 8);
		PWM4T2L = (u8)(period2);
		PWM4T2H = (u8)(period2 >> 8);
		return 0;
		break;
	case PWM_5:
		PWM5T1L = (u8)(period1);
		PWM5T1H = (u8)(period1 >> 8);
		PWM5T2L = (u8)(period2);
		PWM5T2H = (u8)(period2 >> 8);
		return 0;
		break;
	case PWM_6:
		PWM6T1L = (u8)(period1);
		PWM6T1H = (u8)(period1 >> 8);
		PWM6T2L = (u8)(period2);
		PWM6T2H = (u8)(period2 >> 8);
		return 0;
		break;
	case PWM_7:
		PWM7T1L = (u8)(period1);
		PWM7T1H = (u8)(period1 >> 8);
		PWM7T2L = (u8)(period2);
		PWM7T2H = (u8)(period2 >> 8);
		return 0;
		break;
	default:
		return 1;
		break;
	}
}
