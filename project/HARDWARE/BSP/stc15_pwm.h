/************************************************************
* 文件名称: STC15_PWM.h
* 作者:  第三方
* 版本:  1.1
* 日期:  2017/4/27
* 描述:  硬件pwm的库函数头文件
* 历史修改记录: // 历史修改记录
* <作者> <时间> <版本 > <描述>
* 周晨阳 2017/5/6 1.1   简化了硬件pwm的配置，只需要几个简单的函数调用便可以初始化任意一路pwm
***********************************************************/
#ifndef __STC15_PWM_H__
#define __STC15_PWM_H__
#include    "config.h"
                             /*********对外参数和接口函数***********/
/************************************
硬件PWMio引脚
PWM_N| io  | 第二组
PWM2 :P3.7 -> P2.7
PWM3 :P2.1 -> P4.5
PWM4 :P2.2 -> P4.4
PWM5 :P2.3 -> P4.2
PWM6 :P1.6 -> P0.7
PWM7 :P1.7 -> P0.6
************************************/
 void setPWM_DIV(u8 PWM_N,u8 DIV);
 u8 getPWM_DIV(u8 PWM_N);
void open_PWM_ALL(void);
void close_PWM_ALL(void);
void close_PWM_N(u8 PWM_N);
void open_PWM_N(u8 PWM_N);
bit getPWM_state(u8 PWM_N) ;
	/*************************************************
* 函数名称: u32 getPWM_period(void )
* 描述: 读取所设置的pwm频率信息
* 输入: 无
* 输出: 无
* 返回值: pwm频率
* 其他说明: 若没有设置pwm的频率就调用此函数则返回不确定数值；
*************************************************/
u32  get_PWM_period(u8 PWN_N);



/*************************************************
* 函数名称: float getPWM_n_duty(u8 PWM_N)
* 描述: 返回PWM_N的占空比信息
* 输入: u8 PWM_N
* 输出: 无
* 返回值: PWM_N的占空比信息,float形式
* 其他说明: 若没有设置pwm的占空比就调用此函数则返回不确定数值；
*************************************************/
float get_PWM_N_duty(u8 PWM_N);






/*************************************************
* 函数名称:void PWM_period(u16 Hz)
* 描述: 设置硬件pwm的同一频率 ，并保存频率数据
* 被本函数调用的函数:
* 1.PWM_SET_PERIOD
* 调用本函数的函数:
* 输入:
* 1.u16 Hz:要输出的pwm的频率，作为计数器的参数值，由于硬件所限，将会改变所有6个pwm的频率
* 输出: 无
* 返回值: 无
* 其他: 此函数只能设置pwm的计数器初始值，从而完成pwm不同频率的输出，
        但是由于单片机硬件所限，不可以单独对每路pwm的频率进行修改，
        只能一改全改。
*************************************************/
void set_PWM_period(u8 PWM_N,u16 Hz)  ;




/*************************************************
* 函数名称: void PWM_duty(u8 PWM_N,float duty)
* 描述: 修改某一路pwm的占空比 ，并保存占空比数据
* 被本函数调用的函数:
* 调用本函数的函数:
* 输入:
* 1.u8 PWM_N ： 哪一路pwm
* 2.float duty：占空比，使用小数，如0.8代表80%的占空比
* 输出: 无
* 返回值: 无
* 其他说明:
*************************************************/
void set_PWM_duty(u8 PWM_N,float duty);



static u8 PWM_SET_PERIOD(u16 period);
static u8 PWM_SET_T12_PERIOD(u8 PWM_N, u16 period1, u16 period2);
//u8   PWM_SET_PERIOD(u16 period);
//u8   PWM_SET_T12_PERIOD(u8 PWM_N,u16 period1,u32 period2);
//void PWM_Inilize(u8 PWM_N,PWM_InitTypeDef *PWMx);
//u8 PWM_N,
             /******************内部参数，无须查看********************/
