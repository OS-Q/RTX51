/************************************************************
* 组织名称： (C), 1988-1999, Tech. Co., Ltd.
* 文件名称: MOTOR.C
* 作者:  周晨阳
* 版本:  1.3
* 日期:  17/4/29
* 描述:  和电机有关的控制函数都在这里，还有pid算法控制也在其中
* 主要函数及其功能 : // 主要函数及其功能
* 1. -------
* 历史修改记录: // 历史修改记录
* <作者> <时间> <版本 > <描述>
* 周晨阳 17/6/216 1.0 创建此描述
* 周晨阳 17/7/9   1.1 更新了数据结构，可以定义任意数量的电机
***********************************************************/
#include "MOTOR.h"
#include "../../../BSP/STC15_PWM.h"
#include "../../../BSP/GPIO.h"

#define DC_MOTOR
#ifdef DC_MOTOR

struct DC_Motor
{
	u8 state;
	u8 speed;

};
static struct DC_Motor g_DC_Motor[DC_MOTOR_NUM];

/*************************************************
* 函数名称: void setMotorSpeed(bit motor,float speed)
* 描述: 设置电机速度函数
* 输入: motor：电机，头文件中定义
				speed：速度 0~1
* 其他说明:
*若要关闭电机请使用电机关闭函数，此函数无法关闭电机
*************************************************/
void setDC_MotorSpeed(u8 motor, float speed)
{

	if (speed > 0.95f)
	{
		speed = 0.95f;
	}
	if (speed < 0.05f)
	{

		speed = 0.05f;
	}

	//	PWM_duty(PWM_2,speed*0.65f);//根据不同电机乘于不同的增益
	set_PWM_duty(motor , speed);//根据不同电机乘于不同的增益
	g_DC_Motor[motor].speed = speed;
}
void open_DC_Motor(u8 motor)
{
	open_PWM_N(motor );
	g_DC_Motor[motor].state = ON;
}
void close_DC_Motor(u8 motor)
{
	close_PWM_N(motor );
	g_DC_Motor[motor].state = OFF;



}
bit getDC_MotorState(u8 motor)
{
	return g_DC_Motor[motor].state;

}
/*************************************************
* 函数名称: void    DC_MOTOR_config(void)
* 描述: 配置需要使用的pwm通道
* 输入: 无
* 返回值: 无
* 其他说明: 将会自动初始化相应的io引脚
*************************************************/
void    DC_MOTOR_config(void)
{
	
	GPIO_InitTypeDef    GPIO_InitStructure;     //结构定义
	PWM_InitTypeDef  PWM_InitStructure;
	GPIO_InitStructure.Mode = GPIO_PullUp;


	GPIO_InitStructure.Pin = GPIO_Pin_7;    //PWM2
	GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);  //初始化



	GPIO_InitStructure.Pin = GPIO_Pin_1;    //PWM4
	GPIO_Inilize(GPIO_P2, &GPIO_InitStructure);  //初始化
	P37 = 1;
	P21 = 1;


	PWM_UNLOCK;
	PWM_InitStructure.PWM_GOTO_ADC = DISABLE;
	PWM_InitStructure.PWM_V_INIT = PWM_LOW;
	PWM_InitStructure.PWM_0ISR_EN = DISABLE;
	PWM_InitStructure.PWM_OUT_EN = ENABLE;
	PWM_InitStructure.PWM_UNUSUAL_EN = DISABLE;
	PWM_InitStructure.PWM_UNUSUAL_OUT = DISABLE;
	PWM_InitStructure.PWM_UNUSUAL_ISR_EN = DISABLE;
	PWM_InitStructure.PWM_UNUSUAL_CMP0_EN = DISABLE;
	PWM_InitStructure.PWM_UNUSUAL_P24_EN = DISABLE;
	PWM_InitStructure.PWM_CLOCK = PWM_Clock_NT;
	PWM_InitStructure.PWM_CLOCK_DIV = 0x00;
	PWM_InitStructure.PWM_SELECTx_IO = PWM_SELECT_N;
	PWM_InitStructure.PWM_ISRx_EN = DISABLE;
	PWM_InitStructure.PWM_T1x_EN = DISABLE;
	PWM_InitStructure.PWM_T2x_EN = DISABLE;
	PWM_InitStructure.PWM_EN = DISABLE;
	PWM_Inilize(PWM_2, &PWM_InitStructure);
	PWM_Inilize(PWM_3, &PWM_InitStructure);
  set_PWM_period (PWM_2,5000);
	set_PWM_period (PWM_3,5000);
	PWM_LOCK;


}

#endif


