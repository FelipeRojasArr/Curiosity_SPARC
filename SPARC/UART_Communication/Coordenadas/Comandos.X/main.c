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
       
        char a[3];
        char b[3];

        a[0]=(CoordAntX/100)+48;
        a[1]=((CoordAntX%100)/10)+48;
        a[2]=((CoordAntX%100)%10)+48;

        b[0]=(CoordAntY/100)+48;
        b[1]=((CoordAntY%100)/10)+48;
        b[2]=((CoordAntY%100)%10)+48;

        for(int i=0; i<3; i++){

            UARTWrite(a[i]);
        }
        for(int i=0; i<3; i++){

            UARTWrite(b[i]);
        }
    }
}
