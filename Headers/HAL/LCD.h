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

void initLCD(void);
void LCD_cmd(char cmd);
void LCD_data(char data);
void LCD_string(char *str, char len);

#endif
