/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : stc15_spi.H
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 *
 * 版本代号 : V1.0
 * 修改日期 : 2015-08-29
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
              为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
              视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐
 * Copyright (C), 2013-2015, 刘平（xymbmcu@163.com）/清华大学出版社/STC MCU International Limited
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */
#ifndef __STC15_SPI_H__
#define __STC15_SPI_H__
#include    "config.h"
#define SPI_Mode_Master     1
#define SPI_Mode_Slave      0
#define SPI_CPOL_High       1
#define SPI_CPOL_Low        0
#define SPI_CPHA_1Edge      1
#define SPI_CPHA_2Edge      0
#define SPI_Speed_4         0
#define SPI_Speed_16        1
#define SPI_Speed_64        2
#define SPI_Speed_128       3
#define SPI_MSB             0
#define SPI_LSB             1
#define SPI_P12_P13_P14_P15 (0<<2)
#define SPI_P24_P23_P22_P21 (1<<2)
#define SPI_P54_P40_P41_P43 (2<<2)
typedef struct
{
    u8  SPI_Module;     //ENABLE,DISABLE 使能或者禁止SPI
    u8  SPI_SSIG;       //ENABLE-->主机还是从机由/SS管脚决定,
    //DISABLE-->SPCTL的位4 MSTR 来确定主机还是从机
    u8  SPI_FirstBit;   //SPI_MSB 数据的最高位最先发送
    //SPI_LSB数据的最低位最先发送
    u8  SPI_Mode;       //SPI_Mode_Master主机
    //SPI_Mode_Slave从机
    u8  SPI_CPOL;       //时钟极性
    //SPI_CPOL_High空闲时SCL为高电平 SCL的前时钟沿为下降沿 后时钟沿为上升沿,
    //SPI_CPOL_Low空闲时SCL为低电平 SCL的前时钟沿为上升沿 后时钟沿为下降沿
    u8  SPI_CPHA;       //时钟相位
    //SPI_CPHA_1Edge 仅在/SS=0并且SPI_SSIG=ENABLE时 数据在SCL前时钟沿采样 后时钟沿驱动 当SPI_SSIG=DISABLE时未定义
    //SPI_CPHA_2Edge 数据在SCL前时钟沿驱动 后时钟沿采样
    u8  SPI_Interrupt;  //ENABLE,DISABLE  中断使能/禁止
    u8  SPI_Speed;      //SPI_Speed_4,SPI_Speed_16,SPI_Speed_64,SPI_Speed_128 SPI速率分别是CPU时钟的4 16 64 128分频
    u8  SPI_IoUse;      //SPI管脚切换管理
    //SPI_P12_P13_P14_P15
    //SPI_P24_P23_P22_P21
    //SPI_P54_P40_P41_P43
} SPI_InitTypeDef;
extern void SPI_Init                        (SPI_InitTypeDef *SPIx);
extern void SPI_SetMode                     (u8 mode);
extern void SPI_WriteByteToTxBuf            (u8 dat);
extern void SPI_WriteNByteToTxBuf           (u8 *sp,u8 num);
extern u8   SPI_SPI_ReadByteToRxBuf         (void);
extern u8   SPI_SPI_ReadTheNByteToRxBuf     (u8 num);
extern void SPI_TrigTx                      (void);
#endif
