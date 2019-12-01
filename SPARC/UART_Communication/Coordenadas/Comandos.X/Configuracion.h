/**************CONFIGURACION***************/
#define _XTAL_FREQ 4000000UL
#define INITIAL_FRAME 0X3C
#define ENDING_FRAME 0x3E
#define LETTER_C   0x43
#define LETTER_S   0x53

#pragma config PLLDIV = 2
#pragma config FOSC = INTOSCIO_EC
#pragma config WDT = OFF  
#pragma config PBADEN = OFF   
#pragma config LVP = OFF  
#pragma config MCLRE = OFF