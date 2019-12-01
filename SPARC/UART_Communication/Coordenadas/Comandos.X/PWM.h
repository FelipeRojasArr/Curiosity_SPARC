/*FUNCIONES PWM*/
void PWM(void);
int PWMx (int distancia);
int PWMy (int distancia);
int ContarPulsos(int pasos);
void OneShot(void);
void ResetOneShot(void);
int Movimiento(void);

/* DECLARACION DE VARIABLES */

    /*Coordenadas anteriores*/
    unsigned int CoordAntX;
    unsigned int CoordAntY;
    
    /*Coordenadas relativas*/
    int CoordRelatX;
    int CoordRelatY;
    
    /*Contador de pasos recorridos*/
    int pasosRecorridos;
    
     /*Pasos actuales*/
    unsigned int PasosActuales;
    unsigned int ons;