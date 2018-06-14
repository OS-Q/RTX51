#include "task.h"
#include "../../HARDWARE/DEVICES/MOTOR/DC_MOTOR/MOTOR.h"

 bit setBoardWithAngle(float angle)
{

  if(angle>=179.9f)
    {
      angle=179.9f;
#ifdef MOTOR_DEBUG
      PrintString1("angle is over maximum adjusting\n");
#endif
    }
  if(angle<=0.1f)
    {
      angle=0.1f;
#ifdef MOTOR_DEBUG
      PrintString1("angle is over miximum adjusting\n");
#endif
    }
  setDC_MotorSpeed(LEFT_MOTOR,angle/180.0f);
  setDC_MotorSpeed(RIGHT_MOTOR,1.0f-angle/180.0f);
  return 1;
}

