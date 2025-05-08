/*#ifndef LCD_H
#define LCD_H

extern void initLCD (void);
extern void printdata(unsigned char data);
extern void LCD_data(unsigned char data);
extern void LCD_cmd(unsigned char cmd);
extern void LCD_string(unsigned char *str,unsigned char len);

#endif
*/
#ifndef LCD_H
#define LCD_H
#include<stdint.h>

void LCD_Init(void) ;
void LCD_WriteCommand(uint8_t cmd) ;
void LCD_WriteData(uint8_t data) ;
void LCD_String(char* str) ;
void LCD_Clear(void);
#endif
