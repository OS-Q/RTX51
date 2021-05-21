/************************************************************
* ��֯���ƣ� ���Ӵ���С��
* �ļ�����: DataScope_DP.c
* ����:  δ֪
* �汾 :1.1
* ����:
* ��Ҫ���� :
* ����λ���������ݵ��ļ�
* ��ʷ�޸ļ�¼: // ��ʷ�޸ļ�¼
* <����> <ʱ��> <�汾 > <����>
***********************************************************/
/***************����ʾ������������************************/
#include "DataScope_DP.h"
#include "../../../HARDWARE/BSP/USART1.h"
#define DATA_SCOPE
#ifdef DATA_SCOPE

unsigned char DataScope_OutPut_Buffer[42] = {0};       //���ڷ��ͻ�����
//����˵�����������ȸ�������ת��4�ֽ����ݲ�����ָ����ַ
//����˵�����û�����ֱ�Ӳ����˺���
//target:Ŀ�굥��������
//buf:��д������
//beg:ָ��������ڼ���Ԫ�ؿ�ʼд��
//�����޷���
//�Դ˺����������޸ģ�ԭ����������ģ���������point�����˳���ˣ�����������ʹ����
 void Float2Byte(float *target,unsigned char *buf,unsigned char beg)
{
  unsigned char *point;
  point = (unsigned char*)target;   //�õ�float�ĵ�ַ
  buf[beg]   = point[3];
  buf[beg+1] = point[2];
  buf[beg+2] = point[1];
  buf[beg+3] = point[0];
}
 /*************************************************
 * ��������:
 * ����:
 * ����:
 * ���:
 * ����ֵ:
 * ����˵��:
 *************************************************/
 void sendScopeData(float Data, u8 channel)
 {
	 u8 a; //

	 DataScope_Get_Channel_Data(Data, channel);

	 for (a = 0; a < DataScope_Data_Generate(channel); a++)
	 {
		 TX1_write2buff(DataScope_OutPut_Buffer[a]); //����һͨ�����ݵ�����ʾ����
	 }

 }

//����˵������������ͨ���ĵ����ȸ�������д�뷢�ͻ�����
//Data��ͨ������
//Channel��ѡ��ͨ����1-10��
//�����޷���
void DataScope_Get_Channel_Data(float Data,unsigned char Channel)
{
  if ( (Channel > 10) || (Channel == 0) )
    {
      return;    //ͨ����������10�����0��ֱ����������ִ�к���
    }
  else
    {
      switch (Channel)
        {
          case 1:
            Float2Byte(&Data,DataScope_OutPut_Buffer,1);
            break;
          case 2:
            Float2Byte(&Data,DataScope_OutPut_Buffer,5);
            break;
          case 3:
            Float2Byte(&Data,DataScope_OutPut_Buffer,9);
            break;
          case 4:
            Float2Byte(&Data,DataScope_OutPut_Buffer,13);
            break;
          case 5:
            Float2Byte(&Data,DataScope_OutPut_Buffer,17);
            break;
          case 6:
            Float2Byte(&Data,DataScope_OutPut_Buffer,21);
            break;
          case 7:
            Float2Byte(&Data,DataScope_OutPut_Buffer,25);
            break;
          case 8:
            Float2Byte(&Data,DataScope_OutPut_Buffer,29);
            break;
          case 9:
            Float2Byte(&Data,DataScope_OutPut_Buffer,33);
            break;
          case 10:
            Float2Byte(&Data,DataScope_OutPut_Buffer,37);
            break;
        }
    }
}
//����˵�������� DataScopeV1.0 ����ȷʶ���֡��ʽ
//Channel_Number����Ҫ���͵�ͨ������
//���ط��ͻ��������ݸ���
//����0��ʾ֡��ʽ����ʧ��
unsigned char DataScope_Data_Generate(unsigned char Channel_Number)
{
  if ( (Channel_Number > 10) || (Channel_Number == 0) )
    {
      return 0;    //ͨ����������10�����0��ֱ����������ִ�к���
    }
  else
    {
      DataScope_OutPut_Buffer[0] = '$';  //֡ͷ
      switch(Channel_Number)
        {
          case 1:
            DataScope_OutPut_Buffer[5]  =  5;
            return  6;
            break;
          case 2:
            DataScope_OutPut_Buffer[9]  =  9;
            return 10;
            break;
          case 3:
            DataScope_OutPut_Buffer[13] = 13;
            return 14;
            break;
          case 4:
            DataScope_OutPut_Buffer[17] = 17;
            return 18;
            break;
          case 5:
            DataScope_OutPut_Buffer[21] = 21;
            return 22;
            break;
          case 6:
            DataScope_OutPut_Buffer[25] = 25;
            return 26;
            break;
          case 7:
            DataScope_OutPut_Buffer[29] = 29;
            return 30;
            break;
          case 8:
            DataScope_OutPut_Buffer[33] = 33;
            return 34;
            break;
          case 9:
            DataScope_OutPut_Buffer[37] = 37;
            return 38;
            break;
          case 10:
            DataScope_OutPut_Buffer[41] = 41;
            return 42;
            break;
        }
    }
  return 0;
}
#endif
