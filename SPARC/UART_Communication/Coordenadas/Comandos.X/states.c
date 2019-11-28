/* 
 * File:   states.c
 * Author: angie
 *
 * Created on 26 de noviembre de 2019, 09:00 PM
 */

#include <stdio.h>
#include <stdlib.h>


typedef enum
{
    Iddle_State,
	wait_cmd_State,
	validate_Par_State,
	validate_Instruct_State,
	validate_Coord_State,
	validate_Actuator_State,
	end_State,


}systemState;
int main(int argc, char** argv) {

    return (EXIT_SUCCESS);
}

