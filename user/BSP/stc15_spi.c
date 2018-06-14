/************************************************************
* 组织名称： (C), 1988-1999, Tech. Co., Ltd.
* 文件名称: test.cpp
* 作者:
* 版本 :
* 日期:
* 描述: // 模块描述
* 主要函数及其功能 : // 主要函数及其功能
  1. -------
* 历史修改记录: // 历史修改记录
* <作者> <时间> <版本 > <描述>
* David 96/10/12 1.0 build this moudle
***********************************************************/
//------------------------------------------------
//头文件
#include "stc15_spi.h"
//------------------------------------------------------------------------
//注意:
//以下库函数都是建立在
//SPI_SSIG=DISABLE-->SPCTL的位4 MSTR 来确定主机还是从机
//SPI_Mode=SPI_Mode_Master主机
//的情况下的
//一般用mcu的SPI 就是主机模式 这个模式最常用
//虽然初始化的时候我可以设置成其它模式,但我的库函数只支持上面我说的设置
//------------------------------------------------
//预定义
#define SPI_BUF_LENTH   32
#define SPI_BUF_type    idata
//------------------------------------------------
//静态变量
static u8   SPI_TxWrite;
static u8   SPI_TxRead;
static u8   SPI_BUF_type SPI_TxBuffer[SPI_BUF_LENTH];
static u8   SPI_RxWrite;
static u8   SPI_RxRead;
static u8   SPI_BUF_type SPI_RxBuffer[SPI_BUF_LENTH];
//------------------------------------------------------------------------
//全局函数
//void  SPI_Init                        (SPI_InitTypeDef *SPIx);    //SPI初始化程序.
//void  SPI_SetMode                     (u8 mode);                  //SPI设置主从模式函数.
//void  SPI_WriteByteToTxBuf            (u8 dat);                   //SPI装载要发送的1个字节 但先不发送
//void  SPI_WriteNByteToTxBuf           (u8 *sp,u8 num);            //SPI装载要发送的N个字节 但先不发送
//void  SPI_TrigTx                      (void);                     //触发SPI发送函数, 将发送缓冲的数据发出
//u8    SPI_SPI_ReadByteToRxBuf         (void);                     //SPI从读缓冲区里读出1个字节
//u8    SPI_SPI_ReadTheNByteToRxBuf     (u8 num);                   //SPI从读缓冲区里读出第N个字节 之前的N-1个字节都丢弃
///////////////////////////////////////////////////////////////
//全局函数
/////////////////////////////////////////////////////////////////////
// 函数: void   SPI_Init(SPI_InitTypeDef *SPIx)
// 描述: SPI初始化程序.
// 参数: SPIx: 结构参数,请参考spi.h里的定义.
void    SPI_Init(SPI_InitTypeDef *SPIx)
{
    if(SPIx->SPI_SSIG == ENABLE)
    {
        SPCTL &= ~(1<<7);    //enable SS, conform Master or Slave by SS pin. 目前只支持DISABLE
    }
    else
    {
        SPCTL |=  (1<<7);    //disable SS, conform Master or Slave by SPI_Mode
    }
    if(SPIx->SPI_Module == ENABLE)
    {
        SPCTL |=  (1<<6);    //SPI enable
    }
    else
    {
        SPCTL &= ~(1<<6);    //SPI disable
    }
    if(SPIx->SPI_FirstBit == SPI_LSB)
    {
        SPCTL |=  (1<<5);    //LSB first
    }
    else
    {
        SPCTL &= ~(1<<5);    //MSB first
    }
    if(SPIx->SPI_Mode == SPI_Mode_Slave)
    {
        SPCTL &= ~(1<<4);    //slave  目前只支持SPI_Mode_Master
    }
    else
    {
        SPCTL |=  (1<<4);    //master
    }
    if(SPIx->SPI_CPOL == SPI_CPOL_High)
    {
        SPCTL |=  (1<<3);    //SCLK Idle High, Low Active.
    }
    else
    {
        SPCTL &= ~(1<<3);    //SCLK Idle Low, High Active.
    }
    if(SPIx->SPI_CPHA == SPI_CPHA_2Edge)
    {
        SPCTL |=  (1<<2);    //sample at the second edge
    }
    else
    {
        SPCTL &= ~(1<<2);    //sample at the first  edge
    }
    if(SPIx->SPI_Interrupt == ENABLE)
    {
        IE2 |=  (1<<1);    //目前只支持ENABLE
    }
    else
    {
        IE2 &= ~(1<<1);
    }
    SPCTL = (SPCTL & ~3) | (SPIx->SPI_Speed & 3);                   //set speed
    AUXR1 = (AUXR1 & ~(3<<2)) | SPIx->SPI_IoUse;
}
///////////////////////////////////////////////////////////////////////
// 函数: void   SPI_SetMode(u8 mode)
// 描述: SPI设置主从模式函数.
// 参数: mode: 指定模式,取值 SPI_Mode_Master 或 SPI_Mode_Slave
// 注意: 目前只支持SPI_Mode_Master
void    SPI_SetMode(u8 mode)
{
    if(mode == SPI_Mode_Slave)
    {
        SPCTL &= ~(1<<4);   //slave
    }
    else
    {
        SPCTL |=  (1<<4);   //master
    }
}
//////////////////////////////////////////////////////////////
// 函数: void SPI_WriteByteToTxBuf(u8 dat)
// 描述: SPI装载发要发送的1个字节 但先不发送
// 参数: dat: 要发送的值
void SPI_WriteByteToTxBuf(u8 dat)   //写入发送缓冲，指针+1
{
    SPI_TxBuffer[SPI_TxWrite] = dat;
    if(++SPI_TxWrite >= SPI_BUF_LENTH)
    {
        SPI_TxWrite = 0;
    }
}
//////////////////////////////////////////////////////////////
// 函数: void SPI_WriteNByteToTxBuf(u8 *sp,u8 num)
// 描述: SPI装载要发送的N个字节 但先不发送
// 参数: *sp: 指向要发送的N个字节的首地址
//       num: 要装载字节的数量  不要超过SPI_BUF_LENTH
// 注意: SPI_BUF_LENTH长度问题
void    SPI_WriteNByteToTxBuf(u8 *sp,u8 num)
{
    u8 i=num;
    u8 *spp=sp;
    if(num>SPI_BUF_LENTH)
    {
        ;
    }
    else
    {
        for(i=0; i<num; i++)
        {
            SPI_WriteByteToTxBuf(*spp);
            spp++;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////
// 函数: void   SPI_TrigTx(void)
// 描述: 触发SPI发送函数, 将发送缓冲的数据发出
void SPI_TrigTx(void)
{
    u8  i;
    if(SPI_TxRead == SPI_TxWrite)
    {
        ;
    }
    else
    {
        SPI_SetMode(SPI_Mode_Master);
        i = SPI_TxBuffer[SPI_TxRead];
        if(++SPI_TxRead >= SPI_BUF_LENTH)
        {
            SPI_TxRead = 0;
        }
        SPDAT = i;
    }
}
//////////////////////////////////////////////////////////////
// 函数: u8 SPI_SPI_ReadByteToRxBuf(void)
// 描述: SPI从读缓冲区里读出1个字节
// 返回参数:读出这个字节的值
// 注意: 程序员要保证缓冲区里确实至少有1个还没有读出的数据
u8 SPI_SPI_ReadByteToRxBuf(void)
{
    u8 dat;
    if(SPI_RxRead==SPI_RxWrite)
    {
        return 0;//返回的0 不是读出的值 而是缓冲区里没有要读出的数据
    }
    else
    {
        dat=SPI_RxBuffer[SPI_RxRead];
        if(++SPI_RxRead >= SPI_BUF_LENTH)
        {
            SPI_RxRead = 0;
        }
    }
    return dat;
}
//////////////////////////////////////////////////////////////
// 函数: u8 SPI_SPI_ReadByteToRxBuf(void)
// 描述: SPI从读缓冲区里读出第N个字节 之前的N-1个字节都丢弃
// 返回参数:读出这个字节的值
// 注意: 程序员要保证缓冲区里确实至少有N个还没有读出的数据
// 注意: SPI_BUF_LENTH长度问题
u8 SPI_SPI_ReadTheNByteToRxBuf(u8 num)
{
    u8 i=num;
    u8 dat;
    if(i>SPI_BUF_LENTH)
    {
        return 0;//返回的0 不是读出的值 而是形式参数不合法
    }
    else
    {
        while(i>1)
        {
            SPI_SPI_ReadByteToRxBuf();
            i--;
        }
        dat=SPI_SPI_ReadByteToRxBuf();
        return dat;
    }
}
////////////////////////////////////////////////////////////////////
// 函数: void SPI_Transivion (void) interrupt SPI_VECTOR
// 描述: SPI中断函数.
void SPI_Transivion (void) interrupt SPI_VECTOR
{
    if(SPI_TxRead != SPI_TxWrite)
    {
        //在写数据之前先读出SPDAT
        SPI_RxBuffer[SPI_RxWrite] = SPDAT ;
        if(++SPI_RxWrite >= SPI_BUF_LENTH)
        {
            SPI_RxWrite = 0;
        }
        SPDAT = SPI_TxBuffer[SPI_TxRead];
        if(++SPI_TxRead >= SPI_BUF_LENTH)
        {
            SPI_TxRead = 0;
        }
    }
    SPSTAT = SPIF + WCOL;   //清0 SPIF和WCOL标志
}
