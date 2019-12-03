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


void InterruptionsConfiguration()
{
    INTCONbits.PEIE = ON;
    RCONbits.IPEN = OFF;                //Disables priority
    INTCONbits.GIE = ON;               //All samepriority
    INTCONbits.INT0IF = OFF;          //External interrupt flag for INT0
    INTCONbits.INT0IE = ON;             //Enables INT0 external interruptions
   // INTCONbits.RBIE = ON;               //RB Port Change Interrupt Enable bit
    INTCON2bits.INTEDG0 = ON;           //Rising Edge on external interrupt 0
    INTCON2bits.INTEDG1 = ON;           //Rising Edge on external interrupt 1
  //  INTCON2bits.INTEDG2 = ON;           //Rising Edge on external interrupt 2
   // INTCON3bits.INT2IE = ON;            //Enables INT2 external interrupt
    INTCON3bits.INT1IE = ON;            //Enables INT1 external interrupt
    
    INTCON2bits.RBPU = OFF;
            
    // MUST BE CLEARES WHEN AN EXTERNAL INTERRUPTION HAPPENS
    
    //INTCON3bits.INT1IF = OFF;          //External interrupt flag for INT0
    //INTCON3bits.INT2IF = OFF;          //External interrupt flag for INT0
}


