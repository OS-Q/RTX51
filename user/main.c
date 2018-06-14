#include "DMX512.h"
#include "EEPROM.H"
#include "UART.H"
#include "initialize.h"
#include "interrupt.h"
#include <STC15.H>
#include <rtx51tny.h>
#include <stdio.h>
#include <string.h>
sbit SN75176_DE = P1 ^ 2;
void startup_task() _task_ 0 {
  unsigned short i = 0;
  SP = 0x80;         //设置栈顶在80H位置
  ES = 1;            //允许串口1中断
  PS = 1;            //串口1中断最高优先级
  IP2 |= 0x01;       //串口2最高中断优先级	// PS2 = 1;
  IAP_CONTR |= 0x01; //设定EEPROM操作时CPU等待时间为时钟不小于24MHz时
  S2CON |= 0x08; // S2TB8 = 1;
  SN75176_DE = 1;
  uart_init_1();
  uart_init_2();
  timer3_init();
  timer4_init();
  for (i = 0; i < DMX512_256__SIZE + 1; i++) {
    master_to_slave[i] = 0;
  }
  os_create_task(1);
  os_create_task(2);
  os_create_task(3);
  os_delete_task(0);
}
void process_serial_cmds() _task_ 1 {
  unsigned char i = 0;
  while (1) {
    os_wait(K_SIG, 0, 0);
    if (1 == rdata_complete_flag) {
      rdata_complete_flag = 0;
      for (i = 0; i < 19; i++) {
        if ((p_b_buffer = strstr(g_command, receive_keywords[i])) != NULL) {
          if (1 >= i) {
            sscanf(p_b_buffer, receive_keywords_data[i], &b_command_data,
                   &b_command_data_2);
          } else {
            sscanf(p_b_buffer, receive_keywords_data[i], &b_command_data);
          }
          switch (i) {
          case 0:
          case 1: {
            current_light_num = b_command_data + light_group_true;
            master_to_slave[current_light_num] =
                (unsigned char)b_command_data_2;
            if (1 == i) {
              uart_send_str(g_command);
            }
            break;
          }
          case 2:
          case 3: {
            spark_cycle = (unsigned char)b_command_data;
            //判断是否需要计算真实频闪周期以及频闪占空比以及是否需要开启定时器0中断
            if (spark_cycle == SPARK_CYCLE_MIN) {
              os_delete_task(4);
              send_data_DMX512 = master_to_slave;
            } else {
              spark_cycle_true =
                  (unsigned short)spark_cycle * SPARK_PWM_RESOLUTION;
              spark_PWM_true =
                  (unsigned short)spark_cycle * (unsigned short)spark_PWM;
              os_create_task(4);
            }
            if (3 == i) {
              uart_send_str(g_command);
            }
            break;
          }
          case 4:
          case 5: {
            spark_PWM = (unsigned char)b_command_data;
            spark_PWM_true = (unsigned short)spark_PWM *
                             (unsigned short)spark_cycle; //计算真实占空比信息
            if (5 == i) {
              uart_send_str(g_command);
            }
            break;
          }
          case 6:
          case 7: {
            gradient_cycle = (unsigned char)b_command_data; //获取渐变周期信息
            gradient_cycle_true = (unsigned short)gradient_cycle *
                                  GRADIENT_RESOLUTION; //计算真实渐变信息
            if (7 == i) {
              uart_send_str(g_command);
            }
            break;
          }
          case 8:
          case 9: {
            auto_sleep = (unsigned char)b_command_data; //得到自动轮询停留时长
            auto_sleep_true = (unsigned short)auto_sleep *
                              AUTO_SLEEP_RESOLUTION; //计算真实停留时长
            if (9 == i) {
              uart_send_str(g_command);
            }
            break;
          }
          case 10: {
            auto_start = (unsigned char)b_command_data; //获取轮询开始位
            uart_send_str(g_command);
            break;
          }
          case 11: {
            auto_stop = (unsigned char)b_command_data; //获取轮询停止位
            uart_send_str(g_command);
            break;
          }
          case 12: {
            auto_turn = (unsigned char)b_command_data; //得到自动轮询方向信息
            uart_send_str(g_command);
            break;
          }
          case 13: {
            auto_status = (unsigned char)b_command_data; //获取轮询状态位
            if (auto_status == AUTO_STATUS_ON) {
              iap_address_num_old = iap_address_num;
              iap_address_num = auto_start;
              Load_data_quick();
              uart_send_str(g_command);
            } else if (auto_status == AUTO_STATUS_OFF) {
              iap_address_num = iap_address_num_old; //恢复原状态
              Load_data_quick();
              send_feedfack_information(0); //返回状态信息
            }
            break;
          }
          case 14: {
            light_group = (unsigned char)b_command_data; //获取灯组信息
            light_group_true = (short)(light_group << 4);
            send_feedfack_information(1); //返回状态信息
            break;
          }
          case 15: {
            light_all_mute = (unsigned char)b_command_data; //得到静音信息
            uart_send_str(g_command);
            break;
          }
          case 16: {
            iap_address_num = (unsigned char)b_command_data; //获取EPROM序号
            auto_status = AUTO_STATUS_OFF;
            Load_data_quick();            //载入指定需要EPROM
            send_feedfack_information(1); //返回状态信息
            break;
          }
          case 17: {
            iap_address_num = (unsigned char)b_command_data; //获取EPROM序号
            //保存状态到指定序号
            write_EEPROM(IAP_ADDRESS[iap_address_num], 0, DMX512_256__SIZE + 1,
                         master_to_slave);
            write_EEPROM(IAP_ADDRESS[iap_address_num], DMX512_256__SIZE + 1, 1,
                         &spark_cycle);
            write_EEPROM(IAP_ADDRESS[iap_address_num], DMX512_256__SIZE + 2, 1,
                         &spark_PWM);
            uart_send_str(g_command);
            break;
          }
          case 18: {
            iap_address_num = (unsigned char)b_command_data; //获取EPROM序号
            auto_status = AUTO_STATUS_OFF;
            Load_data_quick();            //载入指定需要EPROM
            send_feedfack_information(0); //返回部分状态信息
            break;
          }
          default: { break; }
          }
          break;
        }
      }
    }
    os_switch_task();
  }
}
void send_DMX512_signal() _task_ 2 {
  while (1) {
    //判断静音状态并指定输出DMX信号数组
    if (light_all_mute == MUTE_ON) {
      send_signal(master_to_slave_off);
    } else if (light_all_mute == MUTE_OFF) {
      send_signal(send_data_DMX512);
    }
    os_switch_task();
  }
}
void horse_race_lamp() _task_ 3 {
  while (1) {
    os_wait(K_SIG, 0, 0);
    if (1 == run_change_flag) {
      run_change_flag = 0;
      Load_data_quick();
      sprintf(feedfack_information, "EN=%03hd\r\n", (short)iap_address_num);
      uart_send_str(feedfack_information); //返回切换到的EPROM序号
    }
    os_switch_task();
  }
}
void process_spark() _task_ 4 {
  while (1) {
		os_wait(K_TMO, 2, 0);
    if (spark_PWM == SPARK_PWM_MAX) {
      send_data_DMX512 = master_to_slave;
    } else if (spark_PWM == SPARK_PWM_MIN) {
      send_data_DMX512 = master_to_slave_off;
    } else {
      if (timer_0_count < spark_PWM) {
        timer_0_count++;
        send_data_DMX512 = master_to_slave;
      } else if (timer_0_count < spark_cycle) {
        timer_0_count++;
        send_data_DMX512 = master_to_slave_off;
      } else {
        timer_0_count = 1;
        send_data_DMX512 = master_to_slave;
      }
    }
    os_switch_task();
  }
}