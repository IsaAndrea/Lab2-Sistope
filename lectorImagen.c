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
unsigned char *leerImagenBMP(char *nombreArchivo, cabeceraInformacion *binformacion, cabeceraArchivo *bcabecera){
    FILE *archivo;
    uint16_t type;
    unsigned char *data_imagen;
   // int pipeLI[2];
 
    archivo = fopen(nombreArchivo , "r");
    if(!archivo){
        printf("No se pudo leer la imagen");
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
         
        data_imagen = (unsigned char*)malloc(binformacion -> tamanoImagen* sizeof(unsigned char));
        if(!data_imagen){
            fclose(archivo);
            return 0;
        }

        else{
            fseek(archivo, bcabecera -> offsetBit, SEEK_SET);
            fread(data_imagen, binformacion -> tamanoImagen, 1, archivo);  
            fclose(archivo);

            /*
            close(pipeLI[0]);  // Cerrar lectura pipe
 
            // Escribir data_imagen en pipe y cerrar
            write(pipeLI[1], data_imagen, sizeof(data_imagen));
            close(pipeLI[1]);
            */
     

            return data_imagen;
        }
    }
}