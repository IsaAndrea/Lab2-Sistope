#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

/* Función que binariza una imágen grisasea.
   ENTRADA:
        - Estructura de una cabecera de informacion de un bitmap.
        - Un arreglo de pixeles grisaseos.
        - Un entero que representa al umbral.
        - Total de pixeles de la imagen.
   SALIDA:
        - Una matriz de pixeles binarizados.
*/
unsigned char *binarizarImagen(int binformacionTamano,int binformacionTotalBit,int *totalBlanco, int *totalNegro, unsigned char *data_grisaseo, int UMBRAL){
    int columnas;
    int contadorTotal = 0;
    int contadorNegros = 0;
    int contadorBlancos = 0;
    int filas = 0;
    unsigned char data, *binariosColor;
    binariosColor = (unsigned char *)malloc(binformacionTamano * sizeof(unsigned char));


    if(binformacionTotalBit == 32){
        for(filas = 0; filas < binformacionTamano; filas = filas + 4){
            if(data_grisaseo[filas] > UMBRAL){
                binariosColor[filas+3] = 255; 
                binariosColor[filas + 2] = 255;
                binariosColor[filas+ 1] = 255;
                binariosColor[filas] = 255;
                contadorBlancos++;
            }

            else{
                binariosColor[filas+3] = 255; 
                binariosColor[filas + 2] = 0;
                binariosColor[filas+ 1] = 0;
                binariosColor[filas] = 0;
                contadorNegros++;
            }
        }
    }

    totalBlanco = contadorBlancos;
    totalNegro = contadorNegros; 
    return binariosColor;
}