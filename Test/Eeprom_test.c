/*#include "../Headers/MCAL/EEPROM.h"
#include "../Headers/MCAL/UART.h"
#include "../Services/tm4c123gh6pm.h"
#include <stdint.h>
#include <stdio.h>

void test_eeprom(void) {
	    // Test data
    float test_data = 3.14159;
    uint16_t test_addr = 0x100;
	  char buf[50];
	  float read_data = eeprom_read(test_addr);

    // Initialize UART0 for debug output
    UART0_Init();
    
    // Initialize EEPROM
    if(EEPROM_Init() != 1) {
        UART0_SendString("EEPROM Init Failed\r\n");
        return;
    }
    

    
    // Write/Read test
    eeprom_write(test_data, test_addr);
    
    // Print results
    
    sprintf(buf, "Wrote: %.5f, Read: %.5f\r\n", test_data, read_data);
    UART0_SendString(buf);
    
    // Verification
    if(test_data != read_data) {
        UART0_SendString("EEPROM Test Failed!\r\n");
    } else {
        UART0_SendString("EEPROM Test Passed!\r\n");
    }
}*/