#include "DMX512.h"
#include "Delay.h"
#include "EEPROM.H"
#include "UART.h"
#include "interrupt.h"
#include <STC15.H>
#include <rtx51tny.h>
// Break信号
void Break(void) {
  P11 = 0;
  Delay88us();
}
// MAB信号
void MAB(void) {
  P11 = 1;
  Delay8us();
}
// MTBP信号
void MTBP(void) {
  P11 = 1;
  Delay88us();
  Delay88us();
}
//发送1个数据包
void send_signal(unsigned char *p_str) {
  Break();
  MAB();
  IE2 |= 0x01; //允许串口2中断	// ES2 = 1;
  uart_send_str_2(p_str, 257);
  while (send_data_end_flag_2 != UART_STATUS_READY)
    ;
  IE2 &= 0xFE; //禁止串口2中断	// ES2 = 0;
  MTBP();
}
void Load_data_quick(void) {
  unsigned short i;
  IE2 &= 0xDF; //关闭定时器3中断
  IE2 &= 0xBF; //关闭定时器4中断
  read_EEPROM(IAP_ADDRESS[iap_address_num], DMX512_256__SIZE + 1, 1,
              &spark_cycle);
  read_EEPROM(IAP_ADDRESS[iap_address_num], DMX512_256__SIZE + 2, 1,
              &spark_PWM);
  if (gradient_cycle == GRADIENT_CYCLE_MIN) //判断是否启用渐变
  {
    //不启用渐变情况时直接读取到当前状态数组
    read_EEPROM(IAP_ADDRESS[iap_address_num], 0, DMX512_256__SIZE + 1,
                master_to_slave);
    //不启动渐变时判断是否开启轮询，需要启动定时器4
    if (auto_status == AUTO_STATUS_ON) {
      timer_4_count = 0;
      IE2 |= 0x40;
    }
  } else {
    //启用渐变情况时读取到临时数组中
    read_EEPROM(IAP_ADDRESS[iap_address_num], 0, DMX512_256__SIZE + 1,
                new_master_to_slave);
    for (i = 0; i < DMX512_256__SIZE + 1; i++) {
      old_master_to_slave[i] = master_to_slave[i];
    }
    for (i = 0; i < DMX512_256__SIZE + 1; i++) {
      gradient_master_to_slave[i] =
          ((float)new_master_to_slave[i] - (float)master_to_slave[i]) /
          GRADIENT_RESOLUTION;
    }
    //循环计数初始化
    timer_3_count = 1;
    IE2 |= 0x20; //开启定时器3中断
  }
  if (spark_cycle == SPARK_CYCLE_MIN) {
    os_delete_task(4);
    send_data_DMX512 = master_to_slave;
  } else {
    spark_cycle_true = (unsigned short)spark_cycle * SPARK_PWM_RESOLUTION;
    spark_PWM_true = (unsigned short)spark_PWM * (unsigned short)spark_cycle;
    os_create_task(4);
  }
}