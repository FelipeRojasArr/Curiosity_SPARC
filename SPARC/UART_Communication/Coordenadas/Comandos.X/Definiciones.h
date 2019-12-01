
/**************CONFIGURACION***************/
#define FREC_CRISTAL 8000000L
#define INITIAL_FRAME 0X3C
#define ENDING_FRAME 0x3E
#define LETTER_C   0x43
#define LETTER_S   0x53

/****************PUERTOS*******************/

/*PWM*/
# define salidaDirA PORTDbits.RD0 /*Salida del dirA*/
# define salidaDirB PORTDbits.RD1 /*Salida del dirB*/

# define pulsosA PORTCbits.RC1 /*Salida del PWM1*/
# define pulsosB PORTCbits.RC2 /*Salida del PWM2*/

# define enableA PORTCbits.RD2 /*Enable del PWM1*/
# define enableB PORTCbits.RD3 /*Enable del PWM2*/

/*Switches*/
# define LimitSwitch1 PORTCbits.RB0 
# define LimitSwitch2 PORTCbits.RB1 
# define SwitchParar  PORTCbits.RB2

/*LED's*/
# define LedRojo PORTCbits.RD4 
# define LedVerde PORTCbits.RD5
# define LedAzul PORTCbits.RD6

/*Solenoide*/
# define Solenoide PORTCbits.RD7  

/**********DEFINICIONES GLOBALES*************/
# define HIGH 1
# define LOW 0
# define INPUT 1
# define OUTPUT 0

/******************PWM***********************/

/*Valores de configuracion PWM*/
#define PR2VALUE 0xF9 /*PR2 VALUE*/
#define CCPRXL 0x7D    /*CCPR1L VALUE*/

/*Valores de salida de PWM*/
# define NumPasos 5
# define positivo 1
# define negativo 0

/***************CALCULOS PWM***************/
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
