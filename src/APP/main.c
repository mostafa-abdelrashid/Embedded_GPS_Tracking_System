#include "../../Services/tm4c123gh6pm.h"
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
		
}

