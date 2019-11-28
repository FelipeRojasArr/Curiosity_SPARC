#include <xc.h>
#include <stdint.h>
#include <string.h>
#include "config.h"
#include "UART.h"
#include "cases.h"

char init[10]="Waiting...";
char e_c[13]="Enter_command";
char Error[6]="Error1";
char Error2[6]="Error2";
char Error3[6]="Error3";
char okay[4]="Okay" ;




uint8_t start(){
     for(int i=0;i<10;i++){
        UARTWrite(init[i]);
    }
     PORTC = 0xff;
     return wait_cmd_State;
}


uint8_t cmd(){
    UARTWrite(13);
    PORTC = 0x00;
    for(int i=0;i<10;i++){
        UARTWrite(e_c[i]);
    }
    coord(&Par1,&letter,&cord_x, &cord_y, &Par2);
    PORTC =0Xff;
    return validate_Par_State;
}

uint8_t Par_Validated(){
    PORTC=0x00;
    if(Par1==INITIAL_FRAME && Par2==ENDING_FRAME){
        PORTC=0X02;
        return validate_Instruct_State;
    }
    else{
        for(int i=0;i<6;i++){
            UARTWrite(Error[i]);
        }
        PORTC= 0X04;
        return wait_cmd_State;
    } 
}

uint8_t Ins_Validated(){
    PORTC=0x00;
    if(letter==LETTER_C || letter== LETTER_S){
        PORTC=0X02;
        return validate_Coord_State;
    }
    else{
        for(int i=0;i<6;i++){
            UARTWrite(Error2[i]);
        }
        PORTC= 0X04;
        return wait_cmd_State;
    }
}

uint8_t Coord_Validated(void){
    PORTC=0x00;
    if(cord_x<=300 && cord_y<=300){
        PORTC=0X02;
        return end_State;
    }
    else{
        for(int i=0;i<6;i++){
            UARTWrite(Error2[i]);
        }
        PORTC= 0X04;
       return wait_cmd_State;
    }
   
}

uint8_t end(){
    for(int i=0;i<4;i++){
        UARTWrite(okay[i]);
    }
    PORTC=0XFF;
    return wait_cmd_State;
    
}

