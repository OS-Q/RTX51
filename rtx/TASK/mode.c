#include "mode.h"
#include "../ALGORITHM/PID/PID.h"
#include "../../HARDWARE/DEVICES/MOTOR/DC_MOTOR/MOTOR.h"
#include "../../HARDWARE/BSP/timer.h"
#include "../../HARDWARE/BSP/USART1.h"
void mode1(void)
{
					static bit step1=0;//ģʽһ����1��־λ
          static bit step2=0; //����2 ��־λ
          static bit step3=0;  //��������־λ

          if(step1)//����һ�Ѿ����
            {

              if(step2) //�������2�����
                {
                  if(step3) //����������Ѿ����
                    {
                      //ģʽһ�Ѿ���� ����������ʼ��
                //      mode=0;//��ʼ��ģʽ
                      step1=0;
                      step2=0;
                      step3=0;

                    }
                  else//���������û�����
                    {
                      close_DC_Motor(LEFT_MOTOR);
									    close_DC_Motor(RIGHT_MOTOR);

                      step3=OK;
                      PrintString1("step3 is ok\n");

                    }

                }
              else //��������û�����
                {
                  setTimeout(Timer1,5000); //���ö�ʱ����ʱ���� ,5��
                  //////////////////////��ʱ��////////////////////////////////////////
                  if(isExpiredTimer(Timer1))   //����ﵽ��ʱʱ��
                    {

                      setDC_MotorSpeed(LEFT_MOTOR,0.01f);
                      setDC_MotorSpeed(RIGHT_MOTOR,0.99f);
                      close_DC_Motor(RIGHT_MOTOR);
											 close_DC_Motor(LEFT_MOTOR);
                      step2=OK;
                      PrintString1("step2 is ok\n");
                    }
                  else//���δ�ﵽ��ʱʱ���ʱ��δ����
                    {

                      if(isStopped(Timer1)) //ֻ�е���ʱ����ֹͣ״̬ʱ��������ʱ����
                        {
                          restartTimer(Timer1);

                        }
                    }
                  ////////////////////////////////////////////////////////////////

                }
            }
          else //�������һû�����
            {
              PID_setTargetParameter(PID_1,100); //�趨�ȶ��Ƕ�
              setTimeout(Timer1,5000); //���ö�ʱ����ʱ���� ,5��
              open_DC_Motor(LEFT_MOTOR);//�����ʼ����
							open_DC_Motor(RIGHT_MOTOR);//�����ʼ����
							openPID(PID_1);
              if(abs(PID_getErr(PID_1))<2.0f)//�����С��2��ʱ����Ϊ�ﵽ�ȶ�,��ʱ���Ϳ�ʼ��ʱ
                {
                  //////////////////////��ʱ��////////////////////////////////////////
                  if(isExpiredTimer(Timer1))   //����ﵽ��ʱʱ��
                    {
                      stopTimer(Timer1);//�ﵽ��ʱʱ���رն�ʱ��
                      step1=OK; //����һ��� ���Ѿ��ﵽ�ȶ�״̬����������һ��
                      PrintString1("step1 is ok\n");
                    }
                  else//���δ�ﵽ��ʱʱ���ʱ��δ����
                    {

                      if(isStopped(Timer1)) //ֻ�е���ʱ����ֹͣ״̬ʱ��������ʱ����
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
