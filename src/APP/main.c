
#include "../../Services/tm4c123gh6pm.h"
#include "../../Services/Bit_Utilities.h"
#include "../../Headers/MCAL/UART.h"
#include "../../Headers/MCAL/Systick.h"
#include "../../Headers/MCAL/GPIO.h"
#include "../../Headers/MCAL/EEPROM.h"
#include "../../Headers/HAL/GPS.h"
#include "../../Headers/HAL/Landmarks.h"
#include "../../Headers/HAL/LCD.h"
#include "../../Headers/HAL/LED.h"
#include "../../Headers/APP/APP.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// Global variables
double currentDistance;
char uartBuffer[60];
char lcdBuffer[20];
double minDistance = 999999.0;
const char* nearestLandmark = "Unknown";

int main(void) {
	int i;
    // Initialize hardware
    LCD_Init();
    UART0_Init();  // For PuTTY
    UART2_Init();  // For GPS
    
    // Test GPS read
    GPS_read();
    GPS_ParseData();
    
    UART0_SendString("Navigation System Started\r\n");

    while(1) {
        // Get GPS data
        GPS_read();
        GPS_ParseData();

        // Reset tracking variables
        minDistance = 999999.0;
        nearestLandmark = "Unknown";
        
        // Check for valid GPS fix
        if(strcmp(GPS_Data[1], "A") != 0) {
            LCD_Clear();
            LCD_String("No GPS Fix");
            UART0_SendString("Waiting for GPS fix...\r\n");
            delay(1000);
            continue;
        }

        // Find nearest landmark
        for(i = 0; i < LANDMARK_COUNT; i++) {
            currentDistance = GET_Distance(
                currentLat, 
                currentLong,
                presetLandmarks[i].latitude, 
                presetLandmarks[i].longitude);
            
            if(currentDistance < minDistance) {
                minDistance = currentDistance;
                nearestLandmark = presetLandmarks[i].name;
            }
        }
        
        // Display on LCD
        snprintf(lcdBuffer, sizeof(lcdBuffer), "%-16s", nearestLandmark);
        LCD_Clear();
        LCD_String(lcdBuffer);
        
        snprintf(lcdBuffer, sizeof(lcdBuffer), "%.0fm", minDistance);
        LCD_String(lcdBuffer);
        
        // Send to UART
        snprintf(uartBuffer, sizeof(uartBuffer),
            "Nearest: %s\r\n"
            "Distance: %.0f meters\r\n"
            "Position: %.6f, %.6f\r\n",
            nearestLandmark, 
            minDistance, 
            currentLat, 
            currentLong);
        UART0_SendString(uartBuffer);
        
        delay(300); // Update every 300ms
    }
}

/*
int main() {
	volatile int i;
	char buffer[20];
    UART0_Init();  // For PuTTY output
    UART2_Init();  // For GPS (assuming this exists)
    
    UART0_SendString("GPS Test Started\r\n");

    while(1) {
        GPS_read();          // Uses UART2 internally
        GPS_ParseData();     // Processes into global variables
        
        // Access the global variables declared in GPS.h
        if(strcmp(GPS_Data[1], "A") == 0) {  // Valid fix
            UART0_SendString("Lat: ");
            UART0_SendString(GPS_Data[2]);
            UART0_SendString(GPS_Data[3]);  // N/S
            
            UART0_SendString(", Lon: ");
            UART0_SendString(GPS_Data[4]);
            UART0_SendString(GPS_Data[5]);  // E/W
            
            // You can also use the float variables:
            UART0_SendString("\r\nFloat values: ");
            
            sprintf(buffer, "%.6f, %.6f", currentLat, currentLong);
            UART0_SendString(buffer);
            
            UART0_SendString("\r\n");
        }
        else {
            UART0_SendString("No valid GPS fix\r\n");
        }
        
        // Delay (~1 second)
        delay(1000);
    }
}
*/
