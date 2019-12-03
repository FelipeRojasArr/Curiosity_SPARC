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

/*
  La función de PWM:
  - Obtiene la distancia total a recorrer.
  - Determina la dirección de los motores.
  - Activa los enables.
  - Cuenta los pasos.
  - Actualiza las coordenadas.
 */

void PWM(){
    
    BanderaDisX= POSITIVO;
    BanderaDisY= POSITIVO;
    
    // Obtenemos coordenadas relativas //
    
    /*Si la coordenada X anterior es cero la coordenada deseada es igual a la relativa*/
    if (CoordAntX==0) CoordRelatX=cord_x;
        else CoordRelatX=cord_x-CoordAntX;
        
    /*Definimos las direcciones de los motores para x*/
    if (CoordRelatX<0){
        DIR_A=0;
        DIR_B=0;
        CoordRelatX=CoordRelatX*(-1);
        BanderaDisX= NEGATIVO;
    }
        else {
            DIR_A=1;
            DIR_B=1;
            BanderaDisX= POSITIVO;
        } 
        
    PasosX=CoordRelatX*NUM_PASOS;                   //Relación 1mm a 5 pasos
    ContarPulsos(PasosX);
      
    /*ACTUALIZAMOS COORDENADA X */      
    if(BanderaDisX== NEGATIVO) CoordAntX= CoordAntX-CoordRelatX; //Si la distancia es negativa se resta
    else{ 
        if (BanderaDisX== POSITIVO) CoordAntX=CoordAntX+CoordRelatX;
    }
        
    //*********************************************
                         /* Y */
    
    /*Si la coordenada Y anterior es cero la coordenada deseada es igual a la relativa*/
    if (CoordAntY==0) CoordRelatY=cord_y;
        else CoordRelatY=cord_y-CoordAntY;
    
    if (CoordRelatY<0){
        DIR_A=0;
        DIR_B=1;
        CoordRelatY=CoordRelatY*(-1);
        BanderaDisY= NEGATIVO;
    }
    else {
        DIR_A=1;
        DIR_B=1;
         BanderaDisY= POSITIVO;  
     } 
   
    PasosY=CoordRelatY*NUM_PASOS;
    ContarPulsos(PasosY);
    
    /*ACTUALIZAMOS COORDENADA Y */    
    if(BanderaDisY== NEGATIVO) CoordAntY= CoordAntY-CoordRelatY; //Si la distancia es negativa se resta
    else{ 
        if (BanderaDisY== POSITIVO) CoordAntY=CoordAntY+CoordRelatY;
    }
    
    return;
}
int ContarPulsos(int pasos){
    PasosActuales=0;
    ons=0;
    ENABLE_A=0;
    ENABLE_B=0;
    while(PasosActuales< pasos)
    {
        if (PORTCbits.CCP1==1) OneShot();
        if(ons==1) ResetOneShot();
    }
    
    ENABLE_A=1;
    ENABLE_B=1;
    
    return(PasosActuales);  
}
void OneShot(void){
    if(ons==1) return;
    if(PORTCbits.CCP1==1)
    {
        PasosActuales++;
        ons=1;
    }
    return;
}
void ResetOneShot(void){
    if(PORTCbits.CCP1==1)return;
    if(PORTCbits.CCP1==0)ons=0;
    return;
}

/*void HaltMotors(void)
{
    ENABLE_A=1;
    ENABLE_B=1;
    UARTWrite(0x4B);
    TXSTAbits.TXEN = 0;
    RCSTAbits.CREN = 0;
}*/