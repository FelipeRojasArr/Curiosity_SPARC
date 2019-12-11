#include <pic18f4550.h>
#include <xc.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "main.h"
#include "UART.h"
#include "cases.h"
#include "Definiciones.h"
#include "Configuracion.h"
#include "PWM.h"

int Movement(void)
{
    if(click == ON){
        PWM();
        SOLENOIDE=HIGH;
        __delay_ms(1200);
        SOLENOIDE=LOW;
        myPrintf("Click");
    }
    else{
        if(click == OFF)
        {
            SOLENOIDE=HIGH;
            PWM();
            SOLENOIDE=LOW;
            myPrintf("Slide");
        }
    }
    
    ControlFlagVerification = ON;
    
    return ControlFlagVerification;
}
