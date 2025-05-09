

#include "../../Headers/Mcal/UART.h"
#include <stdio.h>
#include "../../Services/tm4c123gh6pm.h"
#include "../../Services/Bit_Utilities.h"
#include "../../Headers/Mcal/GPIO.h"
#include "../../Headers/Mcal/Systick.h"


void UART0_Init(void) {
	
    SYSCTL_RCGCUART_R |= 0x01;  // Enable UART0
    SYSCTL_RCGCGPIO_R |= 0x01;  // Enable PORTA (UART0 is on PA0, PA1)

    while ((SYSCTL_PRUART_R & 0x01) == 0); // Wait until UART0 is ready
    while ((SYSCTL_PRGPIO_R & 0x01) == 0); // Wait until PORTA is ready

    UART0_CTL_R &= ~0x01;       // Disable UART0

    UART0_IBRD_R = 104;         // Integer part of BRD (9600 baud, 16MHz)
    UART0_FBRD_R = 11;          // Fractional part

    UART0_LCRH_R = 0x70;        // 8-bit, no parity, 1-stop, FIFOs enabled
    UART0_CTL_R = 0x301;        // Enable UART0, TXE, RXE

    GPIO_PORTA_AFSEL_R |= 0x03; // Enable alt function on PA0, PA1
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & ~0xFF) + 0x11; // UART
    GPIO_PORTA_DEN_R |= 0x03;   // Digital on PA0, PA1
    GPIO_PORTA_AMSEL_R &= ~0x03;// Disable analog on PA0, PA1
	  delay(100);                 //delay for peripheral clock to stabalize 
}

void UART0_WaitForTxReady(void) {
    while ((UART0_FR_R & 0x20));  // Wait until TX FIFO is not full
}
void UART0_SendChar(char data) {
		UART0_WaitForTxReady();    // Wait until TX FIFO not full
    UART0_DR_R = data; 
}

void UART0_SendString(char *pt) {
    while(*pt) {
        UART0_SendChar(*pt);
        pt++;
    }
}

char UART0_ReceiveChar (){
		while ((UART0_FR_R & 0x10));
	return (char)UART0_DR_R;
}


void UART0_ReceiveString(char *buffer, uint32_t max_len) {
    uint32_t i = 0;
    char c;
    
    while(i < max_len - 1) {
        c = UART0_ReceiveChar();
        
        if(c == '\r' || c == '\n') { // Handle both CR and LF
            buffer[i] = '\0'; // Null-terminate
            return;
        }
        // Remove this line to disable echo from MCU:
        // UART0_SendChar(c); // (PuTTY already echoes locally)
        buffer[i++] = c;
    }
    buffer[i] = '\0'; // Safety termination
}



// Initialize UART2 for GPS on Port D (PD6=RX, PD7=TX)


void UART2_WaitForTxReady(void) {
    while ((UART2_FR_R & 0x20));  // Wait until TX FIFO is not full
}

void UART2_SendChar(char data) {
    UART2_WaitForTxReady();       // Wait until TX FIFO not full
    UART2_DR_R = data;
}

void UART2_SendString(char *pt) {
    while(*pt) {
        UART2_SendChar(*pt);
        pt++;
    }
}

void UART2_Init(void) {
    SYSCTL_RCGCUART_R |= 0x04;      // Enable UART2 clock
    SYSCTL_RCGCGPIO_R |= 0x08;      // Enable Port D clock
    while ((SYSCTL_PRUART_R & 0x04) == 0); // Wait for UART2
    while ((SYSCTL_PRGPIO_R & 0x08) == 0); // Wait for Port D

    UART2_CTL_R &= ~0x01;           // Disable UART2
    UART2_IBRD_R = 104;             // 9600 baud @16MHz
    UART2_FBRD_R = 11;
    UART2_LCRH_R = 0x70;            // 8-bit, FIFO enabled
    GPIO_PORTD_AFSEL_R |= 0xC0;     // PD6+PD7 as UART
    GPIO_PORTD_PCTL_R |= 0x11000000;
    GPIO_PORTD_DEN_R |= 0xC0;       // Digital enable
    UART2_CTL_R |= 0x301;           // Enable UART2 + TX/RX
}

