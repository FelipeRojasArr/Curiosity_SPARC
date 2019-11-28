#include <pic18f4550.h>
#include <xc.h>
#include <stdint.h>
#include "cases.h"

void verification(void){ 
    NextState = iddle_State;
    switch(NextState)
		{
            case iddle_State:{
                NextState= start();
            }
            
            case wait_cmd_State:{
                NextState=cmd();
            }
            
            case validate_Par_State:{
                NextState=Par_Validated();
            }
            
            case validate_Instruct_State:{
                NextState=Ins_Validated();
            }
            
            case validate_Coord_State:{
                NextState=Coord_Validated();
            }
            
            case end_State:{
                end();
            }break;
            
            default: break;  
    }
}