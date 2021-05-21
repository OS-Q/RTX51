/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : stc15_spi.H
 * Ӳ��ƽ̨ ���w����̖ FSST15ʵ���
 * ������� ��Keil uVision5.13
 *
 * �汾���� : V1.0
 * �޸����� : 2015-08-29
 * ������̳ �����ӹ���ʦ���أ�http://www.ieebase.net��
 * �Ա����� ��http://fsmcu.taobao.com
 * ����˵�� ��������Ϊ�̲ġ���STC15��Ƭ��ǣ�ֵ���Щ�꡷���廪��ѧ�����磩��������
              Ϊ��Ƶ������ǳ����תSTC15��Ƭ�����������̣�¼��100��--�������޹���
              ��Ƶ���鼮����STC�����ں꾧�Ƽ����ٷ���ѧ�ƻ��͸�У����������ʵ����Ȩ���Ƽ�
 * Copyright (C), 2013-2015, ��ƽ��xymbmcu@163.com��/�廪��ѧ������/STC MCU International Limited
 * ����ѧϰʹ�ã�δ��������ɣ���������������ҵ��;������ؾ���
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
    u8  SPI_Module;     //ENABLE,DISABLE ʹ�ܻ��߽�ֹSPI
    u8  SPI_SSIG;       //ENABLE-->�������Ǵӻ���/SS�ܽž���,
    //DISABLE-->SPCTL��λ4 MSTR ��ȷ���������Ǵӻ�
    u8  SPI_FirstBit;   //SPI_MSB ���ݵ����λ���ȷ���
    //SPI_LSB���ݵ����λ���ȷ���
    u8  SPI_Mode;       //SPI_Mode_Master����
    //SPI_Mode_Slave�ӻ�
    u8  SPI_CPOL;       //ʱ�Ӽ���
    //SPI_CPOL_High����ʱSCLΪ�ߵ�ƽ SCL��ǰʱ����Ϊ�½��� ��ʱ����Ϊ������,
    //SPI_CPOL_Low����ʱSCLΪ�͵�ƽ SCL��ǰʱ����Ϊ������ ��ʱ����Ϊ�½���
    u8  SPI_CPHA;       //ʱ����λ
    //SPI_CPHA_1Edge ����/SS=0����SPI_SSIG=ENABLEʱ ������SCLǰʱ���ز��� ��ʱ�������� ��SPI_SSIG=DISABLEʱδ����
    //SPI_CPHA_2Edge ������SCLǰʱ�������� ��ʱ���ز���
    u8  SPI_Interrupt;  //ENABLE,DISABLE  �ж�ʹ��/��ֹ
    u8  SPI_Speed;      //SPI_Speed_4,SPI_Speed_16,SPI_Speed_64,SPI_Speed_128 SPI���ʷֱ���CPUʱ�ӵ�4 16 64 128��Ƶ
    u8  SPI_IoUse;      //SPI�ܽ��л�����
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
