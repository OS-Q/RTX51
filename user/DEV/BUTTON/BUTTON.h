#ifndef _BUTTON_H_
#define _BUTTON_H_
#include "../../BSP/config.h"
#include "../../BSP/GPIO.h"

#define FIRST_MEUN_NUM 0
#define SECOND_MEUN_NUM 1
#define BUTTON1_GPIO_PIN GPIO_Pin_3
#define BUTTON2_GPIO_PIN GPIO_Pin_4
#define BUTTON3_GPIO_PIN GPIO_Pin_5
#define BUTTON4_GPIO_PIN GPIO_Pin_6
#define BUTTON1 P23
#define BUTTON2 P24
#define BUTTON3 P25
#define BUTTON4 P26
/*********对外参数和接口函数***********/
extern void  buttonScan(void );
extern void Button_config(void);
extern bit getButtonState(u8 BUTTON_data); //读取按键状态函数,按下按键返回1，没按下返回0
#endif
