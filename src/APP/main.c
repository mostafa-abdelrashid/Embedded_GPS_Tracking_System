#include "tm4c123gh6pm.h"

void delay2(unsigned int ms) {
	volatile unsigned int i;
    for(i=0; i<ms*1000; i++);
}

int main() {
    // 1. Enable clocks
    SYSCTL->RCGCGPIO |= 0x01;  // Port A
    SYSCTL->RCGCUART |= 0x01;   // UART0
    delay2(2);
    
    // 2. Minimal UART0 setup
    GPIOA->AFSEL |= 0x03;       // PA0/PA1 as alternate function
    GPIOA->PCTL = (GPIOA->PCTL & ~0xFF) | 0x11;  // UART mode
    GPIOA->DEN |= 0x03;         // Digital enable
    
    UART0->CTL = 0;             // Disable UART
    UART0->IBRD = 104;          // 9600 baud @16MHz
    UART0->FBRD = 11;
    UART0->LCRH = 0x60;         // 8N1
    UART0->CTL = 0x301;         // Enable UART
    
    while(1) {
        if(UART0->FR & 0x10) {  // RXFE bit (data available)
            char c = UART0->DR;
            UART0->DR = c;       // Echo back
        }
    }
		
}

