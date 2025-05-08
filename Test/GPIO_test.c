/*#include "../Headers/MCAL/GPIO.h"
#include "../Services/tm4c123gh6pm.h"
#include <stdint.h>
#include "../Headers/MCAL/Systick.h" 
#include "../Headers/MCAL/UART.h"
  // For delay functions
// For delay functions
// For delay functions

// Helper function for visual feedback
void toggle_led(uint8_t port, uint8_t pin) {
    switch(port) {
        case 'F': GPIO_PORTF_DATA_R ^= (1<<pin); break;
        case 'B': GPIO_PORTB_DATA_R ^= (1<<pin); break;
        // Add other ports as needed
    }
    delay(500);  // 500ms delay
}

// Test GPIO Port F (LEDs and switches)
void test_gpio_portf(void) {
    // Initialize Port F
		uint8_t pin;
    initPortF();
    
    // Test LED outputs (PF1-PF3)
			
    for( pin = 1; pin <= 3; pin++) {
        GPIO_PORTF_DATA_R |= (1<<pin);  // Turn on
        delay(500);
        GPIO_PORTF_DATA_R &= ~(1<<pin); // Turn off
        delay(500);
    }
    
    // Test input switches (PF0, PF4)
    UART0_SendString("Press PF0 and PF4 switches:\r\n");
    while(1) {
        uint8_t sw1 = !(GPIO_PORTF_DATA_R & 0x10);  // PF4
        uint8_t sw2 = !(GPIO_PORTF_DATA_R & 0x01);  // PF0
        
        if(sw1) GPIO_PORTF_DATA_R |= (1<<2);  // Turn on PF2 (Blue) when PF4 pressed
        else    GPIO_PORTF_DATA_R &= ~(1<<2);
        
        if(sw2) GPIO_PORTF_DATA_R |= (1<<1);  // Turn on PF1 (Red) when PF0 pressed
        else    GPIO_PORTF_DATA_R &= ~(1<<1);
    }
}

// Test GPIO Port B (LCD data lines)
void test_gpio_portb(void) {
		uint8_t i;
    initPortB();
    
    // Walk through all 8 bits (PB0-PB7)
		
    for( i = 0; i < 8; i++) {
        GPIO_PORTB_DATA_R = (1<<i);  // Set single bit
        delay(200);
    }
    GPIO_PORTB_DATA_R = 0;  // Clear all
}

// Test GPIO Port A (UART alternate function)
void test_gpio_porta(void) {
    initPortA();
    // PA0-PA1 should be tested via UART
    UART0_SendString("Port A tested via UART0\r\n");
}

// Test GPIO Port D (UART2 and others)
void test_gpio_portd(void) {
    initPortD();
    // PD6-PD7 tested via UART2
    // Test other pins if needed
    GPIO_PORTD_DATA_R |= 0xC0;  // Set PD6-PD7
    delay(500);
    GPIO_PORTD_DATA_R &= ~0xC0;
}

// Test GPIO Port E (UART5)
void test_gpio_porte(void) {
    initPortE();
    // PE4-PE5 tested via UART5
    GPIO_PORTE_DATA_R |= 0x30;  // Set PE4-PE5
    delay(500);
    GPIO_PORTE_DATA_R &= ~0x30;
}

// Main GPIO test harness
void test_gpio(void) {
    UART0_Init();
    UART0_SendString("Starting GPIO Tests...\r\n");
    
    test_gpio_portf();  // Interactive test with LEDs/switches
    test_gpio_portb();  // Visual test (connect logic analyzer)
    test_gpio_porta();  // Verified via UART0
    test_gpio_portd();  // Verified via UART2
    test_gpio_porte();  // Verified via UART5
    
    UART0_SendString("All GPIO Tests Completed\r\n");
}*/