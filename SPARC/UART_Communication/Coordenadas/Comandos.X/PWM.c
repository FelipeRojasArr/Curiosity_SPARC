#include <pic18f4550.h>
#include "PWM.h"
#include <xc.h>
#include "cases.h"
#include "Definiciones.h"
#include "Configuracion.h"
#include "UART.h"


/*
  La función de PWM:
  - Obtiene la distancia total a recorrer.
  - Determina la dirección de los motores.
  - Activa los enables.
  - Cuenta los pasos.
  - Actualiza las coordenadas.
 */

void PWM(void){
    /*Obtenemos coordenadas relativas*/
    CoordRelatX=CoordAntX-cord_x;
    CoordRelatY=CoordAntY-cord_y; 
    
    /*PWM en X*/
    pasosRecorridos=PWMx(CoordRelatX);
    
    /*ACTUALIZAMOS COORDENADA X */      
    if(CoordRelatX<0) CoordAntX= CoordAntX-pasosRecorridos; //Si la distancia es negativa se resta
    else{ 
        if (CoordRelatX>0) CoordAntX=CoordAntX+pasosRecorridos;
    }
    
    /* PWM en Y*/    
    pasosRecorridos=PWMy(CoordRelatY);
    
    /*ACTUALIZAMOS COORDENADA Y */    
    if(CoordRelatY<0){
        CoordAntY = CoordAntY-pasosRecorridos; //Si la distancia es negativa se resta
    }
    else{ 
        if (CoordAntY>0) CoordAntY=CoordAntY+pasosRecorridos;// SI es positiva se suma
    }
    return;
}

int PWMx (int distancia){
    if (distancia<0){
        DIR_A=0;
        DIR_B=0;
        distancia=distancia*(-1);
    }
    else {
        DIR_A=1;
        DIR_B=1;
    } 
    int pasos= ContarPulsos(distancia);
    return(pasos);   
}

int PWMy (int distancia){
    if (distancia<0){
        DIR_A=0;
        DIR_B=1;
        distancia=distancia*(-1);
    }
    else {
        DIR_A=1;
        DIR_B=1;
     } 
   int pasos= ContarPulsos(distancia);
    return(pasos);   
}
int ContarPulsos(int pasos){
    PasosActuales=0;
    ons=0;
    ENABLE_A=0;
    ENABLE_B=0;
    while(PasosActuales<= pasos)
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
