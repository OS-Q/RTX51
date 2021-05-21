/* ****************************** 作者：残弈悟恩 *****************************************
 * 文件名称 : stc15_eeprom.H
 * 硬件平台 ：飛天三號 FSST15实验板
 * 软件环境 ：Keil uVision5.13
 * 
 * 版本代号	: V1.0 	   					
 * 修改日期	: 2015-08-29
 * 技术论坛 ：电子工程师基地（http://www.ieebase.net）
 * 淘宝店铺 ：http://fsmcu.taobao.com
 * 例程说明 ：本例程为教材《与STC15单片机牵手的那些年》（清华大学出版社）配套例程
			  为视频《深入浅出玩转STC15单片机》配套例程（录制100讲--西安：愚公）
			  视频和书籍均被STC（深圳宏晶科技）官方大学计划和高校高性能联合实验室权威推荐

 * Copyright (C), 2013-2015, 刘平（xymbmcu@163.com）/清华大学出版社/STC MCU International Limited
 
 * 仅供学习使用，未经作者许可，不得用于其它商业用途，盗版必究。
************************************************************************************** */

#ifndef	__STC15_EEPROM_H__
#define	__STC15_EEPROM_H__

#include	"config.h"

//	选择MCU型号
//#define	MCU_Type	STC15W_4K16S4	
//#define	MCU_Type	STC15W_4K32S4	
//#define	MCU_Type	STC15W_4K40S4	
//#define	MCU_Type	STC15W_4K48S4	
//#define	MCU_Type	STC15W_4K56S4	
#define		MCU_Type    IAP15W_4K58S4	
//#define	MCU_Type	IAP15W_4K61S4	
//#define	MCU_Type	IAP15W_4K63S4	


/************************** ISP/IAP *****************************
 IAP系列 可以在应用程序修改应用程序。

STC15W4KxxS4	扇区分配，512字节/扇区，从0x0000开始。

     型号        大小   扇区数  开始地址  结束地址   MOVC读偏移地址
STC15W4K16S4   42K   	84扇区  0x0000  ~  0xD3FF        0x4000
STC15W4K32S4   26K    	52扇区  0x0000  ~  0xB3FF        0x8000
STC15W4K40S4   18K    	36扇区  0x0000  ~  0x93FF        0xA000
STC15W4K48S4   10K   	20扇区  0x0000  ~  0xD3FF        0xC000
STC15W4K56S4   2K    	4扇区  	0x0000  ~  0xB3FF        0xE000

IAP15W4K58S4   K    116扇区  0x0000  ~  0xE7FF        0x0000
IAP15W4K61S4   K    122扇区  0x0000  ~  0xE3FF        0x0000
IRC15W4K63S4   K    127扇区  0x0000  ~  0xFDFF        0x0000

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
/*根据实际需要更改 但要注意不要覆盖了自己的有效程序区 在这里我们取2K*/
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