#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <stdint.h>
#include <unistd.h>
#include "cabecerasYfunciones.h"

int main(int argc,char **argv){
    int c, cantidadImagenes,largo, UMBRAL, UMBRAL_clasificacion;
    int bflag = 0;
    char *archivoEntrada, *archivoSalidaGrisaseo, *archivoSalidaBinario; 
    opterr = 0;
    while((c = getopt(argc,argv,"c:u:n:b")) != -1)
        switch(c){
            case 'c':
                sscanf(optarg,"%d",&cantidadImagenes);
                largo = strlen(optarg);
                archivoEntrada = malloc(largo + 11);
                archivoSalidaGrisaseo = malloc(largo + 28);
                archivoSalidaBinario = malloc(largo + 27);
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
                    fprintf(stderr,"Opcion -%c necesita un argumento \n",optopt);
                else if(isprint(optopt))
                    fprintf(stderr,"Opcion desconocida -%c .\n",optopt);
                else
                    fprintf(stderr,"Opcion con caracter desconocido '\\x%x' . \n",optopt);
                return 1;
            default:
                abort();
        }
    if(cantidadImagenes <= 0 || UMBRAL <= 0 || UMBRAL_clasificacion <= 0  ){
        printf("ingrese los parametros correctamente sino son superiores a 0 o no son los los indicados no se puede ejecutar el codigo vuelva a ejecutarlo \n");
        return -1;
    }
    else if(cantidadImagenes > 0 && (UMBRAL < 0 || UMBRAL_clasificacion < 0)){
        printf("ingrese los parametros correctamente sino son superiores a 0 o no son los los indicados no se puede ejecutar el codigo vuelva a ejecutarlo \n");
        return -1;
    }
    else if(UMBRAL_clasificacion > 101){
        printf("ingrese los parametros correctamente sino son superiores a 0 o no son los los indicados no se puede ejecutar el codigo vuelva a ejecutarlo \n");
        return -1;
    }
    while(cantidadImagenes > 0 && UMBRAL > 0 && UMBRAL_clasificacion > 0 ){
        procesarImagenes(cantidadImagenes, UMBRAL, UMBRAL_clasificacion, bflag, archivoEntrada, archivoSalidaBinario, archivoSalidaGrisaseo);
        cantidadImagenes--;
    }
    
}

