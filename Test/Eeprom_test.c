////////////////////////    TEST 2 for testing eeprom   ////////////////////
/*#include "../Services/tm4c123gh6pm.h"
#include "../Services/Bit_Utilities.h"
#include "../Headers/MCAL/UART.h"
#include "../Headers/MCAL/Systick.h"
#include "../Headers/MCAL/GPIO.h"
#include "../Headers/MCAL/EEPROM.h"
#include "../Headers/HAL/GPS.h"
#include "../Headers/HAL/Landmarks.h"
#include "../Headers/HAL/LCD.h"
#include "../Headers/HAL/LED.h"
#include "../Headers/APP/APP.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


#define RED_LED 1
#define BLUE_LED 2
#define GREEN_LED 3
#define EEPROM_ADDR 0x00

int main(void) {
    int testValue = 12345;
    int readValue = 0;

    union {
        int i;
        float f;
    } converter;

    Systick_Init();
    initPortF();
    EEPROM_Init();

    converter.i = testValue;
    eeprom_write(converter.f, EEPROM_ADDR);
    TOG_BIT(GPIO_PORTF_DATA_R, BLUE_LED);  // Indicate write complete
    delay(10000);
		TOG_BIT(GPIO_PORTF_DATA_R, BLUE_LED);
			delay(10000);
    converter.f = eeprom_read(EEPROM_ADDR);
    readValue = converter.i;

    while (1) {
        if (readValue == testValue) {
					    

            TOG_BIT(GPIO_PORTF_DATA_R, GREEN_LED);
          
        } else {
				
            TOG_BIT(GPIO_PORTF_DATA_R, RED_LED);
       
        }
        delay(50000);
    }
}
*/