#include <pic18f4550.h>
#include "PWM.h"
#include <xc.h>
#include "cases.h"
#include "Definiciones.h"
#include "Configuracion.h"

int Movimiento(void) {
    if(click==1){
        PWM();
        SOLENOIDE=HIGH;
        __delay_ms(100);
        SOLENOIDE=LOW;
        
    }
    else if(click==0){
        SOLENOIDE=HIGH;
        PWM();
        SOLENOIDE=LOW;
    }
}


//void HaltMotors()
//{
//    ENABLE_A = HIGH;
//    ENABLE_B = HIGH;
//}