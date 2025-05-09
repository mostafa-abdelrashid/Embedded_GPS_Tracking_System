/*#include <stdint.h>
#include <string.h>
#include "tm4c123gh6pm.h"
#include "../Headers/MCAL/UART.h"
#include "../Headers/HAL/GPS.h"


int main() {
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
            char buffer[20];
            sprintf(buffer, "%.6f, %.6f", currentLat, currentLong);
            UART0_SendString(buffer);
            
            UART0_SendString("\r\n");
        }
        else {
            UART0_SendString("No valid GPS fix\r\n");
        }
        
        // Delay (~1 second)
        for(volatile int i = 0; i < 1000000; i++);
    }
}*/