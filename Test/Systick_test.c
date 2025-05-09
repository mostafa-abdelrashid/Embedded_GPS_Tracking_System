////////////////////////   TEST 1 FOR TOGGLING 3 LEDS and testing systick    ////////////////////
/*#include "../Services/tm4c123gh6pm.h"
#include "../Headers/MCAL/Systick.h"






int main(void) {
    // Enable Port F clock
    SYSCTL_RCGCGPIO_R |= 0x20;
    while ((SYSCTL_PRGPIO_R & 0x20) == 0);
    
    // Configure PF1 (Red), PF2 (Blue), PF3 (Green)
    GPIO_PORTF_DIR_R |= 0x0E;
    GPIO_PORTF_DEN_R |= 0x0E;
    
    while (1) {
        GPIO_PORTF_DATA_R ^= 0x02;  // Toggle Red
        delay(1000);
        GPIO_PORTF_DATA_R ^= 0x04;  // Toggle Blue
        delay(2000);
        GPIO_PORTF_DATA_R ^= 0x08;  // Toggle Green
        delay(5000);
    }
}
*/

