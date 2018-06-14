#ifndef __INTERRUPT_H
#define __INTERRUPT_H
#define SC 0 // SC�ź�
#define LIGHT_NUM_MIN 0
#define LIGHT_NUM_MAX 15
#define CURRENT_LIGHT_NUM_MIN 1
#define CURRENT_LIGHT_NUM_MAX 16
#define IAP_ADDRESS_NUM_Min 0
#define IAP_ADDRESS_NUM_Max 51
#define MASTER_TO_SLAVE_DATA_MIN 0
#define MASTER_TO_SLAVE_DATA_MAX 255
#define EEPROM_SIZE_MAX 512
#define DMX512_256__SIZE 256
#define SPARK_CYCLE_MIN 0
#define SPARK_CYCLE_MAX 100
#define SPARK_PWM_MIN 0
#define SPARK_PWM_MAX 100
#define SPARK_PWM_RESOLUTION 100
#define GRADIENT_CYCLE_MIN 0
#define GRADIENT_CYCLE_MAX 100
#define GRADIENT_RESOLUTION 100
#define AUTO_SLEEP_MIN 0
#define AUTO_SLEEP_MAX 100
#define AUTO_SLEEP_RESOLUTION 50
//���ڷ�������״̬��Ϣ
#define UART_STATUS_READY 0
#define UART_STATUS_BUSY 1
//Ƶ��״̬
#define SPARK_STATUS_ON 0
#define SPARK_STATUS_OFF 1
//���龲��״̬����
#define MUTE_ON 0
#define MUTE_OFF 1
//�Զ���ѯ״̬����
#define AUTO_STATUS_ON 0
#define AUTO_STATUS_OFF 1
//�Զ���ѯ����
#define AUTO_TURN_LEFT 0
#define AUTO_TURN_RIGHT 1
// EPROM��ҳ����
#define EPROM_TURN_LEFT 0
#define EPROM_TURN_RIGHT 1
extern unsigned int code IAP_ADDRESS[]; // EEPROM������ַ
extern unsigned char iap_address_num;   // EEPROM������� 0~23
extern unsigned char iap_address_num_old;
extern char feedfack_information[256]; //������Ϣ����
extern char *send_str; //����1���ڷ�����Ϣ������ָ��
extern unsigned char send_data_end_flag; //����1������Ϣ������־
extern unsigned char code
    master_to_slave_off[DMX512_256__SIZE + 1]; //Ƶ��ʱȫ0��Ϣ����
extern unsigned char master_to_slave[DMX512_256__SIZE + 1]; // DMX512�����ź�
extern unsigned char *send_data_DMX512; //����2���ڷ�����Ϣ���޷����ַ�ָ��
extern unsigned short send_data_size_2; //����2�����ַ�������
extern unsigned char *send_str_2; //����2���ڷ�����Ϣ������ָ��
extern unsigned short
    send_data_end_flag_2; //����2������Ϣ������־�Լ�����ָ��ƫ����
extern unsigned char light_group;          // DMX512ͨ����ҳѡ��
extern unsigned short light_group_true;    //��������м���Ϣ
extern unsigned short current_light_num;   //��ǰ����ͨ��
extern unsigned char spark_cycle;          //Ƶ������
extern unsigned short spark_cycle_true;    //Ƶ������ʵ��ֵ
extern unsigned char spark_PWM;            //Ƶ��ռ�ձ� 0~10
extern unsigned short spark_PWM_true;      //Ƶ��ռ�ձ�ʵ��ֵ
extern unsigned char gradient_cycle;       //��������
extern unsigned short gradient_cycle_true; //��������ʵ��ֵ
extern float gradient_master_to_slave[DMX512_256__SIZE + 1]; //�����ۼӵ�Ԫ����
extern unsigned char
    new_master_to_slave[DMX512_256__SIZE + 1]; //��ȡ��������ʱ�����ݴ�������
extern unsigned char
    old_master_to_slave[DMX512_256__SIZE + 1]; //��ȡ��������ʱ�����ݴ�������
extern unsigned short timer_0_count; //��ʱ��3��ʱѭ������
extern unsigned short timer_3_count; //��ʱ��3��ʱѭ������
extern unsigned short timer_4_count; //��ʱ��4��ʱѭ������
extern unsigned char light_all_mute; //���龲����־
extern char g_command[32];           //ȫ�������ַ���
extern char b_command[32];           //���������ַ���
extern short b_command_data, b_command_data_2; //ȫ����������
extern unsigned char b_command_count;  //�����ַ����±�λ��
extern unsigned char auto_status;      //��ѯ״̬��־λ
extern unsigned char auto_start;       //��ѯ��ʼλ
extern unsigned char auto_stop;        //��ѯֹͣλ
extern unsigned char auto_sleep;       //��ѯ״̬����ʱ��
extern unsigned short auto_sleep_true; //��ѯ״̬��ʵ����ʱ��
extern unsigned char auto_turn;        //��ѯ����
extern char *p_b_buffer;               //�ַ����йؼ���ָ��
extern char code *receive_keywords[];
extern char code *receive_keywords_data[];
extern char code *send_keywords[];
extern char code *send_key_words_data[];
extern unsigned char rdata_complete_flag; //�ַ���������ɴ����־λ
extern unsigned char spark_change_flag; //Ƶ��״̬��ת��־λ
extern unsigned char run_change_flag;   //������л�EEPROM��־λ
extern unsigned char gradient_change_flag; //����������ƫ������־λ
#endif                                     /* __INTERRUPT_H*/