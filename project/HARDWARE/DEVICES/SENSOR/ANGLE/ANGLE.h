#ifndef _ANGLE_H_
#define _ANGLE_H_
#include "../../../BSP/config.h"
#include "../../../BSP/ADC.h"
#define LAST_ANGLE   0   //当前角度，函数参数宏定义
#define PRESENT_ANGLE 1   //上一次角度，函数参数宏定义
/*********对外参数和接口函数***********/
/*************************************************
* 函数名称:void    ADC_config(u8 pin,u8 speed)
* 描述: 初始化adc
* 输入：u8 pin:需要使用的adc引脚
*       u8 speed: adc的转换速度
* 其他说明:
pin:
                 ADC_P10
                 ADC_P11
                 ADC_P12
                 ADC_P13
                 ADC_P14
                 ADC_P15
                 ADC_P16
                 ADC_P17
speed:
                 ADC_90T
                 ADC_180T
                 ADC_360T
                 ADC_540T
*************************************************/
extern void    ADC_config(u8 pin,u8 speed)  ;
/*************************************************
* 函数名称: float getAngle(bit whichAngle)
* 描述:  读取当前风摆角度或者上一次读取的角度
* 输入:  bit whichAngle
* 返回值: float 角度
* 其他说明:
现在已经测量了电阻的线性曲线，Y=(101/4)*X+ 305/2,其中y是电阻输出值，
x是角度值 ，需要串联一个10k的电阻
whichAngle:
                        PRESENT_ANGLE
            LAST_ANGLE
*************************************************/
extern float getAngle(bit whichAngle)  ;
/****************************/
#endif
