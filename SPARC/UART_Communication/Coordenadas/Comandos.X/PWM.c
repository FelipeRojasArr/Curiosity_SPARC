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

/*
 PWM function:
 -Get distance to travel
 -Determine turn direction for motors
 -Activates enable
 -Count steps
 -Update coordinates
*/

void PWM()
{
    FlagDirectionX= POSITIVE;
    FlagDirectionY= POSITIVE;
    
    // Get reltive coordenates //
    if(CoordAntX==ZERO_POSITION)
    {
        CoordRelatX=cord_x;                                                     //if prior X coordinate equals 0, input coordinate must be equal to relative
    }else{
        CoordRelatX=cord_x-CoordAntX;
    }
    
    /*Motor direcctions for X movement*/
    if (CoordRelatX<ZERO_POSITION)
    {
        DIR_A= ANTICLOCKWISE_TURN;
        DIR_B= ANTICLOCKWISE_TURN;
        CoordRelatX=CoordRelatX*CONSTANT_TO_ABSOLUTE_VALUE;                     //Absolute vale for relative coordinate X 
        FlagDirectionX= NEGATIVE;
    }
        else {
            DIR_A= CLOCKWISE_TURN;
            DIR_B= CLOCKWISE_TURN;
            FlagDirectionX= POSITIVE;
        } 
        
    StepsOnX=CoordRelatX*STEPS_PER_1MM;                                         //5 steps per 1mm ratio
    ContarPulsos(StepsOnX);
      
    /*X coordinate actualization*/      
    if(FlagDirectionX==NEGATIVE)
    {
        CoordAntX= CoordAntX-CoordRelatX;                                       //if distance is negative, it substracts
    }
    else{ 
        if(FlagDirectionX== POSITIVE)
        {
            CoordAntX=CoordAntX+CoordRelatX;
        }
    }
    
                         /* Y axis movement */
    /*if prior Y coordinate equals 0, input coordinate must be equal to relative*/
    if(CoordAntY==ZERO_POSITION)
    {
        CoordRelatY=cord_y;
    }
    else{
            CoordRelatY=cord_y-CoordAntY;
    }
    if(CoordRelatY<ZERO_POSITION)
    {
        DIR_A= CLOCKWISE_TURN;
        DIR_B= ANTICLOCKWISE_TURN;
        CoordRelatY=CoordRelatY*CONSTANT_TO_ABSOLUTE_VALUE;
        FlagDirectionY= NEGATIVE;
    }
    else{
        DIR_A= ANTICLOCKWISE_TURN;
        DIR_B= CLOCKWISE_TURN;
        FlagDirectionY= POSITIVE;  
     } 
   
    StepsOnY=CoordRelatY*STEPS_PER_1MM;
    ContarPulsos(StepsOnY);
    
    /*ACTUALIZAMOS COORDENADA Y */    
    if(FlagDirectionY== NEGATIVE)
    {
        CoordAntY= CoordAntY-CoordRelatY; //If distance is less than 0, it substracts
    }
    else{
            if(FlagDirectionY==POSITIVE)
            {
                CoordAntY=CoordAntY+CoordRelatY;
            }
        }
    
    return;
}
void ContarPulsos(int pasos)
{
    ActualSteps=ZERO;
    ons=OFF;
    ENABLE_A= ENABLE_STEPPER_MOTORS;
    ENABLE_B= ENABLE_STEPPER_MOTORS;
    while(ActualSteps< pasos)
    {
        if (PORTCbits.CCP1==ON)
        {
            OneShot();
        }
        if(ons==ON)
        {
            ResetOneShot();
        }
    }
    
    ENABLE_A= DISABLE_STEPPER_MOTORS;
    ENABLE_B= DISABLE_STEPPER_MOTORS;
    
    return;  
}

void OneShot(void)
{
    if(ons==ON)
    {
        return;
    }
    if(PORTCbits.CCP1==ON)
    {
        ActualSteps++;
        ons=ON;
    }
    return;
}

void ResetOneShot(void)
{
    if(PORTCbits.CCP1==ON)
    {
        return; 
    }
    if(PORTCbits.CCP1==OFF)
    {
        ons=OFF;
    }
    return;
}

void InicialX(void)
{
    DIR_A= ANTICLOCKWISE_TURN;
    DIR_B= ANTICLOCKWISE_TURN;
    while(CoordAntX!=ZERO_POSITION){
        if(CoordAntX==ZERO_POSITION)
        {
            ENABLE_A= DISABLE_STEPPER_MOTORS;
            ENABLE_B= DISABLE_STEPPER_MOTORS;
        }else{ 
            if(CoordAntX!=ZERO_POSITION)
            {
                ENABLE_A= ENABLE_STEPPER_MOTORS;
                ENABLE_B= ENABLE_STEPPER_MOTORS; 
            }
        }
    }
}

void InicialY(void)
{ 
    DIR_A= CLOCKWISE_TURN;
    DIR_B= ANTICLOCKWISE_TURN;  
    
    do{
    ENABLE_A= ENABLE_STEPPER_MOTORS;
    ENABLE_B= ENABLE_STEPPER_MOTORS;
    }while(CoordAntY!=ZERO_POSITION);
    
    ENABLE_A= DISABLE_STEPPER_MOTORS;
    ENABLE_B= DISABLE_STEPPER_MOTORS;
    
}

void GoToInitialXPosition(void)
{
    DIR_A= CLOCKWISE_TURN;
    DIR_B= CLOCKWISE_TURN;
    ContarPulsos(MOVE_5MM);
    ENABLE_A= DISABLE_STEPPER_MOTORS;
    ENABLE_B= DISABLE_STEPPER_MOTORS;
    CoordAntX = ZERO_POSITION;
}

void GoToInitialYPosition(void)
{
    DIR_A= ANTICLOCKWISE_TURN;
    DIR_B= CLOCKWISE_TURN; 
    ContarPulsos(MOVE_5MM);
    ENABLE_A= DISABLE_STEPPER_MOTORS;
    ENABLE_B= DISABLE_STEPPER_MOTORS;
    CoordAntY = ZERO_POSITION;
}

