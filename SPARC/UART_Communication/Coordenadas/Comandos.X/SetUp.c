void SetUp(void){
    //CLOCK FREQUENCY CONFIGURATION
   //============================
   OSCCON = 0x60;                       // 4 MHz internal oscillator

   //DISABLE PORT's ANALOG FUNCTIONS
   //===============================
   CMCON = 0xFF;                        // Comparators OFF, to use PORT_Ds LSN
   CVRCONbits.CVREN = 0;                // Comparator Voltge Reference Module OFF
   ADCON1 = 0x0F;                       // All ports as DIGITAL I/O
   
                              /*PWM*/
   //////////////////////////////////////////////////////////////////
   
    TRISC1 = OUTPUT;		/* Set CCP1 pin as output for PWM out */
    TRISC2 = OUTPUT;		/* Set CCP2 pin as output for PWM out */
    
    PR2 = PR2value;		// Load period value de formula
    
    /**** generate PWM on CCP1 ****/
    CCP1CON = 0x0C;	/* Set PWM mode and no decimal for PWM */ //PR2
    CCPR1L = CCPRXL;    /* load 50% duty cycle value */
    
    /**** generate PWM on CCP2 ****/
    CCP2CON = 0x0C;	/* Set PWM mode and no decimal for PWM */    
    CCPR2L = CCPRXL;	/* load 50% duty cycle value */
    
    /*configure Timer 2 for PWM*/
    T2CON = 0x03;		/* pre-scalar, timer2 is 4 */
    TMR2 = 0;		/* Clear Timer2 initially */
    TMR2ON = 1;		/* Timer ON for start counting*/
    ////////////////////////////////////////////////////////////////////
    
    //================================================
    /*DEFINIMOS COMO OUTPUTS LOS PINES DE LOS ENABLES*/
    TRISCbits.RC6 = OUTPUT;	/*EnableA*/	
    TRISCbits.RC7 = OUTPUT;	/*Enable B*/
}
