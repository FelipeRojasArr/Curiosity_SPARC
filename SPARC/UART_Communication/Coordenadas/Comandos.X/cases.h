#ifndef CASES_HEADER

#define INITIAL_FRAME 0X3C
#define ENDING_FRAME 0x3E
#define CLICK_INSTRUCCTION   0x43
#define SLIDE_INSTRUCCTION   0x53
#define MAXIMAL_ASCII_NUMBER 57
#define MINIMAL_ASCII_NUMBER 48


void verification(void);

int coord(char* P1, char* L, unsigned short* x, unsigned short* y, char* P2);

char Par1;
char letter;
unsigned int cord_x;
unsigned int cord_y;
char Par2;

int ControlFlagVerification;

typedef enum
{
    iddle_State,
	wait_cmd_State,
	validate_Par_State,
	validate_Instruct_State,
    validate_Coord_State,      
	end_State,

}systemState;

enum CharactersOfASCII{
    StartCommandCharacter = 0,               //Starts at 0
    InstructionCharacter,
    CharacterX1,
    CharacterX2,
    CharacterX3,
    CharacterY1,
    CharacterY2,
    CharacterY3,
    EndCommandCharacter                     //End Command equals to the size of the enum list
};

uint8_t start(void);
uint8_t cmd(void);
uint8_t Par_Validated(void);
uint8_t Ins_Validated(void);
uint8_t Coord_Validated(void);
void end(void);

systemState NextState;

uint8_t click;

#endif //CASES_HEADER