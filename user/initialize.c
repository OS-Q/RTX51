#include "initialize.h"
#include <STC15.H>
void uart_init_1(void) // 115200bps@24.000MHz
{
  SCON = 0xD0;  // 9位数据,可变波特率
  AUXR |= 0x40; //定时器1时钟为Fosc,即1T
  AUXR &= 0xFE; //串口1选择定时器1为波特率发生器
  TMOD &= 0x0F; //设定定时器1为16位自动重装方式
  TL1 = 0xCC;   //设定定时初值
  TH1 = 0xFF;   //设定定时初值
  ET1 = 0;      //禁止定时器1中断
  TR1 = 1;      //启动定时器1
}
void uart_init_2(void) // 250000bps@24.000MHz
{
  S2CON |= 0xD0; // 9位数据,可变波特率
  AUXR |= 0x04;  //定时器2时钟为Fosc,即1T
  T2L = 0xE8;    //设定定时初值
  T2H = 0xFF;    //设定定时初值
  AUXR |= 0x10;  //启动定时器2
}
void timer3_init(void) // 3毫秒@24.000MHz
{
  T4T3M &= 0xFD; //定时器时钟12T模式
  T3L = 0x90;    //设置定时初值
  T3H = 0xE8;    //设置定时初值
  T4T3M |= 0x08; //定时器3开始计时
}
void timer4_init(void) // 2毫秒@24.000MHz
{
  T4T3M |= 0x20; //定时器时钟1T模式
  T4L = 0x80;    //设置定时初值
  T4H = 0x44;    //设置定时初值
  T4T3M |= 0x80; //定时器4开始计时
}
