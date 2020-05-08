/************************************************************
* 组织名称：
* 文件名称: BUTTON.c
* 作者:  周晨阳
* 版本 : v1.0
* 日期:
* 描述: 按键初始化及相关函数
* 主要函数及其功能 : 

* 历史修改记录: // 历史修改记录
* <作者> <时间> <版本 > <描述>
* 周晨阳
***********************************************************/
#include "BUTTON.h"
#include "../../BSP/delay.h"

#define BUTTON
#ifdef BUTTON
//extern  struct PID pid;
/*************************************************
* 函数名称: void Button_config()
* 描述: 片上按键io初始化函数
* 其他说明: 初始化 P23,24,25,26为按键
*************************************************/
void Button_config(void)
{
    GPIO_InitTypeDef    GPIO_InitStructure;     //结构定义
    GPIO_InitStructure.Pin  = BUTTON1_GPIO_PIN | BUTTON2_GPIO_PIN | BUTTON3_GPIO_PIN|BUTTON4_GPIO_PIN;      //指定要初始化的IO, GPIO_Pin_0 ~ GPIO_Pin_7, 或操作
    GPIO_InitStructure.Mode = GPIO_PullUp;       //指定IO的输入或输出方式,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
    GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);  //初始化
    P23=1;
    P24=1;
    P25=1;
    P26=1;
}
/*************************************************
* 函数名称:static bit digitalRead(pin)//读取按键状态函数,按下按键返回1，没按下返回0
* 描述: 带防抖的引脚电平读取函数
* 输入: 需要读取的pin* 输出:
* 返回值: 引脚电平，按下返回1，未按下返回0
* 其他说明: 内部函数，外部无须调用
*************************************************/
static bit digitalRead(pin)//读取按键状态函数,按下按键返回1，没按下返回0
{
    if(!pin)
    {
        return !pin;
    }
}
static bit BUTTON1_bit=0;
static bit BUTTON2_bit=0;
static bit BUTTON3_bit=0;
static bit BUTTON4_bit=0;
/*************************************************
* 函数名称: bit getButtonState(u8 BUTTON_data)
* 描述: 按键状态读取
* 输入: 按键引脚宏
* 返回值: 按键状态，按下返回1，未按下返回0
* 其他说明: 此函数为外界接口函数
*************************************************/
bit getButtonState(u8 BUTTON_data)
{
    switch(BUTTON_data)
    {
    case BUTTON1_GPIO_PIN:
        return   BUTTON1_bit;
        break;
    case BUTTON2_GPIO_PIN:
        return   BUTTON2_bit;
        break;
    case BUTTON3_GPIO_PIN:
        return   BUTTON3_bit;
        break;
    case BUTTON4_GPIO_PIN:
        return   BUTTON4_bit;
        break;
    }
}
/*************************************************
* 函数名称: void  buttonScan(void )//按键扫描函数
* 描述: 按键检测程序
* 输入: 无
* 输出: 无
* 返回值: 无
* 其他说明: 此按键检测程序没有使用到定时器，
*           将在后续的工程中改进此函数
*************************************************/
void  buttonScan(void )//按键扫描函数 ,有bug
{
    if(digitalRead(BUTTON1))
    {
        if(digitalRead(BUTTON1))
        {
#ifdef BUTTON_DEBUG
            PrintString1("BUTTON1 is on\n");
#endif
            BUTTON1_bit=1;
        }
    }
    else
    {
        BUTTON1_bit=0;
    }
    if(digitalRead(BUTTON2))
    {
        if(!BUTTON2_bit)
        {
#ifdef BUTTON_DEBUG
            PrintString1("BUTTON2 is on\n");
#endif
            BUTTON2_bit=1;
        }
    }
    else
    {
        BUTTON2_bit=0;
    }
    if(digitalRead(BUTTON3))
    {
        if(!BUTTON3_bit)
        {
#ifdef BUTTON_DEBUG
            PrintString1("BUTTON3 is on\n");
#endif
            BUTTON3_bit=1;
           
        }
    }
    else
    {
        BUTTON3_bit=0;
    }
    if(digitalRead(BUTTON4))
    {
        if(!BUTTON4_bit)
        {
#ifdef BUTTON_DEBUG
            PrintString1("BUTTON4 is on\n");
#endif
            BUTTON4_bit=1;
           
        }
    }
    else
    {
        BUTTON4_bit=0;
    }
}
#endif
