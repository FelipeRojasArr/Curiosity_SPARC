#include <stdio.h>
#include <stdint.h>
//Different state of ATM machine
typedef enum
{
    Iddle_State,
	wait_cmd_State,
	validate_Par_State,
	error_Par_State,
	validate_Instruct_State,
	error_Instruct_State,
	validate_Coord_State,
	error_Coord_State,
	validate_Actuator_State,
	error_Actuator_State,
	end_State,


}systemState;

int main() {

	systemState NextState = Iddle_State;

    int Par1,letter,cord_x, cord_y,Par2;
		while(1)
	{

		switch(NextState)
		{
            case Iddle_State:
                {
                    NextState=wait_cmd_State;
                }
                break;
            case wait_cmd_State:
                {
                    printf("\nIngresa un comando:\n");
                    coord(&Par1,&letter,&cord_x, &cord_y, &Par2);
                    NextState=validate_Par_State;
                }

                break;
            case validate_Par_State:
                {
                        if(Par1==60 && Par2==62){
                        NextState=validate_Instruct_State;
                    }
                    else{
                        printf("\n\nError. Debe tener la forma <>");
                        NextState=error_Par_State;
                    }
                }
                break;
            case error_Par_State:
                {
                         printf("\n\nSe prende Led de parentesis");
                         NextState=wait_cmd_State;
                }
                break;
            case validate_Instruct_State:
                {
                     if(letter==99 || letter==67 || letter ==115 || letter== 83) {
                        NextState=validate_Coord_State;
                     }
                     else{
                        printf("\nInstruccion desconocida. Escriba C para click o S para slide");
                        NextState=error_Instruct_State;
                     }
                }
                break;
            case error_Instruct_State:
                {
                         printf("\n\nSe prende Led de instruccion");
                         NextState=wait_cmd_State;
                }
            case validate_Coord_State:
                {
                    if(cord_x<=300 && cord_y<=300){
                        NextState=end_State;
                    }
                    else{printf("\nError. Coordenada mayor a 300.");
                        NextState=error_Coord_State;

                    }
                }
            case error_Coord_State:
                {
                    printf("\n Se prende led coordenada");
                }
            case end_State:
                {
                    printf("\nComando correcto. Ahora los motores.");
                    NextState=wait_cmd_State;
                }
            default:
                break;

        }
    }
}
coord(int* P1, int*L, int* x, int* y, int*P2)
{


	// a is stored in the address pointed
		// by the pointer variable *add_great
		uint8_t buffer [9];
        uint8_t read;
        printf("\nComando:");
        for(int i=0; i<=8; i++){
            scanf("%c", &read);
            buffer[i]=read;
        }
        *P1= buffer[0];
        *L= buffer[1];
		*x = 1*(buffer[4]-48) + 10*(buffer[3]-48) + 100*(buffer[2]-48);
		*y = 1*(buffer[7]-48) + 10*(buffer[6]-48) + 100*(buffer[5]-48);
		*P2= buffer[8];



}
