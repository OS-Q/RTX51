/*------------------------------------------------------------------*/
/* --- STC MCU International Limited -------------------------------*/
/* --- STC 1T Series MCU RC Demo -----------------------------------*/
/* --- Mobile: (86)13922805190 -------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ---------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ---------------------*/
/* --- Web: www.GXWMCU.com -----------------------------------------*/
/* --- QQ:  800003751 ----------------------------------------------*/
/* If you want to use the program or the program referenced in the  */
/* article, please specify in which data and procedures from STC    */
/*------------------------------------------------------------------*/
#ifndef __USART_H
#define __USART_H
#include    "config.h"
#define	COM_TX1_Lenth	128
#define	COM_RX1_Lenth	128
#define	COM_TX2_Lenth	128
#define	COM_RX2_Lenth	128
#define	COM_TX3_Lenth	28
#define	COM_RX3_Lenth	28
#define	COM_TX4_Lenth	28
#define	COM_RX4_Lenth	28

#define	USART1	1
#define	USART2	2
#define	USART3	3
#define	USART4	4

#define	UART_ShiftRight	0		//ͬ����λ���
#define	UART_8bit_BRTx	(1<<6)	//8λ����,�ɱ䲨����
#define	UART_9bit		(2<<6)	//9λ����,�̶�������
#define	UART_9bit_BRTx	(3<<6)	//9λ����,�ɱ䲨����

#define	UART1_SW_P30_P31	0
#define	UART1_SW_P36_P37	(1<<6)
#define	UART1_SW_P16_P17	(2<<6)	/*����ʹ���ڲ�ʱ�� */
#define	UART2_SW_P10_P11	0
#define	UART2_SW_P46_P47	1
#define	UART3_SW_P00_P01	0
#define	UART3_SW_P50_P51	2
#define	UART4_SW_P02_P03	0
#define	UART4_SW_P52_P53	4


#define	TimeOutSet1		5
#define	TimeOutSet2		5
#define	TimeOutSet3		5
#define	TimeOutSet4		5

#define	BRT_Timer1	1
#define	BRT_Timer2	2
#define	BRT_Timer3	1
#define	BRT_Timer4	2

typedef struct
{ 
	u8	id;				//���ں�

	u8	TX_read;		//���Ͷ�ָ��
	u8	TX_write;		//����дָ��
	u8	B_TX_busy;		//æ��־

	u8 	RX_Cnt;			//�����ֽڼ���
	u8	RX_TimeOut;		//���ճ�ʱ
	u8	B_RX_OK;		//���տ����
} COMx_Define; 

typedef struct
{ 
	u8	UART_Mode;			//ģʽ,         UART_ShiftRight,UART_8bit_BRTx,UART_9bit,UART_9bit_BRTx
	u8	UART_BRT_Use;		//ʹ�ò�����,   BRT_Timer1,BRT_Timer2
	u32	UART_BaudRate;		//������,       ENABLE,DISABLE
	u8	Morecommunicate;	//���ͨѶ����, ENABLE,DISABLE
	u8	UART_RxEnable;		//�������,   ENABLE,DISABLE
	u8	BaudRateDouble;		//�����ʼӱ�, ENABLE,DISABLE
	u8	UART_Interrupt;		//�жϿ���,   ENABLE,DISABLE
	u8	UART_Polity;		//���ȼ�,     PolityLow,PolityHigh
	u8	UART_P_SW;			//�л��˿�,   UART1_SW_P30_P31,UART1_SW_P36_P37,UART1_SW_P16_P17(����ʹ���ڲ�ʱ��)
	u8	UART_RXD_TXD_Short;	//�ڲ���·RXD��TXD, ���м�, ENABLE,DISABLE

} COMx_InitDefine; 

extern	COMx_Define	COM1,COM2,COM3,COM4;
extern	u8	xdata TX1_Buffer[COM_TX1_Lenth];	//���ͻ���
extern	u8 	xdata RX1_Buffer[COM_RX1_Lenth];	//���ջ���
extern	u8	xdata TX2_Buffer[COM_TX2_Lenth];	//���ͻ���
extern	u8 	xdata RX2_Buffer[COM_RX2_Lenth];	//���ջ���
extern	u8	xdata TX3_Buffer[COM_TX3_Lenth];	//���ͻ���
extern	u8 	xdata RX3_Buffer[COM_RX3_Lenth];	//���ջ���
extern	u8	xdata TX4_Buffer[COM_TX4_Lenth];	//���ͻ���
extern	u8 	xdata RX4_Buffer[COM_RX4_Lenth];	//���ջ���

u8	USART_Configuration(u8 UARTx, COMx_InitDefine *COMx);
void TX1_write2buff(u8 dat);	//д�뷢�ͻ��壬ָ��+1
void TX2_write2buff(u8 dat);	//д�뷢�ͻ��壬ָ��+1
void TX3_write2buff(u8 dat);	//д�뷢�ͻ��壬ָ��+1
void TX4_write2buff(u8 dat);	//д�뷢�ͻ��壬ָ��+1
void PrintString1(u8 *puts);
void PrintString2(u8 *puts);
void PrintString3(u8 *puts);
void PrintString4(u8 *puts);

//void COMx_write2buff(COMx_Define *COMx, u8 dat);	//д�뷢�ͻ��壬ָ��+1
//void PrintString(COMx_Define *COMx, u8 *puts);

#endif

