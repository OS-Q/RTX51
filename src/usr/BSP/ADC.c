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
#include    "adc.h"
//========================================================================
// ����: void   ADC_Inilize(ADC_InitTypeDef *ADCx)
// ����: ADC��ʼ������.
// ����: ADCx: �ṹ����,��ο�adc.h��Ķ���.
// ����: none.
// �汾: V1.0, 2012-10-22
//========================================================================
void    ADC_Inilize(ADC_InitTypeDef *ADCx)
{
    P1ASF = ADCx->ADC_Px;
    ADC_CONTR = (ADC_CONTR & ~ADC_90T) | ADCx->ADC_Speed;
    if(ADCx->ADC_Power == ENABLE)
    {
        ADC_CONTR |= 0x80;
    }
    else
    {
        ADC_CONTR &= 0x7F;
    }
    if(ADCx->ADC_AdjResult == ADC_RES_H2L8)
    {
        PCON2 |=  (1<<5);    //10λAD����ĸ�2λ��ADC_RES�ĵ�2λ����8λ��ADC_RESL��
    }
    else
    {
        PCON2 &= ~(1<<5);    //10λAD����ĸ�8λ��ADC_RES����2λ��ADC_RESL�ĵ�2λ��
    }
    if(ADCx->ADC_Interrupt == ENABLE)
    {
        EADC = 1;    //�ж�����     ENABLE,DISABLE
    }
    else
    {
        EADC = 0;
    }
    if(ADCx->ADC_Polity == PolityHigh)
    {
        PADC = 1;    //���ȼ�����   PolityHigh,PolityLow
    }
    else
    {
        PADC = 0;
    }
}
//========================================================================
// ����: void   ADC_PowerControl(u8 pwr)
// ����: ADC��Դ���Ƴ���.
// ����: pwr: ��Դ����,ENABLE��DISABLE.
// ����: none.
// �汾: V1.0, 2012-10-22
//========================================================================
void    ADC_PowerControl(u8 pwr)
{
    if(pwr == ENABLE)
    {
        ADC_CONTR |= 0x80;
    }
    else
    {
        ADC_CONTR &= 0x7f;
    }
}
//========================================================================
// ����: u16    Get_ADC10bitResult(u8 channel)
// ����: ��ѯ����һ��ADC���.
// ����: channel: ѡ��Ҫת����ADC.
// ����: 10λADC���.
// �汾: V1.0, 2012-10-22
//========================================================================
u16 Get_ADC10bitResult(u8 channel)  //channel = 0~7
{
    u16 adc;
    u8  i;
    if(channel > ADC_CH7)
    {
        return    1024;    //����,����1024,���õĳ����ж�
    }
    ADC_RES = 0;
    ADC_RESL = 0;
    ADC_CONTR = (ADC_CONTR & 0xe0) | ADC_START | channel;
    NOP(4);         //��ADC_CONTR������Ҫ4T֮����ܷ���
    for(i=0; i<250; i++)        //��ʱ
    {
        if(ADC_CONTR & ADC_FLAG)
        {
            ADC_CONTR &= ~ADC_FLAG;
            if(PCON2 &  (1<<5))     //10λAD����ĸ�2λ��ADC_RES�ĵ�2λ����8λ��ADC_RESL��
            {
                adc = (u16)(ADC_RES & 3);
                adc = (adc << 8) | ADC_RESL;
            }
            else        //10λAD����ĸ�8λ��ADC_RES����2λ��ADC_RESL�ĵ�2λ��
            {
                adc = (u16)ADC_RES;
                adc = (adc << 2) | (ADC_RESL & 3);
            }
            return  adc;
        }
    }
    return  1024;   //����,����1024,���õĳ����ж�
}
//========================================================================
// ����: void ADC_int(void) interrupt ADC_VECTOR
// ����: ADC�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2012-10-22
//========================================================================
void ADC_int (void) interrupt ADC_VECTOR
{
    ADC_CONTR &= ~ADC_FLAG;
}
