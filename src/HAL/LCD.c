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

void LCD_Clear(void) {
    LCD_WriteCommand(0x01);     // Clear display
    delayMs(3);                 // Clear needs extra time (up to 1.64ms)
}
