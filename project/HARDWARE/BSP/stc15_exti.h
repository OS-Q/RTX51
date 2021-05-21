/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : stc15_exti.h
 * Ӳ��ƽ̨ ���w����̖ FSST15ʵ���
 * ������� ��Keil uVision5.13
 * 
 * �汾����	: V1.0 	   					
 * �޸�����	: 2015-08-30
 * ������̳ �����ӹ���ʦ���أ�http://www.ieebase.net��
 * �Ա����� ��http://fsmcu.taobao.com
 * ����˵�� ��������Ϊ�̲ġ���STC15��Ƭ��ǣ�ֵ���Щ�꡷���廪��ѧ�����磩��������
			  Ϊ��Ƶ������ǳ����תSTC15��Ƭ�����������̣�¼��100��--�������޹���
			  ��Ƶ���鼮����STC�����ں꾧�Ƽ����ٷ���ѧ�ƻ��͸�У����������ʵ����Ȩ���Ƽ�

 * Copyright (C), 2013-2015, ��ƽ��xymbmcu@163.com��/�廪��ѧ������/STC MCU International Limited
 
 * ����ѧϰʹ�ã�δ��������ɣ���������������ҵ��;������ؾ���
************************************************************************************** */

#ifndef	__STC15_EXTI_H__
#define	__STC15_EXTI_H__

#include    "config.h"

#define	EXT_INT0			0	//��ʼ�����ж�0
#define	EXT_INT1			1	//��ʼ�����ж�1
#define	EXT_INT2			2	//��ʼ�����ж�2
#define	EXT_INT3			3	//��ʼ�����ж�3
#define	EXT_INT4			4	//��ʼ�����ж�4

#define	EXT_MODE_RiseFall	0	//������/�½����ж�  (ֻ������INT0 1)
#define	EXT_MODE_Fall		1	//�½����ж�

typedef struct
{
	u8	EXTI_Mode;			//�ж�ģʽ,  	EXT_MODE_RiseFall, EXT_MODE_Fall
	u8	EXTI_Polity;		//���ȼ�����	PolityHigh,PolityLow
	u8	EXTI_Interrupt;		//�ж�����		ENABLE,DISABLE
} EXTI_InitTypeDef;

u8	Ext_Inilize(u8 EXT, EXTI_InitTypeDef *INTx);

#endif
