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

void SetUp(void);
int PWMx (int distancia);
int PWMy (int distancia);
int ContarPulsos(int pasos);

void OneShot(void);
void ResetOneShot(void);
int pasosRecorridos;
int PasosActuales;
 


void main(void){
    SetUp();
    CoordRelatX=(200);// Recorrido total requerido 
    CoordRelatY=800;
    CoordAntX=0;
    CoordAntX=0;

    //PWM en X
    pasosRecorridos=PWMx(CoordRelatX);
    
      
    if(CoordRelatX<0) CoordAntX= CoordAntX-pasosRecorridos; //Si la distancia es negativa se resta
    else{ 
        if (CoordRelatX>0) CoordAntX=CoordAntX+pasosRecorridos;
    }
//    //PWM en Y
    pasosRecorridos=PWMy(CoordRelatY);
    
    if(CoordRelatY<0) CoordAntY= CoordAntY-pasosRecorridos; //Si la distancia es negativa se resta
    else{ 
        if (CoordAntY>0) CoordAntY=CoordAntY+pasosRecorridos;
   }
    
}

void SetUp(void){
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
    
    //================================================
    /*DEFINIMOS COMO OUTPUTS LOS PINES DE LOS ENABLES*/
    TRISCbits.RC6 = OUTPUT;	/*EnableA*/	
    TRISCbits.RC7 = OUTPUT;	/*Enable B*/
    TRISCbits.RC0 = OUTPUT; /*Bit de prueba*/
}

int PWMx (int distancia){
    if (distancia<0){
        salidaDirA=0;
        salidaDirB=0;
        distancia=distancia*(-1);
    }
    else {
        salidaDirA=1;
        salidaDirB=1;
    } 
    int pasos= ContarPulsos(distancia);
    return(pasos);   
}

int PWMy (int distancia){
    if (distancia<0){
        salidaDirA=0;
        salidaDirB=1;
        distancia=distancia*(-1);
    }
    else {
        salidaDirA=1;
        salidaDirB=1;
    } 
   int pasos= ContarPulsos(distancia);
    return(pasos);   
}
int ContarPulsos(int pasos){
    PasosActuales=0;
    ons=0;
    enableA=0;
    while(PasosActuales<pasos)
    {
        if (PORTCbits.CCP1==1) OneShot();
        if(ons==1) ResetOneShot();
    }
    
    enableA=1;
    return(PasosActuales);  
}
void OneShot(void){
    if(ons==1) return;
    if(PORTCbits.CCP1==1)
    {
        PasosActuales++;
        ons=1;
    }
}
void ResetOneShot(void){
    if(PORTCbits.CCP1==1)return;
    if(PORTCbits.CCP1==0)ons=0;
}