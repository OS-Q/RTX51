#ifndef _SERVO_H_
#define _SERVO_H_
#include "../../../BSP/config.h"
#define SERVO_NUM 2
#define SERVO_1 0
#define SERVO_2 1
#define SERVO_3 2
extern void Init_Str_Motor(u8 MOTOR,float pl,float ph,float ma,unsigned int n) ;
extern void set_STR_angle(u8 MOTOR,float angle);
extern float read_STR_angle(u8 MOTOR);
extern bit open_STR(u8 MOTOR);
extern bit close_STR(u8 MOTOR);
#endif