#include "SERVO.h"
#include "../../../BSP/STC15_PWM.H"
#include "../../../BSP/GPIO.H"

/**********************************
* 文件名称：舵机控制
* 作者：夏志强
* 版本：1.0
* 日期：2017/07/08
* 描述：
* 1.0：编写了舵机的主要控制函数，包括：舵机开关控制、舵机角度读取与设定
************************************/

typedef struct
{
	float Set_angle;//舵机旋转角度
	unsigned char state;//舵机状态
	float Pulse_Width_L;//舵机最低脉冲宽度
	float Pulse_Width_H;//舵机最高脉冲宽度
	float Str_DIV;//舵机时间精度
	unsigned int Str_N;//舵机划分
	float Current_angle;//当前舵机角度
	float Str_MAX_angle;//舵机最大旋转角度
	float Str_ACC_angle;//舵机角度精度
	unsigned int Str_state;//舵机开关
	float Actual_Pulse_Width;//实际脉宽
}StrMotor;

static StrMotor str_motor[SERVO_NUM]; //需要使用多少个舵机


/**********************************************
 *函数：Inti_Str_Motor(float,float,float,unsigned int)
 *描述：对舵机进行初始化
 *输入：
 *1.pl为最低可接收的脉冲宽度，单位为ms                  
 *2.ph为最高可接收的脉冲宽度，单位为ms                 
 *3.n为脉冲分级
 *输出：无
 *返回值：void
 *其他说明：
 **********************************************/
void Init_Str_Motor(u8 MOTOR,float pl,float ph,float ma,unsigned int n)
{
	 GPIO_InitTypeDef    GPIO_InitStructure;     //结构定义
    PWM_InitTypeDef  PWM_InitStructure;
	  GPIO_InitStructure.Mode = GPIO_PullUp;       //指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_InitStructure.Pin  = GPIO_Pin_7 ;    //指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
    GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);  //初始化
//		  GPIO_InitStructure.Mode = GPIO_PullUp;       //指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
//    GPIO_InitStructure.Pin  = GPIO_Pin_1 ;    //指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
//    GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);  //初始化

    P37=1;
//	  P21=1;
		PWM_UNLOCK;
    PWM_InitStructure.PWM_GOTO_ADC=DISABLE;
    PWM_InitStructure.      PWM_V_INIT= PWM_LOW;
    PWM_InitStructure.      PWM_0ISR_EN=  DISABLE;
    PWM_InitStructure.      PWM_OUT_EN=ENABLE;
    PWM_InitStructure.     PWM_UNUSUAL_EN= DISABLE;
    PWM_InitStructure.     PWM_UNUSUAL_OUT=  DISABLE;
    PWM_InitStructure.     PWM_UNUSUAL_ISR_EN=DISABLE;
    PWM_InitStructure.     PWM_UNUSUAL_CMP0_EN=DISABLE;
    PWM_InitStructure.     PWM_UNUSUAL_P24_EN=DISABLE;
    PWM_InitStructure.       PWM_CLOCK=PWM_Clock_NT;
    PWM_InitStructure.       PWM_CLOCK_DIV=15;
    PWM_InitStructure.       PWM_SELECTx_IO=PWM_SELECT_N;
    PWM_InitStructure.     PWM_ISRx_EN=  DISABLE;
    PWM_InitStructure.       PWM_T1x_EN=   DISABLE;
    PWM_InitStructure.       PWM_T2x_EN=    DISABLE;
    PWM_InitStructure.       PWM_EN=  DISABLE;
    PWM_Inilize(MOTOR,&PWM_InitStructure) ;

    PWM_LOCK;
		setPWM_DIV(MOTOR,16);
		set_PWM_period(MOTOR,50);
		str_motor[MOTOR].Pulse_Width_L = pl;
		str_motor[MOTOR].Pulse_Width_H = ph;
		str_motor[MOTOR].Str_MAX_angle = ma;
		str_motor[MOTOR].Str_N = n;
		str_motor[MOTOR].Str_DIV = (str_motor[MOTOR].Pulse_Width_H - str_motor[MOTOR].Pulse_Width_L) / str_motor[MOTOR].Str_N;//计算舵机的最小精度，单位为ms
		str_motor[MOTOR].Str_ACC_angle = str_motor[MOTOR].Str_MAX_angle / (float)str_motor[MOTOR].Str_N;
		str_motor[MOTOR].Current_angle = 0;
}

/**********************************************
 *函数：set_STR_angle(float)
 *描述：设定舵机角度
 *输入：
 *1.angle为设定的角度，浮点型                 
 *输出：无
 *返回值：void
 *其他说明：
 **********************************************/
void set_STR_angle(u8 MOTOR,float angle)
{
		float str_duty;
		str_motor[MOTOR].Set_angle = angle;
		str_motor[MOTOR].Actual_Pulse_Width = (	(angle / str_motor[MOTOR].Str_ACC_angle) * str_motor[MOTOR].Str_DIV )+str_motor[MOTOR].Pulse_Width_L ;
//	if(str_motor[MOTOR].Actual_Pulse_Width >= str_motor[MOTOR].Pulse_Width_H)
//	{
//		set_PWM_duty(MOTOR,0.125f);
//	}
//	 else if(str_motor[MOTOR].Actual_Pulse_Width <= str_motor[MOTOR].Pulse_Width_L)
//	{
//		set_PWM_duty(MOTOR,0.025f);
//	}
//	else
	{
		str_duty =	str_motor[MOTOR].Actual_Pulse_Width	 / 20;
		set_PWM_duty(MOTOR,str_duty);
	}
		str_motor[MOTOR].Current_angle = str_motor[MOTOR].Set_angle;
}

/**********************************************
 *函数：read_STR_angle()
 *描述：读取舵机角度
 *输入：void                
 *输出：舵机当前角度
 *返回值：float
 *其他说明：
 **********************************************/
float read_STR_angle(u8 MOTOR)
{
		return str_motor[MOTOR].Current_angle;
}
bit open_STR(u8 MOTOR)
{ 
	open_PWM_N(MOTOR);
	str_motor[MOTOR].Str_state = ON;
	return 1;
}
bit close_STR(u8 MOTOR)
{
	close_PWM_N(MOTOR);
	str_motor[MOTOR].Str_state = OFF;
	return 1;
}
