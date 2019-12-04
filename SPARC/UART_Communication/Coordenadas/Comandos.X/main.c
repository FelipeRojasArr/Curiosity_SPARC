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

void GoToInitialYPosition(void);
void GoToInitialXPosition(void);
//void PrintMyActulPosition(void)

void __interrupt() INT_ISR(void)
{
    if(INTCONbits.INT0IF == 1)
    {
        GoToInitialXPosition();
        if(PORTBbits.RB0 == 0)
        {
            __delay_ms(15);
            if(PORTBbits.RB0 == 0)
            {
                INTCONbits.INT0IF = 0;
            }
        }
    }
        
    if(INTCON3bits.INT1IF == 1)
    {
        GoToInitialYPosition();
        if(PORTBbits.RB1 == 0)
        {
            __delay_ms(15);
            if(PORTBbits.RB1 == 0)
            {
                INTCON3bits.INT1IF = 0;
            }
        }
    }
}
   

void main(void) {
    
    Configuracion();
    InterruptionsConfiguration();
    CoordAntX=1;
    CoordAntY=1;
    ENABLE_A=1;
    ENABLE_B=1;
    InicialX();
    InicialY();
    GoToInitialXPosition();
    GoToInitialYPosition();
    
    
    while(1){ /*Programa principal*/
        x=1;
       verification();
       Movimiento();
    }
}

/*void GoToCero(void)
{

}*/

/*void PrintMyActulPosition(void)
{

}*/