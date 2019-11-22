<<<<<<< HEAD
// Modified program using pointers
#include <stdio.h>
#include <stdint.h>

// add is the short name for address
void coord(int* x, int* y)
{
	*x=301;
	*y=301;

	while(*x>=300 || *y>=300){
	// a is stored in the address pointed
		// by the pointer variable *add_great
		uint8_t buffer [8];
        uint8_t read;
        printf("\nCoordenada x:");
        for(int i=0; i<=7; i++){
            scanf("%c", &read);
            buffer[i]=read-48;
            if(i==4){
                printf("\nCoordenada y:");
            }
        }
		*x = 1*buffer[3] + 10*buffer[2] + 100*buffer[1];
		*y = 1*buffer[7] + 10*buffer[6] + 100*buffer[5];

		if(*x>300 || *y>300){ printf("\nError. Ingrese de nuevo.\n");}
	}

}

// Driver code
int main()
{
     uint8_t rv; //receive value
    int cx;
    int cy;
=======
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main()
{
    uint8_t rv; //receive value

>>>>>>> Coord-new
    printf("Press I if you want to initiate\n" );
    //aqui iria la lectura serial
   while(1){
    scanf("%c", &rv );
   // printf("%d", rv);

        if((rv==73 || rv == 105)) {
<<<<<<< HEAD
        coord(&cx, &cy);
        printf("\nCoordenada en x= %d", cx);
        printf("\nCoordenada en y= %d", cy);
=======
            coordinates();
>>>>>>> Coord-new

        }

        else{
            printf("\nwaiting...");
        }
   }
<<<<<<< HEAD

}

=======
}

coordinates(){
    uint8_t buffer [6];
    uint8_t read;
    printf("\nCoordenada x:");
    for(int i=0; i<=8; i++){
        scanf("%c", &read);
        buffer[i]=read-48;
        if(i==4){
            printf("\nCoordenada y:");
        }
    }
    uint16_t x = 1*buffer[3] + 10*buffer[2] + 100*buffer[1];
    uint16_t y = 1*buffer[7] + 10*buffer[6] + 100*buffer[5];

   printf("\nCoordenada en x= %d", x);
   printf("\nCoordenada en y= %d", y);

}
>>>>>>> Coord-new
