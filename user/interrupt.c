#include "UART.h"
#include "interrupt.h"
#include <STC15.H>
#include <rtx51tny.h>
#include <stdio.h>
#include <string.h>
unsigned int code IAP_ADDRESS[] = {
    0x0000, 0x0200, 0x0400, 0x0600, 0x0800, 0x0A00, 0x0C00, 0x0E00, 0x1000,
    0x1200, 0x1400, 0x1600, 0x1800, 0x1A00, 0x1C00, 0x1E00, 0x2000, 0x2200,
    0x2400, 0x2600, 0x2800, 0x2A00, 0x2C00, 0x2E00, 0x3000, 0x3200, 0x3400,
    0x3600, 0x3800, 0x3A00, 0x3C00, 0x3E00, 0x4000, 0x4200, 0x4400, 0x4600,
    0x4800, 0x4A00, 0x4C00, 0x4E00, 0x5000, 0x5200, 0x5400, 0x5600, 0x5800,
    0x5A00, 0x5C00, 0x5E00, 0x6000, 0x6200, 0x6400, 0x6600}; // EEPROM扇区地址
unsigned char iap_address_num = IAP_ADDRESS_NUM_Min; // EEPROM扇区序号 0~51
unsigned char iap_address_num_old;
char feedfack_information[256]; //反馈信息数组
char *send_str;                 //串口1用于发送信息的数组指针
unsigned char send_data_end_flag = UART_STATUS_READY; //串口1发送信息结束标志
unsigned char code master_to_slave_off[DMX512_256__SIZE + 1] = {
    SC};                                             //频闪时全0信息数组
unsigned char master_to_slave[DMX512_256__SIZE + 1]; // DMX512控制信号
unsigned char *send_data_DMX512 =
    master_to_slave; //串口2用于发送信息的无符号字符指针
unsigned short send_data_size_2; //串口2发送字符串长度
unsigned char *send_str_2;       //串口2用于发送信息的数组指针
unsigned short send_data_end_flag_2 =
    UART_STATUS_READY; //串口2发送信息结束标志以及数组指针偏移量
unsigned char light_group = LIGHT_NUM_MIN;   // DMX512通道翻页选择	0~15
unsigned short light_group_true = 0;         //灯组计算中间信息
unsigned short current_light_num;            //当前控制通道
unsigned char spark_cycle = SPARK_CYCLE_MIN; //频闪周期
unsigned short spark_cycle_true;             //频闪周期实际值
unsigned char spark_PWM = SPARK_PWM_MAX / 2; //频闪占空比 0~10
unsigned short spark_PWM_true;               //频闪占空比实际值
unsigned char gradient_cycle = GRADIENT_CYCLE_MIN;    //渐变周期
unsigned short gradient_cycle_true;                   //渐变周期实际值
float gradient_master_to_slave[DMX512_256__SIZE + 1]; //渐变累加单元数组
unsigned char
    new_master_to_slave[DMX512_256__SIZE + 1]; //读取更新数据时新数据储存数组
unsigned char
    old_master_to_slave[DMX512_256__SIZE + 1]; //读取更新数据时旧数据储存数组
unsigned short timer_0_count = 1;              //定时器3延时循环计数
unsigned short timer_3_count = 1;              //定时器3延时循环计数
unsigned short timer_4_count = 0;              //定时器4延时循环计数
unsigned char light_all_mute = MUTE_OFF;        //灯组静音标志
char g_command[32];                             //全局命令字符串
char b_command[32];                             //缓冲命令字符串
short b_command_data, b_command_data_2;         //全局命令数据
unsigned char b_command_count;                  //缓冲字符串下标位置
unsigned char auto_status = AUTO_STATUS_OFF;    //轮询状态标志位
unsigned char auto_start = IAP_ADDRESS_NUM_Min; //轮询起始位
unsigned char auto_stop = IAP_ADDRESS_NUM_Min;  //轮询停止位
unsigned char auto_sleep = AUTO_SLEEP_MIN;      //轮询状态保持时长
unsigned short auto_sleep_true;                 //轮询状态真实保持时长
unsigned char auto_turn = AUTO_TURN_RIGHT;      //轮询方向
unsigned char rdata_complete_flag;  //字符串接收完成处理标志位
unsigned char spark_change_flag;    //频闪状态翻转标志位
unsigned char run_change_flag;      //走马灯切换EEPROM标志位
unsigned char gradient_change_flag; //渐变数据总偏移量标志位
char *p_b_buffer;                   //字符串中关键字指针
char code *receive_keywords[] = {"FDS",    "FDN",  "SLTS", "SLTN", "SLPWMS",
                                 "SLPWMN", "GCTS", "GCTN", "WTS",  "WTN",
                                 "SF",     "EUW",  "RD",   "RUN",  "LG",
                                 "MUTE",   "LOAD", "SAVE", "QUICK"};
char code *receive_keywords_data[] = {
    "FDS%03hd=%03hd", "FDN%03hd=%03hd", "SLTS=%03d",  "SLTN=%03d",
    "SLPWMS=%03hd",   "SLPWMN=%03hd",   "GCTS=%03hd", "GCTN=%03hd",
    "WTS=%03hd",      "WTN=%03hd",      "SF=%03hd",   "EUW=%03hd",
    "RD=%03hd",       "RUN=%03hd",      "LG=%03hd",   "MUTE=%03hd",
    "LOAD=%03hd",     "SAVE=%03hd",     "QUICK=%03hd"};
