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
void transformarAGrises(unsigned char *data_imagen){
    int tuberia[2];
    pid_t pid;
    int filas, colorGrisaseo;
    int cantidadBits = binformacion -> totalBit/8;
    unsigned char azul, verde, rojo, extra, *grisaseos;
    cabeceraInformacion *binformacion;

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    // Se crea un fifo con las mismas propiedades de main para para realizar lectura de binformacion
    char * myfifo = "./myfifo";
    mkfifo(myfifo, 0666);
    int fd;

    // Leer de FIFO binformacion
    fd = open(myfifo, O_RDONLY);
    read(fd, &binformacion, sizeof(binformacion));
    close(fd);


    grisaseos = (unsigned char *)malloc(binformacion -> tamanoImagen * sizeof(unsigned char));
    for(filas = 0; filas <binformacion -> tamanoImagen; filas = filas + 4){
        colorGrisaseo = data_imagen[filas+2] * 0.3 + data_imagen[filas+1] * 0.59 + data_imagen[filas] * 0.11;
        grisaseos[filas+3] = 255;
        grisaseos[filas+2] = colorGrisaseo;
        grisaseos[filas+1] = colorGrisaseo;
        grisaseos[filas] = colorGrisaseo;
    }
    pipe(tuberia);
    pid = fork();
    if (pid < 0){
        printf("Error al crear proceso hijo \n");
        exit(EXIT_FAILURE);
    }
    if(pid == 0){
         execlp("./binarizadorimagen.exe", &grisaseos);
    }
    else{/*
        close(tuberia[0]);
        data_pipe = fdopen(tuberia[1],'w');
        fwrite(NombreArchivo_salida_binario,sizeof(NombreArchivo_salida_binario) , 1, data_pipe);*/


    }
    waitpid(pid,NULL,0); //esperar a que el hijo termine
    free(grisaseos);
}