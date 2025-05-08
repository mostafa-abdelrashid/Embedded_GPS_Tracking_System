
#include "../../Headers/Mcal/UART.h"
#include <stdio.h>
#include "../../Services/tm4c123gh6pm.h"
#include "../../Services/Bit_Utilities.h"



void UART0_Init(void){
	
	SYSCTL_RCGCUART_R |= 0x01;
	SYSCTL_RCGCGPIO_R |= 0x01;
	while ((SYSCTL_PRUART_R & 0x01) == 0) {};
	while ((SYSCTL_PRGPIO_R & 0x01) == 0) {};
	UART0_CTL_R = ~0x01; // Clear UARTEN bit (bit 0)
	UART0_IBRD_R = 104; // Integer part
  UART0_FBRD_R = 11; // Fractional part (0.1667 × 64 + 0.5 ˜ 11)
	UART0_LCRH_R = 0x70; // 8-bit word length (WLEN=11), enable FIFO (FEN=1)
	// 6. Enable UART, TX, and RX
	UART0_CTL_R = 0x301; // Enable UARTEN (bit 0), TXE (bit 8), RXE (bit 9)
	// 7. Configure GPIO pins for UART
	GPIO_PORTA_AFSEL_R |= 0x03; // Enable alt function on PA0, PA1
	GPIO_PORTA_PCTL_R |= 0x00000011; // Configure PA0 and PA1 for UART
	GPIO_PORTA_DEN_R |= 0x03; // Digital enable on PA0, PA1
	GPIO_PORTA_AMSEL_R &= ~0x03; // Disable analog on PA0, PA1
    /*SET_BIT(SYSCTL_RCGCUART_R, UART0);          // Enable UART0 clock
    while(GET_BIT(SYSCTL_PRUART_R, UART0) == 0);

    SET_BIT(SYSCTL_RCGCGPIO_R, UART_PORTA);     // Enable GPIOA clock
    while(GET_BIT(SYSCTL_PRGPIO_R, UART_PORTA) == 0);

    CLR_BIT(UART0_CTL_R, 0);                    // Disable UART0

    UART0_IBRD_R = 0x68;                        // Integer part: 104
    UART0_FBRD_R = 0x0B;                        // Fractional: 11
		//UART0_FBRD_R =34;
		//UART0_IBRD_R =325;
	  UART0_CC_R = 0x0;                           // Use system clock (16 MHz)
    UART0_LCRH_R = 0x70;                        // 8-bit, no parity, 1 stop

    // GPIO config
    SET(GPIO_PORTA_AFSEL_R, UART0_PINS);        // Enable alt func PA0, PA1
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) | 0x00000011;
    SET(GPIO_PORTA_DEN_R, UART0_PINS);          // Digital enable
    CLR(GPIO_PORTA_AMSEL_R, UART0_PINS);        // Disable analog

    UART0_CTL_R = 0x301; */                       // Enable UART0, TXE, RXE
}

// UART2_initialization 
void UART2_Init(void){
    SET(SYSCTL_RCGCUART_R,UART2); // activate UART2 clock
    while(GET_BIT(SYSCTL_PRUART_R,UART2)==0);
    SET(SYSCTL_RCGCGPIO_R,UART_PORTD);  // activate PORTD GPIO clock
    while(GET_BIT(SYSCTL_PRGPIO_R,UART_PORTD)==0);
    CLR_BIT(UART2_CTL_R,0); // disable UART2
    UART2_IBRD_R=0x68;      // Fixed to 16MHz clock (was 80MHz)
    UART2_FBRD_R=0xB;       // Fixed to match 16MHz
    UART2_LCRH_R=0x70;      // 8-bits data & enable fifo
    UART2_CTL_R=0x301;      // enable UART2, RX, TX
    SET(GPIO_PORTD_AFSEL_R,UART2_PINS); // alt function PD7,PD6
    GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0x00FFFFFF) + 0x11000000;
    SET(GPIO_PORTD_DEN_R,UART2_PINS); // digital enable D6,D7
    CLR(GPIO_PORTD_AMSEL_R,UART2_PINS); // disable analog D6,D7
}

// UART5_initialization 
void UART5_Init(void){
    SET(SYSCTL_RCGCUART_R,UART5); // activate UART5 clock
    while(GET_BIT(SYSCTL_PRUART_R,UART5)==0);
    SET(SYSCTL_RCGCGPIO_R,UART_PORTE);  // activate PORTE GPIO clock
    while(GET_BIT(SYSCTL_PRGPIO_R,UART_PORTE)==0);
    CLR_BIT(UART5_CTL_R,0); // disable UART5
    UART5_IBRD_R=0x68;      // 104 for 9600 baud @16MHz
    UART5_FBRD_R=0xB;       // 11
    UART5_LCRH_R=0x70;      // 8-bits data & enable fifo
    UART5_CTL_R=0x301;      // enable UART5, RX, TX
    SET(GPIO_PORTE_AFSEL_R,UART5_PINS); 
    GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & 0xFF00FFFF) + 0x00110000;
    SET(GPIO_PORTE_DEN_R,UART5_PINS); 
    CLR(GPIO_PORTE_AMSEL_R,UART5_PINS); 
}

// UART0 send char and string functions
void UART0_SendChar(char data){
    while(GET_BIT(UART0_FR_R,5)); // Wait while TX FIFO full
    UART0_DR_R=data;
}

void UART0_SendString(char* str){
    while(*str){
        UART0_SendChar(*str);
        str++;
    }
}

// UART0 receive string and char functions (for debugging through PC terminal)
char UART0_ReceiveChar(){ 
    while(GET_BIT(UART0_FR_R,4)); // Wait while RX FIFO empty
    return (char)UART0_DR_R;
}

void UART0_ReceiveString(char* ptr, unsigned int length){  
    char character;
	int i;
    for( i=0;i<length;i++){
        character = UART0_ReceiveChar();
        if(character != CR){
            ptr[i]=character;
            UART0_SendChar(ptr[i]);
        }
        else if(character == CR || i==length){    
            break;
        }                    
    }
} 

// UART2 receive string and char functions (for communication with GPS)
char UART2_ReceiveChar(){  
    while(GET_BIT(UART2_FR_R,4)); // Wait while RX FIFO empty
    return (char)UART2_DR_R;
}

void UART2_ReceiveString(char* ptr, unsigned int length){  
    char character;
	int i;
    for( i=0;i<length;i++){
        character = UART2_ReceiveChar();
        if(character != END){
            ptr[i]=character;
        }
        else if(character == END || i==length){    
            break;
        }                    
    }
}

// UART5 receive string and char functions
char UART5_ReceiveChar(){  
    while(GET_BIT(UART5_FR_R,4)); // Wait while RX FIFO empty
    return (char)UART5_DR_R;
}

void UART5_ReceiveString(char* ptr, unsigned int length){  //
    char character;
	int i;
    for( i=0;i<length;i++){
        character = UART5_ReceiveChar();
        if(character != END){
            ptr[i]=character;
       
        }
        else if(character == END || i==length){    
            break;
        }                    
    }
}

// UART5 send functions 
void UART5_SendChar(char data){
    while(GET_BIT(UART5_FR_R,5));
    UART5_DR_R=data;  
}

void UART5_SendString(char* ptr){
    while(*ptr){
        UART5_SendChar(*ptr);
        ptr++;
    }
}

