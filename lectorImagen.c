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
    int tuberia[2]
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
            pipe(tuberia);
            pid = fork();
            if(pid == 0){
                // compartir tuberias entre estos dos procesos
                // ejecutar conversor de grises
            }
            //esperar a que el hijo temrine
        }
    }
}