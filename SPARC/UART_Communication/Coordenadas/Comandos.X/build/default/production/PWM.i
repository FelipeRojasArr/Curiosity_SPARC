# 1 "PWM.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "PWM.c" 2
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
