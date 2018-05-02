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
void binarizarImagen(cabeceraInformacion *binformacion, unsigned char *data_grisaseo, int UMBRAL, bitmaptotal *total_pixel){
    unsigned char *binariosColor;
    int tuberia[2];
    pid_t pid;
    int columnas;
    int contadorTotal = 0;
    int contadorNegros = 0;
    int contadorBlancos = 0;
    int filas = 0;
    unsigned char data, *binariosColor;
    binariosColor = (unsigned char *)malloc(binformacion -> tamanoImagen * sizeof(unsigned char));
    for(filas = 0; filas < binformacion -> tamanoImagen; filas = filas + 4){
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
    totalPixel -> totalBlancos = contadorBlancos;
    totalPixel -> totalNegros = contadorNegros;
    pid = fork();
    if (pid < 0){
        printf("Error al crear proceso hijo \n");
        exit(EXIT_FAILURE);
    }
    if(pid == 0){
         execlp("./conversorGris.exe",&binformacion,&data_imagen);
    }
    else{
        close(tuberia[0]);
        data_pipe = fdopen(tuberia[1],'w');
        fwrite(NombreArchivo_salida_binario,sizeof(NombreArchivo_salida_binario) , 1, data_pipe);
    }
    waitpid(pid,NULL,0); //esperar a que el hijo termine
    free(binariosColor);
}