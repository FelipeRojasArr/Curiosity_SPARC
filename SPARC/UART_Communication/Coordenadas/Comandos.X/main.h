#ifndef MAIN_HEADER

#define DEBUG

#define NUMBER_OF_ASCII_COORDINATES 3
#define HUNDRED_NUMBER_POISITION    0
#define TENS_NUMBER_POISITION       1
#define UNIT_NUMBER_POISITION       2


//VALORES ASCII
#define COMA                        0x2C
#define SALTO_RENGLON               0x0A
#define COMMAND_ERROR               0x26
#define FRAME_ERROR                 0x21
#define TYPE_OF_TOUCH_ERROR         0x2B
#define ENTER                       0x0D
#define Y_LIMITS                    300
#define X_LIMITS                    300

void GoToInitialYPosition(void);
void GoToInitialXPosition(void);
void PrintMyActulPosition(void);
void myPrintf(unsigned char *PointString);

#endif //MAIN_HEADER