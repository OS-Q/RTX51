/************************************************************
* 组织名称：电子大赛小组
* 文件名称: MOTOR.H
* 作者:     周晨阳
* 版本 :    1.0
* 日期:
* 描述: 	 电机相关头文件
* 历史修改记录: 1.0:添加了void DC_MOTOR_config(void)电机初始化函数
* <作者> <时间> <版本 > <描述>
***********************************************************/
#ifndef _MOTOR_H_
#define _MOTOR_H_
#include <math.h>
#include "../../../BSP/config.h"
#define DC_MOTOR_NUM	2
#define DC_MOTOR_1	0
#define DC_MOTOR_2	1

/************************************
硬件PWMio引脚（没有pwm1）
PWM_N| io  | 第二组
PWM2 :P3.7 -> P2.7
PWM3 :P2.1 -> P4.5
PWM4 :P2.2 -> P4.4
PWM5 :P2.3 -> P4.2
PWM6 :P1.6 -> P0.7
PWM7 :P1.7 -> P0.6
************************************/

#define LEFT_MOTOR   1
#define RIGHT_MOTOR  0
#define STOP         0


void close_DC_Motor(u8 motor);
void open_DC_Motor(u8 motor);
bit getDC_MotorState(u8 motor);
/*************************************************
* 函数名称: void setMotorSpeed(bit motor,float speed)
* 描述: 设置电机速度函数
* 输入: motor：电机，头文件中定义
				speed：速度 0~1   0时电机停转
* 其他说明: 
*************************************************/
void setDC_MotorSpeed(u8 motor,float speed);
extern void DC_MOTOR_config(void);//电机/IO口初始化



#endif
