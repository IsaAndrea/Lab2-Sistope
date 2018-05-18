#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "cabecerasYfunciones.h"


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
            int tamano = binformacion->tamanoImagen;
            return data_imagen;
        }
    }
}


int main(int argc,char *argv[]) {
    printf("argumentos salida en leer imagen: %s ,%s,%s,%s \n",argv[0],argv[1],argv[2],argv[3]);
    pid_t pid;
    int status;
    cabeceraInformacion binformacion;
    cabeceraArchivo bcabecera;
    unsigned char *data_imagen;
    char data1[50],data2[50],data3[50],data4[50],data5[50],data6[50],data7[50],data8[50],data9[50],data10[50],data11[50],data12[50],data13[50],data14[50],data15[50];
    //Los parametros que son recibidos como char, se transforma en enteros para su posterior utilizacion
    data_imagen = leerImagenBMP(argv[0],&binformacion,&bcabecera);
    printf("pude leer la imagen \n");
    pid = fork();
        if (pid < 0){
            printf("Error al crear proceso hijo \n");
            return 0;
        }
    if(pid == 0){
        sprintf(data1, "%d", binformacion.alto);
        sprintf(data2, "%d", binformacion.ancho);
        sprintf(data3, "%d", binformacion.coloresImportantes);
        sprintf(data4, "%d", binformacion.colorPixel);
        sprintf(data5, "%d", binformacion.compresion);
        sprintf(data6, "%d", binformacion.direcciones);
        sprintf(data7, "%d", binformacion.tamano);
        sprintf(data8, "%d", binformacion.tamanoImagen);
        sprintf(data9, "%d", binformacion.totalBit);
        sprintf(data10, "%d", binformacion.XResolporMetros);
        sprintf(data11, "%d", binformacion.YResolporMetros);
        sprintf(data12, "%d", bcabecera.tamano);
        sprintf(data13, "%d", bcabecera.offsetBit);
        sprintf(data14, "%d", bcabecera.reservado1);
        sprintf(data15, "%d", bcabecera.reservado2);
        printf("el valor dentro de la estructura es: %d \n",binformacion.alto);
        printf("el valor guardado en string es: %s \n",data1);
        char *arreglos[] = {
            data1,data2,data3,data4,data5,data6,data7,data8,data9,data10,data11,data12,data13,data14,data15,NULL};
        // execv("./conversorGris.exe",arreglos);
    }
    waitpid(pid, &status, 0);
    printf("pase por aqui en padre de leer imagen \n");
  return 0;
}