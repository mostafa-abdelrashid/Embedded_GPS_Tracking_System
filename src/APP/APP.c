#include "../../Headers/HAL/GPS.h"
#include "../../Headers/APP/APP.h"
#include "../../Services/Bit_Utilities.h"
#include <math.h>


float ToDegree(float angle) {
    int degrees = (int)(angle / 100);
    float minutes = angle - (degrees * 100);
    return degrees + (minutes / 60.0f);
}

float ToRad(float angle){
		return angle * PI / 180.0f;
}

float GET_Distance(float Longitude_Start, float Latitude_Start, float Longitude_End, float Latitude_End) {
    // Convert coordinates to radians
    float lat1 = ToRad(ToDegree(Latitude_Start));
    float lon1 = ToRad(ToDegree(Longitude_Start));
    float lat2 = ToRad(ToDegree(Latitude_End));
    float lon2 = ToRad(ToDegree(Longitude_End));

    // Differences
    float dLat = lat2 - lat1;
    float dLon = lon2 - lon1;

    // Haversine formula
    float a = powf(sinf(dLat / 2), 2) +
              cosf(lat1) * cosf(lat2) * powf(sinf(dLon / 2), 2);
    float c = 2.0f * atanf(sqrtf(a) / sqrtf(1.0f - a));

    return EARTH_RADIUS * c;  // Distance in meters
}