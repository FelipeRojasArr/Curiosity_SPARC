#include <xc.h>
#include <stdint.h>

#pragma config OSC = IRCIO67       //CONFIG1H (0-3) = 0010: INTIO2 oscillator, Internal oscillator block, port function on RA6 and RA7.
#pragma config MCLRE    = OFF        //Master Clear Reset activado
#pragma config PBADEN   = OFF       //Hace que los puertos A y B sean digitales
#pragma config LVP      = OFF       //Low-voltage Programming desactivado */

//#define DEBUG                       //Debug control

#define BAUD                        9600
#define _XTAL_FREQ                  4000000     //Frecuencia de 4MHz  
#define ON                          1
#define OFF                         0
#define BAUD_RATE_CONSTANT          103         //Para 9600
#define VALIDATE_START_FRAME        0x3C
#define VALIDATE_END_FRAME          0x3E
#define COORDINATE_INSTRUCTION      0x69
#define EEPROM_INSTRUCTION          0x65
#define MINIMAL_ASCII_NUMBER        0x30
#define MAXIMUM_ASCII_NUMBER        0x39
#define TRUE                        1
#define FALSE                       0

typedef unsigned int unit;
typedef unsigned char FLAG;
typedef unsigned char uchar;

enum CharactersOfASCII{
    StartCommandCharacter = 0,                     //Starts at 0
    InstructionCharacter,
    CharacterX1,
    CharacterX2,
    CharacterX3,
    CharacterY1,
    CharacterY2,
    CharacterY3,
    SelectTypeOfTouch,
    EndCommandCharacter                     //End Command equals to the size of the enum list
};

enum States{
    State_0 = 0,
    State_1,
    State_2,
    State_3,
    State_4,
    State_5
};

unsigned char ArrayForCommands[EndCommandCharacter+1];
unsigned int coordinate_X;
unsigned int coordinate_Y;
unsigned int coordinateVerification_X;
unsigned int coordinateVerification_Y;
unsigned char CurrentState;
unsigned char positionX_Hundreds;
unsigned char positionX_Tens;
unsigned char positionX_Unit;
unsigned char positionY_Hundreds;
unsigned char positionY_Tens;
unsigned char positionY_Unit;


unsigned char UARTRead();
void UARTWrite(unsigned char Write_UART);
void UARTconfi (void);

unsigned char FramesVerification(void);
int InstructionVerification(void);
//void coordinatesTransposition(unsigned char ArrayForCommands[]);
//int CoordinateVerification(void);
//int asciiToDecimal_Coordenate_X(unsigned char positionX_Hundreds,unsigned char positionX_Tens,unsigned char positionX_Unit);
//int asciiToDecimal_CoordenateY(unsigned char positionY_Hundreds,unsigned char positionY_Tens,unsigned char positionY_Unit);
char ASCIICoordinatesValidation_X(unsigned char positionX_Hundreds,unsigned char positionX_Tens,unsigned char positionX_Unit);
char ASCIICoordinatesValidation_Y(unsigned charpositionY_Hundreds,unsigned char positionY_Tens,unsigned char positionY_Unit);
void myPrintf(unsigned char *PointString);

void main(void) {
    
    unsigned char Write_UART; //Informacion por enviar 
    unsigned char CommandReceived;
    UARTconfi();                     
    while(1){
        CommandReceived = UARTRead();
        for(char i=0; i<(EndCommandCharacter+1); i++){
            ArrayForCommands[i] = CommandReceived;
        }
        
        if(FramesVerification(ArrayForCommands) == TRUE)
        {
            UARTWrite(0x47);
        }
        else
        {
            UARTWrite(0x45);
        }
       }
         /*switch(CurrentState){
            case 0:
                if(FramesVerification() == TRUE)
                {
                    CurrentState = State_1;
                }
                break;
                
            case 1:
                if(InstructionVerification() == TRUE)
                {
                    CurrentState = State_2;
                }
                break;
            case 2:
                if(CoordinateVerification() == TRUE)
                {
                    CurrentState = State_3;
                }
                break;
                
            case 3:
          return;
                break;
                
            default:
                CurrentState = State_0;
                break;
        
        }*/
    
   }

