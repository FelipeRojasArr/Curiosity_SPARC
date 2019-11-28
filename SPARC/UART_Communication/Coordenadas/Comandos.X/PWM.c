#include "PWM.h"
#include <xc.h>
#include "config.h"
int PWMx (int distancia){
    if (distancia<0){
        salidaDirA=0;
        salidaDirB=0;
        distancia=distancia*(-1);
    }
    else {
        salidaDirA=1;
        salidaDirB=1;
    } 
    int pasos= ContarPulsos(distancia);
    return(pasos);   
}

int PWMy (int distancia){
    if (distancia<0){
        salidaDirA=0;
        salidaDirB=1;
        distancia=distancia*(-1);
    }
    else {
        salidaDirA=1;
        salidaDirB=1;
    } 
   int pasos= ContarPulsos(distancia);
    return(pasos);   
}
int ContarPulsos(int pasos){
    PasosActuales=0;
    ons=0;
    enableA=0;
    while(PasosActuales<= pasos)
    {
        if (PORTCbits.CCP1==1) OneShot();
        if(ons==1) ResetOneShot();
    }
    
    enableA=1;
    return(PasosActuales);  
}
void OneShot(void){
    if(ons==1) return;
    if(PORTCbits.CCP1==1)
    {
        PasosActuales++;
        ons=1;
    }
}
void ResetOneShot(void){
    if(PORTCbits.CCP1==1)return;
    if(PORTCbits.CCP1==0)ons=0;
}