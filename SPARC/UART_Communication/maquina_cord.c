#include <xc.h>
#include <stdint.h>

#pragma config	OSC = IRCIO67       //CONFIG1H (0-3) = 0010: INTIO2 oscillator, Internal oscillator block, port function on RA6 and RA7.
#pragma config	MCLRE = ON          // CONFIG3H.7 = 1: Pin de RESET habilitado y Entrada RE3 desactivado.
#pragma config	PBADEN = OFF        // CONFIG3H.1 = 0: PORTB.0 -- PORTB.4 as Digital I/O.
#pragma config	LVP = OFF           // CONFIG3H.2 = 0: Single-Supply ICSP disabled  so that PORTB.5 works as Digital I/O.
#pragma config	WDT = OFF  
//Different state of ATM machine

#define  BAUD 9600
#define _XTAL_FREQ  4000000 

void UARTconfi (void); 
uint8_t UARTRead(void);
typedef enum
{
    Iddle_State,
	wait_cmd_State,
	validate_Par_State,
	validate_Instruct_State,
	validate_Coord_State,
	validate_Actuator_State,
	end_State,


}systemState;

int main() {
    PORTC = 0x00;                        // Initialize PORTC 
    LATC = 0x00;    
    TRISC =0X00;
    OSCCON = 0x60; //Reloj interno a 4MHz
    UARTconfi ();
   

	systemState NextState = Iddle_State;

    int Par1,letter,cord_x, cord_y,Par2;
		while(1)
	{

		switch(NextState)
		{
            case Iddle_State:
                {
                    NextState=wait_cmd_State;
                }
                break;
            case wait_cmd_State:
                {
                   // printf("\nIngresa un comando:\n");
                    coord(&Par1,&letter,&cord_x, &cord_y, &Par2);
                    NextState=validate_Par_State;
                    PORTC =0X00;
                }

                break;
            case validate_Par_State:
                {
                        if(Par1==60 && Par2==62){
                        NextState=validate_Instruct_State;
                    }
                    else{
                       // printf("\n\nError. Debe tener la forma <>");
                        NextState=wait_cmd_State;
                        PORTC=0X01;
                    }
                }
                break;
            case validate_Instruct_State:
                {
                     if(letter==99 || letter==67 || letter ==115 || letter== 83) {
                        NextState=validate_Coord_State;
                     }
                     else{
                       // printf("\nInstruccion desconocida. Escriba C para click o S para slide");
                        NextState=wait_cmd_State;
                        PORTC=0X02;
                     }
                }
                break;
           case validate_Coord_State:
                {
                    if(cord_x<=300 && cord_y<=300){
                        NextState=end_State;
                    }
                    else{
                        //printf("\nError. Coordenada mayor a 300.");
                        NextState=wait_cmd_State;
                        PORTC=0X03;

                    }
                }
                break;
                   case end_State:
                {
                    //printf("\n\nComando correcto. Ahora los motores.");
                    NextState=wait_cmd_State;
                    PORTC=0X08;
                }
                break;
            default:
                break;

        }
    }
}
coord(int* P1, int*L, int* x, int* y, int*P2)
{


	// a is stored in the address pointed
		// by the pointer variable *add_great
		uint8_t buffer [9];
        uint8_t read;
//        printf("\nComando:");
        for(int i=0; i<=8; i++){
            read= UARTRead();//scanf("%c", &read);
            buffer[i]=read;
        }
        *P1= buffer[0];
        *L= buffer[1];
		*x = 1*(buffer[4]-48) + 10*(buffer[3]-48) + 100*(buffer[2]-48);
		*y = 1*(buffer[7]-48) + 10*(buffer[6]-48) + 100*(buffer[5]-48);
		*P2= buffer[8];


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