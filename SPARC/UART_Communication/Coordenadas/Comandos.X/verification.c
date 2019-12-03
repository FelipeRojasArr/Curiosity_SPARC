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

void verification(void){ 
    NextState = iddle_State;
    while(x==1){
    switch(NextState)
		{
            case iddle_State:{
                NextState= start();
            }
            break;
            case wait_cmd_State:{
                NextState=cmd();
            }
            break;
            case validate_Par_State:{
                NextState=Par_Validated();
            }
            break;            
            case validate_Instruct_State:{
                NextState=Ins_Validated();
            }
            break;
            case validate_Coord_State:{
                NextState=Coord_Validated();
            }
            break;
            case end_State:{
                end();
            }break;
            
        }
    }
}

