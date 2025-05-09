#include "../../Headers/HAL/Landmarks.h"
#include <stdint.h>
#include "../../Headers/MCAL/EEPROM.h"

const Landmark presetLandmarks[MAX_LANDMARKS]= {
		{3202.11068,3428.44868, "Home"},
    {3202.11078, 3428.44883,"Away"}
	
};
///////////////////////////PREVIOUS APPROACH THAT IS NOT USED BECAUSE IT WAS EASIER TO SAVE LANDAMRKS IN THE INTRUCTION MEMORY NOT LIKE AN ARRAY //////////////////////////////
//function to write all preset landmarks to EEPROM
void Landmarks_EEPROM_WriteAll(void) {
    unsigned int baseAddr = 0;//keeps track of the current EEPROM address to write to.
		int i,j;
    for ( i = 0; i < MAX_LANDMARKS; i++) {
        const Landmark* lm = &presetLandmarks[i];//pointer lm to the current landmark in the array, just to improve readabillity 

        /* Write latitude
				Converts the float latitude into a uint32_t using type-punning:
				*(uint32_t*)&lm->latitude interprets the float bits as a 32-bit unsigned int
				Then writes this 4-byte number to EEPROM at baseAddr.*/
        eeprom_write(*(uint32_t*)&lm->latitude, baseAddr);
        baseAddr += 4;

        /* Write longitude
				Converts the float latitude into a uint32_t using type-punning:
				*(uint32_t*)&lm->latitude interprets the float bits as a 32-bit unsigned int
				Then writes this 4-byte number to EEPROM at baseAddr.*/
        eeprom_write(*(uint32_t*)&lm->longitude, baseAddr);
        baseAddr += 4;//Moves the EEPROM address forward by 4 byte

        // Write name (byte by byte)
        for ( j = 0; j < MAX_NAME_LENGTH; j++) {
            eeprom_write((uint8_t)lm->name[j], baseAddr);
            baseAddr += 1;
        }
    }
}

// Helper function to read landmarks from EEPROM into buffer
void Landmarks_EEPROM_ReadAll(Landmark* landmarksBuffer) {
    unsigned int baseAddr = 0;//keeps track of the current EEPROM address to write to.
		uint32_t lat_raw;
		uint32_t lon_raw;
		int i,j;
    for ( i = 0; i < MAX_LANDMARKS; i++) {
        Landmark* lm = &landmarksBuffer[i];//pointer lm to the current landmark in the array, just to improve readabillity 

        // Read latitude
         lat_raw = eeprom_read(baseAddr);
        lm->latitude = *(float*)&lat_raw;
        baseAddr += 4;

        // Read longitude
         lon_raw = eeprom_read(baseAddr);
        lm->longitude = *(float*)&lon_raw;
        baseAddr += 4;

        // Read name
        for ( j = 0; j < MAX_NAME_LENGTH; j++) {
            lm->name[j] = (char)eeprom_read(baseAddr);
            baseAddr += 1;
        }
    }
}
