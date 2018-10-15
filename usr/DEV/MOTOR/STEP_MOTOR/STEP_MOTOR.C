/************************************************************
* 组织名称：
* 文件名称: K:\单片机相关\电子大赛程序框架\HARDWARE\DEVICES\MOTOR\STEP_MOTOR\STEP_MOTOR.C
* 作者:  周晨阳
* 版本:  1.0
* 日期:  2017/07/11
* 描述: 步进电机的驱动程序
* 历史修改记录:
* <作者> <时间> <版本 > <描述>
*
***********************************************************/

#include "STEP_MOTOR.H"
#include "../../../COMMON_HARDWARE/fixedPulser.h"
#define STEP_MOTOR_NUM 2 
typedef struct
{
	u16 angle;//旋转角度
	u8 state;//电机状态：停转（堵住），停转（自由态），旋转
	u16 round;//旋转圈数
	u8 speed;//旋转速度
	float DIV;//步进电机单步角度值 ，如1.8°
	u8 driverDiv;//步进电机驱动板上所选的角度细分值 2，4，8，16
	u16 maxPeriod; 	//步进电机所能承受的最大频率
	u8 diversion;//电机转向


}StepMotor;
static  StepMotor g_stepMotor[STEP_MOTOR_NUM];
//enum {
//	 RUNNING,FREE,LOCKED
//}g_stepMotor[0]=LOCKED;

//************************************
// Method:    setStepMotorWithAngle
// FullName:  setStepMotorWithAngle
// Access:    public 
// Returns:   bit
// Qualifier: 设置步进电机的旋转角度
// Parameter: u8 motor：哪一个电机
// Parameter: u16 angle 旋转角度，不限于360°，可以超过360°
// Parameter: u8 speed：旋转速度，1-100
//************************************
bit setStepMotorWithAngle(u8 motor, float angle, u8 speed)
{
	setPulse(motor, (u16)((1 + g_stepMotor[motor].maxPeriod / 99)*speed - (g_stepMotor[motor].maxPeriod / 99)), \
		(u16)((angle*g_stepMotor[STEP_MOTOR_1].driverDiv) / g_stepMotor[STEP_MOTOR_1].DIV));
	return 1;
}
//************************************
// Method:    setStepMotorWithRound
// FullName:  setStepMotorWithRound
// Access:    public 
// Returns:   bit
// Qualifier: 设置步进电机的旋转圈数
// Parameter: u8 motor
// Parameter: u16 round
// Parameter: u8 speed
//************************************
bit setStepMotorWithRound(u8 motor, u16 round, u8 speed)
{
	setStepMotorWithAngle(motor, 360 * round, speed);
	return 1;
}
//************************************
// Method:    getStepMotorState
// FullName:  getStepMotorState
// Access:    public 
// Returns:   bit
// Qualifier: 读取步进电机当前的状态
// Parameter: u8 motor
//************************************
u8 getStepMotorState(u8 motor)
{
	return g_stepMotor[motor].state;
}
bit setStepMotorDiversion(u8 motor)
{

	return 1;
}
//************************************
// Method:    close_StepMotor
// FullName:  close_StepMotor
// Access:    public 
// Returns:   void
// Qualifier: 关闭步进电机
// Parameter: u8 motor
//************************************
void close_StepMotor(u8 motor)
{
	closePulser(motor);
	g_stepMotor[motor].state = OFF;

}
//************************************
// Method:    open_StepMotor
// FullName:  open_StepMotor
// Access:    public 
// Returns:   void
// Qualifier: 打开步进电机
// Parameter: u8 motor
//************************************
void open_StepMotor(u8 motor)
{
	openPulser(motor);
	g_stepMotor[motor].state = ON;
}
bit freeStepMotor(u8 motor)
{

	return 1;
}
bit lockStepMotor(u8 motor)
{

	return 1;
}
//************************************
// Method:    stepMotor_Init
// FullName:  stepMotor_Init
// Access:    public 
// Returns:   void
// Qualifier: 设置
// div:步进电机步进角
// driverDiv：驱动板细分值
// maxPeriod：电机所能承受的最大启动频率
//************************************
void stepMotor_Init(u8 motor,float div,u8 driverDiv,u16 maxPeriod)
{
	g_stepMotor[motor].DIV = div;//1.8°的步进角
	g_stepMotor[motor].driverDiv = driverDiv; //驱动板上使用8的细分
	g_stepMotor[motor].maxPeriod = maxPeriod;
	PulserInit();
}
