/************************************************************
* ��֯���ƣ� (C), 1988-1999, Tech. Co., Ltd.
* �ļ�����: test.cpp
* ����:
* �汾 :
* ����:
* ����: // ģ������
* ��Ҫ�������书�� : // ��Ҫ�������书��
  1. -------
* ��ʷ�޸ļ�¼: // ��ʷ�޸ļ�¼
* <����> <ʱ��> <�汾 > <����>
* David 96/10/12 1.0 build this moudle
***********************************************************/
//------------------------------------------------
//ͷ�ļ�
#include "stc15_spi.h"
//------------------------------------------------------------------------
//ע��:
//���¿⺯�����ǽ�����
//SPI_SSIG=DISABLE-->SPCTL��λ4 MSTR ��ȷ���������Ǵӻ�
//SPI_Mode=SPI_Mode_Master����
//������µ�
//һ����mcu��SPI ��������ģʽ ���ģʽ���
//��Ȼ��ʼ����ʱ���ҿ������ó�����ģʽ,���ҵĿ⺯��ֻ֧��������˵������
//------------------------------------------------
//Ԥ����
#define SPI_BUF_LENTH   32
#define SPI_BUF_type    idata
//------------------------------------------------
//��̬����
static u8   SPI_TxWrite;
static u8   SPI_TxRead;
static u8   SPI_BUF_type SPI_TxBuffer[SPI_BUF_LENTH];
static u8   SPI_RxWrite;
static u8   SPI_RxRead;
static u8   SPI_BUF_type SPI_RxBuffer[SPI_BUF_LENTH];
//------------------------------------------------------------------------
//ȫ�ֺ���
//void  SPI_Init                        (SPI_InitTypeDef *SPIx);    //SPI��ʼ������.
//void  SPI_SetMode                     (u8 mode);                  //SPI��������ģʽ����.
//void  SPI_WriteByteToTxBuf            (u8 dat);                   //SPIװ��Ҫ���͵�1���ֽ� ���Ȳ�����
//void  SPI_WriteNByteToTxBuf           (u8 *sp,u8 num);            //SPIװ��Ҫ���͵�N���ֽ� ���Ȳ�����
//void  SPI_TrigTx                      (void);                     //����SPI���ͺ���, �����ͻ�������ݷ���
//u8    SPI_SPI_ReadByteToRxBuf         (void);                     //SPI�Ӷ������������1���ֽ�
//u8    SPI_SPI_ReadTheNByteToRxBuf     (u8 num);                   //SPI�Ӷ��������������N���ֽ� ֮ǰ��N-1���ֽڶ�����
///////////////////////////////////////////////////////////////
//ȫ�ֺ���
/////////////////////////////////////////////////////////////////////
// ����: void   SPI_Init(SPI_InitTypeDef *SPIx)
// ����: SPI��ʼ������.
// ����: SPIx: �ṹ����,��ο�spi.h��Ķ���.
void    SPI_Init(SPI_InitTypeDef *SPIx)
{
    if(SPIx->SPI_SSIG == ENABLE)
    {
        SPCTL &= ~(1<<7);    //enable SS, conform Master or Slave by SS pin. Ŀǰֻ֧��DISABLE
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
        SPCTL &= ~(1<<4);    //slave  Ŀǰֻ֧��SPI_Mode_Master
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
        IE2 |=  (1<<1);    //Ŀǰֻ֧��ENABLE
    }
    else
    {
        IE2 &= ~(1<<1);
    }
    SPCTL = (SPCTL & ~3) | (SPIx->SPI_Speed & 3);                   //set speed
    AUXR1 = (AUXR1 & ~(3<<2)) | SPIx->SPI_IoUse;
}
///////////////////////////////////////////////////////////////////////
// ����: void   SPI_SetMode(u8 mode)
// ����: SPI��������ģʽ����.
// ����: mode: ָ��ģʽ,ȡֵ SPI_Mode_Master �� SPI_Mode_Slave
// ע��: Ŀǰֻ֧��SPI_Mode_Master
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
// ����: void SPI_WriteByteToTxBuf(u8 dat)
// ����: SPIװ�ط�Ҫ���͵�1���ֽ� ���Ȳ�����
// ����: dat: Ҫ���͵�ֵ
void SPI_WriteByteToTxBuf(u8 dat)   //д�뷢�ͻ��壬ָ��+1
{
    SPI_TxBuffer[SPI_TxWrite] = dat;
    if(++SPI_TxWrite >= SPI_BUF_LENTH)
    {
        SPI_TxWrite = 0;
    }
}
//////////////////////////////////////////////////////////////
// ����: void SPI_WriteNByteToTxBuf(u8 *sp,u8 num)
// ����: SPIװ��Ҫ���͵�N���ֽ� ���Ȳ�����
// ����: *sp: ָ��Ҫ���͵�N���ֽڵ��׵�ַ
//       num: Ҫװ���ֽڵ�����  ��Ҫ����SPI_BUF_LENTH
// ע��: SPI_BUF_LENTH��������
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
// ����: void   SPI_TrigTx(void)
// ����: ����SPI���ͺ���, �����ͻ�������ݷ���
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
// ����: u8 SPI_SPI_ReadByteToRxBuf(void)
// ����: SPI�Ӷ������������1���ֽ�
// ���ز���:��������ֽڵ�ֵ
// ע��: ����ԱҪ��֤��������ȷʵ������1����û�ж���������
u8 SPI_SPI_ReadByteToRxBuf(void)
{
    u8 dat;
    if(SPI_RxRead==SPI_RxWrite)
    {
        return 0;//���ص�0 ���Ƕ�����ֵ ���ǻ�������û��Ҫ����������
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
// ����: u8 SPI_SPI_ReadByteToRxBuf(void)
// ����: SPI�Ӷ��������������N���ֽ� ֮ǰ��N-1���ֽڶ�����
// ���ز���:��������ֽڵ�ֵ
// ע��: ����ԱҪ��֤��������ȷʵ������N����û�ж���������
// ע��: SPI_BUF_LENTH��������
u8 SPI_SPI_ReadTheNByteToRxBuf(u8 num)
{
    u8 i=num;
    u8 dat;
    if(i>SPI_BUF_LENTH)
    {
        return 0;//���ص�0 ���Ƕ�����ֵ ������ʽ�������Ϸ�
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
// ����: void SPI_Transivion (void) interrupt SPI_VECTOR
// ����: SPI�жϺ���.
void SPI_Transivion (void) interrupt SPI_VECTOR
{
    if(SPI_TxRead != SPI_TxWrite)
    {
        //��д����֮ǰ�ȶ���SPDAT
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
    SPSTAT = SPIF + WCOL;   //��0 SPIF��WCOL��־
}
