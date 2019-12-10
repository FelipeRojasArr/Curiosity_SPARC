#ifndef PWM_HEADER

#define MOVE_5MM 25

/*FUNCIONES PWM*/
    void PWM(void);
    void ContarPulsos(int pasos);
    void OneShot(void);
    void ResetOneShot(void);
    int Movement(void);


/* DECLARACION DE VARIABLES */
    /*Prior Coordinates*/
    unsigned int CoordAntX;
    unsigned int CoordAntY;
    
    /*Relative Coordinates*/
    int CoordRelatX;
    int CoordRelatY;
        
    /*Actual Steps*/
    unsigned int ActualSteps;
    unsigned int ons;
    
    /*Flags*/
    unsigned int StepsOnX;
    unsigned int StepsOnY;
    unsigned int FlagDirectionX;
    unsigned int FlagDirectionY;
    
#endif //PWM_HEADER