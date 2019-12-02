#include <pic18f4550.h>
#include "PWM.h"
#include <xc.h>
#include "cases.h"
#include "Definiciones.h"
#include "Configuracion.h"
#include "UART.h"

int Movimiento(void) {
    if(click==1){
        PWM();
        SOLENOIDE=HIGH;
        __delay_ms(100);
        SOLENOIDE=LOW;
        char loquequieras[5]="click";
       for(int i=0;i<5;i++){
       UARTWrite(loquequieras[i]);
       }
        
    }
    else if(click==0){
        SOLENOIDE=HIGH;
        PWM();
        SOLENOIDE=LOW;
        char loquequieras2[5]="slide";
       for(int i=0;i<5;i++){
       UARTWrite(loquequieras2[i]);
       }
    }
}


//void HaltMotors()
//{
//    ENABLE_A = HIGH;
//    ENABLE_B = HIGH;
//}