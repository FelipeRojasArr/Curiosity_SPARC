#include <pic18f4550.h>
#include <xc.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "config.h"
#include "UART.h"
#include "cases.h"


void main(void) {
    OSCCON=0x72; /*CAMBIAMOS A 4MHZ*/
    UARTConfi(9600);
    TRISC=0X00;
    verification(); 
    //PWM(cord_x, cord_y);
}
