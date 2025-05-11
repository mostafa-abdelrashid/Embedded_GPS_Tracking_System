#include "../../Headers/HAL/GPS.h"
#include "../../Headers/APP/APP.h"
#include "../../Services/Bit_Utilities.h"
#include <math.h>


double ToDegree(float angle) {
    int degrees = (int)(angle / 100);
    double minutes = angle - (degrees * 100);
    return (double)(degrees + (minutes / 60));
}

double ToRad(double angle){
		return angle * PI / 180.0;
}

double GET_Distance(double lat1, double lon1, 
                  double lat2, double lon2) 
{
    // Convert decimal degrees to radians
    
    // Haversine formula
    double dLat = ToRad(lat2 - lat1);
    double dLon = ToRad(lon2 - lon1);
    
    float a = sinf(dLat/2) * sinf(dLat/2) + 
              cosf(lat1) * cosf(lat2) * 
              sinf(dLon/2) * sinf(dLon/2);
    
    float c = 2 * atan2f(sqrtf(a), sqrtf(1-a));
    
    return EARTH_RADIUS * c;
}