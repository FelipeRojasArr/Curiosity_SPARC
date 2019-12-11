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
#include "PWM.h"


int coord(char* P1, char*L, uint16_t* x , uint16_t* y , char*P2){
		char buffer[EndCommandCharacter+1];
        char read;
        char flagBuffer = OFF;
        char counterRevision = 0;
        
        TURN_ON_RECEIVER
        
        for(int i=StartCommandCharacter; i<(EndCommandCharacter+1); i++){
            read= UARTRead(); 
            buffer[i]=read;
        
            
            if(i == (EndCommandCharacter))
            {
                TURN_OFF_RECEIVER
                TURN_OFF_GREEN_LED
            }
        }
        
        if(RCSTAbits.OERR == ON)                    //Error has ocurred
        {
            TXSTA1bits.TXEN = OFF;
            RCSTA1bits.CREN = OFF;
            __delay_ms(15);
            TXSTA1bits.TXEN = ON;
            RCSTA1bits.CREN = ON;     
        }
        
        *P1= buffer[StartCommandCharacter];
        *L= buffer[InstructionCharacter];
        *P2= buffer[EndCommandCharacter];
        
        for(char n=CharacterX1; n<(CharacterY3+1); n++)
        {   
            if(buffer[n] <= MAXIMAL_ASCII_NUMBER && buffer[n] >= MINIMAL_ASCII_NUMBER)
            {
                counterRevision++;
            }
        }    
            if(counterRevision == ALL_COORDINATES)
            {
                flagBuffer = ON;
            }
            
            else
            {
                return FALSE;
            }
        
        if(flagBuffer == ON)
        {
            *x = UNIT*(buffer[CharacterX3]-FIRST_ASCII_NUMBER) + TEN*(buffer[CharacterX2]-FIRST_ASCII_NUMBER) + HUNDRED*(buffer[CharacterX1]-FIRST_ASCII_NUMBER);
            *y = UNIT*(buffer[CharacterY3]-FIRST_ASCII_NUMBER) + TEN*(buffer[CharacterY2]-FIRST_ASCII_NUMBER) + HUNDRED*(buffer[CharacterY1]-FIRST_ASCII_NUMBER);
            
            return TRUE;
        }  
}

