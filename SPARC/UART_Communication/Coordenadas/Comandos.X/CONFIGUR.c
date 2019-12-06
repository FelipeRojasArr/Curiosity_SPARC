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

 
void Configuracion(void)
{ 
     
   //CLOCK FREQUENCY CONFIGURATION 
   //============================ 
   OSCCON=0x72; /* Set internal clock to 8MHz */ 
     
   //DISABLE PORT's ANALOG FUNCTIONS 
   //=============================== 
   CMCON = 0xFF;                        // Comparators OFF, to use PORT_Ds LSN 
   CVRCONbits.CVREN = 0;                // Comparator Voltge Reference Module OFF 
   ADCON1 = 0x0F;                       // All ports as DIGITAL I/O 
    
   // PORT DEFINITIONS  
   //=============================== 
   PORTD = 0x00;                         
   LATD = 0x00;                          
   TRISD = 0xF0;                        // PORTD as Input 
    
   PORTC = 0x00;                         
   LATC= 0x00;                          
   TRISC= 0x00;                        // PORTC as Output 
    
   PORTB = 0x00;                         
   LATB= 0x00;                          
   TRISB= 0xFF;                        // PORTB as Input 
    
   // UART CONFIGURATION 
   //=============================== 
   UARTConfi(9600); 
    TRISC=0X00; 
     
    //PWM CONFIGURATION 
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
