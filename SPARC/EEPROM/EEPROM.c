/*
 * File:   EEPROM.c
 * Author: felix
 *
 * Created on November 21, 2019, 2:35 PM
 */


#include <xc.h>

void main(void) {
    return;
}

int Read_EEPROM(int AddressToRead){
    EEADR = AddressToRead;               //read from what address
    EECON1bits.EEPGD = 0;               //Determines if the access will be to program or data memory
    EECON1bits.RD = 1;     
    EECON1bits.CFGS = 0;
    
    return;
}


int Write_EEPROM(char ContentToWrite, int AddressToWrite){
    EEADR = AddressToWrite;                 //
    EEDATA = ContentToWrite;
    EECON1bits.EEPGD = 0;                   // EEPGD = 0, access data EEPROM memory
    EECON1bits.CFGS = 0;                    //Access Flash program or data memory EEPROM
    EECON1bits.WREN = 1;                    //WREN = 1, Allows write cycles to data EEPROM
    EECON2 = 0x55;
    NOP();
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    
}  