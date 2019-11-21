
#include "config_intosc.h"
#include <pic18f4550.h>
//=======================================================
//PWM Period = [(PR2) + 1] ? 4 ? TOSC ?(TMR2 Prescale Value)
//(PWM Period/( 4 ? TOSC ?(TMR2 Prescale Value)))-1 = PR2//Periodo=1/8KHz
// Prescaler=16
// Oscilador= 4MHz ---> Tosc= 1/4MHz
// PR2=((1/8KHz)/(4*(1/4MHz)*16)-1
// PR2=((1/(8*10^3))/(4*(1/(4*10^6))*16))-1
// PR2= 6.8dec -->7 -->0x07 hex

// PWM Duty Cycle = (CCPR1L:CCP1CON<5:4> ?TOSC ? (TMR2 Prescale Value)
//CCPR1L= PWM/Tosc*Prescaler
//	=(1/8KHz)/(1/4MHz)*16=
//	=(1/(8*10^3))/(1/(4*10^6)*16)
//	=31.25 --> 31
//31	100%
//15.5	50%
// CCPR1L= 16 --> 0001 0000
// 0000 0100 00
//CCPR1L= 0x04 hex
void main()
{
    ADCON1=0x0F;
    OSCCON = 0x60;	/* Set internal clock to 4MHz */
    TRISC1 = 0;		/* Set CCP1 pin as output for PWM out */
    TRISC2 = 0;		/* Set CCP2 pin as output for PWM out */
    PR2 = 0x07;		// Load period value de formula
    
    /**** generate PWM on CCP1 ****/
    CCP1CON = 0x0C;	/* Set PWM mode and no decimal for PWM */ //PR2
    CCPR1L = 0x04;    /* load 50% duty cycle value */
    
    /**** generate PWM on CCP2 ****/
    CCP2CON = 0x0C;	/* Set PWM mode and no decimal for PWM */    
    CCPR2L = 0x04;	/* load 50% duty cycle value */
    
    /*configure Timer 2 for PWM*/
    T2CON = 0x03;		/* pre-scalar, timer2 is 16 */
    TMR2 = 0;		/* Clear Timer2 initially */
    TMR2ON = 1;		/* Timer ON for start counting*/
    while(1);
}