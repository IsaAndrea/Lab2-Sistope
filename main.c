#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <stdint.h>
#include <unistd.h>
#include "cabecerasYfunciones.h"

int main(int argc,char **argv){
    int filas, i, j, verificador;
    unsigned char *data_imagen, *grisaseos, *binariosColor;
    cabeceraInformacion binformacion;
    cabeceraArchivo bcabecera;
    bitmaptotal totalPixel;
    int tuberia[2];
    int c, cantidad_imagenes,largo, UMBRAL, UMBRAL_clasificacion;
    int bflag = 0;
    char *NombreArchivo_entrada, *NombreArchivo_salida, *NombreArchivo_salida_bmp, *NombreArchivo_salida_grisaseo, *NombreArchivo_salida_binario; 
    opterr = 0;
    while((c = getopt(argc,argv,"c:u:n:b")) != -1)
        switch(c){
            case 'c':
                sscanf(optarg,"%d",&cantidad_imagenes);
                largo = strlen(optarg);
                NombreArchivo_entrada = malloc(largo + 11);
                NombreArchivo_salida_bmp = malloc(largo + 19);
                NombreArchivo_salida_grisaseo = malloc(largo + 28);
                NombreArchivo_salida_binario = malloc(largo + 27);
                break;
            case 'u':
                
                sscanf(optarg,"%d",&UMBRAL);
                break;
            case 'n':
                sscanf(optarg,"%d",&UMBRAL_clasificacion);
                break;
            case 'b':
                bflag = 1;
                break;
            case '?':
                if(optopt == 'c')
                    fprintf(stderr,"Opcion -%c necesita unargumento \n",optopt);
                else if(isprint(optopt))
                    fprintf(stderr,"Opcion desconocida -%c .\n",optopt);
                else
                    fprintf(stderr,"Opcion con caracter desconocido '\\x%x' . \n",optopt);
                return 1;
            default:
                abort();
        }
    if(cantidad_imagenes <= 0 || UMBRAL <= 0 || UMBRAL_clasificacion <= 0  ){
        printf("ingrese los parametros correctamente sino son superiores a 0 o no son los los indicados no se puede ejecutar el codigo vuelva a ejecutarlo \n");
        return -1;
    }
    else if(cantidad_imagenes > 0 && (UMBRAL < 0 || UMBRAL_clasificacion < 0)){
        printf("ingrese los parametros correctamente sino son superiores a 0 o no son los los indicados no se puede ejecutar el codigo vuelva a ejecutarlo \n");
        return -1;
    }
    else if(UMBRAL_clasificacion > 101){
        printf("ingrese los parametros correctamente sino son superiores a 0 o no son los los indicados no se puede ejecutar el codigo vuelva a ejecutarlo \n");
        return -1;
    }
    while(cantidad_imagenes > 0 && UMBRAL > 0 && UMBRAL_clasificacion > 0 ){
        pipe(tuberia);
        pid = fork();
        if (pid < 0){
            printf("Error al crear proceso hijo \n");
            exit(EXIT_FAILURE);
        }
        if(pid == 0){
            sprintf(archivoEntrada,"imagen_%d.bmp",cantidadImagenes);
            sprintf(archivoGrisaseo,"archivo_salida_grisaseo_%d.bmp",cantidadImagenes);
            sprintf(archivoBinario,"archivo_salida_binario_%d.bmp",cantidadImagenes);
            //conecto las tuberias entre los procesos por si necesito variables
            //ejecuto con exect la funcion de lectura
            }
        //esperamos a los N hijos terminen  
        }
    
    free(binariosColor);
    free(data_imagen);
    free(grisaseos);
    cantidadImagenes -= 1;
    cantidad_imagenes--;
    }
    
}