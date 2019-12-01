#include <stdint.h>
void verification(void);

int coord(char* P1, char* L, unsigned short* x, unsigned short* y, char* P2);

char Par1;
char letter;
unsigned short cord_x;
unsigned short cord_y;
char Par2;

int x;

typedef enum
{
    iddle_State,
	wait_cmd_State,
	validate_Par_State,
	validate_Instruct_State,
	validate_Coord_State,
	validate_Actuator_State,
	end_State,

}systemState;

uint8_t start(void);
uint8_t cmd(void);
uint8_t Par_Validated(void);
uint8_t Ins_Validated(void);
uint8_t Coord_Validated(void);
void end(void);

systemState NextState;

uint8_t click;