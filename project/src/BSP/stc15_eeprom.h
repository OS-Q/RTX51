/* ****************************** ���ߣ�������� *****************************************
 * �ļ����� : stc15_eeprom.H
 * Ӳ��ƽ̨ ���w����̖ FSST15ʵ���
 * ������� ��Keil uVision5.13
 * 
 * �汾����	: V1.0 	   					
 * �޸�����	: 2015-08-29
 * ������̳ �����ӹ���ʦ���أ�http://www.ieebase.net��
 * �Ա����� ��http://fsmcu.taobao.com
 * ����˵�� ��������Ϊ�̲ġ���STC15��Ƭ��ǣ�ֵ���Щ�꡷���廪��ѧ�����磩��������
			  Ϊ��Ƶ������ǳ����תSTC15��Ƭ�����������̣�¼��100��--�������޹���
			  ��Ƶ���鼮����STC�����ں꾧�Ƽ����ٷ���ѧ�ƻ��͸�У����������ʵ����Ȩ���Ƽ�

 * Copyright (C), 2013-2015, ��ƽ��xymbmcu@163.com��/�廪��ѧ������/STC MCU International Limited
 
 * ����ѧϰʹ�ã�δ��������ɣ���������������ҵ��;������ؾ���
************************************************************************************** */

#ifndef	__STC15_EEPROM_H__
#define	__STC15_EEPROM_H__

#include	"config.h"

//	ѡ��MCU�ͺ�
//#define	MCU_Type	STC15W_4K16S4	
//#define	MCU_Type	STC15W_4K32S4	
//#define	MCU_Type	STC15W_4K40S4	
//#define	MCU_Type	STC15W_4K48S4	
//#define	MCU_Type	STC15W_4K56S4	
#define		MCU_Type    IAP15W_4K58S4	
//#define	MCU_Type	IAP15W_4K61S4	
//#define	MCU_Type	IAP15W_4K63S4	


/************************** ISP/IAP *****************************
 IAPϵ�� ������Ӧ�ó����޸�Ӧ�ó���

STC15W4KxxS4	�������䣬512�ֽ�/��������0x0000��ʼ��

     �ͺ�        ��С   ������  ��ʼ��ַ  ������ַ   MOVC��ƫ�Ƶ�ַ
STC15W4K16S4   42K   	84����  0x0000  ~  0xD3FF        0x4000
STC15W4K32S4   26K    	52����  0x0000  ~  0xB3FF        0x8000
STC15W4K40S4   18K    	36����  0x0000  ~  0x93FF        0xA000
STC15W4K48S4   10K   	20����  0x0000  ~  0xD3FF        0xC000
STC15W4K56S4   2K    	4����  	0x0000  ~  0xB3FF        0xE000

IAP15W4K58S4   K    116����  0x0000  ~  0xE7FF        0x0000
IAP15W4K61S4   K    122����  0x0000  ~  0xE3FF        0x0000
IRC15W4K63S4   K    127����  0x0000  ~  0xFDFF        0x0000

*/


#if   (MCU_Type == STC15W_4K16S4)
      #define   MOVC_ShiftAddress    0x4000
#elif (MCU_Type == STC15W_4K32S4)
      #define   MOVC_ShiftAddress    0x8000
#elif (MCU_Type == STC15W_4K40S4)
      #define   MOVC_ShiftAddress    0xA000
#elif (MCU_Type == STC15W_4K48S4)
      #define   MOVC_ShiftAddress    0xC000
#elif (MCU_Type == STC15W_4K56S4)
      #define   MOVC_ShiftAddress    0xE000
#elif (MCU_Type == IAP15W_4K58S4)
/*����ʵ����Ҫ���� ��Ҫע�ⲻҪ�������Լ�����Ч������ ����������ȡ2K*/
      #define   MOVC_ShiftAddress    0xE000 
#elif (MCU_Type == IAP15W_4K61S4)
      #define   MOVC_ShiftAddress    0xE000
#elif (MCU_Type == IAP15W_4K63S4)
      #define   MOVC_ShiftAddress    0xE000
#endif


void	DisableEEPROM(void);
void 	EEPROM_read_n(u16 EE_address,u8 *DataAddress,u16 number);
void 	EEPROM_write_n(u16 EE_address,u8 *DataAddress,u16 number);
void	EEPROM_SectorErase(u16 EE_address);


#endif