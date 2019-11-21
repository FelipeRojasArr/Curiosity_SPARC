//=======================================================
//PWM Period = [(PR2) + 1] • 4 • TOSC •(TMR2 Prescale Value)
//Periodo=1/8KHz
// Prescaler=16
// Oscilador= 20MHz ---> Tosc= 1/20MHz 4MHz
// PR2=38dec --> 26Hex

// PWM Duty Cycle = (CCPR1L:CCP1CON<5:4> •TOSC • (TMR2 Prescale Value)
//CCPR1L= PWM/Tosc*Prescaler
//	=(1/8KHz)/(1/20MHz)*16=156.25=156
//156	100%
//78	50%
//0100 11 10
//0001 0011 .0x13
#include "config_intosc.h"
#include <pic18f4550.h>
void main()
{
    ADCON1=0x0F;
    OSCCON = 0x60;	/* Set internal clock to 8MHz */
    TRISC1 = 0;		/* Set CCP1 pin as output for PWM out */
    TRISC2 = 0;		/* Set CCP2 pin as output for PWM out */
    PR2 = 0x26;		// Load period value de formula
    
    /**** generate PWM on CCP1 ****/
    CCP1CON = 0x0C;	/* Set PWM mode and no decimal for PWM */ //PR2
    CCPR1L = 0x13;    /* load 50% duty cycle value */
    
    /**** generate PWM on CCP2 ****/
    CCP2CON = 0x0C;	/* Set PWM mode and no decimal for PWM */    
    CCPR2L = 0x13;	/* load 50% duty cycle value */
    
    /*configure Timer 2 for PWM*/
    T2CON = 0x03;		/* No pre-scalar, timer2 is off */
    TMR2 = 0;		/* Clear Timer2 initially */
    TMR2ON = 1;		/* Timer ON for start counting*/
    while(1);
}