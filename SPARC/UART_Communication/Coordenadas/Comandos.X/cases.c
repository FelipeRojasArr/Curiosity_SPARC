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


char init[10]="Waiting...";
char e_c[13]="Enter_command";
char Error[5]="Error";
char gracias[7]="Gracias" ;

uint8_t start()
{
    UARTWrite(13);
    for(int i=0;i<10;i++){
        UARTWrite(init[i]);
    }
     
    return wait_cmd_State;
}

uint8_t cmd()
{
    UARTWrite(13);
    
    for(int i=0;i<10;i++){
        UARTWrite(e_c[i]);
    }
    
    if(coord(&Par1,&letter,&cord_x, &cord_y, &Par2) == TRUE)
    {
        return validate_Par_State;
    }
    else
    {
        UARTWrite(13);
        for(int i=0;i<5;i++){
            UARTWrite(Error[i]);
        }
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
        UARTWrite(13);
        for(int i=0;i<5;i++){
            UARTWrite(Error[i]);
        }
        return wait_cmd_State;
    } 
}

uint8_t Ins_Validated()
{
    if(letter == CLICK_INSTRUCCTION)
    {
        click=1;
        return validate_Coord_State;
    }
    
    else if(letter== SLIDE_INSTRUCCTION)
    {
        click=0;
        return validate_Coord_State;
    }
    else
    {
        UARTWrite(13);
        for(int i=0;i<5;i++){
            UARTWrite(Error[i]);
        }
        return wait_cmd_State;
    }
}

uint8_t Coord_Validated()
{
    if(cord_x<=300 && cord_y<=300)
    {
        return end_State;
    }
    else
    {
        UARTWrite(13);
        for(int i=0;i<5;i++){
            UARTWrite(Error[i]);
        }
        return wait_cmd_State;
    }
}

void end()
{
    UARTWrite(13);
    for(int i=0;i<7;i++)
    {
        UARTWrite(gracias[i]);
    }
    ControlFlagVerification = OFF;
    return;
}

