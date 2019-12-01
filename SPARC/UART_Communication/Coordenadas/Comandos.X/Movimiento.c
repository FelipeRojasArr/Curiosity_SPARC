#include <pic18f4550.h>
#include "PWM.h"
#include <xc.h>
#include "cases.h"
#include "Definiciones.h"
#include "Configuracion.h"

void Movimiento(void) {
    if(click==1){
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
