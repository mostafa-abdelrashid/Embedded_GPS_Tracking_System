#include  "../../Services/Bit_Utilities.h"
#include  "../../Services/tm4c123gh6pm.h"
#include  "../../Headers/MCAL/Systick.h"
#include  "../../Headers/MCAL/EEPROM.h"
#include<stdint.h>



								/////****eeprom true intialize ****/////
int EEPROM_Start(void){
    SYSCTL_RCGCEEPROM_R = 0x01;
    delay(6);
    while (EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);

    if ((EEPROM_EESUPP_R & EEPROM_EESUPP_ERETRY) || 
        (EEPROM_EESUPP_R & EEPROM_EESUPP_PRETRY)) {
        return -1;
    }

    // Commented for testing - may erase contents
    // SYSCTL_SREEPROM_R = SYSCTL_SREEPROM_R0;
    // SYSCTL_SREEPROM_R = 0;
    delay(6);

    while (EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);

    if ((EEPROM_EESUPP_R & EEPROM_EESUPP_ERETRY) || 
        (EEPROM_EESUPP_R & EEPROM_EESUPP_PRETRY)) {
        return -1;
    }  ///comment 

    return 1;
}						/////****eeprom error handling****/////
int eeprom_error_recovery(void) // NEEDS MORE INVESTIGATION
{
		unsigned int  timeout = 100000;

	 EEPROM_EESUPP_R = EEPROM_EESUPP_START; // start erase
	 while((EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING) && timeout--)
        ; // Wait until working bit clears or timeout happens

    if (timeout == 0)
    {
        return 0; // Timeout happened -> failure
    }
    else
    {
        return 1; // EEPROM recovery successful
    }
}

							/////****eeprom intialize****/////
int EEPROM_Init(void) {
    int status = EEPROM_Start();
    if (status != 1) status = eeprom_error_recovery();
    return status;
}

void eeprom_write(float data, unsigned int addr) {
    union {
        float f;
        uint32_t u;
    } converter;

    converter.f = data;

    if (addr + 4 > EEPROM_SIZE || addr % 4 != 0) return;

    while (EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);
    EEPROM_EEBLOCK_R = addr >> 4;
    EEPROM_EEOFFSET_R = addr & 0xF;
    EEPROM_EERDWR_R = converter.u;
    while (EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);
}

float eeprom_read(unsigned int addr) {
    union {
        float f;
        uint32_t u;
    } converter;

    if (addr + 4 > EEPROM_SIZE || addr % 4 != 0) return 0;

    while (EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);
    EEPROM_EEBLOCK_R = addr >> 4;
    EEPROM_EEOFFSET_R = addr & 0xF;
    converter.u = EEPROM_EERDWR_R;
    return converter.f;
}


							/////****eeprom write****/////
/*void eeprom_write(float data,unsigned int addr) // ???? uinnt8_t mkan kol u8 ?????   //data ->32-bit
{		
		if (addr % 4 != 0) return ; 
	  if (addr + 4 > EEPROM_SIZE) return; // prevent overflow

	while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING); //	checking not busy
	//EEPROM_EEBLOCK_R = (addr&0x1F0);								// passing the block address only and zeroing anything else
	EEPROM_EEBLOCK_R = addr >>4;										//	shifting for keeping in the same block number
	EEPROM_EEOFFSET_R = (addr& 0xF);				 //offset within the block
	EEPROM_EERDWR_R = data; 									//data written 
	while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);
}*/
							/////****eeprom read****/////
/*float eeprom_read(unsigned int addr) // hl el data htb2a saved mn mara l mara ??
{	
	if (addr % 4 != 0) return 0; 
	if (addr + 4 > EEPROM_SIZE) return 0; // prevent overflow
	
	while(EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING);
	//EEPROM_EEBLOCK_R = (addr&0x1F0);								// passing the block address only and zeroing anything else
	EEPROM_EEBLOCK_R = addr >>4;//Block number
	EEPROM_EEOFFSET_R = (addr& 0xF); //offset within the block
	return EEPROM_EERDWR_R;
}*/