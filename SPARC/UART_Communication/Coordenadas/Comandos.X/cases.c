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
#include "Interruptions.h"
#include "PWM.h"


uint8_t start()
{
    UARTWrite(ENTER);
    myPrintf("Waiting...");     
    return wait_cmd_State;
}

uint8_t cmd()
{
    UARTWrite(ENTER);
    myPrintf("Enter command");     
    
    if(coord(&Par1,&letter,&cord_x, &cord_y, &Par2) == TRUE)
    {
        return validate_Par_State;
    }
    else
    {
#ifdef DEBUG
        myPrintf("Commands were not recognized");
        UARTWrite(SALTO_RENGLON);
#else
        UARTWrite(COMMAND_ERROR);
        UARTWrite(SALTO_RENGLON);
#endif //DEBUG
        return wait_cmd_State;
    }
}

uint8_t Par_Validated()
{
    if(Par1==INITIAL_FRAME && Par2==ENDING_FRAME)
    {
        return validate_Instruct_State;
    }
    else
    {
#ifdef DEBUG
        myPrintf("Frames are not inserted correctly");
        UARTWrite(SALTO_RENGLON);
#else
        UARTWrite(FRAME_ERROR);
        UARTWrite(SALTO_RENGLON);
#endif //DEBUG
        
        
        return wait_cmd_State;
    } 
}

uint8_t Ins_Validated()
{
    if(letter == CLICK_INSTRUCCTION)
    {
        click=TOUCH;
        return validate_Coord_State;
    }
    
    else if(letter== SLIDE_INSTRUCCTION)
    {
        click=SLIDE;
        return validate_Coord_State;
    }
    else
    {

#ifdef DEBUG
        myPrintf("Touch Instrucction is not recognized");
        UARTWrite(SALTO_RENGLON);
#else
        UARTWrite(TYPE_OF_TOUCH_ERROR);
        UARTWrite(SALTO_RENGLON);
#endif //DEBUG
        return wait_cmd_State;
    }
}

uint8_t Coord_Validated()
{
    if(cord_x<=X_LIMITS && cord_y<=Y_LIMITS)
    {
        return end_State;
    }
    else
    {
#ifdef DEBUG
        myPrintf("Surpasses coordinates size");
        UARTWrite(SALTO_RENGLON);
#else
        UARTWrite(TYPE_OF_TOUCH_ERROR);
        UARTWrite(SALTO_RENGLON);
#endif //DEBUG
        return wait_cmd_State;
    }
}

void end()
{
    UARTWrite(ENTER);
#ifdef DEBUG
        myPrintf("Verify Completed");
        UARTWrite(SALTO_RENGLON);
#else
        UARTWrite(TYPE_OF_TOUCH_ERROR);
        UARTWrite(SALTO_RENGLON);
#endif //DEBUG
    ControlFlagVerification = OFF;
    return;
}

