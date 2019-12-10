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
#include "Interruptions.h"
#include "PWM.h"

int Movimiento(void)
{

    if(click == ON){
        PWM();
        SOLENOIDE=HIGH;
        __delay_ms(1200);
        SOLENOIDE=LOW;
        char loquequieras[5]="click";
       for(int i=0;i<5;i++){
       UARTWrite(loquequieras[i]);
       }
        
    }
    else if(click == OFF){
        SOLENOIDE=HIGH;
        PWM();
        SOLENOIDE=LOW;
        char loquequieras2[5]="slide";
       for(int i=0;i<5;i++){
       UARTWrite(loquequieras2[i]);
       }
    }
    
    ControlFlagVerification = ON;
    
    return ControlFlagVerification;
}
