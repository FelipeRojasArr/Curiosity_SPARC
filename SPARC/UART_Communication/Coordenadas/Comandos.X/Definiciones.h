#ifndef DEFINICIONES_HEADER
/****************PUERTOS*******************/

/*PWM*/
# define DIR_A PORTDbits.RD0 /*Salida del dirA*/
# define DIR_B PORTDbits.RD1 /*Salida del dirB*/

# define PULSOS_A PORTCbits.RC1 /*Salida del PWM1*/
# define PULSOS_B PORTCbits.RC2 /*Salida del PWM2*/

# define ENABLE_A PORTDbits.RD2 /*Enable del PWM1*/
# define ENABLE_B PORTDbits.RD3 /*Enable del PWM2*/

/*Switches*/
# define LIMIT_SWITCH_1 PORTBbits.RB0 
# define LIMIT_SWITCH_2 PORTBbits.RB1 
# define STOP_SWITCH  PORTBbits.RB2

/*LED's*/
# define RED_LED PORTDbits.RD4 
# define GREEN_LED PORTDbits.RD5
# define BLUE_LED PORTDbits.RD6

/*Solenoide*/
# define SOLENOIDE PORTDbits.RD7  

/*Turn on/off comunication*/
#define TURN_OFF_RECEIVER  RCSTAbits.CREN = 0;
#define TURN_ON_RECEIVER   RCSTAbits.CREN = 1;

/**********DEFINICIONES GLOBALES*************/
# define HIGH               1
# define LOW                0
# define INPUT              1
# define OUTPUT             0
# define OFF                0
# define ON                 1
# define TRUE               1
# define FALSE              0
# define HUNDRED            100
# define TEN                10
# define UNIT               1
# define FIRST_ASCII_NUMBER 48
# define ALL_COORDINATES    6

/******************PWM***********************/

/*Valores de configuracion PWM*/
#define PR2VALUE 0xF9 /*PR2 VALUE*/
#define CCPRXL 0x7D    /*CCPR1L VALUE*/


/*Valores de salida de PWM*/
# define NUM_PASOS 5
# define POSITIVO 1
# define NEGATIVO 0

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

#endif //DEFINICIONES_HEADER