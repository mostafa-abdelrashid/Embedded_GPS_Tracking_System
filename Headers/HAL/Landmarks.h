#ifndef LANDMARKS_H
#define LANDMARKS_H

#define MAX_NAME_LENGTH 30
#define MAX_LANDMARKS   50

typedef struct {
    float latitude;
    float longitude;
    char name[MAX_NAME_LENGTH];
} Landmark;

// Array of landmarks stored in flash initially
extern const Landmark presetLandmarks[MAX_LANDMARKS];

// EEPROM functions
void Landmarks_EEPROM_WriteAll(void);
void Landmarks_EEPROM_ReadAll(Landmark* landmarksBuffer);

#endif // LANDMARKS_H
