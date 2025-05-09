#ifndef GPS_H
#define GPS_H

extern float currentLat;
extern float currentLong;
extern char  GPS[100];
extern char  GPS_Data[12][20];

extern void GPS_read(void);
extern void GPS_ParseData(void);


#endif
