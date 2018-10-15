#ifndef __LCD1602_H__
#define __LCD1602_H__

#include	"../../../BSP/config.h"
#include	"../../../BSP/delay.h"

//LCD1602 IO设置
#define LCD1602_PORT P4
sbit LCD1602_RS = P5^0;
sbit LCD1602_RW = P5^1;
sbit LCD1602_EN = P5^2;

sbit LCD1602_Backlight = P5^4;

//函数或者变量声明
extern void LCD1602_write_com(unsigned char com);
extern void LCD1602_write_char(unsigned char dat);
extern void LCD1602_write_word(unsigned char *s);
extern void LCD1602_Init();
extern void LCD1602_GPIO_config();


#endif