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
                execlp("./conversorGris.exe",&binformacion,&data_imagen);
            }
            else{
                close(tuberia[0]);
                data_pipe = fdopen(tuberia[1],'w');
                fwrite(NombreArchivo_salida_binario,sizeof(NombreArchivo_salida_binario) , 1, data_pipe);
            }
            waitpid(pid,NULL,0); //esperar a que el hijo termine
        }
    }
    free(data_imagen);
}