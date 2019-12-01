#include "Definiciones.h"
#include "Configuracion.h"
#include <pic18f4550.h>
#include <xc.h>

void ConfiguracionPWM(void) {//PWM CONFIGURATION
   //===============================    
     PR2 = PR2VALUE;		// Load period value de formula
    
    /**** generate PWM on CCP1 ****/
    CCP1CON = 0x0C;	/* Set PWM mode and no decimal for PWM */ //PR2
    CCPR1L = CCPRXL;    /* load 50% duty cycle value */
    
    /**** generate PWM on CCP2 ****/
    CCP2CON = 0x0C;	/* Set PWM mode and no decimal for PWM */    
    CCPR2L = CCPRXL;	/* load 50% duty cycle value */
    
    /*configure Timer 2 for PWM*/
    T2CON = 0x03;		/* pre-scalar, timer2 is 16 */
    TMR2 = 0;		/* Clear Timer2 initially */
    TMR2ON = 1;		/* Timer ON for start counting*/
    return;
}