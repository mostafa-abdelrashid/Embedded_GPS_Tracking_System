#ifndef LANDMARKS_H
#define LANDMARKS_H

#define MAX_NAME_LENGTH 30
#define MAX_LANDMARKS   50

typedef struct {
		char* name;
    float latitude;
    float longitude;
   
} Landmark;

// Array of landmarks stored in flash initially
extern const Landmark presetLandmarks[];
extern const int LANDMARK_COUNT;

// EEPROM functions
void Landmarks_EEPROM_WriteAll(void);
void Landmarks_EEPROM_ReadAll(Landmark* landmarksBuffer);

#endif // LANDMARKS_H

