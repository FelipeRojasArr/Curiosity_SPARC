/*FUNCIONES PWM*/
void PWM(void);
void ContarPulsos(int pasos);
void OneShot(void);
void ResetOneShot(void);
int Movimiento(void);
void HaltMotors(void);

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
    /*extras*/
    unsigned int PasosX;
    unsigned int PasosY;
    unsigned int BanderaDisX;
    unsigned int BanderaDisY;