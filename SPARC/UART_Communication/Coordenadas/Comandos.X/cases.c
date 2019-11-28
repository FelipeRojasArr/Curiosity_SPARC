#include <xc.h>
#include <stdint.h>
#include <string.h>
#include "config.h"
#include "UART.h"
#include "cases.h"

char init[10]="Waiting...";
char e_c[13]="Enter_command";
char Error[5]="Error";
char okay[4]="Okay" ;




void delay(void){             
    int i, j;
    for(i=0;i<5000;i++)
    {
        for(j=0;j<70;j++){}
    }   
}


uint8_t start(){
     for(int i=0;i<10;i++){
        UARTWrite(init[i]);
    }
     PORTC = 0xff;
     delay();
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
        delay();
        return validate_Instruct_State;
    }
    else{
        for(int i=0;i<5;i++){
            UARTWrite(Error[i]);
        }
        PORTC= 0X04;
        delay();
        return wait_cmd_State;
    } 
}

uint8_t Ins_Validated(){
    PORTC=0x00;
    if(letter==LETTER_C || letter== LETTER_S){
        PORTC=0X02;
        delay();
        return validate_Coord_State;
    }
    else{
        for(int i=0;i<5;i++){
            UARTWrite(Error[i]);
        }
        PORTC= 0X04;
        delay();
        return wait_cmd_State;
    }
}

uint8_t Coord_Validated(void){
    PORTC=0x00;
    if(cord_x<=300 && cord_y<=300){
        PORTC=0X02;
        delay();
        return end_State;
    }
    else{
        for(int i=0;i<5;i++){
            UARTWrite(Error[i]);
        }
        PORTC= 0X04;
        delay();
        return wait_cmd_State;
    }
   
}

uint8_t end(){
    for(int i=0;i<4;i++){
        UARTWrite(okay[i]);
    }
    PORTC=0XFF;
    delay();
    return wait_cmd_State;
    
}

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
