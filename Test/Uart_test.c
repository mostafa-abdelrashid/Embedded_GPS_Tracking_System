/*#include "../Headers/MCAL/UART.h"
#include "../Services/tm4c123gh6pm.h"
#include <stdint.h>

void test_uart0(void) {
    // Initialize UART0
    UART0_Init();
    
    // Initialize LED (PF2) for visual feedback
    SYSCTL_RCGCGPIO_R |= (1<<5);
    while((SYSCTL_PRGPIO_R & (1<<5)) == 0);
    GPIO_PORTF_DIR_R |= (1<<2);
    GPIO_PORTF_DEN_R |= (1<<2);
    
    // Loopback test
    UART0_SendString("UART0 Test - Type characters:\r\n");
    
    while(1) {
        char c = UART0_ReceiveChar();
        UART0_SendChar(c);  // Echo back
        
        // Toggle LED on each received character
        GPIO_PORTF_DATA_R ^= (1<<2);
    }
}

void test_uart2(void) {
    // Initialize UART2 (GPS)
	    char buffer[100];
    UART2_Init();
    
    // Test NMEA sentence reception

    UART0_SendString("Waiting for GPS data...\r\n");
    
    while(1) {
        UART2_ReceiveString(buffer, sizeof(buffer));
        UART0_SendString("Received: ");
        UART0_SendString(buffer);
        UART0_SendString("\r\n");
    }
}*/