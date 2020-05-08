#ifndef __INTERRUPT_H
#define __INTERRUPT_H
#define SC 0 // SC信号
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
//串口发送数组状态信息
#define UART_STATUS_READY 0
#define UART_STATUS_BUSY 1
//频闪状态
#define SPARK_STATUS_ON 0
#define SPARK_STATUS_OFF 1
//灯组静音状态变量
#define MUTE_ON 0
#define MUTE_OFF 1
//自动轮询状态变量
#define AUTO_STATUS_ON 0
#define AUTO_STATUS_OFF 1
//自动轮询方向
#define AUTO_TURN_LEFT 0
#define AUTO_TURN_RIGHT 1
// EPROM翻页方向
#define EPROM_TURN_LEFT 0
#define EPROM_TURN_RIGHT 1
extern unsigned int code IAP_ADDRESS[]; // EEPROM扇区地址
extern unsigned char iap_address_num;   // EEPROM扇区序号 0~23
extern unsigned char iap_address_num_old;
extern char feedfack_information[256]; //反馈信息数组
extern char *send_str; //串口1用于发送信息的数组指针
extern unsigned char send_data_end_flag; //串口1发送信息结束标志
extern unsigned char code
    master_to_slave_off[DMX512_256__SIZE + 1]; //频闪时全0信息数组
extern unsigned char master_to_slave[DMX512_256__SIZE + 1]; // DMX512控制信号
extern unsigned char *send_data_DMX512; //串口2用于发送信息的无符号字符指针
extern unsigned short send_data_size_2; //串口2发送字符串长度
extern unsigned char *send_str_2; //串口2用于发送信息的数组指针
extern unsigned short
    send_data_end_flag_2; //串口2发送信息结束标志以及数组指针偏移量
extern unsigned char light_group;          // DMX512通道翻页选择
extern unsigned short light_group_true;    //灯组计算中间信息
extern unsigned short current_light_num;   //当前控制通道
extern unsigned char spark_cycle;          //频闪周期
extern unsigned short spark_cycle_true;    //频闪周期实际值
extern unsigned char spark_PWM;            //频闪占空比 0~10
extern unsigned short spark_PWM_true;      //频闪占空比实际值
extern unsigned char gradient_cycle;       //渐变周期
extern unsigned short gradient_cycle_true; //渐变周期实际值
extern float gradient_master_to_slave[DMX512_256__SIZE + 1]; //渐变累加单元数组
extern unsigned char
    new_master_to_slave[DMX512_256__SIZE + 1]; //读取更新数据时新数据储存数组
extern unsigned char
    old_master_to_slave[DMX512_256__SIZE + 1]; //读取更新数据时旧数据储存数组
extern unsigned short timer_0_count; //定时器3延时循环计数
extern unsigned short timer_3_count; //定时器3延时循环计数
extern unsigned short timer_4_count; //定时器4延时循环计数
extern unsigned char light_all_mute; //灯组静音标志
extern char g_command[32];           //全局命令字符串
extern char b_command[32];           //缓冲命令字符串
extern short b_command_data, b_command_data_2; //全局命令数据
extern unsigned char b_command_count;  //缓冲字符串下标位置
extern unsigned char auto_status;      //轮询状态标志位
extern unsigned char auto_start;       //轮询起始位
extern unsigned char auto_stop;        //轮询停止位
extern unsigned char auto_sleep;       //轮询状态保持时长
extern unsigned short auto_sleep_true; //轮询状态真实保持时长
extern unsigned char auto_turn;        //轮询方向
extern char *p_b_buffer;               //字符串中关键字指针
extern char code *receive_keywords[];
extern char code *receive_keywords_data[];
extern char code *send_keywords[];
extern char code *send_key_words_data[];
extern unsigned char rdata_complete_flag; //字符串接收完成处理标志位
extern unsigned char spark_change_flag; //频闪状态翻转标志位
extern unsigned char run_change_flag;   //走马灯切换EEPROM标志位
extern unsigned char gradient_change_flag; //渐变数据总偏移量标志位
#endif                                     /* __INTERRUPT_H*/