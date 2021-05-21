 /************************************************************
 * ��֯���ƣ�
 * �ļ�����: K:\��Ƭ�����\���Ӵ���������\SOFTWARE\ALGORITHM\PID\PID.H
 * ����:     
 * �汾 :    
 * ����:     2017/07/06
 * ����:
 * ��ʷ�޸ļ�¼:
 * <����> <ʱ��> <�汾 > <����>
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
#define PID_NUM	2   //��Ҫʹ�ö��ٸ�pid
#define PID_1 0
#define PID_2 1






/*************************************************
* ��������: void PID_config(float kp,float ki,float kd)
*                    ����:
*************************************************
* pid�㷨��ʼ��������������������P,I,D,
* �˺���ֻ����Ϊ��ʼ����������Ϊ����������ֵ�Ľӿ�
* �����Ҫ����������ֵ����ʹ��setPID_data()����
* ***********************************************
* ����: float kp,float ki,float kd
* ���:     ��
* ����ֵ:   ��
* ����˵��: ��
*************************************************/
void PID_config(u8 PID_N, float kp, float ki, float kd);//pid�㷨��ʼ��������������������PID


 
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