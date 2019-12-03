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

void UARTErrorR1(void);
void UARTErrorR0(void);

void __interrupt() INT_ISR(void)
{
    if(PORTBbits.RB0 == 1)
    {
        while(INTCONbits.INT0IF == 1)
        {
            __delay_ms(250);
            UARTErrorR0();
            //HaltMotors();
            if(PORTBbits.RB0 == 0)
            {
                __delay_ms(15);
                if(PORTBbits.RB0 == 0)
                {
                    INTCONbits.INT0IF = 0;
                }
            }
        }
    }
        
    if(PORTBbits.RB1 == 1)
    {
        while(INTCON3bits.INT1IF == 1)
        {
            UARTErrorR1();      //cAMBIA ESTA FUNCIÓN A LO QUE QUIERAS
            __delay_ms(250);
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
}
   
void UARTErrorR0()
{
    UARTWrite(0x45);
}

void UARTErrorR1()
{
    UARTWrite(0x65);
}

void main(void) {
  
    Configuracion();
    InterruptionsConfiguration();
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
