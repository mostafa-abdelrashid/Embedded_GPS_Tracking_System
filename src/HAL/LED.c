#include "../../Services/tm4c123gh6pm.h"
#include "../../Headers/HAL/LED.h"

void LED_Init(void) {
    SYSCTL_RCGCGPIO_R |= 0x20;
    while ((SYSCTL_PRGPIO_R & 0x20) == 0);
    GPIO_PORTF_DIR_R |= 0x02;
    GPIO_PORTF_DEN_R |= 0x02;
}

void RED(void) {
    GPIO_PORTF_DATA_R ^= 0x02;
}
void BLUE(void) {
    GPIO_PORTF_DATA_R ^= 0x04;
}
void GREEN(void) {
    GPIO_PORTF_DATA_R ^= 0x08;
}