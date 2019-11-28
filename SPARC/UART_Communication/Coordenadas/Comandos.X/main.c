#include <pic18f4550.h>
#include <xc.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "config.h"
#include "UART.h"
#include "cases.h"

uint8_t start(void);
uint8_t cmd(void);
uint8_t Par_Validated(void);
uint8_t Ins_Validated(void);
uint8_t Coord_Validated(void);
uint8_t end(void);


systemState NextState;

void main(void) {
    OSCCON=0x72;
    UARTConfi(9600);
    TRISC=0X00;
    
    
    NextState = iddle_State;

    while(1){
          
       
        switch(NextState)
		{
            case iddle_State:{
                NextState= start();
            }break;
            
            case wait_cmd_State:{
                NextState=cmd();
            }break;
            
            case validate_Par_State:{
                NextState=Par_Validated();
            }break;
            
            case validate_Instruct_State:{
                NextState=Ins_Validated();
            }break;
            
            case validate_Coord_State:{
                NextState=Coord_Validated();
            }break;
            
            case end_State:{
                NextState=end();
            }break;
            
            default: break;

        }  
    }
    
    return;
}
