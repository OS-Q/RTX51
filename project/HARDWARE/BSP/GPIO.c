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
/*************  ����˵��    **************
���ļ�ΪSTC15xxxϵ�еĶ˿ڳ�ʼ������,�û��������Բ��޸��������.
******************************************/
#include    "GPIO.h"
void setPinState(u8 Pin,bit State)
{
	 Pin=State;
	
	
}
//========================================================================
// ����: u8 GPIO_Inilize(u8 GPIO, GPIO_InitTypeDef *GPIOx)
// ����: ��ʼ��IO��.
// ����: GPIOx: �ṹ����,��ο�timer.h��Ķ���.
// ����: �ɹ�����0, �ղ�������1,���󷵻�2.
// �汾: V1.0, 2012-10-22
//========================================================================
u8  GPIO_Inilize(u8 GPIO, GPIO_InitTypeDef *GPIOx)
{
    if(GPIO > GPIO_P5)
    {
        return 1;    //�ղ���
    }
    if(GPIOx->Mode > GPIO_OUT_PP)
    {
        return 2;    //����
    }
    if(GPIO == GPIO_P0)
    {
        if(GPIOx->Mode == GPIO_PullUp)
        {
            P0M1 &= ~GPIOx->Pin,  P0M0 &= ~GPIOx->Pin;    //����׼˫���
        }
        if(GPIOx->Mode == GPIO_HighZ)
        {
            P0M1 |=  GPIOx->Pin,  P0M0 &= ~GPIOx->Pin;    //��������
        }
        if(GPIOx->Mode == GPIO_OUT_OD)
        {
            P0M1 |=  GPIOx->Pin,  P0M0 |=  GPIOx->Pin;    //��©���
        }
        if(GPIOx->Mode == GPIO_OUT_PP)
        {
            P0M1 &= ~GPIOx->Pin,  P0M0 |=  GPIOx->Pin;    //�������
        }
    }
    if(GPIO == GPIO_P1)
    {
        if(GPIOx->Mode == GPIO_PullUp)
        {
            P1M1 &= ~GPIOx->Pin,  P1M0 &= ~GPIOx->Pin;    //����׼˫���
        }
        if(GPIOx->Mode == GPIO_HighZ)
        {
            P1M1 |=  GPIOx->Pin,  P1M0 &= ~GPIOx->Pin;    //��������
        }
        if(GPIOx->Mode == GPIO_OUT_OD)
        {
            P1M1 |=  GPIOx->Pin,  P1M0 |=  GPIOx->Pin;    //��©���
        }
        if(GPIOx->Mode == GPIO_OUT_PP)
        {
            P1M1 &= ~GPIOx->Pin,  P1M0 |=  GPIOx->Pin;    //�������
        }
    }
    if(GPIO == GPIO_P2)
    {
        if(GPIOx->Mode == GPIO_PullUp)
        {
            P2M1 &= ~GPIOx->Pin,  P2M0 &= ~GPIOx->Pin;    //����׼˫���
        }
        if(GPIOx->Mode == GPIO_HighZ)
        {
            P2M1 |=  GPIOx->Pin,  P2M0 &= ~GPIOx->Pin;    //��������
        }
        if(GPIOx->Mode == GPIO_OUT_OD)
        {
            P2M1 |=  GPIOx->Pin,  P2M0 |=  GPIOx->Pin;    //��©���
        }
        if(GPIOx->Mode == GPIO_OUT_PP)
        {
            P2M1 &= ~GPIOx->Pin,  P2M0 |=  GPIOx->Pin;    //�������
        }
    }
    if(GPIO == GPIO_P3)
    {
        if(GPIOx->Mode == GPIO_PullUp)
        {
            P3M1 &= ~GPIOx->Pin,  P3M0 &= ~GPIOx->Pin;    //����׼˫���
        }
        if(GPIOx->Mode == GPIO_HighZ)
        {
            P3M1 |=  GPIOx->Pin,  P3M0 &= ~GPIOx->Pin;    //��������
        }
        if(GPIOx->Mode == GPIO_OUT_OD)
        {
            P3M1 |=  GPIOx->Pin,  P3M0 |=  GPIOx->Pin;    //��©���
        }
        if(GPIOx->Mode == GPIO_OUT_PP)
        {
            P3M1 &= ~GPIOx->Pin,  P3M0 |=  GPIOx->Pin;    //�������
        }
    }
    if(GPIO == GPIO_P4)
    {
        if(GPIOx->Mode == GPIO_PullUp)
        {
            P4M1 &= ~GPIOx->Pin,  P4M0 &= ~GPIOx->Pin;    //����׼˫���
        }
        if(GPIOx->Mode == GPIO_HighZ)
        {
            P4M1 |=  GPIOx->Pin,  P4M0 &= ~GPIOx->Pin;    //��������
        }
        if(GPIOx->Mode == GPIO_OUT_OD)
        {
            P4M1 |=  GPIOx->Pin,  P4M0 |=  GPIOx->Pin;    //��©���
        }
        if(GPIOx->Mode == GPIO_OUT_PP)
        {
            P4M1 &= ~GPIOx->Pin,  P4M0 |=  GPIOx->Pin;    //�������
        }
    }
    if(GPIO == GPIO_P5)
    {
        if(GPIOx->Mode == GPIO_PullUp)
        {
            P5M1 &= ~GPIOx->Pin,  P5M0 &= ~GPIOx->Pin;    //����׼˫���
        }
        if(GPIOx->Mode == GPIO_HighZ)
        {
            P5M1 |=  GPIOx->Pin,  P5M0 &= ~GPIOx->Pin;    //��������
        }
        if(GPIOx->Mode == GPIO_OUT_OD)
        {
            P5M1 |=  GPIOx->Pin,  P5M0 |=  GPIOx->Pin;    //��©���
        }
        if(GPIOx->Mode == GPIO_OUT_PP)
        {
            P5M1 &= ~GPIOx->Pin,  P5M0 |=  GPIOx->Pin;    //�������
        }
    }
    return 0;   //�ɹ�
}
