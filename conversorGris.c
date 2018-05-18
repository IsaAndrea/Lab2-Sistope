#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <unistd.h>

/* Función que aplica una fórmula a los pixeles definidos dentro de una estructura que contiene todos los 
   pixeles de una imagen procesada.
   ENTRADA:
        - Estructura de una cabecera de informacion de un bitmap.
        - Un arreglo de pixeles que representa a la imagen.
   SALIDA:
        - Una matriz de pixeles checkeados.
*/
unsigned char *transformarAGrises(cabeceraInformacion *binformacion, unsigned char *data_imagen){
    int filas, colorGrisaseo;
    int cantidadBits = binformacion -> totalBit/8;
    unsigned char azul, verde, rojo, extra, *grisaseos;

    /*
    int pipeLI[2];
    unsigned char *data_imagen;
    data_imagen = (unsigned char*)malloc(binformacion -> tamanoImagen* sizeof(unsigned char));

    // Cerrar escritura pipe
    close(pipeLI[1]); 
    // Leer data_imagen en pipe y cerrar
    read(pipeLI[0], data_imagen, sizeof(data_imagen));
    close(pipeLI[0]);

    printf("se leyó el pipe\n");*/


    grisaseos = (unsigned char *)malloc(binformacion -> tamanoImagen * sizeof(unsigned char));

    if(cantidadBits == 3){
        for(filas = 0; filas < binformacion -> tamanoImagen; filas = filas + 3){
            colorGrisaseo = data_imagen[filas+2] * 0.3 + data_imagen[filas+1] * 0.59 + data_imagen[filas] * 0.11;
            grisaseos[filas+2] = colorGrisaseo;
            grisaseos[filas+1] = colorGrisaseo;
            grisaseos[filas] = colorGrisaseo;
        }
    }

    if(cantidadBits == 4){
            for(filas = 0; filas <binformacion -> tamanoImagen; filas = filas + 4){
            colorGrisaseo = data_imagen[filas+2] * 0.3 + data_imagen[filas+1] * 0.59 + data_imagen[filas] * 0.11;
            grisaseos[filas+3] = 255;
            grisaseos[filas+2] = colorGrisaseo;
            grisaseos[filas+1] = colorGrisaseo;
            grisaseos[filas] = colorGrisaseo;
        }
    }

    return grisaseos;
}
