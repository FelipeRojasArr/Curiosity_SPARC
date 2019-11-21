
/*
* Generate 10 KHz PWM with 20% duty cycle
* www.electronicwings.com
*/

#include "config_intosc.h"
#include <pic18f4550.h>


void main()
{
    OSCCON = 0x60;	/* Set internal clock to 8MHz */
    TRISC1 = 0;		/* Set CCP2 pin as output for PWM out */
    TRISC2 = 0;		/* Set CCP1 pin as output for PWM out */
    PR2 = 199;		/* Load period value */
    
    /**** generate PWM on CCP1 ****/
    CCP1CON = 0x0C;	/* Set PWM mode and no decimal for PWM */
    CCPR1L = 50;    /* load 25% duty cycle value */
    
    /**** generate PWM on CCP2 ****/
    CCP2CON = 0x0C;	/* Set PWM mode and no decimal for PWM */    
    CCPR2L = 100;	/* load 50% duty cycle value */
    
    /*configure Timer 2 for PWM*/
    T2CON = 0;		/* No pre-scalar, timer2 is off */
    TMR2 = 0;		/* Clear Timer2 initially */
    TMR2ON = 1;		/* Timer ON for start counting*/
    while(1);
}