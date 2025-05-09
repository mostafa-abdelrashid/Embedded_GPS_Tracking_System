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

float GET_Distance(float lon1_decimal, float lat1_decimal, 
                  float lon2_decimal, float lat2_decimal) 
{
    // Convert decimal degrees to radians
    float lat1 = lat1_decimal * PI / 180.0f;
    float lon1 = lon1_decimal * PI / 180.0f;
    float lat2 = lat2_decimal * PI / 180.0f;
    float lon2 = lon2_decimal * PI / 180.0f;

    // Haversine formula
    float dLat = lat2 - lat1;
    float dLon = lon2 - lon1;
    
    float a = sinf(dLat/2) * sinf(dLat/2) + 
              cosf(lat1) * cosf(lat2) * 
              sinf(dLon/2) * sinf(dLon/2);
    
    float c = 2.0f * atan2f(sqrtf(a), sqrtf(1.0f-a));
    
    return EARTH_RADIUS * c;
}