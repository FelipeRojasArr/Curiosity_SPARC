//=======================================================
//PWM Period = [(PR2) + 1] ? 4 ? TOSC ?(TMR2 Prescale Value)
//(PWM Period/( 4 ? TOSC ?(TMR2 Prescale Value)))-1 = PR2//Periodo=1/8KHz
// Prescaler=16
// Oscilador= 4MHz ---> Tosc= 1/4MHz
// PR2=((1/250Hz)/(4*(1/4MHz)*16)-1
// PR2=((1/(250))/(4*(1/(4*10^6))*16))-1
// PR2= 249dec -->249 -->0xF9 hex

// PWM Duty Cycle = (CCPR1L:CCP1CON<5:4> ?TOSC ? (TMR2 Prescale Value)
//CCPR1L= PWM/Tosc*Prescaler
//	=(1/250Hz)/(1/4MHz)*16=
//	=(1/(250))/(1/(4*10^6)*16)
//	=1000 --> 4E2
//1000	100%
//500	50%
// CCPR1L= 625 --> 0001 1111 0100
// 0000 0111 1101 00
//CCPR1L= 0x7D hex

#include "config_intosc.h"
#include <pic18f4550.h>
#include "Variables.h"
#include <xc.h>
#define PR2value 0xF9 /*PR2 VALUE*/
#define CCPRXL 0x7D    /*CCPR1L VALUE*/

unsigned int ContarPulsos(unsigned int pasosA);
void Calculos(void);
void OneShot(void);
void ResetOneShot(void);

void main(void){
    
   //CLOCK FREQUENCY CONFIGURATION
   //============================
   OSCCON = 0x60;                       // 4 MHz internal oscillator

   //DISABLE PORT's ANALOG FUNCTIONS
   //===============================
   CMCON = 0xFF;                        // Comparators OFF, to use PORT_Ds LSN
   CVRCONbits.CVREN = 0;                // Comparator Voltge Reference Module OFF
   ADCON1 = 0x0F;                       // All ports as DIGITAL I/O
   
                              /*PWM*/
   //////////////////////////////////////////////////////////////////
   
    TRISC1 = OUTPUT;		/* Set CCP1 pin as output for PWM out */
    TRISC2 = OUTPUT;		/* Set CCP2 pin as output for PWM out */
    
    PR2 = PR2value;		// Load period value de formula
    
    /**** generate PWM on CCP1 ****/
    CCP1CON = 0x0C;	/* Set PWM mode and no decimal for PWM */ //PR2
    CCPR1L = CCPRXL;    /* load 50% duty cycle value */
    
    /**** generate PWM on CCP2 ****/
    CCP2CON = 0x0C;	/* Set PWM mode and no decimal for PWM */    
    CCPR2L = CCPRXL;	/* load 50% duty cycle value */
    
    /*configure Timer 2 for PWM*/
    T2CON = 0x03;		/* pre-scalar, timer2 is 4 */
    TMR2 = 0;		/* Clear Timer2 initially */
    TMR2ON = 1;		/* Timer ON for start counting*/
    ////////////////////////////////////////////////////////////////////
    PORTD = 0x00;
    LATD = 0x00;
    TRISD = 0x00;
    
    //================================================
    /*DEFINIMOS COMO OUTPUTS LOS PINES DE LOS ENABLES*/
    TRISCbits.RC6 = OUTPUT;	/*EnableA*/	
    TRISCbits.RC7 = OUTPUT;	/*Enable B*/
    TRISCbits.RC0 = OUTPUT; /*Bit de prueba*/
    
    
    while(1){
             
        //Calculos();
        pasosA=200;
        PasosActualesA= ContarPulsos(pasosA); 
        if (PasosActualesA==200) bit=HIGH;
        __delay_ms(250);
        bit=LOW;
    }
    
}



void Calculos(void){      
    CoordRelatX=CoordNewX-CoordAntX;
    CoordRelatY=CoordNewY-CoordAntY;
    
    //MovMotorA y MovMotorB son delta del motor A y delta del motor B para saber cuanto los tenemos que mover
    MovMotorA=CoordRelatX+CoordRelatY;
    MovMotorB=CoordRelatX-CoordRelatY;
    //Si el delta es negativo la direccion es 1
    if(MovMotorA<0)  dirA=adelante;
         else dirA=atras;

    if (MovMotorB<0) dirB=adelante;
    else dirB=atras;
    
    //Guardamos las coordenadas actuales para usarlas posteriormente
    CoordAntX=CoordNewX;
    CoordAntY=CoordNewY;

    //Si el delta es negativo lo multiplicamos por -1 para volverlo positivo
    if (MovMotorA<0) MovMotorA=MovMotorA*(-1);
    if (MovMotorB<0) MovMotorB=MovMotorB*(-1);

    //Regla de tres para obtener pasos necesarios
    //Con 5 pasos recorre 1mm (distancia*5)
    pasosA= (MovMotorA*NumPasos);
    pasosB= (MovMotorB*NumPasos);
    
    salidaDirA=dirA;
    salidaDirB=dirB;
}

unsigned int ContarPulsos(unsigned int pasosA){
    
    PasosActualesA=0;
    ons=0;
    enableA=LOW;
    while(PasosActualesA<pasosA)
    {
        if (PORTCbits.CCP1==1) OneShot();
        if(ons==1) ResetOneShot();
    }
    
    enableA=HIGH;    
}
void OneShot(void){
    if(ons==1) return;
    PasosActualesA++;
    ons=1;
    return;
}
void ResetOneShot(void){
    if(PORTCbits.CCP1==1)return;
    if(PORTCbits.CCP1==0)ons=0;
    return;
}