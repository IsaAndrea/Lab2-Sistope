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
unsigned char *transformarAGrises(int binformacionTamano, unsigned char *data_imagen){
    int filas, colorGrisaseo;
    unsigned char azul, verde, rojo, extra, *grisaseos;
    grisaseos = (unsigned char *)malloc(binformacionTamano * sizeof(unsigned char));
    for(filas = 0; filas <binformacionTamano; filas = filas + 4){
        colorGrisaseo = data_imagen[filas+2] * 0.3 + data_imagen[filas+1] * 0.59 + data_imagen[filas] * 0.11;
        grisaseos[filas+3] = 255;
        grisaseos[filas+2] = colorGrisaseo;
        grisaseos[filas+1] = colorGrisaseo;
        grisaseos[filas] = colorGrisaseo;
    }

    return grisaseos;
}

int main(int argc,char *argv[]) {
  pid_t pid;
  int status;
  unsigned char *data_grisaseos;
  int tamano = atoi(argv[7]);
  //Los parametros que son recibidos como char, se transforma en enteros para su posterior utilizacion
  data_grisaseos = transformarAGrises(argv[7],argv[15]);
  printf("pude leer la imagen \n");
  pid = fork();
            if (pid < 0){
                printf("Error al crear proceso hijo \n");
                return 0;
            }
            if(pid == 0){
                char *arreglos[] = {
                    tamano,
                    NULL};
                // execv("./conversorGris.exe",arreglos);
                // printf("regrese a el hijo \n");
            }
            waitpid(pid, &status, 0);
            printf("pase por aqui \n");
  return 0;
}
