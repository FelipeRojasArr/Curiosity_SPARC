#include <pic18f4550.h>
#include <xc.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
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
    while(!RCIF);
    return RCREG; 
}