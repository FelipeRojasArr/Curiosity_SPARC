#include <xc.h>

//OSCILLATOR SOURCE AND DIGITAL I/O CONFIGURATION BITS
//====================================================
#pragma config	FOSC = INTOSCIO_EC  //CONFIG1H (0-3) = 0010: Internal oscillator, port function on RA6, EC used by USB (INTIO)..
#pragma config	MCLRE = ON          // CONFIG3H.7 = 1: Pin de RESET habilitado y Entrada RE3 desactivado.
#pragma config	PBADEN = OFF        // CONFIG3H.1 = 0: PORTB.0 -- PORTB.4 as Digital I/O.
#pragma config	LVP = OFF           // CONFIG3H.2 = 0: Single-Supply ICSP disabled  so that PORTB.5 works as Digital I/O.

//PICIT-3 DEBUGGER SETUP CONFIGURATION BITS
//=========================================
#pragma config	WDT = OFF           // CONFIG2H (0) = 0: Watchdog Timer Disabled.

//=========================================
# include <time.h>
# include <pic18f4550.h>

void myHighPriorityInterruptCode(void);

__interrupt(high_priority)void high_isr(void){
     myHighPriorityInterruptCode();
   
}
// High Priority ISR declaration.


void MoveX(void);
void MoveY(void);

void myHighPriorityInterruptCode (void){
    if (INTCONbits.TMR0IF==1) // If timer0 flag is 1 interruption occurs
    {
        INTCONbits.TMR0IF=0;
        MoveX();
        TMR0L=30;
    }
    if (PIR1bits.TMR1IF==1) // If timer1 flag is 1 interruption occurs
    {
        PIR1bits.TMR1IF=0;
        MoveY();
    }
}
//=================================================
# define NumPasos 5
# define adelante 1
# define atras 0

//=================================================
// DECLARACION DE VARIABLES
// Coordenadas anteriores

    unsigned int CoordAntX=0;
    unsigned int CoordAntY=0;
    // Coordenadas absolutas dadas por el usuario
    unsigned int CoordNewY;
    unsigned int CoordNewX;
    // Coordenadas relativas
    int CoordRelatX;
    int CoordRelatY;
    // Movimiento de motores
    int MovMotorA;
    int MovMotorB;
    // Direccion de motores
    unsigned int dirA;
    unsigned int dirB;
// Pasos de motores
    unsigned int pasosA;
    unsigned int pasosB;
    // LEDs de prueba pulsos
    unsigned int LedIsOn2;
    unsigned int LedIsOn1;

void main(void){
    
   //CLOCK FREQUENCY CONFIGURATION
   //============================
   OSCCON = 0x60;                       // 4 MHz internal oscillator

   //DISABLE PORT's ANALOG FUNCTIONS
   //===============================
   CMCON = 0xFF;                        // Comparators OFF, to use PORT_Ds LSN
   CVRCONbits.CVREN = 0;                // Comparator Voltge Reference Module OFF
   ADCON1 = 0x0F;                       // All ports as DIGITAL I/O
   //////////////////////////////////////////////////////////////////
   TRISC=0;
      //Apago timers hasta que los configure
   //================================
    T0CONbits.TMR0ON=0; 
    T1CONbits.TMR1ON=0;
    
    // PERMITIMOS PRIORIDADES DE INTERRUPCIONES
    RCONbits.IPEN=1;
    INTCONbits.GIEH=1;
    
    //CONFIGURAMOS TIMER 0 
    // El timer 0 tiene un frecuencia de 15.26 Hz
    //Por lo tanto, activa la interrupción cada 0.0655s
    
    INTCON2bits.TMR0IP=1;               // high priority
    T0CONbits.T08BIT=1;                 // set timer 0 to 8 bits
    T0CONbits.T0CS=0;                   // use internal clock to increment timer
    INTCONbits.TMR0IE=1;                // enable interrupt
    T0CONbits.PSA=0;                    // use prescaler with timer 0
    
    T0CONbits.T0PS2=1;                  // estos 3 bits en conjunto establecen un preescaler de 1:256
    T0CONbits.T0PS1=1;
    T0CONbits.T0PS0=1;                  
                                        // end of configuration timer 0
    
    //Configuramos Timer1
    // El timer 1 tiene un frecuencia de 15.26 Hz
    //Por lo tanto, activa la interrupción cada 0.0655s
    PIE1bits.TMR1IE=1;                  // enable timer1 overflow interrupt
    IPR1bits.TMR1IP=1;                  // priority set to high
    
    T1CONbits.T1CKPS1=0;                // timer 1 prescale 1:1
    T1CONbits.T1CKPS0=0;
    
    T1CONbits.T1OSCEN=0;                // turn off separate oscillator that is internal to timer 1
    T1CONbits.TMR1CS=0;                 // use internal clock to increment timer 1
                                        // end of configuration timer 1
   //Solo voy a activar timer cuando ya tenga las coordenadas listas y la direccion del motor establecidas
   // Inicializo la suma en 0 y dentro de movex le pongo un if si ya llego a la cuenta , voy actualizando la posicion y cuando ya llegue, apago el if y el on
   //Prendo timers 
   //================================
    T0CONbits.TMR0ON=1; 
    T1CONbits.TMR1ON=1;
    
    //===============================================
    CoordRelatX=CoordNewX-CoordAntX;
    CoordRelatY=CoordNewY-CoordAntY;
    
    //dA y dB son delta del motor A y delta del motor B para saber cuanto los tenemos que mover
    MovMotorA=CoordRelatX+CoordRelatY;
    MovMotorB=CoordRelatX-CoordRelatY;
    //Si el delta es negativo la direccion es 1
    if(MovMotorA<0) dirA=adelante;
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
     
      while(1){
        
    }
    
}
void MoveX(void){
   if(LedIsOn1==0) {
       PORTCbits.RC1=1;
       LedIsOn1=1;
   }
   else if(LedIsOn1==1){
        PORTCbits.RC1=0;
       LedIsOn1=0;
   }
}
void MoveY(void){
       if(LedIsOn2==0) {
       PORTCbits.RC0=1;
       LedIsOn2=1;
   }
   else if(LedIsOn2==1){
        PORTCbits.RC0=0;
       LedIsOn2=0;
   }
}