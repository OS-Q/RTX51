#ifndef _FIXEDPULSER_H_
#define _FIXEDPULSER_H_
#include "../BSP/config.h"
//如有需要可以更改发生器的名称
#define PULSER_1	0
#define PULSER_2	1
#define PULSER_3	2
#define PULSER_4	3
#define PULSER_5	4
#define PULSER_6	5


extern void PulserInit(void)                          ;
extern bool setPulse( u8 pulser_num,u16 Hz,u32 count) ;
extern bool openPulser(u8 pulser_num)                 ;
extern bool closePulser(u8 pulser_num)                ;
extern bool getPulserState(u8 pulser_num)             ;
#endif