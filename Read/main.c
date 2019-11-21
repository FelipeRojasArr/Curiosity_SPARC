#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
int main()
{
    uint8_t rv; //receive value

    printf("Press I if you want to initiate\n" );
    //aqui iria la lectura serial
    scanf("%c", &rv );
   // printf("%d", rv);

        if(rv==73 || rv == 105) {
            coordinates();
        }

        else{
            printf("\nwaiting...");
        }

}

coordinates(){
    uint8_t buffer [6];
    uint8_t read;
    for(int i=0; i<=7; i++){
        scanf("%c", &read);
        buffer[i]=read-48;
    }
    uint16_t x = 1*buffer[1] + 10*buffer[2] + 100*buffer[3];
    uint16_t y = 1*buffer[4] + 10*buffer[5] + 100*buffer[6];

   printf("\nCoordenada en x= %d", x);
   printf("\nCoordenada en y= %d", y);

}
