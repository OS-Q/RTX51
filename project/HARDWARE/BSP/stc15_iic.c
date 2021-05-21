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
#include    "stc15_iic.h"
/* ***************************************************** */
// �������ƣ�Delay5US()
// �������ܣ�5΢����ʱ,����Լ�����Ƶ�б䣬�������޸�
// ��ڲ�������
// ���ڲ�������
/* ***************************************************** */
void Delay5US(void)     //@11.0592MHz
{
    u8 i;
    _nop_();
    i = 11;
    while (--i)
    {
        ;
    }
}
/* ***************************************************** */
// �������ƣ�IIC_Start()
// �������ܣ�IIC��
// ��ڲ�������
// ���ڲ�������
/* ***************************************************** */
void IIC_Start(void)
{
    SDA = 1;
    Delay5US();
    SCL = 1;
    Delay5US();
    SDA = 0;
    Delay5US();
}
/* ***************************************************** */
// �������ƣ�IIC_Stop()
// �������ܣ�IICֹͣ
// ��ڲ�������
// ���ڲ�������
/* ***************************************************** */
void IIC_Stop(void)
{
    SDA = 0;
    Delay5US();
    SCL = 1;
    Delay5US();
    SDA =1;
}
/* ***************************************************** */
// �������ƣ�IIC_Ack()
// �������ܣ�IICӦ��
// ��ڲ�������
// ���ڲ�������
/* ***************************************************** */
void IIC_Ack(void)
{
    SCL = 0;                // Ϊ��������׼��
    SDA = 0;                // ����Ӧ���ź�
    Delay5US();             // ��ʱ�㶮��
    SCL = 1;
    Delay5US();
    SCL = 0;
    Delay5US();     // ����������
    SDA = 1;                // �ͷ�����
}
/* ***************************************************** */
// �������ƣ�IIC_RdAck()
// �������ܣ���IICӦ��
// ��ڲ�������
// ���ڲ������Ƿ�Ӧ����ֵ
/* ***************************************************** */
BOOL IIC_RdAck(void)
{
    BOOL AckFlag;
    u8 uiVal = 0;
    SCL = 0;
    Delay5US();
    SDA = 1;
    SCL = 1;
    Delay5US();
    while((1 == SDA) && (uiVal < 255))
    {
        uiVal ++;
        AckFlag = SDA;
    }
    SCL = 0;
    return AckFlag;     // Ӧ�𷵻أ�0;��Ӧ�𷵻أ�1
}
/* ***************************************************** */
// �������ƣ�IIC_Nack()
// �������ܣ�IIC��Ӧ��
// ��ڲ�������
// ���ڲ�������
/* ***************************************************** */
void IIC_Nack(void)
{
    SDA = 1;
    SCL = 0;
    Delay5US();
    SCL = 1;
    Delay5US();
    SCL = 0;
}
/* ***************************************************** */
// �������ƣ�OutputOneByte()
// �������ܣ���IIC�����ж���һ���ֽ�
// ��ڲ�������
// ���ڲ�����������һ���ֽڣ�uByteVal��
/* ***************************************************** */
u8 OutputOneByte(void)
{
    u8 uByteVal = 0;
    u8 iCount;
    SDA = 1;
    for (iCount = 0; iCount < 8; iCount++)
    {
        SCL = 0;
        Delay5US();
        SCL = 1;
        Delay5US();
        uByteVal <<= 1;
        if(SDA)
        {
            uByteVal |= 0x01;
        }
    }
    SCL = 0;
    return(uByteVal);
}
/* ***************************************************** */
// �������ƣ�InputOneByte()
// �������ܣ���IIC����д��һ���ֽ�
// ��ڲ�������д���һ���ֽڣ�uByteVal��
// ���ڲ�������
/* ***************************************************** */
void InputOneByte(u8 uByteVal)
{
    u8 iCount;
    for(iCount = 0; iCount < 8; iCount++)
    {
        SCL = 0;
        Delay5US();
        SDA = (uByteVal & 0x80) >> 7;
        Delay5US();
        SCL = 1;
        Delay5US();
        uByteVal <<= 1;
    }
    SCL = 0;
}
/* ***************************************************** */
// �������ƣ�IIC_WrDevAddAndDatAdd()
// �������ܣ���IIC����д�����������ݵ�ַ
// ��ڲ�����������ַ��uDevAdd�������ݵ�ַ��uDatAdd��
// ���ڲ�����д���Ƿ�ɹ���ֵ
/* ***************************************************** */
BOOL IIC_WrDevAddAndDatAdd(u8 uDevAdd,u8 uDatAdd)
{
    IIC_Start();            // ���Ϳ�ʼ�ź�
    InputOneByte(uDevAdd);  // ����������ַ
    IIC_RdAck();            // ��Ӧ���ź�
    InputOneByte(uDatAdd);  // �������ݵ�ַ
    IIC_RdAck();            // ��Ӧ���ź�
    return TRUE;
}
/* ***************************************************** */
// �������ƣ�IIC_WrDatToAdd()
// �������ܣ���IIC����д����
// ��ڲ���������ID(uDevID)�����ݴ洢��ʼ��ַ(uStaAddVal)
//           ��������(*p)�������洢���ݵĸ���(uiLenVal)
// ���ڲ�������
/* ***************************************************** */
void IIC_WrDatToAdd(u8 uDevID, u8 uStaAddVal, u8 *p, u8 ucLenVal)
{
    u8 iCount;
    IIC_WrDevAddAndDatAdd(uDevID | IIC_WRITE,uStaAddVal);
    // IIC_WRITE Ϊд�����׺��
    for(iCount = 0; iCount < ucLenVal; iCount++)
    {
        InputOneByte(*p++);
        IIC_RdAck();
    }
    IIC_Stop();
}
/* ***************************************************** */
// �������ƣ�IIC_RdDatFromAdd()
// �������ܣ���IIC����������
// ��ڲ���������ID(uDevID)�����ݴ洢��ַ(uStaAddVal)
//           ��������(*p)�������洢���ݵĸ���(uiLenVal)
// ���ڲ�������
/* ***************************************************** */
void IIC_RdDatFromAdd(u8 uDevID, u8 uStaAddVal, u8 *p, u8 uiLenVal)
{
    u8 iCount;
    IIC_WrDevAddAndDatAdd(uDevID | IIC_WRITE,uStaAddVal);
    IIC_Start();
    InputOneByte(uDevID | IIC_READ);
    // IIC_READ Ϊд�����׺��
    IIC_RdAck();
    for(iCount = 0; iCount < uiLenVal; iCount++)
    {
        *p++ = OutputOneByte();
        if(iCount != (uiLenVal - 1))
        {
            IIC_Ack();
        }
    }
    IIC_Nack();
    IIC_Stop();
}
