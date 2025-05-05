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

    GPS[counter] = '\0'; // Null-terminate the string
}

void GPS_ParseData(void) {
    char args = 0;

    // Parse the GPS data string into GPS_Data[]
    token = strtok(GPS, ",");
    while (token != NULL && args < 12) {
        strcpy(GPS_Data[args++], token);
        token = strtok(NULL, ",");
    }

    // Parse latitude and longitude
    if (strcmp(GPS_Data[1], "A") == 0) {
        // Latitude
        if (strcmp(GPS_Data[3], "N") == 0) {
            currentLat = atof(GPS_Data[2]);
        } else {
            currentLat = -atof(GPS_Data[2]);
        }

        // Longitude
        if (strcmp(GPS_Data[5], "E") == 0) {
            currentLong = atof(GPS_Data[4]);
        } else {
            currentLong = -atof(GPS_Data[4]);
        }
    }
}
