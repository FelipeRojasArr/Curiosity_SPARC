#include <xc.h>
#include <stdint.h>

#pragma config OSC = IRCIO67       //CONFIG1H (0-3) = 0010: INTIO2 oscillator, Internal oscillator block, port function on RA6 and RA7.
#pragma config MCLRE    = OFF        //Master Clear Reset activado
#pragma config PBADEN   = OFF       //Hace que los puertos A y B sean digitales
#pragma config LVP      = OFF       //Low-voltage Programming desactivado */
#pragma config WDT = OFF

#define ON 1
#define OFF 0
#define BUTTON_STOP PORTBbits.RB0
#define BUTTON_MOTORY PORTBbits.RB1
#define BUTTON_MOTORX PORTBbits.RB2
#define _XTAL_FREQ 4000000

//Instrucction to be added to the main
/*void __interrupt() INT_ISR(void)
{
    doSomething();
}*/


void interruptsConfiguration()
{
    RCONbits.IPEN = OFF;                //Disables priority
    INTCONbits.GIEH = ON;               //All High priority
    INTCONbits.INT0IE = ON;             //Enables INT0 external interruptions
    INTCONbits.RBIE = ON;               //RB Port Change Interrupt Enable bit
    INTCON2bits.INTEDG0 = ON;           //Rising Edge on external interrupt 0
    INTCON2bits.INTEDG1 = ON;           //Rising Edge on external interrupt 1
    INTCON2bits.INTEDG2 = ON;           //Rising Edge on external interrupt 2
    INTCON3bits.INT2IE = ON;            //Enables INT2 external interrupt
    INTCON3bits.INT1IE = ON;            //Enables INT1 external interrupt
            
    // MUST BE CLEARES WHEN AN EXTERNAL INTERRUPTION HAPPENS
    //INTCONbits.INT0IF = OFF;          //External interrupt flag for INT0
    //INTCON3bits.INT1IF = OFF;          //External interrupt flag for INT0
    //INTCON3bits.INT2IF = OFF;          //External interrupt flag for INT0
}
void buttonConfiguration(void)
{
    PORTB = 0;
    LATB = 0;
    TRISB = 0x07;
    //TRISBbits.RB0 = ON;
    //TRISBbits.RB1 = ON;
    //TRISBbits.RB2 = ON;
}


