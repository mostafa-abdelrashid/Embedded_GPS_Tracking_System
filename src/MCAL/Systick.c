#include "../../Services/tm4c123gh6pm.h"
#include "../../Services/Bit_Utilities.h"
#include "../../Headers/MCAL/Systick.h"


void Systick_Init(void){
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = 0x00FFFFFF;
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = 0x00000005;  
}
void Systick_Wait(unsigned int delay){
    NVIC_ST_CTRL_R = 0;
    NVIC_ST_RELOAD_R = delay-1;
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R=0x00000005; 
		while(GET_BIT(NVIC_ST_CTRL_R,16)==0);
}
void delay (unsigned int delay){
		unsigned int i ;
		for(i=0;i<delay;i++){
			Systick_Wait(16000);
		}
}