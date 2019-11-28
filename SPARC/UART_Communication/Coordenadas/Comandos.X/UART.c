#include <xc.h>
#include "config.h"
#include "UART.h"

void UARTConfi(int BAUD){
    //Configuracion de pines
    TRISCbits.RC6=0; //RC6= Tx
    TRISCbits.RC7=1; //RC7= Rx
  
    SPBRG = (unsigned char)((FREC_CRISTAL/BAUD)/64)-1;
    TXSTAbits.BRGH = 0; //Low speed
    TXSTAbits.SYNC = 0; //Asincrono
    RCSTAbits.SPEN = 1; //Habilitar Tx y Rx
    
    //Transmisi�n
    TXSTAbits.TX9 = 0; //8 bits 
    TXSTAbits.TXEN = 1; //Activar transmisi�n
    
    //Recepci�n
    RCSTAbits.RC9 = 0; //8 bits
    RCSTAbits.CREN = 1; //Activamos recepci�n   
}

void UARTWrite(char data){
    while(!PIR1bits.TXIF);
    TXREG= data; 
    
}

char UARTRead(void){
    while(!RCIF);
    return RCREG; 
}