void UARTconfi (void) { 
    OSCCON = 0x60; //Parte de declarar el clk
    TRISCbits.RC6 = OFF; //Se declara el TX como output
    TRISCbits.RC7 = ON; //Se declara el RX como input
    SPBRG = BAUD_RATE_CONSTANT;        //Baudrate de 8 para 9600 de baudrate
    TXSTA1bits.BRGH = ON; // Highrate value  (1)
    BAUDCONbits.BRG16 = ON; //Se usa baudrate de 16 bits cuando activo

    TXSTA1bits.TX9 = OFF; // Transmision de 8 bits
    TXSTA1bits.TXEN = ON; //Se permite la transmision 
    TXSTA1bits.SYNC = OFF; //Modo asincrono 
    RCSTA1bits.SPEN = ON; // Enciedne TX y RX
    RCSTA1bits.RX9 = OFF; //Recepcion a 8 bits 
    RCSTA1bits.CREN = ON; //Habilita recibir
}

unsigned char UARTRead() {
    unsigned char Lecture;
    while (PIR1bits.RCIF == 0) {
        // Mientras RCRGEG1 este vacio nada hasta
    } //Cuando se lleno
    Lecture = RCREG1; // se guarda lo que llego de RCREG1 en viene
    RCREG1 = 0; //Se resetea el registro recibidor
    return Lecture;
}

void UARTWrite(unsigned char Write_UART) {
    while (TXSTA1bits.TRMT == 0) {
        //Mientres TSR este lleno no hace nada 
    } // Cuando se vacio 
    TXREG1 = Write_UART; // Se envia el nuevo caracter al registro de transmision USART
}

unsigned char FramesVerification()
{
    if(ArrayForCommands[CharacterX1] == VALIDATE_START_FRAME || ArrayForCommands[CharacterX2] == VALIDATE_END_FRAME || ArrayForCommands[CharacterX3])
    {
        return TRUE;
    }
    else
    {      
#ifdef DEBUG
        myPrintf("Frames Error");        
#else
            UARTWrite(0x45);
#endif //Debug
        return FALSE;
    }
}

int InstructionVerification(void)
{
    if(ArrayForCommands[InstructionCharacter] == COORDINATE_INSTRUCTION || ArrayForCommands[InstructionCharacter] == EEPROM_INSTRUCTION )
    {
        return TRUE;
    }
    else
    {      
#ifdef DEBUG
        myPrintf("Instruction Error");
#else
            UARTWrite(0x45);
#endif //Debug
        return FALSE;
    }
}

void coordinatesTransposition(ArrayForCommands[])
{
    positionX_Hundreds = ArrayForCommands[CharacterX1];
    positionX_Tens = ArrayForCommands[CharacterX2];
    positionX_Unit = ArrayForCommands[CharacterX3];

    positionY_Hundreds = ArrayForCommands[CharacterY1];
    positionY_Tens = ArrayForCommands[CharacterY2];
    positionY_Unit = ArrayForCommands[CharacterY3];
    
    return;
}

//int CoordinateVerificationX(void)
/*{
    if(ArrayForCommands[InstructionCharacter])
#ifdef DEBUG
        myPrintf("Coordinates exceeds size dimensions");        
#else
        UARTWrite(0x55);
#endif //DEBUG
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}*/

//int asciiToDecimal_Coordenate_X(positionX_Hundreds, positionX_Tens, positionX_Unit)
/*{   
       unit hundreds;                                       //Unidad de centenas
       unit tens;                                           //Unidad de decenas
       unit single;                                         //Unidad de unidades
       if(ASCIICoordinatesValidation(positionX_Hundreds, positionX_Tens, positionX_Unit) == TRUE)
       {
            hundreds = (unsigned int)(positionX_Hundreds - MINIMAL_ASCII_NUMBER);
            tens = (unsigned int)(positionX_Tens - MINIMAL_ASCII_NUMBER);
            single = (unsigned int)(positionX_Unit - MINIMAL_ASCII_NUMBER);
        
            coordinate_X = hundreds*100 + tens*10 + single;
            return coordinate_X;
       }
        else
        {

#ifdef DEBUG
        myPrintf("Coordinate X Error: some ASCII values does not correspond to numbers");
#else
            UARTWrite(0x33);
#endif //Debug
            return 0;   
        }
}*/

