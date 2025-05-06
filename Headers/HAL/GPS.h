#ifndef GPS_H
#define GPS_H

extern float currentLat;
extern float currentLong;

extern void GPS_read(void);
extern void GPS_ParseData(void);


#endif
