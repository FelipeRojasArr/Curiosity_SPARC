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

int Read_EEPROM(int x_coordinate){
    EEADR = x_coordinate;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.RD = 1;
    
    //BCF EECON1, EEPGD ; Point to DATA memory
    //BCF EECON1, CFGS ; Access EEPROM
    //BSF EECON1, RD ; EEPROM Read
    //MOVF EEDATA, W ; W = EEDATA
}
