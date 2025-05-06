#ifndef LCD_H
#define LCD_H

extern void initLCD (void);
extern void printdata(unsigned char data);
extern void LCD_data(unsigned char data);
extern void LCD_cmd(unsigned char cmd);
extern void LCD_string(unsigned char *str,unsigned char len);

#endif
