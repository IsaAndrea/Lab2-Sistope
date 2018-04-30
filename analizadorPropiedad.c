#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <unistd.h>

/* Procedimiento que verifica y muestra por pantalla si la imagen corresponde o no a nearly black.
   ENTRADA:
        - Total de pixeles de la imagen.
        - Un entero que corresponde al umbral definido.
*/
void verificarNearlyBlack(bitmaptotal *totalPixeles, int UMBRAL, int numeroImagen){
    int tuberia[2];
    pid_t pid;
    float negros = totalPixeles -> totalNegros;
    float todos = totalPixeles -> totalBlancos + totalPixeles -> totalNegros;
    int porcentaje = (negros/todos)*100;
    if(porcentaje > UMBRAL){
        printf("-------------------------------------\n");
        printf("Imagen %d: Nearly Black Positivo    | \n", numeroImagen);
        printf("-------------------------------------\n");
        printf("\n");
        pipe(tuberia);
        pid = fork();
        if(pid == 0){
            //conectamos las tuberias
            //ejecutamos la funcion de escritura de imagen
        }

    }
    else{
        printf("-------------------------------------\n");
        printf("Imagen %d: Nearly Black Negativo    | \n", numeroImagen);
        printf("-------------------------------------\n");
        printf("\n");
        pipe(tuberia);
        pid = fork();
        if(pid == 0){
            //conectamos las tuberias
            //ejecutamos la funcion de escritura de imagen
        }
    }
    //esperamos que el proceso hijo termine
}
