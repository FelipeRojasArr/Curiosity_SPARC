#include <pic18f4550.h> 
#include <xc.h> 
#include <stdint.h> 
#include <string.h> 
#include "UART.h" 
#include "cases.h" 
#include "Definiciones.h" 
#include "Configuracion.h" 
#include "PWM.h"
 
void Configuracion(void) { 
     
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
void InicialX(void){ /*Movemos x hacia atrás hasta que llegue a coordenada 0*/
    /*Dirección hacia atrás*/
    DIR_A=0;
    DIR_B=0;
    /*Encendemos motores mientras la coordenada no sea 0*/    
    do 
    {
    ENABLE_A=1;
    ENABLE_B=1;
    }while (CoordAntX!=0);
    /*Cuando ya llegó, se apagan motores*/
    ENABLE_A=0;
    ENABLE_B=0;
}
void InicialY(void){ /*Movemos y hacia atrás hasta que llegue a coordenada 0*/
    /*Dirección hacia atrás*/
    DIR_A=0;
    DIR_B=1;  
    /*Encendemos motores mientras la coordenada no sea 0*/
    do{
    ENABLE_A=1;
    ENABLE_B=1;
    }while (CoordAntY!=0);
    /*Cuando ya llegó, se apagan motores*/
    ENABLE_A=0;
    ENABLE_B=0;
    
}
