#include <pic18f4550.h>
#include <xc.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "UART.h"
#include "cases.h"
#include "Definiciones.h"
#include "Configuracion.h"
#include "Interruptions.h"
#include "PWM.h"

//void __interrupt() INT_ISR(void)
//{
//    if(INTCON3bits.INT2IF = ON)
//    {
//        __delay_ms(15);
//        while(INTCON3bits.INT2IF = ON)
//        {
//            HaltMotors();
//        }
//        if(STOP_SWITCH = OFF)
//        {
//            __delay_ms(15);
//            if(STOP_SWITCH = OFF)
//            {
//                INTCON3bits.INT2IF = OFF;
//            }
//        }
//    }
//}

   
void main(void) {
    Configuracion();
    CoordAntX=0;
    CoordAntY=0;
    ENABLE_A=1;
    ENABLE_B=1;
    
    while(1){
        x=1;
       verification(); 
       
        Movimiento();
       
        CoordAntY = (unsigned char)CoordAntY;
        CoordAntX = (unsigned char)CoordAntX;
        UARTWrite(CoordAntX);
        UARTWrite(CoordAntY);
    }
    
}
