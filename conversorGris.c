#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <unistd.h>
#include "cabecerasYfunciones.h"

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
    unsigned char azul, verde, rojo, extra, *grisaseos;
    grisaseos = (unsigned char *)malloc(binformacion->tamano * sizeof(unsigned char));
    for(filas = 0; filas <binformacion->tamano; filas = filas + 4){
        colorGrisaseo = data_imagen[filas+2] * 0.3 + data_imagen[filas+1] * 0.59 + data_imagen[filas] * 0.11;
        grisaseos[filas+3] = 255;
        grisaseos[filas+2] = colorGrisaseo;
        grisaseos[filas+1] = colorGrisaseo;
        grisaseos[filas] = colorGrisaseo;
    }

    return grisaseos;
}

void crearImagen(cabeceraInformacion *binformacion, cabeceraArchivo *bcarchivo_guardado, char *archivoSalida, unsigned char *data_imagen){
    FILE *archivo;  
    uint16_t type;

    archivo = fopen(archivoSalida, "wb" );
    if(!archivo){ 
        printf( "La imagen no se pudo crear\n");
        exit(1);
    }
    binformacion -> compresion = 0;
    type=0x4D42;
    fwrite(&type,sizeof(uint16_t),1,archivo);
    fwrite(&bcarchivo_guardado -> tamano, 4, 1, archivo);
    fwrite(&bcarchivo_guardado -> reservado1, 2, 1, archivo);
    fwrite(&bcarchivo_guardado -> reservado2, 2, 1, archivo);
    fwrite(&bcarchivo_guardado -> offsetBit, 4, 1, archivo);
    fwrite(&binformacion -> tamano, 4, 1, archivo);
    fwrite(&binformacion -> alto, 4, 1, archivo);
    fwrite(&binformacion -> ancho, 4, 1, archivo);
    fwrite(&binformacion -> direcciones, 2, 1, archivo);
    fwrite(&binformacion -> totalBit, 2, 1, archivo);
    fwrite(&binformacion -> compresion, 4, 1, archivo);
    fwrite(&binformacion -> tamanoImagen, 4, 1, archivo);
    fwrite(&binformacion -> XResolporMetros, 4, 1, archivo);
    fwrite(&binformacion -> YResolporMetros,4, 1, archivo);
    fwrite(&binformacion -> colorPixel, 4, 1, archivo);
    fwrite(&binformacion -> coloresImportantes, 4, 1, archivo);
    fseek(archivo,bcarchivo_guardado -> offsetBit, SEEK_SET);
    fwrite(data_imagen, binformacion -> tamanoImagen, 1, archivo);
    fclose(archivo);
}

int main(int argc,char *argv[]) {
    printf("%s %s %s %s \n",argv[0],argv[1],argv[2],argv[3]);
    pid_t pid;
    int status;
    unsigned char *data_grisaseos;
    cabeceraInformacion binformacion;
    cabeceraArchivo bcabecera;
    int tuberia = atoi(argv[3]);
    //lectura de la data en el pipe
    read(tuberia,&bcabecera.tamano,sizeof(uint32_t));
    read(tuberia,&bcabecera.reservado1,sizeof(uint16_t));
    read(tuberia,&bcabecera.reservado2,sizeof(uint16_t));
    read(tuberia,&bcabecera.offsetBit,sizeof(uint32_t));

    read(tuberia,&binformacion.alto,sizeof(uint32_t));
    read(tuberia,&binformacion.ancho,sizeof(uint32_t));
    read(tuberia,&binformacion.coloresImportantes,sizeof(uint32_t));
    read(tuberia,&binformacion.colorPixel,sizeof(uint16_t));
    read(tuberia,&binformacion.compresion,sizeof(uint16_t));
    read(tuberia,&binformacion.direcciones,sizeof(uint32_t));
    read(tuberia,&binformacion.tamano,sizeof(uint32_t));
    read(tuberia,&binformacion.tamanoImagen,sizeof(uint32_t));
    read(tuberia,&binformacion.totalBit,sizeof(uint32_t));
    read(tuberia,&binformacion.XResolporMetros,sizeof(uint32_t));
    read(tuberia,&binformacion.YResolporMetros,sizeof(uint32_t));

    printf("el valor de alto en CONVERSOR GRISSES ES: %d \n",binformacion.alto);
    unsigned char *data_imagen = (unsigned char*)malloc(binformacion.tamanoImagen* sizeof(unsigned char));
    read(110,data_imagen,sizeof(data_imagen));
    crearImagen(&binformacion,&bcabecera,"salida.bmp",data_imagen);
    // for(int i = 0; i<binformacion.tamanoImagen;i++){
    //     if(i<10){
    //         printf("dato: %c ",data_imagen[i]);
    //     }
    // }
    int tamano = atoi(argv[7]);
    //Los parametros que son recibidos como char, se transforma en enteros para su posterior utilizacion
    //data_grisaseos = transformarAGrises(argv[7],argv[15]);
    printf("pude leer la imagen CONVERSOR GRISES\n");
    // pid = fork();
    // if (pid < 0){
    //     printf("Error al crear proceso hijo \n");
    //     return 0;
    // }
    // if(pid == 0){
    //     char *arreglos[] = {
    //         tamano,
    //         NULL};
    //     // execv("./conversorGris.exe",arreglos);
    //     // printf("regrese a el hijo \n");
    // }
    // waitpid(pid, &status, 0);
    // printf("pase por aqui \n");
  return 0;
}
