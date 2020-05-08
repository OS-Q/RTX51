#include "mode.h"
#include "../ALGORITHM/PID/PID.h"
#include "../../HARDWARE/DEVICES/MOTOR/DC_MOTOR/MOTOR.h"
#include "../../HARDWARE/BSP/timer.h"
#include "../../HARDWARE/BSP/USART1.h"
void mode1(void)
{
					static bit step1=0;//模式一步骤1标志位
          static bit step2=0; //步骤2 标志位
          static bit step3=0;  //步骤三标志位

          if(step1)//步骤一已经完成
            {

              if(step2) //如果步骤2已完成
                {
                  if(step3) //如果步骤三已经完成
                    {
                      //模式一已经完成 ，蜂鸣器开始叫
                //      mode=0;//初始化模式
                      step1=0;
                      step2=0;
                      step3=0;

                    }
                  else//如果步骤三没有完成
                    {
                      close_DC_Motor(LEFT_MOTOR);
									    close_DC_Motor(RIGHT_MOTOR);

                      step3=OK;
                      PrintString1("step3 is ok\n");

                    }

                }
              else //如果步骤二没有完成
                {
                  setTimeout(Timer1,5000); //设置定时器定时长度 ,5秒
                  //////////////////////定时器////////////////////////////////////////
                  if(isExpiredTimer(Timer1))   //如果达到定时时间
                    {

                      setDC_MotorSpeed(LEFT_MOTOR,0.01f);
                      setDC_MotorSpeed(RIGHT_MOTOR,0.99f);
                      close_DC_Motor(RIGHT_MOTOR);
											 close_DC_Motor(LEFT_MOTOR);
                      step2=OK;
                      PrintString1("step2 is ok\n");
                    }
                  else//如果未达到定时时间或定时器未启动
                    {

                      if(isStopped(Timer1)) //只有当定时器是停止状态时才启动定时器。
                        {
                          restartTimer(Timer1);

                        }
                    }
                  ////////////////////////////////////////////////////////////////

                }
            }
          else //如果步骤一没有完成
            {
              PID_setTargetParameter(PID_1,100); //设定稳定角度
              setTimeout(Timer1,5000); //设置定时器定时长度 ,5秒
              open_DC_Motor(LEFT_MOTOR);//电机开始工作
							open_DC_Motor(RIGHT_MOTOR);//电机开始工作
							openPID(PID_1);
              if(abs(PID_getErr(PID_1))<2.0f)//当误差小于2°时，认为达到稳定,定时器就开始计时
                {
                  //////////////////////定时器////////////////////////////////////////
                  if(isExpiredTimer(Timer1))   //如果达到定时时间
                    {
                      stopTimer(Timer1);//达到定时时间后关闭定时器
                      step1=OK; //步骤一完成 ，已经达到稳定状态，蜂鸣器响一下
                      PrintString1("step1 is ok\n");
                    }
                  else//如果未达到定时时间或定时器未启动
                    {

                      if(isStopped(Timer1)) //只有当定时器是停止状态时才启动定时器。
                        {
                          restartTimer(Timer1);

                        }
                    }
                  ////////////////////////////////////////////////////////////////
                }
            }

}

void mode2(void)
{
	
}


void mode3(void)
{
	
}

void mode4(void)
{
	
}
void modeLauncher(void)
{
	
}
