#include <xc.h>
#include <stdint.h>

#define  BAUD 9600
#define _XTAL_FREQ  4000000 //Frecuencia de 4MHz  

void UARTconfi (void); 
uint8_t UARTRead(void);
void UARTWrite(uint8_t txData);
void BITSCONFI(uint8_t X);

unsigned char init=0;//caracter de inicializacion
unsigned char Enviar;

void main(void) {
    OSCCON = 0x60; //Reloj interno a 4MHz
    UARTconfi (); //9600 BAUD, Tranmitir y recibir
    uint8_t rv; //receive value
    int cx;
    int cy;
    while(1){
        rv= UARTRead();//scanf("%c", &rv );

        if((rv==73 || rv == 105)) {

            coord(&cx, &cy);
        //printf("\nCoordenada en x= %d", cx);
        //printf("\nCoordenada en y= %d", cy);

        }
       /* else{
            printf("\nwaiting...");
        }*/
   }
}

void UARTconfi (void) { 
    ADCON1 = 0x0F; //COnfigurar los pin a digitales
    LATB=0; //Los pines b inicializados en 0
    TRISB=0x00; //Todo el puerto B es salida
    
    TRISCbits.RC6 = 0; //  Pin RC6 como salida digital para TX.
    TRISCbits.RC7 = 1; //  Pin RC7 como entrada digital para RX.
    
    TXSTAbits.TX9 = 0; // Transmision de 8 bits
    RCSTAbits.RX9 = 0; //Recepcion a 8 bits 
    TXSTAbits.TXEN = 1; //  Habilita Transmisi?n.
    TXSTAbits.SYNC = 0; //  Modo-As?ncrono	Full Duplex
    TXSTAbits.BRGH = 1; //  Modo-Baja Velocidad de Baudios.
    BAUDCONbits.BRG16 = 1; //  Baudios modo-16bits.
    RCSTAbits.SPEN = 1; //  Hbilita el M?dulo SSP como UART.
    RCSTAbits.CREN = 1; //Habilita recibir
    //  Escribe el valor necesario para configurar los Baudios a 9600.
    SPBRGH1:SPBRG1 = 103;
}

uint8_t UARTRead(void) {
    uint8_t X;
    if (PIR1bits.RCIF == 1){ // Si RCREG esta lleno (llego informacion)
        X = RCREG1; // se guarda lo que llego de RCREG1 en la variable de inicio
        RCREG1 = 0; //Se resetea el registro recibidor
    }
    return X;
}

coord(int* x, int* y){
	*x=301;
	*y=301;

	while(*x>300 || *y>300){ //para que se repita si x o y son mayores a 300
		uint8_t buffer [8];
        uint8_t read;
        for(int i=0; i<=7; i++){
            read=UARTRead();//scanf("%c", &read);
            buffer[i]=read-48;
        }
        
		*x = 1*buffer[3] + 10*buffer[2] + 100*buffer[1];
		*y = 1*buffer[7] + 10*buffer[6] + 100*buffer[5];

		//if(*x>300 || *y>300){ printf("\nError. Ingrese de nuevo.\n");}
        }
}