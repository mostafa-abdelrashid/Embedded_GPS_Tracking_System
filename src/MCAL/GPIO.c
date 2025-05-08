#include "../../Services/tm4c123gh6pm.h"
#include "../../Services/Bit_Utilities.h"
#include "../../Headers/MCAL/GPIO.h"

void initPortA(void){
	SET_BIT(SYSCTL_RCGCGPIO_R,0);
	while(GET_BIT(SYSCTL_PRGPIO_R,0) == 0);
	GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTA_CR_R = 0x03;
	GPIO_PORTA_AMSEL_R = 0x00;
	GPIO_PORTA_AFSEL_R = 0x03;
	GPIO_PORTA_DEN_R = 0x03;
	GPIO_PORTA_PCTL_R = 0x11;
}
void initPortB(void){	// could be used for LCD
	SET_BIT(SYSCTL_RCGCGPIO_R,1);
	while(GET_BIT(SYSCTL_PRGPIO_R,1) == 0);
	GPIO_PORTB_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTB_CR_R = 0xFF;
	GPIO_PORTB_AMSEL_R = 0x00;
	GPIO_PORTB_AFSEL_R = 0x00;
	GPIO_PORTB_DEN_R = 0xFF;
	GPIO_PORTB_PCTL_R = 0x00;
}
void initPortD(void){
    SET_BIT(SYSCTL_RCGCGPIO_R, 3);                     // Enable clock for Port D
    while (GET_BIT(SYSCTL_PRGPIO_R, 3) == 0);          // Wait for it to be ready
    
    GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;                 // Unlock PD7
    GPIO_PORTD_CR_R |= (1 << 7) | (1 << 6);            // Commit PD6 and PD7

    GPIO_PORTD_AFSEL_R |= (1 << 6) | (1 << 7);         // Enable alternate function on PD6, PD7
    GPIO_PORTD_PCTL_R &= ~0xFF000000;                  // Clear PCTL bits for PD6, PD7
    GPIO_PORTD_PCTL_R |= 0x11000000;                   // Set PCTL to UART2: PD6=U2Rx, PD7=U2Tx

    GPIO_PORTD_AMSEL_R &= ~((1 << 6) | (1 << 7));      // Disable analog mode
    GPIO_PORTD_DEN_R |= (1 << 6) | (1 << 7);           // Digital enable for PD6 and PD7
}

void initPortE(void){
	SET_BIT(SYSCTL_RCGCGPIO_R,4);
	while(GET_BIT(SYSCTL_PRGPIO_R,4) == 0);
	GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTE_CR_R = 0x30;
	GPIO_PORTE_AMSEL_R = 0x00;
	GPIO_PORTE_AFSEL_R = 0x30;
	GPIO_PORTE_DEN_R = 0x30;
	GPIO_PORTE_PCTL_R = 0x00110000;
}
void initPortF(void){
	SET_BIT(SYSCTL_RCGCGPIO_R,5);
	while(GET_BIT(SYSCTL_PRGPIO_R,5) == 0);
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTF_CR_R = 0x1F;
	GPIO_PORTF_AMSEL_R = 0x00;
	GPIO_PORTF_AFSEL_R = 0x00;
	GPIO_PORTF_DEN_R = 0x1F;
	GPIO_PORTF_PCTL_R = 0x00;
	SET(GPIO_PORTF_DIR_R,0x0E);
	CLR(GPIO_PORTF_DATA_R,0x0E); 
	GPIO_PORTF_PUR_R = 0x11;
}

	