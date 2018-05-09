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
void transformarAGrises(cabeceraInformacion *binformacion, unsigned char *data_imagen){
    int tuberia[2];
    unsigned char *grisaseos;
    unsigned char *data_imagen;
    pid_t pid;
    int filas, colorGrisaseo;
    int cantidadBits = binformacion -> totalBit/8;
    unsigned char azul, verde, rojo, extra, *grisaseos;

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    // Se crea un fifo con las mismas propiedades que el anterior, para realizar lectura de lo escrito
    char * myfifo = ""/tmp/myfifo"";
    mkfifo(myfifo, 0666);
    int fd1;

    // Se crea un nuevo fifo para guardar lo nuevo escrito
    char * myfifo = ""/tmp/myfifo2"";
    mkfifo(myfifo, 0666);
    int fd2;

    // Leer de FIFO
    fd1 = open(myfifo, O_RDONLY);
    //JESUUUUUSS NO CACHO MUCHO EL READ PARA QUE LO REVISES JAJA TAMBIÉN SE PUEDE USAR FWREAD
    read(fd1, &data_imagen, sizeof(data_imagen));
    close(fd1);
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////

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
         execlp("./binarizarimagen.exe",&binformacion,&data_imagen);
    }
    else{/*
        close(tuberia[0]);
        data_pipe = fdopen(tuberia[1],'w');
        fwrite(NombreArchivo_salida_binario,sizeof(NombreArchivo_salida_binario) , 1, data_pipe);*/


        /////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // Abrir fifo sólo para escritura
        fd2 = open(myfifo2, O_WRONLY);
      
        // Escribir imagen en fifo
        //JESUUUUUSS NO CACHO MUCHO EL WRITE PARA QUE LO REVISES JAJA TAMBIÉN SE PUEDE USAR FWRITE
        write(fd2, &grisaseos, sizeof(grisaseos));
        close(fd2);
        // PODRIAMOS PASAR EL DATA_IMAGEN COMO ARGUMENTO EN EL EXEC
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////

    }
    waitpid(pid,NULL,0); //esperar a que el hijo termine
    free(grisaseos);
}