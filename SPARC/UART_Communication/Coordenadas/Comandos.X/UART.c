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


void UARTConfi(int BAUD){
    //Configuracion de pines
    TRISCbits.RC6=0; //RC6= Tx
    TRISCbits.RC7=1; //RC7= Rx
  
    SPBRG = (unsigned char)((_XTAL_FREQ/BAUD)/64)-1;
    TXSTAbits.BRGH = 0; //Low speed
    TXSTAbits.SYNC = 0; //Asincrono
    RCSTAbits.SPEN = 1; //Habilitar Tx y Rx
    
    //Transmisión
    TXSTAbits.TX9 = 0; //8 bits 
    TXSTAbits.TXEN = 1; //Activar transmisión
    
    //Recepción
    RCSTAbits.RC9 = 0; //8 bits
    RCSTAbits.CREN = 1; //Activamos recepción   
}

void UARTWrite(char data){
    while(!PIR1bits.TXIF);
    TXREG= data; 
 
}

char UARTRead(void){
    unsigned char Lecture;
    if(RCSTAbits.OERR == ON)                    //Error has ocurred
    {
        TXSTA1bits.TXEN = OFF;
        RCSTA1bits.CREN = OFF;
        __delay_us(500);
        TXSTA1bits.TXEN = ON;
        RCSTA1bits.CREN = ON;
    }
    while (PIR1bits.RCIF == 0);          // Mientras RCRGEG1 este vacio has nada hasta                
 
    Lecture = RCREG; // se guarda lo que llego de RCREG1 en viene
    RCREG = 0; //Se resetea el registro recibidor
    return Lecture;  
}