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

void __interrupt() INT_ISR(void)
{
    if(INTCONbits.INT0IF == ON)
    {
        UARTWrite(0x45);
        GoToInitialXPosition();
        if(PORTBbits.RB0 == OFF)
        {
            __delay_ms(15);
            if(PORTBbits.RB0 == OFF)
            {
                INTCONbits.INT0IF = OFF;
            }
        }
    }
        
    if(INTCON3bits.INT1IF == ON)
    {
        UARTWrite(0x65);
        GoToInitialYPosition();
        if(PORTBbits.RB1 == OFF)
        {
            __delay_ms(15);
            if(PORTBbits.RB1 == OFF)
            {
                INTCON3bits.INT1IF = OFF;
            }
        }
    }
}
   
void main(void)
{    
    Configuracion();
    //InterruptionsConfiguration();
    
    TURN_ON_BLUE_LED
    CoordAntX=1;
    CoordAntY=1;
    
    ENABLE_A=DISABLE_STEPPER_MOTORS;
    ENABLE_B=DISABLE_STEPPER_MOTORS;
    
    //PRIMERO SE MUEVE EN X
    DIR_A= ANTICLOCKWISE_TURN;
    DIR_B= ANTICLOCKWISE_TURN;
    
    
    while(LIMIT_SWITCH_2==0)
    {
        ENABLE_A=ENABLE_STEPPER_MOTORS;
        ENABLE_B=ENABLE_STEPPER_MOTORS;
        myPrintf("Si entro a x");
    }
     ENABLE_A=DISABLE_STEPPER_MOTORS;
     ENABLE_B=DISABLE_STEPPER_MOTORS;
     if(LIMIT_SWITCH_2==1){
     CoordAntX=0;
     myPrintf("Salio de x");
     }
     
     // CAMBIA DIRECCION PARA MOVER Y
    DIR_A= CLOCKWISE_TURN;
    DIR_B= ANTICLOCKWISE_TURN; 
    
    while(LIMIT_SWITCH_1==0)
    {
        ENABLE_A=ENABLE_STEPPER_MOTORS;
        ENABLE_B=ENABLE_STEPPER_MOTORS;
        myPrintf("Si entro a y");
    }
    
     ENABLE_A=DISABLE_STEPPER_MOTORS;
     ENABLE_B=DISABLE_STEPPER_MOTORS;
     if(LIMIT_SWITCH_1==1) {
         CoordAntY=0;
         myPrintf("Salio de y");
     }
         
    while(1)
    { 
        TURN_ON_GREEN_LED
        ControlFlagVerification = ON;
        verification();
        PrintMyActulPosition();
        Movement();
        PrintMyActulPosition();
    }
}

void PrintMyActulPosition(void)
{
/*Imprimir en serial coordenada actualizada*/
        char a[NUMBER_OF_ASCII_COORDINATES];
        char b[NUMBER_OF_ASCII_COORDINATES];

        a[HUNDRED_NUMBER_POISITION]=(CoordAntX/100)+FIRST_ASCII_NUMBER;
        a[TENS_NUMBER_POISITION]=((CoordAntX%100)/10)+FIRST_ASCII_NUMBER;
        a[UNIT_NUMBER_POISITION]=((CoordAntX%100)%10)+FIRST_ASCII_NUMBER;

        b[HUNDRED_NUMBER_POISITION]=(CoordAntY/100)+FIRST_ASCII_NUMBER;
        b[TENS_NUMBER_POISITION]=((CoordAntY%100)/10)+FIRST_ASCII_NUMBER;
        b[UNIT_NUMBER_POISITION]=((CoordAntY%100)%10)+FIRST_ASCII_NUMBER;

        for(int i=0; i<NUMBER_OF_ASCII_COORDINATES; i++){

            UARTWrite(a[i]);
        }
        UARTWrite(COMA);
        for(int i=0; i<NUMBER_OF_ASCII_COORDINATES; i++){

            UARTWrite(b[i]);
        }
}

void myPrintf(unsigned char *PointString)
{
    for (unsigned char i = 0; i < MAX_SIZE_OF_UCHAR; i++) {
        if (PointString[i] == NULL) {
            break;
        } else
            UARTWrite(PointString[i]);
    }
}

