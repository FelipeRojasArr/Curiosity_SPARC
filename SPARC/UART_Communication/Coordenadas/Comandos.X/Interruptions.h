#ifndef INTERRUPTIONS_HEADER

#define BUTTON_STOP PORTBbits.RB0
#define BUTTON_MOTORY PORTBbits.RB1
#define BUTTON_MOTORX PORTBbits.RB2

void InterruptionsConfiguration(void);
void buttonInterruptionConfiguration(void);

#endif