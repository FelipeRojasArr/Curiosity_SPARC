#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main()
{
    uint8_t rv; //receive value

    printf("Press I if you want to initiate\n" );
    //aqui iria la lectura serial
   while(1){
    scanf("%c", &rv );
   // printf("%d", rv);

        if((rv==73 || rv == 105)) {
            coordinates();

        }

        else{
            printf("\nwaiting...");
        }
   }
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
