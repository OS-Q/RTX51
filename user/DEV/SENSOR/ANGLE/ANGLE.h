#ifndef _ANGLE_H_
#define _ANGLE_H_
#include "../../../BSP/config.h"
#include "../../../BSP/ADC.h"
#define LAST_ANGLE   0   //��ǰ�Ƕȣ����������궨��
#define PRESENT_ANGLE 1   //��һ�νǶȣ����������궨��
/*********��������ͽӿں���***********/
/*************************************************
* ��������:void    ADC_config(u8 pin,u8 speed)
* ����: ��ʼ��adc
* ���룺u8 pin:��Ҫʹ�õ�adc����
*       u8 speed: adc��ת���ٶ�
* ����˵��:
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
* ��������: float getAngle(bit whichAngle)
* ����:  ��ȡ��ǰ��ڽǶȻ�����һ�ζ�ȡ�ĽǶ�
* ����:  bit whichAngle
* ����ֵ: float �Ƕ�
* ����˵��:
�����Ѿ������˵�����������ߣ�Y=(101/4)*X+ 305/2,����y�ǵ������ֵ��
x�ǽǶ�ֵ ����Ҫ����һ��10k�ĵ���
whichAngle:
                        PRESENT_ANGLE
            LAST_ANGLE
*************************************************/
extern float getAngle(bit whichAngle)  ;
/****************************/
#endif
