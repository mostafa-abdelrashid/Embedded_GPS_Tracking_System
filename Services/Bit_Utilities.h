
#define SET(reg,value) reg|=value 	// Set (enable) all bits specified in 'value' in the given register 

#define CLR(reg,value) reg&=~value // Clear (disable) all bits specified in 'value' in the given register

#define SET_BIT(reg,bit) reg|=(1<<bit) //Set a specific bit in a register (bit position 0-31

#define GET_BIT(reg,bit) (reg&(1<<bit))>>bit //Get the value (0 or 1) of a specific bit in a register 

#define CLR_BIT(reg,bit) reg&=(~(1<<bit)) //Clear a specific bit in a register (bit position 0-31)

#define TOG_BIT(reg,bit)	reg^=(1<<bit)  // Toggle a specific bit in a register
