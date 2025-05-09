#include <string.h>
#include <math.h>
#include <stdlib.h>
///MCAL///
#include "../../Headers/MCAL/UART.h"
#include "../../Headers/MCAL/Systick.h"
#include "../../Headers/MCAL/EEPROM.h"
#include "../../Headers/MCAL/GPIO.h"
///HAL///
#include "../../Headers/HAL/GPS.h"

char GPS[100];
char GPS_logName[] = "$GPRMC,";
char* token;
char GPS_Data[12][20];
float currentLat, currentLong;

void GPS_read(void) {
    char flag = 1;
    char receivedChar;
    char i;
    char counter = 0;

    // Check if the received log is $GPRMC
    do {
        flag = 1;
        for (i = 0; i < 7; i++) {
            if (UART2_ReceiveChar() != GPS_logName[i]) {
                flag = 0;
                break;
            }
        }
    } while (flag == 0);

    // Clear the GPS string
    strcpy(GPS, "");

    // Receive GPS data until '*'
    do {
        receivedChar = UART2_ReceiveChar();
        if (counter < sizeof(GPS) - 1) {
            GPS[counter++] = receivedChar;
        }
    } while (receivedChar != '*');

    GPS[counter] = '\0'; // terminate the string
}
/*void GPS_ParseData(void) {
		float lat_deg,lat_min,lon_deg,lon_min;
    char args = 0;
    token = strtok(GPS, ",");
    
    while (token != NULL && args < 12) {
        strcpy(GPS_Data[args++], token);
        token = strtok(NULL, ",");
    }

    // Only parse if there is a GPS fix (GPS_Data[1] == "A")
    if (args > 1 && strcmp(GPS_Data[1], "A") == 0) {
        // Parse latitude 
        lat_deg = atof(GPS_Data[2]) / 100.0f;
        lat_min = atof(GPS_Data[2]) - floorf(lat_deg)*100.0f;
        currentLat = floorf(lat_deg) + (lat_min / 60.0f);
        if (GPS_Data[3][0] == 'S') currentLat = -currentLat;

        // Parse longitude
        lon_deg = atof(GPS_Data[4]) / 100.0f;
        lon_min = atof(GPS_Data[4]) - floorf(lon_deg)*100.0f;
        currentLong = floorf(lon_deg) + (lon_min / 60.0f);
        if (GPS_Data[5][0] == 'W') currentLong = -currentLong;
    }
}*/

void GPS_ParseData(void) {
    char args = 0;
    float lat_deg, lat_min, lon_deg, lon_min;  // All declarations at start
    token = strtok(GPS, ",");
    
    while (token != NULL && args < 12) {
        strncpy(GPS_Data[args], token, sizeof(GPS_Data[0])-1);
        GPS_Data[args][sizeof(GPS_Data[0])-1] = '\0';
        args++;
        token = strtok(NULL, ",");
    }

    if (args > 5 && strcmp(GPS_Data[1], "A") == 0) {
        // Parse latitude */
        lat_deg = atof(GPS_Data[2]) / 100.0f;
        lat_min = atof(GPS_Data[2]) - floorf(lat_deg)*100.0f;
        currentLat = floorf(lat_deg) + (lat_min / 60.0f);
        if (GPS_Data[3][0] == 'S') currentLat = -currentLat;

         //Parse longitude */
        lon_deg = atof(GPS_Data[4]) / 100.0f;
        lon_min = atof(GPS_Data[4]) - floorf(lon_deg)*100.0f;
        currentLong = floorf(lon_deg) + (lon_min / 60.0f);
        if (GPS_Data[5][0] == 'W') currentLong = -currentLong;
    }
}
