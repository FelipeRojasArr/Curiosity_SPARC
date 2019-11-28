#include <xc.h>
#include <stdlib.h>
#include <stdint.h>
#include "UART.h"
#include "cases.h"



int coord(char* P1, char*L, uint16_t* x , uint16_t* y , char*P2){
		char buffer [9];
        char read;
        //printf("\nComando:");
        for(int i=0; i<=8; i++){
            read= UARTRead(); //scanf("%c", &read);
            buffer[i]=read;
        }
        *P1= buffer[0];
        *L= buffer[1];
		*x = 1*(buffer[4]-48) + 10*(buffer[3]-48) + 100*(buffer[2]-48);
		*y = 1*(buffer[7]-48) + 10*(buffer[6]-48) + 100*(buffer[5]-48);
		*P2= buffer[8];
        
}
