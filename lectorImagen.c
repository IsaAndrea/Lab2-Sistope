#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

/*Función que permite retornar una imagen leida en bit almacenada en una variable data_imagen
  Ademas permite rellenar las estructuras de la cabecera y la informacion del bitmap 
  ENTRADA:
        - Puntero al nombre del archivo a leer
        - Estructura de una cabecera de informacion de un bitmap
        
  SALIDA:
        - Un arreglo de char de una imagen leida
*/
void leerImagenBMP(char *nombreArchivo, cabeceraInformacion *binformacion, cabeceraArchivo *bcabecera){
    unsigned char *data_imagen;
    pid_t pid;
    FILE *archivo;
    uint16_t type;
    unsigned char *data_procesada;
    archivo = fopen(nombreArchivo , "r");
    int cantidadImagenes, UMBRAL, UMBRAL_clasificacion;
    char *archivoBinario; 
    bitmaptotal totalPixel;


    /*
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    // Se crea un fifo con las mismas propiedades que el anterior, para realizar lectura de lo escrito
    char * myfifo = "./myfifo";
    mkfifo(myfifo, 0666);
    int fd;*/

    // Se crea un nuevo fifo para guardar data_imagen
    char * myfifo = "./myfifo1";
    mkfifo(myfifo, 0666);
    int fd1;

    /*
    // Abrir fifo sólo para lectura
    fd = open(myfifo, O_RDONLY);
    // leer de fifo 
    read(fd, archivoBinario, sizeof(archivoBinario));
    read(fd, UMBRAL, 4);
    read(fd, UMBRAL_clasificacion, 4);
    read(fd, cantidadImagenes, 4);
    read(fd, &totalPixel, sizeof(bitmaptotal));
    close(fd);
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    */

    if(!archivo){
        return NULL;
    }

    else{
        fread(&type, sizeof(uint16_t), 1, archivo);
        if(type != 0x4D42){
            printf("La imagen no es de tipo bmp");
            fclose(archivo);
            return NULL;
        }

        fread(bcabecera, sizeof(cabeceraArchivo), 1, archivo);
        fread(binformacion, sizeof(cabeceraInformacion), 1, archivo);
         
        data_procesada = (unsigned char*)malloc(binformacion -> tamanoImagen* sizeof(unsigned char));
        if(!data_procesada){
            fclose(archivo);
            return 0;
        }

        else{
            fseek(archivo, bcabecera -> offsetBit, SEEK_SET);
            fread(data_procesada, binformacion -> tamanoImagen, 1, archivo);  
            fclose(archivo);
            pid = fork();
            if (pid < 0){
               printf("Error al crear proceso hijo \n");
               exit(EXIT_FAILURE);
            }
            if(pid == 0){
       //         execlp("./conversorGris.exe",&binformacion,&data_imagen);
                execlp("./conversorGris.exe",&data_imagen);
            }
            else{
            /*
                close(tuberia[0]);
                data_pipe = fdopen(tuberia[1],'w');
                fwrite(NombreArchivo_salida_binario,sizeof(NombreArchivo_salida_binario) , 1, data_pipe);*/


                /////////////////////////////////////////////////////////////////////////////////////////////////////
                /////////////////////////////////////////////////////////////////////////////////////////////////////
                // Abrir fifo sólo para escritura
                fd1 = open(myfifo1, O_WRONLY);
      
                // Escribir data_imagen en fifo
                write(fd1, &data_imagen, sizeof(data_imagen));
                /*
                write(fd1, archivoBinario, sizeof(archivoBinario));
                write(fd1, UMBRAL, 4);
                write(fd1, UMBRAL_clasificacion, 4);
                write(fd1, cantidadImagenes, 4);
                write(fd1, &totalPixel, sizeof(bitmaptotal));
                close(fd1);*/
                /////////////////////////////////////////////////////////////////////////////////////////////////////
                /////////////////////////////////////////////////////////////////////////////////////////////////////
         

            }
            waitpid(pid,NULL,0); //esperar a que el hijo termine
        }
    }
    free(data_imagen);
}