#define PWM_2           0
#define PWM_3           1
#define PWM_4           2
#define PWM_5           3
#define PWM_6           4
#define PWM_7           5
#define PWM_HIGHT  1
#define PWM_LOW    0
#define PWM_Clock_NT        0
#define PWM_Clock_Timer2_OF 1
#define PWM_SELECT_N        0
#define PWM_SELECT_N_2      1
////////////常量宏///////////////////////////////////////////////////////////
///////////////////////////////////////////////
#define PWM_DEFAULT_PERIOD 5000
#define PWM_DEFAULT_DUTY 0.5f


//PWM寄存器操作使能 如果禁止的话 凡是关于PWM的寄存器都不能操作
#define PWM_UNLOCK    P_SW2|=0X80      /*使能*/
#define PWM_LOCK      P_SW2&=(~0X80)   /*禁止*/

///////////////////////////////////////////////
//PWM总开关
#define PWM_ALL_EN        PWMCR|=(1<<7)
#define PWM_ALL_NO        PWMCR&=(~(1<<7))
//PWM次级开关
#define PWM_N_EN(PWM_N)   PWMCR|=(1<<(PWM_N))
#define PWM_N_NO(PWM_N)   PWMCR&=(~(1<<(PWM_N)))

////PWM对应管脚初始值
////i=PWM_2~PWM_7
//#define PWM_INIT_HIGHT(i)        PWMCFG|=(1<<(i));
//#define PWM_INIT_LOW(i)          PWMCFG&=(~(1<<(i)))
typedef struct
{
    u8 PWM_GOTO_ADC;            //ENABLE=计数器归零时 触发ADC
    u8 PWM_V_INIT;              //PWM_HIGHT=初始高电平  PWM_LOW=初始低电平
    u8 PWM_0ISR_EN;             //ENABLE=使能PWM计数器归零中断  DISABLE=关闭PWM计数器归零中断 但 CBIF仍然会被硬件置位
    u8 PWM_OUT_EN;              //ENABLE=PWM通道x的端口为PWM波形输出口 受PWM波形发生器控制
    u8 PWM_UNUSUAL_EN;          //ENABLE=使能PWM的外部异常检测功能
    u8 PWM_UNUSUAL_OUT;         //ENABLE=发生异常时，PWM对应的输出口会变成 高阻输入模式
    u8 PWM_UNUSUAL_ISR_EN;      //ENABLE=使能异常检测中断 DISABLE=关闭异常检测中断 但FDIF仍然会被硬件置位
    u8 PWM_UNUSUAL_CMP0_EN;     //ENABLE=异常检测源为比较器的输出 当比较结果为高时 触发PWM异常
    u8 PWM_UNUSUAL_P24_EN;      //ENABLE=异常检测源为P24/PWMFLT 当P24=1 触发PWM异常
    u8 PWM_CLOCK;               //PWM_Clock_NT=PWM的时钟源是系统时钟经分频后的时钟  PWM_Clock_Timer2_OF=PWM的时钟源是TMER2的溢出脉冲
    u8 PWM_CLOCK_DIV;           //当PWM_CLOCK=PWM_Clock_NT时 PWM的时钟源是系统时钟/(PS[3:0]+1)
    u8 PWM_SELECTx_IO;          //PWM_SELECT_N=PWM第一选择IO口 PWM_SELECT_N_2=PWM第二选择IO口
    u8 PWM_ISRx_EN;             //ENABLE=使能PWMx中断 使能第一翻转或第二翻转中断
    u8 PWM_T1x_EN;              //ENABLE=使能第一翻转中断
    u8 PWM_T2x_EN;              //ENABLE=使能第二翻转中断
    u8 PWM_EN;                  //ENABLE=PWM使能 在其他PWM参数设置好后最后设置 如果被关闭后在打开，则PWM计数器重新从0计数
} PWM_InitTypeDef;
 void PWM_Inilize(u8 PWM_N,PWM_InitTypeDef *PWMx);
                             

#endif
