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
    //InterruptionsConfiguration();
    //GoToCero();
    
    while(1)
    { 
        TURN_ON_RECEIVER
        ControlFlagVerification = ON;
        verification();
        PrintMyActulPosition();
        Movimiento();
        /*if(x == 0)
        {
            TXSTAbits.TXEN = 0;
            Movimiento();
        }        
        RCSTAbits.CREN = 1;*/
        PrintMyActulPosition();
        
    }
}

void GoToCero(void)
{
    CoordAntX=1;
    CoordAntY=1;
    ENABLE_A=1;
    ENABLE_B=1;
    InicialX();
    InicialY();
    GoToInitialXPosition();
    GoToInitialYPosition();
}

void PrintMyActulPosition(void)
{
/*Imprimir en serial coordenada actualizada*/
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

