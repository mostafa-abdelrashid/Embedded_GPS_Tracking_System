<<<<<<< temp-branch
#include	 "../../Services/tm4c123gh6pm.h"
#include <stdint.h>
#include "../../Headers/HAL/LCD.h"
#include "../../Headers/MCAl/GPIO.h"


// Add a small delay function for stabilization
// Add a small delay function for stabilization
static void delayMs(int ms) {
    volatile int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 1000; j++);
}

void LCD_Init(void) {
		initPortA();
		initPortB();
    SYSCTL_RCGCGPIO_R |= 0x03;  // Enable Ports A and B
    delayMs(10);                // Allow time for clock to stabilize
    
    GPIO_PORTA_DIR_R |= 0xE0;   // PA5-PA7 as output (RS, E)
=======
#include "../../Services/tm4c123gh6pm.h"
#include "../../Services/Bit_Utilities.h"
#include "../../Headers/MCAL/UART.h"
#include "../../Headers/MCAL/Systick.h"
#include "../../Headers/MCAL/GPIO.h"
#include "../../Headers/MCAL/EEPROM.h"
#include "../../Headers/HAL/Landmarks.h"
#include "../../Headers/APP/APP.h"
#include "../../Headers/HAL/GPS.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>

void initLCD (void);
void printdata(unsigned char data);
void LCD_data(unsigned char data);
void LCD_cmd(unsigned char cmd);
void LCD_string(unsigned char *str,unsigned char len);


//P for PIN

//RS == PD0
//RN == PD1
//EN == PD2

//Bo == PA7
//B1 == PA6
//B2 == PA5
//B3 == PB4
//B4 == PB5
//B5 == PD3
//B6 == PB1
//B7 == PB0

void initLCD (void){
	initPortA(); //A7-A6-A5
	GPIO_PORTA_DIR_R |= 0xE0;
	GPIO_PORTA_DEN_R |= 0xE0;
	GPIO_PORTA_CR_R  |= 0xE0;
	initPortB(); //B4-B1-B0-B5
	GPIO_PORTB_DIR_R |= 0xFF;
	//the rest already intialized in GPIO.c In PORTB
	initPortD(); //D3 //D0-D1-D2 ForRS-RN-EN
	GPIO_PORTD_DIR_R |= 0xF;
	GPIO_PORTD_DEN_R |= 0xF;
	GPIO_PORTD_CR_R  |= 0xF;
	delay(600);
	initPortF(); //F1
	GPIO_PORTF_DIR_R |= 0x2;

	// staring commands for LCD
	LCD_cmd(0x38);	//8-bit mode utilsing 16 columons and 2 rows (upper row 0x80 :0x8F)(lower row 0xC0 :0xCF)
	delay(1000);
	LCD_cmd(0x38);
	delay(2000);
	LCD_cmd(0x38);
	delay(500); //three time to ensure Intilziation 
	LCD_cmd(0x0C); //cursor off  and display on 
	LCD_cmd(0x01); //clearscreen
	delay(5000);
	LCD_cmd(0x06); // auto increment 	
	LCD_cmd(0x80);
}


//printing Bits on GPIO PINS
void printdata(unsigned char data) //data = 8-bit hexadecimal data
{
	//zero bit(B0) = A7
	if((data&0x01) !=0)  {GPIO_PORTA_DATA_R |= (1<<7);}
	else								 {GPIO_PORTA_DATA_R &= (~(1<<7));}
	//first bit(B1) =A6
	if((data&0x02) !=0) {GPIO_PORTA_DATA_R |= (1<<6);}
	else								{GPIO_PORTA_DATA_R &= (~(1<<6));}
	//second bit(B2) =A5
	if((data&0x04) !=0) {GPIO_PORTA_DATA_R |= (1<<5);}
	else								{GPIO_PORTA_DATA_R &= (~(1<<5));}
	//third bit(B3) = B4
	if((data&0x08) !=0) {GPIO_PORTB_DATA_R |= (1<<4);}
	else								{GPIO_PORTB_DATA_R &= (~(1<<4));}
	//forth bit(B4) = B5
	if((data&0x10) !=0) {GPIO_PORTB_DATA_R |= (1<<5);}
	else								{GPIO_PORTB_DATA_R &= (~(1<<5));}
	//fifth bit(B5) =D3
	if((data&0x20) !=0) {GPIO_PORTD_DATA_R |= (1<<3);}
	else								{GPIO_PORTD_DATA_R &= (~(1<<3));}
	//sixth bit(B6) =B1
	if((data&0x40) !=0) {GPIO_PORTB_DATA_R |= (1<<1);}
	else								{GPIO_PORTB_DATA_R &= (~(1<<1));}
	//seventh bit(B7) =B0
	if((data&0x80) !=0) {GPIO_PORTB_DATA_R |= (1<<0);}
	else								{GPIO_PORTB_DATA_R &= (~(1<<0));}
}

void LCD_data(unsigned char data)
{
	printdata(data);   							  //print 8bits on the pins
	GPIO_PORTD_DATA_R &= (~(1<<1));   //turnoff RN to R/W bin on Write 
	GPIO_PORTD_DATA_R |= (1<<0);      // Turn on the RS to Write on data Register for LCD (off for Command REG.)
	GPIO_PORTD_DATA_R |= (1<<2);      //Turn on enable 
	delay(500);                       //500 is not calculated
	GPIO_PORTD_DATA_R &= (~(1<<2));	//Turn off enable of LCD 
	delay(2000);

}
void LCD_cmd(unsigned char cmd)
{
	printdata(cmd);   							  //print 8bits on the pins
	GPIO_PORTD_DATA_R &= (~(1<<1));   //turnoff RN to R/W bin on Write 
	GPIO_PORTD_DATA_R &= (~(1<<0));   // Turn offthe RS to Write on Command Register for LCD (on for Data REG.)
	GPIO_PORTD_DATA_R |= (1<<2);      //Turn on enable 
	delay(1);                       //500 is not calculated
	GPIO_PORTD_DATA_R &= (~(1<<2));   //Turn off enable of LCD 
	delay(2000);
}

void LCD_string(unsigned char *str,unsigned char len)
{
	char i;
	for(i=0;i<len;i++){
		LCD_data(str[i]);
	}
}
/*#include "../../Services/tm4c123gh6pm.h"
#include "../../Services/Bit_Utilities.h"
#include "../../Headers/MCAL/GPIO.h"
#include "../../Headers/MCAL/Systick.h"
#include "../../Headers/HAL/LCD.h"

void initLCD(void) {
    initPortA();
    GPIO_PORTA_DIR_R |= 0xE0;
>>>>>>> main
    GPIO_PORTA_DEN_R |= 0xE0;
    GPIO_PORTB_DIR_R = 0xFF;    // PB0-PB7 as output (Data)
    GPIO_PORTB_DEN_R = 0xFF;
    
    delayMs(20);                // Additional LCD power-up time
    
    // Extended initialization sequence
    LCD_WriteCommand(0x38);     // 8-bit mode, 2 lines, 5x7 font
    delayMs(5);
    LCD_WriteCommand(0x38);     // Repeat for stabilization
    delayMs(1);
    LCD_WriteCommand(0x38);     // Third time ensures reliability
    delayMs(1);
    
    LCD_WriteCommand(0x0C);     // Display on, cursor off
    LCD_WriteCommand(0x01);     // Clear display
    delayMs(2);                 // Clear display needs extra time
    LCD_WriteCommand(0x06);     // Entry mode: increment, no shift
}

void LCD_WriteCommand(uint8_t cmd) {
    GPIO_PORTA_DATA_R &= ~0xE0;     // RS=0, E=0
    GPIO_PORTB_DATA_R = cmd;
    GPIO_PORTA_DATA_R |= 0x80;      // E = 1
    delayMs(1);
    GPIO_PORTA_DATA_R &= ~0x80;     // E = 0
    delayMs(2);
}

void LCD_WriteData(uint8_t data) {
    GPIO_PORTA_DATA_R = (GPIO_PORTA_DATA_R & ~0xE0) | 0x20;  // RS=1, E=0
    GPIO_PORTB_DATA_R = data;
    GPIO_PORTA_DATA_R |= 0x80;      // E = 1
    delayMs(1);
    GPIO_PORTA_DATA_R &= ~0x80;     // E = 0
    delayMs(1);
}

void LCD_String(char* str) {
    while (*str) {
        LCD_WriteData(*str++);
    }
}

<<<<<<< temp-branch
void LCD_Clear(void) {
    LCD_WriteCommand(0x01);     // Clear display
    delayMs(3);                 // Clear needs extra time (up�to�1.64ms)
}
=======
void LCD_string(char *str, char len) {
    char i;
    for (i = 0; i < len; i++) {
        LCD_data(str[i]);
    }
}*/
>>>>>>> main
