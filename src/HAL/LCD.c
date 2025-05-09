
#include <stdint.h>
#include "../../Services/tm4c123gh6pm.h"
#include "../../Headers/MCAL/Systick.h"


void LCD_WriteCommand(uint8_t cmd) {
    GPIO_PORTA_DATA_R = 0x00;   // RS=0 (command), E=0
    GPIO_PORTB_DATA_R = cmd;    // Send command
    GPIO_PORTA_DATA_R |= 0x80;  // Pulse E high (PA7)
		delay(1);
    GPIO_PORTA_DATA_R &= ~0x80; // E low
    delay(2);                 // Most commands need 2ms to execute
}
void LCD_Init(void) {
    SYSCTL_RCGCGPIO_R |= 0x03;  // Enable Ports A and B
    delay(10);                // Allow time for clock to stabilize
    
    GPIO_PORTA_DIR_R |= 0xE0;   // PA5-PA7 as output (RS, E)
    GPIO_PORTA_DEN_R |= 0xE0;
    GPIO_PORTB_DIR_R = 0xFF;    // PB0-PB7 as output (Data)
    GPIO_PORTB_DEN_R = 0xFF;
    
    delay(20);                // Additional LCD power-up time
    
    // Extended initialization sequence
    LCD_WriteCommand(0x38);     // 8-bit mode, 2 lines, 5x7 font
    delay(5);
    LCD_WriteCommand(0x38);     // Repeat for stabilization
    delay(1);
    LCD_WriteCommand(0x38);     // Third time ensures reliability
    delay(1);
    
    LCD_WriteCommand(0x0C);     // Display on, cursor off
    LCD_WriteCommand(0x01);     // Clear display
    delay(2);                 // Clear display needs extra time
    LCD_WriteCommand(0x06);     // Entry mode: increment, no shift
}



void LCD_WriteData(uint8_t data) {
    GPIO_PORTA_DATA_R = 0x20;   // RS=1 (data), E=0
    GPIO_PORTB_DATA_R = data;   // Send data
    GPIO_PORTA_DATA_R |= 0x80;  // Pulse E high (PA7)
    delay(1);                 // ~1ms pulse width
    GPIO_PORTA_DATA_R &= ~0x80; // E low
    delay(1);                 // Short delay between writes
}

void LCD_String(char* str) {
    while (*str) {
        LCD_WriteData(*str++);
    }
}

void LCD_Clear(void) {
    LCD_WriteCommand(0x01);     // Clear display
    delay(3);                 // Clear needs extra time (up to 1.64ms)
}
