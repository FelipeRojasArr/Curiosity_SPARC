/*
 * File:   UART_Communication.c
 * Author: felix
 *
 * Created on November 18, 2019, 10:31 AM
 */

#include <xc.h>
#include <stdint.h>

#define  BAUD 9600
#define _XTAL_FREQ  4000000 //Frecuencia de 4MHz  

void Communication_BITsConfiguration(void);

void main(void) {
	Communication_BITsConfiguration();
	return;
}


void Communication_BITsConfiguration(void){
	ADCON1 = 0x0F; 						//	COnfigurar los pin a digitales
    LATB=0; 									//	Los pines b inicializados en 0
    TRISB=0x00; 							//	Todo el puerto B es salida
    
    TRISCbits.RC6 = 0; 					//  Pin RC6 como salida digital para TX. Master/slave Mode Asíncrono
    TRISCbits.RC7 = 1; 					//  Pin RC7 como entrada digital para RX
    TXSTAbits.TX9 = 0; 					//  Transmision de 8 bits
	TXSTAbits.TXEN = 1; 				//  Habilita Transmisión.
    TXSTAbits.SYNC = 0; 				//  Modo-Asíncrono	Full Duplex
    TXSTAbits.BRGH = 1; 				//  Modo-Alta Velocidad de Baudios.
    RCSTAbits.SPEN = 1; 				//  Habilita el Módulo SSP como UART. Serial Port Enable
	RCSTAbits.RX9 = 0; 					//  Recepcion de 8 bits 
    
    BAUDCONbits.BRG16 = 1; 			//  Baudios modo-16bits.
    
    RCSTAbits.CREN = 1; 				//	 Habilita recibir
													//  Escribe el valor necesario para configurar los Baudios a 9600.
    SPBRGH1:SPBRG1 = 103;
	return;
}