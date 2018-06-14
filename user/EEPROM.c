#include "EEPROM.H"
#include <STC15.H>
#include <intrins.h>
#define SECTOR_SIZE 512 // EEPROM扇区大小
char temp_data[512];
char read_EEPROM(unsigned int address, unsigned short start_address,
                 unsigned short read_size, unsigned char *DATA) {
  unsigned int i;
  if ((start_address + read_size) > SECTOR_SIZE) {
    // goto ERROR;
  }
  address += start_address;
  for (i = 0; i < read_size; i++) {
    *(DATA++) = iap_read_byte(address++);
  }
  return 0;
}
char write_EEPROM(unsigned int address, unsigned short start_address,
                  unsigned short write_size, unsigned char *DATA) {
  unsigned int i;
  if ((start_address + write_size) > SECTOR_SIZE) {
    // goto ERROR;
  }
  for (i = 0; i < SECTOR_SIZE; i++) {
    temp_data[i] = iap_read_byte(address + i);
  }
  iap_erase_sector(address);
  for (i = 0; i < SECTOR_SIZE; i++) {
    if (iap_read_byte(address + i) != 0xFF) {
      // goto ERROR;
    }
  }
  for (i = 0; i < start_address; i++) {
    iap_program_byte(address++, temp_data[i]);
  }
  for (i = 0; i < write_size; i++) {
    iap_program_byte(address++, *(DATA++));
  }
  for (i = (start_address + write_size); i < SECTOR_SIZE; i++) {
    iap_program_byte(address++, temp_data[i]);
  }
  return 0;
}
void iap_idle() {
  IAP_CONTR = 0;
  IAP_CMD = 0;
  IAP_TRIG = 0;
  IAP_ADDRH = 0x80;
  IAP_ADDRL = 0;
}
unsigned char iap_read_byte(unsigned int addr) {
  unsigned char dat;
  IAP_CONTR = ENABLE_IAP;
  IAP_CMD = CMD_READ;
  IAP_ADDRL = addr;
  IAP_ADDRH = addr >> 8;
  IAP_TRIG = 0x5A;
  IAP_TRIG = 0xA5;
  _nop_();
  dat = IAP_DATA;
  iap_idle();
  return dat;
}
void iap_program_byte(unsigned int addr, unsigned char dat) {
  IAP_CONTR = ENABLE_IAP;
  IAP_CMD = CMD_PROGRAM;
  IAP_ADDRL = addr;
  IAP_ADDRH = addr >> 8;
  IAP_DATA = dat;
  IAP_TRIG = 0x5A;
  IAP_TRIG = 0xA5;
  _nop_();
  iap_idle();
}
void iap_erase_sector(unsigned int addr) {
  IAP_CONTR = ENABLE_IAP;
  IAP_CMD = CMD_ERASE;
  IAP_ADDRL = addr;
  IAP_ADDRH = addr >> 8;
  IAP_TRIG = 0x5A;
  IAP_TRIG = 0xA5;
  _nop_();
  iap_idle();
}