//int asciiToDecimal_CoordenateY(positionY_Hundreds, positionY_Tens, positionY_Unit)
/*{   
       unit hundreds;                                       //Unidad de centenas
       unit tens;                                           //Unidad de decenas
       unit single;                                         //Unidad de unidades
       if(ASCIICoordinatesValidation(ArrayForCommands[CharacterY1], ArrayForCommands[CharacterY2], ArrayForCommands[CharacterY3]) == TRUE)
       {
            hundreds = (unsigned int)(ArrayForCommands[CharacterY1] - MINIMAL_ASCII_NUMBER);
            tens = (unsigned int)(ArrayForCommands[CharacterY2] - MINIMAL_ASCII_NUMBER);
            single = (unsigned int)(ArrayForCommands[CharacterY3] - MINIMAL_ASCII_NUMBER);
        
            coordinate_Y = hundreds*100 + tens*10 + single;
            return coordinate_Y;
       }
        else
        {
#ifdef DEBUG
        myPrintf("Coordinate Y Error: some values does not correspond to numbers");
#else
            UARTWrite(0x44);
#endif //Debug
            return 0;   
        }
}*/

unsigned char ASCIICoordinatesValidation_X(positionX_Hundreds, positionX_Tens, positionX_Unit)
{
    FLAG ASCII_Coordinate_Minimal = 0;
    FLAG ASCII_Coordinate_Maximium = 0;
    if(positionX_Hundreds>= MINIMAL_ASCII_NUMBER || positionX_Tens>= MINIMAL_ASCII_NUMBER || positionX_Unit>= MINIMAL_ASCII_NUMBER)
    {        
        FLAG ASCII_Coordinate_Minimal = 1;
    }
    if(positionX_Hundreds<= MAXIMUM_ASCII_NUMBER || positionX_Tens<= MAXIMUM_ASCII_NUMBER || positionX_Unit<= MAXIMUM_ASCII_NUMBER)
    {
        FLAG ASCII_Coordinate_Maximium = 1;
    }

    if(ASCII_Coordinate_Maximium == 1 && ASCII_Coordinate_Minimal == 1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    
}

char ASCIICoordinatesValidation_Y(positionY_Hundreds, positionY_Tens, positionY_Unit)
{
    FLAG ASCII_Coordinate_Minimal = 0;
    FLAG ASCII_Coordinate_Maximium = 0;
    if(positionY_Hundreds>= MINIMAL_ASCII_NUMBER || positionY_Tens>= MINIMAL_ASCII_NUMBER || positionY_Unit>= MINIMAL_ASCII_NUMBER)
    {        
        FLAG ASCII_Coordinate_Minimal = 1;
    }
    if(positionY_Hundreds<= MAXIMUM_ASCII_NUMBER || positionY_Tens<= MAXIMUM_ASCII_NUMBER || positionY_Unit<= MAXIMUM_ASCII_NUMBER)
    {
        FLAG ASCII_Coordinate_Maximium = 1;
    }

    if(ASCII_Coordinate_Maximium == 1 && ASCII_Coordinate_Minimal == 1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    
}
 
void myPrintf(unsigned char *PointString)
{
    for (unsigned char i = 0; i < 255; i++) {
        if (PointString[i] == NULL) {
            break;
        } else
            UARTWrite(PointString[i]);
    }
}

/*void scanf(unsigned char *guardarscan, unsigned char numcaracteres)
{
    for (unsigned char i = 0; i < numcaracteres; i++) {
        guardarscan[i] = receive();
    }
}*/