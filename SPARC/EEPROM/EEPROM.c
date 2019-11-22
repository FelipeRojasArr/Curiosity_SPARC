/*
 * File:   EEPROM.c
 * Author: felix
 *
 * Created on November 21, 2019, 2:35 PM
 */


#include <xc.h>
#include "EEPROM.h"

void main(void) {
    
    return;
}

unsigned char Read_EEPROM(int AddressToRead){
    EEADR = AddressToRead;                  //Read from what address
    EECON1bits.EEPGD = 0;                   //Determines if the access will be to program or data memory
    EECON1bits.CFGS = 0;                    //Access EEPROM
    EECON1bits.RD = 1;                      //EEPROM Read
    EEDATA = contentOfAddress;              //Copies content
    
    return contentOfAddress;                
}


void Write_EEPROM(char ContentToWrite, int AddressToWrite){
    EEADR = AddressToWrite;                 //Assign the address
    EEDATA = ContentToWrite;                //Writes the desire content 
    EECON1bits.EEPGD = 0;                   //EEPGD = 0, Access data EEPROM memory
    EECON1bits.CFGS = 0;                    //CFGS = 0, Access Flash program or data memory EEPROM
    EECON1bits.WREN = 1;                    //WREN = 1, Allows write cycles to data EEPROM
    INTCONbits.GIE = 0;                     //Disables interruptions
    EECON2 = 0x55;                          //Values needed defined by datasheet
    NOP();
    EECON2 = 0x0AA;                         //Values needed defined by datasheet
    EECON1bits.WR = 1;                      //Write control bit
    INTCONbits.GIE = 1;                     //Enables interruptions
    while(PIR2bits.EEIF == 0)               //Interruption Flag for EEPROM. If equal 0, write hasn't been completed
    {
        ;;
    }
    EECON1bits.WREN = 0;                    //End of Write
    return;
}  

