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

/*Valores de configuracion PWM*/
#define PR2VALUE 0xF9 /*PR2 VALUE*/
#define CCPRXL 0x7D    /*CCPR1L VALUE*/

/*Valores de salida de PWM*/
# define NumPasos 5
# define positivo 1
# define negativo 0
# define HIGH 1
# define LOW 0
# define INPUT 1
# define OUTPUT 0

/*PUERTO DE PWM*/
# define salidaDirA PORTDbits.RD0 /*Salida del dirA*/
# define salidaDirB PORTDbits.RD1 /*Salida del dirB*/

# define pulsosA PORTCbits.RC1 /*Salida del PWM1*/
# define pulsosB PORTCbits.RC2 /*Salida del PWM2*/

# define enableA PORTCbits.RC6 /*Enable del PWM1*/
# define enableB PORTCbits.RC7 /*Enable del PWM2*/

/*FUNCIONES PWM*/
void PWM(void)
int PWMx (int distancia);
int PWMy (int distancia);
int ContarPulsos(int pasos);
void OneShot(void);
void ResetOneShot(void);

/* DECLARACION DE VARIABLES */

    /*Coordenadas anteriores*/
    unsigned int CoordAntX;
    unsigned int CoordAntY;
    
    /*Coordenadas relativas*/
    int CoordRelatX;
    int CoordRelatY;
    
    /*Contador de pasos recorridos*/
    int pasosRecorridos;
    
     /*Pasos actuales*/
    unsigned int PasosActuales;
  
