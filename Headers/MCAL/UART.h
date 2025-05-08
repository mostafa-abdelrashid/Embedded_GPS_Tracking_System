#ifndef UART_H
#define UART_H
#include "tm4c123gh6pm.h"
#include <stdint.h>


void UART0_Init(void);
void UART0_SendChar(char data);
void UART0_SendString(char *pt);
char UART0_ReceiveChar(void);
void UART0_ReceiveString(char *command, uint32_t length);
void UART2_Init(void);
void UART2_SendChar(char data);
void UART2_SendString(char *pt);
char UART2_ReceiveChar(void);
void UART2_ReceiveString(char *command, uint32_t length);

#endif // UART_H
/*
#ifndef UART_H
#define UART_H

//UART 0(for pc comm),2(for gps comm) communicatiom functions
extern void UART0_SendChar(char data );
extern void UART0_SendString(char *str);
extern char UART0_ReceiveChar(void);
extern void UART0_ReceiveString(char* cmd, unsigned int length);
extern int UART0_isTxReady(void);

extern void UART2_SendChar(char data );
extern void UART2_SendString(char *str);
extern char UART2_ReceiveChar(void);
extern void UART2_ReceiveString(char* cmd, unsigned int length);

//UART5 n\for other peripheral but unused till now
extern void UART5_SendChar(char data );
extern void UART5_SendString(char *str);
extern char UART5_ReceiveChar(void);
extern void UART5_ReceiveString(char* cmd, unsigned int length);

//UART Initialization functions 
extern void UART0_Init(void);
extern void UART2_Init(void);
extern void UART5_Init(void);

//Identification for all UART modules
#define UART0   0
#define UART1   1
#define UART2   2
#define UART3   3
#define UART4   4
#define UART5   5
#define UART6   6
#define UART7   7

//Defining some useful constants

#define UART_PARITY_NONE        0
#define UART_PARITY_ODD         1
#define UART_PARITY_EVEN        2


#define UART_STOP_BIT_1			1
#define UART_STOP_BIT_2			2

#define UART_PORTA				0
#define UART_PORTB				1
#define UART_PORTC				2
#define UART_PORTD				3
#define UART_PORTE				4

#define UART0_PINS    0x03
#define UART2_PINS		0xC0
#define UART5_PINS		0x30
#define CR 0x0D  // "\r"
#define END 0x2A			// "*" 


#endif // UART_H*/