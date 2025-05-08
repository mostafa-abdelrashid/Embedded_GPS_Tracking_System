
///////////////////////    TEST 5 FOR TESTING all DRIVERS     ////////////////////
#include "../../Headers/MCAL/Systick.h"
#include "../../Headers/MCAL/EEPROM.h"
#include "../../Headers/MCAL/UART.h"
#include "../../Headers/MCAL/GPIO.h"
#include "../../Services/tm4c123gh6pm.h"
#include "../../Test/Uart_test.c"
#include "../../Test/GPIO_test.c"
#include "../../Test/Eeprom_test.c"
#include "../../Test/Systick_test.c"
#include "../../Services/Bit_Utilities.h"
#include "../../Headers/HAL/LCD.h"
#include<stdint.h>



/*void PortF_Init(void){
    SYSCTL_RCGCGPIO_R |= 0x20;            // Enable clock for Port F
    while ((SYSCTL_RCGCGPIO_R & 0x20) == 0);  // Wait for clock to be ready
    GPIO_PORTF_DIR_R |= RED_LED;         // Set PF1 as output
    GPIO_PORTF_DEN_R |= RED_LED;         // Enable digital function on PF1
}

int main(void){
    PortF_Init();        // Initialize PF1
    Systick_Init();      // Initialize SysTick

    while(1){
        TOG_BIT(GPIO_PORTF_DATA_R, RED_LED);  // Toggle PF1
        delay(500);                           // Delay 500 ms (assumes 16 MHz clock)
    }
}*/
    // Initialize system components
   /* Systick_Init();       // Required for delay functions
    UART0_Init();         // For debug output
    initPortF();          // For status LEDs
    
    // Test sequence with visual feedback
    GPIO_PORTF_DATA_R |= (1<<1);  // Turn on Red LED (testing started)
    
    UART0_SendString("\r\n===== Starting Driver Tests =====\r\n");
    
    // 1. Test GPIO first (basic I/O functionality)
    UART0_SendString("[1/4] Testing GPIO...");
    test_gpio();
    GPIO_PORTF_DATA_R |= (1<<2);  // Blue LED on (GPIO test passed)
    UART0_SendString("OK\r\n");
    
    // 2. Test SysTick (timing critical)
    UART0_SendString("[2/4] Testing SysTick...");
    test_systick();              // Will toggle LED
    UART0_SendString("OK\r\n");
    
    // 3. Test EEPROM (non-volatile storage)
    UART0_SendString("[3/4] Testing EEPROM...");
    if(test_eeprom() == 0) {     // Returns 0 on failure
        GPIO_PORTF_DATA_R |= (1<<1);  // Red LED on (error)
        UART0_SendString("FAILED!\r\n");
        while(1);  // Halt on critical failure
    }
    UART0_SendString("OK\r\n");
    
    // 4. Test UARTs (communication)
    UART0_SendString("[4/4] Testing UARTs...\r\n");
    test_uart0();  // Interactive test (connect to PC terminal)
    test_uart2();  // GPS interface test
    
    // All tests passed
    GPIO_PORTF_DATA_R = (1<<3);  // Green LED on (all tests passed)
    UART0_SendString("\r\n==== ALL TESTS PASSED ====\r\n");
    
    while(1) {
        // Blink all LEDs to show system is alive
        GPIO_PORTF_DATA_R ^= 0x0E;  // Toggle all LEDs
        delay(1000);
    }*/
	
///////////////////////// TEST 4 for testing LCD              /////////////////
/*
int main(void) {
    Systick_Init();
    initLCD();

    LCD_string("Tiva C LCD Test", 15);

    while (1) {
        // Stay here
    }
}*/
////////////////////////    TEST 3 for testing uart      ////////////////////
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
	
     UART0_SendChar('c');	
    //UART0_SendString("UART0 test: Enter text\r\n");
	

    }

////////////////////////    TEST 2 for testing eeprom   ////////////////////
/*
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
}*/
////////////////////////   TEST 1 FOR TOGGLING 3 LEDS and testing systick    ////////////////////
/*#include <stdint.h>



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




/*#include "../../Services/tm4c123gh6pm.h"
#include "../../Services/Bit_Utilities.h"
#include "../../Headers/MCAL/UART.h"
#include "../../Headers/MCAL/Systick.h"
#include "../../Headers/MCAL/GPIO.h"
#include "../../Headers/MCAL/EEPROM.h"
#include "../../Headers/HAL/GPS.h"
#include "../../Headers/HAL/Landmarks.h"
#include "../../Headers/APP/APP.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>

int flag;
float minDistance;
float distance;
unsigned char firstDistance = 0;
Landmark landmarks[MAX_LANDMARKS];
Landmark* nearestLandmark;

int main() {
    Systick_Init();
		initPortA();
		initPortD();
		UART0_Init();
		UART2_Init();
		flag = EEPROM_Init();
	  // if recovery failed return an error message and terminate the program
		if(flag == 0){
			UART0_SendString("EEPROM Failed");
			return 0;
		}
		Landmarks_EEPROM_ReadAll(landmarks);
    while(1) {
			GPS_read();
			GPS_ParseData();
			// in the beginning default the first location in the landmarks array as the nearest location for comparisons;
			if(firstDistance == 0){
				minDistance = GET_Distance(currentLong,currentLat,landmarks[0].longitude,landmarks[0].latitude);
				nearestLandmark = &landmarks[0];
				firstDistance = 1;
			}
			else{
				int i;
				for(i = 0; i < MAX_LANDMARKS; i++){
					distance = GET_Distance(currentLong,currentLat,landmarks[i].longitude,landmarks[i].latitude);
					if(distance < minDistance){
						minDistance = distance;
						nearestLandmark = &landmarks[i];
					}
				}
				if(minDistance <= 10.0f) UART0_SendString(nearestLandmark->name); // Name appears only if near location (about 10 meters radius)
			}
    }
		
}*/

