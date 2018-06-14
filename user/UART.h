#ifndef __UART_H
#define __UART_H
void uart_send_byte(unsigned char uc_data);
void uart_send_byte_2(unsigned char uc_data);
void uart_send_str(char *p_str);
void uart_send_str_2(char *p_str, unsigned short str_size);
void send_feedfack_information(unsigned char message_flag);
#endif /* __UART_H */