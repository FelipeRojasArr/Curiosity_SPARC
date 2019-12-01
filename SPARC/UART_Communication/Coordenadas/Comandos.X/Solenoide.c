/*
 * File:   Solenoide.c
 * Author: MLS
 *
 * Created on November 30, 2019, 4:32 PM
 */

#include "Definiciones.h"
#include <xc.h>
#include "Configuracion.h"

void Movimiento (void) {
    if (click==1){
        PWM();
        Solenoide=HIGH;
        _delay_ms(100);
        Solenoide=LOW;
    }
    else if(click==0){
        Solenoide=HIGH;
        PWM();
        Solenoide=LOW;
    }
    
    return;
}
