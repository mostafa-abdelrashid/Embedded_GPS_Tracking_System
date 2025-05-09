#ifndef LCD_H
#define LCD_H
#include<stdint.h>

void LCD_Init(void) ;
void LCD_WriteCommand(uint8_t cmd) ;
void LCD_WriteData(uint8_t data) ;
void LCD_String(char* str) ;
void LCD_Clear(void);

#endif