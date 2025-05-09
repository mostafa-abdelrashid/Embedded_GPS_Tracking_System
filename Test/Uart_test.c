////////////////////////    TEST 3 for testing uart      ////////////////////
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

	

extern char GPS[100];
extern char GPS_Data[12][20];
extern float currentLat, currentLong;

int main() {
		volatile int i;
    // Initialize UARTs
    UART0_Init();  // For PuTTY output
    UART2_Init();  // For GPS input
    
    UART0_SendString("GPS Test Started\r\n");
    UART0_SendString("Waiting for satellite fix...\r\n");

    while(1) {
        // 1. Read GPS data (using your existing HAL function)
        GPS_read();
        
        // 2. Parse data (using your existing HAL function)
        GPS_ParseData();
        
        // 3. Display results via PuTTY
        if(strcmp(GPS_Data[1], "A") == 0) {  // Check if data is valid
            UART0_SendString("Valid Fix: ");
            
            // Latitude
            UART0_SendString("Lat: ");
            UART0_SendString(GPS_Data[2]);
            UART0_SendString(GPS_Data[3]);  // N/S
            
            // Longitude
            UART0_SendString(", Lon: ");
            UART0_SendString(GPS_Data[4]);
            UART0_SendString(GPS_Data[5]);  // E/W
            
            // Optional: Print timestamp
            UART0_SendString(", Time: ");
            UART0_SendString(GPS_Data[0]);
            
            UART0_SendString("\r\n");
        }
        else {
            UART0_SendString("No valid fix\r\n");
        }
        
        // Delay between readings (~1 second)
        for( i = 0; i < 1000000; i++);
    }
}
/////////////////////////  PREVIOUS TEST FOR TESTING UART    /////////////////////////

#define RED_LED 1
#define BLUE_LED 2
#define GREEN_LED 3
int main(void) {
		
	  char buffer[50];
		initPortF();
  
		TOG_BIT(GPIO_PORTF_DATA_R, BLUE_LED);	
		delay(10000);
    UART0_Init(); // Connects to PC
	  TOG_BIT(GPIO_PORTF_DATA_R, BLUE_LED);

     UART0_SendChar('B');	
    UART0_SendString("UART0 test: Enter text\r\n");
	

    }
*/
