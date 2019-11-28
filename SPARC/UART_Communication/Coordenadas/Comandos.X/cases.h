int coord(char* P1, char* L, unsigned short* x, unsigned short* y, char* P2);

char Par1;
char letter;
unsigned short cord_x;
unsigned short cord_y;
char Par2;

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

