
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

// GPS Variables (extern if they're in GPS.h)
extern char GPS[100];
extern char GPS_Data[12][20];
extern float currentLat, currentLong;

int main() 
{
		const Landmark* nearest;
    float minDist;
    unsigned int i;
    char* landmarkName;
    UART0_Init();  // For PuTTY
    UART2_Init();  // For GPS
    LCD_Init();
    


    
    while(1) 
    {
        //  Getting GPS data
        GPS_read();
        GPS_ParseData();
        
        //  Finding nearest landmark
        nearest = &presetLandmarks[0];
        minDist = GET_Distance(currentLong, currentLat, 
                             nearest->longitude, nearest->latitude);
        
        for(i = 1; i < MAX_LANDMARKS; i++) 
        {
            float dist = GET_Distance(currentLong, currentLat,
                                    presetLandmarks[i].longitude,
                                    presetLandmarks[i].latitude);
            if(dist < minDist) 
            {
                minDist = dist;
                nearest = &presetLandmarks[i];
            }
        }
        
        // 3. Display nearest landmark name only
        landmarkName = (char*)nearest->name; 
        
        LCD_Clear();
        LCD_String(landmarkName);
				
				/// for testing in putty 
        UART0_SendString(landmarkName);
        UART0_SendString("\r\n");
        
        delay(1000); // Update every second
    }
}
//////////////////////  previous approach    //////////////////////////////////////////////////
/*
#include "../../Services/tm4c123gh6pm.h"
#include "../../Services/Bit_Utilities.h"
#include "../../Headers/MCAL/UART.h"
#include "../../Headers/MCAL/Systick.h"
#include "../../Headers/MCAL/GPIO.h"
#include "../../Headers/MCAL/EEPROM.h"
#include "../../Headers/HAL/GPS.h"
#include "../../Headers/HAL/Landmarks.h"
#include "../../Headers/HAL/LCD.h"
#include "../../Headers/APP/APP.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>

float minDistance;
float distance;
unsigned char firstDistance = 0;
const Landmark* nearestLandmark;
int i;

int main() {
    Systick_Init();
		initPortA();
		initPortB();
		LCD_Init();
		UART0_Init();
		UART2_Init();
		
    while(1) {
			GPS_read();
			GPS_ParseData();
			// in the beginning default the first location in the landmarks array as the nearest location for comparisons;
			if(firstDistance == 0){
				minDistance = GET_Distance(currentLong,currentLat,presetLandmarks[0].longitude,presetLandmarks[0].latitude);
				nearestLandmark = &presetLandmarks[0];
				firstDistance = 1;
			}
			for(i = 0; i < MAX_LANDMARKS; i++){
				distance = GET_Distance(currentLong,currentLat,presetLandmarks[i].longitude,presetLandmarks[i].latitude);
				if(distance < minDistance){
					minDistance = distance;
					nearestLandmark = &presetLandmarks[i];
				}
			}
			if(minDistance <= 10.0f){
				UART0_SendString((char*)nearestLandmark->name); // Name appears only if near location (about 10 meters radius)
				LCD_Clear();
				LCD_WriteData(' ');              // Write the leading space
				LCD_String((char*)nearestLandmark->name);	
			} 
			delay(500);	
    }
		
}*/
////testing gps parse data 
/*int main() {
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