char UART2_ReceiveChar(void) {
    while (UART2_FR_R & 0x10);      // Wait for RX FIFO data
    return (char)(UART2_DR_R & 0xFF);
}

void UART2_ReceiveString(char *buf, uint32_t max_len) {
    uint32_t i = 0;
    char c;
    while (i < max_len - 1) {
        c = UART2_ReceiveChar();
        if (c == '\r' || c == '\n') break;
        buf[i++] = c;
    }
    buf[i] = '\0';  // Null-terminate
}
//////////////////////////Some of the previous approaches /////////////////

/*
#include "../../Headers/Mcal/UART.h"
#include <stdio.h>
#include "../../Services/tm4c123gh6pm.h"
#include "../../Services/Bit_Utilities.h"
#include "../../Headers/Mcal/GPIO.h"
void UART0_Init (void){
	SYSCTL_RCGCUART_R |= 0x0001; 	//activate UART0
	while((SYSCTL_PRUART_R & 0x00000001) == 0);
	SYSCTL_RCGCGPIO_R |= 0x0001;  //activate portA clk
	while((SYSCTL_PRGPIO_R & 0x01) == 0);
	UART0_CTL_R &= ~0x0001;				//disable UART
	UART0_IBRD_R = 0x68;
	UART0_FBRD_R = 0xB;
	UART0_LCRH_R = 0x070;					//8-bits Data + enable FIFO
	UART0_CTL_R = 0x0301;					//activate RXE, TXE & UART
	GPIO_PORTA_AFSEL_R |= 0x03; 	//enable alternate function PA0 & PA1
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011;
	GPIO_PORTA_DEN_R |= 0x03;			//enable digtal I/O 
	GPIO_PORTA_AMSEL_R &= ~0x03;	//disable analog I/O

	*/
 /*SYSCTL_RCGCGPIO_R |= 0x01;       // Enable clock for Port A
    while((SYSCTL_PRGPIO_R & 0x01) == 0) {};  // Wait for clock to be ready

    SYSCTL_RCGCUART_R |= 0x01;       // Enable clock for UART0
    while((SYSCTL_PRUART_R & 0x01) == 0) {};  // Wait for clock to be ready

    GPIO_PORTA_LOCK_R = 0x4C4F434B;  // Unlock Port A
    GPIO_PORTA_CR_R = 0x03;          // Commit changes to PA0-PA1

    GPIO_PORTA_DEN_R = 0x03;         // Enable digital function for PA0-PA1
    GPIO_PORTA_DIR_R &= ~0x03;       // Set PA0-PA1 as input/output as required by UART

    GPIO_PORTA_AMSEL_R = 0x00;       // Disable analog function
    GPIO_PORTA_PCTL_R = 0x00000011;  // Set PCTL for PA0-PA1 as UART (U0RX, U0TX)
    GPIO_PORTA_AFSEL_R |= 0x03;      // Enable alternate function for PA0-PA1 (UART)

    UART0_CTL_R = 0;                 // Disable UART0 for configuration
    UART0_IBRD_R = 104;              // Integer part of baud rate divisor (9600 baud with 16 MHz clock)
    UART0_FBRD_R = 11;               // Fractional part of baud rate divisor
    UART0_LCRH_R = 0x70;             // 8-bit, no parity, 1 stop bit, FIFOs enabled
    UART0_CTL_R = 0x301;  }


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

 
void UART0_SendString(char *str){
    while(*str != '\0'){ // Loop until null terminator is reached
        UART0_SendChar(*str); // Send each character
        str++; // Move to the next character
    }
}

void UART0_SendChar(char data){
    while(UART0_isTxReady() == 0); // Wait for transmit FIFO to be not full
    UART0_DR_R = data; // Send character to UART0 data register
}

int  UART0_isTxReady(void){
    return (UART0_FR_R & 0x20) == 0; // Check if TXFF is 0 (transmit FIFO not full)
}

void UART0_SendChar(char data){
    while(GET_BIT(UART0_FR_R,5)); // Wait while TX FIFO full
    UART0_DR_R=data;
}*/
/*
void UART0_SendString(char* str){
    while(*str){
        UART0_SendChar(*str);
        str++;
    }
}*/

// UART0 receive string and char functions (for debugging through PC terminal)
/*char UART0_ReceiveChar(){ 
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
*/

