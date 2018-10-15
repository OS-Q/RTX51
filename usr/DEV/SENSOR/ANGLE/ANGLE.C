#include "ANGLE.h"
#include "../../../../SOFTWARE/ALGORITHM/FILTER/FILTER.H"
#define  POTENTIOMETER
#ifdef POTENTIOMETER
//ADC初始化函数 p1^0
/*************************************************
* 函数名称:void    ADC_config(u8 pin,u8 speed)
* 描述: 初始化adc
* 输入：u8 pin:需要使用的adc引脚
*       u8 speed: adc的转换速度
* 其他说明:
* pin:
*                ADC_P10
*                ADC_P11
*                ADC_P12
*                ADC_P13
*                ADC_P14
*                ADC_P15
*                ADC_P16
*                ADC_P17
* speed:
*                ADC_90T
*                ADC_180T
*                ADC_360T
*                ADC_540T
*************************************************/
void    ADC_config(u8 pin, u8 speed)
{
    ADC_InitTypeDef     ADC_InitStructure;
    ADC_InitStructure.ADC_Px = pin;
    ADC_InitStructure.ADC_Speed = speed;
    ADC_InitStructure.ADC_Power = ENABLE;
    ADC_InitStructure.ADC_AdjResult = ADC_RES_H8L2;
    ADC_InitStructure.ADC_Polity = PolityLow;
    ADC_InitStructure.ADC_Interrupt = DISABLE;
    ADC_Inilize(&ADC_InitStructure);
    //ADC_PowerControl(ENABLE);
}


/*************************************************
* 函数名称: float getAngle(bit whichAngle)
* 描述:  读取当前风摆角度或者上一次读取的角度
* 输入:  bit whichAngle
* 返回值: float 角度
* 其他说明:
  接线方法已经固定，不能再改变
whichAngle:
            PRESENT_ANGLE
            LAST_ANGLE
*************************************************/

float getAngle(bit whichAngle)
{
    u16 angleData[10];
	u8  angleDataloopTemp1=0;
    static float presentAngle, lastAngle;  //此函数还可以返回上一次的角度值，不需要读取时间 ，是静态的数据，因为需要保存
    if (whichAngle)  //返回当前结果
    {
    
		for(angleDataloopTemp1 = 0; angleDataloopTemp1 < 10; angleDataloopTemp1++) //读取10次数据并保存在数组中
			{
				angleData[angleDataloopTemp1] =  Get_ADC10bitResult(ADC_CH0);
			}
	     presentAngle= filter(angleData,10,1024,0);
       presentAngle=(0.3261f*presentAngle -19.36f);
        lastAngle = presentAngle;
        return presentAngle;
    }
    else  //返回上一次结果
    {
        return  lastAngle;
    }
}
#endif
