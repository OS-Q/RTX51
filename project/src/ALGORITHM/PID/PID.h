 /************************************************************
 * 组织名称：
 * 文件名称: K:\单片机相关\电子大赛程序框架\SOFTWARE\ALGORITHM\PID\PID.H
 * 作者:     
 * 版本 :    
 * 日期:     2017/07/06
 * 描述:
 * 历史修改记录:
 * <作者> <时间> <版本 > <描述>
 * 
 ***********************************************************/
 
 #ifndef _PID_H_
 #define _PID_H_
#include "../HARDWARE/BSP/config.h"
#define SET_ANGLE    0
#define ERR          1
#define ERR_LAST     2
#define KP 			 3
#define KI 			 4
#define KD           5
#define INTEGRAL     6
#define OUTPUT       7
#define PID_NUM	2   //需要使用多少个pid
#define PID_1 0
#define PID_2 1






/*************************************************
* 函数名称: void PID_config(float kp,float ki,float kd)
*                    描述:
*************************************************
* pid算法初始化函数，参数是三个，P,I,D,
* 此函数只能作为初始化，不能作为调整这三个值的接口
* 如果需要调整这三个值，请使用setPID_data()函数
* ***********************************************
* 输入: float kp,float ki,float kd
* 输出:     无
* 返回值:   无
* 其他说明: 无
*************************************************/
void PID_config(u8 PID_N, float kp, float ki, float kd);//pid算法初始化函数，参数是三个，PID


 
void openPID(u8 PID_N);
void closePID(u8 PID_N);
bit PID(u8 PID_N);
void PID_setParameterInferiorLimit(u8 PID_N, float value);
void PID_setParameterUpperLimit(u8 PID_N, float value);
void PID_setActualParameter(u8 PID_N, float value);
void PID_setKi(u8 PID_N, float value);
void PID_setKp(u8 PID_N, float value);
void PID_setKd(u8 PID_N, float value);
void PID_setTargetParameter(u8 PID_N, float value);
float PID_getParameter(u8 PID_N);
float PID_getErr(u8 PID_N);
float PID_getErrLast(u8 PID_N);
float PID_getKp(u8 PID_N);
float PID_getKi(u8 PID_N);
float PID_getKd(u8 PID_N);
float PID_getOutput(u8 PID_N);
float PID_getIntegral(u8 PID_N);
bit PID_getState(u8 PID_N);
#endif