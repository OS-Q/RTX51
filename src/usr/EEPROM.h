#ifndef __EEPROM_H
#define __EEPROM_H
#define CMD_IDLE 0
#define CMD_READ 1
#define CMD_PROGRAM 2
#define CMD_ERASE 3
#define ENABLE_IAP 0x81
//#define IAP_ADDRESS 0x0000
char read_EEPROM(unsigned int address, unsigned short start_address,
                 unsigned short read_size, char *DATA);
char write_EEPROM(unsigned int address, unsigned short start_address,
                  unsigned short write_size, char *DATA);
unsigned char iap_read_byte(unsigned int addr);
void iap_program_byte(unsigned int addr, unsigned char dat);
void iap_erase_sector(unsigned int addr);
#endif /* __EEPROM_H */
