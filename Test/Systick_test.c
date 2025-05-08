/*#include "../Headers/MCAL/Systick.h"
#include "../Services/tm4c123gh6pm.h"
#include <stdint.h>

void test_systick(void) {
    // Initialize LED (PF1)
    SYSCTL_RCGCGPIO_R |= (1<<5);          // Enable Port F clock
    while((SYSCTL_PRGPIO_R & (1<<5)) == 0);
    GPIO_PORTF_DIR_R |= (1<<1);           // PF1 = output
    GPIO_PORTF_DEN_R |= (1<<1);           // Digital enable
    
    // Initialize SysTick
    Systick_Init();
    
    // Test delay
    while(1) {
        GPIO_PORTF_DATA_R ^= (1<<1);      // Toggle LED
        delay(1000);                      // 1-second delay
    }
}*/