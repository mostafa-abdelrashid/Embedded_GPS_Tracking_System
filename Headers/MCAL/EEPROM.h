#ifndef EEPROM_H
#define EEPROM_H



#define EEPROM_START_ADDR     0x2000  // Start address of EEPROM emulation in flash memory  //the true base addres of EEPROM from datasheet (0x400A.F000)
#define EEPROM_SIZE           1024    // EEPROM size in bytes (adjust according to your device)


extern void EEPROM_Init(void);
extern void eeprom_write(float data,unsigned int addr);
extern float eeprom_read(unsigned int addr);




#endif