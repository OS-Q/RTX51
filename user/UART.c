#include "UART.h"
#include "interrupt.h"
#include <STC15.H>
#include <intrins.h>
#include <stdio.h>
#include <string.h>
//串口1发送1个字节
void uart_send_byte(unsigned char uc_data) {
  ACC = uc_data;
  TB8 = P;
  SBUF = uc_data;
}
//串口2发送1个字节
void uart_send_byte_2(unsigned char uc_data) {
  /*
        ACC = uc_data;
        if (P) {
                S2CON |= 0x08;
        } else {
                S2CON &= 0xF7;
        }
  */
  S2BUF = uc_data;
}
//串口1发送1个字符串
void uart_send_str(char *p_str) {
  if (*p_str != '\0' &&
      send_data_end_flag ==
          UART_STATUS_READY) //判断为空数组以及上一个数组是否发送完毕
  {
    send_data_end_flag = UART_STATUS_BUSY;
    send_str = p_str;
    uart_send_byte(*send_str++); //数组第一个字符
  }
}
//串口2发送指定长度字符串
void uart_send_str_2(unsigned char *p_str, unsigned short str_size) {
  if (send_data_end_flag_2 == UART_STATUS_READY) {
    send_data_size_2 = str_size;
    send_str_2 = p_str;
    uart_send_byte_2(*(send_str_2 + send_data_end_flag_2++)); //数组第一个字符
  }
}
//发送回传信息函数
void send_feedfack_information(unsigned char message_flag) {
  char i, j;
  char temp_data[64];
  short feedback_data;
  feedfack_information[0] = '\0';
  for (j = 0; j < 12; j++) {
    if (0 == j && message_flag == 1) {
      for (i = 1; i <= 16; i++) {
        sprintf(temp_data, send_key_words_data[j], (short)i,
                (short)master_to_slave[light_group_true + i]);
        strcat(feedfack_information, temp_data);
      }
    } else {
      switch (j) {
      case 1: {
        feedback_data = (short)spark_cycle;
        break;
      }
      case 2: {
        feedback_data = (short)spark_PWM;
        break;
      }
      case 3: {
        feedback_data = (short)gradient_cycle;
        break;
      }
      case 4: {
        feedback_data = (short)auto_sleep;
        break;
      }
      case 5: {
        feedback_data = (short)auto_start;
        break;
      }
      case 6: {
        feedback_data = (short)auto_stop;
        break;
      }
      case 7: {
        feedback_data = (short)auto_turn;
        break;
      }
      case 8: {
        feedback_data = (short)auto_status;
        break;
      }
      case 9: {
        feedback_data = (short)light_group;
        break;
      }
      case 10: {
        feedback_data = (short)light_all_mute;
        break;
      }
      case 11: {
        feedback_data = (short)iap_address_num;
        break;
      }
      default: { break; }
      }
      sprintf(temp_data, send_key_words_data[j], feedback_data);
      strcat(feedfack_information, temp_data);
    }
  }
  uart_send_str(feedfack_information);
}