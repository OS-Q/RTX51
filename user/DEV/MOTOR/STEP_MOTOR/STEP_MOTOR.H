#ifndef _STEP_MOTOR_H_
#define _STEP_MOTOR_H_
#include "../../../BSP/config.h"

#define CW 0	//转向，顺时针
#define CCW 1	//转向，逆时针
//如有需要可更改电机的名称
#define	STEP_MOTOR_1 0
#define	STEP_MOTOR_2 1
#define	STEP_MOTOR_3 2
#define	STEP_MOTOR_4 3
#define	STEP_MOTOR_5 4
#define	STEP_MOTOR_6 5

extern bit setStepMotorWithAngle(u8 motor, float angle, u8 speed);
extern bit setStepMotorWithRound(u8 motor, u16 round, u8 speed);
extern u8 getStepMotorState(u8 motor);
extern void close_StepMotor(u8 motor);
extern void open_StepMotor(u8 motor);
extern void stepMotor_Init(u8 motor, float div, u8 driverDiv, u16 maxPeriod);
extern bit freeStepMotor(u8 motor);
#endif