char code *send_keywords[] = {"FDN",  "SLTN", "SLPWMN", "GCTN", "WTN",
                              "SF",   "EUW",  "RD",     "RUN",  "LG",
                              "MUTE", "EN",   "LOAD",   "SAVE"};
char code *send_key_words_data[] = {
    "FDN%03hd=%03hd", "SLTN=%03hd",   "SLPWMN=%03hd", "GCTN=%03hd", "WTN=%03hd",
    "SF=%03hd",       "EUW=%03hd",    "RD=%03hd",     "RUN=%03hd",  "LG=%03hd",
    "MUTE=%03hd",     "EN=%03hd\r\n", "LOAD=%03hd",   "SAVE=%03hd",
};
//定时器0中断处理程序
// void timer_0(void) interrupt 1 {
//  if (spark_PWM == SPARK_PWM_MAX) {
//    send_data_DMX512 = master_to_slave;
//  } else if (spark_PWM == SPARK_PWM_MIN) {
//    send_data_DMX512 = master_to_slave_off;
//  } else {
//    if (timer_0_count < spark_PWM_true) {
//      timer_0_count++;
//      send_data_DMX512 = master_to_slave;
//    } else if (timer_0_count < spark_cycle_true) {
//      timer_0_count++;
//      send_data_DMX512 = master_to_slave_off;
//    } else {
//      timer_0_count = 1;
//      send_data_DMX512 = master_to_slave;
//    }
//  }
//}
//串口1中断处理程序
void uart_1(void) interrupt 4 {
  char r_data;
  if (TI == 1) {
    TI = 0;
    if (*send_str != '\0') //判断是否到达数组结束
    {
      uart_send_byte(*send_str++); //继续发送数组
    } else {
      send_data_end_flag = UART_STATUS_READY;
    }
  } else if (RI == 1) {
    RI = 0;
    ACC = SBUF;
    if (RB8 == P) {
      r_data = SBUF;
    } else {
      // goto ERROR;
    }
    b_command[b_command_count++] = r_data; //将接收到的字符装入到字符串
    if (b_command_count > 31) {
      b_command_count = 0;
    }
    if (r_data == 0x0A) {
      b_command[b_command_count] = '\0';
      b_command_count = 0;
      strcpy(g_command, b_command); //将缓冲数组装入到全局命令数组
      rdata_complete_flag = 1;
      isr_send_signal(1);
    }
  }
}
//串口2中断处理程序
void uart_2(void) interrupt 8 {
  char r_data;
  // if (S2TI == 1)
  if ((bit)((S2CON & 0x02) >> 1) == 1) {
    // S2TI = 0;
    S2CON &= 0xFD;
    if (send_data_end_flag_2 < send_data_size_2) {
      uart_send_byte_2(*(send_str_2 + send_data_end_flag_2++));
    } else {
      send_data_end_flag_2 = UART_STATUS_READY;
    }
  }
  // else if (S2RI == 1)
  else if ((bit)(S2CON & 0x01) == 1) {
    // S2RI == 0;
    S2CON &= 0xFE;
    ACC = S2BUF;
    if (P == (bit)(S2CON & 0x04 >> 2)) {
      r_data = S2BUF;
    } else {
    }
  }
}
//定时器3中断处理
void timer_3(void) interrupt 19 {
  unsigned short i = 0;
  if (timer_3_count <= gradient_cycle_true) {
    timer_3_count++;
    if ((timer_3_count % gradient_cycle) == 0) {
      for (i = 0; i < DMX512_256__SIZE + 1; i++) {
        master_to_slave[i] =
            (unsigned char)((float)old_master_to_slave[i] +
                            gradient_master_to_slave[i] *
                                (timer_3_count / gradient_cycle));
      }
    }
  } else {
    timer_3_count = 1;
    for (i = 0; i < DMX512_256__SIZE + 1; i++) {
      master_to_slave[i] = new_master_to_slave[i];
    }
    //如果启用轮询，开启定时器4中断
    if (auto_status == AUTO_STATUS_ON) {
      timer_4_count = 0;
      IE2 |= 0x40;
    }
    IE2 &= 0xDF; //关闭定时器3中断
  }
}
//定时器4中断处理
void timer_4(void) interrupt 20 {
  if (timer_4_count < auto_sleep_true) {
    timer_4_count++;
  } else {
    run_change_flag = 1;
    isr_send_signal(3);
    timer_4_count = 0;
    //如果状态轮询到中止位，装入初始值
    if (iap_address_num == auto_stop) {
      iap_address_num = auto_start;
    } else {
      //根据轮询方向对EPROM序号++或--
      if (auto_turn == AUTO_TURN_LEFT) {
        if (iap_address_num > IAP_ADDRESS_NUM_Min) {
          iap_address_num--;
        } else {
          iap_address_num = IAP_ADDRESS_NUM_Max;
        }
      } else if (auto_turn == AUTO_TURN_RIGHT) {
        if (iap_address_num < IAP_ADDRESS_NUM_Max) {
          iap_address_num++;
        } else {
          iap_address_num = IAP_ADDRESS_NUM_Min;
        }
      }
    }
    IE2 &= 0xBF; //关闭定时器4中断
  }
}