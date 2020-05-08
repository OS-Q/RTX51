/****************************************Copyright (c)****************************************************
**                            kangzhipeng All 
**                                      						   
**                            zhipeng.k@gmail.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               led_display.c
** Latest modified Date:    2013-3-04
** Latest Version:          1.0
** Descriptions:            多位数码管动态程序文件
**--------------------------------------------------------------------------------------------------------
** Created by:              zhipeng.k
** Created date:            2013-03-04
** Version:                 1.0
** Descriptions:            The original version
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
*********************************************************************************************************/
# include<reg52.h>
# include<string.h>
# include "led_display_cfg.h"
# include "led_display.h"

unsigned char LedDisplayBuf[6];
static unsigned char iIndex;

char LedDisplayInit()
{
	return 0;
}
/*******************************************************************************************************/
/* LedDisplay()
** 八位数码管刷新程序，每次刷新一位
** 该驱动不妥当，需要修改；P0应该只访问LedDisplayBuf[]即可，不应该加入太多嵌套。
********************************************************************************************************/


void LedDisplayScan()
{
	static unsigned char iIndex=0;
	//***************************************
	//消隐藏
	wela=1;
	P0=0xff;
	wela=0;
	//***************************************
	dula=1;
	P0=LedShowTable[LedDisplayBuf[iIndex]][1];
	dula=0;
	wela=1;
	P0=SegTable[iIndex];
	wela=0;

	if (iIndex==5) {
		iIndex=0;
	}
	else {
		 	iIndex++;
	}
}
/*******************************************************************************************************/
/* LedDisplayPuts()
** 将字符型数据放入显示缓存区LedDisplayBuf[]
********************************************************************************************************/
char LedDisplayPuts(char * pcstr)
{
	unsigned char i,j;
	if (pcstr==NULL)
		{
		  return -1;
		}
	for (i=0;i<6;i++)	
		{
			if (* pcstr=='0')
		   		{
					LedDisplayBuf[i]=0;	
				}
			if (* pcstr=='.')
				{
				 	i--;
					LedDisplayBuf[i]=LedDisplayBuf[i]|0x80;
				}
				else
					{
						for (j=0;LedShowTable[j][0]!=0;j++)
							{
							   if (LedShowTable[j][0]==* pcstr)
							   		{
									 	LedDisplayBuf[i]= LedShowTable[j][1];
										break;
									}
									
							}
						pcstr++;
					}
		}
		return 0;
}

