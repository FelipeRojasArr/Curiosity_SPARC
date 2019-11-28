#include <xc.h>
# define NumPasos 5
# define positivo 1
# define negativo 0
# define HIGH 1
# define LOW 0
# define INPUT 1
# define OUTPUT 0
# define salidaDirA PORTDbits.RD0 /*Salida del dirA*/
# define salidaDirB PORTDbits.RD1 /*Salida del dirB*/

# define pulsosA PORTCbits.RC1 /*Salida del PWM1*/
# define pulsosB PORTCbits.RC2 /*Salida del PWM2*/
# define enableA PORTCbits.RC6 /*Enable del PWM1*/
# define enableB PORTCbits.RC7 /*Enablr del PWM2*/
# define bit PORTCbits.RC0 /*bit de prueba*/

// DECLARACION DE VARIABLES
// Coordenadas anteriores

    unsigned int CoordAntX;
    unsigned int CoordAntY;
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
        
// Pasos actuales de motores
    unsigned int PasosActualesA;
    unsigned int PasosActualesB;
//    // LEDs de prueba pulsos
   unsigned int LedIsOn2;
   unsigned int LedIsOn1;
   unsigned int ons;
 