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
    float negros = totalPixeles -> totalNegros;
    float todos = totalPixeles -> totalBlancos + totalPixeles -> totalNegros;
    int cantidadImagenes;
    int porcentaje = (negros/todos)*100;
    totalPixeles -> porcentaje = porcentaje;

    if(porcentaje > UMBRAL){
        printf("---------------------------------------------------------------------------------------\n");
        printf("Imagen %d: Nearly Black positivo con porcentaje (pixelesNegros/totalePixeles) de: %d   | \n", numeroImagen, porcentaje);
        printf("---------------------------------------------------------------------------------------\n");
        printf("\n"); 
    }
    else{
        printf("---------------------------------------------------------------------------------------\n");
        printf("Imagen %d: Nearly Black negativo con porcentaje (pixelesNegros/totalePixeles) de: %d   | \n", numeroImagen, porcentaje);
        printf("---------------------------------------------------------------------------------------\n");
        printf("\n");
    }
}
