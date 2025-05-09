#include "../../Headers/HAL/Landmarks.h"
#include <stdint.h>
#include "../../Headers/MCAL/EEPROM.h"

const Landmark presetLandmarks[MAX_LANDMARKS]= {
		{30.064347490644835, 31.27761282027815, "Kharasana Building"},
    {30.064623222639995, 31.28040946583904,"Faculty Mosque"},
    {30.064096296685296, 31.280098317778666 ,"Hall A & B "},
		{30.06408665098429, 31.28063700439362,"Architecture Building"},
		{30.0636282597642, 31.280309308139543,"Hall C & D"},
		{30.063892141446093, 31.280327794946015,"Students Cafeteria"},//not exact location and might need a rename 
		{30.063402043412136, 31.279631503787666,"Luban Workshop"},
		{30.063184045633715, 31.278934285155604,"ASU Racing Team"},
		{30.062899378923245, 31.279004380004746,"Mechatronics Building"},
		{30.062916528209314, 31.278562975535948,"Garage"},
		{30.063469778810354, 31.278404746251482,"Credit Building"},
		{30.063376483333226, 31.27880560985057,"Football Field"},
		{30.06366897631229, 31.278677534369272,"VolleyBall Field"},
		{30.063794330182212, 31.278185349031183,"Student Union"},
		{30.0640495253919, 31.278933010762326,"Auto Repair Shop"},
		{30.06409263726539, 31.278420797337134,"Automotive Workshop"},
		{30.063789565722114, 31.27951981255547,"Playground"}
};

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